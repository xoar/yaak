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

static char rcsid[] = {"$Id: eingabe.c,v 1.31 2009/08/05 22:06:06 profw Exp $\n"};

#include "p2c.h"
#include <stdlib.h>
#define HAS_STDLIB
#include "obstack.h"
#include "options.h"


/*      *******/
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
/*--------------------------------------------------------------------*/
/*                                                                    */
/*        Dieses (EINGABE-) Modul von ZEDER wurde aus dem             */
/*        PGS-System uebernommen und angepasst.                       */
/*                                                                    */
/*           Autor des PGS : Peter Dencker                            */
/*                                                                    */
/**********************************************************************/
/*                                                                    */
/* DATEIEN:                                                           */
/*         input          : text; (EINGABE)                           */
/*               ENTHAELT DIE STEUERDATEN FUER DAS SYSTEM             */
/*                                                                    */
/*         output         : text; (AUSGABE)                           */
/*               ENTHAELT DIE DIALOG-INFORMATION                      */
/*                                                                    */
/*         PUTOUT         : text; (AUSGABE)                           */
/*               ENTHAELT DAS BENUTZERPROTOKOLL                       */
/*                                                                    */
/*         EINDAT         : text; (AUSGABE/EINGABE)                   */
/*               ENTHAELT DIE EINGABE FUER DAS SYSTEM                 */
/*                                                                    */
/*         PRODUDAT       : text; (AUSGABE/EINGABE)                   */
/*               ENTHAELT DIE BNF-GRAMMATIK, DIE INS BENUTZERPROTOKOLL*/
/*               GEDRUCKT WIRD.                                       */
/*                                                                    */
/*         VAREINDA       : INTFILE; (AUSGABE)                        */
/*               IST DIE VARIABLENSCHNITTSTELLE ZUR ANALYSE.          */
/*                                                                    */
/*         SYMBOLDA       : DRUSYMFILE; (AUSGABE)                     */
/*               ENTHAELT DIE BEZEICHNER DER SYMBOLTABELLE            */
/*                                                                    */
/*         VOKDAT         : text; (AUSGABE/EINGABE)                   */
/*               ENTHAELT BIS ZUR ANALYSE DAS VOKABULAR DER GRAMMATIK.*/
/*                                                                    */
/*         FEHLERDA       : text; (AUSGABE/EINGABE)                   */
/*               ENTHAELT DIE FEHLERMELDUNGEN DER EINGABEANALYSE      */
/*                                                                    */
/* EXTERNAL:                                                          */
/*           OPTIONS : IST DIE MENGE, DIE ALLE BEIM AUFRUF DES        */
/*                     SYSTEMS GESETZTEN OPTIONEN ENTHAELT.           */
/*                     (UNIVAC-PASCAL)                                */
/*           PROZESSCHALTER 1 :  ON <=> ANALYSE WIRD AUSGE-           */
/*                                       FUEHRT. (SIEMENS-PASCAL)     */
/*                                                                    */
/* MODULAUFBAU:                                                       */
/*        procedure LIESOPTIONEN;                                     */
/*        procedure LIESGRAMTITEL;                                    */
/*        function  cputime : integer;                                */
/*        procedure MESSZEIT(3);                                      */
/*        procedure DRUCKEDATEI(2);                                   */
/*        procedure ZUZUMENGE(2);                                     */
/*        procedure ZUPRODMENGE(2);                                   */
/*        function  INZUMENGE(2): boolean;                            */
/*        function  INPRODMENGE(2): boolean;                          */
/*        function  INSYMBOL(2): boolean;                             */
/*        procedure WRINT(2);                                         */
/*        procedure EINGABEAUS(1);                                    */
/*        procedure EINGABE;                                          */
/*                                                                    */
/* OPTION:                                                            */
/*     B = AUSGABE DER BNFGRAMMATIK                                   */
/*     E = AUSGABE DER EINGABEGRAMMATIK                               */
/*     V = DRUCKE DAS VOKABULAR                                       */
/*                                                                    */
/**********************************************************************/

#include "parameter.h"


/* ZAHL 0 RESERVIERT FUER:  */
/* KEINE NAECHSTE PRODUKTION */

typedef Char *Symbolstring;
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

typedef struct Tstrukturtyp {
  short Strukturnr;
  struct Tstrukturtyp *Naechste;
} Tstrukturtyp;

typedef struct Tmodifiktyp {
  boolean Reduziere;
  short Modsymnr;
  struct Tmodifiktyp *Naechste;
} Tmodifiktyp;

typedef struct Tlstyp {
  short Symnr;   /* SYMBOLKENNUNG */
  short Naechste;   /* [0]+PRODNRBEREICH */
  boolean Zusatz;
  union {
    struct {
      Tstrukturtyp *Struktan;
      Tmodifiktyp *Modifik;
    } U1;
  } UU;
} Tlstyp;

/*       NAECHSTE VERWEIST AUF DIE NAECHSTE PROD. MIT DIESER LS */
/*       NAECHSTE=0  BEDEUTET 'KEINE NAECHSTE PRODUKTION'       */

typedef struct Trstyp {
  long Rsanfang, Rslaenge;
} Trstyp;

typedef long Tntermenge[Maxnterm / SETBITS + 2];
typedef long Ttermenge[Maxterm / SETBITS + 2];
typedef long Prodmenge[Maxprodnr / SETBITS + 2];
typedef long Zumenge[Maxzustand / SETBITS + 2];



Static FILE *Vareinda;
Static FILE *Symbolda;

Static FILE *Putout;
#ifdef MONITOR
Static FILE *prodsfile;
#endif
/* SIEMENS-PASCAL */
/* STANDARD: output */
Static FILE *Vokdat, *Produdat;   /* = BNFGRAMMATIK = ZERKONSTDAT */
Static FILE *Eindat, *Fehlerda;   /* = BNFFEHLERDA : FOLGEN EINANDER */

Static Symnrtyp Separator, Semklammer, Ueberlesen, Kellermenge;

Static Char Udatum[24];   /* SIEMENS-PASCAL */
Static Char Zederversion[26];


Static short Aktmaxrslaenge;
Static short Aktrspos;
Static short Startproduktion, Aktmaxprodnr;
Static short Startsymnr, Stopsymnr, Maxsymzahl, Maxterminalcode, Aktmaxterm;
    /* 0..MAXTERM     0 <=> EPSILON */
Static short Aktmaxnterm;   /* 0..MAXNTERM */
Static short Aktmaxsymnr;
Static int Aktmaxsymlaenge;

Static boolean Bad;   /* BOOLESCHER AUSDRUCK */
Static boolean Keinefehler;
Static long Egtlaenge;   /* EXTERNE GRAMMATIK TITELLAENGE */
Static long Fehlerzahl, Eazeit, Gszeit, I;

Static Tsymtabtyp *Symtab[Maxsymnr + 1];
Static short Rsfeld[Maxlaengeallerrs];
/* ENTHAELT ALLE RECHTE SEITEN ANEINANDERGEHAENGT */
Static Tlstyp *Ls[Maxprodnr];
Static Trstyp Rs[Maxprodnr];
Static short Tab[Maxterm];
Static short Ntab[Maxnterm];
Static short Inab[Maxsymnr + 1];
FILEBUF(Symbolda,Static,Char);
FILEBUF(Vokdat,Static,Char);
FILEBUF(Produdat,Static,Char);
FILEBUF(Eindat,Static,Char);
FILEBUF(Fehlerda,Static,Char);


/* Text coordinates */

static long Zeilennummer;


/* Table of strings representing single characters */

static Char *CharSet[] = {
  "\000", "\001", "\002", "\003", "\004", "\005", "\006", "\007",
  "\010", "\011", "\012", "\013", "\014", "\015", "\016", "\017",
  "\020", "\021", "\022", "\023", "\024", "\025", "\026", "\027",
  "\030", "\031", "\032", "\033", "\034", "\035", "\036", "\037",
  " ", "!", "\"", "#", "$", "%", "&", "'",
  "(", ")", "*", "+", ",", "-", ".", "/",
  "0", "1", "2", "3", "4", "5", "6", "7",
  "8", "9", ":", ";", "<", "=", ">", "?",
  "@", "A", "B", "C", "D", "E", "F", "G",
  "H", "I", "J", "K", "L", "M", "N", "O",
  "P", "Q", "R", "S", "T", "U", "V", "W",
  "X", "Y", "Z", "[", "\\", "]", "^", "_",
  "`", "a", "b", "c", "d", "e", "f", "g",
  "h", "i", "j", "k", "l", "m", "n", "o",
  "p", "q", "r", "s", "t", "u", "v", "w",
  "x", "y", "z", "{", "|", "}", "~", "\177"
};

/* Table of strings representing keywords */

static Char *Symcode	= "CODE";
static Char *Symstack	= "STACK";
static Char *Symsepa	= "SEPA";
static Char *Symbracket	= "BRACKET";
static Char *Symskip	= "SKIP";
static Char *Symmeta	= "META";
static Char *Symstop	= "STOP";
static Char *Symgrammar	= "GRAMMAR";
static Char *Stopsymbol	= "EOF";

/* Obstack for identifer and literal strings */

static struct obstack SymObs;




/* DIE ABBILDUNGEN TAB, NTAB UND INAB SIND NUR FUER DIE BEREICHE
   DER TERMINALE UND NICHTTERMINALE DEFINIERT. */

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



Static Void FehlerdaInt(I)
long *I;
{
  /* Read an integer from file Fehlerda */
  boolean neg;

  neg = false;
  while (P_peek(Fehlerda) == ' ')
    getc(Fehlerda);
  if (P_peek(Fehlerda) == '-') {
    neg = true;
    getc(Fehlerda);
  } else if (P_peek(Fehlerda) == '+')
    getc(Fehlerda);
  *I = 0;
  while ((P_peek(Fehlerda) >= '0') & (P_peek(Fehlerda) <= '9')) {
    *I = *I * 10 + P_peek(Fehlerda) - '0';
    getc(Fehlerda);
  }
  if (neg && *I != 0)
    *I = -*I;
}


#define Varende         (-1)   /* TRENNT VARIABLEN */
#define Strende         (-2)   /* TRENNT VERBUNDE */
#define Setende         (-3)   /* TRENNT MENGEN */
#define Wahr            1
#define Falsch          0



Static Void Eingabeaus()
{
  /*        **********/
  long J;
  Tstrukturtyp *Struktlauf;
  Tmodifiktyp *Modifiklauf;
  long TEMP, FORLIM;
  Trstyp *WITH;
  Tlstyp *WITH1;
  Tstrukturtyp *WITH2;
  Tmodifiktyp *WITH3;
  Tsymtabtyp *WITH4;

/* p2c: eingabe.p, line 484: Note: REWRITE does not specify a name [181] */
  if (Vareinda != NULL)
    Vareinda = freopen("Vareinda", "wb", Vareinda);
  else
    Vareinda = fopen("Vareinda", "wb");
  if (Vareinda == NULL)
    _EscIO(FileNotFound);
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  TEMP = Aktrspos;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  TEMP = Aktmaxrslaenge;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  TEMP = Startproduktion;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  TEMP = Aktmaxprodnr;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  TEMP = Startsymnr;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  TEMP = Stopsymnr;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  TEMP = Maxterminalcode;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  TEMP = Aktmaxterm;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  TEMP = Aktmaxnterm;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  TEMP = Aktmaxsymnr;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  TEMP = Aktmaxsymlaenge;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  fwrite((Anyptr)(&Egtlaenge), sizeof(long), 1, Vareinda);
  fwrite((Anyptr)(&Fehlerzahl), sizeof(long), 1, Vareinda);
  fwrite((Anyptr)(&Eazeit), sizeof(long), 1, Vareinda);
  fwrite((Anyptr)(&Gszeit), sizeof(long), 1, Vareinda);
  if (Keinefehler) {
    TEMP = Wahr;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  } else {
    TEMP = Falsch;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  }
  for (J = 0; J < Datumsgrenze; J++) {
    TEMP = Udatum[J];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  for (J = 0; J < Maxsymlaenge; J++) {
    TEMP = ' ';
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  for (J = 0; J < Maxsymlaenge; J++) {
    TEMP = ' ';
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);


    for (J = 0; J <= Maxsymnr; J++) {
      if (P_inset((int)J, Separator))
	fwrite((Anyptr)(&J), sizeof(long), 1, Vareinda);
    }
/**********    TEMP = Setende;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda); *******/
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);


    for (J = 0; J <= Maxsymnr; J++) {
      if (P_inset((int)J, Semklammer))
	fwrite((Anyptr)(&J), sizeof(long), 1, Vareinda);
    }
/**********    TEMP = Setende;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda); *******/
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);


    for (J = 0; J <= Maxsymnr; J++) {
      if (P_inset((int)J, Ueberlesen))
	fwrite((Anyptr)(&J), sizeof(long), 1, Vareinda);
    }
/*********    TEMP = Setende;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda); ********/  
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);


    for (J = 0; J <= Maxsymnr; J++) {
      if (P_inset((int)J, Kellermenge))
	fwrite((Anyptr)(&J), sizeof(long), 1, Vareinda);
    }
