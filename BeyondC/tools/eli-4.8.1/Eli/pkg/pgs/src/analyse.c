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

static char rcsid[] = {"$Id: analyse.c,v 1.30 2013/11/12 20:38:25 profw Exp $"};

/* Output from p2c, the Pascal-to-C translator */
/* From input file "analyse.p" */


#include "p2c.h"
#include <stdlib.h>
#define HAS_STDLIB
#include "obstack.h"
#include "options.h"
#include "showEx.h"
#include "analyse.h"


/**********************************************************************/
/*                                                                    */
/*          ZZZZZZ   EEEEEE   DDDDD    EEEEEE   RRRRR                 */
/*          ZZZZZZ   EEEEEE   DDDDDD   EEEEEE   RRRRRR                */
/*             ZZ    EE       DD  DD   EE       RR  RR                */
/*            ZZ     EEEEE    DD  DD   EEEEE    RRRRR                 */
/*           ZZ      EE       DD  DD   EE       RRRR                  */
/*          ZZZZZZ   EEEEEE   DDDDDD   EEEEEE   RR RR                 */
/*          ZZZZZZ   EEEEEE   DDDDD    EEEEEE   RR  RR                */
/*                                                                    */
/*                                                                    */
/*                                                                    */
/*          Ein System zur automatischen LR-Zerteiler-                */
/*          erzeugung mit - wahlweise - Zeitoptimierungs-             */
/*          verfahren DEVAR durch Verschmelzen von                    */
/*          Aktionen in Zerteilern.                                   */
/*                                                                    */
/*      Autoren : Eduard Klein                                        */
/*                Richard Laengle                                     */
/*                                                                    */
/*             Im September 1984                                      */
/*                                                                    */
/**********************************************************************/
/**********************************************************************/
/*                                                                    */
/* Verzeichnis der Literaturhinweise im Programm :                    */
/*                                                                    */
/*    [Goos83]   Goos Gerhard, Waite M.                               */
/*               Compiler Construction                                */
/*               Springer 1983                                        */
/*                                                                    */
/*    [Kl84]     Klein Eduard                                         */
/*               Ein allgemeines LR-SLR-LALR-System                   */
/*               Diplomarbeit am Institut II fuer Informatik          */
/*               Universitaet Karlsruhe                               */
/*                                                                    */
/*    [Roe78]    Roehrich Johannes                                    */
/*               Automatic Construction of Error Correcting           */
/*               Parsers                                              */
/*               Institut II fuer Informatik                          */
/*               Universitaet Karlsruhe                               */
/*               Bericht Nr. 8, Sept 1978                             */
/*                                                                    */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                    */
/* DATEIEN:                                                           */
/*         infile         : text; (EINGABE)                           */
/*               ENTHAELT DIE STEUERDATEN (OPTIONEN) FUER DIE ANALYSE */
/*                                                                    */
/*         output         : text; (AUSGABE)                           */
/*               ENTHAELT DIE DIALOG-INFORMATION                      */
/*                                                                    */
/*         PUTOUT         : text; (AUSGABE)                           */
/*               ENTHAELT DAS BENUTZERPROTOKOLL                       */
/*                                                                    */
/*         VAREINDA       : INTFILE; (EINGABE)                       */
/*               VARIABLENSCHNITTSTELLE ZWISCHEN EINGABE UND ANALYSE  */
/*                                                                    */
/*         VARANADA       : INTFILE; (AUSGABE)                       */
/*               VARIABLENSCHNITTSTELLE ZU DEVAR                      */
/*                                                                    */
/*         KETTDAT        : INTFILE; (AUSGABE)                       */
/*               SCHNITTSTELLE ZU DEVAR  (ENTHAELT ALLE KETTEN-PROD.) */
/*                                                                    */
/*         TABDAT         : INTFILE; (AUSGABE)                        */
/*               ENTHAELT DIE NICHT OPTIMIERTEN ZERTEILERTABELLEN     */
/*                                                                    */
/*                                                                    */
/*         SYMBOLDA       : text; (EINGABE)                   */
/*               ENTHAELT DIE BEZEICHNER DER SYMBOLTABELLE            */
/*                                                                    */
/*         VOKDAT         : text; (AUSGABE)                           */
/*               ENTHAELT FUER TESTZWECKE DEN LESBAREN INHALT         */
/*               VON TABDAT : INTFILE                                 */
/*                                                                    */
/*         FEHLERDA       : text; (AUSGABE/EINGABE)                   */
/*               ENTHAELT DIE FEHLERZUSTANDSNUMMERN UND FEHLER-       */
/*               NUMMERN UND -SYMBOLE DER ZUSTANDSTABELLE             */
/*                                                                    */
/*         OPTIONEN       : text ( EINGABE )                          */
/*               enthaelt die Optionen                                */
/*                                                                    */
/* OPTION:                                                            */
/*     A = PERFORM LALR(1) ANALYSIS                                   */
/*     C = DO NOT ELIMINATE CHAIN PRODUCTIONS                         */
/*     D = OUTPUT THE COMPLETE STATE TABLE                            */
/*     N = CONFLICTS ILLUSTRATED BY DERIVATIONS (IMPLIES C+W)         */
/*     S = A+O+Z                                                      */
/*     W = DO NOT USE SHIFT-REDUCE OPERATIONS                         */
/*     X = PARTIAL CHAIN PRODUCTION ELIMINATION                       */
/*                                                                    */
/**********************************************************************/
/*$page*/

#define MaxHuellLaenge  20000
#define MaxUnter        1023

typedef Char Usymbolstring[Maxsymlaenge];

FILE *infile, *Putout, *Vokdat, *Fehlerda;

Static FILE *Kettdat, *Vareinda, *Varanada, *Tabdat;
Static FILE *Symbolda;

Static SymMenge Separator, Semklammer, Ueberlesen, Kellermenge;

Static ZuMenge LeerZuMenge;
Static ProdMenge LeerProdMenge;
/* Leere Mengen */


Static Usymbolstring Extgramtitel, Gramtitel;
Static Char Udatum[24];   /* SIEMENS-PASCAL */


short AktMaxRsLaenge;
short AktRsPos;
short StartProduktion, AktMaxProdNr;
short StartSymNr, StopSymNr, MaxTerminalCode;
short AktMaxTerm;   /* 0 <=> EPSILON */
short AktMaxNterm;
short AktMaxSymNr;
int AktMaxSymLaenge;
short AktMaxZustand;

Static boolean KeineFehler;
Static int FehlerZahl;
Static long EgtLaenge;   /* EXTERNE GRAMMATIK TITELLAENGE */
Static long EaZeit, GsZeit, I, J, Zeit, AnalyseEaZeit, AnalyseZeit;

TSymTabTyp *SymTab[Maxsymnr + 1];
short RsFeld[Maxlaengeallerrs];
/* Enthaelt alle rechten Seiten aneinandergehaengt */
TLsTyp *Ls[Maxprodnr];
TRsTyp Rs[Maxprodnr];
short Tab[Maxterm];
short Ntab[Maxnterm];
short Inab[Maxsymnr + 1];
FILEBUF(infile,Static,Char);
FILEBUF(Vareinda,Static,long);
FILEBUF(Symbolda,Static,Char);


/* Identifer and literal strings */
 
TBez *Bezeichner[Maxsymnr + 1];
static struct obstack SymObs;


/* INAB liefert zu einer Symbol-Nummer die Terminal- bzw Nicht- */
/* Terminal-Nummer ==>  Bildbereich >= Max (MAX_TERM,MAX_NTERM) */

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


Static Void Druint(Dat, Spalte, Zahl, Breite)
FILE **Dat;
long *Spalte, Zahl, Breite;
{
  /* Diese Prozedur verwaltet die Dateibeschreibung,da auf der SIEMENS*/
  /* am logischen Zeilenende kein automatischer Zeilenwechsel erfolgt */
  /* DRUINT */
  *Spalte += Breite;
  if (*Spalte > Maxdruckspalte) {
    *Spalte = Breite;
    putc('\n', *Dat);
  }
  fprintf(*Dat, "%*ld", (int)Breite, Zahl);
}


Static long RdEindat()
{
  long Result;

  Result = GETFBUF(Vareinda, long);
  GET(Vareinda, long);
  return Result;
}  /* VON RDINT */


Static Void Messzeit(Mess, Startzeit, Stopzeit)
Char *Mess;
long Startzeit, Stopzeit;
{
  /*
  long Zeit;

  Zeit = Stopzeit - Startzeit;
  fprintf(Putout, "%.12s-Time           : %8.2f Seconds\n",
	  Mess, (double)Zeit / Izeiteinheit);
  */
}  /* VON MESSZEIT */



static char *
ProdString(i)
int i;
{
   static char *Last = (char *)0;
   char *p;
   int j;

   if (Last) obstack_free(&SymObs, Last);
   for (p = Bezeichner[Ls[i-1]->SymNr]->Bezei; *p; p++)
      obstack_1grow(&SymObs, *p);
   obstack_grow(&SymObs, ": ", 2);
   for (j = 0; j < Rs[i-1].RsLaenge; j++) {
      for (p = (char *)Bezeichner[RsFeld[Rs[i-1].RsAnfang - 1 + j]]->Bezei; *p; p++)
         obstack_1grow(&SymObs, *p);
      obstack_1grow(&SymObs, ' ');
   }
   obstack_1grow(&SymObs, '.'); obstack_1grow(&SymObs, '\0');
   return (Last = (char *)obstack_finish(&SymObs));
}

Static Void Fehlertext(Dat, Nummer, V1, V2, V3)
FILE **Dat;
long Nummer, V1, V2, V3;
{
  switch (Nummer) {

  case 1:
    fprintf(*Dat, "Error reading file Vareinda");
    break;

  case 3:
    fprintf(*Dat, "Ambiguous chain derivation including symbols \"%s\" and \"%s\"",
	    Bezeichner[V2]->Bezei, Bezeichner[V1]->Bezei);
    break;

  case 4:
    fprintf(*Dat,
	    "The symbol \"%s\" must not be of type SymStruk (illegal input)",
	    Bezeichner[V1]->Bezei);
    break;

  case 5:
    fprintf(*Dat, "The constant Maxzustand = %ld is too small",
	    (long)Maxzustand);
    break;

  case 6:
    fprintf(*Dat, "The constant MaxUnter = %ld is too small", (long)MaxUnter);
    break;

  case 7:
    fprintf(*Dat,
      "Modifications in production \"%s\" ignored for LR(0) reduce states",
      ProdString(V1));
    break;

  case 8:
    fprintf(*Dat, "SymTab [StartSymNr] ^.ERZU has to be 0 \n");
    break;

  case 9:
    fprintf(*Dat,
      "No error symbol can be defined in state %ld due to modifications\n",
      V1);
    break;

  case 10:
    fprintf(*Dat,
      "No error symbol can be defined in state %ld due to modifications\n",
      V1);
    break;

  case 11:
    fprintf(*Dat,
      "\"$%s\" ignored in \"%s\" (state %ld)\n",
      Bezeichner[V3]->Bezei, ProdString(V1), V2);
    break;

  case 12:
    fprintf(*Dat,
      "\"$%s\" solves a conflict in \"%s\" (state %ld)\n",
      Bezeichner[V3]->Bezei, ProdString(V1), V2);
    break;

  case 13:
    fprintf(*Dat,
      "\"@%s\" ignored in \"%s\" (state %ld)\n",
      Bezeichner[V3]->Bezei, ProdString(V1), V2);
    break;

  case 14:
    fprintf(*Dat,
      "\"@%s\" solves a conflict in \"%s\" (state %ld)\n",
      Bezeichner[V3]->Bezei, ProdString(V1), V2);
    break;

  case 18:
    fprintf(*Dat, "The constant MaxHuellLaenge = %ld is too small",
	    (long)MaxHuellLaenge);
    break;

  case 19:
    fprintf(*Dat,
      "Modification '@' with terminal \"%s\" not compatible with automatic error recovery: production %ld\n",
      Bezeichner[V3]->Bezei, V1);
    break;
  }
}  /* von FEHLERTEXT  */


Static Void Fehler(Fehler, Nummer, V1, V2, V3)
boolean Fehler;
long Nummer, V1, V2, V3;
{
  /* Ausdruck auf Datei PUTOUT und output */
  if (Fehler) {
    KeineFehler = false;
    FehlerZahl++;
    fprintf(Putout, "*** Error   %2ld : ", Nummer);
  } else
    fprintf(Putout, "*** Warning %2ld : ", Nummer);
  Fehlertext(&Putout, Nummer, V1, V2, V3);
  putc('\n', Putout);
}  /* von FEHLER */


#define Epsi            0
#define UndefSymbol     (-1)


/* Haengt von der Codierung der Entscheidungs- */
/* tabelle ab                                  */


typedef struct TTKette {
  short T;
  struct TTKette *NextT;
} TTKette;

typedef struct TSymbole {
  short ESym;
  struct TSymbole *Naechstes;
} TSymbole;

/* Hash_tabelle */

typedef struct THashKette {
  long *Tm;
  struct THashKette *NextEl;
} THashKette;



typedef struct _REC_Nth {
  short HuellAnf, HuellEnde;
} _REC_Nth;


/* Darstellung aller Nachfolger eines Zustands */


typedef struct TNeuUeberElem {
  short A;
  struct TNeuUeberElem *Naechste;
  TItemTyp *I, *LetztesI;
} TNeuUeberElem;


#define Leer3           "   "
#define Leer5           "     "
#define Leer7           "       "


typedef Char PackDruckZeile[Maxdruckspalte];



/* Local variables for Analyse: */
struct LOC_Analyse { /* Make these variables global */ };
  TZustandsTyp *Q[Maxzustand];
  /* Das ist die Menge Q aus [Go83]   */

  short FSymbol[Maxzustand];
  /* Datenstruktur fuer die Fehlerbehandlung im Zerteiler */
  /* Theorie dazu : [Roe 78]                              */
  /* F_SYMBOL [Z] = UNDEF_SYMBOL <=> Fehler im Algorithmus*/
  /* F_SYMBOL [Z] = 0 <=> F_SYMBOL [Z] ist Red.-Zeichen   */
  /*               (wird in TESTE_EINGENSCHAFT bestimmt ) */
  /* F_SYMBOL [Z] = i > 0 <=> i ist Uebergang-Zeichen     */

  short KettFSymbol[Maxnterm];
  /* Zu jedem Nicht-Terminal N enthaelt KETT_F_SYMBOL [N] */
  /* = t das "erste" ([Roe 78]) Terminal t mit :    +     */
  /*                                             N ===> t */
  /*                                                  K   */
  /* Falls es so ein t nicht gibt, ist t = 0.             */
  /* Da die Ketten-Items in den Zustaenden nicht vorkommen*/
  /* , kann daraus auch kein Fehlersymbol abgelesen werden*/
  /* Dies rechtfertigt diese zusaetzliche Variable        */

  SymMenge LeerSymMenge;
  TTMenge LeerTMenge;
  TNtMenge LeerNtMenge;
  /* Leere Mengen fuer Initialisierung */

  TUeberElem *UeTabelle[Maxzustand];

  TTKette *KettenZeichen[Maxnterm];
  /* Erlaeuterung siehe Prozedur KETT_ZEICH */

  long *UeberZeich[Maxzustand];
  /* UEBER_ZEICH [Z]^ enthaelt alle Terminal-Zeichen, mit de- */
  /* nen es einen Uebergang von Z aus gibt. Diese Information */
  /* steht zwar auch in der Uebergangs-Tabelle, aber als Ver- */
  /* gleichsmenge (in TESTE_EIGENSCHAFT) ist diese Datenstruk-*/
  /* tur guenstiger                                           */

  short HuellFeld[MaxHuellLaenge];

  _REC_Nth Nth[Maxnterm];
  TTMenge Ntanf[Maxnterm];

  ProdMenge KettPMenge;   /* Hier sind genau alle    */
  /* Kettenproduktionen drin */

  THashKette *HashTabelle[Maxhash + 1];


  ProdMenge Lr0Zustaende;
  ZuMenge FehlerZustaende;
  SymMenge OptSymMenge;

  boolean Devar;
  /* Option */

  boolean DruckOption, TeilKettProd, OhneKettProd;

  boolean SrOpti;
/*} ;*/


/*********************************************************************/
/*                                                                   */
/*     Operationen auf Terminalmengen                                */
/*                                                                   */
/*********************************************************************/

void
VereinigeT(A, B)
long *A, *B;
{
  /*  A := A vereinigt B    */
  
    P_setunion(A, A, B);
}  /* von VEREINIGE_T */


/**********************************************************************/
/*                                                                    */
/*        Operationen auf Nicht-Terminal-Mengen                       */
/*                                                                    */
/**********************************************************************/

void
VereinigeNt(A, B)
long *A, *B;
{
  /* A := A vereinigt B   */
  
    P_setunion(A, A, B);
}  /* von VEREINIGE_NT */


/**********************************************************************/
/*                                                                    */
/*          Ein- ,Ausgabe- Routinen                                   */
/*                                                                    */
/**********************************************************************/


Local Void LiesKettProd(Ein, Aus, LINK)
FILE **Ein, **Aus;
struct LOC_Analyse *LINK;
{
  /* Je nach Option werden die Ketten-Produktionen bestimmt oder von */
  /* Hand eingelesen                                                 */
  /* External : KETT_P_MENGE                                         */
  boolean Null;
  long P, FORLIM;

  if (TeilKettProd) {
    Null = false;
    while (!Null) {
      if (*Aus != NULL)
	rewind(*Aus);
      else
	*Aus = tmpfile();
      if (*Aus == NULL)
	_EscIO(FileNotFound);
      fprintf(*Aus, "Chain productions?..Terminate input with 0 !!\n");
      rewind(*Ein);
      while (!P_eoln(*Ein)) {
	fscanf(*Ein, "%ld", &P);
	if (P < 0 || AktMaxProdNr < P) {
	  fprintf(*Aus, "%3ld is out of range !!\n", P);
	  continue;
	}
	if (P == 0)
	  Null = true;
	else {
	  if (Ls[P - 1]->Zusatz || Rs[P - 1].RsLaenge != 1 ||
	      P == StartProduktion)
	    fprintf(*Aus, "%3ld is not a chain production !!\n", P);
	  else
	    HinzuP(KettPMenge, (int)P);
	}
      }
    }
/* p2c: analyse.p, line 964: Note: REWRITE does not specify a name [181] */
    return;
  }

  if (!OhneKettProd) {
    fprintf(*Aus, "No chain productions recognized due to options\n");
    return;
  }
  FORLIM = AktMaxProdNr;
  for (P = 1; P <= FORLIM; P++) {
    if (!Ls[P - 1]->Zusatz && Rs[P - 1].RsLaenge == 1 && P != StartProduktion)
      HinzuP(KettPMenge, (int)P);
  }
}  /* von LIES_KETT_PROD */

Local Void DruckeBez(Sn, LINK)
short Sn;
struct LOC_Analyse *LINK;
{
  /* Druckt das Zeichen mit der Symbol-Nummer SN */
  fprintf(Putout, "%s  ", Bezeichner[Sn]->Bezei);
}  /* von DRUCKE_BEZ */


/*********************************************************************/
/*                                                                   */
/*     Realisierung der Hash_Tabelle                                 */
/*                                                                   */
/*********************************************************************/


