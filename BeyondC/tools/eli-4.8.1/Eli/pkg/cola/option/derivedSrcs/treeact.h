

#define _TERMACT_SW2

#define _TERMACT_SW1

#define _TERMACT_DE3

#define _TERMACT_DE2

#define _TERMACT_DE1 \
	_currn->_ATTERM_1=_TERM1; \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_DC11

#define _TERMACT_DC10

#define _TERMACT_DC9

#define _TERMACT_DC8

#define _TERMACT_DC7

#define _TERMACT_DC6 \
	_currn->_ATTERM_1=_TERM1; \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_DC5 \
	_currn->_ATTERM_1=_TERM1; \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_DC4

#define _TERMACT_DC3

#define _TERMACT_DC2

#define _TERMACT_DC1

#define _TERMACT_DS6 \
	_currn->_ATTERM_1=_TERM1; \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_DS5

#define _TERMACT_DS4

#define _TERMACT_DS3

#define _TERMACT_DS2

#define _TERMACT_DS1 \
	_currn->_ATTERM_1=_TERM1; \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_D3

#define _TERMACT_D2

#define _TERMACT_D1

#define _TERMACT_M8

#define _TERMACT_M7

#define _TERMACT_M6

#define _TERMACT_M5

#define _TERMACT_M4

#define _TERMACT_M3

#define _TERMACT_M2

#define _TERMACT_M1

#define _TERMACT_T3

#define _TERMACT_T2

#define _TERMACT_T1

#define _TERMACT_F3

#define _TERMACT_F2

#define _TERMACT_F1

#define _TERMACT_Opt5

#define _TERMACT_Opt4 \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_Opt3 \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_Opt2 \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);

#define _TERMACT_Opt1

#define _TERMACT_Root \
	_currn->_AT_pos=(_coordref ? *_coordref : NoCoord);
