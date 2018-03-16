
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

typedef struct _TSErrorOpt* _TSPErrorOpt;
typedef struct _TSCodeOpt* _TSPCodeOpt;
typedef struct _TSStackOpt* _TSPStackOpt;
typedef struct _TSMode* _TSPMode;
typedef struct _TSOnOff* _TSPOnOff;
typedef struct _TSDirect* _TSPDirect;
typedef struct _TSTable* _TSPTable;
typedef struct _TSFrontend* _TSPFrontend;
typedef struct _TSOption* _TSPOption;
typedef struct _TSStart* _TSPStart;
typedef struct _TPSW2* _TPPSW2;
typedef struct _TPSW1* _TPPSW1;
typedef struct _TPDE3* _TPPDE3;
typedef struct _TPDE2* _TPPDE2;
typedef struct _TPDE1* _TPPDE1;
typedef struct _TPDC11* _TPPDC11;
typedef struct _TPDC10* _TPPDC10;
typedef struct _TPDC9* _TPPDC9;
typedef struct _TPDC8* _TPPDC8;
typedef struct _TPDC7* _TPPDC7;
typedef struct _TPDC6* _TPPDC6;
typedef struct _TPDC5* _TPPDC5;
typedef struct _TPDC4* _TPPDC4;
typedef struct _TPDC3* _TPPDC3;
typedef struct _TPDC2* _TPPDC2;
typedef struct _TPDC1* _TPPDC1;
typedef struct _TPDS6* _TPPDS6;
typedef struct _TPDS5* _TPPDS5;
typedef struct _TPDS4* _TPPDS4;
typedef struct _TPDS3* _TPPDS3;
typedef struct _TPDS2* _TPPDS2;
typedef struct _TPDS1* _TPPDS1;
typedef struct _TPD3* _TPPD3;
typedef struct _TPD2* _TPPD2;
typedef struct _TPD1* _TPPD1;
typedef struct _TPM8* _TPPM8;
typedef struct _TPM7* _TPPM7;
typedef struct _TPM6* _TPPM6;
typedef struct _TPM5* _TPPM5;
typedef struct _TPM4* _TPPM4;
typedef struct _TPM3* _TPPM3;
typedef struct _TPM2* _TPPM2;
typedef struct _TPM1* _TPPM1;
typedef struct _TPT3* _TPPT3;
typedef struct _TPT2* _TPPT2;
typedef struct _TPT1* _TPPT1;
typedef struct _TPF3* _TPPF3;
typedef struct _TPF2* _TPPF2;
typedef struct _TPF1* _TPPF1;
typedef struct _TPOpt5* _TPPOpt5;
typedef struct _TPOpt4* _TPPOpt4;
typedef struct _TPOpt3* _TPPOpt3;
typedef struct _TPOpt2* _TPPOpt2;
typedef struct _TPOpt1* _TPPOpt1;
typedef struct _TPRoot* _TPPRoot;

struct _TSErrorOpt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSCodeOpt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSStackOpt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSMode
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSOnOff
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSDirect
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSTable
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSFrontend
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

struct _TSStart
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPSW2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPSW1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPDE3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPDE2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPDE1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPDC11
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPDC10
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPDC9
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPDC8
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPDC7
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPDC6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPDC5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPDC4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPDC3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPDC2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPDC1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPDS6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPDS5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPDS4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPDS3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPDS2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPDS1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPD3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPErrorOpt _desc1;
};

struct _TPD2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPCodeOpt _desc1;
};

struct _TPD1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPStackOpt _desc1;
};

struct _TPM8
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPM7
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPM6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPM5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPM4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPM3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPM2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPM1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPT3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPMode _desc1;
};

struct _TPT2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPMode _desc1;
};

struct _TPT1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPF3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPF2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPF1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOnOff _desc1;
};

struct _TPOpt5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPOpt4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDirect _desc1;
POSITION _AT_pos;
};

struct _TPOpt3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTable _desc1;
POSITION _AT_pos;
};

struct _TPOpt2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFrontend _desc1;
POSITION _AT_pos;
};

struct _TPOpt1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOption _desc1;
_TSPOption _desc2;
};

struct _TPRoot
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOption _desc1;
POSITION _AT_pos;
};

#undef _NODECOMMON
#endif
