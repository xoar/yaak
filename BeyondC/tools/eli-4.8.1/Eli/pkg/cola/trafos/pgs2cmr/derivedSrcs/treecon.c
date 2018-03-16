
/* implementation of tree construction functions */

#include "node.h"

#include "nodecode.h"

#include "attrpredef.h"

#include "visitmap.h"

#include "treeact.h"

#ifdef MONITOR
#include "attr_mon_dapto.h"
#endif

#include <stdlib.h>

#define _USE_OBSTACK 1

/* use of obstack: */

#if _USE_OBSTACK

#include "obstack.h"
static struct obstack TreeSpace;
static void *_TreeBase;

#ifdef __cplusplus
void* NODEPTR_struct::operator new(size_t size)
{
	return obstack_alloc(&TreeSpace, size);
}
#else
#if defined(__STDC__) || defined(__cplusplus)
char* TreeNodeAlloc(int size)
#else
char* TreeNodeAlloc(size) int size;
#endif
{
	return (char *)(obstack_alloc(&TreeSpace, size));
}
#endif

void InitTree()
{
	obstack_init(&TreeSpace);
	_TreeBase=obstack_alloc(&TreeSpace,0);
}

void FreeTree()
{
	obstack_free(&TreeSpace, _TreeBase);
	_TreeBase=obstack_alloc(&TreeSpace,0);
}

#else

#include <stdio.h>

#ifdef __cplusplus
void* NODEPTR_struct::operator new(size_t size)
{
	void *retval = malloc(size);
	if (retval) return retval;
	fprintf(stderr, "*** DEADLY: No more memory.\n");
	exit(1);
}
#else
#if defined(__STDC__) || defined(__cplusplus)
char* TreeNodeAlloc(int size)
#else
char* TreeNodeAlloc(size) int size;
#endif
{
	char *retval = (char *) malloc(size);
	if (retval) return retval;
	fprintf(stderr, "*** DEADLY: No more memory.\n");
	exit(1);
}
#endif

void InitTree() { }

void FreeTree() { }

#endif

#ifdef MONITOR
#define _SETCOORD(node) \
        node->_coord = _coordref ? *_coordref : NoCoord;
#define _COPYCOORD(node) \
        node->_coord = _currn->_desc1->_coord;
