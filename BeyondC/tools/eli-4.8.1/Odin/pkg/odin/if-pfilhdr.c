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
#include "inc/PrmFHdr.h"


int			num_PrmFHdrS = 0;

static int		num_PrmFHdrs = 0;
static tp_PrmFHdr	FreePrmFHdr = NIL;

/* PrmFHdr's are absorbed when used as an argument to a function
 * that returns a PrmFHdr.
 */

tp_PrmFHdr
New_PrmFHdr(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilPrm, FilPrm)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilPrm, FilPrm)
{
   tp_PrmFHdr PrmFHdr;

   FORBIDDEN(FilHdr == ERROR || FilPrm == ERROR);

   /*select*/{
      if (FreePrmFHdr == NIL) {
	 PrmFHdr = (tp_PrmFHdr)malloc(sizeof(tps_PrmFHdr));
	 num_PrmFHdrS += 1;
	 PrmFHdr->InUse = FALSE;
      }else{
	 PrmFHdr = FreePrmFHdr;
	 FreePrmFHdr = FreePrmFHdr->Next; };}/*select*/;

   FORBIDDEN(PrmFHdr->InUse);
   num_PrmFHdrs += 1;
   PrmFHdr->InUse = TRUE;
   PrmFHdr->FilHdr = FilHdr;
   PrmFHdr->FilPrm = FilPrm;
   PrmFHdr->Next = NIL;
   return PrmFHdr;
   }/*New_PrmFHdr*/


static void
Rls_PrmFHdr(
   GMC_ARG(tp_PrmFHdr, PrmFHdr)
   )
   GMC_DCL(tp_PrmFHdr, PrmFHdr)
{
   FORBIDDEN(PrmFHdr == ERROR);
   PrmFHdr->Next = FreePrmFHdr;
   FORBIDDEN(!PrmFHdr->InUse);
   FORBIDDEN(PrmFHdr->FilHdr != NIL);
   PrmFHdr->InUse = FALSE;
   num_PrmFHdrs -= 1;
   FreePrmFHdr = PrmFHdr;
   }/*Rls_PrmFHdr*/


void
Use_PrmFHdr(
   GMC_ARG(tp_FilHdr*, FilHdrPtr),
   GMC_ARG(tp_FilPrm*, FilPrmPtr),
   GMC_ARG(tp_PrmFHdr, PrmFHdr)
   )
   GMC_DCL(tp_FilHdr*, FilHdrPtr)
   GMC_DCL(tp_FilPrm*, FilPrmPtr)
   GMC_DCL(tp_PrmFHdr, PrmFHdr)
{
   if (PrmFHdr == ERROR) {
      *FilHdrPtr = ERROR;
      *FilPrmPtr = ERROR;
      return; }/*if*/;
   *FilHdrPtr = PrmFHdr->FilHdr;
   PrmFHdr->FilHdr = NIL;
   *FilPrmPtr = PrmFHdr->FilPrm;
   Rls_PrmFHdr(PrmFHdr);
   }/*Use_PrmFHdr*/


boolean
PrmFHdrs_InUse(GMC_ARG_VOID)
{
   return (num_PrmFHdrs != 0);
   }/*PrmFHdrs_InUse*/

