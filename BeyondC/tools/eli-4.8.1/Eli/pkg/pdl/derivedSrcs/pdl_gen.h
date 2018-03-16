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

#include "deftbl.h"
#include "ptg_gen.h"
#include "func.h"
#include "header.h"
#include "ptg_gen.h"
#include "ptg_gen.h"
#include "envmod.h"
#include "ElementList.h"
#include "KnownKey.h"
#include "CoordCmp.h"

#define TYPE int
extern TYPE Getint ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setint ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetint ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern TYPE SetGetint ELI_ARG((int _Property, DefTableKey key, TYPE init, TYPE reset));
extern void Isint ELI_ARG((int _Property, DefTableKey key, TYPE _which, TYPE _error));
extern int Hasint ELI_ARG((int _Property, DefTableKey key));
#undef TYPE
#define TYPE OpOutput
extern TYPE GetOpOutput ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetOpOutput ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetOpOutput ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE PTGNode
extern TYPE GetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE ExtOutput
extern TYPE GetExtOutput ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetExtOutput ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetExtOutput ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE DefTableKey
extern TYPE GetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE funclist
extern TYPE Getfunclist ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setfunclist ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetfunclist ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE Environment
extern TYPE GetEnvironment ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetEnvironment ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetEnvironment ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE ElementList
extern TYPE GetElementList ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetElementList ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetElementList ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern void ListInsertElementList ELI_ARG((int _Property, DefTableKey key, Element elt));
extern PTGNode FirstElementList ELI_ARG((int _Property, DefTableKey key));
#undef TYPE

#define SetClpValue(key, _add, _replace)   \
		Setint(1, (key), (_add), (_replace))
#define ResetClpValue(key, _val)   \
		Resetint(1, (key), (_val))
#define GetClpValue(key, deflt)   \
		Getint(1, (key), (deflt))
#define SetKind(key, _add, _replace)   \
		Setint(2, (key), (_add), (_replace))
#define ResetKind(key, _val)   \
		Resetint(2, (key), (_val))
#define GetKind(key, deflt)   \
		Getint(2, (key), (deflt))
#define SetFuncOut(key, _add, _replace)   \
		SetOpOutput(3, (key), (_add), (_replace))
#define ResetFuncOut(key, _val)   \
		ResetOpOutput(3, (key), (_val))
#define GetFuncOut(key, deflt)   \
		GetOpOutput(3, (key), (deflt))
#define SetArgList(key, _add, _replace)   \
		SetPTGNode(4, (key), (_add), (_replace))
#define ResetArgList(key, _val)   \
		ResetPTGNode(4, (key), (_val))
#define GetArgList(key, deflt)   \
		GetPTGNode(4, (key), (deflt))
#define SetFormalList(key, _add, _replace)   \
		SetPTGNode(5, (key), (_add), (_replace))
#define ResetFormalList(key, _val)   \
		ResetPTGNode(5, (key), (_val))
#define GetFormalList(key, deflt)   \
		GetPTGNode(5, (key), (deflt))
#define SetExtOut(key, _add, _replace)   \
		SetExtOutput(6, (key), (_add), (_replace))
#define ResetExtOut(key, _val)   \
		ResetExtOutput(6, (key), (_val))
#define GetExtOut(key, deflt)   \
		GetExtOutput(6, (key), (deflt))
#define SetSym(key, _add, _replace)   \
		Setint(7, (key), (_add), (_replace))
#define ResetSym(key, _val)   \
		Resetint(7, (key), (_val))
#define GetSym(key, deflt)   \
		Getint(7, (key), (deflt))
#define SetDefine(key, _add, _replace)   \
		Setint(8, (key), (_add), (_replace))
#define ResetDefine(key, _val)   \
		Resetint(8, (key), (_val))
#define GetDefine(key, deflt)   \
		Getint(8, (key), (deflt))
#define SetType(key, _add, _replace)   \
		SetDefTableKey(9, (key), (_add), (_replace))
#define ResetType(key, _val)   \
		ResetDefTableKey(9, (key), (_val))
#define GetType(key, deflt)   \
		GetDefTableKey(9, (key), (deflt))
