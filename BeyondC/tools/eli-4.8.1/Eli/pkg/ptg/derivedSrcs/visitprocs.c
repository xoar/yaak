
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
DefTableKeyList* _IG_incl15;
Environment* _IG_incl14;
int* _IG_incl10;
int* _IG_incl9;
int* _IG_incl7;
int* _IG_incl6;
DefTableKeyList* _IG_incl8;
int* _IG_incl4;
int* _IG_incl3;
Environment* _IG_incl1;
PatElemListPtr _AVCStringNode_cPatElemListPtr_post;
DefTableKeyList _AVFunctionCallinsertPointChain_post;
int _AVFunctionCallinsertionCount_post;
int _AVG2__const2;
PTGNode _AVG1__const12;
PTGNode _AVG1__const13;
PTGNode _AVG1__const14;
int _AVG4__const2;
int _AVG4__const3;
int _AVG4__const4;
int _AVG4__const5;
int _AVG4__const6;
PTGNode _AVG4__const7;
DefTableKeyListPtr _AVArgument_cDefTableKeyListPtr_post;
int _AVArgument__const2;
int _AVArgument__const3;
int _AVArgument__const4;
int _AVArgument__const5;
int _AVArgument__const6;
PTGNode _AVArgument__const7;
int _AVArgument_DefTableKeyTakeIt;
DefTableKey _AVArgument_DefTableKeyElem;
int _AVOptional__const4;
int _AVOptional__const5;
int _AVOptional__const6;
PTGNode _AVOptional__const14;
int _AVOptional_PatElemTakeIt;
PTGNode _AVOptional_code;
PatElem _AVOptional_PatElemElem;
int _AVItem__const2;
PTGNode _AVItem__const21;
int _AVItem_one;
int _AVCStringNode_PatElemTakeIt;
PTGNode _AVCStringNode_code;
int _AVCStringNode_hasValueType;
PatElem _AVCStringNode_PatElemElem;
Binding _AVPatternName_Bind;
PTGNode _AVPatternName_bodyCode;
PTGNode _AVPatternName_emptyResultCode;
PTGNode _AVPatternName_constructorCode;
PTGNode _AVPatternName_printCode;
PTGNode _AVPatternName_structCode;
int _AVPatternName_DoIt;
PTGNode _AVPatternName_implCode;
PTGNode _AVPatternName_hdrCode;
PTGNode _AVPatternName_codeName;
PTGNode _AVPatternName_typedParams;
int _AVArguments__const2;
int _AVArguments__const3;
int _AVArguments__const4;
int _AVArguments__const5;
int _AVArguments__const6;
PTGNode _AVArguments__const7;
DefTableKeyList _AVArguments__DefTableKeyauxList;
DefTableKeyList _AVArguments_DefTableKeyList;
int _AVFunctionName_PatElemTakeIt;
Binding _AVFunctionName_Bind;
int _AVFunctionName_DoIt;
PTGNode _AVFunctionName_hdrCode;
PatElem _AVFunctionName_PatElemElem;
int _AVFunctionCall__const2;
int _AVFunctionCall__const3;
int _AVFunctionCall__const4;
int _AVFunctionCall__const5;
int _AVFunctionCall__const6;
PTGNode _AVFunctionCall__const14;
PTGNode _AVFunctionCall_code;
int _AVFunctionCall_hasValueType;
PTGNode _AVPatternBody__const0;
int _AVPatternBody__const2;
int _AVPatternBody__const3;
int _AVPatternBody__const4;
int _AVPatternBody__const5;
int _AVPatternBody__const6;
PTGNode _AVPatternBody__const14;
PatElemList _AVPatternBody__PatElemauxList;
PatElemList _AVPatternBody_PatElemList;
PTGNode _AVPatternSpec__const12;
PTGNode _AVPatternSpec__const13;
PTGNode _AVPatternSpec__const14;
int _AVIndexinsertionCount_pre;
int _AVIndex_index;
int _AVInsertion__const6;
DefTableKey _AVInsertion__const23;
int _AVInsertion_PatElemTakeIt;
Binding _AVInsertion_Bind;
PTGNode _AVInsertion_code;
int _AVInsertion_hasNodeType;
int _AVInsertion_hasValueType;
PatElem _AVInsertion_PatElemElem;
int _AVInsertion_Sym;

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
_currn->_ATtype=doubleType;
/*SPC(162)*/

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
_currn->_ATtype=floatType;
/*SPC(160)*/

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
_currn->_ATtype=charType;
/*SPC(158)*/

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
_currn->_ATtype=shortType;
/*SPC(156)*/

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
_currn->_ATtype=longType;
/*SPC(154)*/

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
_currn->_ATtype=stringType;
/*SPC(150)*/

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
_currn->_ATtype=intType;
/*SPC(148)*/

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
_AVCStringNode_PatElemTakeIt=1;
/*SPC(793)*/
_AVCStringNode_code=PTGOutputCall("STRING", PTGId(_currn->_ATTERM_1));
/*SPC(408)*/
_AVCStringNode_hasValueType=1;
/*SPC(298)*/
_AVCStringNode_PatElemElem=newPatElem(CSTRING, NoKey, _currn->_ATTERM_1);
/*SPC(127)*/
_AVCStringNode_cPatElemListPtr_post=
((_AVCStringNode_PatElemTakeIt
) ? (RefEndConsPatElemList(_AVCStringNode_cPatElemListPtr_post, _AVCStringNode_PatElemElem)
) : (_AVCStringNode_cPatElemListPtr_post))
;
/*SPC(794)*/

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
_AVItem_one=1;
/*SPC(143)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_9(_TPPrule_9 _currn)
#else
void _VS3rule_9(_currn )
_TPPrule_9 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_AT_const0=IDENTICAL(_AVCStringNode_code);
/*SPC(125)*/
_AVItem__const2=ZERO();
/*SPC(125)*/
_currn->_AT_const3=IDENTICAL(_AVCStringNode_hasValueType);
/*SPC(125)*/
_currn->_AT_const4=ZERO();
/*SPC(125)*/
_currn->_AT_const5=ARGTOONE(_AVCStringNode_hasValueType);
/*SPC(125)*/
_currn->_AT_const6=ZERO();
/*SPC(125)*/
_currn->_AT_const14=PTGNull();
/*SPC(125)*/
_AVItem__const21=IDENTICAL(_AVCStringNode_code);
/*SPC(125)*/

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
_AVFunctionCallinsertPointChain_post=NULLDefTableKeyList;
/*SPC(242)*/
_AVFunctionCallinsertionCount_post=1;
/*SPC(22)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
_AVFunctionCallinsertionCount_post=_currn->_desc1->_ATinsertionCount_post;
/*SPC(0)*/
_currn->_desc2->_ATEnv=NewScope((* _IG_incl1));
/*SPC(508)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_10(_TPPrule_10 _currn)
#else
void _VS3rule_10(_currn )
_TPPrule_10 _currn;

#endif
{
int* _IL_incl6;
DefTableKeyList* _IL_incl8;
int* _IL_incl4;
int* _IL_incl3;

_VisitVarDecl()
_VisitEntry();
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_AThasFreeSubtrees);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATinsertKeyList);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATisInOption);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATinFunctionCall);
_currn->_ATisInOption=0;
/*SPC(469)*/
_currn->_ATinFunctionCall=0;
/*SPC(57)*/
_AVFunctionCallinsertPointChain_post=_currn->_desc1->_ATinsertPointChain_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_AThasFreeSubtrees=_AVPatternBody__const2;
/*SPC(290)*/
_currn->_ATinsertKeyList=FillInsertKeyList(_AVFunctionCallinsertPointChain_post);
/*SPC(243)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_desc1->_ATpattern=_AVPatternBody_PatElemList;
/*SPC(90)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl6=_IL_incl6;
_IG_incl8=_IL_incl8;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_10(_TPPrule_10 _currn)
#else
void _VS4rule_10(_currn )
_TPPrule_10 _currn;

#endif
{
int* _IL_incl6;
DefTableKeyList* _IL_incl8;
int* _IL_incl4;
int* _IL_incl3;

_VisitVarDecl()
_VisitEntry();
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_AThasFreeSubtrees);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATinsertKeyList);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATisInOption);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATinFunctionCall);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl6=_IL_incl6;
_IG_incl8=_IL_incl8;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_10(_TPPrule_10 _currn)
#else
void _VS5rule_10(_currn )
_TPPrule_10 _currn;

#endif
{
int* _IL_incl10;
int* _IL_incl9;
int* _IL_incl7;
int* _IL_incl6;
DefTableKeyList* _IL_incl8;
int* _IL_incl4;
int* _IL_incl3;

_VisitVarDecl()
_VisitEntry();
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_AThasInsertions);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATisEmptyPattern);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_AThasFreeLeafs);
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_AThasFreeSubtrees);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATinsertKeyList);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATisInOption);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATinFunctionCall);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

if (AND(GT(_AVFunctionCallinsertionCount_post, 1), _AVPatternBody__const6)) {
message(WARNING, "do not mix indexed and non-indexed insertions", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(41)*/
_currn->_AThasFreeLeafs=_AVPatternBody__const3;
/*SPC(284)*/
_currn->_AThasInsertions=_AVPatternBody__const4;
/*SPC(280)*/
_currn->_ATisEmptyPattern=NOT(_AVPatternBody__const5);
/*SPC(257)*/
_AVPatternName_bodyCode=_AVPatternBody__const0;
/*SPC(392)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPatternSpec__const12=IDENTICAL(_AVPatternName_implCode);
/*SPC(89)*/
_AVPatternSpec__const13=IDENTICAL(_AVPatternName_hdrCode);
/*SPC(89)*/
_AVPatternSpec__const14=_AVPatternBody__const14;
/*SPC(89)*/
_IG_incl10=_IL_incl10;
_IG_incl9=_IL_incl9;
_IG_incl7=_IL_incl7;
_IG_incl6=_IL_incl6;
_IG_incl8=_IL_incl8;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;

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
_currn->_ATtype=pointerType;
/*SPC(152)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_11(_TPPrule_11 _currn)
#else
void _VS2rule_11(_currn )
_TPPrule_11 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (NOT((* _IG_incl3))) {
message(ERROR, "pointer type is not allowed here", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(65)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_12(_TPPrule_12 _currn)
#else
void _VS1rule_12(_currn )
_TPPrule_12 _currn;

#endif
{
DefTableKeyList* _IL_incl15;

_VisitVarDecl()
_VisitEntry();
_IL_incl15=_IG_incl15;_IG_incl15= &(_currn->_ATtypes);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATtypes=_AVArguments_DefTableKeyList;
/*SPC(199)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl15=_IL_incl15;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_12(_TPPrule_12 _currn)
#else
void _VS2rule_12(_currn )
_TPPrule_12 _currn;

#endif
{
DefTableKeyList* _IL_incl15;

_VisitVarDecl()
_VisitEntry();
_IL_incl15=_IG_incl15;_IG_incl15= &(_currn->_ATtypes);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl15=_IL_incl15;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_12(_TPPrule_12 _currn)
#else
void _VS3rule_12(_currn )
_TPPrule_12 _currn;

#endif
{
DefTableKeyList* _IL_incl15;
int* _IL_incl3;

_VisitVarDecl()
_VisitEntry();
_IL_incl15=_IG_incl15;_IG_incl15= &(_currn->_ATtypes);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATinFunctionCall);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATinFunctionCall=1;
/*SPC(56)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVFunctionCall__const2=_AVArguments__const2;
/*SPC(50)*/
_AVFunctionCall__const3=_AVArguments__const3;
/*SPC(50)*/
_AVFunctionCall__const4=_AVArguments__const4;
/*SPC(50)*/
_AVFunctionCall__const5=_AVArguments__const5;
/*SPC(50)*/
_AVFunctionCall__const6=_AVArguments__const6;
/*SPC(50)*/
_AVFunctionCall__const14=IDENTICAL(_AVFunctionName_hdrCode);
/*SPC(50)*/
_AVFunctionCall_code=PTGFunctionCall(PTGId(_currn->_desc1->_ATSym), PTGCommaOpt(_AVArguments__const7));
/*SPC(422)*/
_AVFunctionCall_hasValueType=1;
/*SPC(299)*/
_IG_incl15=_IL_incl15;
_IG_incl3=_IL_incl3;

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
_AVFunctionCallinsertionCount_post=ADD(_AVIndexinsertionCount_pre, 1);
/*SPC(27)*/
_currn->_ATisIndexed=0;
/*SPC(32)*/
_AVIndex_index=_AVIndexinsertionCount_pre;
/*SPC(26)*/

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
_AVFunctionCallinsertionCount_post=_AVIndexinsertionCount_pre;
/*SPC(0)*/
_currn->_ATisIndexed=1;
/*SPC(31)*/
_AVIndex_index=_currn->_ATTERM_1;
/*SPC(9)*/

