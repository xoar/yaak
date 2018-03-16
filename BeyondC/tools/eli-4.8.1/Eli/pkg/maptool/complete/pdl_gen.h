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
#include "DefTableKeyList.h"
#include "SymbolPList.h"
#include "oiladt2.h"
#include "csm.h"
#include "rules.h"
#include "intList.h"
#include "deftbl.h"
#include "DefTableKeyList.h"
#include "CoordCmp.h"
#include "oiladt2.h"

#define TYPE int
extern TYPE Getint ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setint ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetint ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern TYPE SetGetint ELI_ARG((int _Property, DefTableKey key, TYPE init, TYPE reset));
extern void Isint ELI_ARG((int _Property, DefTableKey key, TYPE _which, TYPE _error));
extern DefTableKey KResetint ELI_ARG((int _Property, DefTableKey key, TYPE val));
extern charp Strint ELI_ARG((int _Property, DefTableKey key));
extern int Incint ELI_ARG((int _Property, DefTableKey key));
#undef TYPE
#define TYPE DefTableKeyList
extern TYPE GetDefTableKeyList ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetDefTableKeyList ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetDefTableKeyList ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE DefTableKey
extern TYPE GetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern DefTableKey KResetDefTableKey ELI_ARG((int _Property, DefTableKey key, TYPE val));
#undef TYPE
#define TYPE SymbolPList
extern TYPE GetSymbolPList ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetSymbolPList ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetSymbolPList ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE tOilOp
extern TYPE GettOilOp ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SettOilOp ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResettOilOp ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE tOilType
extern TYPE GettOilType ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SettOilType ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResettOilType ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE intList
extern TYPE GetintList ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetintList ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetintList ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE tOilClass
extern TYPE GettOilClass ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SettOilClass ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResettOilClass ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE

#define SetClpValue(key, _add, _replace)   \
		Setint(1, (key), (_add), (_replace))
#define ResetClpValue(key, _val)   \
		Resetint(1, (key), (_val))
#define GetClpValue(key, deflt)   \
		Getint(1, (key), (deflt))
#define SetAbsDone(key, _add, _replace)   \
		Setint(2, (key), (_add), (_replace))
#define ResetAbsDone(key, _val)   \
		Resetint(2, (key), (_val))
#define GetAbsDone(key, deflt)   \
		Getint(2, (key), (deflt))
#define SetListChainDone(key, _add, _replace)   \
		Setint(3, (key), (_add), (_replace))
#define ResetListChainDone(key, _val)   \
		Resetint(3, (key), (_val))
#define GetListChainDone(key, deflt)   \
		Getint(3, (key), (deflt))
#define SetChainDone(key, _add, _replace)   \
		Setint(4, (key), (_add), (_replace))
#define ResetChainDone(key, _val)   \
		Resetint(4, (key), (_val))
#define GetChainDone(key, deflt)   \
		Getint(4, (key), (deflt))
#define SetPChainDone(key, _add, _replace)   \
		Setint(5, (key), (_add), (_replace))
#define ResetPChainDone(key, _val)   \
		Resetint(5, (key), (_val))
#define GetPChainDone(key, deflt)   \
		Getint(5, (key), (deflt))
#define SetLISTOFDone(key, _add, _replace)   \
		Setint(6, (key), (_add), (_replace))
#define ResetLISTOFDone(key, _val)   \
		Resetint(6, (key), (_val))
#define GetLISTOFDone(key, deflt)   \
		Getint(6, (key), (deflt))
#define SetPLISTOFDone(key, _add, _replace)   \
		Setint(7, (key), (_add), (_replace))
#define ResetPLISTOFDone(key, _val)   \
		Resetint(7, (key), (_val))
#define GetPLISTOFDone(key, deflt)   \
		Getint(7, (key), (deflt))
#define SetConRules(key, _add, _replace)   \
		SetDefTableKeyList(8, (key), (_add), (_replace))
#define ResetConRules(key, _val)   \
		ResetDefTableKeyList(8, (key), (_val))
#define GetConRules(key, deflt)   \
		GetDefTableKeyList(8, (key), (deflt))
#define SetAbsRules(key, _add, _replace)   \
		SetDefTableKeyList(9, (key), (_add), (_replace))
#define ResetAbsRules(key, _val)   \
		ResetDefTableKeyList(9, (key), (_val))
#define GetAbsRules(key, deflt)   \
		GetDefTableKeyList(9, (key), (deflt))
#define SetRHSConRules(key, _add, _replace)   \
		SetDefTableKeyList(10, (key), (_add), (_replace))
#define ResetRHSConRules(key, _val)   \
		ResetDefTableKeyList(10, (key), (_val))
