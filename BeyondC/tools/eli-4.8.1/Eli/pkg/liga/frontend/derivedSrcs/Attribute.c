
#include "Attribute.h"
#include "Strings.h"
#include "pdl_gen.h"
#include "PreDefId.h"

/* set by call of InheritAttrProps: */
Environment globEnv = NoEnv;
Environment attrEnv = NoEnv;


#ifdef TEST
#define TEST
#include "csm.h"
#include <stdio.h>

void PrintAttrBind (Binding attr)
{ 
  if (attr == NoBinding)
  { printf ("no attr binding\n");
    return;
  }
  printf ("Attr: %s.%s ",
    StringTable (GetNameSym (KeyOfEnv (EnvOf (attr)),0)),
    StringTable (IdnOf (attr)));
  { DefTableKey tp = GetAttrType (KeyOf(attr), NoKey);
    int cl = GetAttrClass (KeyOf (attr), NoClass);
    printf ("%s ",
      (cl == SYNTClass ? "SYNT" :
       cl == INHClass  ? "INH"  :
       "No Class"));
    printf ("%s\n",
      (tp == NoKey ? "No Type" :
         StringTable (GetNameSym (tp, 0))));
  }
}
#endif

#if defined(__cplusplus) || defined(__STDC__)
Binding SetCoordSymToBinding (Binding b, CoordPtr c, int sym)
#else
Binding SetCoordSymToBinding (b, c) Binding b; CoordPtr c; int sym;
#endif
{
  ResetCoord (KeyOf (b), c);
  ResetNameSym (KeyOf (b), sym);
  return b;
}


#if defined(__cplusplus) || defined(__STDC__)
int InheritAttrClass (Binding attr, int isTree)
#else
int InheritAttrClass (attr, isTree) Binding attr; int isTree;
#endif
/* on entry:
     attr is a binding of an attribute in an attribute
     scope of a symbol
   on exit:
     The class property is set and checked along the
     inheritance chain. It must be uniquely determined
     for each attribute (both CLASS or TREE).
     If the property is not specified at the end of the
     inheritance chain it is taken from an ATTR specification,
     if any.
     The class ist returned as result.
*/
{ DefTableKey attrkey; 
  int cl; int attrid; int triedInh = 0;
  Environment atenv;
  Binding over;

  if (attr == NoBinding) return NoClass;

  attrkey = KeyOf (attr);
  attrid = IdnOf (attr);
  cl = GetAttrClass (attrkey, NoClass);

  /* avoid multiple analysis in case of 
     multiple inheritance:
  */
  if (GetAttrClassDone (attrkey, 0)) return cl;
  ResetAttrClassDone (attrkey, 1);

  /* a deep search through overridden bindings
     establishes all class properties there 
  */
  atenv = EnvOf (attr);
  over = OverridesBinding (attr);
  while (over != NoBinding)
  {
    int inhcl = InheritAttrClass (over, 0);
    triedInh = 1;
    if (inhcl != NoClass)
    {
      SetChkAttrClass 
        (attrkey, attrid, inhcl, 
         GetCoord (KeyOf(over), NoPosition));
      if (cl == NoClass) cl = inhcl;
    }
    over = NextInhBinding (atenv, over);
  }

  if (cl == NoClass && !triedInh)
  /* the class is not determined by inheritance */
  { Binding attrname = BindingInEnv (attrEnv, attrid);
    int ancl = GetAttrClass (KeyOf (attrname), NoClass);
    if (ancl != NoClass)
      SetChkAttrClass 
        (attrkey, attrid, ancl, 
         GetCoord (KeyOf(attrname), NoPosition));
    cl = ancl;
  }
  if (cl == NoClass && (isTree || GetIsDefined (attrkey, 0)))
    message (ERROR, CatStrInd (
                    "Attribute class SYNT or INH is not known: ", attrid),
             0, GetCoord (attrkey, NoPosition));
#ifdef TEST
  PrintAttrBind (attr);
#endif
  return cl;
}/* InheritAttrClass */