/*********    TEMP = Setende;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda); ********/
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);


  FORLIM = Aktmaxterm;
  for (J = 0; J < FORLIM; J++) {
    TEMP = Tab[J];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  FORLIM = Aktmaxnterm;
  for (J = 0; J < FORLIM; J++) {
    TEMP = Ntab[J];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  FORLIM = Aktmaxsymnr;
  for (J = 0; J <= FORLIM; J++) {
    TEMP = Inab[J];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  FORLIM = Aktrspos - 2;
  for (J = 0; J <= FORLIM; J++) {
    TEMP = Rsfeld[J];
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  FORLIM = Aktmaxprodnr;
  for (J = 0; J < FORLIM; J++) {
    WITH = &Rs[J];
    TEMP = WITH->Rsanfang;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
    TEMP = WITH->Rslaenge;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  FORLIM = Aktmaxprodnr;
  for (J = 0; J < FORLIM; J++) {
    WITH1 = Ls[J];
    TEMP = WITH1->Symnr;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
    TEMP = WITH1->Naechste;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
    if (!WITH1->Zusatz) {
      TEMP = Falsch;
      fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
    } else {
      TEMP = Wahr;
      fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
      Struktlauf = WITH1->UU.U1.Struktan;
      while (Struktlauf != (Tstrukturtyp *)0) {
	WITH2 = Struktlauf;
	TEMP = WITH2->Strukturnr;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
	Struktlauf = WITH2->Naechste;
      }
      TEMP = Setende;
      fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
      Modifiklauf = WITH1->UU.U1.Modifik;
      while (Modifiklauf != (Tmodifiktyp *)0) {
	WITH3 = Modifiklauf;
	if (WITH3->Reduziere) {
	  TEMP = Wahr;
	  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
	} else {
	  TEMP = Falsch;
	  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
	}
	TEMP = WITH3->Modsymnr;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
	Modifiklauf = WITH3->Naechste;
      }
    }
    TEMP = Strende;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  }
  TEMP = Varende;
  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  FORLIM = Aktmaxsymnr;
  for (J = 0; J <= FORLIM; J++) {
    if (Symtab[J] != (Tsymtabtyp *)0) {
      WITH4 = Symtab[J];
      WITH4->Erzu = 0;
      TEMP = WITH4->Erzu;
      fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
      switch (WITH4->Symart2) {

      case Term:
	TEMP = 1;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
	break;

      case Symstruk:
	TEMP = 2;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
	break;

      case Nt:
	TEMP = 3;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
	break;

      case Hilfnt:
	TEMP = 4;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
	break;
      }
      switch (WITH4->Symart2) {

      case Term:
      case Symstruk:
	/* blank case */
	break;

      case Nt:
      case Hilfnt:
	TEMP = WITH4->UU.U2.Lseite;
	fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
	if (WITH4->UU.U2.Epsilon) {
	  TEMP = Wahr;
	  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
	} else {
	  TEMP = Falsch;
	  fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
	}
	break;
      }
    }
    TEMP = Strende;
    fwrite((Anyptr)(&TEMP), sizeof(long), 1, Vareinda);
  }
  if (Vareinda != NULL)
    Vareinda = freopen("Vareinda", "rb", Vareinda);
  else
    Vareinda = fopen("Vareinda", "rb");
  if (Vareinda == NULL)
    _EscIO(FileNotFound);
}  /* VON EINGABEAUS */

#undef Varende
#undef Strende
#undef Setende
#undef Wahr
#undef Falsch


/*
 0        1         2         3         4         5         6         7
 12345678901234567890123456789012345678901234567890123456789012345678901
*/

#define Maxzahllaenge   10   /* = LAENGE(2**35)-1 */
#define Maxprodlaenge   500   /* LAENGE DES RS-KELLERS */
#define Maxmetapp       3   /* METASYMBOLE PRO BNF-PRODUKTION */
#define Maxelemkeller   500   /* ELEMENTEKELLER */
#define Maxfokeller     60   /* FOLGEKELLER */
#define Maxatkeller     20   /* ALTERNATIVE-KELLER */
#define Maxatnkeller    20   /* =MAXATKELLER , ALTERNATIVEN-KELLER */


/* 0=DUMMY */

typedef enum {
  Bezeichner, Bracket, Code, Datend, Dollar, Doppelpkt, Eklauf, Eklazu,
  Gleich, Grammar, Klamaffe, Meta, Oder, Plus, Punkt, Rklauf, Rklazu, Sepa,
  Skip, Stack, Stern, Stop, Symbol, Und, Wdh, Zahl
} Symbolart;
typedef enum {
  Sym, Met, Struan, Red, Rednich, Plu, Ster, Rkl, Ekl, Rklplu, Rklster, Kopf
} Elemart;
typedef enum {
  Undef, Terminal, Nichtterminal, Fehlerhaft, Strukturan
} Symbolart1;


typedef struct Tsymboltyp {
  int Symnr, Slaenge;
  Symbolstring Bezeichner;
  struct Tsymboltyp *Naechster;   /* GLEICHER LAENGE */
  unsigned Symart1 : 3;
/* p2c: eingabe.p, line 779: Note:
 * Field width for Symart1 assumes enum Symbolart1 has 5 elements [105] */
} Tsymboltyp;

/* NAECHSTER : DIENT DER VERKETTUNG in DER SYMTABHASH */

typedef struct Tmetatyp {
  Symbolstring Bezeichner;
  struct Tmetaelement *Kopfelement;
  struct Tmetatyp *Naechster;
} Tmetatyp;

typedef struct Tmetaelement {
  unsigned Symnr : 10;
  struct Tmetaelement *Naechstes;
} Tmetaelement;

typedef struct Talternk {
  long Elzahl;
  struct Telementk *El1;
  struct Talterk *At;
} Talternk;

typedef struct Talterk {
  /* ALTERNATIVE-KNOTEN */
  long Fozahl;
  struct Tfolgek *Fo;
} Talterk;

typedef struct Tfolgek {
  struct Tfolgek *Naechster;
  long Elzahl;
  struct Telementk *El1, *Modi;
} Tfolgek;

typedef struct Telementk {
  struct Telementk *Vorg, *Naechster;
  Elemart Art;
  union {
    Talternk *Atn;
    short Elsymnr;
    Tmetatyp *Metasym;
  } UU;
} Telementk;

typedef short Bnfkellertyp[Maxprodlaenge + 1];
typedef char Mzgrkellertyp[Maxmetapp];
typedef Tmetaelement *Msymkellertyp[Maxmetapp];
typedef Telementk *Elemkellertyp[Maxelemkeller + 1];
typedef Tfolgek *Fokellertyp[Maxfokeller + 1];
typedef Talterk *Atkellertyp[Maxatkeller + 1];
typedef Talternk *Atnkellertyp[Maxatnkeller + 1];


/* Local variables for Eingabe: */
struct LOC_Eingabe {
  Symnrtyp Symnrmenge;
  int Symlaenge;
  Symbolstring Symbez;
  Symbolart Symart;
  long Letztsymi;   /* MENGENBEREICH */
  long Letztsymj;   /* SYMSETINDEXBEREICH */
  long Codenr;   /* IM SYMNRBEREICH AUSSER in LIESSYMBOL */
  long Druspa, I;
  short Aktprodnr;
  Tsymboltyp *Symboltabhash[Maxsymlaenge];
  Tmetatyp *Metatabhash[Maxsymlaenge];
  long Progew[Maxprodnr];   /* PROD.GEWICHT */
  long Zahlen[9], Bezmenge[9];
  boolean Metaexist, Imgrammatikteil;
} ;

/* Symbol table should be global */

static Tsymboltyp *Symboltabelle[Maxsymnr + 1];

/*$page*/


Local Void Fehlertext(Datei, Nummer)
FILE **Datei;
long Nummer;
{ switch (Nummer) {

  case 2:
    fprintf(*Datei, " Number too large; Maximum = %4d", Maxsymnr);
    break;

  case 4:
    fprintf(*Datei, " Symbol must not exceed line");
    break;

  case 5:
    fprintf(*Datei, " '$' expected; '$' inserted");
    break;

  case 6:
    fprintf(*Datei, " Keyword expected; GRAMMAR inserted");
    break;

  case 7:
    fprintf(*Datei, " Terminal symbol expected");
    break;

  case 8:
    fprintf(*Datei, " Terminal already encoded");
    break;

  case 9:
    fprintf(*Datei, " '=' expected");
    break;

  case 10:
    fprintf(*Datei, " Coding has to be in the range of 0 to %12d", Maxsymnr);
    break;

  case 11:
    fprintf(*Datei, " This code is already used");
    break;

  case 12:
    fprintf(*Datei, " '.' expected");
    break;

  case 13:
    fprintf(*Datei, " Stack symbol expected");
    break;

  case 14:
    fprintf(*Datei, " '.' expected");
    break;

  case 15:
    fprintf(*Datei, " Too many symbols defined; Maximum = %d", Maxsymnr);
    break;

  case 16:
    fprintf(*Datei, " Meta symbol expected");
    break;

  case 17:
    fprintf(*Datei, " '=' expected");
    break;

  case 18:
    fprintf(*Datei, " '.' expected");
    break;

  case 19:
    fprintf(*Datei, " Left-hand side of a rule must be a nonterminal");
    break;

  case 20:
    fprintf(*Datei, " Left-hand side of a rule must be a nonterminal");
    break;

  case 21:
    fprintf(*Datei, " ':' expected");
    break;

  case 22:
    fprintf(*Datei, " Too many closing ']'");
    break;

  case 23:
    fprintf(*Datei, " Too many closing ')'");
    break;

  case 24:
    fprintf(*Datei, " A rule must be terminated by a dot '.'");
    break;

  case 25:
    fprintf(*Datei, " Element before '+' or '*' is missing");
    break;

  case 26:
    fprintf(*Datei, " Repetition of meta symbols not allowed");
    break;

  case 27:
    fprintf(*Datei,
	    " Repetition of semantic actions or modifications not allowed");
    break;

  case 28:
    fprintf(*Datei, " Illegal semantic action or illegal modification");
    break;

  case 29:
    fprintf(*Datei, " Meta symbol not allowed here");
    break;

  case 30:
    fprintf(*Datei, " ')' expected");
    break;

  case 31:
    fprintf(*Datei, " ']' expected");
    break;

  case 32:
    fprintf(*Datei, " Illegal element");
    break;

  case 33:
    fprintf(*Datei, " This modification contains no terminal");
    break;

  case 34:
    fprintf(*Datei, " Illegal semantic action");
    break;

  case 35:
    fprintf(*Datei, " A modification may not separate list elements");
    break;

  case 36:
    fprintf(*Datei, " System error: not(FO^.mod^.ART in [RED,REDNICH]).");
    break;

  case 37:
    fprintf(*Datei, " System error: ELEM^.ART in [RED,REDNICH] .");
    break;

  case 38:
    fprintf(*Datei, " Symbols of length 0 are not allowed");
    break;

  /*   FALLS SIE DOCH MAL BENOETIGT WERDEN, MUSS NUR DER
       SYMLAENGENBEREICH= 0..MAXSYMLAENGE GESETZT WERDEN. */
  case 39:
    fprintf(*Datei, " Name of grammar expected");
    break;

  case 40:
    fprintf(*Datei, " Stack overflow (Elemkeller)");
    break;

  case 41:
    fprintf(*Datei, " Stack overflow (Fokeller)");
    break;

  case 42:
    fprintf(*Datei, " Stack overflow (Atkeller)");
    break;

  case 43:
    fprintf(*Datei, " Stack overflow (Atnkeller)");
    break;

  case 44:
    fprintf(*Datei, " Start symbol may not appear on right-hand side");
    break;

  case 45:
    fprintf(*Datei, " Terminal expected");
    break;

  case 46:
    fprintf(*Datei, " Right-hand side of start symbol may not be empty");
    break;

  case 47:
    fprintf(*Datei, " Start symbol may appear on left-hand side only once");
    break;

  case 48:
    fprintf(*Datei, " No sequence of terminals can be derived from this symbol");
    break;

  case 49:
    fprintf(*Datei, " Too many terminals; Maximum = %ld", (long)Maxterm);
    break;

  case 50:
    fprintf(*Datei, " Too many nonterminals; Maximum = %ld", (long)Maxnterm);
    break;

  case 51:
    fprintf(*Datei, " This is an illegal end-of-input indicator");
    break;

  case 52:
    fprintf(*Datei, " '.' expected");
    break;

  case 53:
    fprintf(*Datei,
	    " Only one symbol may be defined as end of input indicator");
    break;

  case 54:
    fprintf(*Datei, " Transformed EBNF rule too long; Maximum = %d",
	    Maxlaengers);
    break;

  case 55:
    fprintf(*Datei, " Illegal character with this ordinal number");
    break;

  case 56:
    fprintf(*Datei, " '.' expected");
    break;

  case 57:
    fprintf(*Datei,
	    " Semantic brackets and unsafe restart points must be disjoint");
    break;

  case 58:
    fprintf(*Datei,
	    " List separators and unsafe restart points  must be disjoint");
    break;

  case 59:
    fprintf(*Datei, " This nonterminal is not reachable");
    break;

  case 60:
    fprintf(*Datei, " Too many productions; Maximum = %d", Maxprodnr);
    break;

  default:
    fprintf(*Datei, " Invalid error number %ld", Nummer);
  }
}  /* VON FEHLERTEXT */

Local Void Feproz(Fedat, Nummer, Zeprodnr, Laenge, Symbol)
FILE **Fedat;
long Nummer, Zeprodnr, Laenge;
Char *Symbol;
{
  /*        ******/

  /**********************************************************************/
  /* EXTERNAL:                                                          */
  /*           KEINEFEHLER,                                             */
  /*           FEHLERZAHL,                                              */
  /*           MAXZAHLLAENGE,                                           */
  /*           MAXSYMLAENGE .                                           */
  /*                                                                    */
  /* DIE ZEPRODNR ZUSAMMEN MIT DER FEHLERNUMMER UND DEM AUFBEREI-       */
  /* TETEN FEHLERTEXT WIRD AUF DIE DATEI FEDAT GESCHRIEBEN.             */
  /*                                                                    */
  /**********************************************************************/
  long I;

  Keinefehler = false;
  Fehlerzahl++;
  fprintf(*Fedat, "%6ld", Zeprodnr);
  fprintf(*Fedat, "*** Error %3ld ***  <", Nummer);
  for (I = 0; I < Laenge; I++)
    putc(Symbol[I], *Fedat);
  fprintf(*Fedat, ">: ");
  Fehlertext(Fedat, Nummer);
  putc('\n', *Fedat);
}  /* VON FEPROZ */

#define Fehler(Nummer,Laenge,Symbol)\
  Feproz(&Fehlerda, Nummer, Zeilennummer, Laenge, Symbol)

#define Bnffehler(Nummer,Prodnr,Laenge,Symbol)\
  Feproz(&Fehlerda, Nummer, Prodnr, Laenge, Symbol)

Local Void Zusymbol(S, I)
long *S;
unsigned I;
{
  /*        ********/
 
   P_addset(S, I);
}  /* VON ZUSYMBOL */

Local boolean Leerschnittmenge(M1, M2, Schnittsymbol)
long *M1, *M2;
short *Schnittsymbol;
{
  /*       ****************/
  boolean Leer;
  Symnrtyp Schnittmenge;
  long SET[Maxsymnr / SETBITS + 2];

  *Schnittsymbol = 0;
    Leer = (*P_setint(SET, M1, M2) == 0L);
  if (Leer)
    return Leer;

  P_setint(Schnittmenge, M1, M2);
  while (!P_inset(*Schnittsymbol, Schnittmenge))
    (*Schnittsymbol)++;
  return Leer;
}  /* VON LEERSCHNITTMENGE */

/*$page*/
Local Void Liessymbol(LINK)
struct LOC_Eingabe *LINK;
{
  /*        **********/
  /**********************************************************************/
  /* AB DER AKTUELLEN STELLUNG DES ZEIGERS 'EINDAT^' WIRD EIN NEUES     */
  /* SYMBOL AUS DER DATEI EINDAT GELESEN UND in DIE STRINGVARIABLE      */
  /* USYMBEZ GESCHRIEBEN. DABEI WIRD DER ALTE INHALT VON USYMBEZ VON    */
  /*   1 BIS ZUR LAENGE DES NEUEN SYMBOLS ('SYMLAENGE') UEBERSCHRIEBEN. */
  /* DER REST BLEIBT WIE ER WAR, AUSSER BEI BEZEICHNERN UND SYMBOLEN.   */
  /* DORT WIRD DER REST MIT LEERZEICHEN GEFUELLT.                       */
  /* EIN ZEILENENDE WIRD WIE EIN LEERZEICHEN BEHANDELT; ZUSAETZLICH     */
  /* WIRD DIE ZEILENNUMMER UM EINS ERHOEHT.                             */
  /* BEI ZAHLEN WIRD ZUSAETZLICH DEREN WERT in CODENR ABGELEGT.         */
  /* ANSONSTEN HAT DER PARAMETER CODENR KEINE BEDEUTUNG.                */
  /* ES WERDEN 27 VERSCHIEDENE SYMBOLARTEN (SYMART) ERKANNT:            */
  /* *BEZEICHNER,*BRACKET,*CODE,DATEND,DOLLAR,DOPPELPKT,EKLAUF,EKLAZU,  */
  /* GLEICH,*GRAMMAR,KLAMAFFE,*META,*ODER,PLUS,PROZENT,PUNKT,RKLAUF,    */
  /* RKLAZU,*SEPA,*SKIP,*STACK,STERN,*STOP,*SYMBOL,UND,*WDH,*ZAHL.      */
  /* NACH VERARBEITUNG DER MIT EINEM STERN VERSEHENEN ARTEN STEHT DER   */
  /* ZEIGER 'EINDAT^' AUF DEM ERSTEN NOCH NICHT VERARBEITETEN ZEICHEN   */
  /* DER EINGABE, BEI ALLEN UEBRIGEN ARTEN AUF DEM ZULETZT VERARBEITETEN*/
  /* ZEICHEN.                                                           */
  /* DAMIT DER ZEIGER AM ENDE DER PROZEDUR EINHEITLICH AUF DAS ERSTE    */
  /* NICHTVERARBEITETE ZEICHEN POSITIONIERT IST UND DES KUERZEREN       */
  /* PROGRAMMTEXTS WEGEN WURDE DIE BOOLESCHE VARIABLE 'VERARBEITET'     */
  /* EINGEFUEHRT, DIE AM SCHLUSS DER PROZEDUR ABGEFRAGT WIRD.           */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*         * EINDAT,                                                  */
  /*           MAXSYMLAENGE,                                            */
  /*         * AKTMAXSYMLAENGE,                                         */
  /*           MAXZAHLLAENGE,                                           */
  /*           MAXSYMNR,                                                */
  /*           BEZMENGE,                                                */
  /*           ZAHLEN,                                                  */
  /*         * IMGRAMMATIKTEIL                                          */
  /*         * USYMBEZ,                                                 */
  /*         * SYMBEZ,                                                  */
  /*         * SYMLAENGE,                                               */
  /*         * CODENR,                                                  */
  /*         * SYMART,                                                  */
  /*         * ZEILENNUMMER.                                            */
  /*                                                                    */
  /* DIE GESTERNTEN EXTERNEN VARIABLEN KOENNEN BEI JEDEM AUFRUF         */
  /* VERAENDERT WERDEN||                                                */
  /*                                                                    */
  /**********************************************************************/
  /*$page*/
  /* WIRD IM FALL 'SYMBOL' BENOETIGT */
  boolean Verarbeitet;
  Char C;

  LINK->Symlaenge = 1;
  Verarbeitet = false;

  while ((!P_eof(Eindat)) & (P_peek(Eindat) == '\t' ||
			     P_peek(Eindat) == '%' ||
			     P_peek(Eindat) == ' ')) {
    if (P_eoln(Eindat) | (P_peek(Eindat) == '%')) {
      fscanf(Eindat, "%*[^\n]");
      getc(Eindat);
      Zeilennummer++;
    } else getc(Eindat);
  }

  if (P_eof(Eindat)) C = ' '; else C = P_peek(Eindat);

  LINK->Symbez = CharSet[(int)C];

  switch (C) {

  case ' ':
    Verarbeitet = true;
    LINK->Symart = Datend;
    break;

  case '@':
    LINK->Symart = Klamaffe;
    break;

  case '$':
    LINK->Symart = Dollar;
    break;

  case '&':
    LINK->Symart = Und;
    break;

  case '*':
    LINK->Symart = Stern;
    break;

  case '+':
    LINK->Symart = Plus;
    break;

  case '=':
    LINK->Symart = Gleich;
    break;

  case '.':
    LINK->Symart = Punkt;
    break;

  case ':':
    LINK->Symart = Doppelpkt;
    break;

  case '(':
    LINK->Symart = Rklauf;
    break;

  case ')':
    LINK->Symart = Rklazu;
    break;

  case '[':
    LINK->Symart = Eklauf;
    break;

  case ']':
    LINK->Symart = Eklazu;
    break;

  case '/':   /* 'ODER' ODER WIEDERHOLUNG */
    getc(Eindat);
    Verarbeitet = true;
    if (P_peek(Eindat) == '/') {
	LINK->Symlaenge = 2;
	LINK->Symbez = "//";
	LINK->Symart = Wdh;
	getc(Eindat);
    } else LINK->Symart = Oder;
    break;

  case '|':   /* 'ODER' ODER WIEDERHOLUNG */
    getc(Eindat);
    Verarbeitet = true;
    if (P_peek(Eindat) == '|') {
	LINK->Symlaenge = 2;
	LINK->Symbez = "||";
	LINK->Symart = Wdh;
	getc(Eindat);
    } else LINK->Symart = Oder;
    break;

  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
  case 'G':
  case 'H':
  case 'I':
  case 'J':
  case 'K':
  case 'L':
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  case 'R':
  case 'S':
  case 'T':
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z':
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z':
  case '_':   /*BEZ ODER WORTSYMB*/
    Verarbeitet = true;
    obstack_1grow(&SymObs, C); getc(Eindat); C = P_peek(Eindat);

    while (P_inset(C, LINK->Bezmenge)) {
	LINK->Symlaenge++;
        obstack_1grow(&SymObs, C); getc(Eindat); C = P_peek(Eindat);
    }
    obstack_1grow(&SymObs, '\0');

    {Char *ObjPointer = (Char *)obstack_finish(&SymObs);
      if (LINK->Imgrammatikteil) LINK->Symart = Bezeichner;
      else if (!strcmp(ObjPointer, Symcode)) {
        LINK->Symbez = Symcode; LINK->Symart = Code;
      } else if (!strcmp(ObjPointer, Symstack)) {
        LINK->Symbez = Symstack; LINK->Symart = Stack;
      } else if (!strcmp(ObjPointer, Symbracket)) {
        LINK->Symbez = Symbracket; LINK->Symart = Bracket;
      } else if (!strcmp(ObjPointer, Symsepa)) {
        LINK->Symbez = Symsepa; LINK->Symart = Sepa;
      } else if (!strcmp(ObjPointer, Symskip)) {
        LINK->Symbez = Symskip; LINK->Symart = Skip;
      } else if (!strcmp(ObjPointer, Symmeta)) {
        LINK->Symbez = Symmeta; LINK->Symart = Meta;
      } else if (!strcmp(ObjPointer, Symstop)) {
        LINK->Symbez = Symstop; LINK->Symart = Stop;
      } else if (!strcmp(ObjPointer, Symgrammar)) {
  	LINK->Symbez = Symgrammar; LINK->Symart = Grammar;
        LINK->Imgrammatikteil = true;
      } else LINK->Symart = Bezeichner;
      if (LINK->Symart == Bezeichner) LINK->Symbez = ObjPointer;
      else obstack_free(&SymObs, ObjPointer);
    }

    if (Aktmaxsymlaenge < LINK->Symlaenge) Aktmaxsymlaenge = LINK->Symlaenge;
    break;

  /*$page*/
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':   /* ZAHL */
    Verarbeitet = true;
    LINK->Codenr = C - '0';
    obstack_1grow(&SymObs, C); getc(Eindat); C = P_peek(Eindat);

    while (P_inset(C, LINK->Zahlen)) {
	LINK->Symlaenge++;
	LINK->Codenr = LINK->Codenr * 10 + C - '0';
        obstack_1grow(&SymObs, C); getc(Eindat); C = P_peek(Eindat);
    }
    obstack_1grow(&SymObs, '\0');

    LINK->Symbez = (Char *)obstack_finish(&SymObs);
    LINK->Symart = Zahl;
    if (LINK->Codenr > Maxsymnr) {
	Fehler(2L, (long)LINK->Symlaenge, LINK->Symbez);
	  /*ZU GROSSE ZAHL*/
	LINK->Codenr = Maxsymnr;
    }
    break;

  /*$page*/
  case '\'':   /* SYMBOL */
    obstack_1grow(&SymObs, C); getc(Eindat); C = P_peek(Eindat);
    Verarbeitet = true;
    for (;;) {
      if (P_eoln(Eindat)) {
        Fehler(4L, (long)LINK->Symlaenge, LINK->Symbez);
        goto _L111;
      }
      if (C == '\'') {
        getc(Eindat); C = P_peek(Eindat);
        if (C != '\'') goto _L111;
        LINK->Symlaenge++; obstack_1grow(&SymObs, C);
      }
      LINK->Symlaenge++;
      obstack_1grow(&SymObs, C); getc(Eindat); C = P_peek(Eindat);
    }
_L111:
    LINK->Symlaenge++; obstack_1grow(&SymObs, '\'');
    LINK->Symart = Symbol;
    obstack_1grow(&SymObs, '\0'); LINK->Symbez = (Char *)obstack_finish(&SymObs);
    if (LINK->Symlaenge == 2) Fehler(38L, 0L, LINK->Symbez);
    if (Aktmaxsymlaenge < LINK->Symlaenge) Aktmaxsymlaenge = LINK->Symlaenge;
    break;

  /*$page*/
  case '<':   /* SYMBOL */
    LINK->Symlaenge = 0;
    getc(Eindat); C = P_peek(Eindat);

    while (!(P_eoln(Eindat) | (C == '>'))) {
      LINK->Symlaenge++;
      obstack_1grow(&SymObs, C); getc(Eindat); C = P_peek(Eindat);
    }
    obstack_1grow(&SymObs, '\0'); LINK->Symbez = (Char *)obstack_finish(&SymObs);

    if (P_peek(Eindat) != '>') {
      Fehler(4L, (long)LINK->Symlaenge, LINK->Symbez);
    }
    LINK->Symart = Symbol;
    if (Aktmaxsymlaenge < LINK->Symlaenge) Aktmaxsymlaenge = LINK->Symlaenge;
    else {
      if (LINK->Symlaenge == 0) {
	LINK->Symlaenge = 1;
	Fehler(38L, 0L, LINK->Symbez);
	obstack_free(&SymObs, LINK->Symbez); LINK->Symbez = " ";
	}
    }
    break;
  default:
    LINK->Codenr = C;
    C = LINK->Codenr / 100 + '0'; obstack_1grow(&SymObs, C);
    LINK->Codenr %= 100;
    C = LINK->Codenr / 10 + '0'; obstack_1grow(&SymObs, C);
    LINK->Codenr %= 10;
    C = LINK->Codenr + '0'; obstack_1grow(&SymObs, C);
    obstack_1grow(&SymObs, '\0'); LINK->Symbez = (Char *)obstack_finish(&SymObs);
    LINK->Symlaenge = 3;
    Fehler(55L, 3L, LINK->Symbez);
    LINK->Symart = Symbol;
  }

  if (!P_eof(Eindat)) {   /***** EK 7.11.85 ****/
    if (!(Verarbeitet | P_eoln(Eindat)))
      getc(Eindat);
  }

}  /* ENDE VON LIESSYMBOL */

Local Void Freispalten(Dat, Spa, Einschub, LINK)
FILE **Dat;
int Spa, Einschub;
struct LOC_Eingabe *LINK;
{
  /*        ***********/
  long I;

  if (LINK->Druspa + Spa <= Maxdruckspalte) {
    LINK->Druspa += Spa;
    return;
  }
  putc('\n', *Dat);

  for (I = 1; I <= Einschub; I++)
    putc(' ', *Dat);

  LINK->Druspa = Einschub + Spa;
}  /* VON FREISPALTEN */

Local Void Druckevokdat(Z)
Char Z;
{
  /*        ************/
  while (!P_eof(Vokdat)) {
    if (P_peek(Vokdat) == Z) {
      getc(Vokdat);
      while (!P_eoln(Vokdat)) {
	putc(P_peek(Vokdat), Putout);
	getc(Vokdat);
      }
      putc('\n', Putout);
    } else {
      while (!P_eoln(Vokdat))
	getc(Vokdat);
    }

    getc(Vokdat);
  }
  if (Vokdat != NULL)
    Vokdat = freopen("Vokdat", "r", Vokdat);
  else
    Vokdat = fopen("Vokdat", "r");
  if (Vokdat == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Vokdat, Char);
}  /* VON DRUCKEVOKDAT */

/*$page*/
Local Void Druckevokabular(Hntzaehler, LINK)
long *Hntzaehler;
struct LOC_Eingabe *LINK;
{
  /*        ***************/
  /**********************************************************************/
  /* EXTERNAL:                                                          */
  /*          MAXTERMINALCODE                                           */
  /*          .                                                         */
  /**********************************************************************/
  short Unzaehler, Fezaehler, Stzaehler, I, Tzaehler, Ntzaehler;
  Tsymboltyp *WITH;

  Tzaehler = 0;
  Ntzaehler = 0;
  Unzaehler = 0;
  Fezaehler = 0;
  Stzaehler = 0;

  if (Vokdat != NULL) Vokdat = freopen("Vokdat", "w", Vokdat);
  else Vokdat = fopen("Vokdat", "w");
  if (Vokdat == NULL) _EscIO(FileNotFound);
  SETUPBUF(Vokdat, Char);

  for (I = 0; I <= Maxsymnr; I++) {
    if (Symboltabelle[I] != (Tsymboltyp *)0) {
      WITH = Symboltabelle[I];
      /* ENDE VOM case */
	switch ((Symbolart1)WITH->Symart1) {

	case Terminal:
	  Tzaehler++;
	  fprintf(Vokdat, "T%4d%5d  %s",
		  WITH->Symnr, Tzaehler, WITH->Bezeichner);
	  if (P_inset(I, Kellermenge))
	    fprintf(Vokdat, "  KELLER  ");
	  else
	    fprintf(Vokdat, "          ");
	  if (WITH->Symnr > Maxterminalcode)
	    Maxterminalcode = WITH->Symnr;
	  break;

	case Undef:   /* DARF AB 4.10.76 NICHT MEHR VORKOMMEN. */
	  Unzaehler++;
	  fprintf(Vokdat, "U%4d%5d  %s",
		  WITH->Symnr, Unzaehler, WITH->Bezeichner);
	  break;

	case Fehlerhaft:
	  Fezaehler++;
	  fprintf(Vokdat, "F%4d%5d  %s",
		  WITH->Symnr, Fezaehler, WITH->Bezeichner);
	  break;

	case Strukturan:
	  Stzaehler++;
	  fprintf(Vokdat, "S%4d%5d  %s",
		  WITH->Symnr, Stzaehler, WITH->Bezeichner);
	  break;
	default:
	Ntzaehler++;
	fprintf(Vokdat, "N%4d%5d  %s",
		WITH->Symnr, Ntzaehler, WITH->Bezeichner);
      }
      putc('\n', Vokdat);
    }
  }

  if (Vokdat != NULL)
    Vokdat = freopen("Vokdat", "r", Vokdat);
  else
    Vokdat = fopen("Vokdat", "r");
  if (Vokdat == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Vokdat, Char);


  fprintf(Putout, "Terminals                        : %d\n", Tzaehler);
  fprintf(Putout, "Nonterminals                     : %ld\n",
	  Ntzaehler - *Hntzaehler);
  if (*Hntzaehler > 0)
    fprintf(Putout, "Auxiliary nonterminals           : %ld\n", *Hntzaehler);
  if (Stzaehler > 0)
    fprintf(Putout, "Semantic actions                 : %d\n", Stzaehler);
  if (Fezaehler > 0)
    fprintf(Putout, "Erroneous symbols                : %d\n", Fezaehler);
  if (Unzaehler > 0)
    fprintf(Putout, "Undefined symbols                : %d\n", Unzaehler);
  putc('\n', Putout);

  if (P_inset('V', Options)) {
    fprintf(Putout, "The columns have the following meaning :\n");
    fprintf(Putout, "1. Internal encoding\n");
    fprintf(Putout, "2. Symbol number\n");
    fprintf(Putout, "3. Identifier\n\n");
    fprintf(Putout, "Terminals\n");
    fprintf(Putout, "=========\n\n");
    Druckevokdat('T');
    fprintf(Putout, "\nNonterminals\n");
    fprintf(Putout, "============\n\n");
    Druckevokdat('N');
    putc('\n', Putout);
    if (Unzaehler > 0) {
      fprintf(Putout, "Undefined Symbols\n");
      fprintf(Putout, "=================\n\n");
      Druckevokdat('U');
      putc('\n', Putout);
    }

    if (Fezaehler > 0) {
      fprintf(Putout, "Erroneous Symbols\n");
      fprintf(Putout, "=================\n\n");
      Druckevokdat('F');
      putc('\n', Putout);
    }

    if (Stzaehler > 0) {
      fprintf(Putout, "Semantic Actions\n");
      fprintf(Putout, "================\n\n");
      Druckevokdat('S');
      putc('\n', Putout);
    }

  }
  putc('\n', Putout);
}  /* VON DRUCKE-VOKABULAR */

/*$page*/
Local Void Druckemetatabelle(LINK)
struct LOC_Eingabe *LINK;
{
  /*        *****************/
  Tmetatyp *Laeufer;
  Tmetaelement *Element;
  Char I;
  Tsymboltyp *WITH1;

  fprintf(Putout, "Meta Symbols\n");
  fprintf(Putout, "============\n\n");
  for (I = 0; I < Maxsymlaenge; I++) {
    Laeufer = LINK->Metatabhash[(int)I];
    while (Laeufer != (Tmetatyp *)0) {
      fprintf(Putout, "%s :\n        ", Laeufer->Bezeichner);
      LINK->Druspa = 8;
      Element = Laeufer->Kopfelement->Naechstes;
	  /* WEGEN LEEREM KOPFELEMENT */
      while (Element != (Tmetaelement *)0) {
	WITH1 = Symboltabelle[Element->Symnr];
	Freispalten(&Putout, (int)(WITH1->Slaenge + 1), Aktmaxsymlaenge + 2, LINK);
	fprintf(Putout, " %s", WITH1->Bezeichner);
	Element = Element->Naechstes;
      }
      fputs(" .\n", Putout);
      Laeufer = Laeufer->Naechster;
    }
  }
}  /* VON DRUCKEMETATABELLE */

/*$page*/
Local Void Druckebnfgrammatik(Bnfd, A, E, LINK)
FILE **Bnfd;
short A, E;
struct LOC_Eingabe *LINK;
{
  /*        ******************/

  /**********************************************************************/
  /* DIE BNF-GRAMMATIK WIRD BEREITS IM ANSCHLUSS AN DIE EINGABEANALYSE  */
  /* AUF EINE ZWISCHENDATEI AUSGEDRUCKT, WEIL SIE ZUM ZEITPUNKT DER     */
  /* OPTIMIERUNG NICHT MEHR VONNOETEN IST UND NUR SPEICHERPLATZ         */
  /* SCHWIERIGKEITEN BEREITEN WUERDE, WENN SIE BIS ZUM AUSGABEMODUL     */
  /* HINUEBERGERETTET WERDEN SOLLTE. DER AUSDRUCK ERFOLGT NATUERLICH    */
  /* NUR BEI GESETZTER OPTION (B) ODER FEHLERN in DER BNFGRAMMATIK.     */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*           LS,RS,RSFELD,                                            */
  /*           PROGEW,                                                  */
  /*           SYMBOLTABELLE.                                           */
  /*                                                                    */
  /**********************************************************************/
  Tstrukturtyp *Strul;
  Tmodifiktyp *Modil;
  Char C;
  int Einschub, Einschubk, I, J;
  Tlstyp *WITH;
  Trstyp *WITH1;
  long FORLIM1;
  Tsymboltyp *WITH2;

/* p2c: eingabe.p, line 1532: Note: REWRITE does not specify a name [181] */
  if (*Bnfd != NULL)
    rewind(*Bnfd);
  else
    *Bnfd = tmpfile();
  if (*Bnfd == NULL)
    _EscIO(FileNotFound);
  Einschubk = 6;
  fprintf(*Bnfd, "BNF Grammar\n");
  fprintf(*Bnfd, "===========\n\n");
  for (I = A; I <= E; I++) {   /* VOM with */
    WITH = Ls[I - 1];
    WITH1 = &Rs[I - 1];
    fprintf(*Bnfd, "%4d. %s :", I, Symboltabelle[WITH->Symnr]->Bezeichner);
    Einschub = Einschubk + Symboltabelle[WITH->Symnr]->Slaenge + 2;
    LINK->Druspa = Einschub;

    FORLIM1 = WITH1->Rsanfang + WITH1->Rslaenge - 2;
    for (J = WITH1->Rsanfang - 1; J <= FORLIM1; J++) {
      WITH2 = Symboltabelle[Rsfeld[J]];
	switch ((Symbolart1)WITH2->Symart1) {

	case Terminal:
	  Freispalten(Bnfd, (int)(WITH2->Slaenge + 3), Einschub, LINK);
	  fprintf(*Bnfd, " '%s'", WITH2->Bezeichner);
	  break;

	case Nichtterminal:
	  Freispalten(Bnfd, (int)(WITH2->Slaenge + 1), Einschub, LINK);
	  fprintf(*Bnfd, " %s", WITH2->Bezeichner);
	  break;

	case Undef:
	case Fehlerhaft:
	  Freispalten(Bnfd, (int)(WITH2->Slaenge + 3), Einschub, LINK);
	  fprintf(*Bnfd, " ?%s?", WITH2->Bezeichner);
	  break;
	default:
	fprintf(Putout,
	  "*** Error *** : in Druckebnfgrammatik : not (SYMART1 in [TERMINAL,NICHTTERMINAL,UNDEF,FEHLERHAFT])\n");
	}
    }

    Freispalten(Bnfd, 2, Einschub, LINK);
    fprintf(*Bnfd, " .");
    switch (WITH->Zusatz) {

    case false:   /* NIX */
      break;

    case true:
      Strul = WITH->UU.U1.Struktan;
      Modil = WITH->UU.U1.Modifik;
      while (Strul != (Tstrukturtyp *)0) {
	WITH2 = Symboltabelle[Strul->Strukturnr];
	Freispalten(Bnfd, (int)(WITH2->Slaenge + 2), Einschub, LINK);
	fprintf(*Bnfd, " &%s", WITH2->Bezeichner);
	Strul = Strul->Naechste;
      }

      while (Modil != (Tmodifiktyp *)0) {
	WITH2 = Symboltabelle[Modil->Modsymnr];
	if (Modil->Reduziere)
	  C = '@';
	else
	  C = '$';
	Freispalten(Bnfd, (int)(WITH2->Slaenge + 4), Einschub, LINK);
	fprintf(*Bnfd, " %c'%s'", C, WITH2->Bezeichner);
	Modil = Modil->Naechste;
      }
      break;
    }/* VOM case */
    putc('\n', *Bnfd);
  }
  rewind(*Bnfd);
}  /* VON DRUCKEBNFGRAMMATIK */

/*$page*/
Local Void Ergaenzesymtab(Hntnr, LINK)
long *Hntnr;
struct LOC_Eingabe *LINK;
{
  /**********************************************************************/
  /* VOR AUFRUF DIESER PROZEDUR DARF KEIN SYMBOL DES TERMINAL-TEILS     */
  /* DER SYMTAB ERZEUGT WORDEN SEIN, SONST WERDEN DIE TERMINALSYMBOLE   */
  /* NICHT ALS SOLCHE in DIE SYMTAB EINGETRAGEN.                        */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*           MAXSYMNR,                                                */
  /*           AKTMAXSYMNR,                                             */
  /*           USYMBEZ,SYMBEZ,                                          */
  /*           SYMBOLTABELLE,                                           */
  /*           SYMTAB,                                                  */
  /*           MAXSYMLAENGE,                                            */
  /*           MAXSYMZAHL.                                              */
  /*                                                                    */
  /**********************************************************************/
  long I, J, K, L;
  Char Keller[4];
  Tsymboltyp *Symboltabi;
  Tsymtabtyp *Symtabi;
  Tsymboltyp *WITH1;

  if (Symbolda != NULL) Symbolda = freopen("Symbolda", "w", Symbolda);
  else Symbolda = fopen("Symbolda", "w");
  if (Symbolda == NULL) _EscIO(FileNotFound);

  *Hntnr = 0;
  Maxsymzahl = 0;
  for (I = 0; I <= Maxsymnr; I++) {
    Symboltabi = Symboltabelle[I];
    Symtabi = Symtab[I];
    if (Symboltabi == (Tsymboltyp *)0 && Symtabi != (Tsymtabtyp *)0)
    {   /* SYMTAB[I] IST HILFSNICHTTERMINAL */
      Symboltabelle[I] = (Tsymboltyp *)Malloc(sizeof(Tsymboltyp));
      *Hntnr += 1;
      K = *Hntnr;
      J = 0;
      L = 1;
      while (K > 0) {
	Keller[J] = (Char)(K % 10 + '0');
	J++;
	K /= 10;
      }
      obstack_1grow(&SymObs, 'H');
      for (K = J - 1; K >= 0; K--) {
	L++;
	obstack_1grow(&SymObs, Keller[K]);
      }
      WITH1 = Symboltabelle[I];
      WITH1->Bezeichner = (Char *)obstack_finish(&SymObs);
      WITH1->Slaenge = L;
      WITH1->Symnr = I;
      WITH1->Symart1 = (unsigned)Nichtterminal;
      WITH1->Naechster = NULL;
    } else {
      if (Symtabi == (Tsymtabtyp *)0 && Symboltabi != (Tsymboltyp *)0) {
	Symtab[I] = (Tsymtabtyp *)Malloc(sizeof(Tsymtabtyp));   /*TERM);*/
	Symtab[I]->Symart2 = Term;
	{   /*FEHLERHAFT BLEIBT UNVERAENDERT */
	  switch ((Symbolart1)Symboltabi->Symart1) {

	  case Strukturan:
	    Symtab[I]->Symart2 = Symstruk;
	    break;

	  case Nichtterminal:
	    /* TRITT NUR EIN, WENN EIN NICHTTERMINAL ZWAR
	       ERKANNT WURDE, ABER KEINE BNF-PRODUKTION DAZU ERZEUGT
	       WURDE, WEIL EIN FEHLER in DER EINGABE FESTGESTELLT
	       WURDE. */
	    Symtab[I]->Symart2 = Term;
	    break;

	  /* DAMIT in KANONISIERE NICHT FOLGEFEHLER WEGEN
	     NICHTTERMINALISIERBARKEIT AUFTRETEN ! */
	  case Undef:
	  case Terminal:
	    Symtab[I]->Symart2 = Term;
	    Symboltabi->Symart1 = (unsigned)Terminal;
	  default:
	    break;
	  }
	}
      }
    }
    if (Symboltabelle[I] != NULL) {
      Maxsymzahl++;
      Aktmaxsymnr = I;
      WITH1 = Symboltabelle[I];
      /* BESCHREIBE DIE SYM'BOL'D'ATEI' UND ERZEUGE DIE
         ABBILDUNGEN TAB, NTAB UND  INAB */
	switch ((Symbolart1)WITH1->Symart1) {

	case Terminal:
	  Aktmaxterm++;
	  Tab[Aktmaxterm - 1] = I;
	  Inab[I] = Aktmaxterm;
	  break;

	case Nichtterminal:
	  Aktmaxnterm++;
	  Ntab[Aktmaxnterm - 1] = I;
	  Inab[I] = Aktmaxnterm;
	  break;
	default:
	  ;
	}
      fprintf(Symbolda, "%5ld%4d %s\n", I, WITH1->Slaenge, WITH1->Bezeichner);
    }
  }
  if (Aktmaxterm > Maxterm)
    Bnffehler(49L, (long)Aktmaxterm, 0L, LINK->Symbez);
  if (Aktmaxnterm > Maxnterm)
    Bnffehler(50L, (long)Aktmaxnterm, 0L, LINK->Symbez);

  /* BLEIBT UNVERAENDERT */
}  /* VON ERGAENZESYMTAB */

Local Void Minmaxbnffehler(Min, Max)
short *Min, *Max;
{
  /*        ***************/
  /**********************************************************************/
  /* EXTERNAL:                                                          */
  /*           MAXPRODNR,                                               */
  /*           FEHLERDA.                                                */
  /**********************************************************************/
  long I;

  if (Fehlerda != NULL)
    Fehlerda = freopen("Fehlerda", "r", Fehlerda);
  else
    Fehlerda = fopen("Fehlerda", "r");
  if (Fehlerda == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Fehlerda, Char);
  *Min = Maxprodnr;
  *Max = 1;
  while (P_peek(Fehlerda) != '#') {
    fscanf(Fehlerda, "%*[^\n]");
    getc(Fehlerda);
  }

  fscanf(Fehlerda, "%*[^\n]");

  getc(Fehlerda);
  while (!P_eof(Fehlerda)) {
    FehlerdaInt(&I);
    if (*Min > I)
      *Min = I;
    if (*Max < I)
      *Max = I;
    fscanf(Fehlerda, "%*[^\n]");
    getc(Fehlerda);
  }
  if (Fehlerda != NULL)
    Fehlerda = freopen("Fehlerda", "r", Fehlerda);
  else
    Fehlerda = fopen("Fehlerda", "r");
  if (Fehlerda == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Fehlerda, Char);
  /* SETZE DEN DATEIZEIGER WIEDER AN SEINEN URSPRUENGLICHEN ORT */
  while (P_peek(Fehlerda) != '#') {
    fscanf(Fehlerda, "%*[^\n]");
    getc(Fehlerda);
  }

}  /* VON MINMAXBNFFEHLER */

Local Void Lrvoraus(LINK)
struct LOC_Eingabe *LINK;
{
  /*        ********/
  long I, J;
  short Schnittsymbol;
  long FORLIM;
  Trstyp *WITH;
  long FORLIM1;
  Tsymboltyp *WITH1;

  Schnittsymbol = 0;
  FORLIM = Aktmaxprodnr;
  for (I = 1; I <= FORLIM; I++) {
    WITH = &Rs[I - 1];
    if (WITH->Rslaenge > 0) {
      FORLIM1 = WITH->Rsanfang + WITH->Rslaenge - 2;
      for (J = WITH->Rsanfang - 1; J <= FORLIM1; J++) {
	WITH1 = Symboltabelle[Rsfeld[J]];
	if (Rsfeld[J] == Startsymnr)
	  Bnffehler(44L, I, (long)WITH1->Slaenge, WITH1->Bezeichner);
      }
    }
  }

  if (Keinefehler) {
    Startproduktion = Symtab[Startsymnr]->UU.U2.Lseite;
    if (Rs[Startproduktion - 1].Rslaenge < 1)
      Bnffehler(46L, (long)Startproduktion, 0L, LINK->Symbez);
    if (Ls[Startproduktion - 1]->Naechste != 0)
      Bnffehler(47L, (long)Startproduktion, 0L, LINK->Symbez);
  }
  /* ZERTEILER-FEHLERBEHANDLUNGS-TEST */
  Zusymbol(Semklammer, Stopsymnr);
  if (!Leerschnittmenge(Semklammer, Ueberlesen, &Schnittsymbol))
    Bnffehler(57L, (long)Schnittsymbol, 0L, LINK->Symbez);
  if (!Leerschnittmenge(Separator, Ueberlesen, &Schnittsymbol))
    Bnffehler(58L, (long)Schnittsymbol, 0L, LINK->Symbez);
}  /* VON LRVORAUS */

Local Void Kanonisiere(LINK)
struct LOC_Eingabe *LINK;
{
  /*        ***********/
  /**********************************************************************/
  /* ZUERST WERDEN DIE GEWICHTE DER GRAMMATIKSYMBOLE BESTIMMT.          */
  /* DANN WERDEN DIE PRODUKTIONEN BEWERTET UND FUER JEDES NICHT-        */
  /* TERMINAL WIRD EINE KANONISCHE PRODUKTIONENORDNUNG NACH DEM         */
  /* KRITERIUM DES MINIMALEN PRODUKTIONSGEWICHT ERZEUGT.                */
  /*                                                                    */
  /* F[I] : V -> N                                                      */
  /*               < 1           FALLS X AUS T                          */
  /* F[0](X) =     <                                                    */
  /*               < UNENDLICH   SONST                                  */
  /*                                                                    */
  /*               < 1           FALLS X AUS T                          */
  /* F[I](X) =     <                                                    */
  /*               < MIN( SUM(J=1,N)(F[I-1](X[J]))/ X -> X[1]...X[N])   */
  /*                                                                    */
  /* in DIESER PROZEDUR GILT: F[I](X) = GEW[X] .                        */
  /*                                                                    */
  /**********************************************************************/
  boolean Sortiere, Naechsterschritt;
  long Gew[Maxsymnr + 1];
  long Null, Eins, Zwei, Gewi, I, J, Umkehr, FORLIM;
  Tlstyp *WITH;
  Trstyp *WITH1;
  long FORLIM1;
  Tsymtabtyp *WITH2;

  FORLIM = Aktmaxsymnr;
  /* GEWICHTE DIE GRAMMATIKSYMBOLE */
  for (I = 0; I <= FORLIM; I++) {
    if (Symtab[I] != (Tsymtabtyp *)0) {
      if (Symtab[I]->Symart2 == Term)
	Gew[I] = 1;
      else
	Gew[I] = Unendlich;
    } else
      Gew[I] = Unendlich;
  }
  Naechsterschritt = true;
  Umkehr = 0;
  /* ITERATION  ZUR BESTIMMUNG DER NICHTTERMINALGEWICHTE */
  while (Naechsterschritt) {
    Naechsterschritt = false;
    for (I = Aktmaxprodnr; I >= 1; I--) {
      WITH = Ls[labs(I - Umkehr) - 1];
      WITH1 = &Rs[labs(I - Umkehr) - 1];
      /* BEI DIESER RICHTUNG DER LAUFANWEISUNG WIRD BERUECKSICHTIGT,
         DASS DIE 'TERMINALEREN' PRODUKTIONEN GEWOEHNLICH AM ENDE
         DER GRAMMATIK STEHEN. DOCH NACH DEM ERSTEN DURCHGANG WIRD
         DIE GRAMMATIK NACH DEM PRINZIP 'RAUF-RUNTER-RAUF-RUNTER'
         DURCHLAUFEN */
      Gewi = 0;
      FORLIM1 = WITH1->Rsanfang + WITH1->Rslaenge - 2;
      for (J = WITH1->Rsanfang - 1; J <= FORLIM1; J++)
	Gewi += Gew[Rsfeld[J]];
      if (Gewi < Gew[WITH->Symnr]) {   /* =>  GEWI<UNENDLICH */
	Naechsterschritt = true;
	Gew[WITH->Symnr] = Gewi;
      }
    }
    if (Umkehr == 0)
      Umkehr = Aktmaxprodnr + 1;
    else
      Umkehr = 0;
  }
  /* MARKIERE DIE EPSILON-NICHTTERMINALE */
  if (Keinefehler) {
    FORLIM = Aktmaxnterm;
    for (I = 0; I < FORLIM; I++)
      Symtab[Ntab[I]]->UU.U2.Epsilon = (Gew[Ntab[I]] == 0);
  }
  FORLIM = Aktmaxprodnr;
  /* GEWICHTE DIE PRODUKTIONEN */
  for (I = 1; I <= FORLIM; I++) {
    WITH1 = &Rs[I - 1];
    Gewi = 0;
    FORLIM1 = WITH1->Rsanfang + WITH1->Rslaenge - 2;
    for (J = WITH1->Rsanfang - 1; J <= FORLIM1; J++)
      Gewi += Gew[Rsfeld[J]];
    LINK->Progew[I - 1] = Gewi;
    if (Gewi >= Unendlich)
      Bnffehler(48L, I, Symboltabelle[Ls[I-1]->Symnr]->Slaenge,
                        Symboltabelle[Ls[I-1]->Symnr]->Bezeichner);
  }
  FORLIM = Aktmaxnterm;
  /* KANONISIERE */
  for (I = 0; I < FORLIM; I++) {
    WITH2 = Symtab[Ntab[I]];
    /* SYMTAB[NTAB[I]]<>nil <= LS[LSEITE]<>nil */
    if (WITH2->UU.U2.Lseite > 0 && WITH2->UU.U2.Lseite <= Maxprodnr)
    {   /* <= KEINEFEHLER */
      if (Ls[WITH2->UU.U2.Lseite - 1] != NULL) {   /* <= KEINEFEHLER */
	if (Ls[WITH2->UU.U2.Lseite - 1]->Naechste != 0) {
	  Sortiere = true;
	  while (Sortiere) {
	    /* SORTIEREN DURCH VERTAUSCHEN OHNE
	                         OPTIMIERUNG */
	    Sortiere = false;
	    Null = WITH2->UU.U2.Lseite;
	    Eins = Ls[Null - 1]->Naechste;
	    if (LINK->Progew[Null - 1] > LINK->Progew[Eins - 1]) {
	      WITH2->UU.U2.Lseite = Eins;
	      Ls[Null - 1]->Naechste = Ls[Eins - 1]->Naechste;
	      Ls[Eins - 1]->Naechste = Null;
	      Sortiere = true;
	    }
	    Null = WITH2->UU.U2.Lseite;
	    Eins = Ls[Null - 1]->Naechste;
	    Zwei = Ls[Eins - 1]->Naechste;
	    while (Zwei != 0) {
	      if (LINK->Progew[Eins - 1] > LINK->Progew[Zwei - 1]) {
		Ls[Null - 1]->Naechste = Zwei;
		Ls[Eins - 1]->Naechste = Ls[Zwei - 1]->Naechste;
		Ls[Zwei - 1]->Naechste = Eins;
		Sortiere = true;
	      }
	      Null = Ls[Null - 1]->Naechste;
	      Eins = Ls[Null - 1]->Naechste;
	      Zwei = Ls[Eins - 1]->Naechste;
	    }
	  }
	}
      }
    }
  }
}  /* VON KANONISIERE */

Local Void Ueberfluessig(LINK)
struct LOC_Eingabe *LINK;
{
  /*        *************/
  /**********************************************************************/
  /* DIESE PROZEDUR UNTERSUCHT DIE EINGABEGRAMMATIK AUF UEBERFLUESSIGE  */
  /* PRODUKTIONEN, INDEM VON DER STARTPRODUKTION AUSGEHEND DIE          */
  /* ERREICHBARKEIT ALLER NICHTTERMINALE UNTERSUCHT WIRD.               */
  /*                                                                    */
  /* INITIALISIERUNG                                                    */
  /* ERREICHBAR[I] = false FUER 0<I<=AKTMAXNTERM                        */
  /* NTK : array[NTERMINALBEREICH] of NTERMINALBEREICH;                 */
  /* NTK = NICHTTERMINALKELLER                                          */
  /* NT : NTERMINALBEREICH;                                             */
  /* NT:=''STARTSYMBOL'';                                               */
  /* J:=1;                                                              */
  /* NTK[J]:=NT;                                                        */
  /* ERREICHBAR[NT]:=true;                                              */
  /* while J>0 do                                                       */
  /* begin                                                              */
  /*   NT:=NTK[J]; J:=J-1;                                              */
  /*   DURCHSUCHE RS ALLER P MIT LS[P]=NT:                              */
  /*   if RS[P,I] in N and ( not ERREICHBAR[RS[P,I]]) then              */
  /*   begin                                                            */
  /*     J:=J+1;                                                        */
  /*     NTK[J]:=RS[P,I];                                               */
  /*     ERREICHBAR[RS[P,I]]:=true;                                     */
  /*   end;                                                             */
  /* end;                                                               */
  /*                                                                    */
  /* ERREICHBAR[I]  <=> I ERREICHBAR VOM ''STARTSYMBOL''                */
  /**********************************************************************/
  long I;
  short Rsnr;   /* RECHTE-SEITE SYMBOLNUMMER */
  short J;   /* KELLERPEGEL */
  short N;   /* NICHTTERMINAL */
  short P;   /* PRODUKTIONSNUMMER */
  boolean Erreichbar[Maxnterm];
  short Ntk[Maxnterm];
  long FORLIM;
  Tlstyp *WITH;
  Trstyp *WITH1;
  short FORLIM1;
  Tsymtabtyp *WITH2;
  Tsymboltyp *WITH3;

  /* NICHTTERMINALKELLER */

  FORLIM = Aktmaxnterm;
  /* INITIALISIERUNG */
  for (I = 0; I < FORLIM; I++)
    Erreichbar[I] = false;
  N = Inab[Startsymnr];
  J = 1;
  Ntk[J - 1] = N;
  Erreichbar[N - 1] = true;
  /* INITIALISIERUNGSENDE */

  while (J > 0) {
    N = Ntk[J - 1];
    J--;
    P = Symtab[Ntab[N - 1]]->UU.U2.Lseite;

    while (P > 0) {   /* P=0 */
      WITH = Ls[P - 1];
      WITH1 = &Rs[P - 1];
      FORLIM = WITH1->Rsanfang + WITH1->Rslaenge - 2;
      for (I = WITH1->Rsanfang - 1; I <= FORLIM; I++) {
	Rsnr = Rsfeld[I];
	if (((1L << ((long)Symtab[Rsnr]->Symart2)) &
	     ((1L << ((long)Nt)) | (1L << ((long)Hilfnt)))) != 0) {
	  if (!Erreichbar[Inab[Rsnr] - 1]) {
	    J++;
	    Ntk[J - 1] = Inab[Rsnr];
	    Erreichbar[Inab[Rsnr] - 1] = true;
	  }
	}
      }
      P = WITH->Naechste;
    }
  }  /* J=0 */

  FORLIM1 = Aktmaxnterm;
  for (N = 0; N < FORLIM1; N++) {
    if (!Erreichbar[N]) {
      WITH2 = Symtab[Ntab[N]];
      WITH3 = Symboltabelle[Ntab[N]];
      Bnffehler(59L, (long)WITH2->UU.U2.Lseite, (long)WITH3->Slaenge,
		WITH3->Bezeichner);
    }
  }
}  /* VON UEBERFLUESSIG  */

/* Local variables for Lalreingabe: */
struct LOC_Lalreingabe {
  struct LOC_Eingabe *LINK;
  jmp_buf _JL1;
  /* EINGABE-ANALYSE-ABBRUCH */

  long Symbolmenge, Elemenge;
} ;

/*$page*/
Local boolean Fehlerpunkt(Nummer, LINK)
long Nummer;
struct LOC_Lalreingabe *LINK;
{
  /*       ***********/
  /**********************************************************************/
  /* EXTERNAL:                                                          */
  /*           SYMLAENGE,                                               */
  /*           USYMBEZ,                                                 */
  /*           SYMART.                                                  */
  /*                                                                    */
  /* DIESE FUNKTION GIBT EINE FEHLERMELDUNG AUS UND SUCHT DANN          */
  /* NACH EINEM DER AUFFANGZEICHEN DATEND,DOLLAR ODER PUNKT             */
  /* UND SETZT IM FALLE VON PUNKT DEN LESEZEIGER AUF DAS DARAUF-        */
  /* FOLGENDE SYMBOL.                                                   */
  /* SIE WIRD in DEN PROZEDUREN CODETEIL,KELLERTEIL UND METATEIL        */
  /* BENUTZT.                                                           */
  /*                                                                    */
  /**********************************************************************/
  Fehler(Nummer, (long)LINK->LINK->Symlaenge, LINK->LINK->Symbez);
  while (((1L << ((long)LINK->LINK->Symart)) & ((1L << ((long)Datend)) |
	    (1L << ((long)Dollar)) | (1L << ((long)Punkt)))) == 0)
    Liessymbol(LINK->LINK);
  if (LINK->LINK->Symart == Punkt) {
    Liessymbol(LINK->LINK);
    return true;
  } else
    return false;
}  /* VON FEHLERPUNKT */

Local Void Fehlerinstand(Nummer, Dahinter, LINK)
long Nummer;
boolean Dahinter;
struct LOC_Lalreingabe *LINK;
{
  /*        *************/
  /**********************************************************************/
  /* DIESE PROZEDUR GIBT EINE FEHLERMELDUNG AUS, SUCHT DANN NACH        */
  /* DEM AUFFANGZEICHEN PUNKT ODER DATEND UND SETZT DEN LESEZEIGER,     */
  /* FALLS DAHINTER=true IST, AUF DAS DARAUFFOLGENDE SYMBOL.            */
  /* SIE WIRD in DEN PROZEDUREN INNERHALB DES GRAMMATIKTEILS BENUTZT.   */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*           SYMLAENGE,                                               */
  /*           USYMBEZ,                                                 */
  /*           SYMART.                                                  */
  /*                                                                    */
  /**********************************************************************/
  Fehler(Nummer, (long)LINK->LINK->Symlaenge, LINK->LINK->Symbez);
  while (((1L << ((long)LINK->LINK->Symart)) &
	  ((1L << ((long)Datend)) | (1L << ((long)Punkt)))) == 0)
    Liessymbol(LINK->LINK);
  Dahinter = (Dahinter && LINK->LINK->Symart != Datend);
  if (Dahinter)
    Liessymbol(LINK->LINK);
}  /* VON FEHLERINSTAND */

/*$page*/
Local short Freiesymnr(I, J, LINK)
long *I, *J;
struct LOC_Lalreingabe *LINK;
{
  /*       **********/
  /**********************************************************************/
  /* DIESE FUNKTION SUCHT VON J*MAXBITS2+I BEGINNEND AUFWAERTS IM       */
  /* KOMPLEMENT DER MENGE SYMNRMENGE DIE ERSTE FREIE SYMBOLNUMMER UND   */
  /* LIEFERT SIE ALS FUNKTIONSWERT AB. DABEI FUEGT SIE DIESE NUMMER DER */
  /* SYMNRMENGE HINZU.                                                  */
  /* WENN KEINE FREIE NUMMER MEHR VORHANDEN IST, WIRD DIE PROGRAMM-     */
  /* AUSFUEHRUNG MIT DER FEHLERELDUNG 15 ABGEBROCHEN.                   */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*           SYMNRMENGE,                                              */
  /*           MAXBITS2,                                                */
  /*           MAXSYMSETINDEX.                                          */
  /*                                                                    */
  /**********************************************************************/
  unsigned K;
  long Hfreisym;
  
  K = *J * Maxbits2 + *I;
  while (P_inset((int) K, LINK->LINK->Symnrmenge)) 
    K++;
   
  Hfreisym = K;
  if (Hfreisym > Maxsymnr) {
    Fehler(15L, (long)LINK->LINK->Symlaenge, LINK->LINK->Symbez);
    longjmp(LINK->_JL1, 1);   /* SPRUNG ANS ENDE VON LALREINGABE */
    /*******************************************/
  }
  *J = K / Maxbits2;   /* ONLY BASETYPE VARIABLE ALLOWED in SETS */
  *I = K & (Maxbits2 - 1);

  P_addset(LINK->LINK->Symnrmenge, K);
  return Hfreisym;
}  /* VON FREIESYMNR */

Local Void Streiche(Symnr, LINK)
short Symnr;
struct LOC_Lalreingabe *LINK;
{
  /*        ********/
  
  P_remset(LINK->LINK->Symnrmenge, Symnr);
}  /* VON STREICHE */

/*$page*/
Local Tsymboltyp *Suchsymbol(Symbez, Laenge, Ssymart1, Gefunden, LINK)
Char *Symbez;
int Laenge;
Symbolart1 Ssymart1;
boolean *Gefunden;
struct LOC_Lalreingabe *LINK;
{
  /*       **********/
  /**********************************************************************/
  /* DIESE FUNKTION SUCHT in DER HASHTABELLE SYMBOLTABHASH UNTER DEM    */
  /* EINTRAG LAENGE LEXIKOGRAPHISCH NACH DEM SYMBOL SYMBEZ.             */
  /* BEI NICHTFINDEN TRAEGT SIE EIN NEUES SYMBOL VON DER ART            */
  /* SSYMART1 in DIE DURCHSUCHTE LISTE EIN.                             */
  /* DAS ERGEBNIS DER FUNKTION IST AUF JEDEN FALL EIN VERWEIS AUF DAS   */
  /* GESUCHTE SYMBOL in DER SYMBOLTABHASH.                              */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*           SYMBOLTABHASH.                                           */
  /*                                                                    */
  /**********************************************************************/
/* p2c: eingabe.p, line 2183:
 * Warning: Symbol 'Result' was already defined [220] */
  Tsymboltyp *Result;   /* WEGEN SIEMENS-PASCAL-FEHLER */
  Tsymboltyp *Laeufer, *Vorlaeufer, *WITH, *WITH1;

  Laeufer = LINK->LINK->Symboltabhash[Laenge % Maxsymlaenge];
  if (Laeufer == (Tsymboltyp *)0) {
    LINK->LINK->Symboltabhash[Laenge % Maxsymlaenge] = (Tsymboltyp *)Malloc(sizeof(Tsymboltyp));
    WITH = LINK->LINK->Symboltabhash[Laenge % Maxsymlaenge];
    WITH->Bezeichner = Symbez;
    WITH->Symart1 = (unsigned)Ssymart1;
    WITH->Slaenge = Laenge;
    WITH->Naechster = NULL;
    Result = LINK->LINK->Symboltabhash[Laenge % Maxsymlaenge];
    return Result;
  }
  /* LEERE LISTE */
  if (strcmp(Laeufer->Bezeichner, Symbez) > 0) {
    LINK->LINK->Symboltabhash[Laenge % Maxsymlaenge] = (Tsymboltyp *)Malloc(sizeof(Tsymboltyp));
    WITH = LINK->LINK->Symboltabhash[Laenge % Maxsymlaenge];
    WITH->Naechster = Laeufer;
    WITH->Bezeichner = Symbez;
    WITH->Symart1 = (unsigned)Ssymart1;
    WITH->Slaenge = Laenge;
    Result = LINK->LINK->Symboltabhash[Laenge % Maxsymlaenge];
    return Result;
  }
  /* VORNE EINFUEGEN */
  if (!strcmp(Laeufer->Bezeichner, Symbez)) {
    /* GEFUNDEN 1*/
    *Gefunden = true;
    Result = Laeufer;
    return Result;
  }
  Vorlaeufer = Laeufer->Naechster;
  /* LAEUFER^.BEZEICHNER<SYMBEZ */

  if (Vorlaeufer != (Tsymboltyp *)0)
    Bad = (strcmp(Vorlaeufer->Bezeichner, Symbez) < 0);
  else
    Bad = false;

  while (Bad) {
    Laeufer = Vorlaeufer;
    Vorlaeufer = Vorlaeufer->Naechster;

    if (Vorlaeufer != (Tsymboltyp *)0)
      Bad = (strcmp(Vorlaeufer->Bezeichner, Symbez) < 0);
    else
      Bad = false;
  }
  /* LAEUFER^.BEZEICHNER<SYMBEZ UND (VORLAEUFER=nil ODER
     VORLAEUFER^.BEZEICHNER>=SYMBEZ) */
  if (Vorlaeufer == (Tsymboltyp *)0) {
    Laeufer->Naechster = (Tsymboltyp *)Malloc(sizeof(Tsymboltyp));
    WITH1 = Laeufer->Naechster;
    WITH1->Bezeichner = Symbez;
    WITH1->Symart1 = (unsigned)Ssymart1;
    WITH1->Slaenge = Laenge;
    WITH1->Naechster = NULL;
    Result = Laeufer->Naechster;
    return Result;
  }
  /* AM ENDE EINFUEGEN */
  if (!strcmp(Vorlaeufer->Bezeichner, Symbez)) {
    /* GEFUNDEN 2 */
    *Gefunden = true;
    Result = Vorlaeufer;
    return Result;
  }
  Laeufer->Naechster = (Tsymboltyp *)Malloc(sizeof(Tsymboltyp));
  WITH1 = Laeufer->Naechster;
  WITH1->Naechster = Vorlaeufer;
  WITH1->Bezeichner = Symbez;
  WITH1->Symart1 = (unsigned)Ssymart1;
  WITH1->Slaenge = Laenge;
  Result = Laeufer->Naechster;
  return Result;

  /* in DER MITTE EINFUEGEN */
}  /* VON SUCHSYMBOL */

/*$page*/
Local Tsymboltyp *Suchetsymbol(Symbez, Laenge, Gefunden, LINK)
Char *Symbez;
int Laenge;
boolean *Gefunden;
struct LOC_Lalreingabe *LINK;
{
  /*       ************/
  /**********************************************************************/
  /* DIESE FUNKTION SUCHT in DER HASHTABELLE SYMBOLTABHASH UNTER DEM    */
  /* EINTRAG LAENGE LEXIKOGRAPHISCH NACH DEM SYMBOL SYMBEZ.             */
  /* BEI NICHTFINDEN TRAEGT SIE EIN NEUES SYMBOL VON DER ART            */
  /* TERMINAL in DIE DURCHSUCHTE LISTE EIN.                             */
  /* DAS ERGEBNIS DER FUNKTION IST AUF JEDEN FALL EIN VERWEIS AUF DAS   */
  /* GESUCHTE SYMBOL in DER SYMBOLTABHASH.                              */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*           SYMBOLTABHASH.                                           */
  /*                                                                    */
  /**********************************************************************/
  *Gefunden = false;
  return (Suchsymbol(Symbez, Laenge, Terminal, Gefunden, LINK));
}  /* VON SUCHETSYMBOL */

Local Tsymboltyp *Suchentsymbol(Symbez, Laenge, LINK)
Char *Symbez;
int Laenge;
struct LOC_Lalreingabe *LINK;
{
  /*       *************/
 /**********************************************************************/
  /* DIESE FUNKTION SUCHT in DER HASHTABELLE SYMBOLTABHASH UNTER DEM    */
  /* EINTRAG LAENGE LEXIKOGRAPHISCH NACH DEM SYMBOL SYMBEZ.             */
  /* BEI NICHTFINDEN TRAEGT SIE EIN NEUES SYMBOL VON DER ART            */
  /* NICHTTERMINAL in DIE SYMTABHASH UND MIT EINER NOCH FREIEN SYMBOL-  */
  /* NUMMER in DIE SYMBOLTABELLE EIN.                                   */
  /* IST DIE SYMART1 DES GEFUNDENEN SYMBOLS 'UNDEF' DANN WIRD SIE in    */
  /* 'NICHTTERMINAL' GEAENDERT.                                         */
  /* DAS ERGEBNIS DER FUNKTION IST AUF JEDEN FALL EIN VERWEIS AUF DAS   */
  /* GESUCHTE SYMBOL in DER SYMBOLTABHASH.                              */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*           CODENR,                                                  */
  /*           FREIESYMNR,                                              */
  /*           LETZTSYMI,                                               */
  /*           LETZTSYMJ,                                               */
  /*           SYMBOLTABELLE,                                           */
  /*           SYMBOLTABHASH.                                           */
  /*                                                                    */
  /**********************************************************************/
  Tsymboltyp *Ntsym;
  boolean Gefunden;

  Gefunden = false;
  Ntsym = Suchsymbol(Symbez, Laenge, Nichtterminal, &Gefunden, LINK);
  if (Gefunden) {
    if ((Symbolart1)Ntsym->Symart1 == Undef)
      Ntsym->Symart1 = (unsigned)Nichtterminal;
    return Ntsym;
  }
  LINK->LINK->Codenr = Freiesymnr (&LINK->LINK->Letztsymi,
				   &LINK->LINK->Letztsymj, LINK);
  Ntsym->Symnr = LINK->LINK->Codenr;
  Symboltabelle[LINK->LINK->Codenr] = Ntsym;
  return Ntsym;
}  /* VON SUCHENTSYMBOL */

/*$page*/
Local Void Suchesymbol(Symbez, Laenge, Art, Elemnr, Metasym, Gefunden, LINK)
Char *Symbez;
int Laenge;
Elemart *Art;
short *Elemnr;
Tmetatyp **Metasym;
boolean *Gefunden;
struct LOC_Lalreingabe *LINK;
{
  /*        ***********/
  /**********************************************************************/
  /* DIESE PROZEDUR SUCHT ZUERST in DER METATABHASH SEQUENTIELL UND     */
  /* BEI NICHTFINDEN in DER SYMTABHASH LEXIKOGAPHISCH NACH DEM SYMBOL   */
  /* SYMBEZ, JEWEILS MIT DEM SCHLUESSEL LAENGE .                        */
  /* BEI NICHTFINDEN TRAEGT SIE EIN NEUES SYMBOL VON DER ART            */
  /* UNDEF in DIE SYMTABHASH UND MIT EINER NOCH FREIEN SYMBOL-          */
  /* NUMMER in DIE SYMBOLTABELLE EIN.                                   */
  /* ALS ERGEBNIS LIEFERT SIE DIE ART (MET,SYM) UND JE NACH ART EINEN   */
  /* VERWEIS ELEMNR ODER METASYM AUF DAS ENTSPRECHENDE SYMBOL.          */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*            FREIESYMNR,                                             */
  /*           METATABHASH,                                             */
  /*           SYMBOLTABELLE,                                           */
  /*           SYMBOLTABHASH.                                           */
  /*                                                                    */
  /**********************************************************************/
  Tsymboltyp *Elemsym;

  *Gefunden = false;
  /* SUCHE in DER METATABHASH */
  *Metasym = LINK->LINK->Metatabhash[Laenge % Maxsymlaenge];

  if (*Metasym != (Tmetatyp *)0)
    Bad = (strcmp((*Metasym)->Bezeichner, Symbez) != 0);
  else
    Bad = false;

  while (Bad) {
    *Metasym = (*Metasym)->Naechster;

    if (*Metasym != (Tmetatyp *)0)
      Bad = (strcmp((*Metasym)->Bezeichner, Symbez) != 0);
    else
      Bad = false;
  }

  if (*Metasym != (Tmetatyp *)0) {
    /* METASYM^.BEZEICHNER=SYMBEZ */
    *Art = Met;
    *Gefunden = true;
    return;
  }
  /* SUCHE in DER SYMBOLTABHASH */
  *Art = Sym;
  Elemsym = Suchsymbol(Symbez, Laenge, Undef, Gefunden, LINK);
  if (*Gefunden) {
    *Elemnr = Elemsym->Symnr;
    return;
  }
  *Elemnr = Freiesymnr(&LINK->LINK->Letztsymi, &LINK->LINK->Letztsymj, LINK);
  Elemsym->Symnr = *Elemnr;
  Symboltabelle[*Elemnr] = Elemsym;

  /* VON SUCHE in DER SYMBOLTABHASH */
}  /* VON SUCHESYMBOL */

/*$page*/
Local Void Codeteil(LINK)
struct LOC_Lalreingabe *LINK;
{
  /*        ********/
  /**********************************************************************/
  /* SYMBOLE VON FEHLERHAFTEN KODIERUNGSANWEISUNGEN STEHEN NICHT        */
  /* in DER SYMBOLTABELLE (HABEN ALSO KEINE KODIERUNG) WOHL ABER        */
  /* in DER SYMBOLTABHASH.                                              */
  /*                                                                    */
  /**********************************************************************/
  /* DATEIENDE ODER DOLLAR ERREICHT */
  Tsymboltyp *Codesym;
  boolean Schonda;

  if (LINK->LINK->Symart != Code) {
    return;
  }  /* SYMART=CODE */
  Liessymbol(LINK->LINK);
  while (LINK->LINK->Symart != Dollar) {
    if (((1L << ((long)LINK->LINK->Symart)) & LINK->Symbolmenge) == 0)
    {  /*FALSCHE LINKE SEITE */
      if (!Fehlerpunkt(7L, LINK))
	goto _L9999;
      continue;
    }
    Codesym = Suchetsymbol(LINK->LINK->Symbez, LINK->LINK->Symlaenge,
			   &Schonda, LINK);
    if (Schonda) {  /* MEHRFACHDEFINITION */
      if (!Fehlerpunkt(8L, LINK))
	goto _L9999;
      continue;
    }
    Liessymbol(LINK->LINK);
    Codesym->Symnr = 0;   /* INITIALISIERUNG */
    if (LINK->LINK->Symart != Gleich) {  /* '=' FEHLT */
      if (!Fehlerpunkt(9L, LINK))
	goto _L9999;
      continue;
    }
    Liessymbol(LINK->LINK);
    if (LINK->LINK->Symart != Zahl) {  /* CODIERUNG IST KEINE ZAHL */
      if (!Fehlerpunkt(10L, LINK))
	goto _L9999;
      continue;
    }
    if (Symboltabelle[LINK->LINK->Codenr] != NULL)
    {  /* MEHRDEUTIGE CODIERUNG */
      if (!Fehlerpunkt(11L, LINK))
	goto _L9999;
      continue;
    }
    Symboltabelle[LINK->LINK->Codenr] = Codesym;
    Symboltabelle[LINK->LINK->Codenr]->Symnr = LINK->LINK->Codenr;
    /* TRAGESYMNR(CODENR) EIN */
   
    P_addset(LINK->LINK->Symnrmenge, LINK->LINK->Codenr);

    Liessymbol(LINK->LINK);
    if (LINK->LINK->Symart != Punkt) {  /* SCHLIESSENDER '.' FEHLT */
      if (!Fehlerpunkt(12L, LINK))
	goto _L9999;
    } else
      Liessymbol(LINK->LINK);
  }
  /* SYMART=DOLLAR */
_L9999:   /* DOLLAR ODER DATEIENDE GEFUNDEN */
  Liessymbol(LINK->LINK);

  /* 0<=CODENR<=MAXSYMNR ?||||| */
  /* SYMBOLTABELLE[CODENR]=nil */
  /* SYMART=GLEICH */
  /* SCHONDA=false */
  /* SYMART in SYMBOLMENGE */
}  /* VOM CODETEIL */

/*$page*/
Local Void Kellerteil(LINK)
struct LOC_Lalreingabe *LINK;
{
  /*        **********/
  Tsymboltyp *Kellersym;
  boolean Schonda;

  if (LINK->LINK->Symart != Stack) {
    return;
  }  /* SYMART=STACK */
  Liessymbol(LINK->LINK);
  while (LINK->LINK->Symart != Dollar) {
    if (((1L << ((long)LINK->LINK->Symart)) & LINK->Symbolmenge) == 0) {
      if (!Fehlerpunkt(13L, LINK))
	goto _L9999;
      continue;
    }
    Kellersym = Suchetsymbol(LINK->LINK->Symbez, LINK->LINK->Symlaenge,
			     &Schonda, LINK);
    if (!Schonda) {
      LINK->LINK->Codenr = Freiesymnr(&LINK->LINK->Letztsymi,
				      &LINK->LINK->Letztsymj, LINK);
      Kellersym->Symnr = LINK->LINK->Codenr;
      Symboltabelle[LINK->LINK->Codenr] = Kellersym;
    } else
      LINK->LINK->Codenr = Kellersym->Symnr;
    /* TRAGEKELLERUNGSSYMBOL EIN */
   
    P_addset(Kellermenge, LINK->LINK->Codenr);

    Liessymbol(LINK->LINK);
    if (LINK->LINK->Symart != Punkt) {
      if (!Fehlerpunkt(14L, LINK))
	goto _L9999;
    } else
      Liessymbol(LINK->LINK);
  }
_L9999:   /* DOLLAR ODER DATEIENDE GEFUNDEN */
  Liessymbol(LINK->LINK);

  /* SYMART in SYMBOLMENGE */
}  /* VOM KELLERTEIL */

/*$page*/
Local Void Stopteil(LINK)
struct LOC_Lalreingabe *LINK;
{
  /*        ********/
  /**********************************************************************/
  /* WENN DER STOPTEIL in DER EINGABEGRAMMATIK DEFINIERT IST,           */
  /* DANN WIRD DAS DORT BEZEICHNETE STOPSYMBOL ALS EINGABEENDEZEICHEN   */
  /* UEBERNOMMEN, ANSONSTEN GILT STANDARDMAESSIG DAS WORTSYMBOL         */
  /* 'eof' ALS STOPSYMBOL.                                              */
  /* DIE CODIERUNG DES STOPSYMBOLS KANN IM CODETEIL ERFOLGEN.           */
  /**********************************************************************/
  boolean Stopda, Schonda;
  Tsymboltyp *Stopsym;
  Symbolstring Stopsymbez;
  int Stopsymlaenge;

  Stopda = false;
  if (LINK->LINK->Symart == Stop) {
    Liessymbol(LINK->LINK);
    if (LINK->LINK->Symart != Dollar) {
      if (((1L << ((long)LINK->LINK->Symart)) & LINK->Symbolmenge) == 0) {
	Fehler(51L, (long)LINK->LINK->Symlaenge, LINK->LINK->Symbez);
	while (((1L << ((long)LINK->LINK->Symart)) &
		((1L << ((long)Datend)) | (1L << ((long)Dollar)))) == 0)
	  Liessymbol(LINK->LINK);
      } else {
	Stopda = true;
	Stopsymbez = LINK->LINK->Symbez;
	Stopsymlaenge = LINK->LINK->Symlaenge;
	Liessymbol(LINK->LINK);
	if (LINK->LINK->Symart != Punkt) {
	  Fehler(52L, (long)LINK->LINK->Symlaenge, LINK->LINK->Symbez);
	  while (((1L << ((long)LINK->LINK->Symart)) &
		  ((1L << ((long)Datend)) | (1L << ((long)Dollar)))) == 0)
	    Liessymbol(LINK->LINK);
	} else {
	  Liessymbol(LINK->LINK);
	  if (LINK->LINK->Symart != Dollar) {
	    Fehler(53L, (long)LINK->LINK->Symlaenge, LINK->LINK->Symbez);
	    while (((1L << ((long)LINK->LINK->Symart)) &
		    ((1L << ((long)Datend)) | (1L << ((long)Dollar)))) == 0)
	      Liessymbol(LINK->LINK);
	  }
	}
      }
    }
    /* SYMART in [DOLLAR,DATEND] */
    Liessymbol(LINK->LINK);
  }
  if (!Stopda) {   /* DEFINIERE STANDARD-STOPSYMBOL */
    Stopsymbez = Stopsymbol;
    Stopsymlaenge = 3;
  }

  Stopsym = Suchetsymbol(Stopsymbez, Stopsymlaenge, &Schonda, LINK);
  if (Schonda) {
    Stopsymnr = Stopsym->Symnr;
    return;
  }
  Stopsymnr = Freiesymnr(&LINK->LINK->Letztsymi, &LINK->LINK->Letztsymj, LINK);
  Stopsym->Symnr = Stopsymnr;
  Symboltabelle[Stopsymnr] = Stopsym;
}  /* VOM STOPTEIL */

/*$page*/
Local Void Fehlerteil(Teil, Femenge, LINK)
Symbolart Teil;
long *Femenge;
struct LOC_Lalreingabe *LINK;
{
  /*        **********/
  Tsymboltyp *Femengensym;
  boolean Schonda;

  if (LINK->LINK->Symart != Teil) {
    return;
  }  /* SYMART=TEIL */
  Liessymbol(LINK->LINK);
  while (LINK->LINK->Symart != Dollar) {
    if (((1L << ((long)LINK->LINK->Symart)) & LINK->Symbolmenge) == 0) {
      if (!Fehlerpunkt(45L, LINK))
	goto _L9999;
      continue;
    }
    Femengensym = Suchetsymbol(LINK->LINK->Symbez, LINK->LINK->Symlaenge,
			       &Schonda, LINK);
    if (!Schonda) {
      LINK->LINK->Codenr = Freiesymnr(&LINK->LINK->Letztsymi,
				      &LINK->LINK->Letztsymj, LINK);
      Femengensym->Symnr = LINK->LINK->Codenr;
      Symboltabelle[LINK->LINK->Codenr] = Femengensym;
    } else
      LINK->LINK->Codenr = Femengensym->Symnr;
    /* TRAGE FEHLERSYMBOL EIN */
   
    P_addset(Femenge, LINK->LINK->Codenr);

    Liessymbol(LINK->LINK);
    if (LINK->LINK->Symart != Punkt) {
      if (!Fehlerpunkt(56L, LINK))
	goto _L9999;
    } else
      Liessymbol(LINK->LINK);
  }
_L9999:   /* DOLLAR ODER DATEIENDE GEFUNDEN */
  Liessymbol(LINK->LINK);

  /* SYMART in SYMBOLMENGE */
}  /* VOM FEHLERTEIL */

/* Local variables for Metateil: */
struct LOC_Metateil {
  struct LOC_Lalreingabe *LINK;
} ;

Local Void Haengemetasyman(Metasym, Laenge, LINK)
Tmetatyp **Metasym;
int Laenge;
struct LOC_Metateil *LINK;
{
  /*        ***************/
  Tmetatyp *WITH;

  LINK->LINK->LINK->Metaexist = true;
  *Metasym = LINK->LINK->LINK->Metatabhash[Laenge % Maxsymlaenge];
  if (*Metasym == (Tmetatyp *)0) {
    LINK->LINK->LINK->Metatabhash[Laenge % Maxsymlaenge] = (Tmetatyp *)Malloc(sizeof(Tmetatyp));
    *Metasym = LINK->LINK->LINK->Metatabhash[Laenge % Maxsymlaenge];
  } else {  /* SUCHE DAS LISTENENDE */
    while ((*Metasym)->Naechster != NULL)
      *Metasym = (*Metasym)->Naechster;
    (*Metasym)->Naechster = (Tmetatyp *)Malloc(sizeof(Tmetatyp));
    *Metasym = (*Metasym)->Naechster;
  }
  WITH = *Metasym;
  WITH->Bezeichner = LINK->LINK->LINK->Symbez;
  WITH->Kopfelement = (Tmetaelement *)Malloc(sizeof(Tmetaelement));
  WITH->Naechster = NULL;
  WITH->Kopfelement->Naechstes = NULL;
}  /* VON HAENGEMETASYMAN */

/*$page*/
Local Void Metateil(LINK)
struct LOC_Lalreingabe *LINK;
{  /* VOM METATEIL-ANWEISUNGSTEIL */
  /**********************************************************************/
  /* DIESE PROZEDUR BAUT DIE HASHTABELLE METATABHASH AUF.               */
  /* DER SUCHSCHLUESSEL IST DIE LAENGE DES METASYMBOLS.                 */
  /* METASYMBOLE GLEICHER LAENGE WERDEN DANN AN EINE LISTE HINTEN       */
  /* DRANGEHAENGT. AN JEDEM METASYMBOL HAENGT EINE KETTE VOM            */
  /* METAELEMENTEN. DAS ERSTE ELEMENT DIESER KETTE IST DAS              */
  /* KOPFELEMENT UND ENTHAELT KEINE WEITEREN INFORMATIONEN.             */
  /* ES DIENT NUR DER BESCHLEUNIGUNG DES TABELLENAUFBAUS UND DER        */
  /* GEFAELLIGEN FORMULIERUNG DES ALGORITHMUS.                          */
  /*                                                                    */
  /**********************************************************************/
  struct LOC_Metateil V;

  Tmetatyp *Metasym;
  Tmetaelement *Metaelem;
  Tsymboltyp *Symbolm;
  boolean Schonda;
  Tmetaelement *WITH1;


  V.LINK = LINK;
  if (LINK->LINK->Symart != Meta) {
    return;
  }  /* SYMART=META */
  Liessymbol(LINK->LINK);
  while (LINK->LINK->Symart != Dollar) {
    if (((1L << ((long)LINK->LINK->Symart)) & LINK->Symbolmenge) == 0) {
      if (!Fehlerpunkt(16L, LINK))
	goto _L9999;
      continue;
    }
    Haengemetasyman(&Metasym, LINK->LINK->Symlaenge, &V);
    Liessymbol(LINK->LINK);
    if (LINK->LINK->Symart != Gleich) {
      if (!Fehlerpunkt(17L, LINK))
	goto _L9999;
      continue;
    }
    Liessymbol(LINK->LINK);
    Metaelem = Metasym->Kopfelement;
    while (((1L << ((long)LINK->LINK->Symart)) & LINK->Symbolmenge) != 0) {
      /* SUCHE SYMBOL in DER SYMBOLTABHASH; TRAGE ES BEI
         NICHTFINDEN in DIE SYMBOLTABELLE EIN; DANN HAENGE
         ES AN DIE METASYMLISTE */
      Symbolm = Suchetsymbol(LINK->LINK->Symbez, LINK->LINK->Symlaenge,
			     &Schonda, LINK);
      if (!Schonda) {
	LINK->LINK->Codenr = Freiesymnr(&LINK->LINK->Letztsymi,
					&LINK->LINK->Letztsymj, LINK);
	Symbolm->Symnr = LINK->LINK->Codenr;
	Symboltabelle[LINK->LINK->Codenr] = Symbolm;
      }
      Metaelem->Naechstes = (Tmetaelement *)Malloc(sizeof(Tmetaelement));
      WITH1 = Metaelem->Naechstes;
      WITH1->Symnr = Symbolm->Symnr;
      WITH1->Naechstes = NULL;
      Metaelem = Metaelem->Naechstes;
      Liessymbol(LINK->LINK);
    }  /* SYMART in SYMBOLMENGE */
    if (LINK->LINK->Symart != Punkt) {
      if (!Fehlerpunkt(18L, LINK))
	goto _L9999;
    } else
      Liessymbol(LINK->LINK);
  }
  /* SYMART=DOLLAR */
_L9999:   /* DOLLAR ODER DATEIENDE GEFUNDEN */
  Liessymbol(LINK->LINK);

  /* ANHAENGEN DES METASYMBOLS AN SEINE LISTE */
  /* SYMART=GLEICH */
  /* SYMART=BEZEICHNER */
}  /* VOM METATEIL */

/* Local variables for Grammatikteil: */
struct LOC_Grammatikteil {
  struct LOC_Lalreingabe *LINK;
  Bnfkellertyp Keller;
  Elemkellertyp Elemkeller;
  Fokellertyp Fokeller;
  Atkellertyp Atkeller;
  Atnkellertyp Atnkeller;
  long Kellerpegel;
  long Elempegel, Fopegel, Atpegel, Atnpegel;
} ;

/* Local variables for Produktion: */
struct LOC_Produktion {
  struct LOC_Grammatikteil *LINK;
  jmp_buf _JL2;
} ;

Local Void Erzeugebnfwdh PP((Talternk **Atn, int Lssymnr, short *Prodnr,
			     Tlstyp *Lsei, struct LOC_Produktion *LINK));
Local Void Alternativen PP((Talternk **Atn, struct LOC_Produktion *LINK));

Local Void Getelem(Elem, Elart, LINK)
Telementk **Elem;
Elemart Elart;
struct LOC_Produktion *LINK;
{
  /*        *******/
  Telementk *WITH;

  if (LINK->LINK->Elempegel > Maxelemkeller) {
    Fehlerinstand(40L, true, LINK->LINK->LINK);
    longjmp(LINK->_JL2, 1);
    return;
  }
  *Elem = LINK->LINK->Elemkeller[LINK->LINK->Elempegel];
  WITH = *Elem;
  WITH->Art = Elart;
  WITH->Naechster = NULL;
  WITH->Vorg = NULL;
  LINK->LINK->Elempegel++;
}  /* VON GETELEM */

/*$page*/
Local Void Getfo(Fo, LINK)
Tfolgek **Fo;
struct LOC_Produktion *LINK;
{
  /*        *****/
  Tfolgek *WITH;

  if (LINK->LINK->Fopegel > Maxfokeller) {
    Fehlerinstand(41L, true, LINK->LINK->LINK);
    longjmp(LINK->_JL2, 1);
    return;
  }
  *Fo = LINK->LINK->Fokeller[LINK->LINK->Fopegel];
  WITH = *Fo;
  WITH->Naechster = NULL;
  WITH->Modi = NULL;
  LINK->LINK->Fopegel++;
}  /* VON GETFO */

Local Void Getat(At, LINK)
Talterk **At;
struct LOC_Produktion *LINK;
{
  /*        *****/
  if (LINK->LINK->Atpegel > Maxatkeller) {
    Fehlerinstand(42L, true, LINK->LINK->LINK);
    longjmp(LINK->_JL2, 1);
  } else {
    *At = LINK->LINK->Atkeller[LINK->LINK->Atpegel];
    LINK->LINK->Atpegel++;
  }
}  /* VON GETAT */

Local Void Getatn(Atn, LINK)
Talternk **Atn;
struct LOC_Produktion *LINK;
{
  /*        ******/
  if (LINK->LINK->Atnpegel > Maxatnkeller) {
    Fehlerinstand(43L, true, LINK->LINK->LINK);
    longjmp(LINK->_JL2, 1);
  } else {
    *Atn = LINK->LINK->Atnkeller[LINK->LINK->Atnpegel];
    LINK->LINK->Atnpegel++;
  }
}  /* VON GETATN */

Local Void Push(Symnr, LINK)
short Symnr;
struct LOC_Produktion *LINK;
{
  /*        ****/
  LINK->LINK->Keller[LINK->LINK->Kellerpegel] = Symnr;
  LINK->LINK->Kellerpegel++;
}

Local short Pop(LINK)
struct LOC_Produktion *LINK;
{
  /*       ***/
  LINK->LINK->Kellerpegel--;
  return (LINK->LINK->Keller[LINK->LINK->Kellerpegel]);
}

/*$page*/
Local Void Lsverkette(Prodnr, Symnr)
short Prodnr;
short Symnr;
{
  /*        **********/

  /**********************************************************************/
  /* DIE PRODUKTIONEN WERDEN RUECKWAERTS VERKETTET.                     */
  /**********************************************************************/
  Tsymtabtyp *WITH;

  if (Symtab[Symnr] == (Tsymtabtyp *)0) {
	/* AUFBAU DES NT- UND HILFNT-TEILS DER SYMTAB */
	  Symtab[Symnr] = (Tsymtabtyp *)Malloc(sizeof(Tsymtabtyp));   /*NT);*/
    WITH = Symtab[Symnr];
    WITH->Symart2 = Nt;
    WITH->UU.U2.Lseite = 0;
  }
  WITH = Symtab[Symnr];
  Ls[Prodnr - 1]->Naechste = WITH->UU.U2.Lseite;
  WITH->UU.U2.Lseite = Prodnr;
}  /* VON LSVERKETTE */

Local Void Bnfprod(Lsei, Lssymnr, Prodnr, Rszahl, LINK)
Tlstyp *Lsei;
short Lssymnr;
short *Prodnr;
long Rszahl;
struct LOC_Produktion *LINK;
{
  /*        *******/
  /* 0..MAXPRODLAENGE*/

  /**********************************************************************/
  /* DIESE PROZEDUR ERZEUGT UND/ODER BEWERTET DIE DATENSTRUKTUR FUER    */
  /* EINE BNF-PRODUKTION.                                               */
  /* DIE GEKELLERTE RECHTE SEITE WIRD RUECKWAERTS WIEDER AUSGELESEN.    */
  /* PROZEDURERGEBNIS : KELLERPEGEL:=KELLERPEGEL-RSZAHL                 */
  /* VOR AUFRUF DIESER PROZEDUR DARF KEIN SYMBOL DES TERMINAL-TEILS     */
  /* DER SYMTAB ERZEUGT WORDEN SEIN, SONST WERDEN DIE TERMINALSYMBOLE   */
  /* NICHT ALS SOLCHE in DIE SYMTAB EINGETRAGEN.                        */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*          AKTRSPOS                                                  */
  /*          .                                                         */
  /**********************************************************************/
  long I;
  Trstyp *WITH;

  if (Lsei == (Tlstyp *)0) {
    Ls[*Prodnr - 1] = (Tlstyp *)Malloc(sizeof(Tlstyp));   /*false);*/
    /* PRODUKTION OHNE ZUSATZ */
    Ls[*Prodnr - 1]->Zusatz = false;
  } else
    Ls[*Prodnr - 1] = Lsei;
  /* LINKE SEITE ERZEUGEN */
  Ls[*Prodnr - 1]->Symnr = Lssymnr;
  Lsverkette(*Prodnr, Lssymnr);
  /* RECHTE SEITE ERZEUGEN */
  if (Rszahl > Aktmaxrslaenge)
    Aktmaxrslaenge = Rszahl;
  WITH = &Rs[*Prodnr - 1];
  WITH->Rsanfang = Aktrspos;
  WITH->Rslaenge = Rszahl;
  for (I = 1; I <= Rszahl; I++) {
    Rsfeld[Aktrspos - 1] = Pop(LINK);
    Aktrspos++;
  }
  (*Prodnr)++;
}  /* VON BNFPROD */

/*$page*/
Local Void Produziereprod(Lsei, Lssymnr, Prodnr, Rszahl, Metazahl,
			  Mzeigerkeller, Msymkeller, Inkr, LINK)
Tlstyp **Lsei;
short Lssymnr;
short *Prodnr;
long Rszahl, Metazahl;
char *Mzeigerkeller;
Tmetaelement **Msymkeller;
long Inkr;
struct LOC_Produktion *LINK;
{
  /*        **************/
  /* 0..MAXPRODLAENGE */
  /* 0..MAXMETAPP*/

  /**********************************************************************/
  /* PROZEDURERGEBNIS : KELLERPEGEL:=KELLERPEGEL-RSZAHL                 */
  /**********************************************************************/
  Tmetaelement *Metaelem;
  long I;   /* LAUFVARIABLE */
  long Schnapp;
  Tlstyp *Hilsei;

  Hilsei = (Tlstyp *)0;
  Metaelem = (Tmetaelement *)0;
  if (Metazahl <= 0) {
    Bnfprod(*Lsei, Lssymnr, Prodnr, Rszahl, LINK);
    return;
  }
  Metaelem = Msymkeller[Metazahl - 1];
  if (Metazahl > 1) {
    Schnapp = LINK->LINK->Kellerpegel;
    for (I = Rszahl; I >= 1; I--)
      Push(LINK->LINK->Keller[Schnapp - I], LINK);
  }
  while (Metaelem != (Tmetaelement *)0) {
    Produziereprod(Lsei, Lssymnr, Prodnr, Rszahl, Metazahl - 1, Mzeigerkeller,
		   Msymkeller, Inkr + 1, LINK);
    /* DIE FOLGENDE BEDINGUNG STEHT HIER, DAMIT AUCH WIRKLICH JEDE
       LINKE SEITE EINEN EIGENEN VERBUND BEKOMMT, UM EINE KORREKTE
       VERKETTUNG DER LINKEN SEITEN ZU ERMOEGLICHEN.
       DIE ANKNUEPFUNGS- UND MODIFIKATIONSKETTEN DER LS WERDEN JE-
       DOCH NICHT DUPLIZIERT! DAS IST BEI PRODUKTIONEN MIT META-
       ELEMENTEN AUCH SEMANTISCH KORREKT UND ERWUENSCHT. */
    if (*Lsei != (Tlstyp *)0) {
      Hilsei = (Tlstyp *)Malloc(sizeof(Tlstyp));   /* PRODUKTION MIT ZUSATZ */
      Hilsei->UU.U1.Struktan = NULL;
      Hilsei->UU.U1.Modifik = NULL;
      Hilsei->Zusatz = true;
      Hilsei->Naechste = 0;
      /* DIE VARIANTE BEI new WIRD NICHT ANGEGEBEN, DAMIT DIE
         NAECHSTE ANWEISUNG MOEGLICH IST|| */
      *Hilsei = **Lsei;
      *Lsei = Hilsei;
    }
    LINK->LINK->Keller[Mzeigerkeller[Metazahl - 1] + Inkr * Rszahl] =
      Metaelem->Symnr;
    if (Metazahl > 1) {
      Schnapp = LINK->LINK->Kellerpegel;
      for (I = Rszahl; I >= 1; I--)
	Push(LINK->LINK->Keller[Schnapp - I], LINK);
    } else
      LINK->LINK->Kellerpegel += Rszahl;
    Metaelem = Metaelem->Naechstes;
  }
  Produziereprod(Lsei, Lssymnr, Prodnr, Rszahl, Metazahl - 1, Mzeigerkeller,
		 Msymkeller, Inkr + 1, LINK);
}  /* VON PRODUZIEREPROD */

/*        *************/

Local short Bnfelement(Elem, Foelzahl, Prodnr, Bmeta, Metaelem, Lsei, LINK)
Telementk **Elem;
long *Foelzahl;
short *Prodnr;
boolean *Bmeta;
Tmetaelement **Metaelem;
Tlstyp **Lsei;
struct LOC_Produktion *LINK;
{
  /*       **********/

  /**********************************************************************/
  /* WENN DAS GEFUNDENE ELEMENT EIN METASYMBOL IST, DANN LIEFERE DAS    */
  /* ERSTE METAELEMENT in BNFELEMENT AN, SETZE BMETA=true UND           */
  /* METAELEMENT AUF DAS NAECHSTE METAELEMENT.                          */
  /* WENN DAS GEFUNDENE ELEMENT EINE STRUKTURANKNUEPFUNG IST UND        */
  /* FOELZAHL=0, DANN HAENGE DIE STRUKTURANKNUEPFUNG AN DIE LINKE       */
  /* SEITE DER PRODUKTION PRODNR;                                       */
  /* SONST ERZEUGE EINE EPSILON-PRODUKTION                              */
  /* UND HAENGE DARAN DIE STRUKTURANKNUEPFUNG.                          */
  /*                                                                    */
  /* AM SCHLUSS WIRD ELEM:=ELEM^.VORG AUSGEFUEHRT.                      */
  /*                                                                    */
  /**********************************************************************/
  short Result;
  Tstrukturtyp *Hilfstru;
  boolean Bstrukt;
  short Hi, Hi2;
  Tlstyp *Hilsei;
  long Hifoelzahl;
  Telementk *WITH;
  Tlstyp *WITH1;
  Tstrukturtyp *WITH2;
  Tsymtabtyp *WITH3;

  Hilsei = (Tlstyp *)0;
  Hilfstru = (Tstrukturtyp *)0;
  Bstrukt = false;
  *Bmeta = false;
  WITH = *Elem;
    switch (WITH->Art) {

    case Met:
      *Metaelem = WITH->UU.Metasym->Kopfelement->Naechstes;
      if (*Metaelem == NULL) {
	Bstrukt = true;
	LINK->LINK->Kellerpegel--;
	Result = LINK->LINK->Keller[LINK->LINK->Kellerpegel];
	/* TRICK : SIEHE UNTEN BEI STRUAN */
      } else {
	Result = (*Metaelem)->Symnr;
	*Metaelem = (*Metaelem)->Naechstes;
	/* METAELEM ZEIGT SCHON AUF DAS 2.TE METAELEMENT */
	if (*Metaelem != NULL)
	  *Bmeta = true;
      }
      break;

    case Sym:
      Result = WITH->UU.Elsymnr;
      break;

    case Struan:
      if (*Foelzahl == 0) {
	if (*Lsei == NULL) {
	  *Lsei = (Tlstyp *)Malloc(sizeof(Tlstyp));   /*true);*/
	  WITH1 = *Lsei;
	  WITH1->UU.U1.Struktan = NULL;
	  WITH1->UU.U1.Modifik = NULL;
	  WITH1->Zusatz = true;
	  WITH1->Naechste = 0;
	}
	WITH1 = *Lsei;
	Hilfstru = WITH1->UU.U1.Struktan;
	WITH1->UU.U1.Struktan = (Tstrukturtyp *)Malloc(sizeof(Tstrukturtyp));
	WITH2 = WITH1->UU.U1.Struktan;
	WITH2->Strukturnr = WITH->UU.Elsymnr;
	/*STRUKTAN^.*/
	WITH2->Naechste = Hilfstru;
	Bstrukt = true;
	LINK->LINK->Kellerpegel--;
	Result = LINK->LINK->Keller[LINK->LINK->Kellerpegel];
	/* TRICK: VERHINDERT, DASS DAS OBERSTE KELLERELEMENT
	DURCH DEN AUFRUF PUSH(BNFELEMENT[]) VERAENDERT WIRD.*/
      } else {
	Hi = Freiesymnr(&LINK->LINK->LINK->LINK->Letztsymi,
			&LINK->LINK->LINK->LINK->Letztsymj, LINK->LINK->LINK);
	Symtab[Hi] = (Tsymtabtyp *)Malloc(sizeof(Tsymtabtyp));   /*HILFNT);*/
	WITH3 = Symtab[Hi];
	WITH3->Symart2 = Hilfnt;
	WITH3->UU.U2.Lseite = 0;
	Hilsei = (Tlstyp *)Malloc(sizeof(Tlstyp));
	Hilsei->Naechste = 0;
	Hilsei->UU.U1.Modifik = NULL;
	Hilsei->Zusatz = true;
	Hilsei->UU.U1.Struktan = (Tstrukturtyp *)Malloc(sizeof(Tstrukturtyp));
	WITH2 = Hilsei->UU.U1.Struktan;
	WITH2->Strukturnr = WITH->UU.Elsymnr;
	WITH2->Naechste = NULL;
	Hifoelzahl = 0;

	while ((*Elem)->Vorg->Art == Struan) {
	  /* FALLS MEHRERE STRUKTURANKNUEPFUNGEN AUFEINANDERFOLGEN*/
	  /* DIESE SCHLEIFE WIRD NIE in SICH REKURSIV, WAS ZU FEHLERN
	     FUEHREN WUERDE, DA DER PARAMETER HIFOELZAHL=0 IST UND
	     DAMIT  BSTRUKT=true WIRD UND FOELZAHL=0 BLEIBT !! */
	  Push(Bnfelement(&(*Elem)->Vorg, &Hifoelzahl, Prodnr, Bmeta,
			  Metaelem, &Hilsei, LINK), LINK);
	}
	/*HIFOELZAHL=0,BMETA=false,PRODNR=UNVERAENDERT*/

	/* DIE FOLGENDE BEDINGUNG FUEHRT ZUM FALSCHEN ANHAENGEN
	   VON STRUKTURANKNUEPFUNGEN, Z.B.:
	   Z : A* &S B .   =>
	   Z : H1 B .
	   H1 : . &S
	   H1 : H1 A . &S
	   RICHTIG IST:
	   Z : H1 H2 B .
	   H1 : .
	   H1 : H1 A .
	   H2 : . &S
	   DAHER GILT NUR FUER: VORG^.ART in [RKL,EKL]  */

	if (((1L << ((long)(*Elem)->Vorg->Art)) &
	     ((1L << ((long)Rkl)) | (1L << ((long)Ekl)))) != 0) {
	  /* BMETA=false,PRODNR=VERAENDERT */
	  Push(Bnfelement(&(*Elem)->Vorg, Foelzahl, Prodnr, Bmeta, Metaelem,
			  &Hilsei, LINK), LINK);
	  /* BMETA=false,PRODNR=VERAENDERT */
	  Bstrukt = true;
	  /* VERHINDERT DAS NOCHMALIGE HOCHZAEHLEN
	                    VON FOELZAHL */

	  Bnfprod(Hilsei, Hi, Prodnr, 1L, LINK);   /* HI : ( A ) . &S */
	  Result = Hi;

	} else {  /* ERZEUGE EPSILON-PRODUKTION */
	  Result = Hi;
	  Bnfprod(Hilsei, Hi, Prodnr, Hifoelzahl, LINK);
	}
	/* Z : ( A ) &S B .          ODER
	   Z : [ A ] &S B .      WIRD ZU
	   Z : H1 B .
	   H1: ( A ) &S .        ODER
	   H1: [ A ] &S .
	*/

      }
      break;
    default:
    Hi = Freiesymnr(&LINK->LINK->LINK->LINK->Letztsymi,
		    &LINK->LINK->LINK->LINK->Letztsymj, LINK->LINK->LINK);
    if (Symtab[Hi] == (Tsymtabtyp *)0) {   /* STRUKTURANK. GING VORAUS */
      Symtab[Hi] = (Tsymtabtyp *)Malloc(sizeof(Tsymtabtyp));   /*HILFNT);*/
      WITH3 = Symtab[Hi];
      WITH3->Symart2 = Hilfnt;
      WITH3->UU.U2.Lseite = 0;
    } else
      Hilsei = *Lsei;

      switch (WITH->Art) {

      case Plu:
      case Ster:   /* A : B* ., A : B+ . */
	if (WITH->Art == Ster)   /* HI : . */
	  Bnfprod(Hilsei, Hi, Prodnr, 0L, LINK);
	else {
	  Push(WITH->UU.Elsymnr, LINK);
	  Bnfprod(Hilsei, Hi, Prodnr, 1L, LINK);   /* HI : B . */
	}
	Push(WITH->UU.Elsymnr, LINK);
	Push(Hi, LINK);
	if (Hilsei != NULL) {
	  Hilsei = (Tlstyp *)Malloc(sizeof(Tlstyp));
	  *Hilsei = **Lsei;
	}
	Bnfprod(Hilsei, Hi, Prodnr, 2L, LINK);   /* HI : HI B . */
	Result = Hi;   /* A : HI . */
	break;

      case Rkl:   /* A : (B) . */
	Erzeugebnfwdh(&WITH->UU.Atn, Hi, Prodnr, Hilsei, LINK);
	    /* HI : B . */
	Result = Hi;   /* A : HI . */
	break;

      case Ekl:   /* A : [B] . */
	Erzeugebnfwdh(&WITH->UU.Atn, Hi, Prodnr, Hilsei, LINK);
	    /* HI : B . */
	if (Hilsei != NULL) {
	  Hilsei = (Tlstyp *)Malloc(sizeof(Tlstyp));
	  *Hilsei = **Lsei;
	}
	Bnfprod(Hilsei, Hi, Prodnr, 0L, LINK);   /* HI : . */
	Result = Hi;   /* A : HI . */
	break;

      case Rklplu:
      case Rklster:   /* A : (B)+ ., A : (B)* . */
	Hi2 = Freiesymnr(&LINK->LINK->LINK->LINK->Letztsymi,
			 &LINK->LINK->LINK->LINK->Letztsymj,
			 LINK->LINK->LINK);
	Symtab[Hi2] = (Tsymtabtyp *)Malloc(sizeof(Tsymtabtyp));   /*HILFNT);*/
	WITH3 = Symtab[Hi2];
	WITH3->Symart2 = Hilfnt;
	WITH3->UU.U2.Lseite = 0;
	if (WITH->Art == Rklster)   /* HI : . */
	  Bnfprod(Hilsei, Hi, Prodnr, 0L, LINK);
	else {
	  Push(Hi2, LINK);
	  Bnfprod(Hilsei, Hi, Prodnr, 1L, LINK);   /* HI : HI2 . */
	}
	Push(Hi2, LINK);
	Push(Hi, LINK);
	if (Hilsei != NULL) {
	  Hilsei = (Tlstyp *)Malloc(sizeof(Tlstyp));
	  *Hilsei = **Lsei;
	}
	Bnfprod(Hilsei, Hi, Prodnr, 2L, LINK);   /* HI : HI HI2 . */
	Erzeugebnfwdh(&WITH->UU.Atn, Hi2, Prodnr, (Tlstyp *)0, LINK);
	    /* HI2 : B . */
	Result = Hi;   /* A : HI . */
	break;
      default:
      Fehler(37L, 0L, LINK->LINK->LINK->LINK->Symbez);
      }
  }  /* VOM with */
  if (!Bstrukt)
    (*Foelzahl)++;
  *Elem = (*Elem)->Vorg;
  return Result;
}  /* VOM BNFELEMENT */

/*$page*/
Local Void Bnfoder(Fo, Lssymnr, Prodnr, Mzeigerkeller, Msymkeller, LINK)
Tfolgek **Fo;
short Lssymnr;
short *Prodnr;
char *Mzeigerkeller;
Tmetaelement **Msymkeller;
struct LOC_Produktion *LINK;
{
  /*        *******/

  /**********************************************************************/
  /* DIE ELEMENTE EINER BNF-PRODUKTION WERDEN RUECKWAERTS               */
  /* in DEN KELLER GESCHRIEBEN.                                         */
  /**********************************************************************/
  Tlstyp *Lsei;
  Tmetaelement *Metaelem;
  Telementk *Fomodel;   /* FOLGEN-/MODIFIKATIONSELEMENT */
  Tmodifiktyp *Hilfmod;
  long Foelzahl;   /* FOLGENELEMENTEZAHL */
  boolean Bmeta;
  char Metazahl;
  Tmodifiktyp *WITH1;

  Lsei = NULL;
  Fomodel = NULL;
  Metaelem = NULL;
  Hilfmod = NULL;
  Fomodel = (*Fo)->Modi;
  if (Fomodel != NULL) {  /* HAENGE MODIFIKATIONEN AN DIE LINKE SEITE */
    Lsei = (Tlstyp *)Malloc(sizeof(Tlstyp));
    Lsei->Zusatz = true;
    Lsei->UU.U1.Modifik = NULL;
    Lsei->UU.U1.Struktan = NULL;
    while (Fomodel != NULL) {
      Hilfmod = Lsei->UU.U1.Modifik;
      Lsei->UU.U1.Modifik = (Tmodifiktyp *)Malloc(sizeof(Tmodifiktyp));
      WITH1 = Lsei->UU.U1.Modifik;
      WITH1->Reduziere = (Fomodel->Art == Red);
      WITH1->Modsymnr = Fomodel->UU.Elsymnr;
      WITH1->Naechste = Hilfmod;
      Fomodel = Fomodel->Naechster;
    }
  }  /* ERZEUGE RECHTE SEITE */
  Fomodel = (*Fo)->El1->Vorg;
  Foelzahl = 0;
  Metazahl = 0;
  while (Fomodel->Art != Kopf) {
    Push(Bnfelement(&Fomodel, &Foelzahl, Prodnr, &Bmeta, &Metaelem, &Lsei,
		    LINK), LINK);
    /* FOELZAHL WIRD in BNFELEMENT ERHOEHT, FALLS NOETIG */
    if (Bmeta) {
      Metazahl++;
      Mzeigerkeller[Metazahl - 1] = LINK->LINK->Kellerpegel - 1;
      Msymkeller[Metazahl - 1] = Metaelem;
    }
  }
/*
  if (Foelzahl >= Maxlaengers)
    Fehler(54L, 0L, LINK->LINK->LINK->LINK->Symbez);
  else
*/
    Produziereprod(&Lsei, Lssymnr, Prodnr, Foelzahl, (long)Metazahl,
		   Mzeigerkeller, Msymkeller, 0L, LINK);
}  /* VON BNFODER */

/*$page*/
Local Void Erzeugebnfwdh(Atn, Lssymnr, Prodnr, Lsei, LINK)
Talternk **Atn;
short Lssymnr;
short *Prodnr;
Tlstyp *Lsei;
struct LOC_Produktion *LINK;
{
  /*ATN,LSSYMNR,PRODNR,LSEI*/
  /*        *************/
  /**********************************************************************/
  /* EXTERNAL                                                           */
  /*          LETZTSYMI,                                                */
  /*          LETZTSYMJ.                                                */
  /*                                                                    */
  /* FALLS 'B//C' EINE UNGEKLAMMERTE WIEDERHOLUNG IST,                  */
  /* GILT:                     , SONST GILT:                            */
  /*    A   : HI .                 A  : HI .                            */
  /*    HI  : HI2 .                                                     */
  /*    HI  : HI C HI2 .           A  : A C HI .                        */
  /*    HI2 : B .                  HI : B .                             */
  /*                                                                    */
  /**********************************************************************/
  Tmetaelement *Metaelem;
  short Hi;
  Mzgrkellertyp Mzeigerkeller;
  Msymkellertyp Msymkeller;
  char Metazahl;
  boolean Bmeta;
  long Foelzahl;
  Tfolgek *Folg;
  Talternk *WITH;
  Tsymtabtyp *WITH1;

  Metaelem = NULL;
  Folg = NULL;
  WITH = *Atn;
  if (WITH->El1->Vorg->Art != Kopf) {  /* WDH :            A : B // C   */
    Hi = Freiesymnr(&LINK->LINK->LINK->LINK->Letztsymi,
		    &LINK->LINK->LINK->LINK->Letztsymj, LINK->LINK->LINK);
    Symtab[Hi] = (Tsymtabtyp *)Malloc(sizeof(Tsymtabtyp));   /*HILFNT);*/
    WITH1 = Symtab[Hi];
    WITH1->Symart2 = Hilfnt;
    WITH1->UU.U2.Lseite = 0;
    Push(Hi, LINK);
    Bnfprod((Tlstyp *)0, Lssymnr, Prodnr, 1L, LINK);   /* A : HI . */
    /* BNFPROD ==> LSVERKETTE ==> ( SYMTAB[LSSYMNR]<>nil )  */

    if (Symtab[Lssymnr]->Symart2 == Nt) {  /* UNGEKLAMMERTE WIEDERHOLUNG ! */
      Lssymnr = Hi;   /* A <-- HI */
      Hi = Freiesymnr(&LINK->LINK->LINK->LINK->Letztsymi,
		      &LINK->LINK->LINK->LINK->Letztsymj, LINK->LINK->LINK);
      Symtab[Hi] = (Tsymtabtyp *)Malloc(sizeof(Tsymtabtyp));   /*HILFNT);*/
      WITH1 = Symtab[Hi];
      WITH1->Symart2 = Hilfnt;
      WITH1->UU.U2.Lseite = 0;
      Push(Hi, LINK);   /* HI2 */
      Bnfprod((Tlstyp *)0, Lssymnr, Prodnr, 1L, LINK);   /*  HI : HI2 . */
    }

    Push(Hi, LINK);   /* HI */
    Foelzahl = 1;
    Push(Bnfelement(&WITH->El1->Vorg, &Foelzahl, Prodnr, &Bmeta, &Metaelem,
		    &Lsei, LINK), LINK);
    /* C */
    Push(Lssymnr, LINK);   /* A */
    if (Bmeta) {
      Metazahl = 1;
      Mzeigerkeller[Metazahl - 1] = LINK->LINK->Kellerpegel - 2;   /* C */
      Msymkeller[Metazahl - 1] = Metaelem;
    } else
      Metazahl = 0;
    Produziereprod(&Lsei, Lssymnr, Prodnr, 3L, (long)Metazahl, Mzeigerkeller,
		   Msymkeller, 0L, LINK);
    /* A : A C HI . */
    Erzeugebnfwdh(Atn, Hi, Prodnr, (Tlstyp *)0, LINK);   /* HI : B . */
    return;
  }
  Folg = WITH->At->Fo;   /* FOLG <> nil ||| */
  while (Folg != NULL) {
    Bnfoder(&Folg, Lssymnr, Prodnr, Mzeigerkeller, Msymkeller, LINK);
    Folg = Folg->Naechster;
  }
}  /* VON ERZEUGEBNFWDH */

/*        ************/
/*$page*/
Local Void Element(Elem, Vorelem, Fo, LINK)
Telementk **Elem, **Vorelem;
Tfolgek **Fo;
struct LOC_Produktion *LINK;
{
  /*        *******/
  short Elemnr;
  Tmetatyp *Metasym;
  Symbolart Merksymart;
  Elemart Art;
  boolean Gefunden;
  Telementk *Hilfel, *WITH;
  Tsymboltyp *WITH1;

  Metasym = NULL;
  Hilfel = NULL;
    switch (LINK->LINK->LINK->LINK->Symart) {

    case Bezeichner:
    case Symbol:
      /* BRACKET,CODE,GRAMMAR,META,SEPA,SKIP,STACK
         KANN INNERHALB DES GRAMMATIKTEILS NICHT MEHR VORKOMMEN*/
      Suchesymbol(LINK->LINK->LINK->LINK->Symbez,
		  LINK->LINK->LINK->LINK->Symlaenge, &Art, &Elemnr, &Metasym,
		  &Gefunden, LINK->LINK->LINK);
      if (Art == Met) {
	Getelem(Elem, Met, LINK);
	(*Elem)->UU.Metasym = Metasym;
      } else {  /* ART=SYM */
	Getelem(Elem, Sym, LINK);
	(*Elem)->UU.Elsymnr = Elemnr;
      }
      (*Elem)->Vorg = *Vorelem;
      break;

    case Plus:
    case Stern:
      WITH = *Vorelem;
	switch (WITH->Art) {

	case Kopf:
	  Fehlerinstand(25L, false, LINK->LINK->LINK);
	  break;

	case Sym:
	  if (LINK->LINK->LINK->LINK->Symart == Plus)
	    WITH->Art = Plu;
	  else
	    WITH->Art = Ster;
	  break;

	case Met:
	  Fehlerinstand(26L, false, LINK->LINK->LINK);
	  break;

	case Plu:
	  if (LINK->LINK->LINK->LINK->Symart == Stern)
	    WITH->Art = Ster;
	  break;

	case Ster:   /* ART:=STER; ->DIE ART BLEIBT STERN. */
	  break;

	case Rklplu:
	case Rkl:
	  if (LINK->LINK->LINK->LINK->Symart == Plus)
	    WITH->Art = Rklplu;
	  else
	    WITH->Art = Rklster;
	  break;

	case Rklster:
	case Ekl:
	  WITH->Art = Rklster;
	  break;
	default:
	Fehlerinstand(27L, false, LINK->LINK->LINK);
	}
      *Elem = NULL;
      break;

    case Dollar:
    case Klamaffe:
    case Und:
      Merksymart = LINK->LINK->LINK->LINK->Symart;
      Liessymbol(LINK->LINK->LINK->LINK);
      if (((1L << ((long)LINK->LINK->LINK->LINK->Symart)) & LINK->LINK->LINK->
							    Symbolmenge) == 0)
	Fehlerinstand(28L, false, LINK->LINK->LINK);
      else {
	Suchesymbol(LINK->LINK->LINK->LINK->Symbez,
		    LINK->LINK->LINK->LINK->Symlaenge, &Art, &Elemnr,
		    &Metasym, &Gefunden, LINK->LINK->LINK);
	if (Art == Met)
	  Fehlerinstand(29L, false, LINK->LINK->LINK);
	else {
	  WITH1 = Symboltabelle[Elemnr];
	  switch (Merksymart) {

	  case Dollar:
	  case Klamaffe:   /* MODIFIKATION */
	    if (((1L << WITH1->Symart1) &
		 ((1L << ((long)Undef)) | (1L << ((long)Terminal)))) != 0) {
	      if (*Fo == NULL) {
		/* SIEHE ELEMENT-AUFRUF in ALTERNATIVEN | */
		Fehlerinstand(35L, false, LINK->LINK->LINK);
	      } else {
		WITH1->Symart1 = (unsigned)Terminal;
		Hilfel = (*Fo)->Modi;
		/* DIE MODIFIKATIONEN WERDEN in UMGEKEHRTER REIHEN-
		   FOLGE IHRES AUFTRETENS EINFACH VERKETTET. */
		if (Merksymart == Dollar)
		  Getelem(&(*Fo)->Modi, Rednich, LINK);
		else
		  Getelem(&(*Fo)->Modi, Red, LINK);
		WITH = (*Fo)->Modi;
		WITH->UU.Elsymnr = Elemnr;
		WITH->Naechster = Hilfel;
	      }
	    } else
	      Fehlerinstand(33L, false, LINK->LINK->LINK);
	    break;

	  case Und:   /* STRUKTURANKNUEPFUNG */
	    if ((Symbolart1)WITH1->Symart1 == Strukturan || !Gefunden) {
	      WITH1->Symart1 = (unsigned)Strukturan;
	      Getelem(Elem, Struan, LINK);
	    } else
	      Fehlerinstand(34L, false, LINK->LINK->LINK);
	    break;
	  default:
	    ;
	  }
	  if (*Elem != NULL) {   /* WEDER FEHLER NOCH MODIFIKATION */
	    WITH = *Elem;
	    WITH->UU.Elsymnr = Elemnr;
	    WITH->Vorg = *Vorelem;
	  }
	}  /* ART=SYM */
      }  /* SYMART in SYMBOLMENGE */
      break;

    case Rklauf:
      Getelem(Elem, Rkl, LINK);
      (*Elem)->Vorg = *Vorelem;
      Liessymbol(LINK->LINK->LINK->LINK);
      Alternativen(&(*Elem)->UU.Atn, LINK);
      if (LINK->LINK->LINK->LINK->Symart != Rklazu)
	Fehlerinstand(30L, false, LINK->LINK->LINK);
      break;

    case Eklauf:
      Getelem(Elem, Ekl, LINK);
      (*Elem)->Vorg = *Vorelem;
      Liessymbol(LINK->LINK->LINK->LINK);
      Alternativen(&(*Elem)->UU.Atn, LINK);
      if (LINK->LINK->LINK->LINK->Symart != Eklazu)
	Fehlerinstand(31L, false, LINK->LINK->LINK);
      break;
    default:
    /* DATEND,DOPPELPKT,EKLAZU,GLEICH,ODER,
            PUNKT,RKLAZU,WDH,ZAHL */
    Fehlerinstand(32L, false, LINK->LINK->LINK);
    }

  if (((1L << ((long)LINK->LINK->LINK->LINK->Symart)) &
       ((1L << ((long)Punkt)) | (1L << ((long)Datend)))) == 0)
    Liessymbol(LINK->LINK->LINK->LINK);
  /*D.H.:WENN KEIN FEHLER VORLAG, DANN LIES DAS NAECHSTE SYMBOL */
}  /* VON ELEMENT */

/*$page*/
Local Void Folge(Fo, LINK)
Tfolgek **Fo;
struct LOC_Produktion *LINK;
{
  /*        *****/
  Telementk *Elem;
  Tfolgek *WITH, *WITH1;

  Getfo(Fo, LINK);
  WITH = *Fo;
  WITH->Elzahl = 0;
  Getelem(&WITH->El1, Kopf, LINK);
  Elem = WITH->El1;
  while (((1L << ((long)LINK->LINK->LINK->LINK->Symart)) & LINK->LINK->LINK->
							   Elemenge) != 0) {
    Element(&Elem->Naechster, &Elem, Fo, LINK);
    if (Elem->Naechster != NULL) {
      WITH1 = *Fo;
      WITH1->Elzahl++;
      Elem = Elem->Naechster;
    }
  }
  (*Fo)->El1->Vorg = Elem;
}  /* VON FOLGE */

Local Void Alternative(At, LINK)
Talterk **At;
struct LOC_Produktion *LINK;
{
  /*        ***********/
  Tfolgek *Folg;
  Talterk *WITH, *WITH1;

  Getat(At, LINK);
  Folge(&(*At)->Fo, LINK);
  WITH = *At;
  WITH->Fozahl = 1;
  Folg = WITH->Fo;
  while (LINK->LINK->LINK->LINK->Symart == Oder) {
    Liessymbol(LINK->LINK->LINK->LINK);
    Folge(&Folg->Naechster, LINK);
    WITH1 = *At;
    WITH1->Fozahl++;
    Folg = Folg->Naechster;
  }
}  /* VON ALTERNATIVE */

/*$page*/
Local Void Alternativen(Atn, LINK)
Talternk **Atn;
struct LOC_Produktion *LINK;
{
  /* PARAMETER: ATN */
  /*        ************/
  Telementk *Elem;
  Tfolgek *Nille;   /* DUMMY */
  Talternk *WITH, *WITH1;

  Nille = NULL;
  Getatn(Atn, LINK);
  Alternative(&(*Atn)->At, LINK);
  WITH = *Atn;
  WITH->Elzahl = 0;
  Getelem(&WITH->El1, Kopf, LINK);
  Elem = WITH->El1;
  while (LINK->LINK->LINK->LINK->Symart == Wdh) {
    Liessymbol(LINK->LINK->LINK->LINK);   /* LIEST NACH '//' WEITER */
    Element(&Elem->Naechster, &Elem, &Nille, LINK);
    if (Elem->Naechster != NULL) {
      WITH1 = *Atn;
      WITH1->Elzahl++;
      Elem = Elem->Naechster;
    }
  }
  (*Atn)->El1->Vorg = Elem;
}  /* VON ALTERNATIVEN */




/*$page*/
Local Void Produktion(LINK)
struct LOC_Grammatikteil *LINK;
{
  /*        **********/
  /**********************************************************************/
  /* GLEICHZEITIG MIT DEN BNF-PRODUKTIONEN WIRD DER NT- UND HILFNT-TEIL */
  /* DER SYMTAB (SYMBOLTABELLE ZUM MODUL ANALYSE) AUFGEBAUT.            */
  /*                                                                    */
  /**********************************************************************/
  struct LOC_Produktion V;
  /* KELLERUEBERLAUF */

  Tsymboltyp *Lssym;
  Talternk *Atn;

  V.LINK = LINK;
  if (setjmp(V._JL2))
    goto _L2;
  Atn = NULL;
  if (((1L << ((long)LINK->LINK->LINK->Symart)) & LINK->LINK->Symbolmenge) == 0)
    Fehlerinstand(19L, true, LINK->LINK);
  else {
    Lssym = Suchentsymbol(LINK->LINK->LINK->Symbez,
			  LINK->LINK->LINK->Symlaenge, LINK->LINK);
    if (((1L << Lssym->Symart1) &
	 ((1L << ((long)Terminal)) | (1L << ((long)Strukturan)))) != 0) {
      Fehler(20L, (long)LINK->LINK->LINK->Symlaenge, LINK->LINK->LINK->Symbez);
      Lssym->Symart1 = (unsigned)Fehlerhaft;
    }
    Liessymbol(LINK->LINK->LINK);
    if (LINK->LINK->LINK->Symart != Doppelpkt)
      Fehlerinstand(21L, true, LINK->LINK);
    else {
      Liessymbol(LINK->LINK->LINK);
      Alternativen(&Atn, &V);
      if (((long)LINK->LINK->LINK->Symart) == ((long)Eklazu))
	Fehlerinstand(22L, false, LINK->LINK);
      if (((long)LINK->LINK->LINK->Symart) == ((long)Rklazu))
	Fehlerinstand(23L, false, LINK->LINK);
      if (((long)LINK->LINK->LINK->Symart) != ((long)Punkt))
	Fehlerinstand(24L, false, LINK->LINK);
      if (Keinefehler) {
	LINK->Kellerpegel = 1;
	Erzeugebnfwdh(&Atn, (short)(Lssym->Symnr),
                      &LINK->LINK->LINK->Aktprodnr, (Tlstyp *)0, &V);
      }
      Liessymbol(LINK->LINK->LINK);
    }  /* SYMART=DOPPELPKT */
  }  /* SYMART in SYMBOLMENGE */
  /***/
_L2: ;   /* KELLERUEBERLAUF-SPRUNGZIEL */
  /***/
}  /* VON PRODUKTION */

/*$page*/
Local Void Grammatikteil(LINK)
struct LOC_Lalreingabe *LINK;
{  /* VOM GRAMMATIKTEIL-ANWEISUNGSTEIL */
  /*        *************/
  /**********************************************************************/
  /* DER KELLER DIENT DEM AUFBAU DER BNF-PRODUKTIONEN. ER WIRD VON      */
  /* DEN PROZEDUREN PUSH,POP,PRODUZIEREPROD UND BNFELEMENT MANIPULIERT. */
  /* DER ELEM-,FO-,AT- UND ATNKELLER SIMULIERT JEWEILS EINE HALDE FUER  */
  /* VERBUNDE DES GLEICHNAMIGEN TYPS BEIM AUFBAU DES STRUKTURBAUMS      */
  /* ZU EINER PRODUKTION DER EINGABEGRAMMATIK. DIE HALDENPEGEL WERDEN   */
  /* VOR JEDER ANALYSE EINER PRODUKTION DER EINGABEGRAMMATIK AUF 0      */
  /* GESETZT.                                                           */
  /*                                                                    */
  /* MODULAUFBAU:                                                       */
  /*        procedure GETELEM(2);                                       */
  /*        procedure GETFO(1);                                         */
  /*        procedure GETAT(1);                                         */
  /*        procedure GETATN(1);                                        */
  /*        procedure PUSH(1);                                          */
  /*        function  POP : SYMNRBEREICH;                               */
  /*        procedure LSVERKETTE(2);                                    */
  /*        procedure BNFPROD(4);                                       */
  /*        procedure PRODUZIEREPROD(8);                                */
  /*        procedure ERZEUGEBNFWDH(4);                                 */
  /*        function  BNFELEMENT(6) : SYMNRBEREICH;                     */
  /*        procedure BNFODER(5);                                       */
  /*        procedure ALTERNATIVEN(1);                                  */
  /*        procedure ELEMENT(3);                                       */
  /*        procedure FOLGE(1);                                         */
  /*        procedure ALTERNATIVE(1);                                   */
  /*        procedure PRODUKTION;                                       */
  /*                                                                    */
  /**********************************************************************/
  struct LOC_Grammatikteil V;
  long I;   /* LAUFVARIABLE */

  /*$page*/
  V.LINK = LINK;
  /* INITIALISIERUNG */
  V.Keller[0] = 0;   /* EXISTIERT NUR ZUR ERMOEGLICHUNG DES BNFELEM-TRICKS*/
  for (I = 0; I <= Maxelemkeller; I++)
    V.Elemkeller[I] = (Telementk *)Malloc(sizeof(Telementk));
  for (I = 0; I <= Maxfokeller; I++)
    V.Fokeller[I] = (Tfolgek *)Malloc(sizeof(Tfolgek));
  for (I = 0; I <= Maxatkeller; I++)
    V.Atkeller[I] = (Talterk *)Malloc(sizeof(Talterk));
  for (I = 0; I <= Maxatnkeller; I++)
    V.Atnkeller[I] = (Talternk *)Malloc(sizeof(Talternk));
  /* INITIALISIERUNGS-ENDE */
  if (LINK->LINK->Symart != Grammar) {
    LINK->LINK->Imgrammatikteil = true;
    Fehler(6L, (long)LINK->LINK->Symlaenge, LINK->LINK->Symbez);
  } else
    Liessymbol(LINK->LINK);

  if (LINK->LINK->Symart == Gleich) {
    Liessymbol(LINK->LINK);
    if (((1L << ((long)LINK->LINK->Symart)) & LINK->Symbolmenge) == 0) {
      Fehlerinstand(39L, true, LINK);
    } else {
      Liessymbol(LINK->LINK);
    }
  }

  LINK->LINK->Aktprodnr = 1;
  Aktrspos = 1;
  Startsymnr = Freiesymnr(&LINK->LINK->Letztsymi, &LINK->LINK->Letztsymj, LINK);
  Streiche(Startsymnr, LINK);
  while (LINK->LINK->Symart != Datend) {
    if (LINK->LINK->Aktprodnr > Maxprodnr) {
      Fehler(60L, 0L, ""); break;
    }
    V.Elempegel = 0;
    V.Fopegel = 0;
    V.Atpegel = 0;
    V.Atnpegel = 0;
    Produktion(&V);
  }
  Aktmaxprodnr = LINK->LINK->Aktprodnr - 1;
  if (Aktmaxprodnr == 0)
    Keinefehler = false;
}  /* VOM GRAMMATIKTEIL */

/*$page*/
Local Void Lalreingabe(LINK)
struct LOC_Eingabe *LINK;
{  /* VOM  LALREINGABE-ANWEISUNGSTEIL */
  /*        ***********/
  /**********************************************************************/
  /* DIE EINGEGEBENE GRAMMATIK WIRD NACH DEM VERFAHREN DES REKURSIVEN   */
  /* ABSTIEGS ANALYSIERT. DABEI ENTSPRECHEN DIE PROZEDUREN              */
  /*                                                                    */
  /*    LALREINGABE,                                                    */
  /*    CODETEIL,                                                       */
  /*    KELLERTEIL,                                                     */
  /*    STOPTEIL,                                                       */
  /*    FEHLERTEIL(SEPA,SEPARATOR),                                     */
  /*    FEHLERTEIL(BRACKET,SEMKLAMMER),                                 */
  /*    FEHLERTEIL(SKIP,UEBERLESEN),                                    */
  /*    METATEIL,                                                       */
  /*    GRAMMATIKTEIL,                                                  */
  /*    PRODUKTION,                                                     */
  /*    ALTERNATIVEN,                                                   */
  /*    ALTERNATIVE,                                                    */
  /*    FOLGE,                                                          */
  /*    ELEMENT                                                         */
  /*                                                                    */
  /* DEN LINKEN SEITEN DER FOLGENDEN GRAMMATIK:                         */
  /*                                                                    */
  /* LALREINGABE   : '$' CODETEIL                                       */
  /*                     KELLERTEIL                                     */
  /*                     STOPTEIL                                       */
  /*                     SEPARATORTEIL                                  */
  /*                     KLAMMERTEIL                                    */
  /*                     UEBERLESETEIL                                  */
  /*                     METATEIL                                       */
  /*                     GRAMMATIKTEIL .                                */
  /* CODETEIL      : [ 'CODE' (SYMBOLM '=' 'GANZE ZAHL OHNE VORZEICHEN' */
  /*                                                       '.')* '$'] . */
  /* KELLERTEIL    : [ 'STACK' (SYMBOLM '.')* '$'] .                    */
  /* STOPTEIL      : [ 'STOP' [SYMBOLM '.'] '$'] .                      */
  /* SEPARATORTEIL: [ 'SEPA' (SYMBOLM '.')* '$'] .                      */
  /* KLAMMERTEIL  : [ 'BRACKET' (SYMBOLM '.')* '$'] .                   */
  /* UEBERLESETEIL: [ 'SKIP' (SYMBOLM '.')* '$'] .                      */
  /* METATEIL      : [ 'META' (SYMBOLM '=' SYMBOLM* '.')* '$'] .        */
  /* GRAMMATIKTEIL : 'GRAMMAR' [ '=' SYMBOLM ]  PRODUKTION* 'eof' .     */
  /* PRODUKTION    : SYMBOLM ':' ALTERNATIVEN '.' .                     */
  /* ALTERNATIVEN  : ALTERNATIVE ('//' ELEMENT )* .                     */
  /* ALTERNATIVE   : FOLGE ('/' FOLGE )* .                              */
  /* FOLGE         : ELEMENT* .                                         */
  /* ELEMENT       : SYMBOLM / '$' SYMBOLM / '@' SYMBOLM /              */
  /*                 '&' SYMBOLM /                                      */
  /*                 '(' ALTERNATIVEN ')' / '[' ALTERNATIVEN ']' /      */
  /*                 ELEMENT '*' / ELEMENT '+' .                        */
  /* SYMBOLM       : BEZEICHNER / 'BRACKET' / 'CODE' / 'GRAMMAR' /      */
  /*                 'META' / 'SEPA' / 'SKIP' / 'STACK' / 'STOP' /      */
  /*                 'SYMBOL' .                                         */
  /* BEZEICHNER    : 'BUCHSTABE' ( 'BUCHSTABE' / 'ZIFFER' / '-' )* .    */
  /*                                                                    */
  /*                                                                    */
  /* DABEI STEHT                                                        */
  /*              '@'  FUER  'REDUZIERE BEI'                            */
  /*              '$'  FUER  'REDUZIERE NICHT BEI'                      */
  /*              '&'  VOR EINER STRUKTURANKNUEPFUNG                    */
  /*                                                                    */
  /*                                                                    */
  /* SYMBOLE in DER SYMBOLTABELLE KOENNEN 5 ZUSTAENDE ANNEHMEN:         */
  /* UNDEF(INIERT),TERMINAL,NICHTTERMINAL,FEHLERHAFT,                   */
  /* STRUKTURAN(KNUEPFUNG).                                             */
  /* UNDEFINIERT SIND ALLE SYMBOLE, VON DENEN NOCH NICHT FESTSTELLBAR   */
  /* IST, OB SIE TERMINAL ODER NICHTTERMINAL SIND.                      */
  /* FEHLERHAFT SIND ALLE SYMBOLE DEREN ARTEN (SYMART1), WENN SIE       */
  /* MEHRFACH DEFINIERT WERDEN, NICHT DIE PARTIELLE UEBERFUEHRBARKEITS- */
  /* RELATION [(UNDEF->TERMINAL),(UNDEF->NICHTTERMINAL)] + IDENTITAET   */
  /* ERFUELLEN.                                                         */
  /*                                                                    */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*           AKTPRODNR  = AKTUELLE ANZAHL VON BNFPRODUKTIONEN +1 ,    */
  /*           SYMNRMENGE,                                              */
  /*           STOPSYMNR,                                               */
  /*           GRAMTITEL,                                               */
  /*           MAXBITS2,                                                */
  /*           SYMBOLTABELLE.                                           */
  /*                                                                    */
  /* MODULAUFBAU:                                                       */
  /*        function  FEHLERPUNKT(1) : boolean;                         */
  /*        procedure FEHLERINSTAND(2);                                 */
  /*        function  FREIESYMNR(2) : SYMNRBEREICH;                     */
  /*        procedure STREICHE(1);                                      */
  /*        function  SUCHSYMBOL(4) : SYMBOLTYP;                        */
  /*        function  SUCHETSYMBOL(3) : SYMBOLTYP;                      */
  /*        function  SUCHENTSYMBOL(2) : SYMBOLTYP;                     */
  /*        procedure SUCHESYMBOL(6);                                   */
  /*        procedure CODETEIL;                                         */
  /*        procedure KELLERTEIL;                                       */
  /*        procedure STOPTEIL;                                         */
  /*        procedure FEHLERTEIL(2);                                    */
  /*        procedure METATEIL;                                         */
  /*        procedure GRAMMATIKTEIL;                                    */
  /*                                                                    */
  /**********************************************************************/
  struct LOC_Lalreingabe V;

  /*$page*/
  V.LINK = LINK;
  if (setjmp(V._JL1))
    goto _L1;
  /* INITIALISIERUNG */
  V.Symbolmenge = (1L << ((long)Bezeichner)) | (1L << ((long)Bracket)) |
      (1L << ((long)Code)) | (1L << ((long)Grammar)) | (1L << ((long)Meta)) |
      (1L << ((long)Sepa)) | (1L << ((long)Skip)) | (1L << ((long)Stack)) |
      (1L << ((long)Stop)) | (1L << ((long)Symbol));
  V.Elemenge = V.Symbolmenge | (1L << ((long)Eklauf)) |
      (1L << ((long)Rklauf)) | (1L << ((long)Und)) | (1L << ((long)Klamaffe)) |
      (1L << ((long)Dollar)) | (1L << ((long)Plus)) | (1L << ((long)Stern));
  LINK->Imgrammatikteil = false;
  LINK->Metaexist = false;
  /* INITIALISIERUNG-ENDE */
  Liessymbol(LINK);
  if (LINK->Symart != Dollar)
    Fehler(5L, (long)LINK->Symlaenge, LINK->Symbez);
  else
    Liessymbol(LINK);

  Codeteil(&V);
  Kellerteil(&V);
  Stopteil(&V);
  Fehlerteil(Sepa, Separator, &V);
  Fehlerteil(Bracket, Semklammer, &V);
  Fehlerteil(Skip, Ueberlesen, &V);
  Metateil(&V);
  Grammatikteil(&V);
  /***/
_L1: ;   /* EINGABE-ANALYSE-ABBRUCH-SPRUNGZIEL */
  /***/
}  /* VON LALREINGABE*/


/*$page*/
Static Void Eingabe()
{  /* VOM EINGABE - ANWEISUNGSTEIL */
  /*        *******/
  /**********************************************************************/
  /*                                                                    */
  /*               EINGABE-MODUL                                        */
  /*               =============                                        */
  /*                                                                    */
  /* EINGABE VERARBEITET DIE DATEI EINDAT,UNTERSUCHT SIE AUF EINGABE-   */
  /* FEHLER,UEBERSETZT DIE EINGABEGRAMMATIK in EINFACHE BNF-NOTATION,   */
  /* ERSETZT DIE                                                        */
  /* METAELEMENTE, BAUT DIE CODIERUNGS- UND SYMBOLTABELLE AUF MIT DEN   */
  /* ZUSATZINFORMATIONEN UEBER ZU KELLERNDE TERMINALZEICHEN UND UEBER   */
  /* DIE ANKNUEPFUNGEN UND MODIFIKATIONEN, SPEICHERT DIE UEBERSETZTE    */
  /* GRAMMATIK in GUENSTIGER ZUGRIFFSSCHNELLER UND PLATZSPARENDER       */
  /* DATENSTRUKTUR - ZUR WEITERVERARBEITUNG DURCH ANDERE MODULN-        */
  /* UND SCHREIBT JE NACH OPTION B UND E DIE EINGABEGRAMMATIK           */
  /* in NICHTUEBERSETZTER UND UEBERSETZTER FORM in DAS PROTOKOLL.       */
  /* DIE VARIABLEN SYMBEZ UND USYMBEZ HABEN FUER DIE FAELLE SYMBOL      */
  /* UND BEZEICHNER DEN GLEICHEN STRING ZUM INHALT.                     */
  /*                                                                    */
  /* DIE PEGEL LETZTSYMI UND -J ZEIGEN AUF DIE LETZTE UND DAMIT         */
  /* HOECHSTE SYMBOLNUNMER, DIE DURCH DEN LETZTEN AUFRUF VON            */
  /* FREIESYMNR VERGEBEN WURDE.                                         */
  /*                                                                    */
  /* AUSGABEPARAMETER SIND:                                             */
  /*    CODIERUNGSTABELLE                                               */
  /*    SYMBOLTABELLE                                                   */
  /*    STACKTABELLE                                                    */
  /*    PRODUKTIONENTABELLE                                             */
  /*                                                                    */
  /* EXTERNAL:                                                          */
  /*           MAXSYMSETINDEX,                                          */
  /*           MAXSYMLAENGE,                                            */
  /*           SYMBOLSTRING,                                            */
  /*           USYMBOLSTRING,                                           */
  /*           SYMNRBEREICH,                                            */
  /*           SYMLAENGENBEREICH,                                       */
  /*           SYMNRTYP,                                                */
  /*           KEINEFEHLER,                                             */
  /*           TAB,NTAB,INAB,                                           */
  /*           ZEIT,EAZEIT,                                             */
  /*           OPTIONS.                                                 */
  /*                                                                    */
  /* DATEIEN:                                                           */
  /*         EINDAT      : text; (AUSGABE/EINGABE)                      */
  /*         SYMBOLDA : DRUSYMFILE; (AUSGABE)                           */
  /*         FEHLERDA   : text; (AUSGABE/EINGABE)                       */
  /*         VOKDAT      : text; (AUSGABE/EINGABE)                      */
  /*                                                                    */
  /*         PRODUDAT    : text; (AUSGABE)                              */
  /*             HIER WERDEN DIE BNF-PRODUKTIONEN DRAUFGESCHRIEBEN      */
  /*                                                                    */
  /* LOKALE GROESSEN SIND:                                              */
  /*    SYMLAENGE       : LAENGE DES BEARBEITETEN SYMBOLS               */
  /*    USYMBEZ         : GERADE BEARBEITETES SYMBOL (UNGEPACKT)        */
  /*    SYMBEZ          : GERADE BEARBEITETES SYMBOL (GEPACKT)          */
  /*    SYMART          : ART DES GERADE BEARBEITETEN SYMBOLS           */
  /*    ZAHLEN          : ['0'..'9']                                    */
  /*    BEZMENGE        : ['A'..'Z','-','_'] + ZAHLEN                   */
  /*    IMGRAMMATIKTEIL : BESCHLEUNIGT DAS ERKENNEN VON BEZEICHNERN     */
  /*    SYMBOLNUMMER    : MENGE ALLER BENUTZTEN SYMBOLNUMMERN           */
  /*    ZEILENNUMMER    : AKTUELLE ZEILENNUMMER BEZUEGLICH DER DATEIEN  */
  /*                      EINDAT UND GRAMDAT                            */
  /*    CODENR          : ENTHAELT DEN WERT DER GELESENEN ZAHL, WENN    */
  /*                      SYMART = ZAHL IST                             */
  /*    METATABHASH     : HASTABELLE FUER DIE METASYMBOLE               */
  /*                                                                    */
  /* MODULAUFBAU:                                                       */
  /*        procedure FEHLERTEXT(5);                                    */
  /*        procedure FEPROZ(6);                                        */
  /*        procedure FEHLER(3);                                        */
  /*        procedure BNFFEHLER(4);                                     */
  /*        procedure ZUSYMBOL(2);                                      */
  /*        function  LEERSCHNITTMENGE(3): boolean;                     */
  /*        procedure LIESSYMBOL;                                       */
  /*        procedure FREISPALTEN(3);                                   */
  /*        procedure DRUCKEBEZ(3);                                     */
  /*        procedure DRUCKEVOKABULAR;                                  */
  /*        procedure DRUCKEMETATABELLE;                                */
  /*        procedure DRUCKEBNFGRAMMATIK(1);                            */
  /*        procedure ERGAENZESYMTAB(2);                                */
  /*        procedure MINMAXBNFFEHLER(2);                               */
  /*        procedure LRVORAUS;                                         */
  /*        procedure KANONISIERE;                                      */
  /*        procedure UEBERFLUESSIG;                                    */
  /*        procedure LALREINGABE;                                      */
  /*                                                                    */
  /**********************************************************************/
  struct LOC_Eingabe V;
  Char Ch;
  short Minbnf, Maxbnf;
  int I;
  long Hntzaehler, Fehlerzeilennr;
  boolean Druein;   /* DRUCKE EINGABEGRAMMATIK */

  /*$page*/
  /**********************************************************************/
  /*  INITIALISIERUNG                                                   */
  /**********************************************************************/
  if (Eindat != NULL) Eindat = freopen("Eindat", "r", Eindat);
  else Eindat = fopen("Eindat", "r");
  if (Eindat == NULL) _EscIO(FileNotFound);
  RESETBUF(Eindat, Char);

  P_addset(P_expset(V.Zahlen, 0L), (unsigned)'0');
  P_addset(V.Zahlen, (unsigned)'1');
  P_addset(V.Zahlen, (unsigned)'2');
  P_addset(V.Zahlen, (unsigned)'3');
  P_addset(V.Zahlen, (unsigned)'4');
  P_addset(V.Zahlen, (unsigned)'5');
  P_addset(V.Zahlen, (unsigned)'6');
  P_addset(V.Zahlen, (unsigned)'7');
  P_addset(V.Zahlen, (unsigned)'8');
  P_addset(V.Zahlen, (unsigned)'9');
  P_setunion(V.Bezmenge, P_expset(V.Bezmenge, 0L), V.Zahlen);
  P_addset(V.Bezmenge, (unsigned)'A');
  P_addset(V.Bezmenge, (unsigned)'B');
  P_addset(V.Bezmenge, (unsigned)'C');
  P_addset(V.Bezmenge, (unsigned)'D');
  P_addset(V.Bezmenge, (unsigned)'E');
  P_addset(V.Bezmenge, (unsigned)'F');
  P_addset(V.Bezmenge, (unsigned)'G');
  P_addset(V.Bezmenge, (unsigned)'H');
  P_addset(V.Bezmenge, (unsigned)'I');
  P_addset(V.Bezmenge, (unsigned)'J');
  P_addset(V.Bezmenge, (unsigned)'K');
  P_addset(V.Bezmenge, (unsigned)'L');
  P_addset(V.Bezmenge, (unsigned)'M');
  P_addset(V.Bezmenge, (unsigned)'N');
  P_addset(V.Bezmenge, (unsigned)'O');
  P_addset(V.Bezmenge, (unsigned)'P');
  P_addset(V.Bezmenge, (unsigned)'Q');
  P_addset(V.Bezmenge, (unsigned)'R');
  P_addset(V.Bezmenge, (unsigned)'S');
  P_addset(V.Bezmenge, (unsigned)'T');
  P_addset(V.Bezmenge, (unsigned)'U');
  P_addset(V.Bezmenge, (unsigned)'V');
  P_addset(V.Bezmenge, (unsigned)'W');
  P_addset(V.Bezmenge, (unsigned)'X');
  P_addset(V.Bezmenge, (unsigned)'Y');
  P_addset(V.Bezmenge, (unsigned)'Z');
  P_addset(V.Bezmenge, (unsigned)'a');
  P_addset(V.Bezmenge, (unsigned)'b');
  P_addset(V.Bezmenge, (unsigned)'c');
  P_addset(V.Bezmenge, (unsigned)'d');
  P_addset(V.Bezmenge, (unsigned)'e');
  P_addset(V.Bezmenge, (unsigned)'f');
  P_addset(V.Bezmenge, (unsigned)'g');
  P_addset(V.Bezmenge, (unsigned)'h');
  P_addset(V.Bezmenge, (unsigned)'i');
  P_addset(V.Bezmenge, (unsigned)'j');
  P_addset(V.Bezmenge, (unsigned)'k');
  P_addset(V.Bezmenge, (unsigned)'l');
  P_addset(V.Bezmenge, (unsigned)'m');
  P_addset(V.Bezmenge, (unsigned)'n');
  P_addset(V.Bezmenge, (unsigned)'o');
  P_addset(V.Bezmenge, (unsigned)'p');
  P_addset(V.Bezmenge, (unsigned)'q');
  P_addset(V.Bezmenge, (unsigned)'r');
  P_addset(V.Bezmenge, (unsigned)'s');
  P_addset(V.Bezmenge, (unsigned)'t');
  P_addset(V.Bezmenge, (unsigned)'u');
  P_addset(V.Bezmenge, (unsigned)'v');
  P_addset(V.Bezmenge, (unsigned)'w');
  P_addset(V.Bezmenge, (unsigned)'x');
  P_addset(V.Bezmenge, (unsigned)'y');
  P_addset(V.Bezmenge, (unsigned)'z');
  P_addset(V.Bezmenge, (unsigned)'-');
  P_addset(V.Bezmenge, (unsigned)'_');
  
  Zeilennummer = 1;
  Fehlerzahl = 0;
 
/******  setcpy(V.Symnrmenge,*****/ P_expset(V.Symnrmenge, 0L);
  memcpy(Kellermenge, V.Symnrmenge, sizeof(Symnrtyp));
  memcpy(Separator, V.Symnrmenge, sizeof(Symnrtyp));
  memcpy(Semklammer, V.Symnrmenge, sizeof(Symnrtyp));
  memcpy(Ueberlesen, V.Symnrmenge, sizeof(Symnrtyp));

  V.Letztsymi = 0;
  V.Letztsymj = 0;
  Aktmaxrslaenge = 0;
  Aktmaxsymlaenge = 1;
  Aktmaxterm = 0;
  Aktmaxnterm = 0;
  Maxterminalcode = 0;

  for (I = 0; I <= Maxsymnr; I++) Symboltabelle[I] = (Tsymboltyp *)0;
  for (I = 0; I < Maxsymlaenge; I++) {
    V.Symboltabhash[I] = (Tsymboltyp *)0;
    V.Metatabhash[I] = (Tmetatyp *)0;
  }
  V.Symbez = (Char *)0;

/* p2c: eingabe.p, line 3672: Note: REWRITE does not specify a name [181] */
  if (Fehlerda != NULL)
    Fehlerda = freopen("Fehlerda", "w", Fehlerda);
  else
    Fehlerda = fopen("Fehlerda", "w");
  if (Fehlerda == NULL)
    _EscIO(FileNotFound);
  SETUPBUF(Fehlerda, Char);

  fprintf(Putout, "PGS 8.0 --- Input\n");

  /* INITIALISIERUNG-ENDE */


  /**********************************************************************/
  /*      EINGABE-GRAMMATIK  ANALYSE                                    */
  /**********************************************************************/

  Lalreingabe(&V);

  fprintf(Fehlerda, "#\n");
  /* TRENNZEICHEN ZWISCHEN in DIE EINGABEGRAMMATIK EINGESTREUTEN
     FEHLERMELDUNGEN UND NICHT GENAU LOKALISIERBAREN FEHLERMELDUNGEN*/

  Ergaenzesymtab(&Hntzaehler, &V);

  /**********************************************************************/
  /*    TEST AUF -LR- VORAUSSETZUNGEN                                   */
  /*    *****************************                                   */
  /*                                                                    */
  /*  DAS ZIEL DER GRAMMATIK DARF NUR in EINER PRODUKTION AUF DER LINKEN*/
  /*  SEITE VORKOMMEN UND SONST NIRGENDS.                               */
  /*  BESTIMMUNG DER STARTPRODUKTION                                    */
  /**********************************************************************/
  Lrvoraus(&V);
  Kanonisiere(&V);
  if (Keinefehler)
    Ueberfluessig(&V);

  fprintf(Putout, "\nInput Summary\n");
  fprintf(Putout, "=============\n\n");
  fprintf(Putout, "Options                          : ");
  for (Ch = 'A'; Ch <= 'Z'; Ch++) {
    if (P_inset(Ch, Options))
      putc(Ch, Putout);
  }
  fprintf(Putout, "\nNumber of lines                  : %ld\n",
	  Zeilennummer - 1);

  fprintf(Putout, "Number of errors                 : %ld\n", Fehlerzahl);
  fprintf(Putout, "BNF rules                        : %d\n", Aktmaxprodnr);
  fprintf(Putout, "Total length of right-hand sides : %d\n", Aktrspos - 1);
  fprintf(Putout, "Max.length of a right-hand side  : %d\n", Aktmaxrslaenge);
  if (Keinefehler)
    fprintf(Putout, "Number of start production       : %d\n",
	    Startproduktion);
  fprintf(Putout, "Number of symbols                : %d\n", Maxsymzahl);
  fprintf(Putout, "Largest terminal code            : %d\n", Aktmaxsymnr);
  fprintf(Putout, "Maximum length of a symbol       : %d\n", Aktmaxsymlaenge);

  Druckevokabular(&Hntzaehler, &V);
  if (P_inset('V', Options) && V.Metaexist)
    Druckemetatabelle(&V);
  fprintf(Putout, "\n\n");
  Zeilennummer = 1;
  if (Fehlerda != NULL)
    Fehlerda = freopen("Fehlerda", "r", Fehlerda);
  else
    Fehlerda = fopen("Fehlerda", "r");
  if (Fehlerda == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Fehlerda, Char);
  Fehlerzeilennr = 0;
  if (P_peek(Fehlerda) != '#')
    FehlerdaInt(&Fehlerzeilennr);
  if (Eindat != NULL)
    Eindat = freopen("Eindat", "r", Eindat);
  else
    Eindat = fopen("Eindat", "r");
  if (Eindat == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Eindat, Char);
  Druein = P_inset('E', Options);
  if (Druein || !Keinefehler) {
    fprintf(Putout, "Input Grammar\n");
    fprintf(Putout, "=============\n");
    while (!P_eof(Eindat)) {
      if (!(Druein || Zeilennummer == Fehlerzeilennr)) {
	fscanf(Eindat, "%*[^\n]");
	getc(Eindat);
	Zeilennummer++;
	continue;
      }
      if (P_eoln(Eindat)) {
	putc('\n', Putout);
	while (Zeilennummer == Fehlerzeilennr) {
	  while (!P_eoln(Fehlerda)) {
	    putc(P_peek(Fehlerda), Putout);
	    getc(Fehlerda);
	  }
	  putc('\n', Putout);
	  getc(Fehlerda);
	  if (P_peek(Fehlerda) == '#')
	    Fehlerzeilennr = 0;
	  else
	    FehlerdaInt(&Fehlerzeilennr);
	}
	Zeilennummer++;
      } else
	putc(P_peek(Eindat), Putout);
      getc(Eindat);
    }
    putc('\n', Putout);
  }
  if (Fehlerzeilennr != 0) {
    fprintf(Putout, "!!!Error!!!\n");
    fprintf(Putout, "%6ld", Fehlerzeilennr);
    while (P_peek(Fehlerda) != '#') {
      if (P_eoln(Fehlerda))
	putc('\n', Putout);
      else
	putc(P_peek(Fehlerda), Putout);
      getc(Fehlerda);
    }
  }
  if (Aktmaxprodnr > 0) {
    /* FALLS UEBERHAUPT BNF-PRODUKTIONEN
                              ERZEUGT WURDEN */
    if (P_inset('B', Options))
      Druckebnfgrammatik(&Produdat, 1, Aktmaxprodnr, &V);
    else {
      if (!Keinefehler) {
	Minmaxbnffehler(&Minbnf, &Maxbnf);
	Druckebnfgrammatik(&Produdat, Minbnf, Maxbnf, &V);
      }
    }
  }

  if (Produdat != NULL)
    Produdat = freopen("Produdat", "r", Produdat);
  else
    Produdat = fopen("Produdat", "r");
  if (Produdat == NULL)
    _EscIO(FileNotFound);
  RESETBUF(Produdat, Char);
  while (!P_eof(Produdat)) {
    if (P_eoln(Produdat))
      putc('\n', Putout);
    else
      putc(P_peek(Produdat), Putout);
    getc(Produdat);
  }

  while (!P_eof(Fehlerda)) {
    if (P_eoln(Fehlerda))
      putc('\n', Putout);
    else
      putc(P_peek(Fehlerda), Putout);
    getc(Fehlerda);
  }
}  /* ENDE VON EINGABE */

#undef Maxzahllaenge
#undef Maxprodlaenge
#undef Maxmetapp
#undef Maxelemkeller
#undef Maxfokeller
#undef Maxatkeller
#undef Maxatnkeller


/*$page*/
int
main(argc, argv)
int argc;
Char *argv[];
{  /* LALREIN - ANWEISUNGSTEIL */

  /* INITIALISIERUNG  */
  PASCAL_MAIN(argc, argv);
  Eindat = NULL;
  Vokdat = NULL;
  Symbolda = NULL;
  Vareinda = NULL;
  Gszeit = 0;
  Eazeit = 0;
  for (I = 0; I <= Maxsymnr; I++) Symtab[I] = NULL;
  for (I = 1; I <= Maxprodnr; I++) Ls[I - 1] = NULL;
  obstack_init(&SymObs);

  Putout = fopen("Putout", "w");
  if (Putout == NULL) _EscIO(FileNotFound);

  Fehlerda = fopen("Fehlerda", "w");
  if (Fehlerda == NULL) _EscIO(FileNotFound);
  SETUPBUF(Fehlerda, Char);

  Produdat = fopen("Produdat", "w");
  if (Produdat == NULL) _EscIO(FileNotFound);
  SETUPBUF(Produdat, Char);

  Keinefehler = true;
  InitOptions();

  /* INITIALISIERUNG-ENDE  */

  Egtlaenge = 0;

  Eingabe();
  Eingabeaus();

#ifdef MONITOR
{
  int i, j, *lens;
  Char *cp;

  prodsfile = fopen("mon_cprods.h", "w");
  fprintf (prodsfile,
    "#ifdef MONITOR\nCONST char *conc_prods[] = {\n(char *) 0,\n");
  lens = (int *) malloc (sizeof (int) * Maxprodnr);
  lens[0] = 0;
  for (i = 1; i <= Maxprodnr; i++) {
    Tlstyp *l = Ls[i - 1];

    if (l == (Tlstyp *) 0) {
      break;
    } else {
      Trstyp *r = &Rs[i - 1];
      int lim = r->Rsanfang + r->Rslaenge - 2;
      Tsymboltyp *sym;
      int len = 0;

      fprintf (prodsfile, "\"%s : ", Symboltabelle[l->Symnr]->Bezeichner);
      for (j = r->Rsanfang - 1; j <= lim; j++) {
        sym = Symboltabelle[Rsfeld[j]];
        if (((1L << sym->Symart1) & (1L << ((long)Terminal))) != 0) {
	  if (*sym->Bezeichner != '\'')
            fputc ('\'', prodsfile);
          for (cp = sym->Bezeichner; *cp != '\0'; cp++) {
            if (*cp == '"')
              fputc ('\\', prodsfile);
            fputc (*cp, prodsfile);
          }
          if (*sym->Bezeichner != '\'')
            fputc ('\'', prodsfile);
          fputc (' ', prodsfile);
        }
	else if (((1L << sym->Symart1) & (1L << ((long)Nichtterminal))) != 0) {
	  fprintf (prodsfile, "%s ", sym->Bezeichner);
	  len++;
        }
      }
      lens[i] = len;
      fprintf (prodsfile, ".\",\n");
    }
  }
  fprintf (prodsfile, "};\n\nint ntlen[] = {\n");
  for (j = 0; j < i; j++)
    fprintf (prodsfile, "%d,\n", lens[j]);
  fprintf (prodsfile, "};\n#else\n/* To avoid messages about empty files*/\n");
  fprintf (prodsfile, "static int _dapto;\n#endif\n");
  fclose (prodsfile);
}
#endif

  return Fehlerzahl == 0 ? 0 : 1;
}
/* End. */
