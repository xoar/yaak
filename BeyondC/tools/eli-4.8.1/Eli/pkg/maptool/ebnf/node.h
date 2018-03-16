
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

typedef struct _TSLST_EBNF* _TSPLST_EBNF;
typedef struct _TSAtomic* _TSPAtomic;
typedef struct _TSSymbol* _TSPSymbol;
typedef struct _TSExpression* _TSPExpression;
typedef struct _TSRule* _TSPRule;
typedef struct _TSEBNF* _TSPEBNF;
typedef struct _TPLST_Rulerule_16* _TPPLST_Rulerule_16;
typedef struct _TPLST_0rule_16* _TPPLST_0rule_16;
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

struct _TSLST_EBNF
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSAtomic
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSSymbol
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

struct _TSRule
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSEBNF
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPLST_Rulerule_16
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRule _desc1;
_TSPLST_EBNF _desc2;
};

struct _TPLST_0rule_16
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
int _ATTERM_1;
};

struct _TPrule_2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymbol _desc1;
};

struct _TPrule_4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymbol _desc1;
};

struct _TPrule_5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymbol _desc1;
};

struct _TPrule_6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSymbol _desc1;
};

struct _TPrule_7
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPAtomic _desc1;
};

struct _TPrule_8
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_9
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpression _desc1;
_TSPSymbol _desc2;
};

struct _TPrule_10
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpression _desc1;
};

struct _TPrule_11
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpression _desc1;
};

struct _TPrule_12
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpression _desc1;
_TSPExpression _desc2;
};

struct _TPrule_13
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpression _desc1;
};

struct _TPrule_14
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpression _desc1;
_TSPExpression _desc2;
};

struct _TPrule_15
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPExpression _desc1;
int _ATTERM_1;
};

struct _TPrule_16
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLST_EBNF _desc1;
};

#undef _NODECOMMON
#endif
