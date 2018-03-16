
/* implementation of tree construction functions */

#include "node.h"

#include "nodecode.h"

#include "attrpredef.h"

#include "visitmap.h"

#include "treeact.h"

#ifdef MONITOR
#include "attr_mon_dapto.h"
#include "MONTblStack.h"
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
NODEPTR MkBackendOpt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkBackendOpt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBBackendOpt)) return (_currn);
return(NULLNODEPTR);
}/* MkBackendOpt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkNamesList (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkNamesList (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBNamesList)) return (_currn);
return(NULLNODEPTR);
}/* MkNamesList */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrNames (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrNames (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrNames)) return (_currn);
return(NULLNODEPTR);
}/* MkAttrNames */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrList (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrList (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrList)) return (_currn);
return(NULLNODEPTR);
}/* MkAttrList */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrType (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrType (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrType)) return (_currn);
return(NULLNODEPTR);
}/* MkAttrType */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOptimOpt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOptimOpt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOptimOpt)) return (_currn);
return(NULLNODEPTR);
}/* MkOptimOpt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrSpec)) return (_currn);
return(NULLNODEPTR);
}/* MkAttrSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkArrangeType (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkArrangeType (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBArrangeType)) return (_currn);
return(NULLNODEPTR);
}/* MkArrangeType */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOrderOpt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOrderOpt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOrderOpt)) return (_currn);
return(NULLNODEPTR);
}/* MkOrderOpt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkExpandOpt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkExpandOpt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBExpandOpt)) return (_currn);
return(NULLNODEPTR);
}/* MkExpandOpt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkBackendOpts (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkBackendOpts (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBBackendOpts)) return (_currn);
if (IsSymb (_currn, SYMBBackendOpt)) return (MkBACKS2(_coordref, _currn));
return(NULLNODEPTR);
}/* MkBackendOpts */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOptimOpts (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOptimOpts (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOptimOpts)) return (_currn);
if (IsSymb (_currn, SYMBOptimOpt)) return (MkOPTIMS2(_coordref, _currn));
return(NULLNODEPTR);
}/* MkOptimOpts */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOrderOpts (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOrderOpts (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOrderOpts)) return (_currn);
if (IsSymb (_currn, SYMBOrderOpt)) return (MkORDERS2(_coordref, _currn));
return(NULLNODEPTR);
}/* MkOrderOpts */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkExpandOpts (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkExpandOpts (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBExpandOpts)) return (_currn);
if (IsSymb (_currn, SYMBExpandOpt)) return (MkEXPANDS2(_coordref, _currn));
return(NULLNODEPTR);
}/* MkExpandOpts */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkIdentList (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkIdentList (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBIdentList)) return (_currn);
return(NULLNODEPTR);
}/* MkIdentList */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOption (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOption (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOption)) return (_currn);
return(NULLNODEPTR);
}/* MkOption */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOptions (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOptions (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOptions)) return (_currn);
return(NULLNODEPTR);
}/* MkOptions */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkStart (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkStart (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBStart)) return (_currn);
if (IsSymb (_currn, SYMBOptions)) return (MkSTART(_coordref, _currn));
return(NULLNODEPTR);
}/* MkStart */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkBACKEND2 (POSITION *_coordref, int _TERM1, int _TERM2)
#else
NODEPTR MkBACKEND2 (_coordref, _TERM1, _TERM2)
	POSITION *_coordref;
	int _TERM1;
	int _TERM2;
