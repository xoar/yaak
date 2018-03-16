
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
NODEPTR MkAtomic (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAtomic (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAtomic)) return (_currn);
if (IsSymb (_currn, SYMBSymbol)) return (Mkrule_6(_coordref, _currn));
return(NULLNODEPTR);
}/* MkAtomic */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSymbol (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSymbol (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSymbol)) return (_currn);
return(NULLNODEPTR);
}/* MkSymbol */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkExpression (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkExpression (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBExpression)) return (_currn);
if (IsSymb (_currn, SYMBSymbol)) return (Mkrule_7(_coordref, _currn));
if (IsSymb (_currn, SYMBAtomic)) return (Mkrule_7(_coordref, _currn));
return(NULLNODEPTR);
}/* MkExpression */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRule (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRule (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRule)) return (_currn);
return(NULLNODEPTR);
}/* MkRule */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkEBNF (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkEBNF (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBEBNF)) return (_currn);
return(NULLNODEPTR);
}/* MkEBNF */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_1 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_1 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_1 _currn;
#ifdef __cplusplus
_currn = new _TPrule_1;
#else
_currn = (_TPPrule_1) TreeNodeAlloc (sizeof (struct _TPrule_1));
#endif
_currn->_prod = RULErule_1;
_SETCOORD(_currn)
_TERMACT_rule_1;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Literal", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_2 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_2 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_2 _currn;
#ifdef __cplusplus
_currn = new _TPrule_2;
#else
_currn = (_TPPrule_2) TreeNodeAlloc (sizeof (struct _TPrule_2));
#endif
_currn->_prod = RULErule_2;
_SETCOORD(_currn)
_TERMACT_rule_2;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

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
_currn->_desc1 = (_TSPSymbol) MkSymbol (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_3: root of subtree no. 1 can not be made a Symbol node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_3;
return ( (NODEPTR) _currn);
}/* Mkrule_3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_4 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_4 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_4 _currn;
#ifdef __cplusplus
_currn = new _TPrule_4;
#else
_currn = (_TPPrule_4) TreeNodeAlloc (sizeof (struct _TPrule_4));
#endif
_currn->_prod = RULErule_4;
_currn->_desc1 = (_TSPSymbol) MkSymbol (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_4: root of subtree no. 1 can not be made a Symbol node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_4;
return ( (NODEPTR) _currn);
}/* Mkrule_4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_5 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_5 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_5 _currn;
#ifdef __cplusplus
_currn = new _TPrule_5;
#else
_currn = (_TPPrule_5) TreeNodeAlloc (sizeof (struct _TPrule_5));
#endif
_currn->_prod = RULErule_5;
_currn->_desc1 = (_TSPSymbol) MkSymbol (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_5: root of subtree no. 1 can not be made a Symbol node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_5;
return ( (NODEPTR) _currn);
}/* Mkrule_5 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_6 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_6 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_6 _currn;
#ifdef __cplusplus
_currn = new _TPrule_6;
#else
_currn = (_TPPrule_6) TreeNodeAlloc (sizeof (struct _TPrule_6));
#endif
_currn->_prod = RULErule_6;
_currn->_desc1 = (_TSPSymbol) MkSymbol (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_6: root of subtree no. 1 can not be made a Symbol node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_6;
return ( (NODEPTR) _currn);
}/* Mkrule_6 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_7 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_7 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_7 _currn;
#ifdef __cplusplus
_currn = new _TPrule_7;
#else
_currn = (_TPPrule_7) TreeNodeAlloc (sizeof (struct _TPrule_7));
#endif
_currn->_prod = RULErule_7;
_currn->_desc1 = (_TSPAtomic) MkAtomic (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_7: root of subtree no. 1 can not be made a Atomic node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_7;
return ( (NODEPTR) _currn);
}/* Mkrule_7 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_8 (POSITION *_coordref)
#else
NODEPTR Mkrule_8 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_8 _currn;
#ifdef __cplusplus
_currn = new _TPrule_8;
#else
_currn = (_TPPrule_8) TreeNodeAlloc (sizeof (struct _TPrule_8));
#endif
_currn->_prod = RULErule_8;
_SETCOORD(_currn)
_TERMACT_rule_8;
return ( (NODEPTR) _currn);
}/* Mkrule_8 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_9 (POSITION *_coordref, NODEPTR _desc1, int _TERM1, NODEPTR _desc2)
#else
NODEPTR Mkrule_9 (_coordref,_desc1, _TERM1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	int _TERM1;
	NODEPTR _desc2;
#endif
{	_TPPrule_9 _currn;
#ifdef __cplusplus
_currn = new _TPrule_9;
#else
_currn = (_TPPrule_9) TreeNodeAlloc (sizeof (struct _TPrule_9));
#endif
_currn->_prod = RULErule_9;
_currn->_desc1 = (_TSPExpression) MkExpression (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 1 can not be made a Expression node ", 0, _coordref);
_currn->_desc2 = (_TSPSymbol) MkSymbol (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 2 can not be made a Symbol node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_9;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Sep", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_9 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_10 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_10 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_10 _currn;
#ifdef __cplusplus
_currn = new _TPrule_10;
#else
_currn = (_TPPrule_10) TreeNodeAlloc (sizeof (struct _TPrule_10));
#endif
_currn->_prod = RULErule_10;
_currn->_desc1 = (_TSPExpression) MkExpression (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 1 can not be made a Expression node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_10;
return ( (NODEPTR) _currn);
}/* Mkrule_10 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_11 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_11 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_11 _currn;
#ifdef __cplusplus
_currn = new _TPrule_11;
#else
_currn = (_TPPrule_11) TreeNodeAlloc (sizeof (struct _TPrule_11));
#endif
_currn->_prod = RULErule_11;
_currn->_desc1 = (_TSPExpression) MkExpression (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 1 can not be made a Expression node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_11;
return ( (NODEPTR) _currn);
}/* Mkrule_11 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_12 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_12 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_12 _currn;
#ifdef __cplusplus
_currn = new _TPrule_12;
#else
_currn = (_TPPrule_12) TreeNodeAlloc (sizeof (struct _TPrule_12));
#endif
_currn->_prod = RULErule_12;
_currn->_desc1 = (_TSPExpression) MkExpression (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_12: root of subtree no. 1 can not be made a Expression node ", 0, _coordref);
_currn->_desc2 = (_TSPExpression) MkExpression (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_12: root of subtree no. 2 can not be made a Expression node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_12;
return ( (NODEPTR) _currn);
}/* Mkrule_12 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_13 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_13 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_13 _currn;
#ifdef __cplusplus
_currn = new _TPrule_13;
#else
_currn = (_TPPrule_13) TreeNodeAlloc (sizeof (struct _TPrule_13));
#endif
_currn->_prod = RULErule_13;
_currn->_desc1 = (_TSPExpression) MkExpression (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_13: root of subtree no. 1 can not be made a Expression node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_13;
return ( (NODEPTR) _currn);
}/* Mkrule_13 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_14 (POSITION *_coordref, NODEPTR _desc1, int _TERM1, NODEPTR _desc2)
#else
NODEPTR Mkrule_14 (_coordref,_desc1, _TERM1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	int _TERM1;
	NODEPTR _desc2;
#endif
{	_TPPrule_14 _currn;
#ifdef __cplusplus
_currn = new _TPrule_14;
#else
_currn = (_TPPrule_14) TreeNodeAlloc (sizeof (struct _TPrule_14));
#endif
_currn->_prod = RULErule_14;
_currn->_desc1 = (_TSPExpression) MkExpression (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_14: root of subtree no. 1 can not be made a Expression node ", 0, _coordref);
_currn->_desc2 = (_TSPExpression) MkExpression (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_14: root of subtree no. 2 can not be made a Expression node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_14;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Or", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_14 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_15 (POSITION *_coordref, int _TERM1, int _TERM2, NODEPTR _desc1)
#else
NODEPTR Mkrule_15 (_coordref, _TERM1, _TERM2,_desc1)
	POSITION *_coordref;
	int _TERM1;
	int _TERM2;
	NODEPTR _desc1;
#endif
{	_TPPrule_15 _currn;
#ifdef __cplusplus
_currn = new _TPrule_15;
#else
_currn = (_TPPrule_15) TreeNodeAlloc (sizeof (struct _TPrule_15));
#endif
_currn->_prod = RULErule_15;
_currn->_desc1 = (_TSPExpression) MkExpression (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_15: root of subtree no. 1 can not be made a Expression node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_15;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Is", _TERM2);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_15 */

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkRulerule_16 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkRulerule_16 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_Rulerule_16 _new;
#ifdef __cplusplus
	_new = new _TPLST_Rulerule_16;
