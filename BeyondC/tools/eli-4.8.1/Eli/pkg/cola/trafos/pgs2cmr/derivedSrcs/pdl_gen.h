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

#include "cmrlib.h"
#include "comar.h"
#include "cmrlib.h"
#include "CoordCmp.h"

#define TYPE int
extern TYPE Getint ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setint ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetint ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern TYPE SetGetint ELI_ARG((int _Property, DefTableKey key, TYPE init, TYPE reset));
#undef TYPE
#define TYPE DID
extern TYPE GetDID ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetDID ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetDID ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE def_entry
extern TYPE Getdef_entry ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setdef_entry ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetdef_entry ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE SID
extern TYPE GetSID ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetSID ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetSID ELI_ARG((int _Property, DefTableKey key, TYPE _val));
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
#define SetClass(key, _add, _replace)   \
		Setint(2, (key), (_add), (_replace))
#define ResetClass(key, _val)   \
		Resetint(2, (key), (_val))
#define GetClass(key, deflt)   \
		Getint(2, (key), (deflt))
#define SetNoStart(key, _add, _replace)   \
		Setint(3, (key), (_add), (_replace))
#define ResetNoStart(key, _val)   \
		Resetint(3, (key), (_val))
#define GetNoStart(key, deflt)   \
		Getint(3, (key), (deflt))
#define SetNullNt(key, _add, _replace)   \
		SetDID(4, (key), (_add), (_replace))
#define ResetNullNt(key, _val)   \
		ResetDID(4, (key), (_val))
#define GetNullNt(key, deflt)   \
		GetDID(4, (key), (deflt))
#define SetDef(key, _add, _replace)   \
		Setdef_entry(5, (key), (_add), (_replace))
#define ResetDef(key, _val)   \
		Resetdef_entry(5, (key), (_val))
#define GetDef(key, deflt)   \
		Getdef_entry(5, (key), (deflt))
#define SetOtherDef(key, _add, _replace)   \
		Setdef_entry(6, (key), (_add), (_replace))
#define ResetOtherDef(key, _val)   \
		Resetdef_entry(6, (key), (_val))
#define GetOtherDef(key, deflt)   \
		Getdef_entry(6, (key), (deflt))
#define SetReduceDef(key, _add, _replace)   \
		Setdef_entry(7, (key), (_add), (_replace))
#define ResetReduceDef(key, _val)   \
		Resetdef_entry(7, (key), (_val))
#define GetReduceDef(key, deflt)   \
		Getdef_entry(7, (key), (deflt))
#define SetNoReduceDef(key, _add, _replace)   \
		Setdef_entry(8, (key), (_add), (_replace))
#define ResetNoReduceDef(key, _val)   \
		Resetdef_entry(8, (key), (_val))
#define GetNoReduceDef(key, deflt)   \
		Getdef_entry(8, (key), (deflt))
#define SetConnectDef(key, _add, _replace)   \
		Setdef_entry(9, (key), (_add), (_replace))
#define ResetConnectDef(key, _val)   \
		Resetdef_entry(9, (key), (_val))
#define GetConnectDef(key, deflt)   \
		Getdef_entry(9, (key), (deflt))
#define SetSid(key, _add, _replace)   \
		SetSID(10, (key), (_add), (_replace))
#define ResetSid(key, _val)   \
		ResetSID(10, (key), (_val))
#define GetSid(key, deflt)   \
		GetSID(10, (key), (deflt))
#define SetChain(key, _add, _replace)   \
		Setint(11, (key), (_add), (_replace))
#define ResetChain(key, _val)   \
		Resetint(11, (key), (_val))
#define GetChain(key, deflt)   \
		Getint(11, (key), (deflt))
#define SetReplace(key, _add, _replace)   \
		SetDefTableKey(12, (key), (_add), (_replace))
#define ResetReplace(key, _val)   \
		ResetDefTableKey(12, (key), (_val))
#define GetReplace(key, deflt)   \
		GetDefTableKey(12, (key), (deflt))
#define SetGetFirstOcc(key, init, reset)   \
		SetGetint(13, (key), (init), (reset))
#define SetFirstOcc(key, _add, _replace)   \
		Setint(13, (key), (_add), (_replace))
#define ResetFirstOcc(key, _val)   \
		Resetint(13, (key), (_val))
#define GetFirstOcc(key, deflt)   \
		Getint(13, (key), (deflt))

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
