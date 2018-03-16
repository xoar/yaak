
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

typedef struct _TSLST_Source* _TSPLST_Source;
typedef struct _TSLST_ConAlt* _TSPLST_ConAlt;
typedef struct _TSLST_AbsElements* _TSPLST_AbsElements;
typedef struct _TSLST_AbsAlts* _TSPLST_AbsAlts;
typedef struct _TSLST_MapMembers* _TSPLST_MapMembers;
typedef struct _TSLST_MapAlt* _TSPLST_MapAlt;
typedef struct _TSLST_MapReorderAlt* _TSPLST_MapReorderAlt;
typedef struct _TSMapDelim* _TSPMapDelim;
typedef struct _TSMapReorder* _TSPMapReorder;
typedef struct _TSMapProd* _TSPMapProd;
typedef struct _TSMapAbs* _TSPMapAbs;
typedef struct _TSAbsSignature* _TSPAbsSignature;
typedef struct _TSRuleIdUse* _TSPRuleIdUse;
typedef struct _TSMapLHS* _TSPMapLHS;
typedef struct _TSMaptoId* _TSPMaptoId;
typedef struct _TSAbsRuleId* _TSPAbsRuleId;
typedef struct _TSMapText* _TSPMapText;
typedef struct _TSMapPosition* _TSPMapPosition;
typedef struct _TSMapReorderAlt* _TSPMapReorderAlt;
typedef struct _TSMapElement* _TSPMapElement;
typedef struct _TSMapAlt* _TSPMapAlt;
typedef struct _TSMapMember* _TSPMapMember;
typedef struct _TSMapMembers* _TSPMapMembers;
typedef struct _TSAbsAlt* _TSPAbsAlt;
typedef struct _TSAbsAlts* _TSPAbsAlts;
typedef struct _TSAbsElements* _TSPAbsElements;
typedef struct _TSBottomUpRule* _TSPBottomUpRule;
typedef struct _TSMapChains* _TSPMapChains;
typedef struct _TSMapRule* _TSPMapRule;
typedef struct _TSMapSymbol* _TSPMapSymbol;
typedef struct _TSAbsElement* _TSPAbsElement;
typedef struct _TSConElement* _TSPConElement;
typedef struct _TSAbsLHS* _TSPAbsLHS;
typedef struct _TSConAlt* _TSPConAlt;
typedef struct _TSConLHS* _TSPConLHS;
typedef struct _TSAbsProd* _TSPAbsProd;
typedef struct _TSConProd* _TSPConProd;
typedef struct _TSSource* _TSPSource;
typedef struct _TPLST_BottomUpRulerule_35* _TPPLST_BottomUpRulerule_35;
typedef struct _TPLST_MapChainsrule_35* _TPPLST_MapChainsrule_35;
typedef struct _TPLST_MapRulerule_35* _TPPLST_MapRulerule_35;
typedef struct _TPLST_MapSymbolrule_35* _TPPLST_MapSymbolrule_35;
typedef struct _TPLST_AbsProdrule_35* _TPPLST_AbsProdrule_35;
typedef struct _TPLST_ConProdrule_35* _TPPLST_ConProdrule_35;
typedef struct _TPLST_0rule_35* _TPPLST_0rule_35;
typedef struct _TPLST_ConElementrule_34* _TPPLST_ConElementrule_34;
typedef struct _TPLST_0rule_34* _TPPLST_0rule_34;
typedef struct _TPLST_AbsElementrule_33* _TPPLST_AbsElementrule_33;
typedef struct _TPLST_0rule_33* _TPPLST_0rule_33;
typedef struct _TPLST_AbsAltrule_32* _TPPLST_AbsAltrule_32;
typedef struct _TPLST_0rule_32* _TPPLST_0rule_32;
typedef struct _TPLST_MapMemberrule_31* _TPPLST_MapMemberrule_31;
typedef struct _TPLST_0rule_31* _TPPLST_0rule_31;
typedef struct _TPLST_MapElementrule_30* _TPPLST_MapElementrule_30;
typedef struct _TPLST_0rule_30* _TPPLST_0rule_30;
typedef struct _TPLST_MapTextrule_29* _TPPLST_MapTextrule_29;
typedef struct _TPLST_MapPositionrule_29* _TPPLST_MapPositionrule_29;
typedef struct _TPLST_0rule_29* _TPPLST_0rule_29;
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
typedef struct _TPrule_31* _TPPrule_31;
typedef struct _TPrule_32* _TPPrule_32;
typedef struct _TPrule_33* _TPPrule_33;
typedef struct _TPrule_34* _TPPrule_34;
typedef struct _TPrule_35* _TPPrule_35;
typedef struct _TPrule_36* _TPPrule_36;
typedef struct _TPrule_37* _TPPrule_37;
typedef struct _TPrule_38* _TPPrule_38;
typedef struct _TPrule_39* _TPPrule_39;
typedef struct _TPrule_003* _TPPrule_003;
typedef struct _TPrule_002* _TPPrule_002;
typedef struct _TPrule_001* _TPPrule_001;
typedef struct _TPrule_000* _TPPrule_000;

struct _TSLST_Source
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSLST_ConAlt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSLST_AbsElements
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSLST_AbsAlts
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSLST_MapMembers
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSLST_MapAlt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSLST_MapReorderAlt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMapDelim
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMapReorder
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMapProd
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMapAbs
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAbsSignature
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _AT_const4;
int _ATargcount;
tOilArgSig _ATargsig;
};

