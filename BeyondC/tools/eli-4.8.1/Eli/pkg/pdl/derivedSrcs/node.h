
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

typedef struct _TSG2* _TSPG2;
typedef struct _TSG1* _TSPG1;
typedef struct _TSPropertyValueList* _TSPPropertyValueList;
typedef struct _TSPropertyValue* _TSPPropertyValue;
typedef struct _TSKnownKey* _TSPKnownKey;
typedef struct _TSPropertyValues* _TSPPropertyValues;
typedef struct _TSFileDecl* _TSPFileDecl;
typedef struct _TSParameterTypeDecl* _TSPParameterTypeDecl;
typedef struct _TSParameterTypeList* _TSPParameterTypeList;
typedef struct _TSModifier* _TSPModifier;
typedef struct _TSParameterDecl* _TSPParameterDecl;
typedef struct _TSOperationNameList* _TSPOperationNameList;
typedef struct _TSType* _TSPType;
typedef struct _TSPropertyNameList* _TSPPropertyNameList;
typedef struct _TSPropertyDecl* _TSPPropertyDecl;
typedef struct _TSOperationNameDecl* _TSPOperationNameDecl;
typedef struct _TSParameterList* _TSPParameterList;
typedef struct _TSTypeSpecifier* _TSPTypeSpecifier;
typedef struct _TSOperationList* _TSPOperationList;
typedef struct _TSOperationDecl* _TSPOperationDecl;
typedef struct _TSPropertyNameDecl* _TSPPropertyNameDecl;
typedef struct _TSTypeIdent* _TSPTypeIdent;
typedef struct _TSLibraryList* _TSPLibraryList;
typedef struct _TSRange* _TSPRange;
typedef struct _TSSource* _TSPSource;
typedef struct _TPrule_1* _TPPrule_1;
typedef struct _TPrule_2* _TPPrule_2;
typedef struct _TPrule_016* _TPPrule_016;
typedef struct _TPrule_015* _TPPrule_015;
typedef struct _TPrule_014* _TPPrule_014;
typedef struct _TPrule_013* _TPPrule_013;
typedef struct _TPrule_012* _TPPrule_012;
typedef struct _TPrule_011* _TPPrule_011;
typedef struct _TPrule_010* _TPPrule_010;
typedef struct _TPrule_009* _TPPrule_009;
typedef struct _TPrule_008* _TPPrule_008;
typedef struct _TPrule_007* _TPPrule_007;
typedef struct _TPrule_006* _TPPrule_006;
typedef struct _TPrule_005* _TPPrule_005;
typedef struct _TPrule_004* _TPPrule_004;
typedef struct _TPrule_003* _TPPrule_003;
typedef struct _TPrule_002* _TPPrule_002;
typedef struct _TPrule_001* _TPPrule_001;
typedef struct _TPrule_000* _TPPrule_000;
typedef struct _TPFileSpec* _TPPFileSpec;
typedef struct _TPIdentParameterTS* _TPPIdentParameterTS;
typedef struct _TPParameterTypeSpec* _TPPParameterTypeSpec;
typedef struct _TPSingleParameterType* _TPPSingleParameterType;
typedef struct _TPMultipleParameterTypes* _TPPMultipleParameterTypes;
typedef struct _TPExtendedModifier* _TPPExtendedModifier;
typedef struct _TPSimpleModifier* _TPPSimpleModifier;
typedef struct _TPVoidModifier* _TPPVoidModifier;
typedef struct _TPEmptyModifier* _TPPEmptyModifier;
typedef struct _TPParameterSpec* _TPPParameterSpec;
typedef struct _TPSingleParameter* _TPPSingleParameter;
typedef struct _TPMultipleParameters* _TPPMultipleParameters;
typedef struct _TPTypeWithOp* _TPPTypeWithOp;
typedef struct _TPTypeNoOp* _TPPTypeNoOp;
typedef struct _TPPropertySpec* _TPPPropertySpec;
typedef struct _TPDefinedType* _TPPDefinedType;
typedef struct _TPGenericType* _TPPGenericType;
typedef struct _TPOperationName* _TPPOperationName;
typedef struct _TPOperationSpec* _TPPOperationSpec;
typedef struct _TPPropertyName* _TPPPropertyName;
typedef struct _TPTypeName* _TPPTypeName;
typedef struct _TPLibrarySpec* _TPPLibrarySpec;
typedef struct _TPAxiom* _TPPAxiom;

struct _TSG2
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
int _ATElementNum_post;
};

struct _TSPropertyValueList
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSPropertyValue
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKnownKeyKey;
};

struct _TSKnownKey
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKnownKeyKey;
};

struct _TSPropertyValues
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATKnownKeyEnv;
};

