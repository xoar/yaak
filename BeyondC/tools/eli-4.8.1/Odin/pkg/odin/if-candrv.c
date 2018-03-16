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

#include "inc/GMC.h"
#include "inc/FileName.h"
#include "inc/DPType_.h"
#include "inc/FKind_.h"
#include "inc/Flag_.h"
#include "inc/InpKind_.h"
#include "inc/LogLevel_.h"
#include "inc/NodTyp_.h"
#include "inc/Str.h"
#include "inc/Status_.h"


tp_DrvPth
Get_DrvPth(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilTyp, ToFilTyp)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilTyp, ToFilTyp)
{
   tp_DrvPth DrvPth, GenericDrvPth;
   boolean IsGeneric;
   tp_FilHdr GenericFilHdr, TmpGenericFilHdr;

   if (FilHdr == ERROR || ToFilTyp == ERROR) return ERROR;

   Do_Search(&DrvPth, &IsGeneric,
	     FilHdr_FKind(FilHdr), FilHdr_FilTyp(FilHdr), ToFilTyp);

   if (IsGeneric) {
      GenericFilHdr = Copy_FilHdr(FilHdr);
      GenericDrvPth = DrvPth;
      while (IsGeneric) {
	 TmpGenericFilHdr = GenericFilHdr;
	 GenericFilHdr = Do_DrvPth(GenericFilHdr, RootFilPrm, RootFilPrm, GenericDrvPth);
	 IsGeneric = FALSE;
	 /*select*/{
	    if (GenericFilHdr == TmpGenericFilHdr) {
	       GenericDrvPth = NIL;
	    }else if (FilHdr_FilTyp(GenericFilHdr) != ToFilTyp) {
	       Do_Search(&GenericDrvPth, &IsGeneric,
			 FilHdr_FKind(GenericFilHdr),
			 FilHdr_FilTyp(GenericFilHdr), ToFilTyp);
	       AppendDrvPth(&DrvPth, GenericDrvPth); };}/*select*/; }/*while*/;
      Ret_FilHdr(GenericFilHdr);
      if (GenericDrvPth == NIL) {
	 Ret_DrvPth(DrvPth);
	 DrvPth = NIL; }/*if*/; }/*if*/;
   return DrvPth;
   }/*Get_DrvPth*/


tp_PrmTypLst
DrvPth_PrmTypLst(
   GMC_ARG(tp_DrvPth, DrvPth)
   )
   GMC_DCL(tp_DrvPth, DrvPth)
{
   tp_DrvEdg DrvEdg;

   DrvEdg = DrvPth_DrvEdg(DrvPth);
   if (DrvEdg != NIL) {
      return DrvEdg_PrmTypLst(DrvEdg); }/*if*/;
   if (DrvPth_FKind(DrvPth) == FK_PntrHo) {
      return FilTyp_MapPrmTypLst(DrvPth_FilTyp(DrvPth)); }/*if*/;
   return (tp_PrmTypLst)NIL;
   }/*DrvPth_PrmTypLst*/


tp_DrvPth
Find_GroupingDrvPthElm(
   GMC_ARG(tp_DrvPth, DrvPth)
   )
   GMC_DCL(tp_DrvPth, DrvPth)
{
   tp_DrvPth DrvPthElm, GroupingDrvPthElm;

   GroupingDrvPthElm = NIL;
   for (DrvPthElm = DrvPth;
	DrvPthElm != NIL;
	DrvPthElm = DrvPth_Next(DrvPthElm)) {
      if (DrvPth_DPType(DrvPthElm) == DPT_Drv) {
	 GroupingDrvPthElm = DrvPthElm;
	 if (!IsGrouping_FilTyp(DrvPth_FilTyp(DrvPthElm))) {
	    GroupingDrvPthElm = NIL; }/*if*/; }/*if*/; }/*for*/;
   return GroupingDrvPthElm;
   }/*Find_GroupingDrvPthElm*/


