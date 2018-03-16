
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
NODEPTR MkSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSpec)) return (_currn);
if (IsSymb (_currn, SYMBAttrSpec)) return (Mkrule_112(_coordref, _currn));
if (IsSymb (_currn, SYMBChainSpec)) return (Mkrule_113(_coordref, _currn));
if (IsSymb (_currn, SYMBRuleSpec)) return (Mkrule_114(_coordref, _currn));
if (IsSymb (_currn, SYMBSymAttrSpec)) return (Mkrule_117(_coordref, _currn));
if (IsSymb (_currn, SYMBSymCompSpec)) return (Mkrule_118(_coordref, _currn));
if (IsSymb (_currn, SYMBTermSpec)) return (Mkrule_119(_coordref, _currn));
return(NULLNODEPTR);
}/* MkSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkShieldSyms (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkShieldSyms (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBShieldSyms)) return (_currn);
if (IsSymb (_currn, SYMBSymbolId)) return (Mkrule_109(_coordref, _currn));
if (IsSymb (_currn, SYMBShieldSym)) return (Mkrule_109(_coordref, _currn));
return(NULLNODEPTR);
}/* MkShieldSyms */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkShieldSym (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkShieldSym (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBShieldSym)) return (_currn);
if (IsSymb (_currn, SYMBSymbolId)) return (Mkrule_111(_coordref, _currn));
return(NULLNODEPTR);
}/* MkShieldSym */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkShieldClause (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkShieldClause (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBShieldClause)) return (_currn);
if (IsSymb (_currn, SYMBSymbolId)) return (Mkrule_106(_coordref, _currn));
if (IsSymb (_currn, SYMBShieldSym)) return (Mkrule_106(_coordref, _currn));
return(NULLNODEPTR);
}/* MkShieldClause */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkShield (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkShield (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBShield)) return (_currn);
return(NULLNODEPTR);
}/* MkShield */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSubtree (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSubtree (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSubtree)) return (_currn);
if (IsSymb (_currn, SYMBSymOcc)) return (Mkrule_121(_coordref, _currn));
return(NULLNODEPTR);
}/* MkSubtree */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRemoteClause (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRemoteClause (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRemoteClause)) return (_currn);
if (IsSymb (_currn, SYMBRemoteAttr)) return (Mkrule_97(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRemoteClause */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRemoteAttr (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRemoteAttr (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRemoteAttr)) return (_currn);
return(NULLNODEPTR);
}/* MkRemoteAttr */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRemoteAttrs (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRemoteAttrs (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRemoteAttrs)) return (_currn);
if (IsSymb (_currn, SYMBRemoteAttr)) return (Mkrule_94(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRemoteAttrs */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkParams (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkParams (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBParams)) return (_currn);
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_90(_coordref, _currn));
if (IsSymb (_currn, SYMBRemoteExpression)) return (Mkrule_90(_coordref, _currn));
if (IsSymb (_currn, SYMBRhsAttrs)) return (Mkrule_90(_coordref, _currn));
if (IsSymb (_currn, SYMBSymbolRef)) return (Mkrule_90(_coordref, _currn));
if (IsSymb (_currn, SYMBExpression)) return (Mkrule_90(_coordref, _currn));
if (IsSymb (_currn, SYMBParam)) return (Mkrule_90(_coordref, _currn));
if (IsSymb (_currn, SYMBExpressionDep)) return (Mkrule_90(_coordref, _currn));
return(NULLNODEPTR);
}/* MkParams */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkParam (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkParam (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBParam)) return (_currn);
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_87(_coordref, _currn));
if (IsSymb (_currn, SYMBRemoteExpression)) return (Mkrule_87(_coordref, _currn));
if (IsSymb (_currn, SYMBRhsAttrs)) return (Mkrule_87(_coordref, _currn));
if (IsSymb (_currn, SYMBSymbolRef)) return (Mkrule_87(_coordref, _currn));
if (IsSymb (_currn, SYMBExpression)) return (Mkrule_87(_coordref, _currn));
if (IsSymb (_currn, SYMBExpressionDep)) return (Mkrule_87(_coordref, _currn));
return(NULLNODEPTR);
}/* MkParam */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkInheritSym (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkInheritSym (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBInheritSym)) return (_currn);
if (IsSymb (_currn, SYMBSymbolId)) return (Mkrule_85(_coordref, _currn));
return(NULLNODEPTR);
}/* MkInheritSym */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkInheritSyms (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkInheritSyms (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBInheritSyms)) return (_currn);
if (IsSymb (_currn, SYMBInheritSym)) return (Mkrule_83(_coordref, _currn));
if (IsSymb (_currn, SYMBSymbolId)) return (Mkrule_83(_coordref, _currn));
return(NULLNODEPTR);
}/* MkInheritSyms */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG1 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG1 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG1)) return (_currn);
if (IsSymb (_currn, SYMBSymbolDefId)) return (Mkrule_78(_coordref, _currn));
return(NULLNODEPTR);
}/* MkG1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkParamsOpt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkParamsOpt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBParamsOpt)) return (_currn);
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_89(_coordref, _currn));
if (IsSymb (_currn, SYMBRemoteExpression)) return (Mkrule_89(_coordref, _currn));
if (IsSymb (_currn, SYMBRhsAttrs)) return (Mkrule_89(_coordref, _currn));
if (IsSymb (_currn, SYMBSymbolRef)) return (Mkrule_89(_coordref, _currn));
if (IsSymb (_currn, SYMBExpression)) return (Mkrule_89(_coordref, _currn));
if (IsSymb (_currn, SYMBParam)) return (Mkrule_89(_coordref, _currn));
if (IsSymb (_currn, SYMBParams)) return (Mkrule_89(_coordref, _currn));
if (IsSymb (_currn, SYMBExpressionDep)) return (Mkrule_89(_coordref, _currn));
return(NULLNODEPTR);
}/* MkParamsOpt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkExpression (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkExpression (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBExpression)) return (_currn);
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_66(_coordref, _currn));
if (IsSymb (_currn, SYMBRemoteExpression)) return (Mkrule_74(_coordref, _currn));
if (IsSymb (_currn, SYMBRhsAttrs)) return (Mkrule_75(_coordref, _currn));
if (IsSymb (_currn, SYMBSymbolRef)) return (Mkrule_76(_coordref, _currn));
return(NULLNODEPTR);
}/* MkExpression */

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
NODEPTR MkDependence (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDependence (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDependence)) return (_currn);
if (IsSymb (_currn, SYMBDepAttr)) return (Mkrule_62(_coordref, _currn));
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_62(_coordref, _currn));
if (IsSymb (_currn, SYMBRemoteExpression)) return (Mkrule_62(_coordref, _currn));
if (IsSymb (_currn, SYMBRhsAttrs)) return (Mkrule_62(_coordref, _currn));
return(NULLNODEPTR);
}/* MkDependence */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDepClause (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDepClause (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDepClause)) return (_currn);
return(NULLNODEPTR);
}/* MkDepClause */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDepAttrs (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDepAttrs (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDepAttrs)) return (_currn);
if (IsSymb (_currn, SYMBDepAttr)) return (Mkrule_58(_coordref, _currn));
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_58(_coordref, _currn));
if (IsSymb (_currn, SYMBRemoteExpression)) return (Mkrule_58(_coordref, _currn));
if (IsSymb (_currn, SYMBRhsAttrs)) return (Mkrule_58(_coordref, _currn));
return(NULLNODEPTR);
}/* MkDepAttrs */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRhsAttrs (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRhsAttrs (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRhsAttrs)) return (_currn);
return(NULLNODEPTR);
}/* MkRhsAttrs */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRemoteExpression (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRemoteExpression (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRemoteExpression)) return (_currn);
return(NULLNODEPTR);
}/* MkRemoteExpression */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDepAttr (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDepAttr (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDepAttr)) return (_currn);
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_55(_coordref, _currn));
if (IsSymb (_currn, SYMBRemoteExpression)) return (Mkrule_56(_coordref, _currn));
if (IsSymb (_currn, SYMBRhsAttrs)) return (Mkrule_57(_coordref, _currn));
return(NULLNODEPTR);
}/* MkDepAttr */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPlainComp (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPlainComp (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPlainComp)) return (_currn);
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_92(_coordref, _currn));
if (IsSymb (_currn, SYMBRemoteExpression)) return (Mkrule_92(_coordref, _currn));
if (IsSymb (_currn, SYMBRhsAttrs)) return (Mkrule_92(_coordref, _currn));
if (IsSymb (_currn, SYMBSymbolRef)) return (Mkrule_92(_coordref, _currn));
if (IsSymb (_currn, SYMBExpression)) return (Mkrule_92(_coordref, _currn));
if (IsSymb (_currn, SYMBExpressionDep)) return (Mkrule_92(_coordref, _currn));
if (IsSymb (_currn, SYMBLoop)) return (Mkrule_93(_coordref, _currn));
return(NULLNODEPTR);
}/* MkPlainComp */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkCompute (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkCompute (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBCompute)) return (_currn);
if (IsSymb (_currn, SYMBAttrComp)) return (Mkrule_52(_coordref, _currn));
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_53(_coordref, _currn));
if (IsSymb (_currn, SYMBRemoteExpression)) return (Mkrule_53(_coordref, _currn));
if (IsSymb (_currn, SYMBRhsAttrs)) return (Mkrule_53(_coordref, _currn));
if (IsSymb (_currn, SYMBSymbolRef)) return (Mkrule_53(_coordref, _currn));
if (IsSymb (_currn, SYMBExpression)) return (Mkrule_53(_coordref, _currn));
if (IsSymb (_currn, SYMBExpressionDep)) return (Mkrule_53(_coordref, _currn));
if (IsSymb (_currn, SYMBLoop)) return (Mkrule_53(_coordref, _currn));
if (IsSymb (_currn, SYMBPlainComp)) return (Mkrule_53(_coordref, _currn));
return(NULLNODEPTR);
}/* MkCompute */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkComputation (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkComputation (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBComputation)) return (_currn);
if (IsSymb (_currn, SYMBAttrComp)) return (Mkrule_48(_coordref, _currn));
if (IsSymb (_currn, SYMBCompute)) return (Mkrule_48(_coordref, _currn));
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_48(_coordref, _currn));
if (IsSymb (_currn, SYMBRemoteExpression)) return (Mkrule_48(_coordref, _currn));
if (IsSymb (_currn, SYMBRhsAttrs)) return (Mkrule_48(_coordref, _currn));
if (IsSymb (_currn, SYMBSymbolRef)) return (Mkrule_48(_coordref, _currn));
if (IsSymb (_currn, SYMBExpression)) return (Mkrule_48(_coordref, _currn));
if (IsSymb (_currn, SYMBExpressionDep)) return (Mkrule_48(_coordref, _currn));
if (IsSymb (_currn, SYMBLoop)) return (Mkrule_48(_coordref, _currn));
if (IsSymb (_currn, SYMBPlainComp)) return (Mkrule_48(_coordref, _currn));
return(NULLNODEPTR);
}/* MkComputation */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkComputations (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkComputations (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBComputations)) return (_currn);
return(NULLNODEPTR);
}/* MkComputations */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkChainSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkChainSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBChainSpec)) return (_currn);
return(NULLNODEPTR);
}/* MkChainSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkChainNames (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkChainNames (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBChainNames)) return (_currn);
if (IsSymb (_currn, SYMBChainName)) return (Mkrule_40(_coordref, _currn));
return(NULLNODEPTR);
}/* MkChainNames */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkChainName (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkChainName (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBChainName)) return (_currn);
return(NULLNODEPTR);
}/* MkChainName */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSymOcc (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSymOcc (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSymOcc)) return (_currn);
return(NULLNODEPTR);
}/* MkSymOcc */

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
NODEPTR MkAttrNames (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrNames (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrNames)) return (_currn);
if (IsSymb (_currn, SYMBAttrName)) return (Mkrule_34(_coordref, _currn));
return(NULLNODEPTR);
}/* MkAttrNames */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrName (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrName (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrName)) return (_currn);
return(NULLNODEPTR);
}/* MkAttrName */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrDefs (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrDefs (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrDefs)) return (_currn);
if (IsSymb (_currn, SYMBAttrDef)) return (Mkrule_29(_coordref, _currn));
return(NULLNODEPTR);
}/* MkAttrDefs */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrDefId (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrDefId (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrDefId)) return (_currn);
return(NULLNODEPTR);
}/* MkAttrDefId */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkClass (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkClass (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBClass)) return (_currn);
return(NULLNODEPTR);
}/* MkClass */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrDefIds (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrDefIds (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrDefIds)) return (_currn);
if (IsSymb (_currn, SYMBAttrDefId)) return (Mkrule_27(_coordref, _currn));
return(NULLNODEPTR);
}/* MkAttrDefIds */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrDef)) return (_currn);
return(NULLNODEPTR);
}/* MkAttrDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkLoop (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkLoop (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBLoop)) return (_currn);
return(NULLNODEPTR);
}/* MkLoop */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkExpressionDep (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkExpressionDep (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBExpressionDep)) return (_currn);
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_70(_coordref, _currn));
if (IsSymb (_currn, SYMBRemoteExpression)) return (Mkrule_70(_coordref, _currn));
if (IsSymb (_currn, SYMBRhsAttrs)) return (Mkrule_70(_coordref, _currn));
if (IsSymb (_currn, SYMBSymbolRef)) return (Mkrule_70(_coordref, _currn));
if (IsSymb (_currn, SYMBExpression)) return (Mkrule_70(_coordref, _currn));
return(NULLNODEPTR);
}/* MkExpressionDep */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDefAttr (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDefAttr (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDefAttr)) return (_currn);
if (IsSymb (_currn, SYMBAttr)) return (Mkrule_54(_coordref, _currn));
return(NULLNODEPTR);
}/* MkDefAttr */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrComp (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrComp (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrComp)) return (_currn);
return(NULLNODEPTR);
}/* MkAttrComp */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrUseId (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrUseId (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrUseId)) return (_currn);
return(NULLNODEPTR);
}/* MkAttrUseId */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttr (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttr (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttr)) return (_currn);
return(NULLNODEPTR);
}/* MkAttr */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAsgnTok (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAsgnTok (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAsgnTok)) return (_currn);
return(NULLNODEPTR);
}/* MkAsgnTok */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAlt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAlt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAlt)) return (_currn);
if (IsSymb (_currn, SYMBSyntId)) return (Mkrule_18(_coordref, _currn));
return(NULLNODEPTR);
}/* MkAlt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSpecs (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSpecs (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSpecs)) return (_currn);
return(NULLNODEPTR);
}/* MkSpecs */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAlts (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAlts (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAlts)) return (_currn);
if (IsSymb (_currn, SYMBAlt)) return (Mkrule_16(_coordref, _currn));
if (IsSymb (_currn, SYMBSyntId)) return (Mkrule_16(_coordref, _currn));
return(NULLNODEPTR);
}/* MkAlts */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSyntUnits (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSyntUnits (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSyntUnits)) return (_currn);
return(NULLNODEPTR);
}/* MkSyntUnits */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRuleSpecId (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRuleSpecId (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRuleSpecId)) return (_currn);
if (IsSymb (_currn, SYMBRuleId)) return (Mkrule_4(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRuleSpecId */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRuleSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRuleSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRuleSpec)) return (_currn);
return(NULLNODEPTR);
}/* MkRuleSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSyntUnit (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSyntUnit (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSyntUnit)) return (_currn);
if (IsSymb (_currn, SYMBSyntId)) return (Mkrule_136(_coordref, _currn));
if (IsSymb (_currn, SYMBSyntLit)) return (Mkrule_137(_coordref, _currn));
return(NULLNODEPTR);
}/* MkSyntUnit */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSyntLit (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSyntLit (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSyntLit)) return (_currn);
return(NULLNODEPTR);
}/* MkSyntLit */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkProduction (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkProduction (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBProduction)) return (_currn);
return(NULLNODEPTR);
}/* MkProduction */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkCompPart (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkCompPart (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBCompPart)) return (_currn);
return(NULLNODEPTR);
}/* MkCompPart */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkInheritOpt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkInheritOpt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBInheritOpt)) return (_currn);
return(NULLNODEPTR);
}/* MkInheritOpt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttrDefsOpt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttrDefsOpt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttrDefsOpt)) return (_currn);
if (IsSymb (_currn, SYMBAttrDef)) return (Mkrule_32(_coordref, _currn));
if (IsSymb (_currn, SYMBAttrDefs)) return (Mkrule_32(_coordref, _currn));
return(NULLNODEPTR);
}/* MkAttrDefsOpt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSymbolDefIds (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSymbolDefIds (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSymbolDefIds)) return (_currn);
if (IsSymb (_currn, SYMBSymbolDefId)) return (Mkrule_123(_coordref, _currn));
if (IsSymb (_currn, SYMBG1)) return (Mkrule_123(_coordref, _currn));
return(NULLNODEPTR);
}/* MkSymbolDefIds */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSymClass (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSymClass (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSymClass)) return (_currn);
return(NULLNODEPTR);
}/* MkSymClass */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTermSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTermSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTermSpec)) return (_currn);
return(NULLNODEPTR);
}/* MkTermSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSymCompSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSymCompSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSymCompSpec)) return (_currn);
return(NULLNODEPTR);
}/* MkSymCompSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSymAttrSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSymAttrSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSymAttrSpec)) return (_currn);
return(NULLNODEPTR);
}/* MkSymAttrSpec */

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
NODEPTR MkSymbolRef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSymbolRef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSymbolRef)) return (_currn);
return(NULLNODEPTR);
}/* MkSymbolRef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAG (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAG (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAG)) return (_currn);
if (IsSymb (_currn, SYMBSpecs)) return (Mkrule_14(_coordref, _currn));
return(NULLNODEPTR);
}/* MkAG */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRuleId (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRuleId (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRuleId)) return (_currn);
return(NULLNODEPTR);
}/* MkRuleId */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTypeId (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTypeId (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTypeId)) return (_currn);
return(NULLNODEPTR);
}/* MkTypeId */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSyntId (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSyntId (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSyntId)) return (_currn);
return(NULLNODEPTR);
}/* MkSyntId */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSymbolId (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSymbolId (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSymbolId)) return (_currn);
return(NULLNODEPTR);
}/* MkSymbolId */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSymbolDefId (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSymbolDefId (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSymbolDefId)) return (_currn);
return(NULLNODEPTR);
}/* MkSymbolDefId */

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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_1;
_currn->_desc1 = (_TSPSyntId) MkSyntId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_1: root of subtree no. 1 can not be made a SyntId node ", 0, _coordref);
_currn->_desc2 = (_TSPAlts) MkAlts (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_1: root of subtree no. 2 can not be made a Alts node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_1;
return ( (NODEPTR) _currn);
}/* Mkrule_1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_2 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_2 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_2 _currn;
#ifdef __cplusplus
_currn = new _TPrule_2;
#else
_currn = (_TPPrule_2) TreeNodeAlloc (sizeof (struct _TPrule_2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_2;
_currn->_desc1 = (_TSPSyntId) MkSyntId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_2: root of subtree no. 1 can not be made a SyntId node ", 0, _coordref);
_currn->_desc2 = (_TSPSyntUnits) MkSyntUnits (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_2: root of subtree no. 2 can not be made a SyntUnits node ", 0, _coordref);
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_3;
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_4;
_currn->_desc1 = (_TSPRuleId) MkRuleId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_4: root of subtree no. 1 can not be made a RuleId node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_4;
return ( (NODEPTR) _currn);
}/* Mkrule_4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_5 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_5 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_5 _currn;
#ifdef __cplusplus
_currn = new _TPrule_5;
#else
_currn = (_TPPrule_5) TreeNodeAlloc (sizeof (struct _TPrule_5));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_5;
_currn->_desc1 = (_TSPRuleSpecId) MkRuleSpecId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_5: root of subtree no. 1 can not be made a RuleSpecId node ", 0, _coordref);
_currn->_desc2 = (_TSPProduction) MkProduction (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_5: root of subtree no. 2 can not be made a Production node ", 0, _coordref);
_currn->_desc3 = (_TSPCompPart) MkCompPart (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_5: root of subtree no. 3 can not be made a CompPart node ", 0, _coordref);
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_6;
_currn->_desc1 = (_TSPSyntId) MkSyntId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_6: root of subtree no. 1 can not be made a SyntId node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_6;
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_7;
_SETCOORD(_currn)
_TERMACT_rule_7;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "P_String", _TERM1);
#endif

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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_8;
_currn->_desc1 = (_TSPSymbolDefIds) MkSymbolDefIds (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_8: root of subtree no. 1 can not be made a SymbolDefIds node ", 0, _coordref);
_currn->_desc2 = (_TSPTypeId) MkTypeId (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_8: root of subtree no. 2 can not be made a TypeId node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_8;
return ( (NODEPTR) _currn);
}/* Mkrule_8 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_9 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3, NODEPTR _desc4)
#else
NODEPTR Mkrule_9 (_coordref,_desc1,_desc2,_desc3,_desc4)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
	NODEPTR _desc4;
#endif
{	_TPPrule_9 _currn;
#ifdef __cplusplus
_currn = new _TPrule_9;
#else
_currn = (_TPPrule_9) TreeNodeAlloc (sizeof (struct _TPrule_9));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_9;
_currn->_desc1 = (_TSPSymClass) MkSymClass (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 1 can not be made a SymClass node ", 0, _coordref);
_currn->_desc2 = (_TSPSymbolDefId) MkSymbolDefId (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 2 can not be made a SymbolDefId node ", 0, _coordref);
_currn->_desc3 = (_TSPInheritOpt) MkInheritOpt (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 3 can not be made a InheritOpt node ", 0, _coordref);
_currn->_desc4 = (_TSPCompPart) MkCompPart (_coordref, _desc4);	
if (((NODEPTR)_currn->_desc4) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 4 can not be made a CompPart node ", 0, _coordref);
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_10;
_currn->_desc1 = (_TSPSymClass) MkSymClass (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 1 can not be made a SymClass node ", 0, _coordref);
_currn->_desc2 = (_TSPSymbolDefIds) MkSymbolDefIds (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 2 can not be made a SymbolDefIds node ", 0, _coordref);
_currn->_desc3 = (_TSPAttrDefsOpt) MkAttrDefsOpt (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 3 can not be made a AttrDefsOpt node ", 0, _coordref);
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_11;
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_12;
_SETCOORD(_currn)
_TERMACT_rule_12;
return ( (NODEPTR) _currn);
}/* Mkrule_12 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_13 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_13 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_13 _currn;
#ifdef __cplusplus
_currn = new _TPrule_13;
#else
_currn = (_TPPrule_13) TreeNodeAlloc (sizeof (struct _TPrule_13));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_13;
_currn->_desc1 = (_TSPSymbolId) MkSymbolId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_13: root of subtree no. 1 can not be made a SymbolId node ", 0, _coordref);
_currn->_desc2 = (_TSPIndex) MkIndex (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_13: root of subtree no. 2 can not be made a Index node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_13;
return ( (NODEPTR) _currn);
}/* Mkrule_13 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_138 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_138 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_138 _currn;
#ifdef __cplusplus
_currn = new _TPrule_138;
#else
_currn = (_TPPrule_138) TreeNodeAlloc (sizeof (struct _TPrule_138));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_138;
_SETCOORD(_currn)
_TERMACT_rule_138;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_138 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_137 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_137 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_137 _currn;
#ifdef __cplusplus
_currn = new _TPrule_137;
#else
_currn = (_TPPrule_137) TreeNodeAlloc (sizeof (struct _TPrule_137));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_137;
_currn->_desc1 = (_TSPSyntLit) MkSyntLit (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_137: root of subtree no. 1 can not be made a SyntLit node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_137;
return ( (NODEPTR) _currn);
}/* Mkrule_137 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_136 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_136 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_136 _currn;
#ifdef __cplusplus
_currn = new _TPrule_136;
#else
_currn = (_TPPrule_136) TreeNodeAlloc (sizeof (struct _TPrule_136));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_136;
_currn->_desc1 = (_TSPSyntId) MkSyntId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_136: root of subtree no. 1 can not be made a SyntId node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_136;
return ( (NODEPTR) _currn);
}/* Mkrule_136 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_135 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_135 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_135 _currn;
#ifdef __cplusplus
_currn = new _TPrule_135;
#else
_currn = (_TPPrule_135) TreeNodeAlloc (sizeof (struct _TPrule_135));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_135;
_currn->_desc1 = (_TSPSyntUnits) MkSyntUnits (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_135: root of subtree no. 1 can not be made a SyntUnits node ", 0, _coordref);
_currn->_desc2 = (_TSPSyntUnit) MkSyntUnit (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_135: root of subtree no. 2 can not be made a SyntUnit node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_135;
return ( (NODEPTR) _currn);
}/* Mkrule_135 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_134 (POSITION *_coordref)
#else
NODEPTR Mkrule_134 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_134 _currn;
#ifdef __cplusplus
_currn = new _TPrule_134;
#else
_currn = (_TPPrule_134) TreeNodeAlloc (sizeof (struct _TPrule_134));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_134;
_SETCOORD(_currn)
_TERMACT_rule_134;
return ( (NODEPTR) _currn);
}/* Mkrule_134 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_133 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_133 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_133 _currn;
#ifdef __cplusplus
_currn = new _TPrule_133;
#else
_currn = (_TPPrule_133) TreeNodeAlloc (sizeof (struct _TPrule_133));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_133;
_SETCOORD(_currn)
_TERMACT_rule_133;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_133 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_132 (POSITION *_coordref)
#else
NODEPTR Mkrule_132 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_132 _currn;
#ifdef __cplusplus
_currn = new _TPrule_132;
#else
_currn = (_TPPrule_132) TreeNodeAlloc (sizeof (struct _TPrule_132));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_132;
_SETCOORD(_currn)
_TERMACT_rule_132;
return ( (NODEPTR) _currn);
}/* Mkrule_132 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_131 (POSITION *_coordref)
#else
NODEPTR Mkrule_131 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_131 _currn;
#ifdef __cplusplus
_currn = new _TPrule_131;
#else
_currn = (_TPPrule_131) TreeNodeAlloc (sizeof (struct _TPrule_131));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_131;
_SETCOORD(_currn)
_TERMACT_rule_131;
return ( (NODEPTR) _currn);
}/* Mkrule_131 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_130 (POSITION *_coordref)
#else
NODEPTR Mkrule_130 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_130 _currn;
#ifdef __cplusplus
_currn = new _TPrule_130;
#else
_currn = (_TPPrule_130) TreeNodeAlloc (sizeof (struct _TPrule_130));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_130;
_SETCOORD(_currn)
_TERMACT_rule_130;
return ( (NODEPTR) _currn);
}/* Mkrule_130 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_129 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_129 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_129 _currn;
#ifdef __cplusplus
_currn = new _TPrule_129;
#else
_currn = (_TPPrule_129) TreeNodeAlloc (sizeof (struct _TPrule_129));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_129;
_currn->_desc1 = (_TSPSymbolId) MkSymbolId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_129: root of subtree no. 1 can not be made a SymbolId node ", 0, _coordref);
_currn->_desc2 = (_TSPIndex) MkIndex (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_129: root of subtree no. 2 can not be made a Index node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_129;
return ( (NODEPTR) _currn);
}/* Mkrule_129 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_128 (POSITION *_coordref)
#else
NODEPTR Mkrule_128 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_128 _currn;
#ifdef __cplusplus
_currn = new _TPrule_128;
#else
_currn = (_TPPrule_128) TreeNodeAlloc (sizeof (struct _TPrule_128));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_128;
_SETCOORD(_currn)
_TERMACT_rule_128;
return ( (NODEPTR) _currn);
}/* Mkrule_128 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_127 (POSITION *_coordref)
#else
NODEPTR Mkrule_127 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_127 _currn;
#ifdef __cplusplus
_currn = new _TPrule_127;
#else
_currn = (_TPPrule_127) TreeNodeAlloc (sizeof (struct _TPrule_127));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_127;
_SETCOORD(_currn)
_TERMACT_rule_127;
return ( (NODEPTR) _currn);
}/* Mkrule_127 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_126 (POSITION *_coordref)
#else
NODEPTR Mkrule_126 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_126 _currn;
#ifdef __cplusplus
_currn = new _TPrule_126;
#else
_currn = (_TPPrule_126) TreeNodeAlloc (sizeof (struct _TPrule_126));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_126;
_SETCOORD(_currn)
_TERMACT_rule_126;
return ( (NODEPTR) _currn);
}/* Mkrule_126 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_125 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_125 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_125 _currn;
#ifdef __cplusplus
_currn = new _TPrule_125;
#else
_currn = (_TPPrule_125) TreeNodeAlloc (sizeof (struct _TPrule_125));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_125;
_currn->_desc1 = (_TSPIndex) MkIndex (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_125: root of subtree no. 1 can not be made a Index node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_125;
return ( (NODEPTR) _currn);
}/* Mkrule_125 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_124 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_124 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_124 _currn;
#ifdef __cplusplus
_currn = new _TPrule_124;
#else
_currn = (_TPPrule_124) TreeNodeAlloc (sizeof (struct _TPrule_124));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_124;
_SETCOORD(_currn)
_TERMACT_rule_124;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_124 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_123 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_123 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_123 _currn;
#ifdef __cplusplus
_currn = new _TPrule_123;
#else
_currn = (_TPPrule_123) TreeNodeAlloc (sizeof (struct _TPrule_123));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_123;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_123: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_123;
return ( (NODEPTR) _currn);
}/* Mkrule_123 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_122 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_122 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_122 _currn;
#ifdef __cplusplus
_currn = new _TPrule_122;
#else
_currn = (_TPPrule_122) TreeNodeAlloc (sizeof (struct _TPrule_122));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_122;
_SETCOORD(_currn)
_TERMACT_rule_122;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_122 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_121 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_121 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_121 _currn;
#ifdef __cplusplus
_currn = new _TPrule_121;
#else
_currn = (_TPPrule_121) TreeNodeAlloc (sizeof (struct _TPrule_121));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_121;
_currn->_desc1 = (_TSPSymOcc) MkSymOcc (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_121: root of subtree no. 1 can not be made a SymOcc node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_121;
return ( (NODEPTR) _currn);
}/* Mkrule_121 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_120 (POSITION *_coordref)
#else
NODEPTR Mkrule_120 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_120 _currn;
#ifdef __cplusplus
_currn = new _TPrule_120;
#else
_currn = (_TPPrule_120) TreeNodeAlloc (sizeof (struct _TPrule_120));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_120;
_SETCOORD(_currn)
_TERMACT_rule_120;
return ( (NODEPTR) _currn);
}/* Mkrule_120 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_119 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_119 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_119 _currn;
#ifdef __cplusplus
_currn = new _TPrule_119;
#else
_currn = (_TPPrule_119) TreeNodeAlloc (sizeof (struct _TPrule_119));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_119;
_currn->_desc1 = (_TSPTermSpec) MkTermSpec (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_119: root of subtree no. 1 can not be made a TermSpec node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_119;
return ( (NODEPTR) _currn);
}/* Mkrule_119 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_118 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_118 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_118 _currn;
#ifdef __cplusplus
_currn = new _TPrule_118;
#else
_currn = (_TPPrule_118) TreeNodeAlloc (sizeof (struct _TPrule_118));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_118;
_currn->_desc1 = (_TSPSymCompSpec) MkSymCompSpec (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_118: root of subtree no. 1 can not be made a SymCompSpec node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_118;
return ( (NODEPTR) _currn);
}/* Mkrule_118 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_117 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_117 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_117 _currn;
#ifdef __cplusplus
_currn = new _TPrule_117;
#else
_currn = (_TPPrule_117) TreeNodeAlloc (sizeof (struct _TPrule_117));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_117;
_currn->_desc1 = (_TSPSymAttrSpec) MkSymAttrSpec (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_117: root of subtree no. 1 can not be made a SymAttrSpec node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_117;
return ( (NODEPTR) _currn);
}/* Mkrule_117 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_116 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_116 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_116 _currn;
#ifdef __cplusplus
_currn = new _TPrule_116;
#else
_currn = (_TPPrule_116) TreeNodeAlloc (sizeof (struct _TPrule_116));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_116;
_currn->_desc1 = (_TSPSpecs) MkSpecs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_116: root of subtree no. 1 can not be made a Specs node ", 0, _coordref);
_currn->_desc2 = (_TSPSpec) MkSpec (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_116: root of subtree no. 2 can not be made a Spec node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_116;
return ( (NODEPTR) _currn);
}/* Mkrule_116 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_115 (POSITION *_coordref)
#else
NODEPTR Mkrule_115 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_115 _currn;
#ifdef __cplusplus
_currn = new _TPrule_115;
#else
_currn = (_TPPrule_115) TreeNodeAlloc (sizeof (struct _TPrule_115));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_115;
_SETCOORD(_currn)
_TERMACT_rule_115;
return ( (NODEPTR) _currn);
}/* Mkrule_115 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_114 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_114 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_114 _currn;
#ifdef __cplusplus
_currn = new _TPrule_114;
#else
_currn = (_TPPrule_114) TreeNodeAlloc (sizeof (struct _TPrule_114));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_114;
_currn->_desc1 = (_TSPRuleSpec) MkRuleSpec (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_114: root of subtree no. 1 can not be made a RuleSpec node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_114;
return ( (NODEPTR) _currn);
}/* Mkrule_114 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_113 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_113 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_113 _currn;
#ifdef __cplusplus
_currn = new _TPrule_113;
#else
_currn = (_TPPrule_113) TreeNodeAlloc (sizeof (struct _TPrule_113));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_113;
_currn->_desc1 = (_TSPChainSpec) MkChainSpec (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_113: root of subtree no. 1 can not be made a ChainSpec node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_113;
return ( (NODEPTR) _currn);
}/* Mkrule_113 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_112 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_112 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_112 _currn;
#ifdef __cplusplus
_currn = new _TPrule_112;
#else
_currn = (_TPPrule_112) TreeNodeAlloc (sizeof (struct _TPrule_112));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_112;
_currn->_desc1 = (_TSPAttrSpec) MkAttrSpec (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_112: root of subtree no. 1 can not be made a AttrSpec node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_112;
return ( (NODEPTR) _currn);
}/* Mkrule_112 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_111 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_111 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_111 _currn;
#ifdef __cplusplus
_currn = new _TPrule_111;
#else
_currn = (_TPPrule_111) TreeNodeAlloc (sizeof (struct _TPrule_111));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_111;
_currn->_desc1 = (_TSPSymbolId) MkSymbolId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_111: root of subtree no. 1 can not be made a SymbolId node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_111;
return ( (NODEPTR) _currn);
}/* Mkrule_111 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_110 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_110 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_110 _currn;
#ifdef __cplusplus
_currn = new _TPrule_110;
#else
_currn = (_TPPrule_110) TreeNodeAlloc (sizeof (struct _TPrule_110));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_110;
_currn->_desc1 = (_TSPShieldSyms) MkShieldSyms (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_110: root of subtree no. 1 can not be made a ShieldSyms node ", 0, _coordref);
_currn->_desc2 = (_TSPShieldSym) MkShieldSym (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_110: root of subtree no. 2 can not be made a ShieldSym node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_110;
return ( (NODEPTR) _currn);
}/* Mkrule_110 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_109 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_109 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_109 _currn;
#ifdef __cplusplus
_currn = new _TPrule_109;
#else
_currn = (_TPPrule_109) TreeNodeAlloc (sizeof (struct _TPrule_109));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_109;
_currn->_desc1 = (_TSPShieldSym) MkShieldSym (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_109: root of subtree no. 1 can not be made a ShieldSym node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_109;
return ( (NODEPTR) _currn);
}/* Mkrule_109 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_108 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_108 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_108 _currn;
#ifdef __cplusplus
_currn = new _TPrule_108;
#else
_currn = (_TPPrule_108) TreeNodeAlloc (sizeof (struct _TPrule_108));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_108;
_currn->_desc1 = (_TSPShieldClause) MkShieldClause (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_108: root of subtree no. 1 can not be made a ShieldClause node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_108;
return ( (NODEPTR) _currn);
}/* Mkrule_108 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_107 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_107 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_107 _currn;
#ifdef __cplusplus
_currn = new _TPrule_107;
#else
_currn = (_TPPrule_107) TreeNodeAlloc (sizeof (struct _TPrule_107));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_107;
_currn->_desc1 = (_TSPShieldSyms) MkShieldSyms (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_107: root of subtree no. 1 can not be made a ShieldSyms node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_107;
return ( (NODEPTR) _currn);
}/* Mkrule_107 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_106 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_106 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_106 _currn;
#ifdef __cplusplus
_currn = new _TPrule_106;
#else
_currn = (_TPPrule_106) TreeNodeAlloc (sizeof (struct _TPrule_106));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_106;
_currn->_desc1 = (_TSPShieldSym) MkShieldSym (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_106: root of subtree no. 1 can not be made a ShieldSym node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_106;
return ( (NODEPTR) _currn);
}/* Mkrule_106 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_105 (POSITION *_coordref)
#else
NODEPTR Mkrule_105 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_105 _currn;
#ifdef __cplusplus
_currn = new _TPrule_105;
#else
_currn = (_TPPrule_105) TreeNodeAlloc (sizeof (struct _TPrule_105));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_105;
_SETCOORD(_currn)
_TERMACT_rule_105;
return ( (NODEPTR) _currn);
}/* Mkrule_105 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_104 (POSITION *_coordref)
#else
NODEPTR Mkrule_104 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_104 _currn;
#ifdef __cplusplus
_currn = new _TPrule_104;
#else
_currn = (_TPPrule_104) TreeNodeAlloc (sizeof (struct _TPrule_104));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_104;
_SETCOORD(_currn)
_TERMACT_rule_104;
return ( (NODEPTR) _currn);
}/* Mkrule_104 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_103 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_103 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_103 _currn;
#ifdef __cplusplus
_currn = new _TPrule_103;
#else
_currn = (_TPPrule_103) TreeNodeAlloc (sizeof (struct _TPrule_103));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_103;
_SETCOORD(_currn)
_TERMACT_rule_103;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_103 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_102 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_102 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_102 _currn;
#ifdef __cplusplus
_currn = new _TPrule_102;
#else
_currn = (_TPPrule_102) TreeNodeAlloc (sizeof (struct _TPrule_102));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_102;
_SETCOORD(_currn)
_TERMACT_rule_102;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_102 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_101 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3, NODEPTR _desc4)
#else
NODEPTR Mkrule_101 (_coordref,_desc1,_desc2,_desc3,_desc4)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
	NODEPTR _desc4;
#endif
{	_TPPrule_101 _currn;
#ifdef __cplusplus
_currn = new _TPrule_101;
#else
_currn = (_TPPrule_101) TreeNodeAlloc (sizeof (struct _TPrule_101));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_101;
_currn->_desc1 = (_TSPSubtree) MkSubtree (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_101: root of subtree no. 1 can not be made a Subtree node ", 0, _coordref);
_currn->_desc2 = (_TSPRemoteClause) MkRemoteClause (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_101: root of subtree no. 2 can not be made a RemoteClause node ", 0, _coordref);
_currn->_desc3 = (_TSPShield) MkShield (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_101: root of subtree no. 3 can not be made a Shield node ", 0, _coordref);
_currn->_desc4 = (_TSPExpandOpt) MkExpandOpt (_coordref, _desc4);	
if (((NODEPTR)_currn->_desc4) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_101: root of subtree no. 4 can not be made a ExpandOpt node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_101;
return ( (NODEPTR) _currn);
}/* Mkrule_101 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_100 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_100 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_100 _currn;
#ifdef __cplusplus
_currn = new _TPrule_100;
#else
_currn = (_TPPrule_100) TreeNodeAlloc (sizeof (struct _TPrule_100));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_100;
_currn->_desc1 = (_TSPSubtree) MkSubtree (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_100: root of subtree no. 1 can not be made a Subtree node ", 0, _coordref);
_currn->_desc2 = (_TSPRemoteClause) MkRemoteClause (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_100: root of subtree no. 2 can not be made a RemoteClause node ", 0, _coordref);
_currn->_desc3 = (_TSPShield) MkShield (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_100: root of subtree no. 3 can not be made a Shield node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_100;
return ( (NODEPTR) _currn);
}/* Mkrule_100 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_99 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_99 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_99 _currn;
#ifdef __cplusplus
_currn = new _TPrule_99;
#else
_currn = (_TPPrule_99) TreeNodeAlloc (sizeof (struct _TPrule_99));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_99;
_currn->_desc1 = (_TSPRemoteClause) MkRemoteClause (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_99: root of subtree no. 1 can not be made a RemoteClause node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_99;
return ( (NODEPTR) _currn);
}/* Mkrule_99 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_98 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_98 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_98 _currn;
#ifdef __cplusplus
_currn = new _TPrule_98;
#else
_currn = (_TPPrule_98) TreeNodeAlloc (sizeof (struct _TPrule_98));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_98;
_currn->_desc1 = (_TSPRemoteAttrs) MkRemoteAttrs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_98: root of subtree no. 1 can not be made a RemoteAttrs node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_98;
return ( (NODEPTR) _currn);
}/* Mkrule_98 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_97 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_97 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_97 _currn;
#ifdef __cplusplus
_currn = new _TPrule_97;
#else
_currn = (_TPPrule_97) TreeNodeAlloc (sizeof (struct _TPrule_97));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_97;
_currn->_desc1 = (_TSPRemoteAttr) MkRemoteAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_97: root of subtree no. 1 can not be made a RemoteAttr node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_97;
return ( (NODEPTR) _currn);
}/* Mkrule_97 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_96 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_96 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_96 _currn;
#ifdef __cplusplus
_currn = new _TPrule_96;
#else
_currn = (_TPPrule_96) TreeNodeAlloc (sizeof (struct _TPrule_96));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_96;
_currn->_desc1 = (_TSPSymbolId) MkSymbolId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_96: root of subtree no. 1 can not be made a SymbolId node ", 0, _coordref);
_currn->_desc2 = (_TSPAttrUseId) MkAttrUseId (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_96: root of subtree no. 2 can not be made a AttrUseId node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_96;
return ( (NODEPTR) _currn);
}/* Mkrule_96 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_95 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_95 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_95 _currn;
#ifdef __cplusplus
_currn = new _TPrule_95;
#else
_currn = (_TPPrule_95) TreeNodeAlloc (sizeof (struct _TPrule_95));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_95;
_currn->_desc1 = (_TSPRemoteAttr) MkRemoteAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_95: root of subtree no. 1 can not be made a RemoteAttr node ", 0, _coordref);
_currn->_desc2 = (_TSPRemoteAttrs) MkRemoteAttrs (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_95: root of subtree no. 2 can not be made a RemoteAttrs node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_95;
return ( (NODEPTR) _currn);
}/* Mkrule_95 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_94 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_94 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_94 _currn;
#ifdef __cplusplus
_currn = new _TPrule_94;
#else
_currn = (_TPPrule_94) TreeNodeAlloc (sizeof (struct _TPrule_94));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_94;
_currn->_desc1 = (_TSPRemoteAttr) MkRemoteAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_94: root of subtree no. 1 can not be made a RemoteAttr node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_94;
return ( (NODEPTR) _currn);
}/* Mkrule_94 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_93 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_93 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_93 _currn;
#ifdef __cplusplus
_currn = new _TPrule_93;
#else
_currn = (_TPPrule_93) TreeNodeAlloc (sizeof (struct _TPrule_93));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_93;
_currn->_desc1 = (_TSPLoop) MkLoop (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_93: root of subtree no. 1 can not be made a Loop node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_93;
return ( (NODEPTR) _currn);
}/* Mkrule_93 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_92 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_92 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_92 _currn;
#ifdef __cplusplus
_currn = new _TPrule_92;
#else
_currn = (_TPPrule_92) TreeNodeAlloc (sizeof (struct _TPrule_92));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_92;
_currn->_desc1 = (_TSPExpressionDep) MkExpressionDep (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_92: root of subtree no. 1 can not be made a ExpressionDep node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_92;
return ( (NODEPTR) _currn);
}/* Mkrule_92 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_91 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_91 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_91 _currn;
#ifdef __cplusplus
_currn = new _TPrule_91;
#else
_currn = (_TPPrule_91) TreeNodeAlloc (sizeof (struct _TPrule_91));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_91;
_currn->_desc1 = (_TSPParam) MkParam (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_91: root of subtree no. 1 can not be made a Param node ", 0, _coordref);
_currn->_desc2 = (_TSPParams) MkParams (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_91: root of subtree no. 2 can not be made a Params node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_91;
return ( (NODEPTR) _currn);
}/* Mkrule_91 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_90 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_90 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_90 _currn;
#ifdef __cplusplus
_currn = new _TPrule_90;
#else
_currn = (_TPPrule_90) TreeNodeAlloc (sizeof (struct _TPrule_90));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_90;
_currn->_desc1 = (_TSPParam) MkParam (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_90: root of subtree no. 1 can not be made a Param node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_90;
return ( (NODEPTR) _currn);
}/* Mkrule_90 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_89 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_89 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_89 _currn;
#ifdef __cplusplus
_currn = new _TPrule_89;
#else
_currn = (_TPPrule_89) TreeNodeAlloc (sizeof (struct _TPrule_89));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_89;
_currn->_desc1 = (_TSPParams) MkParams (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_89: root of subtree no. 1 can not be made a Params node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_89;
return ( (NODEPTR) _currn);
}/* Mkrule_89 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_88 (POSITION *_coordref)
#else
NODEPTR Mkrule_88 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_88 _currn;
#ifdef __cplusplus
_currn = new _TPrule_88;
#else
_currn = (_TPPrule_88) TreeNodeAlloc (sizeof (struct _TPrule_88));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_88;
_SETCOORD(_currn)
_TERMACT_rule_88;
return ( (NODEPTR) _currn);
}/* Mkrule_88 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_87 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_87 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_87 _currn;
#ifdef __cplusplus
_currn = new _TPrule_87;
#else
_currn = (_TPPrule_87) TreeNodeAlloc (sizeof (struct _TPrule_87));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_87;
_currn->_desc1 = (_TSPExpressionDep) MkExpressionDep (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_87: root of subtree no. 1 can not be made a ExpressionDep node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_87;
return ( (NODEPTR) _currn);
}/* Mkrule_87 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_86 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_86 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_86 _currn;
#ifdef __cplusplus
_currn = new _TPrule_86;
#else
_currn = (_TPPrule_86) TreeNodeAlloc (sizeof (struct _TPrule_86));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_86;
_currn->_desc1 = (_TSPExpressionDep) MkExpressionDep (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_86: root of subtree no. 1 can not be made a ExpressionDep node ", 0, _coordref);
_currn->_desc2 = (_TSPAttr) MkAttr (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_86: root of subtree no. 2 can not be made a Attr node ", 0, _coordref);
_currn->_desc3 = (_TSPExpressionDep) MkExpressionDep (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_86: root of subtree no. 3 can not be made a ExpressionDep node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_86;
return ( (NODEPTR) _currn);
}/* Mkrule_86 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_85 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_85 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_85 _currn;
#ifdef __cplusplus
_currn = new _TPrule_85;
#else
_currn = (_TPPrule_85) TreeNodeAlloc (sizeof (struct _TPrule_85));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_85;
_currn->_desc1 = (_TSPSymbolId) MkSymbolId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_85: root of subtree no. 1 can not be made a SymbolId node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_85;
return ( (NODEPTR) _currn);
}/* Mkrule_85 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_84 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_84 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_84 _currn;
#ifdef __cplusplus
_currn = new _TPrule_84;
#else
_currn = (_TPPrule_84) TreeNodeAlloc (sizeof (struct _TPrule_84));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_84;
_currn->_desc1 = (_TSPInheritSyms) MkInheritSyms (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_84: root of subtree no. 1 can not be made a InheritSyms node ", 0, _coordref);
_currn->_desc2 = (_TSPInheritSym) MkInheritSym (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_84: root of subtree no. 2 can not be made a InheritSym node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_84;
return ( (NODEPTR) _currn);
}/* Mkrule_84 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_83 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_83 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_83 _currn;
#ifdef __cplusplus
_currn = new _TPrule_83;
#else
_currn = (_TPPrule_83) TreeNodeAlloc (sizeof (struct _TPrule_83));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_83;
_currn->_desc1 = (_TSPInheritSym) MkInheritSym (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_83: root of subtree no. 1 can not be made a InheritSym node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_83;
return ( (NODEPTR) _currn);
}/* Mkrule_83 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_82 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_82 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_82 _currn;
#ifdef __cplusplus
_currn = new _TPrule_82;
#else
_currn = (_TPPrule_82) TreeNodeAlloc (sizeof (struct _TPrule_82));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_82;
_currn->_desc1 = (_TSPInheritSyms) MkInheritSyms (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_82: root of subtree no. 1 can not be made a InheritSyms node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_82;
return ( (NODEPTR) _currn);
}/* Mkrule_82 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_81 (POSITION *_coordref)
#else
NODEPTR Mkrule_81 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_81 _currn;
#ifdef __cplusplus
_currn = new _TPrule_81;
#else
_currn = (_TPPrule_81) TreeNodeAlloc (sizeof (struct _TPrule_81));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_81;
_SETCOORD(_currn)
_TERMACT_rule_81;
return ( (NODEPTR) _currn);
}/* Mkrule_81 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_80 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_80 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_80 _currn;
#ifdef __cplusplus
_currn = new _TPrule_80;
#else
_currn = (_TPPrule_80) TreeNodeAlloc (sizeof (struct _TPrule_80));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_80;
_SETCOORD(_currn)
_TERMACT_rule_80;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "C_Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_80 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_79 (POSITION *_coordref)
#else
NODEPTR Mkrule_79 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_79 _currn;
#ifdef __cplusplus
_currn = new _TPrule_79;
#else
_currn = (_TPPrule_79) TreeNodeAlloc (sizeof (struct _TPrule_79));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_79;
_SETCOORD(_currn)
_TERMACT_rule_79;
return ( (NODEPTR) _currn);
}/* Mkrule_79 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_78 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_78 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_78 _currn;
#ifdef __cplusplus
_currn = new _TPrule_78;
#else
_currn = (_TPPrule_78) TreeNodeAlloc (sizeof (struct _TPrule_78));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_78;
_currn->_desc1 = (_TSPSymbolDefId) MkSymbolDefId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_78: root of subtree no. 1 can not be made a SymbolDefId node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_78;
return ( (NODEPTR) _currn);
}/* Mkrule_78 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_77 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_77 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_77 _currn;
#ifdef __cplusplus
_currn = new _TPrule_77;
#else
_currn = (_TPPrule_77) TreeNodeAlloc (sizeof (struct _TPrule_77));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_77;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_77: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_currn->_desc2 = (_TSPSymbolDefId) MkSymbolDefId (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_77: root of subtree no. 2 can not be made a SymbolDefId node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_77;
return ( (NODEPTR) _currn);
}/* Mkrule_77 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_76 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_76 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_76 _currn;
#ifdef __cplusplus
_currn = new _TPrule_76;
#else
_currn = (_TPPrule_76) TreeNodeAlloc (sizeof (struct _TPrule_76));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_76;
_currn->_desc1 = (_TSPSymbolRef) MkSymbolRef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_76: root of subtree no. 1 can not be made a SymbolRef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_76;
return ( (NODEPTR) _currn);
}/* Mkrule_76 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_75 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_75 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_75 _currn;
#ifdef __cplusplus
_currn = new _TPrule_75;
#else
_currn = (_TPPrule_75) TreeNodeAlloc (sizeof (struct _TPrule_75));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_75;
_currn->_desc1 = (_TSPRhsAttrs) MkRhsAttrs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_75: root of subtree no. 1 can not be made a RhsAttrs node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_75;
return ( (NODEPTR) _currn);
}/* Mkrule_75 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_74 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_74 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_74 _currn;
#ifdef __cplusplus
_currn = new _TPrule_74;
#else
_currn = (_TPPrule_74) TreeNodeAlloc (sizeof (struct _TPrule_74));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_74;
_currn->_desc1 = (_TSPRemoteExpression) MkRemoteExpression (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_74: root of subtree no. 1 can not be made a RemoteExpression node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_74;
return ( (NODEPTR) _currn);
}/* Mkrule_74 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_73 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_73 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_73 _currn;
#ifdef __cplusplus
_currn = new _TPrule_73;
#else
_currn = (_TPPrule_73) TreeNodeAlloc (sizeof (struct _TPrule_73));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_73;
_SETCOORD(_currn)
_TERMACT_rule_73;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "P_String", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_73 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_72 (POSITION *_coordref, int _TERM1, NODEPTR _desc1)
#else
NODEPTR Mkrule_72 (_coordref, _TERM1,_desc1)
	POSITION *_coordref;
	int _TERM1;
	NODEPTR _desc1;
#endif
{	_TPPrule_72 _currn;
#ifdef __cplusplus
_currn = new _TPrule_72;
#else
_currn = (_TPPrule_72) TreeNodeAlloc (sizeof (struct _TPrule_72));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_72;
_currn->_desc1 = (_TSPParamsOpt) MkParamsOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_72: root of subtree no. 1 can not be made a ParamsOpt node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_72;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_72 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_71 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_71 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_71 _currn;
#ifdef __cplusplus
_currn = new _TPrule_71;
#else
_currn = (_TPPrule_71) TreeNodeAlloc (sizeof (struct _TPrule_71));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_71;
_currn->_desc1 = (_TSPExpression) MkExpression (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_71: root of subtree no. 1 can not be made a Expression node ", 0, _coordref);
_currn->_desc2 = (_TSPDepClause) MkDepClause (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_71: root of subtree no. 2 can not be made a DepClause node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_71;
return ( (NODEPTR) _currn);
}/* Mkrule_71 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_70 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_70 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_70 _currn;
#ifdef __cplusplus
_currn = new _TPrule_70;
#else
_currn = (_TPPrule_70) TreeNodeAlloc (sizeof (struct _TPrule_70));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_70;
_currn->_desc1 = (_TSPExpression) MkExpression (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_70: root of subtree no. 1 can not be made a Expression node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_70;
return ( (NODEPTR) _currn);
}/* Mkrule_70 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_69 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_69 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_69 _currn;
#ifdef __cplusplus
_currn = new _TPrule_69;
#else
_currn = (_TPPrule_69) TreeNodeAlloc (sizeof (struct _TPrule_69));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_69;
_SETCOORD(_currn)
_TERMACT_rule_69;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "C_String", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_69 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_68 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_68 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_68 _currn;
#ifdef __cplusplus
_currn = new _TPrule_68;
#else
_currn = (_TPPrule_68) TreeNodeAlloc (sizeof (struct _TPrule_68));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_68;
_SETCOORD(_currn)
_TERMACT_rule_68;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "C_Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_68 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_67 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_67 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_67 _currn;
#ifdef __cplusplus
_currn = new _TPrule_67;
#else
_currn = (_TPPrule_67) TreeNodeAlloc (sizeof (struct _TPrule_67));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_67;
_SETCOORD(_currn)
_TERMACT_rule_67;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "C_Float", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_67 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_66 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_66 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_66 _currn;
#ifdef __cplusplus
_currn = new _TPrule_66;
#else
_currn = (_TPPrule_66) TreeNodeAlloc (sizeof (struct _TPrule_66));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_66;
_currn->_desc1 = (_TSPAttr) MkAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_66: root of subtree no. 1 can not be made a Attr node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_66;
return ( (NODEPTR) _currn);
}/* Mkrule_66 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_65 (POSITION *_coordref, NODEPTR _desc1, int _TERM1, int _TERM2, int _TERM3)
#else
NODEPTR Mkrule_65 (_coordref,_desc1, _TERM1, _TERM2, _TERM3)
	POSITION *_coordref;
	NODEPTR _desc1;
	int _TERM1;
	int _TERM2;
	int _TERM3;
#endif
{	_TPPrule_65 _currn;
#ifdef __cplusplus
_currn = new _TPrule_65;
#else
_currn = (_TPPrule_65) TreeNodeAlloc (sizeof (struct _TPrule_65));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_65;
_currn->_desc1 = (_TSPTypeId) MkTypeId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_65: root of subtree no. 1 can not be made a TypeId node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_65;
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
}/* Mkrule_65 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_64 (POSITION *_coordref)
#else
NODEPTR Mkrule_64 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_64 _currn;
#ifdef __cplusplus
_currn = new _TPrule_64;
#else
_currn = (_TPPrule_64) TreeNodeAlloc (sizeof (struct _TPrule_64));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_64;
_SETCOORD(_currn)
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_63;
_currn->_desc1 = (_TSPDepAttrs) MkDepAttrs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_63: root of subtree no. 1 can not be made a DepAttrs node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_63;
return ( (NODEPTR) _currn);
}/* Mkrule_63 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_62 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_62 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_62 _currn;
#ifdef __cplusplus
_currn = new _TPrule_62;
#else
_currn = (_TPPrule_62) TreeNodeAlloc (sizeof (struct _TPrule_62));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_62;
_currn->_desc1 = (_TSPDepAttr) MkDepAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_62: root of subtree no. 1 can not be made a DepAttr node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_62;
return ( (NODEPTR) _currn);
}/* Mkrule_62 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_61 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_61 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_61 _currn;
#ifdef __cplusplus
_currn = new _TPrule_61;
#else
_currn = (_TPPrule_61) TreeNodeAlloc (sizeof (struct _TPrule_61));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_61;
_currn->_desc1 = (_TSPDependence) MkDependence (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_61: root of subtree no. 1 can not be made a Dependence node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_61;
return ( (NODEPTR) _currn);
}/* Mkrule_61 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_60 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_60 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_60 _currn;
#ifdef __cplusplus
_currn = new _TPrule_60;
#else
_currn = (_TPPrule_60) TreeNodeAlloc (sizeof (struct _TPrule_60));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_60;
_currn->_desc1 = (_TSPDependence) MkDependence (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_60: root of subtree no. 1 can not be made a Dependence node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_60;
return ( (NODEPTR) _currn);
}/* Mkrule_60 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_59 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_59 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_59 _currn;
#ifdef __cplusplus
_currn = new _TPrule_59;
#else
_currn = (_TPPrule_59) TreeNodeAlloc (sizeof (struct _TPrule_59));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_59;
_currn->_desc1 = (_TSPDepAttr) MkDepAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_59: root of subtree no. 1 can not be made a DepAttr node ", 0, _coordref);
_currn->_desc2 = (_TSPDepAttrs) MkDepAttrs (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_59: root of subtree no. 2 can not be made a DepAttrs node ", 0, _coordref);
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_58;
_currn->_desc1 = (_TSPDepAttr) MkDepAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_58: root of subtree no. 1 can not be made a DepAttr node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_58;
return ( (NODEPTR) _currn);
}/* Mkrule_58 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_57 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_57 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_57 _currn;
#ifdef __cplusplus
_currn = new _TPrule_57;
#else
_currn = (_TPPrule_57) TreeNodeAlloc (sizeof (struct _TPrule_57));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_57;
_currn->_desc1 = (_TSPRhsAttrs) MkRhsAttrs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_57: root of subtree no. 1 can not be made a RhsAttrs node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_57;
return ( (NODEPTR) _currn);
}/* Mkrule_57 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_56 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_56 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_56 _currn;
#ifdef __cplusplus
_currn = new _TPrule_56;
#else
_currn = (_TPPrule_56) TreeNodeAlloc (sizeof (struct _TPrule_56));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_56;
_currn->_desc1 = (_TSPRemoteExpression) MkRemoteExpression (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_56: root of subtree no. 1 can not be made a RemoteExpression node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_56;
return ( (NODEPTR) _currn);
}/* Mkrule_56 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_55 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_55 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_55 _currn;
#ifdef __cplusplus
_currn = new _TPrule_55;
#else
_currn = (_TPPrule_55) TreeNodeAlloc (sizeof (struct _TPrule_55));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_55;
_currn->_desc1 = (_TSPAttr) MkAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_55: root of subtree no. 1 can not be made a Attr node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_55;
return ( (NODEPTR) _currn);
}/* Mkrule_55 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_54 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_54 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_54 _currn;
#ifdef __cplusplus
_currn = new _TPrule_54;
#else
_currn = (_TPPrule_54) TreeNodeAlloc (sizeof (struct _TPrule_54));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_54;
_currn->_desc1 = (_TSPAttr) MkAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_54: root of subtree no. 1 can not be made a Attr node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_54;
return ( (NODEPTR) _currn);
}/* Mkrule_54 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_53 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_53 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_53 _currn;
#ifdef __cplusplus
_currn = new _TPrule_53;
#else
_currn = (_TPPrule_53) TreeNodeAlloc (sizeof (struct _TPrule_53));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_53;
_currn->_desc1 = (_TSPPlainComp) MkPlainComp (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_53: root of subtree no. 1 can not be made a PlainComp node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_53;
return ( (NODEPTR) _currn);
}/* Mkrule_53 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_52 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_52 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_52 _currn;
#ifdef __cplusplus
_currn = new _TPrule_52;
#else
_currn = (_TPPrule_52) TreeNodeAlloc (sizeof (struct _TPrule_52));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_52;
_currn->_desc1 = (_TSPAttrComp) MkAttrComp (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_52: root of subtree no. 1 can not be made a AttrComp node ", 0, _coordref);
_COPYCOORD(_currn)
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_51;
_currn->_desc1 = (_TSPComputation) MkComputation (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_51: root of subtree no. 1 can not be made a Computation node ", 0, _coordref);
_currn->_desc2 = (_TSPComputations) MkComputations (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_51: root of subtree no. 2 can not be made a Computations node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_51;
return ( (NODEPTR) _currn);
}/* Mkrule_51 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_50 (POSITION *_coordref)
#else
NODEPTR Mkrule_50 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_50 _currn;
#ifdef __cplusplus
_currn = new _TPrule_50;
#else
_currn = (_TPPrule_50) TreeNodeAlloc (sizeof (struct _TPrule_50));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_50;
_SETCOORD(_currn)
_TERMACT_rule_50;
return ( (NODEPTR) _currn);
}/* Mkrule_50 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_49 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_49 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_49 _currn;
#ifdef __cplusplus
_currn = new _TPrule_49;
#else
_currn = (_TPPrule_49) TreeNodeAlloc (sizeof (struct _TPrule_49));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_49;
_currn->_desc1 = (_TSPCompute) MkCompute (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_49: root of subtree no. 1 can not be made a Compute node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_49;
return ( (NODEPTR) _currn);
}/* Mkrule_49 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_48 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_48 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_48 _currn;
#ifdef __cplusplus
_currn = new _TPrule_48;
#else
_currn = (_TPPrule_48) TreeNodeAlloc (sizeof (struct _TPrule_48));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_48;
_currn->_desc1 = (_TSPCompute) MkCompute (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_48: root of subtree no. 1 can not be made a Compute node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_48;
return ( (NODEPTR) _currn);
}/* Mkrule_48 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_47 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_47 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_47 _currn;
#ifdef __cplusplus
_currn = new _TPrule_47;
#else
_currn = (_TPPrule_47) TreeNodeAlloc (sizeof (struct _TPrule_47));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_47;
_currn->_desc1 = (_TSPComputations) MkComputations (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_47: root of subtree no. 1 can not be made a Computations node ", 0, _coordref);
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_46;
_SETCOORD(_currn)
_TERMACT_rule_46;
return ( (NODEPTR) _currn);
}/* Mkrule_46 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_45 (POSITION *_coordref)
#else
NODEPTR Mkrule_45 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_45 _currn;
#ifdef __cplusplus
_currn = new _TPrule_45;
#else
_currn = (_TPPrule_45) TreeNodeAlloc (sizeof (struct _TPrule_45));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_45;
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_44;
_SETCOORD(_currn)
_TERMACT_rule_44;
return ( (NODEPTR) _currn);
}/* Mkrule_44 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_43 (POSITION *_coordref)
#else
NODEPTR Mkrule_43 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_43 _currn;
#ifdef __cplusplus
_currn = new _TPrule_43;
#else
_currn = (_TPPrule_43) TreeNodeAlloc (sizeof (struct _TPrule_43));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_43;
_SETCOORD(_currn)
_TERMACT_rule_43;
return ( (NODEPTR) _currn);
}/* Mkrule_43 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_42 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_42 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_42 _currn;
#ifdef __cplusplus
_currn = new _TPrule_42;
#else
_currn = (_TPPrule_42) TreeNodeAlloc (sizeof (struct _TPrule_42));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_42;
_currn->_desc1 = (_TSPChainNames) MkChainNames (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_42: root of subtree no. 1 can not be made a ChainNames node ", 0, _coordref);
_currn->_desc2 = (_TSPTypeId) MkTypeId (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_42: root of subtree no. 2 can not be made a TypeId node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_42;
return ( (NODEPTR) _currn);
}/* Mkrule_42 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_41 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_41 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_41 _currn;
#ifdef __cplusplus
_currn = new _TPrule_41;
#else
_currn = (_TPPrule_41) TreeNodeAlloc (sizeof (struct _TPrule_41));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_41;
_currn->_desc1 = (_TSPChainNames) MkChainNames (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_41: root of subtree no. 1 can not be made a ChainNames node ", 0, _coordref);
_currn->_desc2 = (_TSPChainName) MkChainName (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_41: root of subtree no. 2 can not be made a ChainName node ", 0, _coordref);
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_40;
_currn->_desc1 = (_TSPChainName) MkChainName (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_40: root of subtree no. 1 can not be made a ChainName node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_40;
return ( (NODEPTR) _currn);
}/* Mkrule_40 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_39 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_39 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_39 _currn;
#ifdef __cplusplus
_currn = new _TPrule_39;
#else
_currn = (_TPPrule_39) TreeNodeAlloc (sizeof (struct _TPrule_39));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_39;
_SETCOORD(_currn)
_TERMACT_rule_39;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_39 */

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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_38;
_SETCOORD(_currn)
_TERMACT_rule_38;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_38 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_37 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_37 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_37 _currn;
#ifdef __cplusplus
_currn = new _TPrule_37;
#else
_currn = (_TPPrule_37) TreeNodeAlloc (sizeof (struct _TPrule_37));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_37;
_currn->_desc1 = (_TSPSymOcc) MkSymOcc (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_37: root of subtree no. 1 can not be made a SymOcc node ", 0, _coordref);
_currn->_desc2 = (_TSPAttrUseId) MkAttrUseId (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_37: root of subtree no. 2 can not be made a AttrUseId node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_37;
return ( (NODEPTR) _currn);
}/* Mkrule_37 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_36 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_36 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_36 _currn;
#ifdef __cplusplus
_currn = new _TPrule_36;
#else
_currn = (_TPPrule_36) TreeNodeAlloc (sizeof (struct _TPrule_36));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_36;
_currn->_desc1 = (_TSPAttrNames) MkAttrNames (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_36: root of subtree no. 1 can not be made a AttrNames node ", 0, _coordref);
_currn->_desc2 = (_TSPTypeId) MkTypeId (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_36: root of subtree no. 2 can not be made a TypeId node ", 0, _coordref);
_currn->_desc3 = (_TSPClass) MkClass (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_36: root of subtree no. 3 can not be made a Class node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_36;
return ( (NODEPTR) _currn);
}/* Mkrule_36 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_35 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_35 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_35 _currn;
#ifdef __cplusplus
_currn = new _TPrule_35;
#else
_currn = (_TPPrule_35) TreeNodeAlloc (sizeof (struct _TPrule_35));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_35;
_currn->_desc1 = (_TSPAttrNames) MkAttrNames (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_35: root of subtree no. 1 can not be made a AttrNames node ", 0, _coordref);
_currn->_desc2 = (_TSPAttrName) MkAttrName (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_35: root of subtree no. 2 can not be made a AttrName node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_35;
return ( (NODEPTR) _currn);
}/* Mkrule_35 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_34 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_34 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_34 _currn;
#ifdef __cplusplus
_currn = new _TPrule_34;
#else
_currn = (_TPPrule_34) TreeNodeAlloc (sizeof (struct _TPrule_34));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_34;
_currn->_desc1 = (_TSPAttrName) MkAttrName (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_34: root of subtree no. 1 can not be made a AttrName node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_34;
return ( (NODEPTR) _currn);
}/* Mkrule_34 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_33 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_33 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_33 _currn;
#ifdef __cplusplus
_currn = new _TPrule_33;
#else
_currn = (_TPPrule_33) TreeNodeAlloc (sizeof (struct _TPrule_33));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_33;
_SETCOORD(_currn)
_TERMACT_rule_33;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_32;
_currn->_desc1 = (_TSPAttrDefs) MkAttrDefs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_32: root of subtree no. 1 can not be made a AttrDefs node ", 0, _coordref);
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_31;
_SETCOORD(_currn)
_TERMACT_rule_31;
return ( (NODEPTR) _currn);
}/* Mkrule_31 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_30 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_30 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_30 _currn;
#ifdef __cplusplus
_currn = new _TPrule_30;
#else
_currn = (_TPPrule_30) TreeNodeAlloc (sizeof (struct _TPrule_30));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_30;
_currn->_desc1 = (_TSPAttrDefs) MkAttrDefs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_30: root of subtree no. 1 can not be made a AttrDefs node ", 0, _coordref);
_currn->_desc2 = (_TSPAttrDef) MkAttrDef (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_30: root of subtree no. 2 can not be made a AttrDef node ", 0, _coordref);
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_29;
_currn->_desc1 = (_TSPAttrDef) MkAttrDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_29: root of subtree no. 1 can not be made a AttrDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_29;
return ( (NODEPTR) _currn);
}/* Mkrule_29 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_28 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_28 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_28 _currn;
#ifdef __cplusplus
_currn = new _TPrule_28;
#else
_currn = (_TPPrule_28) TreeNodeAlloc (sizeof (struct _TPrule_28));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_28;
_currn->_desc1 = (_TSPAttrDefIds) MkAttrDefIds (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_28: root of subtree no. 1 can not be made a AttrDefIds node ", 0, _coordref);
_currn->_desc2 = (_TSPAttrDefId) MkAttrDefId (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_28: root of subtree no. 2 can not be made a AttrDefId node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_28;
return ( (NODEPTR) _currn);
}/* Mkrule_28 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_27 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_27 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_27 _currn;
#ifdef __cplusplus
_currn = new _TPrule_27;
#else
_currn = (_TPPrule_27) TreeNodeAlloc (sizeof (struct _TPrule_27));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_27;
_currn->_desc1 = (_TSPAttrDefId) MkAttrDefId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_27: root of subtree no. 1 can not be made a AttrDefId node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_27;
return ( (NODEPTR) _currn);
}/* Mkrule_27 */

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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_26;
_SETCOORD(_currn)
_TERMACT_rule_26;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Identifier", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_26 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_25 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_25 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_25 _currn;
#ifdef __cplusplus
_currn = new _TPrule_25;
#else
_currn = (_TPPrule_25) TreeNodeAlloc (sizeof (struct _TPrule_25));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_25;
_currn->_desc1 = (_TSPAttrDefIds) MkAttrDefIds (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_25: root of subtree no. 1 can not be made a AttrDefIds node ", 0, _coordref);
_currn->_desc2 = (_TSPTypeId) MkTypeId (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_25: root of subtree no. 2 can not be made a TypeId node ", 0, _coordref);
_currn->_desc3 = (_TSPClass) MkClass (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_25: root of subtree no. 3 can not be made a Class node ", 0, _coordref);
_SETCOORD(_currn)
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_24;
_currn->_desc1 = (_TSPDefAttr) MkDefAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_24: root of subtree no. 1 can not be made a DefAttr node ", 0, _coordref);
_currn->_desc2 = (_TSPLoop) MkLoop (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_24: root of subtree no. 2 can not be made a Loop node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_24;
return ( (NODEPTR) _currn);
}/* Mkrule_24 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_23 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_23 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_23 _currn;
#ifdef __cplusplus
_currn = new _TPrule_23;
#else
_currn = (_TPPrule_23) TreeNodeAlloc (sizeof (struct _TPrule_23));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_23;
_currn->_desc1 = (_TSPDefAttr) MkDefAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_23: root of subtree no. 1 can not be made a DefAttr node ", 0, _coordref);
_currn->_desc2 = (_TSPAsgnTok) MkAsgnTok (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_23: root of subtree no. 2 can not be made a AsgnTok node ", 0, _coordref);
_currn->_desc3 = (_TSPExpressionDep) MkExpressionDep (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_23: root of subtree no. 3 can not be made a ExpressionDep node ", 0, _coordref);
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_22;
_currn->_desc1 = (_TSPDefAttr) MkDefAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_22: root of subtree no. 1 can not be made a DefAttr node ", 0, _coordref);
_currn->_desc2 = (_TSPExpressionDep) MkExpressionDep (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_22: root of subtree no. 2 can not be made a ExpressionDep node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_22;
return ( (NODEPTR) _currn);
}/* Mkrule_22 */

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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_21;
_currn->_desc1 = (_TSPAttrUseId) MkAttrUseId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_21: root of subtree no. 1 can not be made a AttrUseId node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_21;
return ( (NODEPTR) _currn);
}/* Mkrule_21 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_20 (POSITION *_coordref)
#else
NODEPTR Mkrule_20 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_20 _currn;
#ifdef __cplusplus
_currn = new _TPrule_20;
#else
_currn = (_TPPrule_20) TreeNodeAlloc (sizeof (struct _TPrule_20));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_20;
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_19;
_SETCOORD(_currn)
_TERMACT_rule_19;
return ( (NODEPTR) _currn);
}/* Mkrule_19 */

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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_18;
_currn->_desc1 = (_TSPSyntId) MkSyntId (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_18: root of subtree no. 1 can not be made a SyntId node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_18;
return ( (NODEPTR) _currn);
}/* Mkrule_18 */

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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_17;
_currn->_desc1 = (_TSPAlts) MkAlts (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_17: root of subtree no. 1 can not be made a Alts node ", 0, _coordref);
_currn->_desc2 = (_TSPAlt) MkAlt (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_17: root of subtree no. 2 can not be made a Alt node ", 0, _coordref);
_SETCOORD(_currn)
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_16;
_currn->_desc1 = (_TSPAlt) MkAlt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_16: root of subtree no. 1 can not be made a Alt node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_16;
return ( (NODEPTR) _currn);
}/* Mkrule_16 */

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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_15;
_SETCOORD(_currn)
_TERMACT_rule_15;
return ( (NODEPTR) _currn);
}/* Mkrule_15 */

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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_14;
_currn->_desc1 = (_TSPSpecs) MkSpecs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_14: root of subtree no. 1 can not be made a Specs node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_14;
return ( (NODEPTR) _currn);
}/* Mkrule_14 */
