static char rcsid[] = {"$Id: showEx.c,v 1.11 2013/11/12 20:38:25 profw Exp $"};

/* Copyright 2005, The Regents of the University of Colorado
 *
 * This file is part of the Eli translator construction system.  It
 * implements the conflict reporting mechanism of DeRemer and Pennello
 * (http://doi.acm.org/10.1145/69622.357187) on top of the ZEDER parser
 * generator (http://doi.acm.org/10.1145/1780.1802).
 *
 * Eli is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2, or (at your option) any later
 * version.
 *
 * Eli is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Eli; see the file COPYING.  If not, write to the Free Software
 * Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "p2c.h"
#include <stdio.h>
#include <stdlib.h>
#include "analyse.h"
#include "obstack.h"
#include "showEx.h"

		/* These should be available anywhere for debugging */

static void PrintProduction ELI_ARG((int, int));
static void PrintRHS        ELI_ARG((int, int));

/************************************************************************
 * 									*
 * 			Dynamic Storage					*
 * 									*
 ************************************************************************/

#ifndef obstack_chunk_alloc
#define obstack_chunk_alloc xmalloc
#endif
#ifndef obstack_chunk_free
#define obstack_chunk_free free
#endif

static struct obstack hold;	/* Storage not to be freed */
static struct obstack conf;	/* Storage freed after each conflict */

static void *
#ifdef PROTO_OK
xmalloc(size_t bytes)
#else
xmalloc(bytes) size_t bytes;
#endif
/* Verifying storage allocation
 *   On entry-
 *     bytes=amount of storage to allocate
 *   If enough storage remains then on exit-
 *     xmalloc points to the allocated storage
 *   Else
 *     The program has been terminated with an error report
 **/
{ void *temp = (void *)malloc(bytes);
  if (temp) return (temp);
  fprintf(stderr, "Out of virtual memory!\n");
  exit(2);
}


/************************************************************************
 * 									*
 * 			Queue module					*
 * 									*
 ************************************************************************/

typedef struct QueueElt {
  void *data;
  struct QueueElt *next;
} *QueueElt;

typedef struct Queue {
  QueueElt In, Out;
} *Queue;

static Queue
#ifdef PROTO_OK
NewQueue(void)
#else
NewQueue()
#endif
{ Queue Q = (Queue)obstack_alloc(&hold, sizeof(struct Queue));
  Q->In = Q->Out = (QueueElt)obstack_alloc(&hold, sizeof(struct QueueElt));
  Q->In->next = Q->Out;
  return Q;
}

static void
#ifdef PROTO_OK
PushQueue(Queue Q, void *data)
#else
PushQueue(Q, data) Queue Q; void *data;
#endif
{ if (Q->In->next == Q->Out) {
    Q->In->next = (QueueElt)obstack_alloc(&hold, sizeof(struct QueueElt));
    Q->In->next->next = Q->Out;
  }
  Q->In->data = data; Q->In = Q->In->next;
}

static void *
#ifdef PROTO_OK
PopQueue(Queue Q)
#else
PopQueue(Q) Queue Q;
#endif
{ void *data;
  if (Q->In == Q->Out) return (void *)0;
  data = Q->Out->data; Q->Out = Q->Out->next;
  return data;
}

static void
#ifdef PROTO_OK
EmptyQueue(Queue Q)
#else
EmptyQueue(Q) Queue Q;
#endif
{ Q->Out = Q->In;
}


/************************************************************************
 * 									*
 * 			Transition queue module				*
 * 									*
 ************************************************************************/

static Queue TransitionQ;
static int TTime = 0;	/* "Clock" used to prevent transitions from being
			   considered more than once during the breadth-
			   first search of the "lookback o includes*"
			   relation.  TTime is incremented when a new
			   search is begun. */

		/* Chain to remember the introducing transition */

typedef struct TrChain {
  TUeberElem *data;
  struct TrChain *last;
} *TrChain;

static void
#ifdef PROTO_OK
AddTransitions(Pair *Ts, TrChain L)
#else
AddTransitions(T, L) Pair *T; TrChain L;
#endif
/* Add transitions to TransitionQ
 *   On entry-
 *     Ts points to a list of transitions
 *     L points to the parent of the transitions
 *     TransitionQ has been initialized for this search
 *   On exit-
 *     Each transition on Ts has been added to Q with parent L
 */
{ Pair *p;

  for (p = Ts; p; p = p->N) {
    if (p->T->Seen != TTime) {
      TrChain newelt = (TrChain)obstack_alloc(&conf, sizeof(struct TrChain));
      newelt->data = p->T; newelt->last = L;
      PushQueue(TransitionQ, (void *)newelt); p->T->Seen = TTime; 
    }
  }
}

static void
#ifdef PROTO_OK
InitTransitionQ(Pair *Ts, TrChain L)
#else
InitTransitionQ(Ts, L) Pair *Ts; TrChain L;
#endif
/* Initialize TransitionQ for a breadth-first search
 *   On entry-
 *     Ts points to a list of transitions
 *     L points to the parent of the transitions
 *   On exit-
 *     TransitionQ has been initialized for a new search
 *     Each transition on Ts has been added to TransitionQ with parent L
 */
{ EmptyQueue(TransitionQ); TTime++;
  AddTransitions(Ts, L);
}


