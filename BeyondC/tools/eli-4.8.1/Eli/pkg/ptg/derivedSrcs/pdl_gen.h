#ifndef PDL_GEN_H
#define PDL_GEN_H

#include "deftbl.h"

#ifdef ELI_ARG
#undef ELI_ARG
#endif

#if defined(__STDC__) || defined(__cplusplus)
#define ELI_ARG(proto)    proto
#else
#define ELI_ARG(proto)    ()
#endif

#include "DefTableKeyList.h"
#include "PatElemList.h"
#include "ptg_gen.h"
#include "Strings.h"
#include "CoordCmp.h"

#define TYPE int
extern TYPE Getint ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setint ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetint ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE DefTableKey
extern TYPE GetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern void SetDiffDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE thistype, TYPE diff));
#undef TYPE
#define TYPE DefTableKeyList
extern TYPE GetDefTableKeyList ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetDefTableKeyList ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetDefTableKeyList ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE PatElemList
extern TYPE GetPatElemList ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetPatElemList ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetPatElemList ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE PTGNode
extern TYPE GetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE CharPtr
extern TYPE GetCharPtr ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetCharPtr ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetCharPtr ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE

#define SetClpValue(key, _add, _replace)   \
		Setint(1, (key), (_add), (_replace))
#define ResetClpValue(key, _val)   \
		Resetint(1, (key), (_val))
#define GetClpValue(key, deflt)   \
		Getint(1, (key), (deflt))
#define SetisPredefined(key, _add, _replace)   \
		Setint(2, (key), (_add), (_replace))
#define ResetisPredefined(key, _val)   \
		Resetint(2, (key), (_val))
#define GetisPredefined(key, deflt)   \
		Getint(2, (key), (deflt))
#define SetDiffType(key, thistype, diff)   \
		SetDiffDefTableKey(3, (key), (thistype), (diff))
#define SetType(key, _add, _replace)   \
		SetDefTableKey(3, (key), (_add), (_replace))
#define ResetType(key, _val)   \
		ResetDefTableKey(3, (key), (_val))
#define GetType(key, deflt)   \
		GetDefTableKey(3, (key), (deflt))
#define SetIndex(key, _add, _replace)   \
		Setint(4, (key), (_add), (_replace))
#define ResetIndex(key, _val)   \
		Resetint(4, (key), (_val))
#define GetIndex(key, deflt)   \
		Getint(4, (key), (deflt))
#define SetArgumentTypes(key, _add, _replace)   \
		SetDefTableKeyList(5, (key), (_add), (_replace))
#define ResetArgumentTypes(key, _val)   \
		ResetDefTableKeyList(5, (key), (_val))
#define GetArgumentTypes(key, deflt)   \
		GetDefTableKeyList(5, (key), (deflt))
#define SetIsInconsistent(key, _add, _replace)   \
		Setint(6, (key), (_add), (_replace))
#define ResetIsInconsistent(key, _val)   \
		Resetint(6, (key), (_val))
#define GetIsInconsistent(key, deflt)   \
		Getint(6, (key), (deflt))
#define SetPattern(key, _add, _replace)   \
		SetPatElemList(7, (key), (_add), (_replace))
#define ResetPattern(key, _val)   \
		ResetPatElemList(7, (key), (_val))
#define GetPattern(key, deflt)   \
		GetPatElemList(7, (key), (deflt))
#define SetIsMultDef(key, _add, _replace)   \
		Setint(8, (key), (_add), (_replace))
#define ResetIsMultDef(key, _val)   \
		Resetint(8, (key), (_val))
#define GetIsMultDef(key, deflt)   \
		Getint(8, (key), (deflt))
#define SetDoIt(key, _add, _replace)   \
		Setint(9, (key), (_add), (_replace))
#define ResetDoIt(key, _val)   \
		Resetint(9, (key), (_val))
#define GetDoIt(key, deflt)   \
		Getint(9, (key), (deflt))
#define SetUsed(key, _add, _replace)   \
		Setint(10, (key), (_add), (_replace))
#define ResetUsed(key, _val)   \
		Resetint(10, (key), (_val))
#define GetUsed(key, deflt)   \
		Getint(10, (key), (deflt))
#define SetTargetType(key, _add, _replace)   \
		SetPTGNode(11, (key), (_add), (_replace))
#define ResetTargetType(key, _val)   \
		ResetPTGNode(11, (key), (_val))
#define GetTargetType(key, deflt)   \
		GetPTGNode(11, (key), (deflt))
#define SetOutputName(key, _add, _replace)   \
		SetCharPtr(12, (key), (_add), (_replace))
#define ResetOutputName(key, _val)   \
		ResetCharPtr(12, (key), (_val))
#define GetOutputName(key, deflt)   \
		GetCharPtr(12, (key), (deflt))
#define SethasFreeOccurrence(key, _add, _replace)   \
		Setint(13, (key), (_add), (_replace))
#define ResethasFreeOccurrence(key, _val)   \
		Resetint(13, (key), (_val))
#define GethasFreeOccurrence(key, deflt)   \
		Getint(13, (key), (deflt))

extern struct PropList PDLk[];

#define NodeKey (&PDLk[0])
#define NULLKey (&PDLk[1])
#define NullKey (&PDLk[2])
#define OutKey (&PDLk[3])
#define OutFileKey (&PDLk[4])
#define OutFPtrKey (&PDLk[5])
#define FreeKey (&PDLk[6])
#define ProcessKey (&PDLk[7])
#define nodeType (&PDLk[8])
#define intType (&PDLk[9])
#define stringType (&PDLk[10])
#define pointerType (&PDLk[11])
#define longType (&PDLk[12])
#define shortType (&PDLk[13])
#define charType (&PDLk[14])
#define floatType (&PDLk[15])
#define doubleType (&PDLk[16])
#define multipleType (&PDLk[17])

extern DefTableKey CloneKey ELI_ARG((DefTableKey key));
/* Clone a definition
 *    On entry-
 *       key=a valid definition
 *    On exit-
 *       CloneKey=Unique definition with the same properties
 *                and property values as key
 ***/

#ifdef MONITOR
extern void pdl_mon_properties ELI_ARG((DefTableKey));
#endif

#endif
