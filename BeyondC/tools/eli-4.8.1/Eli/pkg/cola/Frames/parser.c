/* (C) Copyright 1997 University of Paderborn */

/* This file is part of the Eli Module Library.

The Eli Module Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The Eli Module Library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the Eli Module Library; see the file COPYING.LIB.
If not, write to the Free Software Foundation, Inc., 59 Temple Place -
Suite 330, Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Eli into the
   directory resulting from a :source derivation, you may use that
   created file as a part of that directory without restriction. */

static char rcs_id[]= "$Id: parser.c,v 2.41 1999/02/15 10:24:33 mjung Exp $";
/****************************************************************************/
/********       Skeleton for COLA's table driven parser              ********/
/****************************************************************************/

/****************************************************************************/
/* This part adapts the parser implementation to Eli's compiler environment */
/****************************************************************************/

/*** Include Files ***/

#include <stdlib.h>     /* Provides Prototype for calloc(), exit(), etc. */
#include <string.h>	/* for strlen() */

#include "err.h"	/* Error-handler-module provided by ELI */
#include "treestack.h"	/* functions/types needed for connections */
#include "gsdescr.h"	/* types GRUNDSYMBOLDESKRIPTOR, TERMINALSYMBOL, ATTRTYPE
			 * and macros T_CODE, T_POS, T_ATTR, GET_TOKEN
			 */
#include "HEAD.h"	/* definitions for user defined connections */
#include "reparatur.h"	/* function Reparatur() */
#include "gla.h"	/* function glalex() */
#include "parser.h"	/* parser interface declaring Zerteiler() */

#ifdef MONITOR
#include "dapto_dapto.h"
#include "cola_dapto.h"
#endif 

/* Compare with declaration in "parser.h" */
#define	Parser	Zerteiler

/*** Size of internally used static sized stacks ***/
#ifndef STACKSIZE
#define	STACKSIZE	500
#endif

/*** Default attribute value of inserted semantic terminals ***/
#ifndef	DEFAULT_ATTRVAL
#define	DEFAULT_ATTRVAL	0
#endif

/*** Types ***/

#define	TOKENTYPE	GRUNDSYMBOLDESKRIPTOR
#define	CODETYPE	TERMINALSYMBOL
#define	ATTRTYPE	ATTRTYPE

/*** TOKENTYPE-Macros ***/

#define	CODE(tok)	(T_CODE((*tok)))
#define	POS(tok)	(T_POS((*tok)))
#define	LINE(tok)	(LineOf(T_POS((*tok))))
#define	ATTR(tok)	(T_ATTR((*tok)))

/*** Function Calls ***/

/* Scanner interface: read next token from input stream */
/*	GET_TOKEN must be defined in "gsdescr.h" */
#define	TOKEN(tok)	GET_TOKEN(*(tok))


/* Error module interface: producing an error message */
#define	ERR_MSG(class, text, pos)	message(class, text, 0, &(pos))

#ifdef RIGHTCOORD
/* Position for holding right-hand coordinate */
static POSITION rightpos;
#endif

/* Function for executing semantic actions */
#if defined(__STDC__) || defined(__cplusplus)
static	void	USER(unsigned short action, TOKENTYPE *Token)
#else
static	void	USER(action, Token)
unsigned short	action;
TOKENTYPE	*Token;
#endif
{

/* Connections in "semprods.h" are using names ZAttributKeller, TokenStack,
   and curpos. */
#define ZAttributKeller Token
#ifdef RIGHTCOORD
    POSITION curpos;
    curpos = POS(Token);
    RLineOf (curpos) = RLineOf (rightpos);
    RColOf (curpos) = RColOf (rightpos);
#ifdef MONITOR
    RCumColOf (curpos) = RCumColOf (rightpos);
#endif
#else
#define	curpos		(POS(Token))
#endif
#define TokenStack(i)   (Token[i])
#define	OFFSET		9	/* Depends on conncode[] in "ptabs.h" */

#include "semprods.h"

#undef ZAttributKeller
#undef curpos	/* curpos must be undefined, because its use in GET_TOKEN
		 * may not be influenced! */
#undef TokenStack
  return;
}  /* of USER() */


