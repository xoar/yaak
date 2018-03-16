
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
IdList _AVNamesList_Ids;
ANamesList _AVAttrList_Names;
int _AVAttrType_Flag;
OrdOption _AVArrangeType_OrdEntry;
BEList _AVBackendOpts_BEOpts;
OptList _AVOptimOpts_OptOpts;
OrdList _AVOrderOpts_OrdOpts;
ExpList _AVExpandOpts_EOpts;
IdList _AVIdentList_Ids;
OptCollect _AVOptions_Opts;
int _AVStart_OK;

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
void _VS1BACKEND2(_TPPBACKEND2 _currn,BEOption* _AS0BEEntry)
#else
void _VS1BACKEND2(_currn ,_AS0BEEntry)
_TPPBACKEND2 _currn;
BEOption* _AS0BEEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0BEEntry)=BEOptEnter2(_currn->_ATTERM_1, _currn->_ATTERM_2);
/*SPC(342)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1BACKEND1(_TPPBACKEND1 _currn,BEOption* _AS0BEEntry)
#else
void _VS1BACKEND1(_currn ,_AS0BEEntry)
_TPPBACKEND1 _currn;
BEOption* _AS0BEEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0BEEntry)=BEOptEnter1(_currn->_ATTERM_1);
/*SPC(335)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1NAMESL2(_TPPNAMESL2 _currn)
#else
void _VS1NAMESL2(_currn )
_TPPNAMESL2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVNamesList_Ids=creatIdList(_currn->_ATTERM_1);
/*SPC(326)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1NAMESL1(_TPPNAMESL1 _currn)
#else
void _VS1NAMESL1(_currn )
_TPPNAMESL1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVNamesList_Ids=concatIdList(creatIdList(_currn->_ATTERM_1), _AVNamesList_Ids);
/*SPC(317)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ATTRNAMES(_TPPATTRNAMES _currn,int* _AS0Id,IdList* _AS0Ids)
#else
void _VS1ATTRNAMES(_currn ,_AS0Id,_AS0Ids)
_TPPATTRNAMES _currn;
IdList* _AS0Ids;
int* _AS0Id;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0Ids)=_AVNamesList_Ids;
/*SPC(312)*/
(* _AS0Id)=_currn->_ATTERM_1;
/*SPC(311)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ATTRS2(_TPPATTRS2 _currn)
#else
void _VS1ATTRS2(_currn )
_TPPATTRS2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAttrList_Names=nullNamesList();
/*SPC(306)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ATTRS1(_TPPATTRS1 _currn)
#else
void _VS1ATTRS1(_currn )
_TPPATTRS1 _currn;

#endif
{
IdList _AS1Ids;
int _AS1Id;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,IdList*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Id)),(&( _AS1Ids)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVAttrList_Names=concatNamesList(creatNamesList(_AS1Id, _AS1Ids), _AVAttrList_Names);
/*SPC(297)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ATTRTYPE2(_TPPATTRTYPE2 _currn)
#else
void _VS1ATTRTYPE2(_currn )
_TPPATTRTYPE2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAttrType_Flag=AttrTypeId2();
/*SPC(292)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ATTRTYPE1(_TPPATTRTYPE1 _currn)
#else
void _VS1ATTRTYPE1(_currn )
_TPPATTRTYPE1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAttrType_Flag=AttrTypeId1(_currn->_ATTERM_1, _currn->_ATTERM_2);
/*SPC(285)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OPTIM3(_TPPOPTIM3 _currn,OptOption* _AS0OptEntry)
#else
void _VS1OPTIM3(_currn ,_AS0OptEntry)
_TPPOPTIM3 _currn;
OptOption* _AS0OptEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(* _AS0OptEntry)=OptOptEnter3(_AVAttrType_Flag, _AVAttrList_Names);
/*SPC(275)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OPTIM2(_TPPOPTIM2 _currn,OptOption* _AS0OptEntry)
#else
void _VS1OPTIM2(_currn ,_AS0OptEntry)
_TPPOPTIM2 _currn;
OptOption* _AS0OptEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0OptEntry)=OptOptEnter2(_currn->_ATTERM_1);
/*SPC(269)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OPTIM1(_TPPOPTIM1 _currn,OptOption* _AS0OptEntry)
#else
void _VS1OPTIM1(_currn ,_AS0OptEntry)
_TPPOPTIM1 _currn;
OptOption* _AS0OptEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0OptEntry)=OptOptEnter1(_currn->_ATTERM_1);
/*SPC(262)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ATTR1(_TPPATTR1 _currn,int* _AS0Id1,int* _AS0Id2,int* _AS0IntVal)
#else
void _VS1ATTR1(_currn ,_AS0Id1,_AS0Id2,_AS0IntVal)
_TPPATTR1 _currn;
int* _AS0IntVal;
int* _AS0Id2;
int* _AS0Id1;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0IntVal)=_currn->_ATTERM_2;
/*SPC(255)*/
(* _AS0Id2)=_currn->_ATTERM_3;
/*SPC(254)*/
(* _AS0Id1)=_currn->_ATTERM_1;
/*SPC(253)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ARRANGE3(_TPPARRANGE3 _currn)
#else
void _VS1ARRANGE3(_currn )
_TPPARRANGE3 _currn;

#endif
{
int _AS2IntVal;
int _AS2Id2;
int _AS2Id1;
int _AS1IntVal;
int _AS1Id2;
int _AS1Id1;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*,int*,int*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Id1)),(&( _AS1Id2)),(&( _AS1IntVal)));
(*(_CALL_VS_((NODEPTR ,int*,int*,int*)) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Id1)),(&( _AS2Id2)),(&( _AS2IntVal)));
_AVArrangeType_OrdEntry=OrdOptEnter6(_currn->_ATTERM_1, _AS1Id1, _AS1Id2, _AS1IntVal, _AS2Id1, _AS2Id2, _AS2IntVal);
/*SPC(241)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ARRANGE2(_TPPARRANGE2 _currn)
#else
void _VS1ARRANGE2(_currn )
_TPPARRANGE2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVArrangeType_OrdEntry=OrdOptEnter5(_currn->_ATTERM_1, _currn->_ATTERM_2, _currn->_ATTERM_3);
/*SPC(233)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ARRANGE4(_TPPARRANGE4 _currn)
#else
void _VS1ARRANGE4(_currn )
_TPPARRANGE4 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVArrangeType_OrdEntry=OrdOptEnter7();
/*SPC(228)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ARRANGE1(_TPPARRANGE1 _currn)
#else
void _VS1ARRANGE1(_currn )
_TPPARRANGE1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVArrangeType_OrdEntry=OrdOptEnter4();
/*SPC(223)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ORDER4(_TPPORDER4 _currn,OrdOption* _AS0OrdEntry)
#else
void _VS1ORDER4(_currn ,_AS0OrdEntry)
_TPPORDER4 _currn;
OrdOption* _AS0OrdEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0OrdEntry)=_AVArrangeType_OrdEntry;
/*SPC(218)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ORDER3(_TPPORDER3 _currn,OrdOption* _AS0OrdEntry)
#else
void _VS1ORDER3(_currn ,_AS0OrdEntry)
_TPPORDER3 _currn;
OrdOption* _AS0OrdEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0OrdEntry)=OrdOptEnter3(_currn->_ATTERM_1);
/*SPC(212)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ORDER2(_TPPORDER2 _currn,OrdOption* _AS0OrdEntry)
#else
void _VS1ORDER2(_currn ,_AS0OrdEntry)
_TPPORDER2 _currn;
OrdOption* _AS0OrdEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0OrdEntry)=OrdOptEnter2(_currn->_ATTERM_1, _AVIdentList_Ids);
/*SPC(204)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ORDER1(_TPPORDER1 _currn,OrdOption* _AS0OrdEntry)
#else
void _VS1ORDER1(_currn ,_AS0OrdEntry)
_TPPORDER1 _currn;
OrdOption* _AS0OrdEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0OrdEntry)=OrdOptEnter1(_currn->_ATTERM_1, _currn->_ATTERM_2);
/*SPC(194)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1EXPAND2(_TPPEXPAND2 _currn,ExpOption* _AS0ExpEntry)
#else
void _VS1EXPAND2(_currn ,_AS0ExpEntry)
_TPPEXPAND2 _currn;
ExpOption* _AS0ExpEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0ExpEntry)=ExpOptEnter2(_currn->_ATTERM_1);
/*SPC(185)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1EXPAND3(_TPPEXPAND3 _currn,ExpOption* _AS0ExpEntry)
#else
void _VS1EXPAND3(_currn ,_AS0ExpEntry)
_TPPEXPAND3 _currn;
ExpOption* _AS0ExpEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0ExpEntry)=ExpOptEnter3(_currn->_ATTERM_1);
/*SPC(178)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1EXPAND1(_TPPEXPAND1 _currn,ExpOption* _AS0ExpEntry)
#else
void _VS1EXPAND1(_currn ,_AS0ExpEntry)
_TPPEXPAND1 _currn;
ExpOption* _AS0ExpEntry;

#endif
{

_VisitVarDecl()
_VisitEntry();
(* _AS0ExpEntry)=ExpOptEnter1(_currn->_ATTERM_1, _currn->_ATTERM_2);
/*SPC(170)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1BACKS2(_TPPBACKS2 _currn)
#else
void _VS1BACKS2(_currn )
_TPPBACKS2 _currn;

#endif
{
BEOption _AS1BEEntry;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,BEOption*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1BEEntry)));
_AVBackendOpts_BEOpts=creatBEOList(_AS1BEEntry);
/*SPC(161)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1BACKS1(_TPPBACKS1 _currn)
#else
void _VS1BACKS1(_currn )
_TPPBACKS1 _currn;

#endif
{
BEOption _AS1BEEntry;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,BEOption*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1BEEntry)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVBackendOpts_BEOpts=concatBEOList(creatBEOList(_AS1BEEntry), _AVBackendOpts_BEOpts);
/*SPC(153)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OPTIMS2(_TPPOPTIMS2 _currn)
#else
void _VS1OPTIMS2(_currn )
_TPPOPTIMS2 _currn;

#endif
{
OptOption _AS1OptEntry;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,OptOption*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1OptEntry)));
_AVOptimOpts_OptOpts=creatOptOList(_AS1OptEntry);
/*SPC(147)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OPTIMS1(_TPPOPTIMS1 _currn)
#else
void _VS1OPTIMS1(_currn )
_TPPOPTIMS1 _currn;

#endif
{
OptOption _AS1OptEntry;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,OptOption*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1OptEntry)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVOptimOpts_OptOpts=concatOptOList(creatOptOList(_AS1OptEntry), _AVOptimOpts_OptOpts);
/*SPC(139)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ORDERS2(_TPPORDERS2 _currn)
#else
void _VS1ORDERS2(_currn )
_TPPORDERS2 _currn;

#endif
{
OrdOption _AS1OrdEntry;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,OrdOption*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1OrdEntry)));
_AVOrderOpts_OrdOpts=creatOrdOList(_AS1OrdEntry);
/*SPC(133)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1ORDERS1(_TPPORDERS1 _currn)
#else
void _VS1ORDERS1(_currn )
_TPPORDERS1 _currn;

#endif
{
OrdOption _AS1OrdEntry;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,OrdOption*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1OrdEntry)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVOrderOpts_OrdOpts=concatOrdOList(creatOrdOList(_AS1OrdEntry), _AVOrderOpts_OrdOpts);
/*SPC(125)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1EXPANDS2(_TPPEXPANDS2 _currn)
#else
void _VS1EXPANDS2(_currn )
_TPPEXPANDS2 _currn;

#endif
{
ExpOption _AS1ExpEntry;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,ExpOption*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1ExpEntry)));
_AVExpandOpts_EOpts=creatExpOList(_AS1ExpEntry);
/*SPC(118)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1EXPANDS1(_TPPEXPANDS1 _currn)
#else
void _VS1EXPANDS1(_currn )
_TPPEXPANDS1 _currn;

#endif
{
ExpOption _AS1ExpEntry;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,ExpOption*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1ExpEntry)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVExpandOpts_EOpts=concatExpOList(creatExpOList(_AS1ExpEntry), _AVExpandOpts_EOpts);
/*SPC(110)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1IDENTS2(_TPPIDENTS2 _currn)
#else
void _VS1IDENTS2(_currn )
_TPPIDENTS2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVIdentList_Ids=nullIdList();
/*SPC(103)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1IDENTS1(_TPPIDENTS1 _currn)
#else
void _VS1IDENTS1(_currn )
_TPPIDENTS1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVIdentList_Ids=concatIdList(creatIdList(_currn->_ATTERM_1), _AVIdentList_Ids);
/*SPC(94)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OPTBACK(_TPPOPTBACK _currn,OptCombin* _AS0Opts)
#else
void _VS1OPTBACK(_currn ,_AS0Opts)
_TPPOPTBACK _currn;
OptCombin* _AS0Opts;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0Opts)=TransferOpts4(_AVBackendOpts_BEOpts);
/*SPC(87)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OPTOPT(_TPPOPTOPT _currn,OptCombin* _AS0Opts)
#else
void _VS1OPTOPT(_currn ,_AS0Opts)
_TPPOPTOPT _currn;
OptCombin* _AS0Opts;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0Opts)=TransferOpts3(_AVOptimOpts_OptOpts);
/*SPC(81)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OPTORD(_TPPOPTORD _currn,OptCombin* _AS0Opts)
#else
void _VS1OPTORD(_currn ,_AS0Opts)
_TPPOPTORD _currn;
OptCombin* _AS0Opts;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0Opts)=TransferOpts2(_AVOrderOpts_OrdOpts);
/*SPC(75)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OPTEXP(_TPPOPTEXP _currn,OptCombin* _AS0Opts)
#else
void _VS1OPTEXP(_currn ,_AS0Opts)
_TPPOPTEXP _currn;
OptCombin* _AS0Opts;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0Opts)=TransferOpts1(_AVExpandOpts_EOpts);
/*SPC(69)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OPTIONS2(_TPPOPTIONS2 _currn)
#else
void _VS1OPTIONS2(_currn )
_TPPOPTIONS2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVOptions_Opts=InitOpts();
/*SPC(64)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1OPTIONS1(_TPPOPTIONS1 _currn)
#else
void _VS1OPTIONS1(_currn )
_TPPOPTIONS1 _currn;

#endif
{
OptCombin _AS1Opts;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,OptCombin*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Opts)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVOptions_Opts=JoinOpts(_AS1Opts, _AVOptions_Opts);
/*SPC(57)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1START(_TPPSTART _currn)
#else
void _VS1START(_currn )
_TPPSTART _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVStart_OK=Mix_Options(Conflict_Test(_AVOptions_Opts), _AVOptions_Opts);
/*SPC(48)*/
Output(_AVOptions_Opts, _AVStart_OK);
/*SPC(47)*/

_VisitExit();
}

