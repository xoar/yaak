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

#if defined(__STDC__) || defined(__cplusplus)
void
GuaranteeCharPtr (int _property, DefTableKey key, TYPE val)
#else
void
GuaranteeCharPtr (_property, key, val)
int _property;
DefTableKey key;
TYPE val;
#endif
{  CharPtrProperty _Item;
{
  if (key == NoKey)
    return;
  else if (!ACCESS)
    VALUE = val;
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
         ResetUnique (k, ((intProperty)e)->PropVal);
         break;
      case 3:
         ResetRegex (k, ((CharPtrProperty)e)->PropVal);
         break;
      case 4:
         ResetEncoding (k, ((intProperty)e)->PropVal);
         break;
      case 5:
         ResetCounter (k, ((intProperty)e)->PropVal);
         break;
      case 6:
         ResetScanner (k, ((CharPtrProperty)e)->PropVal);
         break;
      case 7:
         ResetProcessor (k, ((CharPtrProperty)e)->PropVal);
         break;
      case 8:
         ResetStr (k, ((CharPtrProperty)e)->PropVal);
         break;
      }
  }
  return k;
}

#ifdef MONITOR
static CONST char *pdl_names[] = {
    (char *)0,
    "ClpValue",
    "Unique",
    "Regex",
    "Encoding",
    "Counter",
    "Scanner",
    "Processor",
    "Str",
};
static CONST char *pdl_types[] = {
    (char *)0,
    "int",
    "int",
    "CharPtr",
    "int",
    "int",
    "CharPtr",
    "CharPtr",
    "CharPtr",
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
#ifdef DAPTO_RESULTCharPtr
                DAPTO_RESULTCharPtr (((CharPtrProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((CharPtrProperty)e)->PropVal);
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
#ifdef DAPTO_RESULTCharPtr
                DAPTO_RESULTCharPtr (((CharPtrProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((CharPtrProperty)e)->PropVal);
#endif
                break;
            case 7:
#ifdef DAPTO_RESULTCharPtr
                DAPTO_RESULTCharPtr (((CharPtrProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((CharPtrProperty)e)->PropVal);
#endif
                break;
            case 8:
#ifdef DAPTO_RESULTCharPtr
                DAPTO_RESULTCharPtr (((CharPtrProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((CharPtrProperty)e)->PropVal);
#endif
                break;
            default: DAPTO_RESULT_STR ("unknown property");
        }
    }
}
#endif
