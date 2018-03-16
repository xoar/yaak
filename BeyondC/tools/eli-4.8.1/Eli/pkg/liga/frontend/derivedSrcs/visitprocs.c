
#include "HEAD.h"
#include "err.h"
#include "node.h"
#include "visitprocs.h"
#include "attrpredef.h"

#include "visitmap.h"

#ifdef MONITOR
#include "attr_mon_dapto.h"
#include "liga_dapto.h"
#endif

#ifndef _VisitVarDecl
#define _VisitVarDecl()
#endif

#ifndef _VisitEntry
#define _VisitEntry()
#endif

#ifndef _VisitExit
#define _VisitExit()
#endif


#if defined(__STDC__) || defined(__cplusplus)
#define _CALL_VS_(args) (void (*)args)
#else
#define _CALL_VS_(args) 
#endif
DefTableKey* _IG_incl39;
int* _IG_incl38;
DefTableKeyList* _IG_incl37;
DefTableKey* _IG_incl36;
int* _IG_incl35;
DefTableKey* _IG_incl34;
Environment* _IG_incl33;
int* _IG_incl32;
int* _IG_incl30;
int* _IG_incl31;
DefTableKey* _IG_incl29;
int* _IG_incl28;
Environment* _IG_incl26;
Environment* _IG_incl25;
Environment* _IG_incl24;
Environment* _IG_incl22;
Environment* _IG_incl21;
Environment* _IG_incl20;
Environment* _IG_incl19;
DefTableKey* _IG_incl18;
Environment* _IG_incl17;
int* _IG_incl13;
int* _IG_incl6;
DefTableKey* _IG_incl8;
DefTableKey* _IG_incl4;
PTGNode _AVSpec__const20;
PExprListPtr _AVParam_cPExprListPtr_post;
DefTableKeyListPtr _AVSymbolDefId_cDefTableKeyListPtr_post;
PTGNode _AVComputations__const20;
PTGNode _AVSpecs__const20;
int _AVParam_PExprTakeIt;
PExpr _AVParam_PExprElem;
PExprListPtr _AVParamsOpt_HEAD$48_RuleAttr_203;
PExprList _AVParamsOpt_PExprList;
int _AVDepAttr_PExprTakeIt;
PExpr _AVDepAttr_PExprElem;
PExprList _AVDepClause__PExprauxList;
PExprList _AVDepClause_PExprList;
PExpr _AVExpression_repr;
int _AVExpandOpt_Fct0;
int _AVExpandOpt_Fct1;
int _AVExpandOpt_Fct2;
DefTableKey _AVExpandOpt_Type;
int _AVSubtree_SubtreeNo;
PExpr _AVRemoteExpression_repr;
int _AVRemoteExpression_SubtreeNo;
SymbAttrList _AVRemoteClause_RemoteSet;
DefTableKeyList _AVShield_ShieldSet;
Binding _AVAttrComp__const3;
PExpr _AVAttrComp_repr;
DefTableKey _AVAttrComp_IsChainStart;
PExpr _AVDefAttr_repr;
int _AVDefAttr_hasAccuToken;
int _AVDefAttr_IsUpperSymbComp;
Environment _AVDefAttr_CompScope;
PTGNode _AVCompute_InhComps;
int _AVCompute_Sym;
PExpr _AVPlainComp_repr;
Environment _AVPlainComp_CompScope;
Binding _AVAttrName_Bind;
PExpr _AVLoop_repr;
int _AVAttrDefId_Sym;
Binding _AVChainName_Bind;
int _AVSymOcc_IsDefining;
int _AVSymOcc_AttrClass;
int _AVAttr_IsIterate;
Binding _AVAttrUseId_auxChainBind_RuleAttr_149;
DefTableKey _AVAttrUseId_auxChainKey_RuleAttr_149;
Binding _AVAttrUseId_Bind;
DefTableKey _AVAttrUseId_ScopeKey;
ProdSymbolListPtr _AVSyntLit_cProdSymbolListPtr_post;
DefTableKey _AVRuleSpecId_Key;
PTGNode _AVRuleSpec__const20;
RuleProd _AVRuleSpec_Rule;
Binding _AVSyntUnit_newGenTreeAttr_RuleAttr_160;
int _AVSyntLit_ProdSymbolTakeIt;
ProdSymbol _AVSyntLit_ProdSymbolElem;
ProdSymbolList _AVProduction__ProdSymbolauxList;
int _AVProduction_IsListof;
ProdSymbolList _AVProduction_ProdSymbolList;
PTGNode _AVCompPart__const20;
DefTableKeyList _AVSymbolDefIds__DefTableKeyauxList;
PTGNode _AVSymCompSpec__const20;
DefTableKeyList _AVSymCompSpec__DefTableKeyauxList_RuleAttr_163;
int _AVSymCompSpec_isRoot;
ProdSymbol _AVSymbolRef_ProdSymbol_RuleAttr_167;
int _AVSymbolRef_occs_RuleAttr_167;
PExpr _AVSymbolRef_repr;
int _AVSymbolRef_Pos;
DefTableKey _AVSymbolRef_Key;
PTGNode _AVAG_TargetComps;
PTGNode _AVAG_TargetDefs;
Binding _AVRuleId_Bind;
Binding _AVTypeId_Bind;
int _AVSyntId_ProdSymbolTakeIt;
Binding _AVSyntId_Bind;
ProdSymbol _AVSyntId_ProdSymbolElem;
int _AVSyntId_IsGenSymbol;
int _AVSymbolDefId_DefTableKeyTakeIt;
Binding _AVSymbolDefId_Bind;
DefTableKey _AVSymbolDefId_DefTableKeyElem;

#if defined(__STDC__) || defined(__cplusplus)
void LIGA_ATTREVAL (NODEPTR _currn)
#else
void LIGA_ATTREVAL (_currn) NODEPTR _currn;
#endif
{(*(VS1MAP[_currn->_prod])) ((NODEPTR)_currn);}
/*SPC(0)*/

