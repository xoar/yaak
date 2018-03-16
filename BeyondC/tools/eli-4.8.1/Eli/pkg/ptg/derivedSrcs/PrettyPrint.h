
#ifndef _PRETTY_PRINT_H
#define _PRETTY_PRINT_H

#include "ptg_gen.h"
#include "eliproto.h"


void PP_SetLineWidth ELI_ARG((int newwidth));
void PP_BreakLine ELI_ARG((PTG_OUTPUT_FILE f));

void PP_SetSoftBreakShortcut ELI_ARG((char sbc));

void PP_Newline ELI_ARG((PTG_OUTPUT_FILE f));

void PP_SetIndentationWidth ELI_ARG((int newindent));
void PP_Indent ELI_ARG((PTG_OUTPUT_FILE f));
void PP_Exdent ELI_ARG((PTG_OUTPUT_FILE f));

void PP_SetEndline ELI_ARG((char *new_eol));

PTGNode PP_OutFPtr ELI_ARG((FILE *fptr, PTGNode root));
PTGNode PP_OutFile ELI_ARG((char *filename, PTGNode root));
PTGNode PP_Out ELI_ARG((PTGNode root));


#endif
