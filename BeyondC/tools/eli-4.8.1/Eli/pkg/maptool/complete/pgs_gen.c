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
  case 1: _nst[_nsp]=Mkrule_35(&curpos, _nst[_nsp+0]); break;
  case 2: _nsp -= 1;_nst[_nsp]=Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 3: _nsp -= 1;_nst[_nsp]=Mkrule_35(&curpos, Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1])); break;
  case 4: _nsp -= 1;_nst[_nsp]=Mkrule_35(&curpos, Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1])); break;
  case 5: _nsp -= 1;_nst[_nsp]=Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 6: _nsp -= 1;_nst[_nsp]=Mkrule_35(&curpos, Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1])); break;
  case 7: _nsp -= 1;_nst[_nsp]=Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 8: _nsp -= 2;_nst[_nsp]=Mkrule_35(&curpos, Mk2rule_35(&curpos, Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]), _nst[_nsp+2])); break;
  case 9: _nsp -= 2;_nst[_nsp]=Mkrule_35(&curpos, Mk2rule_35(&curpos, Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]), _nst[_nsp+2])); break;
  case 10: _nsp -= 2;_nst[_nsp]=Mkrule_35(&curpos, Mk2rule_35(&curpos, Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]), _nst[_nsp+2])); break;
  case 11: _nsp -= 1;_nst[_nsp]=Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 12: _nsp -= 1;_nst[_nsp]=Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 13: _nsp -= 1;_nst[_nsp]=Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 14: _nsp -= 1;_nst[_nsp]=Mk2rule_34(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 15: _nsp -= 3;_nst[_nsp]=Mkrule_35(&curpos, Mk2rule_35(&curpos, Mk2rule_35(&curpos, Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]), _nst[_nsp+2]), _nst[_nsp+3])); break;
  case 16: _nsp -= 1;_nst[_nsp]=Mkrule_8(&curpos, Mkrule_7(&(T_POS(TokenStack(0))), MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))), _nst[_nsp+0], _nst[_nsp+1]); break;
  case 17: _nsp -= 1;_nst[_nsp]=Mk2rule_30(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 18: _nsp -= 1;_nst[_nsp]=Mk2rule_29(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 19: _nsp -= 1;_nst[_nsp]=Mk2rule_29(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 20: _nst[_nsp]=Mkrule_10(&curpos, _nst[_nsp+0]); break;
  case 21: _nsp -= 1;_nst[_nsp]=Mk2rule_31(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 22: _nst[_nsp]=Mkrule_15(&curpos, Mkrule_18(&(T_POS(TokenStack(0))), MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))), _nst[_nsp+0]); break;
  case 23: _nst[_nsp]=Mkrule_17(&curpos, Mkrule_18(&(T_POS(TokenStack(0))), MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))), _nst[_nsp+0]); break;
  case 24: _nsp -= 1;_nst[_nsp]=Mk2rule_33(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 25: _nsp -= 1;_nst[_nsp]=Mk2rule_32(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 26: _incrnodestack();_nst[_nsp]=Mkrule_35(&curpos, Mk0rule_35(NoPosition)); break;
  case 27: _incrnodestack();_nst[_nsp]=Mkrule_1(&curpos); break;
  case 28: _nst[_nsp]=Mkrule_35(&curpos, _nst[_nsp+0]); break;
  case 29: _nst[_nsp]=Mkrule_35(&curpos, _nst[_nsp+0]); break;
  case 30: _incrnodestack();_nst[_nsp]=Mk0rule_35(NoPosition); break;
  case 31: _nst[_nsp]=Mkrule_35(&curpos, _nst[_nsp+0]); break;
  case 33: _nsp -= 1;_nst[_nsp]=Mkrule_35(&curpos, Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1])); break;
  case 34: _incrnodestack();_nst[_nsp]=Mk0rule_34(NoPosition); break;
  case 35: _nsp -= 1;_nst[_nsp]=Mkrule_35(&curpos, Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1])); break;
  case 36: _nsp -= 1;_nst[_nsp]=Mkrule_35(&curpos, Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1])); break;
  case 38: _incrnodestack();_nst[_nsp]=Mkrule_14(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 39: _incrnodestack();_nst[_nsp]=Mkrule_002(&curpos); break;
  case 40: _incrnodestack();_nst[_nsp]=Mkrule_001(&curpos); break;
  case 43: _incrnodestack();_nst[_nsp]=Mkrule_25(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 44: _incrnodestack();_nst[_nsp]=Mkrule_24(&curpos, MkText(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 45: _nst[_nsp]=Mkrule_34(&curpos, _nst[_nsp+0]); break;
  case 46: _nst[_nsp]=Mkrule_39(&curpos, Mkrule_28(&(T_POS(TokenStack(0))), MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))), _nst[_nsp+0]); break;
  case 47: _nsp -= 2;_nst[_nsp]=Mkrule_35(&curpos, Mk2rule_35(&curpos, Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]), _nst[_nsp+2])); break;
  case 48: _incrnodestack();_nst[_nsp]=Mk0rule_30(NoPosition); break;
  case 49: _incrnodestack();_nst[_nsp]=Mk0rule_29(NoPosition); break;
  case 50: _incrnodestack();_nst[_nsp]=Mkrule_11(&curpos); break;
  case 51: _incrnodestack();_nst[_nsp]=Mkrule_13(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 52: _nsp -= 1;_nst[_nsp]=Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 53: _nsp -= 1;_nst[_nsp]=Mk2rule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 54: _incrnodestack();_nst[_nsp]=Mkrule_23(&curpos, MkIdentifier(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 55: _incrnodestack();_nst[_nsp]=Mkrule_22(&curpos, MkText(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 56: _incrnodestack();_nst[_nsp]=Mkrule_21(&curpos, MkIdentifier(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 57: _incrnodestack();_nst[_nsp]=Mkrule_20(&curpos, MkText(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 58: _incrnodestack();_nst[_nsp]=Mkrule_38(&curpos, MkText(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 59: _incrnodestack();_nst[_nsp]=Mkrule_6(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 60: _incrnodestack();_nst[_nsp]=Mkrule_5(&curpos, MkText(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 61: _nst[_nsp]=Mkrule_30(&curpos, _nst[_nsp+0]); break;
  case 62: _incrnodestack();_nst[_nsp]=Mkrule_2(&curpos, MkText(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 63: _nst[_nsp]=Mkrule_29(&curpos, _nst[_nsp+0]); break;
  case 64: _nst[_nsp]=Mkrule_4(&curpos, _nst[_nsp+0]); break;
  case 65: _incrnodestack();_nst[_nsp]=Mkrule_003(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 66: _nsp -= 2;_nst[_nsp]=Mkrule_9(&curpos, _nst[_nsp+0], _nst[_nsp+1], _nst[_nsp+2]); break;
  case 67: _nst[_nsp]=Mkrule_31(&curpos, _nst[_nsp+0]); break;
  case 68: _nst[_nsp]=Mkrule_12(&curpos, Mkrule_26(&(T_POS(TokenStack(0))), MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))), _nst[_nsp+0]); break;
  case 69: _incrnodestack();_nst[_nsp]=Mkrule_000(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 70: _incrnodestack();_nst[_nsp]=Mk0rule_33(NoPosition); break;
  case 71: _nst[_nsp]=Mkrule_19(&curpos, Mkrule_27(&(T_POS(TokenStack(1))), MkIdentifier(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))), _nst[_nsp+0]); break;
  case 72: _incrnodestack();_nst[_nsp]=Mkrule_3(&curpos, MkInteger(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 73: _nst[_nsp]=Mkrule_32(&curpos, _nst[_nsp+0]); break;
  case 74: _incrnodestack();_nst[_nsp]=Mkrule_36(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 75: _incrnodestack();_nst[_nsp]=Mkrule_37(&curpos, MkText(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 76: _nst[_nsp]=Mkrule_33(&curpos, _nst[_nsp+0]); break;
  case 77: _incrnodestack();_nst[_nsp]=Mkrule_16(&curpos, MkIdentifier(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  } /* end switch */
}
