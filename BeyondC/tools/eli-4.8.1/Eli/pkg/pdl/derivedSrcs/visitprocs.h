
#ifndef _VISITPROCS_H
#define _VISITPROCS_H

#include "HEAD.h"
#include "node.h"
#include "treecon.h"

#include "eliproto.h"


extern void LIGA_ATTREVAL ELI_ARG((NODEPTR));
extern void _VS0Empty ELI_ARG((NODEPTR _currn));
extern void _VS1rule_1 ELI_ARG((_TPPrule_1 _currn));
extern void _VS2rule_1 ELI_ARG((_TPPrule_1 _currn));
extern void _VS1rule_2 ELI_ARG((_TPPrule_2 _currn));
extern void _VS2rule_2 ELI_ARG((_TPPrule_2 _currn));
extern void _VS3rule_2 ELI_ARG((_TPPrule_2 _currn));
extern void _VS1rule_016 ELI_ARG((_TPPrule_016 _currn));
extern void _VS2rule_016 ELI_ARG((_TPPrule_016 _currn));
extern void _VS3rule_016 ELI_ARG((_TPPrule_016 _currn));
extern void _VS4rule_016 ELI_ARG((_TPPrule_016 _currn));
extern void _VS5rule_016 ELI_ARG((_TPPrule_016 _currn));
extern void _VS6rule_016 ELI_ARG((_TPPrule_016 _currn));
extern void _VS1rule_015 ELI_ARG((_TPPrule_015 _currn));
extern void _VS2rule_015 ELI_ARG((_TPPrule_015 _currn));
extern void _VS3rule_015 ELI_ARG((_TPPrule_015 _currn));
extern void _VS1rule_014 ELI_ARG((_TPPrule_014 _currn));
extern void _VS2rule_014 ELI_ARG((_TPPrule_014 _currn));
extern void _VS3rule_014 ELI_ARG((_TPPrule_014 _currn));
#define _VS1rule_013 _VS0Empty

extern void _VS2rule_013 ELI_ARG((_TPPrule_013 _currn));
#define _VS3rule_013 _VS0Empty

extern void _VS1rule_012 ELI_ARG((_TPPrule_012 _currn));
extern void _VS2rule_012 ELI_ARG((_TPPrule_012 _currn));
extern void _VS3rule_012 ELI_ARG((_TPPrule_012 _currn));
#define _VS1rule_011 _VS1rule_016

extern void _VS2rule_011 ELI_ARG((_TPPrule_011 _currn));
extern void _VS3rule_011 ELI_ARG((_TPPrule_011 _currn));
#define _VS1rule_010 _VS1rule_012

#define _VS1rule_009 _VS1rule_016

extern void _VS1rule_008 ELI_ARG((_TPPrule_008 _currn));
extern void _VS2rule_008 ELI_ARG((_TPPrule_008 _currn));
extern void _VS1rule_007 ELI_ARG((_TPPrule_007 _currn));
#define _VS2rule_007 _VS3rule_014

