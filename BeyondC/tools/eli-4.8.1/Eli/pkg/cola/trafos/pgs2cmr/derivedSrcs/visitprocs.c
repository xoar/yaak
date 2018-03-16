
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
int* _IG_incl15;
int* _IG_incl14;
Environment* _IG_incl13;
int* _IG_incl11;
Environment* _IG_incl9;
DID* _IG_incl6;
SID* _IG_incl2;
SID* _IG_incl1;
DID _AVpgs_root__const27;
SEQunit _AVliterallist_post;
int _AVG3__const16;
int _AVG3__const18;
int _AVt_or_nttntcnt_post;
DefTableKey _AVelem_list__const6;
int _AVelem_list__const7;
int _AVelem_list__const8;
DefTableKey _AVelem__const6;
int _AVelem__const7;
int _AVelem__const8;
int _AVelem_chaincnt;
DefTableKey _AVoptelem__const6;
int _AVoptelem__const7;
int _AVoptelem__const8;
int _AVoptelem_isebnf;
Binding _AVstop_part_Bind;
DefTableKey _AVstop_part_Key;
int _AVstop_part_type;
SID _AVstop_part_symbol;
int _AVstop_part_Sym;
SID _AVstop_part_psymbol;
int _AVmodification_Sym;
SID _AVmodification_symbol;
DefTableKey _AVmodification_Key;
def_entry _AVmodification_def;
Binding _AVnonliteral_Bind;
Binding _AVliteral_Bind;
Binding _AVconnection_Bind;
int _AVconnection_chaincnt;
int _AVconnection_Sym;
SEQunit _AVconnection_connect;
SID _AVconnection_symbol;
def_entry _AVconnection_def;
SID _AVconnection_psymbol;
DefTableKey _AVt_or_nt_NewKey;
SID _AVt_or_nt_symbol;
int _AVt_or_nt_Sym;
def_entry _AVt_or_nt_def;
int _AVterminal__const1;
SID _AVterminal__const2;
DefTableKey _AVterminal__const3;
int _AVterminal__const12;
DefTableKey _AVterminal__const13;
int _AVterminal_Sym;
SID _AVterminal_symbol;
int _AVterminal_type;
Binding _AVnonterminal_Bind;
DefTableKey _AVnonterminal_NewKey;
int _AVnonterminal_Sym;
def_entry _AVnonterminal_def;
DID _AVnonterminal_startdid;
int _AVnonterminal_type;
Binding _AVrulename_Bind;
int _AVrulename_Sym;
DefTableKey _AVrulename_Key;
int _AVrule__const16;
int _AVrule__const18;
DefTableKey _AVrule_replkey;
DefTableKey _AVrule_rhskey;
int _AVrule_chaincnt;
def_entry _AVrule_def;
SEQunit _AVrule_placeholder;
int _AVrule_list__const16;
int _AVstart__const16;
int _AVstart_HEAD$17_RuleAttr_83;
Binding _AVgrammarname_Bind;
SID _AVgrammarname_symbol;
int _AVgrammarname_Sym;
DefTableKey _AVgrammarname_Key;
def_entry _AVgrammarname_def;
int _AVgrammarname_type;
SID _AVgrammarname_psymbol;
def_entry _AVgrammar_part_def;
int _AVgrammar_part_lhssym;
DID _AVgrammar_part_eofdid;
DID _AVgrammar_part_startdid;
SID _AVgrammar_part_psymbol;

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
_AVt_or_nttntcnt_post=0;
/*SPC(180)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVt_or_nttntcnt_post=_currn->_desc1->_ATtntcnt_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
VOIDEN(0);
/*SPC(470)*/

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
ResetNoStart(_currn->_desc2->_ATKey, FALSE);
/*SPC(139)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_1(_TPPrule_1 _currn)
#else
void _VS3rule_1(_currn )
_TPPrule_1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_AT_const18=IDENTICAL(_currn->_desc2->_ATstartcnt);
/*SPC(468)*/
VOIDEN(0);
/*SPC(471)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_1(_TPPrule_1 _currn)
#else
void _VS4rule_1(_currn )
_TPPrule_1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVstart__const16=IDENTICAL(_AVnonterminal_startdid);
/*SPC(468)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVelem__const6=IDENTICAL(_currn->_desc1->_ATKey);
/*SPC(429)*/
_AVelem__const7=ZERO();
/*SPC(429)*/
_AVelem__const8=ZERO();
/*SPC(429)*/
_AVelem_chaincnt=
((EQ(_currn->_desc1->_ATtype, Kp_nterm)
) ? (1
) : (2))
;
/*SPC(430)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_2(_TPPrule_2 _currn)
#else
void _VS3rule_2(_currn )
_TPPrule_2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_3(_TPPrule_3 _currn)
#else
void _VS2rule_3(_currn )
_TPPrule_3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
VOIDEN(cmrlib_newprop(_currn->_desc1->_ATdef, (* _IG_incl1)));
/*SPC(415)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVmodification_Sym=_AVterminal__const1;
/*SPC(68)*/
_AVmodification_symbol=_AVterminal__const2;
/*SPC(248)*/
_AVmodification_Key=_AVterminal__const3;
/*SPC(67)*/
_AVmodification_def=ins_modification(_AVmodification_Key, _AVmodification_symbol, _currn->_desc1->_ATm_op);
/*SPC(327)*/
_AVliterallist_post=concatSEQunit(_AVliterallist_post, build_elunit(didOfdef_entry(_AVmodification_def)));
/*SPC(374)*/
VOIDEN(cmrlib_newpropval(_AVmodification_def, _currn->_desc1->_ATpsymbol, p_dvalTovalue(Mkp_dval(didOfdef_entry(_currn->_desc2->_ATdef)))));
/*SPC(411)*/

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
VOIDEN(cmrlib_newpropval(_currn->_desc1->_ATdef, (* _IG_incl2), p_nvalTovalue(Mkp_nval(_currn->_ATTERM_1))));
/*SPC(402)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_currn->_ATopr=Kp_star;
/*SPC(393)*/
_currn->_ATisebnf=1;
/*SPC(188)*/

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
_currn->_ATopr=Kp_plus;
/*SPC(389)*/
_currn->_ATisebnf=1;
/*SPC(188)*/

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVelem__const6=_AVelem__const6;
/*SPC(384)*/
_AVelem__const7=ADD(_AVelem__const7, IDENTICAL(_AVelem_chaincnt));
/*SPC(384)*/
_AVelem__const8=ADD(_AVelem__const8, IDENTICAL(_currn->_desc2->_ATisebnf));
/*SPC(384)*/
_AVelem_chaincnt=2;
/*SPC(424)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_8(_TPPrule_8 _currn)
#else
void _VS3rule_8(_currn )
_TPPrule_8 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVliterallist_post=build_rhs(_AVliterallist_post, nullSEQunit(), _currn->_desc2->_ATopr);
/*SPC(385)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_9(_TPPrule_9 _currn)
#else
void _VS1rule_9(_currn )
_TPPrule_9 _currn;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
SEQunit _AS1list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_9(_TPPrule_9 _currn,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS2rule_9(_currn ,_AS0_const7,_AS0_const6)
_TPPrule_9 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
SEQunit _AS1list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,DefTableKey*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const7)),(&( _AS1_const6)));
_AVt_or_nttntcnt_post=_currn->_desc1->_ATtntcnt_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(* _AS0_const6)=KEY(_AS1_const6, _AVelem_list__const6);
/*SPC(368)*/
(* _AS0_const7)=ADD(_AS1_const7, _AVelem_list__const7);
/*SPC(368)*/
_currn->_AT_const8=ADD(_currn->_desc1->_AT_const8, _AVelem_list__const8);
/*SPC(368)*/
_currn->_ATtntcnt_post=_AVt_or_nttntcnt_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_9(_TPPrule_9 _currn,SEQunit* _AS0list_post,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS3rule_9(_currn ,_AS0list_post,_AS0_const7,_AS0_const6)
_TPPrule_9 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;
SEQunit* _AS0list_post;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
SEQunit _AS1list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,SEQunit*,int*,DefTableKey*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1list_post)),(&( _AS1_const7)),(&( _AS1_const6)));
_AVliterallist_post=nullSEQunit();
/*SPC(370)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(* _AS0list_post)=build_rhs(_AS1list_post, _AVliterallist_post, Kp_alt);
/*SPC(369)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_10(_TPPrule_10 _currn)
#else
void _VS1rule_10(_currn )
_TPPrule_10 _currn;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
SEQunit _AS1list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_10(_TPPrule_10 _currn,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS2rule_10(_currn ,_AS0_const7,_AS0_const6)
_TPPrule_10 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
SEQunit _AS1list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,DefTableKey*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const7)),(&( _AS1_const6)));
(* _AS0_const6)=_AS1_const6;
/*SPC(362)*/
(* _AS0_const7)=_AS1_const7;
/*SPC(362)*/
_currn->_AT_const8=ADD(_currn->_desc1->_AT_const8, IDENTICAL(_currn->_desc2->_ATisebnf));
/*SPC(362)*/
_currn->_ATtntcnt_post=_currn->_desc1->_ATtntcnt_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_10(_TPPrule_10 _currn,SEQunit* _AS0list_post,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS3rule_10(_currn ,_AS0list_post,_AS0_const7,_AS0_const6)
_TPPrule_10 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;
SEQunit* _AS0list_post;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
SEQunit _AS1list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,SEQunit*,int*,DefTableKey*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1list_post)),(&( _AS1_const7)),(&( _AS1_const6)));
_AVliterallist_post=_AS1list_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(* _AS0list_post)=build_rhs(_AS1list_post, build_elunit(didOfdef_entry(_currn->_desc3->_ATdef)), Kp_delrep);
/*SPC(363)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_11(_TPPrule_11 _currn)
#else
void _VS1rule_11(_currn )
_TPPrule_11 _currn;

#endif
{
DefTableKey _AS3_const6;
int _AS3_const7;
SEQunit _AS3list_post;

_VisitVarDecl()
_VisitEntry();
_AVt_or_nttntcnt_post=0;
/*SPC(174)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
SetChain(_currn->_desc1->_ATKey, 1, 2);
/*SPC(460)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_11(_TPPrule_11 _currn)
#else
void _VS2rule_11(_currn )
_TPPrule_11 _currn;

#endif
{
DefTableKey _AS3_const6;
int _AS3_const7;
SEQunit _AS3list_post;

_VisitVarDecl()
_VisitEntry();
_AVt_or_nttntcnt_post=_currn->_desc2->_ATtntcnt_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,int*,DefTableKey*)) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3,(&( _AS3_const7)),(&( _AS3_const6)));
_AVrule_rhskey=_AS3_const6;
/*SPC(436)*/
_AVrule_chaincnt=_AS3_const7;
/*SPC(434)*/
_currn->_ATchainelim=AND(EQ(_AVrule_chaincnt, 1), EQ(GetChain(_currn->_desc1->_ATKey, 0), 1));
/*SPC(438)*/

