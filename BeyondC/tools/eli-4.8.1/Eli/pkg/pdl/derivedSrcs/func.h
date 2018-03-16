
/* Exported definitions for function output generation */

#ifndef FUNC_H
#define FUNC_H

#include "ptg_gen.h"    /* definition for PTG symbols */
#include "deftbl.h"     /* definition for DefTableKey */
#include "envmod.h"     /* definition for Environment */

#define nullptgnode()         PTGNULL
#define creatptgnode(x)       x
#define concatptgnode(x,y)    PTGSeq((x),(y))

/* element structs and funclists are used to build up a list of operations */
/* associated with a type or property key */
typedef struct element {
        DefTableKey key;
        struct element *next;
} element;

typedef element *funclist;

typedef struct {
        PTGNode rettype;
        PTGNode opname;
        PTGNode paramlist;
        PTGNode paramdecls;
        PTGNode text;
} OpOutput;

/* A dummyfunclist should guarantee not to cause allocation of new space */
/* as opposed to nullfunclist - this can vary according to how the list */
/* is represented */
#define dummyfunclist     ((funclist) 0)

/* exported functions */

#if defined(__cplusplus) || defined(__STDC__)
extern void addfunclist(DefTableKey key, funclist list);
extern funclist nullfunclist();
extern funclist concatfunclist(DefTableKey key, funclist list);
extern DefTableKey FindOpKey(Environment env, int ident);
extern PTGNode GenFunctions(DefTableKey key, int type, 
                            Environment env, funclist list);
extern void PrIdent();
extern OpOutput BuildOperationSpec(PTGNode type, PTGNode opname,
                                   PTGNode paramlist, PTGNode paramdecls,
                                   PTGNode text);
#else
extern void addfunclist();
extern funclist nullfunclist();
extern funclist concatfunclist();
extern DefTableKey FindOpKey();
extern PTGNode GenFunctions();
extern void PrIdent();
extern OpOutput BuildOperationSpec();
#endif

#endif