/****************************************************************************/
/* End of adaptable parser interface -- Start of parser implementation      */
/****************************************************************************/

typedef	unsigned short	U_SHORT;

#ifdef	BOOL
#undef	BOOL
#endif
#define	BOOL	int


#ifdef	FALSE
#undef  FALSE
#endif
#define	FALSE	0

#ifdef	TRUE
#undef	TRUE
#endif
#define	TRUE	1

/****************************************************************************/

/*** Definitions depending on the COLA generated file "ptabs.h" ***/

#include "ptabs.h"

#define	STATETYPE	U_SHORT
#define	ACTIONTYPE	U_SHORT
#define	LENGTHTYPE	U_SHORT

#define	IS_CONN(rule)	((U_SHORT)conncode[rule])

#define	CONN_CODE(rule)	((U_SHORT)conncode[rule])

#define	GET_LHS_NT(rule) ((U_SHORT)lhs[rule])

#define	LENGTH(rule)	((LENGTHTYPE)len[rule])

#define	CONTINUATION(state) ((CODETYPE)cont[state])

#define	STATE2TERMS(state)  (state2terms[state])

#ifdef  NUOFSEPAS
#define SEPASYMB(ind)	((CODETYPE)seps[ind])
#endif

#define	IS_BRACKET(term) (FALSE)

#define	IS_SKIP(term)	(FALSE)


#define	ACTIONMASK	0x0000f000

#define	OPERANDMASK	0x00000fff

/* Action codes */
#define	ERR		0
#define	SHIFT		(1<<12)
#define	SHIFT_NT	(6<<12)
#define	REDUCE		(2<<12)
#define	SHIFTRED	(4<<12)
#define	SHIFTRED_NT	(9<<12)
#define	ACCEPT		(8<<12)

#define	START_STATE	0


/****************************************************************************/
/* Implementation of the table driven parser                                */
/****************************************************************************/

/* Text for Messages */
#define	SX_ERR	"Syntax error"
#define	SE_ERR	"Syntax error: a %s expected."
#define	SI_ERR	"Symbol inserted"
#define	SD_ERR	"Symbol deleted"
#define	PR_ERR	"Parsing resumed here"
#define	PT_ERR	"Wrong parse tables"
#define	SF_ERR	"Parse stack overflow"
#define	AC_ERR	"Accept not expected"

/* String buffer for computing an error message */
#define	BUFLEN	128
static	char	BUF[BUFLEN];

#ifdef __LASTPOS__
static	int	LASTPOS = -1;
#endif

/* Global stack of states and tokens */
static	STATETYPE	state[STACKSIZE];
static	TOKENTYPE	token[STACKSIZE];


