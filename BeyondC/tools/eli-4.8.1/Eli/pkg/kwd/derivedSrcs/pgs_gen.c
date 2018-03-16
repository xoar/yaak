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
  case 1: _nst[_nsp]=Mkrule_6(&curpos, _nst[_nsp+0]); break;
  case 2: _nst[_nsp]=Mkrule_8(&curpos, _nst[_nsp+0]); break;
  case 3: _nsp -= 1;_nst[_nsp]=Mkrule_5(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 4: _nst[_nsp]=Mkrule_7(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0))), _nst[_nsp+0]); break;
  case 5: _nsp -= 2;_nst[_nsp]=Mkrule_3(&curpos, _nst[_nsp+0], _nst[_nsp+1], _nst[_nsp+2]); break;
  case 6: _nsp -= 1;_nst[_nsp]=Mkrule_4(&curpos, MkRegularExpr(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0))), _nst[_nsp+0], _nst[_nsp+1]); break;
  case 7: _incrnodestack();_nst[_nsp]=Mkrule_2(&curpos, MkIdentifier(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 8: _incrnodestack();_nst[_nsp]=Mkrule_9(&curpos); break;
  case 9: _nst[_nsp]=Mkrule_12(&curpos, _nst[_nsp+0]); break;
  case 11: _incrnodestack();_nst[_nsp]=Mkrule_10(&curpos); break;
  case 12: _incrnodestack();_nst[_nsp]=Mkrule_1(&curpos, MkIdentifier(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 13: _incrnodestack();_nst[_nsp]=Mkrule_11(&curpos, MkIdentifier(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  } /* end switch */
}
