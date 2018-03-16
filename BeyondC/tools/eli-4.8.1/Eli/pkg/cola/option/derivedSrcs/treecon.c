
/* implementation of tree construction functions */

#include "node.h"

#include "nodecode.h"

#include "attrpredef.h"

#include "visitmap.h"

#include "treeact.h"

#ifdef MONITOR
#include "attr_mon_dapto.h"
#endif

#include <stdlib.h>

#define _USE_OBSTACK 1

/* use of obstack: */

#if _USE_OBSTACK

#include "obstack.h"
static struct obstack TreeSpace;
static void *_TreeBase;

#ifdef __cplusplus
void* NODEPTR_struct::operator new(size_t size)
{
	return obstack_alloc(&TreeSpace, size);
}
#else
#if defined(__STDC__) || defined(__cplusplus)
char* TreeNodeAlloc(int size)
#else
char* TreeNodeAlloc(size) int size;
#endif
{
	return (char *)(obstack_alloc(&TreeSpace, size));
}
#endif

void InitTree()
{
	obstack_init(&TreeSpace);
	_TreeBase=obstack_alloc(&TreeSpace,0);
}

void FreeTree()
{
	obstack_free(&TreeSpace, _TreeBase);
	_TreeBase=obstack_alloc(&TreeSpace,0);
}

#else

#include <stdio.h>

#ifdef __cplusplus
void* NODEPTR_struct::operator new(size_t size)
{
	void *retval = malloc(size);
	if (retval) return retval;
	fprintf(stderr, "*** DEADLY: No more memory.\n");
	exit(1);
}
#else
#if defined(__STDC__) || defined(__cplusplus)
char* TreeNodeAlloc(int size)
#else
char* TreeNodeAlloc(size) int size;
#endif
{
	char *retval = (char *) malloc(size);
	if (retval) return retval;
	fprintf(stderr, "*** DEADLY: No more memory.\n");
	exit(1);
}
#endif

void InitTree() { }

void FreeTree() { }

#endif

#ifdef MONITOR
#define _SETCOORD(node) \
        node->_coord = _coordref ? *_coordref : NoCoord;
#define _COPYCOORD(node) \
        node->_coord = _currn->_desc1->_coord;
