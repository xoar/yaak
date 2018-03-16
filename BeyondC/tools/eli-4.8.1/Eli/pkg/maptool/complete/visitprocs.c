
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
DefTableKey* _IG_incl21;
int* _IG_incl14;
DefTableKey* _IG_incl11;
DefTableKey* _IG_incl10;
int* _IG_incl7;
int* _IG_incl3;
DefTableKey* _IG_incl1;
Environment* _IG_incl0;
PTGNode _AVLST_Source__const11;
int _AVLST_Source__const12;
PTGNode _AVLST_Source__const15;
PTGNode _AVLST_Source__const16;
PTGNode _AVLST_Source__const17;
PTGNode _AVLST_Source__const18;
int _AVLST_Source__const19;
PTGNode _AVLST_Source__const27;
DefTableKey _AVLST_ConAlt__const6;
PTGNode _AVLST_ConAlt__const11;
int _AVLST_ConAlt__const28;
int _AVLST_ConAlt__const29;
SymbolPListPtr _AVMapText_cSymbolPListPtr_post;
tOilSetSig _AVLST_ConAltsetsig_post;
int _AVLST_AbsElements__const2;
int _AVLST_AbsElements__const3;
DefTableKey _AVLST_AbsElements__const5;
PTGNode _AVLST_AbsElements__const11;
tOilArgSig _AVLST_AbsElementssig_post;
DefTableKeyList _AVMapMemberssymset_post;
int _AVLST_MapReorderAlt__const0;
int _AVLST_MapReorderAlt__const1;
intList _AVLST_MapReorderAltpos_post;
int _AVMapReorder__const0;
int _AVMapReorder__const1;
SymbolPList _AVMapReorder__SymbolPauxList;
intList _AVMapReorder_olist;
SymbolPList _AVMapReorder_SymbolPList;
SymbolPList _AVMapProd__SymbolPauxList;
SymbolPList _AVMapProd_SymbolPList;
DefTableKey _AVMapProd_Key;
DefTableKey _AVMapAbs_Key;
PTGNode _AVAbsSignature__const11;
SymbolPList _AVAbsSignature__SymbolPauxList;
SymbolPList _AVAbsSignature_SymbolPList;
Binding _AVRuleIdUse_Bind;
int _AVRuleIdUse_Sym;
DefTableKey _AVRuleIdUse_Key;
Binding _AVMapLHS_Bind;
int _AVMapLHS_Sym;
DefTableKey _AVMapLHS_Key;
Binding _AVMaptoId_Bind;
Binding _AVAbsRuleId_Bind;
int _AVAbsRuleId_Sym;
DefTableKey _AVAbsRuleId_Key;
int _AVMapText_SymbolPTakeIt;
Binding _AVMapText_Bind;
SymbolP _AVMapText_SymbolPElem;
SymbolP _AVMapText_Symbol;
SymbolP _AVMapPosition_SymbolPElem;
int _AVMapReorderAlt__const0;
int _AVMapReorderAlt__const1;
int _AVMapElement_SymbolPTakeIt;
Binding _AVMapElement_Bind;
int _AVMapElement_Sym;
int _AVMapElement_Class;
DefTableKey _AVMapElement_Key;
SymbolP _AVMapElement_SymbolPElem;
SymbolP _AVMapElement_Symbol;
DefTableKey _AVMapMember_Key_RuleAttr_103;
Binding _AVMapMember_Bind;
int _AVMapMember_Sym;
int _AVAbsAlt_SymbolPTakeIt;
Binding _AVAbsAlt_Bind;
int _AVAbsAlt_Sym;
DefTableKey _AVAbsAlt_Key;
SymbolP _AVAbsAlt_SymbolPElem;
SymbolP _AVAbsAlt_Symbol;
int _AVAbsElements__const2;
int _AVAbsElements__const3;
PTGNode _AVAbsElements__const11;
Binding _AVBottomUpRule_Bind;
int _AVBottomUpRule_Sym;
DefTableKey _AVBottomUpRule_Key;
DefTableKeyList _AVMapSymbol_KeyList;
int _AVAbsElement_SymbolPTakeIt;
Binding _AVAbsElement_Bind;
int _AVAbsElement_Sym;
int _AVAbsElement_Class;
SymbolP _AVAbsElement_SymbolPElem;
SymbolP _AVAbsElement_Symbol;
int _AVAbsElement_IsFirstOcc;
int _AVConElement_SymbolPTakeIt;
Binding _AVConElement_Bind;
int _AVConElement_Sym;
int _AVConElement_Class;
SymbolP _AVConElement_SymbolPElem;
SymbolP _AVConElement_Symbol;
int _AVConElement_IsFirstOcc;
Binding _AVAbsLHS_Bind;
PTGNode _AVConAlt__const11;
int _AVConAlt__const28;
int _AVConAlt__const29;
Binding _AVConLHS_Bind;
DefTableKey _AVConProd_Key_RuleAttr_129;
tOilSetSig _AVConProd_signature_RuleAttr_129;
SymbolPList _AVConProd__SymbolPauxList;
SymbolPList _AVConProd_SymbolPList;
PTGNode _AVSource_SymOut;
PTGNode _AVSource_Pgram;
PTGNode _AVSource_StartOut;
PTGNode _AVSource_AbsTOut;
PTGNode _AVSource_AbsSOut;
PTGNode _AVSource_ConOut;

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
void _VS1LST_BottomUpRulerule_35(_TPPLST_BottomUpRulerule_35 _currn)
#else
void _VS1LST_BottomUpRulerule_35(_currn )
_TPPLST_BottomUpRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2LST_BottomUpRulerule_35(_TPPLST_BottomUpRulerule_35 _currn)
#else
void _VS2LST_BottomUpRulerule_35(_currn )
_TPPLST_BottomUpRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3LST_BottomUpRulerule_35(_TPPLST_BottomUpRulerule_35 _currn)
#else
void _VS3LST_BottomUpRulerule_35(_currn )
_TPPLST_BottomUpRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4LST_BottomUpRulerule_35(_TPPLST_BottomUpRulerule_35 _currn)
#else
void _VS4LST_BottomUpRulerule_35(_currn )
_TPPLST_BottomUpRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5LST_BottomUpRulerule_35(_TPPLST_BottomUpRulerule_35 _currn)
#else
void _VS5LST_BottomUpRulerule_35(_currn )
_TPPLST_BottomUpRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6LST_BottomUpRulerule_35(_TPPLST_BottomUpRulerule_35 _currn)
#else
void _VS6LST_BottomUpRulerule_35(_currn )
_TPPLST_BottomUpRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const12=ADD(IDENTICAL(_currn->_desc1->_ATGotBottomUp), _AVLST_Source__const12);
/*SPC(183)*/
_AVLST_Source__const19=_AVLST_Source__const19;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7LST_BottomUpRulerule_35(_TPPLST_BottomUpRulerule_35 _currn)
#else
void _VS7LST_BottomUpRulerule_35(_currn )
_TPPLST_BottomUpRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS7MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const15=_AVLST_Source__const15;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS8LST_BottomUpRulerule_35(_TPPLST_BottomUpRulerule_35 _currn)
#else
void _VS8LST_BottomUpRulerule_35(_currn )
_TPPLST_BottomUpRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS8MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const11=_AVLST_Source__const11;
/*SPC(183)*/
_AVLST_Source__const16=_AVLST_Source__const16;
/*SPC(183)*/
_AVLST_Source__const17=_AVLST_Source__const17;
/*SPC(183)*/
_AVLST_Source__const18=_AVLST_Source__const18;
/*SPC(183)*/
_AVLST_Source__const27=_AVLST_Source__const27;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1LST_MapChainsrule_35(_TPPLST_MapChainsrule_35 _currn)
#else
void _VS1LST_MapChainsrule_35(_currn )
_TPPLST_MapChainsrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2LST_MapChainsrule_35(_TPPLST_MapChainsrule_35 _currn)
#else
void _VS2LST_MapChainsrule_35(_currn )
_TPPLST_MapChainsrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6LST_MapChainsrule_35(_TPPLST_MapChainsrule_35 _currn)
#else
void _VS6LST_MapChainsrule_35(_currn )
_TPPLST_MapChainsrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const12=_AVLST_Source__const12;
/*SPC(183)*/
_AVLST_Source__const19=_AVLST_Source__const19;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7LST_MapChainsrule_35(_TPPLST_MapChainsrule_35 _currn)
#else
void _VS7LST_MapChainsrule_35(_currn )
_TPPLST_MapChainsrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS7MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const15=_AVLST_Source__const15;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS8LST_MapChainsrule_35(_TPPLST_MapChainsrule_35 _currn)
#else
void _VS8LST_MapChainsrule_35(_currn )
_TPPLST_MapChainsrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS8MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const11=_AVLST_Source__const11;
/*SPC(183)*/
_AVLST_Source__const16=_AVLST_Source__const16;
/*SPC(183)*/
_AVLST_Source__const17=_AVLST_Source__const17;
/*SPC(183)*/
_AVLST_Source__const18=_AVLST_Source__const18;
/*SPC(183)*/
_AVLST_Source__const27=_AVLST_Source__const27;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3LST_MapRulerule_35(_TPPLST_MapRulerule_35 _currn)
#else
void _VS3LST_MapRulerule_35(_currn )
_TPPLST_MapRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6LST_MapRulerule_35(_TPPLST_MapRulerule_35 _currn)
#else
void _VS6LST_MapRulerule_35(_currn )
_TPPLST_MapRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const12=_AVLST_Source__const12;
/*SPC(183)*/
_AVLST_Source__const19=_AVLST_Source__const19;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7LST_MapRulerule_35(_TPPLST_MapRulerule_35 _currn)
#else
void _VS7LST_MapRulerule_35(_currn )
_TPPLST_MapRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS7MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const15=_AVLST_Source__const15;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS8LST_MapRulerule_35(_TPPLST_MapRulerule_35 _currn)
#else
void _VS8LST_MapRulerule_35(_currn )
_TPPLST_MapRulerule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS8MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const11=_AVLST_Source__const11;
/*SPC(183)*/
_AVLST_Source__const16=_AVLST_Source__const16;
/*SPC(183)*/
_AVLST_Source__const17=_AVLST_Source__const17;
/*SPC(183)*/
_AVLST_Source__const18=_AVLST_Source__const18;
/*SPC(183)*/
_AVLST_Source__const27=_AVLST_Source__const27;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2LST_MapSymbolrule_35(_TPPLST_MapSymbolrule_35 _currn)
#else
void _VS2LST_MapSymbolrule_35(_currn )
_TPPLST_MapSymbolrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6LST_MapSymbolrule_35(_TPPLST_MapSymbolrule_35 _currn)
#else
void _VS6LST_MapSymbolrule_35(_currn )
_TPPLST_MapSymbolrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const12=_AVLST_Source__const12;
/*SPC(183)*/
_AVLST_Source__const19=_AVLST_Source__const19;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7LST_MapSymbolrule_35(_TPPLST_MapSymbolrule_35 _currn)
#else
void _VS7LST_MapSymbolrule_35(_currn )
_TPPLST_MapSymbolrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS7MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const15=_AVLST_Source__const15;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS8LST_MapSymbolrule_35(_TPPLST_MapSymbolrule_35 _currn)
#else
void _VS8LST_MapSymbolrule_35(_currn )
_TPPLST_MapSymbolrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS8MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const11=_AVLST_Source__const11;
/*SPC(183)*/
_AVLST_Source__const16=_AVLST_Source__const16;
/*SPC(183)*/
_AVLST_Source__const17=_AVLST_Source__const17;
/*SPC(183)*/
_AVLST_Source__const18=_AVLST_Source__const18;
/*SPC(183)*/
_AVLST_Source__const27=_AVLST_Source__const27;
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4LST_AbsProdrule_35(_TPPLST_AbsProdrule_35 _currn)
#else
void _VS4LST_AbsProdrule_35(_currn )
_TPPLST_AbsProdrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6LST_AbsProdrule_35(_TPPLST_AbsProdrule_35 _currn)
#else
void _VS6LST_AbsProdrule_35(_currn )
_TPPLST_AbsProdrule_35 _currn;