/************************************************************************
 * 									*
 * 			Unique item module				*
 * 									*
 ************************************************************************/

#define TBLSIZ 8  /* Number of bits in the hash table index */

		/* Chain of colliding items */

typedef struct ItemList {
  struct ItemList *next;
  int P, D;	  /* Production and dot */
  int Q;	  /* Additional qualifier information */
  int Seen;	  /* Flag for item queue module */
} *ItemList;

static ItemList ItemHash[hashsize(TBLSIZ)];

static void
#ifdef PROTO_OK
InitUniqueItems(void)
#else
InitUniqueItems()
#endif
/* Initialize the unique item module
 *   On entry-
 *     The hold obstack has been initialized
 **/
{ int i;

  for (i = 0; i < hashsize(TBLSIZ); i++) ItemHash[i] = (ItemList)0;
}

static int
#ifdef PROTO_OK
CompareItems(int P, int D, int Q, ItemList Found)
#else
CompareItems(P, D, Q) int P, D, Q; ItemList Found;
#endif
/* Check for a collision
 *   On entry-
 *     P is the item's production
 *     D is is the position of the dot in the production
 *     Q refines the item definition
 *     Found points to the item in the table
 *   If the new item precedes the item found then on exit-
 *     CompareItems<0
 *   If the new item is the item found then on exit-
 *     CompareItems=0
 *   If the new item follows the item found then on exit-
 *     CompareItems>0
 **/
{ if (P == Found->P) {
    if (D == Found->D) return Q - Found->Q;
    return D - Found->D;
  }
  return P - Found->P;
}

static ItemList
#ifdef PROTO_OK
UniqueItem(int P, int D, int Q)
#else
UniqueItem(P, D, Q) int P, D, Q;
#endif
/* Obtain a unique representation of an item
 *   On entry-
 *     P is the item's production
 *     D is is the position of the dot in the production
 *     Q refines the item definition
 *   On exit-
 *     UniqueItem is a unique representation of the refined item
 **/
{ int index;
  ItemList *p, result;

  index =
    hash((ub1*)(&P), sizeof(int),
      hash((ub1*)(&D), sizeof(int),
        hash((ub1*)(&Q), sizeof(int), 0)));
  for  (p = &ItemHash[index & hashmask(TBLSIZ)];
	(result = *p);
	p = &(result->next)) {
    int rel = CompareItems(P, D, Q, result);
    if (rel == 0) return result;
    if (rel < 0) break;
  }

  result = (ItemList)obstack_alloc(&hold, sizeof(struct ItemList));
  result->next = *p; result->P = P; result->D = D; result->Q = Q;
  result->Seen = 0;
  *p = result;
  return result;
}


/************************************************************************
 * 									*
 * 			Item queue module				*
 * 									*
 ************************************************************************/

static Queue ItemQ;
static int ITime = 0;	/* "Clock" used to prevent items from being
			   considered more than once during a breadth-
			   first search.  ITime is incremented when a new
			   search is begun. */

		/* Chain to remember the introducing item */

typedef struct ItemChain {
  ItemList ItemRep;
  struct ItemChain *last;
} *ItemChain;

static void
#ifdef PROTO_OK
AddItem(int P, int D, int Q, ItemChain L)
#else
AddItem(P, D, Q, L) int P, D, Q; ItemChain L;
#endif
/* Add items to ItemQ
 *   On entry-
 *     P is the item's production
 *     D is is the position of the dot in the production
 *     Q qualifies the item
 *     L points to the introducing item
 *     ItemQ has been initialized for this search
 *   On exit-
 *     The item has been added to ItemQ with its introducing item
 */
{ ItemChain new;
  ItemList i = UniqueItem(P, D, Q);

  if (i->Seen == ITime) return;

  new = (ItemChain)obstack_alloc(&conf, sizeof(struct ItemChain));
  new->ItemRep = i; new->last = L;
  PushQueue(ItemQ, (void *)new); i->Seen = ITime;
}

static void
#ifdef PROTO_OK
InitItemQ(int P, int D, int Q, ItemChain L)
#else
InitItemQ(P, D, Q, L) int P, D, Q; ItemChain L;
#endif
/* Initialize ItemQ for a breadth-first search
 *   On entry-
 *     P is the item's production
 *     D is is the position of the dot in the production
 *     Q qualifies the item
 *     L points to the introducing item
 *   On exit-
 *     ItemQ has been initialized for a new search
 *     The item has been added to ItemQ with its introducing item
 */
{ int i;
  
  EmptyQueue(ItemQ); ITime++;
  AddItem(P, D, Q, L);
}


/************************************************************************
 * 									*
 * 		Digraph algorithm to compute Read sets			*
 * 									*
 ************************************************************************/

static TUeberElem **TransStack;
static int TransStackTop, Infinity;
static int *TransArray;