tp_FilHdr
Do_DrvPth(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilPrm, InhFilPrm),
   GMC_ARG(tp_FilPrm, PrecFilPrm),
   GMC_ARG(tp_DrvPth, DrvPth)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilPrm, InhFilPrm)
   GMC_DCL(tp_FilPrm, PrecFilPrm)
   GMC_DCL(tp_DrvPth, DrvPth)
{
   tp_DrvPth DrvPthElm, GroupingDrvPthElm;
   tp_FilTyp FilTyp;
   tp_FKind FKind;
   tp_FilPrm FilPrm, DrvFilPrm;
   tp_PrmTypLst PrmTypLst;
   tps_FileName PkgDirName;
   boolean NoInput_Flag=FALSE;

   FORBIDDEN(DrvPth == ERROR);
   if (FilHdr == ERROR || InhFilPrm == ERROR || PrecFilPrm == ERROR) {
      Ret_FilHdr(FilHdr);
      return ERROR; }/*if*/;

   FilPrm = Append_FilPrm(PrecFilPrm, InhFilPrm);
   GroupingDrvPthElm = (PrecFilPrm == RootFilPrm ? NIL
			: Find_GroupingDrvPthElm(DrvPth));
   for (DrvPthElm = DrvPth;
	DrvPthElm != NIL;
	DrvPthElm = DrvPth_Next(DrvPthElm)) {
      switch (DrvPth_DPType(DrvPthElm)) {
	 case DPT_Drv: {
	    FilTyp = DrvPth_FilTyp(DrvPthElm);
	    FKind = DrvPth_FKind(DrvPthElm);
	    PrmTypLst = DrvPth_PrmTypLst(DrvPthElm);
	    /*select*/{
	       if (IsGroupingInput_FilTyp(FilTyp)) {
		  DrvFilPrm = FilPrm;
	       }else if (DrvPthElm == GroupingDrvPthElm) {
		  DrvFilPrm = Strip_FilPrm(InhFilPrm, PrmTypLst);
		  DrvFilPrm = Append_FilPrm(PrecFilPrm, DrvFilPrm);
	       }else{
		  DrvFilPrm = Strip_FilPrm(FilPrm, PrmTypLst); };}/*select*/;
	    if (NoInput_Flag) {
	       FORBIDDEN(FilHdr != ERROR);
	       Get_PkgDirName(PkgDirName,
			      Tool_Package(FilTyp_Tool(FilTyp)));
	       FilHdr = HostFN_FilHdr(PkgDirName);
	       NoInput_Flag = FALSE; }/*if*/;
	    FilHdr = Get_Drv(FilHdr, FKind, FilTyp, DrvFilPrm, DfltIdent);
	    break;}/*case*/;
	 case DPT_Eqv: {
	    if (DrvPth_FilTyp(DrvPthElm) == NoInputFilTyp) {
	       Ret_FilHdr(FilHdr);
	       FilHdr = ERROR;
	       NoInput_Flag = TRUE; }/*if*/; break;}/*case*/;
	 }/*switch*/; }/*for*/;
   return FilHdr;
   }/*Do_DrvPth*/


tp_FilHdr
Do_Deriv(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilPrm, InhFilPrm),
   GMC_ARG(tp_FilPrm, PrecFilPrm),
   GMC_ARG(tp_FilTyp, ToFilTyp)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilPrm, InhFilPrm)
   GMC_DCL(tp_FilPrm, PrecFilPrm)
   GMC_DCL(tp_FilTyp, ToFilTyp)
{
   tp_DrvPth DrvPth;

   if (FilHdr == ERROR || InhFilPrm == ERROR || ToFilTyp == ERROR) {
      Ret_FilHdr(FilHdr);
      return ERROR; }/*if*/;

   if (FilHdr_FilTyp(FilHdr) == ToFilTyp) {
      if (PrecFilPrm != RootFilPrm) {
	 Do_Log("Ignoring parameters of", FilHdr, LOGLEVEL_IgnorePrm); }/*if*/;
      return FilHdr; }/*if*/;

   DrvPth = Get_DrvPth(FilHdr, ToFilTyp);
   if (DrvPth == ERROR) {
      SystemError("Cannot derive to <%s> from <%s>\n",
		  FilTyp_FTName(ToFilTyp),
		  FilTyp_FTName(FilHdr_FilTyp(FilHdr)));
      Ret_FilHdr(FilHdr);
      return ERROR; }/*if*/;
   FilHdr = Do_DrvPth(FilHdr, InhFilPrm, PrecFilPrm, DrvPth);
   Ret_DrvPth(DrvPth);

   return FilHdr;
   }/*Do_Deriv*/


