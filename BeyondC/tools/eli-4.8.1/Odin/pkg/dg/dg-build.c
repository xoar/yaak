/*
Copyright (C) 1991 Geoffrey M. Clemm

This file is part of the Odin system.

The Odin system is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation (see the file COPYING).

The Odin system is distributed WITHOUT ANY WARRANTY, without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

geoff@boulder.colorado.edu
*/

#include <stdio.h>
#include "inc/GMC.h"
#include "inc/DG_Version.h"
#include "inc/Entry.h"
#include "inc/FTClass_.h"
#include "inc/InpSpc.h"
#include "inc/InpKind_.h"
#include "inc/ISKind_.h"
#include "inc/NodTyp_.h"
#include "inc/Str.h"
#include "inc/TClass_.h"
#include "inc/Tool.h"

extern int	num_SrcTypS, num_FilTypS, num_PrmTypS, num_EnvVarS,
		num_EnvVarLstS, num_ToolS, num_InpEdgS,
		num_MemEdgS, num_EqvEdgS, num_CastEdgS, num_DrvEdgS,
		num_PrmTypLstS, num_InpSpcS;

static tp_Str 		Banner = NIL;

static tp_InpSpc	NoInputInpSpc;


static tp_InpSpc Nod_InpSpc(GMC_P1(tp_Nod) GMC_PN(tp_Tool));


void
Init_InpSpcs()
{
   NoInputInpSpc = New_InpSpc();
   NoInputInpSpc->ISKind = ISK_Drv;
   NoInputInpSpc->FilTyp = NoInputFilTyp;
   }/*Init_InpSpcs*/


static tp_FilTyp
Make_FilTyp(DrvNod)
   tp_Nod DrvNod;
{
   FORBIDDEN(Nod_NodTyp(DrvNod) != NOD_Word);
   return Lookup_FilTyp(Sym_Str(Nod_Sym(DrvNod)));
   }/*Make_FilTyp*/


static tp_FilTyp
Make_SecOrdFilTyp(DrvNod)
   tp_Nod DrvNod;
{
   FORBIDDEN(Nod_NodTyp(DrvNod) != NOD_SecOrdDrvOpr);
   return Lookup_SecOrdFilTyp(Sym_Str(Nod_Sym(Nod_Son(1, DrvNod))),
			      Make_FilTyp(Nod_Son(2, DrvNod)));
   }/*Make_SecOrdFilTyp*/


static tp_PrmTyp
Make_PrmTyp(DrvNod)
   tp_Nod DrvNod;
{
   FORBIDDEN(Nod_NodTyp(DrvNod) != NOD_Word);
   return Lookup_PrmTyp(Sym_Str(Nod_Sym(DrvNod)));
   }/*Make_PrmTyp*/


static void
Declare_SrcTyp(EntryNod)
   tp_Nod EntryNod;
{
   tp_Nod PatternNod;
   tp_SrcTyp SrcTyp;
   boolean IsPrefix;
   tp_Pattern Pattern;

   PatternNod = Nod_Son(1, EntryNod);
   IsPrefix = (Nod_NodTyp(PatternNod) == NOD_Prefix);
   Pattern = Sym_Str(Nod_Sym(Nod_Son(1, PatternNod)));
   if (Pattern == NIL) Pattern = "";
   SrcTyp = Lookup_SrcTyp(Pattern, IsPrefix);
   if (SrcTyp_FilTyp(SrcTyp) != NIL) {
      if (strcmp(FilTyp_FTName(SrcTyp_FilTyp(SrcTyp)),
		 Sym_Str(Nod_Sym(Nod_Son(2, EntryNod)))) != 0) {
	 if (!IsPrefix) Write(StdOutFD, "*");
	 Write(StdOutFD, Pattern);
	 if (IsPrefix) Write(StdOutFD, "*");
	 Writeln (StdOutFD,
		  " : pattern already declared - redefinition ignored.");
	 }/*if*/;
      return; }/*if*/;
   Set_SrcTyp_FilTyp(SrcTyp, Make_FilTyp(Nod_Son(2, EntryNod)));
   }/*Declare_SrcTyp*/


