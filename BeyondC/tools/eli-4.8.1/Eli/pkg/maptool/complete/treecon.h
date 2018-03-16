
/* interface of tree construction functions */

#ifndef TREECON_H
#define TREECON_H
#include "eliproto.h"

#include "err.h"

#include "nodeptr.h"

#include "HEAD.h"


extern void InitTree ELI_ARG((void));

extern void FreeTree ELI_ARG((void));

extern NODEPTR MkMapDelim ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapReorder ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapProd ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapAbs ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAbsSignature ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRuleIdUse ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapLHS ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMaptoId ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAbsRuleId ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapText ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapPosition ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapReorderAlt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapElement ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapAlt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapMember ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapMembers ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAbsAlt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAbsAlts ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAbsElements ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkBottomUpRule ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapChains ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapRule ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkMapSymbol ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAbsElement ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkConElement ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAbsLHS ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkConAlt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkConLHS ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAbsProd ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkConProd ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkSource ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrule_1 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_2 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_3 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_4 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_5 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_6 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_7 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_8 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_9 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_10 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_11 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_12 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_13 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_14 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_15 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_16 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_17 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_18 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_19 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_20 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_21 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_22 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_23 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_24 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_25 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_26 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_27 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_28 ELI_ARG((POSITION *_coordref, int _TERM1));
#define Mk0rule_29(_coordref) NULLNODEPTR
extern NODEPTR Mk2rule_29 ELI_ARG((POSITION *_coordref, NODEPTR l, NODEPTR r));
extern NODEPTR Mkrule_29 ELI_ARG((POSITION *_coordref, NODEPTR t));
#define Mk0rule_30(_coordref) NULLNODEPTR
extern NODEPTR Mk2rule_30 ELI_ARG((POSITION *_coordref, NODEPTR l, NODEPTR r));
extern NODEPTR Mkrule_30 ELI_ARG((POSITION *_coordref, NODEPTR t));
#define Mk0rule_31(_coordref) NULLNODEPTR
extern NODEPTR Mk2rule_31 ELI_ARG((POSITION *_coordref, NODEPTR l, NODEPTR r));
extern NODEPTR Mkrule_31 ELI_ARG((POSITION *_coordref, NODEPTR t));
#define Mk0rule_32(_coordref) NULLNODEPTR
extern NODEPTR Mk2rule_32 ELI_ARG((POSITION *_coordref, NODEPTR l, NODEPTR r));
extern NODEPTR Mkrule_32 ELI_ARG((POSITION *_coordref, NODEPTR t));
#define Mk0rule_33(_coordref) NULLNODEPTR
extern NODEPTR Mk2rule_33 ELI_ARG((POSITION *_coordref, NODEPTR l, NODEPTR r));
extern NODEPTR Mkrule_33 ELI_ARG((POSITION *_coordref, NODEPTR t));
#define Mk0rule_34(_coordref) NULLNODEPTR
extern NODEPTR Mk2rule_34 ELI_ARG((POSITION *_coordref, NODEPTR l, NODEPTR r));
extern NODEPTR Mkrule_34 ELI_ARG((POSITION *_coordref, NODEPTR t));
#define Mk0rule_35(_coordref) NULLNODEPTR
extern NODEPTR Mk2rule_35 ELI_ARG((POSITION *_coordref, NODEPTR l, NODEPTR r));
extern NODEPTR Mkrule_35 ELI_ARG((POSITION *_coordref, NODEPTR t));
extern NODEPTR Mkrule_36 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_37 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_38 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_39 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_003 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_002 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_001 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_000 ELI_ARG((POSITION *_coordref, int _TERM1));
#define MkIdentifier(pos,val) (val)
#define MkInteger(pos,val) (val)
#define MkText(pos,val) (val)
#endif
