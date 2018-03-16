/*****************************************************************************\
*								       	     *
*   Option-Tool for Parser Generators					     *
*   Author: M.Jung 							     *
*   									     *
*   Headerfile defining Option Database to store option values               *
\*****************************************************************************/
 
/* $Id: optdefs.h,v 1.1 1992/01/22 15:14:23 cogito Exp $ */

#ifndef OPTDEFS_H
#define OPTDEFS_H

typedef enum optswitchenum
{
    off, on
} optswitch;

typedef enum tabmodeenum
{
    MODE_GCSA, MODE_GCSB, MODE_LESA, MODE_LESB,
    MODE_RCSA, MODE_RCSB, MODE_SDS, MODE_RDS
} tabmode;

typedef enum optionenum 
{
    /* Options for direct executable parser */

    OPT_HBL, OPT_DGD, OPT_MP, OPT_CRE, OPT_LP, 
    OPT_NOC, OPT_NOSA, OPT_DFS, OPT_SCC, OPT_CC, 
    OPT_DUM, OPT_SRC, OPT_IRC, OPT_DSC, OPT_LO, 
    OPT_AEC, OPT_CL, OPT_QZ, OPT_SZ,

    /* Options for table driven parser */

    OPT_OPTINFO, OPT_TTAB, OPT_NTAB,

    /* Options for Frontend */

    OPT_INFO, OPT_FREEPOS,

    /* This option is for automatic sizing of option array */

    MAXOPT
    
} option;

typedef struct 
{
    int optval;
    char optdefined;
} optinfo;

extern optinfo optvalues[MAXOPT];

void init_options();
int define_option();


#endif
    
    