struct _TSRuleIdUse
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMapLHS
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMaptoId
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
};

struct _TSAbsRuleId
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMapText
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATSym;
};

struct _TSMapPosition
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMapReorderAlt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMapElement
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMapAlt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMapMember
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSMapMembers
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAbsAlt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAbsAlts
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAbsElements
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSBottomUpRule
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATGotBottomUp;
};

struct _TSMapChains
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMapRule
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATntcount;
};

struct _TSMapSymbol
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSAbsElement
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSConElement
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSAbsLHS
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
};

struct _TSConAlt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSConLHS
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
};

struct _TSAbsProd
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATaxiom;
DefTableKey _ATKey;
};

struct _TSConProd
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATargcount;
int _ATaxiom;
DefTableKey _ATKey;
};

struct _TSSource
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
int _ATGotBottomUp;
int _ATAxiomCnt;
};

struct _TPLST_BottomUpRulerule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPBottomUpRule _desc1;
_TSPLST_Source _desc2;
};

struct _TPLST_MapChainsrule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPMapChains _desc1;
_TSPLST_Source _desc2;
};

struct _TPLST_MapRulerule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPMapRule _desc1;
_TSPLST_Source _desc2;
};

struct _TPLST_MapSymbolrule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPMapSymbol _desc1;
_TSPLST_Source _desc2;
};

struct _TPLST_AbsProdrule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAbsProd _desc1;
_TSPLST_Source _desc2;
};

struct _TPLST_ConProdrule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPConProd _desc1;
_TSPLST_Source _desc2;
};

struct _TPLST_0rule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
NODEPTR _desc1;
NODEPTR _desc2;
};

struct _TPLST_ConElementrule_34
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPConElement _desc1;
_TSPLST_ConAlt _desc2;
};

struct _TPLST_0rule_34
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
NODEPTR _desc1;
NODEPTR _desc2;
};

struct _TPLST_AbsElementrule_33
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAbsElement _desc1;
_TSPLST_AbsElements _desc2;
};

struct _TPLST_0rule_33
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
NODEPTR _desc1;
NODEPTR _desc2;
};

struct _TPLST_AbsAltrule_32
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAbsAlt _desc1;
_TSPLST_AbsAlts _desc2;
};

struct _TPLST_0rule_32
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
NODEPTR _desc1;
NODEPTR _desc2;
};

struct _TPLST_MapMemberrule_31
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPMapMember _desc1;
_TSPLST_MapMembers _desc2;
};

struct _TPLST_0rule_31
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
NODEPTR _desc1;
NODEPTR _desc2;
};

struct _TPLST_MapElementrule_30
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPMapElement _desc1;
_TSPLST_MapAlt _desc2;
};

struct _TPLST_0rule_30
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
NODEPTR _desc1;
NODEPTR _desc2;
};

struct _TPLST_MapTextrule_29
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPMapText _desc1;
_TSPLST_MapReorderAlt _desc2;
};

struct _TPLST_MapPositionrule_29
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPMapPosition _desc1;
_TSPLST_MapReorderAlt _desc2;
};

struct _TPLST_0rule_29
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
NODEPTR _desc1;
NODEPTR _desc2;
};

struct _TPrule_1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATSym;
};

struct _TPrule_3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPMapReorderAlt _desc1;
};

struct _TPrule_5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_7
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_8
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPMapLHS _desc1;
_TSPMapDelim _desc2;
_TSPMapAlt _desc3;
POSITION _AT_pos;
};

struct _TPrule_9
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATntcount;
_TSPMapProd _desc1;
_TSPMapReorder _desc2;
_TSPMapAbs _desc3;
POSITION _AT_pos;
};

struct _TPrule_10
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRuleIdUse _desc1;
};

struct _TPrule_11
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_12
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
_TSPMaptoId _desc1;
_TSPMapMembers _desc2;
POSITION _AT_pos;
};

struct _TPrule_13
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_14
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATGotBottomUp;
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_15
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _AT_const4;
int _ATargcount;
tOilArgSig _ATargsig;
_TSPAbsLHS _desc1;
_TSPAbsAlts _desc2;
POSITION _AT_pos;
};

struct _TPrule_16
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_17
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _AT_const4;
int _ATargcount;
tOilArgSig _ATargsig;
_TSPAbsLHS _desc1;
_TSPAbsElements _desc2;
};

struct _TPrule_18
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_19
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATaxiom;
DefTableKey _ATKey;
_TSPAbsRuleId _desc1;
_TSPAbsSignature _desc2;
};

struct _TPrule_20
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_21
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_22
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_23
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_24
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_25
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_26
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
};

struct _TPrule_27
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_28
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_29
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLST_MapReorderAlt _desc1;
};

struct _TPrule_30
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLST_MapAlt _desc1;
};

struct _TPrule_31
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLST_MapMembers _desc1;
};

struct _TPrule_32
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLST_AbsAlts _desc1;
};

struct _TPrule_33
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLST_AbsElements _desc1;
};

struct _TPrule_34
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLST_ConAlt _desc1;
};

struct _TPrule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
int _ATGotBottomUp;
int _ATAxiomCnt;
_TSPLST_Source _desc1;
};

struct _TPrule_36
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_37
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_38
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_39
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATargcount;
int _ATaxiom;
DefTableKey _ATKey;
_TSPConLHS _desc1;
_TSPConAlt _desc2;
POSITION _AT_pos;
};

struct _TPrule_003
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_002
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_001
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_000
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

#undef _NODECOMMON
#endif