#if defined(__cplusplus) || defined(__STDC__)
DefTableKey InheritAttrType (Binding attr, int isTree)
#else
DefTableKey InheritAttrType (attr, isTree) Binding attr; int isTree;
#endif
/* on entry:
     attr is a binding of an attribute in an attribute
     scope of a symbol
   on exit:
     The type property is set and checked along the
     inheritance chain. It may not be ambigously specified
     for any attribute (both CLASS or TREE). It may be 
     left unspecified for a CLASS symbol.
     If the property is not specified at the end of the
     inheritance chain it is taken from an ATTR specification,
     if any. If it is still unspecified it is set to VOID.
     The type is returned as result.
*/
{ DefTableKey attrkey; 
  DefTableKey tp; int attrid; int triedInh = 0;
  Environment atenv;
  Binding over;

  if (attr == NoBinding) return NoKey;

  attrkey = KeyOf (attr);
  attrid = IdnOf (attr);
  tp = GetAttrType (attrkey, NoKey);

  /* avoid multiple analysis in case of 
     multiple inheritance:
  */
  if (GetAttrTypeDone (attrkey, 0)) return tp;
  ResetAttrTypeDone (attrkey, 1);

  /* a deep search through overridden bindings
     establishes all type properties there 
  */
  atenv = EnvOf (attr);
  over = OverridesBinding (attr);
  while (over != NoBinding)
  {
    DefTableKey inhtp = InheritAttrType (over, 0);
    triedInh = 1;
    if (inhtp != NoKey)
    { CoordPtr inhcoord = GetAttrTypeCoord (KeyOf(over), NoPosition);
      if (inhcoord == NoPosition) 
         inhcoord = GetCoord (KeyOf(over), NoPosition);
      SetChkAttrType
        (attrkey, attrid, inhtp, inhcoord);
      if (tp == NoKey) tp = inhtp;
    }
    over = NextInhBinding (atenv, over);
  }

  if (tp == NoKey && !triedInh)
  /* the type is not determined by inheritance */
  { Binding attrname = BindingInEnv (attrEnv, attrid);
    DefTableKey antp = GetAttrType (KeyOf (attrname), NoKey);
    if (antp != NoKey)
      SetChkAttrType 
        (attrkey, attrid, antp, 
         GetCoord (KeyOf(attrname), NoPosition));
    tp = antp;
  }
  if (tp == NoKey && isTree)
  {
    ResetAttrType (attrkey, VOIDkey);
    ResetAttrTypeDefault (attrkey, 1);
    tp = VOIDkey;
  }
#ifdef TEST
  PrintAttrBind (attr);
#endif
  return tp;
}/* InheritAttrType */

#if defined(__cplusplus) || defined(__STDC__)
void InheritAttributes (Environment globenv, Environment attrenv)
#else
void InheritAttributes (globenv, attrenv)
   Environment globenv, attrenv;
#endif
/* on entry
     the attribute properties are set from rule and symbol
     contexts, and from attribute specifications,
     the IsDefining property is set,
     the attribute name properties are set
   on exit
     attributes are bound for inherited that are defined,
     starting from a tree symbol attribute the properties
     are determined and checked along the inheritance chain;
     if properties are still open they are taken from an
     attribute name specifications or set to VOID type
*/
{ Binding gl;
  globEnv = globenv;
  attrEnv = attrenv;

#ifdef TEST
      printf ("InheritAttributes begin\n");
#endif
  gl = DefinitionsOf (globEnv);
  while (gl != NoBinding)
  { DefTableKey k = KeyOf (gl);
    if (!GetIsTerm (k, 0) && (GetIsRule (k,0) || GetIsTreeSym (k, 0)))
    { Environment symEnv = GetAttrScope (k, NoEnv);
      CoordPtr coord = GetCoord (k, NoPosition);
      int idn;
      int isRootSymbol =
             (GetIsTreeSym (k, 0) &&  GetIsRoot (k, 0));

#ifdef TEST
      printf ("SYMBOL/RULE: %s\n", StringTable (GetNameSym (k, 0)));
      if (isRootSymbol) printf ("is root symbol\n");
#endif
      /* try all string codes, includes all idn codes: */
      for (idn = 1; idn < numstr; idn++)
      { Binding at = BindingInEnv (symEnv, idn), newAttr;
        if (at != NoBinding)
        { if (EnvOf (at) != symEnv)
          { 
            /* inherit that attribute and its properties: */
            newAttr = 
               SetCoordSymToBinding (BindIdn (symEnv, idn), coord, idn);
            if (isRootSymbol)
                 /* root inherits all attributes as SYNT */
                 SetChkAttrClass (KeyOf (newAttr), idn, SYNTClass, coord);
            else
                 (void)InheritAttrClass (newAttr, 1);

            (void)InheritAttrType (newAttr, 1);
            ResetIsPlain (KeyOf (newAttr), GetIsPlain (KeyOf (at), 0));
          } else /* at has been bound in symEnv directly: */
          {   
               if (isRootSymbol)
                  /* root inherits all attributes as SYNT */
                  SetChkAttrClass (KeyOf (at), idn, SYNTClass, coord);
               else
                  (void)InheritAttrClass (at, 1);
              (void)InheritAttrType (at, 1);
          }
        }
      }
    }
    gl = NextDefinition (gl);
  }
#ifdef TEST
      printf ("InheritAttributes end\n");
#endif
}/* InheritAttributes */

