
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
NODEPTR MknonLitDesc (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MknonLitDesc (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBnonLitDesc)) return (_currn);
if (IsSymb (_currn, SYMBrest)) return (Mkrule_8(_coordref, _currn));
return(NULLNODEPTR);
}/* MknonLitDesc */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG1 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG1 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG1)) return (_currn);
if (IsSymb (_currn, SYMBrest)) return (Mkrule_6(_coordref, _currn));
if (IsSymb (_currn, SYMBnonLitDesc)) return (Mkrule_6(_coordref, _currn));
return(NULLNODEPTR);
}/* MkG1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkspec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkspec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBspec)) return (_currn);
if (IsSymb (_currn, SYMBrest)) return (Mkrule_12(_coordref, _currn));
if (IsSymb (_currn, SYMBnonLitDesc)) return (Mkrule_12(_coordref, _currn));
if (IsSymb (_currn, SYMBG1)) return (Mkrule_12(_coordref, _currn));
return(NULLNODEPTR);
}/* Mkspec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MklibrRef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MklibrRef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBlibrRef)) return (_currn);
return(NULLNODEPTR);
}/* MklibrRef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkoptProcessor (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkoptProcessor (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBoptProcessor)) return (_currn);
return(NULLNODEPTR);
}/* MkoptProcessor */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkoptAuxScanner (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkoptAuxScanner (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBoptAuxScanner)) return (_currn);
return(NULLNODEPTR);
}/* MkoptAuxScanner */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrest (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkrest (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBrest)) return (_currn);
return(NULLNODEPTR);
}/* Mkrest */

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
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
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
NODEPTR Mkrule_3 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_3 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_3 _currn;
#ifdef __cplusplus
_currn = new _TPrule_3;
#else
_currn = (_TPPrule_3) TreeNodeAlloc (sizeof (struct _TPrule_3));
#endif
_currn->_prod = RULErule_3;
_currn->_desc1 = (_TSPlibrRef) MklibrRef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_3: root of subtree no. 1 can not be made a librRef node ", 0, _coordref);
_currn->_desc2 = (_TSPoptAuxScanner) MkoptAuxScanner (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_3: root of subtree no. 2 can not be made a optAuxScanner node ", 0, _coordref);
_currn->_desc3 = (_TSPoptProcessor) MkoptProcessor (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_3: root of subtree no. 3 can not be made a optProcessor node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_3;
return ( (NODEPTR) _currn);
}/* Mkrule_3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_4 (POSITION *_coordref, int _TERM1, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_4 (_coordref, _TERM1,_desc1,_desc2)
	POSITION *_coordref;
	int _TERM1;
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
_currn->_desc1 = (_TSPoptAuxScanner) MkoptAuxScanner (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_4: root of subtree no. 1 can not be made a optAuxScanner node ", 0, _coordref);
_currn->_desc2 = (_TSPoptProcessor) MkoptProcessor (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_4: root of subtree no. 2 can not be made a optProcessor node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_4;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "RegularExpr", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_12 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_12 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_12 _currn;
#ifdef __cplusplus
_currn = new _TPrule_12;
#else
_currn = (_TPPrule_12) TreeNodeAlloc (sizeof (struct _TPrule_12));
#endif
_currn->_prod = RULErule_12;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_12: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_12;
return ( (NODEPTR) _currn);
}/* Mkrule_12 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_11 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_11 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_11 _currn;
#ifdef __cplusplus
_currn = new _TPrule_11;
#else
_currn = (_TPPrule_11) TreeNodeAlloc (sizeof (struct _TPrule_11));
#endif
_currn->_prod = RULErule_11;
_SETCOORD(_currn)
_TERMACT_rule_11;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_11 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_10 (POSITION *_coordref)
#else
NODEPTR Mkrule_10 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_10 _currn;
#ifdef __cplusplus
_currn = new _TPrule_10;
#else
_currn = (_TPPrule_10) TreeNodeAlloc (sizeof (struct _TPrule_10));
#endif
_currn->_prod = RULErule_10;
_SETCOORD(_currn)
_TERMACT_rule_10;
return ( (NODEPTR) _currn);
}/* Mkrule_10 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_9 (POSITION *_coordref)
#else
NODEPTR Mkrule_9 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_9 _currn;
#ifdef __cplusplus
_currn = new _TPrule_9;
#else
_currn = (_TPPrule_9) TreeNodeAlloc (sizeof (struct _TPrule_9));
#endif
_currn->_prod = RULErule_9;
_SETCOORD(_currn)
_TERMACT_rule_9;
return ( (NODEPTR) _currn);
}/* Mkrule_9 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_8 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_8 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_8 _currn;
#ifdef __cplusplus
_currn = new _TPrule_8;
#else
_currn = (_TPPrule_8) TreeNodeAlloc (sizeof (struct _TPrule_8));
#endif
_currn->_prod = RULErule_8;
_currn->_desc1 = (_TSPrest) Mkrest (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_8: root of subtree no. 1 can not be made a rest node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_8;
return ( (NODEPTR) _currn);
}/* Mkrule_8 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_7 (POSITION *_coordref, int _TERM1, NODEPTR _desc1)
#else
NODEPTR Mkrule_7 (_coordref, _TERM1,_desc1)
	POSITION *_coordref;
	int _TERM1;
	NODEPTR _desc1;
#endif
{	_TPPrule_7 _currn;
#ifdef __cplusplus
_currn = new _TPrule_7;
#else
_currn = (_TPPrule_7) TreeNodeAlloc (sizeof (struct _TPrule_7));
#endif
_currn->_prod = RULErule_7;
_currn->_desc1 = (_TSPrest) Mkrest (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_7: root of subtree no. 1 can not be made a rest node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_7;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_7 */

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
_currn->_desc1 = (_TSPnonLitDesc) MknonLitDesc (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_6: root of subtree no. 1 can not be made a nonLitDesc node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_6;
return ( (NODEPTR) _currn);
}/* Mkrule_6 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_5 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_5 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_5 _currn;
#ifdef __cplusplus
_currn = new _TPrule_5;
#else
_currn = (_TPPrule_5) TreeNodeAlloc (sizeof (struct _TPrule_5));
#endif
_currn->_prod = RULErule_5;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_5: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_currn->_desc2 = (_TSPnonLitDesc) MknonLitDesc (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_5: root of subtree no. 2 can not be made a nonLitDesc node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_5;
return ( (NODEPTR) _currn);
}/* Mkrule_5 */