/*
--------------------------------------------------------------------
mix -- mix 3 32-bit values reversibly.
For every delta with one or two bits set, and the deltas of all three
  high bits or all three low bits, whether the original value of a,b,c
  is almost all zero or is uniformly distributed,
* If mix() is run forward or backward, at least 32 bits in a,b,c
  have at least 1/4 probability of changing.
* If mix() is run forward, every bit of c will change between 1/3 and
  2/3 of the time.  (Well, 22/100 and 78/100 for some 2-bit deltas.)
mix() was built out of 36 single-cycle latency instructions in a 
  structure that could supported 2x parallelism, like so:
      a -= b; 
      a -= c; x = (c>>13);
      b -= c; a ^= x;
      b -= a; x = (a<<8);
      c -= a; b ^= x;
      c -= b; x = (b>>13);
      ...
  Unfortunately, superscalar Pentiums and Sparcs can't take advantage 
  of that parallelism.  They've also turned some of those single-cycle
  latency instructions into multi-cycle latency instructions.  Still,
  this is the fastest good hash I could find.  There were about 2^^68
  to choose from.  I only looked at a billion or so.
--------------------------------------------------------------------
*/
#define mix(a,b,c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8); \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12);  \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

/*
--------------------------------------------------------------------
hash() -- hash a variable-length key into a 32-bit value
  k       : the key (the unaligned variable-length array of bytes)
  len     : the length of the key, counting by bytes
  initval : can be any 4-byte value
Returns a 32-bit value.  Every bit of the key affects every bit of
the return value.  Every 1-bit and 2-bit delta achieves avalanche.
About 6*len+35 instructions.

The best hash table sizes are powers of 2.  There is no need to do
mod a prime (mod is sooo slow!).  If you need less than 32 bits,
use a bitmask.  For example, if you need only 10 bits, do
  h = (h & hashmask(10));
In which case, the hash table should have hashsize(10) elements.

If you are hashing n strings (ub1 **)k, do it like this:
  for (i=0, h=0; i<n; ++i) h = hash( k[i], len[i], h);

By Bob Jenkins, 1996.  bob_jenkins@burtleburtle.net.  You may use this
code any way you wish, private, educational, or commercial.  It's free.

See http://burtleburtle.net/bob/hash/evahash.html
Use for hash table lookup, or anything where one collision in 2^^32 is
acceptable.  Do NOT use for cryptographic purposes.
--------------------------------------------------------------------
*/

ub4 hash( k, length, initval)
register ub1 *k;        /* the key */
register ub4  length;   /* the length of the key */
register ub4  initval;  /* the previous hash, or an arbitrary value */
{
   register ub4 a,b,c,len;

   /* Set up the internal state */
   len = length;
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = initval;         /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   return c;
}

long *
HashIn(TTm)
long *TTm;
/* Insert a set into the hash table
 *   On entry-
 *     TTm points to a non-hash-table copy of the desired set
 *   On exit-
 *     HashIn points to a hash-table copy of the desired set
 ***/
{ 
  /*  Ein Objekt vom Typ T_T_MENGE wird in die Hash-Tabelle */
  /*  eingehaengt, falls noch nicht drin                    */
  THashKette *HashLaeufer;
  char H;
  boolean Weiter;

  H = hash((ub1*)TTm, (TTm[0] + 1) * sizeof(long), 0) & Maxhash;
  HashLaeufer = HashTabelle[H];
  if (HashLaeufer != NULL)
    Weiter = !GleichT(HashLaeufer->Tm, TTm);
  else
    Weiter = false;

  while (Weiter) {
    HashLaeufer = HashLaeufer->NextEl;

    if (HashLaeufer != NULL)
      Weiter = !GleichT(HashLaeufer->Tm, TTm);
    else
      Weiter = false;
  }

  if (HashLaeufer != NULL)
    return (HashLaeufer->Tm);

  HashLaeufer = (THashKette *)Malloc(sizeof(THashKette));
  HashLaeufer->Tm = (long *)Malloc(sizeof(TTMenge));
  memcpy(HashLaeufer->Tm, TTm, sizeof(TTMenge));
  HashLaeufer->NextEl = HashTabelle[H];
  HashTabelle[H] = HashLaeufer;
  return (HashLaeufer->Tm);
}  /* von HASH_IN */

/*******************************************************************/

Local Void UeberOpt(LINK)
struct LOC_Analyse *LINK;
{
  /* Die Prozedur sammelt alle NT's N in OPT_SYM_MENGE auf, zu denen*/
  /* es keine Produktion mit linker Seite N gibt, die nicht Ketten- */
  /* produktion ist                                                 */
  /* External : KETT_P_MENGE , OPT_SYM_MENGE , LS , SYM_TAB         */
  short P;
  boolean Kett;
  short I, FORLIM;

  memcpy(OptSymMenge, LeerSymMenge, sizeof(SymMenge));
  FORLIM = AktMaxSymNr;
  for (I = 1; I <= FORLIM; I++) {
    if (SymTab[I] != NULL) {
      if (((1L << ((long)SymTab[I]->SymArt)) &
	   ((1L << ((long)Nt)) | (1L << ((long)HilfNt)))) != 0) {
	Kett = true;
	P = SymTab[I]->UU.U2.LSeite;
	if (!InP(KettPMenge, P))
	  Kett = false;
	if (P != 0) {
	  P = Ls[P - 1]->Naechste;
	  while (P != 0 && Kett) {
	    if (InP(KettPMenge, P))
	      P = Ls[P - 1]->Naechste;
	    else
	      Kett = false;
	  }
	}
	if (Kett)
	  HinzuSym(OptSymMenge, I);
      }
    }
  }
}  /* UEBER_OPT */

/* Local variables for HuellInv: */
struct LOC_HuellInv {
  struct LOC_Analyse *LINK;
  TSymbole *NeuSym;
  boolean Vorab[Maxnterm];
  SymMenge Betrachtet;
} ;


/**********************************************************************/

Local Void ZyklusTest(Sym, LINK)
short *Sym;
struct LOC_HuellInv *LINK;
{
  /* External : BETRACHTET , VORAB                                 */
  /* Wirkung  : Es werden Kettenproduktions-Zyklen und mehrdeutige */
  /*            Kettenproduktions-Ableitungen erkannt und gemeldet.*/
  /*            Im Erfolgsfall wird die Zustandstabelle nicht auf- */
  /*            gebaut.                                            */
  short P;
  short V0;

  if (((1L << ((long)SymTab[*Sym]->SymArt)) &
       ((1L << ((long)Term)) | (1L << ((long)SymStruk)))) != 0) {
    fprintf(Putout, "ZyklusTest nur mit NTs aufrufen !!\n");
    exit(1);
  }
  P = SymTab[*Sym]->UU.U2.KettProd;
  while (P != 0) {
    V0 = RsFeld[Rs[P - 1].RsAnfang - 1];
    if (InSym(LINK->Betrachtet, V0))
      Fehler(true, 3L, (long)(*Sym), (long)V0, 0L);
    else {
      HinzuSym(LINK->Betrachtet, V0);
      if (((1L << ((long)SymTab[V0]->SymArt)) &
	   ((1L << ((long)Nt)) | (1L << ((long)HilfNt)))) != 0) {
	ZyklusTest(&V0, LINK);
	LINK->Vorab[Inab[V0] - 1] = true;
      }
    }
    P = Ls[P - 1]->KettProd;
  }
}

/* Local variables for KettZeich: */
struct LOC_KettZeich {
  struct LOC_HuellInv *LINK;
  short LsV;
} ;

/* Zum schnelleren Aufbau von KETTEN_ZEICHEN */

Local TTKette *GibTElem(T, LINK)
short T;
struct LOC_KettZeich *LINK;
{
  /* Die Funktion haengt ein neues Element in die */
  /* KETTEN_ZEICHEN - Verkettung ein              */
  /* External : LS_V , KETTEN_ZEICHEN             */
  TTKette *TObjekt;

  TObjekt = (TTKette *)Malloc(sizeof(TTKette));
  TObjekt->T = T;
  TObjekt->NextT = KettenZeichen[Inab[LINK->LsV] - 1];
  return TObjekt;
}


/**********************************************************************/
/*                                                                    */
/*               Berechnung von KETTEN_ZEICHEN                        */
/*                                                                    */
/**********************************************************************/

Local Void KettZeich(LINK)
struct LOC_HuellInv *LINK;
{
  /* Die Prozedur berechnet zu jedem Nichtterminal N die      */
  /* Menge (( t element T , N ==> t ))                        */
  /*                            K                             */
  /* Das Ergebnis steht in KETTEN_ZEICHEN                     */
  /* Ausserdem wird die Reihung KETT_F_SYMBOL berechnet.      */
  /* Zur Theorie siehe Def. von KETT_F_SYMBOL                 */
  /* External : SYM_TAB , LS , RS , RS_FELD , KETTEN_ZEICHEN  */
  struct LOC_KettZeich V;
  long I;
  short KettLaeufer;
  boolean Fertig;
  short V0;
  short T;
  TTKette *TLaeufer;
  TTMenge Lok[Maxnterm];
  long FORLIM;


  V.LINK = LINK;
  FORLIM = AktMaxNterm;
  /* Initialisierung */
  for (I = 0; I < FORLIM; I++) {
    memcpy(Lok[I], LeerTMenge, sizeof(TTMenge));
    KettenZeichen[I] = NULL;
    if (OhneKettProd || TeilKettProd)
      KettFSymbol[I] = 0;
  }
  FORLIM = AktMaxProdNr;
  /* Berechnung der direkten KETTEN_ZEICHEN */
  for (I = 0; I < FORLIM; I++) {
    if (InP(KettPMenge, (int)(I + 1))) {
      V.LsV = Ls[I]->SymNr;
      V0 = RsFeld[Rs[I].RsAnfang - 1];
      if (SymTab[V0]->SymArt == Term) {
	if (!InT(Lok[Inab[V.LsV] - 1], (long)V0)) {
	  if (OhneKettProd || TeilKettProd) {
	    if (KettFSymbol[Inab[V.LsV] - 1] == 0)
	      KettFSymbol[Inab[V.LsV] - 1] = Inab[V0];
	  }
	  HinzuT(Lok[Inab[V.LsV] - 1], (long)V0);
	  KettenZeichen[Inab[V.LsV] - 1] = GibTElem(Inab[V0], &V);
	}
      }
    }
  }
  /* Berechnung der transitiven Huelle */
  Fertig = false;
  while (!Fertig) {
    Fertig = true;
    FORLIM = AktMaxNterm;
    for (I = 0; I < FORLIM; I++) {
      KettLaeufer = SymTab[Ntab[I]]->UU.U2.KettProd;
      while (KettLaeufer != 0) {
	V0 = RsFeld[Rs[KettLaeufer - 1].RsAnfang - 1];
	if (SymTab[V0]->SymArt != Term) {
	  V.LsV = Ls[KettLaeufer - 1]->SymNr;
	  if (OhneKettProd || TeilKettProd) {
	    if (KettFSymbol[Inab[V.LsV] - 1] == 0)
	      KettFSymbol[Inab[V.LsV] - 1] = KettFSymbol[Inab[V0] - 1];
	  }
	  if (!TeilmengeT(Lok[Inab[V0] - 1], Lok[Inab[V.LsV] - 1])) {
	    TLaeufer = KettenZeichen[Inab[V0] - 1];
	    while (TLaeufer != NULL) {
	      T = TLaeufer->T;
	      if (!InT(Lok[Inab[V.LsV] - 1], (long)T))
		KettenZeichen[Inab[V.LsV] - 1] = GibTElem(T, &V);
	      TLaeufer = TLaeufer->NextT;
	    }
	    VereinigeT(Lok[Inab[V.LsV] - 1], Lok[Inab[V0] - 1]);
	    Fertig = false;
	  }  /* von then */
	}
	KettLaeufer = Ls[KettLaeufer - 1]->KettProd;
      }
    }
  }
}  /* von KETT_ZEICH*/

/* Local variables for BerechneFirst: */
struct LOC_BerechneFirst {
  struct LOC_HuellInv *LINK;
  boolean Vorab[Maxnterm];
  /* VORAB (X) = true zeigt an, ob die Vorabberechnungen fuer X */
  /* schon gemacht worden sind                                  */
  TNtMenge AufrufMenge, AbbruchMenge, Betrachtet;
} ;





Local Void BerechneNtanf(Sym, Zw, LINK)
short Sym;
long *Zw;
struct LOC_BerechneFirst *LINK;
{  /* BERECHNE_NTANF */
  /*                                                                 */
  /* External: BETRACHTET, NTANF(X) ,ABBRUCH_MENGE,AUFRUF_MENGE      */
  /* Wirkung : Die Prozedur berechnet NTANF [X].                     */
  short P;
  long I, L;
  boolean Fertig;
  /* Abbruchkriterium */
  short V0;
  TTMenge Erg;




  HinzuNt(LINK->Betrachtet, Inab[Sym]);
  HinzuNt(LINK->AufrufMenge, Inab[Sym]);
  memcpy(Zw, LeerTMenge, sizeof(TTMenge));
  memcpy(Erg, LeerTMenge, sizeof(TTMenge));
  P = SymTab[Sym]->UU.U2.LSeite;
  while (P != 0) {
    if (Rs[P - 1].RsLaenge == 0) {   /* Epsilon - Produktion */
      /* FIRST_1-MENGE erweitert */
      HinzuT(Zw, (long)Epsi);
    } else {
      /* Initialisierung der while-Schleife */
      L = Rs[P - 1].RsLaenge;
      I = 1;
      Fertig = false;

      /* Diese while-Schleife durchlaeufet die rechte Seite */
      /* der Produktion P                                   */
      while (I <= L && !Fertig) {
	V0 = RsFeld[Rs[P - 1].RsAnfang + I - 2];
	if (SymTab[V0]->SymArt == Term) {
	  HinzuT(Zw, (long)Inab[V0]);
	  Fertig = true;
	} else {
	  if (LINK->Vorab[Inab[V0] - 1])
	    memcpy(Erg, Ntanf[Inab[V0] - 1],
		   sizeof(TTMenge));
	  else {
	    if (InNt(LINK->Betrachtet, Inab[V0])) {
	      if (InNt(LINK->AufrufMenge, Inab[V0]))
		HinzuNt(LINK->AbbruchMenge, Inab[V0]);
	      if (SymTab[V0]->UU.U2.Epsilon)
		HinzuT(Erg, (long)Epsi);
	      else
		Fertig = true;
	    } else
	      BerechneNtanf(V0, Erg, LINK);
	  }
	  if (I < L) {
	    if (InT(Erg, (long)Epsi))
	      StreicheT(Erg, Epsi);
	    else
	      Fertig = true;
	  } else
	    Fertig = true;
	  VereinigeT(Zw, Erg);
	}
	I++;
      }  /* von while */

    }
    P = Ls[P - 1]->Naechste;
  }  /* von while */
  StreicheNt(LINK->AbbruchMenge, Inab[Sym]);
  if (LeerNt(LINK->AbbruchMenge)) {
    LINK->Vorab[Inab[Sym] - 1] = true;
    memcpy(Ntanf[Inab[Sym] - 1], Zw, sizeof(TTMenge));
  }
  StreicheNt(LINK->AufrufMenge, Inab[Sym]);




}  /* BERECHNE_NTANF */

/**********************************************************************/
/*                                                                    */
/*               Berechnung der FIRST_1 - Mengen                      */
/*                                                                    */
/**********************************************************************/

Local Void BerechneFirst(LINK)
struct LOC_HuellInv *LINK;
{  /* BERECHNE_FIRST */
  /*  */
  /* */
  /*  */
  struct LOC_BerechneFirst V;
  /* Enthaelt die Zeichen, die im momentanen Aufruf schon      */
  /* betrachtet wurden                                         */
  short N, FORLIM;



  V.LINK = LINK;
  FORLIM = AktMaxNterm;
  for (N = 0; N < FORLIM; N++)
    V.Vorab[N] = false;


  FORLIM = AktMaxNterm;
  /* Berechnung von NTANF */

  for (N = 0; N < FORLIM; N++) {
    if (!V.Vorab[N]) {
      memcpy(V.AufrufMenge, LeerNtMenge, sizeof(TNtMenge));
      memcpy(V.AbbruchMenge, LeerNtMenge, sizeof(TNtMenge));
      memcpy(V.Betrachtet, LeerNtMenge, sizeof(TNtMenge));
      BerechneNtanf(Ntab[N], Ntanf[N], &V);
      V.Vorab[N] = true;
    }
  }



  Zeit = cputime();


  EaZeit += cputime() - Zeit;

}  /* von BERECHNE_FIRST */

/* Local variables for ErzeugeVererber: */
struct LOC_ErzeugeVererber {
  struct LOC_HuellInv *LINK;
} ;

/* Die Datenstruktur dient nur dem schnellen Aufbau von RK_-  */
/* SCHLANGE. In der momentanen Einstellung von ZEDER benoetigt*/
/* sie 32 kByte                                               */

Local TNtKette *GibNtElem(Nt, Index)
short Nt;
short Index;
{
  /* Die Funktion haengt ein neues Element in die */
  /* SYM_TAB - Verkettung ein                     */
  TNtKette *NtObjekt;

  NtObjekt = (TNtKette *)Malloc(sizeof(TNtKette));
  NtObjekt->N = Nt;
  NtObjekt->NextN = SymTab[Index]->UU.U2.RkSchlange;
  return NtObjekt;
}


Local Void RkVorab(LINK)
struct LOC_ErzeugeVererber *LINK;
{  /* RK_VORAB */
  /*                                                                  */
  /* External : SYM_TAB , RS , RS_FELD                                */
  /* Wirkung  : Es wird folgende Verkettung aufgebaut :               */
  /*            Zu jedem NT N sind alle NT's X verkettet mit          */
  /*                                        +                         */
  /*                                      X===>N                      */
  /*                                          R                       */
  /*                  Diese Verkettung steht in SYM_TAB ^.RK_SCHLANGE */
  /*                                                                  */
  /* Theorie dazu : [Kl84] ,Transitive Vererbung                      */
  /*                                                                  */
  long I, L;
  boolean Fertig;
  short V0, V1;
  short P;
  TNtKette *NtLaeufer, *Nt1Laeufer;
  TNtMenge LokaleHilfe[Maxnterm];
  long FORLIM;
  short FORLIM1;

  FORLIM = AktMaxNterm;
  /* Initialisierung */
  for (I = 0; I < FORLIM; I++)
    memcpy(LokaleHilfe[I], LeerNtMenge, sizeof(TNtMenge));

  FORLIM1 = AktMaxProdNr;
  /* Berechnung der direkten Vererber */
  for (P = 0; P < FORLIM1; P++) {
    if (Rs[P].RsLaenge != 0) {   /* Keine Epsilon - Produktion */
      L = Rs[P].RsLaenge;
      V0 = RsFeld[Rs[P].RsAnfang - 1];
      if (((1L << ((long)SymTab[V0]->SymArt)) &
	   ((1L << ((long)Nt)) | (1L << ((long)HilfNt)))) != 0) {
	if (L == 1)
	  I = L + 1;
	else {
	  I = 2;
	  Fertig = false;


	  /* Diese while-Schleife ist ein Durchgang durch */
	  /* die rechte Seite der Produktion P            */
	  while (I <= L && !Fertig) {
	    V1 = RsFeld[Rs[P].RsAnfang + I - 2];
	    if (SymTab[V1]->SymArt == Term) {
	      Fertig = true;
	      I = 0;   /* Somit ist I <> L + 1 und Eintrag */
	      /* in RK_SCHLANGE wird verhindert   */
	    } else if (!SymTab[V1]->UU.U2.Epsilon) {
	      Fertig = true;
	      I = 0;   /* Somit ist I <> L + 1 und Eintrag */
	      /* in RK_SCHLANGE wird verhindert   */
	    }
	    I++;
	  }  /* von while */

	}  /* von else */

	/* Eintragen der direkten Vererber */
	if (I == L + 1) {
	  if (!InNt(LokaleHilfe[Inab[V0] - 1], Inab[Ls[P]->SymNr])) {
	    HinzuNt(LokaleHilfe[Inab[V0] - 1], Inab[Ls[P]->SymNr]);
	    SymTab[V0]->UU.U2.RkSchlange = GibNtElem(Inab[Ls[P]->SymNr], V0);
	  }
	}
      }  /* von then */
      else if (SymTab[V0]->SymArt == SymStruk)
	Fehler(true, 4L, (long)V0, 0L, 0L);
    }  /* von then */
  }  /* von for */


