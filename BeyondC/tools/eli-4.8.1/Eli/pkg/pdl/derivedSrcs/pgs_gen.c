/* $Id: StructConn,v 1.13 1998/10/12 06:09:57 tony Exp $ */
#include "gsdescr.h"
#include "treestack.h"
#include "HEAD.h"

#define TokenStack(i)	(ZAttributKeller[(i)])

#ifdef RIGHTCOORD
extern POSITION rightpos;
#endif

#if defined(__cplusplus) || defined(__STDC__) 
void
StrukturAnknuepfung(unsigned PR, GRUNDSYMBOLDESKRIPTOR *ZAttributKeller)
#else
void
StrukturAnknuepfung(PR, ZAttributKeller)
unsigned  PR;
register GRUNDSYMBOLDESKRIPTOR  *ZAttributKeller;
#endif
{
  curpos = ZAttributKeller->Pos;
#ifdef RIGHTCOORD
  RLineOf (curpos) = RLineOf (rightpos);
  RColOf (curpos) = RColOf (rightpos);
#ifdef MONITOR
  RCumColOf (curpos) = RCumColOf (rightpos);
#endif
#endif
  switch (PR) {
  case 1: _nsp -= 1;_nst[_nsp]=Mkrule_002(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 2: _nst[_nsp]=Mkrule_000(&curpos, _nst[_nsp+0]); break;
  case 3: _nsp -= 1;_nst[_nsp]=Mkrule_003(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 4: _nsp -= 1;_nst[_nsp]=Mkrule_004(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 5: _nst[_nsp]=Mkrule_011(&curpos, _nst[_nsp+0]); break;
  case 6: _nst[_nsp]=Mkrule_007(&curpos, _nst[_nsp+0]); break;
  case 7: _nsp -= 1;_nst[_nsp]=Mkrule_012(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 8: _nst[_nsp]=Mkrule_006(&curpos, _nst[_nsp+0]); break;
  case 9: _nst[_nsp]=Mkrule_014(&curpos, _nst[_nsp+0]); break;
  case 10: _nsp -= 1;_nst[_nsp]=Mkrule_008(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 11: _nst[_nsp]=MkSingleParameter(&curpos, _nst[_nsp+0]); break;
  case 12: _nst[_nsp]=Mkrule_009(&curpos, _nst[_nsp+0]); break;
  case 13: _nsp -= 1;_nst[_nsp]=Mkrule_005(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 14: _nsp -= 1;_nst[_nsp]=MkParameterSpec(&curpos, _nst[_nsp+0], MkIdentifier(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1))), _nst[_nsp+1]); break;
  case 15: _nsp -= 1;_nst[_nsp]=MkMultipleParameters(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 16: _nst[_nsp]=MkSingleParameterType(&curpos, _nst[_nsp+0]); break;
  case 17: _nsp -= 1;_nst[_nsp]=Mkrule_010(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 18: _nsp -= 1;_nst[_nsp]=MkParameterTypeSpec(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 19: _nsp -= 1;_nst[_nsp]=MkIdentParameterTS(&curpos, _nst[_nsp+0], MkIdentifier(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1))), _nst[_nsp+1]); break;
  case 20: _nsp -= 1;_nst[_nsp]=MkMultipleParameterTypes(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 21: _incrnodestack();_nst[_nsp]=Mkrule_001(&curpos); break;
  case 22: _incrnodestack();_nst[_nsp]=MkFileSpec(&curpos, MkString(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 23: _nst[_nsp]=Mkrule_016(&curpos, _nst[_nsp+0]); break;
  case 24: _incrnodestack();_nst[_nsp]=MkGenericType(&curpos); break;
  case 26: _incrnodestack();_nst[_nsp]=MkPropertyName(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 27: _incrnodestack();_nst[_nsp]=MkDefinedType(&curpos, MkTypeName(&(T_POS(TokenStack(0))), MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0))))); break;
  case 28: _incrnodestack();_nst[_nsp]=Mkrule_013(&curpos); break;
  case 29: _nst[_nsp]=Mkrule_2(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0))), _nst[_nsp+0]); break;
  case 30: _nsp -= 1;_nst[_nsp]=MkAxiom(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 31: _nst[_nsp]=MkTypeNoOp(&curpos, _nst[_nsp+0]); break;
  case 32: _nsp -= 1;_nst[_nsp]=MkPropertySpec(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 33: _nst[_nsp]=Mkrule_015(&curpos, _nst[_nsp+0]); break;
  case 34: _incrnodestack();_nst[_nsp]=MkOperationName(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 35: _incrnodestack();_nst[_nsp]=Mkrule_1(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0))), MkText(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))); break;
  case 36: _incrnodestack();_nst[_nsp]=MkEmptyModifier(&curpos); break;
  case 37: _nsp -= 1;_nst[_nsp]=MkOperationSpec(&curpos, _nst[_nsp+0], MkIdentifier(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1))), _nst[_nsp+1], MkText(&(T_POS(TokenStack(5))), T_ATTR(TokenStack(5)))); break;
  case 38: _nsp -= 1;_nst[_nsp]=MkTypeWithOp(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 39: _incrnodestack();_nst[_nsp]=MkVoidModifier(&curpos); break;
  case 40: _nst[_nsp]=MkSimpleModifier(&curpos, _nst[_nsp+0]); break;
  case 41: _nst[_nsp]=MkExtendedModifier(&curpos, _nst[_nsp+0]); break;
  } /* end switch */
}