#if defined(__cplusplus) || defined(__STDC__)
void SetChkAttrClass
   (DefTableKey attr, int attrid, int attrclass, CoordPtr coord)
#else
void SetChkAttrClass (attr, attrid, attrclass, coord)
    DefTableKey attr; int attrid, attrclass; CoordPtr coord;
#endif
{ int oldclass;
  if (attrclass == NoClass) return;
  oldclass = GetAttrClass (attr, NoClass);
  if (oldclass == attrclass) return;
  if (oldclass == NoClass)
  { ResetAttrClass (attr, attrclass);
    ResetAttrClassCoord (attr, coord);
    return;
  }
  if (GetAttrClassReported (attr, 0)) return;
  ResetAttrClassReported (attr, 1);
  message (ERROR, CatStrInd (
               oldclass == SYNTClass ?
               "Attribute is defined to be SYNT elsewhere: " :
               "Attribute is defined to be INH elsewhere: ",
               attrid),
            0, coord);
  message (ERROR, CatStrInd (
               attrclass == SYNTClass ?
               "Attribute is defined to be SYNT elsewhere: " :
               "Attribute is defined to be INH elsewhere: ",
               attrid),
            0, GetAttrClassCoord (attr, NoPosition));
}/* SetChkAttrClass */

#if defined(__cplusplus) || defined(__STDC__)
void SetChkAttrType
   (DefTableKey attr, int attrid, DefTableKey attrtype, CoordPtr coord)
#else
void SetChkAttrType (attr, attrid, attrtype, coord)
    DefTableKey attr, attrtype; int attrid; CoordPtr coord;
#endif
{ DefTableKey oldtype;
  if (attrtype == NoKey) return;
  oldtype = GetAttrType (attr, NoKey);
  if (oldtype == attrtype) return;
  if (oldtype == NoKey)
  { ResetAttrType (attr, attrtype);
    ResetAttrTypeCoord (attr, coord);
    return;
  }
  if (GetAttrTypeReported (attr, 0)) return;
  ResetAttrTypeReported (attr, 1);
  if (attrid != GENTREEsym) {
    message (ERROR, CatStrInd (
                 "Different type is specified elsewhere for: ",
                 attrid),
            0, coord);
    message (ERROR, CatStrInd (
                 "Different type is specified elsewhere for: ",
                 attrid),
              0, GetAttrTypeCoord (attr, NoPosition));
  }
}/* SetChkAttrType */

#if defined(__cplusplus) || defined(__STDC__)
void BindDefAttrs
  (int attrid, 
   DefTableKeyList symkeys,
   Environment chainscope,
   int attrclass,
   DefTableKey attrtype,
   CoordPtr coord)
#else
void BindDefAttrs 
  (attrid, symkeys, chainscope, attrclass, attrtype, coord)
   int attrid;
   DefTableKeyList symkeys;
   Environment chainscope;
   int attrclass;
   DefTableKey attrtype;
   CoordPtr coord;
#endif
{ DefTableKey k = KeyInScope (chainscope, attrid);

  if (k != NoKey)
  { message (ERROR, CatStrInd (
               "Attribute name must not be a CHAIN name: ",
               attrid),
             0, coord);
    return;
  }

  while (symkeys != NULLDefTableKeyList)
  { DefTableKey symkey = HeadDefTableKeyList (symkeys);
    Environment attrenv = GetAttrScope (symkey, NoEnv);
    k = DefineIdn (attrenv, attrid);
    ResetNameSym (k, attrid);
    SetOnceCoord (k, coord);
    SetChkAttrClass (k, attrid, attrclass, coord);
    SetChkAttrType (k, attrid, attrtype, coord);
    symkeys = TailDefTableKeyList (symkeys);
  }
}/* BindDefAttrs */