if (_currn->_ATchainelim) {
Addchain(_currn->_desc1->_ATKey, _AVrule_rhskey);

} else {
}
;
/*SPC(441)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_11(_TPPrule_11 _currn)
#else
void _VS3rule_11(_currn )
_TPPrule_11 _currn;

#endif
{
DefTableKey _AS3_const6;
int _AS3_const7;
SEQunit _AS3list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVrule__const18=IDENTICAL(_currn->_desc1->_ATstartcnt);
/*SPC(344)*/
_AVrule_replkey=GetReplKey(_currn->_desc1->_ATKey);
/*SPC(443)*/

if (_currn->_ATchainelim) {
ResetReplace(_currn->_desc1->_ATKey, _AVrule_replkey);

} else {
}
;
/*SPC(461)*/

if (EQ(_AVrule_replkey, NoKey)) {
message(ERROR, "This rule lies on a cycle of chain productions", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(447)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_11(_TPPrule_11 _currn)
#else
void _VS4rule_11(_currn )
_TPPrule_11 _currn;

#endif
{
int* _IL_incl15;
int* _IL_incl14;
DefTableKey _AS3_const6;
int _AS3_const7;
SEQunit _AS3list_post;

_VisitVarDecl()
_VisitEntry();
_IL_incl15=_IG_incl15;_IG_incl15= &(_currn->_ATmaxcnt);
_IL_incl14=_IG_incl14;_IG_incl14= &(_currn->_ATisebnf);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATmaxcnt=_currn->_desc3->_ATtntcnt_post;
/*SPC(175)*/
_currn->_ATisebnf=_currn->_desc3->_AT_const8;
/*SPC(172)*/
_AVliterallist_post=nullSEQunit();
/*SPC(345)*/
(*(_CALL_VS_((NODEPTR ,SEQunit*,int*,DefTableKey*)) (VS3MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3,(&( _AS3list_post)),(&( _AS3_const7)),(&( _AS3_const6)));
_AVrule__const16=IDENTICAL(_AVnonterminal_startdid);
/*SPC(344)*/
_AVliterallist_post=_AS3list_post;
/*SPC(0)*/
_AVrule_placeholder=nullSEQunit();
/*SPC(341)*/
_AVrule_def=
((_currn->_ATchainelim
) ? (NoDef
) : (ins_def(NoKey, Kp_prod, S_NONAME, didOfdef_entry(_AVnonterminal_def), concatSEQunit(_AS3list_post, _AVrule_placeholder))))
;
/*SPC(346)*/
_IG_incl15=_IL_incl15;
_IG_incl14=_IL_incl14;

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
_currn->_ATm_op=P_NOREDUCE;
/*SPC(293)*/
_currn->_ATpsymbol=ins_property_name(P_NOREDUCE);
/*SPC(292)*/

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
_currn->_desc1->_ATpsymbol=ins_property_name(P_SKIP);
/*SPC(274)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_currn->_desc1->_ATpsymbol=ins_property_name(P_BRACKET);
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_currn->_desc1->_ATpsymbol=ins_property_name(P_SEPA);
/*SPC(262)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_currn->_desc1->_ATpsymbol=ins_property_name(P_CODE);
/*SPC(256)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_21(_TPPrule_21 _currn)
#else
void _VS2rule_21(_currn )
_TPPrule_21 _currn;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
SEQunit _AS1list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,DefTableKey*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const7)),(&( _AS1_const6)));
_AVoptelem__const6=_AS1_const6;
/*SPC(185)*/
_AVoptelem__const7=_AS1_const7;
/*SPC(185)*/
_AVoptelem__const8=_currn->_desc1->_AT_const8;
/*SPC(185)*/
_AVt_or_nttntcnt_post=_currn->_desc1->_ATtntcnt_post;
/*SPC(0)*/
_AVoptelem_isebnf=1;
/*SPC(188)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_21(_TPPrule_21 _currn)
#else
void _VS3rule_21(_currn )
_TPPrule_21 _currn;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
SEQunit _AS1list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,SEQunit*,int*,DefTableKey*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1list_post)),(&( _AS1_const7)),(&( _AS1_const6)));
_AVliterallist_post=build_rhs(_AS1list_post, nullSEQunit(), Kp_opt);
/*SPC(381)*/

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
_AVelem__const6=_AVoptelem__const6;
/*SPC(184)*/
_AVelem__const7=_AVoptelem__const7;
/*SPC(184)*/
_AVelem__const8=ADD(_AVoptelem__const8, IDENTICAL(_AVoptelem_isebnf));
/*SPC(184)*/
_AVelem_chaincnt=2;
/*SPC(424)*/

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
VOIDEN(0);
/*SPC(144)*/

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
_currn->_AT_const18=ZERO();
/*SPC(143)*/

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
_AVstart__const16=ZERO();
/*SPC(143)*/
_AVstart_HEAD$17_RuleAttr_83=0;
/*SPC(180)*/

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
_AVt_or_nttntcnt_post=ADD(_AVt_or_nttntcnt_post, 1);
/*SPC(196)*/
_currn->_ATKey=_currn->_desc1->_ATKey;
/*SPC(67)*/

if (EQ(GetClass(_currn->_ATKey, UNDEF), UNDEF)) {
ResetClass(_currn->_ATKey, TERMINAL);

} else {
}
;
/*SPC(37)*/
TRUE;
/*SPC(115)*/
_currn->_ATtype=
((EQ(GetClass(_currn->_ATKey, UNDEF), NONTERMINAL)
) ? (Kp_nterm
) : (Kp_term))
;
/*SPC(40)*/

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
_AVt_or_nt_NewKey=GetReplace(_currn->_ATKey, _currn->_ATKey);
/*SPC(303)*/
_AVt_or_nt_symbol=_currn->_desc1->_ATsymbol;
/*SPC(248)*/
_AVt_or_nt_Sym=_currn->_desc1->_ATSym;
/*SPC(68)*/
_AVt_or_nt_def=ins_def(_AVt_or_nt_NewKey, _currn->_ATtype, GetSid(_AVt_or_nt_NewKey, _AVt_or_nt_symbol), NoDid, nullSEQunit());
/*SPC(305)*/
_AVliterallist_post=concatSEQunit(_AVliterallist_post, build_elunit(didOfdef_entry(_AVt_or_nt_def)));
/*SPC(374)*/

if (EQ((* _IG_incl6), didOfdef_entry(_AVt_or_nt_def))) {
message(ERROR, "The end-of-file symbol is not allowed here.", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(102)*/

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
_AVt_or_nttntcnt_post=ADD(_AVt_or_nttntcnt_post, 1);
/*SPC(196)*/
_currn->_ATKey=_currn->_desc1->_ATKey;
/*SPC(67)*/

if (EQ(GetClass(_currn->_ATKey, UNDEF), UNDEF)) {
ResetClass(_currn->_ATKey, TERMINAL);

} else {
}
;
/*SPC(37)*/
ResetNoStart(_currn->_ATKey, TRUE);
/*SPC(111)*/
_currn->_ATtype=
((EQ(GetClass(_currn->_ATKey, UNDEF), NONTERMINAL)
) ? (Kp_nterm
) : (Kp_term))
;
/*SPC(40)*/

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
_AVt_or_nt_NewKey=GetReplace(_currn->_ATKey, _currn->_ATKey);
/*SPC(303)*/
_AVt_or_nt_symbol=_currn->_desc1->_ATsymbol;
/*SPC(248)*/
_AVt_or_nt_Sym=_currn->_desc1->_ATSym;
/*SPC(68)*/
_AVt_or_nt_def=ins_def(_AVt_or_nt_NewKey, _currn->_ATtype, GetSid(_AVt_or_nt_NewKey, _AVt_or_nt_symbol), NoDid, nullSEQunit());
/*SPC(305)*/
_AVliterallist_post=concatSEQunit(_AVliterallist_post, build_elunit(didOfdef_entry(_AVt_or_nt_def)));
/*SPC(374)*/

if (EQ((* _IG_incl6), didOfdef_entry(_AVt_or_nt_def))) {
message(ERROR, "The end-of-file symbol is not allowed here.", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(102)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVstop_part_type=Kp_term;
/*SPC(87)*/
_AVstop_part_Sym=_AVterminal__const12;
/*SPC(93)*/
_AVstop_part_Bind=BindIdn((* _IG_incl9), _AVstop_part_Sym);
/*SPC(617)*/
_AVstop_part_Key=_AVterminal__const13;
/*SPC(94)*/
_AVstop_part_symbol=_AVterminal_symbol;
/*SPC(95)*/
_currn->_ATdef=_currn->_desc1->_ATdef;
/*SPC(96)*/
_currn->_ATeofdid=didOfdef_entry(_currn->_ATdef);
/*SPC(89)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_26(_TPPrule_26 _currn)
#else
void _VS2rule_26(_currn )
_TPPrule_26 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVstop_part_psymbol=ins_property_name(P_STOP);
/*SPC(84)*/
VOIDEN(cmrlib_newprop(_currn->_ATdef, _AVstop_part_psymbol));
/*SPC(88)*/

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
_AVrulename_Sym=_currn->_ATTERM_1;
/*SPC(54)*/
_currn->_ATsymbol=ins_symbol(StringTable(_currn->_ATTERM_1), Kp_name);
/*SPC(230)*/
_AVrulename_Bind=BindIdn((* _IG_incl9), _AVrulename_Sym);
/*SPC(617)*/
_AVrulename_Key=KeyOf(_AVrulename_Bind);
/*SPC(619)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_28(_TPPrule_28 _currn)
#else
void _VS1rule_28(_currn )
_TPPrule_28 _currn;

#endif
{
DefTableKey _AS4_const6;
int _AS4_const7;
SEQunit _AS4list_post;

_VisitVarDecl()
_VisitEntry();
_AVt_or_nttntcnt_post=0;
/*SPC(174)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);
SetChain(_currn->_desc2->_ATKey, 1, 2);
/*SPC(460)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_28(_TPPrule_28 _currn)
#else
void _VS2rule_28(_currn )
_TPPrule_28 _currn;

#endif
{
DefTableKey _AS4_const6;
int _AS4_const7;
SEQunit _AS4list_post;

_VisitVarDecl()
_VisitEntry();
_AVt_or_nttntcnt_post=_currn->_desc3->_ATtntcnt_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,int*,DefTableKey*)) (VS2MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4,(&( _AS4_const7)),(&( _AS4_const6)));
_AVrule_rhskey=_AS4_const6;
/*SPC(436)*/
_AVrule_chaincnt=_AS4_const7;
/*SPC(434)*/
_currn->_ATchainelim=AND(EQ(_AVrule_chaincnt, 1), EQ(GetChain(_currn->_desc2->_ATKey, 0), 1));
/*SPC(438)*/

if (_currn->_ATchainelim) {
Addchain(_currn->_desc2->_ATKey, _AVrule_rhskey);

} else {
}
;
/*SPC(441)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_28(_TPPrule_28 _currn)
#else
void _VS3rule_28(_currn )
_TPPrule_28 _currn;

#endif
{
DefTableKey _AS4_const6;
int _AS4_const7;
SEQunit _AS4list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVrule__const18=IDENTICAL(_currn->_desc2->_ATstartcnt);
/*SPC(6)*/
_AVrule_replkey=GetReplKey(_currn->_desc2->_ATKey);
/*SPC(443)*/

if (_currn->_ATchainelim) {
ResetReplace(_currn->_desc2->_ATKey, _AVrule_replkey);

} else {
}
;
/*SPC(461)*/

if (EQ(_AVrule_replkey, NoKey)) {
message(ERROR, "This rule lies on a cycle of chain productions", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(447)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_28(_TPPrule_28 _currn)
#else
void _VS4rule_28(_currn )
_TPPrule_28 _currn;

#endif
{
int* _IL_incl15;
int* _IL_incl14;
DefTableKey _AS4_const6;
int _AS4_const7;
SEQunit _AS4list_post;

_VisitVarDecl()
_VisitEntry();
_IL_incl15=_IG_incl15;_IG_incl15= &(_currn->_ATmaxcnt);
_IL_incl14=_IG_incl14;_IG_incl14= &(_currn->_ATisebnf);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATmaxcnt=_currn->_desc4->_ATtntcnt_post;
/*SPC(175)*/
_currn->_ATisebnf=_currn->_desc4->_AT_const8;
/*SPC(172)*/
_AVliterallist_post=nullSEQunit();
/*SPC(354)*/
(*(_CALL_VS_((NODEPTR ,SEQunit*,int*,DefTableKey*)) (VS3MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4,(&( _AS4list_post)),(&( _AS4_const7)),(&( _AS4_const6)));
_AVrule__const16=IDENTICAL(_AVnonterminal_startdid);
/*SPC(6)*/
_AVliterallist_post=_AS4list_post;
/*SPC(0)*/
_AVrule_placeholder=nullSEQunit();
/*SPC(341)*/
_AVrule_def=
((_currn->_ATchainelim
) ? (NoDef
) : (ins_def(NoKey, Kp_prod, _currn->_desc1->_ATsymbol, didOfdef_entry(_AVnonterminal_def), concatSEQunit(_AS4list_post, _AVrule_placeholder))))
;
/*SPC(355)*/
_IG_incl15=_IL_incl15;
_IG_incl14=_IL_incl14;

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
_AVgrammarname_symbol=ins_symbol(StringTable(_currn->_ATTERM_1), Kp_name);
/*SPC(230)*/
_AVgrammarname_Sym=_currn->_ATTERM_1;
/*SPC(54)*/
_AVgrammarname_type=Kp_other;
/*SPC(323)*/
_AVgrammarname_psymbol=ins_property_name(P_GRAMMAR);
/*SPC(280)*/
_AVgrammarname_Bind=BindIdn((* _IG_incl9), _AVgrammarname_Sym);
/*SPC(617)*/
_AVgrammarname_Key=KeyOf(_AVgrammarname_Bind);
/*SPC(619)*/
_AVgrammarname_def=ins_def(_AVgrammarname_Key, _AVgrammarname_type, _AVgrammarname_symbol, NoDid, nullSEQunit());
/*SPC(316)*/
VOIDEN(cmrlib_newprop(_AVgrammarname_def, _AVgrammarname_psymbol));
/*SPC(406)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_30(_TPPrule_30 _currn)
#else
void _VS3rule_30(_currn )
_TPPrule_30 _currn;

#endif
{
int* _IL_incl11;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATstartcnt);
_currn->_ATstartcnt=ADD(_currn->_desc2->_AT_const18, _currn->_desc3->_AT_const18);
/*SPC(122)*/

if (NOT(_currn->_ATstartcnt)) {
message(ERROR, "A start symbol cannot be determined.", 0, NoPosition);

} else {
}
;
/*SPC(125)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_AVgrammar_part_lhssym=GenerateName("COLA_ROOT");
/*SPC(132)*/
_AVgrammar_part_eofdid=(* _IG_incl6);
/*SPC(131)*/
_AVgrammar_part_startdid=MAXIMUM(_AVstart__const16, _AVrule_list__const16);
/*SPC(129)*/
_AVgrammar_part_psymbol=ins_property_name(P_START);
/*SPC(119)*/
_AVgrammar_part_def=ins_startrule(_AVgrammar_part_startdid, _AVgrammar_part_eofdid, _AVgrammar_part_lhssym);
/*SPC(134)*/

if (_currn->_ATstartcnt) {
VOIDEN(cmrlib_newprop(_AVgrammar_part_def, _AVgrammar_part_psymbol));

} else {
}
;
/*SPC(135)*/
_IG_incl11=_IL_incl11;

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
_AVterminal__const12=_currn->_desc1->_ATSym;
/*SPC(828)*/
_AVterminal__const13=_currn->_desc1->_ATKey;
/*SPC(828)*/
_AVterminal_symbol=_currn->_desc1->_ATsymbol;
/*SPC(248)*/
_currn->_ATKey=_currn->_desc1->_ATKey;
/*SPC(67)*/
_AVterminal_type=Kp_term;
/*SPC(21)*/
Classify(_currn->_ATKey, TERMINAL);
/*SPC(22)*/
_currn->_ATdef=ins_def(_currn->_ATKey, _AVterminal_type, _AVterminal_symbol, NoDid, nullSEQunit());
/*SPC(316)*/

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

if (EQ(GetClass(_currn->_ATKey, FAULT), FAULT)) {
message(ERROR, MESSAGE1, 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(25)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVterminal__const1=_currn->_desc1->_ATSym;
/*SPC(828)*/
_AVterminal__const2=_currn->_desc1->_ATsymbol;
/*SPC(828)*/
_AVterminal__const3=_currn->_desc1->_ATKey;
/*SPC(828)*/
_AVterminal_Sym=_currn->_desc1->_ATSym;
/*SPC(68)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_64(_TPPrule_64 _currn)
#else
void _VS1rule_64(_currn )
_TPPrule_64 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVterminal__const12=_currn->_desc1->_ATSym;
/*SPC(824)*/
_AVterminal__const13=_currn->_desc1->_ATKey;
/*SPC(824)*/
_AVterminal_symbol=_currn->_desc1->_ATsymbol;
/*SPC(248)*/
_currn->_ATKey=_currn->_desc1->_ATKey;
/*SPC(67)*/
_AVterminal_type=Kp_term;
/*SPC(21)*/
Classify(_currn->_ATKey, TERMINAL);
/*SPC(22)*/
_currn->_ATdef=ins_def(_currn->_ATKey, _AVterminal_type, _AVterminal_symbol, NoDid, nullSEQunit());
/*SPC(316)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_64(_TPPrule_64 _currn)
#else
void _VS2rule_64(_currn )
_TPPrule_64 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (EQ(GetClass(_currn->_ATKey, FAULT), FAULT)) {
message(ERROR, MESSAGE1, 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(25)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVterminal__const1=_currn->_desc1->_ATSym;
/*SPC(824)*/
_AVterminal__const2=_currn->_desc1->_ATsymbol;
/*SPC(824)*/
_AVterminal__const3=_currn->_desc1->_ATKey;
/*SPC(824)*/
_AVterminal_Sym=_currn->_desc1->_ATSym;
/*SPC(68)*/

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

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_63(_TPPrule_63 _currn)
#else
void _VS2rule_63(_currn )
_TPPrule_63 _currn;

#endif
{
SID* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATpsymbol);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl1=_IL_incl1;

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
_AVstop_part_type=Kp_term;
/*SPC(87)*/
_AVstop_part_Sym=ins_eof();
/*SPC(85)*/
_AVstop_part_Bind=BindIdn((* _IG_incl9), _AVstop_part_Sym);
/*SPC(617)*/
_AVstop_part_Key=KeyOf(_AVstop_part_Bind);
/*SPC(619)*/
_AVstop_part_symbol=ins_symbol(StringTable(_AVstop_part_Sym), Kp_name);
/*SPC(86)*/
_currn->_ATdef=ins_def(_AVstop_part_Key, _AVstop_part_type, _AVstop_part_symbol, NoDid, nullSEQunit());
/*SPC(316)*/
_currn->_ATeofdid=didOfdef_entry(_currn->_ATdef);
/*SPC(89)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_62(_TPPrule_62 _currn)
#else
void _VS2rule_62(_currn )
_TPPrule_62 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVstop_part_psymbol=ins_property_name(P_STOP);
/*SPC(84)*/
VOIDEN(cmrlib_newprop(_currn->_ATdef, _AVstop_part_psymbol));
/*SPC(88)*/

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
_AVstop_part_type=Kp_term;
/*SPC(87)*/
_AVstop_part_Sym=ins_eof();
/*SPC(85)*/
_AVstop_part_Bind=BindIdn((* _IG_incl9), _AVstop_part_Sym);
/*SPC(617)*/
_AVstop_part_Key=KeyOf(_AVstop_part_Bind);
/*SPC(619)*/
_AVstop_part_symbol=ins_symbol(StringTable(_AVstop_part_Sym), Kp_name);
/*SPC(86)*/
_currn->_ATdef=ins_def(_AVstop_part_Key, _AVstop_part_type, _AVstop_part_symbol, NoDid, nullSEQunit());
/*SPC(316)*/
_currn->_ATeofdid=didOfdef_entry(_currn->_ATdef);
/*SPC(89)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_61(_TPPrule_61 _currn)
#else
void _VS2rule_61(_currn )
_TPPrule_61 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVstop_part_psymbol=ins_property_name(P_STOP);
/*SPC(84)*/
VOIDEN(cmrlib_newprop(_currn->_ATdef, _AVstop_part_psymbol));
/*SPC(88)*/

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
_currn->_ATtntcnt_post=_AVt_or_nttntcnt_post;
/*SPC(0)*/

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
_currn->_ATtntcnt_post=_AVt_or_nttntcnt_post;
/*SPC(0)*/

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

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_58(_TPPrule_58 _currn)
#else
void _VS2rule_58(_currn )
_TPPrule_58 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_58(_TPPrule_58 _currn)
#else
void _VS3rule_58(_currn )
_TPPrule_58 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_AT_const18=_AVG3__const18;
/*SPC(800)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_58(_TPPrule_58 _currn)
#else
void _VS4rule_58(_currn )
_TPPrule_58 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVrule_list__const16=_AVG3__const16;
/*SPC(800)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_57(_TPPrule_57 _currn)
#else
void _VS1rule_57(_currn )
_TPPrule_57 _currn;

#endif
{
Environment* _IL_incl13;
Environment* _IL_incl9;
DID* _IL_incl6;

_VisitVarDecl()
_VisitEntry();
_IL_incl13=_IG_incl13;_IG_incl13= &(_currn->_ATLiteralEnv);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATNonliteralEnv);
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATeofdid);
_currn->_ATNonliteralEnv=NonliteralRootEnv;
/*SPC(582)*/
_currn->_ATLiteralEnv=LiteralRootEnv;
/*SPC(486)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATeofdid=_AVpgs_root__const27;
/*SPC(79)*/
_AVliterallist_post=nullSEQunit();
/*SPC(337)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl13=_IL_incl13;
_IG_incl9=_IL_incl9;
_IG_incl6=_IL_incl6;

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);
_AVpgs_root__const27=_currn->_desc2->_ATeofdid;
/*SPC(792)*/

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);

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
_AVnonterminal_Sym=_currn->_ATTERM_1;
/*SPC(54)*/
_AVnonterminal_Bind=BindIdn((* _IG_incl9), _AVnonterminal_Sym);
/*SPC(617)*/
_currn->_ATKey=KeyOf(_AVnonterminal_Bind);
/*SPC(619)*/
Classify(_currn->_ATKey, NONTERMINAL);
/*SPC(30)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_55(_TPPrule_55 _currn)
#else
void _VS2rule_55(_currn )
_TPPrule_55 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATsymbol=ins_symbol(StringTable(_currn->_ATTERM_1), Kp_name);
/*SPC(230)*/
_currn->_ATIsFirstOcc=SetGetFirstOcc(_currn->_ATKey, 1, 0);
/*SPC(686)*/
_currn->_ATstartcnt=
((_currn->_ATIsFirstOcc
) ? (
((GetNoStart(_currn->_ATKey, FALSE)
) ? (0
) : (1))

) : (0))
;
/*SPC(150)*/
ResetSid(_currn->_ATKey, _currn->_ATsymbol);
/*SPC(234)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_55(_TPPrule_55 _currn)
#else
void _VS3rule_55(_currn )
_TPPrule_55 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (AND(AND(_currn->_ATIsFirstOcc, _currn->_ATstartcnt), GT((* _IG_incl11), 1))) {
message(ERROR, "This is one of several start symbols. Only one is allowed.", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(160)*/

if (EQ(GetClass(_currn->_ATKey, FAULT), FAULT)) {
message(ERROR, MESSAGE2, 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(33)*/
_AVnonterminal_NewKey=GetReplace(_currn->_ATKey, _currn->_ATKey);
/*SPC(303)*/
_AVnonterminal_type=Kp_nterm;
/*SPC(29)*/
_AVnonterminal_def=ins_def(_AVnonterminal_NewKey, _AVnonterminal_type, GetSid(_AVnonterminal_NewKey, _currn->_ATsymbol), NoDid, nullSEQunit());
/*SPC(305)*/
_AVnonterminal_startdid=
((_currn->_ATstartcnt
) ? (didOfdef_entry(_AVnonterminal_def)
) : (NoDid))
;
/*SPC(154)*/

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
_currn->_ATsymbol=ins_symbol(StringTable(_currn->_ATTERM_1), Kp_name);
/*SPC(230)*/
_AVnonliteral_Bind=BindIdn((* _IG_incl9), _currn->_ATSym);
/*SPC(617)*/
_currn->_ATKey=KeyOf(_AVnonliteral_Bind);
/*SPC(619)*/
ResetSid(_currn->_ATKey, _currn->_ATsymbol);
/*SPC(234)*/

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
_currn->_ATsymbol=ins_symbol(StringTable(_currn->_ATTERM_1), Kp_string);
/*SPC(226)*/
_AVliteral_Bind=BindIdn((* _IG_incl13), _currn->_ATSym);
/*SPC(521)*/
_currn->_ATKey=KeyOf(_AVliteral_Bind);
/*SPC(523)*/
ResetSid(_currn->_ATKey, _currn->_ATsymbol);
/*SPC(234)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_52(_TPPrule_52 _currn)
#else
void _VS3rule_52(_currn )
_TPPrule_52 _currn;

#endif
{
int* _IL_incl11;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATstartcnt);
_currn->_ATstartcnt=ADD(_currn->_desc1->_AT_const18, _currn->_desc2->_AT_const18);
/*SPC(122)*/

if (NOT(_currn->_ATstartcnt)) {
message(ERROR, "A start symbol cannot be determined.", 0, NoPosition);

} else {
}
;
/*SPC(125)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVgrammar_part_lhssym=GenerateName("COLA_ROOT");
/*SPC(132)*/
_AVgrammar_part_eofdid=(* _IG_incl6);
/*SPC(131)*/
_AVgrammar_part_startdid=MAXIMUM(_AVstart__const16, _AVrule_list__const16);
/*SPC(129)*/
_AVgrammar_part_psymbol=ins_property_name(P_START);
/*SPC(119)*/
_AVgrammar_part_def=ins_startrule(_AVgrammar_part_startdid, _AVgrammar_part_eofdid, _AVgrammar_part_lhssym);
/*SPC(134)*/

if (_currn->_ATstartcnt) {
VOIDEN(cmrlib_newprop(_AVgrammar_part_def, _AVgrammar_part_psymbol));

} else {
}
;
/*SPC(135)*/
_IG_incl11=_IL_incl11;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_51(_TPPrule_51 _currn,int* _AS0_const8,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS2rule_51(_currn ,_AS0_const8,_AS0_const7,_AS0_const6)
_TPPrule_51 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;
int* _AS0_const8;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
int _AS1_const8;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*,DefTableKey*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const8)),(&( _AS1_const7)),(&( _AS1_const6)));
(* _AS0_const6)=_AS1_const6;
/*SPC(772)*/
(* _AS0_const7)=_AS1_const7;
/*SPC(772)*/
(* _AS0_const8)=_AS1_const8;
/*SPC(772)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_51(_TPPrule_51 _currn,int* _AS0_const8,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS3rule_51(_currn ,_AS0_const8,_AS0_const7,_AS0_const6)
_TPPrule_51 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;
int* _AS0_const8;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
int _AS1_const8;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*,DefTableKey*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const8)),(&( _AS1_const7)),(&( _AS1_const6)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_50(_TPPrule_50 _currn,int* _AS0_const8,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS2rule_50(_currn ,_AS0_const8,_AS0_const7,_AS0_const6)
_TPPrule_50 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;
int* _AS0_const8;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
int _AS1_const8;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*,DefTableKey*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const8)),(&( _AS1_const7)),(&( _AS1_const6)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(* _AS0_const6)=KEY(_AS1_const6, _AVelem__const6);
/*SPC(768)*/
(* _AS0_const7)=ADD(_AS1_const7, ADD(_AVelem__const7, IDENTICAL(_AVelem_chaincnt)));
/*SPC(768)*/
(* _AS0_const8)=ADD(_AS1_const8, _AVelem__const8);
/*SPC(768)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_50(_TPPrule_50 _currn,int* _AS0_const8,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS3rule_50(_currn ,_AS0_const8,_AS0_const7,_AS0_const6)
_TPPrule_50 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;
int* _AS0_const8;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
int _AS1_const8;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*,DefTableKey*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const8)),(&( _AS1_const7)),(&( _AS1_const6)));
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_49(_TPPrule_49 _currn,int* _AS0_const8,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS2rule_49(_currn ,_AS0_const8,_AS0_const7,_AS0_const6)
_TPPrule_49 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;
int* _AS0_const8;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
int _AS1_const8;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*,DefTableKey*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const8)),(&( _AS1_const7)),(&( _AS1_const6)));
_currn->_desc2->_ATtntcnt_pre=_AVt_or_nttntcnt_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(* _AS0_const6)=_AS1_const6;
/*SPC(764)*/
(* _AS0_const7)=ADD(_AS1_const7, IDENTICAL(_AVconnection_chaincnt));
/*SPC(764)*/
(* _AS0_const8)=_AS1_const8;
/*SPC(764)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_49(_TPPrule_49 _currn,int* _AS0_const8,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS3rule_49(_currn ,_AS0_const8,_AS0_const7,_AS0_const6)
_TPPrule_49 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;
int* _AS0_const8;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
int _AS1_const8;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*,DefTableKey*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const8)),(&( _AS1_const7)),(&( _AS1_const6)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_48(_TPPrule_48 _currn,int* _AS0_const8,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS2rule_48(_currn ,_AS0_const8,_AS0_const7,_AS0_const6)
_TPPrule_48 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;
int* _AS0_const8;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0_const6)=NOKEY();
/*SPC(760)*/
(* _AS0_const7)=ZERO();
/*SPC(760)*/
(* _AS0_const8)=ZERO();
/*SPC(760)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_48(_TPPrule_48 _currn,int* _AS0_const8,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS3rule_48(_currn ,_AS0_const8,_AS0_const7,_AS0_const6)
_TPPrule_48 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;
int* _AS0_const8;

#endif
{

_VisitVarDecl()
_VisitEntry();

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG3__const18=ADD(_AVG3__const18, _AVrule__const18);
/*SPC(756)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_47(_TPPrule_47 _currn)
#else
void _VS4rule_47(_currn )
_TPPrule_47 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG3__const16=MAXIMUM(_AVG3__const16, _AVrule__const16);
/*SPC(756)*/

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
_AVG3__const18=ZERO();
/*SPC(752)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_46(_TPPrule_46 _currn)
#else
void _VS4rule_46(_currn )
_TPPrule_46 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVG3__const16=ZERO();
/*SPC(752)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_41(_TPPrule_41 _currn)
#else
void _VS2rule_41(_currn )
_TPPrule_41 _currn;

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
void _VS2rule_40(_TPPrule_40 _currn)
#else
void _VS2rule_40(_currn )
_TPPrule_40 _currn;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
SEQunit _AS1list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,DefTableKey*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const7)),(&( _AS1_const6)));
_AVelem__const6=_AS1_const6;
/*SPC(728)*/
_AVelem__const7=_AS1_const7;
/*SPC(728)*/
_AVelem__const8=_currn->_desc1->_AT_const8;
/*SPC(728)*/
_AVt_or_nttntcnt_post=_currn->_desc1->_ATtntcnt_post;
/*SPC(0)*/
_AVelem_chaincnt=2;
/*SPC(424)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_40(_TPPrule_40 _currn)
#else
void _VS3rule_40(_currn )
_TPPrule_40 _currn;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
SEQunit _AS1list_post;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,SEQunit*,int*,DefTableKey*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1list_post)),(&( _AS1_const7)),(&( _AS1_const6)));
_AVliterallist_post=_AS1list_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_39(_TPPrule_39 _currn)
#else
void _VS2rule_39(_currn )
_TPPrule_39 _currn;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
int _AS1_const8;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*,DefTableKey*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const8)),(&( _AS1_const7)),(&( _AS1_const6)));
_AVelem_list__const6=_AS1_const6;
/*SPC(724)*/
_AVelem_list__const7=_AS1_const7;
/*SPC(724)*/
_AVelem_list__const8=_AS1_const8;
/*SPC(724)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_39(_TPPrule_39 _currn)
#else
void _VS3rule_39(_currn )
_TPPrule_39 _currn;

#endif
{
DefTableKey _AS1_const6;
int _AS1_const7;
int _AS1_const8;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*,DefTableKey*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const8)),(&( _AS1_const7)),(&( _AS1_const6)));

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
_currn->_ATisebnf=1;
/*SPC(188)*/

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
_currn->_ATisebnf=1;
/*SPC(188)*/

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
_AVt_or_nttntcnt_post=_currn->_ATtntcnt_pre;
/*SPC(0)*/
_AVconnection_chaincnt=2;
/*SPC(424)*/
_AVconnection_Sym=_currn->_ATTERM_1;
/*SPC(50)*/
_AVconnection_Bind=BindIdn((* _IG_incl13), _AVconnection_Sym);
/*SPC(521)*/
_currn->_ATKey=KeyOf(_AVconnection_Bind);
/*SPC(523)*/

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

if ((* _IG_incl14)) {
message(WARNING, "Connections within ebnf rules are not properly transformed.", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(209)*/
_AVconnection_symbol=ins_symbol(StringTable(_currn->_ATTERM_1), Kp_string);
/*SPC(226)*/
_AVconnection_def=ins_connect(_currn->_ATKey, _AVconnection_symbol);
/*SPC(201)*/
_AVconnection_psymbol=ins_property_name(P_CONNECT);
/*SPC(200)*/
_AVconnection_connect=build_elunit(didOfdef_entry(_AVconnection_def));
/*SPC(204)*/
_AVliterallist_post=concatSEQunit(_AVliterallist_post, 
((LT(_currn->_ATtntcnt_pre, (* _IG_incl15))
) ? (ins_nullnt(_currn->_ATKey, _AVconnection_connect)
) : (_AVconnection_connect))
);
/*SPC(211)*/
VOIDEN(cmrlib_newprop(_AVconnection_def, _AVconnection_psymbol));
/*SPC(202)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_35(_TPPrule_35 _currn)
#else
void _VS2rule_35(_currn )
_TPPrule_35 _currn;

#endif
{
SID* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATpsymbol);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl2=_IL_incl2;

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
void _VS2rule_32(_TPPrule_32 _currn,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS2rule_32(_currn ,_AS0_const7,_AS0_const6)
_TPPrule_32 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0_const6)=_AVelem_list__const6;
/*SPC(696)*/
(* _AS0_const7)=_AVelem_list__const7;
/*SPC(696)*/
_currn->_AT_const8=_AVelem_list__const8;
/*SPC(696)*/
_currn->_ATtntcnt_post=_AVt_or_nttntcnt_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_32(_TPPrule_32 _currn,SEQunit* _AS0list_post,int* _AS0_const7,DefTableKey* _AS0_const6)
#else
void _VS3rule_32(_currn ,_AS0list_post,_AS0_const7,_AS0_const6)
_TPPrule_32 _currn;
DefTableKey* _AS0_const6;
int* _AS0_const7;
SEQunit* _AS0list_post;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0list_post)=_AVliterallist_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1Rmod_op1(_TPPRmod_op1 _currn)
#else
void _VS1Rmod_op1(_currn )
_TPPRmod_op1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATm_op=P_REDUCE;
/*SPC(288)*/
_currn->_ATpsymbol=ins_property_name(P_REDUCE);
/*SPC(287)*/

_VisitExit();
}

