
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
NODEPTR MkMapDelim (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapDelim (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapDelim)) return (_currn);
return(NULLNODEPTR);
}/* MkMapDelim */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapReorder (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapReorder (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapReorder)) return (_currn);
return(NULLNODEPTR);
}/* MkMapReorder */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapProd (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapProd (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapProd)) return (_currn);
return(NULLNODEPTR);
}/* MkMapProd */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapAbs (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapAbs (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapAbs)) return (_currn);
return(NULLNODEPTR);
}/* MkMapAbs */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAbsSignature (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAbsSignature (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAbsSignature)) return (_currn);
return(NULLNODEPTR);
}/* MkAbsSignature */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRuleIdUse (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRuleIdUse (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRuleIdUse)) return (_currn);
return(NULLNODEPTR);
}/* MkRuleIdUse */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapLHS (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapLHS (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapLHS)) return (_currn);
return(NULLNODEPTR);
}/* MkMapLHS */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMaptoId (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMaptoId (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMaptoId)) return (_currn);
return(NULLNODEPTR);
}/* MkMaptoId */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAbsRuleId (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAbsRuleId (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAbsRuleId)) return (_currn);
return(NULLNODEPTR);
}/* MkAbsRuleId */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapText (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapText (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapText)) return (_currn);
return(NULLNODEPTR);
}/* MkMapText */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapPosition (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapPosition (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapPosition)) return (_currn);
return(NULLNODEPTR);
}/* MkMapPosition */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapReorderAlt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapReorderAlt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapReorderAlt)) return (_currn);
return(NULLNODEPTR);
}/* MkMapReorderAlt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapElement (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapElement (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapElement)) return (_currn);
return(NULLNODEPTR);
}/* MkMapElement */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapAlt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapAlt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapAlt)) return (_currn);
return(NULLNODEPTR);
}/* MkMapAlt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapMember (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapMember (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapMember)) return (_currn);
return(NULLNODEPTR);
}/* MkMapMember */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapMembers (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapMembers (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapMembers)) return (_currn);
return(NULLNODEPTR);
}/* MkMapMembers */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAbsAlt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAbsAlt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAbsAlt)) return (_currn);
return(NULLNODEPTR);
}/* MkAbsAlt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAbsAlts (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAbsAlts (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAbsAlts)) return (_currn);
return(NULLNODEPTR);
}/* MkAbsAlts */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAbsElements (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAbsElements (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAbsElements)) return (_currn);
return(NULLNODEPTR);
}/* MkAbsElements */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkBottomUpRule (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkBottomUpRule (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBBottomUpRule)) return (_currn);
return(NULLNODEPTR);
}/* MkBottomUpRule */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapChains (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapChains (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapChains)) return (_currn);
return(NULLNODEPTR);
}/* MkMapChains */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapRule (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapRule (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapRule)) return (_currn);
return(NULLNODEPTR);
}/* MkMapRule */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMapSymbol (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMapSymbol (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMapSymbol)) return (_currn);
return(NULLNODEPTR);
}/* MkMapSymbol */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAbsElement (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAbsElement (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAbsElement)) return (_currn);
return(NULLNODEPTR);
}/* MkAbsElement */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkConElement (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkConElement (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBConElement)) return (_currn);
return(NULLNODEPTR);
}/* MkConElement */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAbsLHS (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAbsLHS (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAbsLHS)) return (_currn);
return(NULLNODEPTR);
}/* MkAbsLHS */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkConAlt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkConAlt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBConAlt)) return (_currn);
return(NULLNODEPTR);
}/* MkConAlt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkConLHS (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkConLHS (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBConLHS)) return (_currn);
return(NULLNODEPTR);
}/* MkConLHS */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAbsProd (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAbsProd (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAbsProd)) return (_currn);
return(NULLNODEPTR);
}/* MkAbsProd */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkConProd (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkConProd (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBConProd)) return (_currn);
return(NULLNODEPTR);
}/* MkConProd */

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
_dapto_term_int(((NODEPTR)_currn), "Text", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_3 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_3 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Integer", _TERM1);
#endif

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
_currn->_desc1 = (_TSPMapReorderAlt) MkMapReorderAlt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_4: root of subtree no. 1 can not be made a MapReorderAlt node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_4;
return ( (NODEPTR) _currn);
}/* Mkrule_4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_5 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_5 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Text", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_5 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_6 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_6 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_6 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_7 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_7 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_7 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_8 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_8 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_8 _currn;
#ifdef __cplusplus
_currn = new _TPrule_8;
#else
_currn = (_TPPrule_8) TreeNodeAlloc (sizeof (struct _TPrule_8));
#endif
_currn->_prod = RULErule_8;
_currn->_desc1 = (_TSPMapLHS) MkMapLHS (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_8: root of subtree no. 1 can not be made a MapLHS node ", 0, _coordref);
_currn->_desc2 = (_TSPMapDelim) MkMapDelim (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_8: root of subtree no. 2 can not be made a MapDelim node ", 0, _coordref);
_currn->_desc3 = (_TSPMapAlt) MkMapAlt (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_8: root of subtree no. 3 can not be made a MapAlt node ", 0, _coordref);
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
_currn->_desc1 = (_TSPMapProd) MkMapProd (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 1 can not be made a MapProd node ", 0, _coordref);
_currn->_desc2 = (_TSPMapReorder) MkMapReorder (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 2 can not be made a MapReorder node ", 0, _coordref);
_currn->_desc3 = (_TSPMapAbs) MkMapAbs (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 3 can not be made a MapAbs node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_9;
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
_currn->_desc1 = (_TSPRuleIdUse) MkRuleIdUse (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 1 can not be made a RuleIdUse node ", 0, _coordref);
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
_currn->_desc1 = (_TSPMaptoId) MkMaptoId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_12: root of subtree no. 1 can not be made a MaptoId node ", 0, _coordref);
_currn->_desc2 = (_TSPMapMembers) MkMapMembers (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_12: root of subtree no. 2 can not be made a MapMembers node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_12;
return ( (NODEPTR) _currn);
}/* Mkrule_12 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_13 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_13 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

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
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
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
_currn->_desc1 = (_TSPAbsLHS) MkAbsLHS (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_15: root of subtree no. 1 can not be made a AbsLHS node ", 0, _coordref);
_currn->_desc2 = (_TSPAbsAlts) MkAbsAlts (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_15: root of subtree no. 2 can not be made a AbsAlts node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_15;
return ( (NODEPTR) _currn);
}/* Mkrule_15 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_16 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_16 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_16 _currn;
#ifdef __cplusplus
_currn = new _TPrule_16;
#else
_currn = (_TPPrule_16) TreeNodeAlloc (sizeof (struct _TPrule_16));
#endif
_currn->_prod = RULErule_16;
_SETCOORD(_currn)
_TERMACT_rule_16;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_16 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_17 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_17 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_17 _currn;
#ifdef __cplusplus
_currn = new _TPrule_17;
#else
_currn = (_TPPrule_17) TreeNodeAlloc (sizeof (struct _TPrule_17));
#endif
_currn->_prod = RULErule_17;
_currn->_desc1 = (_TSPAbsLHS) MkAbsLHS (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_17: root of subtree no. 1 can not be made a AbsLHS node ", 0, _coordref);
_currn->_desc2 = (_TSPAbsElements) MkAbsElements (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_17: root of subtree no. 2 can not be made a AbsElements node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_17;
return ( (NODEPTR) _currn);
}/* Mkrule_17 */

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
NODEPTR Mkrule_19 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_19 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_19 _currn;
#ifdef __cplusplus
_currn = new _TPrule_19;
#else
_currn = (_TPPrule_19) TreeNodeAlloc (sizeof (struct _TPrule_19));
#endif
_currn->_prod = RULErule_19;
_currn->_desc1 = (_TSPAbsRuleId) MkAbsRuleId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_19: root of subtree no. 1 can not be made a AbsRuleId node ", 0, _coordref);
_currn->_desc2 = (_TSPAbsSignature) MkAbsSignature (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_19: root of subtree no. 2 can not be made a AbsSignature node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_19;
return ( (NODEPTR) _currn);
}/* Mkrule_19 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_20 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_20 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_20 _currn;
#ifdef __cplusplus
_currn = new _TPrule_20;
#else
_currn = (_TPPrule_20) TreeNodeAlloc (sizeof (struct _TPrule_20));
#endif
_currn->_prod = RULErule_20;
_SETCOORD(_currn)
_TERMACT_rule_20;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Text", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_20 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_21 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_21 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_21 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_22 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_22 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_22 _currn;
#ifdef __cplusplus
_currn = new _TPrule_22;
#else
_currn = (_TPPrule_22) TreeNodeAlloc (sizeof (struct _TPrule_22));
#endif
_currn->_prod = RULErule_22;
_SETCOORD(_currn)
_TERMACT_rule_22;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Text", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_22 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_23 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_23 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_23 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_24 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_24 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_24 _currn;
#ifdef __cplusplus
_currn = new _TPrule_24;
#else
_currn = (_TPPrule_24) TreeNodeAlloc (sizeof (struct _TPrule_24));
#endif
_currn->_prod = RULErule_24;
_SETCOORD(_currn)
_TERMACT_rule_24;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Text", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_24 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_25 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_25 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_25 _currn;
#ifdef __cplusplus
_currn = new _TPrule_25;
#else
_currn = (_TPPrule_25) TreeNodeAlloc (sizeof (struct _TPrule_25));
#endif
_currn->_prod = RULErule_25;
_SETCOORD(_currn)
_TERMACT_rule_25;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_25 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_26 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_26 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

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
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_27 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_28 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_28 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_28 _currn;
#ifdef __cplusplus
_currn = new _TPrule_28;
#else
_currn = (_TPPrule_28) TreeNodeAlloc (sizeof (struct _TPrule_28));
#endif
_currn->_prod = RULErule_28;
_SETCOORD(_currn)
_TERMACT_rule_28;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_28 */

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkMapPositionrule_29 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkMapPositionrule_29 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_MapPositionrule_29 _new;
#ifdef __cplusplus
	_new = new _TPLST_MapPositionrule_29;
