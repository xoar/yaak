
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
PTGNode _AVRuleBnf_post;
PTGNode _AVAtomic_Ptg;
PTGNode _AVSymbol_Ptg;
int _AVSymbol_Sym;
PTGNode _AVExpression_Ptg_RuleAttr_34;
PTGNode _AVExpression_Ptg_RuleAttr_33;
PTGNode _AVExpression_Ptg_RuleAttr_32;
PTGNode _AVRule_Ptg;
int _AVRule_Sym;

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
void _VS1LST_Rulerule_16(_TPPLST_Rulerule_16 _currn)
#else
void _VS1LST_Rulerule_16(_currn )
_TPPLST_Rulerule_16 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
_AVSymbol_Sym=_currn->_ATTERM_1;
/*SPC(30)*/
_AVSymbol_Ptg=PTGId(_AVSymbol_Sym);
/*SPC(28)*/

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
_AVSymbol_Sym=_currn->_ATTERM_1;
/*SPC(30)*/
_AVSymbol_Ptg=PTGId(_AVSymbol_Sym);
/*SPC(28)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVAtomic_Ptg=PTGConn(_AVSymbol_Ptg);
/*SPC(46)*/

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
_AVAtomic_Ptg=PTGDolMod(_AVSymbol_Ptg);
/*SPC(42)*/

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
_AVAtomic_Ptg=PTGAtMod(_AVSymbol_Ptg);
/*SPC(38)*/

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
_AVAtomic_Ptg=_AVSymbol_Ptg;
/*SPC(34)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_7(_TPPrule_7 _currn,PTGNodeList* _AS0Rhs)
#else
void _VS1rule_7(_currn ,_AS0Rhs)
_TPPrule_7 _currn;
PTGNodeList* _AS0Rhs;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0Rhs)=SinglePTGNodeList(_AVAtomic_Ptg);
/*SPC(66)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_8(_TPPrule_8 _currn,PTGNodeList* _AS0Rhs)
#else
void _VS1rule_8(_currn ,_AS0Rhs)
_TPPrule_8 _currn;
PTGNodeList* _AS0Rhs;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0Rhs)=SinglePTGNodeList(PTGNULL);
/*SPC(62)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_9(_TPPrule_9 _currn,PTGNodeList* _AS0Rhs)
#else
void _VS1rule_9(_currn ,_AS0Rhs)
_TPPrule_9 _currn;
PTGNodeList* _AS0Rhs;

#endif
{
PTGNodeList _AS1Rhs;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNodeList*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Rhs)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVExpression_Ptg_RuleAttr_32=PTGId(GenerateName("G"));
/*SPC(115)*/
(* _AS0Rhs)=SinglePTGNodeList(_AVExpression_Ptg_RuleAttr_32);
/*SPC(116)*/
_AVRuleBnf_post=Combine(_AVRuleBnf_post, _AVExpression_Ptg_RuleAttr_32, AppPTGNodeList(_AS1Rhs, Concatenate(SinglePTGNodeList(PTGSpSeq(_AVExpression_Ptg_RuleAttr_32, _AVSymbol_Ptg)), _AS1Rhs)));
/*SPC(117)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_10(_TPPrule_10 _currn,PTGNodeList* _AS0Rhs)
#else
void _VS1rule_10(_currn ,_AS0Rhs)
_TPPrule_10 _currn;
PTGNodeList* _AS0Rhs;

#endif
{
PTGNodeList _AS1Rhs;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNodeList*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Rhs)));
_AVExpression_Ptg_RuleAttr_33=PTGId(GenerateName("G"));
/*SPC(102)*/
(* _AS0Rhs)=SinglePTGNodeList(_AVExpression_Ptg_RuleAttr_33);
/*SPC(103)*/
_AVRuleBnf_post=Combine(_AVRuleBnf_post, _AVExpression_Ptg_RuleAttr_33, AppPTGNodeList(_AS1Rhs, Concatenate((* _AS0Rhs), _AS1Rhs)));
/*SPC(104)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_11(_TPPrule_11 _currn,PTGNodeList* _AS0Rhs)
#else
void _VS1rule_11(_currn ,_AS0Rhs)
_TPPrule_11 _currn;
PTGNodeList* _AS0Rhs;

#endif
{
PTGNodeList _AS1Rhs;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNodeList*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Rhs)));
_AVExpression_Ptg_RuleAttr_34=PTGId(GenerateName("G"));
/*SPC(89)*/
(* _AS0Rhs)=SinglePTGNodeList(_AVExpression_Ptg_RuleAttr_34);
/*SPC(90)*/
_AVRuleBnf_post=Combine(_AVRuleBnf_post, _AVExpression_Ptg_RuleAttr_34, ConsPTGNodeList(PTGNULL, Concatenate((* _AS0Rhs), _AS1Rhs)));
/*SPC(91)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_12(_TPPrule_12 _currn,PTGNodeList* _AS0Rhs)
#else
void _VS1rule_12(_currn ,_AS0Rhs)
_TPPrule_12 _currn;
PTGNodeList* _AS0Rhs;

#endif
{
PTGNodeList _AS2Rhs;
PTGNodeList _AS1Rhs;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNodeList*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Rhs)));
(*(_CALL_VS_((NODEPTR ,PTGNodeList*)) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Rhs)));
(* _AS0Rhs)=Concatenate(_AS1Rhs, _AS2Rhs);
/*SPC(78)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_13(_TPPrule_13 _currn,PTGNodeList* _AS0Rhs)
#else
void _VS1rule_13(_currn ,_AS0Rhs)
_TPPrule_13 _currn;
PTGNodeList* _AS0Rhs;

#endif
{
PTGNodeList _AS1Rhs;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNodeList*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Rhs)));
(* _AS0Rhs)=ConsPTGNodeList(PTGNULL, _AS1Rhs);
/*SPC(70)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_14(_TPPrule_14 _currn,PTGNodeList* _AS0Rhs)
#else
void _VS1rule_14(_currn ,_AS0Rhs)
_TPPrule_14 _currn;
PTGNodeList* _AS0Rhs;

#endif
{
PTGNodeList _AS2Rhs;
PTGNodeList _AS1Rhs;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNodeList*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Rhs)));
(*(_CALL_VS_((NODEPTR ,PTGNodeList*)) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Rhs)));
(* _AS0Rhs)=AppPTGNodeList(_AS1Rhs, _AS2Rhs);
/*SPC(74)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_15(_TPPrule_15 _currn)
#else
void _VS1rule_15(_currn )
_TPPrule_15 _currn;

#endif
{
PTGNodeList _AS1Rhs;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNodeList*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Rhs)));
_AVRuleBnf_post=Combine(_AVRuleBnf_post, PTGId(_currn->_ATTERM_1), _AS1Rhs);
/*SPC(84)*/
_AVRule_Sym=_currn->_ATTERM_1;
/*SPC(31)*/
_AVRule_Ptg=PTGId(_AVRule_Sym);
/*SPC(28)*/

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
_AVRuleBnf_post=PTGNULL;
/*SPC(53)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
PTGOut(_AVRuleBnf_post);
/*SPC(54)*/

_VisitExit();
}

