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
DefTableKey
KResetint (int _property, DefTableKey key, TYPE val)
#else
DefTableKey
KResetint (_property, key, val)
int _property;
DefTableKey key;
TYPE val;
#endif
{  intProperty _Item;
{ if (key == NoKey) return NoKey;
  ACCESS; VALUE = val; return key;
}
}

#if defined(__STDC__) || defined(__cplusplus)
charp
Strint (int _property, DefTableKey key)
#else
charp
Strint (_property, key)
int _property;
DefTableKey key;
#endif
{  intProperty _Item;
{ if (key == NoKey) return ((char *)0);
  if (PRESENT) return StringTable(VALUE);
  else return ((char *)0);
}
}

#if defined(__STDC__) || defined(__cplusplus)
int
Incint (int _property, DefTableKey key)
#else
int
Incint (_property, key)
int _property;
DefTableKey key;
#endif
{  intProperty _Item;
{ if (key == NoKey) return 0;
  if (ACCESS) ++VALUE;
  else VALUE = 1;
  return VALUE;
}
}

#undef ACCESS
#undef TYPE
#define TYPE DefTableKeyList

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct DefTableKeyListElt))

typedef struct DefTableKeyListElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *DefTableKeyListProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetDefTableKeyList (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetDefTableKeyList (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  DefTableKeyListProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetDefTableKeyList (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetDefTableKeyList (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  DefTableKeyListProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetDefTableKeyList (int _property, DefTableKey key, TYPE _val)
#else
void
ResetDefTableKeyList (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  DefTableKeyListProperty _Item;
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

#if defined(__STDC__) || defined(__cplusplus)
DefTableKey
KResetDefTableKey (int _property, DefTableKey key, TYPE val)
#else
DefTableKey
KResetDefTableKey (_property, key, val)
int _property;
DefTableKey key;
TYPE val;
#endif
{  DefTableKeyProperty _Item;
{ if (key == NoKey) return NoKey;
  ACCESS; VALUE = val; return key;
}
}

#undef ACCESS
#undef TYPE
#define TYPE SymbolPList

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct SymbolPListElt))

typedef struct SymbolPListElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *SymbolPListProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetSymbolPList (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetSymbolPList (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  SymbolPListProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetSymbolPList (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetSymbolPList (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  SymbolPListProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetSymbolPList (int _property, DefTableKey key, TYPE _val)
#else
void
ResetSymbolPList (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  SymbolPListProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE tOilOp

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct tOilOpElt))

typedef struct tOilOpElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *tOilOpProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GettOilOp (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GettOilOp (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  tOilOpProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SettOilOp (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SettOilOp (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  tOilOpProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResettOilOp (int _property, DefTableKey key, TYPE _val)
#else
void
ResettOilOp (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  tOilOpProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE tOilType

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct tOilTypeElt))

typedef struct tOilTypeElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *tOilTypeProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GettOilType (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GettOilType (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  tOilTypeProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SettOilType (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SettOilType (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  tOilTypeProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResettOilType (int _property, DefTableKey key, TYPE _val)
#else
void
ResettOilType (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  tOilTypeProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE intList

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct intListElt))

typedef struct intListElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *intListProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetintList (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetintList (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  intListProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetintList (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetintList (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  intListProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetintList (int _property, DefTableKey key, TYPE _val)
#else
void
ResetintList (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  intListProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE tOilClass

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct tOilClassElt))

typedef struct tOilClassElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *tOilClassProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GettOilClass (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GettOilClass (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  tOilClassProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SettOilClass (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SettOilClass (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  tOilClassProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResettOilClass (int _property, DefTableKey key, TYPE _val)
#else
void
ResettOilClass (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  tOilClassProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
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
         ResetAbsDone (k, ((intProperty)e)->PropVal);
         break;
      case 3:
         ResetListChainDone (k, ((intProperty)e)->PropVal);
         break;
      case 4:
         ResetChainDone (k, ((intProperty)e)->PropVal);
         break;
      case 5:
         ResetPChainDone (k, ((intProperty)e)->PropVal);
         break;
      case 6:
         ResetLISTOFDone (k, ((intProperty)e)->PropVal);
         break;
      case 7:
         ResetPLISTOFDone (k, ((intProperty)e)->PropVal);
         break;
      case 8:
         ResetConRules (k, ((DefTableKeyListProperty)e)->PropVal);
         break;
      case 9:
         ResetAbsRules (k, ((DefTableKeyListProperty)e)->PropVal);
         break;
      case 10:
         ResetRHSConRules (k, ((DefTableKeyListProperty)e)->PropVal);
         break;
      case 11:
         ResetLHS (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 12:
         ResetRHS (k, ((SymbolPListProperty)e)->PropVal);
         break;
      case 13:
         ResetType (k, ((intProperty)e)->PropVal);
         break;
      case 14:
         ResetOilOp (k, ((tOilOpProperty)e)->PropVal);
         break;
      case 15:
         ResetOilType (k, ((tOilTypeProperty)e)->PropVal);
         break;
      case 16:
         ResetNTCount (k, ((intProperty)e)->PropVal);
         break;
      case 17:
         ResetArgCount (k, ((intProperty)e)->PropVal);
         break;
      case 18:
         ResetStr (k, ((intProperty)e)->PropVal);
         break;
      case 19:
         ResetBottomUp (k, ((intProperty)e)->PropVal);
         break;
      case 20:
         ResetMap (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 21:
         ResetAbsMap (k, ((DefTableKeyListProperty)e)->PropVal);
         break;
      case 22:
         ResetOrder (k, ((intListProperty)e)->PropVal);
         break;
      case 23:
         ResetEqClass (k, ((intProperty)e)->PropVal);
         break;
      case 24:
         ResetMappedRHS (k, ((SymbolPListProperty)e)->PropVal);
         break;
      case 25:
         ResetMatch (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 26:
         ResetAbsMatch (k, ((DefTableKeyListProperty)e)->PropVal);
         break;
      case 27:
         ResetDuplicate (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 28:
         ResetTraversal (k, ((intProperty)e)->PropVal);
         break;
      case 29:
         ResetBadRootError (k, ((intProperty)e)->PropVal);
         break;
      case 30:
         ResetRecursive (k, ((intProperty)e)->PropVal);
         break;
      case 31:
         ResetIsRHS (k, ((intProperty)e)->PropVal);
         break;
      case 32:
         ResetNonTerm (k, ((intProperty)e)->PropVal);
         break;
      case 33:
         ResetStart (k, ((intProperty)e)->PropVal);
         break;
      case 34:
         ResetReach (k, ((intProperty)e)->PropVal);
         break;
      case 35:
         ResetConSym (k, ((intProperty)e)->PropVal);
         break;
      case 36:
         ResetIsCon (k, ((intProperty)e)->PropVal);
         break;
      case 37:
         ResetIsAbs (k, ((intProperty)e)->PropVal);
         break;
      case 38:
         ResetRootErr (k, ((intProperty)e)->PropVal);
         break;
      case 39:
         ResetSibling (k, ((intProperty)e)->PropVal);
         break;
      case 40:
         ResetOilClass (k, ((tOilClassProperty)e)->PropVal);
         break;
      case 41:
         ResetFirstOcc (k, ((intProperty)e)->PropVal);
         break;
      }
  }
  return k;
}

#ifdef MONITOR
static CONST char *pdl_names[] = {
    (char *)0,
    "ClpValue",
    "AbsDone",
    "ListChainDone",
    "ChainDone",
    "PChainDone",
    "LISTOFDone",
    "PLISTOFDone",
    "ConRules",
    "AbsRules",
    "RHSConRules",
    "LHS",
    "RHS",
    "Type",
    "OilOp",
    "OilType",
    "NTCount",
    "ArgCount",
    "Str",
    "BottomUp",
    "Map",
    "AbsMap",
    "Order",
    "EqClass",
    "MappedRHS",
    "Match",
    "AbsMatch",
    "Duplicate",
    "Traversal",
    "BadRootError",
    "Recursive",
    "IsRHS",
    "NonTerm",
    "Start",
    "Reach",
    "ConSym",
    "IsCon",
    "IsAbs",
    "RootErr",
    "Sibling",
    "OilClass",
    "FirstOcc",
};
static CONST char *pdl_types[] = {
    (char *)0,
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "DefTableKeyList",
    "DefTableKeyList",
    "DefTableKeyList",
    "DefTableKey",
    "SymbolPList",
    "int",
    "tOilOp",
    "tOilType",
    "int",
    "int",
    "int",
    "int",
    "DefTableKey",
    "DefTableKeyList",
    "intList",
    "int",
    "SymbolPList",
    "DefTableKey",
    "DefTableKeyList",
    "DefTableKey",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "tOilClass",
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
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 4:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 5:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 6:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTDefTableKeyList
                DAPTO_RESULTDefTableKeyList (((DefTableKeyListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyListProperty)e)->PropVal);
#endif
                break;
            case 9:
#ifdef DAPTO_RESULTDefTableKeyList
                DAPTO_RESULTDefTableKeyList (((DefTableKeyListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyListProperty)e)->PropVal);
#endif
                break;
            case 10:
#ifdef DAPTO_RESULTDefTableKeyList
                DAPTO_RESULTDefTableKeyList (((DefTableKeyListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyListProperty)e)->PropVal);
#endif
                break;
            case 11:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 12:
#ifdef DAPTO_RESULTSymbolPList
                DAPTO_RESULTSymbolPList (((SymbolPListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((SymbolPListProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTtOilOp
                DAPTO_RESULTtOilOp (((tOilOpProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((tOilOpProperty)e)->PropVal);
#endif
                break;
            case 15:
#ifdef DAPTO_RESULTtOilType
                DAPTO_RESULTtOilType (((tOilTypeProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((tOilTypeProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 18:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 21:
#ifdef DAPTO_RESULTDefTableKeyList
                DAPTO_RESULTDefTableKeyList (((DefTableKeyListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyListProperty)e)->PropVal);
#endif
                break;
            case 22:
#ifdef DAPTO_RESULTintList
                DAPTO_RESULTintList (((intListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intListProperty)e)->PropVal);
#endif
                break;
            case 23:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 24:
#ifdef DAPTO_RESULTSymbolPList
                DAPTO_RESULTSymbolPList (((SymbolPListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((SymbolPListProperty)e)->PropVal);
#endif
                break;
            case 25:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 26:
#ifdef DAPTO_RESULTDefTableKeyList
                DAPTO_RESULTDefTableKeyList (((DefTableKeyListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyListProperty)e)->PropVal);
#endif
                break;
            case 27:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 28:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 29:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 30:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 31:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 32:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 33:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 34:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 35:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 36:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 37:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 38:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 39:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 40:
#ifdef DAPTO_RESULTtOilClass
                DAPTO_RESULTtOilClass (((tOilClassProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((tOilClassProperty)e)->PropVal);
#endif
                break;
            case 41:
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
