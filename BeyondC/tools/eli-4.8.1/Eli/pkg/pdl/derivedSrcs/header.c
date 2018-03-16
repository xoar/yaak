
/* Attribution computations for header output generation */

#include <stdio.h>
#include <stdlib.h>
#include "err.h"        /* error module */
#include "deftbl.h"     /* definition table */
#include "envmod.h"     /* environment module */
#include "ptg_gen.h"    /* output generation functions */
#include "func.h"       /* header for source output generation */
#include "pdl_gen.h"    /* PDL generated functions */
#include "csm.h"        /* string table module */

/* global constants */

#define FALSE      0
#define TRUE       1

/* string table indices for predefined operations */
extern int GetHandle, SetHandle, ResetHandle;

/* Generate extern declarations for each of the generated functions */
#if defined(__cplusplus) || defined(__STDC__)
PTGNode
GenExterns (DefTableKey key, int type, Environment env, funclist list)
#else
PTGNode
GenExterns (key, type, env, list)
DefTableKey key;        /* deftbl key for the type */
int type;               /* string table index for type */
Environment env;        /* operation declaration environment */
funclist list;          /* list of operations associated with this type */
#endif
{
  PTGNode result;
  DefTableKey SetKey, GetKey, ResetKey;
  ExtOutput out;

  /* If the externs have already been generated, do not generate them again */
  if (!GetGenExts(key, FALSE)) {
    /* Always generate Get and Set and Reset */
    result = PTGNULL;
    ResetKey=KeyInEnv(env, ResetHandle);
    SetKey=KeyInEnv(env, SetHandle);
    GetKey=KeyInEnv(env, GetHandle);
    if (GetKey != NoKey) {
      out=GetExtOut(GetKey,out);
      result=PTGExternSpec(out.type,out.opname,PTGIdentifier(type),
                           out.paramlist);
    }
    if (SetKey != NoKey) {
      out=GetExtOut(SetKey,out);
      result=PTGSeq(result,PTGExternSpec(out.type,out.opname,
                                         PTGIdentifier(type),
                                         out.paramlist));
    }
    if (ResetKey != NoKey) {
      out=GetExtOut(ResetKey,out);
      result=PTGSeq(result,PTGExternSpec(out.type,out.opname,
                                         PTGIdentifier(type),
                                         out.paramlist));
    }

    /* For each of the operations in the list, append its output to the */
    /* already generated output */
    while (list) {
      out=GetExtOut(list->key,out);
      result=PTGSeq(result,PTGExternSpec(out.type,out.opname,
                                         PTGIdentifier(type),out.paramlist));
      list=list->next;
    }

    /* Indicate that the output has now been generated */
    SetGenExts(key, TRUE, TRUE);
    return PTGExterns(PTGIdentifier(type), result);
  } else
    return PTGNULL;
}

/* Generate the appropriate macros for property declarations */
#if defined(__cplusplus) || defined(__STDC__)
PTGNode
GenMacros (DefTableKey key, int prop, Environment env, funclist list)
#else
PTGNode
GenMacros (key, prop, env, list)
DefTableKey key;        /* deftbl key for property */
int prop;               /* string table index for property */
Environment env;        /* operation declaration environment */
funclist list;          /* list of operations associated with this property */
#endif
{
  DefTableKey SetKey, GetKey, ResetKey;
  PTGNode result, selector;
  int opidn, idn;
  static int PropCtr = 0;  /* unique index for each property */

  /* If the macros have already been generated, do not generate them again */
  if (!GetGenMacros(key, FALSE)) {
    /* Increment the property counter */
    selector = PTGNum(++PropCtr);
    ResetSelector(key, PropCtr);

    /* Always generate the macros for Get and Set */
    idn=GetSym(GetType(key, NoKey), 0);
    ResetKey=KeyInEnv(env, ResetHandle);
    SetKey=KeyInEnv(env, SetHandle);
    GetKey=KeyInEnv(env, GetHandle);
    result = PTGNULL;
    if (SetKey != NoKey) {
      result=PTGMacro(PTGIdentifier(SetHandle), PTGIdentifier(prop),
                      GetArgList(SetKey, PTGNULL),
                      PTGIdentifier(SetHandle), PTGIdentifier(idn),
                      selector, GetFormalList(SetKey, PTGNULL));
    }
    if (ResetKey != NoKey) {
      result = PTGSeq(result,
                      PTGMacro(PTGIdentifier(ResetHandle), PTGIdentifier(prop),
                               GetArgList(ResetKey, PTGNULL),
                               PTGIdentifier(ResetHandle), PTGIdentifier(idn),
                               selector, GetFormalList(ResetKey, PTGNULL)));
    }
    if (GetKey != NoKey) {
      result = PTGSeq(result,
                      PTGMacro(PTGIdentifier(GetHandle), PTGIdentifier(prop),
                               GetArgList(GetKey, PTGNULL),
                               PTGIdentifier(GetHandle), PTGIdentifier(idn),
                               selector, GetFormalList(GetKey, PTGNULL)));
    }

    /* For each operation in the list, append the macro for that operation */
    /* to the output generated so far */
    while (list) {
      opidn=GetSym(list->key, 0);
      result=PTGSeq(PTGMacro(PTGIdentifier(opidn), PTGIdentifier(prop), 
                                GetArgList(list->key, PTGNULL),
                                PTGIdentifier(opidn), PTGIdentifier(idn),
                                selector, 
                                GetFormalList(list->key, PTGNULL)),
                    result);
      list=list->next;
    }

    /* Indicate that the macros have now been generated */
    SetGenMacros(key, TRUE, TRUE);
    return result;
  } else
    return PTGNULL;
}

/* Build a structure to hold information for generation of an extern */
#if defined(__cplusplus) || defined(__STDC__)
ExtOutput
BuildExternSpec (PTGNode type, PTGNode opname, PTGNode paramlist)
#else
ExtOutput
BuildExternSpec (type, opname, paramlist)
PTGNode type, opname, paramlist;
#endif
{
  ExtOutput *temp;

  if (!(temp = (ExtOutput *) malloc(sizeof(ExtOutput))))
    message(DEADLY, "BuildExternSpec: malloc failed", 0, (POSITION *)0);

  temp->type = type;
  temp->opname = opname;
  temp->paramlist = paramlist;
  return *temp;
}