#define SetFuncList(key, _add, _replace)   \
		Setfunclist(10, (key), (_add), (_replace))
#define ResetFuncList(key, _val)   \
		Resetfunclist(10, (key), (_val))
#define GetFuncList(key, deflt)   \
		Getfunclist(10, (key), (deflt))
#define SetGenFuncs(key, _add, _replace)   \
		Setint(11, (key), (_add), (_replace))
#define ResetGenFuncs(key, _val)   \
		Resetint(11, (key), (_val))
#define GetGenFuncs(key, deflt)   \
		Getint(11, (key), (deflt))
#define SetTypeName(key, _add, _replace)   \
		SetPTGNode(12, (key), (_add), (_replace))
#define ResetTypeName(key, _val)   \
		ResetPTGNode(12, (key), (_val))
#define GetTypeName(key, deflt)   \
		GetPTGNode(12, (key), (deflt))
#define SetFirst(key, _add, _replace)   \
		Setint(13, (key), (_add), (_replace))
#define ResetFirst(key, _val)   \
		Resetint(13, (key), (_val))
#define GetFirst(key, deflt)   \
		Getint(13, (key), (deflt))
#define SetGenExts(key, _add, _replace)   \
		Setint(14, (key), (_add), (_replace))
#define ResetGenExts(key, _val)   \
		Resetint(14, (key), (_val))
#define GetGenExts(key, deflt)   \
		Getint(14, (key), (deflt))
#define SetGenMacros(key, _add, _replace)   \
		Setint(15, (key), (_add), (_replace))
#define ResetGenMacros(key, _val)   \
		Resetint(15, (key), (_val))
#define GetGenMacros(key, deflt)   \
		Getint(15, (key), (deflt))
#define SetSelector(key, _add, _replace)   \
		Setint(16, (key), (_add), (_replace))
#define ResetSelector(key, _val)   \
		Resetint(16, (key), (_val))
#define GetSelector(key, deflt)   \
		Getint(16, (key), (deflt))
#define SetEnv(key, _add, _replace)   \
		SetEnvironment(17, (key), (_add), (_replace))
#define ResetEnv(key, _val)   \
		ResetEnvironment(17, (key), (_val))
#define GetEnv(key, deflt)   \
		GetEnvironment(17, (key), (deflt))
#define FirstValueList(key)   \
		FirstElementList(18, (key))
#define ListInsertValueList(key, elt)   \
		ListInsertElementList(18, (key), (elt))
#define SetValueList(key, _add, _replace)   \
		SetElementList(18, (key), (_add), (_replace))
#define ResetValueList(key, _val)   \
		ResetElementList(18, (key), (_val))
#define GetValueList(key, deflt)   \
		GetElementList(18, (key), (deflt))
#define HasText(key)   \
		Hasint(19, (key))
#define IsText(key, _which, _error)   \
		Isint(19, (key), (_which), (_error))
#define SetText(key, _add, _replace)   \
		Setint(19, (key), (_add), (_replace))
#define ResetText(key, _val)   \
		Resetint(19, (key), (_val))
#define GetText(key, deflt)   \
		Getint(19, (key), (deflt))
#define SetElementDone(key, _add, _replace)   \
		Setint(20, (key), (_add), (_replace))
#define ResetElementDone(key, _val)   \
		Resetint(20, (key), (_val))
#define GetElementDone(key, deflt)   \
		Getint(20, (key), (deflt))
#define SetGenCloneCases(key, _add, _replace)   \
		Setint(21, (key), (_add), (_replace))
#define ResetGenCloneCases(key, _val)   \
		Resetint(21, (key), (_val))
#define GetGenCloneCases(key, deflt)   \
		Getint(21, (key), (deflt))
#define SetGetKnownKeyFirstOcc(key, init, reset)   \
		SetGetint(22, (key), (init), (reset))
#define SetKnownKeyFirstOcc(key, _add, _replace)   \
		Setint(22, (key), (_add), (_replace))
#define ResetKnownKeyFirstOcc(key, _val)   \
		Resetint(22, (key), (_val))
#define GetKnownKeyFirstOcc(key, deflt)   \
		Getint(22, (key), (deflt))

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
