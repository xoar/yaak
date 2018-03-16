
#include "IdentTerm.h"
#include "PreDefMod.h"
#include "PreDefId.h"
#include "pdl_gen.h"

extern Environment RootEnv; /* provided by a scope module */

#define PreDefSym(_str,_sym) int _sym;
#define PreDefKey(_str,_key) 
#define PreDefSymKey(_str,_sym,_key) int _sym;
#define PreDefBind(_str,_bnd) Binding _bnd;
#define PreDefKeyBind(_str,_key,_bnd) Binding _bnd;
#define PreDefSymKeyBind(_str,_sym,_key,_bnd) int _sym; Binding _bnd;
#include "PreDefId.d.h"
#undef PreDefSym
#undef PreDefKey
#undef PreDefSymKey
#undef PreDefBind
#undef PreDefKeyBind
#undef PreDefSymKeyBind

void InitPreDef ()
{ int _dummysym; Binding _dummybnd;
  if (RootEnv == NoEnv) RootEnv = NewEnv ();
#define PreDefSym(_str,_sym) \
        PreDefineSym (_str, _IdentTerm, &_sym);
#define PreDefKey(_str,_key) \
        PreDefine(_str,_IdentTerm,&_dummysym,RootEnv,_key,&_dummybnd);
#define PreDefSymKey(_str,_sym,_key) \
        PreDefine(_str,_IdentTerm,&_sym,RootEnv,_key,&_dummybnd);
#define PreDefBind(_str,_bnd) \
        PreDefine (_str,_IdentTerm,&_dummysym,RootEnv,NewKey(),&_bnd);
#define PreDefKeyBind(_str,_key,_bnd) \
        PreDefine (_str,_IdentTerm,&_dummysym,RootEnv,_key,&_bnd);
#define PreDefSymKeyBind(_str,_sym,_key,_bnd) \
        PreDefine (_str,_IdentTerm,RootEnv,&_sym,_key,&_bnd);
#include "PreDefId.d.h"
#undef PreDefSym
#undef PreDefKey
#undef PreDefSymKey
#undef PreDefBind
#undef PreDefKeyBind
#undef PreDefSymKeyBind
}
