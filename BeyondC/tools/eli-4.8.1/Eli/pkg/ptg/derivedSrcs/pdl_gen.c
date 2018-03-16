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
#define TYPE PatElemList

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct PatElemListElt))

typedef struct PatElemListElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *PatElemListProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetPatElemList (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetPatElemList (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  PatElemListProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetPatElemList (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetPatElemList (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  PatElemListProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetPatElemList (int _property, DefTableKey key, TYPE _val)
#else
void
ResetPatElemList (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  PatElemListProperty _Item;
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
#define TYPE CharPtr

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct CharPtrElt))

typedef struct CharPtrElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *CharPtrProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetCharPtr (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetCharPtr (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  CharPtrProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetCharPtr (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetCharPtr (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  CharPtrProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetCharPtr (int _property, DefTableKey key, TYPE _val)
#else
void
ResetCharPtr (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  CharPtrProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE

static struct PropElt PDLe0 = {(Entry)0, 0};
static struct intElt PDLe1 = {(Entry)&PDLe0, 2, 1};
static struct intElt PDLe2 = {(Entry)&PDLe0, 2, 1};
static struct intElt PDLe3 = {(Entry)&PDLe0, 2, 1};
static struct intElt PDLe4 = {(Entry)&PDLe0, 2, 1};
static struct intElt PDLe5 = {(Entry)&PDLe0, 2, 1};
static struct intElt PDLe6 = {(Entry)&PDLe0, 2, 1};
static struct intElt PDLe7 = {(Entry)&PDLe0, 2, 1};
static struct intElt PDLe8 = {(Entry)&PDLe0, 2, 1};

struct PropList PDLk[] = {
  {(Entry)&PDLe1},
  {(Entry)&PDLe2},
  {(Entry)&PDLe3},
  {(Entry)&PDLe4},
  {(Entry)&PDLe5},
  {(Entry)&PDLe6},
  {(Entry)&PDLe7},
  {(Entry)&PDLe8},
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
         ResetisPredefined (k, ((intProperty)e)->PropVal);
         break;
      case 3:
         ResetType (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 4:
         ResetIndex (k, ((intProperty)e)->PropVal);
         break;
      case 5:
         ResetArgumentTypes (k, ((DefTableKeyListProperty)e)->PropVal);
         break;
      case 6:
         ResetIsInconsistent (k, ((intProperty)e)->PropVal);
         break;
      case 7:
         ResetPattern (k, ((PatElemListProperty)e)->PropVal);
         break;
      case 8:
         ResetIsMultDef (k, ((intProperty)e)->PropVal);
         break;
      case 9:
         ResetDoIt (k, ((intProperty)e)->PropVal);
         break;
      case 10:
         ResetUsed (k, ((intProperty)e)->PropVal);
         break;
      case 11:
         ResetTargetType (k, ((PTGNodeProperty)e)->PropVal);
         break;
      case 12:
         ResetOutputName (k, ((CharPtrProperty)e)->PropVal);
         break;
      case 13:
         ResethasFreeOccurrence (k, ((intProperty)e)->PropVal);
         break;
      }
  }
  return k;
}

#ifdef MONITOR
static CONST char *pdl_names[] = {
    (char *)0,
    "ClpValue",
    "isPredefined",
    "Type",
    "Index",
    "ArgumentTypes",
    "IsInconsistent",
    "Pattern",
    "IsMultDef",
    "DoIt",
    "Used",
    "TargetType",
    "OutputName",
    "hasFreeOccurrence",
};
static CONST char *pdl_types[] = {
    (char *)0,
    "int",
    "int",
    "DefTableKey",
    "int",
    "DefTableKeyList",
    "int",
    "PatElemList",
    "int",
    "int",
    "int",
    "PTGNode",
    "CharPtr",
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
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTDefTableKeyList
                DAPTO_RESULTDefTableKeyList (((DefTableKeyListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyListProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTPatElemList
                DAPTO_RESULTPatElemList (((PatElemListProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PatElemListProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTPTGNode
                DAPTO_RESULTPTGNode (((PTGNodeProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PTGNodeProperty)e)->PropVal);
#endif
                break;
            case 12:
#ifdef DAPTO_RESULTCharPtr
                DAPTO_RESULTCharPtr (((CharPtrProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((CharPtrProperty)e)->PropVal);
#endif
                break;
            case 13:
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