tp_FilHdr
Do_Key(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_Key, Key)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_Key, Key)
{
   tp_FilHdr DirFilHdr, DirSymFilHdr, SymDirFilHdr;
   tp_FilTyp FilTyp;
   tp_FKind FKind;

   if (FilHdr == ERROR || Key == ERROR) {
      Ret_FilHdr(FilHdr);
      return ERROR; }/*if*/;

   if (strcmp(Key, ".") == 0) {
      return FilHdr; }/*if*/;

   if (strcmp(Key, "") == 0
       && !(FilHdr == RootFilHdr || FilHdr == NetRootFilHdr)) {
      return FilHdr; }/*if*/;

   if (IsSource(FilHdr)) {
      if (strcmp(Key, "..") == 0) {
	 if (FilHdr == RootFilHdr) {
	    return FilHdr; }/*if*/;
	 DirFilHdr = FilHdr_Father(Copy_FilHdr(FilHdr));
	 if (DirFilHdr == NetRootFilHdr) {
	    Ret_FilHdr(DirFilHdr);
	    return FilHdr; }/*if*/;
	 DirSymFilHdr = FilHdr_Father(Deref_SymLink(Copy_FilHdr(FilHdr)));
	 SymDirFilHdr = Deref_SymLink(Copy_FilHdr(DirFilHdr));
	 Ret_FilHdr(FilHdr);
	 if (DirSymFilHdr == SymDirFilHdr) {
	    Ret_FilHdr(DirSymFilHdr); Ret_FilHdr(SymDirFilHdr);
	    return DirFilHdr; }/*if*/;
	 Ret_FilHdr(DirFilHdr); Ret_FilHdr(SymDirFilHdr);
	 return FilHdr_AliasFilHdr(DirSymFilHdr); }/*if*/;

      if (FilHdr == CacheDirFilHdr) {
	 if (strlen(Key) == 1) {
	    return FilHdr; }/*if*/;
	 Ret_FilHdr(FilHdr);
	 return CacheFileName_FilHdr(Key); }/*if*/;

      return Get_KeyDrv(FilHdr, FK_SrcReg, Key); }/*if*/;

   if (IsVirDir(FilHdr)) {
      return Get_KeyDrv(FilHdr, FK_VirDirElm, Key); }/*if*/;

   if (IsTargets(FilHdr)) {
      return Get_KeyDrv(FilHdr, FK_ActTgtText, Key); }/*if*/;

   if (IsPntr(FilHdr)) {
      return Get_Drv(FilHdr, FK_PntrElm, Key_FilTyp(Key), RootFilPrm, Key);
      }/*if*/;

   if (IsDrvDirElm(FilHdr)) {
      return Get_KeyDrv(FilHdr, FK_DrvDirElm, Key); }/*if*/;

   if (!IsKeyList(FilHdr)) {
      FilHdr_Error("Cannot select from <%s>.\n", FilHdr);
      Ret_FilHdr(FilHdr);
      return ERROR; }/*if*/;

   FilTyp = FilHdr_FilTyp(FilHdr);
   /*select*/{
      if (FilTyp == ActTargetsFilTyp) {
	 FKind = FK_ActTgt;
      }else if (FilTyp == VirTargetsFilTyp) {
	 FKind = FK_VirTgt;
      }else{
         FKind = FK_DrvDirElm; };}/*select*/;
   return Get_KeyDrv(FilHdr, FKind, Key);
   }/*Do_Key*/


tp_FilHdr
Str_FilHdr(
   GMC_ARG(tp_Str, Str),
   GMC_ARG(tp_PrmTyp, PrmTyp)
   )
   GMC_DCL(tp_Str, Str)
   GMC_DCL(tp_PrmTyp, PrmTyp)
{
   if (strcmp(Str, "") == 0) {
      return Copy_FilHdr(NilStrFilHdr); }/*if*/;
   return Extend_FilHdr(PrmTyp_StrDirFilHdr(PrmTyp), FK_Str,
			ObjectFilTyp, RootFilPrm, Str);
   }/*Str_FilHdr*/


