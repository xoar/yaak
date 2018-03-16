/* Copyright 1977, Peter Dencker, Universitaet Karlsruhe, Fakultaet fuer
     Informatik */

/* This file is part of the PGS parser generator

PGS is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

PGS is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with PGS; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

static char rcsid[] = {"$Id: pgs_optim.c,v 1.21 2009/09/28 11:32:26 asloane Exp $"};

/* Output from p2c, the Pascal-to-C translator */
/* From input file "optimierung.p" */


#include "p2c.h"
#include <stdlib.h>
#define HAS_STDLIB
#include "obstack.h"
#include "options.h"


/**********************************************************************/
/*                                                                    */
/*  Autor der Optimierung : Matthias Martin im August 1987            */
/*                                                                    */
/**********************************************************************/
/*                                                                    */
/* Dateien :                                                          */
/*         output         : text; (Ausgabe)                           */
/*              Enthaelt die Dialog-Information                       */
/*                                                                    */
/*         Putout         : text; (Ausgabe)                           */
/*              Enthaelt das Benutzerprotokoll                        */
/*                                                                    */
/*         Interdat       : Intfile; (Eingabe)                        */
/*              Ist die Variablenschnittstelle zwischen Analyse und   */
/*              Optimierung                                           */
/*                                                                    */
/*         Zerdat         : Intfile; (Ausgabe)                        */
/*              Enthaelt die optimierten Zerteilertabellen            */
/*                                                                    */
/*         Zudat          : text; (Ausgabe)                           */
/*              Enthaelt die Zerteilerkonstanten und Tabellenoptionen */
/*                                                                    */
/*         Tabdat         : Intfile; (Eingabe)                        */
/*              Enthaelt die nicht optimierten Zerteilertabellen      */
/*                                                                    */
/*         Symbolda       : text; (Eingabe)                     */
/*              Enthaelt die Symboltabelle                            */
/*                                                                    */
/*                                                                    */
/*  Optionen fuer die Optimierung:                                    */
/*      F = Verwendung von festen Defaultzustaenden fuer den TTeil    */
/*      O = Optimierung                                               */
/*      P = Zielsprache Modula2                                       */
/*      S = A+O+Z                                                     */
/*      U = Zielsprache C                                             */
/*      Y = Zielsprache Ada                                           */
/*                                                                    */
/**********************************************************************/

#include "parameter.h"

#define MaxAdjacent     100000
typedef int AdjacentRange;	/* 1..MaxAdjacent */

#define MaxTrie         5000
typedef short TrieRange;	/* 0..MaxTrie */

#define MaxComb         20000
typedef short CombRange;	/* 0..MaxComb */

#define TNil            0
#define NoState         0
#define NoProduction    0
#define NoDist          0

#define MaxTableEntry   32767
typedef int  TableRange;	/* 0..MaxTableEntry */


/* willkuerlich aber >= Max (Maxzustand*3, Maxprodnr*3+2 )    */



/* ZAHL 0 RESERVIERT FUER:  */
/* KEINE NAECHSTE PRODUKTION */

typedef char *Symbolstring;
typedef long Symnrtyp[Maxsymnr / SETBITS + 2];

typedef enum {
  Term, Symstruk, Nt, Hilfnt
} Symbolart2;



typedef struct Tsymtabtyp {
  short Erzu;
  Symbolart2 Symart2;
  union {
    struct {
      short Lseite, Kettprod;
      long *Rkschlange;
      /* Irgendein Verweisyyp,wegen Schnittstellenkonsistenz */
      boolean Epsilon;
    } U2;
  } UU;
} Tsymtabtyp;

typedef struct Drusym {
  int Snr, Laenge;
  Symbolstring Bez;
} Drusym;

typedef struct Tstrukturtyp {
  short Strukturnr;
  struct Tstrukturtyp *Naechste;
} Tstrukturtyp;

typedef struct _REC_Strukturanknuepfung {
  boolean Strukt;
  union {
    Tstrukturtyp *Anknuepfung;
  } UU;
} _REC_Strukturanknuepfung;



typedef _REC_Strukturanknuepfung Strukturanknuepfung[Maxprodnr];

/* 0 <-> NoState */
/* 0 <-> NoProduction */

typedef struct AdjacentEntry {
  short Symbol;
  TableRange TableEntry;
} AdjacentEntry;

typedef struct BaseEntry {
  AdjacentRange StateBase;
  short StateCard;
} BaseEntry;

typedef struct TrieNode {
  TrieRange Next;
  boolean EndMarker;
  union {
    struct {
      TrieRange Son;
      short Distance;
    } U0;
    struct {
      short State;
      short StartCol;
    } U1;
  } UU;
} TrieNode;


Static FILE *Interdat, *Zerdat, *Tabdat;
Static FILE *Symbolda;
Static FILE *Strukdat, *Putout, *Zudat;
#ifdef MONITOR
Static FILE *prodsfile;
#endif
Static Symnrtyp BRACKET, SKIP;
Static Drusym *SymbolTable[Maxsymnr + 1];
Static long Two;   /* Workaround for BSD Pascal bug */


Static char Extgramtitel[Maxsymlaenge], Gramtitel[Maxsymlaenge];
Static Char Udatum[24];   /* SIEMENS-PASCAL */


Static AdjacentEntry AdjacentVector[MaxAdjacent];
Static BaseEntry BaseVector[Maxzustand];
/* Die nicht optimierten Zerteilertabellen werden zur Opti-   */
/* mierung in eine Adjazenzliste (AdjacentVector) eingelesen. */
/* Durch diese Methode muessen nur die nicht leeren Eintraege */
/* der Zerteilertabellen gespeichert werden. Der Vektor Base- */
/* Vector enthaelt zu jedem Zustand den Index des ersten Ein- */
/* trags in der Adjazenzliste und die Anzahl der Eintraege.   */
/* Jeder Eintrag der Adjazenzliste besteht aus einem Eintrag  */
/* der Zerteilertabelle und dem dazugehoerigen Symbol. Die    */
/* Eintraege der Adjazenzliste zu jedem Zustand werden nach   */
/* den Symbolen sortiert.                                     */
Static TrieNode Trie[MaxTrie];
/* Der Trie wird zur schnellen Konstruktion eines Kammvektors */
/* aus den duenn besetzten Zerteilertabellen benoetigt.       */
Static short ActMaxRsLength;
Static short ActMaxProdNr;
Static short StopSymNr, StartSymNr, NonMinimal, MaxTerminalCode, ActMaxTerm,
	     ActMaxNTerm, ActMaxSymNr;
Static long NumProd;
Static short ActMaxState;

Static boolean Keinefehler;
Static long Optimierzeit;

Static short Tab[Maxterm];
/* Abbildung vom Terminalbereich in den Bereich der Symbolnummern */
Static short Ntab[Maxnterm];
FILEBUF(Interdat,Static,long);
FILEBUF(Zerdat,Static,long);
FILEBUF(Tabdat,Static,long);
FILEBUF(Symbolda,Static,char);

/* Obstack for identifer and literal strings */

static struct obstack SymObs;


/* Abbildung vom Nichtterminalbereich in den Bereich der      */
/* Symbolnummern                                              */

/************************************************************/
/*                                                          */
/*    Module time_date                                      */
/*    ================                                      */
/*                                                          */
/*    Author: J. Grosch                                     */
/*    Date  : 30.10.85                                      */
/*                                                          */
/*    provides the following subroutines to access          */
/*    time and date information for various PASCAL          */
/*    systems:                                              */
/*                                                          */
/*                                                          */
/*    function cputime: integer;                            */
/*                                                          */
/*    - returns the used cpu time in ms                     */
/*                                                          */
/*                                                          */
/*    procedure daytime (var dt: string12);                 */
/*                                                          */
/*    - returns the time of day in a 12 character           */
/*    - representation                                      */
/*                                                          */
/*                                                          */
/*    procedure daydate (var dd: string12);                 */
/*                                                          */
/*    - returns the date in a 12 character representation   */
/*                                                          */
/*                                                          */
/*    The type string12 has to be declared in the           */
/*    following way:                                        */
/*                                                          */
/*    type string12 = packed array [1..12] of char;         */
/*                                                          */
/*                                                          */
/*    Currently the following PASCAL systems are            */
/*    supported:                                            */
/*                                                          */
/*    SIEMENS    - BS2000       - PASCAL 3.0                */
/*    PCS Cadmus - Munix        - PASCAL 68000              */
/*    PCS Cadmus - Munix        - PASCAL-2 (Oregon)         */
/*    DEC VAX    - BSD Unix 4.2 - BSD-PASCAL                */
/*                                                          */
/************************************************************/



Static long cputime()
{
  return 0;
}


Static long RdInterdat()
{
  long Result;

  /*       *****/
  Result = GETFBUF(Interdat, long);
  GET(Interdat, long);
  return Result;
}  /* VON RDINT */


Static Void Messzeit(Mess, Startzeit, Stopzeit)
Char *Mess;
long Startzeit, Stopzeit;
{
  /*        ********/
  long Zeit;

  Zeit = Stopzeit - Startzeit;
  fprintf(Putout, "%.12s-Time           : %8.2f Seconds\n",
	  Mess, (double)Zeit / Izeiteinheit);
}  /* VON MESSZEIT */


Static boolean Insymbol(S, I)
long *S;
unsigned I;
{
  /*       ********/
  return P_inset(I, S);
}  /* VON INSYMBOL */




Static Void ErrorText(Dat, Number)
FILE **Dat;
long Number;
{
  switch (Number) {

  case 1:
    fprintf(*Dat, "Error reading file Interdat");
    break;

  case 2:
    fprintf(*Dat, "Constant MaxComb = %ld is too small", (long)MaxComb);
    break;

  case 3:
    fprintf(*Dat, "Constant MaxTrie = %ld is too small", (long)MaxTrie);
    break;

  case 4:
    fprintf(*Dat, "Constant MaxAdjacent = %ld is too small",
	    (long)MaxAdjacent);
    break;

  case 5:
    fprintf(*Dat, "Constant Maxzustand = %ld is too small", (long)Maxzustand);
    break;

  case 6:
    fprintf(*Dat, "Constant Maxlaengeallers = %ld is too small",
	    (long)Maxlaengeallerrs);
    break;

  case 7:
    fprintf(*Dat, "Constant Maxprodnr = %ld is too small", (long)Maxprodnr);
    break;

  case 8:
    fprintf(*Dat, "Constant Maxsymnr = %ld is too small", (long)Maxsymnr);
    break;

  case 9:
    fprintf(*Dat, "Constant Maxterm = %ld is too small", (long)Maxterm);
    break;

  case 10:
    fprintf(*Dat, "Constant Maxnterm = %ld is too small", (long)Maxnterm);
    break;
  }
}  /* ErrorText */


Static Void ErrorMessage(Number)
long Number;
{
  /* Ausdruck auf Datei Putout und output */
  FILE *TEMP;

  Keinefehler = false;
  printf("*** Optimization-Error: ");
  TEMP = stdout;
/* p2c: optimierung.p, line 463:
 * Note: Taking address of stdout; consider setting VarFiles = 0 [144] */
  ErrorText(&TEMP, Number);
  putchar('\n');
  fprintf(Putout, "*** Error : ");
  ErrorText(&Putout, Number);
  putc('\n', Putout);
}  /* ErrorMessage */


typedef CombRange BaseType[Maxzustand + 1];
typedef short ProProType[Maxprodnr];
typedef short StStType[Maxzustand + 1];
typedef enum {
  PASCAL, MODULA2, C, ADA
} Language;


Static jmp_buf _JL1;


#define NumInterval     3   /* Der Kammvektor wird in NumInterval Schritten */


#define MaxChain        8   /* Maximal MaxChain Zustaende     */


/* duerfen in einer Kette ent-    */
/* halten sein. Laengere Ketten   */
/* werden durchgetrennt.          */


#define Bytes           " bytes"

#define B               8   /* Druckbreite  */


#define ZEMAXBIT2       "ZEMAXBIT2         "
#define ZEMAXBITS2      "ZEMAXBITS2        "
#define ZEMAXTEINTRAG   "ZEMAXTEINTRAG     "
#define ZEMAXNTEINTRAG  "ZEMAXNTEINTRAG    "
#define ZEMAXTE1        "ZEMAXTE1          "
#define ZEMAXTE2        "ZEMAXTE2          "
#define ZEMAXNTE        "ZEMAXNTE          "
#define ZEMAXTERMINALCODE  "ZEMAXTERMINALCODE "
#define ZEMAXRSLAENGE   "ZEMAXRSLAENGE     "
#define ZEANZZST        "ZEANZZST          "
#define ZEANZNT         "ZEANZNT           "
#define ZEANZPROD       "ZEANZPROD         "
#define ZEMAXTNEXT      "ZEMAXTNEXT        "
#define ZEMAXTCHECK     "ZEMAXTCHECK       "
#define ZEMAXTTAB       "ZEMAXTTAB         "
#define ZEMAXNTNEXT     "ZEMAXNTNEXT       "
#define ZEMAXNTAB       "ZEMAXNTAB         "
#define ZETINDEX        "ZETINDEX          "
#define ZESTOPSYMBOL    "ZESTOPSYMBOL      "


