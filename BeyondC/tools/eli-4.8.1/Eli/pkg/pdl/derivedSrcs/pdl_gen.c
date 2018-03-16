#include "pdl_gen.h"

#ifdef MONITOR
#include "pdl_dapto.h"
#endif

#define PRESENT find(key, _property, (Entry *)&_Item, 0)
#define VALUE (_Item->PropVal)

#define TYPE int

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct intElt))

typedef struct intElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *intProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getint (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getint (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  intProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setint (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setint (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  intProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetint (int _property, DefTableKey key, TYPE _val)
#else
void
Resetint (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  intProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#if defined(__STDC__) || defined(__cplusplus)
TYPE
SetGetint (int _property, DefTableKey key, TYPE init, TYPE reset)
#else
TYPE
SetGetint (_property, key, init, reset)
int _property;
DefTableKey key;
TYPE init;
TYPE reset;
#endif
{  intProperty _Item;
{ if (key == NoKey) return init;
  if (ACCESS)   {VALUE = reset; return reset;}
  else          {VALUE = init; return init;}
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Isint (int _property, DefTableKey key, TYPE _which, TYPE _error)
#else
void
Isint (_property, key, _which, _error)
int _property;
DefTableKey key;
TYPE _which;
TYPE _error;
#endif
{  intProperty _Item;
{ if (key == NoKey) return;
  if (!ACCESS) VALUE = _which;
  else if (VALUE != _which) VALUE = _error;
}
}

#if defined(__STDC__) || defined(__cplusplus)
int
Hasint (int _property, DefTableKey key)
#else
int
Hasint (_property, key)
int _property;
DefTableKey key;
#endif
{  intProperty _Item;
{ if (key == NoKey) return 0;
  return PRESENT;
}
}

#undef ACCESS
#undef TYPE
#define TYPE OpOutput

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct OpOutputElt))

typedef struct OpOutputElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *OpOutputProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetOpOutput (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetOpOutput (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  OpOutputProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetOpOutput (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetOpOutput (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  OpOutputProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetOpOutput (int _property, DefTableKey key, TYPE _val)
#else
void
ResetOpOutput (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  OpOutputProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE PTGNode

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct PTGNodeElt))

typedef struct PTGNodeElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *PTGNodeProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetPTGNode (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetPTGNode (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  PTGNodeProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetPTGNode (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetPTGNode (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  PTGNodeProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetPTGNode (int _property, DefTableKey key, TYPE _val)
#else
void
ResetPTGNode (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  PTGNodeProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE ExtOutput

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct ExtOutputElt))

typedef struct ExtOutputElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *ExtOutputProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetExtOutput (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetExtOutput (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  ExtOutputProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetExtOutput (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetExtOutput (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  ExtOutputProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetExtOutput (int _property, DefTableKey key, TYPE _val)
#else
void
ResetExtOutput (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  ExtOutputProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE DefTableKey

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct DefTableKeyElt))

typedef struct DefTableKeyElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *DefTableKeyProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetDefTableKey (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetDefTableKey (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  DefTableKeyProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetDefTableKey (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetDefTableKey (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  DefTableKeyProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetDefTableKey (int _property, DefTableKey key, TYPE _val)
#else
void
ResetDefTableKey (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  DefTableKeyProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE funclist

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct funclistElt))

typedef struct funclistElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *funclistProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getfunclist (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getfunclist (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  funclistProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setfunclist (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setfunclist (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  funclistProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetfunclist (int _property, DefTableKey key, TYPE _val)
#else
void
Resetfunclist (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  funclistProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE Environment

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct EnvironmentElt))

typedef struct EnvironmentElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *EnvironmentProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetEnvironment (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetEnvironment (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  EnvironmentProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetEnvironment (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetEnvironment (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  EnvironmentProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetEnvironment (int _property, DefTableKey key, TYPE _val)
#else
void
ResetEnvironment (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  EnvironmentProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE ElementList

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct ElementListElt))

typedef struct ElementListElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *ElementListProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetElementList (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetElementList (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  ElementListProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetElementList (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetElementList (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  ElementListProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetElementList (int _property, DefTableKey key, TYPE _val)
#else
void
ResetElementList (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  ElementListProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ListInsertElementList (int _property, DefTableKey key, Element elt)
#else
void
ListInsertElementList (_property, key, elt)
int _property;
DefTableKey key;
Element elt;
#endif
{  ElementListProperty _Item;
{
  if (!ACCESS)
    VALUE = NULLElementList;
  VALUE = OrderedInsertElementList(VALUE, elt, CmpElements);
}
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode
FirstElementList (int _property, DefTableKey key)
#else
PTGNode
FirstElementList (_property, key)
int _property;
DefTableKey key;
#endif
{  ElementListProperty _Item;
{
  if (PRESENT)
    return HeadElementList(VALUE)->name;
  else
    return PTGEndList();
}
}

#undef ACCESS
#undef TYPE

static struct PropElt PDLe0 = {(Entry)0, 0};

DefTableKey
#if defined(__STDC__) || defined(__cplusplus)
CloneKey (DefTableKey key)
#else
CloneKey (key)
    DefTableKey key;
#endif
{
  DefTableKey k;
  Entry e;

  if (key == NoKey) return NoKey;
  k = NewKey ();
  for (e = key->List; (e != (Entry)0) && (e->selector != 0);
       e = e->next) {
    switch (e->selector) {
      case 1:
         ResetClpValue (k, ((intProperty)e)->PropVal);
         break;
      case 2:
         ResetKind (k, ((intProperty)e)->PropVal);
         break;
      case 3:
         ResetFuncOut (k, ((OpOutputProperty)e)->PropVal);
         break;
      case 4:
         ResetArgList (k, ((PTGNodeProperty)e)->PropVal);
         break;
      case 5:
         ResetFormalList (k, ((PTGNodeProperty)e)->PropVal);
         break;
      case 6:
         ResetExtOut (k, ((ExtOutputProperty)e)->PropVal);
         break;
      case 7:
         ResetSym (k, ((intProperty)e)->PropVal);
         break;
      case 8:
         ResetDefine (k, ((intProperty)e)->PropVal);
         break;
      case 9:
         ResetType (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 10:
         ResetFuncList (k, ((funclistProperty)e)->PropVal);
         break;
      case 11:
         ResetGenFuncs (k, ((intProperty)e)->PropVal);
         break;
      case 12:
         ResetTypeName (k, ((PTGNodeProperty)e)->PropVal);
         break;
      case 13:
         ResetFirst (k, ((intProperty)e)->PropVal);
         break;
      case 14:
         ResetGenExts (k, ((intProperty)e)->PropVal);
         break;
      case 15:
         ResetGenMacros (k, ((intProperty)e)->PropVal);
         break;
      case 16:
         ResetSelector (k, ((intProperty)e)->PropVal);
         break;
      case 17:
         ResetEnv (k, ((EnvironmentProperty)e)->PropVal);
         break;
      case 18:
         ResetValueList (k, ((ElementListProperty)e)->PropVal);
         break;
      case 19:
         ResetText (k, ((intProperty)e)->PropVal);
         break;
      case 20:
         ResetElementDone (k, ((intProperty)e)->PropVal);
         break;
      case 21:
         ResetGenCloneCases (k, ((intProperty)e)->PropVal);
         break;
      case 22:
         ResetKnownKeyFirstOcc (k, ((intProperty)e)->PropVal);
         break;
      }
  }
  return k;
}

#ifdef MONITOR
static CONST char *pdl_names[] = {
    (char *)0,
    "ClpValue",
    "Kind",
    "FuncOut",
    "ArgList",
    "FormalList",
    "ExtOut",
    "Sym",
    "Define",
    "Type",
    "FuncList",
    "GenFuncs",
    "TypeName",
    "First",
    "GenExts",
    "GenMacros",
    "Selector",
    "Env",
    "ValueList",
    "Text",
    "ElementDone",
    "GenCloneCases",
    "KnownKeyFirstOcc",
};
static CONST char *pdl_types[] = {
    (char *)0,
    "int",
    "int",
    "OpOutput",
    "PTGNode",
    "PTGNode",
    "ExtOutput",
    "int",
    "int",
    "DefTableKey",
    "funclist",
    "int",
    "PTGNode",
    "int",
    "int",
    "int",
    "int",
    "Environment",
    "ElementList",
    "int",
    "int",
    "int",
    "int",
};

void
#if defined(__STDC__) || defined(__cplusplus)
pdl_mon_properties(DefTableKey k)
#else
pdl_mon_properties(k) DefTableKey k;
#endif
{
    Entry e;
    if (k == NoKey) return;
    for (e = k->List; (e != (Entry)0) && (e->selector != 0);
         e = e->next) {
        DAPTO_RESULT_STR (pdl_names[e->selector]);
        DAPTO_RESULT_STR (pdl_types[e->selector]);
        switch (e->selector) {
            case 1:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 2:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 3:
#ifdef DAPTO_RESULTOpOutput
                DAPTO_RESULTOpOutput (((OpOutputProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((OpOutputProperty)e)->PropVal);
#endif
                break;
            case 4:
#ifdef DAPTO_RESULTPTGNode
                DAPTO_RESULTPTGNode (((PTGNodeProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PTGNodeProperty)e)->PropVal);
#endif
                break;
            case 5:
#ifdef DAPTO_RESULTPTGNode
                DAPTO_RESULTPTGNode (((PTGNodeProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PTGNodeProperty)e)->PropVal);
#endif
                break;
            case 6:
#ifdef DAPTO_RESULTExtOutput
                DAPTO_RESULTExtOutput (((ExtOutputProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((ExtOutputProperty)e)->PropVal);
#endif
                break;
            case 7:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 8:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 9:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 10:
#ifdef DAPTO_RESULTfunclist
                DAPTO_RESULTfunclist (((funclistProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((funclistProperty)e)->PropVal);
#endif
                break;
            case 11:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 12:
#ifdef DAPTO_RESULTPTGNode
                DAPTO_RESULTPTGNode (((PTGNodeProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PTGNodeProperty)e)->PropVal);
#endif
                break;
            case 13:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 14:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 15:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 16:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 17:
#ifdef DAPTO_RESULTEnvironment
                DAPTO_RESULTEnvironment (((EnvironmentProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((EnvironmentProperty)e)->PropVal);
#endif
                break;
            case 18:
#ifdef DAPTO_RESULTElementList
                DAPTO_RESULTElementList (((ElementListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((ElementListProperty)e)->PropVal);
#endif
                break;
            case 19:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 20:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 21:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 22:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            default: DAPTO_RESULT_STR ("unknown property");
        }
    }
}
#endif
