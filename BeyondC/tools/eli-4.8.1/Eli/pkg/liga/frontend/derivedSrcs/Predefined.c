
#include "Predefined.h"
#include "pdl_gen.h"
#include "Attribute.h"
#include "PreDefId.h"

int maxPredefSym = 0;

#ifdef TEST
#define TEST
#include <stdio.h>
#endif

#if defined(__cplusplus) || defined(__STDC__)
int IsPredefSym (int idn)
#else
int IsPredefSym (idn) int idn;
#endif
{ return idn <= maxPredefSym;
}

static 
#if defined(__cplusplus) || defined(__STDC__)
void SetPredefProp (DefTableKey k, int idn)
#else
void SetPredefProp (k) DefTableKey k; int idn;
#endif
{ if (idn > maxPredefSym) maxPredefSym = idn;
  ResetNameSym (k, idn);
  ResetCoord (k, NoPosition);
}

#if defined(__cplusplus) || defined(__STDC__)
void MakePredef 
 (Environment globenv,
  Environment attrenv, Environment attrnameenv, Environment symbolenv)
#else
void MakePredef (globenv, attrenv, attrnameenv, symbolenv)
  Environment globenv, attrenv, attrnameenv, symbolenv;
#endif
{ Binding b;
  Environment e;
  DefTableKey k;

#ifdef TEST
  printf ("MakePredef begin\n");
#endif
  SetPredefProp (VOIDkey, VOIDsym);
  ResetIsType (VOIDkey, 1);

  SetPredefProp (VOID_LISTkey, VOID_LISTsym);
  ResetIsType (VOID_LISTkey, 1);

  SetPredefProp (intkey, intsym);
  ResetIsType (intkey, 1);

  SetPredefProp (BOOLkey, BOOLsym);
  ResetIsType (BOOLkey, 1);

  SetPredefProp (SYMBkey, SYMBsym);
  ResetIsType (SYMBkey, 1);

  SetPredefProp (POSITIONkey, POSITIONsym);
  ResetIsType (POSITIONkey, 1);

  SetPredefProp (NODEPTRkey, NODEPTRsym);
  ResetIsType (NODEPTRkey, 1);

  SetPredefProp (ROOTCLASSkey, ROOTCLASSsym);
  ResetIsSymbol (ROOTCLASSkey, 1);
  ResetIsCLASSSym (ROOTCLASSkey, 1);
  ResetIsUsed (ROOTCLASSkey, 1);

  e = NewScope (symbolenv); SetKeyOfEnv (e, ROOTCLASSkey);
  ResetUpperScope (ROOTCLASSkey, e);
  e = NewScope (symbolenv); SetKeyOfEnv (e, ROOTCLASSkey);
  ResetLowerScope (ROOTCLASSkey, e);
  e = NewScope (symbolenv); SetKeyOfEnv (e, ROOTCLASSkey);
  ResetHEADScope (ROOTCLASSkey, e);
  e = NewScope (attrenv); SetKeyOfEnv (e, ROOTCLASSkey);
  ResetAttrScope (ROOTCLASSkey, e);
#ifdef TEST
  k = KeyOf(BindingInEnv (globenv, ROOTCLASSsym));
  printf ("bind ROOTCLASS key %s\n", 
    k != ROOTCLASSkey ? "failed" : "ok");
#endif

  BindKey (attrnameenv, GENTREEsym, GENTREEkey);
  SetPredefProp (GENTREEkey, GENTREEsym);
  ResetAttrClass (GENTREEkey, INHClass);
  ResetAttrType (GENTREEkey, NODEPTRkey);

  SetPredefProp (IFkey, IFsym);
  SetPredefProp (ORDERkey, ORDERsym);
  SetPredefProp (RuleFctkey, RuleFctsym);
  SetPredefProp (RhsFctkey, RhsFctsym);
  SetPredefProp (TermFctkey, TermFctsym);
  SetPredefProp (LINEkey, LINEsym);
  SetPredefProp (COLkey, COLsym);
  SetPredefProp (COORDREFkey, COORDREFsym);
  SetPredefProp (RULENAMEkey, RULENAMEsym);
  SetPredefProp (NULLNODEPTRkey, NULLNODEPTRsym);
#ifdef TEST
  printf ("MakePredef end\n");
#endif
}
