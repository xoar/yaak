
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

typedef struct _TSG3* _TSPG3;
typedef struct _TSG2* _TSPG2;
typedef struct _TSG1* _TSPG1;
typedef struct _TSG4* _TSPG4;
typedef struct _TSArgument* _TSPArgument;
typedef struct _TSOptional* _TSPOptional;
typedef struct _TSItem* _TSPItem;
typedef struct _TSCStringNode* _TSPCStringNode;
typedef struct _TSPTGSpec* _TSPPTGSpec;
typedef struct _TSPatternName* _TSPPatternName;
typedef struct _TSArguments* _TSPArguments;
typedef struct _TSFunctionName* _TSPFunctionName;
typedef struct _TSFunctionCall* _TSPFunctionCall;
typedef struct _TSPatternBody* _TSPPatternBody;
typedef struct _TSPatternSpec* _TSPPatternSpec;
typedef struct _TSType* _TSPType;
typedef struct _TSIndex* _TSPIndex;
typedef struct _TSInsertion* _TSPInsertion;
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

struct _TSG3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const4;
int _AT_const5;
int _AT_const6;
PTGNode _AT_const14;
PTGNode _AT_const21;
int _AT_const22;
};

struct _TSG2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const0;
int _AT_const3;
int _AT_const4;
int _AT_const5;
int _AT_const6;
PTGNode _AT_const14;
int _ATinsertionCount_post;
};

struct _TSG1
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

struct _TSArgument
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSOptional
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATisInOption;
};

struct _TSItem
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const0;
int _AT_const3;
int _AT_const4;
int _AT_const5;
int _AT_const6;
PTGNode _AT_const14;
};

struct _TSCStringNode
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSPTGSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATFctEnv;
Environment _ATEnv;
};

struct _TSPatternName
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKeyList _ATinsertPointChain_post;
int _ATinsertionCount_post;
PatElemList _ATpattern;
int _ATSym;
DefTableKey _ATKey;
};

struct _TSArguments
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSFunctionName
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATSym;
DefTableKey _ATKey;
};

struct _TSFunctionCall
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKeyList _ATtypes;
int _ATinFunctionCall;
};

struct _TSPatternBody
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
};

struct _TSPatternSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATisInOption;
int _AThasFreeSubtrees;
int _AThasFreeLeafs;
int _AThasInsertions;
int _ATisEmptyPattern;
DefTableKeyList _ATinsertKeyList;
int _ATinFunctionCall;
};

struct _TSType
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATtype;
};

struct _TSIndex
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATisIndexed;
};

struct _TSInsertion
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATindex;
};

struct _TPrule_1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATtype;
};

struct _TPrule_2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATtype;
};

struct _TPrule_3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATtype;
};

struct _TPrule_4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATtype;
};

struct _TPrule_5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATtype;
};

struct _TPrule_6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATtype;
};

struct _TPrule_7
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATtype;
};

struct _TPrule_8
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_9
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const0;
int _AT_const3;
int _AT_const4;
int _AT_const5;
int _AT_const6;
PTGNode _AT_const14;
_TSPCStringNode _desc1;
};

struct _TPrule_10
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATisInOption;
int _AThasFreeSubtrees;
int _AThasFreeLeafs;
int _AThasInsertions;
int _ATisEmptyPattern;
DefTableKeyList _ATinsertKeyList;
int _ATinFunctionCall;
_TSPPatternName _desc1;
_TSPPatternBody _desc2;
POSITION _AT_pos;
};

struct _TPrule_11
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATtype;
POSITION _AT_pos;
};

struct _TPrule_12
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKeyList _ATtypes;
int _ATinFunctionCall;
_TSPFunctionName _desc1;
_TSPArguments _desc2;
};

struct _TPrule_13
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATisIndexed;
};

struct _TPrule_14
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATisIndexed;
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
DefTableKey _ATKey;
int _ATindex;
_TSPIndex _desc1;
_TSPType _desc2;
POSITION _AT_pos;
};

struct _TPrule_34
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATtype;
};

struct _TPrule_33
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATFctEnv;
Environment _ATEnv;
_TSPG1 _desc1;
};

struct _TPrule_32
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKeyList _ATinsertPointChain_post;
int _ATinsertionCount_post;
PatElemList _ATpattern;
int _ATSym;
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_31
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
_TSPG2 _desc1;
};

struct _TPrule_30
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATisInOption;
_TSPG3 _desc1;
POSITION _AT_pos;
};

struct _TPrule_29
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const0;
int _AT_const3;
int _AT_const4;
int _AT_const5;
int _AT_const6;
PTGNode _AT_const14;
_TSPInsertion _desc1;
};

struct _TPrule_28
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const0;
int _AT_const3;
int _AT_const4;
int _AT_const5;
int _AT_const6;
PTGNode _AT_const14;
_TSPFunctionCall _desc1;
};

struct _TPrule_27
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG4 _desc1;
_TSPArgument _desc2;
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
int _AT_const4;
int _AT_const5;
int _AT_const6;
PTGNode _AT_const14;
PTGNode _AT_const21;
int _AT_const22;
_TSPItem _desc1;
};

struct _TPrule_24
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const4;
int _AT_const5;
int _AT_const6;
PTGNode _AT_const14;
PTGNode _AT_const21;
int _AT_const22;
_TSPG3 _desc1;
_TSPItem _desc2;
};

struct _TPrule_23
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const0;
int _AT_const3;
int _AT_const4;
int _AT_const5;
int _AT_const6;
PTGNode _AT_const14;
int _ATinsertionCount_post;
_TSPG2 _desc1;
_TSPOptional _desc2;
};

struct _TPrule_22
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const0;
int _AT_const3;
int _AT_const4;
int _AT_const5;
int _AT_const6;
PTGNode _AT_const14;
int _ATinsertionCount_post;
_TSPG2 _desc1;
_TSPItem _desc2;
};

struct _TPrule_21
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const0;
int _AT_const3;
int _AT_const4;
int _AT_const5;
int _AT_const6;
PTGNode _AT_const14;
int _ATinsertionCount_post;
};

struct _TPrule_20
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG1 _desc1;
_TSPPatternSpec _desc2;
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
int _ATSym;
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_17
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG4 _desc1;
};

struct _TPrule_16
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPInsertion _desc1;
};

#undef _NODECOMMON
#endif
