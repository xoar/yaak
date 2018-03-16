
/* interface of tree construction functions */

#ifndef TREECON_H
#define TREECON_H
#include "eliproto.h"

#include "err.h"

#include "nodeptr.h"

#include "HEAD.h"


extern void InitTree ELI_ARG((void));

extern void FreeTree ELI_ARG((void));

extern NODEPTR MkBackendOpt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkNamesList ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAttrNames ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAttrList ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAttrType ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOptimOpt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAttrSpec ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkArrangeType ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOrderOpt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkExpandOpt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkBackendOpts ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOptimOpts ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOrderOpts ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkExpandOpts ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkIdentList ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOption ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkOptions ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkStart ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkBACKEND2 ELI_ARG((POSITION *_coordref, int _TERM1, int _TERM2));
extern NODEPTR MkBACKEND1 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkNAMESL2 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkNAMESL1 ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1));
extern NODEPTR MkATTRNAMES ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1));
extern NODEPTR MkATTRS2 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkATTRS1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkATTRTYPE2 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkATTRTYPE1 ELI_ARG((POSITION *_coordref, int _TERM1, int _TERM2));
extern NODEPTR MkOPTIM3 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkOPTIM2 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkOPTIM1 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkATTR1 ELI_ARG((POSITION *_coordref, int _TERM1, int _TERM2, int _TERM3));
extern NODEPTR MkARRANGE3 ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkARRANGE2 ELI_ARG((POSITION *_coordref, int _TERM1, int _TERM2, int _TERM3));
extern NODEPTR MkARRANGE4 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkARRANGE1 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkORDER4 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkORDER3 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkORDER2 ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1));
extern NODEPTR MkORDER1 ELI_ARG((POSITION *_coordref, int _TERM1, int _TERM2));
extern NODEPTR MkEXPAND2 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkEXPAND3 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR MkEXPAND1 ELI_ARG((POSITION *_coordref, int _TERM1, int _TERM2));
extern NODEPTR MkBACKS2 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkBACKS1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkOPTIMS2 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkOPTIMS1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkORDERS2 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkORDERS1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkEXPANDS2 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkEXPANDS1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkIDENTS2 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkIDENTS1 ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1));
extern NODEPTR MkOPTBACK ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkOPTOPT ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkOPTORD ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkOPTEXP ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR MkOPTIONS2 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkOPTIONS1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR MkSTART ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
#define MkIntNumber(pos,val) (val)
#define MkIdentifier(pos,val) (val)
#endif
