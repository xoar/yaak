/* $Log: keywords.c,v $
 * Revision 1.4  2001/11/05 17:23:46  cogito
 * *** empty log message ***
 *
 * Revision 1.2  2000/04/03 12:51:26  peter
 * Introduction of option "NO_GROUPING"
 * If this option is set, all grouping of variables is supressed,
 * including the grouping requested by system internal grouping
 * directives for CHAIN attributes.  This option usually leads to
 * increased memory and time requirements of the generated processor. It
 * is only recommended during the development of language processors for
 * large specifications, since it may decrease the time required for
 * processor generation.
 *
 * Revision 1.1  1996/02/06 13:30:25  cogito
 * Initial revision
 *
 * Revision 2.3  1991/07/23  17:21:12  cogito
 * expand options: INCLUDING_FUNCTION replaced by INCLUDING ON / OFF
 * order options: new option ARRANGE FAST to cancel default ARRANGE AUTOMATICALLY
 * backend options: new option FREE_TREE (opposite of KEEP_TREE)
 *
 * Revision 2.2  91/01/24  14:59:37  cogito
 * added new backend option
 * 
 * Revision 2.1  90/12/04  14:42:39  cogito
 * new version of option handler
 *  */

static char rcs_id[]= "$Id: keywords.c,v 1.4 2001/11/05 17:23:46 cogito Exp $";

/***********************************************************************\
*	keywords.c							*
*	strings with keywords for LIGA option handler			*
*									*
*	Written 06/20/90 - 07/23/91	by HaDeS			*
\***********************************************************************/

#include <stdio.h>
#include "keywords.h"

keywords exp1kw= {
	"CONST_ATTR_NAME", "INCL_ATTR_NAME",
	"CHAIN_PRE_ATTR_NAME", "CHAIN_POST_ATTR_NAME", NULL
};

keywords exp2kw= {
	"INCLUDINGS_SEPARATE", "INFO", NULL
};

keywords exp3kw= {
	"ON", "OFF", NULL
};

keywords ord1kw= {
	"PARTITION", "TOPOLOGICAL", NULL
};

keywords ord2kw= {
	"EARLY", "LATE", NULL
};

keywords ord3kw= {
	"DIRECT_SYMBOL", "TRANSITIVE_SYMBOL", "INDUCED_SYMBOL",
	"DIRECT_RULE", "TRANSITIVE_RULE", "INDUCED_RULE", "PARTITIONED_RULE",
	"PARTITION", "VISIT_SEQUENCE", NULL
};

keywords ord4kw= {
	"COMPLETE", "BOTTOM_UP", "TOP_DOWN", NULL
};

keywords opt1kw= {
	"OFF", "INFO", "MORE_GLOBALS", "NO_VARIABLES", "NO_STACKS", "NO_GROUPING", NULL
};

keywords opt2kw= {
	"VARIABLE", "STACK", "ALL", NULL
};

keywords opt3kw= {
	"GLOBAL", "GROUP", NULL
};

keywords opt4kw= {
	"STACK", "VAR", NULL
};

keywords be1kw= {
	"READABLE", "KEEP_TREE", "FREE_TREE", NULL
};

keywords be2kw= {
	"SPLIT_CASE", "ATSTACK_SIZE", "NODESTACK_SIZE", NULL
};

