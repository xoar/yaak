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
            default: DAPTO_RESULT_STR ("unknown property");
        }
    }
}
#endif