static void
Make_VarWord(StrPtr, IsEnvVarPtr, VarWordNod, Tool)
   tp_Str *StrPtr;
   boolean *IsEnvVarPtr;
   tp_Nod VarWordNod;
   tp_Tool Tool;
{
   tp_EnvVar EnvVar;

   if (Nod_NodTyp(VarWordNod) == NOD_VarWord) {
      *StrPtr = Sym_Str(Nod_Sym(Nod_Son(1, VarWordNod)));
      *IsEnvVarPtr = TRUE;
      EnvVar = Lookup_EnvVar(*StrPtr);
      Set_Tool_EnvVarLst(Tool, Union_EnvVarLst(Tool_EnvVarLst(Tool),
					       Make_EnvVarLst(EnvVar)));
      return; }/*if*/;
   *StrPtr = Sym_Str(Nod_Sym(VarWordNod));
   *IsEnvVarPtr = FALSE;
   }/*Make_VarWord*/


static void
Set_InpSpcPrmVal(InpSpc, Nod, Tool)
   tp_InpSpc InpSpc;
   tp_Nod Nod;
   tp_Tool Tool;
{
   if (Nod_NodTyp(Nod) == NOD_OdinExpr) {
      InpSpc->InpSpc = Nod_InpSpc(Nod, Tool);
      Add_HomInpEdg(InpSpc->InpSpc, Tool);
      return; }/*if*/;
   Make_VarWord(&InpSpc->Str, &InpSpc->IsEnvVar, Nod, Tool);
   }/*Set_InpSpcPrmVal*/