#if defined(__STDC__) || defined(__cplusplus)
void _VS0Empty(NODEPTR _currn)
#else
void _VS0Empty(_currn) NODEPTR _currn;
#endif
{ _VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_1(_TPPrule_1 _currn)
#else
void _VS1rule_1(_currn )
_TPPrule_1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATisAccu=1;
/*SPC(2100)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_2(_TPPrule_2 _currn)
#else
void _VS1rule_2(_currn )
_TPPrule_2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATisAccu=0;
/*SPC(2099)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_3(_TPPrule_3 _currn)
#else
void _VS1rule_3(_currn )
_TPPrule_3 _currn;

#endif
{
PExpr _AS3repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_3(_TPPrule_3 _currn)
#else
void _VS2rule_3(_currn )
_TPPrule_3 _currn;

#endif
{
PExpr _AS3repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_3(_TPPrule_3 _currn)
#else
void _VS3rule_3(_currn )
_TPPrule_3 _currn;

#endif
{
PExpr _AS3repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_3(_TPPrule_3 _currn)
#else
void _VS4rule_3(_currn )
_TPPrule_3 _currn;

#endif
{
PExpr _AS3repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (AND(_currn->_desc2->_ATisAccu, GetIsChain(_currn->_desc1->_ATAttrKey, 0))) {
message(ERROR, CatStrInd("CHAIN computation can not be accumulating: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(2068)*/
_AVAttrComp__const3=_currn->_desc1->_ATBind;
/*SPC(2057)*/
_currn->_AT_const4=_AVDefAttr_IsUpperSymbComp;
/*SPC(2057)*/
_currn->_ATisAccu=AND(_currn->_desc2->_ATisAccu, NOT(GetIsChain(_currn->_desc1->_ATAttrKey, 0)));
/*SPC(2058)*/
_AVAttrComp_IsChainStart=NoKey;
/*SPC(1651)*/

if (_currn->_ATisAccu) {
ResetHasAccuAsgn(_currn->_desc1->_ATAttrKey, 1);

} else {
ResetHasNonAccuAsgn(_currn->_desc1->_ATAttrKey, 1);
}
;
/*SPC(2070)*/

if (AND(_currn->_ATisAccu, NE(GetAttrType(_currn->_desc1->_ATAttrKey, VOIDkey), VOIDkey))) {
message(ERROR, CatStrInd("Accumulating attribute must have type VOID: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(2091)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_3(_TPPrule_3 _currn)
#else
void _VS5rule_3(_currn )
_TPPrule_3 _currn;

#endif
{
PExpr _AS3repr;

_VisitVarDecl()
_VisitEntry();

if (AND(_currn->_ATisAccu, GetHasNonAccuAsgn(_currn->_desc1->_ATAttrKey, 0))) {
message(ERROR, CatStrInd("Collides with a non-accumulating computation in this context: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(2079)*/

if (AND(NOT(_currn->_ATisAccu), GetHasAccuAsgn(_currn->_desc1->_ATAttrKey, 0))) {
message(ERROR, CatStrInd("Collides with an accumulating computation in this context: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(2085)*/
_AVDefAttr_hasAccuToken=_currn->_desc2->_ATisAccu;
/*SPC(2062)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR ,PExpr*)) (VS4MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3,(&( _AS3repr)));
_AVAttrComp_repr=newAssign(_AVDefAttr_repr, _AS3repr, (&( _currn->_AT_pos)));
/*SPC(1853)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_4(_TPPrule_4 _currn)
#else
void _VS1rule_4(_currn )
_TPPrule_4 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATrepr=newRHS(_currn->_ATTERM_1, (&( _currn->_AT_pos)));
/*SPC(1960)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_5(_TPPrule_5 _currn)
#else
void _VS1rule_5(_currn )
_TPPrule_5 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_5(_TPPrule_5 _currn)
#else
void _VS4rule_5(_currn )
_TPPrule_5 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVExpression_repr=newIntValue(_currn->_ATTERM_1, (&( _currn->_AT_pos)));
/*SPC(1945)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_6(_TPPrule_6 _currn)
#else
void _VS1rule_6(_currn )
_TPPrule_6 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_6(_TPPrule_6 _currn)
#else
void _VS4rule_6(_currn )
_TPPrule_6 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVExpression_repr=newFltValue(_currn->_ATTERM_1, (&( _currn->_AT_pos)));
/*SPC(1942)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_7(_TPPrule_7 _currn)
#else
void _VS1rule_7(_currn )
_TPPrule_7 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_7(_TPPrule_7 _currn)
#else
void _VS4rule_7(_currn )
_TPPrule_7 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVExpression_repr=newStrValue(_currn->_ATTERM_1, (&( _currn->_AT_pos)));
/*SPC(1939)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_8(_TPPrule_8 _currn)
#else
void _VS1rule_8(_currn )
_TPPrule_8 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_8(_TPPrule_8 _currn)
#else
void _VS4rule_8(_currn )
_TPPrule_8 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVExpression_repr=newChrValue(_currn->_ATTERM_1, (&( _currn->_AT_pos)));
/*SPC(1936)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_9(_TPPrule_9 _currn)
#else
void _VS1rule_9(_currn )
_TPPrule_9 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_9(_TPPrule_9 _currn)
#else
void _VS2rule_9(_currn )
_TPPrule_9 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_9(_TPPrule_9 _currn)
#else
void _VS4rule_9(_currn )
_TPPrule_9 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVExpression_repr=_AVSymbolRef_repr;
/*SPC(1933)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_10(_TPPrule_10 _currn)
#else
void _VS1rule_10(_currn )
_TPPrule_10 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_10(_TPPrule_10 _currn)
#else
void _VS2rule_10(_currn )
_TPPrule_10 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_10(_TPPrule_10 _currn)
#else
void _VS3rule_10(_currn )
_TPPrule_10 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_10(_TPPrule_10 _currn)
#else
void _VS4rule_10(_currn )
_TPPrule_10 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVExpression_repr=_AVRemoteExpression_repr;
/*SPC(1930)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_11(_TPPrule_11 _currn)
#else
void _VS1rule_11(_currn )
_TPPrule_11 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_11(_TPPrule_11 _currn)
#else
void _VS4rule_11(_currn )
_TPPrule_11 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVExpression_repr=_currn->_desc1->_ATrepr;
/*SPC(1927)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_12(_TPPrule_12 _currn)
#else
void _VS1rule_12(_currn )
_TPPrule_12 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_12(_TPPrule_12 _currn)
#else
void _VS2rule_12(_currn )
_TPPrule_12 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_12(_TPPrule_12 _currn)
#else
void _VS3rule_12(_currn )
_TPPrule_12 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATIsDefining=0;
/*SPC(1402)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_12(_TPPrule_12 _currn)
#else
void _VS4rule_12(_currn )
_TPPrule_12 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
_AVAttr_IsIterate=0;
/*SPC(982)*/
(*(_CALL_VS_((NODEPTR ,PExpr*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1repr)));
_AVExpression_repr=_AS1repr;
/*SPC(1924)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_13(_TPPrule_13 _currn)
#else
void _VS1rule_13(_currn )
_TPPrule_13 _currn;

#endif
{
PExprList _AS1_PExprauxList;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_13(_TPPrule_13 _currn)
#else
void _VS2rule_13(_currn )
_TPPrule_13 _currn;

#endif
{
PExprList _AS1_PExprauxList;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_13(_TPPrule_13 _currn)
#else
void _VS3rule_13(_currn )
_TPPrule_13 _currn;

#endif
{
PExprList _AS1_PExprauxList;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_13(_TPPrule_13 _currn)
#else
void _VS4rule_13(_currn )
_TPPrule_13 _currn;

#endif
{
PExprList _AS1_PExprauxList;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PExprList*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_PExprauxList)));
_AVExpression_repr=newCall(_currn->_ATTERM_1, _AVParamsOpt_PExprList, (&( _currn->_AT_pos)));
/*SPC(1915)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_14(_TPPrule_14 _currn)
#else
void _VS1rule_14(_currn )
_TPPrule_14 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_14(_TPPrule_14 _currn)
#else
void _VS2rule_14(_currn )
_TPPrule_14 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_14(_TPPrule_14 _currn)
#else
void _VS3rule_14(_currn )
_TPPrule_14 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_14(_TPPrule_14 _currn,PExpr* _AS0repr)
#else
void _VS4rule_14(_currn ,_AS0repr)
_TPPrule_14 _currn;
PExpr* _AS0repr;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(* _AS0repr)=newDepend(_AVExpression_repr, _AVDepClause_PExprList, (&( _currn->_AT_pos)));
/*SPC(1903)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_15(_TPPrule_15 _currn)
#else
void _VS1rule_15(_currn )
_TPPrule_15 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_15(_TPPrule_15 _currn)
#else
void _VS2rule_15(_currn )
_TPPrule_15 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_15(_TPPrule_15 _currn)
#else
void _VS3rule_15(_currn )
_TPPrule_15 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_15(_TPPrule_15 _currn,PExpr* _AS0repr)
#else
void _VS4rule_15(_currn ,_AS0repr)
_TPPrule_15 _currn;
PExpr* _AS0repr;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0repr)=_AVExpression_repr;
/*SPC(1899)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_16(_TPPrule_16 _currn)
#else
void _VS2rule_16(_currn )
_TPPrule_16 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVExpandOpt_Fct0=NoStrIndex;
/*SPC(1824)*/
_AVExpandOpt_Fct1=NoStrIndex;
/*SPC(1823)*/
_AVExpandOpt_Fct2=NoStrIndex;
/*SPC(1822)*/
_AVExpandOpt_Type=NoKey;
/*SPC(1821)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_17(_TPPrule_17 _currn)
#else
void _VS1rule_17(_currn )
_TPPrule_17 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_17(_TPPrule_17 _currn)
#else
void _VS2rule_17(_currn )
_TPPrule_17 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsSymbol(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(460)*/

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVExpandOpt_Fct0=_currn->_ATTERM_3;
/*SPC(1817)*/
_AVExpandOpt_Fct1=_currn->_ATTERM_2;
/*SPC(1816)*/
_AVExpandOpt_Fct2=_currn->_ATTERM_1;
/*SPC(1815)*/
_AVExpandOpt_Type=_currn->_desc1->_ATKey;
/*SPC(1814)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_18(_TPPrule_18 _currn)
#else
void _VS1rule_18(_currn )
_TPPrule_18 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_18(_TPPrule_18 _currn)
#else
void _VS2rule_18(_currn )
_TPPrule_18 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_18(_TPPrule_18 _currn)
#else
void _VS3rule_18(_currn )
_TPPrule_18 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSymOcc_IsDefining=0;
/*SPC(1224)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVSubtree_SubtreeNo=PosOfProdSymbol(_currn->_desc1->_ATProdSymbol);
/*SPC(1805)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_19(_TPPrule_19 _currn)
#else
void _VS1rule_19(_currn )
_TPPrule_19 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_19(_TPPrule_19 _currn)
#else
void _VS2rule_19(_currn )
_TPPrule_19 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_19(_TPPrule_19 _currn)
#else
void _VS3rule_19(_currn )
_TPPrule_19 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_19(_TPPrule_19 _currn)
#else
void _VS4rule_19(_currn )
_TPPrule_19 _currn;

#endif
{
DefTableKey* _IL_incl18;

_VisitVarDecl()
_VisitEntry();
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRemoteKey);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_currn->_ATRemoteKey=EnterSglConstit(_AVRemoteClause_RemoteSet, _AVShield_ShieldSet, (* _IG_incl4), (&( _currn->_AT_pos)));
/*SPC(1795)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVRemoteExpression_SubtreeNo=_AVSubtree_SubtreeNo;
/*SPC(1794)*/
_AVRemoteExpression_repr=
((GetIsIncluding(_currn->_ATRemoteKey, 0)
) ? (newIncluding(_currn->_ATRemoteKey, (&( _currn->_AT_pos)))
) : (
((GetIsConstituent(_currn->_ATRemoteKey, 0)
) ? (newConstituent(_currn->_ATRemoteKey, _AVRemoteExpression_SubtreeNo, (&( _currn->_AT_pos)))
) : (
((GetIsConstituents(_currn->_ATRemoteKey, 0)
) ? (newConstituents(_currn->_ATRemoteKey, _AVRemoteExpression_SubtreeNo, (&( _currn->_AT_pos)))
) : (wrongExpr))
))
))
;
/*SPC(1949)*/
_IG_incl18=_IL_incl18;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_20(_TPPrule_20 _currn)
#else
void _VS1rule_20(_currn )
_TPPrule_20 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_20(_TPPrule_20 _currn)
#else
void _VS2rule_20(_currn )
_TPPrule_20 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_20(_TPPrule_20 _currn)
#else
void _VS3rule_20(_currn )
_TPPrule_20 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_20(_TPPrule_20 _currn)
#else
void _VS4rule_20(_currn )
_TPPrule_20 _currn;

#endif
{
DefTableKey* _IL_incl18;

_VisitVarDecl()
_VisitEntry();
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRemoteKey);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);
_currn->_ATRemoteKey=EnterMulConstit(_AVRemoteClause_RemoteSet, _AVShield_ShieldSet, _AVExpandOpt_Type, _AVExpandOpt_Fct2, _AVExpandOpt_Fct1, _AVExpandOpt_Fct0, (* _IG_incl4), (&( _currn->_AT_pos)));
/*SPC(1785)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVRemoteExpression_SubtreeNo=_AVSubtree_SubtreeNo;
/*SPC(1784)*/
_AVRemoteExpression_repr=
((GetIsIncluding(_currn->_ATRemoteKey, 0)
) ? (newIncluding(_currn->_ATRemoteKey, (&( _currn->_AT_pos)))
) : (
((GetIsConstituent(_currn->_ATRemoteKey, 0)
) ? (newConstituent(_currn->_ATRemoteKey, _AVRemoteExpression_SubtreeNo, (&( _currn->_AT_pos)))
) : (
((GetIsConstituents(_currn->_ATRemoteKey, 0)
) ? (newConstituents(_currn->_ATRemoteKey, _AVRemoteExpression_SubtreeNo, (&( _currn->_AT_pos)))
) : (wrongExpr))
))
))
;
/*SPC(1949)*/
_IG_incl18=_IL_incl18;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_21(_TPPrule_21 _currn)
#else
void _VS1rule_21(_currn )
_TPPrule_21 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_21(_TPPrule_21 _currn)
#else
void _VS2rule_21(_currn )
_TPPrule_21 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_21(_TPPrule_21 _currn)
#else
void _VS3rule_21(_currn )
_TPPrule_21 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_21(_TPPrule_21 _currn)
#else
void _VS4rule_21(_currn )
_TPPrule_21 _currn;

#endif
{
DefTableKey* _IL_incl18;

_VisitVarDecl()
_VisitEntry();
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRemoteKey);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATRemoteKey=EnterIncluding(_AVRemoteClause_RemoteSet, (* _IG_incl4), (&( _currn->_AT_pos)));
/*SPC(1778)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRemoteExpression_SubtreeNo=0;
/*SPC(1802)*/
_AVRemoteExpression_repr=
((GetIsIncluding(_currn->_ATRemoteKey, 0)
) ? (newIncluding(_currn->_ATRemoteKey, (&( _currn->_AT_pos)))
) : (
((GetIsConstituent(_currn->_ATRemoteKey, 0)
) ? (newConstituent(_currn->_ATRemoteKey, _AVRemoteExpression_SubtreeNo, (&( _currn->_AT_pos)))
) : (
((GetIsConstituents(_currn->_ATRemoteKey, 0)
) ? (newConstituents(_currn->_ATRemoteKey, _AVRemoteExpression_SubtreeNo, (&( _currn->_AT_pos)))
) : (wrongExpr))
))
))
;
/*SPC(1949)*/
_IG_incl18=_IL_incl18;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_22(_TPPrule_22 _currn)
#else
void _VS3rule_22(_currn )
_TPPrule_22 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
UnmarkSymbols();
/*SPC(1709)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVShield_ShieldSet=MakeShieldSet();
/*SPC(1712)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_23(_TPPrule_23 _currn)
#else
void _VS3rule_23(_currn )
_TPPrule_23 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVShield_ShieldSet=NULLDefTableKeyList;
/*SPC(1704)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_24(_TPPrule_24 _currn)
#else
void _VS3rule_24(_currn )
_TPPrule_24 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATIsBottomUp=1;
/*SPC(1669)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_24(_TPPrule_24 _currn)
#else
void _VS4rule_24(_currn )
_TPPrule_24 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_24(_TPPrule_24 _currn,PTGNode* _AS0_const20)
#else
void _VS5rule_24(_currn ,_AS0_const20)
_TPPrule_24 _currn;
PTGNode* _AS0_const20;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0_const20)=IDENTICAL(_AVCompute_InhComps);
/*SPC(1668)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_25(_TPPrule_25 _currn)
#else
void _VS1rule_25(_currn )
_TPPrule_25 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_25(_TPPrule_25 _currn)
#else
void _VS2rule_25(_currn )
_TPPrule_25 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_25(_TPPrule_25 _currn)
#else
void _VS3rule_25(_currn )
_TPPrule_25 _currn;

#endif
{
int* _IL_incl32;

_VisitVarDecl()
_VisitEntry();
_IL_incl32=_IG_incl32;_IG_incl32= &(_currn->_ATIsBottomUp);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl32=_IL_incl32;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_25(_TPPrule_25 _currn)
#else
void _VS4rule_25(_currn )
_TPPrule_25 _currn;

#endif
{
int* _IL_incl32;
DefTableKey* _IL_incl4;

_VisitVarDecl()
_VisitEntry();
_IL_incl32=_IG_incl32;_IG_incl32= &(_currn->_ATIsBottomUp);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATKey);
_currn->_ATisAccu=0;
/*SPC(2101)*/
_currn->_ATBind=_currn->_desc1->_ATBind;
/*SPC(1654)*/
_currn->_ATKey=KeyOf(_currn->_ATBind);
/*SPC(1659)*/
ResetIsAccu(_currn->_ATKey, _currn->_ATisAccu);
/*SPC(2047)*/
ResetContext(_currn->_ATKey, (* _IG_incl8));
ResetIsBottomUp(_currn->_ATKey, _currn->_ATIsBottomUp);
ResetIsRuleComputation(_currn->_ATKey, (* _IG_incl6));
;
/*SPC(1661)*/
_IG_incl32=_IL_incl32;
_IG_incl4=_IL_incl4;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_25(_TPPrule_25 _currn)
#else
void _VS5rule_25(_currn )
_TPPrule_25 _currn;

#endif
{
int* _IL_incl32;
int* _IL_incl13;
DefTableKey* _IL_incl4;

_VisitVarDecl()
_VisitEntry();
_IL_incl32=_IG_incl32;_IG_incl32= &(_currn->_ATIsBottomUp);
_IL_incl13=_IG_incl13;_IG_incl13= &(_currn->_ATIsUpperSymbComp);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATKey);
_currn->_ATIsUpperSymbComp=0;
/*SPC(1655)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (_currn->_ATisAccu) {
AccumulateExpr(_currn->_ATKey, _AVPlainComp_repr);

} else {
ResetCompRepr(_currn->_ATKey, _AVPlainComp_repr);
}
;
/*SPC(1844)*/
_AVCompute_InhComps=
(((* _IG_incl6)
) ? (PTGNULL
) : (InhCompOutput(_currn->_ATKey)))
;
/*SPC(1693)*/
_AVCompute_Sym=IdnOf(_currn->_ATBind);
/*SPC(1660)*/
_IG_incl32=_IL_incl32;
_IG_incl13=_IL_incl13;
_IG_incl4=_IL_incl4;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_26(_TPPrule_26 _currn)
#else
void _VS1rule_26(_currn )
_TPPrule_26 _currn;

#endif
{
PExpr _AS2repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_26(_TPPrule_26 _currn)
#else
void _VS2rule_26(_currn )
_TPPrule_26 _currn;

#endif
{
PExpr _AS2repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_26(_TPPrule_26 _currn)
#else
void _VS3rule_26(_currn )
_TPPrule_26 _currn;

#endif
{
PExpr _AS2repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_26(_TPPrule_26 _currn)
#else
void _VS4rule_26(_currn )
_TPPrule_26 _currn;

#endif
{
PExpr _AS2repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (NOT(GetIsChain(_currn->_desc1->_ATAttrKey, 0))) {
message(ERROR, "CHAINSTART must assign a chain", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1648)*/
_AVAttrComp__const3=_currn->_desc1->_ATBind;
/*SPC(1644)*/
_currn->_AT_const4=_AVDefAttr_IsUpperSymbComp;
/*SPC(1644)*/
_currn->_ATisAccu=0;
/*SPC(2102)*/
_AVAttrComp_IsChainStart=_currn->_desc1->_ATAttrKey;
/*SPC(1645)*/
ResetHasNonAccuAsgn(_currn->_desc1->_ATAttrKey, 1);
/*SPC(2095)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_26(_TPPrule_26 _currn)
#else
void _VS5rule_26(_currn )
_TPPrule_26 _currn;

#endif
{
PExpr _AS2repr;

_VisitVarDecl()
_VisitEntry();
_AVDefAttr_hasAccuToken=0;
/*SPC(2055)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR ,PExpr*)) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2repr)));
_AVAttrComp_repr=newAssign(_AVDefAttr_repr, _AS2repr, (&( _currn->_AT_pos)));
/*SPC(1853)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_27(_TPPrule_27 _currn)
#else
void _VS1rule_27(_currn )
_TPPrule_27 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_27(_TPPrule_27 _currn)
#else
void _VS2rule_27(_currn )
_TPPrule_27 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_27(_TPPrule_27 _currn)
#else
void _VS3rule_27(_currn )
_TPPrule_27 _currn;

#endif
{
int* _IL_incl32;

_VisitVarDecl()
_VisitEntry();
_IL_incl32=_IG_incl32;_IG_incl32= &(_currn->_ATIsBottomUp);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl32=_IL_incl32;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_27(_TPPrule_27 _currn)
#else
void _VS4rule_27(_currn )
_TPPrule_27 _currn;

#endif
{
int* _IL_incl32;
DefTableKey* _IL_incl4;

_VisitVarDecl()
_VisitEntry();
_IL_incl32=_IG_incl32;_IG_incl32= &(_currn->_ATIsBottomUp);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATisAccu=_currn->_desc1->_ATisAccu;
/*SPC(2051)*/
_currn->_ATBind=
(ResetIsChainStart(KeyOf(_AVAttrComp__const3), _AVAttrComp_IsChainStart), _AVAttrComp__const3)
;
/*SPC(1636)*/
_currn->_ATKey=KeyOf(_currn->_ATBind);
/*SPC(1659)*/
ResetIsAccu(_currn->_ATKey, _currn->_ATisAccu);
/*SPC(2047)*/
ResetContext(_currn->_ATKey, (* _IG_incl8));
ResetIsBottomUp(_currn->_ATKey, _currn->_ATIsBottomUp);
ResetIsRuleComputation(_currn->_ATKey, (* _IG_incl6));
;
/*SPC(1661)*/
_IG_incl32=_IL_incl32;
_IG_incl4=_IL_incl4;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_27(_TPPrule_27 _currn)
#else
void _VS5rule_27(_currn )
_TPPrule_27 _currn;

#endif
{
int* _IL_incl32;
int* _IL_incl13;
DefTableKey* _IL_incl4;

_VisitVarDecl()
_VisitEntry();
_IL_incl32=_IG_incl32;_IG_incl32= &(_currn->_ATIsBottomUp);
_IL_incl13=_IG_incl13;_IG_incl13= &(_currn->_ATIsUpperSymbComp);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATKey);
_currn->_ATIsUpperSymbComp=_currn->_desc1->_AT_const4;
/*SPC(1641)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (_currn->_ATisAccu) {
AccumulateExpr(_currn->_ATKey, _AVAttrComp_repr);

} else {
ResetCompRepr(_currn->_ATKey, _AVAttrComp_repr);
}
;
/*SPC(1844)*/
_AVCompute_InhComps=
(((* _IG_incl6)
) ? (PTGNULL
) : (InhCompOutput(_currn->_ATKey)))
;
/*SPC(1693)*/
_AVCompute_Sym=IdnOf(_currn->_ATBind);
/*SPC(1660)*/
_IG_incl32=_IL_incl32;
_IG_incl13=_IL_incl13;
_IG_incl4=_IL_incl4;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_28(_TPPrule_28 _currn)
#else
void _VS1rule_28(_currn )
_TPPrule_28 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_28(_TPPrule_28 _currn)
#else
void _VS2rule_28(_currn )
_TPPrule_28 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
ResetIsSymbol(_currn->_desc1->_ATKey, 1);
/*SPC(436)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_28(_TPPrule_28 _currn)
#else
void _VS3rule_28(_currn )
_TPPrule_28 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (AND(NOT(GetIsDefined(_currn->_desc1->_ATKey, 0)), NOT(GetIsDefinedReported(_currn->_desc1->_ATKey, 0)))) {
ResetIsDefinedReported(_currn->_desc1->_ATKey, 1);
message(ERROR, CatStrInd("Symbol does not occur in rule or definition: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(1443)*/

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
MarkInheritingTreeSymbs(_currn->_desc1->_ATBind);
/*SPC(1717)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_29(_TPPrule_29 _currn)
#else
void _VS1rule_29(_currn )
_TPPrule_29 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATValue=0;
/*SPC(1424)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_30(_TPPrule_30 _currn)
#else
void _VS1rule_30(_currn )
_TPPrule_30 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATValue=
((LE(_currn->_ATTERM_1, 0)
) ? (1
) : (_currn->_ATTERM_1))
;
/*SPC(1415)*/

if (LE(_currn->_ATTERM_1, 0)) {
message(ERROR, "Index must be greater than 0", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1420)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_31(_TPPrule_31 _currn)
#else
void _VS1rule_31(_currn )
_TPPrule_31 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_31(_TPPrule_31 _currn)
#else
void _VS2rule_31(_currn )
_TPPrule_31 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_31(_TPPrule_31 _currn)
#else
void _VS3rule_31(_currn )
_TPPrule_31 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATIsDefining=1;
/*SPC(1409)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_31(_TPPrule_31 _currn)
#else
void _VS4rule_31(_currn )
_TPPrule_31 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
_currn->_ATSym=_currn->_desc1->_AT_const7;
/*SPC(1549)*/
_currn->_ATAttrKey=_currn->_desc1->_AT_const8;
/*SPC(1548)*/
_AVDefAttr_IsUpperSymbComp=
((OR((* _IG_incl6), OR(GetIsChain(_currn->_ATAttrKey, 0), EQ(GetAttrClass(_currn->_ATAttrKey, NoClass), SYNTClass)))
) ? (0
) : (1))
;
/*SPC(1551)*/
_AVDefAttr_CompScope=
(((* _IG_incl6)
) ? (
((EQ(_currn->_desc1->_ATProdSymbol, NoProdSymbol)
) ? (GetLowerScope((* _IG_incl8), NoEnv)
) : (GetSymbolOccScope(_currn->_desc1->_ATProdSymbol)))

) : (
((_currn->_desc1->_ATIsHEADAcc
) ? (GetHEADScope((* _IG_incl8), NoEnv)
) : (
((_AVDefAttr_IsUpperSymbComp
) ? (GetUpperScope((* _IG_incl8), NoEnv)
) : (GetLowerScope((* _IG_incl8), NoEnv)))
))
))
;
/*SPC(1558)*/
_currn->_ATBind=AddAttrToBinding(AddCoordToBinding(BindIdn(_AVDefAttr_CompScope, _currn->_ATSym), (&( _currn->_AT_pos))), _currn->_ATAttrKey);
/*SPC(1570)*/
SetCheckMult(KeyOf(_currn->_ATBind), 1, 2);
/*SPC(1587)*/

if (AND(NOT((* _IG_incl6)), AND(NOT(GetIsChain(_currn->_ATAttrKey, 0)), EQ(GetAttrClass(_currn->_ATAttrKey, NoClass), NoClass)))) {
message(ERROR, CatStrInd("Class of defined attribute not specified: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1585)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_31(_TPPrule_31 _currn)
#else
void _VS5rule_31(_currn )
_TPPrule_31 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();

if (AND(GT(GetCheckMult(KeyOf(_currn->_ATBind), 1), 1), AND(NOT(_AVDefAttr_hasAccuToken), NOT(GetHasAccuAsgn(_currn->_ATAttrKey, 0))))) {
message(ERROR, CatStrInd("Multiple computations of: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1595)*/
_AVAttr_IsIterate=0;
/*SPC(982)*/
(*(_CALL_VS_((NODEPTR ,PExpr*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1repr)));
_AVDefAttr_repr=_AS1repr;
/*SPC(1895)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_32(_TPPrule_32 _currn)
#else
void _VS1rule_32(_currn )
_TPPrule_32 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_32(_TPPrule_32 _currn)
#else
void _VS3rule_32(_currn )
_TPPrule_32 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if ((* _IG_incl6)) {
message(ERROR, "TERM is not allowed in RULE computation", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1391)*/

if ((* _IG_incl13)) {
message(ERROR, "TERM is not allowed in upper symbol computation", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1396)*/
_AVSymbolRef_Key=NoKey;
/*SPC(1386)*/
_AVSymbolRef_Pos=_currn->_desc1->_ATValue;
/*SPC(1385)*/
_AVSymbolRef_repr=newSymbTermAcc(_currn->_desc1->_ATValue, (&( _currn->_AT_pos)));
/*SPC(1970)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_33(_TPPrule_33 _currn)
#else
void _VS1rule_33(_currn )
_TPPrule_33 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_33(_TPPrule_33 _currn)
#else
void _VS2rule_33(_currn )
_TPPrule_33 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
ResetIsSymbol(_currn->_desc1->_ATKey, 1);
/*SPC(436)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_33(_TPPrule_33 _currn)
#else
void _VS3rule_33(_currn )
_TPPrule_33 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATKey=_currn->_desc1->_ATKey;
/*SPC(1288)*/
_currn->_ATProdSymbol=
(((* _IG_incl6)
) ? (FindSymbolOcc(GetRule((* _IG_incl8), NoRuleProd), _currn->_ATKey, _currn->_desc2->_ATValue, (&( _currn->_AT_pos)))
) : (NoProdSymbol))
;
/*SPC(1296)*/
_AVSymOcc_AttrClass=
((OR(EQ(_currn->_ATProdSymbol, NoProdSymbol), NOT(_AVSymOcc_IsDefining))
) ? (NoClass
) : (
((EQ(PosOfProdSymbol(_currn->_ATProdSymbol), 0)
) ? (SYNTClass
) : (INHClass))
))
;
/*SPC(1306)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_33(_TPPrule_33 _currn)
#else
void _VS4rule_33(_currn )
_TPPrule_33 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (NOT((* _IG_incl6))) {
message(ERROR, "Not allowed in SYMBOL computation", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1290)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_34(_TPPrule_34 _currn)
#else
void _VS1rule_34(_currn )
_TPPrule_34 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_34(_TPPrule_34 _currn)
#else
void _VS3rule_34(_currn )
_TPPrule_34 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATKey=TAILKey;
/*SPC(1269)*/
_currn->_ATProdSymbol=
(((* _IG_incl6)
) ? (FindTAILSymbolOcc(GetRule((* _IG_incl8), NoRuleProd))
) : (NoProdSymbol))
;
/*SPC(1272)*/
_AVSymOcc_AttrClass=NoClass;
/*SPC(1225)*/

if (AND((* _IG_incl6), EQ(_currn->_ATProdSymbol, NoProdSymbol))) {
message(ERROR, "TAIL not allowed in RULE without nonterminal", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1283)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_35(_TPPrule_35 _currn)
#else
void _VS1rule_35(_currn )
_TPPrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_35(_TPPrule_35 _currn)
#else
void _VS3rule_35(_currn )
_TPPrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATKey=HEADKey;
/*SPC(1250)*/
_currn->_ATProdSymbol=
(((* _IG_incl6)
) ? (FindHEADSymbolOcc(GetRule((* _IG_incl8), NoRuleProd))
) : (NoProdSymbol))
;
/*SPC(1253)*/
_AVSymOcc_AttrClass=NoClass;
/*SPC(1225)*/

if (AND((* _IG_incl6), EQ(_currn->_ATProdSymbol, NoProdSymbol))) {
message(ERROR, "HEAD not allowed in RULE without nonterminal", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1265)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_36(_TPPrule_36 _currn)
#else
void _VS1rule_36(_currn )
_TPPrule_36 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_36(_TPPrule_36 _currn)
#else
void _VS3rule_36(_currn )
_TPPrule_36 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATKey=
(((* _IG_incl6)
) ? (NoKey
) : ((* _IG_incl8)))
;
/*SPC(1227)*/
_currn->_ATProdSymbol=NoProdSymbol;
/*SPC(1236)*/
_AVSymOcc_AttrClass=INHClass;
/*SPC(1245)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_36(_TPPrule_36 _currn)
#else
void _VS4rule_36(_currn )
_TPPrule_36 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if ((* _IG_incl6)) {
message(ERROR, "Not allowed in RULE computation", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1230)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_37(_TPPrule_37 _currn)
#else
void _VS1rule_37(_currn )
_TPPrule_37 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_37(_TPPrule_37 _currn)
#else
void _VS3rule_37(_currn )
_TPPrule_37 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATKey=
(((* _IG_incl6)
) ? (NoKey
) : ((* _IG_incl8)))
;
/*SPC(1227)*/
_currn->_ATProdSymbol=NoProdSymbol;
/*SPC(1236)*/
_AVSymOcc_AttrClass=SYNTClass;
/*SPC(1241)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_37(_TPPrule_37 _currn)
#else
void _VS4rule_37(_currn )
_TPPrule_37 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if ((* _IG_incl6)) {
message(ERROR, "Not allowed in RULE computation", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1230)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_38(_TPPrule_38 _currn)
#else
void _VS1rule_38(_currn )
_TPPrule_38 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_38(_TPPrule_38 _currn)
#else
void _VS2rule_38(_currn )
_TPPrule_38 _currn;

#endif
{
DefTableKey* _IL_incl34;

_VisitVarDecl()
_VisitEntry();
_IL_incl34=_IG_incl34;_IG_incl34= &(_currn->_ATType);
_currn->_ATType=_currn->_desc2->_ATKey;
/*SPC(1102)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl34=_IL_incl34;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_38(_TPPrule_38 _currn)
#else
void _VS3rule_38(_currn )
_TPPrule_38 _currn;

#endif
{
DefTableKey* _IL_incl34;

_VisitVarDecl()
_VisitEntry();
_IL_incl34=_IG_incl34;_IG_incl34= &(_currn->_ATType);

if (GetIsSymbol(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(460)*/

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl34=_IL_incl34;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_39(_TPPrule_39 _currn)
#else
void _VS1rule_39(_currn )
_TPPrule_39 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_39(_TPPrule_39 _currn)
#else
void _VS2rule_39(_currn )
_TPPrule_39 _currn;

#endif
{
DefTableKey* _IL_incl36;
int* _IL_incl35;

_VisitVarDecl()
_VisitEntry();
_IL_incl36=_IG_incl36;_IG_incl36= &(_currn->_ATType);
_IL_incl35=_IG_incl35;_IG_incl35= &(_currn->_ATAttrClass);
_currn->_ATAttrClass=_currn->_desc3->_ATAttrClass;
/*SPC(1076)*/
_currn->_ATType=_currn->_desc2->_ATKey;
/*SPC(1075)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl36=_IL_incl36;
_IG_incl35=_IL_incl35;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_39(_TPPrule_39 _currn)
#else
void _VS3rule_39(_currn )
_TPPrule_39 _currn;

#endif
{
DefTableKey* _IL_incl36;
int* _IL_incl35;

_VisitVarDecl()
_VisitEntry();
_IL_incl36=_IG_incl36;_IG_incl36= &(_currn->_ATType);
_IL_incl35=_IG_incl35;_IG_incl35= &(_currn->_ATAttrClass);

if (GetIsSymbol(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(460)*/

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl36=_IL_incl36;
_IG_incl35=_IL_incl35;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_40(_TPPrule_40 _currn)
#else
void _VS1rule_40(_currn )
_TPPrule_40 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATAttrClass=NoClass;
/*SPC(1017)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_41(_TPPrule_41 _currn)
#else
void _VS1rule_41(_currn )
_TPPrule_41 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATAttrClass=INHClass;
/*SPC(1014)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_42(_TPPrule_42 _currn)
#else
void _VS1rule_42(_currn )
_TPPrule_42 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATAttrClass=SYNTClass;
/*SPC(1011)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_43(_TPPrule_43 _currn)
#else
void _VS1rule_43(_currn )
_TPPrule_43 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_43(_TPPrule_43 _currn)
#else
void _VS2rule_43(_currn )
_TPPrule_43 _currn;

#endif
{
DefTableKey* _IL_incl39;
int* _IL_incl38;

_VisitVarDecl()
_VisitEntry();
_IL_incl39=_IG_incl39;_IG_incl39= &(_currn->_ATAttrType);
_IL_incl38=_IG_incl38;_IG_incl38= &(_currn->_ATAttrClass);
_currn->_ATAttrClass=_currn->_desc3->_ATAttrClass;
/*SPC(1008)*/
_currn->_ATAttrType=_currn->_desc2->_ATKey;
/*SPC(1007)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl39=_IL_incl39;
_IG_incl38=_IL_incl38;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_43(_TPPrule_43 _currn)
#else
void _VS3rule_43(_currn )
_TPPrule_43 _currn;

#endif
{
DefTableKey* _IL_incl39;
int* _IL_incl38;

_VisitVarDecl()
_VisitEntry();
_IL_incl39=_IG_incl39;_IG_incl39= &(_currn->_ATAttrType);
_IL_incl38=_IG_incl38;_IG_incl38= &(_currn->_ATAttrClass);

if (GetIsSymbol(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(460)*/

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl39=_IL_incl39;
_IG_incl38=_IL_incl38;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_44(_TPPrule_44 _currn)
#else
void _VS1rule_44(_currn )
_TPPrule_44 _currn;

#endif
{
PExpr _AS3repr;
PExpr _AS2repr;
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_44(_TPPrule_44 _currn)
#else
void _VS2rule_44(_currn )
_TPPrule_44 _currn;

#endif
{
PExpr _AS3repr;
PExpr _AS2repr;
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_44(_TPPrule_44 _currn)
#else
void _VS3rule_44(_currn )
_TPPrule_44 _currn;

#endif
{
PExpr _AS3repr;
PExpr _AS2repr;
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_desc2->_ATIsDefining=0;
/*SPC(1402)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_44(_TPPrule_44 _currn)
#else
void _VS4rule_44(_currn )
_TPPrule_44 _currn;

#endif
{
PExpr _AS3repr;
PExpr _AS2repr;
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PExpr*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1repr)));
_AVAttr_IsIterate=1;
/*SPC(979)*/
(*(_CALL_VS_((NODEPTR ,PExpr*)) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2repr)));
(*(_CALL_VS_((NODEPTR ,PExpr*)) (VS4MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3,(&( _AS3repr)));
_AVLoop_repr=newLoop(_AS1repr, _AS2repr, _AS3repr, (&( _currn->_AT_pos)));
/*SPC(1886)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_45(_TPPrule_45 _currn)
#else
void _VS1rule_45(_currn )
_TPPrule_45 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAttrUseId_auxChainBind_RuleAttr_149=BindingInScope((* _IG_incl17), _currn->_ATSym);
/*SPC(935)*/
_AVAttrUseId_auxChainKey_RuleAttr_149=
((EQ(_AVAttrUseId_auxChainBind_RuleAttr_149, NoBinding)
) ? (NoKey
) : (KeyOf(_AVAttrUseId_auxChainBind_RuleAttr_149)))
;
/*SPC(938)*/
_AVAttrUseId_Bind=
((EQ(_AVAttrUseId_auxChainKey_RuleAttr_149, NoKey)
) ? (SetCoordSymToBinding(BindIdn(GetAttrScope(_AVAttrUseId_ScopeKey, NoEnv), _currn->_ATSym), (&( _currn->_AT_pos)), _currn->_ATSym)
) : (_AVAttrUseId_auxChainBind_RuleAttr_149))
;
/*SPC(941)*/
_currn->_ATKey=KeyOf(_AVAttrUseId_Bind);
/*SPC(951)*/

if (AND(OR(EQ(_AVAttrUseId_ScopeKey, HEADKey), EQ(_AVAttrUseId_ScopeKey, TAILKey)), EQ(_AVAttrUseId_auxChainKey_RuleAttr_149, NoKey))) {
message(ERROR, CatStrInd("HEAD and TAIL require a CHAIN name: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(959)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_46(_TPPrule_46 _currn)
#else
void _VS1rule_46(_currn )
_TPPrule_46 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_46(_TPPrule_46 _currn)
#else
void _VS3rule_46(_currn )
_TPPrule_46 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (NOT((* _IG_incl6))) {
message(ERROR, "Not allowed in SYMBOL computation", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(880)*/
_AVAttrUseId_ScopeKey=(* _IG_incl8);
/*SPC(875)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (GetIsChain(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Rule attribute may not have a CHAIN name: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(967)*/
_currn->_AT_const7=_currn->_desc1->_ATSym;
/*SPC(874)*/
_currn->_AT_const8=_currn->_desc1->_ATKey;
/*SPC(874)*/
_currn->_ATIsHEADAcc=0;
/*SPC(1544)*/
_currn->_ATProdSymbol=NoProdSymbol;
/*SPC(1543)*/
SetChkAttrClass(_currn->_desc1->_ATKey, _currn->_desc1->_ATSym, SYNTClass, (&( _currn->_AT_pos)));
/*SPC(898)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_46(_TPPrule_46 _currn,PExpr* _AS0repr)
#else
void _VS4rule_46(_currn ,_AS0repr)
_TPPrule_46 _currn;
PExpr* _AS0repr;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0repr)=newRuleAttrAcc(_currn->_desc1->_ATKey, (&( _currn->_AT_pos)));
/*SPC(1993)*/

if (AND(_currn->_ATIsDefining, NOT(GetIsChain(_currn->_desc1->_ATKey, 0)))) {
ResetIsDefined(_currn->_desc1->_ATKey, 1);

} else {
}
;
/*SPC(1120)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_47(_TPPrule_47 _currn)
#else
void _VS1rule_47(_currn )
_TPPrule_47 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_47(_TPPrule_47 _currn)
#else
void _VS2rule_47(_currn )
_TPPrule_47 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_47(_TPPrule_47 _currn)
#else
void _VS3rule_47(_currn )
_TPPrule_47 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSymOcc_IsDefining=_currn->_ATIsDefining;
/*SPC(1406)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (AND((* _IG_incl6), GetIsTerm(_currn->_desc1->_ATKey, 0))) {
message(ERROR, "A terminal has no attributes", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(871)*/

if (AND(_currn->_ATIsDefining, EQ(_currn->_desc1->_ATKey, TAILKey))) {
message(ERROR, "TAIL must not be defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1536)*/

if (AND(NOT(_currn->_ATIsDefining), EQ(_currn->_desc1->_ATKey, HEADKey))) {
message(ERROR, "HEAD must not be used", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1539)*/
_AVAttrUseId_ScopeKey=_currn->_desc1->_ATKey;
/*SPC(864)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

if (AND(AND(_currn->_ATIsDefining, EQ(_AVSymOcc_AttrClass, INHClass)), AND(NOT((* _IG_incl6)), GetIsChain(_currn->_desc2->_ATKey, 0)))) {
message(ERROR, "CHAIN definition not allowed in upper symbol computation", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(918)*/
_currn->_AT_const7=_currn->_desc2->_ATSym;
/*SPC(863)*/
_currn->_AT_const8=_currn->_desc2->_ATKey;
/*SPC(863)*/
_currn->_ATIsHEADAcc=EQ(_currn->_desc1->_ATKey, HEADKey);
/*SPC(1533)*/
_currn->_ATProdSymbol=_currn->_desc1->_ATProdSymbol;
/*SPC(1532)*/

if (AND(NE(_AVSymOcc_AttrClass, NoClass), NOT(GetIsChain(_currn->_desc2->_ATKey, 0)))) {
SetChkAttrClass(_currn->_desc2->_ATKey, _currn->_desc2->_ATSym, _AVSymOcc_AttrClass, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(904)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_47(_TPPrule_47 _currn,PExpr* _AS0repr)
#else
void _VS4rule_47(_currn ,_AS0repr)
_TPPrule_47 _currn;
PExpr* _AS0repr;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (AND(_AVAttr_IsIterate, GetIsChain(_currn->_desc2->_ATKey, 0))) {
message(ERROR, CatStrInd("ITERATE attribute may not have a CHAIN name: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(989)*/

if (AND(NOT((* _IG_incl6)), AND(GetIsChain(_currn->_desc2->_ATKey, 0), (* _IG_incl13)))) {
message(ERROR, CatStrInd("chain access in upper symbol computation: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1611)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0repr)=
((EQ(_currn->_desc1->_ATKey, HEADKey)
) ? (newHeadAcc(_currn->_desc2->_ATKey, (&( _currn->_AT_pos)))
) : (
((EQ(_currn->_desc1->_ATKey, TAILKey)
) ? (newTailAcc(_currn->_desc2->_ATKey, (&( _currn->_AT_pos)))
) : (
(((* _IG_incl6)
) ? (newAttrAccRule(_currn->_desc1->_ATProdSymbol, _currn->_desc2->_ATKey, GetIsChain(_currn->_desc2->_ATKey, 0), (&( _currn->_AT_pos)))
) : (newAttrAccSymb(_currn->_desc1->_ATKey, _currn->_desc2->_ATKey, GetIsChain(_currn->_desc2->_ATKey, 0), (&( _currn->_AT_pos)))))
))
))
;
/*SPC(1975)*/

if (AND(_currn->_ATIsDefining, NOT(GetIsChain(_currn->_desc2->_ATKey, 0)))) {
ResetIsDefined(_currn->_desc2->_ATKey, 1);

} else {
}
;
/*SPC(1120)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_48(_TPPrule_48 _currn)
#else
void _VS1rule_48(_currn )
_TPPrule_48 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_48(_TPPrule_48 _currn)
#else
void _VS2rule_48(_currn )
_TPPrule_48 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_48(_TPPrule_48 _currn)
#else
void _VS3rule_48(_currn )
_TPPrule_48 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAttrUseId_ScopeKey=_currn->_desc1->_ATKey;
/*SPC(859)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

if (GetIsChain(_currn->_desc2->_ATKey, 0)) {
message(ERROR, "Remote access to a CHAIN not allowed", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(974)*/
ResetIsSymbol(_currn->_desc1->_ATKey, 1);
/*SPC(436)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_48(_TPPrule_48 _currn)
#else
void _VS4rule_48(_currn )
_TPPrule_48 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATuniqueRemAttr_RuleAttr_152=MarkInhTreeSymbAttrs(_currn->_desc1->_ATBind, _currn->_desc2->_ATSym);
/*SPC(1735)*/

if (EQ(_currn->_ATuniqueRemAttr_RuleAttr_152, 0)) {
message(ERROR, CatStrInd("Different attributes of one symbol are not allowed: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1744)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_48(_TPPrule_48 _currn)
#else
void _VS5rule_48(_currn )
_TPPrule_48 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (AND(NOT(GetIsDefined(_currn->_desc1->_ATKey, 0)), NOT(GetIsDefinedReported(_currn->_desc1->_ATKey, 0)))) {
ResetIsDefinedReported(_currn->_desc1->_ATKey, 1);
message(ERROR, CatStrInd("Symbol does not occur in rule or definition: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(1443)*/

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (LT(_currn->_ATuniqueRemAttr_RuleAttr_152, 0)) {
ResetRemoteEpxrIsErr((* _IG_incl18), 1);
message(ERROR, CatStrInd("A terminal inherits this symbol: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;

if (GetIsTerm(KeyOf(_currn->_desc1->_ATBind), 0)) {
ResetRemoteEpxrIsErr((* _IG_incl18), 1);
message(ERROR, CatStrInd("Remote access to a terminal symbol: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
;
/*SPC(1746)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_49(_TPPrule_49 _currn)
#else
void _VS1rule_49(_currn )
_TPPrule_49 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSyntId_IsGenSymbol=0;
/*SPC(580)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_49(_TPPrule_49 _currn)
#else
void _VS2rule_49(_currn )
_TPPrule_49 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_49(_TPPrule_49 _currn)
#else
void _VS3rule_49(_currn )
_TPPrule_49 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsTerm(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("LISTOF element may not be a terminal symbol: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(809)*/

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_50(_TPPrule_50 _currn)
#else
void _VS1rule_50(_currn )
_TPPrule_50 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_50(_TPPrule_50 _currn)
#else
void _VS2rule_50(_currn )
_TPPrule_50 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_50(_TPPrule_50 _currn)
#else
void _VS3rule_50(_currn )
_TPPrule_50 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (NOT(InheritClass((* _IG_incl19), GetAttrScope(_currn->_desc1->_ATKey, NoEnv)))) {
message(ERROR, "Cyclic inheritance", 0, (&( _currn->_AT_pos)));

} else {
InheritClass((* _IG_incl20), GetLowerScope(_currn->_desc1->_ATKey, NoEnv));
InheritClass((* _IG_incl21), GetUpperScope(_currn->_desc1->_ATKey, NoEnv));
InheritClass((* _IG_incl22), GetHEADScope(_currn->_desc1->_ATKey, NoEnv));
;
}
;
/*SPC(1188)*/
ResetIsSymbol(_currn->_desc1->_ATKey, 1);
/*SPC(436)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_50(_TPPrule_50 _currn)
#else
void _VS4rule_50(_currn )
_TPPrule_50 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsTreeSym(_currn->_desc1->_ATKey, 0)) {
message(WARNING, CatStrInd("INHERITS from a TREE symbol: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(697)*/

if (AND(NOT(GetIsDefined(_currn->_desc1->_ATKey, 0)), NOT(GetIsDefinedReported(_currn->_desc1->_ATKey, 0)))) {
ResetIsDefinedReported(_currn->_desc1->_ATKey, 1);
message(ERROR, CatStrInd("Symbol does not occur in rule or definition: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(1443)*/

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_51(_TPPrule_51 _currn)
#else
void _VS1rule_51(_currn )
_TPPrule_51 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVProduction__ProdSymbolauxList=NULLProdSymbolList;
/*SPC(108)*/
_AVSyntLit_cProdSymbolListPtr_post=_ProdSymbolListADDROF(_AVProduction__ProdSymbolauxList);
/*SPC(109)*/
_AVSyntId_IsGenSymbol=0;
/*SPC(580)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVProduction_IsListof=1;
/*SPC(635)*/
_AVProduction_ProdSymbolList=_AVProduction__ProdSymbolauxList;
/*SPC(110)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_51(_TPPrule_51 _currn)
#else
void _VS2rule_51(_currn )
_TPPrule_51 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_51(_TPPrule_51 _currn)
#else
void _VS4rule_51(_currn )
_TPPrule_51 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (AND(GetIsTerm(_currn->_desc1->_ATKey, 0), NOT(GetTermReported(_currn->_desc1->_ATKey, 0)))) {
ResetTermReported(_currn->_desc1->_ATKey, 1);
message(ERROR, CatStrInd("Left-hand side may not be specified TERM: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(789)*/

if (AND(AND(MultipleRoots, GetIsRoot(_currn->_desc1->_ATKey, 0)), NOT(GetRootReported(_currn->_desc1->_ATKey, 0)))) {
ResetRootReported(_currn->_desc1->_ATKey, 1);
message(ERROR, CatStrInd("One of the multiple grammar roots: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(799)*/

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_52(_TPPrule_52 _currn)
#else
void _VS1rule_52(_currn )
_TPPrule_52 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVProduction__ProdSymbolauxList=NULLProdSymbolList;
/*SPC(108)*/
_AVSyntLit_cProdSymbolListPtr_post=_ProdSymbolListADDROF(_AVProduction__ProdSymbolauxList);
/*SPC(109)*/
_AVSyntId_IsGenSymbol=0;
/*SPC(580)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVProduction_IsListof=0;
/*SPC(631)*/
_AVProduction_ProdSymbolList=_AVProduction__ProdSymbolauxList;
/*SPC(110)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_52(_TPPrule_52 _currn)
#else
void _VS2rule_52(_currn )
_TPPrule_52 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_52(_TPPrule_52 _currn)
#else
void _VS3rule_52(_currn )
_TPPrule_52 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_52(_TPPrule_52 _currn)
#else
void _VS4rule_52(_currn )
_TPPrule_52 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (AND(GetIsTerm(_currn->_desc1->_ATKey, 0), NOT(GetTermReported(_currn->_desc1->_ATKey, 0)))) {
ResetTermReported(_currn->_desc1->_ATKey, 1);
message(ERROR, CatStrInd("Left-hand side may not be specified TERM: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(767)*/

if (AND(AND(MultipleRoots, GetIsRoot(_currn->_desc1->_ATKey, 0)), NOT(GetRootReported(_currn->_desc1->_ATKey, 0)))) {
ResetRootReported(_currn->_desc1->_ATKey, 1);
message(ERROR, CatStrInd("One of the multiple grammar roots: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(777)*/

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_53(_TPPrule_53 _currn)
#else
void _VS1rule_53(_currn )
_TPPrule_53 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRuleSpecId_Key=NoKey;
/*SPC(610)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_54(_TPPrule_54 _currn)
#else
void _VS1rule_54(_currn )
_TPPrule_54 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRuleSpecId_Key=_currn->_desc1->_ATKey;
/*SPC(606)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_54(_TPPrule_54 _currn)
#else
void _VS2rule_54(_currn )
_TPPrule_54 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsSymbol(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(460)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_55(_TPPrule_55 _currn)
#else
void _VS1rule_55(_currn )
_TPPrule_55 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_currn->_ATRuleInstance=MakeRuleProd(_AVRuleSpecId_Key, _AVProduction_ProdSymbolList, _AVProduction_IsListof, (&( _currn->_AT_pos)));
/*SPC(598)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_55(_TPPrule_55 _currn)
#else
void _VS2rule_55(_currn )
_TPPrule_55 _currn;

#endif
{
DefTableKey* _IL_incl8;

_VisitVarDecl()
_VisitEntry();
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_currn->_ATKey=RuleKeyOfRuleProd(_currn->_ATRuleInstance);
/*SPC(624)*/
_AVRuleSpec_Rule=GetRule(_currn->_ATKey, NoRuleProd);
/*SPC(626)*/

if (EQ(GetAttrScope(_currn->_ATKey, NoEnv), NoEnv)) {
ResetAttrScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl24)), _currn->_ATKey));

} else {
}
;
/*SPC(831)*/

if (EQ(GetLowerScope(_currn->_ATKey, NoEnv), NoEnv)) {
ResetLowerScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl25)), _currn->_ATKey));

} else {
}
;
/*SPC(1510)*/
_IG_incl8=_IL_incl8;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_55(_TPPrule_55 _currn)
#else
void _VS3rule_55(_currn )
_TPPrule_55 _currn;

#endif
{
int* _IL_incl6;
DefTableKey* _IL_incl8;

_VisitVarDecl()
_VisitEntry();
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATIsRule);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATIsRule=1;
/*SPC(849)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_IG_incl6=_IL_incl6;
_IG_incl8=_IL_incl8;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_55(_TPPrule_55 _currn)
#else
void _VS4rule_55(_currn )
_TPPrule_55 _currn;

#endif
{
int* _IL_incl6;
DefTableKey* _IL_incl8;

_VisitVarDecl()
_VisitEntry();
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATIsRule);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_IG_incl6=_IL_incl6;
_IG_incl8=_IL_incl8;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_55(_TPPrule_55 _currn)
#else
void _VS5rule_55(_currn )
_TPPrule_55 _currn;

#endif
{
int* _IL_incl6;
DefTableKey* _IL_incl8;

_VisitVarDecl()
_VisitEntry();
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATIsRule);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_AVRuleSpec__const20=_AVCompPart__const20;
/*SPC(596)*/
_IG_incl6=_IL_incl6;
_IG_incl8=_IL_incl8;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_56(_TPPrule_56 _currn)
#else
void _VS1rule_56(_currn )
_TPPrule_56 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSyntId_IsGenSymbol=1;
/*SPC(587)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_56(_TPPrule_56 _currn)
#else
void _VS2rule_56(_currn )
_TPPrule_56 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_56(_TPPrule_56 _currn)
#else
void _VS3rule_56(_currn )
_TPPrule_56 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSyntUnit_newGenTreeAttr_RuleAttr_160=SetCoordSymToBinding(BindIdn(GetAttrScope(_currn->_desc1->_ATKey, NoEnv), GENTREEsym), (&( _currn->_AT_pos)), GENTREEsym);
/*SPC(1041)*/
SetChkAttrClass(KeyOf(_AVSyntUnit_newGenTreeAttr_RuleAttr_160), GENTREEsym, INHClass, (&( _currn->_AT_pos)));
SetChkAttrType(KeyOf(_AVSyntUnit_newGenTreeAttr_RuleAttr_160), GENTREEsym, NODEPTRkey, (&( _currn->_AT_pos)));
;
/*SPC(1047)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_56(_TPPrule_56 _currn)
#else
void _VS4rule_56(_currn )
_TPPrule_56 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsTerm(_currn->_desc1->_ATKey, 0)) {
message(WARNING, CatStrInd("Tree insertion is ignored for a terminal symbol: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(819)*/

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_57(_TPPrule_57 _currn)
#else
void _VS1rule_57(_currn )
_TPPrule_57 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSyntLit_ProdSymbolTakeIt=1;
/*SPC(114)*/
_AVSyntLit_ProdSymbolElem=MakeProdLiteral(_currn->_ATTERM_1);
/*SPC(569)*/
_AVSyntLit_cProdSymbolListPtr_post=
((_AVSyntLit_ProdSymbolTakeIt
) ? (RefEndConsProdSymbolList(_AVSyntLit_cProdSymbolListPtr_post, _AVSyntLit_ProdSymbolElem)
) : (_AVSyntLit_cProdSymbolListPtr_post))
;
/*SPC(115)*/

if (EQ(0, strlen(StringTable(_currn->_ATTERM_1)))) {
message(ERROR, "Literal terminal may not be the empty string", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(575)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_58(_TPPrule_58 _currn)
#else
void _VS1rule_58(_currn )
_TPPrule_58 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_58(_TPPrule_58 _currn)
#else
void _VS2rule_58(_currn )
_TPPrule_58 _currn;

#endif
{
int* _IL_incl30;
int* _IL_incl31;
DefTableKey* _IL_incl29;
int* _IL_incl28;

_VisitVarDecl()
_VisitEntry();
_IL_incl30=_IG_incl30;_IG_incl30= &(_currn->_ATIsCLASSSym);
_IL_incl31=_IG_incl31;_IG_incl31= &(_currn->_ATIsTREESym);
_IL_incl29=_IG_incl29;_IG_incl29= &(_currn->_ATTypeKey);
_IL_incl28=_IG_incl28;_IG_incl28= &(_currn->_ATIsTerm);
_currn->_ATTypeKey=_currn->_desc2->_ATKey;
/*SPC(712)*/
_currn->_ATIsTerm=1;
/*SPC(711)*/
_currn->_ATIsCLASSSym=0;
/*SPC(519)*/
_currn->_ATIsTREESym=1;
/*SPC(518)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl30=_IL_incl30;
_IG_incl31=_IL_incl31;
_IG_incl29=_IL_incl29;
_IG_incl28=_IL_incl28;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_58(_TPPrule_58 _currn)
#else
void _VS3rule_58(_currn )
_TPPrule_58 _currn;

#endif
{
int* _IL_incl30;
int* _IL_incl31;
DefTableKey* _IL_incl29;
int* _IL_incl28;

_VisitVarDecl()
_VisitEntry();
_IL_incl30=_IG_incl30;_IG_incl30= &(_currn->_ATIsCLASSSym);
_IL_incl31=_IG_incl31;_IG_incl31= &(_currn->_ATIsTREESym);
_IL_incl29=_IG_incl29;_IG_incl29= &(_currn->_ATTypeKey);
_IL_incl28=_IG_incl28;_IG_incl28= &(_currn->_ATIsTerm);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (GetIsSymbol(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(460)*/

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl30=_IL_incl30;
_IG_incl31=_IL_incl31;
_IG_incl29=_IL_incl29;
_IG_incl28=_IL_incl28;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_59(_TPPrule_59 _currn)
#else
void _VS1rule_59(_currn )
_TPPrule_59 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_59(_TPPrule_59 _currn)
#else
void _VS2rule_59(_currn )
_TPPrule_59 _currn;

#endif
{
DefTableKey* _IL_incl29;
int* _IL_incl28;

_VisitVarDecl()
_VisitEntry();
_IL_incl29=_IG_incl29;_IG_incl29= &(_currn->_ATTypeKey);
_IL_incl28=_IG_incl28;_IG_incl28= &(_currn->_ATIsTerm);
_currn->_ATTypeKey=NoKey;
/*SPC(708)*/
_currn->_ATIsTerm=0;
/*SPC(708)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);
_IG_incl29=_IL_incl29;
_IG_incl28=_IL_incl28;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_59(_TPPrule_59 _currn)
#else
void _VS3rule_59(_currn )
_TPPrule_59 _currn;

#endif
{
DefTableKey* _IL_incl29;
int* _IL_incl28;
Environment* _IL_incl22;
Environment* _IL_incl21;
Environment* _IL_incl20;
Environment* _IL_incl19;
int* _IL_incl6;
DefTableKey* _IL_incl8;

_VisitVarDecl()
_VisitEntry();
_IL_incl29=_IG_incl29;_IG_incl29= &(_currn->_ATTypeKey);
_IL_incl28=_IG_incl28;_IG_incl28= &(_currn->_ATIsTerm);
_IL_incl22=_IG_incl22;_IG_incl22= &(_currn->_ATHEADScope);
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATUpperScope);
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATLowerScope);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATAttrScope);
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATIsRule);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATKey);

if (GetIsTerm(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("A terminal can not inherit computations: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1183)*/
_currn->_ATAttrScope=GetAttrScope(_currn->_desc2->_ATKey, NoEnv);
/*SPC(1174)*/
_currn->_ATHEADScope=GetHEADScope(_currn->_desc2->_ATKey, NoEnv);
/*SPC(1172)*/
_currn->_ATLowerScope=GetLowerScope(_currn->_desc2->_ATKey, NoEnv);
/*SPC(1170)*/
_currn->_ATUpperScope=GetUpperScope(_currn->_desc2->_ATKey, NoEnv);
/*SPC(1168)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_currn->_ATKey=_currn->_desc2->_ATKey;
/*SPC(854)*/
_currn->_ATIsRule=0;
/*SPC(846)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);
_IG_incl29=_IL_incl29;
_IG_incl28=_IL_incl28;
_IG_incl22=_IL_incl22;
_IG_incl21=_IL_incl21;
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl6=_IL_incl6;
_IG_incl8=_IL_incl8;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_59(_TPPrule_59 _currn)
#else
void _VS4rule_59(_currn )
_TPPrule_59 _currn;

#endif
{
int* _IL_incl30;
int* _IL_incl31;
DefTableKey* _IL_incl29;
int* _IL_incl28;
Environment* _IL_incl22;
Environment* _IL_incl21;
Environment* _IL_incl20;
Environment* _IL_incl19;
int* _IL_incl6;
DefTableKey* _IL_incl8;

_VisitVarDecl()
_VisitEntry();
_IL_incl30=_IG_incl30;_IG_incl30= &(_currn->_ATIsCLASSSym);
_IL_incl31=_IG_incl31;_IG_incl31= &(_currn->_ATIsTREESym);
_IL_incl29=_IG_incl29;_IG_incl29= &(_currn->_ATTypeKey);
_IL_incl28=_IG_incl28;_IG_incl28= &(_currn->_ATIsTerm);
_IL_incl22=_IG_incl22;_IG_incl22= &(_currn->_ATHEADScope);
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATUpperScope);
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATLowerScope);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATAttrScope);
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATIsRule);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATKey);
_currn->_ATIsCLASSSym=_currn->_desc1->_ATIsCLASSSym;
/*SPC(515)*/
_currn->_ATIsTREESym=_currn->_desc1->_ATIsTREESym;
/*SPC(514)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);
_IG_incl30=_IL_incl30;
_IG_incl31=_IL_incl31;
_IG_incl29=_IL_incl29;
_IG_incl28=_IL_incl28;
_IG_incl22=_IL_incl22;
_IG_incl21=_IL_incl21;
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl6=_IL_incl6;
_IG_incl8=_IL_incl8;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_59(_TPPrule_59 _currn)
#else
void _VS5rule_59(_currn )
_TPPrule_59 _currn;

#endif
{
int* _IL_incl30;
int* _IL_incl31;
DefTableKey* _IL_incl29;
int* _IL_incl28;
Environment* _IL_incl22;
Environment* _IL_incl21;
Environment* _IL_incl20;
Environment* _IL_incl19;
int* _IL_incl6;
DefTableKey* _IL_incl8;

_VisitVarDecl()
_VisitEntry();
_IL_incl30=_IG_incl30;_IG_incl30= &(_currn->_ATIsCLASSSym);
_IL_incl31=_IG_incl31;_IG_incl31= &(_currn->_ATIsTREESym);
_IL_incl29=_IG_incl29;_IG_incl29= &(_currn->_ATTypeKey);
_IL_incl28=_IG_incl28;_IG_incl28= &(_currn->_ATIsTerm);
_IL_incl22=_IG_incl22;_IG_incl22= &(_currn->_ATHEADScope);
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATUpperScope);
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATLowerScope);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATAttrScope);
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATIsRule);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATKey);
_AVSymCompSpec__DefTableKeyauxList_RuleAttr_163=NULLDefTableKeyList;
/*SPC(1061)*/
_AVSymbolDefId_cDefTableKeyListPtr_post=_DefTableKeyListADDROF(_AVSymCompSpec__DefTableKeyauxList_RuleAttr_163);
/*SPC(1062)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);
_AVSymCompSpec__const20=_AVCompPart__const20;
/*SPC(512)*/
_AVSymCompSpec_isRoot=GetIsRoot(_currn->_desc2->_ATKey, 0);
/*SPC(1177)*/
_IG_incl30=_IL_incl30;
_IG_incl31=_IL_incl31;
_IG_incl29=_IL_incl29;
_IG_incl28=_IL_incl28;
_IG_incl22=_IL_incl22;
_IG_incl21=_IL_incl21;
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl6=_IL_incl6;
_IG_incl8=_IL_incl8;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_60(_TPPrule_60 _currn)
#else
void _VS1rule_60(_currn )
_TPPrule_60 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_60(_TPPrule_60 _currn)
#else
void _VS2rule_60(_currn )
_TPPrule_60 _currn;

#endif
{
int* _IL_incl30;
int* _IL_incl31;
DefTableKey* _IL_incl29;
int* _IL_incl28;

_VisitVarDecl()
_VisitEntry();
_IL_incl30=_IG_incl30;_IG_incl30= &(_currn->_ATIsCLASSSym);
_IL_incl31=_IG_incl31;_IG_incl31= &(_currn->_ATIsTREESym);
_IL_incl29=_IG_incl29;_IG_incl29= &(_currn->_ATTypeKey);
_IL_incl28=_IG_incl28;_IG_incl28= &(_currn->_ATIsTerm);
_currn->_ATTypeKey=NoKey;
/*SPC(705)*/
_currn->_ATIsTerm=0;
/*SPC(705)*/
_currn->_ATIsCLASSSym=_currn->_desc1->_ATIsCLASSSym;
/*SPC(510)*/
_currn->_ATIsTREESym=_currn->_desc1->_ATIsTREESym;
/*SPC(509)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl30=_IL_incl30;
_IG_incl31=_IL_incl31;
_IG_incl29=_IL_incl29;
_IG_incl28=_IL_incl28;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_60(_TPPrule_60 _currn)
#else
void _VS3rule_60(_currn )
_TPPrule_60 _currn;

#endif
{
DefTableKeyList* _IL_incl37;
int* _IL_incl30;
int* _IL_incl31;
DefTableKey* _IL_incl29;
int* _IL_incl28;

_VisitVarDecl()
_VisitEntry();
_IL_incl37=_IG_incl37;_IG_incl37= &(_currn->_ATSymbolKeyList);
_IL_incl30=_IG_incl30;_IG_incl30= &(_currn->_ATIsCLASSSym);
_IL_incl31=_IG_incl31;_IG_incl31= &(_currn->_ATIsTREESym);
_IL_incl29=_IG_incl29;_IG_incl29= &(_currn->_ATTypeKey);
_IL_incl28=_IG_incl28;_IG_incl28= &(_currn->_ATIsTerm);
_currn->_ATSymbolKeyList=_currn->_desc2->_ATDefTableKeyList;
/*SPC(1000)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_IG_incl37=_IL_incl37;
_IG_incl30=_IL_incl30;
_IG_incl31=_IL_incl31;
_IG_incl29=_IL_incl29;
_IG_incl28=_IL_incl28;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_60(_TPPrule_60 _currn)
#else
void _VS4rule_60(_currn )
_TPPrule_60 _currn;

#endif
{
DefTableKeyList* _IL_incl37;
int* _IL_incl30;
int* _IL_incl31;
DefTableKey* _IL_incl29;
int* _IL_incl28;

_VisitVarDecl()
_VisitEntry();
_IL_incl37=_IG_incl37;_IG_incl37= &(_currn->_ATSymbolKeyList);
_IL_incl30=_IG_incl30;_IG_incl30= &(_currn->_ATIsCLASSSym);
_IL_incl31=_IG_incl31;_IG_incl31= &(_currn->_ATIsTREESym);
_IL_incl29=_IG_incl29;_IG_incl29= &(_currn->_ATTypeKey);
_IL_incl28=_IG_incl28;_IG_incl28= &(_currn->_ATIsTerm);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_IG_incl37=_IL_incl37;
_IG_incl30=_IL_incl30;
_IG_incl31=_IL_incl31;
_IG_incl29=_IL_incl29;
_IG_incl28=_IL_incl28;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_61(_TPPrule_61 _currn)
#else
void _VS1rule_61(_currn )
_TPPrule_61 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATIsCLASSSym=1;
/*SPC(502)*/
_currn->_ATIsTREESym=0;
/*SPC(505)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_62(_TPPrule_62 _currn)
#else
void _VS1rule_62(_currn )
_TPPrule_62 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATIsCLASSSym=0;
/*SPC(505)*/
_currn->_ATIsTREESym=1;
/*SPC(499)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_63(_TPPrule_63 _currn)
#else
void _VS1rule_63(_currn )
_TPPrule_63 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_63(_TPPrule_63 _currn)
#else
void _VS2rule_63(_currn )
_TPPrule_63 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_63(_TPPrule_63 _currn)
#else
void _VS3rule_63(_currn )
_TPPrule_63 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSymbolRef_Key=KeyOf(BindingInEnv((* _IG_incl26), _currn->_desc1->_ATSym));
/*SPC(1322)*/
_AVSymbolRef_ProdSymbol_RuleAttr_167=
((AND((* _IG_incl6), GetIsTerm(_AVSymbolRef_Key, 0))
) ? (FindSymbolRef(GetRule((* _IG_incl8), NoRuleProd), _AVSymbolRef_Key, _currn->_desc2->_ATValue)
) : (NoProdSymbol))
;
/*SPC(1325)*/
_AVSymbolRef_occs_RuleAttr_167=
(((* _IG_incl6)
) ? (CountSymbolRef(GetRule((* _IG_incl8), NoRuleProd), _AVSymbolRef_Key)
) : (0))
;
/*SPC(1339)*/
_AVSymbolRef_Pos=
((NE(_AVSymbolRef_ProdSymbol_RuleAttr_167, NoProdSymbol)
) ? (PosOfProdSymbol(_AVSymbolRef_ProdSymbol_RuleAttr_167)
) : (SUB(0, 1)))
;
/*SPC(1335)*/
_AVSymbolRef_repr=
((EQ(_AVSymbolRef_ProdSymbol_RuleAttr_167, NoProdSymbol)
) ? (newName(_currn->_desc1->_ATSym, (&( _currn->_AT_pos)))
) : (newRuleTermAcc(_AVSymbolRef_Pos, _AVSymbolRef_Key, (&( _currn->_AT_pos)))))
;
/*SPC(1964)*/

if ((* _IG_incl6)) {

if (GetIsNonterm(_AVSymbolRef_Key, 0)) {

if (GT(_AVSymbolRef_occs_RuleAttr_167, 0)) {
message(ERROR, "Attribute of nonterminal is missing", 0, (&( _currn->_AT_pos)));

if (AND(GT(_currn->_desc2->_ATValue, 0), GT(_currn->_desc2->_ATValue, _AVSymbolRef_occs_RuleAttr_167))) {
message(ERROR, "Wrong index of nonterminal occurrence", 0, (&( _currn->_AT_pos)));

} else {
}
;
;

} else {

if (GT(_currn->_desc2->_ATValue, 0)) {
message(ERROR, "Symbol does not occur in rule", 0, (&( _currn->_AT_pos)));

} else {
}
;
}
;

} else {

if (GetIsTerm(_AVSymbolRef_Key, 0)) {

if (AND(GT(_AVSymbolRef_occs_RuleAttr_167, 0), AND(GT(_currn->_desc2->_ATValue, 0), GT(_currn->_desc2->_ATValue, _AVSymbolRef_occs_RuleAttr_167)))) {
message(ERROR, "Wrong index of terminal occurrence", 0, (&( _currn->_AT_pos)));

} else {

if (AND(EQ(_AVSymbolRef_occs_RuleAttr_167, 0), GT(_currn->_desc2->_ATValue, 0))) {
message(ERROR, "Symbol does not occur in rule", 0, (&( _currn->_AT_pos)));

} else {
}
;
}
;

} else {

if (GT(_currn->_desc2->_ATValue, 0)) {
message(ERROR, "Only symbols may be indexed", 0, (&( _currn->_AT_pos)));

} else {
}
;
}
;
}
;

} else {

if (GT(_currn->_desc2->_ATValue, 0)) {
message(ERROR, "Indexed name is not allowed", 0, (&( _currn->_AT_pos)));

} else {
}
;
}
;
/*SPC(1381)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_138(_TPPrule_138 _currn)
#else
void _VS1rule_138(_currn )
_TPPrule_138 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTypeId_Bind=BindIdn((* _IG_incl26), _currn->_ATSym);
/*SPC(47)*/
_currn->_ATKey=KeyOf(_AVTypeId_Bind);
/*SPC(49)*/
ResetIsType(_currn->_ATKey, 1);
/*SPC(452)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(414)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_137(_TPPrule_137 _currn)
#else
void _VS1rule_137(_currn )
_TPPrule_137 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_136(_TPPrule_136 _currn)
#else
void _VS1rule_136(_currn )
_TPPrule_136 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSyntId_IsGenSymbol=0;
/*SPC(580)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_136(_TPPrule_136 _currn)
#else
void _VS2rule_136(_currn )
_TPPrule_136 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_136(_TPPrule_136 _currn)
#else
void _VS4rule_136(_currn )
_TPPrule_136 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_135(_TPPrule_135 _currn)
#else
void _VS1rule_135(_currn )
_TPPrule_135 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_135(_TPPrule_135 _currn)
#else
void _VS2rule_135(_currn )
_TPPrule_135 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_135(_TPPrule_135 _currn)
#else
void _VS3rule_135(_currn )
_TPPrule_135 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_135(_TPPrule_135 _currn)
#else
void _VS4rule_135(_currn )
_TPPrule_135 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_133(_TPPrule_133 _currn)
#else
void _VS1rule_133(_currn )
_TPPrule_133 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSyntId_ProdSymbolTakeIt=1;
/*SPC(114)*/
_AVSyntId_Bind=BindIdn((* _IG_incl26), _currn->_ATSym);
/*SPC(47)*/
_currn->_ATKey=KeyOf(_AVSyntId_Bind);
/*SPC(49)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(414)*/
_AVSyntId_ProdSymbolElem=MakeProdSymbol(_currn->_ATKey, _AVSyntId_IsGenSymbol, (&( _currn->_AT_pos)));
/*SPC(582)*/
_AVSyntLit_cProdSymbolListPtr_post=
((_AVSyntId_ProdSymbolTakeIt
) ? (RefEndConsProdSymbolList(_AVSyntLit_cProdSymbolListPtr_post, _AVSyntId_ProdSymbolElem)
) : (_AVSyntLit_cProdSymbolListPtr_post))
;
/*SPC(115)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_133(_TPPrule_133 _currn)
#else
void _VS2rule_133(_currn )
_TPPrule_133 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (EQ(GetUpperScope(_currn->_ATKey, NoEnv), NoEnv)) {
ResetUpperScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl25)), _currn->_ATKey));
ResetLowerScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl25)), _currn->_ATKey));
ResetHEADScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl25)), _currn->_ATKey));
;

} else {
}
;
/*SPC(1145)*/

if (EQ(GetAttrScope(_currn->_ATKey, NoEnv), NoEnv)) {
ResetAttrScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl24)), _currn->_ATKey));

} else {
}
;
/*SPC(831)*/
ResetIsDefined(_currn->_ATKey, 1);
/*SPC(1439)*/
ResetIsTreeSym(_currn->_ATKey, 1);
/*SPC(654)*/
ResetIsSymbol(_currn->_ATKey, 1);
/*SPC(448)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_133(_TPPrule_133 _currn)
#else
void _VS3rule_133(_currn )
_TPPrule_133 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (AND(GetIsCLASSSym(_currn->_ATKey, 0), NOT(GetIsClassInRuleReported(_currn->_ATKey, 0)))) {
ResetIsClassInRuleReported(_currn->_ATKey, 1);
message(ERROR, CatStrInd("May not occur in a RULE: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(664)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_132(_TPPrule_132 _currn)
#else
void _VS1rule_132(_currn )
_TPPrule_132 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_132(_TPPrule_132 _currn)
#else
void _VS3rule_132(_currn )
_TPPrule_132 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATKey=
(((* _IG_incl6)
) ? (NoKey
) : ((* _IG_incl8)))
;
/*SPC(1227)*/
_currn->_ATProdSymbol=NoProdSymbol;
/*SPC(1236)*/
_AVSymOcc_AttrClass=NoClass;
/*SPC(1225)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_132(_TPPrule_132 _currn)
#else
void _VS4rule_132(_currn )
_TPPrule_132 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if ((* _IG_incl6)) {
message(ERROR, "Not allowed in RULE computation", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1230)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_131(_TPPrule_131 _currn)
#else
void _VS1rule_131(_currn )
_TPPrule_131 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATIsCLASSSym=0;
/*SPC(505)*/
_currn->_ATIsTREESym=0;
/*SPC(505)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_130(_TPPrule_130 _currn)
#else
void _VS1rule_130(_currn )
_TPPrule_130 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATBind=BindIdn((* _IG_incl26), _currn->_ATSym);
/*SPC(47)*/
_currn->_ATKey=KeyOf(_currn->_ATBind);
/*SPC(49)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(414)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_130(_TPPrule_130 _currn)
#else
void _VS2rule_130(_currn )
_TPPrule_130 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (EQ(GetUpperScope(_currn->_ATKey, NoEnv), NoEnv)) {
ResetUpperScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl25)), _currn->_ATKey));
ResetLowerScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl25)), _currn->_ATKey));
ResetHEADScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl25)), _currn->_ATKey));
;

} else {
}
;
/*SPC(1145)*/

if (EQ(GetAttrScope(_currn->_ATKey, NoEnv), NoEnv)) {
ResetAttrScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl24)), _currn->_ATKey));

} else {
}
;
/*SPC(831)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_129(_TPPrule_129 _currn)
#else
void _VS1rule_129(_currn )
_TPPrule_129 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_129(_TPPrule_129 _currn)
#else
void _VS2rule_129(_currn )
_TPPrule_129 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSymbolDefIds__DefTableKeyauxList=NULLDefTableKeyList;
/*SPC(209)*/
_AVSymbolDefId_cDefTableKeyListPtr_post=_DefTableKeyListADDROF(_AVSymbolDefIds__DefTableKeyauxList);
/*SPC(210)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATDefTableKeyList=_AVSymbolDefIds__DefTableKeyauxList;
/*SPC(211)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_129(_TPPrule_129 _currn)
#else
void _VS3rule_129(_currn )
_TPPrule_129 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_128(_TPPrule_128 _currn)
#else
void _VS1rule_128(_currn )
_TPPrule_128 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSymbolDefId_Bind=BindIdn((* _IG_incl26), _currn->_ATSym);
/*SPC(47)*/
_currn->_ATKey=KeyOf(_AVSymbolDefId_Bind);
/*SPC(49)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(414)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_128(_TPPrule_128 _currn)
#else
void _VS2rule_128(_currn )
_TPPrule_128 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (EQ(GetUpperScope(_currn->_ATKey, NoEnv), NoEnv)) {
ResetUpperScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl25)), _currn->_ATKey));
ResetLowerScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl25)), _currn->_ATKey));
ResetHEADScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl25)), _currn->_ATKey));
;

} else {
}
;
/*SPC(1145)*/

if (EQ(GetAttrScope(_currn->_ATKey, NoEnv), NoEnv)) {
ResetAttrScope(_currn->_ATKey, AddKeyToEnv(NewScope((* _IG_incl24)), _currn->_ATKey));

} else {
}
;
/*SPC(831)*/

if ((* _IG_incl28)) {
ResetIsTerm(_currn->_ATKey, 1);
SetDiffType(_currn->_ATKey, (* _IG_incl29), ErrorType);
;

} else {
}
;
/*SPC(716)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_128(_TPPrule_128 _currn)
#else
void _VS3rule_128(_currn )
_TPPrule_128 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
ResetIsDefined(_currn->_ATKey, 1);
/*SPC(1436)*/

if ((* _IG_incl31)) {
ResetIsTREESym(_currn->_ATKey, 1);

} else {
}
;

if ((* _IG_incl30)) {
ResetIsCLASSSym(_currn->_ATKey, 1);

} else {
}
;
;
/*SPC(524)*/
ResetIsSymbol(_currn->_ATKey, 1);
/*SPC(432)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_128(_TPPrule_128 _currn)
#else
void _VS4rule_128(_currn )
_TPPrule_128 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSymbolDefId_DefTableKeyTakeIt=1;
/*SPC(215)*/
_AVSymbolDefId_DefTableKeyElem=_currn->_ATKey;
/*SPC(995)*/
_AVSymbolDefId_cDefTableKeyListPtr_post=
((_AVSymbolDefId_DefTableKeyTakeIt
) ? (RefEndConsDefTableKeyList(_AVSymbolDefId_cDefTableKeyListPtr_post, _AVSymbolDefId_DefTableKeyElem)
) : (_AVSymbolDefId_cDefTableKeyListPtr_post))
;
/*SPC(216)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_128(_TPPrule_128 _currn)
#else
void _VS5rule_128(_currn )
_TPPrule_128 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (AND((* _IG_incl28), GetIsNonterm(_currn->_ATKey, 0))) {
message(ERROR, CatStrInd("Terminal occurs on left-hand side of a production: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(755)*/

if (AND((* _IG_incl28), EQ(GetType(_currn->_ATKey, NoKey), ErrorType))) {
message(ERROR, CatStrInd("inconsistent types of terminal: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(735)*/

if (AND(GetIsTreeSym(_currn->_ATKey, 0), AND((* _IG_incl30), NOT(GetIsInRuleReported(_currn->_ATKey, 0))))) {
ResetIsInRuleReported(_currn->_ATKey, 1);
message(ERROR, CatStrInd("May not occur in a RULE: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(688)*/

if (AND(NOT(GetIsTreeSym(_currn->_ATKey, 0)), AND((* _IG_incl31), NOT(GetIsNotInRuleReported(_currn->_ATKey, 0))))) {
ResetIsNotInRuleReported(_currn->_ATKey, 1);
message(ERROR, CatStrInd("Does not occur in a RULE: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(677)*/

if (AND(GetIsTREESym(_currn->_ATKey, 0), AND((* _IG_incl30), NOT(GetIsCLASSReported(_currn->_ATKey, 0))))) {
ResetIsCLASSReported(_currn->_ATKey, 1);
message(ERROR, CatStrInd("Occurs as TREE symbol, too: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(558)*/

if (AND(GetIsCLASSSym(_currn->_ATKey, 0), AND((* _IG_incl31), NOT(GetIsTREEReported(_currn->_ATKey, 0))))) {
ResetIsTREEReported(_currn->_ATKey, 1);
message(ERROR, CatStrInd("Occurs as CLASS symbol, too: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(547)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_127(_TPPrule_127 _currn)
#else
void _VS3rule_127(_currn )
_TPPrule_127 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSubtree_SubtreeNo=0;
/*SPC(1803)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_126(_TPPrule_126 _currn)
#else
void _VS5rule_126(_currn )
_TPPrule_126 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVSpec__const20=PTGNull();
/*SPC(2353)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_125(_TPPrule_125 _currn)
#else
void _VS3rule_125(_currn )
_TPPrule_125 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_125(_TPPrule_125 _currn)
#else
void _VS5rule_125(_currn )
_TPPrule_125 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVSpec__const20=_AVSymCompSpec__const20;
/*SPC(2349)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_124(_TPPrule_124 _currn)
#else
void _VS5rule_124(_currn )
_TPPrule_124 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVSpec__const20=PTGNull();
/*SPC(2345)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_123(_TPPrule_123 _currn)
#else
void _VS5rule_123(_currn )
_TPPrule_123 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVSpecs__const20=PTGSeq(_AVSpecs__const20, _AVSpec__const20);
/*SPC(2341)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_122(_TPPrule_122 _currn)
#else
void _VS5rule_122(_currn )
_TPPrule_122 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSpecs__const20=PTGNull();
/*SPC(2337)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_121(_TPPrule_121 _currn)
#else
void _VS5rule_121(_currn )
_TPPrule_121 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVSpec__const20=_AVRuleSpec__const20;
/*SPC(2333)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_120(_TPPrule_120 _currn)
#else
void _VS5rule_120(_currn )
_TPPrule_120 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVSpec__const20=PTGNull();
/*SPC(2329)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_119(_TPPrule_119 _currn)
#else
void _VS5rule_119(_currn )
_TPPrule_119 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVSpec__const20=PTGNull();
/*SPC(2325)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_113(_TPPrule_113 _currn)
#else
void _VS1rule_113(_currn )
_TPPrule_113 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRuleId_Bind=BindIdn((* _IG_incl26), _currn->_ATSym);
/*SPC(47)*/
_currn->_ATKey=KeyOf(_AVRuleId_Bind);
/*SPC(49)*/
ResetIsRule(_currn->_ATKey, 1);
/*SPC(456)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(414)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_112(_TPPrule_112 _currn)
#else
void _VS4rule_112(_currn )
_TPPrule_112 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
UnsetRemoteAttr();
/*SPC(1725)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRemoteClause_RemoteSet=MakeRemoteSet();
/*SPC(1728)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_112(_TPPrule_112 _currn)
#else
void _VS5rule_112(_currn )
_TPPrule_112 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_111(_TPPrule_111 _currn)
#else
void _VS4rule_111(_currn )
_TPPrule_111 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
UnsetRemoteAttr();
/*SPC(1725)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRemoteClause_RemoteSet=MakeRemoteSet();
/*SPC(1728)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_110(_TPPrule_110 _currn)
#else
void _VS5rule_110(_currn )
_TPPrule_110 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_108(_TPPrule_108 _currn)
#else
void _VS1rule_108(_currn )
_TPPrule_108 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_108(_TPPrule_108 _currn)
#else
void _VS2rule_108(_currn )
_TPPrule_108 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_108(_TPPrule_108 _currn)
#else
void _VS3rule_108(_currn )
_TPPrule_108 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPlainComp_CompScope=GetLowerScope((* _IG_incl8), NoEnv);
/*SPC(1618)*/
_currn->_ATBind=BindNewPlainComp(_AVPlainComp_CompScope, GetAttrScope((* _IG_incl8), NoEnv), (&( _currn->_AT_pos)));
/*SPC(1622)*/
_currn->_ATBUAssignAttr=
(((* _IG_incl32)
) ? (CreateBUAssignAttr((* _IG_incl8), GetAttribute(KeyOf(_currn->_ATBind), NoKey), (&( _currn->_AT_pos)))
) : (NoKey))
;
/*SPC(1863)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_108(_TPPrule_108 _currn)
#else
void _VS4rule_108(_currn )
_TPPrule_108 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPlainComp_repr=
(((* _IG_incl32)
) ? (TurnPlainBUIntoAssign((* _IG_incl8), _currn->_ATBUAssignAttr, _AVLoop_repr, (&( _currn->_AT_pos)))
) : (_AVLoop_repr))
;
/*SPC(1872)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_107(_TPPrule_107 _currn)
#else
void _VS1rule_107(_currn )
_TPPrule_107 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_107(_TPPrule_107 _currn)
#else
void _VS2rule_107(_currn )
_TPPrule_107 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_107(_TPPrule_107 _currn)
#else
void _VS3rule_107(_currn )
_TPPrule_107 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPlainComp_CompScope=GetLowerScope((* _IG_incl8), NoEnv);
/*SPC(1618)*/
_currn->_ATBind=BindNewPlainComp(_AVPlainComp_CompScope, GetAttrScope((* _IG_incl8), NoEnv), (&( _currn->_AT_pos)));
/*SPC(1622)*/
_currn->_ATBUAssignAttr=
(((* _IG_incl32)
) ? (CreateBUAssignAttr((* _IG_incl8), GetAttribute(KeyOf(_currn->_ATBind), NoKey), (&( _currn->_AT_pos)))
) : (NoKey))
;
/*SPC(1863)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_107(_TPPrule_107 _currn)
#else
void _VS4rule_107(_currn )
_TPPrule_107 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PExpr*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1repr)));
_AVPlainComp_repr=
(((* _IG_incl32)
) ? (TurnPlainBUIntoAssign((* _IG_incl8), _currn->_ATBUAssignAttr, _AS1repr, (&( _currn->_AT_pos)))
) : (_AS1repr))
;
/*SPC(1872)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_106(_TPPrule_106 _currn)
#else
void _VS4rule_106(_currn )
_TPPrule_106 _currn;

#endif
{
PExprListPtr _AS1_cPExprListPtr_pre;

_VisitVarDecl()
_VisitEntry();
_AS1_cPExprListPtr_pre=_AVParam_cPExprListPtr_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,PExprListPtr*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_cPExprListPtr_pre)));
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_105(_TPPrule_105 _currn)
#else
void _VS4rule_105(_currn )
_TPPrule_105 _currn;

#endif
{
PExprListPtr _AS1_cPExprListPtr_pre;

_VisitVarDecl()
_VisitEntry();
_AS1_cPExprListPtr_pre=_AVParam_cPExprListPtr_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,PExprListPtr*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_cPExprListPtr_pre)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_104(_TPPrule_104 _currn,PExprList* _AS0_PExprauxList)
#else
void _VS4rule_104(_currn ,_AS0_PExprauxList)
_TPPrule_104 _currn;
PExprList* _AS0_PExprauxList;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0_PExprauxList)=NULLPExprList;
/*SPC(310)*/
_AVParam_cPExprListPtr_post=_PExprListADDROF((* _AS0_PExprauxList));
/*SPC(311)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVParamsOpt_PExprList=(* _AS0_PExprauxList);
/*SPC(312)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_103(_TPPrule_103 _currn,PExprList* _AS0_PExprauxList)
#else
void _VS4rule_103(_currn ,_AS0_PExprauxList)
_TPPrule_103 _currn;
PExprList* _AS0_PExprauxList;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0_PExprauxList)=NULLPExprList;
/*SPC(310)*/
_AVParamsOpt_HEAD$48_RuleAttr_203=_PExprListADDROF((* _AS0_PExprauxList));
/*SPC(311)*/
_AVParamsOpt_PExprList=(* _AS0_PExprauxList);
/*SPC(312)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_102(_TPPrule_102 _currn,PExprListPtr* _AS0_cPExprListPtr_pre)
#else
void _VS4rule_102(_currn ,_AS0_cPExprListPtr_pre)
_TPPrule_102 _currn;
PExprListPtr* _AS0_cPExprListPtr_pre;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PExpr*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1repr)));
_AVParam_PExprTakeIt=1;
/*SPC(316)*/
_AVParam_PExprElem=_AS1repr;
/*SPC(1920)*/
_AVParam_cPExprListPtr_post=
((_AVParam_PExprTakeIt
) ? (RefEndConsPExprList((* _AS0_cPExprListPtr_pre), _AVParam_PExprElem)
) : ((* _AS0_cPExprListPtr_pre)))
;
/*SPC(317)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_97(_TPPrule_97 _currn)
#else
void _VS1rule_97(_currn )
_TPPrule_97 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_97(_TPPrule_97 _currn)
#else
void _VS2rule_97(_currn )
_TPPrule_97 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_97(_TPPrule_97 _currn)
#else
void _VS3rule_97(_currn )
_TPPrule_97 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_96(_TPPrule_96 _currn)
#else
void _VS1rule_96(_currn )
_TPPrule_96 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_96(_TPPrule_96 _currn)
#else
void _VS2rule_96(_currn )
_TPPrule_96 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_96(_TPPrule_96 _currn)
#else
void _VS3rule_96(_currn )
_TPPrule_96 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(480)*/

if (GetIsType(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(470)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_93(_TPPrule_93 _currn)
#else
void _VS4rule_93(_currn )
_TPPrule_93 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDepClause__PExprauxList=NULLPExprList;
/*SPC(310)*/
_AVParam_cPExprListPtr_post=_PExprListADDROF(_AVDepClause__PExprauxList);
/*SPC(311)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVDepClause_PExprList=_AVDepClause__PExprauxList;
/*SPC(312)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_92(_TPPrule_92 _currn)
#else
void _VS4rule_92(_currn )
_TPPrule_92 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDepClause__PExprauxList=NULLPExprList;
/*SPC(310)*/
_AVParam_cPExprListPtr_post=_PExprListADDROF(_AVDepClause__PExprauxList);
/*SPC(311)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVDepClause_PExprList=_AVDepClause__PExprauxList;
/*SPC(312)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_89(_TPPrule_89 _currn)
#else
void _VS4rule_89(_currn )
_TPPrule_89 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDepAttr_PExprTakeIt=1;
/*SPC(316)*/
_AVDepAttr_PExprElem=_currn->_desc1->_ATrepr;
/*SPC(1910)*/
_AVParam_cPExprListPtr_post=
((_AVDepAttr_PExprTakeIt
) ? (RefEndConsPExprList(_AVParam_cPExprListPtr_post, _AVDepAttr_PExprElem)
) : (_AVParam_cPExprListPtr_post))
;
/*SPC(317)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_88(_TPPrule_88 _currn)
#else
void _VS4rule_88(_currn )
_TPPrule_88 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVDepAttr_PExprTakeIt=1;
/*SPC(316)*/
_AVDepAttr_PExprElem=_AVRemoteExpression_repr;
/*SPC(1910)*/
_AVParam_cPExprListPtr_post=
((_AVDepAttr_PExprTakeIt
) ? (RefEndConsPExprList(_AVParam_cPExprListPtr_post, _AVDepAttr_PExprElem)
) : (_AVParam_cPExprListPtr_post))
;
/*SPC(317)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_87(_TPPrule_87 _currn)
#else
void _VS3rule_87(_currn )
_TPPrule_87 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATIsDefining=0;
/*SPC(1402)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_87(_TPPrule_87 _currn)
#else
void _VS4rule_87(_currn )
_TPPrule_87 _currn;

#endif
{
PExpr _AS1repr;

_VisitVarDecl()
_VisitEntry();
_AVAttr_IsIterate=0;
/*SPC(982)*/
(*(_CALL_VS_((NODEPTR ,PExpr*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1repr)));
_AVDepAttr_PExprTakeIt=1;
/*SPC(316)*/
_AVDepAttr_PExprElem=_AS1repr;
/*SPC(1910)*/
_AVParam_cPExprListPtr_post=
((_AVDepAttr_PExprTakeIt
) ? (RefEndConsPExprList(_AVParam_cPExprListPtr_post, _AVDepAttr_PExprElem)
) : (_AVParam_cPExprListPtr_post))
;
/*SPC(317)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_86(_TPPrule_86 _currn)
#else
void _VS5rule_86(_currn )
_TPPrule_86 _currn;

#endif
{
PTGNode _AS1_const20;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const20)));
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVComputations__const20=PTGSeq(_AS1_const20, _AVComputations__const20);
/*SPC(2193)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_85(_TPPrule_85 _currn)
#else
void _VS5rule_85(_currn )
_TPPrule_85 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVComputations__const20=PTGNull();
/*SPC(2189)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_84(_TPPrule_84 _currn)
#else
void _VS3rule_84(_currn )
_TPPrule_84 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATIsBottomUp=0;
/*SPC(1672)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_84(_TPPrule_84 _currn,PTGNode* _AS0_const20)
#else
void _VS5rule_84(_currn ,_AS0_const20)
_TPPrule_84 _currn;
PTGNode* _AS0_const20;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0_const20)=IDENTICAL(_AVCompute_InhComps);
/*SPC(2185)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_83(_TPPrule_83 _currn)
#else
void _VS5rule_83(_currn )
_TPPrule_83 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVCompPart__const20=_AVComputations__const20;
/*SPC(2181)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_82(_TPPrule_82 _currn)
#else
void _VS5rule_82(_currn )
_TPPrule_82 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVCompPart__const20=PTGNull();
/*SPC(2177)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_79(_TPPrule_79 _currn)
#else
void _VS1rule_79(_currn )
_TPPrule_79 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVChainName_Bind=BindIdn((* _IG_incl17), _currn->_ATSym);
/*SPC(892)*/
_currn->_ATKey=KeyOf(_AVChainName_Bind);
/*SPC(49)*/
ResetIsChain(_currn->_ATKey, 1);
/*SPC(893)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(414)*/

if (IsPredefSym(_currn->_ATSym)) {
message(ERROR, CatStrInd("Predefined name is not allowed: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1503)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_79(_TPPrule_79 _currn)
#else
void _VS2rule_79(_currn )
_TPPrule_79 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (NE(BindingInScope((* _IG_incl33), _currn->_ATSym), NoBinding)) {
message(ERROR, CatStrInd("There is an ATTR definition elsewhere: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1115)*/
SetChkAttrType(_currn->_ATKey, _currn->_ATSym, (* _IG_incl34), (&( _currn->_AT_pos)));
/*SPC(1106)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_76(_TPPrule_76 _currn)
#else
void _VS1rule_76(_currn )
_TPPrule_76 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAttrName_Bind=SetCoordSymToBinding(BindIdn((* _IG_incl33), _currn->_ATSym), (&( _currn->_AT_pos)), _currn->_ATSym);
/*SPC(1080)*/
_currn->_ATKey=KeyOf(_AVAttrName_Bind);
/*SPC(49)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(414)*/

if (IsPredefSym(_currn->_ATSym)) {
message(ERROR, CatStrInd("Predefined name is not allowed: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1503)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_76(_TPPrule_76 _currn)
#else
void _VS2rule_76(_currn )
_TPPrule_76 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (NE(BindingInScope((* _IG_incl17), _currn->_ATSym), NoBinding)) {
message(ERROR, CatStrInd("There is a CHAIN definition elsewhere: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1097)*/
SetChkAttrClass(_currn->_ATKey, _currn->_ATSym, (* _IG_incl35), (&( _currn->_AT_pos)));
SetChkAttrType(_currn->_ATKey, _currn->_ATSym, (* _IG_incl36), (&( _currn->_AT_pos)));
;
/*SPC(1085)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_69(_TPPrule_69 _currn)
#else
void _VS1rule_69(_currn )
_TPPrule_69 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAttrDefId_Sym=_currn->_ATTERM_1;
/*SPC(411)*/
BindDefAttrs(_AVAttrDefId_Sym, (* _IG_incl37), (* _IG_incl17), (* _IG_incl38), (* _IG_incl39), (&( _currn->_AT_pos)));
/*SPC(1028)*/

if (IsPredefSym(_AVAttrDefId_Sym)) {
message(ERROR, CatStrInd("Predefined name is not allowed: ", _AVAttrDefId_Sym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(1503)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_68(_TPPrule_68 _currn)
#else
void _VS1rule_68(_currn )
_TPPrule_68 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_68(_TPPrule_68 _currn)
#else
void _VS2rule_68(_currn )
_TPPrule_68 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_68(_TPPrule_68 _currn)
#else
void _VS3rule_68(_currn )
_TPPrule_68 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_68(_TPPrule_68 _currn)
#else
void _VS4rule_68(_currn )
_TPPrule_68 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVAttrComp__const3=_currn->_desc1->_ATBind;
/*SPC(2121)*/
_currn->_AT_const4=_AVDefAttr_IsUpperSymbComp;
/*SPC(2121)*/
_currn->_ATisAccu=0;
/*SPC(2102)*/
_AVAttrComp_IsChainStart=NoKey;
/*SPC(1651)*/
ResetHasNonAccuAsgn(_currn->_desc1->_ATAttrKey, 1);
/*SPC(2095)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_68(_TPPrule_68 _currn)
#else
void _VS5rule_68(_currn )
_TPPrule_68 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDefAttr_hasAccuToken=0;
/*SPC(2055)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVAttrComp_repr=newAssign(_AVDefAttr_repr, _AVLoop_repr, (&( _currn->_AT_pos)));
/*SPC(1853)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_64(_TPPrule_64 _currn)
#else
void _VS1rule_64(_currn )
_TPPrule_64 _currn;

#endif
{
Environment* _IL_incl33;
Environment* _IL_incl26;
Environment* _IL_incl25;
Environment* _IL_incl24;
Environment* _IL_incl17;

_VisitVarDecl()
_VisitEntry();
_IL_incl33=_IG_incl33;_IG_incl33= &(_currn->_ATAttrNameEnv);
_IL_incl26=_IG_incl26;_IG_incl26= &(_currn->_ATEnv);
_IL_incl25=_IG_incl25;_IG_incl25= &(_currn->_ATSymbolEnv);
_IL_incl24=_IG_incl24;_IG_incl24= &(_currn->_ATAttrEnv);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATChainScope);
_currn->_ATSymbolEnv=NewEnv();
/*SPC(1489)*/
_currn->_ATAttrNameEnv=NewEnv();
/*SPC(1488)*/
_currn->_ATChainScope=NewScope(_currn->_ATAttrNameEnv);
/*SPC(886)*/
_currn->_ATAttrEnv=NewEnv();
/*SPC(1487)*/
_currn->_ATEnv=
(MakePredef(RootEnv, _currn->_ATAttrEnv, _currn->_ATAttrNameEnv, _currn->_ATSymbolEnv), RootEnv)
;
/*SPC(1490)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
MakeGrammar(_currn->_ATEnv);
/*SPC(615)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
PTGOutFile("ligaprod", OutputRules());
/*SPC(641)*/
TransformListofRules(_currn->_ATEnv);
ClassifySymbols();
;
/*SPC(740)*/
MakeSymbOccScopes(_currn->_ATSymbolEnv);
/*SPC(1139)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
MarkGrammarUses(_currn->_ATEnv);
/*SPC(1471)*/
InheritAttributes(_currn->_ATEnv, _currn->_ATAttrNameEnv);
/*SPC(1127)*/
PTGOutFile(CatStrStr(SRCFILE, ".symb"), OutputSymbols(_currn->_ATEnv));
/*SPC(1479)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
InheritCompute(_currn->_ATChainScope);
/*SPC(1675)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
PTGOutFile(CatStrStr(SRCFILE, ".inhcmp"), PTGInhComputations(_AVSpecs__const20));
/*SPC(1687)*/
AccumulateInherit(_currn->_ATEnv);
/*SPC(2041)*/
InheritRepr();
/*SPC(1835)*/
CheckRuleComps();
/*SPC(1838)*/
PTGOutFile(CatStrStr(SRCFILE, ".remote"), RemoteOutput());
/*SPC(1768)*/
_AVAG_TargetDefs=OutputDefs(_currn->_ATEnv, _currn->_ATChainScope);
/*SPC(2012)*/
PTGOutFile(CatStrStr(SRCFILE, ".comp"), ReprOut());
/*SPC(2000)*/
_AVAG_TargetComps=CompOut();
/*SPC(2024)*/
PTGOutFile("liga.out", PTGIdlAttrEval(_AVAG_TargetComps, _AVAG_TargetDefs));
/*SPC(2030)*/
_IG_incl33=_IL_incl33;
_IG_incl26=_IL_incl26;
_IG_incl25=_IL_incl25;
_IG_incl24=_IL_incl24;
_IG_incl17=_IL_incl17;

_VisitExit();
}