  /* Berechnung der transitiven Huelle der direkten Vererber */
  Fertig = false;
  while (!Fertig) {
    Fertig = true;
    FORLIM = AktMaxNterm;
    for (I = 0; I < FORLIM; I++) {
      NtLaeufer = SymTab[Ntab[I]]->UU.U2.RkSchlange;
      while (NtLaeufer != NULL) {
	Nt1Laeufer = SymTab[Ntab[NtLaeufer->N - 1]]->UU.U2.RkSchlange;
	while (Nt1Laeufer != NULL) {
	  if (!InNt(LokaleHilfe[I], Nt1Laeufer->N)) {
	    HinzuNt(LokaleHilfe[I], Nt1Laeufer->N);
	    SymTab[Ntab[I]]->UU.U2.RkSchlange = GibNtElem(Nt1Laeufer->N, Ntab[I]);
	    Fertig = false;
	  }
	  Nt1Laeufer = Nt1Laeufer->NextN;
	}
	NtLaeufer = NtLaeufer->NextN;
      }
    }
  }



  /* nichts ! */
}  /* von RK_VORAB */





/**********************************************************************/
/*                                                                    */
/*            Berechnung der transitiven Vererber                     */
/*                                                                    */
/**********************************************************************/

Local Void ErzeugeVererber(LINK)
struct LOC_HuellInv *LINK;
{  /* ERZEUGE_VERERBER */
  /* */
  /* */
  /* */
  struct LOC_ErzeugeVererber V;




  V.LINK = LINK;
  RkVorab(&V);



}  /* ERZEUGE_VERERBER */

/* Local variables for ErzeugeHuellen: */
struct LOC_ErzeugeHuellen {
  struct LOC_HuellInv *LINK;
  short N;
  TNtMenge Betrachtet;
  /* Enthaelt die Zeichen, die im momentanen Aufruf */
  /* schon betrachtet wurden                        */
  TNtMenge AbbruchMenge;
  /* Solange Sie Zeichen enthaelt, kann kein Eintrag */
  /* in NTH erfolgen                                 */
  TNtMenge AufrufMenge;
  /* Enthaelt alle Aufruf-Zeichen der umgebenden     */
  /* Aufrufe                                         */
  boolean Vorab[Maxnterm];
  /* VORAB (X) = true zeigt an, ob die Vorabberechnungen fuer X */
  /* schon gemacht worden sind                                  */
  boolean Innen;
} ;



Local Void BerechneNth(NtNr, Pegel, LINK)
short NtNr;
short *Pegel;
struct LOC_ErzeugeHuellen *LINK;
{

  /*  External : VORAB , HUELL_FELD , N                          */
  /* Parameter : PEGEL  ist der hoechste besetzte Pegel in       */
  /*             HUELL_FELD                                      */
  /* Wirkung   : Es werden fuer NT und fuer alle innerhalb des   */
  /*             Aufrufs erreichten Nichtterminale NTH [NT_NR]   */
  /*             gebildet , sofern moeglich, und in HUELL_FELD   */
  /*             eingetragen.
  (*                                                             */
  short P;
  short LsV, V0;






  HinzuNt(LINK->AufrufMenge, NtNr);
  P = SymTab[Ntab[NtNr - 1]]->UU.U2.LSeite;
  LsV = Ls[P - 1]->SymNr;
  if (!LINK->Vorab[NtNr - 1])
    Nth[NtNr - 1].HuellAnf = *Pegel + 1;
  while (P != 0) {
    /* Eintrag in HUELL_FELD */
    if (*Pegel + 1 >= MaxHuellLaenge)
      Fehler(true, 18L, 0L, 0L, 0L);
    else
      (*Pegel)++;
    HuellFeld[*Pegel - 1] = P;
    if (Rs[P - 1].RsLaenge != 0) {   /* Keine Epsilon - Produktion */
      V0 = RsFeld[Rs[P - 1].RsAnfang - 1];
      if (((1L << ((long)SymTab[V0]->SymArt)) &
	   ((1L << ((long)Nt)) | (1L << ((long)HilfNt)))) != 0) {
	if (InNt(LINK->Betrachtet, Inab[V0])) {
	  if (InNt(LINK->AufrufMenge, Inab[V0]))
	    HinzuNt(LINK->AbbruchMenge, Inab[V0]);
	  else
	    LINK->Innen = false;
	} else {
	  HinzuNt(LINK->Betrachtet, Inab[V0]);
	  BerechneNth(Inab[V0], Pegel, LINK);
	}
      }
    }
    P = Ls[P - 1]->Naechste;
  }  /* von while */


  if (InNt(LINK->AbbruchMenge, Inab[LsV]))
    StreicheNt(LINK->AbbruchMenge, Inab[LsV]);
  if (!LINK->Vorab[NtNr - 1]) {   /* NTH [NT_NR] hat noch keinen Eintrag */
    if ((LeerNt(LINK->AbbruchMenge) && LINK->Innen) ||
	NtNr == LINK->N) {
      /* Der aussere Aufruf ist auf jeden Fall vollst. berechnet */
      /* Eintrag in NTH */
      Nth[NtNr - 1].HuellEnde = *Pegel;
      LINK->Vorab[NtNr - 1] = true;
    }
  }  /* not VORAB... */
  StreicheNt(LINK->AufrufMenge, NtNr);


}  /* von BERECHNE_NTH */


/**********************************************************************/
/*                                                                    */
/*            Berechnung der Nicht-Terminal-Huellen                   */
/*                                                                    */
/**********************************************************************/

Local Void ErzeugeHuellen(LINK)
struct LOC_HuellInv *LINK;
{  /* ERZEUGE_HUELLEN */
  /* */
  /* */
  /* */
  struct LOC_ErzeugeHuellen V;
  short Pegel;
  /* INNEN=true <=> Die vollstaendige NTH-Berechnung innerer */
  /*                Aufrufe wird festgehalten                */
  /* INNEN=false<=> ...wird nicht festgehalten. In diesen    */
  /*                Faellen waere die Berechnung der Verwal- */
  /*                tungsinformation groesser als die noch-  */
  /*                malige spaetere Berechnung der inneren   */
  /*                Aufrufe                                  */
  short FORLIM;




  V.LINK = LINK;
  FORLIM = AktMaxNterm;
  /* Initialisierung */

  for (V.N = 1; V.N <= FORLIM; V.N++)
    V.Vorab[V.N - 1] = false;


  /* Berechnung von NTH */
  Pegel = 0;
  FORLIM = AktMaxNterm;
  for (V.N = 1; V.N <= FORLIM; V.N++) {
    if (!V.Vorab[V.N - 1]) {
      V.Innen = true;
      memcpy(V.AufrufMenge, LeerNtMenge, sizeof(TNtMenge));
      memcpy(V.AbbruchMenge, LeerNtMenge, sizeof(TNtMenge));
      memcpy(V.Betrachtet, LeerNtMenge, sizeof(TNtMenge));
      HinzuNt(V.Betrachtet, V.N);
      BerechneNth(V.N, &Pegel, &V);
    }
  }



}  /* von ERZEUGE_HUELLEN */



/********************************************************************/
/*                                                                  */
/*     Invarianten der Huellenbildung                               */
/*                                                                  */
/********************************************************************/

Local Void HuellInv(LINK)
struct LOC_Analyse *LINK;
{  /* HUELL_INV */
  /*                                                                  */
  /* In dieser Prozedur werden fuer jedes Nicht-Terminal X die        */
  /* Funktionen NTH (X) (siehe [ DE77 ] )                             */
  /*    und     NT_ANF (X) = FIRST_1 (X) = Anf_1 (X)                  */
  /* nach [Goos83] S519 berechnet.                                    */
  /* Ausserdem werden Identitaets-Produktionen, Nichtterminal-Zyklen  */
  /* und mehrdeutige Kettenableitungen erkannt und gemeldet.          */
  /*                                                                  */
  /* Modulaufbau:                                                     */
  /*              procedure HUELL_INV                                 */
  /*                procedure ZYKLUS_TEST                             */
  /*                procedure KETT_ZEICH                              */
  /*                procedure BERECHNE_FIRST                          */
  /*                procedure ERZEUGE_VERERBER                        */
  /*                procedure ERZEUGE_HUELLEN                         */
  /*                                                                  */
  struct LOC_HuellInv V;
  long I;
  short P;
  short Sym;
  boolean Fertig;
  short Zeiger[Maxnterm];
  long FORLIM;










  V.LINK = LINK;
  FORLIM = AktMaxNterm;
  /* Berechnung der Ketten-Prod.-Verweis-Kette */

  for (I = 0; I < FORLIM; I++) {
    Sym = Ntab[I];
    P = SymTab[Sym]->UU.U2.LSeite;
    Fertig = false;
    while (P != 0 && !Fertig) {
      if (InP(KettPMenge, P))
	Fertig = true;
      else
	P = Ls[P - 1]->Naechste;
    }
    SymTab[Sym]->UU.U2.KettProd = P;
    Zeiger[I] = P;
    if (Fertig) {
      P = Ls[P - 1]->Naechste;
      while (P != 0) {
	if (InP(KettPMenge, P)) {
	  Ls[Zeiger[I] - 1]->KettProd = P;
	  Zeiger[I] = P;
	}
	P = Ls[P - 1]->Naechste;
      }
    }
  }

  FORLIM = AktMaxNterm;
  /* Berechnung von Zyklen und Mehrdeutigkeiten */

  for (I = 0; I < FORLIM; I++)
    V.Vorab[I] = false;

  FORLIM = AktMaxNterm;
  for (I = 0; I < FORLIM; I++) {
    if (!V.Vorab[I]) {
      memcpy(V.Betrachtet, LeerSymMenge, sizeof(SymMenge));
      HinzuSym(V.Betrachtet, Ntab[I]);
      ZyklusTest(&Ntab[I], &V);
      V.Vorab[I] = true;
    }
  }



  /* Berechnung von KETTEN_ZEICHEN */

  KettZeich(&V);

  /* Berechnung von NTANF */

  BerechneFirst(&V);


  /* Berechnung der Rechtskontext-Vererber */

  ErzeugeVererber(&V);

  /* Berechnung von NTH */

  ErzeugeHuellen(&V);


}  /* von HUELL_INV */

/* Local variables for BildeZuTab: */
struct LOC_BildeZuTab {
  struct LOC_Analyse *LINK;
  /* Listen zur Aufsammlung nicht mehr benoetigter dynam. Objekte */
  TItemTyp *FreiItems;
  TNeuUeberElem *FreiNeus;
  TSymbole *FreiSym;
  TNeuUeberElem *NeuUe;
  struct {
    long UnterAnf, UnterEnde;
  } NeuUnter;
  /* Der integer - Subrange UNTER_ANF..UNTER_ENDE bedeutet die */
  /* Zustaende, die zum ersten Mal zu untersuchen sind         */

  struct {
    short Pegel;
    short Mark[MaxUnter];
  } AltUnter;
} ;

/* MARK enthaelt Zustaende, die zum mehrten Male zu untersuchen */
/* sind. PEGEL zeigt auf den groessten besetzten Index          */


/**********************************************************************/
/*                                                                    */
/*            Operationen zur Freispeicher-Verwaltung                 */
/*                                                                    */
/**********************************************************************/


Local TItemTyp *BeschaffeItem(P1, P2, B, N, LINK)
short P1;
int P2;
TItemTyp *B, *N;
struct LOC_BildeZuTab *LINK;
{
  /* Wirkung : Ein Objekt vom Typ ITEM_TYP wird angelegt     */
  /* External: FREI_LISTE                                    */
  TItemTyp *It;

  if (LINK->FreiItems != NULL) {
    It = LINK->FreiItems;
    LINK->FreiItems = LINK->FreiItems->Naechstes;
  } else {
    It = (TItemTyp *)Malloc(sizeof(TItemTyp));
    It->RkMenge = NULL;
  }
  It->PNr = P1;
  It->Punkt = P2;
  It->Basis = B;
  It->Naechstes = N;
  return It;
}

Local TZustandsTyp *BeschaffeZustand(IListe, Z)
TItemTyp *IListe;
short Z;
{
  /* Ein Objekt vom Typ ZUSTANDS_TYP wird angelegt             */
  /* Besonderheit: ZUSTAND^.VORGAENGER ist nicht initialisiert */
  TZustandsTyp *Zustand;
  TVorListe *Vl;

  Zustand = (TZustandsTyp *)Malloc(sizeof(TZustandsTyp));
  Vl = (TVorListe *)Malloc(sizeof(TVorListe));
  Zustand->IListe = IListe;
  Zustand->Naechster = Z;
  Zustand->Vorgaenger = Vl;
  return Zustand;
}

/* Local variables for BildeHuelle: */
struct LOC_BildeHuelle {
  struct LOC_BildeZuTab *LINK;
  TTMenge Folge[Maxnterm];
  TSymbole *RelKette;   /* Enthaelt NT-Zeichen */
  TSymbole *RelLaeufer;
} ;

Local Void Anfang(P, Pos, Anf, AnfErg, LINK)
short P;
long Pos;
long *Anf, *AnfErg;
struct LOC_BildeHuelle *LINK;
{
  /* 0..MAX_RS_LAENGE+1 */
  /*                                                                */
  /* Parameter: POS gibt die Position des Punktes im Item an        */
  /*            ANF ist die RK-Menge des betrachteten Items         */
  /*            ANFERG liefert das Ergebnis                         */
  /*   ANFANG ( [X->a.Yv;U] ) = ANF (vU)                            */
  /*                                                                */
  /* Theorie:  [Kl84, Kapitel 4.2.4]                                */
  /*                                                                */
  /* Vorsicht: Unterschied zw. Epsilon und # !! Hat die zu betrach- */
  /*           tende Situation keinen Rechtskontext, U=0 , so       */
  /*           kommt auch kein Zeichen # zu ANFANG dazu             */
  /*                                                                */
  /* Beim Aufruf: [A->x.Yz;U] mit POS + 1 aufrufen                  */
  /*                                                                */
  TTMenge Hanf;
  short V0;


  if (Pos > Rs[P - 1].RsLaenge) {
    memcpy(AnfErg, Anf, sizeof(TTMenge));
    return;
  }

  memcpy(AnfErg, LeerTMenge, sizeof(TTMenge));
  V0 = RsFeld[Rs[P - 1].RsAnfang + Pos - 2];
  switch (SymTab[V0]->SymArt) {

  case Term:
    HinzuT(AnfErg, (long)Inab[V0]);
    break;

  case Nt:
  case HilfNt:
    memcpy(AnfErg, Ntanf[Inab[V0] - 1], sizeof(TTMenge));
    if (InT(AnfErg, (long)Epsi)) {   /*EPSILON*/
      StreicheT(AnfErg, Epsi);
      Anfang(P, Pos + 1, Anf, Hanf, LINK);
      VereinigeT(AnfErg, Hanf);
    }
    break;
  case SymStruk: /* Unmoeglich */
    break;
  }/* von case */

  /* von else */
}  /* VOM ANFANG */

/* Local variables for HuelleNull: */
struct LOC_HuelleNull {
  struct LOC_BildeHuelle *LINK;
  TNtMenge Eingehaengt;
} ;


Local TItemTyp *HaengeNthEin(ILaeufer, Nt, LINK)
TItemTyp *ILaeufer;
short Nt;
struct LOC_HuelleNull *LINK;
{
  /* Die Funktion besetzt ein neues Element (Liste!) vom Typ ITEM_TYP */
  /* und haengt es in die Kette ein modulo der Listen-Elemente, die   */
  /* bereits bei vorher betrachteten Basis-Items eingehaengt wurden   */
  /* External : EINGEHAENGT , FREI_ITEMS                              */
  TItemTyp *Result, *It;
  long I;
  short P;
  TNtMenge LokEingehaengt;
  long FORLIM;

  /* LOKales_EINGEHAENGT hat die gleiche Funktion wie globales */
  /* EINGEHAENGT, wird aber benoetigt, um Konflikte in der     */
  /* Huellenberechnung zu vermeiden                            */

  memcpy(LokEingehaengt, LeerNtMenge,
	 sizeof(TNtMenge));
  FORLIM = Nth[Nt - 1].HuellAnf - 1;
  for (I = Nth[Nt - 1].HuellEnde - 1; I >= FORLIM; I--) {
    P = HuellFeld[I];
    if (!InNt(LINK->Eingehaengt, Inab[Ls[P - 1]->SymNr]))
    {   /* P wurde schon eingehaengt */
      HinzuNt(LokEingehaengt, Inab[Ls[P - 1]->SymNr]);
      if (!((OhneKettProd || TeilKettProd) & InP( KettPMenge, HuellFeld[I])))
      {   /* kein Eintrag */
	It = BeschaffeItem(HuellFeld[I], 1,
			(TItemTyp *)0, ILaeufer->Naechstes, LINK->LINK->LINK);
	ILaeufer->Naechstes = It;
      }
    }
  }  /* for */
  Result = ILaeufer;
  VereinigeNt(LINK->Eingehaengt, LokEingehaengt);
  return Result;
}  /* von HAENGE_NTH_EIN */

Local TSymbole *GibKettElem(Nt, LINK)
short Nt;
struct LOC_HuelleNull *LINK;
{
  /* Haengt ein Element in REL_KETTE EIN */
  TSymbole *S;

  if (LINK->LINK->LINK->FreiSym != NULL) {
    S = LINK->LINK->LINK->FreiSym;
    LINK->LINK->LINK->FreiSym = LINK->LINK->LINK->FreiSym->Naechstes;
  } else
    S = (TSymbole *)Malloc(sizeof(TSymbole));
  S->ESym = Nt;
  S->Naechstes = LINK->LINK->RelKette;
  return S;
}