static tp_InpSpc
Nod_InpSpc(InpNod, Tool)
   tp_Nod InpNod;
   tp_Tool Tool;
{
   tp_Nod RootNod, OprNod, ValsNod, ValNod;
   tp_InpSpc InpSpc, InpSpcElm, PrvInpSpc, ValInpSpc, PrvValInpSpc;
   tps_Str StrBuf;

   if (Nod_NodTyp(InpNod) == NOD_Word || Nod_NodTyp(InpNod) == NOD_VarWord) {
      InpSpc = New_InpSpc();
      InpSpc->ISKind = ISK_Str;
      Make_VarWord(&InpSpc->Str, &InpSpc->IsEnvVar, InpNod, Tool);
      return InpSpc; }/*if*/;

   OprNod = InpNod;
   PrvInpSpc = NIL;

   if (Nod_NodTyp(OprNod) == NOD_OdinExpr) {
      RootNod = Nod_Son(1, OprNod);
      OprNod = Nod_Brother(RootNod);
      InpSpc = New_InpSpc();
      PrvInpSpc = InpSpc;
      switch (Nod_NodTyp(RootNod)) {
	 case NOD_Word: case NOD_VarWord: {
	    InpSpc->ISKind = ISK_Key;
	    Make_VarWord(&InpSpc->Str, &InpSpc->IsEnvVar, RootNod, Tool);
	    break;}/*case*/;
	 case NOD_DrvInput: {
	    InpSpc->ISKind = ISK_Drv;
	    InpSpc->FilTyp = Make_FilTyp(Nod_Son(1, RootNod));
	    break;}/*case*/;
	 case NOD_PrmInput: {
	    InpSpc->ISKind = ISK_Prm;
	    InpSpc->PrmTyp = Make_PrmTyp(Nod_Son(1, RootNod));
	    Tool->BasePrmTypLst = Union_PrmTypLst
	     (Tool->BasePrmTypLst, Make_PrmTypLst(InpSpc->PrmTyp));
	    break;}/*case*/;
	 case NOD_EmptyFile: {
	    InpSpc->ISKind = ISK_EmptyFile;
	    break;}/*case*/;
	 case NOD_AbsRoot: {
	    InpSpc->ISKind = ISK_Sel;
	    break;}/*case*/;
	 case NOD_AbsFile: {
	    InpSpc->ISKind = ISK_Sel;
	    Make_VarWord
	     (&InpSpc->Str, &InpSpc->IsEnvVar, Nod_Son(1, RootNod), Tool);
	    break;}/*case*/;
	 case NOD_VirSelOpr: {
	    InpSpc->ISKind = ISK_VTgt;
	    Make_VarWord
	     (&InpSpc->Str, &InpSpc->IsEnvVar, Nod_Son(1, RootNod), Tool);
	    break;}/*case*/;
	 default: {
	    FATALERROR("Unexpected NodTyp.\n"); };}/*switch*/; }/*if*/;

   if (Nod_NodTyp(OprNod) == NOD_Oprs) OprNod = Nod_Son(1, OprNod);
   for (; OprNod!=NIL; OprNod=Nod_Brother(OprNod)) {
      InpSpcElm = New_InpSpc();
      /*select*/{
	 if (PrvInpSpc == NIL) {
	    InpSpc = InpSpcElm;
	 }else{
	    PrvInpSpc->Next = InpSpcElm; };}/*select*/;
      switch (Nod_NodTyp(OprNod)) {
	 case NOD_PrmOpr: {
	    InpSpcElm->ISKind = ISK_Prm;
	    InpSpcElm->PrmTyp = Make_PrmTyp(Nod_Son(1, OprNod));
	    if (Nod_NumSons(OprNod) > 1) {
	       ValsNod = Nod_Son(2, OprNod);
	       /*select*/{
		  if (Nod_NumSons(ValsNod) == 1) {
		     Set_InpSpcPrmVal(InpSpcElm, Nod_Son(1, ValsNod), Tool);
		  }else{
		     PrvValInpSpc = NIL;
		     for (ValNod = Nod_Son(1, ValsNod);
			  ValNod != NIL;
			  ValNod = Nod_Brother(ValNod)) {
			ValInpSpc = New_InpSpc();
			/*select*/{
			   if (PrvValInpSpc == NIL) {
			      InpSpcElm->InpSpc = ValInpSpc;
			   }else{
			      PrvValInpSpc->Next = ValInpSpc; };}/*select*/;
			PrvValInpSpc = ValInpSpc;
			ValInpSpc->ISKind = ISK_PrmVal;
			ValInpSpc->PrmTyp = InpSpcElm->PrmTyp;
			Set_InpSpcPrmVal(ValInpSpc, ValNod, Tool);
			}/*for*/; };}/*select*/; }/*if*/;
	    break;}/*case*/;
	 case NOD_AplOpr: {
	    InpSpcElm->ISKind = ISK_Prm;
	    InpSpcElm->PrmTyp = ApplyPrmTyp;
	    Set_InpSpcPrmVal(InpSpcElm, Nod_Son(1, OprNod), Tool);
	    InpSpcElm->Next = New_InpSpc();
	    InpSpcElm = InpSpcElm->Next;
	    InpSpcElm->ISKind = ISK_Drv;
	    InpSpcElm->FilTyp = ApplyFilTyp;
	    break;}/*case*/;
	 case NOD_DrvOpr: {
	    InpSpcElm->ISKind = ISK_Drv;
	    InpSpcElm->FilTyp = Make_FilTyp(Nod_Son(1, OprNod));
	    break;}/*case*/;
	 case NOD_SecOrdDrvOpr: {
	    InpSpcElm->ISKind = ISK_Drv;
	    InpSpcElm->FilTyp = Make_SecOrdFilTyp(OprNod);
	    break;}/*case*/;
	 case NOD_SelOpr: {
	    InpSpcElm->ISKind = ISK_Sel;
	    Make_VarWord(&InpSpcElm->Str, &InpSpcElm->IsEnvVar,
			 Nod_Son(1, OprNod), Tool);
	    break;}/*case*/;
	 case NOD_DirOpr: {
	    InpSpcElm->ISKind = ISK_Sel;
	    break;}/*case*/;
	 case NOD_VirSelOpr: {
	    InpSpcElm->ISKind = ISK_VTgt;
	    Make_VarWord(&InpSpcElm->Str, &InpSpcElm->IsEnvVar,
			 Nod_Son(1, OprNod), Tool);
	    break;}/*case*/;
	 default: {
	    FATALERROR("bad operator node type"); };}/*switch*/;
      PrvInpSpc = InpSpcElm; }/*for*/;
   return InpSpc;
   }/*Nod_InpSpc*/