static void
#ifdef PROTO_OK
TraverseRead(TUeberElem *Tr)
#else
TraverseRead(Tr) TUeberElem *Tr;
#endif
/* See DeRemer and Pennello
 *   On entry-
 *     Tr is an unprocessed nonterminal transition
 **/
{ int d;
  Pair *p;

  TransStack[TransStackTop++] = Tr; d = TransStackTop;
  TransArray[Tr->Index] = d;

  for (p = Tr->reads; p; p = p->N) {
    TTMenge scratch;
    TUeberElem *y = p->T;

    if (TransArray[y->Index] == 0) TraverseRead(y);
    TransArray[Tr->Index] = (TransArray[Tr->Index] < TransArray[y->Index] ?
		    TransArray[Tr->Index] : TransArray[y->Index]);
    P_setcpy(scratch, Tr->Read); VereinigeT(scratch, y->Read);
    Tr->Read = HashIn(scratch);
  }

  if (TransArray[Tr->Index] == d) {
    do {
      TransStackTop--;
      TransArray[TransStack[TransStackTop]->Index] = Infinity;
      TransStack[TransStackTop]->Read = Tr->Read;
    } while (TransStack[TransStackTop] != Tr);
  }
}

static void
#ifdef PROTO_OK
InitializeRead(int N)
#else
InitializeRead(N) int N;
#endif
/* Initialize the digraph algorithm
 *   On entry-
 *     N=number of nodes
 *   On exit-
 *     TraverseRead may be called
 */
{ int i;

  Infinity = N + 1;
  TransStack = (TUeberElem **)obstack_alloc(&hold, N * sizeof(TUeberElem *));
  TransStackTop = 0;
  TransArray = (int *)obstack_alloc(&hold, N * sizeof(int));
  for (i = 0; i < N; i++) TransArray[i] = 0;
}


/************************************************************************
 * 									*
 * 			Symbol sequence module				*
 * 									*
 ************************************************************************/

static struct obstack Sequence;
static int *Base = (int *)0;
static int Length;

static void
#ifdef PROTO_OK
StartSequence(void)
#else
StartSequence()
#endif
/* Start a new symbol sequence
 */
{ if (!Base) obstack_init(&Sequence);
  else obstack_free(&Sequence, Base);
  Length = 0;
}

static void
#ifdef PROTO_OK
AddSequence(int S)
#else
AddSequence(S) int S;
#endif
/* Add a symbol to the current sequence
 *   On entry-
 *     A symbol sequence has been started and not finished
 *     S=symbol to be added
 */
{ obstack_grow(&Sequence, &S, sizeof(int));
  Length++;
}

static void
#ifdef PROTO_OK
FinishSequence(void)
#else
FinishSequence()
#endif
/* Finish the current sequence
 *   On entry-
 *     A symbol sequence has been started and not finished
 *   On exit-
 *     Base points to the first element of the sequence
 *     Length=length of the stored sequence
 **/
{ Base = obstack_finish(&Sequence);
}


/************************************************************************
 * 									*
 * 			Common output module				*
 * 									*
 ************************************************************************/

static int Indent;	/* Current indentation level */

typedef struct PD {	/* Data for incrementing the indentation level */
  int P;		  /* Last production printed (0 indicates none) */
  int D;		  /* Index of the symbol in P to be expanded */
} PD;

static int
#ifdef PROTO_OK
ComputeDotIndent(int P, int D, boolean Record)
#else
ComputeDotIndent(P, D, Record) int P, D; boolean Record;
#endif
/* Compute the additional indentation to a symbol to be expanded
 *   On entry-
 *     P=production containing the symbol (0 indicates none)
 *     D=index of the symbol within the right-hand side of the production
 *     Record=true if we need to record the symbols we pass
 *   On exit-
 *     ComputeDotIndent=number of characters preceding the symbol in
 *       the right-hand side of the production
 *     Symbols passed have been recorded if necessary
 **/
{ int result = 0;

  if (P != 0) {
    int RHS = Rs[P-1].RsAnfang - 2;
    int j;
    
    for (j = 1; j < D; j++) {
      int symb = RsFeld[RHS + j];

      if (Record) AddSequence(symb);
      result += Bezeichner[symb]->Lge + 1;
    }
  }
  return result;
}

static void
#ifdef PROTO_OK
PrintIndent(int indent)
#else
PrintIndent(indent) int indent;
#endif
/* Add a sequence of spaces to the current line
 *   On entry-
 *     indent=number of spaces to be printed
 */
{ while (indent > 0) { fputc(' ', Putout); indent--; }
}

static void
#ifdef PROTO_OK
PrintRHS(int P, int D)
#else
PrintRHS(P, D) int P, D;
#endif
/* Add the right-hand side of a production to the current line
 *   On entry-
 *     P=production (0 indicates none)
 *     D=location where a "." is to be inserted
 *	 0 if no "." should be inserted
 */
{ int j, k, l;

  if (P == 0) return;

  j = Rs[P-1].RsAnfang - 1;
  k = j + Rs[P-1].RsLaenge;
  D += j - 1;
  for (l = j; l < k; l++) {
    if (l == D) fputs(". ", Putout);
    fprintf(Putout, "%s ", Bezeichner[RsFeld[l]]->Bezei);
  }
  if (l == D) fputs(". ", Putout);
}