Local Void HuelleNull(Neu, IListe, RelZeich, LINK)
boolean Neu;
TItemTyp **IListe;
long *RelZeich;
struct LOC_BildeHuelle *LINK;
{  /* HUELLE_NULL */
  /*                                                                  */
  /* Parameter : Nach der Prozedur steht in I_LISTE die komplette     */
  /*             Item-Liste ( des Zustands ) in definierter Reihen-   */
  /*             folge.                                               */
  /*             REL_ZEICH enthaelt alle Nichtterminale der rechten   */
  /*             Seiten, die nach einem Punkt stehen                  */
  /*                                                                  */
  /* Wirkung : Falls NEU = true, haengt die Prozedur an Basis-Items,  */
  /*           bei denen nach dem Punkt ein Nichtterminal X steht, die*/
  /*           Huellen-Items ein und besetzt sie mit NTH [X] ( nur    */
  /*           beim ersten Auftreten von X !).                        */
  /*           Falls NEU = false, existieren die Huellen-Items schon. */
  /*                                                                  */
  /*           Theorie dazu: [Kl84]                                   */
  /*                                                                  */
  /*           In beiden Faellen wird ausserdem die Kontext_0-Menge   */
  /*           gebildet fuer alle in Frage kommenden Nichtterminale   */
  /*           Diese stehen in REL_ZEICH bzw. in REL_KETTE            */
  /*                                                                  */
  struct LOC_HuelleNull V;
  TItemTyp *ItemLaeufer;
  /* Enthaelt die Zeichen, fuer die NTH schon eingehaengt wurde,  */
  /* sowie alle Zeichen, die waehrend des Einhaengens auf der lin-*/
  /* ken Seite einer Produktion vorkommen                         */
  TTMenge FolgeNull;
  /* beinhaltet die Kontext_0-Zeichen aus [Kl84,Kap. 4.2.4]       */
  short V0;
  TItemTyp *WITH;




  V.LINK = LINK;
  /* Initialisierung */

  memcpy(V.Eingehaengt, LeerNtMenge, sizeof(TNtMenge));
  ItemLaeufer = *IListe;
  memcpy(FolgeNull, LeerTMenge, sizeof(TTMenge));

  /*  Ein Durchlauf durch die I_LISTE */

  while (ItemLaeufer != NULL) {   /* von while */
    WITH = ItemLaeufer;
    if (WITH->Punkt > 1 || WITH->PNr == StartProduktion) {
	  /* Basis - Item */
	    if (WITH->Punkt <= Rs[WITH->PNr - 1].RsLaenge) {
	V0 = RsFeld[Rs[WITH->PNr - 1].RsAnfang + WITH->Punkt - 2];
	switch (SymTab[V0]->SymArt) {

	case Nt:
	case HilfNt:
	  if (Neu) {
	    /* Hier werden die Kerne der Huellen in die */
	    /* Verkettung eingehaengt                   */
	    if (!InNt(V.Eingehaengt, Inab[V0]))
	      ItemLaeufer = HaengeNthEin(ItemLaeufer, Inab[V0], &V);
	    /* NTH [V0] wurde schon an ein Basis-Item angehaengt */
	  }

	  Anfang(WITH->PNr, (long)(WITH->Punkt + 1), WITH->RkMenge, FolgeNull, LINK);
	  VereinigeT(LINK->Folge[Inab[V0] - 1], FolgeNull);
	  break;

	case Term:
	case SymStruk:
	  /* blank case */
	  break;
	}/* von case */

      }
    } else {
      /* ITEM ist ein Huellen-Item */
      if (Rs[WITH->PNr - 1].RsLaenge != 0) {
	    /* Keine Epsilon - Produktion */
	      if (WITH->Punkt <= Rs[WITH->PNr - 1].RsLaenge) {
	  V0 = RsFeld[Rs[WITH->PNr - 1].RsAnfang + WITH->Punkt - 2];

	  switch (SymTab[V0]->SymArt) {

	  case Nt:
	  case HilfNt:
	    Anfang(WITH->PNr, (long)(WITH->Punkt + 1), LeerTMenge,
		   FolgeNull, LINK);
	    if (InT(FolgeNull, (long)Epsi))
	      StreicheT(FolgeNull, Epsi);
	    VereinigeT(LINK->Folge[Inab[V0] - 1], FolgeNull);
	    break;

	  case Term:
	  case SymStruk:
	    /* blank case */
	    break;
	  }/* von case */
	}
      }
      if (!InNt(RelZeich, Inab[Ls[WITH->PNr - 1]->SymNr])) {
	LINK->RelKette = GibKettElem(Inab[Ls[WITH->PNr - 1]->SymNr], &V);
	HinzuNt(RelZeich, Inab[Ls[WITH->PNr - 1]->SymNr]);
      }
    }  /* von else */
    ItemLaeufer = ItemLaeufer->Naechstes;
  }


  /* Nichts */
  /* nichts */
}  /* HUELLE_NULL */


Local Void HuelleN(IListe, LINK)
TItemTyp **IListe;
struct LOC_BildeHuelle *LINK;
{  /* HUELLE_N */
  /*                                                                  */
  /* Wirkung : Fuer jedes Zeichen aus REL_ZEICH werden die Folge_n-   */
  /*           Mengen berechnet und anschliessend an die entsprechen- */
  /*           den Huellen-Items als Rechtskontext gehaengt.          */
  /*           Nach Ende der Proz. ist die Huellenbildung von I_LISTE */
  /*           beendet.                                               */
  /* External: FOLGE                                                  */
  /*                                                                  */
  short N;
  TItemTyp *ItemLaeufer;
  TNtKette *NtLaeufer;
  TItemTyp *WITH;



  /* Die folgende Schleife bildet bildet fuer alle Y aus */
  /* REL_ZEICH die Menge Folge_N (Y)                     */

  LINK->RelLaeufer = LINK->RelKette;
  while (LINK->RelLaeufer != NULL) {
    N = LINK->RelLaeufer->ESym;
    NtLaeufer = SymTab[Ntab[N - 1]]->UU.U2.RkSchlange;
    while (NtLaeufer != NULL) {
      /* Die Folge-Menge wird erweitert*/
      VereinigeT(LINK->Folge[N - 1], LINK->Folge[NtLaeufer->N - 1]);
      NtLaeufer = NtLaeufer->NextN;
    }  /* von while */
    LINK->RelLaeufer = LINK->RelLaeufer->Naechstes;
  }  /* von then bzw. while */

  ItemLaeufer = *IListe;

  /* Die Rechtskontexte werden in die Items eingefuegt */

  while (ItemLaeufer != NULL) {
    WITH = ItemLaeufer;
    if (WITH->Punkt <= 1 && WITH->PNr != StartProduktion)   /* Basis_Item */
      ItemLaeufer->RkMenge = HashIn(
	  LINK->Folge[Inab[Ls[ItemLaeufer->PNr - 1]->SymNr] - 1]);
    /* Nichts */
    ItemLaeufer = ItemLaeufer->Naechstes;
  }
}  /* HUELLE_N */






Local Void BildeHuelle(IListe, Neu, LINK)
TItemTyp **IListe;
boolean Neu;
struct LOC_BildeZuTab *LINK;
{  /* BILDE_HUELLE */
  /*                                                                  */
  /* External : NTH                                                   */
  /*                                                                  */
  /* Wirkung  : Falls NEU = true, enthaelt I_LISTE nur Basis-Items.   */
  /*            Es werden dann die Huellen gebildet, in kanonischer   */
  /*            Ordnung in I_LISTE eingehaengt und die Rechtskontext- */
  /*            Mengen bestimmt.                                      */
  /*            Falls NEU = false, sind die Huellen bereits einge-    */
  /*            haengt. Es wird dann nur die RK-Berechnung gemacht.   */
  /*                                                                  */
  /* Modulaufbau :                                                    */
  /*              procedure BILDE_HUELLE                              */
  /*                 procedure ANFANG                                 */
  /*                 procedure HUELLE_NULL                            */
  /*                 procedure HUELLE_N                               */
  /*                                                                  */
  struct LOC_BildeHuelle V;
  TNtMenge RelZeich;
  /* Enthaelt alle Zeichen Y, fuer die FOLGE_NULL [Y] gebildet    */
  /* wurde                                                        */
  boolean Weiter;
  short N, FORLIM;





  V.LINK = LINK;
  /* Initialisierung */

  memcpy(RelZeich, LeerNtMenge, sizeof(TNtMenge));
  V.RelKette = NULL;
  FORLIM = AktMaxNterm;
  for (N = 0; N < FORLIM; N++)
    memcpy(V.Folge[N], LeerTMenge, sizeof(TTMenge));

  /* Aufruf */

  HuelleNull(Neu, IListe, RelZeich, &V);


  HuelleN(IListe, &V);
  /* Speicherbereinigung */
  V.RelLaeufer = V.RelKette;
  Weiter = true;
  while (V.RelLaeufer != NULL && Weiter) {
    if (V.RelLaeufer->Naechstes != NULL)
      V.RelLaeufer = V.RelLaeufer->Naechstes;
    else
      Weiter = false;
  }
  if (V.RelLaeufer != NULL)
    V.RelLaeufer = LINK->FreiSym;
  LINK->FreiSym = V.RelKette;




}  /* BILDE_HUELLE */

/* Local variables for BearbeiteZustand: */
struct LOC_BearbeiteZustand {
  struct LOC_BildeZuTab *LINK;
  TItemTyp *ItemLaeufer;
  SymMenge UeberZeichen;
} ;

/**********************************************************************/
/*                                                                    */
/*         Operationen zum Aufbau der neuen Uebergaenge               */
/*                                                                    */
/**********************************************************************/

Local Void BildeItem(Item, It, LINK)
TItemTyp **Item, **It;
struct LOC_BearbeiteZustand *LINK;
{
  /* Die Prozedur beschafft sich entweder ein Item aus der */
  /* Freiliste oder legt eines auf der Halde an.           */
  /* External : FREI_ITEMS                                 */
  *Item = BeschaffeItem((*It)->PNr, (*It)->Punkt + 1, (TItemTyp *)0, (TItemTyp *)0, LINK->LINK);
  (*Item)->RkMenge = (*It)->RkMenge;
}

Local Void Bilde(V0, It, LINK)
short *V0;
TItemTyp *It;
struct LOC_BearbeiteZustand *LINK;
{
  TNeuUeberElem *NeuElem;
  TItemTyp *Item;

  if (LINK->LINK->FreiNeus != NULL) {
    NeuElem = LINK->LINK->FreiNeus;
    LINK->LINK->FreiNeus = LINK->LINK->FreiNeus->Naechste;
  } else
    NeuElem = (TNeuUeberElem *)Malloc(sizeof(TNeuUeberElem));
  NeuElem->A = *V0;
  BildeItem(&Item, &It, LINK);
  NeuElem->I = Item;
  NeuElem->LetztesI = Item;
  NeuElem->Naechste = LINK->LINK->NeuUe;
  LINK->LINK->NeuUe = NeuElem;
}

Local Void HaengeAn(V0, It, LINK)
short *V0;
TItemTyp *It;
struct LOC_BearbeiteZustand *LINK;
{
  /* External : NEU_UE*/
  TItemTyp *Item;
  TNeuUeberElem *NeuUeLaeufer;

  NeuUeLaeufer = LINK->LINK->NeuUe;
  while (NeuUeLaeufer->A != *V0)
    NeuUeLaeufer = NeuUeLaeufer->Naechste;
  BildeItem(&Item, &It, LINK);
  NeuUeLaeufer->LetztesI->Naechstes = Item;
  NeuUeLaeufer->LetztesI->Basis = Item;
  NeuUeLaeufer->LetztesI = Item;
}


Local Void ErzeugeNeuUe(Sym, LINK)
short *Sym;
struct LOC_BearbeiteZustand *LINK;
{
  /* External  : UEBER_ZEICHEN , ITEM_LAEUFER                   */
  /* Wirkung   : Hier wird die Uebergangsliste NEU_UEerzeugt,  */
  /*             die zum Zustand Z (External) alle Uebergaenge  */
  /*             enthaelt                                       */
  short P;

  if (!InSym(OptSymMenge, *Sym)) {
    if (InSym(LINK->UeberZeichen, *Sym))
      HaengeAn(Sym, LINK->ItemLaeufer, LINK);
    else {
      HinzuSym(LINK->UeberZeichen, *Sym);
      Bilde(Sym, LINK->ItemLaeufer, LINK);
    }
  }
  if (((1L << ((long)SymTab[*Sym]->SymArt)) &
       ((1L << ((long)Nt)) | (1L << ((long)HilfNt)))) == 0)
    return;
  P = SymTab[*Sym]->UU.U2.KettProd;
  while (P != 0) {
    ErzeugeNeuUe(&RsFeld[Rs[P - 1].RsAnfang - 1], LINK);
    P = Ls[P - 1]->KettProd;
  }
}  /* von ERZEUGE_NEU_UE */

/* Local variables for UntersucheUebergang: */
struct LOC_UntersucheUebergang {
  struct LOC_BearbeiteZustand *LINK;
} ;

/**********************************************************************/
/*                                                                    */
/*             Operationen auf der Zustandsliste Q                    */
/*                                                                    */
/**********************************************************************/

Local Void TrageEinZ(ItListe, Z, Amz, LINK)
TItemTyp *ItListe;
short Z;
short *Amz;
struct LOC_UntersucheUebergang *LINK;
{
  /* Wirkung  : Die Prozedur traegt einen Zustand in Q ein */
  /*            und aktualisiert AKT_MAX_ZUSTAND (AMZ)     */
  /* External : Zustands-Liste Q                           */
  TZustandsTyp *Zustand;
  short V0;

  (*Amz)++;
  if (*Amz == Maxzustand) {
    Fehler(true, 5L, 0L, 0L, 0L);
    exit(1);
  }
  V0 = RsFeld[Rs[ItListe->PNr - 1].RsAnfang + ItListe->Punkt - 3];


  Zustand = BeschaffeZustand(ItListe, SymTab[V0]->Erzu);
  SymTab[V0]->Erzu = *Amz;
  Zustand->Vorgaenger->NextVor = NULL;
  Zustand->Vorgaenger->Vor = Z;
  Q[*Amz - 1] = Zustand;
}  /* von TRAGE_EIN_Z */


/**********************************************************************/
/*                                                                    */
/*         Operationen auf der Uebergangs - Tabelle                   */
/*                                                                    */
/**********************************************************************/


Local Void TrageEinUe(Z, A, Z1, P, LINK)
short *Z;
short A;
short Z1;
short P;
struct LOC_UntersucheUebergang *LINK;
{
  /* Die Prozedur traegt einen oder mehrere Uebergaenge in die */
  /* Uebergangs-Tabelle (UE_TABELLE) ein;                      */
  TUeberElem *UeElem;

  UeElem = (TUeberElem *)Malloc(sizeof(TUeberElem));
  UeElem->Es = A;
  UeElem->Z = Z1;
  UeElem->P = P;
  /* Falls Z1 = 0, ist P redundant. Es waere schoen, dann P = 0 */
  /* zu setzten, kostet aber Abfrage-Zeit                       */
  UeElem->NextEs = UeTabelle[*Z - 1];
  UeTabelle[*Z - 1] = UeElem;
}  /* TRAGE_EIN_UE */

/**********************************************************************/
/*                                                                    */
/*         Verwaltung schon betrachteter Zustaende                    */
/*                                                                    */
/**********************************************************************/


Local Void HinzuAlt(Z, LINK)
short *Z;
struct LOC_UntersucheUebergang *LINK;
{
  /* Zustand Z wird in ALT_UNTER eingetragen, und spaeter also noch */
  /* einmal betrachtet                                              */
  /* Es ist bisher moeglich, dass Z mehrmals in MARK steht!         */
  /*   Abhilfe : Zusaetzliche Buchfuehrung mit einer Menge          */
  /* External  : ALT_UNTER                                          */
  short Z1;

  Z1 = *Z;
  if (LINK->LINK->LINK->AltUnter.Pegel == MaxUnter)
    Fehler(true, 6L, 0L, 0L, 0L);
  else {
    LINK->LINK->LINK->AltUnter.Pegel++;
    LINK->LINK->LINK->AltUnter.Mark[LINK->LINK->LINK->AltUnter.Pegel - 1] = Z1;
  }
}  /* HINZU_ALT */

Local boolean Relevant(It)
TItemTyp *It;
{
  /* RELEVANT=true <=> I_LISTE ist nicht Teilmenge (([A->ua.;t]      */
  /*                                           fuer alle t aus T))   */
  /* RELEVANT=false<=> I_LISTE enthaelt nur ein Item, das zu einer   */
  /*                   Reduktion fuehrt                              */
  /*                                                                 */
  return (It->Naechstes != NULL || It->Punkt <= Rs[It->PNr - 1].RsLaenge ||
	  It->PNr == StartProduktion);
  /* Ein Lies-Reduziere mit der Start-Produktion soll nicht moeglich */
  /* sein; Sie soll erst reduziert werden, wenn das Stopsymbol gele- */
  /* sen ist.                                                        */
}

Local boolean HuellKrit(It)
TItemTyp *It;
{

  /* HUELLen_KRITerium = true                                         */
  /*    <=> Die Veraenderung der RK_Menge in IT macht eine Huellen-   */
  /*        bildung des ganzen Zustands noetig                        */
  /*    <=> Der Rechts-Kontext wird weitervererbt   *    *            */
  /*    <=> Es gibt ein Item [X->y.Yz;R] mit R aus T, z ===> Epsilon, */
  /*        Y aus N                                                   */
  /*                                                                  */
  /* Besonderheit: Weil die Reihenfolge der Auswertung Bool'scher     */
  /*               Ausdruecke auf der SIEMENS nicht definiert ist,    */
  /*               benoetigt man geschachtelte if-Anweisungen         */
  boolean B;
  int Pos;
  short V0;

  B = false;
  if (It->Punkt == Rs[It->PNr - 1].RsLaenge + 1)   /* Reduce-Item */
    return B;
  /* von with */

  if (It->Punkt == Rs[It->PNr - 1].RsLaenge) {
    if (((1L << ((long)SymTab[RsFeld[Rs[It->PNr - 1].RsAnfang + It->Punkt - 2]]->
	      SymArt)) & ((1L << ((long)Nt)) | (1L << ((long)HilfNt)))) != 0)
/* p2c: analyse.p, line 4220: Note:
 * Line breaker spent 1.4+0.74 seconds, 504 tries on line 2781 [251] */
      B = true;
    return B;
  }
  Pos = It->Punkt + 1;
  while (!B && Pos <= Rs[It->PNr - 1].RsLaenge) {
    V0 = RsFeld[Rs[It->PNr - 1].RsAnfang + Pos - 2];
    if (((1L << ((long)SymTab[V0]->SymArt)) &
	 ((1L << ((long)Nt)) | (1L << ((long)HilfNt)))) != 0) {
      if (!SymTab[V0]->UU.U2.Epsilon)   /* Weiter */
	B = true;
    } else
      B = true;
    Pos++;
  }
  B = !B;
  return B;

  /* von else */
}

Local Void VereinigeZustaende(ZStrich, IListe, Hinzu, Huelle, LINK)
short ZStrich;
TItemTyp **IListe;
boolean *Hinzu, *Huelle;
struct LOC_UntersucheUebergang *LINK;
{
  /* Wirkung : Q [Z_STRICH] ^.I_LISTE und I_LISTE werden vereinigt */
  /*  HINZU = true <=> Z_STRICH muss erneut untersucht werden      */
  /*               <=> Die neuen RK-Zeichen sind relevant fuer     */
  /*                   Uebergaenge                                 */
  /*               <=> Es gibt ein Item mit neuen RK-Zeichen,      */
  /*                   das kein Reduce-Item ist                    */
  /*  HUELLE=true  <=> Die neuen RK-Zeichen machen eine Huellen-   */
  /*                   bildung des Zustands Z_STRICH erforderlich  */
  /* Besonderheit : 1. Nur im LALR - Fall brauchen die Zustaende   */
  /*                   vereinigt werden, da andernfalls die Rechts-*/
  /*                   kontext-Mengen unwichtig sind               */
  /*                2. Vorbedingung : Die Kerne von I_LISTE und    */
  /*                   Q [Z_STRICH] ^.I_LISTE sind gleich          */
  /* External : Q                                                  */
  TItemTyp *BasisLaeufer, *ItemLaeufer;
  TTMenge RkPuffer;
  TItemTyp *WITH;