static void
Make_Desc(DescPtr, HiddenPtr, DescNod)
   tp_Desc *DescPtr;
   boolean *HiddenPtr;
   tp_Nod DescNod;
{
   tp_Nod StrNod;

   /*select*/{
      if (Nod_NodTyp(DescNod) == NOD_Hidden) {
	 StrNod = Nod_Son(1, DescNod);
	 *HiddenPtr = TRUE;
      }else{
	 StrNod = DescNod;
	 *HiddenPtr = FALSE; };}/*select*/;
   *DescPtr = Sym_Str(Nod_Sym(StrNod));
   }/*Make_Desc*/


static void
Declare_ObjTyp(EntryNod)
   tp_Nod EntryNod;
{
   tp_FilTyp FilTyp;
   tp_Desc Desc;
   boolean Hidden;
   tp_Nod Nod;

   FilTyp = Make_FilTyp(Nod_Son(1, EntryNod));
   if (FilTyp_Desc(FilTyp) == NIL) {
      Make_Desc(&Desc, &Hidden, Nod_Son(2, EntryNod));
      Set_FilTyp_Desc(FilTyp, Desc, Hidden); }/*if*/;
   for (Nod = Nod_Son(3, EntryNod); Nod != NIL; Nod = Nod_Brother(Nod)) {
      /*select*/{
	 if (Nod_NodTyp(Nod) == NOD_BaseSupertype) {
	    Add_CastEdg(FilTyp, Make_FilTyp(Nod_Son(1, Nod)));
	 }else{
	    Add_EqvEdg(FilTyp, Make_FilTyp(Nod)); };}/*select*/; }/*for*/;
   }/*Declare_ObjTyp*/


static void
Declare_PrmTyp(EntryNod)
   tp_Nod EntryNod;
{
   tp_PrmTyp PrmTyp;
   tp_FilTyp FilTyp;
   tp_Desc Desc;
   boolean Hidden;

   PrmTyp = Make_PrmTyp(Nod_Son(1, EntryNod));
   FilTyp = Make_FilTyp(Nod_Son(3, EntryNod));
   if (PrmTyp_Desc(PrmTyp) == NIL) {
      Make_Desc(&Desc, &Hidden, Nod_Son(2, EntryNod));
      Set_PrmTyp_Desc(PrmTyp, Desc, Hidden);
      Set_PrmTyp_FilTyp(PrmTyp, FilTyp);
      return; }/*if*/;
   if (PrmTyp_FilTyp(PrmTyp) == FilTyp) {
      return; }/*if*/;
   if (PrmTyp_FilTyp(PrmTyp) == VoidFilTyp) {
      Set_PrmTyp_FilTyp(PrmTyp, FilTyp);
      return; }/*if*/;
   SystemError("Parameter value for +%s cannot be both :%s and :%s.\n",
	       PrmTyp_PTName(PrmTyp), FilTyp_FTName(FilTyp),
	       FilTyp_FTName(PrmTyp_FilTyp(PrmTyp)));
   }/*Declare_PrmTyp*/


static void
Declare_EnvVar(EntryNod)
   tp_Nod EntryNod;
{
   tp_EnvVar EnvVar;
   tp_Desc Desc;
   tp_Str Default;
   boolean Hidden, IsFile;
   tps_Str StrBuf;

   EnvVar = Lookup_EnvVar(Sym_Str(Nod_Sym(Nod_Son(1, EntryNod))));
   if (EnvVar_Desc(EnvVar) == NIL) {
      Make_Desc(&Desc, &Hidden, Nod_Son(2, EntryNod));
      Set_EnvVar_Desc(EnvVar, Desc, Hidden);
      /*select*/{
	 if (Nod_NodTyp(Nod_Son(3, EntryNod)) == NOD_OdinExpr) {
	    YY_Unparse(StrBuf, Nod_Son(3, EntryNod));
	    Default = Sym_Str(Str_Sym(StrBuf));
	    IsFile = TRUE;
	 }else{
	    Default = Sym_Str(Nod_Sym(Nod_Son(3, EntryNod)));
	    IsFile = FALSE; };}/*select*/;
      Set_EnvVar_Default(EnvVar, Default, IsFile); }/*if*/;
   }/*Declare_EnvVar*/


