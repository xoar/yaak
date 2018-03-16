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

#include <stdio.h>
#include "inc/GMC.h"
#include "inc/Entry.h"
#include "inc/EnvVarLst.h"
#include "inc/InpEdg.h"
#include "inc/PrmTypLst.h"
#include "inc/TClass_.h"
#include "inc/Tool.h"


tp_Tool			ToolS = NIL;
static tp_Tool		LastTool = NIL;
int			num_ToolS = 0;

static tp_Tool		SourceTool;
static tp_Tool		StrTool;
static tp_Tool		DrvDirElmTool;
static tp_Tool		VirDirElmTool;

static tp_Tool		PntrHoTool;
static tp_Tool		PntrElmTool;
static tp_Tool		InternalPntrTool;
static tp_Tool		TextDefTool;


tp_Tool
New_Tool()
{
   tp_Tool Tool;

   Tool = (tp_Tool)malloc(sizeof(tps_Tool));
   /*select*/{
      if (LastTool == NIL) {
	 ToolS = Tool;
      }else{
	 LastTool->Link = Tool; };}/*select*/;
   LastTool = Tool;
   Tool->TClass = 0;
   Tool->FilTyp = 0;
   Tool->InpEdg = 0;
   Tool->HomInpEdg = 0;
   Tool->BasePrmTypLst = DfltPrmTypLst;
   Tool->PrmTypLst = 0;
   Tool->EnvVarLst = DfltEnvVarLst;
   Tool->Package = ".";
   Tool->Flag = 0;
   Tool->Defer = 0;
   Tool->Index = num_ToolS;
   Tool->Link = NIL;
   num_ToolS++;
   return Tool;
   }/*New_Tool*/


void
Init_Tools()
{
   SourceTool = New_Tool();
   SourceTool->TClass = TC_Source;

   StrTool = New_Tool();
   StrTool->TClass = TC_Str;

   DrvDirElmTool = New_Tool();
   DrvDirElmTool->TClass = TC_DrvDirElm;

   VirDirElmTool = New_Tool();
   VirDirElmTool->TClass = TC_VirDirElm;

   PntrHoTool = New_Tool();
   PntrHoTool->TClass = TC_PntrHo;

   PntrElmTool = New_Tool();
   PntrElmTool->TClass = TC_PntrElm;

   InternalPntrTool = New_Tool();
   InternalPntrTool->TClass = TC_InternalPntr;

   TextDefTool = New_Tool();
   TextDefTool->TClass = TC_TextDef;
   }/*Init_Tools*/


tp_EnvVarLst
Tool_EnvVarLst(Tool)
   tp_Tool Tool;
{
   return Tool->EnvVarLst;
   }/*Tool_EnvVarLst*/


void
Set_Tool_EnvVarLst(Tool, EnvVarLst)
   tp_Tool Tool;
   tp_EnvVarLst EnvVarLst;
{
   FORBIDDEN(Tool == ERROR || EnvVarLst == ERROR);
   Tool->EnvVarLst = EnvVarLst;
   }/*Set_Tool_EnvVarLst*/


void
Clear_ToolFlags()
{
   tp_Tool Tool;

   for (Tool = ToolS; Tool != NIL; Tool = Tool->Link) {
      Tool->Flag = FALSE; }/*for*/;
   }/*Clear_Flags*/


tp_Str
Tool_Name(Tool)
   tp_Tool Tool;
{
   return FilTyp_FTName(Tool->FilTyp);
   }/*Tool_Name*/


boolean
IsDummy_Tool(Tool)
   tp_Tool Tool;
{
   return (Tool->InpEdg == NIL);
   }/*IsDummy_Tool*/


void
Write_Tools(DRVGRF_FILE, DG_C_FILE)
   FILE *DRVGRF_FILE, *DG_C_FILE;
{
   tp_Tool Tool;
   int iInpEdg, iBasePrmTypLst, iEnvVarLst;
   tps_EntryStr sInpEdg, sBasePrmTypLst, sEnvVarLst;

   DG_FOREACH(Tool)
      DG_ENTRY(Tool,InpEdg,InpEdg);
      if (Tool->BasePrmTypLst == DfltPrmTypLst) Tool->BasePrmTypLst = 0;
      if (Tool->EnvVarLst == DfltEnvVarLst) Tool->EnvVarLst = 0;
      DG_ENTRY(Tool,BasePrmTypLst,PrmTypLst);
      DG_ENTRY(Tool,EnvVarLst,EnvVarLst);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, "%d %d %d %d .%s\1\n",
       Tool->TClass, iInpEdg, iBasePrmTypLst, iEnvVarLst, Tool->Package);
      (void)fprintf(DG_C_FILE, "{%d, %s, %s, %s, \"%s\"}",
       Tool->TClass, sInpEdg, sBasePrmTypLst, sEnvVarLst, Tool->Package);
   DG_END_FOREACH(Tool);

   DG_CONST(SourceTool,Tool);
   DG_CONST(StrTool,Tool);
   DG_CONST(DrvDirElmTool,Tool);
   DG_CONST(VirDirElmTool,Tool);
   DG_CONST(PntrHoTool,Tool);
   DG_CONST(PntrElmTool,Tool);
   DG_CONST(InternalPntrTool,Tool);
   DG_CONST(TextDefTool,Tool);
   }/*Write_Tools*/

