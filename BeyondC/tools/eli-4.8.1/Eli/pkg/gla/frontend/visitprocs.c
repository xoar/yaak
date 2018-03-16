
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
Environment* _IG_incl6;
DefTableKey* _IG_incl0;
int _AVoptions__const4;
int _AVoption__const4;
PTGNode _AVnonLitDescs__const6;
PTGNode _AVnonLitDescs__const8;
int _AVnonLitDescNonlitCount_post;
int _AVencodingLitCount_post;
PTGNode _AVencodings__const5;
PTGNode _AVencodings__const7;
int _AVEofOption_Num;
int _AVlibrRef_Sym;
PTGNode _AVencoding__const5;
PTGNode _AVencoding__const7;
PTGNode _AVLitEncoding_BackOut;
PTGNode _AVLitEncoding_FlexOut;
int _AVLitEncoding_Counter;
int _AVvalue_Num;
Binding _AVIdUse_Bind;
int _AVIdUse_Sym;
DefTableKey _AVIdUse_Key;
DefTableKey _AVNonlitEncoding__const14;
int _AVNonlitEncoding__const15;
CannedDescrPtr _AVrest_libentry_RuleAttr_40;
Binding _AVIdDef_Bind;
int _AVIdDef_Unique;
PTGNode _AVnonLitDesc_BackOut;
PTGNode _AVnonLitDesc_FlexOut;
int _AVnonLitDesc_Counter;

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVEofOption_Num=_AVvalue_Num;
/*SPC(327)*/

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
ResetProcessor((* _IG_incl0), StringTable(_currn->_ATTERM_1));
/*SPC(272)*/

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
ResetScanner((* _IG_incl0), StringTable(_currn->_ATTERM_1));
/*SPC(261)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_AVrest_libentry_RuleAttr_40=libLookup(StringTable(_AVlibrRef_Sym));
/*SPC(245)*/
GuaranteeProcessor((* _IG_incl0), PTRSELECT(_AVrest_libentry_RuleAttr_40, Lprocessor));
/*SPC(251)*/
GuaranteeScanner((* _IG_incl0), PTRSELECT(_AVrest_libentry_RuleAttr_40, Lscanner));
/*SPC(248)*/
ResetRegex((* _IG_incl0), PTRSELECT(_AVrest_libentry_RuleAttr_40, Lpattern));
/*SPC(246)*/