static tp_FilTyp
Make_OutputFilTyp(Package, ToolPackage, Nod)
   tp_Package Package, ToolPackage;
   tp_Nod Nod;
{
   tp_FilTyp FilTyp, OutFilTyp;

   FilTyp = Make_FilTyp(Nod);
   OutFilTyp = Create_OutputFilTyp(Package, ToolPackage, Sym_Str(Nod_Sym(Nod)));
   Add_EqvEdg(OutFilTyp, FilTyp);
   return OutFilTyp;
   }/*Make_OutputFilTyp*/


static tp_FilTyp
Make_ToolFilTyp(Package, ToolPackage, ResultNod)
   tp_Package Package, ToolPackage;
   tp_Nod ResultNod;
{
   tp_Nod Nod;
   tp_FilTyp FilTyp, MemFilTyp;
   tp_Tool Tool;
   tp_InpSpc InpSpc;

   if (Nod_Brother(ResultNod) == NIL) {
      return Make_OutputFilTyp(Package, ToolPackage, ResultNod); }/*if*/;

   FORBIDDEN(ToolPackage != Package);
   FilTyp = Create_StructFilTyp(Package, Sym_Str(Nod_Sym(ResultNod)));
   for (Nod = ResultNod; Nod != NIL; Nod = Nod_Brother(Nod)) {
      MemFilTyp = Make_OutputFilTyp(Package, ToolPackage, Nod);
      Tool = New_Tool();
      Tool->FilTyp = MemFilTyp;
      Tool->TClass = TC_StructMem;
      InpSpc = New_InpSpc();
      InpSpc->ISKind = ISK_Drv;
      InpSpc->FilTyp = FilTyp;
      Add_InpEdg(InpSpc, IK_Simple, FALSE, Tool);
      Set_Tool(MemFilTyp, Tool);
      Add_MemEdg(FilTyp, MemFilTyp); }/*for*/;
   return FilTyp;
   }/*Make_ToolFilTyp*/


static void
Add_InpTyps(Tool, ArgsNod, IsUserArg)
   tp_Tool Tool;
   tp_Nod ArgsNod;
   boolean IsUserArg;
{
   tp_Nod FirstNod, ArgNod, InpNod;
   tp_InpKind InpKind;
   tp_InpSpc InpSpc;

   FirstNod = Nod_Son(1, ArgsNod);
   for (ArgNod = FirstNod; ArgNod != NIL; ArgNod = Nod_Brother(ArgNod)) {
      InpNod = ArgNod;
      InpKind = IK_Trans;
      if (Nod_NodTyp(InpNod) == NOD_ErrOKInput) {
	 InpNod = Nod_Son(1, InpNod);
	 InpKind = IK_AnyOK; }/*if*/;
      if (Nod_NodTyp(InpNod) == NOD_NameInput) {
	 InpNod = Nod_Son(1, InpNod);
	 InpKind = IK_TransName; }/*if*/;
      InpSpc = Nod_InpSpc(InpNod, Tool);
      Add_InpEdg(InpSpc, InpKind, IsUserArg, Tool); }/*for*/;
   }/*Add_InpTyps*/