#endif
{	_TPPBACKEND2 _currn;
#ifdef __cplusplus
_currn = new _TPBACKEND2;
#else
_currn = (_TPPBACKEND2) TreeNodeAlloc (sizeof (struct _TPBACKEND2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEBACKEND2;
_SETCOORD(_currn)
_TERMACT_BACKEND2;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "IntNumber", _TERM2);
#endif

return ( (NODEPTR) _currn);
}/* MkBACKEND2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkBACKEND1 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkBACKEND1 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPBACKEND1 _currn;
#ifdef __cplusplus
_currn = new _TPBACKEND1;
#else
_currn = (_TPPBACKEND1) TreeNodeAlloc (sizeof (struct _TPBACKEND1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEBACKEND1;
_SETCOORD(_currn)
_TERMACT_BACKEND1;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkBACKEND1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkNAMESL2 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkNAMESL2 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPNAMESL2 _currn;
#ifdef __cplusplus
_currn = new _TPNAMESL2;
#else
_currn = (_TPPNAMESL2) TreeNodeAlloc (sizeof (struct _TPNAMESL2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULENAMESL2;
_SETCOORD(_currn)
_TERMACT_NAMESL2;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkNAMESL2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkNAMESL1 (POSITION *_coordref, int _TERM1, NODEPTR _desc1)
#else
NODEPTR MkNAMESL1 (_coordref, _TERM1,_desc1)
	POSITION *_coordref;
	int _TERM1;
	NODEPTR _desc1;
#endif
{	_TPPNAMESL1 _currn;
#ifdef __cplusplus
_currn = new _TPNAMESL1;
#else
_currn = (_TPPNAMESL1) TreeNodeAlloc (sizeof (struct _TPNAMESL1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULENAMESL1;
_currn->_desc1 = (_TSPNamesList) MkNamesList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE NAMESL1: root of subtree no. 1 can not be made a NamesList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_NAMESL1;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkNAMESL1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkATTRNAMES (POSITION *_coordref, int _TERM1, NODEPTR _desc1)
#else
NODEPTR MkATTRNAMES (_coordref, _TERM1,_desc1)
	POSITION *_coordref;
	int _TERM1;
	NODEPTR _desc1;
#endif
{	_TPPATTRNAMES _currn;
#ifdef __cplusplus
_currn = new _TPATTRNAMES;
#else
_currn = (_TPPATTRNAMES) TreeNodeAlloc (sizeof (struct _TPATTRNAMES));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEATTRNAMES;
_currn->_desc1 = (_TSPNamesList) MkNamesList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE ATTRNAMES: root of subtree no. 1 can not be made a NamesList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_ATTRNAMES;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkATTRNAMES */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkATTRS2 (POSITION *_coordref)
#else
NODEPTR MkATTRS2 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPATTRS2 _currn;
#ifdef __cplusplus
_currn = new _TPATTRS2;
#else
_currn = (_TPPATTRS2) TreeNodeAlloc (sizeof (struct _TPATTRS2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEATTRS2;
_SETCOORD(_currn)
_TERMACT_ATTRS2;
return ( (NODEPTR) _currn);
}/* MkATTRS2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkATTRS1 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkATTRS1 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPATTRS1 _currn;
#ifdef __cplusplus
_currn = new _TPATTRS1;
#else
_currn = (_TPPATTRS1) TreeNodeAlloc (sizeof (struct _TPATTRS1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEATTRS1;
_currn->_desc1 = (_TSPAttrNames) MkAttrNames (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE ATTRS1: root of subtree no. 1 can not be made a AttrNames node ", 0, _coordref);
_currn->_desc2 = (_TSPAttrList) MkAttrList (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE ATTRS1: root of subtree no. 2 can not be made a AttrList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_ATTRS1;
return ( (NODEPTR) _currn);
}/* MkATTRS1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkATTRTYPE2 (POSITION *_coordref)
#else
NODEPTR MkATTRTYPE2 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPATTRTYPE2 _currn;
#ifdef __cplusplus
_currn = new _TPATTRTYPE2;
#else
_currn = (_TPPATTRTYPE2) TreeNodeAlloc (sizeof (struct _TPATTRTYPE2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEATTRTYPE2;
_SETCOORD(_currn)
_TERMACT_ATTRTYPE2;
return ( (NODEPTR) _currn);
}/* MkATTRTYPE2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkATTRTYPE1 (POSITION *_coordref, int _TERM1, int _TERM2)
#else
NODEPTR MkATTRTYPE1 (_coordref, _TERM1, _TERM2)
	POSITION *_coordref;
	int _TERM1;
	int _TERM2;
#endif
{	_TPPATTRTYPE1 _currn;
#ifdef __cplusplus
_currn = new _TPATTRTYPE1;
#else
_currn = (_TPPATTRTYPE1) TreeNodeAlloc (sizeof (struct _TPATTRTYPE1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEATTRTYPE1;
_SETCOORD(_currn)
_TERMACT_ATTRTYPE1;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier[1]", _TERM1);
#endif

#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier[2]", _TERM2);
#endif

return ( (NODEPTR) _currn);
}/* MkATTRTYPE1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOPTIM3 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkOPTIM3 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPOPTIM3 _currn;
#ifdef __cplusplus
_currn = new _TPOPTIM3;
#else
_currn = (_TPPOPTIM3) TreeNodeAlloc (sizeof (struct _TPOPTIM3));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEOPTIM3;
_currn->_desc1 = (_TSPAttrType) MkAttrType (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE OPTIM3: root of subtree no. 1 can not be made a AttrType node ", 0, _coordref);
_currn->_desc2 = (_TSPAttrList) MkAttrList (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE OPTIM3: root of subtree no. 2 can not be made a AttrList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_OPTIM3;
return ( (NODEPTR) _currn);
}/* MkOPTIM3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOPTIM2 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkOPTIM2 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPOPTIM2 _currn;
#ifdef __cplusplus
_currn = new _TPOPTIM2;
#else
_currn = (_TPPOPTIM2) TreeNodeAlloc (sizeof (struct _TPOPTIM2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEOPTIM2;
_SETCOORD(_currn)
_TERMACT_OPTIM2;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkOPTIM2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOPTIM1 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkOPTIM1 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPOPTIM1 _currn;
#ifdef __cplusplus
_currn = new _TPOPTIM1;
#else
_currn = (_TPPOPTIM1) TreeNodeAlloc (sizeof (struct _TPOPTIM1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEOPTIM1;
_SETCOORD(_currn)
_TERMACT_OPTIM1;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkOPTIM1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkATTR1 (POSITION *_coordref, int _TERM1, int _TERM2, int _TERM3)
#else
NODEPTR MkATTR1 (_coordref, _TERM1, _TERM2, _TERM3)
	POSITION *_coordref;
	int _TERM1;
	int _TERM2;
	int _TERM3;
#endif
{	_TPPATTR1 _currn;
#ifdef __cplusplus
_currn = new _TPATTR1;
#else
_currn = (_TPPATTR1) TreeNodeAlloc (sizeof (struct _TPATTR1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEATTR1;
_SETCOORD(_currn)
_TERMACT_ATTR1;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier[1]", _TERM1);
#endif

#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "IntNumber", _TERM2);
#endif

#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier[2]", _TERM3);
#endif

return ( (NODEPTR) _currn);
}/* MkATTR1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkARRANGE3 (POSITION *_coordref, int _TERM1, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkARRANGE3 (_coordref, _TERM1,_desc1,_desc2)
	POSITION *_coordref;
	int _TERM1;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPARRANGE3 _currn;
#ifdef __cplusplus
_currn = new _TPARRANGE3;
#else
_currn = (_TPPARRANGE3) TreeNodeAlloc (sizeof (struct _TPARRANGE3));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEARRANGE3;
_currn->_desc1 = (_TSPAttrSpec) MkAttrSpec (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE ARRANGE3: root of subtree no. 1 can not be made a AttrSpec node ", 0, _coordref);
_currn->_desc2 = (_TSPAttrSpec) MkAttrSpec (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE ARRANGE3: root of subtree no. 2 can not be made a AttrSpec node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_ARRANGE3;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkARRANGE3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkARRANGE2 (POSITION *_coordref, int _TERM1, int _TERM2, int _TERM3)
#else
NODEPTR MkARRANGE2 (_coordref, _TERM1, _TERM2, _TERM3)
	POSITION *_coordref;
	int _TERM1;
	int _TERM2;
	int _TERM3;
#endif
{	_TPPARRANGE2 _currn;
#ifdef __cplusplus
_currn = new _TPARRANGE2;
#else
_currn = (_TPPARRANGE2) TreeNodeAlloc (sizeof (struct _TPARRANGE2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEARRANGE2;
_SETCOORD(_currn)
_TERMACT_ARRANGE2;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier[1]", _TERM1);
#endif

#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier[2]", _TERM2);
#endif

#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier[3]", _TERM3);
#endif

return ( (NODEPTR) _currn);
}/* MkARRANGE2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkARRANGE4 (POSITION *_coordref)
#else
NODEPTR MkARRANGE4 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPARRANGE4 _currn;
#ifdef __cplusplus
_currn = new _TPARRANGE4;
#else
_currn = (_TPPARRANGE4) TreeNodeAlloc (sizeof (struct _TPARRANGE4));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEARRANGE4;
_SETCOORD(_currn)
_TERMACT_ARRANGE4;
return ( (NODEPTR) _currn);
}/* MkARRANGE4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkARRANGE1 (POSITION *_coordref)
#else
NODEPTR MkARRANGE1 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPARRANGE1 _currn;
#ifdef __cplusplus
_currn = new _TPARRANGE1;
#else
_currn = (_TPPARRANGE1) TreeNodeAlloc (sizeof (struct _TPARRANGE1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEARRANGE1;
_SETCOORD(_currn)
_TERMACT_ARRANGE1;
return ( (NODEPTR) _currn);
}/* MkARRANGE1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkORDER4 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkORDER4 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPORDER4 _currn;
#ifdef __cplusplus
_currn = new _TPORDER4;
#else
_currn = (_TPPORDER4) TreeNodeAlloc (sizeof (struct _TPORDER4));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEORDER4;
_currn->_desc1 = (_TSPArrangeType) MkArrangeType (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE ORDER4: root of subtree no. 1 can not be made a ArrangeType node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_ORDER4;
return ( (NODEPTR) _currn);
}/* MkORDER4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkORDER3 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkORDER3 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPORDER3 _currn;
#ifdef __cplusplus
_currn = new _TPORDER3;
#else
_currn = (_TPPORDER3) TreeNodeAlloc (sizeof (struct _TPORDER3));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEORDER3;
_SETCOORD(_currn)
_TERMACT_ORDER3;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkORDER3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkORDER2 (POSITION *_coordref, int _TERM1, NODEPTR _desc1)
#else
NODEPTR MkORDER2 (_coordref, _TERM1,_desc1)
	POSITION *_coordref;
	int _TERM1;
	NODEPTR _desc1;
#endif
{	_TPPORDER2 _currn;
#ifdef __cplusplus
_currn = new _TPORDER2;
#else
_currn = (_TPPORDER2) TreeNodeAlloc (sizeof (struct _TPORDER2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEORDER2;
_currn->_desc1 = (_TSPIdentList) MkIdentList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE ORDER2: root of subtree no. 1 can not be made a IdentList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_ORDER2;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkORDER2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkORDER1 (POSITION *_coordref, int _TERM1, int _TERM2)
#else
NODEPTR MkORDER1 (_coordref, _TERM1, _TERM2)
	POSITION *_coordref;
	int _TERM1;
	int _TERM2;
#endif
{	_TPPORDER1 _currn;
#ifdef __cplusplus
_currn = new _TPORDER1;
#else
_currn = (_TPPORDER1) TreeNodeAlloc (sizeof (struct _TPORDER1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEORDER1;
_SETCOORD(_currn)
_TERMACT_ORDER1;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier[1]", _TERM1);
#endif

#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier[2]", _TERM2);
#endif

return ( (NODEPTR) _currn);
}/* MkORDER1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkEXPAND2 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkEXPAND2 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPEXPAND2 _currn;
#ifdef __cplusplus
_currn = new _TPEXPAND2;
#else
_currn = (_TPPEXPAND2) TreeNodeAlloc (sizeof (struct _TPEXPAND2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEEXPAND2;
_SETCOORD(_currn)
_TERMACT_EXPAND2;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkEXPAND2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkEXPAND3 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkEXPAND3 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPEXPAND3 _currn;
#ifdef __cplusplus
_currn = new _TPEXPAND3;
#else
_currn = (_TPPEXPAND3) TreeNodeAlloc (sizeof (struct _TPEXPAND3));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEEXPAND3;
_SETCOORD(_currn)
_TERMACT_EXPAND3;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkEXPAND3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkEXPAND1 (POSITION *_coordref, int _TERM1, int _TERM2)
#else
NODEPTR MkEXPAND1 (_coordref, _TERM1, _TERM2)
	POSITION *_coordref;
	int _TERM1;
	int _TERM2;
#endif
{	_TPPEXPAND1 _currn;
#ifdef __cplusplus
_currn = new _TPEXPAND1;
#else
_currn = (_TPPEXPAND1) TreeNodeAlloc (sizeof (struct _TPEXPAND1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEEXPAND1;
_SETCOORD(_currn)
_TERMACT_EXPAND1;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier[1]", _TERM1);
#endif

#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier[2]", _TERM2);
#endif

return ( (NODEPTR) _currn);
}/* MkEXPAND1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkBACKS2 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkBACKS2 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPBACKS2 _currn;
#ifdef __cplusplus
_currn = new _TPBACKS2;
#else
_currn = (_TPPBACKS2) TreeNodeAlloc (sizeof (struct _TPBACKS2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEBACKS2;
_currn->_desc1 = (_TSPBackendOpt) MkBackendOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE BACKS2: root of subtree no. 1 can not be made a BackendOpt node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_BACKS2;
return ( (NODEPTR) _currn);
}/* MkBACKS2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkBACKS1 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkBACKS1 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPBACKS1 _currn;
#ifdef __cplusplus
_currn = new _TPBACKS1;
#else
_currn = (_TPPBACKS1) TreeNodeAlloc (sizeof (struct _TPBACKS1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEBACKS1;
_currn->_desc1 = (_TSPBackendOpt) MkBackendOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE BACKS1: root of subtree no. 1 can not be made a BackendOpt node ", 0, _coordref);
_currn->_desc2 = (_TSPBackendOpts) MkBackendOpts (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE BACKS1: root of subtree no. 2 can not be made a BackendOpts node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_BACKS1;
return ( (NODEPTR) _currn);
}/* MkBACKS1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOPTIMS2 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkOPTIMS2 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPOPTIMS2 _currn;
#ifdef __cplusplus
_currn = new _TPOPTIMS2;
#else
_currn = (_TPPOPTIMS2) TreeNodeAlloc (sizeof (struct _TPOPTIMS2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEOPTIMS2;
_currn->_desc1 = (_TSPOptimOpt) MkOptimOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE OPTIMS2: root of subtree no. 1 can not be made a OptimOpt node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_OPTIMS2;
return ( (NODEPTR) _currn);
}/* MkOPTIMS2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOPTIMS1 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkOPTIMS1 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPOPTIMS1 _currn;
#ifdef __cplusplus
_currn = new _TPOPTIMS1;
#else
_currn = (_TPPOPTIMS1) TreeNodeAlloc (sizeof (struct _TPOPTIMS1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEOPTIMS1;
_currn->_desc1 = (_TSPOptimOpt) MkOptimOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE OPTIMS1: root of subtree no. 1 can not be made a OptimOpt node ", 0, _coordref);
_currn->_desc2 = (_TSPOptimOpts) MkOptimOpts (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE OPTIMS1: root of subtree no. 2 can not be made a OptimOpts node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_OPTIMS1;
return ( (NODEPTR) _currn);
}/* MkOPTIMS1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkORDERS2 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkORDERS2 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPORDERS2 _currn;
#ifdef __cplusplus
_currn = new _TPORDERS2;
#else
_currn = (_TPPORDERS2) TreeNodeAlloc (sizeof (struct _TPORDERS2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEORDERS2;
_currn->_desc1 = (_TSPOrderOpt) MkOrderOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE ORDERS2: root of subtree no. 1 can not be made a OrderOpt node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_ORDERS2;
return ( (NODEPTR) _currn);
}/* MkORDERS2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkORDERS1 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkORDERS1 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPORDERS1 _currn;
#ifdef __cplusplus
_currn = new _TPORDERS1;
#else
_currn = (_TPPORDERS1) TreeNodeAlloc (sizeof (struct _TPORDERS1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEORDERS1;
_currn->_desc1 = (_TSPOrderOpt) MkOrderOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE ORDERS1: root of subtree no. 1 can not be made a OrderOpt node ", 0, _coordref);
_currn->_desc2 = (_TSPOrderOpts) MkOrderOpts (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE ORDERS1: root of subtree no. 2 can not be made a OrderOpts node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_ORDERS1;
return ( (NODEPTR) _currn);
}/* MkORDERS1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkEXPANDS2 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkEXPANDS2 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPEXPANDS2 _currn;
#ifdef __cplusplus
_currn = new _TPEXPANDS2;
#else
_currn = (_TPPEXPANDS2) TreeNodeAlloc (sizeof (struct _TPEXPANDS2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEEXPANDS2;
_currn->_desc1 = (_TSPExpandOpt) MkExpandOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE EXPANDS2: root of subtree no. 1 can not be made a ExpandOpt node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_EXPANDS2;
return ( (NODEPTR) _currn);
}/* MkEXPANDS2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkEXPANDS1 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkEXPANDS1 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPEXPANDS1 _currn;
#ifdef __cplusplus
_currn = new _TPEXPANDS1;
#else
_currn = (_TPPEXPANDS1) TreeNodeAlloc (sizeof (struct _TPEXPANDS1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEEXPANDS1;
_currn->_desc1 = (_TSPExpandOpt) MkExpandOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE EXPANDS1: root of subtree no. 1 can not be made a ExpandOpt node ", 0, _coordref);
_currn->_desc2 = (_TSPExpandOpts) MkExpandOpts (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE EXPANDS1: root of subtree no. 2 can not be made a ExpandOpts node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_EXPANDS1;
return ( (NODEPTR) _currn);
}/* MkEXPANDS1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkIDENTS2 (POSITION *_coordref)
#else
NODEPTR MkIDENTS2 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPIDENTS2 _currn;
#ifdef __cplusplus
_currn = new _TPIDENTS2;
#else
_currn = (_TPPIDENTS2) TreeNodeAlloc (sizeof (struct _TPIDENTS2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEIDENTS2;
_SETCOORD(_currn)
_TERMACT_IDENTS2;
return ( (NODEPTR) _currn);
}/* MkIDENTS2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkIDENTS1 (POSITION *_coordref, int _TERM1, NODEPTR _desc1)
#else
NODEPTR MkIDENTS1 (_coordref, _TERM1,_desc1)
	POSITION *_coordref;
	int _TERM1;
	NODEPTR _desc1;
#endif
{	_TPPIDENTS1 _currn;
#ifdef __cplusplus
_currn = new _TPIDENTS1;
#else
_currn = (_TPPIDENTS1) TreeNodeAlloc (sizeof (struct _TPIDENTS1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEIDENTS1;
_currn->_desc1 = (_TSPIdentList) MkIdentList (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE IDENTS1: root of subtree no. 1 can not be made a IdentList node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_IDENTS1;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkIDENTS1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOPTBACK (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkOPTBACK (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPOPTBACK _currn;
#ifdef __cplusplus
_currn = new _TPOPTBACK;
#else
_currn = (_TPPOPTBACK) TreeNodeAlloc (sizeof (struct _TPOPTBACK));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEOPTBACK;
_currn->_desc1 = (_TSPBackendOpts) MkBackendOpts (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE OPTBACK: root of subtree no. 1 can not be made a BackendOpts node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_OPTBACK;
return ( (NODEPTR) _currn);
}/* MkOPTBACK */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOPTOPT (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkOPTOPT (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPOPTOPT _currn;
#ifdef __cplusplus
_currn = new _TPOPTOPT;
#else
_currn = (_TPPOPTOPT) TreeNodeAlloc (sizeof (struct _TPOPTOPT));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEOPTOPT;
_currn->_desc1 = (_TSPOptimOpts) MkOptimOpts (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE OPTOPT: root of subtree no. 1 can not be made a OptimOpts node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_OPTOPT;
return ( (NODEPTR) _currn);
}/* MkOPTOPT */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOPTORD (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkOPTORD (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPOPTORD _currn;
#ifdef __cplusplus
_currn = new _TPOPTORD;
#else
_currn = (_TPPOPTORD) TreeNodeAlloc (sizeof (struct _TPOPTORD));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEOPTORD;
_currn->_desc1 = (_TSPOrderOpts) MkOrderOpts (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE OPTORD: root of subtree no. 1 can not be made a OrderOpts node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_OPTORD;
return ( (NODEPTR) _currn);
}/* MkOPTORD */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOPTEXP (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkOPTEXP (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPOPTEXP _currn;
#ifdef __cplusplus
_currn = new _TPOPTEXP;
#else
_currn = (_TPPOPTEXP) TreeNodeAlloc (sizeof (struct _TPOPTEXP));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEOPTEXP;
_currn->_desc1 = (_TSPExpandOpts) MkExpandOpts (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE OPTEXP: root of subtree no. 1 can not be made a ExpandOpts node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_OPTEXP;
return ( (NODEPTR) _currn);
}/* MkOPTEXP */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOPTIONS2 (POSITION *_coordref)
#else
NODEPTR MkOPTIONS2 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPOPTIONS2 _currn;
#ifdef __cplusplus
_currn = new _TPOPTIONS2;
#else
_currn = (_TPPOPTIONS2) TreeNodeAlloc (sizeof (struct _TPOPTIONS2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEOPTIONS2;
_SETCOORD(_currn)
_TERMACT_OPTIONS2;
return ( (NODEPTR) _currn);
}/* MkOPTIONS2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOPTIONS1 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkOPTIONS1 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPOPTIONS1 _currn;
#ifdef __cplusplus
_currn = new _TPOPTIONS1;
#else
_currn = (_TPPOPTIONS1) TreeNodeAlloc (sizeof (struct _TPOPTIONS1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULEOPTIONS1;
_currn->_desc1 = (_TSPOption) MkOption (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE OPTIONS1: root of subtree no. 1 can not be made a Option node ", 0, _coordref);
_currn->_desc2 = (_TSPOptions) MkOptions (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE OPTIONS1: root of subtree no. 2 can not be made a Options node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_OPTIONS1;
return ( (NODEPTR) _currn);
}/* MkOPTIONS1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSTART (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkSTART (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPSTART _currn;
#ifdef __cplusplus
_currn = new _TPSTART;
#else
_currn = (_TPPSTART) TreeNodeAlloc (sizeof (struct _TPSTART));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULESTART;
_currn->_desc1 = (_TSPOptions) MkOptions (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE START: root of subtree no. 1 can not be made a Options node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_START;
return ( (NODEPTR) _currn);
}/* MkSTART */
