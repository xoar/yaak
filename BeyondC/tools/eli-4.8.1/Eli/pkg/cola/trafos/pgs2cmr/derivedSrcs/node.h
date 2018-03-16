
/* definition of tree node structure */

#ifndef NODE_H
#define NODE_H
#include "err.h"
#include "nodeptr.h" /* defines NODEPTR */
#include "HEAD.h"

#ifdef MONITOR
#define _NODECOMMON int _prod; POSITION _coord;
#else
#define _NODECOMMON int _prod;
#endif
struct NODEPTR_struct {
        _NODECOMMON
#ifdef __cplusplus
        void* operator new(size_t size);
#endif
};

typedef struct _TSpgs_root* _TSPpgs_root;
typedef struct _TSG3* _TSPG3;
typedef struct _TSG2* _TSPG2;
typedef struct _TSerr_part* _TSPerr_part;
typedef struct _TSG4* _TSPG4;
typedef struct _TSG1* _TSPG1;
typedef struct _TSactpts_root* _TSPactpts_root;
typedef struct _TSterm_def* _TSPterm_def;
typedef struct _TScode_def* _TSPcode_def;
typedef struct _TSelem_list* _TSPelem_list;
typedef struct _TSalt_op* _TSPalt_op;
typedef struct _TSmod_op* _TSPmod_op;
typedef struct _TSskip_part* _TSPskip_part;
typedef struct _TSbracket_part* _TSPbracket_part;
typedef struct _TSterm_def_list* _TSPterm_def_list;
typedef struct _TSsepa_part* _TSPsepa_part;
typedef struct _TScode_def_list* _TSPcode_def_list;
typedef struct _TScode_part* _TSPcode_part;
typedef struct _TSelem* _TSPelem;
typedef struct _TSoptelem* _TSPoptelem;
typedef struct _TSdel_op* _TSPdel_op;
typedef struct _TSrep_op* _TSPrep_op;
typedef struct _TSstop_part* _TSPstop_part;
typedef struct _TSmodification* _TSPmodification;
typedef struct _TSnonliteral* _TSPnonliteral;
typedef struct _TSliteral* _TSPliteral;
typedef struct _TSconnection* _TSPconnection;
typedef struct _TSt_or_nt* _TSPt_or_nt;
typedef struct _TSterminal* _TSPterminal;
typedef struct _TSroot* _TSProot;
typedef struct _TSrhs* _TSPrhs;
typedef struct _TSsep_op* _TSPsep_op;
typedef struct _TSnonterminal* _TSPnonterminal;
typedef struct _TSrulename* _TSPrulename;
typedef struct _TSrule* _TSPrule;
typedef struct _TSrule_list* _TSPrule_list;
typedef struct _TSstart* _TSPstart;
typedef struct _TSgrammarname* _TSPgrammarname;
typedef struct _TSgrammar_part* _TSPgrammar_part;
typedef struct _TPrule_1* _TPPrule_1;
typedef struct _TPrule_2* _TPPrule_2;
typedef struct _TPrule_3* _TPPrule_3;
typedef struct _TPrule_4* _TPPrule_4;
typedef struct _TPrule_5* _TPPrule_5;
typedef struct _TPrule_6* _TPPrule_6;
typedef struct _TPrule_7* _TPPrule_7;
typedef struct _TPrule_8* _TPPrule_8;
typedef struct _TPrule_9* _TPPrule_9;
typedef struct _TPrule_10* _TPPrule_10;
typedef struct _TPrule_11* _TPPrule_11;
typedef struct _TPrule_12* _TPPrule_12;
typedef struct _TPrule_13* _TPPrule_13;
typedef struct _TPrule_14* _TPPrule_14;
typedef struct _TPrule_15* _TPPrule_15;
typedef struct _TPrule_16* _TPPrule_16;
typedef struct _TPrule_17* _TPPrule_17;
typedef struct _TPrule_18* _TPPrule_18;
typedef struct _TPrule_19* _TPPrule_19;
typedef struct _TPrule_20* _TPPrule_20;
typedef struct _TPrule_21* _TPPrule_21;
typedef struct _TPrule_22* _TPPrule_22;
typedef struct _TPrule_23* _TPPrule_23;
typedef struct _TPrule_24* _TPPrule_24;
typedef struct _TPrule_25* _TPPrule_25;
typedef struct _TPrule_26* _TPPrule_26;
typedef struct _TPrule_27* _TPPrule_27;
typedef struct _TPrule_28* _TPPrule_28;
typedef struct _TPrule_29* _TPPrule_29;
typedef struct _TPrule_30* _TPPrule_30;
typedef struct _TPrule_65* _TPPrule_65;
typedef struct _TPrule_64* _TPPrule_64;
typedef struct _TPrule_63* _TPPrule_63;
typedef struct _TPrule_62* _TPPrule_62;
typedef struct _TPrule_61* _TPPrule_61;
typedef struct _TPrule_60* _TPPrule_60;
typedef struct _TPrule_59* _TPPrule_59;
typedef struct _TPrule_58* _TPPrule_58;
typedef struct _TPrule_57* _TPPrule_57;
typedef struct _TPrule_56* _TPPrule_56;
typedef struct _TPrule_55* _TPPrule_55;
typedef struct _TPrule_54* _TPPrule_54;
typedef struct _TPrule_53* _TPPrule_53;
typedef struct _TPrule_52* _TPPrule_52;
typedef struct _TPrule_51* _TPPrule_51;
typedef struct _TPrule_50* _TPPrule_50;
typedef struct _TPrule_49* _TPPrule_49;
typedef struct _TPrule_48* _TPPrule_48;
typedef struct _TPrule_47* _TPPrule_47;
typedef struct _TPrule_46* _TPPrule_46;
typedef struct _TPrule_45* _TPPrule_45;
typedef struct _TPrule_44* _TPPrule_44;
typedef struct _TPrule_43* _TPPrule_43;
typedef struct _TPrule_42* _TPPrule_42;
typedef struct _TPrule_41* _TPPrule_41;
typedef struct _TPrule_40* _TPPrule_40;
typedef struct _TPrule_39* _TPPrule_39;
typedef struct _TPrule_38* _TPPrule_38;
typedef struct _TPrule_37* _TPPrule_37;
typedef struct _TPrule_36* _TPPrule_36;
typedef struct _TPrule_35* _TPPrule_35;
typedef struct _TPrule_34* _TPPrule_34;
typedef struct _TPrule_33* _TPPrule_33;
typedef struct _TPrule_32* _TPPrule_32;
typedef struct _TPrule_31* _TPPrule_31;
typedef struct _TPRmod_op1* _TPPRmod_op1;

