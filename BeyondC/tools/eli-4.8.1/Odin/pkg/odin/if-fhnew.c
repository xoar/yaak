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
#include "inc/FilHdr.h"
#include "inc/FilTyp.h"
#include "inc/FKind_.h"
#include "inc/LogLevel_.h"
#include "inc/Status_.h"
#include "inc/Str.h"


static int	InsertNesting = 0;
static int	Log_InsertNesting = 100;


void
Make_RootHdrInf(
   GMC_ARG(tp_HdrInf, HdrInf),
   GMC_ARG(tp_LocHdr, LocHdr)
   )
   GMC_DCL(tp_HdrInf, HdrInf)
   GMC_DCL(tp_LocHdr, LocHdr)
{
   HdrInf->LocHdr = LocHdr;
   HdrInf->FKind = FK_SrcDir;
   HdrInf->IFilTyp = ObjectFilTyp->IFilTyp;
   HdrInf->ModDate = 1;
   HdrInf->Status = STAT_OK;
   HdrInf->LocPrm = RootLocPrm;
   HdrInf->LocIdent = LocNilStr;
   }/*Make_RootHdrInf*/


tp_FilHdr
Insert_FilHdr(
   GMC_ARG(tp_FilHdr, BaseFilHdr),
   GMC_ARG(tp_FKind, FKind),
   GMC_ARG(tp_FilTyp, FilTyp),
   GMC_ARG(tp_FilPrm, FilPrm),
   GMC_ARG(tp_Ident, Ident)
   )
   GMC_DCL(tp_FilHdr, BaseFilHdr)
   GMC_DCL(tp_FKind, FKind)
   GMC_DCL(tp_FilTyp, FilTyp)
   GMC_DCL(tp_FilPrm, FilPrm)
   GMC_DCL(tp_Ident, Ident)
{
   tp_FilHdr FilHdr;
   tp_LocHdr LocHdr;

   FORBIDDEN(BaseFilHdr == ERROR || FilTyp == ERROR || FilPrm == ERROR);
   FilHdr = New_FilHdr();
   LocHdr = Alloc_HdrInf();
   Hash_Item((tp_Item)FilHdr, (tp_Loc)LocHdr);
   Init_HdrInf(&FilHdr->HdrInf);
   SetModified(FilHdr);
   FilHdr->HdrInf.LocHdr = LocHdr;
   FilHdr->HdrInf.Father = BaseFilHdr->LocHdr;
   FilHdr->HdrInf.Brother = BaseFilHdr->HdrInf.Son;
   BaseFilHdr->HdrInf.Son = LocHdr;
   SetModified(BaseFilHdr);

   FilHdr->HdrInf.FKind = FKind;
   FilHdr->FilTyp = FilTyp;
   FilHdr->HdrInf.IFilTyp = FilHdr->FilTyp->IFilTyp;
   FilHdr->Ident = (Ident==NIL ? BaseFilHdr->Ident : Ident);
   FilHdr->HdrInf.LocIdent = (Ident==NIL ? BaseFilHdr->HdrInf.LocIdent : WriteStr(Ident));
   FilHdr->FilPrm = FilPrm;
   FilHdr->HdrInf.LocPrm = FilPrm_LocPrm(FilPrm);
   InsertNesting += 1;
   if (InsertNesting > Log_InsertNesting) {
      Do_Log("Creating", FilHdr, LOGLEVEL_Create); }/*if*/;
   FilHdr->HdrInf.LocInp = Get_LocInp(FilHdr);
   InsertNesting -= 1;
   if (IsSource(FilHdr)) {
      if (strcmp(Ident, "..") == 0 || strcmp(Ident, ".") == 0) {
	 FATALERROR("bad identifier.\n"); }/*if*/;
      Update_SrcFilHdr(FilHdr, TRUE); }/*if*/;
   Ret_FilHdr(BaseFilHdr);
   return FilHdr;
   }/*Insert_FilHdr*/


