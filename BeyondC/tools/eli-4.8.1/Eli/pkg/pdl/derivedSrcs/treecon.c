
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
NODEPTR MkG2 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG2 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG2)) return (_currn);
if (IsSymb (_currn, SYMBPropertyValue)) return (Mkrule_006(_coordref, _currn));
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
NODEPTR MkPropertyValueList (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPropertyValueList (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPropertyValueList)) return (_currn);
return(NULLNODEPTR);
}/* MkPropertyValueList */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPropertyValue (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPropertyValue (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPropertyValue)) return (_currn);
return(NULLNODEPTR);
}/* MkPropertyValue */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkKnownKey (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkKnownKey (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBKnownKey)) return (_currn);
return(NULLNODEPTR);
}/* MkKnownKey */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPropertyValues (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPropertyValues (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPropertyValues)) return (_currn);
if (IsSymb (_currn, SYMBPropertyValue)) return (Mkrule_015(_coordref, _currn));
if (IsSymb (_currn, SYMBG2)) return (Mkrule_015(_coordref, _currn));
return(NULLNODEPTR);
}/* MkPropertyValues */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkFileDecl (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkFileDecl (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBFileDecl)) return (_currn);
if (IsSymb (_currn, SYMBKnownKey)) return (Mkrule_000(_coordref, _currn));
return(NULLNODEPTR);
}/* MkFileDecl */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkParameterTypeDecl (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkParameterTypeDecl (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBParameterTypeDecl)) return (_currn);
return(NULLNODEPTR);
}/* MkParameterTypeDecl */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkParameterTypeList (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkParameterTypeList (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBParameterTypeList)) return (_currn);
if (IsSymb (_currn, SYMBParameterTypeDecl)) return (MkSingleParameterType(_coordref, _currn));
return(NULLNODEPTR);
}/* MkParameterTypeList */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkModifier (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkModifier (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBModifier)) return (_currn);
return(NULLNODEPTR);
}/* MkModifier */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkParameterDecl (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkParameterDecl (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBParameterDecl)) return (_currn);
return(NULLNODEPTR);
}/* MkParameterDecl */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOperationNameList (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOperationNameList (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOperationNameList)) return (_currn);
if (IsSymb (_currn, SYMBOperationNameDecl)) return (Mkrule_009(_coordref, _currn));
return(NULLNODEPTR);
}/* MkOperationNameList */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkType (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkType (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBType)) return (_currn);
if (IsSymb (_currn, SYMBTypeIdent)) return (MkTypeNoOp(_coordref, _currn));
if (IsSymb (_currn, SYMBTypeSpecifier)) return (MkTypeNoOp(_coordref, _currn));
return(NULLNODEPTR);
}/* MkType */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPropertyNameList (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPropertyNameList (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPropertyNameList)) return (_currn);
if (IsSymb (_currn, SYMBPropertyNameDecl)) return (Mkrule_011(_coordref, _currn));
return(NULLNODEPTR);
}/* MkPropertyNameList */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPropertyDecl (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPropertyDecl (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPropertyDecl)) return (_currn);
return(NULLNODEPTR);
}/* MkPropertyDecl */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOperationNameDecl (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOperationNameDecl (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOperationNameDecl)) return (_currn);
return(NULLNODEPTR);
}/* MkOperationNameDecl */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkParameterList (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkParameterList (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBParameterList)) return (_currn);
if (IsSymb (_currn, SYMBParameterDecl)) return (MkSingleParameter(_coordref, _currn));
return(NULLNODEPTR);
}/* MkParameterList */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTypeSpecifier (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTypeSpecifier (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTypeSpecifier)) return (_currn);
if (IsSymb (_currn, SYMBTypeIdent)) return (MkDefinedType(_coordref, _currn));
return(NULLNODEPTR);
}/* MkTypeSpecifier */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOperationList (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOperationList (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOperationList)) return (_currn);
if (IsSymb (_currn, SYMBOperationDecl)) return (Mkrule_007(_coordref, _currn));
return(NULLNODEPTR);
}/* MkOperationList */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOperationDecl (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOperationDecl (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOperationDecl)) return (_currn);
return(NULLNODEPTR);
}/* MkOperationDecl */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPropertyNameDecl (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPropertyNameDecl (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPropertyNameDecl)) return (_currn);
return(NULLNODEPTR);
}/* MkPropertyNameDecl */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTypeIdent (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTypeIdent (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTypeIdent)) return (_currn);
return(NULLNODEPTR);
}/* MkTypeIdent */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkLibraryList (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkLibraryList (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBLibraryList)) return (_currn);
if (IsSymb (_currn, SYMBOperationDecl)) return (MkLibrarySpec(_coordref, _currn));
if (IsSymb (_currn, SYMBOperationList)) return (MkLibrarySpec(_coordref, _currn));
return(NULLNODEPTR);
}/* MkLibraryList */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRange (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRange (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRange)) return (_currn);
if (IsSymb (_currn, SYMBG1)) return (Mkrule_016(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRange */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSource (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSource (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSource)) return (_currn);
return(NULLNODEPTR);
}/* MkSource */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_1 (POSITION *_coordref, int _TERM1, int _TERM2)
#else
NODEPTR Mkrule_1 (_coordref, _TERM1, _TERM2)
	POSITION *_coordref;
	int _TERM1;
	int _TERM2;
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

#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Text", _TERM2);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_2 (POSITION *_coordref, int _TERM1, NODEPTR _desc1)
#else
NODEPTR Mkrule_2 (_coordref, _TERM1,_desc1)
	POSITION *_coordref;
	int _TERM1;
	NODEPTR _desc1;
#endif
{	_TPPrule_2 _currn;
#ifdef __cplusplus
_currn = new _TPrule_2;
#else
_currn = (_TPPrule_2) TreeNodeAlloc (sizeof (struct _TPrule_2));
#endif
_currn->_prod = RULErule_2;
_currn->_desc1 = (_TSPPropertyValueList) MkPropertyValueList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_2: root of subtree no. 1 can not be made a PropertyValueList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_2;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_016 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_016 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_016 _currn;
#ifdef __cplusplus
_currn = new _TPrule_016;
#else
_currn = (_TPPrule_016) TreeNodeAlloc (sizeof (struct _TPrule_016));
#endif
_currn->_prod = RULErule_016;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_016: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_016;
return ( (NODEPTR) _currn);
}/* Mkrule_016 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_015 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_015 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_015 _currn;
#ifdef __cplusplus
_currn = new _TPrule_015;
#else
_currn = (_TPPrule_015) TreeNodeAlloc (sizeof (struct _TPrule_015));
#endif
_currn->_prod = RULErule_015;
_currn->_desc1 = (_TSPG2) MkG2 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_015: root of subtree no. 1 can not be made a G2 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_015;
return ( (NODEPTR) _currn);
}/* Mkrule_015 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_014 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_014 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_014 _currn;
#ifdef __cplusplus
_currn = new _TPrule_014;
#else
_currn = (_TPPrule_014) TreeNodeAlloc (sizeof (struct _TPrule_014));
#endif
_currn->_prod = RULErule_014;
_currn->_desc1 = (_TSPPropertyValues) MkPropertyValues (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_014: root of subtree no. 1 can not be made a PropertyValues node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_014;
return ( (NODEPTR) _currn);
}/* Mkrule_014 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_013 (POSITION *_coordref)
#else
NODEPTR Mkrule_013 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_013 _currn;
#ifdef __cplusplus
_currn = new _TPrule_013;
#else
_currn = (_TPPrule_013) TreeNodeAlloc (sizeof (struct _TPrule_013));
#endif
_currn->_prod = RULErule_013;
_SETCOORD(_currn)
_TERMACT_rule_013;
return ( (NODEPTR) _currn);
}/* Mkrule_013 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_012 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_012 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_012 _currn;
#ifdef __cplusplus
_currn = new _TPrule_012;
#else
_currn = (_TPPrule_012) TreeNodeAlloc (sizeof (struct _TPrule_012));
#endif
_currn->_prod = RULErule_012;
_currn->_desc1 = (_TSPPropertyNameList) MkPropertyNameList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_012: root of subtree no. 1 can not be made a PropertyNameList node ", 0, _coordref);
_currn->_desc2 = (_TSPPropertyNameDecl) MkPropertyNameDecl (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_012: root of subtree no. 2 can not be made a PropertyNameDecl node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_012;
return ( (NODEPTR) _currn);
}/* Mkrule_012 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_011 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_011 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_011 _currn;
#ifdef __cplusplus
_currn = new _TPrule_011;
#else
_currn = (_TPPrule_011) TreeNodeAlloc (sizeof (struct _TPrule_011));
#endif
_currn->_prod = RULErule_011;
_currn->_desc1 = (_TSPPropertyNameDecl) MkPropertyNameDecl (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_011: root of subtree no. 1 can not be made a PropertyNameDecl node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_011;
return ( (NODEPTR) _currn);
}/* Mkrule_011 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_010 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_010 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_010 _currn;
#ifdef __cplusplus
_currn = new _TPrule_010;
#else
_currn = (_TPPrule_010) TreeNodeAlloc (sizeof (struct _TPrule_010));
#endif
_currn->_prod = RULErule_010;
_currn->_desc1 = (_TSPOperationNameList) MkOperationNameList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_010: root of subtree no. 1 can not be made a OperationNameList node ", 0, _coordref);
_currn->_desc2 = (_TSPOperationNameDecl) MkOperationNameDecl (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_010: root of subtree no. 2 can not be made a OperationNameDecl node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_010;
return ( (NODEPTR) _currn);
}/* Mkrule_010 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_009 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_009 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_009 _currn;
#ifdef __cplusplus
_currn = new _TPrule_009;
#else
_currn = (_TPPrule_009) TreeNodeAlloc (sizeof (struct _TPrule_009));
#endif
_currn->_prod = RULErule_009;
_currn->_desc1 = (_TSPOperationNameDecl) MkOperationNameDecl (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_009: root of subtree no. 1 can not be made a OperationNameDecl node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_009;
return ( (NODEPTR) _currn);
}/* Mkrule_009 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_008 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_008 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_008 _currn;
#ifdef __cplusplus
_currn = new _TPrule_008;
#else
_currn = (_TPPrule_008) TreeNodeAlloc (sizeof (struct _TPrule_008));
#endif
_currn->_prod = RULErule_008;
_currn->_desc1 = (_TSPOperationList) MkOperationList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_008: root of subtree no. 1 can not be made a OperationList node ", 0, _coordref);
_currn->_desc2 = (_TSPOperationDecl) MkOperationDecl (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_008: root of subtree no. 2 can not be made a OperationDecl node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_008;
return ( (NODEPTR) _currn);
}/* Mkrule_008 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_007 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_007 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_007 _currn;
#ifdef __cplusplus
_currn = new _TPrule_007;
#else
_currn = (_TPPrule_007) TreeNodeAlloc (sizeof (struct _TPrule_007));
#endif
_currn->_prod = RULErule_007;
_currn->_desc1 = (_TSPOperationDecl) MkOperationDecl (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_007: root of subtree no. 1 can not be made a OperationDecl node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_007;
return ( (NODEPTR) _currn);
}/* Mkrule_007 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_006 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_006 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_006 _currn;
#ifdef __cplusplus
_currn = new _TPrule_006;
#else
_currn = (_TPPrule_006) TreeNodeAlloc (sizeof (struct _TPrule_006));
#endif
_currn->_prod = RULErule_006;
_currn->_desc1 = (_TSPPropertyValue) MkPropertyValue (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_006: root of subtree no. 1 can not be made a PropertyValue node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_006;
return ( (NODEPTR) _currn);
}/* Mkrule_006 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_005 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_005 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_005 _currn;
#ifdef __cplusplus
_currn = new _TPrule_005;
#else
_currn = (_TPPrule_005) TreeNodeAlloc (sizeof (struct _TPrule_005));
#endif
_currn->_prod = RULErule_005;
_currn->_desc1 = (_TSPG2) MkG2 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_005: root of subtree no. 1 can not be made a G2 node ", 0, _coordref);
_currn->_desc2 = (_TSPPropertyValue) MkPropertyValue (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_005: root of subtree no. 2 can not be made a PropertyValue node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_005;
return ( (NODEPTR) _currn);
}/* Mkrule_005 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_004 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_004 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_004 _currn;
#ifdef __cplusplus
_currn = new _TPrule_004;
#else
_currn = (_TPPrule_004) TreeNodeAlloc (sizeof (struct _TPrule_004));
#endif
_currn->_prod = RULErule_004;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_004: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_currn->_desc2 = (_TSPPropertyDecl) MkPropertyDecl (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_004: root of subtree no. 2 can not be made a PropertyDecl node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_004;
return ( (NODEPTR) _currn);
}/* Mkrule_004 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_003 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_003 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_003 _currn;
#ifdef __cplusplus
_currn = new _TPrule_003;
#else
_currn = (_TPPrule_003) TreeNodeAlloc (sizeof (struct _TPrule_003));
#endif
_currn->_prod = RULErule_003;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_003: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_currn->_desc2 = (_TSPOperationDecl) MkOperationDecl (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_003: root of subtree no. 2 can not be made a OperationDecl node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_003;
return ( (NODEPTR) _currn);
}/* Mkrule_003 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_002 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_002 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_002 _currn;
#ifdef __cplusplus
_currn = new _TPrule_002;
#else
_currn = (_TPPrule_002) TreeNodeAlloc (sizeof (struct _TPrule_002));
#endif
_currn->_prod = RULErule_002;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_002: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_currn->_desc2 = (_TSPFileDecl) MkFileDecl (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_002: root of subtree no. 2 can not be made a FileDecl node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_002;
return ( (NODEPTR) _currn);
}/* Mkrule_002 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_001 (POSITION *_coordref)
#else
NODEPTR Mkrule_001 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_001 _currn;
#ifdef __cplusplus
_currn = new _TPrule_001;
#else
_currn = (_TPPrule_001) TreeNodeAlloc (sizeof (struct _TPrule_001));
#endif
_currn->_prod = RULErule_001;
_SETCOORD(_currn)
_TERMACT_rule_001;
return ( (NODEPTR) _currn);
}/* Mkrule_001 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_000 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_000 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_000 _currn;
#ifdef __cplusplus
_currn = new _TPrule_000;
#else
_currn = (_TPPrule_000) TreeNodeAlloc (sizeof (struct _TPrule_000));
#endif
_currn->_prod = RULErule_000;
_currn->_desc1 = (_TSPKnownKey) MkKnownKey (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_000: root of subtree no. 1 can not be made a KnownKey node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_000;
return ( (NODEPTR) _currn);
}/* Mkrule_000 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkFileSpec (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkFileSpec (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPFileSpec _currn;
#ifdef __cplusplus
_currn = new _TPFileSpec;
#else
_currn = (_TPPFileSpec) TreeNodeAlloc (sizeof (struct _TPFileSpec));
#endif
_currn->_prod = RULEFileSpec;
_SETCOORD(_currn)
_TERMACT_FileSpec;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "String", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkFileSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkIdentParameterTS (POSITION *_coordref, NODEPTR _desc1, int _TERM1, NODEPTR _desc2)
#else
NODEPTR MkIdentParameterTS (_coordref,_desc1, _TERM1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	int _TERM1;
	NODEPTR _desc2;
#endif
{	_TPPIdentParameterTS _currn;
#ifdef __cplusplus
_currn = new _TPIdentParameterTS;
#else
_currn = (_TPPIdentParameterTS) TreeNodeAlloc (sizeof (struct _TPIdentParameterTS));
#endif
_currn->_prod = RULEIdentParameterTS;
_currn->_desc1 = (_TSPTypeSpecifier) MkTypeSpecifier (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE IdentParameterTS: root of subtree no. 1 can not be made a TypeSpecifier node ", 0, _coordref);
_currn->_desc2 = (_TSPModifier) MkModifier (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE IdentParameterTS: root of subtree no. 2 can not be made a Modifier node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_IdentParameterTS;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkIdentParameterTS */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkParameterTypeSpec (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkParameterTypeSpec (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPParameterTypeSpec _currn;
#ifdef __cplusplus
_currn = new _TPParameterTypeSpec;
#else
_currn = (_TPPParameterTypeSpec) TreeNodeAlloc (sizeof (struct _TPParameterTypeSpec));
#endif
_currn->_prod = RULEParameterTypeSpec;
_currn->_desc1 = (_TSPTypeSpecifier) MkTypeSpecifier (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE ParameterTypeSpec: root of subtree no. 1 can not be made a TypeSpecifier node ", 0, _coordref);
_currn->_desc2 = (_TSPModifier) MkModifier (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE ParameterTypeSpec: root of subtree no. 2 can not be made a Modifier node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_ParameterTypeSpec;
return ( (NODEPTR) _currn);
}/* MkParameterTypeSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSingleParameterType (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkSingleParameterType (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPSingleParameterType _currn;
#ifdef __cplusplus
_currn = new _TPSingleParameterType;
#else
_currn = (_TPPSingleParameterType) TreeNodeAlloc (sizeof (struct _TPSingleParameterType));
#endif
_currn->_prod = RULESingleParameterType;
_currn->_desc1 = (_TSPParameterTypeDecl) MkParameterTypeDecl (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE SingleParameterType: root of subtree no. 1 can not be made a ParameterTypeDecl node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_SingleParameterType;
return ( (NODEPTR) _currn);
}/* MkSingleParameterType */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMultipleParameterTypes (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkMultipleParameterTypes (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPMultipleParameterTypes _currn;
#ifdef __cplusplus
_currn = new _TPMultipleParameterTypes;
#else
_currn = (_TPPMultipleParameterTypes) TreeNodeAlloc (sizeof (struct _TPMultipleParameterTypes));
#endif
_currn->_prod = RULEMultipleParameterTypes;
_currn->_desc1 = (_TSPParameterTypeList) MkParameterTypeList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE MultipleParameterTypes: root of subtree no. 1 can not be made a ParameterTypeList node ", 0, _coordref);
_currn->_desc2 = (_TSPParameterTypeDecl) MkParameterTypeDecl (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE MultipleParameterTypes: root of subtree no. 2 can not be made a ParameterTypeDecl node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_MultipleParameterTypes;
return ( (NODEPTR) _currn);
}/* MkMultipleParameterTypes */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkExtendedModifier (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkExtendedModifier (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPExtendedModifier _currn;
#ifdef __cplusplus
_currn = new _TPExtendedModifier;
#else
_currn = (_TPPExtendedModifier) TreeNodeAlloc (sizeof (struct _TPExtendedModifier));
#endif
_currn->_prod = RULEExtendedModifier;
_currn->_desc1 = (_TSPParameterTypeList) MkParameterTypeList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE ExtendedModifier: root of subtree no. 1 can not be made a ParameterTypeList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_ExtendedModifier;
return ( (NODEPTR) _currn);
}/* MkExtendedModifier */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSimpleModifier (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkSimpleModifier (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPSimpleModifier _currn;
#ifdef __cplusplus
_currn = new _TPSimpleModifier;
#else
_currn = (_TPPSimpleModifier) TreeNodeAlloc (sizeof (struct _TPSimpleModifier));
#endif
_currn->_prod = RULESimpleModifier;
_currn->_desc1 = (_TSPParameterTypeList) MkParameterTypeList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE SimpleModifier: root of subtree no. 1 can not be made a ParameterTypeList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_SimpleModifier;
return ( (NODEPTR) _currn);
}/* MkSimpleModifier */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkVoidModifier (POSITION *_coordref)
#else
NODEPTR MkVoidModifier (_coordref)
	POSITION *_coordref;
#endif
{	_TPPVoidModifier _currn;
#ifdef __cplusplus
_currn = new _TPVoidModifier;
#else
_currn = (_TPPVoidModifier) TreeNodeAlloc (sizeof (struct _TPVoidModifier));
#endif
_currn->_prod = RULEVoidModifier;
_SETCOORD(_currn)
_TERMACT_VoidModifier;
return ( (NODEPTR) _currn);
}/* MkVoidModifier */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkEmptyModifier (POSITION *_coordref)
#else
NODEPTR MkEmptyModifier (_coordref)
	POSITION *_coordref;
#endif
{	_TPPEmptyModifier _currn;
#ifdef __cplusplus
_currn = new _TPEmptyModifier;
#else
_currn = (_TPPEmptyModifier) TreeNodeAlloc (sizeof (struct _TPEmptyModifier));
#endif
_currn->_prod = RULEEmptyModifier;
_SETCOORD(_currn)
_TERMACT_EmptyModifier;
return ( (NODEPTR) _currn);
}/* MkEmptyModifier */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkParameterSpec (POSITION *_coordref, NODEPTR _desc1, int _TERM1, NODEPTR _desc2)
#else
NODEPTR MkParameterSpec (_coordref,_desc1, _TERM1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	int _TERM1;
	NODEPTR _desc2;
#endif
{	_TPPParameterSpec _currn;
#ifdef __cplusplus
_currn = new _TPParameterSpec;
#else
_currn = (_TPPParameterSpec) TreeNodeAlloc (sizeof (struct _TPParameterSpec));
#endif
_currn->_prod = RULEParameterSpec;
_currn->_desc1 = (_TSPTypeSpecifier) MkTypeSpecifier (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE ParameterSpec: root of subtree no. 1 can not be made a TypeSpecifier node ", 0, _coordref);
_currn->_desc2 = (_TSPModifier) MkModifier (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE ParameterSpec: root of subtree no. 2 can not be made a Modifier node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_ParameterSpec;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkParameterSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSingleParameter (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkSingleParameter (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPSingleParameter _currn;
#ifdef __cplusplus
_currn = new _TPSingleParameter;
#else
_currn = (_TPPSingleParameter) TreeNodeAlloc (sizeof (struct _TPSingleParameter));
#endif
_currn->_prod = RULESingleParameter;
_currn->_desc1 = (_TSPParameterDecl) MkParameterDecl (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE SingleParameter: root of subtree no. 1 can not be made a ParameterDecl node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_SingleParameter;
return ( (NODEPTR) _currn);
}/* MkSingleParameter */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMultipleParameters (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkMultipleParameters (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPMultipleParameters _currn;
#ifdef __cplusplus
_currn = new _TPMultipleParameters;
#else
_currn = (_TPPMultipleParameters) TreeNodeAlloc (sizeof (struct _TPMultipleParameters));
#endif
_currn->_prod = RULEMultipleParameters;
_currn->_desc1 = (_TSPParameterList) MkParameterList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE MultipleParameters: root of subtree no. 1 can not be made a ParameterList node ", 0, _coordref);
_currn->_desc2 = (_TSPParameterDecl) MkParameterDecl (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE MultipleParameters: root of subtree no. 2 can not be made a ParameterDecl node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_MultipleParameters;
return ( (NODEPTR) _currn);
}/* MkMultipleParameters */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTypeWithOp (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkTypeWithOp (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPTypeWithOp _currn;
#ifdef __cplusplus
_currn = new _TPTypeWithOp;
#else
_currn = (_TPPTypeWithOp) TreeNodeAlloc (sizeof (struct _TPTypeWithOp));
#endif
_currn->_prod = RULETypeWithOp;
_currn->_desc1 = (_TSPTypeSpecifier) MkTypeSpecifier (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE TypeWithOp: root of subtree no. 1 can not be made a TypeSpecifier node ", 0, _coordref);
_currn->_desc2 = (_TSPOperationNameList) MkOperationNameList (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE TypeWithOp: root of subtree no. 2 can not be made a OperationNameList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_TypeWithOp;
return ( (NODEPTR) _currn);
}/* MkTypeWithOp */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTypeNoOp (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkTypeNoOp (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPTypeNoOp _currn;
#ifdef __cplusplus
_currn = new _TPTypeNoOp;
#else
_currn = (_TPPTypeNoOp) TreeNodeAlloc (sizeof (struct _TPTypeNoOp));
#endif
_currn->_prod = RULETypeNoOp;
_currn->_desc1 = (_TSPTypeSpecifier) MkTypeSpecifier (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE TypeNoOp: root of subtree no. 1 can not be made a TypeSpecifier node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_TypeNoOp;
return ( (NODEPTR) _currn);
}/* MkTypeNoOp */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPropertySpec (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkPropertySpec (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPPropertySpec _currn;
#ifdef __cplusplus
_currn = new _TPPropertySpec;
#else
_currn = (_TPPPropertySpec) TreeNodeAlloc (sizeof (struct _TPPropertySpec));
#endif
_currn->_prod = RULEPropertySpec;
_currn->_desc1 = (_TSPPropertyNameList) MkPropertyNameList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE PropertySpec: root of subtree no. 1 can not be made a PropertyNameList node ", 0, _coordref);
_currn->_desc2 = (_TSPType) MkType (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE PropertySpec: root of subtree no. 2 can not be made a Type node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_PropertySpec;
return ( (NODEPTR) _currn);
}/* MkPropertySpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDefinedType (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkDefinedType (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPDefinedType _currn;
#ifdef __cplusplus
_currn = new _TPDefinedType;
#else
_currn = (_TPPDefinedType) TreeNodeAlloc (sizeof (struct _TPDefinedType));
#endif
_currn->_prod = RULEDefinedType;
_currn->_desc1 = (_TSPTypeIdent) MkTypeIdent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE DefinedType: root of subtree no. 1 can not be made a TypeIdent node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_DefinedType;
return ( (NODEPTR) _currn);
}/* MkDefinedType */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkGenericType (POSITION *_coordref)
#else
NODEPTR MkGenericType (_coordref)
	POSITION *_coordref;
#endif
{	_TPPGenericType _currn;
#ifdef __cplusplus
_currn = new _TPGenericType;
#else
_currn = (_TPPGenericType) TreeNodeAlloc (sizeof (struct _TPGenericType));
#endif
_currn->_prod = RULEGenericType;
_SETCOORD(_currn)
_TERMACT_GenericType;
return ( (NODEPTR) _currn);
}/* MkGenericType */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOperationName (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkOperationName (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPOperationName _currn;
#ifdef __cplusplus
_currn = new _TPOperationName;
#else
_currn = (_TPPOperationName) TreeNodeAlloc (sizeof (struct _TPOperationName));
#endif
_currn->_prod = RULEOperationName;
_SETCOORD(_currn)
_TERMACT_OperationName;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkOperationName */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOperationSpec (POSITION *_coordref, NODEPTR _desc1, int _TERM1, NODEPTR _desc2, int _TERM2)
#else
NODEPTR MkOperationSpec (_coordref,_desc1, _TERM1,_desc2, _TERM2)
	POSITION *_coordref;
	NODEPTR _desc1;
	int _TERM1;
	NODEPTR _desc2;
	int _TERM2;
#endif
{	_TPPOperationSpec _currn;
#ifdef __cplusplus
_currn = new _TPOperationSpec;
#else
_currn = (_TPPOperationSpec) TreeNodeAlloc (sizeof (struct _TPOperationSpec));
#endif
_currn->_prod = RULEOperationSpec;
_currn->_desc1 = (_TSPTypeSpecifier) MkTypeSpecifier (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE OperationSpec: root of subtree no. 1 can not be made a TypeSpecifier node ", 0, _coordref);
_currn->_desc2 = (_TSPParameterList) MkParameterList (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE OperationSpec: root of subtree no. 2 can not be made a ParameterList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_OperationSpec;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Text", _TERM2);
#endif

return ( (NODEPTR) _currn);
}/* MkOperationSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPropertyName (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkPropertyName (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPPropertyName _currn;
#ifdef __cplusplus
_currn = new _TPPropertyName;
#else
_currn = (_TPPPropertyName) TreeNodeAlloc (sizeof (struct _TPPropertyName));
#endif
_currn->_prod = RULEPropertyName;
_SETCOORD(_currn)
_TERMACT_PropertyName;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkPropertyName */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTypeName (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkTypeName (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPTypeName _currn;
#ifdef __cplusplus
_currn = new _TPTypeName;
#else
_currn = (_TPPTypeName) TreeNodeAlloc (sizeof (struct _TPTypeName));
#endif
_currn->_prod = RULETypeName;
_SETCOORD(_currn)
_TERMACT_TypeName;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkTypeName */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkLibrarySpec (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkLibrarySpec (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPLibrarySpec _currn;
#ifdef __cplusplus
_currn = new _TPLibrarySpec;
#else
_currn = (_TPPLibrarySpec) TreeNodeAlloc (sizeof (struct _TPLibrarySpec));
#endif
_currn->_prod = RULELibrarySpec;
_currn->_desc1 = (_TSPOperationList) MkOperationList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE LibrarySpec: root of subtree no. 1 can not be made a OperationList node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_LibrarySpec;
return ( (NODEPTR) _currn);
}/* MkLibrarySpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAxiom (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkAxiom (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPAxiom _currn;
#ifdef __cplusplus
_currn = new _TPAxiom;
#else
_currn = (_TPPAxiom) TreeNodeAlloc (sizeof (struct _TPAxiom));
#endif
_currn->_prod = RULEAxiom;
_currn->_desc1 = (_TSPRange) MkRange (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE Axiom: root of subtree no. 1 can not be made a Range node ", 0, _coordref);
_currn->_desc2 = (_TSPLibraryList) MkLibraryList (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE Axiom: root of subtree no. 2 can not be made a LibraryList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_Axiom;
return ( (NODEPTR) _currn);
}/* MkAxiom */