if (EQ(_AVrest_libentry_RuleAttr_40, NullDescr)) {
message(FATAL, "No such canned description", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(256)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
ResetRegex((* _IG_incl0), ADD(StringTable(_currn->_ATTERM_1), 1));
/*SPC(233)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_AT_const15=_AVvalue_Num;
/*SPC(225)*/
_AVLitEncoding_Counter=ADD(_AVencodingLitCount_post, 1);
/*SPC(215)*/
_currn->_ATKey=NewKey();
/*SPC(214)*/
_AVencodingLitCount_post=_AVLitEncoding_Counter;
/*SPC(216)*/
ResetRegex(_currn->_ATKey, ADD(StringTable(_currn->_ATTERM_1), 1));
/*SPC(227)*/
ResetCounter(_currn->_ATKey, _AVLitEncoding_Counter);
/*SPC(217)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_8(_TPPrule_8 _currn)
#else
void _VS2rule_8(_currn )
_TPPrule_8 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLitEncoding_BackOut=PTGBEEntry(PTGStr(0), PTGStr(GetRegex(_currn->_ATKey, 0)), PTGStr(0), PTGStr(0), PTGNum(GetEncoding(_currn->_ATKey, NORETURN)));
/*SPC(315)*/
_AVLitEncoding_FlexOut=PTGFlexEntry(PTGQuoted(PTGStr(GetRegex(_currn->_ATKey, 0))), PTGNum(GetCounter(_currn->_ATKey, 0)), PTGNum(GetEncoding(_currn->_ATKey, NORETURN)), PTGNum(_currn->_AT_line));
/*SPC(306)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_9(_TPPrule_9 _currn)
#else
void _VS1rule_9(_currn )
_TPPrule_9 _currn;

#endif
{
DefTableKey* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATKey);
_currn->_ATKey=NewKey();
/*SPC(210)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVnonLitDesc_Counter=ADD(_AVnonLitDescNonlitCount_post, 1);
/*SPC(184)*/
_AVnonLitDescNonlitCount_post=_AVnonLitDesc_Counter;
/*SPC(185)*/
ResetCounter(_currn->_ATKey, _AVnonLitDesc_Counter);
/*SPC(186)*/
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_9(_TPPrule_9 _currn)
#else
void _VS2rule_9(_currn )
_TPPrule_9 _currn;

#endif
{
DefTableKey* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATKey);
_AVnonLitDesc_BackOut=PTGBEEntry(PTGStr(GetStr(_currn->_ATKey, 0)), PTGStr(GetRegex(_currn->_ATKey, 0)), PTGStr(GetScanner(_currn->_ATKey, 0)), PTGStr(GetProcessor(_currn->_ATKey, 0)), PTGNum(GetEncoding(_currn->_ATKey, NORETURN)));
/*SPC(293)*/
_AVnonLitDesc_FlexOut=PTGFlexEntry(PTGStr(GetRegex(_currn->_ATKey, 0)), PTGNum(GetCounter(_currn->_ATKey, 0)), PTGNum(GetEncoding(_currn->_ATKey, NORETURN)), PTGNum(_currn->_AT_line));
/*SPC(284)*/
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_10(_TPPrule_10 _currn)
#else
void _VS1rule_10(_currn )
_TPPrule_10 _currn;

#endif
{
DefTableKey* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATKey=NewKey();
/*SPC(204)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
ResetEncoding(_currn->_ATKey, _AVvalue_Num);
/*SPC(205)*/
_AVnonLitDesc_Counter=ADD(_AVnonLitDescNonlitCount_post, 1);
/*SPC(184)*/
_AVnonLitDescNonlitCount_post=_AVnonLitDesc_Counter;
/*SPC(185)*/
ResetCounter(_currn->_ATKey, _AVnonLitDesc_Counter);
/*SPC(186)*/
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_10(_TPPrule_10 _currn)
#else
void _VS2rule_10(_currn )
_TPPrule_10 _currn;

#endif
{
DefTableKey* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATKey);
_AVnonLitDesc_BackOut=PTGBEEntry(PTGStr(GetStr(_currn->_ATKey, 0)), PTGStr(GetRegex(_currn->_ATKey, 0)), PTGStr(GetScanner(_currn->_ATKey, 0)), PTGStr(GetProcessor(_currn->_ATKey, 0)), PTGNum(GetEncoding(_currn->_ATKey, NORETURN)));
/*SPC(293)*/
_AVnonLitDesc_FlexOut=PTGFlexEntry(PTGStr(GetRegex(_currn->_ATKey, 0)), PTGNum(GetCounter(_currn->_ATKey, 0)), PTGNum(GetEncoding(_currn->_ATKey, NORETURN)), PTGNum(_currn->_AT_line));
/*SPC(284)*/
_IG_incl0=_IL_incl0;

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
_AVvalue_Num=NEG(_currn->_ATTERM_1);
/*SPC(166)*/

if (EQ(_AVvalue_Num, NORETURN)) {
message(WARNING, "Encoding used internally", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(171)*/

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
_AVvalue_Num=_currn->_ATTERM_1;
/*SPC(161)*/

if (EQ(_AVvalue_Num, NORETURN)) {
message(WARNING, "Encoding used internally", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(171)*/

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
_AVvalue_Num=_currn->_ATTERM_1;
/*SPC(156)*/

if (EQ(_AVvalue_Num, NORETURN)) {
message(WARNING, "Encoding used internally", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(171)*/

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
_AVIdUse_Sym=_currn->_ATTERM_1;
/*SPC(139)*/
_AVIdUse_Bind=BindingInEnv((* _IG_incl6), _AVIdUse_Sym);
/*SPC(59)*/
_AVIdUse_Key=KeyOf(_AVIdUse_Bind);
/*SPC(63)*/

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

if (EQ(_AVIdUse_Key, NoKey)) {
message(ERROR, CatStrInd("No GLA specification for ", _AVIdUse_Sym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(133)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVNonlitEncoding__const14=_AVIdUse_Key;
/*SPC(129)*/
_AVNonlitEncoding__const15=_AVvalue_Num;
/*SPC(129)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVNonlitEncoding__const14=_AVIdUse_Key;
/*SPC(128)*/
_AVNonlitEncoding__const15=_AVvalue_Num;
/*SPC(128)*/

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
_AVIdDef_Bind=BindIdn((* _IG_incl6), _currn->_ATSym);
/*SPC(47)*/
_currn->_ATKey=KeyOf(_AVIdDef_Bind);
/*SPC(49)*/
SetUnique(_currn->_ATKey, 1, 0);
/*SPC(116)*/

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
_AVIdDef_Unique=GetUnique(_currn->_ATKey, 0);
/*SPC(119)*/

if (NOT(_AVIdDef_Unique)) {
message(ERROR, CatStrInd("Identifier is multiply defined: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(149)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_18(_TPPrule_18 _currn)
#else
void _VS1rule_18(_currn )
_TPPrule_18 _currn;

#endif
{
DefTableKey* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATKey=
(ResetStr(_currn->_desc1->_ATKey, StringTable(_currn->_desc1->_ATSym)), _currn->_desc1->_ATKey)
;
/*SPC(192)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVnonLitDesc_Counter=ADD(_AVnonLitDescNonlitCount_post, 1);
/*SPC(184)*/
_AVnonLitDescNonlitCount_post=ADD(1, _AVnonLitDescNonlitCount_post);
/*SPC(194)*/
ResetCounter(_currn->_ATKey, _AVnonLitDesc_Counter);
/*SPC(186)*/
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_18(_TPPrule_18 _currn)
#else
void _VS2rule_18(_currn )
_TPPrule_18 _currn;

#endif
{
DefTableKey* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATKey);

if (EQ(GetEncoding(_currn->_ATKey, NORETURN), NORETURN)) {
message(WARNING, CatStrInd("Symbol is not a terminal in the grammar: ", _currn->_desc1->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(199)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVnonLitDesc_BackOut=PTGBEEntry(PTGStr(GetStr(_currn->_ATKey, 0)), PTGStr(GetRegex(_currn->_ATKey, 0)), PTGStr(GetScanner(_currn->_ATKey, 0)), PTGStr(GetProcessor(_currn->_ATKey, 0)), PTGNum(GetEncoding(_currn->_ATKey, NORETURN)));
/*SPC(293)*/
_AVnonLitDesc_FlexOut=PTGFlexEntry(PTGStr(GetRegex(_currn->_ATKey, 0)), PTGNum(GetCounter(_currn->_ATKey, 0)), PTGNum(GetEncoding(_currn->_ATKey, NORETURN)), PTGNum(((_currn->_AT_pos).line)));
/*SPC(284)*/
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_32(_TPPrule_32 _currn)
#else
void _VS1rule_32(_currn )
_TPPrule_32 _currn;

#endif
{
Environment* _IL_incl6;

_VisitVarDecl()
_VisitEntry();
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATEnv);
_AVencodingLitCount_post=0;
/*SPC(179)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_currn->_ATEnv=RootEnv;
/*SPC(12)*/
_AVnonLitDescNonlitCount_post=_currn->_desc3->_ATLitCount_post;
/*SPC(180)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVnonLitDescNonlitCount_post=_currn->_desc1->_ATNonlitCount_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
PTGOutFile("backend.data", PTGBackend(PTGNum(_AVoptions__const4), PTGNum(_currn->_desc3->_ATLitCount_post), PTGNum(SUB(_AVnonLitDescNonlitCount_post, _currn->_desc3->_ATLitCount_post)), PTGSeq(_AVencodings__const5, _AVnonLitDescs__const6)));
/*SPC(357)*/
PTGOutFile("xflex.l", PTGFlex(_AVencodings__const7, _AVnonLitDescs__const8));
/*SPC(345)*/
_IG_incl6=_IL_incl6;

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVoptions__const4=NoDups(_AVoptions__const4, _AVoption__const4);
/*SPC(409)*/

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
_AVoptions__const4=_AVoption__const4;
/*SPC(405)*/

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
_AVoption__const4=BOGUS();
/*SPC(401)*/

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
_AVoption__const4=BOGUS();
/*SPC(397)*/

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
_AVoption__const4=IDENTICAL(_AVEofOption_Num);
/*SPC(393)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_26(_TPPrule_26 _currn)
#else
void _VS1rule_26(_currn )
_TPPrule_26 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVoption__const4=BOGUS();
/*SPC(389)*/

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
_AVnonLitDescNonlitCount_post=_currn->_desc1->_ATNonlitCount_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATNonlitCount_post=_AVnonLitDescNonlitCount_post;
/*SPC(0)*/

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVnonLitDescs__const6=PTGSeq(_AVnonLitDescs__const6, IDENTICAL(_AVnonLitDesc_BackOut));
/*SPC(385)*/
_AVnonLitDescs__const8=PTGSeq(_AVnonLitDescs__const8, IDENTICAL(_AVnonLitDesc_FlexOut));
/*SPC(385)*/

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
_currn->_ATNonlitCount_post=_AVnonLitDescNonlitCount_post;
/*SPC(0)*/

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
_AVnonLitDescs__const6=PTGNull();
/*SPC(381)*/
_AVnonLitDescs__const8=PTGNull();
/*SPC(381)*/

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
_AVlibrRef_Sym=_currn->_ATTERM_1;
/*SPC(139)*/

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
_AVencodingLitCount_post=_currn->_desc1->_ATLitCount_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATLitCount_post=_AVencodingLitCount_post;
/*SPC(0)*/

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
_AVencodings__const5=PTGSeq(_AVencodings__const5, _AVencoding__const5);
/*SPC(373)*/
_AVencodings__const7=PTGSeq(_AVencodings__const7, _AVencoding__const7);
/*SPC(373)*/

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
_currn->_ATLitCount_post=_AVencodingLitCount_post;
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
_AVencodings__const5=PTGNull();
/*SPC(369)*/
_AVencodings__const7=PTGNull();
/*SPC(369)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
ResetEncoding(_AVNonlitEncoding__const14, _AVNonlitEncoding__const15);
/*SPC(221)*/

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
_AVencoding__const5=PTGNull();
/*SPC(365)*/
_AVencoding__const7=PTGNull();
/*SPC(365)*/

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
ResetEncoding(_currn->_desc1->_ATKey, _currn->_desc1->_AT_const15);
/*SPC(221)*/

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVencoding__const5=IDENTICAL(_AVLitEncoding_BackOut);
/*SPC(361)*/
_AVencoding__const7=IDENTICAL(_AVLitEncoding_FlexOut);
/*SPC(361)*/

_VisitExit();
}