/* No side effect to State or Token */
/* On exit: error (continuation) symbol */
#if defined(__STDC__) || defined(__cplusplus)
static	CODETYPE	ErrorSymb(STATETYPE *State, TOKENTYPE *Token)
#else
static	CODETYPE	ErrorSymb(State, Token)
STATETYPE	*State;         /* Points to top of stack 'state' */
TOKENTYPE	*Token;		/* Points to current input token */
#endif
{
  CODETYPE	Term;

  Term = CONTINUATION(*State);

#ifdef	NUOFSEPAS
  {
    CODETYPE	SepTerm;
    int		l;
    STATETYPE	SepRuleOrState, RuleOrState;
    ACTIONTYPE	SepAction, Action;
    BOOL	Hoping;

    /* For each separator symbol do */
    for (l=0; l<NUOFSEPAS; l++)
    {
      if ( (SepTerm = SEPASYMB(l))  ==  Term )
        break;

      /* Is there a valid action with SepTerm for state '*State'? */
      SepRuleOrState = *State;
      GET_TTABENTRY(SepRuleOrState, SepAction, SepTerm);
      if ( SepAction == ERR )
	continue;

      /* Testing whether Term and SepTerm causes identical actions */
      RuleOrState = *State;
      GET_TTABENTRY(RuleOrState, Action, Term);
      if ( Action == SepAction  &&  RuleOrState == SepRuleOrState )
        continue;

      /* Would '*Token' directly be a recovery point after inserting SepTerm? */
      Hoping = TRUE;
      while ( Hoping )
      {
	switch ( SepAction )
	{
	  case SHIFT:
	  case SHIFT_NT:
		/* Testing '*Token' as recovery point */
		GET_TTABENTRY(RuleOrState, Action, CODE(Token));
		if ( Action == SHIFT  ||  Action == SHIFTRED )
		  return(SepTerm);	/* SepTerm is a good error symbol! */
		else
		  Hoping = FALSE;	/* Try next separator symbol */
		break;
	  case SHIFTRED:
	  case SHIFTRED_NT:
		State++;
	  case REDUCE:
		State -= LENGTH(SepRuleOrState);
		GET_NTABENTRY(SepRuleOrState, SepAction, 
				*State,	GET_LHS_NT(SepRuleOrState));
		break;
	  case ACCEPT:
		Hoping = FALSE;		/* Try next separator symbol */
		break;
	  default:
		ERR_MSG(DEADLY, PT_ERR, POS(Token));
		return(Term);
	}  /* of switch */
      }  /* of while */
    }  /* of for */
  }  /* end of part #ifdef  NUOFSEPAS */
#endif

  return(Term);
}  /* of ErrorSymb() */

/* No side effect to State, Token or (global) state */
#if defined(__STDC__) || defined(__cplusplus)
static	BOOL	IsReachable(STATETYPE *State, TOKENTYPE *Token)
#else
static	BOOL	IsReachable(State, Token)
STATETYPE	*State;		/* Points to top of stack 'state' */
TOKENTYPE	*Token;
#endif
{
  STATETYPE	CpState[STACKSIZE];	/* Copy of the global stack 'state' */
  STATETYPE	*travel, *TopState = CpState-1;
  BOOL		IsBracket, 
		TryNextInputToken = FALSE; 
		       /* Controls that error continuation goes
			* til EOF iff *Token is a semantic bracket
			* til next error symbol is a semantic bracket otherwise
			*/
  ACTIONTYPE	Action;
  STATETYPE	RuleOrState;
  CODETYPE	ErrTerm;

  IsBracket = IS_BRACKET(CODE(Token));

  /* Copy global stack 'state' into 'CpState' */
  for (travel=state; travel<=State; travel++)
  {
    *(++TopState) =  *travel;
  }

  Action = SHIFT_NT;
  RuleOrState = *(TopState);
  TopState--;
  while ( TRUE )
  {
      switch ( Action )
      {
	case SHIFT:
	case SHIFT_NT:
		*(++TopState) = RuleOrState;
		if ( TopState == CpState+STACKSIZE )
		{
		  ERR_MSG(DEADLY, SF_ERR, POS(Token));
		  return(FALSE);
		}

                /* Is '*Token' a valid recovery point? */
                GET_TTABENTRY(RuleOrState, Action, CODE(Token));
                if ( Action == SHIFT  ||  Action == SHIFTRED )
		  return(TRUE);

		/* Try next input token as recovery point? */
		else if ( TryNextInputToken )
		  return(FALSE);

		/* Continue testing '*Token' as valid recovery point. */
		else
		{
		  ErrTerm = ErrorSymb(TopState, Token);
		  TryNextInputToken = !IsBracket  &&  IS_BRACKET(ErrTerm);
		  RuleOrState = *TopState;
		  GET_TTABENTRY(RuleOrState, Action, ErrTerm);
		}
		break;

	case SHIFTRED:
	case SHIFTRED_NT:
		TopState++;

	case REDUCE:
		TopState -= LENGTH(RuleOrState);
		GET_NTABENTRY(RuleOrState, Action, 
				*TopState, GET_LHS_NT(RuleOrState));
		break;

	case ACCEPT:
		return(FALSE);

	default:
		ERR_MSG(DEADLY, PT_ERR, POS(Token));
		return(FALSE);
      }  /* of switch */
   }  /* of while */
  
}  /* of IsReachable() */


