
/* interface of tree construction functions */

#ifndef TREECON_H
#define TREECON_H
#include "eliproto.h"

#include "err.h"

#include "nodeptr.h"

#include "HEAD.h"


extern void InitTree ELI_ARG((void));

extern void FreeTree ELI_ARG((void));

extern NODEPTR MkErrorOpt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkCodeOpt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkStackOpt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMode ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOnOff ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkDirect ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTable ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkFrontend ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOption ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkStart ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkSW2 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkSW1 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkDE3 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkDE2 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkDE1 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkDC11 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkDC10 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkDC9 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkDC8 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkDC7 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkDC6 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkDC5 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkDC4 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkDC3 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkDC2 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkDC1 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkDS6 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkDS5 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkDS4 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkDS3 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkDS2 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkDS1 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkD3 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkD2 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkD1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkM8 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkM7 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkM6 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkM5 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkM4 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkM3 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkM2 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkM1 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkT3 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkT2 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkT1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkF3 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkF2 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkF1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkOpt5 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkOpt4 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkOpt3 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkOpt2 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkOpt1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkRoot ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
#define Mkinteger(pos,val) (val)
#endif