typedef Char Packoption[20];
typedef Char Konstantenname[18];


/* Local variables for Optimization: */
struct LOC_Optimization {
  boolean FixedDefaults, VariableDefaults, Strukturvorhanden;
  long TMaxNext, TMaxCheck, NtMaxNext, NtMaxEntry, TMaxEntry, NtEntryCount1,
       NtEntryCount2, TEntryCount1, TEntryCount2, TEntryCount3, AdjazenzTop;
  StStType StateImage;
  ProProType ProdImage;
  Strukturanknuepfung Struktur;
  Language TargetLanguage;
} ;

Local Void SortRow(L, R, LINK)
AdjacentRange L, R;
struct LOC_Optimization *LINK;
{
  /* Die zu einem Zustand gehoerigen Eintraege der Zerteilertabellen */
  /* in der Adjazenzliste werden nach aufsteigenden Symbolnummern    */
  /* sortiert.                                                       */
  AdjacentRange I, J;
  short S;
  AdjacentEntry W;


  I = L;
  J = R;
  S = AdjacentVector[(L + R) / 2 - 1].Symbol;
  do {

    while (AdjacentVector[I - 1].Symbol < S)
      I++;
    while (AdjacentVector[J - 1].Symbol > S)
      J--;

    if (I <= J) {
      W = AdjacentVector[I - 1];
      AdjacentVector[I - 1] = AdjacentVector[J - 1];
      AdjacentVector[J - 1] = W;
      I++;
      J--;
    }

  } while (I <= J);

  if (L < J)
    SortRow(L, J, LINK);
  if (I < R)
    SortRow(I, R, LINK);

}  /* SortRow */


Local Void SortStates(MaxState, MaxCard, LINK)
short *MaxState;
short MaxCard;
struct LOC_Optimization *LINK;
{
  /* Schubfachsortierung der Zustaende nach der Anzahl der "aktiven" */
  /* Eintraege durch Aufbau des Abbildungsvektors StateImage.        */
  /* MaxState ist die Anzahl der Zustaende mit mindestens einem      */
  /* Tabelleneintrag. MaxCard ist die groesste vorkommende Anzahl    */
  /* von Eintraegen.                                                 */
  long Bucket[Maxsymnr + 1], StartIndex[Maxsymnr + 1];
  short Index, State;
  short I;
  short FORLIM;
  BaseEntry *WITH;


  FORLIM = ActMaxState + 1;
  for (State = 1; State <= FORLIM; State++)
    LINK->StateImage[State] = State;
  /* StateImage [ActMaxState + 1] muss einen definierten Wert*/
  /* enthalten, da in CompressTable eventuell darauf zugegriffen*/
  /* wird (in einer Schleifenabbruchbedingung).*/

  for (I = 0; I <= MaxCard; I++)
    Bucket[I] = 0;

  FORLIM = ActMaxState;
  for (State = 0; State < FORLIM; State++) {
    WITH = &BaseVector[State];
    Bucket[WITH->StateCard]++;
  }

  Index = 1;
  for (I = MaxCard; I >= 0; I--) {
    StartIndex[I] = Index;
    Index += Bucket[I];
  }

  FORLIM = ActMaxState;
  for (State = 1; State <= FORLIM; State++) {
    WITH = &BaseVector[State - 1];
    LINK->StateImage[StartIndex[WITH->StateCard]] = State;
    StartIndex[WITH->StateCard]++;
  }

  *MaxState = ActMaxState;
  while (*MaxState > 0 &&
	 BaseVector[LINK->StateImage[*MaxState] - 1].StateCard == 0)
    (*MaxState)--;

}  /* SortStates */


/*********************************************************************/
/*                                                                   */
/* Operationen zur Bearbeitung der Datenstruktur Strukturanknuepfung */
/*                                                                   */
/*********************************************************************/

Local boolean Leerstrukt(Liste)
Tstrukturtyp *Liste;
{
  return (Liste == NULL);
}

Local Void Zustrukt(Liste, El)
Tstrukturtyp **Liste;
short El;
{

  /* Fuegt El am Ende der Liste ein, weil Reihenfolge erhalten */
  /* bleiben muss                                              */
  Tstrukturtyp *Selem, *Listlaeufer;

  Selem = (Tstrukturtyp *)malloc(sizeof(Tstrukturtyp));
  Selem->Strukturnr = El;
  Selem->Naechste = NULL;
  if (*Liste == NULL) {
    *Liste = Selem;
    return;
  }
  Listlaeufer = *Liste;
  while (Listlaeufer->Naechste != NULL)
    Listlaeufer = Listlaeufer->Naechste;
  /* Laeuft ans Listenende */
  Listlaeufer->Naechste = Selem;
}

Local short Wegstrukt(Liste)
Tstrukturtyp **Liste;
{
  /* Liefert Element und loescht es aus der Liste */
  short A;

  if (*Liste != NULL) {
    A = (*Liste)->Strukturnr;
    *Liste = (*Liste)->Naechste;
  }
  return A;
}


Local Void Druckeanknuepfung(Sym)
short Sym;
{
  long I;
  Drusym *WITH;

  WITH = SymbolTable[Sym];
  if (WITH->Bez[0] != '\'') {
    fputs(WITH->Bez, Strukdat);
    return;
  }
  I = 2;
  while (I < WITH->Laenge) {
    putc(WITH->Bez[I - 1], Strukdat);
    if (WITH->Bez[I - 1] == '\'')
      I++;
    I++;
  }
}

/**********************************************************************/

Local Void PrintSemanticActions(LINK)
struct LOC_Optimization *LINK;
{

  /* Generiert ein Macro mit Zielsprachentext zum Aufruf der Struk-*/
  /* turanknuepfungen. Das generierte Macro wird mit in den Zer-   */
  /* teiler eingebunden.                                           */
  short I, J;
  long K;
  boolean Erste;
  short FORLIM;
  _REC_Strukturanknuepfung *WITH;


  if (Strukdat != NULL)
    Strukdat = freopen("Strukdat", "w", Strukdat);
  else
    Strukdat = fopen("Strukdat", "w");
  if (Strukdat == NULL)
    _EscIO(FileNotFound);

  switch (LINK->TargetLanguage) {

  case PASCAL:
    if (LINK->Strukturvorhanden) {
      fprintf(Strukdat, "  if PR in [");
      I = 1;
      while (!LINK->Struktur[I - 1].Strukt)
	I++;

      fprintf(Strukdat, "%4d", I);
      K = 0;
      FORLIM = NumProd;
      for (J = I + 1; J <= FORLIM; J++) {
	if (LINK->Struktur[J - 1].Strukt) {
	  K++;
	  if (K % 10 == 0)
	    fprintf(Strukdat, "\n           ");
/* p2c: optimierung.p, line 690:
 * Note: Using % for possibly-negative arguments [317] */
	  fprintf(Strukdat, ",%4d", J);
	}
      }
      fprintf(Strukdat, " ] then\n");
      fprintf(Strukdat, "  case PR of\n");

      FORLIM = NumProd;
      for (I = 1; I <= FORLIM; I++) {
	WITH = &LINK->Struktur[I - 1];
	if (WITH->Strukt) {   /* Leerstrukt = false */
	  if (!Leerstrukt(WITH->UU.Anknuepfung->Naechste))
	  {  /* Es gibt mehr als 1 Strukturanknuepfung     */
	    fprintf(Strukdat, "%7d: begin\n", I);
	    do {
	      fprintf(Strukdat, "           ");
	      Druckeanknuepfung(Wegstrukt(&WITH->UU.Anknuepfung));
	      fprintf(Strukdat, ";\n");
	    } while (!Leerstrukt(WITH->UU.Anknuepfung));
	    fprintf(Strukdat, "         end;\n");
	  } else {  /* Es gibt genau 1 Strukturanknuepfung zu      */
	    fprintf(Strukdat, "%7d: begin ", I);
	    Druckeanknuepfung(Wegstrukt(&WITH->UU.Anknuepfung));
	    fprintf(Strukdat, " end;\n");
	  }
	  /* zu Produktion I                            */
	}
      }

      fprintf(Strukdat, "  end; (* VOM case UND if *)\n");
    } else
      fprintf(Strukdat, "  (* KEINE STRUKTURANKNUEPFUNGEN VORHANDEN *)\n");
    break;


  case MODULA2:
    if (LINK->Strukturvorhanden) {
      fprintf(Strukdat, "  CASE Pr OF\n");

      Erste = true;

      FORLIM = NumProd;
      for (I = 1; I <= FORLIM; I++) {
	WITH = &LINK->Struktur[I - 1];
	if (WITH->Strukt) {   /* Leerstrukt = false */
	  if (Erste) {
	    fprintf(Strukdat, "%7d: ", I);
	    Erste = false;
	  } else
	    fprintf(Strukdat, "  |%4d: ", I);
	  Druckeanknuepfung(Wegstrukt(&WITH->UU.Anknuepfung));
	  putc('\n', Strukdat);
	  while (!Leerstrukt(WITH->UU.Anknuepfung)) {
	    fprintf(Strukdat, "         ");
	    Druckeanknuepfung(Wegstrukt(&WITH->UU.Anknuepfung));
	    putc('\n', Strukdat);
	  }
	}
      }

      fprintf(Strukdat, "    ELSE (* nichts *);\n");
      fprintf(Strukdat, "  END; (* CASE *)\n");
    } else
      fprintf(Strukdat, "  (* KEINE STRUKTURANKNUEPFUNGEN VORHANDEN *)\n");
    break;


  case C:
    if (LINK->Strukturvorhanden) {
      fprintf(Strukdat, "  switch (PR) {\n");

      FORLIM = NumProd;
      for (I = 1; I <= FORLIM; I++) {
	WITH = &LINK->Struktur[I - 1];
	if (WITH->Strukt) {   /* Leerstrukt = false */
	  fprintf(Strukdat, "  case %d: ", I);
	  Druckeanknuepfung(Wegstrukt(&WITH->UU.Anknuepfung));
	  if (Leerstrukt(WITH->UU.Anknuepfung))
	    fprintf(Strukdat, " break;\n");
	  else {
	    putc('\n', Strukdat);
	    do {
	      fprintf(Strukdat, "            ");
	      Druckeanknuepfung(Wegstrukt(&WITH->UU.Anknuepfung));
	      putc('\n', Strukdat);
	    } while (!Leerstrukt(WITH->UU.Anknuepfung));
	    fprintf(Strukdat, "            break;\n");
	  }
	}
      }

      fprintf(Strukdat, "  } /* end switch */\n");
    } else
      fprintf(Strukdat, "  /* KEINE STRUKTURANKNUEPFUNGEN VORHANDEN */\n");
    break;


  case ADA:
    if (LINK->Strukturvorhanden) {
      fprintf(Strukdat, "      case PR is\n");

      FORLIM = NumProd;
      for (I = 1; I <= FORLIM; I++) {
	WITH = &LINK->Struktur[I - 1];
	if (WITH->Strukt) {   /* LEERSTRUKT = false */
	  fprintf(Strukdat, "      when%4d => ", I);
	  Druckeanknuepfung(Wegstrukt(&WITH->UU.Anknuepfung));
	  putc('\n', Strukdat);
	  while (!Leerstrukt(WITH->UU.Anknuepfung)) {
	    fprintf(Strukdat, "                  ");
	    Druckeanknuepfung(Wegstrukt(&WITH->UU.Anknuepfung));
	    putc('\n', Strukdat);
	  }
	}
      }

      fprintf(Strukdat, "      when others => null;\n");
      fprintf(Strukdat, "      end case;\n");
    } else
      fprintf(Strukdat,
	      "      null;  -- KEINE STRUKTURANKNUEPFUNGENVORHANDEN\n");
    break;


  }

  if (Strukdat != NULL)
    Strukdat = freopen("Strukdat", "r", Strukdat);
  else
    Strukdat = fopen("Strukdat", "r");
  if (Strukdat == NULL)
    _EscIO(FileNotFound);

  /* Produktion I                                */
}  /* PrintSemanticActions */


Local Void ReadTable(Teil, MaxCard, LINK)
Char Teil;
short *MaxCard;
struct LOC_Optimization *LINK;
{
  /* Die nicht optimierten Zerteilertabellen werden von der Datei */
  /* Tabdat in die Adjazenzliste (AdjacentVector) eingelesn. Teil */
  /* gibt an, ob es sich um den Terminal- oder Nichtterminalteil  */
  /* handelt. MaxCard ist die groesste vorkommende Anzahl von     */
  /* Tabelleneintraegen in einer Zeile der Matrix.                */
  long I;
  short State;
  long FORLIM;
  BaseEntry *WITH;
  AdjacentEntry *WITH1;


  if (Tabdat != NULL)
    Tabdat = freopen("Tabdat", "rb", Tabdat);
  else
    Tabdat = fopen("Tabdat", "rb");
  if (Tabdat == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Tabdat, long);

  *MaxCard = 0;
  LINK->AdjazenzTop = 0;