static void
Declare_Tool(Package, EntryNod)
   tp_Package Package;
   tp_Nod EntryNod;
{
   tp_Tool Tool;
   tp_Package ToolPackage;
   tp_FilTyp FilTyp;
   tp_Str ToolName;
   tp_Nod ResultNod;

   ToolName = Sym_Str(Nod_Sym(Nod_Son(1, EntryNod)));
   ToolPackage = Package;
   ResultNod = Nod_Son(1, Nod_Son(4, EntryNod));
   if (Nod_NodTyp(ResultNod) == NOD_ForeignResult) {
      ToolPackage = Sym_Str(Nod_Sym(Nod_Son(1, ResultNod)));
      ResultNod = Nod_Son(2, ResultNod); }/*if*/;
   FilTyp = Make_ToolFilTyp(Package, ToolPackage, ResultNod);
   Tool = FilTyp_Tool(FilTyp);
   if (Tool == NIL) {
      Tool = New_Tool();
      Set_Tool(FilTyp, Tool);
      Tool->FilTyp = FilTyp;
      Tool->Package = ToolPackage; }/*if*/;
   Add_InpTyps(Tool, Nod_Son(2, EntryNod), TRUE);
   Add_InpTyps(Tool, Nod_Son(3, EntryNod), FALSE);
   if (!HasInput(Tool)) {
      Add_InpEdg(NoInputInpSpc, IK_Simple, FALSE, Tool); }/*if*/;
   /*select*/{
      if (strcmp(ToolName, "EXEC") == 0) {
	 Tool->TClass = TC_External;
      }else if (strcmp(ToolName, "COLLECT") == 0) {
	 Tool->TClass = TC_Collect;
	 Set_SystemTool_InpKinds(Tool, IK_Name);
      }else if (strcmp(ToolName, "READ-LIST") == 0) {
	 Tool->TClass = TC_ReadList;
	 Set_SystemTool_InpKinds(Tool, IK_Simple);
      }else if (strcmp(ToolName, "READ-REFERENCE") == 0) {
	 Tool->TClass = TC_ReadList;
	 Set_SystemTool_InpKinds(Tool, IK_Simple);
      }else if (strcmp(ToolName, "SOURCES") == 0) {
	 Tool->TClass = TC_SrcNames;
	 Set_SystemTool_InpKinds(Tool, IK_Simple);
      }else if (strcmp(ToolName, "OPERATIONS") == 0) {
	 Tool->TClass = TC_OpNames;
	 Set_SystemTool_InpKinds(Tool, IK_Simple);
      }else if (strcmp(ToolName, "READ-VIEW-SPECIFICATION") == 0) {
	 Tool->TClass = TC_ViewSpec;
	 Set_SystemTool_InpKinds(Tool, IK_Simple);
      }else if (strcmp(ToolName, "COMPUTE-VIEW") == 0) {
	 Tool->TClass = TC_CmptView;
	 Set_SystemTool_InpKinds(Tool, IK_Trans);
      }else if (strcmp(ToolName, "DIRECTORY") == 0) {
	 Tool->TClass = TC_Directory;
	 Set_SystemTool_InpKinds(Tool, IK_TransName);
      }else if (strcmp(ToolName, "LABEL") == 0) {
	 Tool->TClass = TC_Label;
	 Set_SystemTool_InpKinds(Tool, IK_Name);
      }else if (strcmp(ToolName, "LABELS") == 0) {
	 Tool->TClass = TC_Labels;
	 Set_SystemTool_InpKinds(Tool, IK_TransName);
      }else if (strcmp(ToolName, "ID") == 0) {
	 Tool->TClass = TC_Id;
	 Set_SystemTool_InpKinds(Tool, IK_Name);
      }else if (strcmp(ToolName, "DEPEND") == 0) {
	 Tool->TClass = TC_Depend;
	 Set_SystemTool_InpKinds(Tool, IK_Trans);
      }else if (strcmp(ToolName, "ERROR") == 0) {
	 Tool->TClass = TC_Error;
	 Set_SystemTool_InpKinds(Tool, IK_Trans);
      }else if (strcmp(ToolName, "WARNING") == 0) {
	 Tool->TClass = TC_Warning;
	 Set_SystemTool_InpKinds(Tool, IK_Trans);
      }else if (strcmp(ToolName, "NAME") == 0) {
	 Tool->TClass = TC_Name;
	 Set_SystemTool_InpKinds(Tool, IK_Name);
      }else if (strcmp(ToolName, "NAMES") == 0) {
	 Tool->TClass = TC_Names;
	 Set_SystemTool_InpKinds(Tool, IK_TransName);
      }else if (strcmp(ToolName, "FILENAME") == 0) {
	 Tool->TClass = TC_FileName;
	 Set_SystemTool_InpKinds(Tool, IK_TransName);
      }else if (strcmp(ToolName, "FILENAMES") == 0) {
	 Tool->TClass = TC_FileNames;
	 Set_SystemTool_InpKinds(Tool, IK_TransName);
      }else if (strcmp(ToolName, "CONCATENATE") == 0) {
	 Tool->TClass = TC_Cat;
	 Set_SystemTool_InpKinds(Tool, IK_Trans);
      }else if (strcmp(ToolName, "UNION") == 0) {
	 Tool->TClass = TC_Union;
	 Set_SystemTool_InpKinds(Tool, IK_TransName);
      }else if (strcmp(ToolName, "TARGETSPTR") == 0) {
	 Tool->TClass = TC_TargetsPtr;
	 Set_SystemTool_InpKinds(Tool, IK_Simple);
      }else if (strcmp(ToolName, "TARGETSINC") == 0) {
	 Tool->TClass = TC_TargetsInc;
	 Set_SystemTool_InpKinds(Tool, IK_Simple);
      }else if (strcmp(ToolName, "TARGETS") == 0) {
	 Tool->TClass = TC_Targets;
	 Set_SystemTool_InpKind(Tool, 1, IK_Simple);
	 Set_SystemTool_InpKind(Tool, 2, IK_AnyOK);
      }else if (strcmp(ToolName, "ACTTARGETS") == 0) {
	 Tool->TClass = TC_ActTargets;
	 Set_SystemTool_InpKinds(Tool, IK_Simple);
      }else if (strcmp(ToolName, "VIRTARGETS") == 0) {
	 Tool->TClass = TC_VirTargets;
	 Set_SystemTool_InpKinds(Tool, IK_Simple);
      }else if (strcmp(ToolName, "VIRDIR") == 0) {
	 Tool->TClass = TC_VirDir;
	 Set_SystemTool_InpKinds(Tool, IK_TransName);
      }else if (strcmp(ToolName, "COPYCMD") == 0) {
	 Tool->TClass = TC_CopyCmd;
	 Set_SystemTool_InpKind(Tool, 1, IK_Trans);
	 Set_SystemTool_InpKind(Tool, 2, IK_AnyOK);
      }else if (strcmp(ToolName, "EXPANDHOOKS") == 0) {
	 Tool->TClass = TC_ExpandHooks;
	 Set_SystemTool_InpKinds(Tool, IK_Trans);
      }else if (strcmp(ToolName, "NESTEDHOOKS") == 0) {
	 Tool->TClass = TC_NestedHooks;
	 Set_SystemTool_InpKinds(Tool, IK_Simple);
      }else if (strcmp(ToolName, "PRMVALUES") == 0) {
	 Tool->TClass = TC_PrmValues;
	 Set_SystemTool_InpKinds(Tool, IK_Name);
      }else if (strcmp(ToolName, "FIRST") == 0) {
	 Tool->TClass = TC_First;
	 Set_SystemTool_InpKinds(Tool, IK_Simple);
      }else if (strcmp(ToolName, "APPLY") == 0) {
	 Tool->TClass = TC_Apply;
	 Set_SystemTool_InpKind(Tool, 1, IK_Name);
	 Set_SystemTool_InpKind(Tool, 2, IK_Trans);
      }else if (strcmp(ToolName, "PREFIXHELP") == 0) {
	 Tool->TClass = TC_PrefixHelp;
	 Set_SystemTool_InpKind(Tool, 1, IK_Name);
      }else if (strcmp(ToolName, "SUFFIXHELP") == 0) {
	 Tool->TClass = TC_SuffixHelp;
	 Set_SystemTool_InpKind(Tool, 1, IK_Name);
      }else if (strcmp(ToolName, "DRVHELP") == 0) {
	 Tool->TClass = TC_DrvHelp;
	 Set_SystemTool_InpKind(Tool, 1, IK_TransName);
      }else if (strcmp(ToolName, "PRMHELP") == 0) {
	 Tool->TClass = TC_PrmHelp;
	 Set_SystemTool_InpKind(Tool, 1, IK_TransName);
      }else{
	 SystemError("Unknown tool: %s.\n", ToolName);
	 Tool->TClass = TC_External;
	 Set_SystemTool_InpKinds(Tool, IK_Name); };}/*select*/;
   }/*Declare_Tool*/