#else
#define _SETCOORD(node)
#define _COPYCOORD(node)
#endif
#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkErrorOpt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkErrorOpt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBErrorOpt)) return (_currn);
return(NULLNODEPTR);
}/* MkErrorOpt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkCodeOpt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkCodeOpt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBCodeOpt)) return (_currn);
return(NULLNODEPTR);
}/* MkCodeOpt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkStackOpt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkStackOpt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBStackOpt)) return (_currn);
return(NULLNODEPTR);
}/* MkStackOpt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkMode (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkMode (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBMode)) return (_currn);
return(NULLNODEPTR);
}/* MkMode */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOnOff (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOnOff (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOnOff)) return (_currn);
return(NULLNODEPTR);
}/* MkOnOff */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDirect (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDirect (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDirect)) return (_currn);
return(NULLNODEPTR);
}/* MkDirect */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTable (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTable (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTable)) return (_currn);
return(NULLNODEPTR);
}/* MkTable */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkFrontend (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkFrontend (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBFrontend)) return (_currn);
return(NULLNODEPTR);
}/* MkFrontend */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOption (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkOption (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBOption)) return (_currn);
if (IsSymb (_currn, SYMBFrontend)) return (MkOpt2(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (MkOpt3(_coordref, _currn));
if (IsSymb (_currn, SYMBDirect)) return (MkOpt4(_coordref, _currn));
return(NULLNODEPTR);
}/* MkOption */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkStart (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkStart (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBStart)) return (_currn);
if (IsSymb (_currn, SYMBFrontend)) return (MkRoot(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (MkRoot(_coordref, _currn));
if (IsSymb (_currn, SYMBDirect)) return (MkRoot(_coordref, _currn));
if (IsSymb (_currn, SYMBOption)) return (MkRoot(_coordref, _currn));
return(NULLNODEPTR);
}/* MkStart */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSW2 (POSITION *_coordref)
#else
NODEPTR MkSW2 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPSW2 _currn;
#ifdef __cplusplus
_currn = new _TPSW2;
#else
_currn = (_TPPSW2) TreeNodeAlloc (sizeof (struct _TPSW2));
#endif
_currn->_prod = RULESW2;
_SETCOORD(_currn)
_TERMACT_SW2;
return ( (NODEPTR) _currn);
}/* MkSW2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSW1 (POSITION *_coordref)
#else
NODEPTR MkSW1 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPSW1 _currn;
#ifdef __cplusplus
_currn = new _TPSW1;
#else
_currn = (_TPPSW1) TreeNodeAlloc (sizeof (struct _TPSW1));
#endif
_currn->_prod = RULESW1;
_SETCOORD(_currn)
_TERMACT_SW1;
return ( (NODEPTR) _currn);
}/* MkSW1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDE3 (POSITION *_coordref)
#else
NODEPTR MkDE3 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPDE3 _currn;
#ifdef __cplusplus
_currn = new _TPDE3;
#else
_currn = (_TPPDE3) TreeNodeAlloc (sizeof (struct _TPDE3));
#endif
_currn->_prod = RULEDE3;
_SETCOORD(_currn)
_TERMACT_DE3;
return ( (NODEPTR) _currn);
}/* MkDE3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDE2 (POSITION *_coordref)
#else
NODEPTR MkDE2 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPDE2 _currn;
#ifdef __cplusplus
_currn = new _TPDE2;
#else
_currn = (_TPPDE2) TreeNodeAlloc (sizeof (struct _TPDE2));
#endif
_currn->_prod = RULEDE2;
_SETCOORD(_currn)
_TERMACT_DE2;
return ( (NODEPTR) _currn);
}/* MkDE2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDE1 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkDE1 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPDE1 _currn;
#ifdef __cplusplus
_currn = new _TPDE1;
#else
_currn = (_TPPDE1) TreeNodeAlloc (sizeof (struct _TPDE1));
#endif
_currn->_prod = RULEDE1;
_SETCOORD(_currn)
_TERMACT_DE1;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkDE1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDC11 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkDC11 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPDC11 _currn;
#ifdef __cplusplus
_currn = new _TPDC11;
#else
_currn = (_TPPDC11) TreeNodeAlloc (sizeof (struct _TPDC11));
#endif
_currn->_prod = RULEDC11;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE DC11: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_DC11;
return ( (NODEPTR) _currn);
}/* MkDC11 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDC10 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkDC10 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPDC10 _currn;
#ifdef __cplusplus
_currn = new _TPDC10;
#else
_currn = (_TPPDC10) TreeNodeAlloc (sizeof (struct _TPDC10));
#endif
_currn->_prod = RULEDC10;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE DC10: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_DC10;
return ( (NODEPTR) _currn);
}/* MkDC10 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDC9 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkDC9 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPDC9 _currn;
#ifdef __cplusplus
_currn = new _TPDC9;
#else
_currn = (_TPPDC9) TreeNodeAlloc (sizeof (struct _TPDC9));
#endif
_currn->_prod = RULEDC9;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE DC9: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_DC9;
return ( (NODEPTR) _currn);
}/* MkDC9 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDC8 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkDC8 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPDC8 _currn;
#ifdef __cplusplus
_currn = new _TPDC8;
#else
_currn = (_TPPDC8) TreeNodeAlloc (sizeof (struct _TPDC8));
#endif
_currn->_prod = RULEDC8;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE DC8: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_DC8;
return ( (NODEPTR) _currn);
}/* MkDC8 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDC7 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkDC7 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPDC7 _currn;
#ifdef __cplusplus
_currn = new _TPDC7;
#else
_currn = (_TPPDC7) TreeNodeAlloc (sizeof (struct _TPDC7));
#endif
_currn->_prod = RULEDC7;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE DC7: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_DC7;
return ( (NODEPTR) _currn);
}/* MkDC7 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDC6 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkDC6 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPDC6 _currn;
#ifdef __cplusplus
_currn = new _TPDC6;
#else
_currn = (_TPPDC6) TreeNodeAlloc (sizeof (struct _TPDC6));
#endif
_currn->_prod = RULEDC6;
_SETCOORD(_currn)
_TERMACT_DC6;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkDC6 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDC5 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkDC5 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPDC5 _currn;
#ifdef __cplusplus
_currn = new _TPDC5;
#else
_currn = (_TPPDC5) TreeNodeAlloc (sizeof (struct _TPDC5));
#endif
_currn->_prod = RULEDC5;
_SETCOORD(_currn)
_TERMACT_DC5;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkDC5 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDC4 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkDC4 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPDC4 _currn;
#ifdef __cplusplus
_currn = new _TPDC4;
#else
_currn = (_TPPDC4) TreeNodeAlloc (sizeof (struct _TPDC4));
#endif
_currn->_prod = RULEDC4;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE DC4: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_DC4;
return ( (NODEPTR) _currn);
}/* MkDC4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDC3 (POSITION *_coordref)
#else
NODEPTR MkDC3 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPDC3 _currn;
#ifdef __cplusplus
_currn = new _TPDC3;
#else
_currn = (_TPPDC3) TreeNodeAlloc (sizeof (struct _TPDC3));
#endif
_currn->_prod = RULEDC3;
_SETCOORD(_currn)
_TERMACT_DC3;
return ( (NODEPTR) _currn);
}/* MkDC3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDC2 (POSITION *_coordref)
#else
NODEPTR MkDC2 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPDC2 _currn;
#ifdef __cplusplus
_currn = new _TPDC2;
#else
_currn = (_TPPDC2) TreeNodeAlloc (sizeof (struct _TPDC2));
#endif
_currn->_prod = RULEDC2;
_SETCOORD(_currn)
_TERMACT_DC2;
return ( (NODEPTR) _currn);
}/* MkDC2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDC1 (POSITION *_coordref)
#else
NODEPTR MkDC1 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPDC1 _currn;
#ifdef __cplusplus
_currn = new _TPDC1;
#else
_currn = (_TPPDC1) TreeNodeAlloc (sizeof (struct _TPDC1));
#endif
_currn->_prod = RULEDC1;
_SETCOORD(_currn)
_TERMACT_DC1;
return ( (NODEPTR) _currn);
}/* MkDC1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDS6 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkDS6 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPDS6 _currn;
#ifdef __cplusplus
_currn = new _TPDS6;
#else
_currn = (_TPPDS6) TreeNodeAlloc (sizeof (struct _TPDS6));
#endif
_currn->_prod = RULEDS6;
_SETCOORD(_currn)
_TERMACT_DS6;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkDS6 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDS5 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkDS5 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPDS5 _currn;
#ifdef __cplusplus
_currn = new _TPDS5;
#else
_currn = (_TPPDS5) TreeNodeAlloc (sizeof (struct _TPDS5));
#endif
_currn->_prod = RULEDS5;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE DS5: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_DS5;
return ( (NODEPTR) _currn);
}/* MkDS5 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDS4 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkDS4 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPDS4 _currn;
#ifdef __cplusplus
_currn = new _TPDS4;
#else
_currn = (_TPPDS4) TreeNodeAlloc (sizeof (struct _TPDS4));
#endif
_currn->_prod = RULEDS4;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE DS4: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_DS4;
return ( (NODEPTR) _currn);
}/* MkDS4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDS3 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkDS3 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPDS3 _currn;
#ifdef __cplusplus
_currn = new _TPDS3;
#else
_currn = (_TPPDS3) TreeNodeAlloc (sizeof (struct _TPDS3));
#endif
_currn->_prod = RULEDS3;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE DS3: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_DS3;
return ( (NODEPTR) _currn);
}/* MkDS3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDS2 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkDS2 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPDS2 _currn;
#ifdef __cplusplus
_currn = new _TPDS2;
#else
_currn = (_TPPDS2) TreeNodeAlloc (sizeof (struct _TPDS2));
#endif
_currn->_prod = RULEDS2;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE DS2: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_DS2;
return ( (NODEPTR) _currn);
}/* MkDS2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDS1 (POSITION *_coordref, int _TERM1)
#else
NODEPTR MkDS1 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPDS1 _currn;
#ifdef __cplusplus
_currn = new _TPDS1;
#else
_currn = (_TPPDS1) TreeNodeAlloc (sizeof (struct _TPDS1));
#endif
_currn->_prod = RULEDS1;
_SETCOORD(_currn)
_TERMACT_DS1;
#ifdef MONITOR
_dapto_term_int(((NODEPTR)_currn), "integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* MkDS1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkD3 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkD3 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPD3 _currn;
#ifdef __cplusplus
_currn = new _TPD3;
#else
_currn = (_TPPD3) TreeNodeAlloc (sizeof (struct _TPD3));
#endif
_currn->_prod = RULED3;
_currn->_desc1 = (_TSPErrorOpt) MkErrorOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE D3: root of subtree no. 1 can not be made a ErrorOpt node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_D3;
return ( (NODEPTR) _currn);
}/* MkD3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkD2 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkD2 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPD2 _currn;
#ifdef __cplusplus
_currn = new _TPD2;
#else
_currn = (_TPPD2) TreeNodeAlloc (sizeof (struct _TPD2));
#endif
_currn->_prod = RULED2;
_currn->_desc1 = (_TSPCodeOpt) MkCodeOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE D2: root of subtree no. 1 can not be made a CodeOpt node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_D2;
return ( (NODEPTR) _currn);
}/* MkD2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkD1 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkD1 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPD1 _currn;
#ifdef __cplusplus
_currn = new _TPD1;
#else
_currn = (_TPPD1) TreeNodeAlloc (sizeof (struct _TPD1));
#endif
_currn->_prod = RULED1;
_currn->_desc1 = (_TSPStackOpt) MkStackOpt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE D1: root of subtree no. 1 can not be made a StackOpt node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_D1;
return ( (NODEPTR) _currn);
}/* MkD1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkM8 (POSITION *_coordref)
#else
NODEPTR MkM8 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPM8 _currn;
#ifdef __cplusplus
_currn = new _TPM8;
#else
_currn = (_TPPM8) TreeNodeAlloc (sizeof (struct _TPM8));
#endif
_currn->_prod = RULEM8;
_SETCOORD(_currn)
_TERMACT_M8;
return ( (NODEPTR) _currn);
}/* MkM8 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkM7 (POSITION *_coordref)
#else
NODEPTR MkM7 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPM7 _currn;
#ifdef __cplusplus
_currn = new _TPM7;
#else
_currn = (_TPPM7) TreeNodeAlloc (sizeof (struct _TPM7));
#endif
_currn->_prod = RULEM7;
_SETCOORD(_currn)
_TERMACT_M7;
return ( (NODEPTR) _currn);
}/* MkM7 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkM6 (POSITION *_coordref)
#else
NODEPTR MkM6 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPM6 _currn;
#ifdef __cplusplus
_currn = new _TPM6;
#else
_currn = (_TPPM6) TreeNodeAlloc (sizeof (struct _TPM6));
#endif
_currn->_prod = RULEM6;
_SETCOORD(_currn)
_TERMACT_M6;
return ( (NODEPTR) _currn);
}/* MkM6 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkM5 (POSITION *_coordref)
#else
NODEPTR MkM5 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPM5 _currn;
#ifdef __cplusplus
_currn = new _TPM5;
#else
_currn = (_TPPM5) TreeNodeAlloc (sizeof (struct _TPM5));
#endif
_currn->_prod = RULEM5;
_SETCOORD(_currn)
_TERMACT_M5;
return ( (NODEPTR) _currn);
}/* MkM5 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkM4 (POSITION *_coordref)
#else
NODEPTR MkM4 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPM4 _currn;
#ifdef __cplusplus
_currn = new _TPM4;
#else
_currn = (_TPPM4) TreeNodeAlloc (sizeof (struct _TPM4));
#endif
_currn->_prod = RULEM4;
_SETCOORD(_currn)
_TERMACT_M4;
return ( (NODEPTR) _currn);
}/* MkM4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkM3 (POSITION *_coordref)
#else
NODEPTR MkM3 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPM3 _currn;
#ifdef __cplusplus
_currn = new _TPM3;
#else
_currn = (_TPPM3) TreeNodeAlloc (sizeof (struct _TPM3));
#endif
_currn->_prod = RULEM3;
_SETCOORD(_currn)
_TERMACT_M3;
return ( (NODEPTR) _currn);
}/* MkM3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkM2 (POSITION *_coordref)
#else
NODEPTR MkM2 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPM2 _currn;
#ifdef __cplusplus
_currn = new _TPM2;
#else
_currn = (_TPPM2) TreeNodeAlloc (sizeof (struct _TPM2));
#endif
_currn->_prod = RULEM2;
_SETCOORD(_currn)
_TERMACT_M2;
return ( (NODEPTR) _currn);
}/* MkM2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkM1 (POSITION *_coordref)
#else
NODEPTR MkM1 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPM1 _currn;
#ifdef __cplusplus
_currn = new _TPM1;
#else
_currn = (_TPPM1) TreeNodeAlloc (sizeof (struct _TPM1));
#endif
_currn->_prod = RULEM1;
_SETCOORD(_currn)
_TERMACT_M1;
return ( (NODEPTR) _currn);
}/* MkM1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkT3 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkT3 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPT3 _currn;
#ifdef __cplusplus
_currn = new _TPT3;
#else
_currn = (_TPPT3) TreeNodeAlloc (sizeof (struct _TPT3));
#endif
_currn->_prod = RULET3;
_currn->_desc1 = (_TSPMode) MkMode (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE T3: root of subtree no. 1 can not be made a Mode node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_T3;
return ( (NODEPTR) _currn);
}/* MkT3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkT2 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkT2 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPT2 _currn;
#ifdef __cplusplus
_currn = new _TPT2;
#else
_currn = (_TPPT2) TreeNodeAlloc (sizeof (struct _TPT2));
#endif
_currn->_prod = RULET2;
_currn->_desc1 = (_TSPMode) MkMode (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE T2: root of subtree no. 1 can not be made a Mode node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_T2;
return ( (NODEPTR) _currn);
}/* MkT2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkT1 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkT1 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPT1 _currn;
#ifdef __cplusplus
_currn = new _TPT1;
#else
_currn = (_TPPT1) TreeNodeAlloc (sizeof (struct _TPT1));
#endif
_currn->_prod = RULET1;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE T1: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_T1;
return ( (NODEPTR) _currn);
}/* MkT1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkF3 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkF3 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPF3 _currn;
#ifdef __cplusplus
_currn = new _TPF3;
#else
_currn = (_TPPF3) TreeNodeAlloc (sizeof (struct _TPF3));
#endif
_currn->_prod = RULEF3;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE F3: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_F3;
return ( (NODEPTR) _currn);
}/* MkF3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkF2 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkF2 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPF2 _currn;
#ifdef __cplusplus
_currn = new _TPF2;
#else
_currn = (_TPPF2) TreeNodeAlloc (sizeof (struct _TPF2));
#endif
_currn->_prod = RULEF2;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE F2: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_F2;
return ( (NODEPTR) _currn);
}/* MkF2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkF1 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkF1 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPF1 _currn;
#ifdef __cplusplus
_currn = new _TPF1;
#else
_currn = (_TPPF1) TreeNodeAlloc (sizeof (struct _TPF1));
#endif
_currn->_prod = RULEF1;
_currn->_desc1 = (_TSPOnOff) MkOnOff (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE F1: root of subtree no. 1 can not be made a OnOff node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_F1;
return ( (NODEPTR) _currn);
}/* MkF1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOpt5 (POSITION *_coordref)
#else
NODEPTR MkOpt5 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPOpt5 _currn;
#ifdef __cplusplus
_currn = new _TPOpt5;
#else
_currn = (_TPPOpt5) TreeNodeAlloc (sizeof (struct _TPOpt5));
#endif
_currn->_prod = RULEOpt5;
_SETCOORD(_currn)
_TERMACT_Opt5;
return ( (NODEPTR) _currn);
}/* MkOpt5 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOpt4 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkOpt4 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPOpt4 _currn;
#ifdef __cplusplus
_currn = new _TPOpt4;
#else
_currn = (_TPPOpt4) TreeNodeAlloc (sizeof (struct _TPOpt4));
#endif
_currn->_prod = RULEOpt4;
_currn->_desc1 = (_TSPDirect) MkDirect (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE Opt4: root of subtree no. 1 can not be made a Direct node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_Opt4;
return ( (NODEPTR) _currn);
}/* MkOpt4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOpt3 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkOpt3 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPOpt3 _currn;
#ifdef __cplusplus
_currn = new _TPOpt3;
#else
_currn = (_TPPOpt3) TreeNodeAlloc (sizeof (struct _TPOpt3));
#endif
_currn->_prod = RULEOpt3;
_currn->_desc1 = (_TSPTable) MkTable (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE Opt3: root of subtree no. 1 can not be made a Table node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_Opt3;
return ( (NODEPTR) _currn);
}/* MkOpt3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOpt2 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkOpt2 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPOpt2 _currn;
#ifdef __cplusplus
_currn = new _TPOpt2;
#else
_currn = (_TPPOpt2) TreeNodeAlloc (sizeof (struct _TPOpt2));
#endif
_currn->_prod = RULEOpt2;
_currn->_desc1 = (_TSPFrontend) MkFrontend (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE Opt2: root of subtree no. 1 can not be made a Frontend node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_Opt2;
return ( (NODEPTR) _currn);
}/* MkOpt2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkOpt1 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR MkOpt1 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPOpt1 _currn;
#ifdef __cplusplus
_currn = new _TPOpt1;
#else
_currn = (_TPPOpt1) TreeNodeAlloc (sizeof (struct _TPOpt1));
#endif
_currn->_prod = RULEOpt1;
_currn->_desc1 = (_TSPOption) MkOption (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE Opt1: root of subtree no. 1 can not be made a Option node ", 0, _coordref);
_currn->_desc2 = (_TSPOption) MkOption (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE Opt1: root of subtree no. 2 can not be made a Option node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_Opt1;
return ( (NODEPTR) _currn);
}/* MkOpt1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRoot (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR MkRoot (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPRoot _currn;
#ifdef __cplusplus
_currn = new _TPRoot;
#else
_currn = (_TPPRoot) TreeNodeAlloc (sizeof (struct _TPRoot));
#endif
_currn->_prod = RULERoot;
_currn->_desc1 = (_TSPOption) MkOption (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE Root: root of subtree no. 1 can not be made a Option node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_Root;
return ( (NODEPTR) _currn);
}/* MkRoot */
