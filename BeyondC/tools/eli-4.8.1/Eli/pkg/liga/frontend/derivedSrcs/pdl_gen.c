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

#undef ACCESS
#undef TYPE
#define TYPE CoordPtr

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct CoordPtrElt))

typedef struct CoordPtrElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *CoordPtrProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetCoordPtr (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetCoordPtr (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  CoordPtrProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetCoordPtr (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetCoordPtr (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  CoordPtrProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetCoordPtr (int _property, DefTableKey key, TYPE _val)
#else
void
ResetCoordPtr (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  CoordPtrProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#if defined(__STDC__) || defined(__cplusplus)
TYPE
SetOnceCoordPtr (int _property, DefTableKey key, TYPE val)
#else
TYPE
SetOnceCoordPtr (_property, key, val)
int _property;
DefTableKey key;
TYPE val;
#endif
{  CoordPtrProperty _Item;
{ if (key == NoKey) return val;
  if (!ACCESS) VALUE = val;
  return VALUE;
}
}

#undef ACCESS
#undef TYPE
#define TYPE RuleProd

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct RuleProdElt))

typedef struct RuleProdElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *RuleProdProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetRuleProd (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetRuleProd (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  RuleProdProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetRuleProd (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetRuleProd (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  RuleProdProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetRuleProd (int _property, DefTableKey key, TYPE _val)
#else
void
ResetRuleProd (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  RuleProdProperty _Item;
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
void
SetDiffDefTableKey (int _property, DefTableKey key, TYPE thistype, TYPE diff)
#else
void
SetDiffDefTableKey (_property, key, thistype, diff)
int _property;
DefTableKey key;
TYPE thistype;
TYPE diff;
#endif
{  DefTableKeyProperty _Item;
{ if (key == NoKey) return;
  if (!ACCESS)                  VALUE = thistype;
  else if (VALUE != thistype)   VALUE = diff;
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
#define TYPE Binding

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct BindingElt))

typedef struct BindingElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *BindingProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetBinding (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetBinding (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  BindingProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetBinding (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetBinding (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  BindingProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetBinding (int _property, DefTableKey key, TYPE _val)
#else
void
ResetBinding (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  BindingProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
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
#define TYPE SymbAttrList

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct SymbAttrListElt))

typedef struct SymbAttrListElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *SymbAttrListProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetSymbAttrList (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetSymbAttrList (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  SymbAttrListProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetSymbAttrList (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetSymbAttrList (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  SymbAttrListProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetSymbAttrList (int _property, DefTableKey key, TYPE _val)
#else
void
ResetSymbAttrList (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  SymbAttrListProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE PExpr

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct PExprElt))

typedef struct PExprElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *PExprProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetPExpr (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetPExpr (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  PExprProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetPExpr (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetPExpr (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  PExprProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetPExpr (int _property, DefTableKey key, TYPE _val)
#else
void
ResetPExpr (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  PExprProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE PExprList

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct PExprListElt))

typedef struct PExprListElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *PExprListProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetPExprList (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetPExprList (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  PExprListProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetPExprList (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetPExprList (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  PExprListProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetPExprList (int _property, DefTableKey key, TYPE _val)
#else
void
ResetPExprList (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  PExprListProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE

static struct PropElt PDLe0 = {(Entry)0, 0};

struct PropList PDLk[] = {
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0},
  {(Entry)&PDLe0}};

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
         ResetIsSymbol (k, ((intProperty)e)->PropVal);
         break;
      case 3:
         ResetIsType (k, ((intProperty)e)->PropVal);
         break;
      case 4:
         ResetIsRule (k, ((intProperty)e)->PropVal);
         break;
      case 5:
         ResetNameSym (k, ((intProperty)e)->PropVal);
         break;
      case 6:
         ResetCoord (k, ((CoordPtrProperty)e)->PropVal);
         break;
      case 7:
         ResetIsTREESym (k, ((intProperty)e)->PropVal);
         break;
      case 8:
         ResetIsCLASSSym (k, ((intProperty)e)->PropVal);
         break;
      case 9:
         ResetIsTREEReported (k, ((intProperty)e)->PropVal);
         break;
      case 10:
         ResetIsCLASSReported (k, ((intProperty)e)->PropVal);
         break;
      case 11:
         ResetIsNonterm (k, ((intProperty)e)->PropVal);
         break;
      case 12:
         ResetHasListof (k, ((intProperty)e)->PropVal);
         break;
      case 13:
         ResetHasNonListof (k, ((intProperty)e)->PropVal);
         break;
      case 14:
         ResetRule (k, ((RuleProdProperty)e)->PropVal);
         break;
      case 15:
         ResetLhsOfRule (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 16:
         ResetListofRuleOfLhs (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 17:
         ResetType (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 18:
         ResetIsTerm (k, ((intProperty)e)->PropVal);
         break;
      case 19:
         ResetIsRoot (k, ((intProperty)e)->PropVal);
         break;
      case 20:
         ResetTermReported (k, ((intProperty)e)->PropVal);
         break;
      case 21:
         ResetRootReported (k, ((intProperty)e)->PropVal);
         break;
      case 22:
         ResetIsTreeSym (k, ((intProperty)e)->PropVal);
         break;
      case 23:
         ResetIsNotInRuleReported (k, ((intProperty)e)->PropVal);
         break;
      case 24:
         ResetIsInRuleReported (k, ((intProperty)e)->PropVal);
         break;
      case 25:
         ResetIsClassInRuleReported (k, ((intProperty)e)->PropVal);
         break;
      case 26:
         ResetAttrScope (k, ((EnvironmentProperty)e)->PropVal);
         break;
      case 27:
         ResetIsDefined (k, ((intProperty)e)->PropVal);
         break;
      case 28:
         ResetAttrClass (k, ((intProperty)e)->PropVal);
         break;
      case 29:
         ResetAttrClassCoord (k, ((CoordPtrProperty)e)->PropVal);
         break;
      case 30:
         ResetAttrClassReported (k, ((intProperty)e)->PropVal);
         break;
      case 31:
         ResetAttrClassDone (k, ((intProperty)e)->PropVal);
         break;
      case 32:
         ResetAttrType (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 33:
         ResetAttrTypeCoord (k, ((CoordPtrProperty)e)->PropVal);
         break;
      case 34:
         ResetAttrTypeReported (k, ((intProperty)e)->PropVal);
         break;
      case 35:
         ResetAttrTypeDone (k, ((intProperty)e)->PropVal);
         break;
      case 36:
         ResetAttrTypeDefault (k, ((intProperty)e)->PropVal);
         break;
      case 37:
         ResetIsChain (k, ((intProperty)e)->PropVal);
         break;
      case 38:
         ResetUpperScope (k, ((EnvironmentProperty)e)->PropVal);
         break;
      case 39:
         ResetLowerScope (k, ((EnvironmentProperty)e)->PropVal);
         break;
      case 40:
         ResetHEADScope (k, ((EnvironmentProperty)e)->PropVal);
         break;
      case 41:
         ResetIsDefinedReported (k, ((intProperty)e)->PropVal);
         break;
      case 42:
         ResetIsUsed (k, ((intProperty)e)->PropVal);
         break;
      case 43:
         ResetIsMarked (k, ((intProperty)e)->PropVal);
         break;
      case 44:
         ResetCheckMult (k, ((intProperty)e)->PropVal);
         break;
      case 45:
         ResetInheritedFrom (k, ((BindingProperty)e)->PropVal);
         break;
      case 46:
         ResetInheritedBy (k, ((DefTableKeyListProperty)e)->PropVal);
         break;
      case 47:
         ResetAttribute (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 48:
         ResetContext (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 49:
         ResetIsRuleComputation (k, ((intProperty)e)->PropVal);
         break;
      case 50:
         ResetIsBottomUp (k, ((intProperty)e)->PropVal);
         break;
      case 51:
         ResetIsChainStart (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 52:
         ResetIsPlain (k, ((intProperty)e)->PropVal);
         break;
      case 53:
         ResetEmptyHEADChain (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 54:
         ResetEmptyHEADAttr (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 55:
         ResetEmptyHEADCompsOfRule (k, ((DefTableKeyListProperty)e)->PropVal);
         break;
      case 56:
         ResetRemoteAttr (k, ((intProperty)e)->PropVal);
         break;
      case 57:
         ResetIsIncluding (k, ((intProperty)e)->PropVal);
         break;
      case 58:
         ResetIsConstituent (k, ((intProperty)e)->PropVal);
         break;
      case 59:
         ResetIsConstituents (k, ((intProperty)e)->PropVal);
         break;
      case 60:
         ResetRemoteSet (k, ((SymbAttrListProperty)e)->PropVal);
         break;
      case 61:
         ResetShieldSet (k, ((DefTableKeyListProperty)e)->PropVal);
         break;
      case 62:
         ResetFunct2 (k, ((intProperty)e)->PropVal);
         break;
      case 63:
         ResetFunct1 (k, ((intProperty)e)->PropVal);
         break;
      case 64:
         ResetFunct0 (k, ((intProperty)e)->PropVal);
         break;
      case 65:
         ResetInComputations (k, ((DefTableKeyListProperty)e)->PropVal);
         break;
      case 66:
         ResetInVoidContext (k, ((intProperty)e)->PropVal);
         break;
      case 67:
         ResetInValueContext (k, ((intProperty)e)->PropVal);
         break;
      case 68:
         ResetRemoteEpxrIsErr (k, ((intProperty)e)->PropVal);
         break;
      case 69:
         ResetCompRepr (k, ((PExprProperty)e)->PropVal);
         break;
      case 70:
         ResetAllRuleComps (k, ((DefTableKeyListProperty)e)->PropVal);
         break;
      case 71:
         ResetIsLoopInit (k, ((intProperty)e)->PropVal);
         break;
      case 72:
         ResetIsGenTreeDummy (k, ((intProperty)e)->PropVal);
         break;
      case 73:
         ResetDid (k, ((intProperty)e)->PropVal);
         break;
      case 74:
         ResetRuleOfAttr (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 75:
         ResetHasAccuAsgn (k, ((intProperty)e)->PropVal);
         break;
      case 76:
         ResetHasNonAccuAsgn (k, ((intProperty)e)->PropVal);
         break;
      case 77:
         ResetHasAccuAsgnDone (k, ((intProperty)e)->PropVal);
         break;
      case 78:
         ResetIsAccu (k, ((intProperty)e)->PropVal);
         break;
      case 79:
         ResetAccuLhs (k, ((PExprProperty)e)->PropVal);
         break;
      case 80:
         ResetAccuExecList (k, ((PExprListProperty)e)->PropVal);
         break;
      case 81:
         ResetAccuDepList (k, ((PExprListProperty)e)->PropVal);
         break;
      }
  }
  return k;
}

#ifdef MONITOR
static CONST char *pdl_names[] = {
    (char *)0,
    "ClpValue",
    "IsSymbol",
    "IsType",
    "IsRule",
    "NameSym",
    "Coord",
    "IsTREESym",
    "IsCLASSSym",
    "IsTREEReported",
    "IsCLASSReported",
    "IsNonterm",
    "HasListof",
    "HasNonListof",
    "Rule",
    "LhsOfRule",
    "ListofRuleOfLhs",
    "Type",
    "IsTerm",
    "IsRoot",
    "TermReported",
    "RootReported",
    "IsTreeSym",
    "IsNotInRuleReported",
    "IsInRuleReported",
    "IsClassInRuleReported",
    "AttrScope",
    "IsDefined",
    "AttrClass",
    "AttrClassCoord",
    "AttrClassReported",
    "AttrClassDone",
    "AttrType",
    "AttrTypeCoord",
    "AttrTypeReported",
    "AttrTypeDone",
    "AttrTypeDefault",
    "IsChain",
    "UpperScope",
    "LowerScope",
    "HEADScope",
    "IsDefinedReported",
    "IsUsed",
    "IsMarked",
    "CheckMult",
    "InheritedFrom",
    "InheritedBy",
    "Attribute",
    "Context",
    "IsRuleComputation",
    "IsBottomUp",
    "IsChainStart",
    "IsPlain",
    "EmptyHEADChain",
    "EmptyHEADAttr",
    "EmptyHEADCompsOfRule",
    "RemoteAttr",
    "IsIncluding",
    "IsConstituent",
    "IsConstituents",
    "RemoteSet",
    "ShieldSet",
    "Funct2",
    "Funct1",
    "Funct0",
    "InComputations",
    "InVoidContext",
    "InValueContext",
    "RemoteEpxrIsErr",
    "CompRepr",
    "AllRuleComps",
    "IsLoopInit",
    "IsGenTreeDummy",
    "Did",
    "RuleOfAttr",
    "HasAccuAsgn",
    "HasNonAccuAsgn",
    "HasAccuAsgnDone",
    "IsAccu",
    "AccuLhs",
    "AccuExecList",
    "AccuDepList",
};
static CONST char *pdl_types[] = {
    (char *)0,
    "int",
    "int",
    "int",
    "int",
    "int",
    "CoordPtr",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "RuleProd",
    "DefTableKey",
    "DefTableKey",
    "DefTableKey",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "Environment",
    "int",
    "int",
    "CoordPtr",
    "int",
    "int",
    "DefTableKey",
    "CoordPtr",
    "int",
    "int",
    "int",
    "int",
    "Environment",
    "Environment",
    "Environment",
    "int",
    "int",
    "int",
    "int",
    "Binding",
    "DefTableKeyList",
    "DefTableKey",
    "DefTableKey",
    "int",
    "int",
    "DefTableKey",
    "int",
    "DefTableKey",
    "DefTableKey",
    "DefTableKeyList",
    "int",
    "int",
    "int",
    "int",
    "SymbAttrList",
    "DefTableKeyList",
    "int",
    "int",
    "int",
    "DefTableKeyList",
    "int",
    "int",
    "int",
    "PExpr",
    "DefTableKeyList",
    "int",
    "int",
    "int",
    "DefTableKey",
    "int",
    "int",
    "int",
    "int",
    "PExpr",
    "PExprList",
    "PExprList",
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
#ifdef DAPTO_RESULTCoordPtr
                DAPTO_RESULTCoordPtr (((CoordPtrProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((CoordPtrProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 10:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTRuleProd
                DAPTO_RESULTRuleProd (((RuleProdProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((RuleProdProperty)e)->PropVal);
#endif
                break;
            case 15:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 16:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 17:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
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
            case 23:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 24:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 25:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 26:
#ifdef DAPTO_RESULTEnvironment
                DAPTO_RESULTEnvironment (((EnvironmentProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((EnvironmentProperty)e)->PropVal);
#endif
                break;
            case 27:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTCoordPtr
                DAPTO_RESULTCoordPtr (((CoordPtrProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((CoordPtrProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 33:
#ifdef DAPTO_RESULTCoordPtr
                DAPTO_RESULTCoordPtr (((CoordPtrProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((CoordPtrProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTEnvironment
                DAPTO_RESULTEnvironment (((EnvironmentProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((EnvironmentProperty)e)->PropVal);
#endif
                break;
            case 39:
#ifdef DAPTO_RESULTEnvironment
                DAPTO_RESULTEnvironment (((EnvironmentProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((EnvironmentProperty)e)->PropVal);
#endif
                break;
            case 40:
#ifdef DAPTO_RESULTEnvironment
                DAPTO_RESULTEnvironment (((EnvironmentProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((EnvironmentProperty)e)->PropVal);
#endif
                break;
            case 41:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 42:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 43:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 44:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 45:
#ifdef DAPTO_RESULTBinding
                DAPTO_RESULTBinding (((BindingProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((BindingProperty)e)->PropVal);
#endif
                break;
            case 46:
#ifdef DAPTO_RESULTDefTableKeyList
                DAPTO_RESULTDefTableKeyList (((DefTableKeyListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyListProperty)e)->PropVal);
#endif
                break;
            case 47:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 48:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 49:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 50:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 51:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 52:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 53:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 54:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 55:
#ifdef DAPTO_RESULTDefTableKeyList
                DAPTO_RESULTDefTableKeyList (((DefTableKeyListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyListProperty)e)->PropVal);
#endif
                break;
            case 56:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 57:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 58:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 59:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 60:
#ifdef DAPTO_RESULTSymbAttrList
                DAPTO_RESULTSymbAttrList (((SymbAttrListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((SymbAttrListProperty)e)->PropVal);
#endif
                break;
            case 61:
#ifdef DAPTO_RESULTDefTableKeyList
                DAPTO_RESULTDefTableKeyList (((DefTableKeyListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyListProperty)e)->PropVal);
#endif
                break;
            case 62:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 63:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 64:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 65:
#ifdef DAPTO_RESULTDefTableKeyList
                DAPTO_RESULTDefTableKeyList (((DefTableKeyListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyListProperty)e)->PropVal);
#endif
                break;
            case 66:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 67:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 68:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 69:
#ifdef DAPTO_RESULTPExpr
                DAPTO_RESULTPExpr (((PExprProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PExprProperty)e)->PropVal);
#endif
                break;
            case 70:
#ifdef DAPTO_RESULTDefTableKeyList
                DAPTO_RESULTDefTableKeyList (((DefTableKeyListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyListProperty)e)->PropVal);
#endif
                break;
            case 71:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 72:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 73:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 74:
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
#endif
                break;
            case 75:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 76:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 77:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 78:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 79:
#ifdef DAPTO_RESULTPExpr
                DAPTO_RESULTPExpr (((PExprProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PExprProperty)e)->PropVal);
#endif
                break;
            case 80:
#ifdef DAPTO_RESULTPExprList
                DAPTO_RESULTPExprList (((PExprListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PExprListProperty)e)->PropVal);
#endif
                break;
            case 81:
#ifdef DAPTO_RESULTPExprList
                DAPTO_RESULTPExprList (((PExprListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PExprListProperty)e)->PropVal);
#endif
                break;
            default: DAPTO_RESULT_STR ("unknown property");
        }
    }
}
#endif
