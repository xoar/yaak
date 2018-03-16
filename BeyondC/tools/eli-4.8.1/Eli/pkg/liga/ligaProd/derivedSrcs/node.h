
/* definition of tree node structure */

#ifndef NODE_H
#define NODE_H
#include "err.h"
#include "nodeptr.h" /* defines NODEPTR */
#include "HEAD.h"

#ifdef MONITOR
#define _NODECOMMON int _prod; POSITION _coord; int _uid;
#else
#define _NODECOMMON int _prod;
#endif
struct NODEPTR_struct {
        _NODECOMMON
#ifdef __cplusplus
        void* operator new(size_t size);
#endif
};

typedef struct _TSSpec* _TSPSpec;
typedef struct _TSShieldSyms* _TSPShieldSyms;
typedef struct _TSShieldSym* _TSPShieldSym;
typedef struct _TSShieldClause* _TSPShieldClause;
typedef struct _TSShield* _TSPShield;
typedef struct _TSSubtree* _TSPSubtree;
typedef struct _TSRemoteClause* _TSPRemoteClause;
typedef struct _TSRemoteAttr* _TSPRemoteAttr;
typedef struct _TSRemoteAttrs* _TSPRemoteAttrs;
typedef struct _TSParams* _TSPParams;
typedef struct _TSParam* _TSPParam;
typedef struct _TSInheritSym* _TSPInheritSym;
typedef struct _TSInheritSyms* _TSPInheritSyms;
typedef struct _TSG1* _TSPG1;
typedef struct _TSParamsOpt* _TSPParamsOpt;
typedef struct _TSExpression* _TSPExpression;
typedef struct _TSExpandOpt* _TSPExpandOpt;
typedef struct _TSDependence* _TSPDependence;
typedef struct _TSDepClause* _TSPDepClause;
typedef struct _TSDepAttrs* _TSPDepAttrs;
typedef struct _TSRhsAttrs* _TSPRhsAttrs;
typedef struct _TSRemoteExpression* _TSPRemoteExpression;
typedef struct _TSDepAttr* _TSPDepAttr;
typedef struct _TSPlainComp* _TSPPlainComp;
typedef struct _TSCompute* _TSPCompute;
typedef struct _TSComputation* _TSPComputation;
typedef struct _TSComputations* _TSPComputations;
typedef struct _TSChainSpec* _TSPChainSpec;
typedef struct _TSChainNames* _TSPChainNames;
typedef struct _TSChainName* _TSPChainName;
typedef struct _TSSymOcc* _TSPSymOcc;
typedef struct _TSAttrSpec* _TSPAttrSpec;
typedef struct _TSAttrNames* _TSPAttrNames;
typedef struct _TSAttrName* _TSPAttrName;
typedef struct _TSAttrDefs* _TSPAttrDefs;
typedef struct _TSAttrDefId* _TSPAttrDefId;
typedef struct _TSClass* _TSPClass;
typedef struct _TSAttrDefIds* _TSPAttrDefIds;
typedef struct _TSAttrDef* _TSPAttrDef;
typedef struct _TSLoop* _TSPLoop;
typedef struct _TSExpressionDep* _TSPExpressionDep;
typedef struct _TSDefAttr* _TSPDefAttr;
typedef struct _TSAttrComp* _TSPAttrComp;
typedef struct _TSAttrUseId* _TSPAttrUseId;
typedef struct _TSAttr* _TSPAttr;
typedef struct _TSAsgnTok* _TSPAsgnTok;
typedef struct _TSAlt* _TSPAlt;
typedef struct _TSSpecs* _TSPSpecs;
typedef struct _TSAlts* _TSPAlts;
typedef struct _TSSyntUnits* _TSPSyntUnits;
typedef struct _TSRuleSpecId* _TSPRuleSpecId;
typedef struct _TSRuleSpec* _TSPRuleSpec;
typedef struct _TSSyntUnit* _TSPSyntUnit;
typedef struct _TSSyntLit* _TSPSyntLit;
typedef struct _TSProduction* _TSPProduction;
typedef struct _TSCompPart* _TSPCompPart;
typedef struct _TSInheritOpt* _TSPInheritOpt;
typedef struct _TSAttrDefsOpt* _TSPAttrDefsOpt;
typedef struct _TSSymbolDefIds* _TSPSymbolDefIds;
typedef struct _TSSymClass* _TSPSymClass;
typedef struct _TSTermSpec* _TSPTermSpec;
typedef struct _TSSymCompSpec* _TSPSymCompSpec;
typedef struct _TSSymAttrSpec* _TSPSymAttrSpec;
typedef struct _TSIndex* _TSPIndex;
typedef struct _TSSymbolRef* _TSPSymbolRef;
typedef struct _TSAG* _TSPAG;
typedef struct _TSRuleId* _TSPRuleId;
typedef struct _TSTypeId* _TSPTypeId;
typedef struct _TSSyntId* _TSPSyntId;
typedef struct _TSSymbolId* _TSPSymbolId;
typedef struct _TSSymbolDefId* _TSPSymbolDefId;
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
typedef struct _TPrule_138* _TPPrule_138;
typedef struct _TPrule_137* _TPPrule_137;
typedef struct _TPrule_136* _TPPrule_136;
typedef struct _TPrule_135* _TPPrule_135;
typedef struct _TPrule_134* _TPPrule_134;
typedef struct _TPrule_133* _TPPrule_133;
typedef struct _TPrule_132* _TPPrule_132;
typedef struct _TPrule_131* _TPPrule_131;
typedef struct _TPrule_130* _TPPrule_130;
typedef struct _TPrule_129* _TPPrule_129;
typedef struct _TPrule_128* _TPPrule_128;
typedef struct _TPrule_127* _TPPrule_127;
typedef struct _TPrule_126* _TPPrule_126;
typedef struct _TPrule_125* _TPPrule_125;
typedef struct _TPrule_124* _TPPrule_124;
typedef struct _TPrule_123* _TPPrule_123;
typedef struct _TPrule_122* _TPPrule_122;
typedef struct _TPrule_121* _TPPrule_121;
typedef struct _TPrule_120* _TPPrule_120;
typedef struct _TPrule_119* _TPPrule_119;
typedef struct _TPrule_118* _TPPrule_118;
typedef struct _TPrule_117* _TPPrule_117;
typedef struct _TPrule_116* _TPPrule_116;
typedef struct _TPrule_115* _TPPrule_115;
typedef struct _TPrule_114* _TPPrule_114;
typedef struct _TPrule_113* _TPPrule_113;
typedef struct _TPrule_112* _TPPrule_112;
typedef struct _TPrule_111* _TPPrule_111;
typedef struct _TPrule_110* _TPPrule_110;
typedef struct _TPrule_109* _TPPrule_109;
typedef struct _TPrule_108* _TPPrule_108;
typedef struct _TPrule_107* _TPPrule_107;
typedef struct _TPrule_106* _TPPrule_106;
typedef struct _TPrule_105* _TPPrule_105;
typedef struct _TPrule_104* _TPPrule_104;
typedef struct _TPrule_103* _TPPrule_103;
typedef struct _TPrule_102* _TPPrule_102;
typedef struct _TPrule_101* _TPPrule_101;
typedef struct _TPrule_100* _TPPrule_100;
typedef struct _TPrule_99* _TPPrule_99;
typedef struct _TPrule_98* _TPPrule_98;
typedef struct _TPrule_97* _TPPrule_97;
typedef struct _TPrule_96* _TPPrule_96;
typedef struct _TPrule_95* _TPPrule_95;
typedef struct _TPrule_94* _TPPrule_94;
typedef struct _TPrule_93* _TPPrule_93;
typedef struct _TPrule_92* _TPPrule_92;
typedef struct _TPrule_91* _TPPrule_91;
typedef struct _TPrule_90* _TPPrule_90;
typedef struct _TPrule_89* _TPPrule_89;
typedef struct _TPrule_88* _TPPrule_88;
typedef struct _TPrule_87* _TPPrule_87;
typedef struct _TPrule_86* _TPPrule_86;
typedef struct _TPrule_85* _TPPrule_85;
typedef struct _TPrule_84* _TPPrule_84;
typedef struct _TPrule_83* _TPPrule_83;
typedef struct _TPrule_82* _TPPrule_82;
typedef struct _TPrule_81* _TPPrule_81;
typedef struct _TPrule_80* _TPPrule_80;
typedef struct _TPrule_79* _TPPrule_79;
typedef struct _TPrule_78* _TPPrule_78;
typedef struct _TPrule_77* _TPPrule_77;
typedef struct _TPrule_76* _TPPrule_76;
typedef struct _TPrule_75* _TPPrule_75;
typedef struct _TPrule_74* _TPPrule_74;
typedef struct _TPrule_73* _TPPrule_73;
typedef struct _TPrule_72* _TPPrule_72;
typedef struct _TPrule_71* _TPPrule_71;
typedef struct _TPrule_70* _TPPrule_70;
typedef struct _TPrule_69* _TPPrule_69;
typedef struct _TPrule_68* _TPPrule_68;
typedef struct _TPrule_67* _TPPrule_67;
typedef struct _TPrule_66* _TPPrule_66;
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
typedef struct _TPrule_30* _TPPrule_30;
typedef struct _TPrule_29* _TPPrule_29;
typedef struct _TPrule_28* _TPPrule_28;
typedef struct _TPrule_27* _TPPrule_27;
typedef struct _TPrule_26* _TPPrule_26;
typedef struct _TPrule_25* _TPPrule_25;
typedef struct _TPrule_24* _TPPrule_24;
typedef struct _TPrule_23* _TPPrule_23;
typedef struct _TPrule_22* _TPPrule_22;
typedef struct _TPrule_21* _TPPrule_21;
typedef struct _TPrule_20* _TPPrule_20;
typedef struct _TPrule_19* _TPPrule_19;
typedef struct _TPrule_18* _TPPrule_18;
typedef struct _TPrule_17* _TPPrule_17;
typedef struct _TPrule_16* _TPPrule_16;
typedef struct _TPrule_15* _TPPrule_15;
typedef struct _TPrule_14* _TPPrule_14;