tp_FilHdr
Do_VTgt(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_Key, Key)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_Key, Key)
{
   if (FilHdr_FilTyp(FilHdr) == TargetsFilTyp) {
      return Get_KeyDrv(FilHdr, FK_VirTgtText, Key); }/*if*/;
   FilHdr = Do_Deriv(FilHdr, RootFilPrm, RootFilPrm, VirTargetsFilTyp);
   if (strcmp(Key, ".") == 0) {
      return Do_Deriv(FilHdr, RootFilPrm, RootFilPrm, VirDirFilTyp);
      }/*if*/;
   return Get_KeyDrv(FilHdr, FK_VirTgt, Key);
   }/*Do_VTgt*/


void
WriteDrvHelp(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_FilHdr, FilHdr)
{
   Writeln(FilDsc, "*?* Possible Derivations:");
   Clr_FilTypMarks();
   SetFilHdr_DrvMarks(FilHdr);
   WriteMarkedFilTyps(FilDsc);
   }/*WriteDrvHelp*/


void
WritePrmHelp(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilPrm, FilPrm)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilPrm, FilPrm)
{
   tp_FilHdr ValFilHdr;
   tp_FilTyp FilTyp;
   tp_DrvPth DrvPth, DrvPthElm;
   tp_PrmTypLst PrmTypLst;

   Writeln(FilDsc, "*?* Possible Parameters :");
   Clr_PrmTypMarks();
   if (FilPrm == RootFilPrm) {
      SetFilHdr_PrmTypMarks(FilHdr);
      WriteMarkedPrmTyps(FilDsc);
      return; }/*if*/;

   ValFilHdr = LocHdr_FilHdr(FilPVal_LocHdr(FilPrm_FilPVal(FilPrm)));
   FilTyp = FTName_FilTyp(FilHdr_Ident(ValFilHdr));
   Ret_FilHdr(ValFilHdr);
   if (FilTyp == ERROR) {
      return; }/*if*/;
   if (FilHdr_FilTyp(FilHdr) != FilTyp) {
      DrvPth = Get_DrvPth(FilHdr, FilTyp);
      if (DrvPth == ERROR) {
	 SystemError("Cannot derive to <%s>\n", FilTyp_FTName(FilTyp));
	 return; }/*if*/;
      for (DrvPthElm = DrvPth;
	   DrvPthElm != NIL;
	   DrvPthElm = DrvPth_Next(DrvPthElm)) {
	 if (DrvPth_DPType(DrvPthElm) == DPT_Drv) {
	    PrmTypLst = DrvPth_PrmTypLst(DrvPthElm);
	    SetPrmTypLst_Marks(PrmTypLst); }/*if*/; }/*for*/;
      Ret_DrvPth(DrvPth); }/*if*/;
   WriteMarkedPrmTyps(FilDsc);
   }/*WritePrmHelp*/


void
WriteNameDesc(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_Str, Name),
   GMC_ARG(tp_Desc, Desc)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_Str, Name)
   GMC_DCL(tp_Desc, Desc)
{
   tps_Str Msg;

   (void)strcpy(Msg, Name);
   (void)strcat(Msg, " ...............");
   (void)strcpy(&Msg[15], " ");
   (void)strcat(Msg, Desc);
   Writeln(FilDsc, Msg);
   }/*WriteNameDesc*/


tp_FilHdr
Get_BaseVTgtFilHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(IsTargetsPtr(FilHdr));
   while (!IsSource(FilHdr)) {
      if (IsVTgtText(FilHdr) || FilHdr_FilTyp(FilHdr) == VirTargetsFilTyp) {
	 return FilHdr_Father(FilHdr_Father(FilHdr)); }/*if*/;
      if (IsVTgt(FilHdr)) {
	 return FilHdr_Father(FilHdr_Father(FilHdr_Father(FilHdr))); }/*if*/;
      FilHdr = FilHdr_Father(FilHdr); }/*while*/;
   return FilHdr;
   }/*Get_BaseVTgtFilHdr*/


