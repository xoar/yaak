

#define _TERMACT_rule_1 \
	_currn->_ATTERM_1=_TERM1; \
	_currn->_ATTERM_2=_TERM2; \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_rule_2 \
	_currn->_ATTERM_1=_TERM1;

#define _TERMACT_rule_016

#define _TERMACT_rule_015

#define _TERMACT_rule_014

#define _TERMACT_rule_013

#define _TERMACT_rule_012

#define _TERMACT_rule_011

#define _TERMACT_rule_010

#define _TERMACT_rule_009

#define _TERMACT_rule_008

#define _TERMACT_rule_007

#define _TERMACT_rule_006

#define _TERMACT_rule_005

#define _TERMACT_rule_004

#define _TERMACT_rule_003

#define _TERMACT_rule_002

#define _TERMACT_rule_001

#define _TERMACT_rule_000

#define _TERMACT_FileSpec \
	_currn->_ATTERM_1=_TERM1;

#define _TERMACT_IdentParameterTS \
	_currn->_ATTERM_1=_TERM1;

#define _TERMACT_ParameterTypeSpec

#define _TERMACT_SingleParameterType

#define _TERMACT_MultipleParameterTypes

#define _TERMACT_ExtendedModifier

#define _TERMACT_SimpleModifier

#define _TERMACT_VoidModifier

#define _TERMACT_EmptyModifier

#define _TERMACT_ParameterSpec \
	_currn->_ATTERM_1=_TERM1;

#define _TERMACT_SingleParameter

#define _TERMACT_MultipleParameters

#define _TERMACT_TypeWithOp

#define _TERMACT_TypeNoOp

#define _TERMACT_PropertySpec \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_DefinedType

#define _TERMACT_GenericType

#define _TERMACT_OperationName \
	_currn->_ATTERM_1=_TERM1; \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_OperationSpec \
	_currn->_ATTERM_1=_TERM1; \
	_currn->_ATTERM_2=_TERM2; \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_PropertyName \
	_currn->_ATTERM_1=_TERM1; \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_TypeName \
	_currn->_ATTERM_1=_TERM1; \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord); \
	_currn->_ATsym=_TERM1;

#define _TERMACT_LibrarySpec

#define _TERMACT_Axiom