static void
#ifdef PROTO_OK
PrintProduction(int P, int D)
#else
PrintProduction(P, D) int P, D;
#endif
/* Add a complete production to the current line
 *   On entry-
 *     P=production (0 indicates none)
 *     D=location where a "." is to be inserted
 *       0 if no "." should be inserted
 */
{ if (P == 0) return;
  fprintf(Putout, "%s -> ", Bezeichner[Ls[P-1]->SymNr]->Bezei);
  PrintRHS(P, D);
}


/************************************************************************
 * 									*
 * 		Print component (a) of a reduce trace			*
 * 									*
 ************************************************************************/

static void
#ifdef PROTO_OK
PrintPartA(int State, int Production, int Dot)
#else
PrintPartA(State, Production, Dot) int State, Production, Dot;
#endif
/* Print a derivation S =>* gamma B delta
 *   On entry-
 *     State=number of the ending state of the derivation
 *     Production= N -> gamma B delta
 *     Dot=index of B
 *   On exit-
 *     The derivation S =>* gamma B delta has been output
 **/
{ if (Production == StartProduktion) {
    PrintRHS(Production, 0); fputc('\n', Putout);
  } else if (Dot != 1) {
    int pred = State;

    /* Find the lowest-numbered predecessor state */
    TVorListe *v;
    for (v = Q[State-1]->Vorgaenger; v; v = v->NextVor)
      if (v->Vor < pred) pred = v->Vor;

    /* Step back along the current production */
    PrintPartA(pred, Production, Dot - 1);
  } else {
    int LHS = Ls[Production-1]->SymNr;

    /* Find the first item  M -> rho . N chi */
    TItemTyp *i;
    for (i = Q[State-1]->IListe; i; i = i->Naechstes) {
      if (i->Punkt != Rs[i->PNr-1].RsLaenge + 1 &&
	  RsFeld[Rs[i->PNr-1].RsAnfang - 1 + i->Punkt - 1] == LHS) break;
    }
    if (!i) {
      fputs("PrintPartA can't find predecessor item\n", stderr);
      exit(1);
    }

    /* Print a derivation S =>* rho . N chi */
    PrintPartA(State, i->PNr, i->Punkt);

    /* Add gamma B delta to that derivation, starting under N */
    Indent += ComputeDotIndent(i->PNr, i->Punkt, true);
    PrintIndent(Indent); PrintRHS(Production, 0); fputc('\n', Putout);
  }
}


/************************************************************************
 * 									*
 * 			Print the reduce trace				*
 * 									*
 ************************************************************************/

static PD
#ifdef PROTO_OK
RevPrB(ItemChain Derivation)
#else
RevPrB(Derivation) ItemChain Derivation;
#endif
/* Recursively print a derivation
 *   On entry-
 *     Derivation points to the end of the derivation
 *   On exit-
 *     RevPrB defines the position for the next RHS
 */
{ static int Skip;	/* Number of spaces following "|" */
  PD result;

  if (!Derivation->last) {
    /* "|" is at the start of symbol D-1, and takes 1 space */
    Skip = -(ComputeDotIndent(Derivation->ItemRep->P, Derivation->ItemRep->D - 1, false) + 1);
  } else {
    result = RevPrB(Derivation->last);
    if (Derivation->ItemRep->D == 1) {
      Skip += ComputeDotIndent(result.P, result.D, false);
      PrintIndent(Indent); fputc('|', Putout); PrintIndent(Skip);
      PrintRHS(Derivation->ItemRep->P, 0); fputc('\n', Putout);
    }
  }
  result.P = Derivation->ItemRep->P; result.D = Derivation->ItemRep->D;

  return result;
}


static PD
#ifdef PROTO_OK
PrintPartC(TrChain Chain, int Production, int Dot)
#else
PrintPartC(Chain, Production, Dot) TrChain Chain; int Production, Dot;
#endif
/* Expand productions in an includes chain
 *   On entry-
 *     Chain points to the reverse of lookback o includes*
 *     Production=enclosing production
 *     Dot=Position of the nonterminal being expanded
 *   On exit-
 *     All include productions in Chain have been printed
 *     PrintPartC defines the last production printed
 */
{ PD result;
  
  if (Chain->last) {
    TItemTyp *i;

    for (i = Q[Chain->data->S-1]->IListe; i; i = i->Naechstes) {
      int RsLoc = Rs[i->PNr-1].RsAnfang - 1;
      int RsLen = Rs[i->PNr-1].RsLaenge;
      int j;

      if (i->Punkt != 1 || Ls[i->PNr-1]->SymNr != Chain->data->Es) continue;

      for (j = 0; j < RsLen; j++) {
	if (RsFeld[RsLoc + j] == Chain->last->data->Es) {
	  Indent += ComputeDotIndent(Production, Dot, true);
	  PrintIndent(Indent); PrintRHS(i->PNr, 0); fputc('\n', Putout);
	  return PrintPartC(Chain->last, i->PNr, j + 1);
	}
      }
    }
  }

  result.P = Production; result.D = Dot;
  return result;
}

