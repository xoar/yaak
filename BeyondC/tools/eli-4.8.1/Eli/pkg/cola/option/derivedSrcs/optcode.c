/*****************************************************************************\
*								       	     *
*   Option-Tool for Parser Generators					     *
*   Author: M.Jung 							     *
*   									     *
*   Code-Generation.							     *
\*****************************************************************************/
 
static char rcsid[] = "$Id: optcode.c,v 1.2 1992/02/24 17:33:24 cogito Exp $";

#include "optdefs.h"
#include "ptg_gen.h"
#include "clp.h"
#include "optcode.h"

PTGNode DirectOptionCode (AllowDirect)
int AllowDirect;
{
    PTGNode n = PTGNULL;
    
    if (!AllowDirect) return PTGNULL;
    
    if (optvalues[(int)OPT_HBL].optval)
    	n = PTGseq(n, PTGhbl());

    if (optvalues[(int)OPT_DGD].optval)
    	n = PTGseq(n, PTGdgd());
    
    if (optvalues[(int)OPT_MP].optval)
    	n = PTGseq(n, PTGmp());
    
    if (optvalues[(int)OPT_CRE].optval)
    	n = PTGseq(n, PTGcre());

    if (optvalues[(int)OPT_LP].optval)
    	n = PTGseq(n, PTGlp());

    if (optvalues[(int)OPT_NOC].optdefined)
    	n = PTGseq(n, PTGnoc(PTGzahl(optvalues[(int)OPT_NOC].optval)));

    if (optvalues[(int)OPT_NOSA].optdefined)
    	n = PTGseq(n, PTGnosa(PTGzahl(optvalues[(int)OPT_NOSA].optval)));

    if (optvalues[(int)OPT_DFS].optval)
    	n = PTGseq(n, PTGdfs());

    if (optvalues[(int)OPT_SCC].optval)
    	n = PTGseq(n, PTGscc());

    if (optvalues[(int)OPT_CC].optval)
    	n = PTGseq(n, PTGcc());

    if (optvalues[(int)OPT_DUM].optval)
    	n = PTGseq(n, PTGdum());

    if (optvalues[(int)OPT_SRC].optval)
    	n = PTGseq(n, PTGsrc());

    if (optvalues[(int)OPT_IRC].optval)
    	n = PTGseq(n, PTGirc());

    if (optvalues[(int)OPT_DSC].optval)
    	n = PTGseq(n, PTGdsc());

    if (optvalues[(int)OPT_LO].optdefined)
    	n = PTGseq(n, PTGlo(PTGzahl(optvalues[(int)OPT_LO].optval)));

    if (optvalues[(int)OPT_AEC].optval)
    	n = PTGseq(n, PTGaec());

    if (optvalues[(int)OPT_CL].optval)
    	n = PTGseq(n, PTGcl());

    if (optvalues[(int)OPT_QZ].optdefined)
    	n = PTGseq(n, PTGqz(PTGzahl(optvalues[(int)OPT_QZ].optval)));

    if (optvalues[(int)OPT_SZ].optdefined)
    	n = PTGseq(n, PTGsz(PTGzahl(optvalues[(int)OPT_SZ].optval)));

    return n;
}

static PTGNode PTGmakemode(m)
int m;
{
    switch ((tabmode)m)
    {
      case MODE_GCSA:
	return PTGmode_gcsa();
      case MODE_GCSB:
	return PTGmode_gcsb();
      case MODE_LESA:
	return PTGmode_lesa();
      case MODE_LESB:
	return PTGmode_lesb();
      case MODE_RCSA:
	return PTGmode_rcsa();
      case MODE_RCSB:
	return PTGmode_rcsb();
      case MODE_SDS:
	return PTGmode_sds();
      case MODE_RDS:
	return PTGmode_rds();
      default:
	return PTGNULL;
    }
}

       
PTGNode TableOptionCode(allowTable)
int allowTable;
{
    PTGNode n;
    
    if (!allowTable) return PTGNULL;
    
    n = PTGttab(PTGmakemode(optvalues[(int)OPT_TTAB].optval));
    n = PTGline(n, PTGntab(PTGmakemode(optvalues[(int)OPT_NTAB].optval)));
    
    if (optvalues[(int)OPT_OPTINFO].optval)
    	n = PTGline(n, PTGoptinfo());

    return n;
}

PTGNode FrontendOptionCode ()
{
    PTGNode n = PTGNULL;
    
    if (optvalues[(int)OPT_INFO].optval)
    	n = PTGinfo();
    
    if (optvalues[(int)OPT_FREEPOS].optval)
    	n = ( n == PTGNULL) ? PTGfreepos() : PTGline(n, PTGfreepos());
    
    return n;
    
}

PTGNode TableOptionCode2 (allowTable)
int allowTable;
{
    if (allowTable && !optvalues[(int)OPT_AEC].optval)
    	return PTGaecfile();
    else
    	return PTGNULL;
}

    
    
    