tp_FilHdr
Extend_FilHdr(
   GMC_ARG(tp_FilHdr, BaseFilHdr),
   GMC_ARG(tp_FKind, FKind),
   GMC_ARG(tp_FilTyp, FilTyp),
   GMC_ARG(tp_FilPrm, FilPrm),
   GMC_ARG(tp_Str, IdentStr)
   )
   GMC_DCL(tp_FilHdr, BaseFilHdr)
   GMC_DCL(tp_FKind, FKind)
   GMC_DCL(tp_FilTyp, FilTyp)
   GMC_DCL(tp_FilPrm, FilPrm)
   GMC_DCL(tp_Str, IdentStr)
{
   tp_FilHdr FilHdr;
   tp_LocHdr LocHdr;
   tp_Ident Ident;

   FilHdr = ERROR;
   if (BaseFilHdr == ERROR || FilTyp == ERROR || FilPrm == ERROR) {
      Ret_FilHdr(BaseFilHdr);
      return FilHdr; }/*if*/;

   Ident = Sym_Str(Str_Sym(IdentStr));
   if (HasKey_FKind(FKind) && Ident == NIL) {
      FilHdr_Error("Element of <%s> must have a key.\n", BaseFilHdr);
      Ret_FilHdr(BaseFilHdr);
      return FilHdr; }/*if*/;

   for (FilHdr = LocHdr_FilHdr(BaseFilHdr->HdrInf.Son);
	FilHdr != NIL;
	LocHdr = FilHdr->HdrInf.Brother, Ret_FilHdr(FilHdr),
	 FilHdr = LocHdr_FilHdr(LocHdr)) {
      if (FilHdr->FilTyp == FilTyp
	  && (Ident == NIL || FilHdr->Ident == Ident)
	  && (FilHdr->HdrInf.FKind == FKind
	      || (IsSource_FKind(FilHdr->HdrInf.FKind)
		  && IsSource_FKind(FKind))
	      || (IsATgt_FKind(FilHdr->HdrInf.FKind)
		  && IsATgt_FKind(FKind))
	      || (IsVTgt_FKind(FilHdr->HdrInf.FKind)
		  && IsVTgt_FKind(FKind))
	      || (IsATgtText_FKind(FilHdr->HdrInf.FKind)
		  && IsATgtText_FKind(FKind))
	      || (IsVTgtText_FKind(FilHdr->HdrInf.FKind)
		  && IsVTgtText_FKind(FKind)))
	  && Equal_FilPrm(FilHdr->FilPrm, FilPrm)) {
	 Ret_FilHdr(BaseFilHdr);
	 return FilHdr; }/*if*/; }/*for*/;
   return Insert_FilHdr(BaseFilHdr, FKind, FilTyp, FilPrm, Ident);
   }/*Extend_FilHdr*/


tp_FilHdr
Get_Drv(
   GMC_ARG(tp_FilHdr, BaseFilHdr),
   GMC_ARG(tp_FKind, FKind),
   GMC_ARG(tp_FilTyp, FilTyp),
   GMC_ARG(tp_FilPrm, FilPrm),
   GMC_ARG(tp_Ident, Ident)
   )
   GMC_DCL(tp_FilHdr, BaseFilHdr)
   GMC_DCL(tp_FKind, FKind)
   GMC_DCL(tp_FilTyp, FilTyp)
   GMC_DCL(tp_FilPrm, FilPrm)
   GMC_DCL(tp_Ident, Ident)
{
   tp_FilHdr FilHdr, PipeBaseFilHdr;
   tps_Str NewIdent;
   tp_FilTyp NewFilTyp;

   if (BaseFilHdr==ERROR || FilTyp==ERROR || FilPrm==ERROR) {
      Ret_FilHdr(BaseFilHdr);
      return ERROR; }/*if*/;
   FORBIDDEN(FKind == ERROR);

   FilHdr = Extend_FilHdr(BaseFilHdr, FKind, FilTyp, FilPrm, Ident);
   if (IsGeneric(FilHdr)) {
      FORBIDDEN(FilHdr->HdrInf.FKind != FK_User);
      Key_InstanceLabel(NewIdent, FilHdr->Ident);
      NewFilTyp = Key_FilTyp(NewIdent);
      FilHdr = Extend_FilHdr(FilHdr, FK_Instance,
			     NewFilTyp, RootFilPrm, NewIdent); }/*if*/;
   if (IsPipe(FilHdr)) {
      PipeBaseFilHdr = Copy_FilHdr(BaseFilHdr);
      if (IsStruct(PipeBaseFilHdr)) {
	 PipeBaseFilHdr = FilHdr_Father(PipeBaseFilHdr); }/*if*/;
      PipeBaseFilHdr = Deref(PipeBaseFilHdr);
      NewFilTyp = FilHdr_FilTyp(PipeBaseFilHdr);
      Ret_FilHdr(PipeBaseFilHdr);
      if (NewFilTyp == ERROR || !IsAtmc_FilTyp(NewFilTyp)) {
	 NewFilTyp = FileFilTyp; }/*if*/;
      FORBIDDEN(FilHdr->HdrInf.FKind != FK_User);
      FilHdr = Extend_FilHdr(FilHdr, FK_Instance,
			     NewFilTyp, RootFilPrm, Ident); }/*if*/;
   return FilHdr;
   }/*Get_Drv*/


tp_FilHdr
Get_KeyDrv(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FKind, FKind),
   GMC_ARG(tp_Key, Key)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FKind, FKind)
   GMC_DCL(tp_Key, Key)
{
   return Get_Drv(FilHdr, FKind, Key_FilTyp(Key), RootFilPrm, Key);
   }/*Get_KeyDrv*/


