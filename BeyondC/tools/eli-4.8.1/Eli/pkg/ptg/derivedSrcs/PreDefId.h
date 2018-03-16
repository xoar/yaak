
#ifndef _PreDefId_h
#define _PreDefId_h

extern void InitPreDef ();
#include "deftbl.h"
#include "envmod.h"

#define PreDefSym(_str,_sym) extern int _sym;
#define PreDefKey(_str,_key) 
#define PreDefSymKey(_str,_sym,_key) extern int _sym;
#define PreDefBind(_str,_bnd) extern Binding _bnd;
#define PreDefKeyBind(_str,_key,_bnd) Binding _bnd;
#define PreDefSymKeyBind(_str,_sym,_key,_bnd) extern int _sym; Binding _bnd;
#include "PreDefId.d.h"
#undef PreDefSym
#undef PreDefKey
#undef PreDefSymKey
#undef PreDefBind
#undef PreDefKeyBind
#undef PreDefSymKeyBind

#endif