static tp_LocHdr
PrmValNod_LocHdr(
   GMC_ARG(tp_Nod, Nod),
   GMC_ARG(tp_PrmTyp, PrmTyp)
   )
   GMC_DCL(tp_Nod, Nod)
   GMC_DCL(tp_PrmTyp, PrmTyp)
{
   tp_PrmFHdr PrmFHdr;
   tp_FilHdr FilHdr;
   tp_FilPrm FilPrm;
   tp_LocHdr LocHdr;

   if (Nod == ERROR || PrmTyp == ERROR) {
      return ERROR; }/*if*/;

   switch (Nod_NodTyp(Nod)) {
      case DRVFIL: {
	 PrmFHdr = Nod_PrmFHdr(Nod);
	 Use_PrmFHdr(&FilHdr, &FilPrm, PrmFHdr);
	 break;}/*case*/;
      case WORD: {
	 FilHdr = Str_FilHdr(Sym_Str(Nod_Sym(Nod)), PrmTyp);
	 break;}/*case*/;
      default: {
	 FATALERROR("illegal parameter value node"); };}/*select*/;
   if (FilHdr == ERROR) {
      return ERROR; }/*if*/;
   LocHdr = FilHdr_LocHdr(FilHdr);
   Ret_FilHdr(FilHdr);
   return LocHdr;
   }/*PrmValNod_LocHdr*/


static tp_FilPrm
Append_PrmNod(
   GMC_ARG(tp_FilPrm, FilPrm),
   GMC_ARG(tp_Nod, PrmNod)
   )
   GMC_DCL(tp_FilPrm, FilPrm)
   GMC_DCL(tp_Nod, PrmNod)
{
   tp_PrmTyp PrmTyp;
   tp_Nod PrmValsNod, PrmValNod;
   tp_LocHdr LocHdr;
   tp_LocPVal LocPVal;
   tp_FilPVal FilPVal;

   if (FilPrm == ERROR || PrmNod == ERROR) {
      return ERROR; }/*if*/;

   PrmTyp = Nod_PrmTyp(Nod_Son(1, PrmNod));
   if (PrmTyp == ERROR) {
      return ERROR; }/*if*/;

   if (PrmTyp == NullPrmTyp) {
      return FilPrm; }/*if*/;

   LocHdr = NIL; LocPVal = NIL;

   if (Nod_NumSons(PrmNod) == 1) {
      LocPVal = FilPVal_LocPVal(PrmTyp_RootFilPVal(PrmTyp));
      goto done; }/*if*/;

   PrmValsNod = Nod_Son(2, PrmNod);
   if (Nod_NumSons(PrmValsNod) == 1) {
      LocHdr = PrmValNod_LocHdr(Nod_Son(1, PrmValsNod), PrmTyp);
      if (LocHdr == NIL) {
	 return ERROR; }/*if*/;
      goto done; }/*if*/;

   FilPVal = PrmTyp_RootFilPVal(PrmTyp);
   for (PrmValNod = Nod_Son(1, PrmValsNod);
	PrmValNod != NIL;
	PrmValNod = Nod_Brother(PrmValNod)) {
      LocHdr = PrmValNod_LocHdr(PrmValNod, PrmTyp);
      if (LocHdr == NIL) {
	 return ERROR; }/*if*/;
      FilPVal = Add_PValInf(FilPVal, LocHdr, (tp_LocPVal)NIL); }/*for*/;
   LocHdr = NIL;
   LocPVal = FilPVal_LocPVal(FilPVal);

done:;
   return Append_PrmInf(FilPrm, PrmTyp, LocHdr, LocPVal);
   }/*Append_PrmNod*/


