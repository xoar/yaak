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

#include "Strings.h"
#include "glafe.h"

#define TYPE int
extern TYPE Getint ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setint ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetint ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE CharPtr
extern TYPE GetCharPtr ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetCharPtr ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetCharPtr ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern void GuaranteeCharPtr ELI_ARG((int _Property, DefTableKey key, TYPE val));
#undef TYPE

#define SetClpValue(key, _add, _replace)   \
		Setint(1, (key), (_add), (_replace))
#define ResetClpValue(key, _val)   \
		Resetint(1, (key), (_val))
#define GetClpValue(key, deflt)   \
		Getint(1, (key), (deflt))
#define SetUnique(key, _add, _replace)   \
		Setint(2, (key), (_add), (_replace))
#define ResetUnique(key, _val)   \
		Resetint(2, (key), (_val))
#define GetUnique(key, deflt)   \
		Getint(2, (key), (deflt))
#define SetRegex(key, _add, _replace)   \
		SetCharPtr(3, (key), (_add), (_replace))
#define ResetRegex(key, _val)   \
		ResetCharPtr(3, (key), (_val))
#define GetRegex(key, deflt)   \
		GetCharPtr(3, (key), (deflt))
#define SetEncoding(key, _add, _replace)   \
		Setint(4, (key), (_add), (_replace))
#define ResetEncoding(key, _val)   \
		Resetint(4, (key), (_val))
#define GetEncoding(key, deflt)   \
		Getint(4, (key), (deflt))
#define SetCounter(key, _add, _replace)   \
		Setint(5, (key), (_add), (_replace))
#define ResetCounter(key, _val)   \
		Resetint(5, (key), (_val))
#define GetCounter(key, deflt)   \
		Getint(5, (key), (deflt))
#define GuaranteeScanner(key, val)   \
		GuaranteeCharPtr(6, (key), (val))
#define SetScanner(key, _add, _replace)   \
		SetCharPtr(6, (key), (_add), (_replace))
#define ResetScanner(key, _val)   \
		ResetCharPtr(6, (key), (_val))
#define GetScanner(key, deflt)   \
		GetCharPtr(6, (key), (deflt))
#define GuaranteeProcessor(key, val)   \
		GuaranteeCharPtr(7, (key), (val))
#define SetProcessor(key, _add, _replace)   \
		SetCharPtr(7, (key), (_add), (_replace))
#define ResetProcessor(key, _val)   \
		ResetCharPtr(7, (key), (_val))
#define GetProcessor(key, deflt)   \
		GetCharPtr(7, (key), (deflt))
#define SetStr(key, _add, _replace)   \
		SetCharPtr(8, (key), (_add), (_replace))
#define ResetStr(key, _val)   \
		ResetCharPtr(8, (key), (_val))
#define GetStr(key, deflt)   \
		GetCharPtr(8, (key), (deflt))

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
