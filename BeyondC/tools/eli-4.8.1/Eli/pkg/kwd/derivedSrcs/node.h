
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

typedef struct _TSnonLitDesc* _TSPnonLitDesc;
typedef struct _TSG1* _TSPG1;
typedef struct _TSspec* _TSPspec;
typedef struct _TSlibrRef* _TSPlibrRef;
typedef struct _TSoptProcessor* _TSPoptProcessor;
typedef struct _TSoptAuxScanner* _TSPoptAuxScanner;
typedef struct _TSrest* _TSPrest;
typedef struct _TPrule_1* _TPPrule_1;
typedef struct _TPrule_2* _TPPrule_2;
typedef struct _TPrule_3* _TPPrule_3;
typedef struct _TPrule_4* _TPPrule_4;
typedef struct _TPrule_12* _TPPrule_12;
typedef struct _TPrule_11* _TPPrule_11;
typedef struct _TPrule_10* _TPPrule_10;
typedef struct _TPrule_9* _TPPrule_9;
typedef struct _TPrule_8* _TPPrule_8;
typedef struct _TPrule_7* _TPPrule_7;
typedef struct _TPrule_6* _TPPrule_6;
typedef struct _TPrule_5* _TPPrule_5;

struct _TSnonLitDesc
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

struct _TSspec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSlibrRef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSoptProcessor
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSoptAuxScanner
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSrest
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
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
_TSPlibrRef _desc1;
_TSPoptAuxScanner _desc2;
_TSPoptProcessor _desc3;
POSITION _AT_pos;
};

struct _TPrule_4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPoptAuxScanner _desc1;
_TSPoptProcessor _desc2;
int _ATTERM_1;
};

struct _TPrule_12
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG1 _desc1;
};

struct _TPrule_11
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_10
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
};

struct _TPrule_8
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPrest _desc1;
};

struct _TPrule_7
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPrest _desc1;
};

struct _TPrule_6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPnonLitDesc _desc1;
};

struct _TPrule_5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG1 _desc1;
_TSPnonLitDesc _desc2;
};

#undef _NODECOMMON
#endif
