
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
NODEPTR MkG3 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG3 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG3)) return (_currn);
if (IsSymb (_currn, SYMBFunctionCall)) return (Mkrule_25(_coordref, _currn));
if (IsSymb (_currn, SYMBInsertion)) return (Mkrule_25(_coordref, _currn));
if (IsSymb (_currn, SYMBCStringNode)) return (Mkrule_25(_coordref, _currn));
if (IsSymb (_currn, SYMBItem)) return (Mkrule_25(_coordref, _currn));
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
NODEPTR MkArgument (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkArgument (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBArgument)) return (_currn);
if (IsSymb (_currn, SYMBInsertion)) return (Mkrule_16(_coordref, _currn));
return(NULLNODEPTR);
}/* MkArgument */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOptional (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOptional (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOptional)) return (_currn);
return(NULLNODEPTR);
}/* MkOptional */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkItem (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkItem (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBItem)) return (_currn);
if (IsSymb (_currn, SYMBFunctionCall)) return (Mkrule_28(_coordref, _currn));
if (IsSymb (_currn, SYMBInsertion)) return (Mkrule_29(_coordref, _currn));
if (IsSymb (_currn, SYMBCStringNode)) return (Mkrule_9(_coordref, _currn));
return(NULLNODEPTR);
}/* MkItem */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkCStringNode (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkCStringNode (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBCStringNode)) return (_currn);
return(NULLNODEPTR);
}/* MkCStringNode */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPTGSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPTGSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPTGSpec)) return (_currn);
if (IsSymb (_currn, SYMBG1)) return (Mkrule_33(_coordref, _currn));
return(NULLNODEPTR);
}/* MkPTGSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPatternName (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPatternName (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPatternName)) return (_currn);
return(NULLNODEPTR);
}/* MkPatternName */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkArguments (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkArguments (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBArguments)) return (_currn);
if (IsSymb (_currn, SYMBG4)) return (Mkrule_17(_coordref, _currn));
return(NULLNODEPTR);
}/* MkArguments */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkFunctionName (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkFunctionName (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBFunctionName)) return (_currn);
return(NULLNODEPTR);
}/* MkFunctionName */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkFunctionCall (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkFunctionCall (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBFunctionCall)) return (_currn);
return(NULLNODEPTR);
}/* MkFunctionCall */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPatternBody (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPatternBody (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPatternBody)) return (_currn);
if (IsSymb (_currn, SYMBG2)) return (Mkrule_31(_coordref, _currn));
return(NULLNODEPTR);
}/* MkPatternBody */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPatternSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPatternSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPatternSpec)) return (_currn);
return(NULLNODEPTR);
}/* MkPatternSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkType (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkType (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBType)) return (_currn);
return(NULLNODEPTR);
}/* MkType */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkIndex (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkIndex (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBIndex)) return (_currn);
return(NULLNODEPTR);
}/* MkIndex */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkInsertion (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkInsertion (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBInsertion)) return (_currn);
return(NULLNODEPTR);
}/* MkInsertion */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_1 (POSITION *_coordref)
#else
NODEPTR Mkrule_1 (_coordref)
	POSITION *_coordref;
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
return ( (NODEPTR) _currn);
}/* Mkrule_1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_2 (POSITION *_coordref)
#else
NODEPTR Mkrule_2 (_coordref)
	POSITION *_coordref;
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
return ( (NODEPTR) _currn);
}/* Mkrule_2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_3 (POSITION *_coordref)
#else
NODEPTR Mkrule_3 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_3 _currn;
#ifdef __cplusplus
_currn = new _TPrule_3;
#else
_currn = (_TPPrule_3) TreeNodeAlloc (sizeof (struct _TPrule_3));
#endif
_currn->_prod = RULErule_3;
_SETCOORD(_currn)
_TERMACT_rule_3;
return ( (NODEPTR) _currn);
}/* Mkrule_3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_4 (POSITION *_coordref)
#else
NODEPTR Mkrule_4 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_4 _currn;
#ifdef __cplusplus
_currn = new _TPrule_4;
#else
_currn = (_TPPrule_4) TreeNodeAlloc (sizeof (struct _TPrule_4));
#endif
_currn->_prod = RULErule_4;
_SETCOORD(_currn)
_TERMACT_rule_4;
return ( (NODEPTR) _currn);
}/* Mkrule_4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_5 (POSITION *_coordref)
#else
NODEPTR Mkrule_5 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_5 _currn;
#ifdef __cplusplus
_currn = new _TPrule_5;
#else
_currn = (_TPPrule_5) TreeNodeAlloc (sizeof (struct _TPrule_5));
#endif
_currn->_prod = RULErule_5;
_SETCOORD(_currn)
_TERMACT_rule_5;
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
NODEPTR Mkrule_8 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_8 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "CString", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_8 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_9 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_9 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_9 _currn;
#ifdef __cplusplus
_currn = new _TPrule_9;
#else
_currn = (_TPPrule_9) TreeNodeAlloc (sizeof (struct _TPrule_9));
#endif
_currn->_prod = RULErule_9;
_currn->_desc1 = (_TSPCStringNode) MkCStringNode (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 1 can not be made a CStringNode node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_9;
return ( (NODEPTR) _currn);
}/* Mkrule_9 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_10 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_10 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_10 _currn;
#ifdef __cplusplus
_currn = new _TPrule_10;
#else
_currn = (_TPPrule_10) TreeNodeAlloc (sizeof (struct _TPrule_10));
#endif
_currn->_prod = RULErule_10;
_currn->_desc1 = (_TSPPatternName) MkPatternName (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 1 can not be made a PatternName node ", 0, _coordref);
_currn->_desc2 = (_TSPPatternBody) MkPatternBody (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 2 can not be made a PatternBody node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_10;
return ( (NODEPTR) _currn);
}/* Mkrule_10 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_11 (POSITION *_coordref)
#else
NODEPTR Mkrule_11 (_coordref)
	POSITION *_coordref;
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
_currn->_desc1 = (_TSPFunctionName) MkFunctionName (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_12: root of subtree no. 1 can not be made a FunctionName node ", 0, _coordref);
_currn->_desc2 = (_TSPArguments) MkArguments (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_12: root of subtree no. 2 can not be made a Arguments node ", 0, _coordref);
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
NODEPTR Mkrule_14 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_14 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_14 _currn;
#ifdef __cplusplus
_currn = new _TPrule_14;
#else
_currn = (_TPPrule_14) TreeNodeAlloc (sizeof (struct _TPrule_14));
#endif
_currn->_prod = RULErule_14;
_SETCOORD(_currn)
_TERMACT_rule_14;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Number", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_14 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_15 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_15 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_15 _currn;
#ifdef __cplusplus
_currn = new _TPrule_15;
#else
_currn = (_TPPrule_15) TreeNodeAlloc (sizeof (struct _TPrule_15));
#endif
_currn->_prod = RULErule_15;
_currn->_desc1 = (_TSPIndex) MkIndex (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_15: root of subtree no. 1 can not be made a Index node ", 0, _coordref);
_currn->_desc2 = (_TSPType) MkType (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_15: root of subtree no. 2 can not be made a Type node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_15;
return ( (NODEPTR) _currn);
}/* Mkrule_15 */

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
NODEPTR Mkrule_33 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_33 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_33 _currn;
#ifdef __cplusplus
_currn = new _TPrule_33;
#else
_currn = (_TPPrule_33) TreeNodeAlloc (sizeof (struct _TPrule_33));
#endif
_currn->_prod = RULErule_33;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_33: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_33;
return ( (NODEPTR) _currn);
}/* Mkrule_33 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_32 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_32 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_32 _currn;
#ifdef __cplusplus
_currn = new _TPrule_32;
#else
_currn = (_TPPrule_32) TreeNodeAlloc (sizeof (struct _TPrule_32));
#endif
_currn->_prod = RULErule_32;
_SETCOORD(_currn)
_TERMACT_rule_32;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_32 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_31 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_31 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_31 _currn;
#ifdef __cplusplus
_currn = new _TPrule_31;
#else
_currn = (_TPPrule_31) TreeNodeAlloc (sizeof (struct _TPrule_31));
#endif
_currn->_prod = RULErule_31;
_currn->_desc1 = (_TSPG2) MkG2 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_31: root of subtree no. 1 can not be made a G2 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_31;
return ( (NODEPTR) _currn);
}/* Mkrule_31 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_30 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_30 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_30 _currn;
#ifdef __cplusplus
_currn = new _TPrule_30;
#else
_currn = (_TPPrule_30) TreeNodeAlloc (sizeof (struct _TPrule_30));
#endif
_currn->_prod = RULErule_30;
_currn->_desc1 = (_TSPG3) MkG3 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_30: root of subtree no. 1 can not be made a G3 node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_30;
return ( (NODEPTR) _currn);
}/* Mkrule_30 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_29 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_29 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_29 _currn;
#ifdef __cplusplus
_currn = new _TPrule_29;
#else
_currn = (_TPPrule_29) TreeNodeAlloc (sizeof (struct _TPrule_29));
#endif
_currn->_prod = RULErule_29;
_currn->_desc1 = (_TSPInsertion) MkInsertion (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_29: root of subtree no. 1 can not be made a Insertion node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_29;
return ( (NODEPTR) _currn);
}/* Mkrule_29 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_28 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_28 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_28 _currn;
#ifdef __cplusplus
_currn = new _TPrule_28;
#else
_currn = (_TPPrule_28) TreeNodeAlloc (sizeof (struct _TPrule_28));
#endif
_currn->_prod = RULErule_28;
_currn->_desc1 = (_TSPFunctionCall) MkFunctionCall (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_28: root of subtree no. 1 can not be made a FunctionCall node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_28;
return ( (NODEPTR) _currn);
}/* Mkrule_28 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_27 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_27 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_27 _currn;
#ifdef __cplusplus
_currn = new _TPrule_27;
#else
_currn = (_TPPrule_27) TreeNodeAlloc (sizeof (struct _TPrule_27));
#endif
_currn->_prod = RULErule_27;
_currn->_desc1 = (_TSPG4) MkG4 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_27: root of subtree no. 1 can not be made a G4 node ", 0, _coordref);
_currn->_desc2 = (_TSPArgument) MkArgument (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_27: root of subtree no. 2 can not be made a Argument node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_27;
return ( (NODEPTR) _currn);
}/* Mkrule_27 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_26 (POSITION *_coordref)
#else
NODEPTR Mkrule_26 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_26 _currn;
#ifdef __cplusplus
_currn = new _TPrule_26;
#else
_currn = (_TPPrule_26) TreeNodeAlloc (sizeof (struct _TPrule_26));
#endif
_currn->_prod = RULErule_26;
_SETCOORD(_currn)
_TERMACT_rule_26;
return ( (NODEPTR) _currn);
}/* Mkrule_26 */

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
_currn->_desc1 = (_TSPItem) MkItem (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_25: root of subtree no. 1 can not be made a Item node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_25;
return ( (NODEPTR) _currn);
}/* Mkrule_25 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_24 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_24 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_24 _currn;
#ifdef __cplusplus
_currn = new _TPrule_24;
#else
_currn = (_TPPrule_24) TreeNodeAlloc (sizeof (struct _TPrule_24));
#endif
_currn->_prod = RULErule_24;
_currn->_desc1 = (_TSPG3) MkG3 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_24: root of subtree no. 1 can not be made a G3 node ", 0, _coordref);
_currn->_desc2 = (_TSPItem) MkItem (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_24: root of subtree no. 2 can not be made a Item node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_24;
return ( (NODEPTR) _currn);
}/* Mkrule_24 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_23 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_23 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_23 _currn;
#ifdef __cplusplus
_currn = new _TPrule_23;
#else
_currn = (_TPPrule_23) TreeNodeAlloc (sizeof (struct _TPrule_23));
#endif
_currn->_prod = RULErule_23;
_currn->_desc1 = (_TSPG2) MkG2 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_23: root of subtree no. 1 can not be made a G2 node ", 0, _coordref);
_currn->_desc2 = (_TSPOptional) MkOptional (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_23: root of subtree no. 2 can not be made a Optional node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_23;
return ( (NODEPTR) _currn);
}/* Mkrule_23 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_22 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_22 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_22 _currn;
#ifdef __cplusplus
_currn = new _TPrule_22;
#else
_currn = (_TPPrule_22) TreeNodeAlloc (sizeof (struct _TPrule_22));
#endif
_currn->_prod = RULErule_22;
_currn->_desc1 = (_TSPG2) MkG2 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_22: root of subtree no. 1 can not be made a G2 node ", 0, _coordref);
_currn->_desc2 = (_TSPItem) MkItem (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_22: root of subtree no. 2 can not be made a Item node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_22;
return ( (NODEPTR) _currn);
}/* Mkrule_22 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_21 (POSITION *_coordref)
#else
NODEPTR Mkrule_21 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_21 _currn;
#ifdef __cplusplus
_currn = new _TPrule_21;
#else
_currn = (_TPPrule_21) TreeNodeAlloc (sizeof (struct _TPrule_21));
#endif
_currn->_prod = RULErule_21;
_SETCOORD(_currn)
_TERMACT_rule_21;
return ( (NODEPTR) _currn);
}/* Mkrule_21 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_20 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_20 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_20 _currn;
#ifdef __cplusplus
_currn = new _TPrule_20;
#else
_currn = (_TPPrule_20) TreeNodeAlloc (sizeof (struct _TPrule_20));
#endif
_currn->_prod = RULErule_20;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_20: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_currn->_desc2 = (_TSPPatternSpec) MkPatternSpec (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_20: root of subtree no. 2 can not be made a PatternSpec node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_20;
return ( (NODEPTR) _currn);
}/* Mkrule_20 */

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
NODEPTR Mkrule_18 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_18 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_18 _currn;
#ifdef __cplusplus
_currn = new _TPrule_18;
#else
_currn = (_TPPrule_18) TreeNodeAlloc (sizeof (struct _TPrule_18));
#endif
_currn->_prod = RULErule_18;
_SETCOORD(_currn)
_TERMACT_rule_18;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_18 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_17 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_17 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_17 _currn;
#ifdef __cplusplus
_currn = new _TPrule_17;
#else
_currn = (_TPPrule_17) TreeNodeAlloc (sizeof (struct _TPrule_17));
#endif
_currn->_prod = RULErule_17;
_currn->_desc1 = (_TSPG4) MkG4 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_17: root of subtree no. 1 can not be made a G4 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_17;
return ( (NODEPTR) _currn);
}/* Mkrule_17 */

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
_currn->_desc1 = (_TSPInsertion) MkInsertion (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_16: root of subtree no. 1 can not be made a Insertion node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_16;
return ( (NODEPTR) _currn);
}/* Mkrule_16 */