struct _TSSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSShieldSyms
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSShieldSym
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSShieldClause
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSShield
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSSubtree
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRemoteClause
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRemoteAttr
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRemoteAttrs
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSParams
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSParam
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSInheritSym
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSInheritSyms
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

struct _TSParamsOpt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSExpression
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSExpandOpt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSDependence
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSDepClause
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSDepAttrs
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRhsAttrs
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRemoteExpression
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSDepAttr
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSPlainComp
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSCompute
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSComputation
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSComputations
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSChainSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSChainNames
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSChainName
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSSymOcc
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttrSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttrNames
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttrName
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttrDefs
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttrDefId
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSClass
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttrDefIds
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttrDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSLoop
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSExpressionDep
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSDefAttr
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttrComp
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttrUseId
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttr
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAsgnTok
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAlt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSSpecs
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAlts
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSSyntUnits
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRuleSpecId
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRuleSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
RuleProd _ATRuleInstance;
};

struct _TSSyntUnit
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSSyntLit
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSProduction
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSCompPart
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSInheritOpt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttrDefsOpt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSSymbolDefIds
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSSymClass
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSTermSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATIsCLASSSym;
int _ATIsTREESym;
};

struct _TSSymCompSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATIsCLASSSym;
int _ATIsTREESym;
};