  /* Eine Code-Reduktion wird nicht durchgefuehrt, daher wird   */
  /* die in der Analyse berechnete Zustandsabbildung ueberlesen.*/
  while (GETFBUF(Tabdat, long) != -5)
    GET(Tabdat, long);
  GET(Tabdat, long);

  FORLIM = ActMaxState;
  for (I = 1; I <= FORLIM; I++) {
    State = GETFBUF(Tabdat, long);
    GET(Tabdat, long);

    WITH = &BaseVector[State - 1];
    if (LINK->AdjazenzTop < MaxAdjacent)
      WITH->StateBase = LINK->AdjazenzTop + 1;
    /* Index des ersten Tabelleneintrags      */
    /* zum Zustand State in der Adjazenzliste */

    switch (Teil) {

    case 'T':
      /* In DEVAR kann es Zustaende geben, fuer die es */
      /* keine relevante Entscheidung gibt. Solche     */
      /* Zustaende haben nur die Aufgabe, Fehler zu    */
      /* erkennen. Deshalb muss hier mit einer 'while'-*/
      /* Schleife anstatt mit einer 'repeat'-Schleife  */
      /* gearbeitet werden.                            */
      while (GETFBUF(Tabdat, long) != -6) {
	if (LINK->AdjazenzTop == MaxAdjacent) {
	  ErrorMessage(4L);
	  longjmp(_JL1, 1);
	} else
	  LINK->AdjazenzTop++;

	WITH1 = &AdjacentVector[LINK->AdjazenzTop - 1];

	WITH1->Symbol = Tab[GETFBUF(Tabdat, long) - 1];
	GET(Tabdat, long);
	/* Die Optimierung muss zur Konstruktion des Kamm- */
	/* vektors mit den Symbolnummern arbeiten.         */
	WITH1->TableEntry = GETFBUF(Tabdat, long);
	GET(Tabdat, long);
      }

      while (GETFBUF(Tabdat, long) != -7)
	GET(Tabdat, long);
      break;

    case 'N':
      while (GETFBUF(Tabdat, long) != -6)
	GET(Tabdat, long);
      GET(Tabdat, long);
      while (GETFBUF(Tabdat, long) != -7) {
	if (LINK->AdjazenzTop == MaxAdjacent) {
	  ErrorMessage(4L);
	  longjmp(_JL1, 1);
	} else
	  LINK->AdjazenzTop++;

	WITH1 = &AdjacentVector[LINK->AdjazenzTop - 1];
	WITH1->Symbol = GETFBUF(Tabdat, long);
	GET(Tabdat, long);
	WITH1->TableEntry = GETFBUF(Tabdat, long);
	GET(Tabdat, long);
      }
      break;
    }

    GET(Tabdat, long);

    WITH->StateCard = LINK->AdjazenzTop - WITH->StateBase + 1;
    /* Anzahl der Tabelleneintraege zum Zustand State */

    if (WITH->StateCard > *MaxCard)
      *MaxCard = WITH->StateCard;

    if (WITH->StateCard > 1)
      SortRow(WITH->StateBase, WITH->StateBase + WITH->StateCard - 1, LINK);
    /* Die Liste der Tabelleneintraege zum Zustand State wird nach */
    /* aufsteigenden Symbolnummern sortiert                        */

  }

}  /* ReadTable */

Local Void ReadTables(LINK)
struct LOC_Optimization *LINK;
{
  /* Die Vektoren LS, LAENGERS, FSYMBOL und RSYMBOL werden von    */
  /* der Datei Tabdat eingelesen und unveraendert auf die Datei   */
  /* Zerdat geschrieben. Ausserdem wird ermittelt ob und zu       */
  /* welchen Produktionen Strukturanknuepfungen vorhanden sind.   */
  short Prod;
  long I, FORLIM;

  if (Tabdat != NULL)
    Tabdat = freopen("Tabdat", "rb", Tabdat);
  else
    Tabdat = fopen("Tabdat", "rb");
  if (Tabdat == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Tabdat, long);

  for (Prod = 0; Prod < Maxprodnr; Prod++)
    LINK->Struktur[Prod].Strukt = false;

  LINK->Strukturvorhanden = false;

  FORLIM = ActMaxProdNr;
  for (I = 1; I <= FORLIM; I++) {
    PUTFBUF(Zerdat, long, LINK->ProdImage[GETFBUF(Tabdat, long) - 1]);

    if (GETFBUF(Zerdat, long) == 0) {   /* Kettenproduktion */
      do {
	GET(Tabdat, long);
      } while (GETFBUF(Tabdat, long) != -1);
    } else {
      Prod = LINK->ProdImage[GETFBUF(Tabdat, long) - 1];
      PUT(Zerdat, long);
      GET(Tabdat, long);
      PUTFBUF(Zerdat, long, GETFBUF(Tabdat, long));
      PUT(Zerdat, long);
      GET(Tabdat, long);   /* LS */
      PUTFBUF(Zerdat, long, GETFBUF(Tabdat, long));
      PUT(Zerdat, long);
      GET(Tabdat, long);   /* LAENGERS */
      if (GETFBUF(Tabdat, long) != -1) {
	LINK->Strukturvorhanden = true;
	LINK->Struktur[Prod - 1].Strukt = true;
	LINK->Struktur[Prod - 1].UU.Anknuepfung = NULL;
	while (GETFBUF(Tabdat, long) != -1) {
	  Zustrukt(&LINK->Struktur[Prod - 1].UU.Anknuepfung,
		   (int)GETFBUF(Tabdat, long));
	  GET(Tabdat, long);
	}
      } else
	LINK->Struktur[Prod - 1].Strukt = false;

    }

    GET(Tabdat, long);
  }

  PUTFBUF(Zerdat, long, -8);
  PUT(Zerdat, long);

  while (GETFBUF(Tabdat, long) != -8)
    GET(Tabdat, long);
  GET(Tabdat, long);

  FORLIM = ActMaxState;
  for (I = 1; I <= FORLIM; I++) {
    PUTFBUF(Zerdat, long, Tab[GETFBUF(Tabdat, long) - 1]);
    PUT(Zerdat, long);
    GET(Tabdat, long);   /* FSYMBOL */
    PUTFBUF(Zerdat, long, Tab[GETFBUF(Tabdat, long) - 1]);
    PUT(Zerdat, long);
    GET(Tabdat, long);   /* RSYMBOL */
  }

  PUTFBUF(Zerdat, long, -9);
  PUT(Zerdat, long);

}  /* ReadTables */


Local long CountEntries()
{
  /* Ermittelt die Anzahl der gueltigen Eintraege in der Adjazenzliste */
  short State;
  long Count;
  short FORLIM;


  Count = 0;

  FORLIM = ActMaxState;
  for (State = 0; State < FORLIM; State++)
    Count += BaseVector[State].StateCard;

  return Count;

}  /* CountEntries */


Local Void RenumberProductions(Teil, LINK)
Char Teil;
struct LOC_Optimization *LINK;
{
  /* Falls die Kettenproduktionen eliminiert wurden, sind die ver-*/
  /* bleibenden Produktionen nicht mehr fortlaufend nummeriert. In*/
  /* RenumberProductions werden die Produktionen neu nummeriert.  */
  /* Zur Abbildung von den alten Produktionsnummern auf die neuen */
  /* Produktionsnummern wird die Abbildung ProdImage aufgebaut.   */
  /* NumProd ist die Anzahl Produktionen ohne Kettenproduktionen. */
  long Teiler, Action, StPro;
  AdjacentRange AC;
  AdjacentRange FORLIM;
  AdjacentEntry *WITH;


  if (Teil == 'T')
    Teiler = 3;
  else
    Teiler = 2;

  FORLIM = LINK->AdjazenzTop;
  for (AC = 0; AC < FORLIM; AC++) {
    WITH = &AdjacentVector[AC];
    StPro = WITH->TableEntry / Teiler;
    Action = WITH->TableEntry % Teiler;

    if (Action != Zlies) {
      if (LINK->ProdImage[StPro - 1] == 0) {
	NumProd++;
	LINK->ProdImage[StPro - 1] = NumProd;
#ifdef MONITOR
	fprintf (prodsfile, "%ld, /* %ld */\n", StPro, NumProd);
#endif
      }
      switch (Action) {

      case Zliesreduziere:
	WITH->TableEntry = LINK->ProdImage[StPro - 1] * Teiler + Zliesreduziere;
	break;

      case Zreduziere:
	WITH->TableEntry = LINK->ProdImage[StPro - 1] * Teiler + Zreduziere;
	break;
      }
    }

  }


}  /* RenumberProductions */


Local Void RenumberTableEntries(Teil, LINK)
Char Teil;
struct LOC_Optimization *LINK;
{
  /* In dieser Prozedur werden die Tabelleneintraege umkodiert.   */
  /* Die urspruengliche Kodierung war wie folgt:                  */
  /* 1. T-Tabelle                                                 */
  /*      case TabEintrag mod 3 of                                */
  /*        0: Aktion = Lies                                      */
  /*           FolgeZustand = TabEintrag div 3                    */
  /*        1: Aktion = LiesReduziere                             */
  /*           ProduktionsNr = TabEintrag div 3                   */
  /*        2: Aktion = Reduziere                                 */
  /*           ProduktionsNr = TabEintrag div 3                   */
  /*      end case                                                */
  /* 2. N-Tabelle                                                 */
  /*      case TabEintrag mod 2 of                                */
  /*        0: Aktion = LiesNt                                    */
  /*           FolgeZustand = TabEintrag div 2                    */
  /*        1: Aktion = LiesNtReduziere                           */
  /*           ProduktionsNr = TabEintrag div 2                   */
  /*      end case                                                */
  /* Die neue Kodierung ist wie folgt:                            */
  /*      if TabEintrag <= ActMaxState then                       */
  /*        Aktion = Lies                                         */
  /*        FolgeZustand = TabEintrag                             */
  /*      elsif TabEintrag <= ActMaxState + NumProd then          */
  /*        Aktion = LiesReduziere                                */
  /*        ProduktionsNr = TabEintrag - ActMaxState              */
  /*      else                                                    */
  /*        Aktion = Reduziere                                    */
  /*        ProduktionsNr = TabEintrag - ActMaxState - NumProd    */
  /*      end if                                                  */
  /* 2. N-Tabelle                                                 */
  /*      if TabEintrag <= ActMaxState then                       */
  /*        Aktion = LiesNt                                       */
  /*        FolgeZustand = TabEintrag                             */
  /*      else                                                    */
  /*        Aktion = LiesNtReduziere                              */
  /*        ProduktionsNr = TabEintrag - ActMaxState              */
  /*      end if                                                  */
  long Teiler;
  AdjacentRange AC;
  AdjacentRange FORLIM;
  AdjacentEntry *WITH;


  if (Teil == 'T')
    Teiler = 3;
  else
    Teiler = 2;

  FORLIM = LINK->AdjazenzTop;
  for (AC = 0; AC < FORLIM; AC++) {
    WITH = &AdjacentVector[AC];
    switch (WITH->TableEntry % Teiler) {

    case Zlies:
      WITH->TableEntry /= Teiler;
      break;

    case Zliesreduziere:
      WITH->TableEntry = WITH->TableEntry / Teiler + ActMaxState;
      break;

    case Zreduziere:
      WITH->TableEntry = WITH->TableEntry / Teiler + ActMaxState + NumProd;
      break;
    }
  }

}  /* RenumberTableEntries */

/* Local variables for CompressTable: */
struct LOC_CompressTable {
  struct LOC_Optimization *LINK;
  short *Base;
  CombRange *MaxBase;
  long *MaxNext;
  /* konstruiert => Beruecksichtigung der "first  */
  /* fit decreasing" Heuristik.                   */

  long TrieTop;
  TrieRange Root;   /* Wurzel des Tries */
  boolean NotUsed[MaxComb + 1];
  /* Gibt an welche Felder des Kammvektors noch unbelegt sind */
  short DistVec[Maxsymnr + 1];
} ;

/* Hilfsvektor zum Aufbau des Tries */


Local TrieRange DistTrieElem(D, S, N, LINK)
short D;
TrieRange S, N;
struct LOC_CompressTable *LINK;
{
  /* Liefert einen neuen Trieknoten mit EndMarker = false und weist */
  /* D, S und N an das Next, Son und Distance Feld des Trieknotens  */
  /* zu.                                                            */
  TrieNode *WITH;

  if (LINK->TrieTop == MaxTrie) {
    ErrorMessage(3L);
    longjmp(_JL1, 1);
  } else
    LINK->TrieTop++;

  WITH = &Trie[LINK->TrieTop - 1];

  WITH->EndMarker = false;
  WITH->Next = N;
  WITH->UU.U0.Son = S;
  WITH->UU.U0.Distance = D;
  return LINK->TrieTop;

}  /* DistTrieElem */


Local TrieRange EndTrieElem(S, C, N, LINK)
short S;
short C;
TrieRange N;
struct LOC_CompressTable *LINK;
{
  /* Liefert einen neuen Trieknoten mit EndMarker = true und weist S, */
  /* C und N an das State, StartCol und Next Feld des Trieknotens zu. */
  TrieNode *WITH;

