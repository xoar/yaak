
/* interface of tree construction functions */

#ifndef TREECON_H
#define TREECON_H
#include "eliproto.h"

#include "err.h"

#include "nodeptr.h"

#include "HEAD.h"


extern void InitTree ELI_ARG((void));

extern void FreeTree ELI_ARG((void));

extern NODEPTR Mkpgs_root ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG3 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG2 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkerr_part ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG4 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG1 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkactpts_root ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkterm_def ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkcode_def ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkelem_list ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkalt_op ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkmod_op ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkskip_part ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkbracket_part ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkterm_def_list ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mksepa_part ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkcode_def_list ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkcode_part ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkelem ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkoptelem ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkdel_op ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrep_op ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkstop_part ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkmodification ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mknonliteral ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkliteral ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkconnection ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkt_or_nt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkterminal ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkroot ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrhs ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mksep_op ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mknonterminal ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrulename ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrule ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrule_list ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkstart ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkgrammarname ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkgrammar_part ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrule_1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_2 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_3 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_4 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_5 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, int _TERM1));
extern NODEPTR Mkrule_6 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_7 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_8 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_9 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_10 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_11 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_12 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_13 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_14 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_15 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_16 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_17 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_18 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_19 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_20 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_21 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_22 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_23 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_24 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_25 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_26 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_27 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_28 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3, NODEPTR _desc4));
extern NODEPTR Mkrule_29 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_30 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_65 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_64 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_63 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_62 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_61 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_60 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_59 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_58 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_57 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_56 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3, NODEPTR _desc4));
extern NODEPTR Mkrule_55 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_54 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_53 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_52 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_51 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_50 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_49 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_48 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_47 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_46 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_45 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_44 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_43 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_42 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_41 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_40 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_39 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_38 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_37 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_36 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_35 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_34 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_33 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_32 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_31 ELI_ARG((POSITION *_coordref));
extern NODEPTR MkRmod_op1 ELI_ARG((POSITION *_coordref));
#define MkSTRING(pos,val) (val)
#define MkNAME(pos,val) (val)
#define MkCARDINAL(pos,val) (val)
#endif