struct _TSSymAttrSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATIsCLASSSym;
int _ATIsTREESym;
};

struct _TSIndex
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSSymbolRef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAG
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
};

struct _TSRuleId
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
};

struct _TSTypeId
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
};

struct _TSSyntId
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
};

struct _TSSymbolId
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
};

struct _TSSymbolDefId
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
};

struct _TPrule_1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSyntId _desc1;
_TSPAlts _desc2;
POSITION _AT_pos;
};

struct _TPrule_2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSyntId _desc1;
_TSPSyntUnits _desc2;
POSITION _AT_pos;
};

struct _TPrule_3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRuleId _desc1;
POSITION _AT_pos;
};

struct _TPrule_5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
RuleProd _ATRuleInstance;
_TSPRuleSpecId _desc1;
_TSPProduction _desc2;
_TSPCompPart _desc3;
POSITION _AT_pos;
};

struct _TPrule_6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSyntId _desc1;
POSITION _AT_pos;
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
int _ATIsCLASSSym;
int _ATIsTREESym;
_TSPSymbolDefIds _desc1;
_TSPTypeId _desc2;
POSITION _AT_pos;
};

struct _TPrule_9
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATIsCLASSSym;
int _ATIsTREESym;
_TSPSymClass _desc1;
_TSPSymbolDefId _desc2;
_TSPInheritOpt _desc3;
_TSPCompPart _desc4;
POSITION _AT_pos;
};

