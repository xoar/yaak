
/* encoding of tree node types and symbols */

#ifndef NODECODE_H
#define NODECODE_H

extern int LHSMAP[];

#define IsSymb(_n,_c) (LHSMAP[(_n)->_prod] == (_c))

#define SYMBG2 0
#define SYMBG1 1
#define SYMBPropertyValueList 2
#define SYMBPropertyValue 3
#define SYMBKnownKey 4
#define SYMBPropertyValues 5
#define SYMBFileDecl 6
#define SYMBParameterTypeDecl 7
#define SYMBParameterTypeList 8
#define SYMBModifier 9
#define SYMBParameterDecl 10
#define SYMBOperationNameList 11
#define SYMBType 12
#define SYMBPropertyNameList 13
#define SYMBPropertyDecl 14
#define SYMBOperationNameDecl 15
#define SYMBParameterList 16
#define SYMBTypeSpecifier 17
#define SYMBOperationList 18
#define SYMBOperationDecl 19
#define SYMBPropertyNameDecl 20
#define SYMBTypeIdent 21
#define SYMBLibraryList 22
#define SYMBRange 23
#define SYMBSource 24
#define RULErule_001 0
#define RULErule_002 1
#define RULErule_003 2
#define RULErule_004 3
#define RULErule_016 4
#define RULELibrarySpec 5
#define RULETypeName 6
#define RULEPropertyName 7
#define RULEOperationSpec 8
#define RULEGenericType 9
#define RULEDefinedType 10
#define RULEPropertySpec 11
#define RULETypeNoOp 12
#define RULETypeWithOp 13
#define RULEMultipleParameters 14
#define RULESingleParameter 15
#define RULEParameterSpec 16
#define RULEEmptyModifier 17
#define RULEVoidModifier 18
#define RULESimpleModifier 19
#define RULEExtendedModifier 20
#define RULEMultipleParameterTypes 21
#define RULESingleParameterType 22
#define RULEParameterTypeSpec 23
#define RULEIdentParameterTS 24
#define RULEFileSpec 25
#define RULErule_000 26
#define RULErule_011 27
#define RULErule_012 28
#define RULErule_013 29
#define RULErule_014 30
#define RULErule_015 31
#define RULErule_2 32
#define RULErule_005 33
#define RULErule_006 34
#define RULErule_007 35
#define RULErule_008 36
#define RULErule_1 37
#define RULEAxiom 38
#define RULEOperationName 39
#define RULErule_009 40
#define RULErule_010 41
#endif