static tp_PrmFHdr
Apply_OprNods(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilPrm, FilPrm),
   GMC_ARG(tp_Nod, OprNod)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilPrm, FilPrm)
   GMC_DCL(tp_Nod, OprNod)
{
   tp_Nod ElmNod;
   tp_NodTyp NodTyp;
   tp_FilTyp FilTyp;
   tp_LocHdr LocHdr;
   tp_LocPVal LocPVal;

   if (FilHdr == ERROR || FilPrm == ERROR) return ERROR;

   while (OprNod != NIL) {
      NodTyp = Nod_NodTyp(OprNod);
      switch (NodTyp) {
	 case PRMOPR: {
	    FilPrm = Append_PrmNod(FilPrm, OprNod);
	    if (FilPrm == ERROR) {
	       Ret_FilHdr(FilHdr);
	       return ERROR; }/*if*/;
	    break;}/*case*/;
	 case APLOPR: {
	    LocHdr = PrmValNod_LocHdr(Nod_Son(1, OprNod), ApplyPrmTyp);
	    if (LocHdr == ERROR) {
	       Ret_FilHdr(FilHdr);
	       return ERROR; }/*if*/;
	    LocPVal = NIL;
	    FilPrm = Append_PrmInf(FilPrm, ApplyPrmTyp, LocHdr, LocPVal);
	    FilHdr = Extend_FilHdr(FilHdr, FK_User, ApplyFilTyp, FilPrm,
				   DfltIdent);
	    FilPrm = RootFilPrm;
	    if (FilHdr == ERROR) {
	       return ERROR; }/*if*/;
	    break;}/*case*/;
	 case DRVOPR: {
	    FilTyp = Nod_FilTyp(Nod_Son(1, OprNod));
	    /*select*/{
	       if (FilTyp == ObjectFilTyp) {
	       }else if (FilTyp == FatherFilTyp) {
		  if (!IsInstance(FilHdr)) {
		     FilHdr_Error("Input to :abstract must be an instance: %s\n", FilHdr);
		     Ret_FilHdr(FilHdr);
		     return ERROR; }/*if*/;
		  FilHdr = FilHdr_Father(FilHdr);
	       }else{
		  FilHdr = Do_Deriv(FilHdr, RootFilPrm, FilPrm, FilTyp);
		  FilPrm = RootFilPrm;
		  if (FilHdr == ERROR) {
		     return ERROR; }/*if*/; };}/*select*/;
	    break;}/*case*/;
	 case HODOPR: {
	    FilTyp = Nod_FilTyp(OprNod);
	    FilHdr = Do_Deriv(FilHdr, RootFilPrm, FilPrm, FilTyp);
	    if (FilHdr == ERROR) {
	       return ERROR; }/*if*/;
	    FilPrm = RootFilPrm;
	    break;}/*case*/;
	 case ELMOPR: {
	    ElmNod = Nod_Son(1, OprNod);
	    FilPrm = RootFilPrm;
	    FilHdr = Do_Key(FilHdr, "");
	    FilHdr = Do_Keys(FilHdr, Sym_Str(Nod_Sym(ElmNod)));
	    if (FilHdr == ERROR) {
	       return ERROR; }/*if*/;
	    break;}/*case*/;
	 case DIROPR: {
	    FilHdr = Do_Key(FilHdr, "");
	    break;}/*case*/;
	 case SEGOPR: {
	    FilHdr = Do_VTgt(FilHdr, Sym_Str(Nod_Sym(Nod_Son(1, OprNod))));
	    FilPrm = RootFilPrm;
	    break;}/*case*/;
	 default: {
	    FATALERROR("bad operator node type"); };}/*switch*/;
      OprNod = Nod_Brother(OprNod); }/*while*/;

   return New_PrmFHdr(FilHdr, FilPrm);
   }/*Apply_OprNods*/