struct _TPrule_10
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATIsCLASSSym;
int _ATIsTREESym;
_TSPSymClass _desc1;
_TSPSymbolDefIds _desc2;
_TSPAttrDefsOpt _desc3;
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
};

struct _TPrule_13
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymbolId _desc1;
_TSPIndex _desc2;
};

struct _TPrule_138
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

struct _TPrule_137
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSyntLit _desc1;
};

struct _TPrule_136
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSyntId _desc1;
POSITION _AT_pos;
};

struct _TPrule_135
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSyntUnits _desc1;
_TSPSyntUnit _desc2;
};

struct _TPrule_134
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_133
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

struct _TPrule_132
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_131
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_130
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_129
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymbolId _desc1;
_TSPIndex _desc2;
POSITION _AT_pos;
};

struct _TPrule_128
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_127
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_126
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_125
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPIndex _desc1;
};

struct _TPrule_124
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

struct _TPrule_123
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG1 _desc1;
};

struct _TPrule_122
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

struct _TPrule_121
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymOcc _desc1;
};

struct _TPrule_120
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_119
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTermSpec _desc1;
};

struct _TPrule_118
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymCompSpec _desc1;
};

struct _TPrule_117
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymAttrSpec _desc1;
};

struct _TPrule_116
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSpecs _desc1;
_TSPSpec _desc2;
};

struct _TPrule_115
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_114
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRuleSpec _desc1;
};

struct _TPrule_113
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPChainSpec _desc1;
};

struct _TPrule_112
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrSpec _desc1;
};

struct _TPrule_111
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymbolId _desc1;
POSITION _AT_pos;
};

struct _TPrule_110
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPShieldSyms _desc1;
_TSPShieldSym _desc2;
};

struct _TPrule_109
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPShieldSym _desc1;
};

struct _TPrule_108
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPShieldClause _desc1;
};

struct _TPrule_107
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPShieldSyms _desc1;
};

struct _TPrule_106
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPShieldSym _desc1;
};

struct _TPrule_105
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_104
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_103
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

struct _TPrule_102
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_101
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSubtree _desc1;
_TSPRemoteClause _desc2;
_TSPShield _desc3;
_TSPExpandOpt _desc4;
};

struct _TPrule_100
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSubtree _desc1;
_TSPRemoteClause _desc2;
_TSPShield _desc3;
};

struct _TPrule_99
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRemoteClause _desc1;
};

struct _TPrule_98
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRemoteAttrs _desc1;
};

struct _TPrule_97
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRemoteAttr _desc1;
};

struct _TPrule_96
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymbolId _desc1;
_TSPAttrUseId _desc2;
POSITION _AT_pos;
};

struct _TPrule_95
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRemoteAttr _desc1;
_TSPRemoteAttrs _desc2;
};

struct _TPrule_94
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRemoteAttr _desc1;
};

struct _TPrule_93
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLoop _desc1;
};

struct _TPrule_92
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpressionDep _desc1;
};

struct _TPrule_91
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPParam _desc1;
_TSPParams _desc2;
};

struct _TPrule_90
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPParam _desc1;
};

struct _TPrule_89
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPParams _desc1;
};

struct _TPrule_88
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_87
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpressionDep _desc1;
};

struct _TPrule_86
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpressionDep _desc1;
_TSPAttr _desc2;
_TSPExpressionDep _desc3;
};

struct _TPrule_85
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymbolId _desc1;
POSITION _AT_pos;
};