static void
#ifdef PROTO_OK
PrintReduce(TItemTyp *RI, TrChain Chain, TItemTyp *I, int T)
#else
PrintReduce(RI, Chain, I, T) TItemTyp *RI, *I; TrChain Chain; int T;
#endif
/* Print a reduce example
 *   On entry-
 *     RI = conflict item (A -> alpha .)
 *     Chain points to the (lookback o includes*) chain to (p', B)
 *     I = Bn -> alpha B . beta1 in Nucleus(Next(p', B))
 *     T=conflict symbol
 */
{ PD lastPD;
  
  /* Breadth-first search to find the shortest derivation
   * beta1 =>* t beta */
  ItemChain current;

  InitItemQ(I->PNr, I->Punkt, 0, (ItemChain)0);
  while ((current = (ItemChain)PopQueue(ItemQ))) {
    int RHS = Rs[current->ItemRep->P-1].RsAnfang - 2;
    int symb = RsFeld[RHS + current->ItemRep->D];
    int j;

    if (symb == T) break;
    if (SymTab[symb]->SymArt == Term ||
	current->ItemRep->D > Rs[current->ItemRep->P-1].RsLaenge) continue;

    if (SymTab[symb]->UU.U2.Epsilon)
      AddItem(current->ItemRep->P, current->ItemRep->D + 1, 0, current);

    for (j = SymTab[symb]->UU.U2.LSeite; j; j = Ls[j-1]->Naechste) {
      if (Rs[j-1].RsLaenge != 0) AddItem(j, 1, 0, current);
    }
  }
  if (!current) {
    fputs("PrintReduce can't find a path\n", stderr);
    exit(1);
  }

  /* Print the shortest derivation from the axiom to B */
  StartSequence();	/* Remember the symbols of the derivation */
  Indent = 0;
  PrintPartA(Chain->data->S, I->PNr, I->Punkt - 1);
  Indent += ComputeDotIndent(I->PNr, I->Punkt - 1, true);

  /* Print the shortest derivation beta1 =>* t beta */
  RevPrB(current);
  PrintIndent(Indent); fputs("|\n", Putout);

  /* Print the shortest derivation from B to A */
  lastPD = PrintPartC(Chain, 0, 0);

  /* Print the final reduction */
  Indent += ComputeDotIndent(lastPD.P, lastPD.D, true);
  PrintIndent(Indent); PrintRHS(RI->PNr, RI->Punkt);
  ComputeDotIndent(RI->PNr, RI->Punkt, true);
  fputs(" [REDUCE] ", Putout);
  PrintProduction(RI->PNr, 0);
  fprintf(Putout, " {%s} ?\n\n", Bezeichner[T]->Bezei);
  FinishSequence();
}


/************************************************************************
 * 									*
 * 			Print the shift trace				*
 * 									*
 ************************************************************************/

static PD
#ifdef PROTO_OK
RevPrRd(ItemChain Derivation)
#else
RevPrRd(Derivation) ItemChain Derivation;
#endif
/* Recursively print a derivation
 *   On entry-
 *     Derivation points to the end of the derivation
 *   On exit-
 *     RevPrRd defines the position for the next RHS
 */
{ PD result;
  
  if (Derivation->last) {
    result = RevPrRd(Derivation->last);
    if (Derivation->ItemRep->D == 1) {
      Indent += ComputeDotIndent(result.P, result.D, false);
      PrintIndent(Indent);
      PrintRHS(Derivation->ItemRep->P, 0); fputc('\n', Putout);
    }
  } else {
    PrintRHS(Derivation->ItemRep->P, 0); fputc('\n', Putout);
  }

  result.P = Derivation->ItemRep->P; result.D = Derivation->ItemRep->D;
  return result;
}