#define	DEL_TOKEN(tok)	/* ERR_MSG(NOTE, SD_ERR, POS(tok)) */

#define	GEN_TOKEN(tok,code, pos)	{\
					  /* ERR_MSG(NOTE, SI_ERR, pos); */\
					  CODE(tok) = (code);\
					  POS(tok) = (pos);\
					  ATTR(tok) = (DEFAULT_ATTRVAL);\
					}

/* On exit: *Token will be the error recovery point
 *	    State will be unmodified
 */
#if defined(__STDC__) || defined(__cplusplus)
static	void	SearchRecoveryPoint(STATETYPE *State, TOKENTYPE *Token)
#else
static	void	SearchRecoveryPoint(State,Token)
STATETYPE	*State;
TOKENTYPE	*Token;
#endif
{
  BOOL	found = FALSE;

  while ( !found )
  {
    if ( CODE(Token) == PAEOF )
	found = TRUE;
    else
    {
	if ( ! IS_SKIP(CODE(Token)) )		/* Is Token an unsafe anchor? */
	  /* Try Token as anchor (=recovery point). */
	  found = IsReachable(State, Token);
    }  /* of else */

    if ( !found )				/* Token IS an unsafe anchor! */
    {
	DEL_TOKEN(Token);
	TOKEN(Token);				/* Delete Token from input */
    }
  }  /* of while */
}  /* of SearchRecoveryPoint() */


