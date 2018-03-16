
/* interface of tree construction functions */

#ifndef TREECON_H
#define TREECON_H
#include "eliproto.h"

#include "err.h"

#include "nodeptr.h"

#include "HEAD.h"


extern void InitTree ELI_ARG((void));

extern void FreeTree ELI_ARG((void));

extern NODEPTR MknonLitDesc ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG1 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkspec ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MklibrRef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkoptProcessor ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkoptAuxScanner ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrest ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrule_1 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_2 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_3 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_4 ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_12 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_11 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_10 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_9 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_8 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_7 ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1));
extern NODEPTR Mkrule_6 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_5 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
#define MkRegularExpr(pos,val) (val)
#define MkIdentifier(pos,val) (val)
#endif