#else
	_new = (_TPPLST_MapPositionrule_29) TreeNodeAlloc (sizeof (struct _TPLST_MapPositionrule_29));
#endif
	_new->_prod = RULELST_MapPositionrule_29;
	_new->_desc1 = (_TSPMapPosition)elem;
	_new->_desc2 = (_TSPLST_MapReorderAlt)_new;
	{_TPPLST_MapPositionrule_29 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_MapPositionrule_29;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkMapTextrule_29 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkMapTextrule_29 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_MapTextrule_29 _new;
#ifdef __cplusplus
	_new = new _TPLST_MapTextrule_29;
#else
	_new = (_TPPLST_MapTextrule_29) TreeNodeAlloc (sizeof (struct _TPLST_MapTextrule_29));
#endif
	_new->_prod = RULELST_MapTextrule_29;
	_new->_desc1 = (_TSPMapText)elem;
	_new->_desc2 = (_TSPLST_MapReorderAlt)_new;
	{_TPPLST_MapTextrule_29 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_MapTextrule_29;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _Elemrule_29 (POSITION *_coordref, NODEPTR t)
#else
static NODEPTR _Elemrule_29 (_coordref, t)
	POSITION *_coordref; NODEPTR t;
#endif
/* coerces t to a list element and returns a single circular list */
{	NODEPTR elem;
	/* check first without then with coercion: */
	if (IsSymb (t, SYMBMapPosition)) 
		return _MkMapPositionrule_29 (_coordref, MkMapPosition (_coordref, t));
	if (IsSymb (t, SYMBMapText)) 
		return _MkMapTextrule_29 (_coordref, MkMapText (_coordref, t));
	message (DEADLY, "a rule_29 list element node can not be generated ",
		0, _coordref);
	return t; /* never reached */
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mk2rule_29 (POSITION *_coordref, NODEPTR l, NODEPTR r)
#else
NODEPTR Mk2rule_29 (_coordref, l, r) POSITION *_coordref; NODEPTR l, r;
#endif
/* make a list of l and r, which may be null, elements, or lists */
{	NODEPTR last;
if (l == NULLNODEPTR) return r;
if (r == NULLNODEPTR) return l;
/* ensure l and r to be lists: */
if (LHSMAP[l->_prod] != SYMBLST_MapReorderAlt)
	l =_Elemrule_29 (_coordref, l);
if (LHSMAP[r->_prod] != SYMBLST_MapReorderAlt)
	r = _Elemrule_29 (_coordref, r);
/* concatenate two lists: */
last = ((NODEPTR)((_TPPLST_0rule_29)r)->_desc2);
((_TPPLST_0rule_29)r)->_desc2 = ((_TPPLST_0rule_29)l)->_desc2;
((_TPPLST_0rule_29)l)->_desc2 = last;
return l;
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_29 (POSITION *_coordref, NODEPTR t)
#else
NODEPTR Mkrule_29 (_coordref, t) POSITION *_coordref; NODEPTR t;
#endif
{	NODEPTR _currn; _TPPrule_29 root;
	_TPPLST_0rule_29 list, remain, p;
/* argument t may be empty, a list element, or a list: */
if (t == NULLNODEPTR)
	remain = (_TPPLST_0rule_29)NULLNODEPTR;
else {	if (LHSMAP[t->_prod] != SYMBLST_MapReorderAlt)
		t = _Elemrule_29 (_coordref, t);
	remain = (_TPPLST_0rule_29)(((_TPPLST_0rule_29) t)->_desc2);
	((_TPPLST_0rule_29) t)->_desc2 = NULLNODEPTR;
}
/* remain is a possibly empty list in reverse order */
/* finalize the list by an empty context: */
#ifdef __cplusplus
list = new _TPLST_0rule_29;
#else
list = (_TPPLST_0rule_29) TreeNodeAlloc (sizeof (struct _TPLST_0rule_29));
#endif
list->_prod = RULELST_0rule_29;
list->_desc1 = NULLNODEPTR;
list->_desc2 = NULLNODEPTR;
_SETCOORD(list)
_currn = (NODEPTR)list;
/* reverse the list and visit its nodes: */
while (remain) {
	p = (_TPPLST_0rule_29)(remain->_desc2);
	remain->_desc2 = (NODEPTR)list;
	list = remain;
	remain = p;
	_currn = (NODEPTR)list;
	/*if (_currn->_prod == RULELST_MapPositionrule_29)
	{_TPPLST_MapPositionrule_29 _currn = _currn;
	 _TERMACT_LST_MapPositionrule_29;
	} this code has been moved to _Elemrule_29*/
	/*if (_currn->_prod == RULELST_MapTextrule_29)
	{_TPPLST_MapTextrule_29 _currn = _currn;
	 _TERMACT_LST_MapTextrule_29;
	} this code has been moved to _Elemrule_29*/
}
/* make root node and visit it: */
#ifdef __cplusplus
root = new _TPrule_29;
#else
root = (_TPPrule_29) TreeNodeAlloc (sizeof (struct _TPrule_29));
#endif
root->_prod = RULErule_29;
root->_desc1 = (_TSPLST_MapReorderAlt)list;
{ _TPPrule_29 _currn = root;
  _SETCOORD(_currn)
  _TERMACT_rule_29;
}
_currn = (NODEPTR)root;
return (NODEPTR)_currn;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkMapElementrule_30 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkMapElementrule_30 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_MapElementrule_30 _new;
#ifdef __cplusplus
	_new = new _TPLST_MapElementrule_30;
#else
	_new = (_TPPLST_MapElementrule_30) TreeNodeAlloc (sizeof (struct _TPLST_MapElementrule_30));
#endif
	_new->_prod = RULELST_MapElementrule_30;
	_new->_desc1 = (_TSPMapElement)elem;
	_new->_desc2 = (_TSPLST_MapAlt)_new;
	{_TPPLST_MapElementrule_30 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_MapElementrule_30;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _Elemrule_30 (POSITION *_coordref, NODEPTR t)
#else
static NODEPTR _Elemrule_30 (_coordref, t)
	POSITION *_coordref; NODEPTR t;
#endif
/* coerces t to a list element and returns a single circular list */
{	NODEPTR elem;
	/* check first without then with coercion: */
	if (IsSymb (t, SYMBMapElement)) 
		return _MkMapElementrule_30 (_coordref, MkMapElement (_coordref, t));
	message (DEADLY, "a rule_30 list element node can not be generated ",
		0, _coordref);
	return t; /* never reached */
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mk2rule_30 (POSITION *_coordref, NODEPTR l, NODEPTR r)
#else
NODEPTR Mk2rule_30 (_coordref, l, r) POSITION *_coordref; NODEPTR l, r;
#endif
/* make a list of l and r, which may be null, elements, or lists */
{	NODEPTR last;
if (l == NULLNODEPTR) return r;
if (r == NULLNODEPTR) return l;
/* ensure l and r to be lists: */
if (LHSMAP[l->_prod] != SYMBLST_MapAlt)
	l =_Elemrule_30 (_coordref, l);
if (LHSMAP[r->_prod] != SYMBLST_MapAlt)
	r = _Elemrule_30 (_coordref, r);
/* concatenate two lists: */
last = ((NODEPTR)((_TPPLST_0rule_30)r)->_desc2);
((_TPPLST_0rule_30)r)->_desc2 = ((_TPPLST_0rule_30)l)->_desc2;
((_TPPLST_0rule_30)l)->_desc2 = last;
return l;
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_30 (POSITION *_coordref, NODEPTR t)
#else
NODEPTR Mkrule_30 (_coordref, t) POSITION *_coordref; NODEPTR t;
#endif
{	NODEPTR _currn; _TPPrule_30 root;
	_TPPLST_0rule_30 list, remain, p;
/* argument t may be empty, a list element, or a list: */
if (t == NULLNODEPTR)
	remain = (_TPPLST_0rule_30)NULLNODEPTR;
else {	if (LHSMAP[t->_prod] != SYMBLST_MapAlt)
		t = _Elemrule_30 (_coordref, t);
	remain = (_TPPLST_0rule_30)(((_TPPLST_0rule_30) t)->_desc2);
	((_TPPLST_0rule_30) t)->_desc2 = NULLNODEPTR;
}
/* remain is a possibly empty list in reverse order */
/* finalize the list by an empty context: */
#ifdef __cplusplus
list = new _TPLST_0rule_30;
#else
list = (_TPPLST_0rule_30) TreeNodeAlloc (sizeof (struct _TPLST_0rule_30));
#endif
list->_prod = RULELST_0rule_30;
list->_desc1 = NULLNODEPTR;
list->_desc2 = NULLNODEPTR;
_SETCOORD(list)
_currn = (NODEPTR)list;
/* reverse the list and visit its nodes: */
while (remain) {
	p = (_TPPLST_0rule_30)(remain->_desc2);
	remain->_desc2 = (NODEPTR)list;
	list = remain;
	remain = p;
	_currn = (NODEPTR)list;
	/*if (_currn->_prod == RULELST_MapElementrule_30)
	{_TPPLST_MapElementrule_30 _currn = _currn;
	 _TERMACT_LST_MapElementrule_30;
	} this code has been moved to _Elemrule_30*/
}
/* make root node and visit it: */
#ifdef __cplusplus
root = new _TPrule_30;
#else
root = (_TPPrule_30) TreeNodeAlloc (sizeof (struct _TPrule_30));
#endif
root->_prod = RULErule_30;
root->_desc1 = (_TSPLST_MapAlt)list;
{ _TPPrule_30 _currn = root;
  _SETCOORD(_currn)
  _TERMACT_rule_30;
}
_currn = (NODEPTR)root;
return (NODEPTR)_currn;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkMapMemberrule_31 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkMapMemberrule_31 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_MapMemberrule_31 _new;
#ifdef __cplusplus
	_new = new _TPLST_MapMemberrule_31;
#else
	_new = (_TPPLST_MapMemberrule_31) TreeNodeAlloc (sizeof (struct _TPLST_MapMemberrule_31));
#endif
	_new->_prod = RULELST_MapMemberrule_31;
	_new->_desc1 = (_TSPMapMember)elem;
	_new->_desc2 = (_TSPLST_MapMembers)_new;
	{_TPPLST_MapMemberrule_31 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_MapMemberrule_31;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _Elemrule_31 (POSITION *_coordref, NODEPTR t)
#else
static NODEPTR _Elemrule_31 (_coordref, t)
	POSITION *_coordref; NODEPTR t;
#endif
/* coerces t to a list element and returns a single circular list */
{	NODEPTR elem;
	/* check first without then with coercion: */
	if (IsSymb (t, SYMBMapMember)) 
		return _MkMapMemberrule_31 (_coordref, MkMapMember (_coordref, t));
	message (DEADLY, "a rule_31 list element node can not be generated ",
		0, _coordref);
	return t; /* never reached */
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mk2rule_31 (POSITION *_coordref, NODEPTR l, NODEPTR r)
#else
NODEPTR Mk2rule_31 (_coordref, l, r) POSITION *_coordref; NODEPTR l, r;
#endif
/* make a list of l and r, which may be null, elements, or lists */
{	NODEPTR last;
if (l == NULLNODEPTR) return r;
if (r == NULLNODEPTR) return l;
/* ensure l and r to be lists: */
if (LHSMAP[l->_prod] != SYMBLST_MapMembers)
	l =_Elemrule_31 (_coordref, l);
if (LHSMAP[r->_prod] != SYMBLST_MapMembers)
	r = _Elemrule_31 (_coordref, r);
/* concatenate two lists: */
last = ((NODEPTR)((_TPPLST_0rule_31)r)->_desc2);
((_TPPLST_0rule_31)r)->_desc2 = ((_TPPLST_0rule_31)l)->_desc2;
((_TPPLST_0rule_31)l)->_desc2 = last;
return l;
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_31 (POSITION *_coordref, NODEPTR t)
#else
NODEPTR Mkrule_31 (_coordref, t) POSITION *_coordref; NODEPTR t;
#endif
{	NODEPTR _currn; _TPPrule_31 root;
	_TPPLST_0rule_31 list, remain, p;
/* argument t may be empty, a list element, or a list: */
if (t == NULLNODEPTR)
	remain = (_TPPLST_0rule_31)NULLNODEPTR;
else {	if (LHSMAP[t->_prod] != SYMBLST_MapMembers)
		t = _Elemrule_31 (_coordref, t);
	remain = (_TPPLST_0rule_31)(((_TPPLST_0rule_31) t)->_desc2);
	((_TPPLST_0rule_31) t)->_desc2 = NULLNODEPTR;
}
/* remain is a possibly empty list in reverse order */
/* finalize the list by an empty context: */
#ifdef __cplusplus
list = new _TPLST_0rule_31;
#else
list = (_TPPLST_0rule_31) TreeNodeAlloc (sizeof (struct _TPLST_0rule_31));
#endif
list->_prod = RULELST_0rule_31;
list->_desc1 = NULLNODEPTR;
list->_desc2 = NULLNODEPTR;
_SETCOORD(list)
_currn = (NODEPTR)list;
/* reverse the list and visit its nodes: */
while (remain) {
	p = (_TPPLST_0rule_31)(remain->_desc2);
	remain->_desc2 = (NODEPTR)list;
	list = remain;
	remain = p;
	_currn = (NODEPTR)list;
	/*if (_currn->_prod == RULELST_MapMemberrule_31)
	{_TPPLST_MapMemberrule_31 _currn = _currn;
	 _TERMACT_LST_MapMemberrule_31;
	} this code has been moved to _Elemrule_31*/
}
/* make root node and visit it: */
#ifdef __cplusplus
root = new _TPrule_31;
#else
root = (_TPPrule_31) TreeNodeAlloc (sizeof (struct _TPrule_31));
#endif
root->_prod = RULErule_31;
root->_desc1 = (_TSPLST_MapMembers)list;
{ _TPPrule_31 _currn = root;
  _SETCOORD(_currn)
  _TERMACT_rule_31;
}
_currn = (NODEPTR)root;
return (NODEPTR)_currn;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkAbsAltrule_32 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkAbsAltrule_32 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_AbsAltrule_32 _new;
#ifdef __cplusplus
	_new = new _TPLST_AbsAltrule_32;
#else
	_new = (_TPPLST_AbsAltrule_32) TreeNodeAlloc (sizeof (struct _TPLST_AbsAltrule_32));
#endif
	_new->_prod = RULELST_AbsAltrule_32;
	_new->_desc1 = (_TSPAbsAlt)elem;
	_new->_desc2 = (_TSPLST_AbsAlts)_new;
	{_TPPLST_AbsAltrule_32 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_AbsAltrule_32;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _Elemrule_32 (POSITION *_coordref, NODEPTR t)
#else
static NODEPTR _Elemrule_32 (_coordref, t)
	POSITION *_coordref; NODEPTR t;
#endif
/* coerces t to a list element and returns a single circular list */
{	NODEPTR elem;
	/* check first without then with coercion: */
	if (IsSymb (t, SYMBAbsAlt)) 
		return _MkAbsAltrule_32 (_coordref, MkAbsAlt (_coordref, t));
	message (DEADLY, "a rule_32 list element node can not be generated ",
		0, _coordref);
	return t; /* never reached */
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mk2rule_32 (POSITION *_coordref, NODEPTR l, NODEPTR r)
#else
NODEPTR Mk2rule_32 (_coordref, l, r) POSITION *_coordref; NODEPTR l, r;
#endif
/* make a list of l and r, which may be null, elements, or lists */
{	NODEPTR last;
if (l == NULLNODEPTR) return r;
if (r == NULLNODEPTR) return l;
/* ensure l and r to be lists: */
if (LHSMAP[l->_prod] != SYMBLST_AbsAlts)
	l =_Elemrule_32 (_coordref, l);
if (LHSMAP[r->_prod] != SYMBLST_AbsAlts)
	r = _Elemrule_32 (_coordref, r);
/* concatenate two lists: */
last = ((NODEPTR)((_TPPLST_0rule_32)r)->_desc2);
((_TPPLST_0rule_32)r)->_desc2 = ((_TPPLST_0rule_32)l)->_desc2;
((_TPPLST_0rule_32)l)->_desc2 = last;
return l;
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_32 (POSITION *_coordref, NODEPTR t)
#else
NODEPTR Mkrule_32 (_coordref, t) POSITION *_coordref; NODEPTR t;
#endif
{	NODEPTR _currn; _TPPrule_32 root;
	_TPPLST_0rule_32 list, remain, p;
/* argument t may be empty, a list element, or a list: */
if (t == NULLNODEPTR)
	remain = (_TPPLST_0rule_32)NULLNODEPTR;
else {	if (LHSMAP[t->_prod] != SYMBLST_AbsAlts)
		t = _Elemrule_32 (_coordref, t);
	remain = (_TPPLST_0rule_32)(((_TPPLST_0rule_32) t)->_desc2);
	((_TPPLST_0rule_32) t)->_desc2 = NULLNODEPTR;
}
/* remain is a possibly empty list in reverse order */
/* finalize the list by an empty context: */
#ifdef __cplusplus
list = new _TPLST_0rule_32;
#else
list = (_TPPLST_0rule_32) TreeNodeAlloc (sizeof (struct _TPLST_0rule_32));
#endif
list->_prod = RULELST_0rule_32;
list->_desc1 = NULLNODEPTR;
list->_desc2 = NULLNODEPTR;
_SETCOORD(list)
_currn = (NODEPTR)list;
/* reverse the list and visit its nodes: */
while (remain) {
	p = (_TPPLST_0rule_32)(remain->_desc2);
	remain->_desc2 = (NODEPTR)list;
	list = remain;
	remain = p;
	_currn = (NODEPTR)list;
	/*if (_currn->_prod == RULELST_AbsAltrule_32)
	{_TPPLST_AbsAltrule_32 _currn = _currn;
	 _TERMACT_LST_AbsAltrule_32;
	} this code has been moved to _Elemrule_32*/
}
/* make root node and visit it: */
#ifdef __cplusplus
root = new _TPrule_32;
#else
root = (_TPPrule_32) TreeNodeAlloc (sizeof (struct _TPrule_32));
#endif
root->_prod = RULErule_32;
root->_desc1 = (_TSPLST_AbsAlts)list;
{ _TPPrule_32 _currn = root;
  _SETCOORD(_currn)
  _TERMACT_rule_32;
}
_currn = (NODEPTR)root;
return (NODEPTR)_currn;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkAbsElementrule_33 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkAbsElementrule_33 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_AbsElementrule_33 _new;
#ifdef __cplusplus
	_new = new _TPLST_AbsElementrule_33;
#else
	_new = (_TPPLST_AbsElementrule_33) TreeNodeAlloc (sizeof (struct _TPLST_AbsElementrule_33));
#endif
	_new->_prod = RULELST_AbsElementrule_33;
	_new->_desc1 = (_TSPAbsElement)elem;
	_new->_desc2 = (_TSPLST_AbsElements)_new;
	{_TPPLST_AbsElementrule_33 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_AbsElementrule_33;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _Elemrule_33 (POSITION *_coordref, NODEPTR t)
#else
static NODEPTR _Elemrule_33 (_coordref, t)
	POSITION *_coordref; NODEPTR t;
#endif
/* coerces t to a list element and returns a single circular list */
{	NODEPTR elem;
	/* check first without then with coercion: */
	if (IsSymb (t, SYMBAbsElement)) 
		return _MkAbsElementrule_33 (_coordref, MkAbsElement (_coordref, t));
	message (DEADLY, "a rule_33 list element node can not be generated ",
		0, _coordref);
	return t; /* never reached */
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mk2rule_33 (POSITION *_coordref, NODEPTR l, NODEPTR r)
#else
NODEPTR Mk2rule_33 (_coordref, l, r) POSITION *_coordref; NODEPTR l, r;
#endif
/* make a list of l and r, which may be null, elements, or lists */
{	NODEPTR last;
if (l == NULLNODEPTR) return r;
if (r == NULLNODEPTR) return l;
/* ensure l and r to be lists: */
if (LHSMAP[l->_prod] != SYMBLST_AbsElements)
	l =_Elemrule_33 (_coordref, l);
if (LHSMAP[r->_prod] != SYMBLST_AbsElements)
	r = _Elemrule_33 (_coordref, r);
/* concatenate two lists: */
last = ((NODEPTR)((_TPPLST_0rule_33)r)->_desc2);
((_TPPLST_0rule_33)r)->_desc2 = ((_TPPLST_0rule_33)l)->_desc2;
((_TPPLST_0rule_33)l)->_desc2 = last;
return l;
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_33 (POSITION *_coordref, NODEPTR t)
#else
NODEPTR Mkrule_33 (_coordref, t) POSITION *_coordref; NODEPTR t;
#endif
{	NODEPTR _currn; _TPPrule_33 root;
	_TPPLST_0rule_33 list, remain, p;
/* argument t may be empty, a list element, or a list: */
if (t == NULLNODEPTR)
	remain = (_TPPLST_0rule_33)NULLNODEPTR;
else {	if (LHSMAP[t->_prod] != SYMBLST_AbsElements)
		t = _Elemrule_33 (_coordref, t);
	remain = (_TPPLST_0rule_33)(((_TPPLST_0rule_33) t)->_desc2);
	((_TPPLST_0rule_33) t)->_desc2 = NULLNODEPTR;
}
/* remain is a possibly empty list in reverse order */
/* finalize the list by an empty context: */
#ifdef __cplusplus
list = new _TPLST_0rule_33;
#else
list = (_TPPLST_0rule_33) TreeNodeAlloc (sizeof (struct _TPLST_0rule_33));
#endif
list->_prod = RULELST_0rule_33;
list->_desc1 = NULLNODEPTR;
list->_desc2 = NULLNODEPTR;
_SETCOORD(list)
_currn = (NODEPTR)list;
/* reverse the list and visit its nodes: */
while (remain) {
	p = (_TPPLST_0rule_33)(remain->_desc2);
	remain->_desc2 = (NODEPTR)list;
	list = remain;
	remain = p;
	_currn = (NODEPTR)list;
	/*if (_currn->_prod == RULELST_AbsElementrule_33)
	{_TPPLST_AbsElementrule_33 _currn = _currn;
	 _TERMACT_LST_AbsElementrule_33;
	} this code has been moved to _Elemrule_33*/
}
/* make root node and visit it: */
#ifdef __cplusplus
root = new _TPrule_33;
#else
root = (_TPPrule_33) TreeNodeAlloc (sizeof (struct _TPrule_33));
#endif
root->_prod = RULErule_33;
root->_desc1 = (_TSPLST_AbsElements)list;
{ _TPPrule_33 _currn = root;
  _SETCOORD(_currn)
  _TERMACT_rule_33;
}
_currn = (NODEPTR)root;
return (NODEPTR)_currn;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkConElementrule_34 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkConElementrule_34 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_ConElementrule_34 _new;
#ifdef __cplusplus
	_new = new _TPLST_ConElementrule_34;
#else
	_new = (_TPPLST_ConElementrule_34) TreeNodeAlloc (sizeof (struct _TPLST_ConElementrule_34));
#endif
	_new->_prod = RULELST_ConElementrule_34;
	_new->_desc1 = (_TSPConElement)elem;
	_new->_desc2 = (_TSPLST_ConAlt)_new;
	{_TPPLST_ConElementrule_34 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_ConElementrule_34;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _Elemrule_34 (POSITION *_coordref, NODEPTR t)
#else
static NODEPTR _Elemrule_34 (_coordref, t)
	POSITION *_coordref; NODEPTR t;
#endif
/* coerces t to a list element and returns a single circular list */
{	NODEPTR elem;
	/* check first without then with coercion: */
	if (IsSymb (t, SYMBConElement)) 
		return _MkConElementrule_34 (_coordref, MkConElement (_coordref, t));
	message (DEADLY, "a rule_34 list element node can not be generated ",
		0, _coordref);
	return t; /* never reached */
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mk2rule_34 (POSITION *_coordref, NODEPTR l, NODEPTR r)
#else
NODEPTR Mk2rule_34 (_coordref, l, r) POSITION *_coordref; NODEPTR l, r;
#endif
/* make a list of l and r, which may be null, elements, or lists */
{	NODEPTR last;
if (l == NULLNODEPTR) return r;
if (r == NULLNODEPTR) return l;
/* ensure l and r to be lists: */
if (LHSMAP[l->_prod] != SYMBLST_ConAlt)
	l =_Elemrule_34 (_coordref, l);
if (LHSMAP[r->_prod] != SYMBLST_ConAlt)
	r = _Elemrule_34 (_coordref, r);
/* concatenate two lists: */
last = ((NODEPTR)((_TPPLST_0rule_34)r)->_desc2);
((_TPPLST_0rule_34)r)->_desc2 = ((_TPPLST_0rule_34)l)->_desc2;
((_TPPLST_0rule_34)l)->_desc2 = last;
return l;
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_34 (POSITION *_coordref, NODEPTR t)
#else
NODEPTR Mkrule_34 (_coordref, t) POSITION *_coordref; NODEPTR t;
#endif
{	NODEPTR _currn; _TPPrule_34 root;
	_TPPLST_0rule_34 list, remain, p;
/* argument t may be empty, a list element, or a list: */
if (t == NULLNODEPTR)
	remain = (_TPPLST_0rule_34)NULLNODEPTR;
else {	if (LHSMAP[t->_prod] != SYMBLST_ConAlt)
		t = _Elemrule_34 (_coordref, t);
	remain = (_TPPLST_0rule_34)(((_TPPLST_0rule_34) t)->_desc2);
	((_TPPLST_0rule_34) t)->_desc2 = NULLNODEPTR;
}
/* remain is a possibly empty list in reverse order */
/* finalize the list by an empty context: */
#ifdef __cplusplus
list = new _TPLST_0rule_34;
#else
list = (_TPPLST_0rule_34) TreeNodeAlloc (sizeof (struct _TPLST_0rule_34));
#endif
list->_prod = RULELST_0rule_34;
list->_desc1 = NULLNODEPTR;
list->_desc2 = NULLNODEPTR;
_SETCOORD(list)
_currn = (NODEPTR)list;
/* reverse the list and visit its nodes: */
while (remain) {
	p = (_TPPLST_0rule_34)(remain->_desc2);
	remain->_desc2 = (NODEPTR)list;
	list = remain;
	remain = p;
	_currn = (NODEPTR)list;
	/*if (_currn->_prod == RULELST_ConElementrule_34)
	{_TPPLST_ConElementrule_34 _currn = _currn;
	 _TERMACT_LST_ConElementrule_34;
	} this code has been moved to _Elemrule_34*/
}
/* make root node and visit it: */
#ifdef __cplusplus
root = new _TPrule_34;
#else
root = (_TPPrule_34) TreeNodeAlloc (sizeof (struct _TPrule_34));
#endif
root->_prod = RULErule_34;
root->_desc1 = (_TSPLST_ConAlt)list;
{ _TPPrule_34 _currn = root;
  _SETCOORD(_currn)
  _TERMACT_rule_34;
}
_currn = (NODEPTR)root;
return (NODEPTR)_currn;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkConProdrule_35 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkConProdrule_35 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_ConProdrule_35 _new;
#ifdef __cplusplus
	_new = new _TPLST_ConProdrule_35;
#else
	_new = (_TPPLST_ConProdrule_35) TreeNodeAlloc (sizeof (struct _TPLST_ConProdrule_35));
#endif
	_new->_prod = RULELST_ConProdrule_35;
	_new->_desc1 = (_TSPConProd)elem;
	_new->_desc2 = (_TSPLST_Source)_new;
	{_TPPLST_ConProdrule_35 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_ConProdrule_35;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkAbsProdrule_35 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkAbsProdrule_35 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_AbsProdrule_35 _new;
#ifdef __cplusplus
	_new = new _TPLST_AbsProdrule_35;
#else
	_new = (_TPPLST_AbsProdrule_35) TreeNodeAlloc (sizeof (struct _TPLST_AbsProdrule_35));
#endif
	_new->_prod = RULELST_AbsProdrule_35;
	_new->_desc1 = (_TSPAbsProd)elem;
	_new->_desc2 = (_TSPLST_Source)_new;
	{_TPPLST_AbsProdrule_35 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_AbsProdrule_35;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkMapSymbolrule_35 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkMapSymbolrule_35 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_MapSymbolrule_35 _new;
#ifdef __cplusplus
	_new = new _TPLST_MapSymbolrule_35;
#else
	_new = (_TPPLST_MapSymbolrule_35) TreeNodeAlloc (sizeof (struct _TPLST_MapSymbolrule_35));
#endif
	_new->_prod = RULELST_MapSymbolrule_35;
	_new->_desc1 = (_TSPMapSymbol)elem;
	_new->_desc2 = (_TSPLST_Source)_new;
	{_TPPLST_MapSymbolrule_35 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_MapSymbolrule_35;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkMapRulerule_35 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkMapRulerule_35 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_MapRulerule_35 _new;
#ifdef __cplusplus
	_new = new _TPLST_MapRulerule_35;
#else
	_new = (_TPPLST_MapRulerule_35) TreeNodeAlloc (sizeof (struct _TPLST_MapRulerule_35));
#endif
	_new->_prod = RULELST_MapRulerule_35;
	_new->_desc1 = (_TSPMapRule)elem;
	_new->_desc2 = (_TSPLST_Source)_new;
	{_TPPLST_MapRulerule_35 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_MapRulerule_35;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkMapChainsrule_35 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkMapChainsrule_35 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_MapChainsrule_35 _new;
#ifdef __cplusplus
	_new = new _TPLST_MapChainsrule_35;
#else
	_new = (_TPPLST_MapChainsrule_35) TreeNodeAlloc (sizeof (struct _TPLST_MapChainsrule_35));
#endif
	_new->_prod = RULELST_MapChainsrule_35;
	_new->_desc1 = (_TSPMapChains)elem;
	_new->_desc2 = (_TSPLST_Source)_new;
	{_TPPLST_MapChainsrule_35 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_MapChainsrule_35;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _MkBottomUpRulerule_35 (POSITION *_coordref, NODEPTR elem)
#else
static NODEPTR _MkBottomUpRulerule_35 (_coordref, elem)
	POSITION *_coordref; NODEPTR elem;
#endif
{
	_TPPLST_BottomUpRulerule_35 _new;
#ifdef __cplusplus
	_new = new _TPLST_BottomUpRulerule_35;
#else
	_new = (_TPPLST_BottomUpRulerule_35) TreeNodeAlloc (sizeof (struct _TPLST_BottomUpRulerule_35));
#endif
	_new->_prod = RULELST_BottomUpRulerule_35;
	_new->_desc1 = (_TSPBottomUpRule)elem;
	_new->_desc2 = (_TSPLST_Source)_new;
	{_TPPLST_BottomUpRulerule_35 _currn = _new;
	 _SETCOORD(_currn)
	 _TERMACT_LST_BottomUpRulerule_35;
	}
	return (NODEPTR)_new;
}

#if defined(__STDC__) || defined(__cplusplus)
static NODEPTR _Elemrule_35 (POSITION *_coordref, NODEPTR t)
#else
static NODEPTR _Elemrule_35 (_coordref, t)
	POSITION *_coordref; NODEPTR t;
#endif
/* coerces t to a list element and returns a single circular list */
{	NODEPTR elem;
	/* check first without then with coercion: */
	if (IsSymb (t, SYMBConProd)) 
		return _MkConProdrule_35 (_coordref, MkConProd (_coordref, t));
	if (IsSymb (t, SYMBAbsProd)) 
		return _MkAbsProdrule_35 (_coordref, MkAbsProd (_coordref, t));
	if (IsSymb (t, SYMBMapSymbol)) 
		return _MkMapSymbolrule_35 (_coordref, MkMapSymbol (_coordref, t));
	if (IsSymb (t, SYMBMapRule)) 
		return _MkMapRulerule_35 (_coordref, MkMapRule (_coordref, t));
	if (IsSymb (t, SYMBMapChains)) 
		return _MkMapChainsrule_35 (_coordref, MkMapChains (_coordref, t));
	if (IsSymb (t, SYMBBottomUpRule)) 
		return _MkBottomUpRulerule_35 (_coordref, MkBottomUpRule (_coordref, t));
	message (DEADLY, "a rule_35 list element node can not be generated ",
		0, _coordref);
	return t; /* never reached */
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mk2rule_35 (POSITION *_coordref, NODEPTR l, NODEPTR r)
#else
NODEPTR Mk2rule_35 (_coordref, l, r) POSITION *_coordref; NODEPTR l, r;
#endif
/* make a list of l and r, which may be null, elements, or lists */
{	NODEPTR last;
if (l == NULLNODEPTR) return r;
if (r == NULLNODEPTR) return l;
/* ensure l and r to be lists: */
if (LHSMAP[l->_prod] != SYMBLST_Source)
	l =_Elemrule_35 (_coordref, l);
if (LHSMAP[r->_prod] != SYMBLST_Source)
	r = _Elemrule_35 (_coordref, r);
/* concatenate two lists: */
last = ((NODEPTR)((_TPPLST_0rule_35)r)->_desc2);
((_TPPLST_0rule_35)r)->_desc2 = ((_TPPLST_0rule_35)l)->_desc2;
((_TPPLST_0rule_35)l)->_desc2 = last;
return l;
}

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_35 (POSITION *_coordref, NODEPTR t)
#else
NODEPTR Mkrule_35 (_coordref, t) POSITION *_coordref; NODEPTR t;
#endif
{	NODEPTR _currn; _TPPrule_35 root;
	_TPPLST_0rule_35 list, remain, p;
/* argument t may be empty, a list element, or a list: */
if (t == NULLNODEPTR)
	remain = (_TPPLST_0rule_35)NULLNODEPTR;
else {	if (LHSMAP[t->_prod] != SYMBLST_Source)
		t = _Elemrule_35 (_coordref, t);
	remain = (_TPPLST_0rule_35)(((_TPPLST_0rule_35) t)->_desc2);
	((_TPPLST_0rule_35) t)->_desc2 = NULLNODEPTR;
}
/* remain is a possibly empty list in reverse order */
/* finalize the list by an empty context: */
#ifdef __cplusplus
list = new _TPLST_0rule_35;
#else
list = (_TPPLST_0rule_35) TreeNodeAlloc (sizeof (struct _TPLST_0rule_35));
#endif
list->_prod = RULELST_0rule_35;
list->_desc1 = NULLNODEPTR;
list->_desc2 = NULLNODEPTR;
_SETCOORD(list)
_currn = (NODEPTR)list;
/* reverse the list and visit its nodes: */
while (remain) {
	p = (_TPPLST_0rule_35)(remain->_desc2);
	remain->_desc2 = (NODEPTR)list;
	list = remain;
	remain = p;
	_currn = (NODEPTR)list;
	/*if (_currn->_prod == RULELST_ConProdrule_35)
	{_TPPLST_ConProdrule_35 _currn = _currn;
	 _TERMACT_LST_ConProdrule_35;
	} this code has been moved to _Elemrule_35*/
	/*if (_currn->_prod == RULELST_AbsProdrule_35)
	{_TPPLST_AbsProdrule_35 _currn = _currn;
	 _TERMACT_LST_AbsProdrule_35;
	} this code has been moved to _Elemrule_35*/
	/*if (_currn->_prod == RULELST_MapSymbolrule_35)
	{_TPPLST_MapSymbolrule_35 _currn = _currn;
	 _TERMACT_LST_MapSymbolrule_35;
	} this code has been moved to _Elemrule_35*/
	/*if (_currn->_prod == RULELST_MapRulerule_35)
	{_TPPLST_MapRulerule_35 _currn = _currn;
	 _TERMACT_LST_MapRulerule_35;
	} this code has been moved to _Elemrule_35*/
	/*if (_currn->_prod == RULELST_MapChainsrule_35)
	{_TPPLST_MapChainsrule_35 _currn = _currn;
	 _TERMACT_LST_MapChainsrule_35;
	} this code has been moved to _Elemrule_35*/
	/*if (_currn->_prod == RULELST_BottomUpRulerule_35)
	{_TPPLST_BottomUpRulerule_35 _currn = _currn;
	 _TERMACT_LST_BottomUpRulerule_35;
	} this code has been moved to _Elemrule_35*/
}
/* make root node and visit it: */
#ifdef __cplusplus
root = new _TPrule_35;
#else
root = (_TPPrule_35) TreeNodeAlloc (sizeof (struct _TPrule_35));
#endif
root->_prod = RULErule_35;
root->_desc1 = (_TSPLST_Source)list;
{ _TPPrule_35 _currn = root;
  _SETCOORD(_currn)
  _TERMACT_rule_35;
}
_currn = (NODEPTR)root;
return (NODEPTR)_currn;
}

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
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_36 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_37 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_37 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Text", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_37 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_38 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_38 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Text", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_38 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_39 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_39 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_39 _currn;
#ifdef __cplusplus
_currn = new _TPrule_39;
#else
_currn = (_TPPrule_39) TreeNodeAlloc (sizeof (struct _TPrule_39));
#endif
_currn->_prod = RULErule_39;
_currn->_desc1 = (_TSPConLHS) MkConLHS (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_39: root of subtree no. 1 can not be made a ConLHS node ", 0, _coordref);
_currn->_desc2 = (_TSPConAlt) MkConAlt (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_39: root of subtree no. 2 can not be made a ConAlt node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_39;
return ( (NODEPTR) _currn);
}/* Mkrule_39 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_003 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_003 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_003 _currn;
#ifdef __cplusplus
_currn = new _TPrule_003;
#else
_currn = (_TPPrule_003) TreeNodeAlloc (sizeof (struct _TPrule_003));
#endif
_currn->_prod = RULErule_003;
_SETCOORD(_currn)
_TERMACT_rule_003;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_003 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_002 (POSITION *_coordref)
#else
NODEPTR Mkrule_002 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_002 _currn;
#ifdef __cplusplus
_currn = new _TPrule_002;
#else
_currn = (_TPPrule_002) TreeNodeAlloc (sizeof (struct _TPrule_002));
#endif
_currn->_prod = RULErule_002;
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
NODEPTR Mkrule_000 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_000 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_000 _currn;
#ifdef __cplusplus
_currn = new _TPrule_000;
#else
_currn = (_TPPrule_000) TreeNodeAlloc (sizeof (struct _TPrule_000));
#endif
_currn->_prod = RULErule_000;
_SETCOORD(_currn)
_TERMACT_rule_000;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_000 */