  *Hinzu = false;
  *Huelle = false;
  BasisLaeufer = Q[ZStrich - 1]->IListe;
  ItemLaeufer = *IListe;
  while (BasisLaeufer != NULL) {
    WITH = BasisLaeufer;
    if (!TeilmengeT(ItemLaeufer->RkMenge, WITH->RkMenge))
    {   /* nichts */
      memcpy(RkPuffer, WITH->RkMenge, sizeof(TTMenge));
      VereinigeT(RkPuffer, ItemLaeufer->RkMenge);
      WITH->RkMenge = HashIn(RkPuffer);
      if (!*Hinzu)
	*Hinzu = (WITH->Punkt <= Rs[WITH->PNr - 1].RsLaenge);
      /* kein Reduce-Item */
      if (!*Huelle)
	*Huelle = HuellKrit(BasisLaeufer);
    }
    BasisLaeufer = WITH->Basis;
    ItemLaeufer = ItemLaeufer->Naechstes;
  }

}  /* VEREINIGE_ZUSTAENDE */


Local boolean Vertraeglich(Z, IListe, LINK)
short Z;
TItemTyp *IListe;
struct LOC_UntersucheUebergang *LINK;
{
  /* VERTRAEGLICH = true <=> Q [Z] ^.I_LISTE und I_LISTE sind */
  /*                         vertraeglich im Sinne von XLR    */
  /* Besonderheit : I_LISTE enthaelt nur Basis-Items          */
  TItemTyp *BasisLaeufer, *ItemLaeufer;


  BasisLaeufer = Q[Z - 1]->IListe;
  ItemLaeufer = IListe;
  while (BasisLaeufer != NULL && ItemLaeufer != NULL)
  {   /* Abbruch wird erzwungen */
    if (BasisLaeufer->PNr == ItemLaeufer->PNr &&
	BasisLaeufer->Punkt == ItemLaeufer->Punkt) {
      BasisLaeufer = BasisLaeufer->Basis;
      ItemLaeufer = ItemLaeufer->Naechstes;
    } else
      BasisLaeufer = NULL;
  }
  return (ItemLaeufer == NULL && BasisLaeufer == NULL);


}  /* VERTRAEGLICH */


Local Void SucheZustand(It, Z1, LINK)
TItemTyp *It;
short *Z1;
struct LOC_UntersucheUebergang *LINK;
{  /* SUCHE_ZUSTAND */
  /*                                                    */
  /* Die Prozedur schaut, ob ein mit ITvertraeglicher   */
  /* Zustand Z1 schon vorhanden ist                     */
  /* Vorsicht : I_LISTE enthaelt nur Basis-Items !      */
  /* External : AKT_MAX_ZUSTAND                         */
  boolean Abbruch;
  short V0;

  V0 = RsFeld[Rs[It->PNr - 1].RsAnfang + It->Punkt - 3];
  Abbruch = false;
  *Z1 = SymTab[V0]->Erzu;
  if (*Z1 == 0) {
    *Z1 = AktMaxZustand + 1;
    return;
  }

  while (!Abbruch) {
    if (Vertraeglich(*Z1, It, LINK)) {
      Abbruch = true;
      break;
    }
    *Z1 = Q[*Z1 - 1]->Naechster;
    if (*Z1 == 0) {
      *Z1 = AktMaxZustand + 1;
      Abbruch = true;
    }
  }
}  /* SUCHE_ZUSTAND */


/**********************************************************************/



Local Void UntersucheUebergang(Z, UeElem, NeuUeElem, LINK)
short Z;
TUeberElem *UeElem;
TNeuUeberElem *NeuUeElem;
struct LOC_BearbeiteZustand *LINK;
{  /* UNTERSUCHE_UEBERGANG */
  /*                                                         */
  /* External: OPTION SR (SHIFT/REDUCE) , Q                  */
  /*                                                         */
  /* Wirkung : Falls der Zustand Z in Verlauf des Algorith-  */
  /*           mus noch nicht betrachtet wurde, wird ein zu  */
  /*           NEU_UE_ELEM ^.I ( = B (Z , NEU_UE_ELEM ^. A) )*/
  /*           vertraeglicher Zustand gesucht und im Erfolgs-*/
  /*           fall werden die Zustaende vereinigt und die   */
  /*           neuen Uebergaenge in die Uebergangs-Tabelle   */
  /*           eingetragen.                                  */
  /*           Falls Z schon betrachtet wurde, wird nur ver- */
  /*           glichen, ob die bereits gebildeten Nachfol-   */
  /*           gerzustaende zusaetzliche RK-Zeichen bekommen */
  /*           und dadurch noch einmal die Huelle gebildet   */
  /*           werden (HUELLE) bzw. der Nachfolgerzustand    */
  /*           (var WICHTIG) noch einmal betrachtet werden   */
  /*           muss.                                         */
  /*                                                         */
  /* Falls BETRACHTET [Z] = true , ist NEU_UE_ELEM = nil     */
  /* Falls BETRACHTET [Z] =false , ist UE_ELEM     = nil     */
  /*                                                         */
  /* Modulaufbau :                                           */
  /*            procedure UNTERSUCHE_UEBERGANG               */
  /*               procedure SUCHE_ZUSTAND                   */
  /*               procedure VEREINIGUNG                     */
  /*                                                         */
  struct LOC_UntersucheUebergang V;
  short ZStrich;
  short V0;
  TItemTyp *It, *ZLaeufer, *ILaeufer, *BasisLaeufer;
  boolean SrTeil, Huelle, Wichtig;
  TVorListe *VGaenger;
  TTMenge RkPuffer;
  TItemTyp *WITH;







  V.LINK = LINK;
  if (Z < LINK->LINK->NeuUnter.UnterAnf) {
    Huelle = false;
    Wichtig = false;

    V0 = UeElem->Es;
    ZStrich = UeElem->Z;
    if (ZStrich == 0)   /* LR_0 - Zustand */
      return;
    ZLaeufer = Q[Z - 1]->IListe;
    BasisLaeufer = Q[ZStrich - 1]->IListe;
    while (BasisLaeufer != NULL) {   /* vom ausseren while */
      WITH = BasisLaeufer;
      /* Diese Schleife laeuft ueber alle Items vom Nachfolger- */
      /* Zustand Z_STRICH                                       */
      while (ZLaeufer->PNr != WITH->PNr || ZLaeufer->Punkt + 1 != WITH->Punkt) {
	/* Die Items sind verschieden */
	ZLaeufer = ZLaeufer->Naechstes;
      }
      if (!TeilmengeT(ZLaeufer->RkMenge, WITH->RkMenge))
      {   /* Dieses Item ruft keine Veraenderung der */
	memcpy(RkPuffer, WITH->RkMenge, sizeof(TTMenge));
	VereinigeT(RkPuffer, ZLaeufer->RkMenge);
	WITH->RkMenge = HashIn(RkPuffer);
	if (!Huelle)
	  Huelle = HuellKrit(BasisLaeufer);
	if (!Wichtig)
	  Wichtig = (WITH->Punkt <= Rs[WITH->PNr - 1].RsLaenge);
      }
      /* RK_Mengen hervor                        */
      BasisLaeufer = WITH->Basis;
    }
    if (Huelle)
      BildeHuelle(&Q[ZStrich - 1]->IListe, false,
		  LINK->LINK);
    if (Wichtig) {
      if (ZStrich < LINK->LINK->NeuUnter.UnterAnf)
	HinzuAlt(&ZStrich, &V);
    }
    return;
  }


  V0 = NeuUeElem->A;
  ZStrich = 0;
  It = NeuUeElem->I;
  SrTeil = false;
  if (SrOpti) {
    if (Relevant(It) ||
	(((1L << ((long)SymTab[V0]->SymArt)) &
	  ((1L << ((long)Nt)) | (1L << ((long)HilfNt)))) != 0 &&
	 Devar))
/* p2c: analyse.p, line 4220: Note:
 * Line breaker spent 2.6+0.64 seconds, 1652 tries on line 3018 [251] */
      SrTeil = true;
    else {  /* Pruefung der Modifikationen */
/*
      if (Ls[It->PNr - 1]->Zusatz) {
	if (Ls[It->PNr - 1]->UU.U1.Modifik != NULL)
	  Fehler(false, 7L, (long)It->PNr, 0L, 0L);
      }
*/
      /* Haldenbereinigung */
      It->Naechstes = LINK->LINK->FreiItems;
      LINK->LINK->FreiItems = It;
      HinzuP(Lr0Zustaende, It->PNr);
    }
  } else
    SrTeil = true;
  if (SrTeil) {
    SucheZustand(It, &ZStrich, &V);
    if (ZStrich == AktMaxZustand + 1) {   /* neuer Zustand */
      BildeHuelle(&It, true, LINK->LINK);
      TrageEinZ(It, Z, &AktMaxZustand, &V);
      if (LINK->LINK->NeuUnter.UnterEnde != AktMaxZustand - 1)
	fprintf(Putout, "FEHLER ******:UnterEnde = %3ldAktMaxZustand = %3d\n",
		LINK->LINK->NeuUnter.UnterEnde, AktMaxZustand);
      else
	LINK->LINK->NeuUnter.UnterEnde = AktMaxZustand;
    } else {  /* alter Zustand */
      /* Merke Vorgaenger */
      if (Q[ZStrich - 1]->Vorgaenger->Vor != Z)
      {   /* Falls Z <> VOR, ist Z ueberhaupt nicht in der Liste.*/
	VGaenger = (TVorListe *)Malloc(sizeof(TVorListe));
	VGaenger->NextVor = Q[ZStrich - 1]->Vorgaenger;
	VGaenger->Vor = Z;
	Q[ZStrich - 1]->Vorgaenger = VGaenger;
      }
      VereinigeZustaende(ZStrich, &It, &Wichtig, &Huelle, &V);
      if (Huelle)
	BildeHuelle(&Q[ZStrich - 1]->IListe, false,
		    LINK->LINK);
      if (Wichtig) {
	if (ZStrich <= Z)   /* Z_STRICH ist bereits in NEU_UNTER */
	  HinzuAlt(&ZStrich, &V);
      }

      /* Nimm IT in die Frei-Liste auf, damit die  */
      /* Halde nicht zu schnell waechst            */
      ILaeufer = It;
      while (ILaeufer->Naechstes != NULL)
	ILaeufer = ILaeufer->Naechstes;
      ILaeufer->Naechstes = LINK->LINK->FreiItems;
      LINK->LINK->FreiItems = It;
    }
  }  /* SR_TEIL = true */
  TrageEinUe(&Z, NeuUeElem->A, ZStrich, It->PNr, &V);


  /* von else */
  /* Z wurde noch nicht betrachtet */
  /* Z_STRICH kommt in ALT_UNTER */
  /* von else */
}  /* von UNTERSUCHE_UEBERGANG */


Local Void BearbeiteZustand(Z, LINK)
short Z;
struct LOC_BildeZuTab *LINK;
{  /* BEARBEITE_ZUSTAND */
  /*                                                                 */
  /* External  : Q , NEU_UNTER .UNTER_ANF (Alle Zustaende mit kleine-*/
  /*             rer Zustandsnummer sind schon einmal betrachtet     */
  /*                                                                 */
  /* Wirkung   : Falls Z im Laufe des Algorithmus noch nicht         */
  /*             betrachtet wurde, werden alle Uebergaenge gebildet  */
  /*             und mit Uebergangzeichen in NEU_UE_ELEM eingetragen */
  /*             Falls Z schon betrachtet wurde, werden die          */
  /*             Uebergaenge lediglich aus der Uebergans-Tabelle ge- */
  /*             lesen.                                              */
  /*             In beiden Faellen wird F_SYMBOL belegt fuer die     */
  /*             Syntaxfehlerbehandlung im Zerteiler                 */
  struct LOC_BearbeiteZustand V;
  /* Enthaelt alle Symbol-Nummern, fuer die von Z aus bereits ein */
  /* Item als Uebergang relevant war                              */
  TNeuUeberElem *NeuUeLaeufer;
  TUeberElem *UeLaeufer;
  TTKette *TLaeufer;
  short V0;
  boolean Fb, FehlerBehandlung;
  long *T;
  TItemTyp *WITH;







  V.LINK = LINK;
  if (Z < LINK->NeuUnter.UnterAnf) {
    UeLaeufer = UeTabelle[Z - 1];
    while (UeLaeufer != NULL) {
      UntersucheUebergang(Z, UeLaeufer, (TNeuUeberElem *)0, &V);
      UeLaeufer = UeLaeufer->NextEs;
    }
    return;
  }
  LINK->NeuUe = NULL;
  memcpy(V.UeberZeichen, LeerSymMenge, sizeof(SymMenge));
  T = (long *)Malloc(sizeof(TTMenge));
  memcpy(T, LeerTMenge, sizeof(TTMenge));
  UeberZeich[Z - 1] = T;
  V.ItemLaeufer = Q[Z - 1]->IListe;

  FehlerBehandlung = false;

  /* Es werden alle Uebergaenge von Z_NAME gebildet und */
  /* in NEU_UE eingetragen                              */

  while (V.ItemLaeufer != NULL) {
    Fb = false;
    if ((OhneKettProd || TeilKettProd) & InP(KettPMenge, V.ItemLaeufer->PNr)) {
      V0 = RsFeld[Rs[V.ItemLaeufer->PNr - 1].RsAnfang - 1];
      Fb = true;
    } else {
      WITH = V.ItemLaeufer;   /* von with */
      if (WITH->Punkt <= Rs[WITH->PNr - 1].RsLaenge)
      {   /* Es liegt kein Reduce - Item vor */
	V0 = RsFeld[Rs[WITH->PNr - 1].RsAnfang + WITH->Punkt - 2];
	Fb = true;
	if (OhneKettProd || TeilKettProd)
	  ErzeugeNeuUe(&V0, &V);
	else {
	  if (InSym(V.UeberZeichen, V0))
	    HaengeAn(&V0, V.ItemLaeufer, &V);
	  else {
	    HinzuSym(V.UeberZeichen, V0);
	    Bilde(&V0, V.ItemLaeufer, &V);
	  }
	}
      }  /* von then */
      else {  /* Reduce -Item */
	if (!FehlerBehandlung) {
	  FSymbol[Z - 1] = 0;
	  FehlerBehandlung = true;
	}
      }
    }  /* von else */
    if (Fb) {
      if (SymTab[V0]->SymArt == Term) {
	HinzuT(UeberZeich[Z - 1], (long)Inab[V0]);
	if (!FehlerBehandlung) {
	  FSymbol[Z - 1] = Inab[V0];
	  FehlerBehandlung = true;
	}
      } else if (OhneKettProd || TeilKettProd) {
	TLaeufer = KettenZeichen[Inab[V0] - 1];
	if (TLaeufer != NULL) {
	  if (!FehlerBehandlung) {
	    FSymbol[Z - 1] = KettFSymbol[Inab[V0] - 1];
	    FehlerBehandlung = true;
	  }
	}
	while (TLaeufer != NULL) {
	  HinzuT(UeberZeich[Z - 1], (long)TLaeufer->T);
	  TLaeufer = TLaeufer->NextT;
	}
      }
    }


    V.ItemLaeufer = V.ItemLaeufer->Naechstes;
  }  /* von while */


  NeuUeLaeufer = LINK->NeuUe;
  while (NeuUeLaeufer != NULL) {
    /* Falls der Algorithmus ohne Shift-Reduce Optimierung */
    /* ablaeuft, kann Uebergangs-Tabelle leer sein         */

    UntersucheUebergang(Z, (TUeberElem *)0, NeuUeLaeufer, &V);
    NeuUeLaeufer = NeuUeLaeufer->Naechste;
  }

  /* Haldenbereinigung */
  if (LINK->NeuUe == NULL)
    return;
  NeuUeLaeufer = LINK->NeuUe;
  while (NeuUeLaeufer->Naechste != NULL)
    NeuUeLaeufer = NeuUeLaeufer->Naechste;
  NeuUeLaeufer->Naechste = LINK->FreiNeus;
  LINK->FreiNeus = LINK->NeuUe;

  /* Z wurde noch nie betrachtet */
  /* von else  */
}  /* BEARBEITE_ZUSTAND */


/**********************************************************************/
/*                                                                    */
/*            Aufbau aller Zustaende                                  */
/*                                                                    */
/**********************************************************************/




Local Void BildeZuTab(LINK)
struct LOC_Analyse *LINK;
{  /* BILDE_ZUTAB */
  /*                                                                */
  /* Wirkung   : In diesem Modul erfolgt der Aufbau der Zustands-   */
  /*             tabelle Q                                          */
  /* External  : Q                                                  */
  /*                                                                */
  /* Besonderheit : Der Algorithmus erwartet, dass die Bedingungen  */
  /*                1 bis 4 aus [Kl84,Kapitel 3.5] gelten !!        */
  /*                                                                */
  /* Modulaufbau :                                                  */
  /*               procedure BILDE_ZU_TAB                           */
  /*                  Operationen zur Freispeicher-Verwaltung       */
  /*                  procedure BILDE_HUELLE                        */
  /*                     procedure ANFANG                           */
  /*                     procedure HUELLE_NULL                      */
  /*                     procedure HUELLE_N                         */
  /*                  Operationen zum AUSDRUCK                      */
  /*                  procedure BEARBEITE_ZUSTAND                   */
  /*                    Operationen zur Uebergangs-Bildung          */
  /*                    procedure UNTERSUCHE_UEBERGANG              */
  /*                    Operationen auf der Zustandsliste           */
  /*                    Operationen auf der Uebergangs-Tabelle      */
  /*                    procedure HINZU_ALT                         */
  /*                    function RELEVANT                           */
  /*                    function HUELL_KRIT                         */
  /*                    procedure VEREINIGE_ZUSTAENDE               */
  /*                    function VERTRAEGLICH                       */
  /*                    procedure SUCHE_ZUSTAND                     */
  /*                        procedure VEREINIGUNG                   */
  /*                                                                */
  struct LOC_BildeZuTab V;
  TItemTyp *IListe;
  TZustandsTyp *HZustand;
  TTMenge RkPuffer;
  long I, ZIndex, FORLIM;



  V.LINK = LINK;
  FORLIM = AktMaxSymNr;
  /* Initialisierung */

  for (I = 1; I <= FORLIM; I++) {
    if (SymTab[I] != NULL)
      SymTab[I]->Erzu = 0;
  }

  for (I = 0; I < Maxzustand; I++)
    FSymbol[I] = UndefSymbol;

  V.FreiItems = NULL;
  V.FreiNeus = NULL;
  V.FreiSym = NULL;
  V.AltUnter.Pegel = 0;
  V.NeuUnter.UnterAnf = 1;
  V.NeuUnter.UnterEnde = 0;
  AktMaxZustand = 0;

  /* Initialisierung des Startzustandes */

  IListe = BeschaffeItem(StartProduktion, 1, (TItemTyp *)0, (TItemTyp *)0, &V);
  memcpy(RkPuffer, LeerTMenge, sizeof(TTMenge));
  HinzuT(RkPuffer, (long)Inab[StopSymNr]);
  IListe->RkMenge = HashIn(RkPuffer);
  /* Startproduktion wird nur bei Stopsymbol reduziert */
  BildeHuelle(&IListe, true, &V);