extern void _VS1rule_006 ELI_ARG((_TPPrule_006 _currn));
extern void _VS2rule_006 ELI_ARG((_TPPrule_006 _currn));
extern void _VS1rule_005 ELI_ARG((_TPPrule_005 _currn));
extern void _VS2rule_005 ELI_ARG((_TPPrule_005 _currn));
extern void _VS1rule_004 ELI_ARG((_TPPrule_004 _currn));
extern void _VS2rule_004 ELI_ARG((_TPPrule_004 _currn));
extern void _VS3rule_004 ELI_ARG((_TPPrule_004 _currn));
extern void _VS4rule_004 ELI_ARG((_TPPrule_004 _currn));
extern void _VS5rule_004 ELI_ARG((_TPPrule_004 _currn));
extern void _VS6rule_004 ELI_ARG((_TPPrule_004 _currn));
extern void _VS1rule_003 ELI_ARG((_TPPrule_003 _currn));
extern void _VS2rule_003 ELI_ARG((_TPPrule_003 _currn));
extern void _VS3rule_003 ELI_ARG((_TPPrule_003 _currn));
extern void _VS4rule_003 ELI_ARG((_TPPrule_003 _currn));
extern void _VS5rule_003 ELI_ARG((_TPPrule_003 _currn));
extern void _VS6rule_003 ELI_ARG((_TPPrule_003 _currn));
extern void _VS1rule_002 ELI_ARG((_TPPrule_002 _currn));
extern void _VS2rule_002 ELI_ARG((_TPPrule_002 _currn));
extern void _VS3rule_002 ELI_ARG((_TPPrule_002 _currn));
extern void _VS4rule_002 ELI_ARG((_TPPrule_002 _currn));
extern void _VS5rule_002 ELI_ARG((_TPPrule_002 _currn));
extern void _VS6rule_002 ELI_ARG((_TPPrule_002 _currn));
#define _VS1rule_001 _VS0Empty

#define _VS2rule_001 _VS0Empty

extern void _VS3rule_001 ELI_ARG((_TPPrule_001 _currn));
extern void _VS4rule_001 ELI_ARG((_TPPrule_001 _currn));
extern void _VS5rule_001 ELI_ARG((_TPPrule_001 _currn));
extern void _VS6rule_001 ELI_ARG((_TPPrule_001 _currn));
extern void _VS1rule_000 ELI_ARG((_TPPrule_000 _currn));
extern void _VS2rule_000 ELI_ARG((_TPPrule_000 _currn));
extern void _VS3rule_000 ELI_ARG((_TPPrule_000 _currn));
extern void _VS1FileSpec ELI_ARG((_TPPFileSpec _currn));
extern void _VS2FileSpec ELI_ARG((_TPPFileSpec _currn));
extern void _VS3FileSpec ELI_ARG((_TPPFileSpec _currn));
extern void _VS1IdentParameterTS ELI_ARG((_TPPIdentParameterTS _currn));
extern void _VS2IdentParameterTS ELI_ARG((_TPPIdentParameterTS _currn));
extern void _VS3IdentParameterTS ELI_ARG((_TPPIdentParameterTS _currn));
extern void _VS1ParameterTypeSpec ELI_ARG((_TPPParameterTypeSpec _currn));
extern void _VS2ParameterTypeSpec ELI_ARG((_TPPParameterTypeSpec _currn));
extern void _VS3ParameterTypeSpec ELI_ARG((_TPPParameterTypeSpec _currn));
extern void _VS1SingleParameterType ELI_ARG((_TPPSingleParameterType _currn,PTGNode* _AS0out));
extern void _VS2SingleParameterType ELI_ARG((_TPPSingleParameterType _currn,PTGNode* _AS0out));
extern void _VS3SingleParameterType ELI_ARG((_TPPSingleParameterType _currn,PTGNode* _AS0out));
extern void _VS1MultipleParameterTypes ELI_ARG((_TPPMultipleParameterTypes _currn,PTGNode* _AS0out));
extern void _VS2MultipleParameterTypes ELI_ARG((_TPPMultipleParameterTypes _currn,PTGNode* _AS0out));
extern void _VS3MultipleParameterTypes ELI_ARG((_TPPMultipleParameterTypes _currn,PTGNode* _AS0out));
extern void _VS1ExtendedModifier ELI_ARG((_TPPExtendedModifier _currn));
extern void _VS2ExtendedModifier ELI_ARG((_TPPExtendedModifier _currn));
extern void _VS3ExtendedModifier ELI_ARG((_TPPExtendedModifier _currn));
extern void _VS1SimpleModifier ELI_ARG((_TPPSimpleModifier _currn));
extern void _VS2SimpleModifier ELI_ARG((_TPPSimpleModifier _currn));
extern void _VS3SimpleModifier ELI_ARG((_TPPSimpleModifier _currn));
extern void _VS1VoidModifier ELI_ARG((_TPPVoidModifier _currn));
#define _VS2VoidModifier _VS0Empty