#endif
{
PTGNode _AS1_const11;
PTGNode _AS1Pgram;
PTGNode _AS1StartOut;
PTGNode _AS1AbsTOut;
PTGNode _AS1AbsSOut;
PTGNode _AS1ConOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const12=_AVLST_Source__const12;
/*SPC(183)*/
_AVLST_Source__const19=ADD(IDENTICAL(_currn->_desc1->_ATaxiom), _AVLST_Source__const19);
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7LST_AbsProdrule_35(_TPPLST_AbsProdrule_35 _currn)
#else
void _VS7LST_AbsProdrule_35(_currn )
_TPPLST_AbsProdrule_35 _currn;

#endif
{
PTGNode _AS1_const11;
PTGNode _AS1Pgram;
PTGNode _AS1StartOut;
PTGNode _AS1AbsTOut;
PTGNode _AS1AbsSOut;
PTGNode _AS1ConOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Pgram)));
(*(_CALL_VS_((NODEPTR )) (VS7MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const15=PTGSeq(IDENTICAL(_AS1Pgram), _AVLST_Source__const15);
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS8LST_AbsProdrule_35(_TPPLST_AbsProdrule_35 _currn)
#else
void _VS8LST_AbsProdrule_35(_currn )
_TPPLST_AbsProdrule_35 _currn;

#endif
{
PTGNode _AS1_const11;
PTGNode _AS1Pgram;
PTGNode _AS1StartOut;
PTGNode _AS1AbsTOut;
PTGNode _AS1AbsSOut;
PTGNode _AS1ConOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*,PTGNode*,PTGNode*,PTGNode*,PTGNode*,PTGNode*)) (VS6MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1ConOut)),(&( _AS1AbsSOut)),(&( _AS1AbsTOut)),(&( _AS1StartOut)),(&( _AS1Pgram)),(&( _AS1_const11)));
(*(_CALL_VS_((NODEPTR )) (VS8MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const11=PTGSeq(_AS1_const11, _AVLST_Source__const11);
/*SPC(183)*/
_AVLST_Source__const16=PTGSeq(IDENTICAL(_AS1StartOut), _AVLST_Source__const16);
/*SPC(183)*/
_AVLST_Source__const17=PTGSeq(IDENTICAL(_AS1AbsTOut), _AVLST_Source__const17);
/*SPC(183)*/
_AVLST_Source__const18=PTGSeq(IDENTICAL(_AS1AbsSOut), _AVLST_Source__const18);
/*SPC(183)*/
_AVLST_Source__const27=PTGSeq(IDENTICAL(_AS1ConOut), _AVLST_Source__const27);
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5LST_ConProdrule_35(_TPPLST_ConProdrule_35 _currn)
#else
void _VS5LST_ConProdrule_35(_currn )
_TPPLST_ConProdrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6LST_ConProdrule_35(_TPPLST_ConProdrule_35 _currn)
#else
void _VS6LST_ConProdrule_35(_currn )
_TPPLST_ConProdrule_35 _currn;

#endif
{
PTGNode _AS1_const11;
PTGNode _AS1Pgram;
PTGNode _AS1StartOut;
PTGNode _AS1AbsTOut;
PTGNode _AS1ConOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const12=_AVLST_Source__const12;
/*SPC(183)*/
_AVLST_Source__const19=ADD(IDENTICAL(_currn->_desc1->_ATaxiom), _AVLST_Source__const19);
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7LST_ConProdrule_35(_TPPLST_ConProdrule_35 _currn)
#else
void _VS7LST_ConProdrule_35(_currn )
_TPPLST_ConProdrule_35 _currn;

#endif
{
PTGNode _AS1_const11;
PTGNode _AS1Pgram;
PTGNode _AS1StartOut;
PTGNode _AS1AbsTOut;
PTGNode _AS1ConOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Pgram)));
(*(_CALL_VS_((NODEPTR )) (VS7MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const15=PTGSeq(IDENTICAL(_AS1Pgram), _AVLST_Source__const15);
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS8LST_ConProdrule_35(_TPPLST_ConProdrule_35 _currn)
#else
void _VS8LST_ConProdrule_35(_currn )
_TPPLST_ConProdrule_35 _currn;

#endif
{
PTGNode _AS1_const11;
PTGNode _AS1Pgram;
PTGNode _AS1StartOut;
PTGNode _AS1AbsTOut;
PTGNode _AS1ConOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*,PTGNode*,PTGNode*,PTGNode*,PTGNode*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1ConOut)),(&( _AS1AbsTOut)),(&( _AS1StartOut)),(&( _AS1Pgram)),(&( _AS1_const11)));
(*(_CALL_VS_((NODEPTR )) (VS8MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_Source__const11=PTGSeq(_AS1_const11, _AVLST_Source__const11);
/*SPC(183)*/
_AVLST_Source__const16=PTGSeq(IDENTICAL(_AS1StartOut), _AVLST_Source__const16);
/*SPC(183)*/
_AVLST_Source__const17=PTGSeq(IDENTICAL(_AS1AbsTOut), _AVLST_Source__const17);
/*SPC(183)*/
_AVLST_Source__const18=PTGSeq(IDENTICAL(_AS1AbsTOut), _AVLST_Source__const18);
/*SPC(183)*/
_AVLST_Source__const27=PTGSeq(IDENTICAL(_AS1ConOut), _AVLST_Source__const27);
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6LST_0rule_35(_TPPLST_0rule_35 _currn)
#else
void _VS6LST_0rule_35(_currn )
_TPPLST_0rule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_Source__const12=ZERO();
/*SPC(183)*/
_AVLST_Source__const19=ZERO();
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7LST_0rule_35(_TPPLST_0rule_35 _currn)
#else
void _VS7LST_0rule_35(_currn )
_TPPLST_0rule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_Source__const15=PTGNull();
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS8LST_0rule_35(_TPPLST_0rule_35 _currn)
#else
void _VS8LST_0rule_35(_currn )
_TPPLST_0rule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_Source__const11=PTGNull();
/*SPC(183)*/
_AVLST_Source__const16=PTGNull();
/*SPC(183)*/
_AVLST_Source__const17=PTGNull();
/*SPC(183)*/
_AVLST_Source__const18=PTGNull();
/*SPC(183)*/
_AVLST_Source__const27=PTGNull();
/*SPC(183)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1LST_ConElementrule_34(_TPPLST_ConElementrule_34 _currn)
#else
void _VS1LST_ConElementrule_34(_currn )
_TPPLST_ConElementrule_34 _currn;

#endif
{
DefTableKey _AS1SiblingKey;
int _AS1ntcount;
int _AS1argcount;
PTGNode _AS1SymOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1argcount)),(&( _AS1ntcount)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_ConAlt__const28=ADD(IDENTICAL(_AS1argcount), _AVLST_ConAlt__const28);
/*SPC(186)*/
_AVLST_ConAlt__const29=ADD(IDENTICAL(_AS1ntcount), _AVLST_ConAlt__const29);
/*SPC(186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2LST_ConElementrule_34(_TPPLST_ConElementrule_34 _currn)
#else
void _VS2LST_ConElementrule_34(_currn )
_TPPLST_ConElementrule_34 _currn;

#endif
{
DefTableKey _AS1SiblingKey;
int _AS1ntcount;
int _AS1argcount;
PTGNode _AS1SymOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1argcount)),(&( _AS1ntcount)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3LST_ConElementrule_34(_TPPLST_ConElementrule_34 _currn)
#else
void _VS3LST_ConElementrule_34(_currn )
_TPPLST_ConElementrule_34 _currn;

#endif
{
DefTableKey _AS1SiblingKey;
int _AS1ntcount;
int _AS1argcount;
PTGNode _AS1SymOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1argcount)),(&( _AS1ntcount)));
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4LST_ConElementrule_34(_TPPLST_ConElementrule_34 _currn)
#else
void _VS4LST_ConElementrule_34(_currn )
_TPPLST_ConElementrule_34 _currn;

#endif
{
DefTableKey _AS1SiblingKey;
int _AS1ntcount;
int _AS1argcount;
PTGNode _AS1SymOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*,DefTableKey*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1argcount)),(&( _AS1ntcount)),(&( _AS1SiblingKey)));
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_ConAlt__const6=CombineSiblings(IDENTICAL(_AS1SiblingKey), _AVLST_ConAlt__const6);
/*SPC(186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5LST_ConElementrule_34(_TPPLST_ConElementrule_34 _currn)
#else
void _VS5LST_ConElementrule_34(_currn )
_TPPLST_ConElementrule_34 _currn;

#endif
{
DefTableKey _AS1SiblingKey;
int _AS1ntcount;
int _AS1argcount;
PTGNode _AS1SymOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*,int*,int*,DefTableKey*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1SymOut)),(&( _AS1argcount)),(&( _AS1ntcount)),(&( _AS1SiblingKey)));
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_ConAlt__const11=PTGSeq(IDENTICAL(_AS1SymOut), _AVLST_ConAlt__const11);
/*SPC(186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1LST_0rule_34(_TPPLST_0rule_34 _currn)
#else
void _VS1LST_0rule_34(_currn )
_TPPLST_0rule_34 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_ConAlt__const28=ZERO();
/*SPC(186)*/
_AVLST_ConAlt__const29=ZERO();
/*SPC(186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4LST_0rule_34(_TPPLST_0rule_34 _currn)
#else
void _VS4LST_0rule_34(_currn )
_TPPLST_0rule_34 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_ConAlt__const6=ZeroKey();
/*SPC(186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5LST_0rule_34(_TPPLST_0rule_34 _currn)
#else
void _VS5LST_0rule_34(_currn )
_TPPLST_0rule_34 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_ConAlt__const11=PTGNull();
/*SPC(186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1LST_AbsElementrule_33(_TPPLST_AbsElementrule_33 _currn)
#else
void _VS1LST_AbsElementrule_33(_currn )
_TPPLST_AbsElementrule_33 _currn;

#endif
{
DefTableKey _AS1SiblingKey;
int _AS1argcount;
int _AS1ntcount;
PTGNode _AS1SymOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*,DefTableKey*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1ntcount)),(&( _AS1argcount)),(&( _AS1SiblingKey)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_AbsElements__const2=ADD(IDENTICAL(_AS1argcount), _AVLST_AbsElements__const2);
/*SPC(187)*/
_AVLST_AbsElements__const3=ADD(IDENTICAL(_AS1ntcount), _AVLST_AbsElements__const3);
/*SPC(187)*/
_AVLST_AbsElements__const5=CombineSiblings(IDENTICAL(_AS1SiblingKey), _AVLST_AbsElements__const5);
/*SPC(187)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2LST_AbsElementrule_33(_TPPLST_AbsElementrule_33 _currn)
#else
void _VS2LST_AbsElementrule_33(_currn )
_TPPLST_AbsElementrule_33 _currn;

#endif
{
DefTableKey _AS1SiblingKey;
int _AS1argcount;
int _AS1ntcount;
PTGNode _AS1SymOut;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,PTGNode*,int*,int*,DefTableKey*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1SymOut)),(&( _AS1ntcount)),(&( _AS1argcount)),(&( _AS1SiblingKey)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_AbsElements__const11=PTGSeq(IDENTICAL(_AS1SymOut), _AVLST_AbsElements__const11);
/*SPC(187)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1LST_0rule_33(_TPPLST_0rule_33 _currn)
#else
void _VS1LST_0rule_33(_currn )
_TPPLST_0rule_33 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_AbsElements__const2=ZERO();
/*SPC(187)*/
_AVLST_AbsElements__const3=ZERO();
/*SPC(187)*/
_AVLST_AbsElements__const5=ZeroKey();
/*SPC(187)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2LST_0rule_33(_TPPLST_0rule_33 _currn)
#else
void _VS2LST_0rule_33(_currn )
_TPPLST_0rule_33 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_AbsElements__const11=PTGNull();
/*SPC(187)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2LST_MapTextrule_29(_TPPLST_MapTextrule_29 _currn)
#else
void _VS2LST_MapTextrule_29(_currn )
_TPPLST_MapTextrule_29 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_MapReorderAlt__const0=_AVLST_MapReorderAlt__const0;
/*SPC(191)*/
_AVLST_MapReorderAlt__const1=ADD(ARGTOONE(_currn->_desc1->_ATSym), _AVLST_MapReorderAlt__const1);
/*SPC(191)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2LST_MapPositionrule_29(_TPPLST_MapPositionrule_29 _currn)
#else
void _VS2LST_MapPositionrule_29(_currn )
_TPPLST_MapPositionrule_29 _currn;

#endif
{
int _AS1Sym;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Sym)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVLST_MapReorderAlt__const0=ADD(ARGTOONE(_AS1Sym), _AVLST_MapReorderAlt__const0);
/*SPC(191)*/
_AVLST_MapReorderAlt__const1=ADD(ARGTOONE(_AS1Sym), _AVLST_MapReorderAlt__const1);
/*SPC(191)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2LST_0rule_29(_TPPLST_0rule_29 _currn)
#else
void _VS2LST_0rule_29(_currn )
_TPPLST_0rule_29 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_MapReorderAlt__const0=ZERO();
/*SPC(191)*/
_AVLST_MapReorderAlt__const1=ZERO();
/*SPC(191)*/

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
VOIDEN(ASSIGN(MapQChains, 1));
/*SPC(803)*/

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
_AVMapText_Bind=BindIdn((* _IG_incl0), _currn->_ATSym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVMapText_Bind);
/*SPC(1120)*/

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
_AVMapText_SymbolPTakeIt=1;
/*SPC(1185)*/
_AVMapText_Symbol=CreateSymbol();
/*SPC(751)*/
_AVMapText_SymbolPElem=
(SymbolKeySet(_AVMapText_Symbol, _currn->_ATKey), SymbolClassSet(_AVMapText_Symbol, TEXT), _AVMapText_Symbol)
;
/*SPC(752)*/
_AVMapText_cSymbolPListPtr_post=
((_AVMapText_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVMapText_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_3(_TPPrule_3 _currn,int* _AS0Sym)
#else
void _VS1rule_3(_currn ,_AS0Sym)
_TPPrule_3 _currn;
int* _AS0Sym;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_MapReorderAltpos_post=
((ElemInintList(_currn->_ATTERM_1, _AVLST_MapReorderAltpos_post, intCmp)
) ? (
(message(FATAL, "Duplicates not allowed", 0, (&( _currn->_AT_pos))), _AVLST_MapReorderAltpos_post)

) : (AppElintList(_AVLST_MapReorderAltpos_post, _currn->_ATTERM_1)))
;
/*SPC(791)*/
(* _AS0Sym)=_currn->_ATTERM_1;
/*SPC(780)*/
_AVMapPosition_SymbolPElem=GetNthNT(GetRHS((* _IG_incl1), NULLSymbolPList), (* _AS0Sym));
/*SPC(765)*/
_AVMapText_cSymbolPListPtr_post=
((SymbolPValid(_AVMapPosition_SymbolPElem)
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVMapPosition_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(758)*/

if (AND(GT(_currn->_ATTERM_1, (* _IG_incl3)), NE((* _IG_incl1), NoKey))) {
message(FATAL, "Ordering number is larger than number of nonterminals", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(787)*/

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
_AVMapReorder__SymbolPauxList=NULLSymbolPList;
/*SPC(1179)*/
_AVMapText_cSymbolPListPtr_post=_SymbolPListADDROF(_AVMapReorder__SymbolPauxList);
/*SPC(1180)*/
_AVLST_MapReorderAltpos_post=NULLintList;
/*SPC(776)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVMapReorder__const0=_AVMapReorderAlt__const0;
/*SPC(773)*/
_AVMapReorder__const1=_AVMapReorderAlt__const1;
/*SPC(773)*/
_AVMapReorder_olist=_AVLST_MapReorderAltpos_post;
/*SPC(775)*/
_AVMapReorder_SymbolPList=_AVMapReorder__SymbolPauxList;
/*SPC(1181)*/

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
_AVMapElement_SymbolPTakeIt=1;
/*SPC(1185)*/
_AVMapElement_Sym=_currn->_ATTERM_1;
/*SPC(743)*/
_AVMapElement_Class=TEXT;
/*SPC(744)*/
_AVMapElement_Symbol=CreateSymbol();
/*SPC(707)*/
_AVMapElement_Bind=BindingInEnv((* _IG_incl0), _AVMapElement_Sym);
/*SPC(1130)*/
_AVMapElement_Key=KeyOf(_AVMapElement_Bind);
/*SPC(1134)*/
_AVMapElement_SymbolPElem=
(SymbolKeySet(_AVMapElement_Symbol, _AVMapElement_Key), SymbolClassSet(_AVMapElement_Symbol, _AVMapElement_Class), _AVMapElement_Symbol)
;
/*SPC(708)*/
_AVMapText_cSymbolPListPtr_post=
((_AVMapElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVMapElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

if (EQ(_AVMapElement_Key, NoKey)) {
message(FATAL, "Symbol is not present in grammar", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(731)*/

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
_AVMapElement_SymbolPTakeIt=1;
/*SPC(1185)*/
_AVMapElement_Sym=_currn->_ATTERM_1;
/*SPC(738)*/
_AVMapElement_Class=IDENTIFIER;
/*SPC(739)*/
_AVMapElement_Symbol=CreateSymbol();
/*SPC(707)*/
_AVMapElement_Bind=BindingInEnv((* _IG_incl0), _AVMapElement_Sym);
/*SPC(1130)*/
_AVMapElement_Key=KeyOf(_AVMapElement_Bind);
/*SPC(1134)*/
_AVMapElement_SymbolPElem=
(SymbolKeySet(_AVMapElement_Symbol, _AVMapElement_Key), SymbolClassSet(_AVMapElement_Symbol, _AVMapElement_Class), _AVMapElement_Symbol)
;
/*SPC(708)*/
_AVMapText_cSymbolPListPtr_post=
((_AVMapElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVMapElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

if (EQ(_AVMapElement_Key, NoKey)) {
message(FATAL, "Symbol is not present in grammar", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(731)*/

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
_AVMapLHS_Sym=_currn->_ATTERM_1;
/*SPC(724)*/
_AVMapLHS_Bind=BindingInEnv((* _IG_incl0), _AVMapLHS_Sym);
/*SPC(1130)*/
_AVMapLHS_Key=KeyOf(_AVMapLHS_Bind);
/*SPC(1134)*/

if (EQ(_AVMapLHS_Key, NoKey)) {
message(FATAL, "Symbol is not present in grammar", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(731)*/

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
_AVMapProd__SymbolPauxList=NULLSymbolPList;
/*SPC(1179)*/
_AVMapText_cSymbolPListPtr_post=_SymbolPListADDROF(_AVMapProd__SymbolPauxList);
/*SPC(1180)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_AVMapProd_SymbolPList=_AVMapProd__SymbolPauxList;
/*SPC(1181)*/
_AVMapProd_Key=FindConRule(_AVMapLHS_Key, _AVMapProd_SymbolPList);
/*SPC(715)*/

if (EQ(_AVMapProd_Key, NoKey)) {
message(FATAL, "Concrete rule is not present in grammar", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(720)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
DefTableKey* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATntcount);
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATKey=_AVMapProd_Key;
/*SPC(700)*/
_currn->_ATntcount=GetNTCount(_AVMapProd_Key, 0);
/*SPC(698)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);

if (NE(_AVMapProd_Key, NoKey)) {
ResetMappedRHS(_AVMapProd_Key, _AVMapReorder_SymbolPList);
ResetOrder(_AVMapProd_Key, _AVMapReorder_olist);
ResetNTCount(_AVMapProd_Key, _AVMapReorder__const0);
ResetArgCount(_AVMapProd_Key, _AVMapReorder__const1);
ConMatch(_AVMapProd_Key, CreateSignature(_AVMapReorder_SymbolPList), _AVMapAbs_Key, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(659)*/

if (AND(EQ(GetMatch(_AVMapProd_Key, NoKey), NoKey), NE(_AVMapProd_Key, NoKey))) {
message(FATAL, "Couldn't determine a mapping.", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(688)*/
_IG_incl3=_IL_incl3;
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_9(_TPPrule_9 _currn)
#else
void _VS3rule_9(_currn )
_TPPrule_9 _currn;

#endif
{
int* _IL_incl3;
DefTableKey* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATntcount);
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATKey);

if ((* _IG_incl7)) {
message(FATAL, "Rule mappings are not allowed in the presence of bottomup constraints", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(696)*/
_IG_incl3=_IL_incl3;
_IG_incl1=_IL_incl1;

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
_AVMapAbs_Key=_AVRuleIdUse_Key;
/*SPC(650)*/

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
_AVMapAbs_Key=NoKey;
/*SPC(646)*/

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
DefTableKey* _IL_incl10;

_VisitVarDecl()
_VisitEntry();
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATKey);
_currn->_ATKey=KResetStr(_currn->_desc1->_ATKey, _currn->_desc1->_ATSym);
/*SPC(620)*/
_AVMapMemberssymset_post=GetAbsMap(_currn->_ATKey, NULLDefTableKeyList);
/*SPC(578)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVMapSymbol_KeyList=_AVMapMemberssymset_post;
/*SPC(577)*/
ResetAbsMap(_currn->_ATKey, _AVMapSymbol_KeyList);
/*SPC(640)*/
_IG_incl10=_IL_incl10;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_12(_TPPrule_12 _currn)
#else
void _VS3rule_12(_currn )
_TPPrule_12 _currn;

#endif
{
DefTableKey* _IL_incl10;

_VisitVarDecl()
_VisitEntry();
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATKey);

if (GetIsCon(_currn->_ATKey, 0)) {
IsEqClass(_currn->_ATKey, GetNonTerm(_currn->_ATKey, 0), T_ERROR);

} else {
}
;

if (EQ(GetEqClass(_currn->_ATKey, 0), T_ERROR)) {
message(FATAL, "Equivalence classes cannot have both terminals and nonterminals", 0, (&( _currn->_AT_pos)));

} else {

if (AND(AND(GetIsAbs(_currn->_ATKey, 0), GetNonTerm(_currn->_ATKey, 0)), EQ(GetEqClass(_currn->_ATKey, 0), T_TERM))) {
message(FATAL, "Abstract nonterminal equivalenced to concrete terminals", 0, (&( _currn->_AT_pos)));

} else {
}
;
}
;
;
/*SPC(637)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl10=_IL_incl10;

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
_AVMapMember_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVMapMember_Bind=BindingInEnv((* _IG_incl0), _AVMapMember_Sym);
/*SPC(1130)*/
_currn->_ATKey=KeyOf(_AVMapMember_Bind);
/*SPC(1134)*/
_AVMapMemberssymset_post=
((NE(_currn->_ATKey, (* _IG_incl10))
) ? (AddToSetDefTableKeyList(_currn->_ATKey, _AVMapMemberssymset_post, DefTableKeyCmp)
) : (_AVMapMemberssymset_post))
;
/*SPC(584)*/
_AVMapMember_Key_RuleAttr_103=GetMap(_currn->_ATKey, NoKey);
/*SPC(609)*/

if (EQ(_currn->_ATKey, NoKey)) {
;

} else {
IsEqClass((* _IG_incl10), GetNonTerm(_currn->_ATKey, 0), T_ERROR);
}
;
/*SPC(603)*/

if (AND(NE(_AVMapMember_Key_RuleAttr_103, NoKey), NE(_AVMapMember_Key_RuleAttr_103, (* _IG_incl10)))) {
message(ERROR, "Symbol cannot be member of more than one equivalence class", 0, (&( _currn->_AT_pos)));

} else {
ResetMap(_currn->_ATKey, (* _IG_incl10));
}
;
/*SPC(610)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_13(_TPPrule_13 _currn)
#else
void _VS2rule_13(_currn )
_TPPrule_13 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (EQ(_currn->_ATKey, NoKey)) {
message(FATAL, "No such symbol", 0, (&( _currn->_AT_pos)));

} else {

if (GetIsAbs(_currn->_ATKey, 0)) {
message(FATAL, "Abstract syntax symbols may not appear on the rhs of an equivalence class", 0, (&( _currn->_AT_pos)));

} else {
VOIDEN(0);
}
;
}
;
/*SPC(598)*/

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
_AVBottomUpRule_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVBottomUpRule_Key=KeyInEnv((* _IG_incl0), _currn->_ATTERM_1);
/*SPC(525)*/
ResetBottomUp(_AVBottomUpRule_Key, 1);
/*SPC(531)*/
_AVBottomUpRule_Bind=BindingInEnv((* _IG_incl0), _AVBottomUpRule_Sym);
/*SPC(1130)*/
_currn->_ATGotBottomUp=1;
/*SPC(530)*/

if (EQ(_AVBottomUpRule_Key, NoKey)) {
message(FATAL, "Rule name must appear in the abstract syntax.", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(529)*/

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
_currn->_AT_const4=_currn->_desc1->_ATKey;
/*SPC(495)*/

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
_AVAbsSignature__SymbolPauxList=NULLSymbolPList;
/*SPC(1179)*/
_AVMapText_cSymbolPListPtr_post=_SymbolPListADDROF(_AVAbsSignature__SymbolPauxList);
/*SPC(1180)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVAbsSignature_SymbolPList=_AVAbsSignature__SymbolPauxList;
/*SPC(1181)*/
_currn->_ATargcount=0;
/*SPC(503)*/
ResetType((* _IG_incl11), T_LISTOF);
ResetRHS((* _IG_incl11), _AVAbsSignature_SymbolPList);
;
/*SPC(496)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATargsig=NullArgSig;
/*SPC(502)*/

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
ListofMatch((* _IG_incl11), (&( _currn->_AT_pos)));
/*SPC(829)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_15(_TPPrule_15 _currn)
#else
void _VS4rule_15(_currn )
_TPPrule_15 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVAbsSignature__const11=PTGNull();
/*SPC(495)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_16(_TPPrule_16 _currn,int* _AS0ntcount,int* _AS0argcount,DefTableKey* _AS0SiblingKey)
#else
void _VS1rule_16(_currn ,_AS0ntcount,_AS0argcount,_AS0SiblingKey)
_TPPrule_16 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0argcount;
int* _AS0ntcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAbsElement_SymbolPTakeIt=1;
/*SPC(1185)*/
(* _AS0argcount)=0;
/*SPC(492)*/
_AVAbsElement_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVAbsElement_Class=GEN_IDENT;
/*SPC(487)*/
_AVAbsElement_Symbol=CreateSymbol();
/*SPC(445)*/
(* _AS0ntcount)=0;
/*SPC(488)*/
_AVAbsElement_Bind=BindIdn((* _IG_incl0), _AVAbsElement_Sym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVAbsElement_Bind);
/*SPC(1120)*/
(* _AS0SiblingKey)=NoKey;
/*SPC(1039)*/
ResetIsAbs(_currn->_ATKey, 1);
/*SPC(995)*/
ResetIsRHS(_currn->_ATKey, 1);
/*SPC(991)*/
_AVAbsElement_SymbolPElem=
(SymbolKeySet(_AVAbsElement_Symbol, _currn->_ATKey), SymbolClassSet(_AVAbsElement_Symbol, _AVAbsElement_Class), ResetStr(_currn->_ATKey, _AVAbsElement_Sym), _AVAbsElement_Symbol)
;
/*SPC(446)*/
_AVMapText_cSymbolPListPtr_post=
((_AVAbsElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVAbsElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_16(_TPPrule_16 _currn,PTGNode* _AS0SymOut,int* _AS0ntcount,int* _AS0argcount,DefTableKey* _AS0SiblingKey)
#else
void _VS2rule_16(_currn ,_AS0SymOut,_AS0ntcount,_AS0argcount,_AS0SiblingKey)
_TPPrule_16 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0argcount;
int* _AS0ntcount;
PTGNode* _AS0SymOut;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAbsElement_IsFirstOcc=SetGetFirstOcc(_currn->_ATKey, 1, 0);
/*SPC(1389)*/
(* _AS0SymOut)=PTGNULL;
/*SPC(162)*/

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
_currn->_AT_const4=_currn->_desc1->_ATKey;
/*SPC(452)*/

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
_AVAbsSignature__SymbolPauxList=NULLSymbolPList;
/*SPC(1179)*/
_AVMapText_cSymbolPListPtr_post=_SymbolPListADDROF(_AVAbsSignature__SymbolPauxList);
/*SPC(1180)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVLST_AbsElementssig_post=OilNewArgSig();
/*SPC(459)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVAbsSignature_SymbolPList=_AVAbsSignature__SymbolPauxList;
/*SPC(1181)*/
_currn->_ATargcount=_AVAbsElements__const2;
/*SPC(455)*/
ResetType((* _IG_incl11), T_NONLISTOF);
ResetRHS((* _IG_incl11), _AVAbsSignature_SymbolPList);
ResetArgCount((* _IG_incl11), _currn->_ATargcount);
ResetNTCount((* _IG_incl11), _AVAbsElements__const3);
;
/*SPC(435)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATargsig=SigAppend(
((EQ(_currn->_ATargcount, 0)
) ? (SigAppend(_AVLST_AbsElementssig_post, OilTypeName(EmptyType))
) : (_AVLST_AbsElementssig_post))
, _currn->_desc1->_ATKey);
/*SPC(460)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_17(_TPPrule_17 _currn)
#else
void _VS4rule_17(_currn )
_TPPrule_17 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVAbsSignature__const11=_AVAbsElements__const11;
/*SPC(452)*/

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
_AVAbsLHS_Bind=BindIdn((* _IG_incl0), _currn->_ATSym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVAbsLHS_Bind);
/*SPC(1120)*/

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
ResetIsAbs(_currn->_ATKey, 1);
/*SPC(979)*/
ResetNonTerm(_currn->_ATKey, 1);
/*SPC(967)*/
ResetStr(_currn->_ATKey, _currn->_ATTERM_1);
ResetAbsRules(_currn->_ATKey, AppElDefTableKeyList(GetAbsRules(_currn->_ATKey, NULLDefTableKeyList), (* _IG_incl11)));
;
/*SPC(418)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_18(_TPPrule_18 _currn)
#else
void _VS4rule_18(_currn )
_TPPrule_18 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (AND(AND(GetStart(_currn->_ATKey, 0), NE((* _IG_incl14), 1)), NOT(GetRootErr(_currn->_ATKey, 0)))) {
ResetRootErr(_currn->_ATKey, 1);
message(ERROR, CatStrInd("One of the multiple roots: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(975)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_19(_TPPrule_19 _currn)
#else
void _VS1rule_19(_currn )
_TPPrule_19 _currn;

#endif
{
DefTableKey* _IL_incl11;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATKey=KResetLHS(KResetStr(_AVAbsRuleId_Key, _AVAbsRuleId_Sym), _currn->_desc2->_AT_const4);
/*SPC(394)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl11=_IL_incl11;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_19(_TPPrule_19 _currn)
#else
void _VS2rule_19(_currn )
_TPPrule_19 _currn;

#endif
{
DefTableKey* _IL_incl11;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATKey);

if (NE(_currn->_desc2->_ATargsig, NullArgSig)) {
CreateOper(_currn->_desc2->_ATargcount, _currn->_ATKey, _currn->_desc2->_ATargsig);

} else {
}
;
/*SPC(403)*/
_IG_incl11=_IL_incl11;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_19(_TPPrule_19 _currn)
#else
void _VS3rule_19(_currn )
_TPPrule_19 _currn;

#endif
{
DefTableKey* _IL_incl11;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATaxiom=CheckAxiom(_currn->_desc2->_AT_const4, 1);
/*SPC(945)*/

if (_currn->_ATaxiom) {
ComputeReach(_currn->_desc2->_AT_const4);

} else {
;
}
;
/*SPC(950)*/
_IG_incl11=_IL_incl11;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_19(_TPPrule_19 _currn)
#else
void _VS4rule_19(_currn )
_TPPrule_19 _currn;

#endif
{
DefTableKey* _IL_incl11;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATKey);
MarkConSym(_currn->_ATKey);
/*SPC(959)*/
_IG_incl11=_IL_incl11;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_19(_TPPrule_19 _currn,PTGNode* _AS0Pgram)
#else
void _VS5rule_19(_currn ,_AS0Pgram)
_TPPrule_19 _currn;
PTGNode* _AS0Pgram;

#endif
{
DefTableKey* _IL_incl11;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATKey);
(* _AS0Pgram)=GenConProd(_currn->_ATKey, 1, 1);
/*SPC(126)*/
_IG_incl11=_IL_incl11;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_19(_TPPrule_19 _currn,PTGNode* _AS0ConOut,PTGNode* _AS0AbsSOut,PTGNode* _AS0AbsTOut,PTGNode* _AS0StartOut,PTGNode* _AS0Pgram,PTGNode* _AS0_const11)
#else
void _VS6rule_19(_currn ,_AS0ConOut,_AS0AbsSOut,_AS0AbsTOut,_AS0StartOut,_AS0Pgram,_AS0_const11)
_TPPrule_19 _currn;
PTGNode* _AS0_const11;
PTGNode* _AS0Pgram;
PTGNode* _AS0StartOut;
PTGNode* _AS0AbsTOut;
PTGNode* _AS0AbsSOut;
PTGNode* _AS0ConOut;

#endif
{
DefTableKey* _IL_incl11;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(* _AS0_const11)=_AVAbsSignature__const11;
/*SPC(392)*/
(* _AS0StartOut)=
((AND(EQ(GetAbsMap(_currn->_desc2->_AT_const4, NULLDefTableKeyList), NULLDefTableKeyList), _currn->_ATaxiom)
) ? (PTGStart(PTGAsIs(StrStr(_currn->_desc2->_AT_const4)))
) : (PTGNULL))
;
/*SPC(99)*/
(* _AS0AbsTOut)=GenAbsProd(_currn->_ATKey, 0);
/*SPC(67)*/
(* _AS0AbsSOut)=
((GetReach(_currn->_ATKey, 0)
) ? ((* _AS0AbsTOut)
) : (PTGNULL))
;
/*SPC(51)*/
(* _AS0ConOut)=GenConProd(_currn->_ATKey, 1, 0);
/*SPC(28)*/
_IG_incl11=_IL_incl11;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_20(_TPPrule_20 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS1rule_20(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_20 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_SymbolPTakeIt=1;
/*SPC(1185)*/
_AVConElement_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVConElement_Class=DOLLARMODTXT;
/*SPC(387)*/
_AVConElement_Symbol=CreateSymbol();
/*SPC(312)*/
(* _AS0ntcount)=0;
/*SPC(385)*/
(* _AS0argcount)=0;
/*SPC(386)*/
_AVConElement_Bind=BindIdn((* _IG_incl0), _AVConElement_Sym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVConElement_Bind);
/*SPC(1120)*/
_AVConElement_SymbolPElem=
(SymbolKeySet(_AVConElement_Symbol, _currn->_ATKey), SymbolClassSet(_AVConElement_Symbol, _AVConElement_Class), ResetStr(_currn->_ATKey, _AVConElement_Sym), _AVConElement_Symbol)
;
/*SPC(313)*/
_AVMapText_cSymbolPListPtr_post=
((_AVConElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVConElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_20(_TPPrule_20 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS2rule_20(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_20 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
ResetIsRHS(_currn->_ATKey, 1);
/*SPC(991)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_20(_TPPrule_20 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS3rule_20(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_20 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_20(_TPPrule_20 _currn,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS4rule_20(_currn ,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_20 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0SiblingKey)=NoKey;
/*SPC(1069)*/
ResetIsCon(_currn->_ATKey, 1);
/*SPC(1006)*/
ResetConSym(_currn->_ATKey, 1);
/*SPC(1004)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_20(_TPPrule_20 _currn,PTGNode* _AS0SymOut,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS5rule_20(_currn ,_AS0SymOut,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_20 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;
PTGNode* _AS0SymOut;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_IsFirstOcc=SetGetFirstOcc(_currn->_ATKey, 1, 0);
/*SPC(1389)*/
(* _AS0SymOut)=
((AND(_AVConElement_IsFirstOcc, NOT(GetNonTerm(_currn->_ATKey, 0)))
) ? (PTGEol(PTGId(GetStr(_currn->_ATKey, 0)))
) : (PTGNULL))
;
/*SPC(151)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_21(_TPPrule_21 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS1rule_21(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_21 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_SymbolPTakeIt=1;
/*SPC(1185)*/
_AVConElement_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVConElement_Class=DOLLARMODIDN;
/*SPC(379)*/
_AVConElement_Symbol=CreateSymbol();
/*SPC(312)*/
(* _AS0ntcount)=0;
/*SPC(377)*/
(* _AS0argcount)=0;
/*SPC(378)*/
_AVConElement_Bind=BindIdn((* _IG_incl0), _AVConElement_Sym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVConElement_Bind);
/*SPC(1120)*/
_AVConElement_SymbolPElem=
(SymbolKeySet(_AVConElement_Symbol, _currn->_ATKey), SymbolClassSet(_AVConElement_Symbol, _AVConElement_Class), ResetStr(_currn->_ATKey, _AVConElement_Sym), _AVConElement_Symbol)
;
/*SPC(313)*/
_AVMapText_cSymbolPListPtr_post=
((_AVConElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVConElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_21(_TPPrule_21 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS2rule_21(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_21 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
ResetIsRHS(_currn->_ATKey, 1);
/*SPC(991)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_21(_TPPrule_21 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS3rule_21(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_21 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_21(_TPPrule_21 _currn,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS4rule_21(_currn ,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_21 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0SiblingKey)=NoKey;
/*SPC(1065)*/
ResetIsCon(_currn->_ATKey, 1);
/*SPC(1006)*/
ResetConSym(_currn->_ATKey, 1);
/*SPC(1004)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_21(_TPPrule_21 _currn,PTGNode* _AS0SymOut,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS5rule_21(_currn ,_AS0SymOut,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_21 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;
PTGNode* _AS0SymOut;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_IsFirstOcc=SetGetFirstOcc(_currn->_ATKey, 1, 0);
/*SPC(1389)*/
(* _AS0SymOut)=
((AND(_AVConElement_IsFirstOcc, NOT(GetNonTerm(_currn->_ATKey, 0)))
) ? (PTGEol(PTGId(GetStr(_currn->_ATKey, 0)))
) : (PTGNULL))
;
/*SPC(151)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_22(_TPPrule_22 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS1rule_22(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_22 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_SymbolPTakeIt=1;
/*SPC(1185)*/
_AVConElement_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVConElement_Class=ATMODTXT;
/*SPC(371)*/
_AVConElement_Symbol=CreateSymbol();
/*SPC(312)*/
(* _AS0ntcount)=0;
/*SPC(369)*/
(* _AS0argcount)=0;
/*SPC(370)*/
_AVConElement_Bind=BindIdn((* _IG_incl0), _AVConElement_Sym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVConElement_Bind);
/*SPC(1120)*/
_AVConElement_SymbolPElem=
(SymbolKeySet(_AVConElement_Symbol, _currn->_ATKey), SymbolClassSet(_AVConElement_Symbol, _AVConElement_Class), ResetStr(_currn->_ATKey, _AVConElement_Sym), _AVConElement_Symbol)
;
/*SPC(313)*/
_AVMapText_cSymbolPListPtr_post=
((_AVConElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVConElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_22(_TPPrule_22 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS2rule_22(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_22 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
ResetIsRHS(_currn->_ATKey, 1);
/*SPC(991)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_22(_TPPrule_22 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS3rule_22(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_22 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_22(_TPPrule_22 _currn,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS4rule_22(_currn ,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_22 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0SiblingKey)=NoKey;
/*SPC(1061)*/
ResetIsCon(_currn->_ATKey, 1);
/*SPC(1006)*/
ResetConSym(_currn->_ATKey, 1);
/*SPC(1004)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_22(_TPPrule_22 _currn,PTGNode* _AS0SymOut,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS5rule_22(_currn ,_AS0SymOut,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_22 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;
PTGNode* _AS0SymOut;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_IsFirstOcc=SetGetFirstOcc(_currn->_ATKey, 1, 0);
/*SPC(1389)*/
(* _AS0SymOut)=
((AND(_AVConElement_IsFirstOcc, NOT(GetNonTerm(_currn->_ATKey, 0)))
) ? (PTGEol(PTGId(GetStr(_currn->_ATKey, 0)))
) : (PTGNULL))
;
/*SPC(151)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_23(_TPPrule_23 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS1rule_23(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_23 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_SymbolPTakeIt=1;
/*SPC(1185)*/
_AVConElement_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVConElement_Class=ATMODIDN;
/*SPC(363)*/
_AVConElement_Symbol=CreateSymbol();
/*SPC(312)*/
(* _AS0ntcount)=0;
/*SPC(361)*/
(* _AS0argcount)=0;
/*SPC(362)*/
_AVConElement_Bind=BindIdn((* _IG_incl0), _AVConElement_Sym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVConElement_Bind);
/*SPC(1120)*/
_AVConElement_SymbolPElem=
(SymbolKeySet(_AVConElement_Symbol, _currn->_ATKey), SymbolClassSet(_AVConElement_Symbol, _AVConElement_Class), ResetStr(_currn->_ATKey, _AVConElement_Sym), _AVConElement_Symbol)
;
/*SPC(313)*/
_AVMapText_cSymbolPListPtr_post=
((_AVConElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVConElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_23(_TPPrule_23 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS2rule_23(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_23 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
ResetIsRHS(_currn->_ATKey, 1);
/*SPC(991)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_23(_TPPrule_23 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS3rule_23(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_23 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_23(_TPPrule_23 _currn,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS4rule_23(_currn ,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_23 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0SiblingKey)=NoKey;
/*SPC(1057)*/
ResetIsCon(_currn->_ATKey, 1);
/*SPC(1006)*/
ResetConSym(_currn->_ATKey, 1);
/*SPC(1004)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_23(_TPPrule_23 _currn,PTGNode* _AS0SymOut,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS5rule_23(_currn ,_AS0SymOut,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_23 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;
PTGNode* _AS0SymOut;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_IsFirstOcc=SetGetFirstOcc(_currn->_ATKey, 1, 0);
/*SPC(1389)*/
(* _AS0SymOut)=
((AND(_AVConElement_IsFirstOcc, NOT(GetNonTerm(_currn->_ATKey, 0)))
) ? (PTGEol(PTGId(GetStr(_currn->_ATKey, 0)))
) : (PTGNULL))
;
/*SPC(151)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_24(_TPPrule_24 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS1rule_24(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_24 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_SymbolPTakeIt=1;
/*SPC(1185)*/
_AVConElement_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVConElement_Class=TEXT;
/*SPC(344)*/
_AVConElement_Symbol=CreateSymbol();
/*SPC(312)*/
(* _AS0ntcount)=0;
/*SPC(345)*/
(* _AS0argcount)=1;
/*SPC(346)*/
_AVConElement_Bind=BindIdn((* _IG_incl0), _AVConElement_Sym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVConElement_Bind);
/*SPC(1120)*/
_AVConElement_SymbolPElem=
(SymbolKeySet(_AVConElement_Symbol, _currn->_ATKey), SymbolClassSet(_AVConElement_Symbol, _AVConElement_Class), ResetStr(_currn->_ATKey, _AVConElement_Sym), _AVConElement_Symbol)
;
/*SPC(313)*/
_AVMapText_cSymbolPListPtr_post=
((_AVConElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVConElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_24(_TPPrule_24 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS2rule_24(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_24 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
ResetIsRHS(_currn->_ATKey, 1);
/*SPC(991)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_24(_TPPrule_24 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS3rule_24(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_24 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_ConAltsetsig_post=OilAddSetSig(CreateTS(_currn->_ATKey), _AVLST_ConAltsetsig_post);
/*SPC(878)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_24(_TPPrule_24 _currn,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS4rule_24(_currn ,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_24 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0SiblingKey)=
((EQ(GetDuplicate((* _IG_incl21), NoKey), NoKey)
) ? (NoKey
) : (_currn->_ATKey))
;
/*SPC(1045)*/
ResetIsCon(_currn->_ATKey, 1);
/*SPC(1006)*/
ResetConSym(_currn->_ATKey, 1);
/*SPC(1004)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_24(_TPPrule_24 _currn,PTGNode* _AS0SymOut,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS5rule_24(_currn ,_AS0SymOut,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_24 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;
PTGNode* _AS0SymOut;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_IsFirstOcc=SetGetFirstOcc(_currn->_ATKey, 1, 0);
/*SPC(1389)*/
(* _AS0SymOut)=
((AND(_AVConElement_IsFirstOcc, NOT(GetNonTerm(_currn->_ATKey, 0)))
) ? (PTGEol(PTGId(GetStr(_currn->_ATKey, 0)))
) : (PTGNULL))
;
/*SPC(151)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_25(_TPPrule_25 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS1rule_25(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_25 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_SymbolPTakeIt=1;
/*SPC(1185)*/
_AVConElement_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVConElement_Class=IDENTIFIER;
/*SPC(330)*/
_AVConElement_Symbol=CreateSymbol();
/*SPC(312)*/
(* _AS0ntcount)=1;
/*SPC(331)*/
(* _AS0argcount)=1;
/*SPC(332)*/
_AVConElement_Bind=BindIdn((* _IG_incl0), _AVConElement_Sym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVConElement_Bind);
/*SPC(1120)*/
_AVConElement_SymbolPElem=
(SymbolKeySet(_AVConElement_Symbol, _currn->_ATKey), SymbolClassSet(_AVConElement_Symbol, _AVConElement_Class), ResetStr(_currn->_ATKey, _AVConElement_Sym), _AVConElement_Symbol)
;
/*SPC(313)*/
_AVMapText_cSymbolPListPtr_post=
((_AVConElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVConElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_25(_TPPrule_25 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS2rule_25(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_25 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
ResetIsRHS(_currn->_ATKey, 1);
/*SPC(991)*/
ResetRHSConRules(_currn->_ATKey, AddToSetDefTableKeyList((* _IG_incl21), GetRHSConRules(_currn->_ATKey, NULLDefTableKeyList), DefTableKeyCmp));
/*SPC(336)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_25(_TPPrule_25 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS3rule_25(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_25 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLST_ConAltsetsig_post=OilAddSetSig(CreateTS(_currn->_ATKey), _AVLST_ConAltsetsig_post);
/*SPC(870)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_25(_TPPrule_25 _currn,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS4rule_25(_currn ,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_25 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0SiblingKey)=
((EQ(GetDuplicate((* _IG_incl21), NoKey), NoKey)
) ? (NoKey
) : (_currn->_ATKey))
;
/*SPC(1045)*/
ResetIsCon(_currn->_ATKey, 1);
/*SPC(1006)*/
ResetConSym(_currn->_ATKey, 1);
/*SPC(1004)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_25(_TPPrule_25 _currn,PTGNode* _AS0SymOut,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS5rule_25(_currn ,_AS0SymOut,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_25 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;
PTGNode* _AS0SymOut;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_IsFirstOcc=SetGetFirstOcc(_currn->_ATKey, 1, 0);
/*SPC(1389)*/
(* _AS0SymOut)=
((AND(_AVConElement_IsFirstOcc, NOT(GetNonTerm(_currn->_ATKey, 0)))
) ? (PTGEol(PTGId(GetStr(_currn->_ATKey, 0)))
) : (PTGNULL))
;
/*SPC(151)*/

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
_AVMaptoId_Bind=BindIdn((* _IG_incl0), _currn->_ATSym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVMaptoId_Bind);
/*SPC(1120)*/

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
_AVAbsRuleId_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVAbsRuleId_Bind=BindIdn((* _IG_incl0), _AVAbsRuleId_Sym);
/*SPC(1118)*/
_AVAbsRuleId_Key=KeyOf(_AVAbsRuleId_Bind);
/*SPC(1120)*/

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
_AVConLHS_Bind=BindIdn((* _IG_incl0), _currn->_ATSym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVConLHS_Bind);
/*SPC(1120)*/

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
ResetIsCon(_currn->_ATKey, 1);
/*SPC(986)*/
ResetConSym(_currn->_ATKey, 1);
/*SPC(984)*/
ResetNonTerm(_currn->_ATKey, 1);
/*SPC(967)*/
ResetStr(_currn->_ATKey, _currn->_ATSym);
ResetConRules(_currn->_ATKey, AppElDefTableKeyList(GetConRules(_currn->_ATKey, NULLDefTableKeyList), (* _IG_incl21)));
;
/*SPC(322)*/

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

if (AND(AND(GetStart(_currn->_ATKey, 0), NE((* _IG_incl14), 1)), NOT(GetRootErr(_currn->_ATKey, 0)))) {
ResetRootErr(_currn->_ATKey, 1);
message(ERROR, CatStrInd("One of the multiple roots: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));
;

} else {
}
;
/*SPC(975)*/

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
_AVMapReorderAlt__const0=_AVLST_MapReorderAlt__const0;
/*SPC(191)*/
_AVMapReorderAlt__const1=_AVLST_MapReorderAlt__const1;
/*SPC(191)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_31(_TPPrule_31 _currn)
#else
void _VS2rule_31(_currn )
_TPPrule_31 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_AVAbsElements__const2=_AVLST_AbsElements__const2;
/*SPC(187)*/
_AVAbsElements__const3=_AVLST_AbsElements__const3;
/*SPC(187)*/
VOIDEN(_AVLST_AbsElements__const5);
/*SPC(1023)*/

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
_AVAbsElements__const11=_AVLST_AbsElements__const11;
/*SPC(187)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVConAlt__const28=_AVLST_ConAlt__const28;
/*SPC(186)*/
_AVConAlt__const29=_AVLST_ConAlt__const29;
/*SPC(186)*/

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
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_34(_TPPrule_34 _currn)
#else
void _VS4rule_34(_currn )
_TPPrule_34 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
VOIDEN(_AVLST_ConAlt__const6);
/*SPC(1029)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_34(_TPPrule_34 _currn)
#else
void _VS5rule_34(_currn )
_TPPrule_34 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVConAlt__const11=_AVLST_ConAlt__const11;
/*SPC(186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_35(_TPPrule_35 _currn)
#else
void _VS1rule_35(_currn )
_TPPrule_35 _currn;

#endif
{
int* _IL_incl14;
int* _IL_incl7;
Environment* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl14=_IG_incl14;_IG_incl14= &(_currn->_ATAxiomCnt);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATGotBottomUp);
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATEnv);
_currn->_ATEnv=Initialize();
/*SPC(264)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATGotBottomUp=_AVLST_Source__const12;
/*SPC(518)*/
_currn->_ATAxiomCnt=_AVLST_Source__const19;
/*SPC(919)*/

if (EQ(_currn->_ATAxiomCnt, 0)) {
message(ERROR, "Could not determine the start symbol", 0, NoPosition);

} else {
}
;
/*SPC(925)*/
(*(_CALL_VS_((NODEPTR )) (VS7MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVSource_Pgram=_AVLST_Source__const15;
/*SPC(87)*/
(*(_CALL_VS_((NODEPTR )) (VS8MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVSource_SymOut=_AVLST_Source__const11;
/*SPC(144)*/
_AVSource_StartOut=_AVLST_Source__const16;
/*SPC(84)*/
_AVSource_AbsTOut=_AVLST_Source__const17;
/*SPC(60)*/
_AVSource_AbsSOut=_AVLST_Source__const18;
/*SPC(44)*/
_AVSource_ConOut=_AVLST_Source__const27;
/*SPC(8)*/
PTGOutFile("consyntax", _AVSource_ConOut);
/*SPC(11)*/
PTGOutFile("absyntax", _AVSource_AbsSOut);
/*SPC(47)*/
PTGOutFile("abstree", _AVSource_AbsTOut);
/*SPC(63)*/
PTGOutFile("pgram", PTGSeq(_AVSource_StartOut, _AVSource_Pgram));
/*SPC(90)*/
PTGOutFile("symbols", _AVSource_SymOut);
/*SPC(147)*/
_IG_incl14=_IL_incl14;
_IG_incl7=_IL_incl7;
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_36(_TPPrule_36 _currn,int* _AS0ntcount,int* _AS0argcount,DefTableKey* _AS0SiblingKey)
#else
void _VS1rule_36(_currn ,_AS0ntcount,_AS0argcount,_AS0SiblingKey)
_TPPrule_36 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0argcount;
int* _AS0ntcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAbsElement_SymbolPTakeIt=1;
/*SPC(1185)*/
(* _AS0argcount)=1;
/*SPC(474)*/
_AVAbsElement_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVAbsElement_Class=IDENTIFIER;
/*SPC(469)*/
_AVAbsElement_Symbol=CreateSymbol();
/*SPC(445)*/
(* _AS0ntcount)=1;
/*SPC(470)*/
_AVAbsElement_Bind=BindIdn((* _IG_incl0), _AVAbsElement_Sym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVAbsElement_Bind);
/*SPC(1120)*/
_AVLST_AbsElementssig_post=SigAppend(_AVLST_AbsElementssig_post, _currn->_ATKey);
/*SPC(473)*/
(* _AS0SiblingKey)=_currn->_ATKey;
/*SPC(1035)*/
ResetIsAbs(_currn->_ATKey, 1);
/*SPC(995)*/
ResetIsRHS(_currn->_ATKey, 1);
/*SPC(991)*/
_AVAbsElement_SymbolPElem=
(SymbolKeySet(_AVAbsElement_Symbol, _currn->_ATKey), SymbolClassSet(_AVAbsElement_Symbol, _AVAbsElement_Class), ResetStr(_currn->_ATKey, _AVAbsElement_Sym), _AVAbsElement_Symbol)
;
/*SPC(446)*/
_AVMapText_cSymbolPListPtr_post=
((_AVAbsElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVAbsElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_36(_TPPrule_36 _currn,PTGNode* _AS0SymOut,int* _AS0ntcount,int* _AS0argcount,DefTableKey* _AS0SiblingKey)
#else
void _VS2rule_36(_currn ,_AS0SymOut,_AS0ntcount,_AS0argcount,_AS0SiblingKey)
_TPPrule_36 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0argcount;
int* _AS0ntcount;
PTGNode* _AS0SymOut;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAbsElement_IsFirstOcc=SetGetFirstOcc(_currn->_ATKey, 1, 0);
/*SPC(1389)*/
(* _AS0SymOut)=
((AND(_AVAbsElement_IsFirstOcc, AND(NOT(GetNonTerm(_currn->_ATKey, 0)), GetConSym(_currn->_ATKey, 0)))
) ? (PTGEol(PTGId(_currn->_ATTERM_1))
) : (PTGNULL))
;
/*SPC(172)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_37(_TPPrule_37 _currn,int* _AS0ntcount,int* _AS0argcount,DefTableKey* _AS0SiblingKey)
#else
void _VS1rule_37(_currn ,_AS0ntcount,_AS0argcount,_AS0SiblingKey)
_TPPrule_37 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0argcount;
int* _AS0ntcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAbsElement_SymbolPTakeIt=1;
/*SPC(1185)*/
(* _AS0argcount)=1;
/*SPC(483)*/
_AVAbsElement_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVAbsElement_Class=TEXT;
/*SPC(478)*/
_AVAbsElement_Symbol=CreateSymbol();
/*SPC(445)*/
(* _AS0ntcount)=0;
/*SPC(479)*/
_AVAbsElement_Bind=BindIdn((* _IG_incl0), _AVAbsElement_Sym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVAbsElement_Bind);
/*SPC(1120)*/
_AVLST_AbsElementssig_post=SigAppend(_AVLST_AbsElementssig_post, _currn->_ATKey);
/*SPC(482)*/
(* _AS0SiblingKey)=_currn->_ATKey;
/*SPC(1035)*/
ResetIsAbs(_currn->_ATKey, 1);
/*SPC(995)*/
ResetIsRHS(_currn->_ATKey, 1);
/*SPC(991)*/
_AVAbsElement_SymbolPElem=
(SymbolKeySet(_AVAbsElement_Symbol, _currn->_ATKey), SymbolClassSet(_AVAbsElement_Symbol, _AVAbsElement_Class), ResetStr(_currn->_ATKey, _AVAbsElement_Sym), _AVAbsElement_Symbol)
;
/*SPC(446)*/
_AVMapText_cSymbolPListPtr_post=
((_AVAbsElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVAbsElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_37(_TPPrule_37 _currn,PTGNode* _AS0SymOut,int* _AS0ntcount,int* _AS0argcount,DefTableKey* _AS0SiblingKey)
#else
void _VS2rule_37(_currn ,_AS0SymOut,_AS0ntcount,_AS0argcount,_AS0SiblingKey)
_TPPrule_37 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0argcount;
int* _AS0ntcount;
PTGNode* _AS0SymOut;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAbsElement_IsFirstOcc=SetGetFirstOcc(_currn->_ATKey, 1, 0);
/*SPC(1389)*/
(* _AS0SymOut)=
((_AVAbsElement_IsFirstOcc
) ? (PTGEol(PTGId(_currn->_ATTERM_1))
) : (PTGNULL))
;
/*SPC(165)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_38(_TPPrule_38 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS1rule_38(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_38 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_SymbolPTakeIt=1;
/*SPC(1185)*/
_AVConElement_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVConElement_Class=ACTION;
/*SPC(355)*/
_AVConElement_Symbol=CreateSymbol();
/*SPC(312)*/
(* _AS0ntcount)=0;
/*SPC(353)*/
(* _AS0argcount)=0;
/*SPC(354)*/
_AVConElement_Bind=BindIdn((* _IG_incl0), _AVConElement_Sym);
/*SPC(1118)*/
_currn->_ATKey=KeyOf(_AVConElement_Bind);
/*SPC(1120)*/
_AVConElement_SymbolPElem=
(SymbolKeySet(_AVConElement_Symbol, _currn->_ATKey), SymbolClassSet(_AVConElement_Symbol, _AVConElement_Class), ResetStr(_currn->_ATKey, _AVConElement_Sym), _AVConElement_Symbol)
;
/*SPC(313)*/
_AVMapText_cSymbolPListPtr_post=
((_AVConElement_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVConElement_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_38(_TPPrule_38 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS2rule_38(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_38 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
ResetIsRHS(_currn->_ATKey, 1);
/*SPC(991)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_38(_TPPrule_38 _currn,int* _AS0argcount,int* _AS0ntcount)
#else
void _VS3rule_38(_currn ,_AS0argcount,_AS0ntcount)
_TPPrule_38 _currn;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_38(_TPPrule_38 _currn,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS4rule_38(_currn ,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_38 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0SiblingKey)=NoKey;
/*SPC(1053)*/
ResetIsCon(_currn->_ATKey, 1);
/*SPC(1006)*/
ResetConSym(_currn->_ATKey, 1);
/*SPC(1004)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_38(_TPPrule_38 _currn,PTGNode* _AS0SymOut,int* _AS0argcount,int* _AS0ntcount,DefTableKey* _AS0SiblingKey)
#else
void _VS5rule_38(_currn ,_AS0SymOut,_AS0argcount,_AS0ntcount,_AS0SiblingKey)
_TPPrule_38 _currn;
DefTableKey* _AS0SiblingKey;
int* _AS0ntcount;
int* _AS0argcount;
PTGNode* _AS0SymOut;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVConElement_IsFirstOcc=SetGetFirstOcc(_currn->_ATKey, 1, 0);
/*SPC(1389)*/
(* _AS0SymOut)=PTGNULL;
/*SPC(159)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_39(_TPPrule_39 _currn)
#else
void _VS1rule_39(_currn )
_TPPrule_39 _currn;

#endif
{
DefTableKey* _IL_incl21;

_VisitVarDecl()
_VisitEntry();
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATKey);
_AVConProd__SymbolPauxList=NULLSymbolPList;
/*SPC(1179)*/
_AVMapText_cSymbolPListPtr_post=_SymbolPListADDROF(_AVConProd__SymbolPauxList);
/*SPC(1180)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVConProd_Key_RuleAttr_129=NewKey();
/*SPC(292)*/
_AVConProd_SymbolPList=_AVConProd__SymbolPauxList;
/*SPC(1181)*/
_currn->_ATargcount=_AVConAlt__const28;
/*SPC(293)*/
_currn->_ATKey=
(ResetRHS(_AVConProd_Key_RuleAttr_129, _AVConProd_SymbolPList), ResetLHS(_AVConProd_Key_RuleAttr_129, _currn->_desc1->_ATKey), ResetArgCount(_AVConProd_Key_RuleAttr_129, _currn->_ATargcount), ResetNTCount(_AVConProd_Key_RuleAttr_129, _AVConAlt__const29), _AVConProd_Key_RuleAttr_129)
;
/*SPC(295)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl21=_IL_incl21;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_39(_TPPrule_39 _currn)
#else
void _VS2rule_39(_currn )
_TPPrule_39 _currn;

#endif
{
DefTableKey* _IL_incl21;

_VisitVarDecl()
_VisitEntry();
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATKey);
_AVLST_ConAltsetsig_post=OilNewSetSig();
/*SPC(865)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVConProd_signature_RuleAttr_129=
((EQ(_currn->_ATargcount, 0)
) ? (OilAddSetSig(OilTypeToSet(EmptyType), _AVLST_ConAltsetsig_post)
) : (_AVLST_ConAltsetsig_post))
;
/*SPC(860)*/

if (EQ(GetMappedRHS(_currn->_ATKey, NULLSymbolPList), NULLSymbolPList)) {
ConMatch(_currn->_ATKey, _AVConProd_signature_RuleAttr_129, NoKey, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(846)*/
_currn->_ATaxiom=CheckAxiom(_currn->_desc1->_ATKey, 0);
/*SPC(930)*/

if (_currn->_ATaxiom) {
ComputeReach(_currn->_desc1->_ATKey);

} else {
;
}
;
/*SPC(935)*/
_IG_incl21=_IL_incl21;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_39(_TPPrule_39 _currn)
#else
void _VS3rule_39(_currn )
_TPPrule_39 _currn;

#endif
{
DefTableKey* _IL_incl21;

_VisitVarDecl()
_VisitEntry();
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl21=_IL_incl21;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_39(_TPPrule_39 _currn,PTGNode* _AS0Pgram)
#else
void _VS4rule_39(_currn ,_AS0Pgram)
_TPPrule_39 _currn;
PTGNode* _AS0Pgram;

#endif
{
DefTableKey* _IL_incl21;

_VisitVarDecl()
_VisitEntry();
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATKey);
(* _AS0Pgram)=GenConProd(_currn->_ATKey, 0, 1);
/*SPC(110)*/
_IG_incl21=_IL_incl21;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_39(_TPPrule_39 _currn,PTGNode* _AS0ConOut,PTGNode* _AS0AbsTOut,PTGNode* _AS0StartOut,PTGNode* _AS0Pgram,PTGNode* _AS0_const11)
#else
void _VS5rule_39(_currn ,_AS0ConOut,_AS0AbsTOut,_AS0StartOut,_AS0Pgram,_AS0_const11)
_TPPrule_39 _currn;
PTGNode* _AS0_const11;
PTGNode* _AS0Pgram;
PTGNode* _AS0StartOut;
PTGNode* _AS0AbsTOut;
PTGNode* _AS0ConOut;

#endif
{
DefTableKey* _IL_incl21;

_VisitVarDecl()
_VisitEntry();
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(* _AS0_const11)=_AVConAlt__const11;
/*SPC(93)*/
(* _AS0StartOut)=
((_currn->_ATaxiom
) ? (PTGStart(PTGAsIs(StrStr(_currn->_desc1->_ATKey)))
) : (PTGNULL))
;
/*SPC(94)*/
(* _AS0AbsTOut)=GenAbsProd(_currn->_ATKey, 1);
/*SPC(72)*/
(* _AS0ConOut)=GenConProd(_currn->_ATKey, 0, 0);
/*SPC(15)*/
_IG_incl21=_IL_incl21;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_003(_TPPrule_003 _currn)
#else
void _VS1rule_003(_currn )
_TPPrule_003 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRuleIdUse_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVRuleIdUse_Bind=BindingInEnv((* _IG_incl0), _AVRuleIdUse_Sym);
/*SPC(1130)*/
_AVRuleIdUse_Key=KeyOf(_AVRuleIdUse_Bind);
/*SPC(1134)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_000(_TPPrule_000 _currn)
#else
void _VS1rule_000(_currn )
_TPPrule_000 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAbsAlt_SymbolPTakeIt=1;
/*SPC(1185)*/
_AVAbsAlt_Sym=_currn->_ATTERM_1;
/*SPC(198)*/
_AVAbsAlt_Symbol=CreateSymbol();
/*SPC(507)*/
_AVAbsAlt_Bind=BindIdn((* _IG_incl0), _AVAbsAlt_Sym);
/*SPC(1118)*/
_AVAbsAlt_Key=KeyOf(_AVAbsAlt_Bind);
/*SPC(1120)*/
_AVAbsAlt_SymbolPElem=
(SymbolKeySet(_AVAbsAlt_Symbol, _AVAbsAlt_Key), SymbolClassSet(_AVAbsAlt_Symbol, IDENTIFIER), ResetStr(_AVAbsAlt_Key, _AVAbsAlt_Sym), _AVAbsAlt_Symbol)
;
/*SPC(508)*/
_AVMapText_cSymbolPListPtr_post=
((_AVAbsAlt_SymbolPTakeIt
) ? (RefEndConsSymbolPList(_AVMapText_cSymbolPListPtr_post, _AVAbsAlt_SymbolPElem)
) : (_AVMapText_cSymbolPListPtr_post))
;
/*SPC(1186)*/
ResetIsAbs(_AVAbsAlt_Key, 1);
/*SPC(999)*/
ResetIsRHS(_AVAbsAlt_Key, 1);
/*SPC(991)*/

_VisitExit();
}

