
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

typedef struct _TSBackendOpt* _TSPBackendOpt;
typedef struct _TSNamesList* _TSPNamesList;
typedef struct _TSAttrNames* _TSPAttrNames;
typedef struct _TSAttrList* _TSPAttrList;
typedef struct _TSAttrType* _TSPAttrType;
typedef struct _TSOptimOpt* _TSPOptimOpt;
typedef struct _TSAttrSpec* _TSPAttrSpec;
typedef struct _TSArrangeType* _TSPArrangeType;
typedef struct _TSOrderOpt* _TSPOrderOpt;
typedef struct _TSExpandOpt* _TSPExpandOpt;
typedef struct _TSBackendOpts* _TSPBackendOpts;
typedef struct _TSOptimOpts* _TSPOptimOpts;
typedef struct _TSOrderOpts* _TSPOrderOpts;
typedef struct _TSExpandOpts* _TSPExpandOpts;
typedef struct _TSIdentList* _TSPIdentList;
typedef struct _TSOption* _TSPOption;
typedef struct _TSOptions* _TSPOptions;
typedef struct _TSStart* _TSPStart;
typedef struct _TPBACKEND2* _TPPBACKEND2;
typedef struct _TPBACKEND1* _TPPBACKEND1;
typedef struct _TPNAMESL2* _TPPNAMESL2;
typedef struct _TPNAMESL1* _TPPNAMESL1;
typedef struct _TPATTRNAMES* _TPPATTRNAMES;
typedef struct _TPATTRS2* _TPPATTRS2;
typedef struct _TPATTRS1* _TPPATTRS1;
typedef struct _TPATTRTYPE2* _TPPATTRTYPE2;
typedef struct _TPATTRTYPE1* _TPPATTRTYPE1;
typedef struct _TPOPTIM3* _TPPOPTIM3;
typedef struct _TPOPTIM2* _TPPOPTIM2;
typedef struct _TPOPTIM1* _TPPOPTIM1;
typedef struct _TPATTR1* _TPPATTR1;
typedef struct _TPARRANGE3* _TPPARRANGE3;
typedef struct _TPARRANGE2* _TPPARRANGE2;
typedef struct _TPARRANGE4* _TPPARRANGE4;
typedef struct _TPARRANGE1* _TPPARRANGE1;
typedef struct _TPORDER4* _TPPORDER4;
typedef struct _TPORDER3* _TPPORDER3;
typedef struct _TPORDER2* _TPPORDER2;
typedef struct _TPORDER1* _TPPORDER1;
typedef struct _TPEXPAND2* _TPPEXPAND2;
typedef struct _TPEXPAND3* _TPPEXPAND3;
typedef struct _TPEXPAND1* _TPPEXPAND1;
typedef struct _TPBACKS2* _TPPBACKS2;
typedef struct _TPBACKS1* _TPPBACKS1;
typedef struct _TPOPTIMS2* _TPPOPTIMS2;
typedef struct _TPOPTIMS1* _TPPOPTIMS1;
typedef struct _TPORDERS2* _TPPORDERS2;
typedef struct _TPORDERS1* _TPPORDERS1;
typedef struct _TPEXPANDS2* _TPPEXPANDS2;
typedef struct _TPEXPANDS1* _TPPEXPANDS1;
typedef struct _TPIDENTS2* _TPPIDENTS2;
typedef struct _TPIDENTS1* _TPPIDENTS1;
typedef struct _TPOPTBACK* _TPPOPTBACK;
typedef struct _TPOPTOPT* _TPPOPTOPT;
typedef struct _TPOPTORD* _TPPOPTORD;
typedef struct _TPOPTEXP* _TPPOPTEXP;
typedef struct _TPOPTIONS2* _TPPOPTIONS2;
typedef struct _TPOPTIONS1* _TPPOPTIONS1;
typedef struct _TPSTART* _TPPSTART;

struct _TSBackendOpt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSNamesList
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

struct _TSAttrList
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAttrType
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSOptimOpt
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

struct _TSArrangeType
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSOrderOpt
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

struct _TSBackendOpts
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSOptimOpts
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSOrderOpts
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSExpandOpts
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSIdentList
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSOption
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSOptions
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSStart
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPBACKEND2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
int _ATTERM_2;
};

struct _TPBACKEND1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPNAMESL2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPNAMESL1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPNamesList _desc1;
int _ATTERM_1;
};

struct _TPATTRNAMES
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPNamesList _desc1;
int _ATTERM_1;
};

struct _TPATTRS2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPATTRS1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrNames _desc1;
_TSPAttrList _desc2;
};

struct _TPATTRTYPE2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPATTRTYPE1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
int _ATTERM_2;
};

struct _TPOPTIM3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrType _desc1;
_TSPAttrList _desc2;
};

struct _TPOPTIM2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPOPTIM1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPATTR1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_2;
int _ATTERM_3;
int _ATTERM_1;
};

struct _TPARRANGE3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAttrSpec _desc1;
_TSPAttrSpec _desc2;
int _ATTERM_1;
};

struct _TPARRANGE2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
int _ATTERM_2;
int _ATTERM_3;
};

struct _TPARRANGE4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPARRANGE1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPORDER4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPArrangeType _desc1;
};

struct _TPORDER3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPORDER2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPIdentList _desc1;
int _ATTERM_1;
};

struct _TPORDER1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
int _ATTERM_2;
};

struct _TPEXPAND2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPEXPAND3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPEXPAND1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
int _ATTERM_2;
};

struct _TPBACKS2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPBackendOpt _desc1;
};

struct _TPBACKS1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPBackendOpt _desc1;
_TSPBackendOpts _desc2;
};

struct _TPOPTIMS2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOptimOpt _desc1;
};

struct _TPOPTIMS1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOptimOpt _desc1;
_TSPOptimOpts _desc2;
};

struct _TPORDERS2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOrderOpt _desc1;
};

struct _TPORDERS1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOrderOpt _desc1;
_TSPOrderOpts _desc2;
};

struct _TPEXPANDS2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpandOpt _desc1;
};

struct _TPEXPANDS1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpandOpt _desc1;
_TSPExpandOpts _desc2;
};

struct _TPIDENTS2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPIDENTS1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPIdentList _desc1;
int _ATTERM_1;
};

struct _TPOPTBACK
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPBackendOpts _desc1;
};

struct _TPOPTOPT
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOptimOpts _desc1;
};

struct _TPOPTORD
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOrderOpts _desc1;
};

struct _TPOPTEXP
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpandOpts _desc1;
};

struct _TPOPTIONS2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPOPTIONS1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOption _desc1;
_TSPOptions _desc2;
};

struct _TPSTART
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOptions _desc1;
};

#undef _NODECOMMON
#endif
