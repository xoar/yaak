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

#include "CoordCmp.h"
#include "err.h"
#include "RuleProd.h"

#define TYPE int
extern TYPE Getint ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setint ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetint ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE CoordPtr
extern TYPE GetCoordPtr ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetCoordPtr ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetCoordPtr ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern TYPE SetOnceCoordPtr ELI_ARG((int _Property, DefTableKey key, TYPE val));
#undef TYPE
#define TYPE RuleProd
extern TYPE GetRuleProd ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetRuleProd ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetRuleProd ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE DefTableKey
extern TYPE GetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE

#define SetClpValue(key, _add, _replace)   \
		Setint(1, (key), (_add), (_replace))
#define ResetClpValue(key, _val)   \
		Resetint(1, (key), (_val))
#define GetClpValue(key, deflt)   \
		Getint(1, (key), (deflt))
#define SetIsSymbol(key, _add, _replace)   \
		Setint(2, (key), (_add), (_replace))
#define ResetIsSymbol(key, _val)   \
		Resetint(2, (key), (_val))
#define GetIsSymbol(key, deflt)   \
		Getint(2, (key), (deflt))
#define SetIsType(key, _add, _replace)   \
		Setint(3, (key), (_add), (_replace))
#define ResetIsType(key, _val)   \
		Resetint(3, (key), (_val))
#define GetIsType(key, deflt)   \
		Getint(3, (key), (deflt))
#define SetIsRule(key, _add, _replace)   \
		Setint(4, (key), (_add), (_replace))
#define ResetIsRule(key, _val)   \
		Resetint(4, (key), (_val))
#define GetIsRule(key, deflt)   \
		Getint(4, (key), (deflt))
#define SetNameSym(key, _add, _replace)   \
		Setint(5, (key), (_add), (_replace))
#define ResetNameSym(key, _val)   \
		Resetint(5, (key), (_val))
#define GetNameSym(key, deflt)   \
		Getint(5, (key), (deflt))
#define SetOnceCoord(key, val)   \
		SetOnceCoordPtr(6, (key), (val))
#define SetCoord(key, _add, _replace)   \
		SetCoordPtr(6, (key), (_add), (_replace))
#define ResetCoord(key, _val)   \
		ResetCoordPtr(6, (key), (_val))
#define GetCoord(key, deflt)   \
		GetCoordPtr(6, (key), (deflt))
#define SetIsTREESym(key, _add, _replace)   \
		Setint(7, (key), (_add), (_replace))
#define ResetIsTREESym(key, _val)   \
		Resetint(7, (key), (_val))
#define GetIsTREESym(key, deflt)   \
		Getint(7, (key), (deflt))
#define SetIsCLASSSym(key, _add, _replace)   \
		Setint(8, (key), (_add), (_replace))
#define ResetIsCLASSSym(key, _val)   \
		Resetint(8, (key), (_val))
#define GetIsCLASSSym(key, deflt)   \
		Getint(8, (key), (deflt))
#define SetIsTREEReported(key, _add, _replace)   \
		Setint(9, (key), (_add), (_replace))
#define ResetIsTREEReported(key, _val)   \
		Resetint(9, (key), (_val))
#define GetIsTREEReported(key, deflt)   \
		Getint(9, (key), (deflt))
#define SetIsCLASSReported(key, _add, _replace)   \
		Setint(10, (key), (_add), (_replace))
#define ResetIsCLASSReported(key, _val)   \
		Resetint(10, (key), (_val))
#define GetIsCLASSReported(key, deflt)   \
		Getint(10, (key), (deflt))
#define SetIsNonterm(key, _add, _replace)   \
		Setint(11, (key), (_add), (_replace))
#define ResetIsNonterm(key, _val)   \
		Resetint(11, (key), (_val))
#define GetIsNonterm(key, deflt)   \
		Getint(11, (key), (deflt))
#define SetHasListof(key, _add, _replace)   \
		Setint(12, (key), (_add), (_replace))
#define ResetHasListof(key, _val)   \
		Resetint(12, (key), (_val))
#define GetHasListof(key, deflt)   \
		Getint(12, (key), (deflt))
#define SetHasNonListof(key, _add, _replace)   \
		Setint(13, (key), (_add), (_replace))
#define ResetHasNonListof(key, _val)   \
		Resetint(13, (key), (_val))
#define GetHasNonListof(key, deflt)   \
		Getint(13, (key), (deflt))
#define SetRule(key, _add, _replace)   \
		SetRuleProd(14, (key), (_add), (_replace))
#define ResetRule(key, _val)   \
		ResetRuleProd(14, (key), (_val))
#define GetRule(key, deflt)   \
		GetRuleProd(14, (key), (deflt))
#define SetLhsOfRule(key, _add, _replace)   \
		SetDefTableKey(15, (key), (_add), (_replace))
#define ResetLhsOfRule(key, _val)   \
		ResetDefTableKey(15, (key), (_val))
#define GetLhsOfRule(key, deflt)   \
		GetDefTableKey(15, (key), (deflt))
#define SetListofRuleOfLhs(key, _add, _replace)   \
		SetDefTableKey(16, (key), (_add), (_replace))
#define ResetListofRuleOfLhs(key, _val)   \
		ResetDefTableKey(16, (key), (_val))
#define GetListofRuleOfLhs(key, deflt)   \
		GetDefTableKey(16, (key), (deflt))

extern struct PropList PDLk[];


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