#if defined(__STDC__) || defined(__cplusplus)
void	Parser(void)
#else
void	Parser()
#endif
{

register STATETYPE	*State = state;	/* Points to top of stack state */
register TOKENTYPE	*Token = token;	/* Points to top of stack token */
register STATETYPE	RuleOrState = START_STATE;
register ACTIONTYPE	Action = ERR;
register LENGTHTYPE	length;
	 TOKENTYPE	InputToken[1];	/* only used in error recovery */
	 CODETYPE	ErrTerm=0;	/* only used in error recovery */

#ifdef	_STATISTIK
int	_SH=0, _RED=0, _SHRED=0, _SUM=0;
#endif

#ifdef MONITOR
  _dapto_enter ("parser");
#endif

#ifdef __LASTPOS__
  LASTPOS = -1;
#endif
 
L_SHIFT:
  Token++;
  TOKEN(Token);

L_SHIFT_NT:
  *(++State) = RuleOrState;
  if ( State == state+STACKSIZE )
    ERR_MSG(DEADLY, SF_ERR, POS(Token));

L_TRY_NEWTOKEN:
  GET_TTABENTRY(RuleOrState, Action, CODE(Token));

  if ( Action == REDUCE )
  {
#ifdef	_STATISTIK
    _RED++;
#endif
    goto L_REDUCE;
  }
  else if ( Action == SHIFTRED )
  {
#ifdef	_STATISTIK
    _SHRED++;
#endif
    goto L_SHIFTRED;
  }
  else if ( Action == SHIFT )
  {
#ifdef	_STATISTIK
    _SH++;
#endif
    goto L_SHIFT;
  }
  else if ( Action == ACCEPT )
  {
#ifdef	_STATISTIK
   _SUM = _RED + _SH + _SHRED;
   printf("SHIFT: %d(%2d%%), REDUCE: %d(%2d%%), _SH_RED: %d(%2d%%)\n",
	_SH, _SH*100/_SUM, _RED, _RED*100/_SUM, _SHRED, _SHRED*100/_SUM);
   printf("Summe: %d\n", _SUM);
#endif
#ifdef MONITOR
    {
	extern int ntlen[];
	length = LENGTH (STPROD);
	if (length == 0) {
	    _dapto_production (STPROD, ntlen[STPROD], 1, 1, 1, 1);
	} else {
	    POSITION *p = &POS((Token-1));
	    _dapto_production (STPROD, ntlen[STPROD], 1, 1, RLineOf (*p),
			       RCumColOf (*p));
	}
    }
#endif
    length = LENGTH(RuleOrState)-1;
    State -= length;
    Token -= length;

    if ( IS_CONN(STPROD) )
    {
	USER(CONN_CODE(STPROD), Token);
    }
#ifdef MONITOR
    _dapto_leave ("parser");
#endif
    return;
  } 
  else if ( Action == ERR )
  {
    if ( Reparatur( &(POS(Token)), &(CODE(Token)), &(ATTR(Token)) ) )
	goto L_TRY_NEWTOKEN;
    else
	goto L_ERR;
  }
  else
  {
    ERR_MSG(DEADLY, PT_ERR, POS(Token));
#ifdef MONITOR
    _dapto_leave ("parser");
#endif
    return;
  }

L_SHIFTRED:
  Token++;
  TOKEN(Token);

L_SHIFTRED_NT:
  State++;

L_REDUCE:
  length = LENGTH(RuleOrState);
#ifdef RIGHTCOORD
  {
      if (length == 0) {
	  POSITION *p = &POS(Token);
          LineOf (rightpos) = RLineOf (rightpos) = LineOf (*p);
          ColOf (rightpos) = RColOf (rightpos) = ColOf (*p);
#ifdef MONITOR
          CumColOf (rightpos) = RCumColOf (rightpos) = CumColOf (*p);
#endif
      } else {
	  POSITION *p = &POS ((Token-1));
          rightpos = POS ((Token - length));
          RLineOf (rightpos) = RLineOf (*p);
          RColOf (rightpos) = RColOf (*p);
#ifdef MONITOR
          RCumColOf (rightpos) = RCumColOf (*p);
#endif
      }
  }
#endif
  State -= length;
  Token -= length;
  if ( IS_CONN(RuleOrState) )
  {
    USER(CONN_CODE(RuleOrState), Token);
  }

#ifdef RIGHTCOORD
#ifdef MONITOR
  {
      extern int ntlen[];
      _dapto_production (RuleOrState, ntlen[RuleOrState], LineOf (rightpos),
                         CumColOf (rightpos), RLineOf (rightpos),
                         RCumColOf (rightpos));
  }
#endif
  POS (Token) = rightpos;
#endif

  GET_NTABENTRY(RuleOrState, Action, *State, GET_LHS_NT(RuleOrState));

  /* Copy current lookahead token to top of token stack */
  Token++;
  *Token = *(Token+length-1);

  if ( Action == SHIFT_NT )
  {
    goto L_SHIFT_NT;
  }
  else 
#ifdef DEBUG
  if ( Action == SHIFTRED_NT )
#endif
  {
    goto L_SHIFTRED_NT;
  }
#ifdef DEBUG
  else if ( Action == ACCEPT )
  {
    if ( IS_CONN(STPROD) )
    {
	USER(CONN_CODE(STPROD), Token);
	ERR_MSG(FATAL, AC_ERR, POS(Token));
    }
#ifdef MONITOR
    _dapto_leave ("parser");
#endif
    return;
  } 
  else
  {
    ERR_MSG(DEADLY, PT_ERR, POS(Token));
#ifdef MONITOR
    _dapto_leave ("parser");
#endif
    return;
  }
#endif

L_ERR:
  if (	state2terms[*State] != (char *)NULL &&
#ifdef __LASTPOS__
	LASTPOS+1 < LINE(Token) &&
#endif
     	((int)(strlen(state2terms[*State]) + strlen(SE_ERR))) < BUFLEN)
  {
    (void)sprintf(BUF, SE_ERR, STATE2TERMS(*State));
    ERR_MSG(ERROR, BUF, POS(Token));
  }
  else
    ERR_MSG(ERROR, SX_ERR, POS(Token));

#ifdef __LASTPOS__
  LASTPOS = LINE(Token);
#endif

#ifdef  _ERROR_OFF
#ifdef MONITOR
  _dapto_leave ("parser");
#endif
  return;	/* Stop after the first syntax error! */
#endif 

  SearchRecoveryPoint(State, Token);

  /* GotoRecoveryPoint */
  *InputToken = *Token;
  Action = SHIFT_NT;
  RuleOrState = *(State--);
  while ( TRUE )
  {
      switch ( Action )
      {
	case SHIFT:
		GEN_TOKEN(Token, ErrTerm, POS(InputToken));
		Token++;

	case SHIFT_NT:
		*(++State) = RuleOrState;
		if ( State == state+STACKSIZE )
		  ERR_MSG(DEADLY, SF_ERR, POS(InputToken));

                /* Is recovery point reached? */
                GET_TTABENTRY(RuleOrState, Action, CODE(InputToken));
                if ( Action == SHIFT  ||  Action == SHIFTRED )
		{
		  *Token = *InputToken;
		  ERR_MSG(NOTE, PR_ERR, POS(Token));
		  if ( Action == SHIFT )
		    goto L_SHIFT;
		  else
		    goto L_SHIFTRED;
		}

		/* Continue going to the valid recovery point. */
		RuleOrState = *State;
		ErrTerm = ErrorSymb(State, InputToken);
		GET_TTABENTRY(RuleOrState, Action, ErrTerm);
		break;

	case SHIFTRED:
		GEN_TOKEN(Token, ErrTerm, POS(InputToken));
		Token++;

	case SHIFTRED_NT:
		State++;

	case REDUCE:
		length = LENGTH(RuleOrState);
#ifdef RIGHTCOORD
                {
                    if (length == 0) {
                        POSITION *p = &POS (Token);
                        LineOf (rightpos) = RLineOf (rightpos) = LineOf (*p);
                        ColOf (rightpos) = RColOf (rightpos) = ColOf (*p);
#ifdef MONITOR
                        CumColOf (rightpos) = RCumColOf (rightpos) =
                            CumColOf (*p);
#endif
                    } else {
                        POSITION *p = &POS ((Token-1));
                        rightpos = POS ((Token - length));
                        RLineOf (rightpos) = RLineOf (*p);
                        RColOf (rightpos) = RColOf (*p);
#ifdef MONITOR
                        RCumColOf (rightpos) = RCumColOf (*p);
#endif
                    }
                }
#endif

		State -= length;
		Token -= length;
		if ( IS_CONN(RuleOrState) )
		{
		  USER(CONN_CODE(RuleOrState), Token);
		}

#ifdef RIGHTCOORD
#ifdef MONITOR
                {
                    extern int ntlen[];
                    _dapto_production (RuleOrState, ntlen[RuleOrState],
                                       LineOf (rightpos), CumColOf (rightpos),
                                       RLineOf (rightpos),
                                       RCumColOf (rightpos));
                }
#endif
                POS (Token) = rightpos;
#endif

		GET_NTABENTRY(RuleOrState, Action, 
					*State, GET_LHS_NT(RuleOrState));

		/* Copy current lookahead token to top of token stack */
		Token++;
		*Token = *(Token+length-1);

		break;

	case ACCEPT:
		ERR_MSG(NOTE, PR_ERR, POS(InputToken));
		if ( IS_CONN(STPROD) )
		{
		  USER(CONN_CODE(STPROD), Token);
		}
#ifdef MONITOR
		_dapto_leave ("parser");
#endif
		return;

	default:
		ERR_MSG(DEADLY, PT_ERR, POS(InputToken));
#ifdef MONITOR
		_dapto_leave ("parser");
#endif
		return;
      }  /* of switch */
   }  /* of while */
}  /* of Parser() */


