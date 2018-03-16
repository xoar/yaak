#ifndef ANALYSE_H
#define ANALYSE_H

#include "parameter.h"
#include "eliproto.h"

/* The results of the grammar analysis are contained in a data structure
 * expressing the relationships among five main kinds of entity:
 *
 *   Symbols appearing in the input text
 *   Terminals of the context-free grammar
 *   Nonterminals of the context-free grammar
 *   Productions of the context-free grammar
 *   States of the parsing automaton
 *
 * During the computation, sets of each of these kinds of entity are
 * created.
 */

		/* Symbols */

/* Symbols are numbered by integers in the range 0..AktMaxSymNr.
 * StartSymNr=symbol number of $START_SYMBOL
 * StopSymNr=symbol number of EOF
 * The symbol table consists of three parallel arrays:
 *   SymTab[S] points to the dictionary entry for symbol S
 *   Bezeichner[S] points to the string form of symbol S
 *   Inab[S]=index of the symbol in terminal or nonterminal sets
 */

typedef enum {		/* Kinds of symbols */
  Term,			  /* Terminal symbol of the grammar */
  SymStruk,		  /* Structure connection */
  Nt,			  /* Non-terminal symbol of the grammar */
  HilfNt		  /* Generated non-terminal symbol */
} SymbolArt;


			/* List of nonterminals */
typedef struct TNtKette {
  short N;		  /* Ntab[N-1] = symbol */
  struct TNtKette *NextN;
} TNtKette;

typedef struct {	/* Symbol */
  short Erzu;		  /* State entered via this symbol */
  SymbolArt SymArt;	  /* Kind of symbol */
  union {
    struct {		  /* Information for non-terminal symbols */
      short LSeite;	    /* Production with this symbol as LHS */
      short KettProd;	    /* Chain prod. with this symbol as LHS */
      boolean Epsilon;	    /* If this symbol can generate an empty string */
      TNtKette *RkSchlange; /* Nonterminals from which this nonterminal is
			       derivable by a rightmost derivation */
    } U2;
  } UU;
} TSymTabTyp;

typedef struct {	/* Symbol string */
  char Lge;		  /* Length */
  char *Bezei;		  /* Null-terminated character string */
} TBez;

extern short AktMaxSymNr;
extern short StartSymNr, StopSymNr;
extern TSymTabTyp *SymTab[Maxsymnr + 1];
extern TBez *Bezeichner[Maxsymnr + 1];
extern short Inab[Maxsymnr + 1];

typedef long SymMenge[Maxsymnr / SETBITS + 2];

#define HinzuSym(Sm, I) P_addset(Sm, I)
#define InSym(S, I)     P_inset(I, S)


		/* Terminals */

/* Terminals are numbered by integers in the range 1..AktMaxTerm.
 * Terminal 0 represents epsilon.
 * Tab[T-1]=symbol number for terminal T
 *
 * The construction of exact right contexts results in many identical
 * sets of terminals.  Because a terminal set can be rather large,
 * we provide a hash table to store such sets only once.
 */

extern short AktMaxTerm;
extern short Tab[Maxterm];

typedef long TTMenge[Maxterm / SETBITS + 2];

#define HinzuT(Tm, I)            P_addset(Tm, I)
#define StreicheT(Tm, I)         P_remset(Tm, I)
#define SchneideT(A, B, Schnitt) P_setint(Schnitt, A, B)
#define LeerT(Tm)                (*(Tm)==0)
#define InT(Tm, I)               P_inset(I, Tm)
#define TeilmengeT(A, B)         P_subset(A, B)
#define GleichT(A, B)            P_setequal(A, B)
extern void VereinigeT ELI_ARG((long *A, long *B));
/* Compute A = A union B */

extern long *HashIn ELI_ARG((long *TTm));
/* Hash storage for sets of terminals
 *   On entry-
 *     TTm points to a set of terminals
 *   On exit-
 *     HashIn points to a unique representation of TTm
 ***/


		/* Nonterminals */

/* Nonterminals are numbered by integers in the range 1..AktMaxNterm.
 * Ntab[N-1]=symbol number for nonterminal N
 * Ntanf[N-1]=set of terminals that could begin a sentential form derived
 *   from nonterminal N
 */

extern short AktMaxNterm;
extern short Ntab[Maxnterm];
extern TTMenge Ntanf[Maxnterm];

typedef long TNtMenge[Maxnterm / SETBITS + 2];

#define HinzuNt(A, I)    P_addset(A, I)
#define StreicheNt(N, I) P_remset(N, I)
#define LeerNt(Nt)       (*(Nt)==0)
#define InNt(A, I)       P_inset(I, A)
extern void VereinigeNt ELI_ARG((long *A, long *B));
/* Compute A = A union B */

		/* Hash table */

typedef  unsigned long  int  ub4;   /* unsigned 4-byte quantities */
typedef  unsigned       char ub1;   /* unsigned 1-byte quantities */

