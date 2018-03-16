
/* Exported definitions for attribute computations in PDL name analysis */

#ifndef NAME_H
#define NAME_H

#include "envmod.h"     /* definition for Environment */
#include "deftbl.h"     /* definition for DefTableKey */
#include "func.h"       /* definition for OpOutput */
#include "header.h"     /* definition for ExtOutput */

/* Constants for the class identifier attribute to indicate if it is a */
/* property or type name */
#define Undefined         0
#define PropertyClass     1
#define TypeClass         2
#define NameClash         3

/* Constants to indicate if an operation has been defined more than once */
#define Defined           1
#define MultDefined       2

/* exported functions */

#if defined(__cplusplus) || defined(__STDC__)
extern Environment InitEnv();
extern Environment InitOpEnv();
extern void KindIs(DefTableKey key, int kind);
extern void OpDefine(DefTableKey key, OpOutput output, PTGNode arglist, 
                        PTGNode formallist, ExtOutput extrn, int sym);
#else
extern Environment InitEnv();
extern Environment InitOpEnv();
extern void KindIs();
extern void OpDefine();
#endif

#endif
