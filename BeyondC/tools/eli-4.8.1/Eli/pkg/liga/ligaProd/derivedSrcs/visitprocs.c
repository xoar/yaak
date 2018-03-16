
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
int* _IG_incl3;
int* _IG_incl5;
Environment* _IG_incl2;
ProdSymbolListPtr _AVSyntLit_cProdSymbolListPtr_post;
DefTableKey _AVRuleSpecId_Key;
DefTableKey _AVRuleSpec_Key;
RuleProd _AVRuleSpec_Rule;
int _AVSyntLit_ProdSymbolTakeIt;
ProdSymbol _AVSyntLit_ProdSymbolElem;
ProdSymbolList _AVProduction__ProdSymbolauxList;
int _AVProduction_IsListof;
ProdSymbolList _AVProduction_ProdSymbolList;
int _AVSymClass_IsCLASSSym;
int _AVSymClass_IsTREESym;
Binding _AVRuleId_Bind;
Binding _AVTypeId_Bind;
int _AVSyntId_ProdSymbolTakeIt;
Binding _AVSyntId_Bind;
ProdSymbol _AVSyntId_ProdSymbolElem;
int _AVSyntId_IsGenSymbol;
Binding _AVSymbolId_Bind;
Binding _AVSymbolDefId_Bind;

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
_AVProduction__ProdSymbolauxList=NULLProdSymbolList;
/*SPC(108)*/
_AVSyntLit_cProdSymbolListPtr_post=_ProdSymbolListADDROF(_AVProduction__ProdSymbolauxList);
/*SPC(109)*/
_AVSyntId_IsGenSymbol=0;
/*SPC(378)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVProduction_IsListof=1;
/*SPC(433)*/
_AVProduction_ProdSymbolList=_AVProduction__ProdSymbolauxList;
/*SPC(110)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_1(_TPPrule_1 _currn)
#else
void _VS2rule_1(_currn )
_TPPrule_1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
_AVProduction__ProdSymbolauxList=NULLProdSymbolList;
/*SPC(108)*/
_AVSyntLit_cProdSymbolListPtr_post=_ProdSymbolListADDROF(_AVProduction__ProdSymbolauxList);
/*SPC(109)*/
_AVSyntId_IsGenSymbol=0;
/*SPC(378)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVProduction_IsListof=0;
/*SPC(429)*/
_AVProduction_ProdSymbolList=_AVProduction__ProdSymbolauxList;
/*SPC(110)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_2(_TPPrule_2 _currn)
#else
void _VS2rule_2(_currn )
_TPPrule_2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_3(_TPPrule_3 _currn)
#else
void _VS1rule_3(_currn )
_TPPrule_3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRuleSpecId_Key=NoKey;
/*SPC(408)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRuleSpecId_Key=_currn->_desc1->_ATKey;
/*SPC(404)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_4(_TPPrule_4 _currn)
#else
void _VS2rule_4(_currn )
_TPPrule_4 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsSymbol(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(258)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_currn->_ATRuleInstance=MakeRuleProd(_AVRuleSpecId_Key, _AVProduction_ProdSymbolList, _AVProduction_IsListof, (&( _currn->_AT_pos)));
/*SPC(396)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_5(_TPPrule_5 _currn)
#else
void _VS2rule_5(_currn )
_TPPrule_5 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_AVRuleSpec_Key=RuleKeyOfRuleProd(_currn->_ATRuleInstance);
/*SPC(422)*/
_AVRuleSpec_Rule=GetRule(_AVRuleSpec_Key, NoRuleProd);
/*SPC(424)*/

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
_AVSyntId_IsGenSymbol=1;
/*SPC(385)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_6(_TPPrule_6 _currn)
#else
void _VS2rule_6(_currn )
_TPPrule_6 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_AVSyntLit_ProdSymbolTakeIt=1;
/*SPC(114)*/
_AVSyntLit_ProdSymbolElem=MakeProdLiteral(_currn->_ATTERM_1);
/*SPC(367)*/
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
/*SPC(373)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_8(_TPPrule_8 _currn)
#else
void _VS1rule_8(_currn )
_TPPrule_8 _currn;

#endif
{
int* _IL_incl3;
int* _IL_incl5;

_VisitVarDecl()
_VisitEntry();
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATIsCLASSSym);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATIsTREESym);
_currn->_ATIsCLASSSym=0;
/*SPC(317)*/
_currn->_ATIsTREESym=1;
/*SPC(316)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl3=_IL_incl3;
_IG_incl5=_IL_incl5;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_8(_TPPrule_8 _currn)
#else
void _VS2rule_8(_currn )
_TPPrule_8 _currn;

#endif
{
int* _IL_incl3;
int* _IL_incl5;

_VisitVarDecl()
_VisitEntry();
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATIsCLASSSym);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATIsTREESym);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (GetIsSymbol(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(258)*/

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl3=_IL_incl3;
_IG_incl5=_IL_incl5;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_9(_TPPrule_9 _currn)
#else
void _VS1rule_9(_currn )
_TPPrule_9 _currn;