  if (LINK->TrieTop == MaxTrie) {
    ErrorMessage(3L);
    longjmp(_JL1, 1);
  } else
    LINK->TrieTop++;

  WITH = &Trie[LINK->TrieTop - 1];

  WITH->EndMarker = true;
  WITH->Next = N;
  WITH->UU.U1.State = S;
  WITH->UU.U1.StartCol = C;
  return LINK->TrieTop;

}  /* EndTrieElem */


Local Void InitTrie(LINK)
struct LOC_CompressTable *LINK;
{
  /* Initialisieren des Tries */
  LINK->TrieTop = 0;
  LINK->Root = DistTrieElem(NoDist, TNil, TNil, LINK);
}  /* InitTrie */


Local Void InsertIntoTrie(State, StartCol, LINK)
short State;
short StartCol;
struct LOC_CompressTable *LINK;
{
  /* Einfuegen einer Zeile der Matrix in den Trie.                */
  /* Zur Zeile State wurden die Distanzen zwischen den "aktiven"  */
  /* Tabelleneintraegen berechnet und im Vektor DistVec abgelegt. */
  /* NoDist folgt auf die letzte gueltige Distanz. StartCol ist   */
  /* die Spalte des ersten Tabelleneintrags der Zeile State.      */
  /* Die jeweils naechste Distanz der Zeile wird auf der gerade   */
  /* aktuellen Stufe des Tries (entlang der Next-Zeiger) einge-   */
  /* tragen (sortiert nach aufsteigenden Distanzen). Danach wird  */
  /* im Trie eine Stufe herabgestiegen (entlang der Son-Zeiger)   */
  /* und mit der naechsten Distanz analog verfahren. Sind alle    */
  /* Distanzen eingetragen, wird auf dem dann erreichten Niveau   */
  /* des Tries die Markierung fuer die Zeile State eingetragen    */
  /* (am Ende der durch die Next-Zeiger verketteten Liste von     */
  /* Trie-Knoten).                                                */
  TrieRange Cur, Last;
  short DIndex;
  short Dist;
  boolean NotFound;
  TrieNode *WITH;


  Cur = Trie[LINK->Root - 1].UU.U0.Son;
  Last = LINK->Root;
  DIndex = 0;

  while (LINK->DistVec[DIndex] != NoDist) {
    Dist = LINK->DistVec[DIndex];   /* naechste Distanz */

    if (Cur == TNil) {   /* neue Stufe im Trie */
      WITH = &Trie[Last - 1];
      WITH->UU.U0.Son = DistTrieElem(Dist, TNil, TNil, LINK);
      Cur = WITH->UU.U0.Son;

    } else if (Trie[Cur - 1].EndMarker) {
      WITH = &Trie[Last - 1];
      WITH->UU.U0.Son = DistTrieElem(Dist, TNil, WITH->UU.U0.Son, LINK);
      Cur = WITH->UU.U0.Son;

    } else if (Trie[Cur - 1].UU.U0.Distance > Dist) {
      WITH = &Trie[Last - 1];
      WITH->UU.U0.Son = DistTrieElem(Dist, TNil, WITH->UU.U0.Son, LINK);
      Cur = WITH->UU.U0.Son;

    } else if (Trie[Cur - 1].UU.U0.Distance != Dist) {
      NotFound = true;

      while (NotFound) {
	Last = Cur;
	Cur = Trie[Cur - 1].Next;

	if (Cur == TNil) {
	  WITH = &Trie[Last - 1];
	  WITH->Next = DistTrieElem(Dist, TNil, WITH->Next, LINK);
	  Cur = WITH->Next;
	  NotFound = false;

	  continue;
	}

	if (Trie[Cur - 1].EndMarker) {
	  WITH = &Trie[Last - 1];
	  WITH->Next = DistTrieElem(Dist, TNil, WITH->Next, LINK);
	  Cur = WITH->Next;
	  NotFound = false;

	  continue;
	}
	if (Trie[Cur - 1].UU.U0.Distance < Dist)
	  continue;
	if (Trie[Cur - 1].UU.U0.Distance > Dist) {
	  WITH = &Trie[Last - 1];
	  WITH->Next = DistTrieElem(Dist, TNil, WITH->Next, LINK);
	  Cur = WITH->Next;
	}
	NotFound = false;
      }

    }

    Last = Cur;
    Cur = Trie[Cur - 1].UU.U0.Son;   /* naechste Stufe im Trie */
    DIndex++;

  }
  /* Die Distanzen der Zeile State werden in den Trie eingetragen */
  /* => Trie-Knoten mit EndMarker = false                         */


  /* Die Markierung fuer die Zeile State wird in den Trie ein-  */
  /* getragen (am Ende der durch die Next-Zeiger verketteten    */
  /* Liste von Trie-Knoten).                                    */
  /* => Trie-Knoten mit EndMarker = true                        */
  if (Cur == TNil) {
    Trie[Last - 1].UU.U0.Son = EndTrieElem(State, StartCol, TNil, LINK);
    return;
  }

  do {
    Last = Cur;
    Cur = Trie[Cur - 1].Next;
  } while (Cur != TNil);
  Trie[Last - 1].Next = EndTrieElem(State, StartCol, TNil, LINK);

  /* letzte Stufe im Trie */
  /* Suchen der richtigen Position (aufsteigend sortiert) zum */
  /* Eintragen der Distanz Dist.                              */

}  /* InsertIntoTrie */


Local short OccupyNext(Start, CIndex, Cur, Del, LINK)
CombRange Start, CIndex;
TrieRange Cur;
boolean *Del;
struct LOC_CompressTable *LINK;
{
  /* Es wird versucht Felder des Kammvektors, beginnend mit dem   */
  /* Feld Start, zu belegen. Es wird vorausgesetzt, dass Kamm-    */
  /* vektor [CIndex] unbenutzt ist. OccupyNext liefert im Erfolgs-*/
  /* fall die Zeilennummer der eingetragenen Zeile, NoState sonst.*/
  /* Del zeigt an ob der Son-Knoten im Erfolgsfall geloescht      */
  /* werden muss.                                                 */
  short CurState;
  TrieRange Prev;
  TrieNode CurNode;
  long NextCIndex, CMax;
  BaseEntry *WITH;


  Prev = TNil;
  CurState = NoState;

  while (Cur != TNil && CurState == NoState) {
    CurNode = Trie[Cur - 1];


    if (CurNode.EndMarker) {
      if (Start >= CurNode.UU.U1.StartCol) {   /* passt! */
	CurState = CurNode.UU.U1.State;
	LINK->Base[CurNode.UU.U1.State] = Start - CurNode.UU.U1.StartCol;
	if (LINK->Base[CurNode.UU.U1.State] > *LINK->MaxBase)
	  *LINK->MaxBase = LINK->Base[CurNode.UU.U1.State];
	WITH = &BaseVector[CurNode.UU.U1.State - 1];
	CMax = LINK->Base[CurNode.UU.U1.State] +
	       AdjacentVector[WITH->StateBase + WITH->StateCard - 2].Symbol;
	if (CMax > *LINK->MaxNext)
	  *LINK->MaxNext = CMax;

	if (CurNode.Next != TNil) {
	      /* CurNode ist nicht der letzte Knoten */
		Trie[Cur - 1] = Trie[CurNode.Next - 1];
	  *Del = false;
	} else if (Prev != TNil) {
	  /* erste Knoten            */
	  Trie[Prev - 1].Next = TNil;
	  *Del = false;
	} else
	  *Del = true;


      }


    } else {
      NextCIndex = CIndex + CurNode.UU.U0.Distance;

      if (NextCIndex >= MaxComb) {
	ErrorMessage(2L);
	longjmp(_JL1, 1);
      }

      if (LINK->NotUsed[NextCIndex]) {
	CurState = OccupyNext(Start, (int)NextCIndex, CurNode.UU.U0.Son, Del,
			      LINK);

	if (CurState != NoState) {
	  LINK->NotUsed[NextCIndex] = false;   /* Feld des Kammvektors */
	  /* belegt setzen        */
	  if (*Del) {
	    Trie[Cur - 1].UU.U0.Son = TNil;   /* Son-Knoten loeschen */

	    if (Trie[Cur - 1].Next != TNil) {   /* CurNode ist nicht */
	      /* der letzte Knoten */
	      Trie[Cur - 1] = Trie[CurNode.Next - 1];
	      *Del = false;
	    } else if (Prev != TNil) {
	      Trie[Prev - 1].Next = TNil;
	      *Del = false;
	    }

	  }
	}
      }

    }  /* else */


    if (CurState != NoState)   /* passt nicht, andere Distanz */
      break;

    /* with */

    /* versuchen                   */
    Prev = Cur;
    Cur = CurNode.Next;
  }  /* while */


  return CurState;


  /* CurNode ist nicht der   */


  /* CurNode ist nicht der */
  /* erste Knoten          */
}  /* OccupyNext */


Local Void ProcessTrie(LINK)
struct LOC_CompressTable *LINK;
{
  /* Die im Trie enthaltenen Zeilen der Matrix werden in den Kammvektor */
  /* eingetragen.                                                       */
  long CIndex;
  short State;
  boolean Del;


  CIndex = -1;
  Del = false;

  if (Trie[LINK->Root - 1].UU.U0.Son == TNil)
    return;

  do {

    do {
      CIndex++;
    } while (!LINK->NotUsed[CIndex]);

    if (CIndex == MaxComb) {
      ErrorMessage(2L);
      longjmp(_JL1, 1);
    }

    State = OccupyNext((int)CIndex, (int)CIndex,
		       Trie[LINK->Root - 1].UU.U0.Son, &Del, LINK);

    if (State != NoState)
      LINK->NotUsed[CIndex] = false;

  } while (!Del);
}  /* ProcessTrie */

Local Void CalcDist(State, LINK)
short State;
struct LOC_CompressTable *LINK;
{
  /* Zur Zeile State werden die Distanzen zwischen den "aktiven"  */
  /* Tabellen eintraegen berechnet und im Vektor DistVec abgelegt.*/
  /* NoDist wird nach der letzten gueltigen Distanz eingetragen.  */
  short I;
  AdjacentRange AC;
  BaseEntry *WITH;
  AdjacentRange FORLIM;


  I = 0;

  WITH = &BaseVector[State - 1];

  FORLIM = WITH->StateBase + WITH->StateCard;
  for (AC = WITH->StateBase + 1; AC < FORLIM; AC++) {
    LINK->DistVec[I] = AdjacentVector[AC - 1].Symbol - AdjacentVector[AC - 2].Symbol;
    I++;
  }
  LINK->DistVec[I] = NoDist;

}  /* CalcDist */


Local Void CompressTable(Base_, MaxBase_, MaxNext_, MaxCard, MaxState, LINK)
short *Base_;
CombRange *MaxBase_;
long *MaxNext_;
short MaxCard;
short MaxState;
struct LOC_Optimization *LINK;
{
  /* Konstruktion eines Kammvektors aus einer duenn besetzten     */
  /* Matrix mit Hilfe eines Tries und Beruecksichtigung der       */
  /* "first fit decreasing" Heuristik.                            */
  /* Der Base-Vektor enthaelt zu jeder Zeile der Matrix den Index */
  /* ihrer ersten Spalte im Kammvektor, MaxBase ist der groesste  */
  /* dieser Indices. MaxNext ist der Index des letzten Eintrags   */
  /* im Kammvektor. MaxState ist die Anzahl der Zustaende mit     */
  /* mindestens einem Tabelleneintrag. MaxCard ist die groesste   */
  /* vorkommende Anzahl von Tabelleneintraegen in einer Zeile der */
  /* Matrix.                                                      */
  struct LOC_CompressTable V;
  long I;
  short St, State;
  short MinCard;
  long FORLIM;



  V.LINK = LINK;
  V.Base = Base_;
  V.MaxBase = MaxBase_;
  V.MaxNext = MaxNext_;
  FORLIM = ActMaxState;
  /* Initialisierung */
  for (I = 1; I <= FORLIM; I++)
    V.Base[I] = 0;
  for (I = 0; I <= MaxComb; I++)
    V.NotUsed[I] = true;
  *V.MaxBase = 0;
  *V.MaxNext = 0;

  /* Kombination der "first fit decreasing" Heuristik, welche   */
  /* einen relativ kleinen Kammvektor liefert, mit der schnellen*/
  /* Konstruktion des Kammvektors durch eine Trie.              */
  St = 1;
  State = LINK->StateImage[St];
  for (I = NumInterval - 1; I >= 0; I--) {
    MinCard = MaxCard / NumInterval * I + 1;
    InitTrie(&V);
    while (St <= MaxState && BaseVector[State - 1].StateCard >= MinCard) {
      CalcDist(State, &V);
      InsertIntoTrie(State,
	AdjacentVector[BaseVector[State - 1].StateBase - 1].Symbol, &V);
      St++;
      State = LINK->StateImage[St];
    }
    ProcessTrie(&V);
  }

}  /* CompressTable */

#undef NumInterval