static void
#ifdef PROTO_OK
PrintShift(int S, TrChain Chain, TItemTyp *I, int T)
#else
PrintShift(S, Chain, I, T) TrChain Chain; TItemTyp *I; int S, T;
#endif
/* Print a shift example
 *   On entry-
 *     S=state in which the conflict occurs
 *     Chain points to the (lookback o includes*) chain to (p', B)
 *     I = Bn -> alpha B . beta1 in Nucleus(Next(p', B))
 *     T=conflict symbol
 */
{ PD lastPD;
  ItemChain current;

  /* Find the conflicting read item */
  TItemTyp *Shift;
  int Drm1;
  TUeberElem *rd;

  for (rd = UeTabelle[S-1]; rd->Es != T; rd = rd->NextEs) ;
  Shift = Q[rd->Z-1]->IListe;
  Drm1 = Ls[Shift->PNr-1]->SymNr;

  /* Shift = Drm1 -> xir T . etar */

  /* Breadth-first search for the shortest path from B to D */

  InitItemQ(StartProduktion, 1, 0, (ItemChain)0);
  while ((current = (ItemChain)PopQueue(ItemQ))) {
    int LHS = Ls[current->ItemRep->P-1]->SymNr;
    int RHS = Rs[current->ItemRep->P-1].RsAnfang - 2;
    int lng = Rs[current->ItemRep->P-1].RsLaenge;
    int symb = RsFeld[RHS + current->ItemRep->D];
    int j = current->ItemRep->Q, k;

    if (LHS == Drm1 && symb == T && j >= Length) break;

    for (k = SymTab[symb]->UU.U2.LSeite; k; k = Ls[k-1]->Naechste) {
      if (Rs[k-1].RsLaenge != 0) AddItem(k, 1, j, current);
    }

    if (j > Length) continue;

    if (symb == Base[j] &&
	current->ItemRep->D < Rs[current->ItemRep->P-1].RsLaenge)
      AddItem(current->ItemRep->P, current->ItemRep->D + 1, j + 1, current);
  }
  if (!current) {
    fputs("PrintShift can't find a path\n", stderr);
    exit(1);
  }

  /* Remove the last production from the derivation */
  while (current->ItemRep->D > 1) current = current->last;
  current = current->last;

  /* Print the derivation from the axiom to D */
  Indent = 0;
  lastPD = RevPrRd(current);

  /* Print the final shift transition */
  Indent += ComputeDotIndent(lastPD.P, lastPD.D, false);
  PrintIndent(Indent); PrintRHS(Shift->PNr, Shift->Punkt - 1);
  fputs(" [SHIFT] ", Putout);
  PrintProduction(Shift->PNr, Shift->Punkt);
  fputs(" ?\n\n", Putout);
}


/************************************************************************
 * 									*
 * 		Find the transitions invoved in a conflict		*
 * 									*
 ************************************************************************/

static long*
#ifdef PROTO_OK
NextInItem(TItemTyp *Item)
#else
NextInItem(Item) TItemTyp *Item;
#endif
/* Determine the next legal terminals
 *   On entry-
 *     Item = Bn -> alpha B . beta1
 *   On exit-
 *     NextInItem = {t | beta1 =>* t betam}
 **/
{ TTMenge scratch;
  int RsLen = Rs[Item->PNr-1].RsLaenge;
  int RsLoc = Rs[Item->PNr-1].RsAnfang - 2;
  int i;
  
  scratch[0] = 0;
  for (i = Item->Punkt; i <= RsLen; i++) {
    int symb = RsFeld[RsLoc + i];
    if (SymTab[symb]->SymArt == Term) {
      HinzuT(scratch, Inab[symb]);
      break;
    } else {
      VereinigeT(scratch, Ntanf[Inab[symb]-1]);
      if (!SymTab[symb]->UU.U2.Epsilon) break;
    }
  }

  return HashIn(scratch);
}

static void
#ifdef PROTO_OK
PrintOnePair(int S, long Kind, int T)
#else
PrintOnePair(S, Kind, C) int S, T; long Kind;
#endif
/* Print derivations leading to a conflict
 *   On entry-
 *     S is the state in which the conflict occurs
 *     Kind=1 for a reduce-reduce conflict
 *	  2 for a shift-reduce conflict
 *     T=symbol on which the conflict occurs
 ***/
{ TItemTyp *i;

  for (i = Q[S-1]->IListe; i; i = i->Naechstes) {
    if (i->Punkt == Rs[i->PNr-1].RsLaenge + 1 && InT(i->RkMenge, T)) {
      /* i = (A -> alpha .) such that the intersection of LA(S, i) and C is
       * not empty.
       */
      TUeberElem *tr;

      /* Breadth-first search for tr = (p', B) such that
       * (S, A -> alpha .) lookback o includes* (p', B) and
       *   T in Read(p', B)
       */
      TrChain current;

      InitTransitionQ(i->LookBack, (TrChain)0);
      while ((current = (TrChain)PopQueue(TransitionQ))) {
	TItemTyp *I;
	TUeberElem *tr = current->data;

	AddTransitions(tr->Includes, current);
	if (!InT(tr->Read, T)) continue;

	/* Now find an I = Bn -> alpha B . beta1 in Nucleus(Next(p', B))
	 * such that beta1 =>* t
	 *
	 * The ZEDER data structure allows us to visit each such item
	 * exactly once, and therefore we don't need an extra EI set.
	 *
	 * If a state has both reduce-reduce and shift-reduce conflicts,
	 * we only need to report one of the reductions conflicting with
	 * the shift.  The others will be reported wth the reduce-reduce
	 * conflict.
	 */

	for (I = Q[tr->Z-1]->IListe; I; I = I->Basis) {
	  if (I->Punkt != Rs[I->PNr-1].RsLaenge + 1 &&
	      InT(NextInItem(I), T)) {
	    PrintReduce(i, current, I, T);
	    if (Kind == 2) {
	      PrintShift(S, current, I, T);
	      return;	/* Skip additional reduce conflicts */
	    }
	  }
	}
      }
    }
  }
}