if (EQ(_currn->_ATTERM_1, 0)) {
message(ERROR, "index 0 is not allowed", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(16)*/

if (GT(_currn->_ATTERM_1, 20)) {
message(WARNING, "use indices not greater than 20", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(13)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVInsertion__const23=_currn->_desc2->_ATtype;
/*SPC(4)*/

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
_AVIndexinsertionCount_pre=_AVFunctionCallinsertionCount_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATindex=_AVIndex_index;
/*SPC(5)*/
_AVInsertion_Sym=_currn->_ATindex;
/*SPC(47)*/
_AVInsertion_Bind=BindIdn((* _IG_incl1), _AVInsertion_Sym);
/*SPC(529)*/
_currn->_ATKey=KeyOf(_AVInsertion_Bind);
/*SPC(531)*/
SetDiffType(_currn->_ATKey, _currn->_desc2->_ATtype, multipleType);
/*SPC(168)*/
ResetIndex(_currn->_ATKey, _currn->_ATindex);
/*SPC(166)*/

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

if (EQ(GetType(_currn->_ATKey, nodeType), multipleType)) {
message(ERROR, "inconsistent type of insertion point", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(177)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVInsertion__const6=IDENTICAL(_currn->_desc1->_ATisIndexed);
/*SPC(4)*/
_AVFunctionCallinsertPointChain_post=AddToOrderedSetDefTableKeyList(_currn->_ATKey, _AVFunctionCallinsertPointChain_post, cmpPatIndex);
/*SPC(249)*/
_AVInsertion_PatElemTakeIt=1;
/*SPC(793)*/

if (NOT((* _IG_incl4))) {
ResethasFreeOccurrence(_currn->_ATKey, 1);

} else {
}
;
/*SPC(477)*/
_AVInsertion_code=
((EQ(_currn->_desc2->_ATtype, nodeType)
) ? (PTGPrintFctCall(_currn->_ATindex)
) : (PTGOutputCall(GetOutputName(_currn->_desc2->_ATtype, "ERR"), PTGField(_currn->_ATindex))))
;
/*SPC(412)*/
_AVInsertion_hasNodeType=EQ(nodeType, _currn->_desc2->_ATtype);
/*SPC(301)*/
_AVInsertion_hasValueType=NOT(_AVInsertion_hasNodeType);
/*SPC(302)*/
_AVInsertion_PatElemElem=newPatElem(INSERT, _currn->_ATKey, 0);
/*SPC(121)*/
_AVCStringNode_cPatElemListPtr_post=
((_AVInsertion_PatElemTakeIt
) ? (RefEndConsPatElemList(_AVCStringNode_cPatElemListPtr_post, _AVInsertion_PatElemElem)
) : (_AVCStringNode_cPatElemListPtr_post))
;
/*SPC(794)*/

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
_currn->_ATtype=nodeType;
/*SPC(146)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_33(_TPPrule_33 _currn)
#else
void _VS1rule_33(_currn )
_TPPrule_33 _currn;

#endif
{
Environment* _IL_incl14;
Environment* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl14=_IG_incl14;_IG_incl14= &(_currn->_ATFctEnv);
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATEnv);
_currn->_ATFctEnv=FctRootEnv;
/*SPC(590)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATEnv=RootEnv;
/*SPC(494)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
PP_OutFile("ptg_gen.c", PTGPatternFile(_AVG1__const12));
/*SPC(319)*/
PP_OutFile("ptg_gen.h", PTGHeaderFile(_AVG1__const13, _AVG1__const14));
/*SPC(313)*/
_IG_incl14=_IL_incl14;
_IG_incl1=_IL_incl1;

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
_currn->_ATinsertPointChain_post=_AVFunctionCallinsertPointChain_post;
/*SPC(0)*/
_currn->_ATinsertionCount_post=_AVFunctionCallinsertionCount_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_32(_TPPrule_32 _currn)
#else
void _VS2rule_32(_currn )
_TPPrule_32 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPatternName_Bind=BindIdn((* _IG_incl1), _currn->_ATSym);
/*SPC(529)*/
_currn->_ATKey=KeyOf(_AVPatternName_Bind);
/*SPC(531)*/
ResetPattern(_currn->_ATKey, _currn->_ATpattern);
/*SPC(94)*/

if (GetisPredefined(_currn->_ATKey, 0)) {
message(ERROR, CatStrInd("predefined identifier is redefined: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(77)*/

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

if (NOT(GetisPredefined(_currn->_ATKey, 0))) {

if (NE(_currn->_ATpattern, GetPattern(_currn->_ATKey, NULLPatElemList))) {

if (NE(0, CompPatElemList(_currn->_ATpattern, GetPattern(_currn->_ATKey, NULLPatElemList), cmpPatElem))) {
ResetIsMultDef(_currn->_ATKey, 1);

} else {
}
;

} else {
}
;

} else {
}
;
/*SPC(96)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_32(_TPPrule_32 _currn)
#else
void _VS4rule_32(_currn )
_TPPrule_32 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (GetIsMultDef(_currn->_ATKey, 0)) {
message(ERROR, CatStrInd("identifier is multiply defined: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(115)*/
_AVPatternName_DoIt=
((GetDoIt(_currn->_ATKey, 0)
) ? (0
) : (
(ResetDoIt(_currn->_ATKey, 1), 1)
))
;
/*SPC(230)*/
_AVPatternName_codeName=PTGId(_currn->_ATSym);
/*SPC(266)*/
_AVPatternName_typedParams=
((EQ((* _IG_incl8), NULLDefTableKeyList)
) ? (PTGNoTypedParams()
) : (MkTypedParams((* _IG_incl8))))
;
/*SPC(268)*/
_AVPatternName_emptyResultCode=
((_AVPatternName_DoIt
) ? (
((AND((* _IG_incl6), NOT((* _IG_incl7)))
) ? (PTGConditionalReturn(MkEmptyResultCode((* _IG_incl8)))
) : (PTGNULL))

) : (PTGNULL))
;
/*SPC(454)*/
_AVPatternName_constructorCode=
((AND(_AVPatternName_DoIt, NOT((* _IG_incl9)))
) ? (
(((* _IG_incl10)
) ? (PTGConstructorFunction(_AVPatternName_codeName, _AVPatternName_typedParams, MkParamNames((* _IG_incl8)), MkParamSpecs((* _IG_incl8)), _AVPatternName_emptyResultCode, MkParamAssigns((* _IG_incl8)))
) : (PTGConstantConstructor(_AVPatternName_codeName)))

) : (PTGNULL))
;
/*SPC(371)*/
_AVPatternName_printCode=
((_AVPatternName_DoIt
) ? (PTGPrintFunction(_AVPatternName_codeName, _AVPatternName_bodyCode)
) : (PTGNULL))
;
/*SPC(401)*/
_AVPatternName_structCode=
((AND(_AVPatternName_DoIt, NOT((* _IG_incl9)))
) ? (PTGStructure(_AVPatternName_codeName, MkStructFields((* _IG_incl8)))
) : (PTGNULL))
;
/*SPC(357)*/
_AVPatternName_implCode=
((AND(_AVPatternName_DoIt, NE(_currn->_ATpattern, NULLPatElemList))
) ? (PTGPatternImpl(_AVPatternName_codeName, _AVPatternName_structCode, _AVPatternName_printCode, _AVPatternName_constructorCode)
) : (PTGNULL))
;
/*SPC(325)*/
_AVPatternName_hdrCode=
((_AVPatternName_DoIt
) ? (
(((* _IG_incl9)
) ? (PTGEmptyPattern(_AVPatternName_codeName)
) : (PTGFunctHdr(_AVPatternName_codeName, _AVPatternName_typedParams)))

) : (PTGNULL))
;
/*SPC(336)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_31(_TPPrule_31 _currn)
#else
void _VS1rule_31(_currn )
_TPPrule_31 _currn;

#endif
{

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
Environment* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATEnv);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_31(_TPPrule_31 _currn)
#else
void _VS3rule_31(_currn )
_TPPrule_31 _currn;

#endif
{
Environment* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATEnv);
_AVPatternBody__PatElemauxList=NULLPatElemList;
/*SPC(787)*/
_AVCStringNode_cPatElemListPtr_post=_PatElemListADDROF(_AVPatternBody__PatElemauxList);
/*SPC(788)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPatternBody__const2=_AVG2__const2;
/*SPC(938)*/
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_31(_TPPrule_31 _currn)
#else
void _VS4rule_31(_currn )
_TPPrule_31 _currn;

#endif
{
Environment* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATEnv);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPatternBody_PatElemList=_AVPatternBody__PatElemauxList;
/*SPC(789)*/
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_31(_TPPrule_31 _currn)
#else
void _VS5rule_31(_currn )
_TPPrule_31 _currn;

#endif
{
Environment* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATEnv);
_AVPatternBody__const0=_currn->_desc1->_AT_const0;
/*SPC(938)*/
_AVPatternBody__const3=_currn->_desc1->_AT_const3;
/*SPC(938)*/
_AVPatternBody__const4=_currn->_desc1->_AT_const4;
/*SPC(938)*/
_AVPatternBody__const5=_currn->_desc1->_AT_const5;
/*SPC(938)*/
_AVPatternBody__const6=_currn->_desc1->_AT_const6;
/*SPC(938)*/
_AVPatternBody__const14=_currn->_desc1->_AT_const14;
/*SPC(938)*/
_AVFunctionCallinsertionCount_post=_currn->_desc1->_ATinsertionCount_post;
/*SPC(0)*/
_IG_incl1=_IL_incl1;

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_30(_TPPrule_30 _currn)
#else
void _VS2rule_30(_currn )
_TPPrule_30 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_30(_TPPrule_30 _currn)
#else
void _VS3rule_30(_currn )
_TPPrule_30 _currn;

#endif
{
int* _IL_incl4;

_VisitVarDecl()
_VisitEntry();
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATisInOption);
_AVOptional_PatElemTakeIt=1;
/*SPC(801)*/
_currn->_ATisInOption=1;
/*SPC(474)*/
_AVOptional_PatElemElem=newPatElem(OPTION, NoKey, _currn->_desc1->_AT_const22);
/*SPC(136)*/
_AVCStringNode_cPatElemListPtr_post=
((_AVOptional_PatElemTakeIt
) ? (RefEndConsPatElemList(_AVCStringNode_cPatElemListPtr_post, _AVOptional_PatElemElem)
) : (_AVCStringNode_cPatElemListPtr_post))
;
/*SPC(802)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl4=_IL_incl4;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_30(_TPPrule_30 _currn)
#else
void _VS4rule_30(_currn )
_TPPrule_30 _currn;

#endif
{
int* _IL_incl4;

_VisitVarDecl()
_VisitEntry();
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATisInOption);

if (NOT((* _IG_incl6))) {
message(ERROR, "optional clause without choice", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(437)*/
_AVOptional__const4=_currn->_desc1->_AT_const4;
/*SPC(934)*/
_AVOptional__const5=_currn->_desc1->_AT_const5;
/*SPC(934)*/
_AVOptional__const6=_currn->_desc1->_AT_const6;
/*SPC(934)*/
_AVOptional__const14=_currn->_desc1->_AT_const14;
/*SPC(934)*/
_AVOptional_code=PTGIfStatement(MkOptionCondition((* _IG_incl8)), _currn->_desc1->_AT_const21);
/*SPC(439)*/
_IG_incl4=_IL_incl4;

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_29(_TPPrule_29 _currn)
#else
void _VS2rule_29(_currn )
_TPPrule_29 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVItem_one=1;
/*SPC(143)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_29(_TPPrule_29 _currn)
#else
void _VS3rule_29(_currn )
_TPPrule_29 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_AT_const0=IDENTICAL(_AVInsertion_code);
/*SPC(930)*/
_AVItem__const2=IDENTICAL(_AVInsertion_hasNodeType);
/*SPC(930)*/
_currn->_AT_const3=IDENTICAL(_AVInsertion_hasValueType);
/*SPC(930)*/
_currn->_AT_const4=ARGTOONE(_currn->_desc1->_ATKey);
/*SPC(930)*/
_currn->_AT_const5=ARGTOONE(_AVInsertion_hasValueType);
/*SPC(930)*/
_currn->_AT_const6=_AVInsertion__const6;
/*SPC(930)*/
_currn->_AT_const14=PTGNull();
/*SPC(930)*/
_AVItem__const21=IDENTICAL(_AVInsertion_code);
/*SPC(930)*/

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
_AVItem_one=1;
/*SPC(143)*/

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
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_AT_const0=IDENTICAL(_AVFunctionCall_code);
/*SPC(926)*/
_AVItem__const2=_AVFunctionCall__const2;
/*SPC(926)*/
_currn->_AT_const3=OR(_AVFunctionCall__const3, IDENTICAL(_AVFunctionCall_hasValueType));
/*SPC(926)*/
_currn->_AT_const4=_AVFunctionCall__const4;
/*SPC(926)*/
_currn->_AT_const5=OR(_AVFunctionCall__const5, ARGTOONE(_AVFunctionCall_hasValueType));
/*SPC(926)*/
_currn->_AT_const6=_AVFunctionCall__const6;
/*SPC(926)*/
_currn->_AT_const14=_AVFunctionCall__const14;
/*SPC(926)*/
_AVItem__const21=IDENTICAL(_AVFunctionCall_code);
/*SPC(926)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_27(_TPPrule_27 _currn)
#else
void _VS3rule_27(_currn )
_TPPrule_27 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG4__const2=OR(_AVG4__const2, _AVArgument__const2);
/*SPC(922)*/
_AVG4__const3=OR(_AVG4__const3, _AVArgument__const3);
/*SPC(922)*/
_AVG4__const4=OR(_AVG4__const4, _AVArgument__const4);
/*SPC(922)*/
_AVG4__const5=OR(_AVG4__const5, _AVArgument__const5);
/*SPC(922)*/
_AVG4__const6=OR(_AVG4__const6, _AVArgument__const6);
/*SPC(922)*/
_AVG4__const7=PTGCommaSeq(_AVG4__const7, _AVArgument__const7);
/*SPC(922)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_26(_TPPrule_26 _currn)
#else
void _VS3rule_26(_currn )
_TPPrule_26 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVG4__const2=ZERO();
/*SPC(918)*/
_AVG4__const3=ZERO();
/*SPC(918)*/
_AVG4__const4=ZERO();
/*SPC(918)*/
_AVG4__const5=ZERO();
/*SPC(918)*/
_AVG4__const6=ZERO();
/*SPC(918)*/
_AVG4__const7=PTGNull();
/*SPC(918)*/

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
_currn->_AT_const22=IDENTICAL(_AVItem_one);
/*SPC(914)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_25(_TPPrule_25 _currn)
#else
void _VS3rule_25(_currn )
_TPPrule_25 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_AT_const4=_currn->_desc1->_AT_const4;
/*SPC(914)*/
_currn->_AT_const5=_currn->_desc1->_AT_const5;
/*SPC(914)*/
_currn->_AT_const6=_currn->_desc1->_AT_const6;
/*SPC(914)*/
_currn->_AT_const14=_currn->_desc1->_AT_const14;
/*SPC(914)*/
_currn->_AT_const21=_AVItem__const21;
/*SPC(914)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_24(_TPPrule_24 _currn)
#else
void _VS1rule_24(_currn )
_TPPrule_24 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_24(_TPPrule_24 _currn)
#else
void _VS2rule_24(_currn )
_TPPrule_24 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_AT_const22=ADD(_currn->_desc1->_AT_const22, IDENTICAL(_AVItem_one));
/*SPC(910)*/

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
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_AT_const4=OR(_currn->_desc1->_AT_const4, _currn->_desc2->_AT_const4);
/*SPC(910)*/
_currn->_AT_const5=OR(_currn->_desc1->_AT_const5, _currn->_desc2->_AT_const5);
/*SPC(910)*/
_currn->_AT_const6=OR(_currn->_desc1->_AT_const6, _currn->_desc2->_AT_const6);
/*SPC(910)*/
_currn->_AT_const14=PTGSeq(_currn->_desc1->_AT_const14, _currn->_desc2->_AT_const14);
/*SPC(910)*/
_currn->_AT_const21=PTGSeq(_currn->_desc1->_AT_const21, _AVItem__const21);
/*SPC(910)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_23(_TPPrule_23 _currn)
#else
void _VS1rule_23(_currn )
_TPPrule_23 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
_AVFunctionCallinsertionCount_post=_currn->_desc1->_ATinsertionCount_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATinsertionCount_post=_AVFunctionCallinsertionCount_post;
/*SPC(0)*/

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
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG2__const2=_AVG2__const2;
/*SPC(906)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_23(_TPPrule_23 _currn)
#else
void _VS4rule_23(_currn )
_TPPrule_23 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_AT_const0=PTGSeq(_currn->_desc1->_AT_const0, IDENTICAL(_AVOptional_code));
/*SPC(906)*/
_currn->_AT_const3=_currn->_desc1->_AT_const3;
/*SPC(906)*/
_currn->_AT_const4=OR(_currn->_desc1->_AT_const4, _AVOptional__const4);
/*SPC(906)*/
_currn->_AT_const5=OR(_currn->_desc1->_AT_const5, _AVOptional__const5);
/*SPC(906)*/
_currn->_AT_const6=OR(_currn->_desc1->_AT_const6, _AVOptional__const6);
/*SPC(906)*/
_currn->_AT_const14=PTGSeq(_currn->_desc1->_AT_const14, _AVOptional__const14);
/*SPC(906)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_22(_TPPrule_22 _currn)
#else
void _VS1rule_22(_currn )
_TPPrule_22 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_22(_TPPrule_22 _currn)
#else
void _VS2rule_22(_currn )
_TPPrule_22 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVFunctionCallinsertionCount_post=_currn->_desc1->_ATinsertionCount_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATinsertionCount_post=_AVFunctionCallinsertionCount_post;
/*SPC(0)*/

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
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG2__const2=OR(_AVG2__const2, _AVItem__const2);
/*SPC(902)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_22(_TPPrule_22 _currn)
#else
void _VS4rule_22(_currn )
_TPPrule_22 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_AT_const0=PTGSeq(_currn->_desc1->_AT_const0, _currn->_desc2->_AT_const0);
/*SPC(902)*/
_currn->_AT_const3=OR(_currn->_desc1->_AT_const3, _currn->_desc2->_AT_const3);
/*SPC(902)*/
_currn->_AT_const4=OR(_currn->_desc1->_AT_const4, _currn->_desc2->_AT_const4);
/*SPC(902)*/
_currn->_AT_const5=OR(_currn->_desc1->_AT_const5, _currn->_desc2->_AT_const5);
/*SPC(902)*/
_currn->_AT_const6=OR(_currn->_desc1->_AT_const6, _currn->_desc2->_AT_const6);
/*SPC(902)*/
_currn->_AT_const14=PTGSeq(_currn->_desc1->_AT_const14, _currn->_desc2->_AT_const14);
/*SPC(902)*/

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
_currn->_ATinsertionCount_post=_AVFunctionCallinsertionCount_post;
/*SPC(0)*/

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
_AVG2__const2=ZERO();
/*SPC(898)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_21(_TPPrule_21 _currn)
#else
void _VS4rule_21(_currn )
_TPPrule_21 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_AT_const0=PTGNull();
/*SPC(898)*/
_currn->_AT_const3=ZERO();
/*SPC(898)*/
_currn->_AT_const4=ZERO();
/*SPC(898)*/
_currn->_AT_const5=ZERO();
/*SPC(898)*/
_currn->_AT_const6=ZERO();
/*SPC(898)*/
_currn->_AT_const14=PTGNull();
/*SPC(898)*/

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
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
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

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_20(_TPPrule_20 _currn)
#else
void _VS5rule_20(_currn )
_TPPrule_20 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG1__const12=PTGSeq(_AVG1__const12, _AVPatternSpec__const12);
/*SPC(894)*/
_AVG1__const13=PTGSeq(_AVG1__const13, _AVPatternSpec__const13);
/*SPC(894)*/
_AVG1__const14=PTGSeq(_AVG1__const14, _AVPatternSpec__const14);
/*SPC(894)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_19(_TPPrule_19 _currn)
#else
void _VS5rule_19(_currn )
_TPPrule_19 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVG1__const12=PTGNull();
/*SPC(890)*/
_AVG1__const13=PTGNull();
/*SPC(890)*/
_AVG1__const14=PTGNull();
/*SPC(890)*/

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
_AVFunctionName_Bind=BindIdn((* _IG_incl14), _currn->_ATSym);
/*SPC(625)*/
_currn->_ATKey=KeyOf(_AVFunctionName_Bind);
/*SPC(627)*/
ResetArgumentTypes(_currn->_ATKey, (* _IG_incl15));
/*SPC(203)*/

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

if (NE(0, CompDefTableKeyList((* _IG_incl15), GetArgumentTypes(_currn->_ATKey, NULLDefTableKeyList), cmpDefTableKey))) {
ResetIsInconsistent(_currn->_ATKey, 1);

} else {
}
;
/*SPC(207)*/

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

if (GetIsInconsistent(_currn->_ATKey, 0)) {
message(ERROR, CatStrInd("function called inconsistently: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(223)*/
_AVFunctionName_PatElemTakeIt=1;
/*SPC(793)*/
_AVFunctionName_DoIt=
((GetDoIt(_currn->_ATKey, 0)
) ? (0
) : (
(ResetDoIt(_currn->_ATKey, 1), 1)
))
;
/*SPC(230)*/
_AVFunctionName_hdrCode=
((_AVFunctionName_DoIt
) ? (PTGCalledFunction(PTGId(_currn->_ATSym), PTGCommaOpt(MkTypeList((* _IG_incl15))))
) : (PTGNULL))
;
/*SPC(346)*/
_AVFunctionName_PatElemElem=newPatElem(CALL, _currn->_ATKey, 0);
/*SPC(132)*/
_AVCStringNode_cPatElemListPtr_post=
((_AVFunctionName_PatElemTakeIt
) ? (RefEndConsPatElemList(_AVCStringNode_cPatElemListPtr_post, _AVFunctionName_PatElemElem)
) : (_AVCStringNode_cPatElemListPtr_post))
;
/*SPC(794)*/

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
_AVArguments__DefTableKeyauxList=NULLDefTableKeyList;
/*SPC(686)*/
_AVArgument_cDefTableKeyListPtr_post=_DefTableKeyListADDROF(_AVArguments__DefTableKeyauxList);
/*SPC(687)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVArguments_DefTableKeyList=_AVArguments__DefTableKeyauxList;
/*SPC(688)*/

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_17(_TPPrule_17 _currn)
#else
void _VS3rule_17(_currn )
_TPPrule_17 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVArguments__const2=_AVG4__const2;
/*SPC(882)*/
_AVArguments__const3=_AVG4__const3;
/*SPC(882)*/
_AVArguments__const4=_AVG4__const4;
/*SPC(882)*/
_AVArguments__const5=_AVG4__const5;
/*SPC(882)*/
_AVArguments__const6=_AVG4__const6;
/*SPC(882)*/
_AVArguments__const7=_AVG4__const7;
/*SPC(882)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_16(_TPPrule_16 _currn)
#else
void _VS1rule_16(_currn )
_TPPrule_16 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVArgument_DefTableKeyTakeIt=1;
/*SPC(692)*/
_AVArgument_DefTableKeyElem=_AVInsertion__const23;
/*SPC(187)*/
_AVArgument_cDefTableKeyListPtr_post=
((_AVArgument_DefTableKeyTakeIt
) ? (RefEndConsDefTableKeyList(_AVArgument_cDefTableKeyListPtr_post, _AVArgument_DefTableKeyElem)
) : (_AVArgument_cDefTableKeyListPtr_post))
;
/*SPC(693)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_16(_TPPrule_16 _currn)
#else
void _VS3rule_16(_currn )
_TPPrule_16 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVArgument__const2=IDENTICAL(_AVInsertion_hasNodeType);
/*SPC(878)*/
_AVArgument__const3=IDENTICAL(_AVInsertion_hasValueType);
/*SPC(878)*/
_AVArgument__const4=ARGTOONE(_currn->_desc1->_ATKey);
/*SPC(878)*/
_AVArgument__const5=ARGTOONE(_AVInsertion_hasValueType);
/*SPC(878)*/
_AVArgument__const6=_AVInsertion__const6;
/*SPC(878)*/
_AVArgument__const7=PTGField(_currn->_desc1->_ATindex);
/*SPC(878)*/

_VisitExit();
}

