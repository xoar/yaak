/*
Copyright (C) 1991 Geoffrey M. Clemm

This file is part of the Odin system.

The Odin system is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 1,
or (at your option) any later version (see the file COPYING).

The Odin system is distributed WITHOUT ANY WARRANTY, without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

geoff@boulder.colorado.edu
*/

#include "inc/GMC.h"

#include "inc/CastEdg.h"
#include "inc/DrvEdg.h"
#include "inc/EqvEdg.h"
#include "inc/EnvVar.h"
#include "inc/FKind_.h"
#include "inc/FilTyp.h"
#include "inc/FTClass_.h"
#include "inc/InpEdg.h"
#include "inc/InpSpc.h"
#include "inc/IOTyp.h"
#include "inc/MemEdg.h"
#include "inc/PrmTyp.h"
#include "inc/PrmTypLst.h"
#include "inc/SrcTyp.h"
#include "inc/TClass_.h"
#include "inc/Tool.h"

#ifdef __STDC__

#define VALIDATE(x) \
 { extern tp_##x x##S; \
   tp_##x x; \
   for(x = x##S; x != NIL; x=x->Link) { \
      Validate_##x(x); };}

#else

#define VALIDATE(x) \
 { extern tp_/**/x x/**/S; \
   tp_/**/x x; \
   for(x = x/**/S; x != NIL; x=x->Link) { \
      Validate_/**/x(x); };}

#endif

static void
Verify_Atmc_FilTyp(FilTyp)
   tp_FilTyp FilTyp;
{
   if (IsAtmc_FilTyp(FilTyp)) {
      return; }/*if*/;
   SystemError("Type must be atomic : %s.\n", FilTyp_FTName(FilTyp));
   }/*Verify_Atmc_FilTyp*/


static void
Verify_NonAtmc_FilTyp(FilTyp)
   tp_FilTyp FilTyp;
{
   if (IsAtmc_FilTyp(FilTyp)) {
      SystemError("Type cannot be atomic : %s.\n", FilTyp_FTName(FilTyp));
      }/*if*/;
   }/*Verify_NonAtmc_FilTyp*/


static void
Verify_List_FilTyp(FilTyp)
   tp_FilTyp FilTyp;
{
   if (IsList_FilTyp(FilTyp)) {
      return; }/*if*/;
   SystemError("Type must be a list : %s.\n", FilTyp->FTName);
   }/*Verify_List_FilTyp*/


static void
Verify_DrvDir_FilTyp(FilTyp)
   tp_FilTyp FilTyp;
{
   if (IsDrvDir_FilTyp(FilTyp)) {
      return; }/*if*/;
   SystemError("Type must be a directory : %s.\n", FilTyp->FTName);
   }/*Verify_DrvDir_FilTyp*/


static void
Verify_List_or_Struct_FilTyp(FilTyp)
   tp_FilTyp FilTyp;
{
   if (IsList_FilTyp(FilTyp) || IsStruct_FilTyp(FilTyp)) {
      return; }/*if*/;
   SystemError("Type must be a list or composite: %s.\n", FilTyp->FTName);
   }/*Verify_List_or_Struct_FilTyp*/


static void
Verify_Struct_FilTyp(FilTyp)
   tp_FilTyp FilTyp;
{
   if (IsStruct_FilTyp(FilTyp)) {
      return; }/*if*/;
   SystemError("Type must be composite: %s.\n", FilTyp->FTName);
   }/*Verify_Struct_FilTyp*/


static void
Verify_Pntr_FilTyp(FilTyp)
   tp_FilTyp FilTyp;
{
   if (IsPntr_FilTyp(FilTyp)) {
      return; }/*if*/;
   SystemError("Type must be a pointer: %s.\n", FilTyp->FTName);
   }/*Verify_Pntr_FilTyp*/


static int
Tool_NumInps(Tool)
   tp_Tool Tool;
{
   int Num;
   tp_InpEdg InpEdg;

   Num = 0;
   for (InpEdg = Tool->InpEdg; InpEdg != NIL; InpEdg = InpEdg->Next) {
      Num += 1; }/*for*/;
   return Num;
   }/*Tool_NumInps*/


static int
Tool_NumOuts(Tool)
   tp_Tool Tool;
{
   int Num;
   tp_MemEdg MemEdg;

   Num = 0;
   for (MemEdg = Tool->FilTyp->MemEdg; MemEdg != NIL; MemEdg = MemEdg->Next) {
      Num += 1; }/*for*/;
   return Num;
   }/*Tool_NumOuts*/


static void
Validate_ToolIO(Tool)
   tp_Tool Tool;
{
   if (Tool_NumInps(Tool) >= MAX_Inputs) {
      SystemError("Tool cannot have more than %d inputs: %s.\n",
		  MAX_Inputs, Tool->FilTyp->FTName); }/*if*/;
   if (Tool_NumOuts(Tool) >= MAX_Outputs) {
      SystemError("Tool cannot have more than %d outputs: %s.\n",
		  MAX_Outputs, Tool->FilTyp->FTName); }/*if*/;
   }/*Validate_ToolIO*/


static void
Validate_SrcTyp(SrcTyp)
   tp_SrcTyp SrcTyp;
{
   tp_FilTyp FilTyp;

   FilTyp = SrcTyp_FilTyp(SrcTyp);
   if (!IsAtmc_FilTyp(FilTyp)) {
      SystemError("Error for %s: source types must be a FILE.\n",
		  FilTyp_FTName(FilTyp)); }/*if*/;
   }/*Validate_SrcTyp*/


static void
Validate_FilTyp(FilTyp)
   tp_FilTyp FilTyp;
{
   if (FilTyp->Desc == NIL) {
      SystemError("Undeclared file type: \"%s\".\n", FilTyp->FTName);
      return; }/*if*/;
   if (FilTyp->FTClass == NIL) {
      SystemError("Not a subtype of OBJECT: \"%s\".\n", FilTyp->FTName);
      return; }/*if*/;
   if (IsRecurse_FilTyp(FilTyp) && !IsList_FilTyp(FilTyp->ArgFilTyp)) {
      SystemError("Argument type :%s of :%s=:%s must be a list.\n",
		  FilTyp->ArgFilTyp->FTName, FilTyp->FTName,
		  FilTyp->ArgFilTyp->FTName); }/*if*/;
   }/*Validate_FilTyp*/


static void
Validate_PrmTyp(PrmTyp)
   tp_PrmTyp PrmTyp;
{
   tp_DrvPth DrvPth;
   boolean IsGeneric;

   if (PrmTyp->Desc == NIL) {
      SystemError("Undeclared parameter type : \"%s\".\n", PrmTyp->PTName);
      return; }/*if*/;
   if (ListFilTyp != PrmTyp->FilTyp) {
      Do_Search(&DrvPth, &IsGeneric, FK_User, ListFilTyp, PrmTyp->FilTyp);
      if (DrvPth == NIL || IsGeneric) {
	 SystemError("Parameter value type (:%s) for +%s must be derivable from :LIST.\n",
		     FilTyp_FTName(PrmTyp->FilTyp), PrmTyp_PTName(PrmTyp));
	 return; }/*if*/;
      Ret_DrvPth(DrvPth); }/*if*/;
   }/*Validate_PrmTyp*/


static void
Validate_EnvVar(EnvVar)
   tp_EnvVar EnvVar;
{
   if (EnvVar->Default == NIL) {
      SystemError("Undeclared environment variable: \"%s\".\n", EnvVar->Name);
      }/*if*/;
   }/*Validate_EnvVar*/


static void
Verify_PrmTypLst_Count(Tool, Count)
   tp_Tool Tool;
   int Count;
{
   tp_PrmTypLst PrmTypLst;
   int num;

   num = 0;
   for (PrmTypLst = Tool->BasePrmTypLst;
	PrmTypLst != DfltPrmTypLst;
	PrmTypLst = PrmTypLst_Next(PrmTypLst)) {
      num += 1; }/*for*/;
   if (num != Count) {
      SystemError("Tool <%s> must have %d parameter(s).\n",
		  Tool_Name(Tool), Count); }/*if*/;
   }/*Verify_DfltPrmTypLst*/


static void
Verify_Input_Count(Tool, Count)
   tp_Tool Tool;
   int Count;
{
   if (Tool_NumInps(Tool) != Count) {
      SystemError("Tool must have %d input(s) : %s.\n", Count, Tool_Name(Tool));
      }/*if*/;
   }/*Verify_Input_Count*/


static void
Verify_Structure(FilTyp, Test1, Test2)
   tp_FilTyp FilTyp;
#ifdef __STDC__
   void (*Test1)(tp_FilTyp), (*Test2)(tp_FilTyp);
#else
   void (*Test1)(), (*Test2)();
#endif
{
   tp_MemEdg MemEdg;

   if (!IsStruct_FilTyp(FilTyp)) {
      SystemError("Type must be a list : %s.\n", FilTyp->FTName);
      return; }/*if*/;
   MemEdg = FilTyp->MemEdg;
   if (MemEdg == NIL) {
      SystemError("Type must have two members : %s.\n", FilTyp->FTName);
      return; }/*if*/;
   Test1(MemEdg->FilTyp);
   MemEdg = MemEdg->Next;
   if (MemEdg == NIL) {
      SystemError("Type must have two members : %s.\n", FilTyp->FTName);
      return; }/*if*/;
   Test2(MemEdg->FilTyp);
   }/*Verify_Structure*/


static void
Verify_Outputs(Tool, Test)
   tp_Tool Tool;
#ifdef __STDC__
   void (*Test)(tp_FilTyp);
#else
   void (*Test)();
#endif
{
   tp_FilTyp FilTyp;
   tp_MemEdg MemEdg;

   FilTyp = Tool->FilTyp;
   if (!IsStruct_FilTyp(FilTyp)) {
      Test(FilTyp);
      return; }/*if*/;
   for (MemEdg = FilTyp->MemEdg; MemEdg != NIL; MemEdg = MemEdg->Next) {
      Test(MemEdg->FilTyp); }/*for*/;
   }/*Verify_Outputs*/


static void
Validate_Tool(Tool)
   tp_Tool Tool;
{
   tp_FilTyp FilTyp;

   FilTyp = Tool->FilTyp;
   switch (Tool->TClass) {
      case TC_Source: case TC_Str: case TC_DrvDirElm: case TC_VirDirElm:
      case TC_PntrHo: case TC_PntrElm: case TC_InternalPntr: case TC_TextDef: {
	 break; }/*case*/;

      case TC_External: {
	 Validate_ToolIO(Tool);
	 Verify_Outputs(Tool, Verify_Atmc_FilTyp);
	 break; }/*case*/;
      case TC_StructMem: {
	 Validate_ToolIO(Tool);
	 break; }/*case*/;

      case TC_PrmValues: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_First: {
	 Validate_ToolIO(Tool);
	 Verify_Pntr_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Apply: {
	 Validate_ToolIO(Tool);
	 Verify_Pntr_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 2);
	 Verify_PrmTypLst_Count(Tool, 1);
	 break; }/*case*/;
      case TC_DerefPrmVal: {
	 Validate_ToolIO(Tool);
	 Verify_Pntr_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Map: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Recurse: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Extract: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Delete: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;

      case TC_Error: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Warning: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Name: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Names: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_FileName: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_FileNames: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Cat: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Union: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Label: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Labels: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Id: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Collect: {
	 Validate_ToolIO(Tool);
	 Verify_NonAtmc_FilTyp(FilTyp);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_ReadList: {
	 Validate_ToolIO(Tool);
	 Verify_NonAtmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_SrcNames: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_OpNames: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_ViewSpec: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_CmptView: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Directory: {
	 Validate_ToolIO(Tool);
	 Verify_Pntr_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Depend: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_TargetsPtr: {
	 Validate_ToolIO(Tool);
	 Verify_Pntr_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_TargetsInc: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_Targets: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 2);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_ActTargets: case TC_VirTargets: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_VirDir: {
	 Validate_ToolIO(Tool);
	 Verify_DrvDir_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_CopyCmd: {
	 Validate_ToolIO(Tool);
	 Verify_List_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 2);
	 Verify_PrmTypLst_Count(Tool, 1);
	 break; }/*case*/;
      case TC_ExpandHooks: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 2);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_NestedHooks: {
	 Validate_ToolIO(Tool);
	 Verify_Structure(FilTyp, Verify_List_FilTyp, Verify_Atmc_FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_PrefixHelp: case TC_SuffixHelp: case TC_DrvHelp: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 1);
	 Verify_PrmTypLst_Count(Tool, 0);
	 break; }/*case*/;
      case TC_PrmHelp: {
	 Validate_ToolIO(Tool);
	 Verify_Atmc_FilTyp(FilTyp);
	 Verify_Input_Count(Tool, 2);
	 Verify_PrmTypLst_Count(Tool, 1);
	 break; }/*case*/;
      default: {
	 FATALERROR("Illegal ToolClass.\n"); };}/*switch*/;
   }/*Validate_Tool*/


void
Validate_DerivationGraph()
{
   VALIDATE(SrcTyp);
   VALIDATE(FilTyp);
   VALIDATE(PrmTyp);
   VALIDATE(EnvVar);
   VALIDATE(Tool);
   }/*Validate_DerivationGraph*/