void
#ifdef PROTO_OK
PrintExample(int S, long Kind, long *C)
#else
PrintExample(S, Kind, C) int S; long Kind, *C;
#endif
/* Print derivations leading to a conflict
 *   On entry-
 *     S is the state in which the conflict occurs
 *     Kind=1 for a reduce-reduce conflict
 *	  2 for a shift-reduce conflict
 *     C is the conflict set
 ***/
{ /* The outermost loop of DeRemer and Pennello's algorithm is implemented
   * by ZEDER, which invokes PrintExample once for each conflict.  That
   * means we must deal with a single conflict here, and give an example
   * (which might be a pair of reductions or a reduction and a shift) for
   * each terminal in the conflict set.
   */

  void *Bound = obstack_alloc(&conf,0);
  int t;

  for (t = 1; t <= AktMaxTerm; t++)
    if (InT(C, t)) PrintOnePair(S, Kind, Tab[t-1]);

  obstack_free(&conf, Bound);
}


/************************************************************************
 * 									*
 * 		Compute additional information				*
 * 									*
 ************************************************************************/

static boolean EmptyGamma[Maxlaengeallerrs];

static void
#ifdef PROTO_OK
MkEmptyGamma(int first, int length)
#else
MkEmptyGamma(first, length) int first, length;
#endif
/* Initialize EmptyGamma for one production
 *   On entry-
 *     first < length
 *     RsFeld[first],...,Rsfeld[first+length-1] is the production's RHS
 *   On exit-
 *     For all first <= i < length, EmptyGamma[i]=true iff
 *       RsFeld[i+1],...,RsFeld[first+length-1] can derive the empty string
 **/
{ boolean CanSeeFollow = true;
  int i = first + length;

  /* Invariant:
   *   CanSeeFollow=true iff
   *     RsFeld[i],...,RsFeld[first+length-1] can derive the empty string
   *   EmptyGamma[i],...,EmptyGamma[first+length-1] have been set
   */

  while (i != first) {
    TSymTabTyp *Symbol;
    i--;
    EmptyGamma[i] = CanSeeFollow;
    Symbol = SymTab[RsFeld[i]];
    if (Symbol->SymArt == Term) CanSeeFollow = false;
    else CanSeeFollow &= Symbol->UU.U2.Epsilon; 
  }
}

static void
#ifdef PROTO_OK
InsertTransition(TUeberElem *T, Pair **List)
#else
InsertTransition(T, List) TUeberElem *T; Pair **List;
#endif
/* Insert a transition into a sorted list
 *   On entry-
 *     T defines the transition to be inserted
 *     List points to the head of the list
 *   On exit-
 *     T has been inserted in order of S
 **/
{ Pair *next = *List;

  while (next && next->T->S < T->S) {
    List = &(*List)->N; next = *List;
  }
  *List = (Pair *)obstack_alloc(&hold, sizeof(Pair));
  (*List)->T = T; (*List)->N = next;
}

static void
#ifdef PROTO_OK
FindReduction(int S, int P, int D, TUeberElem *T)
#else
FindReduction(S, P, D, T) int S, P, D; TUeberElem *T;
#endif
/* Find the reductions looking back to a non-terminal transition
 *   On entry-
 *     S is the current state number
 *     P is the index of the production whose reduction is sought
 *     D is the number of the symbol after the dot (1-origin)
 *     T defines a transition on the LHS symbol of P
 *   On exit-
 *     T has been added to the lookback relation for P's reduction
 **/
{ TItemTyp *i;
  int RsLoc = (Rs[P-1].RsAnfang - 1) + (D - 1);
  int sym = RsFeld[RsLoc];

  for (i = Q[S-1]->IListe; i; i = i->Naechstes) {
    if (i->PNr == P && i->Punkt == D) {

      if (i->Punkt == Rs[P-1].RsLaenge + 1) {
	/* Reduction */
	InsertTransition(T, &(i->LookBack));
	return;
      }

      { /* Advance */
	TUeberElem *tr;

	/* Invariant:
	 *   tr is the first unexamined transition
	 */
	for (tr = UeTabelle[S-1]; tr; tr = tr->NextEs) {
	  if (tr->Es == sym) {
	    if (/*i->Punkt != Rs[P-1].RsLaenge &&*/
		EmptyGamma[RsLoc] &&
		SymTab[sym]->SymArt != Term &&
		T->Es != StartSymNr) {
	      InsertTransition(T, &(tr->Includes));
	    }
	    FindReduction(tr->Z, P, D + 1, T);
	    return;
	  }
	}
      }
    }
  }
}

static long*
#ifdef PROTO_OK
FindDR(int State)
#else
FindDR(State) int State;
#endif
/* Determine the DR set
 *   On exit-
 *     FindDR points to the set of terminals with transitions from State
 **/
{ TTMenge scratch;
  TUeberElem *tr;

  scratch[0] = 0;
  for (tr = UeTabelle[State-1]; tr; tr = tr->NextEs) {
    if (SymTab[tr->Es]->SymArt == Term) {
      HinzuT(scratch, Inab[tr->Es]);
    }
  }

  return HashIn(scratch);
}