#define GetRHSConRules(key, deflt)   \
		GetDefTableKeyList(10, (key), (deflt))
#define KResetLHS(key, val)   \
		KResetDefTableKey(11, (key), (val))
#define SetLHS(key, _add, _replace)   \
		SetDefTableKey(11, (key), (_add), (_replace))
#define ResetLHS(key, _val)   \
		ResetDefTableKey(11, (key), (_val))
#define GetLHS(key, deflt)   \
		GetDefTableKey(11, (key), (deflt))
#define SetRHS(key, _add, _replace)   \
		SetSymbolPList(12, (key), (_add), (_replace))
#define ResetRHS(key, _val)   \
		ResetSymbolPList(12, (key), (_val))
#define GetRHS(key, deflt)   \
		GetSymbolPList(12, (key), (deflt))
#define SetType(key, _add, _replace)   \
		Setint(13, (key), (_add), (_replace))
#define ResetType(key, _val)   \
		Resetint(13, (key), (_val))
#define GetType(key, deflt)   \
		Getint(13, (key), (deflt))
#define SetOilOp(key, _add, _replace)   \
		SettOilOp(14, (key), (_add), (_replace))
#define ResetOilOp(key, _val)   \
		ResettOilOp(14, (key), (_val))
#define GetOilOp(key, deflt)   \
		GettOilOp(14, (key), (deflt))
#define SetOilType(key, _add, _replace)   \
		SettOilType(15, (key), (_add), (_replace))
#define ResetOilType(key, _val)   \
		ResettOilType(15, (key), (_val))
#define GetOilType(key, deflt)   \
		GettOilType(15, (key), (deflt))
#define IncNTCount(key)   \
		Incint(16, (key))
#define SetNTCount(key, _add, _replace)   \
		Setint(16, (key), (_add), (_replace))
#define ResetNTCount(key, _val)   \
		Resetint(16, (key), (_val))
#define GetNTCount(key, deflt)   \
		Getint(16, (key), (deflt))
#define SetArgCount(key, _add, _replace)   \
		Setint(17, (key), (_add), (_replace))
#define ResetArgCount(key, _val)   \
		Resetint(17, (key), (_val))
#define GetArgCount(key, deflt)   \
		Getint(17, (key), (deflt))
#define StrStr(key)   \
		Strint(18, (key))
#define KResetStr(key, val)   \
		KResetint(18, (key), (val))
#define SetStr(key, _add, _replace)   \
		Setint(18, (key), (_add), (_replace))
#define ResetStr(key, _val)   \
		Resetint(18, (key), (_val))
#define GetStr(key, deflt)   \
		Getint(18, (key), (deflt))
#define SetBottomUp(key, _add, _replace)   \
		Setint(19, (key), (_add), (_replace))
#define ResetBottomUp(key, _val)   \
		Resetint(19, (key), (_val))
#define GetBottomUp(key, deflt)   \
		Getint(19, (key), (deflt))
#define SetMap(key, _add, _replace)   \
		SetDefTableKey(20, (key), (_add), (_replace))
#define ResetMap(key, _val)   \
		ResetDefTableKey(20, (key), (_val))
#define GetMap(key, deflt)   \
		GetDefTableKey(20, (key), (deflt))
#define SetAbsMap(key, _add, _replace)   \
		SetDefTableKeyList(21, (key), (_add), (_replace))
#define ResetAbsMap(key, _val)   \
		ResetDefTableKeyList(21, (key), (_val))
#define GetAbsMap(key, deflt)   \
		GetDefTableKeyList(21, (key), (deflt))
#define SetOrder(key, _add, _replace)   \
		SetintList(22, (key), (_add), (_replace))
#define ResetOrder(key, _val)   \
		ResetintList(22, (key), (_val))
#define GetOrder(key, deflt)   \
		GetintList(22, (key), (deflt))
#define IsEqClass(key, _which, _error)   \
		Isint(23, (key), (_which), (_error))
#define SetEqClass(key, _add, _replace)   \
		Setint(23, (key), (_add), (_replace))
#define ResetEqClass(key, _val)   \
		Resetint(23, (key), (_val))
#define GetEqClass(key, deflt)   \
		Getint(23, (key), (deflt))
#define SetMappedRHS(key, _add, _replace)   \
		SetSymbolPList(24, (key), (_add), (_replace))
#define ResetMappedRHS(key, _val)   \
		ResetSymbolPList(24, (key), (_val))
#define GetMappedRHS(key, deflt)   \
		GetSymbolPList(24, (key), (deflt))
#define SetMatch(key, _add, _replace)   \
		SetDefTableKey(25, (key), (_add), (_replace))
#define ResetMatch(key, _val)   \
		ResetDefTableKey(25, (key), (_val))