void
Build_DerivationGraph(ToolDirName, Package)
   tp_FileName ToolDirName;
   tp_Package Package;
{
   tps_Str DGFileName;
   tp_Nod Root;
   tp_Nod EntryNod;
   tp_FilDsc FilDsc;
   int LineNum;

   (void)sprintf(DGFileName, "%s/%s/%s.dg", ToolDirName, Package, Package);
   FilDsc = FileName_RFilDsc(DGFileName, FALSE);
   if (FilDsc == NIL) {
      SystemError("Derivation graph <%s> not found.\n", DGFileName);
      return; }/*if*/;

   ParseFN = DGFileName; ParseFD = FilDsc; ParseLNPtr = &LineNum;
   LineNum = 1;
   Root = YY_Parse();
   for (EntryNod = Nod_Son(1, Root);
	EntryNod != NIL;
	EntryNod = Nod_Brother(EntryNod)) {
      switch (Nod_NodTyp(EntryNod)) {
	 case NOD_Banner: {
	    if (Banner == NIL) {
	       Banner = Sym_Str(Nod_Sym(Nod_Son(1, EntryNod))); }/*if*/;
	    break; }/*case*/;
	 case NOD_SrcDcl: {
	    Declare_SrcTyp(EntryNod);
	    break; }/*case*/;
	 case NOD_ObjDcl: {
	    Declare_ObjTyp(EntryNod);
	    break; }/*case*/;
	 case NOD_PrmDcl: {
	    Declare_PrmTyp(EntryNod);
	    break; }/*case*/;
	 case NOD_VarDcl: {
	    Declare_EnvVar(EntryNod);
	    break; }/*case*/;
	 case NOD_ToolDcl: {
	    Declare_Tool(Package, EntryNod);
	    break; }/*case*/;
	 default: {
	    FATALERROR("bad entry node type"); };}/*switch*/; }/*for*/;
   Ret_Nod(Root);
   Close(ParseFD);
   }/*Build_DerivationGraph*/