#define _VS3VoidModifier _VS0Empty

extern void _VS1EmptyModifier ELI_ARG((_TPPEmptyModifier _currn));
#define _VS2EmptyModifier _VS0Empty

#define _VS3EmptyModifier _VS0Empty

extern void _VS1ParameterSpec ELI_ARG((_TPPParameterSpec _currn));
extern void _VS2ParameterSpec ELI_ARG((_TPPParameterSpec _currn));
extern void _VS3ParameterSpec ELI_ARG((_TPPParameterSpec _currn));
extern void _VS1SingleParameter ELI_ARG((_TPPSingleParameter _currn));
#define _VS2SingleParameter _VS2rule_016

#define _VS3SingleParameter _VS3rule_014

extern void _VS1MultipleParameters ELI_ARG((_TPPMultipleParameters _currn));
extern void _VS2MultipleParameters ELI_ARG((_TPPMultipleParameters _currn));
extern void _VS3MultipleParameters ELI_ARG((_TPPMultipleParameters _currn));
extern void _VS1TypeWithOp ELI_ARG((_TPPTypeWithOp _currn));
extern void _VS2TypeWithOp ELI_ARG((_TPPTypeWithOp _currn));
extern void _VS3TypeWithOp ELI_ARG((_TPPTypeWithOp _currn));
extern void _VS1TypeNoOp ELI_ARG((_TPPTypeNoOp _currn));
extern void _VS2TypeNoOp ELI_ARG((_TPPTypeNoOp _currn));
extern void _VS3TypeNoOp ELI_ARG((_TPPTypeNoOp _currn));
extern void _VS1PropertySpec ELI_ARG((_TPPPropertySpec _currn));
extern void _VS2PropertySpec ELI_ARG((_TPPPropertySpec _currn));
extern void _VS3PropertySpec ELI_ARG((_TPPPropertySpec _currn));
extern void _VS1DefinedType ELI_ARG((_TPPDefinedType _currn,PTGNode* _AS0out));
extern void _VS2DefinedType ELI_ARG((_TPPDefinedType _currn,PTGNode* _AS0out));
extern void _VS3DefinedType ELI_ARG((_TPPDefinedType _currn,PTGNode* _AS0out));
extern void _VS1GenericType ELI_ARG((_TPPGenericType _currn,PTGNode* _AS0out));
extern void _VS2GenericType ELI_ARG((_TPPGenericType _currn,PTGNode* _AS0out));
extern void _VS3GenericType ELI_ARG((_TPPGenericType _currn,PTGNode* _AS0out));
extern void _VS1OperationName ELI_ARG((_TPPOperationName _currn));
extern void _VS1OperationSpec ELI_ARG((_TPPOperationSpec _currn));
extern void _VS2OperationSpec ELI_ARG((_TPPOperationSpec _currn));
extern void _VS3OperationSpec ELI_ARG((_TPPOperationSpec _currn));
extern void _VS1PropertyName ELI_ARG((_TPPPropertyName _currn));
extern void _VS2PropertyName ELI_ARG((_TPPPropertyName _currn));
extern void _VS3PropertyName ELI_ARG((_TPPPropertyName _currn));
extern void _VS1TypeName ELI_ARG((_TPPTypeName _currn));
extern void _VS2TypeName ELI_ARG((_TPPTypeName _currn));
extern void _VS3TypeName ELI_ARG((_TPPTypeName _currn));
extern void _VS1LibrarySpec ELI_ARG((_TPPLibrarySpec _currn));
extern void _VS2LibrarySpec ELI_ARG((_TPPLibrarySpec _currn));
extern void _VS3LibrarySpec ELI_ARG((_TPPLibrarySpec _currn));
extern void _VS1Axiom ELI_ARG((_TPPAxiom _currn));
#endif