struct _TSFileDecl
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSParameterTypeDecl
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSParameterTypeList
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSModifier
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSParameterDecl
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSOperationNameList
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSType
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSPropertyNameList
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSPropertyDecl
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATtype;
PTGNode _ATtypeid;
funclist _ATfunctions;
DefTableKey _ATTypeKey;
};

struct _TSOperationNameDecl
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSParameterList
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSTypeSpecifier
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATsym;
DefTableKey _ATkey;
};

struct _TSOperationList
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSOperationDecl
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATkey;
};

struct _TSPropertyNameDecl
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATkey;
};

struct _TSTypeIdent
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATsym;
DefTableKey _ATkey;
};

struct _TSLibraryList
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATopenv;
};

struct _TSRange
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSSource
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATKnownKeyEnv;
Environment _ATopenv;
Environment _ATenv;
};

struct _TPrule_1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKnownKeyKey;
POSITION _AT_pos;
int _ATTERM_1;
int _ATTERM_2;
};

struct _TPrule_2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKnownKeyKey;
_TSPPropertyValueList _desc1;
int _ATTERM_1;
};

struct _TPrule_016
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG1 _desc1;
};

struct _TPrule_015
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATKnownKeyEnv;
_TSPG2 _desc1;
};

struct _TPrule_014
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPropertyValues _desc1;
};

struct _TPrule_013
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_012
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPropertyNameList _desc1;
_TSPPropertyNameDecl _desc2;
};

struct _TPrule_011
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPropertyNameDecl _desc1;
};

struct _TPrule_010
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOperationNameList _desc1;
_TSPOperationNameDecl _desc2;
};

struct _TPrule_009
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOperationNameDecl _desc1;
};

struct _TPrule_008
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOperationList _desc1;
_TSPOperationDecl _desc2;
};

struct _TPrule_007
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPOperationDecl _desc1;
};

struct _TPrule_006
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPropertyValue _desc1;
};

struct _TPrule_005
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG2 _desc1;
_TSPPropertyValue _desc2;
};

struct _TPrule_004
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATElementNum_post;
_TSPG1 _desc1;
_TSPPropertyDecl _desc2;
};

struct _TPrule_003
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATElementNum_post;
_TSPG1 _desc1;
_TSPOperationDecl _desc2;
};

struct _TPrule_002
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATElementNum_post;
_TSPG1 _desc1;
_TSPFileDecl _desc2;
};

struct _TPrule_001
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATElementNum_post;
};

struct _TPrule_000
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPKnownKey _desc1;
};

struct _TPFileSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPIdentParameterTS
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTypeSpecifier _desc1;
_TSPModifier _desc2;
int _ATTERM_1;
};

struct _TPParameterTypeSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTypeSpecifier _desc1;
_TSPModifier _desc2;
};

struct _TPSingleParameterType
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPParameterTypeDecl _desc1;
};

struct _TPMultipleParameterTypes
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPParameterTypeList _desc1;
_TSPParameterTypeDecl _desc2;
};

struct _TPExtendedModifier
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPParameterTypeList _desc1;
};

struct _TPSimpleModifier
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPParameterTypeList _desc1;
};

struct _TPVoidModifier
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPEmptyModifier
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPParameterSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTypeSpecifier _desc1;
_TSPModifier _desc2;
int _ATTERM_1;
};

struct _TPSingleParameter
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPParameterDecl _desc1;
};

struct _TPMultipleParameters
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPParameterList _desc1;
_TSPParameterDecl _desc2;
};

struct _TPTypeWithOp
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTypeSpecifier _desc1;
_TSPOperationNameList _desc2;
};

struct _TPTypeNoOp
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTypeSpecifier _desc1;
};

struct _TPPropertySpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATtype;
PTGNode _ATtypeid;
funclist _ATfunctions;
DefTableKey _ATTypeKey;
_TSPPropertyNameList _desc1;
_TSPType _desc2;
POSITION _AT_pos;
};

struct _TPDefinedType
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATsym;
DefTableKey _ATkey;
_TSPTypeIdent _desc1;
};

struct _TPGenericType
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATsym;
DefTableKey _ATkey;
};

struct _TPOperationName
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPOperationSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATkey;
_TSPTypeSpecifier _desc1;
_TSPParameterList _desc2;
POSITION _AT_pos;
int _ATTERM_1;
int _ATTERM_2;
};

struct _TPPropertyName
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATkey;
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPTypeName
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATsym;
DefTableKey _ATkey;
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPLibrarySpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATopenv;
_TSPOperationList _desc1;
};

struct _TPAxiom
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATKnownKeyEnv;
Environment _ATopenv;
Environment _ATenv;
_TSPRange _desc1;
_TSPLibraryList _desc2;
};

#undef _NODECOMMON
#endif