void
Write_DerivationGraph()
{
   FILE *DRVGRF_FILE, *DG_C_FILE;

   if (Banner == NIL) Banner = "";
   DRVGRF_FILE = fopen("DG", "w");
   FORBIDDEN(DRVGRF_FILE == NIL);
   DG_C_FILE = fopen("DG.c", "w");
   FORBIDDEN(DG_C_FILE == NIL);
   (void)fprintf(DRVGRF_FILE, "%s\n", DG_VERSION_STR);
   (void)fprintf(DG_C_FILE, "char *DG_Version = \"%s\";\n", DG_VERSION_STR);
   (void)fprintf(DRVGRF_FILE, ".%s\1\n", Banner);
   (void)fprintf(DG_C_FILE, "char *Banner = \"%s\";\n", Banner);
   (void)fprintf(DG_C_FILE, "#include \"inc/GMC.h\"\n");
   DG_HEAD(SrcTyp);
   DG_HEAD(FilTyp);
   DG_HEAD(PrmTyp);
   DG_HEAD(EnvVar);
   DG_HEAD(EnvVarLst);
   DG_HEAD(Tool);
   DG_HEAD(InpEdg);
   DG_HEAD(MemEdg);
   DG_HEAD(EqvEdg);
   DG_HEAD(CastEdg);
   DG_HEAD(DrvEdg);
   DG_HEAD(PrmTypLst);
   DG_HEAD(InpSpc);
   (void)fprintf(DRVGRF_FILE, "\n");
   Write_FilTyps(DRVGRF_FILE, DG_C_FILE);
   Write_PrmTyps(DRVGRF_FILE, DG_C_FILE);
   Write_EnvVars(DRVGRF_FILE, DG_C_FILE);
   Write_Tools(DRVGRF_FILE, DG_C_FILE);
   Write_Edgs(DRVGRF_FILE, DG_C_FILE);
   Write_InpSpcs(DRVGRF_FILE, DG_C_FILE);
   (void)fclose(DRVGRF_FILE);
   (void)fclose(DG_C_FILE);
   }/*Write_DerivationGraph*/