static Pair*
#ifdef PROTO_OK
FindReads(int State)
#else
FindReads(State) int State;
#endif
/* Determine the reads relation
 *   On exit-
 *     FindReads points to the set of terminals legal in State
 **/
{ Pair *scratch = (Pair *)0;
  TUeberElem *tr;
  
  for (tr = UeTabelle[State-1]; tr; tr = tr->NextEs) {
    if (SymTab[tr->Es]->SymArt != Term && SymTab[tr->Es]->UU.U2.Epsilon) {
      Pair *new = (Pair *)obstack_alloc(&hold, sizeof(struct Pair));
      new->T = tr; new->N = scratch; scratch = new;
    }
  }
  return scratch;
}

static void
#ifdef PROTO_OK
ChangeStartProduction(void)
#else
ChangeStartProduction()
#endif
/* Change the analyzer database to reflect DeRemer and Pennello's
 * structure:
 *
 * 1. The initial state has no transition on $START_SYMBOL
 * 2. The start production is $START_SYMBOL -> S EOF
 **/
{ int s;		/* Index of the target state for the S transition */

  	/* Remove the transition on $START_SYMBOL */

  UeTabelle[0] = UeTabelle[0]->NextEs;
  s = UeTabelle[0]->Z - 1;

  	/* Change the production */

  RsFeld[AktRsPos-1] = RsFeld[Rs[StartProduktion-1].RsAnfang-1];
  RsFeld[AktRsPos]   = StopSymNr;
  Rs[StartProduktion-1].RsAnfang = AktRsPos;
  Rs[StartProduktion-1].RsLaenge = 2;

  	/* Add a new state and a transition on EOF */

  if (AktMaxZustand == Maxzustand) {
    fprintf(stderr, "Maximum number of states (%d) exceeded\n", Maxzustand);
    exit(1);
  }

  Q[AktMaxZustand] =
	  (TZustandsTyp *)obstack_alloc(&hold, sizeof(TZustandsTyp));
  Q[AktMaxZustand]->IListe =
	  (TItemTyp *)obstack_alloc(&hold, sizeof(TItemTyp));
  memcpy(Q[AktMaxZustand]->IListe, Q[s]->IListe, sizeof(TItemTyp));
  Q[AktMaxZustand]->IListe->Punkt = 3;
  Q[AktMaxZustand]->Naechster = 0;
  Q[AktMaxZustand]->Vorgaenger =
	  (TVorListe *)obstack_alloc(&hold, sizeof(TVorListe));
  Q[AktMaxZustand]->Vorgaenger->Vor = s;
  Q[AktMaxZustand]->Vorgaenger->NextVor = (TVorListe *)0;
  AktMaxZustand++;

  UeTabelle[s] = (TUeberElem *)obstack_alloc(&hold, sizeof(TUeberElem));
  UeTabelle[s]->Es = StopSymNr;
  UeTabelle[s]->Z = AktMaxZustand;
  UeTabelle[s]->NextEs = (TUeberElem *)0;

}

static int AktMaxNtTransitions;

void
#ifdef PROTO_OK
InitExamples(void)
#else
InitExamples()
#endif
/* Initialize the relations needed to output examples
 *   On entry-
 *     LALR(1) analysis is complete
 *     Reductions by chain productions have not been eliminated
 *     Shift-reduce optimizations have not been introduced
 *   On exit-
 *     PrintExample may be invoked
 ***/
{ int i;

  obstack_init(&hold);
  obstack_init(&conf);
  InitUniqueItems();
  TransitionQ = NewQueue();
  ItemQ = NewQueue();
  AktMaxNtTransitions = 0;

  ChangeStartProduction();

  for (i = 0; i < AktMaxProdNr; i++) {
    int lng = Rs[i].RsLaenge;
    if (lng != 0) MkEmptyGamma(Rs[i].RsAnfang-1, lng);
  }

  for (i = 0; i < AktMaxZustand; i++) {
    TUeberElem *T;
    TItemTyp   *I;
    for (T = UeTabelle[i]; T; T = T->NextEs) {
      T->S = i + 1;
      if (SymTab[T->Es]->SymArt != Term) {
	T->Index = AktMaxNtTransitions++;
	T->Includes = (Pair *)0;
	T->Seen = 0;
	T->Read = FindDR(T->Z);
	T->reads = FindReads(T->Z);
      }
    }
    for (I = Q[i]->IListe; I; I = I->Naechstes) {
      I->LookBack = (Pair *)0;
    }
  }

  InitializeRead(AktMaxNtTransitions);
  
  for (i = 0; i < AktMaxZustand; i++) {
    TUeberElem *T;
    TSymTabTyp *Symbol;
    for (T = UeTabelle[i]; T; T = T->NextEs) {
      Symbol = SymTab[T->Es];
      if (Symbol->SymArt != Term) {
	int p;
	
	if (TransArray[T->Index] == 0) TraverseRead(T);

	for (p = Symbol->UU.U2.LSeite; p != 0; p = Ls[p-1]->Naechste) {
	  FindReduction(T->S, p, 1, T);
	}
      }
    }
  }
}