struct _TPrule_84
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPInheritSyms _desc1;
_TSPInheritSym _desc2;
};

struct _TPrule_83
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPInheritSym _desc1;
};

struct _TPrule_82
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPInheritSyms _desc1;
};

struct _TPrule_81
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_80
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_79
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_78
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymbolDefId _desc1;
POSITION _AT_pos;
};

struct _TPrule_77
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG1 _desc1;
_TSPSymbolDefId _desc2;
POSITION _AT_pos;
};

struct _TPrule_76
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymbolRef _desc1;
};

struct _TPrule_75
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRhsAttrs _desc1;
};

struct _TPrule_74
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRemoteExpression _desc1;
};

struct _TPrule_73
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_72
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPParamsOpt _desc1;
};

struct _TPrule_71
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpression _desc1;
_TSPDepClause _desc2;
};

struct _TPrule_70
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpression _desc1;
};

struct _TPrule_69
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_68
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_67
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_66
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttr _desc1;
};

struct _TPrule_65
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTypeId _desc1;
POSITION _AT_pos;
};

struct _TPrule_64
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_63
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDepAttrs _desc1;
};

struct _TPrule_62
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDepAttr _desc1;
};

struct _TPrule_61
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDependence _desc1;
};

struct _TPrule_60
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDependence _desc1;
};

struct _TPrule_59
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDepAttr _desc1;
_TSPDepAttrs _desc2;
};

struct _TPrule_58
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDepAttr _desc1;
};

struct _TPrule_57
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRhsAttrs _desc1;
};

struct _TPrule_56
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRemoteExpression _desc1;
};

struct _TPrule_55
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttr _desc1;
};

struct _TPrule_54
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttr _desc1;
};

struct _TPrule_53
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPlainComp _desc1;
};

struct _TPrule_52
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrComp _desc1;
};

struct _TPrule_51
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPComputation _desc1;
_TSPComputations _desc2;
};

struct _TPrule_50
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_49
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPCompute _desc1;
};

struct _TPrule_48
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPCompute _desc1;
};

struct _TPrule_47
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPComputations _desc1;
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
};

struct _TPrule_42
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPChainNames _desc1;
_TSPTypeId _desc2;
POSITION _AT_pos;
};

struct _TPrule_41
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPChainNames _desc1;
_TSPChainName _desc2;
};

struct _TPrule_40
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPChainName _desc1;
};

struct _TPrule_39
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_38
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_37
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymOcc _desc1;
_TSPAttrUseId _desc2;
};

struct _TPrule_36
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrNames _desc1;
_TSPTypeId _desc2;
_TSPClass _desc3;
POSITION _AT_pos;
};

struct _TPrule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrNames _desc1;
_TSPAttrName _desc2;
};

struct _TPrule_34
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrName _desc1;
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
_TSPAttrDefs _desc1;
};

struct _TPrule_31
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_30
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrDefs _desc1;
_TSPAttrDef _desc2;
};

struct _TPrule_29
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrDef _desc1;
};

struct _TPrule_28
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrDefIds _desc1;
_TSPAttrDefId _desc2;
};

struct _TPrule_27
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrDefId _desc1;
};

struct _TPrule_26
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_25
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrDefIds _desc1;
_TSPTypeId _desc2;
_TSPClass _desc3;
POSITION _AT_pos;
};

struct _TPrule_24
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDefAttr _desc1;
_TSPLoop _desc2;
};

struct _TPrule_23
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDefAttr _desc1;
_TSPAsgnTok _desc2;
_TSPExpressionDep _desc3;
};

struct _TPrule_22
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDefAttr _desc1;
_TSPExpressionDep _desc2;
};

struct _TPrule_21
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrUseId _desc1;
};

struct _TPrule_20
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_19
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
_TSPSyntId _desc1;
POSITION _AT_pos;
};

struct _TPrule_17
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAlts _desc1;
_TSPAlt _desc2;
};

struct _TPrule_16
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAlt _desc1;
};

struct _TPrule_15
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
Environment _ATEnv;
_TSPSpecs _desc1;
};

#undef _NODECOMMON
#endif