/* Local variables for ProcessNonTerminalPart: */
struct LOC_ProcessNonTerminalPart {
  struct LOC_Optimization *LINK;
  short NtMaxState;
  StStType SuperState;
  BaseType NtBase;
} ;

Local Void PrintNonTerminalPart(LINK)
struct LOC_ProcessNonTerminalPart *LINK;
{
  /* Ausgabe der Vektoren NTBASE und NTNEXT, sowie der Mengen     */
  /* BRACKET und SKIP auf die Datei Zerdat.                       */
  long I, J, FORLIM;
  BaseEntry *WITH;
  long FORLIM1;
  AdjacentEntry *WITH1;


  FORLIM = MaxTerminalCode;
  for (I = 0; I <= FORLIM; I++) {
    if (Insymbol(BRACKET, (int)I))
      PUTFBUF(Zerdat, long, 1);
    else
      PUTFBUF(Zerdat, long, 0);
    PUT(Zerdat, long);   /* BRACKET-Element */

    if (Insymbol(SKIP, (int)I))
      PUTFBUF(Zerdat, long, 1);
    else
      PUTFBUF(Zerdat, long, 0);
    PUT(Zerdat, long);   /* SKIP-Element */
  }
  PUTFBUF(Zerdat, long, -1);
  PUT(Zerdat, long);

  FORLIM = ActMaxState;
  for (I = 1; I <= FORLIM; I++) {
    PUTFBUF(Zerdat, long, LINK->NtBase[LINK->SuperState[I]]);
    PUT(Zerdat, long);   /* NTBASE */
    WITH = &BaseVector[I - 1];
    if (WITH->StateCard > 0) {
      FORLIM1 = WITH->StateBase + WITH->StateCard - 2;
      for (J = WITH->StateBase - 1; J <= FORLIM1; J++) {
	WITH1 = &AdjacentVector[J];
	PUTFBUF(Zerdat, long, LINK->NtBase[I] + WITH1->Symbol);
	PUT(Zerdat, long);
	PUTFBUF(Zerdat, long, WITH1->TableEntry);
	PUT(Zerdat, long);   /* NTNEXT */
      }
    }
    PUTFBUF(Zerdat, long, -2);
    PUT(Zerdat, long);
  }
  PUTFBUF(Zerdat, long, -3);
  PUT(Zerdat, long);

}  /* PrintNonTerminalPart */


Local Void NtLineElimination(LINK)
struct LOC_ProcessNonTerminalPart *LINK;
{

  /* Da in der Nichtterminalmatrix nur auf signifikante Eintraege */
  /* zugegriffen wird, muessen Zeilen der Nichtterminalmatrix die */
  /* vollkommen in anderen Zeilen enthalten sind d.h.             */
  /* falls Zeile1[Spalte] <> 0 => Zeile1[Spalte] = Zeile2[Spalte] */
  /* nicht in den Kammvektor eingetragen werden. Es genuegt ihren */
  /* Basiszeiger in den Kammvektor auf den Wert des Basiszeigers  */
  /* der Zeile zu setzen, in der sie enthalten sind.              */
  /* Falls nach NtLineElimination SuperState [State] <> State gilt*/
  /* , so ist die Zeile State vollstaendig in SuperState [State]  */
  /* enthalten.                                                   */
  /* Sprungziel zur Simulation einer exit-Anweisung */

  boolean NotEliminated[Maxzustand + 1];
  TableRange NtRow[Maxsymnr + 1];
  short N;
  short S1, S2, State, State1, State2;
  AdjacentRange AC, AL;
  short FORLIM;
  BaseEntry *WITH;
  AdjacentRange FORLIM1;
  AdjacentEntry *WITH1;


  FORLIM = ActMaxNTerm;
  /* Initialisierung */
  for (N = 1; N <= FORLIM; N++)
    NtRow[N] = 0;
  FORLIM = ActMaxState;
  for (State = 1; State <= FORLIM; State++) {
    NotEliminated[State] = true;
    LINK->SuperState[State] = State;
  }

  FORLIM = LINK->NtMaxState;
  for (S1 = 1; S1 < FORLIM; S1++) {
    State1 = LINK->LINK->StateImage[S1];

    if (NotEliminated[State1]) {
      WITH = &BaseVector[State1 - 1];

      FORLIM1 = WITH->StateBase + WITH->StateCard - 2;
      /* Zeile State1 zum schnelleren Zeilenvergleich expandieren */
      for (AC = WITH->StateBase - 1; AC <= FORLIM1; AC++) {
	WITH1 = &AdjacentVector[AC];
	NtRow[WITH1->Symbol] = WITH1->TableEntry;
      }
      FORLIM1 = LINK->NtMaxState;
      for (S2 = S1 + 1; S2 <= FORLIM1; S2++) {
	State2 = LINK->LINK->StateImage[S2];

	if (NotEliminated[State2]) {
	  WITH = &BaseVector[State2 - 1];

	  AC = WITH->StateBase;
	  /* erstes Symbol im AdjacentVector */
	  AL = WITH->StateBase + WITH->StateCard - 1;
	  /* letztes Symbol im AdjacentVector */
	  while (true) {   /* loop */
	    WITH1 = &AdjacentVector[AC - 1];   /* exit */

	    if (WITH1->TableEntry != NtRow[WITH1->Symbol])
	      goto _L1;
	    if (AC == AL)   /* Zeile State2 ist voellig in */
	    {  /* Zeile State1 enthalten.     */
	      LINK->SuperState[State2] = State1;
	      NotEliminated[State2] = false;
	      BaseVector[State2 - 1].StateCard = 0;
	      goto _L1;   /* exit */
	    }

	    AC++;

	  }

_L1: ;   /* end loop */

	}  /* if */


      }  /* for S2 */


      WITH = &BaseVector[State1 - 1];

      FORLIM1 = WITH->StateBase + WITH->StateCard;
      /* expandierte Zeile loeschen */
      for (AC = WITH->StateBase; AC < FORLIM1; AC++)
	NtRow[AdjacentVector[AL - 1].Symbol] = 0;
    }  /* if */


  }  /* for S1 */


}  /* NtLineElimination */


Local Void ProcessNonTerminalPart(LINK)
struct LOC_Optimization *LINK;
{
  /* Bearbeiten des Nichtterminalteils der Zerteilertabellen */
  struct LOC_ProcessNonTerminalPart V;
  short NtMaxCard;
  CombRange NtMaxBase;



  V.LINK = LINK;
  ReadTable('N', &NtMaxCard, LINK);

  LINK->NtEntryCount1 = LINK->AdjazenzTop;

  RenumberProductions('N', LINK);

  LINK->NtMaxEntry = ActMaxState + NumProd;

  RenumberTableEntries('N', LINK);

  SortStates(&V.NtMaxState, NtMaxCard, LINK);

  NtLineElimination(&V);

  LINK->NtEntryCount2 = CountEntries();

  SortStates(&V.NtMaxState, NtMaxCard, LINK);

  CompressTable(V.NtBase, &NtMaxBase, &LINK->NtMaxNext, NtMaxCard,
		V.NtMaxState, LINK);

  PrintNonTerminalPart(&V);

}  /* ProcessNonTerminalPart */

/* Local variables for ProcessTerminalPart: */
struct LOC_ProcessTerminalPart {
  struct LOC_Optimization *LINK;
  short TMaxState;
  StStType DefaultState;
  short DefaultCard[Maxzustand + 1];
  BaseType TBase;
} ;


Local Void ComputeDefaults(LINK)
struct LOC_ProcessTerminalPart *LINK;
{
  /* Berechnung von Ersatzzustaenden. Ein Zustand State2 (Zeile2) */
  /* ist ein moeglicher Ersatzzustand fuer State1 (Zeile1), falls */
  /* gilt aus Zeile2 [Spalte] = 0 folgt Zeile1[Spalte] = 0. Der   */
  /* beste Ersatzzustand fuer einen Zustand ist der, fuer den die */
  /* meisten Eintrage <> 0 uebereinstimmen. Der beste Ersatzzu-   */
  /* stand zum Zustand State wird in DefaultState [State] abgelegt*/
  /* und die Anzahl der uebereinstimmenden Eintraege in Default-  */
  /* Card [State]. Existiert kein Ersatzzustand mit mindestens    */
  /* einem uebereinstimmenden Eintrag, so wird DefaultState       */
  /* [State] auf NoState und DefaultCard [State] auf 0 gesetzt.   */
  /* Sprungziel zur Simulation einer exit-Anweisung */

  TableRange TRow[Maxsymnr + 1];
  short Symbol;
  short S1, S2, State1, State2, DefState;
  short DefCard;
  long MaxPosCard;
  AdjacentRange AC, AL;
  short FORLIM;
  BaseEntry *WITH;
  AdjacentRange FORLIM1;
  AdjacentEntry *WITH1;

  FORLIM = MaxTerminalCode;
  /* Initialisierung */
  for (Symbol = 0; Symbol <= FORLIM; Symbol++)
    TRow[Symbol] = 0;
  FORLIM = ActMaxState;
  for (State1 = 1; State1 <= FORLIM; State1++) {
    LINK->DefaultState[State1] = NoState;
    LINK->DefaultCard[State1] = 0;
  }

  FORLIM = LINK->TMaxState;
  for (S1 = 1; S1 < FORLIM; S1++) {
    State1 = LINK->LINK->StateImage[S1];

    WITH = &BaseVector[State1 - 1];

    FORLIM1 = WITH->StateBase + WITH->StateCard - 2;
    /* Zeile State1 zum schnelleren Zeilenvergleich expandieren */
    for (AC = WITH->StateBase - 1; AC <= FORLIM1; AC++) {
      WITH1 = &AdjacentVector[AC];
      TRow[WITH1->Symbol] = WITH1->TableEntry;
    }
    DefState = NoState;   /* bisher bester Ersatzzustand fuer State1 */
    DefCard = 0;   /* Anzahl der uebereinstimmenden Eintraege */
    S2 = S1;

    do {

      S2++;
      State2 = LINK->LINK->StateImage[S2];

      WITH = &BaseVector[State2 - 1];

      MaxPosCard = WITH->StateCard;
      /* Maximal moegliche Zahl von uebereinstimmenden Eintraegen */
      /* (<> 0) von State1 und State2                             */
      AC = WITH->StateBase;
      /* erstes Symbol im AdjacentVector */
      AL = WITH->StateBase + WITH->StateCard - 1;
      /* letztes Symbol im AdjacentVector */
      while (true) {   /* loop */
	Symbol = AdjacentVector[AC - 1].Symbol;

	if (TRow[Symbol] == 0) {
	  goto _L1;   /* exit */
	  /* State2 kann kein Ersatzzustand fuer State1 sein */
	}
	/* Die maximal moegliche Zahl von uebereinstimmenden Ein- */
	/* traegen (<> 0) von State1 und State2 muss erniedrigt   */
	/* werden                                                 */

	if (TRow[Symbol] != AdjacentVector[AC - 1].TableEntry)
	  MaxPosCard--;
	if (MaxPosCard < DefCard) {
	  goto _L1;   /* exit */
	  /* State2 kann kein besserer Ersatzzutand sein als DefState */
	}

	if (AC == AL) {
	  /* State2 ist ein moeglicher Ersatzzustand fuer State1 und */
	  /* die Anzahl der uebereinstimmenden Eintraege (<> 0) ist  */
	  /* groesser als beim besten bisher bekannten Ersatzzustand */
	  /* DefState                                                */
	  DefState = State2;
	  DefCard = MaxPosCard;
	  goto _L1;   /* exit */
	}
	AC++;

      }

_L1: ;   /* end loop */

    } while (BaseVector[State2 - 1].StateCard >= DefCard &&
	     S2 != LINK->TMaxState);
    /* Abbruch falls alle moeglichen Zustaende betrachtet oder falls */
    /* kein besserer Ersatzzustand mehr gefunden werden kann         */

    if (DefCard > 0) {
      /* Bester Ersatzzustand fuer State1 */
      LINK->DefaultState[State1] = DefState;
      LINK->DefaultCard[State1] = DefCard;
    }

    WITH = &BaseVector[State1 - 1];

    FORLIM1 = WITH->StateBase + WITH->StateCard - 2;
    /* expandierte Zeile loeschen */
    for (AC = WITH->StateBase - 1; AC <= FORLIM1; AC++)
      TRow[AdjacentVector[AC].Symbol] = 0;
  }

}  /* ComputeDefaults */

/* Local variables for OneDefault: */
struct LOC_OneDefault {
  struct LOC_ProcessTerminalPart *LINK;
  /* Zur Vereinfachung der Rechnung wird in OneDefault im 2.  */
  /* Schritt nicht mit den Zustaenden selbst, sondern mit     */
  /* Indices aus dem Bereich ChainRange gerechnet. StateArray */
  /* bildet die Indices auf die Zustaende ab (jeweils fuer    */
  /* eine Kette).                                             */
  short DefArray[MaxChain], TryDefArray[MaxChain];
  short DefCardArray[MaxChain][MaxChain];
  boolean Marked[MaxChain];
  /* DefArray, TryDefArray, DefCardArray und Marked sind      */
  /* Hifsfelder zur Neuberechnung der Ersatzzustaende         */
  long MaxDefCard, ActChainLength;
} ;

