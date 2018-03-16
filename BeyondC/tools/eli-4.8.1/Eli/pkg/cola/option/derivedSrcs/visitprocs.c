
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
boolean _AVErrorOpt_DoublyDefined;
boolean _AVCodeOpt_DoublyDefined;
boolean _AVStackOpt_DoublyDefined;
tabmode _AVMode_Scheme;
boolean _AVOnOff_OptionOn;
boolean _AVDirect_DoublyDefined;
boolean _AVTable_DoublyDefined;
boolean _AVFrontend_DoublyDefined;

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
void _VS1SW2(_TPPSW2 _currn)
#else
void _VS1SW2(_currn )
_TPPSW2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVOnOff_OptionOn=FALSE;
/*SPC(148)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1SW1(_TPPSW1 _currn)
#else
void _VS1SW1(_currn )
_TPPSW1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVOnOff_OptionOn=TRUE;
/*SPC(144)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DE3(_TPPDE3 _currn)
#else
void _VS1DE3(_currn )
_TPPDE3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVErrorOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_CL, 1)
) : (0))
;
/*SPC(387)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DE2(_TPPDE2 _currn)
#else
void _VS1DE2(_currn )
_TPPDE2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVErrorOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_CL, 0)
) : (0))
;
/*SPC(378)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DE1(_TPPDE1 _currn)
#else
void _VS1DE1(_currn )
_TPPDE1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVErrorOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_QZ, testval(_currn->_ATTERM_1, MINIMAL_QZ, (&( _currn->_AT_pos))))
) : (0))
;
/*SPC(367)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DC11(_TPPDC11 _currn)
#else
void _VS1DC11(_currn )
_TPPDC11 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVCodeOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_DSC, _AVOnOff_OptionOn)
) : (0))
;
/*SPC(358)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DC10(_TPPDC10 _currn)
#else
void _VS1DC10(_currn )
_TPPDC10 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVCodeOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_IRC, _AVOnOff_OptionOn)
) : (0))
;
/*SPC(349)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DC9(_TPPDC9 _currn)
#else
void _VS1DC9(_currn )
_TPPDC9 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVCodeOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_SRC, _AVOnOff_OptionOn)
) : (0))
;
/*SPC(340)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DC8(_TPPDC8 _currn)
#else
void _VS1DC8(_currn )
_TPPDC8 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVCodeOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_DUM, _AVOnOff_OptionOn)
) : (0))
;
/*SPC(331)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DC7(_TPPDC7 _currn)
#else
void _VS1DC7(_currn )
_TPPDC7 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVCodeOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_CC, _AVOnOff_OptionOn)
) : (0))
;
/*SPC(322)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DC6(_TPPDC6 _currn)
#else
void _VS1DC6(_currn )
_TPPDC6 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVCodeOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_NOSA, testval(_currn->_ATTERM_1, MINIMAL_NOSA, (&( _currn->_AT_pos))))
) : (0))
;
/*SPC(311)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DC5(_TPPDC5 _currn)
#else
void _VS1DC5(_currn )
_TPPDC5 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVCodeOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_NOC, testval(_currn->_ATTERM_1, MINIMAL_NOC, (&( _currn->_AT_pos))))
) : (0))
;
/*SPC(300)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DC4(_TPPDC4 _currn)
#else
void _VS1DC4(_currn )
_TPPDC4 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVCodeOpt_DoublyDefined=define_option(OPT_LP, _AVOnOff_OptionOn);
/*SPC(292)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DC3(_TPPDC3 _currn)
#else
void _VS1DC3(_currn )
_TPPDC3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVCodeOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_LO, 2)
) : (0))
;
/*SPC(284)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DC2(_TPPDC2 _currn)
#else
void _VS1DC2(_currn )
_TPPDC2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVCodeOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_LO, 1)
) : (0))
;
/*SPC(276)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DC1(_TPPDC1 _currn)
#else
void _VS1DC1(_currn )
_TPPDC1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVCodeOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_LO, 0)
) : (0))
;
/*SPC(267)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DS6(_TPPDS6 _currn)
#else
void _VS1DS6(_currn )
_TPPDS6 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVStackOpt_DoublyDefined=
((GenerateDirect
) ? (
((EQ(_currn->_ATTERM_1, 1)
) ? (OR(define_option(OPT_DFS, 1), define_option(OPT_SCC, 0))
) : (
((EQ(_currn->_ATTERM_1, 2)
) ? (OR(define_option(OPT_DFS, 0), define_option(OPT_SCC, 1))
) : (
(message(WARNING, "Option ignored. Please specify '1' for DFS and '2' for SCC.", 0, (&( _currn->_AT_pos))), 0)
))
))

) : (0))
;
/*SPC(252)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DS5(_TPPDS5 _currn)
#else
void _VS1DS5(_currn )
_TPPDS5 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVStackOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_CRE, _AVOnOff_OptionOn)
) : (0))
;
/*SPC(236)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DS4(_TPPDS4 _currn)
#else
void _VS1DS4(_currn )
_TPPDS4 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVStackOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_MP, _AVOnOff_OptionOn)
) : (0))
;
/*SPC(227)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DS3(_TPPDS3 _currn)
#else
void _VS1DS3(_currn )
_TPPDS3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVStackOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_DGD, _AVOnOff_OptionOn)
) : (0))
;
/*SPC(217)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DS2(_TPPDS2 _currn)
#else
void _VS1DS2(_currn )
_TPPDS2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVStackOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_HBL, _AVOnOff_OptionOn)
) : (0))
;
/*SPC(209)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1DS1(_TPPDS1 _currn)
#else
void _VS1DS1(_currn )
_TPPDS1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVStackOpt_DoublyDefined=
((GenerateDirect
) ? (define_option(OPT_SZ, testval(_currn->_ATTERM_1, MINIMAL_SZ, (&( _currn->_AT_pos))))
) : (0))
;
/*SPC(199)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1D3(_TPPD3 _currn)
#else
void _VS1D3(_currn )
_TPPD3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVDirect_DoublyDefined=_AVErrorOpt_DoublyDefined;
/*SPC(402)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1D2(_TPPD2 _currn)
#else
void _VS1D2(_currn )
_TPPD2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVDirect_DoublyDefined=_AVCodeOpt_DoublyDefined;
/*SPC(398)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1D1(_TPPD1 _currn)
#else
void _VS1D1(_currn )
_TPPD1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVDirect_DoublyDefined=_AVStackOpt_DoublyDefined;
/*SPC(394)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1M8(_TPPM8 _currn)
#else
void _VS1M8(_currn )
_TPPM8 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVMode_Scheme=MODE_RDS;
/*SPC(186)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1M7(_TPPM7 _currn)
#else
void _VS1M7(_currn )
_TPPM7 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVMode_Scheme=MODE_SDS;
/*SPC(182)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1M6(_TPPM6 _currn)
#else
void _VS1M6(_currn )
_TPPM6 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVMode_Scheme=MODE_RCSB;
/*SPC(178)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1M5(_TPPM5 _currn)
#else
void _VS1M5(_currn )
_TPPM5 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVMode_Scheme=MODE_RCSA;
/*SPC(174)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1M4(_TPPM4 _currn)
#else
void _VS1M4(_currn )
_TPPM4 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVMode_Scheme=MODE_LESB;
/*SPC(170)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1M3(_TPPM3 _currn)
#else
void _VS1M3(_currn )
_TPPM3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVMode_Scheme=MODE_LESA;
/*SPC(166)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1M2(_TPPM2 _currn)
#else
void _VS1M2(_currn )
_TPPM2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVMode_Scheme=MODE_GCSB;
/*SPC(162)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1M1(_TPPM1 _currn)
#else
void _VS1M1(_currn )
_TPPM1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVMode_Scheme=MODE_GCSA;
/*SPC(158)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1T3(_TPPT3 _currn)
#else
void _VS1T3(_currn )
_TPPT3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTable_DoublyDefined=
((GenerateTable
) ? (define_option(OPT_TTAB, _AVMode_Scheme)
) : (0))
;
/*SPC(451)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1T2(_TPPT2 _currn)
#else
void _VS1T2(_currn )
_TPPT2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTable_DoublyDefined=
((GenerateTable
) ? (define_option(OPT_NTAB, _AVMode_Scheme)
) : (0))
;
/*SPC(443)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1T1(_TPPT1 _currn)
#else
void _VS1T1(_currn )
_TPPT1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTable_DoublyDefined=
((GenerateTable
) ? (define_option(OPT_OPTINFO, _AVOnOff_OptionOn)
) : (0))
;
/*SPC(431)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1F3(_TPPF3 _currn)
#else
void _VS1F3(_currn )
_TPPF3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVFrontend_DoublyDefined=define_option(OPT_AEC, _AVOnOff_OptionOn);
/*SPC(423)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1F2(_TPPF2 _currn)
#else
void _VS1F2(_currn )
_TPPF2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVFrontend_DoublyDefined=define_option(OPT_FREEPOS, _AVOnOff_OptionOn);
/*SPC(414)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1F1(_TPPF1 _currn)
#else
void _VS1F1(_currn )
_TPPF1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVFrontend_DoublyDefined=define_option(OPT_INFO, _AVOnOff_OptionOn);
/*SPC(406)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1Opt4(_TPPOpt4 _currn)
#else
void _VS1Opt4(_currn )
_TPPOpt4 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (NOT(GenerateDirect)) {
message(WARNING, "Option for direct executable Parser Generator ignored.", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(81)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (_AVDirect_DoublyDefined) {
message(WARNING, "Doubly defined option setting ignored.", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(115)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1Opt3(_TPPOpt3 _currn)
#else
void _VS1Opt3(_currn )
_TPPOpt3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (NOT(GenerateTable)) {
message(WARNING, "Option for table driven Parser Generator ignored.", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(75)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (_AVTable_DoublyDefined) {
message(WARNING, "Doubly defined option setting ignored.", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(109)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1Opt2(_TPPOpt2 _currn)
#else
void _VS1Opt2(_currn )
_TPPOpt2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (_AVFrontend_DoublyDefined) {
message(WARNING, "Doubly defined option setting ignored.", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(103)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1Opt1(_TPPOpt1 _currn)
#else
void _VS1Opt1(_currn )
_TPPOpt1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1Root(_TPPRoot _currn)
#else
void _VS1Root(_currn )
_TPPRoot _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
init_options();
/*SPC(134)*/

if (AND(GenerateDirect, GenerateTable)) {
message(FATAL, "You can't use -table and -direct together", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(69)*/

if (AND(NOT(GenerateDirect), NOT(GenerateTable))) {
message(FATAL, "Specify option set with -table or -direct", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(66)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (GenerateDirect) {
PTGOutFile("direct.opt", DirectOptionCode(GenerateDirect));

} else {
}
;
/*SPC(471)*/

if (GenerateTable) {
PTGOutFile("table.opt", TableOptionCode(GenerateTable));
PTGOutFile("table.2.opt", TableOptionCode2(GenerateTable));
;

} else {
}
;
/*SPC(475)*/
PTGOutFile("frontend.opt", FrontendOptionCode());
/*SPC(477)*/

_VisitExit();
}