  /* Startzustand wird als Sonderfall 'von Hand' eingetragen */
  /* Ansonsten macht das TRAGE_EIN_Z                         */
  AktMaxZustand++;
  if (AktMaxZustand == Maxzustand) {
    Fehler(true, 5L, 0L, 0L, 0L);
    exit(1);
  }
  HZustand = BeschaffeZustand(IListe, 0);
  HZustand->Vorgaenger = NULL;
  Q[AktMaxZustand - 1] = HZustand;

  V.NeuUnter.UnterEnde = 1;

  /* Berechnung aller Zustaende */

  while (V.NeuUnter.UnterAnf <= V.NeuUnter.UnterEnde) {
    /* Es sind noch nicht alle Zustaende betrachtet */
    BearbeiteZustand((int)V.NeuUnter.UnterAnf, &V);
    V.NeuUnter.UnterAnf++;
    ZIndex = 1;
    while (V.AltUnter.Pegel != 0) {
      /* Schleife ueber schon einmal betrachtete Zustaende */
      BearbeiteZustand(V.AltUnter.Mark[ZIndex - 1], &V);
      if (ZIndex == V.AltUnter.Pegel)
	V.AltUnter.Pegel = 0;
      else
	ZIndex++;
    }
  }









}  /* von BILDE_ZU_TAB */

/* Local variables for XlrTest: */
struct LOC_XlrTest {
  struct LOC_Analyse *LINK;
} ;

Local Void XlrFehler(Fall, Z, P, Konf_, LINK)
long Fall;
short Z;
short P;
long *Konf_;
struct LOC_XlrTest *LINK;
{

  /* Die Fehlerzustaende werden auf FEHLERDA geschrieben */
  /* FALL = 1 <=> REDUKTIONS - REDUKTIONS - KONFLIKT     */
  /* FALL = 2 <=> SHIFT - REDUKTIONS - KONFLIKT          */
  /* External : KEINE_FEHLER , FEHLER_ZAHL               */
  TTMenge Konf;
  long Spalte, I, FORLIM;

  memcpy(Konf, Konf_, sizeof(TTMenge));
  KeineFehler = false;
  FehlerZahl++;
  HinzuZu(FehlerZustaende, Z);
  fprintf(Fehlerda, "%5d%5ld", Z, Fall);
  if (Fall == 1)
    fprintf(Fehlerda, "%5d", P);
  Spalte = 16;
  FORLIM = AktMaxTerm;
  for (I = 1; I <= FORLIM; I++) {
    if (InT(Konf, I))
      Druint(&Fehlerda, &Spalte, (long)Tab[I - 1], 5L);
  }
  fprintf(Fehlerda, "%5d\n", -1);
}

/* Local variables for LoescheEinUe: */
struct LOC_LoescheEinUe {
  struct LOC_XlrTest *LINK;
  short S;
} ;

Local Void LaufeAb(UeElem, LINK)
TUeberElem **UeElem;
struct LOC_LoescheEinUe *LINK;
{
  if (*UeElem == NULL)
    return;
  if ((*UeElem)->Es != LINK->S)
    LaufeAb(&(*UeElem)->NextEs, LINK);
  else
    *UeElem = (*UeElem)->NextEs;
}  /* LaufeAb */

Local Void LoescheEinUe(Z, S_, LINK)
short Z;
short S_;
struct LOC_XlrTest *LINK;
{
  /* Die Prozedur traegt loescht einen Uebergang aus der */
  /* Uebergangs-Tabelle (UE_TABELLE).                    */
  struct LOC_LoescheEinUe V;

  V.LINK = LINK;
  V.S = S_;
  LaufeAb(&UeTabelle[Z - 1], &V);
}  /* LoescheEinUe */


Local Void XlrTest(Z, LINK)
short Z;
struct LOC_Analyse *LINK;
{  /* XLR_TEST */

  /* Die Proz. ueberprueft die geforderte Eigenschaft XLR       */
  struct LOC_XlrTest V;
  TTMenge RedMenge;
  /* Enthaelt alle Zeichen, die zu einer Reduktion fuehren  */
  /* unter Beruecksichtigung von Modifikationen             */
  TTMenge KonfMenge;
  /* Enthaelt alle Konfliktzeichen ( mit Beruecksichtigung  */
  /* der Modifikationen )                                   */
  TTMenge Km, RkPuffer, LeerTerm;
  long I;
  TModifikTyp *ModLaeufer;
  TItemTyp *ItemSprinter, *ItemLaeufer;
  long AnzahlKonflikte;
  boolean KonfliktLoesung, FehlerBehandlung;
  TModifikTyp *WITH1;



  V.LINK = LINK;
  if (FSymbol[Z - 1] == UndefSymbol) {
    FSymbol[Z - 1] = Inab[StopSymNr];
    /* Damit ein Symbol drinsteht   */
    Fehler(true, 9L, (long)Z, 0L, 0L);
  }

  /* Initialisierung */
  memcpy(RkPuffer, LeerTMenge, sizeof(TTMenge));
  memcpy(RedMenge, LeerTMenge, sizeof(TTMenge));
  memcpy(KonfMenge, LeerTMenge, sizeof(TTMenge));
  memcpy(LeerTerm, LeerTMenge, sizeof(TTMenge));
  memcpy(Km, LeerTMenge, sizeof(TTMenge));
  FehlerBehandlung = (FSymbol[Z - 1] != 0);

  ItemLaeufer = Q[Z - 1]->IListe;

  /* In dieser Schleife wird geprueft, ob die RK-Mengen */
  /* der Reduce-Items disjunkt sind                     */
  while (ItemLaeufer != NULL) {
    if (ItemLaeufer->Punkt == Rs[ItemLaeufer->PNr - 1].RsLaenge + 1)
    {  /* Reduce - Item */
      /* Bearbeitung der Modifikationen */

      if (Ls[ItemLaeufer->PNr - 1]->Zusatz) {
	for (ModLaeufer = Ls[ItemLaeufer->PNr - 1]->UU.U1.Modifik;
	     ModLaeufer;
	     ModLaeufer = ModLaeufer->Naechste) {
	  WITH1 = ModLaeufer;
	  if (!InT(ItemLaeufer->RkMenge, (long)Inab[WITH1->ModSymNr]))
            continue;
	  if (WITH1->Reduziere) {
	    ItemSprinter = Q[Z - 1]->IListe;
	    while (ItemSprinter != NULL) {
              if (ItemSprinter->PNr != ItemLaeufer->PNr &&
                  ItemSprinter->Punkt ==
                    Rs[ItemSprinter->PNr - 1].RsLaenge + 1) {
                if (InT(ItemSprinter->RkMenge, (long)Inab[WITH1->ModSymNr])) {
                  memcpy(RkPuffer, ItemSprinter->RkMenge, sizeof(TTMenge));
                  StreicheT(RkPuffer, Inab[WITH1->ModSymNr]);
                  StreicheT(RedMenge, Inab[WITH1->ModSymNr]);
                  ItemSprinter->RkMenge = HashIn(RkPuffer);
                }
              }
              ItemSprinter = ItemSprinter->Naechstes;
	    }  /* von while */

	    if (InT(UeberZeich[Z - 1], (long)Inab[WITH1->ModSymNr])) {
              if (FSymbol[Z - 1] == Inab[WITH1->ModSymNr])
                Fehler(true, 19L, (long)ItemLaeufer->PNr, (long)Z,
                  (long)Inab[WITH1->ModSymNr]);
              else {
                memcpy(RkPuffer, UeberZeich[Z - 1], sizeof(TTMenge));
                StreicheT(RkPuffer, Inab[WITH1->ModSymNr]);
                UeberZeich[Z - 1] = HashIn(RkPuffer);
                LoescheEinUe(Z, WITH1->ModSymNr, &V);
              }
	    }
	  } else {  /* REDUZIERE = false */
	    int found=InT(UeberZeich[Z-1],(long)Inab[WITH1->ModSymNr]);

	    for (ItemSprinter = Q[Z - 1]->IListe;
	         !found && ItemSprinter;
		 ItemSprinter = ItemSprinter->Naechstes) {
              found = (ItemSprinter->PNr != ItemLaeufer->PNr &&
                       ItemSprinter->Punkt ==
                         Rs[ItemSprinter->PNr - 1].RsLaenge + 1 &&
                       InT(ItemSprinter->RkMenge,(long)Inab[WITH1->ModSymNr]));
	    }
            if (found) {
              memcpy(RkPuffer, ItemLaeufer->RkMenge, sizeof(TTMenge));
              StreicheT(RkPuffer, Inab[WITH1->ModSymNr]);
              ItemLaeufer->RkMenge = HashIn(RkPuffer);
	    }
	  }
	}
      }

      /* Die Reduktions - Symbole von F_SYMBOL werden besetzt */
      /* Anmerkung : Die RK-Mengen sind durch Modifikationen  */
      /*             bereits verkleinert. Vorteil: F_SYMBOL-  */
      /*             Fehler also nur, wenn durch Modifikatio- */
      /*             kein RK-Zeichen mehr vorhanden ist.      */

      if (!FehlerBehandlung) {
	I = 1;
	FehlerBehandlung = true;
	while (((short)I <= AktMaxTerm) & (!InT(ItemLaeufer->RkMenge, I)))
	  I++;
	if (I == AktMaxTerm + 1)
	  Fehler(true, 10L, (long)Z, (long)ItemLaeufer->PNr, 0L);
	else
	  FSymbol[Z - 1] = I;
      }
      SchneideT(RedMenge, ItemLaeufer->RkMenge, Km);
      if (!TeilmengeT(Km, LeerTerm)) {
	XlrFehler(1L, Z, ItemLaeufer->PNr, Km, &V);
	VereinigeT(KonfMenge, Km);
      }
      VereinigeT(RedMenge, ItemLaeufer->RkMenge);
    }

    ItemLaeufer = ItemLaeufer->Naechstes;
  }  /* von while */

  /* Reduktions-Menge und Uebergangs-Menge disjunkt ? */

  SchneideT(RedMenge, UeberZeich[Z - 1], Km);
  if (!TeilmengeT(Km, LeerTerm))
    XlrFehler(2L, Z, 1, Km, &V);


  /* Keine Aussage moeglich, weil mehrfache Konflikte */
}  /* von XLR_TEST */

Local Void ZerteilerAbbruch(LINK)
struct LOC_Analyse *LINK;
{
  /* Diese Prozedur stellt das korrekte Abbruchkriterium fuer */
  /* die Zerteilerschleife her                                */
  TUeberElem *UeElem;

  UeElem = (TUeberElem *)Malloc(sizeof(TUeberElem));
  UeElem->Es = StartSymNr;
  UeElem->Z = 1;   /* f(q1,S) = q1 */
  UeElem->P = 0;
  UeElem->NextEs = UeTabelle[0];
  UeTabelle[0] = UeElem;
}

/* Local variables for BeschreibeTabellen: */
struct LOC_BeschreibeTabellen {
  struct LOC_Analyse *LINK;
  short Z;
  short RSymbol[Maxzustand];
} ;

Local Void DruckeStrukt(P)
short P;
{
  /*        **************/
  TStrukturTyp *Strul;
  TLsTyp *WITH;
  TStrukturTyp *WITH1;
  long TEMP;

  WITH = Ls[P - 1];
  if (!WITH->Zusatz)
    return;
  if (WITH->UU.U1.Struktan == NULL)
    return;
  Strul = WITH->UU.U1.Struktan;
  while (Strul != NULL) {
    WITH1 = Strul;
    TEMP = WITH1->StrukturNr;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);   /* Strukturanknuepfung */
    Strul = WITH1->Naechste;
  }
}  /* VON DRUCKESTRUKTAN */


Local Void DruckeZuNr(Sym, LINK)
short Sym;
struct LOC_BeschreibeTabellen *LINK;
{

  /* External : Z , Q                                          */
  short Zust;
  long TEMP;

  Zust = SymTab[Sym]->Erzu;
  if (Zust == 0)
    return;
  TEMP = Sym;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);   /* Spalte */
  if (TeilKettProd || OhneKettProd)
  {   /* ZUSTANDS-BASIS */
    TEMP = 0;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);   /* ZUSTANDS-BASIS */
  } else {
    TEMP = LINK->Z;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);
  }
  while (Zust != 0) {
    LINK->Z++;
    TEMP = Zust;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);   /* ALTER ZUSTAND */
    TEMP = LINK->Z;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);   /* NEUER ZUSTAND */
    Zust = Q[Zust - 1]->Naechster;
  }

  TEMP = -3;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);
}  /* von DRUCKE_ZU_NR */

Local Void DruckeZustand(Z, LINK)
short Z;
struct LOC_BeschreibeTabellen *LINK;
{
  TItemTyp *ILaeufer;
  TUeberElem *UeberLaeufer;
  short Symbol;
  long I, TEMP, FORLIM;

  /* Terminal-Tabelle */

  ILaeufer = Q[Z - 1]->IListe;
  TEMP = Z;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);   /* Zustandsnummer */
  while (ILaeufer != NULL) {
    if (ILaeufer->Punkt == Rs[ILaeufer->PNr - 1].RsLaenge + 1)
    {   /* Reduce - Item */
      FORLIM = AktMaxTerm;
      for (I = 1; I <= FORLIM; I++) {
	if (InT(ILaeufer->RkMenge, I)) {
	  fwrite((Anyptr)(&I), sizeof(long), 1, Tabdat);   /* Terminal-Spalte */
	  TEMP = ILaeufer->PNr * 3 + Zreduziere;
	  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);   /* Reduktion */
	  if (InSym(Separator, Tab[I - 1]))
	    LINK->RSymbol[Z - 1] = I;
	}
      }
    }

    ILaeufer = ILaeufer->Naechstes;
  }  /* von while */

  UeberLaeufer = UeTabelle[Z - 1];
  while (UeberLaeufer != NULL) {
    Symbol = UeberLaeufer->Es;
    if (SymTab[Symbol]->SymArt == Term) {
      I = Inab[Symbol];
      if (InSym(Separator, Symbol))
	LINK->RSymbol[Z - 1] = I;
      fwrite((Anyptr)(&I), sizeof(long), 1, Tabdat);   /* Terminalspalte */
      if (UeberLaeufer->Z == 0) {   /* Aktion         */
	TEMP = UeberLaeufer->P * 3 + Zliesreduziere;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);
      } else {
	TEMP = UeberLaeufer->Z * 3;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);
      }
    }
    UeberLaeufer = UeberLaeufer->NextEs;
  }

  TEMP = -6;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);

  /* Nicht-Terminal-Tabelle */

  UeberLaeufer = UeTabelle[Z - 1];
  while (UeberLaeufer != NULL) {
    Symbol = UeberLaeufer->Es;
    if (((1L << ((long)SymTab[Symbol]->SymArt)) &
	 ((1L << ((long)Nt)) | (1L << ((long)HilfNt)))) != 0) {
      I = Inab[Symbol];
      fwrite((Anyptr)(&I), sizeof(long), 1, Tabdat);   /* Nicht-Terminal-Spalte */
      if (UeberLaeufer->Z == 0) {   /* Aktion                */
	TEMP = UeberLaeufer->P * 2 + Zliesreduziere;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);
      } else {
	TEMP = UeberLaeufer->Z * 2;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);
      }
    }
    UeberLaeufer = UeberLaeufer->NextEs;
  }

  TEMP = -7;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);
}  /* VON DRUCKE_ZUSTAND */

Local Void BeschreibeTabellen(LINK)
struct LOC_Analyse *LINK;
{  /* BESCHREIBE_TABELLEN */

  /* External : SEPARATOR , TABDAT                      */
  /* Wirkung  : TABDAT wird mit den Zerteilertabellen   */
  /*            beschrieben                             */
  /*            R_SYMBOL wird berechnet                 */
  struct LOC_BeschreibeTabellen V;
  long I, FORLIM, TEMP;



  V.LINK = LINK;
  FORLIM = AktMaxZustand;
  /* Initialisierung */
  for (I = 0; I < FORLIM; I++)
    V.RSymbol[I] = FSymbol[I];

  if (Tabdat != NULL)
    Tabdat = freopen("Tabdat", "wb", Tabdat);
  else
    Tabdat = fopen("Tabdat", "wb");
  if (Tabdat == NULL)
    _EscIO(FileNotFound);

  Zeit = cputime();

  FORLIM = AktMaxProdNr;
  /* Drucke LS-Symbole, Laenge der rechten Seiten  */
  /* und die Strukturanknuepfungen                 */

  for (I = 1; I <= FORLIM; I++) {
    fwrite((Anyptr)(&I), sizeof(long), 1, Tabdat);   /* Produktion */
    TEMP = Inab[Ls[I - 1]->SymNr];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);   /* Linke Seite */
    TEMP = Rs[I - 1].RsLaenge;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);   /*Laenge der RS */
    DruckeStrukt((int)I);
    TEMP = -1;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);
  }

  TEMP = -2;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);

  /*   Drucke die alten und neuen Zustandsnummern   */

  V.Z = 0;   /* ZUSTAND    */

  if (SymTab[StartSymNr]->Erzu != 0)
    Fehler(true, 8L, 0L, 0L, 0L);

  SymTab[StartSymNr]->Erzu = 1;
  DruckeZuNr(StartSymNr, &V);   /* Dadurch behaelt der Startzustand */
  /* seine Zustandsnummer 1           */
  SymTab[StartSymNr]->Erzu = 0;
  FORLIM = AktMaxNterm;
  for (I = 0; I < FORLIM; I++)
    DruckeZuNr(Ntab[I], &V);

  TEMP = -4;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);

  FORLIM = AktMaxTerm;
  for (I = 0; I < FORLIM; I++)
    DruckeZuNr(Tab[I], &V);

  TEMP = -5;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);

  FORLIM = AktMaxZustand;
  /*  Berechne R_SYMBOL                  */
  /*  Drucke die Zustandstabelle         */

  for (I = 1; I <= FORLIM; I++)
    DruckeZustand((int)I, &V);

  TEMP = -8;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);

  FORLIM = AktMaxZustand;
  for (I = 0; I < FORLIM; I++) {
    TEMP = FSymbol[I];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);
    TEMP = V.RSymbol[I];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Tabdat);
  }

  EaZeit += cputime() - Zeit;
}  /* von BESCHREIBE_TABELLEN */

/* Local variables for Ausdruck: */
struct LOC_Ausdruck {
  struct LOC_Analyse *LINK;
  long DruSpa;
  PackDruckZeile Strich, Stern, ZebraZeile, Vorspann, LeerZeile;
} ;

Local Void Freispalten(Dat, Vorspann, Spa, Einschub, LINK)
FILE **Dat;
Char *Vorspann;
long Spa, Einschub;
struct LOC_Ausdruck *LINK;
{
  /* Falls in der laufenden Zeile keine SPA Spalten mehr frei sind, */
  /* drucke in der naechsten Zeile den VORSPANN der Laenge EINSCHUB */
  long I;

  if (LINK->DruSpa + Spa <= Maxdruckspalte)
  {   /* Wegen Format von DRUCKE_BEZ! */
    LINK->DruSpa += Spa + 2;
    return;
  }
  putc('\n', *Dat);

  for (I = 0; I < Einschub; I++)
    putc(Vorspann[I], *Dat);

  LINK->DruSpa = Einschub + Spa;
}  /* VON FREISPALTEN */


Local Void DruckeItem(It, Fall, LINK)
TItemTyp *It;
Char Fall;
struct LOC_Ausdruck *LINK;
{
  long L, I, RechteSeite, FORLIM;