#define GetMatch(key, deflt)   \
		GetDefTableKey(25, (key), (deflt))
#define SetAbsMatch(key, _add, _replace)   \
		SetDefTableKeyList(26, (key), (_add), (_replace))
#define ResetAbsMatch(key, _val)   \
		ResetDefTableKeyList(26, (key), (_val))
#define GetAbsMatch(key, deflt)   \
		GetDefTableKeyList(26, (key), (deflt))
#define SetDuplicate(key, _add, _replace)   \
		SetDefTableKey(27, (key), (_add), (_replace))
#define ResetDuplicate(key, _val)   \
		ResetDefTableKey(27, (key), (_val))
#define GetDuplicate(key, deflt)   \
		GetDefTableKey(27, (key), (deflt))
#define SetTraversal(key, _add, _replace)   \
		Setint(28, (key), (_add), (_replace))
#define ResetTraversal(key, _val)   \
		Resetint(28, (key), (_val))
#define GetTraversal(key, deflt)   \
		Getint(28, (key), (deflt))
#define SetBadRootError(key, _add, _replace)   \
		Setint(29, (key), (_add), (_replace))
#define ResetBadRootError(key, _val)   \
		Resetint(29, (key), (_val))
#define GetBadRootError(key, deflt)   \
		Getint(29, (key), (deflt))
#define SetRecursive(key, _add, _replace)   \
		Setint(30, (key), (_add), (_replace))
#define ResetRecursive(key, _val)   \
		Resetint(30, (key), (_val))
#define GetRecursive(key, deflt)   \
		Getint(30, (key), (deflt))
#define SetIsRHS(key, _add, _replace)   \
		Setint(31, (key), (_add), (_replace))
#define ResetIsRHS(key, _val)   \
		Resetint(31, (key), (_val))
#define GetIsRHS(key, deflt)   \
		Getint(31, (key), (deflt))
#define SetNonTerm(key, _add, _replace)   \
		Setint(32, (key), (_add), (_replace))
#define ResetNonTerm(key, _val)   \
		Resetint(32, (key), (_val))
#define GetNonTerm(key, deflt)   \
		Getint(32, (key), (deflt))
#define SetStart(key, _add, _replace)   \
		Setint(33, (key), (_add), (_replace))
#define ResetStart(key, _val)   \
		Resetint(33, (key), (_val))
#define GetStart(key, deflt)   \
		Getint(33, (key), (deflt))
#define SetReach(key, _add, _replace)   \
		Setint(34, (key), (_add), (_replace))
#define ResetReach(key, _val)   \
		Resetint(34, (key), (_val))
#define GetReach(key, deflt)   \
		Getint(34, (key), (deflt))
#define SetConSym(key, _add, _replace)   \
		Setint(35, (key), (_add), (_replace))
#define ResetConSym(key, _val)   \
		Resetint(35, (key), (_val))
#define GetConSym(key, deflt)   \
		Getint(35, (key), (deflt))
#define SetIsCon(key, _add, _replace)   \
		Setint(36, (key), (_add), (_replace))
#define ResetIsCon(key, _val)   \
		Resetint(36, (key), (_val))
#define GetIsCon(key, deflt)   \
		Getint(36, (key), (deflt))
#define SetIsAbs(key, _add, _replace)   \
		Setint(37, (key), (_add), (_replace))
#define ResetIsAbs(key, _val)   \
		Resetint(37, (key), (_val))
#define GetIsAbs(key, deflt)   \
		Getint(37, (key), (deflt))
#define SetRootErr(key, _add, _replace)   \
		Setint(38, (key), (_add), (_replace))
#define ResetRootErr(key, _val)   \
		Resetint(38, (key), (_val))
#define GetRootErr(key, deflt)   \
		Getint(38, (key), (deflt))
#define SetSibling(key, _add, _replace)   \
		Setint(39, (key), (_add), (_replace))
#define ResetSibling(key, _val)   \
		Resetint(39, (key), (_val))
#define GetSibling(key, deflt)   \
		Getint(39, (key), (deflt))
#define SetOilClass(key, _add, _replace)   \
		SettOilClass(40, (key), (_add), (_replace))
#define ResetOilClass(key, _val)   \
		ResettOilClass(40, (key), (_val))
#define GetOilClass(key, deflt)   \
		GettOilClass(40, (key), (deflt))
#define SetGetFirstOcc(key, init, reset)   \
		SetGetint(41, (key), (init), (reset))
#define SetFirstOcc(key, _add, _replace)   \
		Setint(41, (key), (_add), (_replace))
#define ResetFirstOcc(key, _val)   \
		Resetint(41, (key), (_val))
#define GetFirstOcc(key, deflt)   \
		Getint(41, (key), (deflt))

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
