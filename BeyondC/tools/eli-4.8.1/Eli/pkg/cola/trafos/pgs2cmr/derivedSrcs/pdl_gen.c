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

#undef ACCESS
#undef TYPE
#define TYPE DID

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct DIDElt))

typedef struct DIDElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *DIDProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetDID (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetDID (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  DIDProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetDID (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetDID (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  DIDProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetDID (int _property, DefTableKey key, TYPE _val)
#else
void
ResetDID (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  DIDProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE def_entry

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct def_entryElt))

typedef struct def_entryElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *def_entryProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getdef_entry (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getdef_entry (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  def_entryProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setdef_entry (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setdef_entry (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  def_entryProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetdef_entry (int _property, DefTableKey key, TYPE _val)
#else
void
Resetdef_entry (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  def_entryProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE SID

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct SIDElt))

typedef struct SIDElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *SIDProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetSID (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetSID (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  SIDProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetSID (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetSID (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  SIDProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetSID (int _property, DefTableKey key, TYPE _val)
#else
void
ResetSID (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  SIDProperty _Item;
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
         ResetClass (k, ((intProperty)e)->PropVal);
         break;
      case 3:
         ResetNoStart (k, ((intProperty)e)->PropVal);
         break;
      case 4:
         ResetNullNt (k, ((DIDProperty)e)->PropVal);
         break;
      case 5:
         ResetDef (k, ((def_entryProperty)e)->PropVal);
         break;
      case 6:
         ResetOtherDef (k, ((def_entryProperty)e)->PropVal);
         break;
      case 7:
         ResetReduceDef (k, ((def_entryProperty)e)->PropVal);
         break;
      case 8:
         ResetNoReduceDef (k, ((def_entryProperty)e)->PropVal);
         break;
      case 9:
         ResetConnectDef (k, ((def_entryProperty)e)->PropVal);
         break;
      case 10:
         ResetSid (k, ((SIDProperty)e)->PropVal);
         break;
      case 11:
         ResetChain (k, ((intProperty)e)->PropVal);
         break;
      case 12:
         ResetReplace (k, ((DefTableKeyProperty)e)->PropVal);
         break;
      case 13:
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
    "Class",
    "NoStart",
    "NullNt",
    "Def",
    "OtherDef",
    "ReduceDef",
    "NoReduceDef",
    "ConnectDef",
    "Sid",
    "Chain",
    "Replace",
    "FirstOcc",
};
static CONST char *pdl_types[] = {
    (char *)0,
    "int",
    "int",
    "int",
    "DID",
    "def_entry",
    "def_entry",
    "def_entry",
    "def_entry",
    "def_entry",
    "SID",
    "int",
    "DefTableKey",
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
#ifdef DAPTO_RESULTDID
                DAPTO_RESULTDID (((DIDProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DIDProperty)e)->PropVal);
#endif
                break;
            case 5:
#ifdef DAPTO_RESULTdef_entry
                DAPTO_RESULTdef_entry (((def_entryProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((def_entryProperty)e)->PropVal);
#endif
                break;
            case 6:
#ifdef DAPTO_RESULTdef_entry
                DAPTO_RESULTdef_entry (((def_entryProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((def_entryProperty)e)->PropVal);
#endif
                break;
            case 7:
#ifdef DAPTO_RESULTdef_entry
                DAPTO_RESULTdef_entry (((def_entryProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((def_entryProperty)e)->PropVal);
#endif
                break;
            case 8:
#ifdef DAPTO_RESULTdef_entry
                DAPTO_RESULTdef_entry (((def_entryProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((def_entryProperty)e)->PropVal);
#endif
                break;
            case 9:
#ifdef DAPTO_RESULTdef_entry
                DAPTO_RESULTdef_entry (((def_entryProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((def_entryProperty)e)->PropVal);
#endif
                break;
            case 10:
#ifdef DAPTO_RESULTSID
                DAPTO_RESULTSID (((SIDProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((SIDProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTDefTableKey
                DAPTO_RESULTDefTableKey (((DefTableKeyProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((DefTableKeyProperty)e)->PropVal);
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