  if (Fall == 'X' || Fall == '+' || Fall == 'R' || Fall == 'B') {
    fprintf(Putout, "%s|%4d | ", Leer7, It->PNr);
  }  /* 15 SPALTEN SIND BESCHRIEBEN */
  else
    fprintf(Putout, " *** FEHLER in DruckeItem *** \n");
  LINK->DruSpa = 15;
  DruckeBez(Ls[It->PNr - 1]->SymNr, LINK->LINK);
  fprintf(Putout, ": ");
  LINK->DruSpa += Bezeichner[Ls[It->PNr - 1]->SymNr]->Lge + 4;
  RechteSeite = LINK->DruSpa;
  FORLIM = It->Punkt - 3;
  for (I = -1; I <= FORLIM; I++) {
    L = Bezeichner[RsFeld[Rs[It->PNr - 1].RsAnfang + I]]->Lge;
    Freispalten(&Putout, LINK->Vorspann, L, RechteSeite, LINK);
    DruckeBez(RsFeld[Rs[It->PNr - 1].RsAnfang + I], LINK->LINK);
  }
  Freispalten(&Putout, LINK->Vorspann, 1L, RechteSeite, LINK);
  fprintf(Putout, ". ");
  FORLIM = Rs[It->PNr - 1].RsLaenge - 2;
  for (I = It->Punkt - 2; I <= FORLIM; I++) {
    L = Bezeichner[RsFeld[Rs[It->PNr - 1].RsAnfang + I]]->Lge;
    Freispalten(&Putout, LINK->Vorspann, L, RechteSeite, LINK);
    DruckeBez(RsFeld[Rs[It->PNr - 1].RsAnfang + I], LINK->LINK);
  }

  /* Rechtskontext wird gedruckt */
  Freispalten(&Putout, LINK->Vorspann, 4L, RechteSeite, LINK);
  fprintf(Putout, "'R:'  ");
  FORLIM = AktMaxTerm;
  for (I = 0; I < FORLIM; I++) {
    if (InT(It->RkMenge, I + 1)) {
      L = Bezeichner[Tab[I]]->Lge;
      Freispalten(&Putout, LINK->Vorspann, L, RechteSeite, LINK);
      DruckeBez(Tab[I], LINK->LINK);
    }
  }
  putc('\n', Putout);
}  /* VON DRUCKE_ITEM */

/* Local variables for DruckeXlrTabelle: */
struct LOC_DruckeXlrTabelle {
  struct LOC_Ausdruck *LINK;
  short FehlerZustand;
} ;

Local Void FehlerBehandlung(Z, Fehler, LINK)
short Z;
boolean *Fehler;
struct LOC_DruckeXlrTabelle *LINK;
{
  long Liesvar, P;

  *Fehler = false;
  if (Z != LINK->FehlerZustand)
    return;
  *Fehler = true;
  while (Z == LINK->FehlerZustand) {
    TTMenge Conf;
    memcpy(Conf, LeerTMenge, sizeof(Conf));
    fscanf(Fehlerda, "%ld", &Liesvar);
    if ((unsigned long)Liesvar < 32 && ((1L << Liesvar) & 0x6) != 0) {
      switch (Liesvar) {

      case 1:
	fscanf(Fehlerda, "%ld", &P);
	fprintf(Putout, "   *** reduce-reduce conflict on: ");
	break;

      case 2:
	fprintf(Putout, "   *** shift-reduce conflict on: ");
	break;
      }/* case */
      fscanf(Fehlerda, "%ld", &P);
      while (P != -1) {
	P_addset((long *)&Conf, P);
	DruckeBez((int)P, LINK->LINK->LINK);
	fscanf(Fehlerda, "%ld", &P);
      }
    } else
      fprintf(Putout, "*** FEHLER in FEHLERBEHANDLUNG (FEHLERDA)***\n");

    putc('\n', Putout);
    if (P_inset('N', Options) && !P_inset('D', Options)) {
      putc('\n', Putout);
      PrintExample(Z, Liesvar, (long *)&Conf);
      fprintf(Putout, "%.*s\n", Maxdruckspalte, LINK->LINK->Stern);
    }

    fscanf(Fehlerda, "%*[^\n]");

    getc(Fehlerda);
    if (!P_eof(Fehlerda))
      fscanf(Fehlerda, "%hd", &LINK->FehlerZustand);
    else
      LINK->FehlerZustand = 0;

  }
}  /* VON FEHLER_BEHANDLUNG */


Local Void DruckeXlrTabelle(LINK)
struct LOC_Ausdruck *LINK;
{  /* VON DRUCKE_XLR_TABELLE */

  /**********************************************************************/
  /* MODULAUFBAU:                                                       */
  /*      procedure FEHLERBEHANDLUNG;                                   */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*           FEHLERDA,                                                */
  /*           DRU_SPA                                                  */
  /*           .                                                        */
  /*                                                                    */
  /**********************************************************************/
  struct LOC_DruckeXlrTabelle V;
  short Z;
  TItemTyp *ItemLaeufer;
  TVorListe *VorLaeufer;
  TUeberElem *UeberLaeufer;
  boolean Drucken;
  long AktSymLaenge;
  short Symbol;
  long I;
  short FORLIM;
  long FORLIM1;


  /* INITIALISIERE */
  V.LINK = LINK;
  putc('\n', Putout);
  if (Fehlerda != NULL)
    Fehlerda = freopen("Fehlerda", "r", Fehlerda);
  else
    Fehlerda = fopen("Fehlerda", "r");
  if (Fehlerda == NULL)
    _EscIO(FileNotFound);
  /* INITIALISIERE-ENDE */


  if (!P_inset('D', Options) && P_inset('N', Options)) {
    fprintf(Putout, "Conflicting Derivations\n");
    fprintf(Putout, "=======================\n\n");
  } else {
    fprintf(Putout, "LALR-State-Table\n");
    fprintf(Putout, "================\n\n");
  }
  fprintf(Putout, "%.*s\n", Maxdruckspalte, LINK->Stern);
  LINK->DruSpa = 0;

  V.FehlerZustand = 0;
  if (!P_eof(Fehlerda))
    fscanf(Fehlerda, "%hd", &V.FehlerZustand);

  FORLIM = AktMaxZustand;
  for (Z = 0; Z < FORLIM; Z++) {
    memcpy(LINK->Vorspann, LINK->LeerZeile, sizeof(PackDruckZeile));
    FehlerBehandlung(Z + 1, &Drucken, &V);
    if (DruckOption || (Drucken && !P_inset('N', Options))) {
      fprintf(Putout, "%sstate: %4d ; ", Leer3, Z + 1);
      LINK->DruSpa = 17;

      /* Fehler-Behandlungs-Symbol */
      fprintf(Putout, "error symbol: ");
      LINK->DruSpa += 14;
      if (FSymbol[Z] > 0) {
	DruckeBez(Tab[FSymbol[Z] - 1], LINK->LINK);
	LINK->DruSpa +=
	  Bezeichner[Tab[FSymbol[Z] - 1]]->Lge + 2;
      } else
	fprintf(Putout, "*** undefined ***");

      /* VORGAENGER-ZUSTAENDE */
      VorLaeufer = Q[Z]->Vorgaenger;
      if (VorLaeufer != NULL) {
	fprintf(Putout, "; pred. states: %4d", VorLaeufer->Vor);
	LINK->DruSpa += 20;
	VorLaeufer = VorLaeufer->NextVor;
	while (VorLaeufer != NULL) {
	  LINK->DruSpa += 5;
	  if (LINK->DruSpa <= Maxdruckspalte)
	    fprintf(Putout, ",%4d", VorLaeufer->Vor);
	  else {
	    Freispalten(&Putout, LINK->LeerZeile, 5L, 19L, LINK);
	    fprintf(Putout, " %4d", VorLaeufer->Vor);
	  }
	  VorLaeufer = VorLaeufer->NextVor;
	}
      }

      fprintf(Putout, "\n%.*s\n", Maxdruckspalte, LINK->Strich);

      LINK->Vorspann[7] = '|';
      LINK->Vorspann[13] = '|';
      /* Items des Zustands */
      ItemLaeufer = Q[Z]->IListe;
      if (Rs[ItemLaeufer->PNr - 1].RsLaenge + 1 == ItemLaeufer->Punkt)
	    /* Reduce-Item */
	      DruckeItem(ItemLaeufer, '+', LINK);
      else
	DruckeItem(ItemLaeufer, 'B', LINK);
      /* Abspaltung von der while-Schleife, weil ansonsten im Fall   */
      /* Z = 1 das erste Item nicht als Basis-Item erkannt wird      */
      ItemLaeufer = ItemLaeufer->Naechstes;
      while (ItemLaeufer != NULL) {
	if (Rs[ItemLaeufer->PNr - 1].RsLaenge + 1 == ItemLaeufer->Punkt)
	{   /* Reduce-Item */
	  if (ItemLaeufer->Punkt > 1)   /* Basis-Item */
	    DruckeItem(ItemLaeufer, '+', LINK);
	  else
	    DruckeItem(ItemLaeufer, 'R', LINK);
	} else {
	  if (ItemLaeufer->Punkt > 1)
	    DruckeItem(ItemLaeufer, 'B', LINK);
	  else
	    DruckeItem(ItemLaeufer, 'X', LINK);
	}
	ItemLaeufer = ItemLaeufer->Naechstes;
      }  /* von while */

      fprintf(Putout, "%.*s\n", Maxdruckspalte, LINK->ZebraZeile);

      /* Uebergaenge und Reduktionen */
      AktSymLaenge = 0;
      UeberLaeufer = UeTabelle[Z];
      /* Diese erste Schleife dient nur zum Feststellen */
      /* der groessten Symbollaenge                     */
      while (UeberLaeufer != NULL) {
	Symbol = UeberLaeufer->Es;
	if (AktSymLaenge < Bezeichner[Symbol]->Lge)
	  AktSymLaenge = Bezeichner[Symbol]->Lge;
	UeberLaeufer = UeberLaeufer->NextEs;
      }  /* von while */
      ItemLaeufer = Q[Z]->IListe;
      while (ItemLaeufer != NULL) {
	if (ItemLaeufer->Punkt == Rs[ItemLaeufer->PNr - 1].RsLaenge + 1)
	{   /* Reduce - Item */
	  FORLIM1 = AktMaxTerm;
	  for (I = 1; I <= FORLIM1; I++) {
	    if (InT(ItemLaeufer->RkMenge, I)) {
	      Symbol = Tab[I - 1];
	      if (AktSymLaenge < Bezeichner[Symbol]->Lge)
		AktSymLaenge = Bezeichner[Symbol]->Lge;
	    }
	  }
	}
	ItemLaeufer = ItemLaeufer->Naechstes;
      }  /* von while */

      UeberLaeufer = UeTabelle[Z];
      while (UeberLaeufer != NULL) {
	Symbol = UeberLaeufer->Es;
	fprintf(Putout, "%son%*c",
		Leer5,
		(int)(AktSymLaenge - Bezeichner[Symbol]->Lge + 2),
		' ');
	DruckeBez(Symbol, LINK->LINK);
	if (UeberLaeufer->Z == 0)
	  fprintf(Putout, "shift-reduce production %4d", UeberLaeufer->P);
	else if (UeberLaeufer->Z == 1 &&
		 ((1L << ((long)SymTab[Symbol]->SymArt)) &
		  ((1L << ((long)Nt)) | (1L << ((long)HilfNt)))) != 0)
	  fprintf(Putout, "accept");
	else
	  fprintf(Putout, "shift to state          %4d", UeberLaeufer->Z);
	putc('\n', Putout);
	UeberLaeufer = UeberLaeufer->NextEs;
      }  /* von while */
      ItemLaeufer = Q[Z]->IListe;
      while (ItemLaeufer != NULL) {
	if (ItemLaeufer->Punkt == Rs[ItemLaeufer->PNr - 1].RsLaenge + 1)
	{   /* Reduce - Item */
	  FORLIM1 = AktMaxTerm;
	  for (I = 1; I <= FORLIM1; I++) {
	    if (InT(ItemLaeufer->RkMenge, I)) {
	      Symbol = Tab[I - 1];
	      fprintf(Putout, "%son%*c",
		Leer5,
		(int)(AktSymLaenge - Bezeichner[Symbol]->Lge + 2),
		' ');
	      DruckeBez(Symbol, LINK->LINK);
	      fprintf(Putout, "reduce production       %4d\n",
		      ItemLaeufer->PNr);
	    }
	  }
	}
	ItemLaeufer = ItemLaeufer->Naechstes;
      }  /* von while */

      fprintf(Putout, "%.*s\n", Maxdruckspalte, LINK->Stern);
      LINK->DruSpa = 0;
    }  /* von then */
  }  /* von for */
}  /* von DRUCKE_XLR_TABELLE */

/*$page*/
Local Void Ausdruck(LINK)
struct LOC_Analyse *LINK;
{  /* von AUSDRUCK */

  /**********************************************************************/
  /*                                                                    */
  /*                   AUSDRUCK-MODUL                                   */
  /*                   ==============                                   */
  /*                                                                    */
  /*                                                                    */
  /* External:                                                          */
  /*          FEHLER_ZAHL                                               */
  /*          .                                                         */
  /*                                                                    */
  /* Dateien:                                                           */
  /*                                                                    */
  /*         FEHLERDA   : text; (EINGABE)                               */
  /*               Enthaelt die Fehlerzustandsnummern und Fehler-       */
  /*               nummern und -Symbole der Zustandstabelle             */
  /*                                                                    */
  /**********************************************************************/
  struct LOC_Ausdruck V;
  long I;
  short Lr0Anzahl;
  long FORLIM;


  /*$page*/
  V.LINK = LINK;
  /* Initialisierung */
  Zeit = cputime();

  for (I = 0; I < Maxdruckspalte; I++) {
    V.LeerZeile[I] = ' ';
    V.Strich[I] = '-';
    V.Stern[I] = '*';
  }

  for (I = 0; I <= 4; I++)
    V.Strich[I] = ' ';

  memcpy(V.ZebraZeile, V.LeerZeile, sizeof(PackDruckZeile));
  for (I = 3; I <= Maxdruckspalte / 2; I++)
    V.ZebraZeile[I * 2 - 1] = '-';

  /* Initialisierungs-Ende */

  fprintf(Putout, "\nAnalysis Results\n");
  fprintf(Putout, "================\n\n");

  fprintf(Putout, "Type                        : ");
  if (FehlerZahl != 0) {
    fprintf(Putout, "not LALR(1)\n");
  } else fprintf(Putout, "LALR(1)\n");
  if (FehlerZahl != 0) {
    fprintf(Putout, "Number of errors            : %d\n", FehlerZahl);
    fprintf(Putout, "Conflict states             : ");
    J = 0;
    FORLIM = AktMaxZustand;
    for (I = 1; I <= FORLIM; I++) {
      if (InZu(FehlerZustaende, (int)I)) {
	fprintf(Putout, "%4ld", I);
	if (I % 25 == 0)
	  putc('\n', Putout);
      }
    }
    putc('\n', Putout);
  }
  fprintf(Putout, "States                      : %d\n", AktMaxZustand);
  fprintf(Putout, "Nonterminals                : %d\n", AktMaxNterm);
  fprintf(Putout, "LR(0) reduce states         : ");
  Lr0Anzahl = 0;
  for (I = 1; I <= Maxprodnr; I++) {
    if (InP(Lr0Zustaende, (int)I))
      Lr0Anzahl++;
  }
  fprintf(Putout, "%d\n", Lr0Anzahl);

  if (FehlerZahl != 0 && P_inset('N', Options) && !P_inset('D', Options)) {
    InitExamples();
  }

  if (DruckOption || FehlerZahl != 0)
    DruckeXlrTabelle(&V);

  EaZeit += cputime() - Zeit;
}  /* von AUSDRUCK */

#undef Leer3
#undef Leer5
#undef Leer7


Static Void Analyse()
{  /* Anweisungsteil von ANALYSE */
  /*                                                                  */
  /* Wirkung : Im ersten Modul HUELL_INV werden einige Invarianten    */
  /*           des Algorithmus vorabberechnet, um dessen Haupt-       */
  /*           schleife zu entlasten.                                 */
  /*           Ausserdem wird die BNF-Grammatik auf Voraussetzungen   */
  /*           zum Algorithmus geprueft.                              */
  /*           In BILDE_ZU_TAB wird die Zustands- und Uebergangs-     */
  /*           Tabelle nach dem in [Goos83] beschriebenen Verfahren   */
  /*           aufgebaut.                                             */
  /*           Schliesslich wird die Zustands-Tabelle auf die gefor-  */
  /*           derte Eigenschaft ( LR, SLR, LALR ) hin ueberprueft    */
  /*           und ggf. die Entscheidungstabelle ( Zerteilertabelle   */
  /*           in nichtoptimierter Form ) erstellt.                   */
  /*           Falls die Option D gesetzt ist, wird die Zustands-     */
  /*           tabelle in lesbarer Form auf die Protokoll-Datei       */
  /*           ausgegeben.                                            */
  /*                                                                  */
  /* Modulaufbau :                                                    */
  /*              procedure ANALYSE                                   */
  /*                 Operationen auf Terminal-Mengen                  */
  /*                 Operationen auf Nichtterminal-Mengen             */
  /*                 Operationen auf Zustands-Mengen                  */
  /*                 Operationen auf Symbol-Mengen                    */
  /*                 Operationen auf Produktionen-Mengen              */
  /*                 Ein-,Ausgabe-Protokoll-Routinen                  */
  /*                 Operationen auf der Hash-Tabelle                 */
  /*                 procedure HUELL_INV                              */
  /*                 procedure BILDE_ZU_TAB                           */
  /*                 procedure XLR_TEST                               */
  /*                 procedure ZERTEILER_ABBRUCH                      */
  /*                 procedure BESCHREIBE_TABELLEN                    */
  /*                 procedure AUSDRUCK                               */
  /*                                                                  */
  /********************************************************************/
  struct LOC_Analyse V;

  boolean Info;
  TBez *BezElem;


  long I, FORLIM;
  long SET[Maxnterm / SETBITS + 2];
  long SET1[Maxterm / SETBITS + 2];
  long SET2[Maxsymnr / SETBITS + 2];
  FILE *TEMP;


  /* Initialisierung */
  fprintf(Putout, "PGS 8.0 --- Analysis\n");
  if (Fehlerda != NULL) {

/* p2c: analyse.p, line 4099: Note: REWRITE does not specify a name [181] */
    Fehlerda = freopen("Fehlerda", "w", Fehlerda);
  } else
    Fehlerda = fopen("Fehlerda", "w");
  if (Fehlerda == NULL)
    _EscIO(FileNotFound);
  if (P_inset('D', Options))
    DruckOption = true;
  else
    DruckOption = false;

  fprintf(Putout, "Algorithm ");

  if (P_inset('W', Options) || P_inset('N', Options))
    SrOpti = false;
  else
    SrOpti = true;

  if (P_inset('C', Options) || P_inset('N', Options))
    OhneKettProd = false;
  else
    OhneKettProd = true;
  /* true, falls Alg. mit El. von Kett.prod. ablaeuft */
  if (P_inset('X', Options))
    TeilKettProd = true;
  else
    TeilKettProd = false;
  /* Benutzer definiert Kett.Prod. selbst */
  if (TeilKettProd) {
    fprintf(Putout, "with partial ");
    if (!OhneKettProd)
      Info = true;
  } else {
    if (OhneKettProd)
      fprintf(Putout, "with ");
    else
      fprintf(Putout, "without ");
  }
  fprintf(Putout, "elimination of chain productions\n");
  if (Info)
    fprintf(Putout, "Option X makes option C useless\n");
  fprintf(Putout, "Algorithm ");

  if (SrOpti)
    fprintf(Putout, "with ");
  else
    fprintf(Putout, "without ");
  fprintf(Putout, "shift/reduce optimization \n");

  for (I = 0; I <= Maxhash; I++)
    HashTabelle[I] = NULL;

  for (I = 0; I < Maxzustand; I++) {
    UeberZeich[I] = NULL;
    UeTabelle[I] = NULL;
  }

  memcpy(Lr0Zustaende, LeerProdMenge, sizeof(ProdMenge));
  memcpy(FehlerZustaende, LeerZuMenge, sizeof(ZuMenge));
  memcpy(KettPMenge, LeerProdMenge, sizeof(ProdMenge));
 
    P_setcpy(LeerNtMenge, P_expset(SET, 0L));
  
    P_setcpy(LeerTMenge, P_expset(SET1, 0L));
 
    P_setcpy(LeerSymMenge, P_expset(SET2, 0L));

  if (P_inset('R', Options))
    Devar = true;
  else
    Devar = false;

  if (OhneKettProd || TeilKettProd) {
    TEMP = stdout;
/* p2c: analyse.p, line 4170:
 * Note: Taking address of stdout; consider setting VarFiles = 0 [144] */
    LiesKettProd(&infile, &TEMP, &V);
  }

  FORLIM = AktMaxSymNr;
  for (I = 0; I <= FORLIM; I++)
    Bezeichner[I] = NULL;
  if (Symbolda != NULL)
    Symbolda = freopen("Symbolda", "r", Symbolda);
  else
    Symbolda = fopen("Symbolda", "r");
  if (Symbolda == NULL)
    _EscIO(FileNotFound);
  while (!P_eof(Symbolda)) {
    char C; int Snr, Laenge;

    (void)fscanf(Symbolda, "%5d%4d ", &Snr, &Laenge);
    for (C = getc(Symbolda); C != '\n' && C != '\r'; C = getc(Symbolda)) {
      obstack_1grow(&SymObs, C);
    }
    if (C == '\r') {
      if ((C = getc(Symbolda)) != '\n') ungetc(C, Symbolda);
    }
    obstack_1grow(&SymObs, '\0');

    BezElem = (TBez *)Malloc(sizeof(TBez));
    BezElem->Lge = Laenge;
    BezElem->Bezei = (char *)obstack_finish(&SymObs);
    Bezeichner[Snr] = BezElem;
  }


  if (OhneKettProd || TeilKettProd)
    UeberOpt(&V);


  HuellInv(&V);

  if (!KeineFehler)
    return;

  BildeZuTab(&V);
  FORLIM = AktMaxZustand;
  for (I = 1; I <= FORLIM; I++)
    XlrTest((int)I, &V);
  if (Fehlerda != NULL)
    Fehlerda = freopen("Fehlerda", "r", Fehlerda);
  else
    Fehlerda = fopen("Fehlerda", "r");
  if (Fehlerda == NULL)
    _EscIO(FileNotFound);

  /**********************************************************************/
  /*   Versieh den Startzustand mit einer Stopaktion                    */
  /**********************************************************************/

  ZerteilerAbbruch(&V);

  /**********************************************************************/
  /*   Numeriere die Zustaende neu nach Uebergangsklassen.              */
  /*   Erzeuge die nichtoptimierten Zerteilertabellen.                  */
  /**********************************************************************/

  AnalyseEaZeit = cputime();
  BeschreibeTabellen(&V);
  Ausdruck(&V);
  AnalyseEaZeit = cputime() - AnalyseEaZeit;
  Messzeit("Analysis-IO ", 0L, AnalyseEaZeit);
  EaZeit += AnalyseEaZeit;
}  /* VON ANALYSE */

