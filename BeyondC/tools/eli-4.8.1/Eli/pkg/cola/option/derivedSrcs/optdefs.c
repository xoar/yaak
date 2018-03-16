/*****************************************************************************\
* 									     *
*   Option-Tool for Parser Generators	       				     *
*   Author: M.Jung 							     *
*   									     *
*   Procedures to define and retrieve option values                          *
\*****************************************************************************/

#include "optdefs.h"

static char rcsid[] = "$Id: optdefs.c,v 1.3 1993/06/24 13:53:56 cogito Exp $";

optinfo optvalues[MAXOPT];

#define SETTO(o,i) optvalues[(int)o].optval = i
#define SET(o) SETTO(o,1)

/* Initialize option database and set the default option values */
void init_options()
{
    int i;

    /* Set optdefined to 0, so that no option ignored message is
     * printed out for the first option setting */

    for (i = 0; i < (int)MAXOPT; i++)
    {
	optvalues[i].optdefined = 0;
	optvalues[i].optval = 0;
    }

    /* Set the default option values */

    SET(OPT_HBL);
    SET(OPT_DGD);
    SET(OPT_MP);
    SET(OPT_CRE);
    SET(OPT_LP);
    SET(OPT_DFS);
    SET(OPT_CC);
    SET(OPT_DUM);
    SET(OPT_SRC);
    SET(OPT_IRC);
    SET(OPT_AEC);
    SET(OPT_CL);

    SETTO(OPT_TTAB,(int) MODE_RDS);
    SETTO(OPT_NTAB,(int) MODE_RDS);
}

/* Define a option, if not already defined */
int define_option(opt, val)
option opt;
int val;
{
    int already_defined = optvalues[(int)opt].optdefined;

    optvalues[(int)opt].optval = val;
    optvalues[(int)opt].optdefined = 1;

    return already_defined;
}