#else
#define _SETCOORD(node)
#define _COPYCOORD(node)
#endif
#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkpgs_root (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkpgs_root (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBpgs_root)) return (_currn);
return(NULLNODEPTR);
}/* Mkpgs_root */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG3 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG3 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG3)) return (_currn);
return(NULLNODEPTR);
}/* MkG3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG2 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG2 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG2)) return (_currn);
return(NULLNODEPTR);
}/* MkG2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkerr_part (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkerr_part (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBerr_part)) return (_currn);
return(NULLNODEPTR);
}/* Mkerr_part */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG4 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG4 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG4)) return (_currn);
return(NULLNODEPTR);
}/* MkG4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG1 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG1 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG1)) return (_currn);
return(NULLNODEPTR);
}/* MkG1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkactpts_root (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkactpts_root (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBactpts_root)) return (_currn);
return(NULLNODEPTR);
}/* Mkactpts_root */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkterm_def (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkterm_def (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBterm_def)) return (_currn);
return(NULLNODEPTR);
}/* Mkterm_def */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkcode_def (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkcode_def (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBcode_def)) return (_currn);
return(NULLNODEPTR);
}/* Mkcode_def */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkelem_list (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkelem_list (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBelem_list)) return (_currn);
if (IsSymb (_currn, SYMBG4)) return (Mkrule_39(_coordref, _currn));
return(NULLNODEPTR);
}/* Mkelem_list */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkalt_op (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkalt_op (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBalt_op)) return (_currn);
return(NULLNODEPTR);
}/* Mkalt_op */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkmod_op (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkmod_op (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBmod_op)) return (_currn);
return(NULLNODEPTR);
}/* Mkmod_op */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkskip_part (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkskip_part (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBskip_part)) return (_currn);
return(NULLNODEPTR);
}/* Mkskip_part */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkbracket_part (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkbracket_part (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBbracket_part)) return (_currn);
return(NULLNODEPTR);
}/* Mkbracket_part */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkterm_def_list (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkterm_def_list (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBterm_def_list)) return (_currn);
if (IsSymb (_currn, SYMBG2)) return (Mkrule_63(_coordref, _currn));
return(NULLNODEPTR);
}/* Mkterm_def_list */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mksepa_part (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mksepa_part (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBsepa_part)) return (_currn);
return(NULLNODEPTR);
}/* Mksepa_part */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkcode_def_list (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkcode_def_list (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBcode_def_list)) return (_currn);
if (IsSymb (_currn, SYMBG1)) return (Mkrule_35(_coordref, _currn));
return(NULLNODEPTR);
}/* Mkcode_def_list */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkcode_part (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkcode_part (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBcode_part)) return (_currn);
return(NULLNODEPTR);
}/* Mkcode_part */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkelem (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkelem (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBelem)) return (_currn);
if (IsSymb (_currn, SYMBnonliteral)) return (Mkrule_2(_coordref, _currn));
if (IsSymb (_currn, SYMBliteral)) return (Mkrule_2(_coordref, _currn));
if (IsSymb (_currn, SYMBoptelem)) return (Mkrule_22(_coordref, _currn));
if (IsSymb (_currn, SYMBt_or_nt)) return (Mkrule_2(_coordref, _currn));
return(NULLNODEPTR);
}/* Mkelem */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkoptelem (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkoptelem (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBoptelem)) return (_currn);
return(NULLNODEPTR);
}/* Mkoptelem */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkdel_op (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkdel_op (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBdel_op)) return (_currn);
return(NULLNODEPTR);
}/* Mkdel_op */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrep_op (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkrep_op (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBrep_op)) return (_currn);
return(NULLNODEPTR);
}/* Mkrep_op */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkstop_part (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkstop_part (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBstop_part)) return (_currn);
return(NULLNODEPTR);
}/* Mkstop_part */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkmodification (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkmodification (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBmodification)) return (_currn);
return(NULLNODEPTR);
}/* Mkmodification */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mknonliteral (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mknonliteral (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBnonliteral)) return (_currn);
return(NULLNODEPTR);
}/* Mknonliteral */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkliteral (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkliteral (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBliteral)) return (_currn);
return(NULLNODEPTR);
}/* Mkliteral */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkconnection (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkconnection (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBconnection)) return (_currn);
return(NULLNODEPTR);
}/* Mkconnection */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkt_or_nt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkt_or_nt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBt_or_nt)) return (_currn);
if (IsSymb (_currn, SYMBnonliteral)) return (Mkrule_25(_coordref, _currn));
if (IsSymb (_currn, SYMBliteral)) return (Mkrule_24(_coordref, _currn));
return(NULLNODEPTR);
}/* Mkt_or_nt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkterminal (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkterminal (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBterminal)) return (_currn);
if (IsSymb (_currn, SYMBnonliteral)) return (Mkrule_65(_coordref, _currn));
if (IsSymb (_currn, SYMBliteral)) return (Mkrule_64(_coordref, _currn));
return(NULLNODEPTR);
}/* Mkterminal */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkroot (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkroot (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBroot)) return (_currn);
return(NULLNODEPTR);
}/* Mkroot */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrhs (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkrhs (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBrhs)) return (_currn);
if (IsSymb (_currn, SYMBG4)) return (Mkrule_32(_coordref, _currn));
if (IsSymb (_currn, SYMBelem_list)) return (Mkrule_32(_coordref, _currn));
return(NULLNODEPTR);
}/* Mkrhs */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mksep_op (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mksep_op (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBsep_op)) return (_currn);
return(NULLNODEPTR);
}/* Mksep_op */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mknonterminal (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mknonterminal (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBnonterminal)) return (_currn);
return(NULLNODEPTR);
}/* Mknonterminal */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrulename (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkrulename (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBrulename)) return (_currn);
return(NULLNODEPTR);
}/* Mkrulename */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkrule (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBrule)) return (_currn);
return(NULLNODEPTR);
}/* Mkrule */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_list (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkrule_list (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBrule_list)) return (_currn);
if (IsSymb (_currn, SYMBG3)) return (Mkrule_58(_coordref, _currn));
return(NULLNODEPTR);
}/* Mkrule_list */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkstart (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkstart (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBstart)) return (_currn);
return(NULLNODEPTR);
}/* Mkstart */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkgrammarname (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkgrammarname (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBgrammarname)) return (_currn);
return(NULLNODEPTR);
}/* Mkgrammarname */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkgrammar_part (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkgrammar_part (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBgrammar_part)) return (_currn);
return(NULLNODEPTR);
}/* Mkgrammar_part */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_1 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_1 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_1 _currn;
#ifdef __cplusplus
_currn = new _TPrule_1;
#else
_currn = (_TPPrule_1) TreeNodeAlloc (sizeof (struct _TPrule_1));
#endif
_currn->_prod = RULErule_1;
_currn->_desc1 = (_TSPsep_op) Mksep_op (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_1: root of subtree no. 1 can not be made a sep_op node ", 0, _coordref);
_currn->_desc2 = (_TSPnonterminal) Mknonterminal (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_1: root of subtree no. 2 can not be made a nonterminal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_1;
return ( (NODEPTR) _currn);
}/* Mkrule_1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_2 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_2 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_2 _currn;
#ifdef __cplusplus
_currn = new _TPrule_2;
#else
_currn = (_TPPrule_2) TreeNodeAlloc (sizeof (struct _TPrule_2));
#endif
_currn->_prod = RULErule_2;
_currn->_desc1 = (_TSPt_or_nt) Mkt_or_nt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_2: root of subtree no. 1 can not be made a t_or_nt node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_2;
return ( (NODEPTR) _currn);
}/* Mkrule_2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_3 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_3 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_3 _currn;
#ifdef __cplusplus
_currn = new _TPrule_3;
#else
_currn = (_TPPrule_3) TreeNodeAlloc (sizeof (struct _TPrule_3));
#endif
_currn->_prod = RULErule_3;
_currn->_desc1 = (_TSPterminal) Mkterminal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_3: root of subtree no. 1 can not be made a terminal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_3;
return ( (NODEPTR) _currn);
}/* Mkrule_3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_4 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_4 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_4 _currn;
#ifdef __cplusplus
_currn = new _TPrule_4;
#else
_currn = (_TPPrule_4) TreeNodeAlloc (sizeof (struct _TPrule_4));
#endif
_currn->_prod = RULErule_4;
_currn->_desc1 = (_TSPmod_op) Mkmod_op (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_4: root of subtree no. 1 can not be made a mod_op node ", 0, _coordref);
_currn->_desc2 = (_TSPterminal) Mkterminal (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_4: root of subtree no. 2 can not be made a terminal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_4;
return ( (NODEPTR) _currn);
}/* Mkrule_4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_5 (POSITION *_coordref, NODEPTR _desc1, int _TERM1)
#else
NODEPTR Mkrule_5 (_coordref,_desc1, _TERM1)
	POSITION *_coordref;
	NODEPTR _desc1;
	int _TERM1;
#endif
{	_TPPrule_5 _currn;
#ifdef __cplusplus
_currn = new _TPrule_5;
#else
_currn = (_TPPrule_5) TreeNodeAlloc (sizeof (struct _TPrule_5));
#endif
_currn->_prod = RULErule_5;
_currn->_desc1 = (_TSPterminal) Mkterminal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_5: root of subtree no. 1 can not be made a terminal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_5;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "CARDINAL", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_5 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_6 (POSITION *_coordref)
#else
NODEPTR Mkrule_6 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_6 _currn;
#ifdef __cplusplus
_currn = new _TPrule_6;
#else
_currn = (_TPPrule_6) TreeNodeAlloc (sizeof (struct _TPrule_6));
#endif
_currn->_prod = RULErule_6;
_SETCOORD(_currn)
_TERMACT_rule_6;
return ( (NODEPTR) _currn);
}/* Mkrule_6 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_7 (POSITION *_coordref)
#else
NODEPTR Mkrule_7 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_7 _currn;
#ifdef __cplusplus
_currn = new _TPrule_7;
#else
_currn = (_TPPrule_7) TreeNodeAlloc (sizeof (struct _TPrule_7));
#endif
_currn->_prod = RULErule_7;
_SETCOORD(_currn)
_TERMACT_rule_7;
return ( (NODEPTR) _currn);
}/* Mkrule_7 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_8 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_8 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_8 _currn;
#ifdef __cplusplus
_currn = new _TPrule_8;
#else
_currn = (_TPPrule_8) TreeNodeAlloc (sizeof (struct _TPrule_8));
#endif
_currn->_prod = RULErule_8;
_currn->_desc1 = (_TSPelem) Mkelem (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_8: root of subtree no. 1 can not be made a elem node ", 0, _coordref);
_currn->_desc2 = (_TSPrep_op) Mkrep_op (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_8: root of subtree no. 2 can not be made a rep_op node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_8;
return ( (NODEPTR) _currn);
}/* Mkrule_8 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_9 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_9 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_9 _currn;
#ifdef __cplusplus
_currn = new _TPrule_9;
#else
_currn = (_TPPrule_9) TreeNodeAlloc (sizeof (struct _TPrule_9));
#endif
_currn->_prod = RULErule_9;
_currn->_desc1 = (_TSPrhs) Mkrhs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 1 can not be made a rhs node ", 0, _coordref);
_currn->_desc2 = (_TSPalt_op) Mkalt_op (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 2 can not be made a alt_op node ", 0, _coordref);
_currn->_desc3 = (_TSPelem_list) Mkelem_list (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 3 can not be made a elem_list node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_9;
return ( (NODEPTR) _currn);
}/* Mkrule_9 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_10 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_10 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_10 _currn;
#ifdef __cplusplus
_currn = new _TPrule_10;
#else
_currn = (_TPPrule_10) TreeNodeAlloc (sizeof (struct _TPrule_10));
#endif
_currn->_prod = RULErule_10;
_currn->_desc1 = (_TSPrhs) Mkrhs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 1 can not be made a rhs node ", 0, _coordref);
_currn->_desc2 = (_TSPdel_op) Mkdel_op (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 2 can not be made a del_op node ", 0, _coordref);
_currn->_desc3 = (_TSPterminal) Mkterminal (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 3 can not be made a terminal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_10;
return ( (NODEPTR) _currn);
}/* Mkrule_10 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_11 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_11 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_11 _currn;
#ifdef __cplusplus
_currn = new _TPrule_11;
#else
_currn = (_TPPrule_11) TreeNodeAlloc (sizeof (struct _TPrule_11));
#endif
_currn->_prod = RULErule_11;
_currn->_desc1 = (_TSPnonterminal) Mknonterminal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 1 can not be made a nonterminal node ", 0, _coordref);
_currn->_desc2 = (_TSPsep_op) Mksep_op (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 2 can not be made a sep_op node ", 0, _coordref);
_currn->_desc3 = (_TSPrhs) Mkrhs (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 3 can not be made a rhs node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_11;
return ( (NODEPTR) _currn);
}/* Mkrule_11 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_12 (POSITION *_coordref)
#else
NODEPTR Mkrule_12 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_12 _currn;
#ifdef __cplusplus
_currn = new _TPrule_12;
#else
_currn = (_TPPrule_12) TreeNodeAlloc (sizeof (struct _TPrule_12));
#endif
_currn->_prod = RULErule_12;
_SETCOORD(_currn)
_TERMACT_rule_12;
return ( (NODEPTR) _currn);
}/* Mkrule_12 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_13 (POSITION *_coordref)
#else
NODEPTR Mkrule_13 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_13 _currn;
#ifdef __cplusplus
_currn = new _TPrule_13;
#else
_currn = (_TPPrule_13) TreeNodeAlloc (sizeof (struct _TPrule_13));
#endif
_currn->_prod = RULErule_13;
_SETCOORD(_currn)
_TERMACT_rule_13;
return ( (NODEPTR) _currn);
}/* Mkrule_13 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_14 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_14 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_14 _currn;
#ifdef __cplusplus
_currn = new _TPrule_14;
#else
_currn = (_TPPrule_14) TreeNodeAlloc (sizeof (struct _TPrule_14));
#endif
_currn->_prod = RULErule_14;
_currn->_desc1 = (_TSPterm_def_list) Mkterm_def_list (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_14: root of subtree no. 1 can not be made a term_def_list node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_14;
return ( (NODEPTR) _currn);
}/* Mkrule_14 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_15 (POSITION *_coordref)
#else
NODEPTR Mkrule_15 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_15 _currn;
#ifdef __cplusplus
_currn = new _TPrule_15;
#else
_currn = (_TPPrule_15) TreeNodeAlloc (sizeof (struct _TPrule_15));
#endif
_currn->_prod = RULErule_15;
_SETCOORD(_currn)
_TERMACT_rule_15;
return ( (NODEPTR) _currn);
}/* Mkrule_15 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_16 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_16 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_16 _currn;
#ifdef __cplusplus
_currn = new _TPrule_16;
#else
_currn = (_TPPrule_16) TreeNodeAlloc (sizeof (struct _TPrule_16));
#endif
_currn->_prod = RULErule_16;
_currn->_desc1 = (_TSPterm_def_list) Mkterm_def_list (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_16: root of subtree no. 1 can not be made a term_def_list node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_16;
return ( (NODEPTR) _currn);
}/* Mkrule_16 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_17 (POSITION *_coordref)
#else
NODEPTR Mkrule_17 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_17 _currn;
#ifdef __cplusplus
_currn = new _TPrule_17;
#else
_currn = (_TPPrule_17) TreeNodeAlloc (sizeof (struct _TPrule_17));
#endif
_currn->_prod = RULErule_17;
_SETCOORD(_currn)
_TERMACT_rule_17;
return ( (NODEPTR) _currn);
}/* Mkrule_17 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_18 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_18 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_18 _currn;
#ifdef __cplusplus
_currn = new _TPrule_18;
#else
_currn = (_TPPrule_18) TreeNodeAlloc (sizeof (struct _TPrule_18));
#endif
_currn->_prod = RULErule_18;
_currn->_desc1 = (_TSPterm_def_list) Mkterm_def_list (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_18: root of subtree no. 1 can not be made a term_def_list node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_18;
return ( (NODEPTR) _currn);
}/* Mkrule_18 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_19 (POSITION *_coordref)
#else
NODEPTR Mkrule_19 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_19 _currn;
#ifdef __cplusplus
_currn = new _TPrule_19;
#else
_currn = (_TPPrule_19) TreeNodeAlloc (sizeof (struct _TPrule_19));
#endif
_currn->_prod = RULErule_19;
_SETCOORD(_currn)
_TERMACT_rule_19;
return ( (NODEPTR) _currn);
}/* Mkrule_19 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_20 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_20 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_20 _currn;
#ifdef __cplusplus
_currn = new _TPrule_20;
#else
_currn = (_TPPrule_20) TreeNodeAlloc (sizeof (struct _TPrule_20));
#endif
_currn->_prod = RULErule_20;
_currn->_desc1 = (_TSPcode_def_list) Mkcode_def_list (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_20: root of subtree no. 1 can not be made a code_def_list node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_20;
return ( (NODEPTR) _currn);
}/* Mkrule_20 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_21 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_21 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_21 _currn;
#ifdef __cplusplus
_currn = new _TPrule_21;
#else
_currn = (_TPPrule_21) TreeNodeAlloc (sizeof (struct _TPrule_21));
#endif
_currn->_prod = RULErule_21;
_currn->_desc1 = (_TSPrhs) Mkrhs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_21: root of subtree no. 1 can not be made a rhs node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_21;
return ( (NODEPTR) _currn);
}/* Mkrule_21 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_22 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_22 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_22 _currn;
#ifdef __cplusplus
_currn = new _TPrule_22;
#else
_currn = (_TPPrule_22) TreeNodeAlloc (sizeof (struct _TPrule_22));
#endif
_currn->_prod = RULErule_22;
_currn->_desc1 = (_TSPoptelem) Mkoptelem (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_22: root of subtree no. 1 can not be made a optelem node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_22;
return ( (NODEPTR) _currn);
}/* Mkrule_22 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_23 (POSITION *_coordref)
#else
NODEPTR Mkrule_23 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_23 _currn;
#ifdef __cplusplus
_currn = new _TPrule_23;
#else
_currn = (_TPPrule_23) TreeNodeAlloc (sizeof (struct _TPrule_23));
#endif
_currn->_prod = RULErule_23;
_SETCOORD(_currn)
_TERMACT_rule_23;
return ( (NODEPTR) _currn);
}/* Mkrule_23 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_24 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_24 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_24 _currn;
#ifdef __cplusplus
_currn = new _TPrule_24;
#else
_currn = (_TPPrule_24) TreeNodeAlloc (sizeof (struct _TPrule_24));
#endif
_currn->_prod = RULErule_24;
_currn->_desc1 = (_TSPliteral) Mkliteral (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_24: root of subtree no. 1 can not be made a literal node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_24;
return ( (NODEPTR) _currn);
}/* Mkrule_24 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_25 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_25 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_25 _currn;
#ifdef __cplusplus
_currn = new _TPrule_25;
#else
_currn = (_TPPrule_25) TreeNodeAlloc (sizeof (struct _TPrule_25));
#endif
_currn->_prod = RULErule_25;
_currn->_desc1 = (_TSPnonliteral) Mknonliteral (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_25: root of subtree no. 1 can not be made a nonliteral node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_25;
return ( (NODEPTR) _currn);
}/* Mkrule_25 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_26 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_26 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_26 _currn;
#ifdef __cplusplus
_currn = new _TPrule_26;
#else
_currn = (_TPPrule_26) TreeNodeAlloc (sizeof (struct _TPrule_26));
#endif
_currn->_prod = RULErule_26;
_currn->_desc1 = (_TSPterminal) Mkterminal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_26: root of subtree no. 1 can not be made a terminal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_26;
return ( (NODEPTR) _currn);
}/* Mkrule_26 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_27 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_27 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_27 _currn;
#ifdef __cplusplus
_currn = new _TPrule_27;
#else
_currn = (_TPPrule_27) TreeNodeAlloc (sizeof (struct _TPrule_27));
#endif
_currn->_prod = RULErule_27;
_SETCOORD(_currn)
_TERMACT_rule_27;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "NAME", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_27 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_28 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3, NODEPTR _desc4)
#else
NODEPTR Mkrule_28 (_coordref,_desc1,_desc2,_desc3,_desc4)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
	NODEPTR _desc4;
#endif
{	_TPPrule_28 _currn;
#ifdef __cplusplus
_currn = new _TPrule_28;
#else
_currn = (_TPPrule_28) TreeNodeAlloc (sizeof (struct _TPrule_28));
#endif
_currn->_prod = RULErule_28;
_currn->_desc1 = (_TSPrulename) Mkrulename (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_28: root of subtree no. 1 can not be made a rulename node ", 0, _coordref);
_currn->_desc2 = (_TSPnonterminal) Mknonterminal (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_28: root of subtree no. 2 can not be made a nonterminal node ", 0, _coordref);
_currn->_desc3 = (_TSPsep_op) Mksep_op (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_28: root of subtree no. 3 can not be made a sep_op node ", 0, _coordref);
_currn->_desc4 = (_TSPrhs) Mkrhs (_coordref, _desc4);	
if (((NODEPTR)_currn->_desc4) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_28: root of subtree no. 4 can not be made a rhs node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_28;
return ( (NODEPTR) _currn);
}/* Mkrule_28 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_29 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_29 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_29 _currn;
#ifdef __cplusplus
_currn = new _TPrule_29;
#else
_currn = (_TPPrule_29) TreeNodeAlloc (sizeof (struct _TPrule_29));
#endif
_currn->_prod = RULErule_29;
_SETCOORD(_currn)
_TERMACT_rule_29;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "NAME", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_29 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_30 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_30 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_30 _currn;
#ifdef __cplusplus
_currn = new _TPrule_30;
#else
_currn = (_TPPrule_30) TreeNodeAlloc (sizeof (struct _TPrule_30));
#endif
_currn->_prod = RULErule_30;
_currn->_desc1 = (_TSPgrammarname) Mkgrammarname (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_30: root of subtree no. 1 can not be made a grammarname node ", 0, _coordref);
_currn->_desc2 = (_TSPstart) Mkstart (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_30: root of subtree no. 2 can not be made a start node ", 0, _coordref);
_currn->_desc3 = (_TSPrule_list) Mkrule_list (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_30: root of subtree no. 3 can not be made a rule_list node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_30;
return ( (NODEPTR) _currn);
}/* Mkrule_30 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_65 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_65 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_65 _currn;
#ifdef __cplusplus
_currn = new _TPrule_65;
#else
_currn = (_TPPrule_65) TreeNodeAlloc (sizeof (struct _TPrule_65));
#endif
_currn->_prod = RULErule_65;
_currn->_desc1 = (_TSPnonliteral) Mknonliteral (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_65: root of subtree no. 1 can not be made a nonliteral node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_65;
return ( (NODEPTR) _currn);
}/* Mkrule_65 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_64 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_64 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_64 _currn;
#ifdef __cplusplus
_currn = new _TPrule_64;
#else
_currn = (_TPPrule_64) TreeNodeAlloc (sizeof (struct _TPrule_64));
#endif
_currn->_prod = RULErule_64;
_currn->_desc1 = (_TSPliteral) Mkliteral (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_64: root of subtree no. 1 can not be made a literal node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_64;
return ( (NODEPTR) _currn);
}/* Mkrule_64 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_63 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_63 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_63 _currn;
#ifdef __cplusplus
_currn = new _TPrule_63;
#else
_currn = (_TPPrule_63) TreeNodeAlloc (sizeof (struct _TPrule_63));
#endif
_currn->_prod = RULErule_63;
_currn->_desc1 = (_TSPG2) MkG2 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_63: root of subtree no. 1 can not be made a G2 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_63;
return ( (NODEPTR) _currn);
}/* Mkrule_63 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_62 (POSITION *_coordref)
#else
NODEPTR Mkrule_62 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_62 _currn;
#ifdef __cplusplus
_currn = new _TPrule_62;
#else
_currn = (_TPPrule_62) TreeNodeAlloc (sizeof (struct _TPrule_62));
#endif
_currn->_prod = RULErule_62;
_SETCOORD(_currn)
_TERMACT_rule_62;
return ( (NODEPTR) _currn);
}/* Mkrule_62 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_61 (POSITION *_coordref)
#else
NODEPTR Mkrule_61 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_61 _currn;
#ifdef __cplusplus
_currn = new _TPrule_61;
#else
_currn = (_TPPrule_61) TreeNodeAlloc (sizeof (struct _TPrule_61));
#endif
_currn->_prod = RULErule_61;
_SETCOORD(_currn)
_TERMACT_rule_61;
return ( (NODEPTR) _currn);
}/* Mkrule_61 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_60 (POSITION *_coordref)
#else
NODEPTR Mkrule_60 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_60 _currn;
#ifdef __cplusplus
_currn = new _TPrule_60;
#else
_currn = (_TPPrule_60) TreeNodeAlloc (sizeof (struct _TPrule_60));
#endif
_currn->_prod = RULErule_60;
_SETCOORD(_currn)
_TERMACT_rule_60;
return ( (NODEPTR) _currn);
}/* Mkrule_60 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_59 (POSITION *_coordref)
#else
NODEPTR Mkrule_59 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_59 _currn;
#ifdef __cplusplus
_currn = new _TPrule_59;
#else
_currn = (_TPPrule_59) TreeNodeAlloc (sizeof (struct _TPrule_59));
#endif
_currn->_prod = RULErule_59;
_SETCOORD(_currn)
_TERMACT_rule_59;
return ( (NODEPTR) _currn);
}/* Mkrule_59 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_58 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_58 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_58 _currn;
#ifdef __cplusplus
_currn = new _TPrule_58;
#else
_currn = (_TPPrule_58) TreeNodeAlloc (sizeof (struct _TPrule_58));
#endif
_currn->_prod = RULErule_58;
_currn->_desc1 = (_TSPG3) MkG3 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_58: root of subtree no. 1 can not be made a G3 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_58;
return ( (NODEPTR) _currn);
}/* Mkrule_58 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_57 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_57 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_57 _currn;
#ifdef __cplusplus
_currn = new _TPrule_57;
#else
_currn = (_TPPrule_57) TreeNodeAlloc (sizeof (struct _TPrule_57));
#endif
_currn->_prod = RULErule_57;
_currn->_desc1 = (_TSPpgs_root) Mkpgs_root (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_57: root of subtree no. 1 can not be made a pgs_root node ", 0, _coordref);
_currn->_desc2 = (_TSPactpts_root) Mkactpts_root (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_57: root of subtree no. 2 can not be made a actpts_root node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_57;
return ( (NODEPTR) _currn);
}/* Mkrule_57 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_56 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3, NODEPTR _desc4)
#else
NODEPTR Mkrule_56 (_coordref,_desc1,_desc2,_desc3,_desc4)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
	NODEPTR _desc4;
#endif
{	_TPPrule_56 _currn;
#ifdef __cplusplus
_currn = new _TPrule_56;
#else
_currn = (_TPPrule_56) TreeNodeAlloc (sizeof (struct _TPrule_56));
#endif
_currn->_prod = RULErule_56;
_currn->_desc1 = (_TSPcode_part) Mkcode_part (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_56: root of subtree no. 1 can not be made a code_part node ", 0, _coordref);
_currn->_desc2 = (_TSPstop_part) Mkstop_part (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_56: root of subtree no. 2 can not be made a stop_part node ", 0, _coordref);
_currn->_desc3 = (_TSPerr_part) Mkerr_part (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_56: root of subtree no. 3 can not be made a err_part node ", 0, _coordref);
_currn->_desc4 = (_TSPgrammar_part) Mkgrammar_part (_coordref, _desc4);	
if (((NODEPTR)_currn->_desc4) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_56: root of subtree no. 4 can not be made a grammar_part node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_56;
return ( (NODEPTR) _currn);
}/* Mkrule_56 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_55 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_55 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_55 _currn;
#ifdef __cplusplus
_currn = new _TPrule_55;
#else
_currn = (_TPPrule_55) TreeNodeAlloc (sizeof (struct _TPrule_55));
#endif
_currn->_prod = RULErule_55;
_SETCOORD(_currn)
_TERMACT_rule_55;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "NAME", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_55 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_54 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_54 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_54 _currn;
#ifdef __cplusplus
_currn = new _TPrule_54;
#else
_currn = (_TPPrule_54) TreeNodeAlloc (sizeof (struct _TPrule_54));
#endif
_currn->_prod = RULErule_54;
_SETCOORD(_currn)
_TERMACT_rule_54;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "NAME", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_54 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_53 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_53 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_53 _currn;
#ifdef __cplusplus
_currn = new _TPrule_53;
#else
_currn = (_TPPrule_53) TreeNodeAlloc (sizeof (struct _TPrule_53));
#endif
_currn->_prod = RULErule_53;
_SETCOORD(_currn)
_TERMACT_rule_53;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "STRING", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_53 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_52 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_52 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_52 _currn;
#ifdef __cplusplus
_currn = new _TPrule_52;
#else
_currn = (_TPPrule_52) TreeNodeAlloc (sizeof (struct _TPrule_52));
#endif
_currn->_prod = RULErule_52;
_currn->_desc1 = (_TSPstart) Mkstart (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_52: root of subtree no. 1 can not be made a start node ", 0, _coordref);
_currn->_desc2 = (_TSPrule_list) Mkrule_list (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_52: root of subtree no. 2 can not be made a rule_list node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_52;
return ( (NODEPTR) _currn);
}/* Mkrule_52 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_51 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_51 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_51 _currn;
#ifdef __cplusplus
_currn = new _TPrule_51;
#else
_currn = (_TPPrule_51) TreeNodeAlloc (sizeof (struct _TPrule_51));
#endif
_currn->_prod = RULErule_51;
_currn->_desc1 = (_TSPG4) MkG4 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_51: root of subtree no. 1 can not be made a G4 node ", 0, _coordref);
_currn->_desc2 = (_TSPmodification) Mkmodification (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_51: root of subtree no. 2 can not be made a modification node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_51;
return ( (NODEPTR) _currn);
}/* Mkrule_51 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_50 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_50 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_50 _currn;
#ifdef __cplusplus
_currn = new _TPrule_50;
#else
_currn = (_TPPrule_50) TreeNodeAlloc (sizeof (struct _TPrule_50));
#endif
_currn->_prod = RULErule_50;
_currn->_desc1 = (_TSPG4) MkG4 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_50: root of subtree no. 1 can not be made a G4 node ", 0, _coordref);
_currn->_desc2 = (_TSPelem) Mkelem (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_50: root of subtree no. 2 can not be made a elem node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_50;
return ( (NODEPTR) _currn);
}/* Mkrule_50 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_49 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_49 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_49 _currn;
#ifdef __cplusplus
_currn = new _TPrule_49;
#else
_currn = (_TPPrule_49) TreeNodeAlloc (sizeof (struct _TPrule_49));
#endif
_currn->_prod = RULErule_49;
_currn->_desc1 = (_TSPG4) MkG4 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_49: root of subtree no. 1 can not be made a G4 node ", 0, _coordref);
_currn->_desc2 = (_TSPconnection) Mkconnection (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_49: root of subtree no. 2 can not be made a connection node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_49;
return ( (NODEPTR) _currn);
}/* Mkrule_49 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_48 (POSITION *_coordref)
#else
NODEPTR Mkrule_48 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_48 _currn;
#ifdef __cplusplus
_currn = new _TPrule_48;
#else
_currn = (_TPPrule_48) TreeNodeAlloc (sizeof (struct _TPrule_48));
#endif
_currn->_prod = RULErule_48;
_SETCOORD(_currn)
_TERMACT_rule_48;
return ( (NODEPTR) _currn);
}/* Mkrule_48 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_47 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_47 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_47 _currn;
#ifdef __cplusplus
_currn = new _TPrule_47;
#else
_currn = (_TPPrule_47) TreeNodeAlloc (sizeof (struct _TPrule_47));
#endif
_currn->_prod = RULErule_47;
_currn->_desc1 = (_TSPG3) MkG3 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_47: root of subtree no. 1 can not be made a G3 node ", 0, _coordref);
_currn->_desc2 = (_TSPrule) Mkrule (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_47: root of subtree no. 2 can not be made a rule node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_47;
return ( (NODEPTR) _currn);
}/* Mkrule_47 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_46 (POSITION *_coordref)
#else
NODEPTR Mkrule_46 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_46 _currn;
#ifdef __cplusplus
_currn = new _TPrule_46;
#else
_currn = (_TPPrule_46) TreeNodeAlloc (sizeof (struct _TPrule_46));
#endif
_currn->_prod = RULErule_46;
_SETCOORD(_currn)
_TERMACT_rule_46;
return ( (NODEPTR) _currn);
}/* Mkrule_46 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_45 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_45 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_45 _currn;
#ifdef __cplusplus
_currn = new _TPrule_45;
#else
_currn = (_TPPrule_45) TreeNodeAlloc (sizeof (struct _TPrule_45));
#endif
_currn->_prod = RULErule_45;
_currn->_desc1 = (_TSPG2) MkG2 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_45: root of subtree no. 1 can not be made a G2 node ", 0, _coordref);
_currn->_desc2 = (_TSPterm_def) Mkterm_def (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_45: root of subtree no. 2 can not be made a term_def node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_45;
return ( (NODEPTR) _currn);
}/* Mkrule_45 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_44 (POSITION *_coordref)
#else
NODEPTR Mkrule_44 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_44 _currn;
#ifdef __cplusplus
_currn = new _TPrule_44;
#else
_currn = (_TPPrule_44) TreeNodeAlloc (sizeof (struct _TPrule_44));
#endif
_currn->_prod = RULErule_44;
_SETCOORD(_currn)
_TERMACT_rule_44;
return ( (NODEPTR) _currn);
}/* Mkrule_44 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_43 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_43 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_43 _currn;
#ifdef __cplusplus
_currn = new _TPrule_43;
#else
_currn = (_TPPrule_43) TreeNodeAlloc (sizeof (struct _TPrule_43));
#endif
_currn->_prod = RULErule_43;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_43: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_currn->_desc2 = (_TSPcode_def) Mkcode_def (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_43: root of subtree no. 2 can not be made a code_def node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_43;
return ( (NODEPTR) _currn);
}/* Mkrule_43 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_42 (POSITION *_coordref)
#else
NODEPTR Mkrule_42 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_42 _currn;
#ifdef __cplusplus
_currn = new _TPrule_42;
#else
_currn = (_TPPrule_42) TreeNodeAlloc (sizeof (struct _TPrule_42));
#endif
_currn->_prod = RULErule_42;
_SETCOORD(_currn)
_TERMACT_rule_42;
return ( (NODEPTR) _currn);
}/* Mkrule_42 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_41 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_41 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_41 _currn;
#ifdef __cplusplus
_currn = new _TPrule_41;
#else
_currn = (_TPPrule_41) TreeNodeAlloc (sizeof (struct _TPrule_41));
#endif
_currn->_prod = RULErule_41;
_currn->_desc1 = (_TSPsepa_part) Mksepa_part (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_41: root of subtree no. 1 can not be made a sepa_part node ", 0, _coordref);
_currn->_desc2 = (_TSPbracket_part) Mkbracket_part (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_41: root of subtree no. 2 can not be made a bracket_part node ", 0, _coordref);
_currn->_desc3 = (_TSPskip_part) Mkskip_part (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_41: root of subtree no. 3 can not be made a skip_part node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_41;
return ( (NODEPTR) _currn);
}/* Mkrule_41 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_40 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_40 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_40 _currn;
#ifdef __cplusplus
_currn = new _TPrule_40;
#else
_currn = (_TPPrule_40) TreeNodeAlloc (sizeof (struct _TPrule_40));
#endif
_currn->_prod = RULErule_40;
_currn->_desc1 = (_TSPrhs) Mkrhs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_40: root of subtree no. 1 can not be made a rhs node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_40;
return ( (NODEPTR) _currn);
}/* Mkrule_40 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_39 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_39 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_39 _currn;
#ifdef __cplusplus
_currn = new _TPrule_39;
#else
_currn = (_TPPrule_39) TreeNodeAlloc (sizeof (struct _TPrule_39));
#endif
_currn->_prod = RULErule_39;
_currn->_desc1 = (_TSPG4) MkG4 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_39: root of subtree no. 1 can not be made a G4 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_39;
return ( (NODEPTR) _currn);
}/* Mkrule_39 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_38 (POSITION *_coordref)
#else
NODEPTR Mkrule_38 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_38 _currn;
#ifdef __cplusplus
_currn = new _TPrule_38;
#else
_currn = (_TPPrule_38) TreeNodeAlloc (sizeof (struct _TPrule_38));
#endif
_currn->_prod = RULErule_38;
_SETCOORD(_currn)
_TERMACT_rule_38;
return ( (NODEPTR) _currn);
}/* Mkrule_38 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_37 (POSITION *_coordref)
#else
NODEPTR Mkrule_37 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_37 _currn;
#ifdef __cplusplus
_currn = new _TPrule_37;
#else
_currn = (_TPPrule_37) TreeNodeAlloc (sizeof (struct _TPrule_37));
#endif
_currn->_prod = RULErule_37;
_SETCOORD(_currn)
_TERMACT_rule_37;
return ( (NODEPTR) _currn);
}/* Mkrule_37 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_36 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_36 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_36 _currn;
#ifdef __cplusplus
_currn = new _TPrule_36;
#else
_currn = (_TPPrule_36) TreeNodeAlloc (sizeof (struct _TPrule_36));
#endif
_currn->_prod = RULErule_36;
_SETCOORD(_currn)
_TERMACT_rule_36;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "STRING", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_36 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_35 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_35 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_35 _currn;
#ifdef __cplusplus
_currn = new _TPrule_35;
#else
_currn = (_TPPrule_35) TreeNodeAlloc (sizeof (struct _TPrule_35));
#endif
_currn->_prod = RULErule_35;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_35: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_35;
return ( (NODEPTR) _currn);
}/* Mkrule_35 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_34 (POSITION *_coordref)
#else
NODEPTR Mkrule_34 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_34 _currn;
#ifdef __cplusplus
_currn = new _TPrule_34;
#else
_currn = (_TPPrule_34) TreeNodeAlloc (sizeof (struct _TPrule_34));
#endif
_currn->_prod = RULErule_34;
_SETCOORD(_currn)
_TERMACT_rule_34;
return ( (NODEPTR) _currn);
}/* Mkrule_34 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_33 (POSITION *_coordref)
#else
NODEPTR Mkrule_33 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_33 _currn;
#ifdef __cplusplus
_currn = new _TPrule_33;
#else
_currn = (_TPPrule_33) TreeNodeAlloc (sizeof (struct _TPrule_33));
#endif
_currn->_prod = RULErule_33;
_SETCOORD(_currn)
_TERMACT_rule_33;
return ( (NODEPTR) _currn);
}/* Mkrule_33 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_32 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_32 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_32 _currn;
#ifdef __cplusplus
_currn = new _TPrule_32;
#else
_currn = (_TPPrule_32) TreeNodeAlloc (sizeof (struct _TPrule_32));
#endif
_currn->_prod = RULErule_32;
_currn->_desc1 = (_TSPelem_list) Mkelem_list (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_32: root of subtree no. 1 can not be made a elem_list node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_32;
return ( (NODEPTR) _currn);
}/* Mkrule_32 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_31 (POSITION *_coordref)
#else
NODEPTR Mkrule_31 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_31 _currn;
#ifdef __cplusplus
_currn = new _TPrule_31;
#else
_currn = (_TPPrule_31) TreeNodeAlloc (sizeof (struct _TPrule_31));
#endif
_currn->_prod = RULErule_31;
_SETCOORD(_currn)
_TERMACT_rule_31;
return ( (NODEPTR) _currn);
}/* Mkrule_31 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRmod_op1 (POSITION *_coordref)
#else
NODEPTR MkRmod_op1 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPRmod_op1 _currn;
#ifdef __cplusplus
_currn = new _TPRmod_op1;
#else
_currn = (_TPPRmod_op1) TreeNodeAlloc (sizeof (struct _TPRmod_op1));
#endif
_currn->_prod = RULERmod_op1;
_SETCOORD(_currn)
_TERMACT_Rmod_op1;
return ( (NODEPTR) _currn);
}/* MkRmod_op1 */