#undef Epsi
#undef UndefSymbol


#define Varende         (-1)
#define Strende         (-2)
#define Setende         (-3)
#define Wahr            1


/* Local variables for Analyseein: */
struct LOC_Analyseein {
  jmp_buf _JL1;
} ;


Local Void Separatortest(Testzahl, Separator, LINK)
long Testzahl, Separator;
struct LOC_Analyseein *LINK;
{
  if (Testzahl != Separator) {
    Fehler(true, 1L, 0L, 0L, 0L);
    longjmp(LINK->_JL1, 1);
  }
} /* VON SEPARATORTEST */ 


Static Void Analyseein()
{
  /* Hier werden die Daten von EINGABE eingelesen */
  struct LOC_Analyseein V;
  long J, k;
  TStrukturTyp *Struktlauf;
  TModifikTyp *Modifiklauf;
  long FORLIM;

  long SET1[Maxsymnr /SETBITS + 2];

  TRsTyp *WITH;
  TLsTyp *WITH1;
  TStrukturTyp *WITH2;
  TModifikTyp *WITH3;
  TSymTabTyp *WITH4;

  if (setjmp(V._JL1))
    goto _L1;
  if (Vareinda != NULL)
    Vareinda = freopen("Vareinda", "rb", Vareinda);
  else
    Vareinda = fopen("Vareinda", "rb");
  if (Vareinda == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Vareinda, long);
  Separatortest(RdEindat(), (long)Varende, &V);
  AktRsPos = RdEindat();
  AktMaxRsLaenge = RdEindat();
  StartProduktion = RdEindat();
  AktMaxProdNr = RdEindat();
  StartSymNr = RdEindat();
  StopSymNr = RdEindat();
  MaxTerminalCode = RdEindat();
  AktMaxTerm = RdEindat();
  AktMaxNterm = RdEindat();
  AktMaxSymNr = RdEindat();
  AktMaxSymLaenge = RdEindat();
  EgtLaenge = RdEindat();
  FehlerZahl = RdEindat();
  EaZeit = RdEindat();
  GsZeit = RdEindat();
  KeineFehler = (RdEindat() == Wahr);
  for (J = 0; J < Datumsgrenze; J++)
    Udatum[J] = (Char)RdEindat();
  Separatortest(RdEindat(), (long)Varende, &V);
  for (J = 0; J < Maxsymlaenge; J++)
    Extgramtitel[J] = (Char)RdEindat();
  Separatortest(RdEindat(), (long)Varende, &V);
  for (J = 0; J < Maxsymlaenge; J++)
    Gramtitel[J] = (Char)RdEindat();
  Separatortest(RdEindat(), (long)Varende, &V);

 
    P_setcpy(Separator, P_expset(SET1, 0L));    
    while (GETFBUF(Vareinda, long) >= 0) 
     HinzuSym( Separator, (unsigned)RdEindat());
/*    Separatortest(RdEindat(), (long)Setende, &V);*/
  Separatortest(RdEindat(), (long)Varende, &V);


    P_setcpy(Semklammer, P_expset(SET1, 0L)); 
    while (GETFBUF(Vareinda, long) >= 0)
      HinzuSym(Semklammer, (unsigned)RdEindat());
/*    Separatortest(RdEindat(), (long)Setende, &V); */ 
  Separatortest(RdEindat(), (long)Varende, &V);
 
    P_setcpy(Ueberlesen, P_expset(SET1, 0L)); 
    while (GETFBUF(Vareinda, long) >= 0)
      HinzuSym(Ueberlesen, (unsigned)RdEindat());
/*    Separatortest(RdEindat(), (long)Setende, &V);*/  
  Separatortest(RdEindat(), (long)Varende, &V);

    P_setcpy(Kellermenge, P_expset(SET1, 0L)); 
    while (GETFBUF(Vareinda, long) >= 0)
      HinzuSym(Kellermenge, (unsigned)RdEindat());
/*    Separatortest(RdEindat(), (long)Setende, &V);*/ 
  Separatortest(RdEindat(), (long)Varende, &V);

  FORLIM = AktMaxTerm;
  for (J = 0; J < FORLIM; J++)
    Tab[J] = RdEindat();
  Separatortest(RdEindat(), (long)Varende, &V);
  FORLIM = AktMaxNterm;
  for (J = 0; J < FORLIM; J++)
    Ntab[J] = RdEindat();
  Separatortest(RdEindat(), (long)Varende, &V);
  FORLIM = AktMaxSymNr;
  for (J = 0; J <= FORLIM; J++)
    Inab[J] = RdEindat();
  Separatortest(RdEindat(), (long)Varende, &V);
  FORLIM = AktRsPos - 2;
  for (J = 0; J <= FORLIM; J++)
    RsFeld[J] = RdEindat();
  Separatortest(RdEindat(), (long)Varende, &V);
  FORLIM = AktMaxProdNr;
  for (J = 0; J < FORLIM; J++) {
    WITH = &Rs[J];
    WITH->RsAnfang = RdEindat();
    WITH->RsLaenge = RdEindat();
  }
  Separatortest(RdEindat(), (long)Varende, &V);
  FORLIM = AktMaxProdNr;
  for (J = 0; J < FORLIM; J++) {
    Ls[J] = (TLsTyp *)Malloc(sizeof(TLsTyp));
    WITH1 = Ls[J];
    WITH1->SymNr = RdEindat();
    WITH1->Naechste = RdEindat();
    WITH1->KettProd = 0;   /* Initialisierung */
    WITH1->Zusatz = (RdEindat() == Wahr);
    if (WITH1->Zusatz) {
      if (GETFBUF(Vareinda, long) < 0)
	WITH1->UU.U1.Struktan = NULL;
      else {
	WITH1->UU.U1.Struktan = (TStrukturTyp *)Malloc(sizeof(TStrukturTyp));
	Struktlauf = WITH1->UU.U1.Struktan;
	while (GETFBUF(Vareinda, long) >= 0) {
	  WITH2 = Struktlauf;
	  WITH2->StrukturNr = RdEindat();
	  if (GETFBUF(Vareinda, long) < 0)
	    WITH2->Naechste = NULL;
	  else {
	    WITH2->Naechste = (TStrukturTyp *)Malloc(sizeof(TStrukturTyp));
	    Struktlauf = WITH2->Naechste;
	  }
	}
      }
      Separatortest(RdEindat(), (long)Setende, &V);
      if (GETFBUF(Vareinda, long) < 0)
	WITH1->UU.U1.Modifik = NULL;
      else {
	WITH1->UU.U1.Modifik = (TModifikTyp *)Malloc(sizeof(TModifikTyp));
	Modifiklauf = WITH1->UU.U1.Modifik;
	while (GETFBUF(Vareinda, long) >= 0) {
	  WITH3 = Modifiklauf;
	  WITH3->Reduziere = (RdEindat() == Wahr);
	  WITH3->ModSymNr = RdEindat();
	  if (GETFBUF(Vareinda, long) < 0)
	    WITH3->Naechste = NULL;
	  else {
	    WITH3->Naechste = (TModifikTyp *)Malloc(sizeof(TModifikTyp));
	    Modifiklauf = WITH3->Naechste;
	  }
	}
      }
    }
    Separatortest(RdEindat(), (long)Strende, &V);
  }
  Separatortest(RdEindat(), (long)Varende, &V);
  FORLIM = AktMaxSymNr;
  for (J = 0; J <= FORLIM; J++) {
    if (GETFBUF(Vareinda, long) < 0)
      SymTab[J] = NULL;
    else {
      SymTab[J] = (TSymTabTyp *)Malloc(sizeof(TSymTabTyp));
      WITH4 = SymTab[J];
      WITH4->Erzu = RdEindat();
      fread((Anyptr)(&k), sizeof(long), 1, Vareinda);
      if ((unsigned long)k < 32 && ((1L << k) & 0x1e) != 0) {
	switch (k) {

	case 1:
	  WITH4->SymArt = Term;
	  break;

	case 2:
	  WITH4->SymArt = SymStruk;
	  break;

	case 3:
	  WITH4->SymArt = Nt;
	  break;

	case 4:
	  WITH4->SymArt = HilfNt;
	  break;
	}
      } else
	Separatortest(0L, 1L, &V);
      if (((1L << ((long)WITH4->SymArt)) &
	   ((1L << ((long)Nt)) | (1L << ((long)HilfNt)))) != 0) {
	WITH4->UU.U2.LSeite = RdEindat();
	WITH4->UU.U2.RkSchlange = NULL;   /* Initialisierung */
	WITH4->UU.U2.KettProd = 0;   /* Initialisierung */
	WITH4->UU.U2.Epsilon = (RdEindat() == Wahr);
      }
    }
    Separatortest(RdEindat(), (long)Strende, &V);
  }
_L1:
  if (Vareinda != NULL)
    Vareinda = freopen("Vareinda", "rb", Vareinda);
  else
    Vareinda = fopen("Vareinda", "rb");
  if (Vareinda == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Vareinda, long);
}  /* VON ANALYSEEIN */

#undef Varende
#undef Strende
#undef Setende
#undef Wahr


#define Varende         (-1)   /* Trennt Variablen */
#define Strende         (-2)   /* Trennt Strukturen wie Listen, Mengen etc. */
#define Wahr            1
#define Falsch          0
#define Null            0



Static Void Analyseaus()
{
  /* Die Daten fuer OPTIMIERUNG bzw. DEVAR werden rausgeschrieben */
  long J, TEMP, FORLIM;

  TSymTabTyp *WITH;

/* p2c: analyse.p, line 4435: Note: REWRITE does not specify a name [181] */
  if (Varanada != NULL)
    Varanada = freopen("Varanada", "wb", Varanada);
  else
    Varanada = fopen("Varanada", "wb");
  if (Varanada == NULL)
    _EscIO(FileNotFound);
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  TEMP = AktMaxRsLaenge;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  TEMP = AktRsPos;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  TEMP = AktMaxProdNr;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  TEMP = 0;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);   /* NICHTMINIMAL !!!!! */
  TEMP = StartSymNr;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  TEMP = StopSymNr;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  TEMP = MaxTerminalCode;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  TEMP = AktMaxTerm;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  TEMP = AktMaxNterm;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  TEMP = AktMaxSymNr;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  TEMP = AktMaxSymLaenge;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  TEMP = AktMaxZustand;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  fwrite((Anyptr)(&EgtLaenge), sizeof(long), 1, Varanada);
  fwrite((Anyptr)(&FehlerZahl), sizeof(long), 1, Varanada);
  fwrite((Anyptr)(&EaZeit), sizeof(long), 1, Varanada);
  fwrite((Anyptr)(&GsZeit), sizeof(long), 1, Varanada);
  if (KeineFehler) {
    TEMP = Wahr;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  } else {
    TEMP = Falsch;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  }
  for (J = 0; J < Datumsgrenze; J++) {
    TEMP = Udatum[J];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  for (J = 0; J < Maxsymlaenge; J++) {
    TEMP = Extgramtitel[J];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  for (J = 0; J < Maxsymlaenge; J++) {
    TEMP = Gramtitel[J];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  for (J = 'A'; J <= 'Z'; J++) {
    if (P_inset((int)J, Options))
      fwrite((Anyptr)(&J), sizeof(long), 1, Varanada);
  }
  for (J = '0'; J <= '9'; J++) {
    if (P_inset((int)J, Options))
      fwrite((Anyptr)(&J), sizeof(long), 1, Varanada);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);


  for (J = 0; J <= Maxsymnr; J++) {
      if (P_inset((int)J, Separator))
	fwrite((Anyptr)(&J), sizeof(long), 1, Varanada);
       }
/*****    TEMP = Strende;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);*****/
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
 

  for (J = 0; J <= Maxsymnr; J++) {
      if (P_inset((int)J, Semklammer))
	fwrite((Anyptr)(&J), sizeof(long), 1, Varanada);
      }
/*****    TEMP = Strende;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);*****/
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada); 


  for (J = 0; J <= Maxsymnr; J++) {
      if (P_inset((int)J, Ueberlesen))
	fwrite((Anyptr)(&J), sizeof(long), 1, Varanada);
      } 
/*****    TEMP = Strende;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);*****/
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada); 


  for (J = 0; J <= Maxsymnr; J++) {
      if (P_inset((int)J, Kellermenge))
	fwrite((Anyptr)(&J), sizeof(long), 1, Varanada);
      } 
/*****    TEMP = Strende;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);*****/
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);


  FORLIM = AktMaxTerm;
  for (J = 0; J < FORLIM; J++) {
    TEMP = Tab[J];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  FORLIM = AktMaxNterm;
  for (J = 0; J < FORLIM; J++) {
    TEMP = Ntab[J];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  FORLIM = AktMaxSymNr;
  for (J = 0; J <= FORLIM; J++) {
    TEMP = Inab[J];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  FORLIM = AktMaxSymNr;
  for (J = 0; J <= FORLIM; J++) {
    if (SymTab[J] != NULL) {
      WITH = SymTab[J];
      TEMP = WITH->Erzu;
      fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
      switch (WITH->SymArt) {

      case Term:
	TEMP = 1;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
	break;

      case SymStruk:
	TEMP = 2;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
	break;

      case Nt:
	TEMP = 3;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
	break;

      case HilfNt:
	TEMP = 4;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
	break;
      }
      switch (WITH->SymArt) {

      case Term:
      case SymStruk:
	/* blank case */
	break;

      case Nt:
      case HilfNt:
	TEMP = WITH->UU.U2.LSeite;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
	if (WITH->UU.U2.KettProd == Maxprodnr) {
	  TEMP = Null;
	  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
	} else {
	  TEMP = WITH->UU.U2.KettProd;
	  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
	}
	if (WITH->UU.U2.Epsilon) {
	  TEMP = Wahr;
	  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
	} else {
	  TEMP = Falsch;
	  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
	}
	break;
      }
    }
    TEMP = Strende;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Varanada);
  }
  if (Varanada != NULL)
    Varanada = freopen("Varanada", "rb", Varanada);
  else
    Varanada = fopen("Varanada", "rb");
  if (Varanada == NULL)
    _EscIO(FileNotFound);
}  /* VON ANALYSEAUS */

#undef Varende
#undef Strende
#undef Wahr
#undef Falsch
#undef Null


int
main(argc, argv)
int argc;
Char *argv[];
{  /* LR-ANWEISUNGSTEIL */
  long SET[Maxprodnr / SETBITS + 2];
  long SET1[Maxzustand / SETBITS + 2];

  PASCAL_MAIN(argc, argv);
  Symbolda = NULL;
  Tabdat = NULL;
  Varanada = NULL;
  Vareinda = NULL;
  Kettdat = NULL;
  Fehlerda = NULL;
  Vokdat = NULL;
  Putout = NULL;
  infile = NULL;

  obstack_init(&SymObs);

  if (Putout != NULL)
    Putout = freopen("Putout", "w", Putout);
  else
    Putout = fopen("Putout", "w");
  if (Putout == NULL)
    _EscIO(FileNotFound);
  Analyseein();
  InitOptions();

  if (KeineFehler & P_inset('A', Options)) {
    /* INITIALISIERUNG  */
    AnalyseZeit = cputime();   
      P_setcpy(LeerProdMenge, P_expset(SET, 0L));
      P_setcpy(LeerZuMenge, P_expset(SET1, 0L));

    if (Vareinda != NULL)
      Vareinda = freopen("Vareinda", "rb", Vareinda);
    else
      Vareinda = fopen("Vareinda", "rb");
    if (Vareinda == NULL)
      _EscIO(FileNotFound);
    RESETBUF(Vareinda, long);

    /* INITIALISIERUNG-ENDE */

    Analyse();
    Messzeit("Analysis    ", AnalyseZeit, cputime());
    GsZeit += AnalyseZeit;
    Analyseaus();
  }
  return FehlerZahl;
}




/* End. */
