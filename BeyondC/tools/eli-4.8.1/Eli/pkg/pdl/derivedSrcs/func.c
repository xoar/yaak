
/* Attribute computations for C output generation */

#include <stdio.h>
#include <stdlib.h>
#include "err.h"                /* error module */
#include "deftbl.h"             /* definition table */
#include "envmod.h"             /* environment module */
#include "ptg_gen.h"            /* output generation functions */
#include "func.h"
#include "header.h"
#include "pdl_gen.h"            /* PDL generated functions */
#include "csm.h"                /* string table */

/* global constants */

#define FALSE      0
#define TRUE       1

/* string table indices for predefined operations */
extern int GetHandle, SetHandle, ResetHandle;

/* Add a list of operations to those already associated with the given key */
#if defined(__cplusplus) || defined(__STDC__)
void
addfunclist (DefTableKey key, funclist list)
#else
void
addfunclist (key, list)
DefTableKey key;
funclist list;
#endif
{
  funclist olist, temp;

  /* Get the current list of operations for the key */
  olist = GetFuncList(key, dummyfunclist);

  /* For each of the functions to add, see if they are already in the list */
  /* and if not add them to the list */
  while (list) {
    temp = olist;
    while (temp && (temp->key != list->key))
      temp = temp->next;
    if (!temp) {
      temp = (funclist) malloc(sizeof(element));
      temp->key = list->key;
      temp->next = olist;
      olist = temp;
    }
    list = list->next;
  }  

  /* Set the appropriate property */
  SetFuncList(key, olist, olist);
}

/* Returns a null funclist */
#if defined(__cplusplus) || defined(__STDC__)
funclist
nullfunclist (void)
#else
funclist
nullfunclist ()
#endif
{
  return ((funclist) 0);
}

/* Concatenate the key for a single operation onto a list of operations */
#if defined(__cplusplus) || defined(__STDC__)
funclist
concatfunclist (DefTableKey key, funclist list)
#else
funclist
concatfunclist (key, list)
DefTableKey key;
funclist list;
#endif
{
  funclist temp;

  if (key == NoKey)
    return list;
  else {
    temp = (funclist) malloc(sizeof(element));
    temp->key = key;
    temp->next = list;
    return temp;
  }
}

/* Return the appropriate operation definition for the given operation */
/* declaration key */
#if defined(__cplusplus) || defined(__STDC__)
DefTableKey
FindOpKey (Environment env, int ident)
#else
DefTableKey
FindOpKey (env, ident)
Environment env;
int ident;
#endif
{
  /* If it is Get or Set, return an invalid key as these operations are */
  /* always generated, otherwise look up the identifier in the operation */
  /* environment */
  if ((ident == GetHandle) || (ident == SetHandle) || (ident == ResetHandle))
    return NoKey;
  else
    return KeyInEnv(env, ident);
}

/* Generate the necessary functions associated with a type */
#if defined(__cplusplus) || defined(__STDC__)
PTGNode
GenFunctions (DefTableKey key, int type, Environment env, funclist list)
#else
PTGNode
GenFunctions (key, type, env, list)
DefTableKey key;        /* deftbl key for the type */
int type;               /* string table index for the type name */
Environment env;        /* operation declaration environment */
funclist list;          /* list of operations declared for this type */
#endif
{
  PTGNode result, typename;
  DefTableKey SetKey, GetKey, ResetKey;
  OpOutput out;
  ExtOutput extout;

  /* If this output has not been generated yet, generate it - otherwise */
  /* return no output */
  if (!GetGenFuncs(key, FALSE)) {
    /* First generate both Get and Set operations */
    ResetKey=KeyInEnv(env, ResetHandle);
    SetKey=KeyInEnv(env, SetHandle);
    GetKey=KeyInEnv(env, GetHandle);
    typename = PTGIdentifier(type); ResetTypeName(key, typename);
    result=PTGTypeDef(typename);
    if (GetKey != NoKey) {
      out=GetFuncOut(GetKey,out);
      extout=GetExtOut(GetKey,extout);
      result=PTGSeq(result,PTGOperationSpec(out.rettype,out.opname,
                                            typename,extout.paramlist,
                                            out.paramlist,out.paramdecls,
                                            out.text));
    }
    if (SetKey != NoKey) {
      out=GetFuncOut(SetKey,out);
      extout=GetExtOut(SetKey,extout);
      result=PTGSeq(result,PTGOperationSpec(out.rettype,out.opname,
                                            typename,extout.paramlist,
                                            out.paramlist,out.paramdecls,
                                            out.text));
    }
    if (ResetKey != NoKey) {
      out=GetFuncOut(ResetKey,out);
      extout=GetExtOut(ResetKey,extout);
      result=PTGSeq(result,PTGOperationSpec(out.rettype,out.opname,
                                            typename,extout.paramlist,
                                            out.paramlist,out.paramdecls,
                                            out.text));
    }

    /* For each operation declared in the list, append the output for that */
    /* function to the output already generated */
    while (list) {
      out=GetFuncOut(list->key,out);
      extout=GetExtOut(list->key,extout);
      result=PTGSeq(result,PTGOperationSpec(out.rettype,out.opname,
                                            typename,extout.paramlist,
                                            out.paramlist,out.paramdecls,
                                            out.text));
      list=list->next;
    }

    /* Indicate that the output has now been generated */
    SetGenFuncs(key, TRUE, TRUE);
    return PTGFunctions(typename, typename, result);
  } else
    return PTGNULL;
}

/* Print an identifier */
#if defined(__cplusplus) || defined(__STDC__)
void
PrIdent (FILE *f, int val)
#else
void
PrIdent (f, val)
FILE *f; int val;
#endif
{
  fprintf(f, "%s", StringTable(val));
}

/* Build up the structure to hold information for an operation declaration */
#if defined(__cplusplus) || defined(__STDC__)
OpOutput
BuildOperationSpec (PTGNode type, PTGNode opname, PTGNode paramlist,
                    PTGNode paramdecls, PTGNode text)
#else
OpOutput
BuildOperationSpec (type, opname, paramlist, paramdecls, text)
PTGNode type, opname, paramlist, paramdecls, text;
#endif
{
  OpOutput *temp;

  if (!(temp = (OpOutput *) malloc(sizeof(OpOutput))))
    message(DEADLY, "BuildOperationSpec: malloc failed", 0, (POSITION *)0);

  temp->rettype = type;
  temp->opname = opname;
  temp->paramlist = paramlist;
  temp->paramdecls = paramdecls;
  temp->text = text;
  return *temp;
}