tp_PrmFHdr
Nod_PrmFHdr(
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(tp_Nod, Nod)
{
   tp_FilHdr FilHdr;
   tp_Nod RootNod, OprNod;
   tp_Key Key;

   if (Nod == ERROR) return ERROR;

   switch (Nod_NodTyp(Nod)) {
      case NSTDEF: case FILDEF: case SEGDEF: {
	 SystemError("Syntax error: Unexpected target.\n");
	 return ERROR; }/*case*/;
      case WORD: {
	 FilHdr = Str_FilHdr(Sym_Str(Nod_Sym(Nod)), NullPrmTyp);
	 return New_PrmFHdr(FilHdr, RootFilPrm); }/*case*/;
      case DRVFIL: {
	 break; }/*case*/;
      default: {
	 FATALERROR("Unexpected node type.\n"); };}/*switch*/;

   RootNod = Nod_Son(1, Nod);
   OprNod = Nod_Brother(RootNod);
   switch (Nod_NodTyp(RootNod)) {
      case EMPFIL: {
	 FilHdr = Copy_FilHdr(EmptyFilHdr);
	 break; }/*case*/;
      case ARTFIL: {
	 FilHdr = Copy_FilHdr(RootFilHdr);
	 break; }/*case*/;
      case OBJTID: {
	 FilHdr = LocHdr_FilHdr
	  ((tp_LocHdr)Str_PosInt(Sym_Str(Nod_Sym(RootNod))));
	 break; }/*case*/;
      case WORD: {
	 FilHdr = HostFN_FilHdr(Sym_Str(Nod_Sym(RootNod)));
	 break; }/*case*/;
      case ABSFIL: {
	 Key = Sym_Str(Nod_Sym(Nod_Son(1, RootNod)));
	 FilHdr = Do_Keys(Copy_FilHdr(RootFilHdr), Key);
	 break; }/*case*/;
      case SEGOPR: {
	 FilHdr = Get_BaseVTgtFilHdr(Top_ContextFilHdr());
	 OprNod = RootNod;
	 break; }/*case*/;
      case DRVOPR: {
	 FilHdr = Top_ContextFilHdr();
	 OprNod = RootNod;
	 break; }/*case*/;
      case STRING: {
	 FilHdr = Str_FilHdr(Sym_Str(Nod_Sym(Nod_Son(1, RootNod))), NullPrmTyp);
	 break; }/*case*/;
      default: {
	 FATALERROR("Unexpected node type.\n"); };}/*switch*/;

   return Apply_OprNods(FilHdr, RootFilPrm, OprNod);
   }/*Nod_PrmFHdr*/


tp_LocElm
Make_ApplyLocElm(
   GMC_ARG(tp_FilHdr, InFilHdr),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FileName, OprFileName)
   )
   GMC_DCL(tp_FilHdr, InFilHdr)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FileName, OprFileName)
{
   tps_Str StrBuf, StrSegBuf;
   tp_Str Str;
   tp_FilDsc FilDsc;
   int StrLen, LineNum;
   tp_Nod Nod;
   tp_PrmFHdr PrmFHdr;
   tp_FilPrm FilPrm, ElmFilPrm;
   tp_FilHdr ElmFilHdr;
   tp_LocElm LocElm;

   LocElm = NIL;
   FilDsc = FileName_RFilDsc(OprFileName, FALSE);
   if (FilDsc == ERROR) {
      SystemError("Cannot read %s.\n", OprFileName);
      return LocElm; }/*if*/;
   (void)strcpy(StrBuf, ".");
   StrLen = strlen(StrBuf);
   for (Str = ReadLine(StrSegBuf, FilDsc);
	Str != NIL;
	Str = ReadLine(StrSegBuf, FilDsc)) {
      (void)strcat(Str, "\n");
      StrLen += strlen(Str);
      if (StrLen >= MAX_Str) {
	 SystemError("%s: parameter file too long.\n", OprFileName);
	 return LocElm; }/*if*/;
      (void)strcat(StrBuf, Str); }/*for*/;
   Close(FilDsc);
   LineNum = 0;
   Nod = YY_Parser(StrBuf, OprFileName, &LineNum);
   if (Nod == ERROR) {
      return LocElm; }/*if*/;
   FilPrm = StripExcept_FilPrm(FilHdr_FilPrm(FilHdr), ApplyPrmTyp);
   PrmFHdr = Apply_OprNods(Copy_FilHdr(InFilHdr), FilPrm,
			   Nod_Brother(Nod_Son(1, Nod)));
   Ret_Nod(Nod);
   Use_PrmFHdr(&ElmFilHdr, &ElmFilPrm, PrmFHdr);
   if (ElmFilHdr == NIL) {
      return LocElm; }/*if*/;
   LocElm = Make_LocElm(ElmFilHdr, ElmFilPrm, FilHdr);
   Ret_FilHdr(ElmFilHdr);
   return LocElm;
   }/*Make_ApplyLocElm*/


static void
Get_Map(
   GMC_ARG(tp_LocElm*, FirstLEPtr),
   GMC_ARG(tp_LocElm*, LastLEPtr),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilPrm, FilPrm),
   GMC_ARG(tp_FilTyp, FilTyp),
   GMC_ARG(tp_FilHdr, ListFilHdr)
   )
   GMC_DCL(tp_LocElm*, FirstLEPtr)
   GMC_DCL(tp_LocElm*, LastLEPtr)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilPrm, FilPrm)
   GMC_DCL(tp_FilTyp, FilTyp)
   GMC_DCL(tp_FilHdr, ListFilHdr)
{
   tp_FilHdr ElmFilHdr;
   tp_LocElm LocElm;
   tp_FilElm FilElm;

   if (IsViewSpec(FilHdr)) {
      FilHdr_Error("Illegal view specification argument: %s\n", FilHdr);
      return; }/*if*/;

   if (FilHdr_Flag(FilHdr, FLAG_Union)) {
      return; }/*if*/;
   Set_Flag(FilHdr, FLAG_Union);

   if (!IsRef(FilHdr)) {
      ElmFilHdr = Do_Deriv(Copy_FilHdr(FilHdr), RootFilPrm, FilPrm, FilTyp);
      /*select*/{
	 if (ElmFilHdr != ERROR) {
	    LocElm = Make_LocElm(ElmFilHdr, RootFilPrm, ListFilHdr);
	    Chain_LocElms(FirstLEPtr, LastLEPtr, LocElm);
	    Ret_FilHdr(ElmFilHdr);
	 }else{
	    FilHdr_Error(" from:\n   %s.\n", FilHdr); };}/*select*/;
      return; }/*if*/;

   for (FilElm = LocElm_FilElm(FilHdr_LocElm(FilHdr));
	FilElm != NIL;
	FilElm = FilElm_NextFilElm(FilElm)) {
      ElmFilHdr = FilElm_FilHdr(FilElm);
      Get_Map(FirstLEPtr, LastLEPtr, ElmFilHdr,
	      Append_FilPrm(FilElm_FilPrm(FilElm), FilPrm),
	      FilTyp, ListFilHdr);
      Ret_FilHdr(ElmFilHdr); }/*for*/;
   }/*Get_Map*/