Local Void Try(St, TryDefCard, LINK)
char St;
long TryDefCard;
struct LOC_OneDefault *LINK;
{
  /* Probieren von neuen Ersatzzustaenden. Marked [St] = true be- */
  /* sagt :                                                       */
  /* St wird bereits als Ersatzzustand benutzt. MaxDefCard ist die*/
  /* Anzahl von Eintraegen, die durch die beste bisher gefundene  */
  /* Loesung eingespart wird. TryeDefCard ist die Anzahl von Ein- */
  /* traegen, die durch die bisher aufgebaute Teilloesung einge-  */
  /* spart wird.                                                  */
  char ASt, FORLIM;

  while (LINK->Marked[St - 1] && St < LINK->ActChainLength)
    St++;
  /* Suchen eines Zustands, fuer den noch ein Ersatzzustand     */
  /* bestimmt werden muss                                       */
  if (St == LINK->ActChainLength) {   /* Loesung */
    if (TryDefCard > LINK->MaxDefCard) {
      /* Diese Loesung ist besser als die beste bisher gefundene */
      LINK->MaxDefCard = TryDefCard;
      memcpy(LINK->DefArray, LINK->TryDefArray, MaxChain * sizeof(short));
    }
    return;
  }
  FORLIM = LINK->ActChainLength;
  for (ASt = St; ASt < FORLIM; ASt++) {
    /* Moegliche Ersatzzustaende fuer St probieren */
    LINK->TryDefArray[St - 1] = ASt + 1;
    /*    case Marked [ASt] of */
    switch (LINK->Marked[ASt]) {

    case true:
      Try(St + 1, TryDefCard + LINK->DefCardArray[St - 1][ASt], LINK);
      break;

    case false:
      LINK->Marked[ASt] = true;
      Try(St + 1, TryDefCard + LINK->DefCardArray[St - 1][ASt], LINK);
      LINK->Marked[ASt] = false;
      break;
    }
    LINK->TryDefArray[St - 1] = NoState;
  }  /* for */
}  /* Try */

Local long DefCard(State1, State2)
short State1, State2;
{
  /* State2 ist ein moeglicher Ersatzzustand fuer State1. DefCard */
  /* ermittelt wieviele Eintraege (<> 0) von State1 und State2    */
  /* uebereinstimmen.                                             */
  short StcCard;
  AdjacentRange AC1, AC2;
  BaseEntry *WITH;
  AdjacentRange FORLIM;
  AdjacentEntry *WITH1;

  StcCard = 0;
  AC1 = BaseVector[State1 - 1].StateBase;
  WITH = &BaseVector[State2 - 1];
  FORLIM = WITH->StateBase + WITH->StateCard - 2;
  for (AC2 = WITH->StateBase - 1; AC2 <= FORLIM; AC2++) {
    WITH1 = &AdjacentVector[AC2];
    while (AdjacentVector[AC1 - 1].Symbol != WITH1->Symbol)
      AC1++;
    if (AdjacentVector[AC1 - 1].TableEntry == WITH1->TableEntry)
      StcCard++;
    AC1++;
  }
  return StcCard;
}  /* DefCard */


Local Void OneDefault(LINK)
struct LOC_ProcessTerminalPart *LINK;
{
  /* Die Berechnung der besten Ersatzzustaende kann moeglicher-   */
  /* weise lange Ketten ergeben d.h. DefaultState [State1] =      */
  /* State2, DefaultState [State2] = State3, u.s.f. Die Zerteiler-*/
  /* tabellen werden dadurch zwar klein, aber beim Tabellenzugriff*/
  /* muss diese Kette immer wieder einmal abgelaufen werden. Dies */
  /* fuehrt zu erhoeten Zerteilungszeiten. Um die Einsparung von  */
  /* Tabelleneintraegen durch Ersatzzustaende mit einem schnellen */
  /* Zugriff zu den Zerteilertabellen zu verbinden, werden in     */
  /* dieser Prozedur, ausgehend von den besten Ersatzzustaenden,  */
  /* die Ersatzzustaende so abgeaendert, dass nur Ketten der      */
  /* Laenge Eins vorkommen. Dies wird durch die beiden folgenden  */
  /* Schritte erreicht.                                           */
  /* 1. Der Ersatzzustand aller Zustaende, die selbst von mehr als*/
  /*    einem Zustand als Ersatzzustand benutzt werden, wird auf  */
  /*    NoState gesetzt                                           */
  /* 2. Jetzt ist jeder Zustand entweder der letzte Zustand einer */
  /*    Kette von Ersatzzustaenden oder er kommt nur noch in      */
  /*    maximal einer solchen Kette vor. Im naechsten Schritt wird*/
  /*    jede dieser Ketten betrachtet. Es werden lokal fuer jede  */
  /*    Kette (d.h. nur unter Beruecksichtigung der Zustaende der */
  /*    Kette) neue Ersatzzustaende berechnet, so dass nur noch   */
  /*    Ketten der Laenge Eins auftreten. Die Auswahl der neuen   */
  /*    Ersatzzustaende geschieht durch Probieren aller Moeglich- */
  /*    keiten.                                                   */
  /* Es sei noch angemerkt, dass fuer jeden Zustand in einer Kette*/
  /* gilt: alle Zustaende, die nach diesem Zustand in der Kette   */
  /* enthalten sind, sind fuer ihn Ersatzzustaende.               */
  struct LOC_OneDefault V;
  short State, St;
  long InCount[Maxzustand + 1];
  /* InCount[State] gibt an von wievielen Zustaenden der      */
  /* Zustand State als Ersatzzustand benutzt wird             */
  short StateArray[MaxChain];
  char i, j;
  short FORLIM;
  char FORLIM1, FORLIM2;



  V.LINK = LINK;
  FORLIM = ActMaxState;
  /* Initialisierung */
  for (State = 1; State <= FORLIM; State++)
    InCount[State] = 0;

  FORLIM = ActMaxState;
  /* Schritt 1 */
  for (State = 1; State <= FORLIM; State++) {
    if (LINK->DefaultState[State] != NoState)
      InCount[LINK->DefaultState[State]]++;
  }

  FORLIM = LINK->TMaxState;
  for (St = 1; St <= FORLIM; St++) {
    State = LINK->LINK->StateImage[St];
    if (InCount[State] > 1 && LINK->DefaultState[State] != NoState) {
      InCount[LINK->DefaultState[State]]--;
      LINK->DefaultState[State] = NoState;
      LINK->DefaultCard[State] = 0;
    }
  }

  FORLIM = LINK->TMaxState;
  /* Schritt 2 */
  for (St = 1; St <= FORLIM; St++) {
    State = LINK->LINK->StateImage[St];

    if (InCount[State] == 0) {   /* erster Zustand einer Kette */
      /* alle Zustaende die zu dieser Kette gehoeren bestimmen */
      V.ActChainLength = 0;
      do {
	if (V.ActChainLength == MaxChain) {
	  /* Die Kette ist zu lang => Kette unterbrechen */
	  InCount[LINK->DefaultState[State]]--;
	  LINK->DefaultState[State] = NoState;
	  LINK->DefaultCard[State] = 0;
	} else {
	  V.ActChainLength++;
	  StateArray[V.ActChainLength - 1] = State;
	}
	State = LINK->DefaultState[State];
      } while (State != NoState);

      if (V.ActChainLength > 2) {
	FORLIM1 = V.ActChainLength;
	for (i = 1; i < FORLIM1; i++) {
	  /* Anzahl der uebereinstimmenden Eintraege (<> 0) bestimmen */
	  V.DefCardArray[i - 1][i] = LINK->DefaultCard[StateArray[i - 1]];
	  if (i + 2 <= V.ActChainLength) {
	    FORLIM2 = V.ActChainLength;
	    for (j = i + 1; j < FORLIM2; j++)
	      V.DefCardArray[i - 1]
		[j] = DefCard(StateArray[i - 1], StateArray[j]);
	  }
	}

	FORLIM1 = V.ActChainLength;
	/* Initialisierung */
	for (i = 0; i < FORLIM1; i++) {
	  V.TryDefArray[i] = NoState;
	  V.DefArray[i] = NoState;
	  V.Marked[i] = false;
	}
	V.MaxDefCard = 0;

	/* neue Ersatzzustaende bestimmen */
	Try(1, 0L, &V);

	FORLIM1 = V.ActChainLength - 2;
	for (i = 0; i <= FORLIM1; i++) {
	  /* neue Ersatzzustaende und neue Anzahl eingesparter    */
	  /* Eintraege in DefaultState und DefaultCard eintragen. */
	  if (V.DefArray[i] != NoState) {
	    LINK->DefaultState[StateArray[i]] = StateArray[V.DefArray[i] - 1];
	    LINK->DefaultCard[StateArray[i]] = V.DefCardArray[i]
	      [V.DefArray[i] - 1];
	  } else {
	    LINK->DefaultState[StateArray[i]] = NoState;
	    LINK->DefaultCard[StateArray[i]] = 0;
	  }
	}

      }  /* if ActChainLength > 2 */
      /* Die Laenge der Kette ist groesser als Eins */


    }  /* InCount [State] = 0 */


  }  /* for */


}  /* OneDefault */

#undef MaxChain

Local Void Adjust(LINK)
struct LOC_ProcessTerminalPart *LINK;
{
  /* Korrektur der Adjazenzliste nach der Berechnung von  */
  /* Ersatzzustaenden                                     */
  short State, St;
  long ACO, ACN;
  AdjacentRange ACL, ACD;
  short FORLIM;
  BaseEntry *WITH;
  AdjacentRange FORLIM1;
  AdjacentEntry *WITH1;

  FORLIM = LINK->TMaxState;
  for (St = 1; St <= FORLIM; St++) {
    State = LINK->LINK->StateImage[St];

    if (LINK->DefaultCard[State] > 0) {
      if (BaseVector[State - 1].StateCard > LINK->DefaultCard[State]) {
	WITH = &BaseVector[State - 1];

	ACO = WITH->StateBase;
	ACN = WITH->StateBase;
	ACL = WITH->StateBase + WITH->StateCard - 1;
	WITH = &BaseVector[LINK->DefaultState[State] - 1];

	FORLIM1 = WITH->StateBase + WITH->StateCard - 2;
	/* Zusammenschieben der uebriggebliebenen Eintraege */
	for (ACD = WITH->StateBase - 1; ACD <= FORLIM1; ACD++) {
	  WITH1 = &AdjacentVector[ACD];
	  while (AdjacentVector[ACO - 1].Symbol != WITH1->Symbol) {
	    AdjacentVector[ACN - 1] = AdjacentVector[ACO - 1];
	    ACN++;
	    ACO++;
	  }

	  if (AdjacentVector[ACO - 1].TableEntry != WITH1->TableEntry) {
	    AdjacentVector[ACN - 1] = AdjacentVector[ACO - 1];
	    ACN++;
	    ACO++;
	  } else
	    ACO++;

	}

	if (ACO <= ACL) {
	  do {
	    AdjacentVector[ACN - 1] = AdjacentVector[ACO - 1];
	    ACN++;
	    ACO++;
	  } while (ACO <= ACL);
	}

      }
      /* Nicht alle Eintraege dieser Zeile wurden eingespart */


      WITH = &BaseVector[State - 1];

      WITH->StateCard -= LINK->DefaultCard[State];
    }
    /* Eintraege in dieser Zeile wurden eingespart */

  }  /* for */

}  /* Adjust */


Local Void PrintTerminalPart(LINK)
struct LOC_ProcessTerminalPart *LINK;
{
  /* Ausgabe der Vektoren TBASE, TNEXT und TDEFAULT auf die       */
  /* Datei Zerdat.                                                */
  long I, J, FORLIM;
  BaseEntry *WITH;
  long FORLIM1;
  AdjacentEntry *WITH1;


  FORLIM = ActMaxState;
  for (I = 1; I <= FORLIM; I++) {
    PUTFBUF(Zerdat, long, LINK->TBase[I]);
    PUT(Zerdat, long);   /* TBASE */
    WITH = &BaseVector[I - 1];
    if (WITH->StateCard > 0) {
      FORLIM1 = WITH->StateBase + WITH->StateCard - 2;
      for (J = WITH->StateBase - 1; J <= FORLIM1; J++) {
	WITH1 = &AdjacentVector[J];
	PUTFBUF(Zerdat, long, LINK->TBase[I] + WITH1->Symbol);
	PUT(Zerdat, long);
	PUTFBUF(Zerdat, long, WITH1->TableEntry);
	PUT(Zerdat, long);   /* TNEXT */
      }
    }
    PUTFBUF(Zerdat, long, -4);
    PUT(Zerdat, long);
  }
  PUTFBUF(Zerdat, long, -5);
  PUT(Zerdat, long);

  if (!(LINK->LINK->FixedDefaults || LINK->LINK->VariableDefaults))
    return;

  FORLIM = ActMaxState;
  for (I = 1; I <= FORLIM; I++) {
    PUTFBUF(Zerdat, long, LINK->DefaultState[I]);
    PUT(Zerdat, long);   /* TZDEFAULT */
  }
  PUTFBUF(Zerdat, long, -6);
  PUT(Zerdat, long);
}  /* PrintTerminalPart */


