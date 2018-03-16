
#ifndef RULES_H
#define RULES_H

#include "eliproto.h"


#include "envmod.h"
#include "deftbl.h"
#include "oiladt2.h"
#include "eliproto.h"

/* Constants for the Class property */
#define IDENTIFIER      0
#define TEXT            1
#define GEN_IDENT       2
#define ACTION          3
#define ATMODIDN        4
#define ATMODTXT        5
#define DOLLARMODIDN    6
#define DOLLARMODTXT    7

/* Constants for the Type property */
#define T_NONLISTOF     0
#define T_LISTOF        1

typedef char *charp;

/* Given a key for a rule, return the name of the rule if it    */
/* already exists or generate a unique name for the rule and    */
/* return it.                                                   */
extern void GenRuleName ELI_ARG((DefTableKey key));

extern int QChain ELI_ARG((DefTableKey key));
extern int Trivial ELI_ARG((DefTableKey key));
extern Environment Initialize ELI_ARG((void));

extern tOilType EmptyType;
extern tOilArgSig NullArgSig;

extern tOilArgSig SigAppend ELI_ARG((tOilArgSig sig, DefTableKey key));
extern void CreateOper ELI_ARG((int argcount, DefTableKey prodkey,
                                tOilArgSig opsig));


#endif
