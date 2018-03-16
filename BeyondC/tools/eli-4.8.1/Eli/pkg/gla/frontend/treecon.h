
/* interface of tree construction functions */

#ifndef TREECON_H
#define TREECON_H
#include "eliproto.h"

#include "err.h"

#include "nodeptr.h"

#include "HEAD.h"


extern void InitTree ELI_ARG((void));

extern void FreeTree ELI_ARG((void));

extern NODEPTR Mkoptions ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkoption ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MknonLitDescs ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkencodings ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkEofOption ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MklibrRef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkoptProcessor ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkoptAuxScanner ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkencoding ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkLitEncoding ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkspec ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkvalue ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkIdUse ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkNonlitEncoding ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrest ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkIdDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MknonLitDesc ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrule_1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_2 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_3 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_4 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_5 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_6 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_7 ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_8 ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1));
extern NODEPTR Mkrule_9 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_10 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_11 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_12 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_13 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_14 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_15 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_16 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_17 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_18 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_32 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_31 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_30 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_29 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_28 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_27 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_26 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_25 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_24 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_23 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_22 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_21 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_20 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_19 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
#define MkInteger(pos,val) (val)
#define MkRegularExpr(pos,val) (val)
#define MkIdentifier(pos,val) (val)
#endif