Local Void ProcessTerminalPart(LINK)
struct LOC_Optimization *LINK;
{
  /* Bearbeiten des Terminalteils der Zerteilertabellen */
  struct LOC_ProcessTerminalPart V;
  short TMaxCard;
  CombRange TMaxBase;



  V.LINK = LINK;
  ReadTable('T', &TMaxCard, LINK);

  LINK->TEntryCount1 = LINK->AdjazenzTop;

  RenumberProductions('T', LINK);

  LINK->TEntryCount2 = LINK->TEntryCount1;

  LINK->TMaxEntry = ActMaxState + NumProd * 2;

  RenumberTableEntries('T', LINK);

  SortStates(&V.TMaxState, TMaxCard, LINK);

  if (LINK->VariableDefaults || LINK->FixedDefaults) {
    ComputeDefaults(&V);
    if (LINK->FixedDefaults)
      OneDefault(&V);
    Adjust(&V);
    SortStates(&V.TMaxState, TMaxCard, LINK);
    LINK->TEntryCount3 = CountEntries();
  }

  CompressTable(V.TBase, &TMaxBase, &LINK->TMaxNext, TMaxCard, V.TMaxState,
		LINK);

  LINK->TMaxCheck = TMaxBase + MaxTerminalCode;

  PrintTerminalPart(&V);

}  /* ProcessTerminalPart */

Local long Anzbyte(X)
long X;
{ long n = 0;
  while (X > 0) { X >>= 1; n++; }
  return n = (n + 7) / 8;
}


Local Void OptimizationResults(LINK)
struct LOC_Optimization *LINK;
{
  /* Ausgabe der Ergebnisse der Optimierung */
  long Sls, Slaengers, Sfsymbol, Srsymbol, Sbracket, Sskip, Stbase, Stnext,
       Stcheck, Stzdefault, Sntbase, Sntnext, Ssum, Ssum1, Suttab, Suntab;


  Suttab = ActMaxState * ActMaxTerm * Anzbyte(LINK->TMaxEntry);
  Suntab = ActMaxState * ActMaxNTerm * Anzbyte(LINK->NtMaxEntry);
  Stbase = ActMaxState * Anzbyte(LINK->TMaxNext);
  Stnext = (LINK->TMaxNext + 1) * Anzbyte(LINK->TMaxEntry);
  Stcheck = (LINK->TMaxCheck + 1) * Anzbyte((long)ActMaxState);
  if (LINK->FixedDefaults || LINK->VariableDefaults)
    Stzdefault = ActMaxState * Anzbyte((long)ActMaxState);
  Sntbase = ActMaxState * Anzbyte(LINK->NtMaxNext);
  Sntnext = LINK->NtMaxNext * Anzbyte(LINK->NtMaxEntry);
  Sls = NumProd * Anzbyte((long)ActMaxNTerm);
  Slaengers = NumProd * Anzbyte((long)ActMaxRsLength);
  Sfsymbol = ActMaxState * Anzbyte((long)MaxTerminalCode);
  Srsymbol = ActMaxState * Anzbyte((long)MaxTerminalCode);
  Sbracket = MaxTerminalCode / 8 + 1;
  Sskip = MaxTerminalCode / 8 + 1;
  Ssum1 = Sls + Slaengers + Sfsymbol + Srsymbol + Sbracket + Sskip;
  Ssum = Ssum1 + Stbase + Stnext + Stcheck + Sntbase + Sntnext;
  if (LINK->FixedDefaults || LINK->VariableDefaults)
    Ssum += Stzdefault;

  fprintf(Putout, "\nOptimization Results\n");
  fprintf(Putout, "====================\n\n");
  fprintf(Putout, "Grammar                      : %.*s\n",
	  Maxsymlaenge, Gramtitel);
  fprintf(Putout, "Terminals                    : %*d\n", B, ActMaxTerm);
  fprintf(Putout, "Nonterminals                 : %*d\n", B, ActMaxNTerm);
  fprintf(Putout, "Productions                  : %*d\n", B, ActMaxProdNr);
  fprintf(Putout, "Without chain productions    : %*ld\n", B, NumProd);
  fprintf(Putout, "States                       : %*d\n", B, ActMaxState);
  fprintf(Putout, "Table entries terminal part  : %*ld\n",
	  B, LINK->TEntryCount1);
  fprintf(Putout, "Table entries nonterm. part  : %*ld\n\n\n",
	  B, LINK->NtEntryCount1);
  fprintf(Putout, "Uncompressed parse tables\n");
  fprintf(Putout, "=========================\n\n");
  fprintf(Putout, "Size of terminal matrix      : %d*%d\n",
	  ActMaxState, ActMaxTerm);
  fprintf(Putout, "Size of nonterminal matrix   : %d*%d\n\n",
	  ActMaxState, ActMaxNTerm);
  fprintf(Putout, "Storage need\n");
  fprintf(Putout, "------------\n");
  fprintf(Putout, "Terminal part                : %*ld%s\n", B, Suttab, Bytes);
  fprintf(Putout, "Nonterminal part             : %*ld%s\n", B, Suntab, Bytes);
  fprintf(Putout, "Left-hand side vector        : %*ld%s\n", B, Sls, Bytes);
  fprintf(Putout, "Right-hand side length vector: %*ld%s\n",
	  B, Slaengers, Bytes);
  fprintf(Putout, "Error recovery information   : %*ld%s\n",
	  B, Sfsymbol + Srsymbol + Sskip + Sbracket, Bytes);
  fprintf(Putout, "Total storage requirements   : %*ld%s\n\n\n",
	  B, Suttab + Suntab + Ssum1, Bytes);
  fprintf(Putout, "Compressed parse tables\n");
  fprintf(Putout, "=======================\n\n");
  fprintf(Putout, "Computation of default states: ");
  if (LINK->FixedDefaults)
    fprintf(Putout, "fixed");
  else
    fprintf(Putout, "variable");
  fprintf(Putout, " default variant\n\n");
  fprintf(Putout, "Storage need\n");
  fprintf(Putout, "------------\n");
  fprintf(Putout, "Terminal part\n");
  fprintf(Putout, "a) base vector               : %*ld%s\n", B, Stbase, Bytes);
  fprintf(Putout, "b) default vector            : %*ld%s\n",
	  B, Stzdefault, Bytes);
  fprintf(Putout, "c) next vector               : %*ld%s\n", B, Stnext, Bytes);
  fprintf(Putout, "   %% of used next entries    : %*.1f%%\n",
	  B, 100 * (LINK->TEntryCount3 / (LINK->TMaxNext + 1.0)));
  fprintf(Putout, "d) check vector              : %*ld%s\n",
	  B, Stcheck, Bytes);
  fprintf(Putout, "Sum                          : %*ld%s\n",
	  B, Stbase + Stzdefault + Stnext + Stcheck, Bytes);
  fprintf(Putout, "Nonterminal part\n");
  fprintf(Putout, "a) base vector               : %*ld%s\n",
	  B, Sntbase, Bytes);
  fprintf(Putout, "b) next vector               : %*ld%s\n",
	  B, Sntnext, Bytes);
  fprintf(Putout, "   %% of used next entries    : %*.1f%%\n",
	  B, 100 * ((double)LINK->NtEntryCount2 / LINK->NtMaxNext));
  fprintf(Putout, "Sum                          : %*ld%s\n",
	  B, Sntbase + Sntnext, Bytes);
  fprintf(Putout, "Other vectors                : %*ld%s\n", B, Ssum1, Bytes);
  fprintf(Putout, "Total storage requirements   : %*ld%s\n\n\n",
	  B, Ssum, Bytes);
  fprintf(Putout, "Storage requiremts reduced to: %*.1f%%\n\n",
	  B, 100 * ((double)Ssum / (Ssum1 + Suttab + Suntab)));
/* p2c: optimierung.p, line 2436: 
 * Note: Line breaker spent 1.5 seconds, 378 tries on line 2532 [251] */

}  /* OptimizationResults */

#undef Bytes
#undef B

/* Local variables for PrintConstants: */
struct LOC_PrintConstants {
  struct LOC_Optimization *LINK;
} ;

Local Void PrintConstant(Name, Wert, LINK)
Char *Name;
long Wert;
struct LOC_PrintConstants *LINK;
{
  switch (LINK->LINK->TargetLanguage) {

  case PASCAL:
    fprintf(Zudat, "     %.18s=%ld;\n", Name, Wert);
    break;

  case MODULA2:
    fprintf(Zudat, "    %.18s=%ld;\n", Name, Wert);
    break;

  case C:
    fprintf(Zudat, "#define    %.18s%ld\n", Name, Wert);
    break;

  case ADA:
    fprintf(Zudat, "    %.18s: constant :=%ld;\n", Name, Wert);
    break;
  }
}


Local Void PrintConstants(LINK)
struct LOC_Optimization *LINK;
{
  /* Generiert ein Macro mit den generierten Zerteilerkonstanten  */
  /* (in der gewuenschten Zielsprache).                           */
  struct LOC_PrintConstants V;


/* p2c: optimierung.p, line 2355:
 * Note: REWRITE does not specify a name [181] */
  V.LINK = LINK;
  if (Zudat != NULL)
    Zudat = freopen("Zudat", "w", Zudat);
  else
    Zudat = fopen("Zudat", "w");
  if (Zudat == NULL)
    _EscIO(FileNotFound);

  fprintf(Zudat, "&MACRO PGS_GEN_ZERTEILERKONSTANTE\n");
  fprintf(Zudat, "/* Date should go here */\n");

  if (LINK->TargetLanguage == PASCAL) {
    PrintConstant(ZEMAXBIT2, (long)Maxbit2, &V);
    PrintConstant(ZEMAXBITS2, (long)Maxbits2, &V);
  }
  PrintConstant(ZEMAXTERMINALCODE, (long)MaxTerminalCode, &V);
  PrintConstant(ZEMAXRSLAENGE, (long)ActMaxRsLength, &V);
  PrintConstant(ZEANZZST, (long)ActMaxState, &V);
  PrintConstant(ZEMAXTEINTRAG, LINK->TMaxEntry, &V);
  PrintConstant(ZEMAXNTEINTRAG, LINK->NtMaxEntry, &V);
  PrintConstant(ZEMAXTE1, (long)ActMaxState, &V);
  PrintConstant(ZEMAXTE2, ActMaxState + NumProd, &V);
  PrintConstant(ZEMAXNTE, (long)ActMaxState, &V);
  PrintConstant(ZEANZNT, (long)ActMaxNTerm, &V);
  PrintConstant(ZEANZPROD, NumProd, &V);
  if (LINK->TargetLanguage == C) {
    PrintConstant(ZEMAXTNEXT, LINK->TMaxNext, &V);
    PrintConstant(ZEMAXTCHECK, LINK->TMaxCheck, &V);
  } else
    PrintConstant(ZEMAXTTAB, LINK->TMaxCheck, &V);
  if (LINK->TargetLanguage == C)
    PrintConstant(ZEMAXNTNEXT, LINK->NtMaxNext, &V);
  else
    PrintConstant(ZEMAXNTAB, LINK->NtMaxNext, &V);
  if (LINK->TargetLanguage == PASCAL)
    PrintConstant(ZETINDEX, (long)(MaxTerminalCode / Maxbits2), &V);
  else if (LINK->TargetLanguage == C)
    fprintf(Zudat, "#define    %s%s/ M_BITS\n", ZETINDEX, ZEMAXTERMINALCODE);
  PrintConstant(ZESTOPSYMBOL, (long)StopSymNr, &V);

  if (Zudat != NULL)
    Zudat = freopen("Zudat", "r", Zudat);
  else
    Zudat = fopen("Zudat", "r");
  if (Zudat == NULL)
    _EscIO(FileNotFound);
}  /* PrintConstants */

#undef ZEMAXBIT2
#undef ZEMAXBITS2
#undef ZEMAXTEINTRAG
#undef ZEMAXNTEINTRAG
#undef ZEMAXTE1
#undef ZEMAXTE2
#undef ZEMAXNTE
#undef ZEMAXTERMINALCODE
#undef ZEMAXRSLAENGE
#undef ZEANZZST
#undef ZEANZNT
#undef ZEANZPROD
#undef ZEMAXTNEXT
#undef ZEMAXTCHECK
#undef ZEMAXTTAB
#undef ZEMAXNTNEXT
#undef ZEMAXNTAB
#undef ZETINDEX
#undef ZESTOPSYMBOL