struct _TSpgs_root
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSG3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSG2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSerr_part
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSG4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSG1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSactpts_root
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSterm_def
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TScode_def
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSelem_list
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSalt_op
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSmod_op
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
proptype _ATm_op;
SID _ATpsymbol;
};

struct _TSskip_part
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSbracket_part
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSterm_def_list
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATpsymbol;
};

struct _TSsepa_part
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TScode_def_list
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATpsymbol;
};

struct _TScode_part
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSelem
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSoptelem
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSdel_op
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATisebnf;
};

struct _TSrep_op
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATopr;
int _ATisebnf;
};

struct _TSstop_part
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
def_entry _ATdef;
DID _ATeofdid;
};

struct _TSmodification
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSnonliteral
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATsymbol;
int _ATSym;
DefTableKey _ATKey;
};

struct _TSliteral
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATsymbol;
int _ATSym;
DefTableKey _ATKey;
};

struct _TSconnection
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATtntcnt_pre;
DefTableKey _ATKey;
};

struct _TSt_or_nt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATtype;
DefTableKey _ATKey;
};

struct _TSterminal
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
def_entry _ATdef;
DefTableKey _ATKey;
};

struct _TSroot
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATNonliteralEnv;
Environment _ATLiteralEnv;
DID _ATeofdid;
};

struct _TSrhs
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const8;
int _ATtntcnt_post;
};

struct _TSsep_op
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATtntcnt_post;
};

struct _TSnonterminal
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATsymbol;
int _ATIsFirstOcc;
int _ATstartcnt;
DefTableKey _ATKey;
};

struct _TSrulename
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATsymbol;
};

struct _TSrule
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATchainelim;
int _ATmaxcnt;
int _ATisebnf;
};

struct _TSrule_list
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const18;
};

struct _TSstart
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const18;
};

struct _TSgrammarname
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSgrammar_part
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATstartcnt;
};

struct _TPrule_1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const18;
_TSPsep_op _desc1;
_TSPnonterminal _desc2;
};

struct _TPrule_2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPt_or_nt _desc1;
};

struct _TPrule_3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPterminal _desc1;
};

struct _TPrule_4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPmod_op _desc1;
_TSPterminal _desc2;
};

struct _TPrule_5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPterminal _desc1;
int _ATTERM_1;
};

struct _TPrule_6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATopr;
int _ATisebnf;
};

struct _TPrule_7
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATopr;
int _ATisebnf;
};

struct _TPrule_8
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPelem _desc1;
_TSPrep_op _desc2;
};

struct _TPrule_9
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const8;
int _ATtntcnt_post;
_TSPrhs _desc1;
_TSPalt_op _desc2;
_TSPelem_list _desc3;
};