#define hashsize(n) ((ub4)1<<(n))
#define hashmask(n) (hashsize(n)-1)

extern ub4 hash( register ub1*, register ub4, register ub4);

		/* Productions */

/* Productions are numbered by integers P in the range 1..AktMaxProdNr.
 * The production set is defined by two parallel arrays:
 *   Ls[P-1] points to the LHS data for production P
 *   Rs[P-1] defines the RHS of production P
 * and another array indexed by values in the range 0..AktRsPos-2:
 *   RsFeld is an array containing the right-hand sides of all productions
 *     Each element of RsFeld is a symbol.  The sequence
 *       RsFeld[Rs[P-1].RsAnfang-1],...,
 *       RsFeld[Rs[P-1].RsAnfang-1 + Rs[P-1].RsLaenge-1]
 *     is the RHS of production P.
 * The number of the start production is given by StartProduktion.
 */

			/* List of structure connections for a production */
typedef struct TStrukturTyp {
  short StrukturNr;
  struct TStrukturTyp *Naechste;
} TStrukturTyp;

			/* List of modifications for a production */
typedef struct TModifikTyp {
  boolean Reduziere;
  short ModSymNr;
  struct TModifikTyp *Naechste;
} TModifikTyp;

typedef struct {	/* Left-hand side */
  short SymNr;		  /* Symbol table index of the LHS symbol */
  short Naechste;	  /* Next production with the same LHS symbol */
  short KettProd;	  /* Next chain production with the same LHS symbol */
  boolean Zusatz;	  /* True if there are connections or modifications */
  union {
    struct {
      TStrukturTyp *Struktan; /* Structure connections */
      TModifikTyp *Modifik;   /* Modifications */
    } U1;
  } UU;
} TLsTyp;

typedef struct {	/* Right-hand side definition */
  short RsAnfang;	  /* Index+1 of the first RHS element */
  int RsLaenge;		  /* Number of RHS elements */
} TRsTyp;

extern short AktMaxProdNr;
extern short StartProduktion;
extern TLsTyp *Ls[Maxprodnr];
extern TRsTyp Rs[Maxprodnr];

extern short AktRsPos;
extern short AktMaxRsLaenge;
extern short RsFeld[Maxlaengeallerrs];

typedef long ProdMenge[Maxprodnr / SETBITS + 2];

#define HinzuP(Pm, I) P_addset(Pm, I)
#define InP(Pm, I)    P_inset(I, Pm)


		/* States */

/* States are numbered by integers S in the range 1..AktMaxZustand.
 * The state set is defined by three parallel arrays:
 *   UeTabelle[S-1] points to the list of transitions from state S
 *   Q[S-1] points to the list of items making up state S
 *   UeberZeich[S-1] points to the set of terminals that correspond to
 *     shift transitions out of state S
 */

			/* List of specific transitions */
typedef struct Pair {
  struct TUeberElem *T;	  /* Pointer to transition defining the pair */
  struct Pair *N;	  /* Pointer to the next pair */
} Pair;

			/* Transition */
typedef struct TUeberElem {
  short Es;		  /* Number of the symbol causing this transition */
  short S;		  /* State in which the transition occurs */
  short Z;		  /* Successor (0 indicates shift-reduce action) */
  short P;		  /* Prod. number to be reduced if shift-reduce */
  struct TUeberElem *NextEs;  /* Next transition for this state */
  int Index;		  /* Index of the transition */
  Pair *Includes;	  /* Other sources of following terminals */
  Pair *reads;		  /* Possible epsilon transitions following */
  long *Read;		  /* Terminals that could be read next */
  int Seen;		  /* Pseudo-clock to prevent multiple enqueues */
} TUeberElem;

			/* Item */
typedef struct TItemTyp {
  short PNr;		  /* Production number */
  int Punkt;		  /* Number of the symbol after the dot (1-origin) */
  struct TItemTyp *Naechstes;  /* Next item in this state */
  struct TItemTyp *Basis; /* Next item in the basis of this state */
  Pair *LookBack;	  /* Transitions to which this can return */
  long *RkMenge;	  /* Exact right context set */
} TItemTyp;

			/* List of predecessor states */
typedef struct TVorListe {
  short Vor;		  /* This element should be ignored if Vor=0 */
  struct TVorListe *NextVor;
} TVorListe;

typedef struct {	/* State */
  TItemTyp *IListe;	  /* Items defining the state */
  short Naechster;	  /* Next state entered by the same symbol */
  TVorListe *Vorgaenger;  /* Predecessors of this state */
} TZustandsTyp;

extern short AktMaxZustand;
extern TUeberElem *UeTabelle[Maxzustand];
extern TZustandsTyp *Q[Maxzustand];
extern long *UeberZeich[Maxzustand];

typedef long ZuMenge[Maxzustand / SETBITS + 2];

#define HinzuZu(Z, I) P_addset(Z, I)
#define InZu(Z, I)    P_inset(I, Z)


		/* Listing file */

extern FILE *Putout;

#endif