Static Void Optimization()
{
  /* In der Prozedur Optimization werden auf die Zerteilertabel-  */
  /* len Methoden zur Speicherung duenn besetzter Matrizen ange-  */
  /* wandt. Die Basismethode ist fuer den Terminal- und den Nicht-*/
  /* terminalteil die sogenannte Kammvektortechnik. Die Anzahl der*/
  /* Eintraege des Terminalteils wird durch die Verwendung von    */
  /* festen oder variablen Defaultzustaenden reduziert. Die Anzahl*/
  /* der Eintraege des Nichtterminalteils wird durch Elimination  */
  /* von "Teilmengenzeilen" reduziert. Kammvektortechnik und Opti-*/
  /* mierung mit Defaultzustaenden sind in Aho, Sethi, Ullman,    */
  /* Compilers: Principles, Techniques and Tools, naeher beschrie-*/
  /* ben.                                                         */
  struct LOC_Optimization V;
  long I, FORLIM;


  fprintf(Putout, "\nPGS 8.0 --- Optimization\n");
  if (Zerdat != NULL) {

/* p2c: optimierung.p, line 2400:
 * Note: REWRITE does not specify a name [181] */
    Zerdat = freopen("Zerdat", "wb", Zerdat);
  } else
    Zerdat = fopen("Zerdat", "wb");
  if (Zerdat == NULL)
    _EscIO(FileNotFound);
  SETUPBUF(Zerdat, long);

  ActMaxNTerm -= NonMinimal;
  NumProd = 0;
  FORLIM = ActMaxProdNr;
  for (I = 0; I < FORLIM; I++)
    V.ProdImage[I] = 0;

  V.FixedDefaults = false;
  V.VariableDefaults = true;
  if (P_inset('F', Options)) {
    V.VariableDefaults = false;
    V.FixedDefaults = true;
  }

  if (P_inset('P', Options))
    V.TargetLanguage = MODULA2;
  else if (P_inset('U', Options))
    V.TargetLanguage = C;
  else if (P_inset('Y', Options))
    V.TargetLanguage = ADA;
  else
    V.TargetLanguage = PASCAL;

  /* Ende der Initialisierung */

#ifdef MONITOR
  prodsfile = fopen ("mon_cprods.h", "a");
  fprintf (prodsfile, "#ifdef MONITOR\nint conc_prodmap[] = {\n0,\n");
#endif

  ProcessNonTerminalPart(&V);
  ProcessTerminalPart(&V);

#ifdef MONITOR
  fprintf (prodsfile, "-1\n};\n#endif\n");
  fclose (prodsfile);
#endif

  OptimizationResults(&V);

  ReadTables(&V);
  PrintSemanticActions(&V);

  PrintConstants(&V);

  if (Zerdat != NULL)
    Zerdat = freopen("Zerdat", "rb", Zerdat);
  else
    Zerdat = fopen("Zerdat", "rb");
  if (Zerdat == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Zerdat, long);
}  /* Optimization */


/* Sprungziel bei Fehler in Optimierungein */

#define Varende         (-1)
#define Strende         (-2)
#define Wahr            1


/* Local variables for Optimierungein: */
struct LOC_Optimierungein {
  jmp_buf _JL1;
} ;

Local Void Separatortest(Testzahl, Separator, LINK)
long Testzahl, Separator;
struct LOC_Optimierungein *LINK;
{
  if (Testzahl != Separator) {
    ErrorMessage(1L);
    longjmp(LINK->_JL1, 1);
  }
}  /* Separatortest */


Static Void Optimierungein()
{
  /* Variablenschnittstelle zwischen Analyse und Optimierung. Fuer */
  /* die Optimierung nicht benoetigte Daten werden ueberlesen      */
  struct LOC_Optimierungein V;

  long J;
  Symbolart2 Symart2;
  long FORLIM;

  if (setjmp(V._JL1))
    goto _L1;
  if (Interdat != NULL)
    Interdat = freopen("Interdat", "rb", Interdat);
  else
    Interdat = fopen("Interdat", "rb");
  if (Interdat == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Interdat, long);
  Separatortest(RdInterdat(), (long)Varende, &V);
  J = RdInterdat();
  if (J > Maxlaengeallerrs) {
    ErrorMessage(6L);
    goto _L1;
  }
  ActMaxRsLength = J;
  GET(Interdat, long);   /* ActRsPos */
  J = RdInterdat();
  if (J > Maxprodnr) {
    ErrorMessage(7L);
    goto _L1;
  }
  ActMaxProdNr = J;
  NonMinimal = RdInterdat();
  StartSymNr = RdInterdat();
  StopSymNr = RdInterdat();
  J = RdInterdat();
  if (J >= Maxsymnr) {
    ErrorMessage(8L);
    goto _L1;
  }
  MaxTerminalCode = J;
  J = RdInterdat();
  if (J > Maxterm) {
    ErrorMessage(9L);
    goto _L1;
  }
  if (J >= Maxsymnr) {
    ErrorMessage(8L);
    goto _L1;
  }
  ActMaxTerm = J;
  J = RdInterdat();
  if (J > Maxnterm) {
    ErrorMessage(10L);
    goto _L1;
  }
  if (J >= Maxsymnr) {
    ErrorMessage(8L);
    goto _L1;
  }
  ActMaxNTerm = J;
  J = RdInterdat();
  if (J >= Maxsymnr) {
    ErrorMessage(8L);
    goto _L1;
  }
  ActMaxSymNr = J;
  GET(Interdat, long);   /* ActMaxSymLength */
  J = RdInterdat();
  if (J >= Maxzustand) {
    ErrorMessage(5L);
    goto _L1;
  }
  ActMaxState = J;
  GET(Interdat, long);   /* Egtlaenge */
  GET(Interdat, long);   /* Fehlerzahl */
  GET(Interdat, long);   /* Eazeit */
  GET(Interdat, long);   /* Gszeit */
  J = RdInterdat();
  if (J == Wahr)
    Keinefehler = true;
  else
    Keinefehler = false;
  /* Keinefehler := RdInterdat = Wahr; */
  for (J = 0; J < Datumsgrenze; J++)
    Udatum[J] = (Char)RdInterdat();
  Separatortest(RdInterdat(), (long)Varende, &V);
  for (J = 0; J < Maxsymlaenge; J++)
    Extgramtitel[J] = (Char)RdInterdat();
  Separatortest(RdInterdat(), (long)Varende, &V);
  for (J = 0; J < Maxsymlaenge; J++)
    Gramtitel[J] = (Char)RdInterdat();
  Separatortest(RdInterdat(), (long)Varende, &V);
  P_expset(Options, 0L);
  while (GETFBUF(Interdat, long) >= 0)
    P_addset(Options, (Char)RdInterdat());
  Separatortest(RdInterdat(), (long)Varende, &V);
  for (J = 0; J <= Maxsymsetindex; J++) {   /* SEPA */
    while (GETFBUF(Interdat, long) >= 0)
      GET(Interdat, long);
  /*  Separatortest(RdInterdat(), (long)Strende, &V);*/ 
  }
  Separatortest(RdInterdat(), (long)Varende, &V);

   P_expset(BRACKET, 0L);
    while (GETFBUF(Interdat, long) >= 0)
       P_addset(BRACKET, (int)RdInterdat());
 /*   Separatortest(RdInterdat(), (long)Strende, &V);*/ 
  
  Separatortest(RdInterdat(), (long)Varende, &V); 

   P_expset(SKIP, 0L);
    while (GETFBUF(Interdat, long) >= 0)
       P_addset(SKIP, (int)RdInterdat());
  /*  Separatortest(RdInterdat(), (long)Strende, &V);*/ 
  
  Separatortest(RdInterdat(), (long)Varende, &V);
  for (J = 0; J <= Maxsymsetindex; J++) {   /* STACK */
    while (GETFBUF(Interdat, long) >= 0)
      GET(Interdat, long);
  /*  Separatortest(RdInterdat(), (long)Strende, &V);*/ 

  }
  Separatortest(RdInterdat(), (long)Varende, &V);
  FORLIM = ActMaxTerm;
  for (J = 0; J < FORLIM; J++)
    Tab[J] = RdInterdat();
  Separatortest(RdInterdat(), (long)Varende, &V);
  FORLIM = ActMaxNTerm;
  for (J = 0; J < FORLIM; J++)
    Ntab[J] = RdInterdat();
  Separatortest(RdInterdat(), (long)Varende, &V);
  FORLIM = ActMaxSymNr;
  for (J = 0; J <= FORLIM; J++)   /* Inab */
    GET(Interdat, long);
  Separatortest(RdInterdat(), (long)Varende, &V);
  FORLIM = ActMaxSymNr;
  for (J = 0; J <= FORLIM; J++) {
    if (GETFBUF(Interdat, long) >= 0) {
      GET(Interdat, long);   /* Erzu */
      if ((unsigned long)GETFBUF(Interdat, long) < 32 &&
	  ((1L << GETFBUF(Interdat, long)) & 0x1e) != 0) {
	switch (GETFBUF(Interdat, long)) {

	case 1:
	  Symart2 = Term;
	  break;

	case 2:
	  Symart2 = Symstruk;
	  break;

	case 3:
	  Symart2 = Nt;
	  break;

	case 4:
	  Symart2 = Hilfnt;
	  break;
	}
      } else
	Separatortest(0L, 1L, &V);
      GET(Interdat, long);
      if (((1L << ((long)Symart2)) &
	   ((1L << ((long)Nt)) | (1L << ((long)Hilfnt)))) != 0) {
	GET(Interdat, long);   /* Lseite */
	/* Rkschlange := nil */
	GET(Interdat, long);   /* Kettprod */
	GET(Interdat, long);   /* Epsilon := RdInterdat = Wahr */
      }
    }
    Separatortest(RdInterdat(), (long)Strende, &V);
  }
_L1:
  if (Interdat != NULL)
    Interdat = freopen("Interdat", "rb", Interdat);
  else
    Interdat = fopen("Interdat", "rb");
  if (Interdat == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Interdat, long);
}  /* Optimierungein */

#undef Varende
#undef Strende
#undef Wahr

int
main(argc, argv)
int argc;
Char *argv[];
{
  PASCAL_MAIN(argc, argv);
  if (setjmp(_JL1))
    goto _L1;
  obstack_init(&SymObs);
  Zudat = NULL;
  Putout = NULL;
  Strukdat = NULL;
  Symbolda = NULL;
  Tabdat = NULL;
  Zerdat = NULL;
  Interdat = NULL;
  if (Putout != NULL)
    Putout = freopen("Putout", "w", Putout);
  else
    Putout = fopen("Putout", "w");
  if (Putout == NULL)
    _EscIO(FileNotFound);
  Two = 2;   /* Workaround for BSD Pascal bug */
  Optimierungein();
  InitOptions();
  if (Keinefehler & P_inset('O', Options)) {
    Optimierzeit = cputime();

    if (Symbolda != NULL)
      Symbolda = freopen("Symbolda", "rb", Symbolda);
    else
      Symbolda = fopen("Symbolda", "rb");
    if (Symbolda == NULL)
      _EscIO(FileNotFound);
    while (!P_eof(Symbolda)) {
      char C; int Snr, Laenge;

      (void)fscanf(Symbolda, "%5d%4d ", &Snr, &Laenge);
      for (C = getc(Symbolda); C != '\n' && C != '\r'; C = getc(Symbolda)) {
        obstack_1grow(&SymObs, C);
      }
      if (C == '\r') {
        if ((C = getc(Symbolda)) != '\n') ungetc(C, stdin);
      }
      obstack_1grow(&SymObs, '\0');

      SymbolTable[Snr] = (Drusym *)malloc(sizeof(Drusym));
      SymbolTable[Snr]->Snr = Snr;
      SymbolTable[Snr]->Laenge = Laenge;
      SymbolTable[Snr]->Bez = (char *)obstack_finish(&SymObs);
    }

    Optimization();

    Optimierzeit = cputime() - Optimierzeit;
    Messzeit("Optimization", 0L, Optimierzeit);
    /* Schliessen aller externen Dateien */
    if (Zudat != NULL)
      Zudat = freopen("Zudat", "r", Zudat);
    else
      Zudat = fopen("Zudat", "r");
    if (Zudat == NULL)
      _EscIO(FileNotFound);
    if (Zerdat != NULL)
      Zerdat = freopen("Zerdat", "rb", Zerdat);
    else
      Zerdat = fopen("Zerdat", "rb");
    if (Zerdat == NULL)
      _EscIO(FileNotFound);
    RESETBUF(Zerdat, long);
    if (Tabdat != NULL)
      Tabdat = freopen("Tabdat", "rb", Tabdat);
    else
      Tabdat = fopen("Tabdat", "rb");
    if (Tabdat == NULL)
      _EscIO(FileNotFound);
    RESETBUF(Tabdat, long);
  } else
    printf("    No execution of Optimization\n");
_L1:
  if (Putout != NULL)
    Putout = freopen("Putout", "r", Putout);
  else
    Putout = fopen("Putout", "r");
  if (Putout == NULL)
    _EscIO(FileNotFound);
  if (!Keinefehler)
    _Escape(0);
  if (Interdat != NULL)
    fclose(Interdat);
  if (Zerdat != NULL)
    fclose(Zerdat);
  if (Tabdat != NULL)
    fclose(Tabdat);
  if (Symbolda != NULL)
    fclose(Symbolda);
  if (Strukdat != NULL)
    fclose(Strukdat);
  if (Putout != NULL)
    fclose(Putout);
  if (Zudat != NULL)
    fclose(Zudat);
  return 0;
}
/* End. */