struct _TPrule_10
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const8;
int _ATtntcnt_post;
_TSPrhs _desc1;
_TSPdel_op _desc2;
_TSPterminal _desc3;
};

struct _TPrule_11
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATchainelim;
int _ATmaxcnt;
int _ATisebnf;
_TSPnonterminal _desc1;
_TSPsep_op _desc2;
_TSPrhs _desc3;
POSITION _AT_pos;
};

struct _TPrule_12
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
proptype _ATm_op;
SID _ATpsymbol;
};

struct _TPrule_13
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_14
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPterm_def_list _desc1;
};

struct _TPrule_15
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_16
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPterm_def_list _desc1;
};

struct _TPrule_17
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_18
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPterm_def_list _desc1;
};

struct _TPrule_19
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_20
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPcode_def_list _desc1;
};

struct _TPrule_21
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPrhs _desc1;
};

struct _TPrule_22
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPoptelem _desc1;
};

struct _TPrule_23
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const18;
};

struct _TPrule_24
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATtype;
DefTableKey _ATKey;
_TSPliteral _desc1;
POSITION _AT_pos;
};

struct _TPrule_25
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATtype;
DefTableKey _ATKey;
_TSPnonliteral _desc1;
POSITION _AT_pos;
};

struct _TPrule_26
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
def_entry _ATdef;
DID _ATeofdid;
_TSPterminal _desc1;
};

struct _TPrule_27
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATsymbol;
int _ATTERM_1;
};

struct _TPrule_28
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATchainelim;
int _ATmaxcnt;
int _ATisebnf;
_TSPrulename _desc1;
_TSPnonterminal _desc2;
_TSPsep_op _desc3;
_TSPrhs _desc4;
POSITION _AT_pos;
};

struct _TPrule_29
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_30
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATstartcnt;
_TSPgrammarname _desc1;
_TSPstart _desc2;
_TSPrule_list _desc3;
};

struct _TPrule_65
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
def_entry _ATdef;
DefTableKey _ATKey;
_TSPnonliteral _desc1;
POSITION _AT_pos;
};

struct _TPrule_64
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
def_entry _ATdef;
DefTableKey _ATKey;
_TSPliteral _desc1;
POSITION _AT_pos;
};

struct _TPrule_63
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATpsymbol;
_TSPG2 _desc1;
};

struct _TPrule_62
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
def_entry _ATdef;
DID _ATeofdid;
};

struct _TPrule_61
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
def_entry _ATdef;
DID _ATeofdid;
};

struct _TPrule_60
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATtntcnt_post;
};

struct _TPrule_59
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATtntcnt_post;
};

struct _TPrule_58
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const18;
_TSPG3 _desc1;
};

struct _TPrule_57
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATNonliteralEnv;
Environment _ATLiteralEnv;
DID _ATeofdid;
_TSPpgs_root _desc1;
_TSPactpts_root _desc2;
};

struct _TPrule_56
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPcode_part _desc1;
_TSPstop_part _desc2;
_TSPerr_part _desc3;
_TSPgrammar_part _desc4;
};

struct _TPrule_55
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATsymbol;
int _ATIsFirstOcc;
int _ATstartcnt;
DefTableKey _ATKey;
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_54
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATsymbol;
int _ATSym;
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_53
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATsymbol;
int _ATSym;
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_52
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATstartcnt;
_TSPstart _desc1;
_TSPrule_list _desc2;
};

struct _TPrule_51
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG4 _desc1;
_TSPmodification _desc2;
};

struct _TPrule_50
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG4 _desc1;
_TSPelem _desc2;
};

struct _TPrule_49
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG4 _desc1;
_TSPconnection _desc2;
};

struct _TPrule_48
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_47
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG3 _desc1;
_TSPrule _desc2;
};

struct _TPrule_46
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_45
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG2 _desc1;
_TSPterm_def _desc2;
};

struct _TPrule_44
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_43
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG1 _desc1;
_TSPcode_def _desc2;
};

struct _TPrule_42
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_41
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPsepa_part _desc1;
_TSPbracket_part _desc2;
_TSPskip_part _desc3;
};

struct _TPrule_40
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPrhs _desc1;
};

struct _TPrule_39
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG4 _desc1;
};

struct _TPrule_38
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATisebnf;
};

struct _TPrule_37
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATisebnf;
};

struct _TPrule_36
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATtntcnt_pre;
DefTableKey _ATKey;
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
SID _ATpsymbol;
_TSPG1 _desc1;
};

struct _TPrule_34
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_33
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_32
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const8;
int _ATtntcnt_post;
_TSPelem_list _desc1;
};

struct _TPrule_31
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPRmod_op1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
proptype _ATm_op;
SID _ATpsymbol;
};

#undef _NODECOMMON
#endif
