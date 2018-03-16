
/* interface of tree construction functions */

#ifndef TREECON_H
#define TREECON_H
#include "eliproto.h"

#include "err.h"

#include "nodeptr.h"

#include "HEAD.h"


extern void InitTree ELI_ARG((void));

extern void FreeTree ELI_ARG((void));

extern NODEPTR MkG2 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG1 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPropertyValueList ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPropertyValue ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkKnownKey ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPropertyValues ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkFileDecl ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkParameterTypeDecl ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkParameterTypeList ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkModifier ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkParameterDecl ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOperationNameList ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkType ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPropertyNameList ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPropertyDecl ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOperationNameDecl ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkParameterList ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTypeSpecifier ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOperationList ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOperationDecl ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPropertyNameDecl ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTypeIdent ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkLibraryList ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRange ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkSource ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrule_1 ELI_ARG((POSITION *_coordref, int _TERM1, int _TERM2));
extern NODEPTR Mkrule_2 ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1));
extern NODEPTR Mkrule_016 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_015 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_014 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_013 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_012 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_011 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_010 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_009 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_008 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_007 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_006 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_005 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_004 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_003 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_002 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_001 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_000 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkFileSpec ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkIdentParameterTS ELI_ARG((POSITION *_coordref, NODEPTR _desc1, int _TERM1, NODEPTR _desc2));
extern NODEPTR MkParameterTypeSpec ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkSingleParameterType ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkMultipleParameterTypes ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkExtendedModifier ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkSimpleModifier ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkVoidModifier ELI_ARG((POSITION *_coordref));
extern NODEPTR MkEmptyModifier ELI_ARG((POSITION *_coordref));
extern NODEPTR MkParameterSpec ELI_ARG((POSITION *_coordref, NODEPTR _desc1, int _TERM1, NODEPTR _desc2));
extern NODEPTR MkSingleParameter ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkMultipleParameters ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkTypeWithOp ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkTypeNoOp ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkPropertySpec ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkDefinedType ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkGenericType ELI_ARG((POSITION *_coordref));
extern NODEPTR MkOperationName ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkOperationSpec ELI_ARG((POSITION *_coordref, NODEPTR _desc1, int _TERM1, NODEPTR _desc2, int _TERM2));
extern NODEPTR MkPropertyName ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkTypeName ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkLibrarySpec ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkAxiom ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
#define MkString(pos,val) (val)
#define MkText(pos,val) (val)
#define MkIdentifier(pos,val) (val)
#endif