#endif
{
int* _IL_incl3;
int* _IL_incl5;

_VisitVarDecl()
_VisitEntry();
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATIsCLASSSym);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATIsTREESym);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATIsCLASSSym=_AVSymClass_IsCLASSSym;
/*SPC(313)*/
_currn->_ATIsTREESym=_AVSymClass_IsTREESym;
/*SPC(312)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);
_IG_incl3=_IL_incl3;
_IG_incl5=_IL_incl5;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_9(_TPPrule_9 _currn)
#else
void _VS2rule_9(_currn )
_TPPrule_9 _currn;

#endif
{
int* _IL_incl3;
int* _IL_incl5;

_VisitVarDecl()
_VisitEntry();
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATIsCLASSSym);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATIsTREESym);

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);
_IG_incl3=_IL_incl3;
_IG_incl5=_IL_incl5;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_10(_TPPrule_10 _currn)
#else
void _VS1rule_10(_currn )
_TPPrule_10 _currn;

#endif
{
int* _IL_incl3;
int* _IL_incl5;

_VisitVarDecl()
_VisitEntry();
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATIsCLASSSym);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATIsTREESym);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATIsCLASSSym=_AVSymClass_IsCLASSSym;
/*SPC(308)*/
_currn->_ATIsTREESym=_AVSymClass_IsTREESym;
/*SPC(307)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_IG_incl3=_IL_incl3;
_IG_incl5=_IL_incl5;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_10(_TPPrule_10 _currn)
#else
void _VS2rule_10(_currn )
_TPPrule_10 _currn;

#endif
{
int* _IL_incl3;
int* _IL_incl5;

_VisitVarDecl()
_VisitEntry();
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATIsCLASSSym);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATIsTREESym);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_IG_incl3=_IL_incl3;
_IG_incl5=_IL_incl5;

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
_AVSymClass_IsCLASSSym=1;
/*SPC(300)*/
_AVSymClass_IsTREESym=0;
/*SPC(303)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_12(_TPPrule_12 _currn)
#else
void _VS1rule_12(_currn )
_TPPrule_12 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSymClass_IsCLASSSym=0;
/*SPC(303)*/
_AVSymClass_IsTREESym=1;
/*SPC(297)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_13(_TPPrule_13 _currn)
#else
void _VS1rule_13(_currn )
_TPPrule_13 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
_AVTypeId_Bind=BindIdn((* _IG_incl2), _currn->_ATSym);
/*SPC(47)*/
_currn->_ATKey=KeyOf(_AVTypeId_Bind);
/*SPC(49)*/
ResetIsType(_currn->_ATKey, 1);
/*SPC(250)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(212)*/

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
/*SPC(378)*/
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

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_AVSyntId_Bind=BindIdn((* _IG_incl2), _currn->_ATSym);
/*SPC(47)*/
_currn->_ATKey=KeyOf(_AVSyntId_Bind);
/*SPC(49)*/
ResetIsSymbol(_currn->_ATKey, 1);
/*SPC(246)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(212)*/
_AVSyntId_ProdSymbolElem=MakeProdSymbol(_currn->_ATKey, _AVSyntId_IsGenSymbol, (&( _currn->_AT_pos)));
/*SPC(380)*/
_AVSyntLit_cProdSymbolListPtr_post=
((_AVSyntId_ProdSymbolTakeIt
) ? (RefEndConsProdSymbolList(_AVSyntLit_cProdSymbolListPtr_post, _AVSyntId_ProdSymbolElem)
) : (_AVSyntLit_cProdSymbolListPtr_post))
;
/*SPC(115)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
ResetIsSymbol(_currn->_desc1->_ATKey, 1);
/*SPC(234)*/

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

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_126(_TPPrule_126 _currn)
#else
void _VS1rule_126(_currn )
_TPPrule_126 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSymClass_IsCLASSSym=0;
/*SPC(303)*/
_AVSymClass_IsTREESym=0;
/*SPC(303)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_125(_TPPrule_125 _currn)
#else
void _VS1rule_125(_currn )
_TPPrule_125 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_124(_TPPrule_124 _currn)
#else
void _VS1rule_124(_currn )
_TPPrule_124 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSymbolId_Bind=BindIdn((* _IG_incl2), _currn->_ATSym);
/*SPC(47)*/
_currn->_ATKey=KeyOf(_AVSymbolId_Bind);
/*SPC(49)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(212)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_123(_TPPrule_123 _currn)
#else
void _VS2rule_123(_currn )
_TPPrule_123 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_122(_TPPrule_122 _currn)
#else
void _VS1rule_122(_currn )
_TPPrule_122 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSymbolDefId_Bind=BindIdn((* _IG_incl2), _currn->_ATSym);
/*SPC(47)*/
_currn->_ATKey=KeyOf(_AVSymbolDefId_Bind);
/*SPC(49)*/
ResetIsSymbol(_currn->_ATKey, 1);
/*SPC(230)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(212)*/

