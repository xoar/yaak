
/* PDL attribute computations for name analysis */

#include <stdio.h>
#include "err.h"        /* error module */
#include "csm.h"        /* string table module */
#include "idn.h"        /* identifier table module */
#include "deftbl.h"     /* definition table module */
#include "envmod.h"     /* environment module */
#include "ptg_gen.h"    /* output generation definitions */
#include "header.h"     /* definition for ExtOutput */
#include "name.h"       /* constants and exported functions */
#include "pdl_gen.h"    /* PDL generated functions */

int GetHandle;          /* identifier handle for "Get" */
int SetHandle;          /* identifier handle for "Set" */
int ResetHandle;        /* identifier handle for "Reset" */
int TypeHandle;         /* identifier handle for "TYPE" */

/* Create an environment for operation names and predefine the operations */
/* 'Get' and 'Set' and 'Reset' */
#if defined(__cplusplus) || defined(__STDC__)
Environment
InitOpEnv (void)
#else
Environment
InitOpEnv()
#endif
{
  int temp;

  mkidn("Get", 3, &temp, &GetHandle);
  mkidn("Set", 3, &temp, &SetHandle);
  mkidn("Reset", 5, &temp, &ResetHandle);
  return NewEnv();
}

/* Create an environment for type and property names and predefine the */
/* keyword 'TYPE' */
#if defined(__cplusplus) || defined(__STDC__)
Environment
InitEnv (void)
#else
Environment
InitEnv()
#endif
{
  Environment env;
  int temp;
  DefTableKey key;

  mkidn("TYPE", 4, &temp, &TypeHandle);
  env = NewEnv();
  key = DefineIdn(env, TypeHandle);
  SetKind(key, TypeClass, TypeClass);
  return env;
}

/***/
#if defined(__cplusplus) || defined(__STDC__)
void
KindIs (DefTableKey key, int kind)
#else
void
KindIs(key,kind)
DefTableKey key; int kind;
#endif
/* Verify the definition of an entity
 *    On entry-
 *       key defines the entity
 *       kind specifies the type of entity
 *    On exit-
 *       The Kind and Index properties have been set
 ***/
{
   int CurrentKind;

   switch (CurrentKind = GetKind(key,Undefined)) {
   case PropertyClass:
   case TypeClass:
      if (CurrentKind != kind) SetKind(key, NameClash, NameClash);
   case NameClash:
      return;
   case Undefined:
      SetKind(key, kind, NameClash);
   }
}

/* Set all properties for an operation declaration key */
#if defined(__cplusplus) || defined(__STDC__)
void
OpDefine (DefTableKey key, OpOutput output, PTGNode arglist,
          PTGNode formallist, ExtOutput extrn, int sym)
#else
void
OpDefine(key,output,arglist,formallist,extrn,sym)
DefTableKey key; OpOutput output; PTGNode arglist; PTGNode formallist; 
ExtOutput extrn; int sym;
#endif
{
  SetFuncOut(key, output, output);
  SetArgList(key, arglist, arglist);
  SetFormalList(key, formallist, formallist);
  SetExtOut(key, extrn, extrn);
  SetSym(key, sym, sym);
  SetDefine(key, Defined, MultDefined);
  return;
}