#else
	_new = (_TPPLST_Rulerule_16) TreeNodeAlloc (sizeof (struct _TPLST_Rulerule_16));
#endif
	_new->_prod = RULELST_Rulerule_16;
	_new->_desc1 = (_TSPRule)elem;
	_new->_desc2 = (_TSPLST_EBNF)_new;
	{_TPPLST_Rulerule_16 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_Rulerule_16;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _Elemrule_16 (POSITION *_coordref, NODEPTR t)
#else
static NODEPTR _Elemrule_16 (_coordref, t)
	POSITION *_coordref; NODEPTR t;
#endif
/* coerces t to a list element and returns a single circular list */
{	NODEPTR elem;
	/* check first without then with coercion: */
	if (IsSymb (t, SYMBRule)) 
		return _MkRulerule_16 (_coordref, MkRule (_coordref, t));
	message (DEADLY, "a rule_16 list element node can not be generated ",
		0, _coordref);
	return t; /* never reached */
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mk2rule_16 (POSITION *_coordref, NODEPTR l, NODEPTR r)
#else
NODEPTR Mk2rule_16 (_coordref, l, r) POSITION *_coordref; NODEPTR l, r;
#endif
/* make a list of l and r, which may be null, elements, or lists */
{	NODEPTR last;
if (l == NULLNODEPTR) return r;
if (r == NULLNODEPTR) return l;
/* ensure l and r to be lists: */
if (LHSMAP[l->_prod] != SYMBLST_EBNF)
	l =_Elemrule_16 (_coordref, l);
if (LHSMAP[r->_prod] != SYMBLST_EBNF)
	r = _Elemrule_16 (_coordref, r);
/* concatenate two lists: */
last = ((NODEPTR)((_TPPLST_0rule_16)r)->_desc2);
((_TPPLST_0rule_16)r)->_desc2 = ((_TPPLST_0rule_16)l)->_desc2;
((_TPPLST_0rule_16)l)->_desc2 = last;
return l;
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_16 (POSITION *_coordref, NODEPTR t)
#else
NODEPTR Mkrule_16 (_coordref, t) POSITION *_coordref; NODEPTR t;
#endif
{	NODEPTR _currn; _TPPrule_16 root;
	_TPPLST_0rule_16 list, remain, p;
/* argument t may be empty, a list element, or a list: */
if (t == NULLNODEPTR)
	remain = (_TPPLST_0rule_16)NULLNODEPTR;
else {	if (LHSMAP[t->_prod] != SYMBLST_EBNF)
		t = _Elemrule_16 (_coordref, t);
	remain = (_TPPLST_0rule_16)(((_TPPLST_0rule_16) t)->_desc2);
	((_TPPLST_0rule_16) t)->_desc2 = NULLNODEPTR;
}
/* remain is a possibly empty list in reverse order */
/* finalize the list by an empty context: */
#ifdef __cplusplus
list = new _TPLST_0rule_16;
#else
list = (_TPPLST_0rule_16) TreeNodeAlloc (sizeof (struct _TPLST_0rule_16));
#endif
list->_prod = RULELST_0rule_16;
list->_desc1 = NULLNODEPTR;
list->_desc2 = NULLNODEPTR;
_SETCOORD(list)
_currn = (NODEPTR)list;
/* reverse the list and visit its nodes: */
while (remain) {
	p = (_TPPLST_0rule_16)(remain->_desc2);
	remain->_desc2 = (NODEPTR)list;
	list = remain;
	remain = p;
	_currn = (NODEPTR)list;
	/*if (_currn->_prod == RULELST_Rulerule_16)
	{_TPPLST_Rulerule_16 _currn = _currn;
	 _TERMACT_LST_Rulerule_16;
	} this code has been moved to _Elemrule_16*/
}
/* make root node and visit it: */
#ifdef __cplusplus
root = new _TPrule_16;
#else
root = (_TPPrule_16) TreeNodeAlloc (sizeof (struct _TPrule_16));
#endif
root->_prod = RULErule_16;
root->_desc1 = (_TSPLST_EBNF)list;
{ _TPPrule_16 _currn = root;
  _SETCOORD(_currn)
  _TERMACT_rule_16;
}
_currn = (NODEPTR)root;
return (NODEPTR)_currn;
}