if ((* _IG_incl5)) {
ResetIsTREESym(_currn->_ATKey, 1);

} else {
}
;

if ((* _IG_incl3)) {
ResetIsCLASSSym(_currn->_ATKey, 1);

} else {
}
;
;
/*SPC(322)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_122(_TPPrule_122 _currn)
#else
void _VS2rule_122(_currn )
_TPPrule_122 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (AND(GetIsTREESym(_currn->_ATKey, 0), AND((* _IG_incl3), NOT(GetIsCLASSReported(_currn->_ATKey, 0))))) {
ResetIsCLASSReported(_currn->_ATKey, 1);
message(ERROR, CatStrInd("Occurs as TREE symbol, too: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(356)*/

if (AND(GetIsCLASSSym(_currn->_ATKey, 0), AND((* _IG_incl5), NOT(GetIsTREEReported(_currn->_ATKey, 0))))) {
ResetIsTREEReported(_currn->_ATKey, 1);
message(ERROR, CatStrInd("Occurs as CLASS symbol, too: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(345)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_111(_TPPrule_111 _currn)
#else
void _VS1rule_111(_currn )
_TPPrule_111 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
ResetIsSymbol(_currn->_desc1->_ATKey, 1);
/*SPC(234)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_111(_TPPrule_111 _currn)
#else
void _VS2rule_111(_currn )
_TPPrule_111 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_103(_TPPrule_103 _currn)
#else
void _VS1rule_103(_currn )
_TPPrule_103 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRuleId_Bind=BindIdn((* _IG_incl2), _currn->_ATSym);
/*SPC(47)*/
_currn->_ATKey=KeyOf(_AVRuleId_Bind);
/*SPC(49)*/
ResetIsRule(_currn->_ATKey, 1);
/*SPC(254)*/
ResetNameSym(_currn->_ATKey, _currn->_ATSym);
SetOnceCoord(_currn->_ATKey, (&( _currn->_AT_pos)));
;
/*SPC(212)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_101(_TPPrule_101 _currn)
#else
void _VS1rule_101(_currn )
_TPPrule_101 _currn;

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
void _VS2rule_101(_TPPrule_101 _currn)
#else
void _VS2rule_101(_currn )
_TPPrule_101 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_100(_TPPrule_100 _currn)
#else
void _VS1rule_100(_currn )
_TPPrule_100 _currn;

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
void _VS2rule_100(_TPPrule_100 _currn)
#else
void _VS2rule_100(_currn )
_TPPrule_100 _currn;

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
ResetIsSymbol(_currn->_desc1->_ATKey, 1);
/*SPC(234)*/

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

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_85(_TPPrule_85 _currn)
#else
void _VS1rule_85(_currn )
_TPPrule_85 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
ResetIsSymbol(_currn->_desc1->_ATKey, 1);
/*SPC(234)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_85(_TPPrule_85 _currn)
#else
void _VS2rule_85(_currn )
_TPPrule_85 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_78(_TPPrule_78 _currn)
#else
void _VS1rule_78(_currn )
_TPPrule_78 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_78(_TPPrule_78 _currn)
#else
void _VS2rule_78(_currn )
_TPPrule_78 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_77(_TPPrule_77 _currn)
#else
void _VS1rule_77(_currn )
_TPPrule_77 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_77(_TPPrule_77 _currn)
#else
void _VS2rule_77(_currn )
_TPPrule_77 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_65(_TPPrule_65 _currn)
#else
void _VS1rule_65(_currn )
_TPPrule_65 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_65(_TPPrule_65 _currn)
#else
void _VS2rule_65(_currn )
_TPPrule_65 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsSymbol(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(258)*/

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_42(_TPPrule_42 _currn)
#else
void _VS2rule_42(_currn )
_TPPrule_42 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsSymbol(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(258)*/

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_36(_TPPrule_36 _currn)
#else
void _VS2rule_36(_currn )
_TPPrule_36 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsSymbol(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(258)*/

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

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

if (GetIsSymbol(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as symbol identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(258)*/

if (GetIsRule(_currn->_desc2->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc2->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_23(_TPPrule_23 _currn)
#else
void _VS2rule_23(_currn )
_TPPrule_23 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

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
_AVSyntId_IsGenSymbol=0;
/*SPC(378)*/
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

if (GetIsRule(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as rule identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(278)*/

if (GetIsType(_currn->_desc1->_ATKey, 0)) {
message(ERROR, CatStrInd("Used as type identifier elsewhere: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_14(_TPPrule_14 _currn)
#else
void _VS1rule_14(_currn )
_TPPrule_14 _currn;

#endif
{
Environment* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATEnv);
_currn->_ATEnv=RootEnv;
/*SPC(12)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
MakeGrammar(_currn->_ATEnv);
/*SPC(413)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
PTGOutFile("ligaprod", OutputRules());
/*SPC(439)*/
_IG_incl2=_IL_incl2;

_VisitExit();
}