tp_LocElm
Make_MapLocElm(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilHdr, ListFilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilHdr, ListFilHdr)
{
   tp_LocElm FirstLE, LastLE;

   if (!(IsList(FilHdr) || IsPntr(FilHdr))) {
      SystemError("Input to :map must be a list.\n");
      return ERROR; }/*if*/;

   FirstLE = NIL; LastLE = NIL;
   Get_Map(&FirstLE, &LastLE, FilHdr, FilHdr_FilPrm(ListFilHdr),
	   FilTyp_ArgFilTyp(FilHdr_FilTyp(ListFilHdr)), ListFilHdr);
   Clr_UnionFlags(FilHdr);
   return FirstLE;
   }/*Make_MapLocElm*/


void
Local_Get_OdinFile(
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(boolean, NeedsData)
   )
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(boolean, NeedsData)
{
   tp_Nod Root;
   tp_PrmFHdr PrmFHdr;
   tp_FilHdr FilHdr;
   tp_FilPrm FilPrm;
   boolean AllDone;

   Root = YY_Parser(OdinExpr, (tp_FileName)NIL, (int *)NIL);
   FORBIDDEN(Root == ERROR);
   PrmFHdr = Nod_PrmFHdr(Root);
   Ret_Nod(Root);
   Use_PrmFHdr(&FilHdr, &FilPrm, PrmFHdr);
   if (FilHdr == ERROR) {
      LocalEnd_Get_OdinFile("", STAT_Unknown, FALSE);
      return; }/*if*/;
   Set_Client_FilHdr(CurrentClient, FilHdr, NeedsData);
   Push_AllReqs(&AllDone);
   Ret_FilHdr(FilHdr);
   IsAny_ReadyServerAction = TRUE;
   }/*Local_Get_OdinFile*/


void
End_Get_OdinFile(GMC_ARG_VOID)
{
   tp_FilHdr FilHdr;
   tps_FileName FileName;
   tp_Status Status;
   boolean ExecFlag, NeedsData;

   FORBIDDEN(Client_ToDo(CurrentClient) != NIL);
   FORBIDDEN(Client_Job(CurrentClient) != NIL);
   FilHdr = Client_FilHdr(CurrentClient);
   FORBIDDEN(FilHdr == NIL);
   ExecFlag = IsAutoExec(FilHdr);
   NeedsData = ExecFlag || Client_NeedsData(CurrentClient);
   Set_Client_FilHdr(CurrentClient, (tp_FilHdr)NIL, FALSE);
   (void)strcpy(FileName, "");
   Status = STAT_Unknown;
   if (Client_Interrupted(CurrentClient)) {
      Set_Client_Interrupted(CurrentClient, FALSE);
      goto done; }/*if*/;
   FilHdr = Deref(FilHdr);
   if (FilHdr == ERROR) {
      goto done; }/*if*/;
   Status = FilHdr_MinStatus(FilHdr, IK_Trans);
   if (IsList(FilHdr)) {
      goto done; }/*if*/;
   if (NeedsData) {
      FilHdr_DataFileName(FileName, FilHdr); }/*if*/;

done:;
   LocalEnd_Get_OdinFile(FileName, Status, ExecFlag);
   Ret_FilHdr(FilHdr);
   }/*End_Get_OdinFile*/


