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

static char RCSid[] = "$Id: buildtab.c,v 8.4 2013/11/12 20:38:25 profw Exp $";

#include <stdlib.h>

/**********************************************************************/
/*                                                                    */
/*     Eingabe :                                                      */
/*     -  ZerDat : file of integer, die vom PGS erzeugten Zerteiler-  */
/*                 tabellen.                                          */
/*                                                                    */
/*     -  ZuDat  : textfile, die gesetzten Tabellenoptionen und die   */
/*                 vom PGS erzeugten Zerteilerkonstanten.             */
/*                                                                    */
/*     Ausgabe :                                                      */
/*     -  ZerTab : textfile, die fuer den Zerteiler erstellten Ta-    */
/*                 bellenvereinbarungen mit Initialisierungen.        */
/*                                                                    */
/**********************************************************************/

/**********************************************************************/
/*                 Makrovereinbarungen                                */
/**********************************************************************/

/* Sollten die Makrovereinbarungen im Zerteilerrahmen geandert werden,*/
/* so muss diese Aenderung auch hier erfolgen.                        */
typedef unsigned char   K_TYP1;    /* 1 Byte  unsigned */
typedef unsigned short  K_TYP2;    /* 2 Bytes unsigned */
typedef unsigned short  M_TYP;     /* Komponententyp des Mengenfeldes */
#define M_BITS  16                 /* (Bits pro Byte) * sizeof(M_TYP) */
#define M_SHIFT 4                  /* ld(M_BITS) */
#define M_MASKE 017                /* Maske : (M_BITS - 1) */
#define M_DIV(x) (x >> M_SHIFT)    /* x DIV M_BITS */
#define M_MOD(x) (x & M_MASKE)     /* x MOD M_BITS */
#define ZUMENGE(m,x) (*(m + M_DIV(x)) |= 01 << M_MOD(x))

/**********************************************************************/
/*                      Tabellenoptionen                              */
/**********************************************************************/

typedef unsigned short  bool;

#define true    1
#define false   0

bool  DEFAULTS;

/**********************************************************************/
/*                 Erzeugte Zerteilerkonstanten                       */
/**********************************************************************/

unsigned int
        ZEMAXTERMINALCODE, ZEMAXRSLAENGE, ZEANZZST,
        ZEMAXTEINTRAG, ZEMAXNTEINTRAG, ZEMAXTE1, ZEMAXTE2,
        ZEMAXNTE, ZEANZNT, ZEANZPROD,
        ZETINDEX, ZEMAXTNEXT, ZEMAXTCHECK, ZEMAXNTNEXT;

/**********************************************************************/
/*                 Vereinbarungen der Zerteilertabellen               */
/**********************************************************************/

/* Terminaltabelle */

K_TYP2   *TBase;        /* ZEANZZST + 1 */
K_TYP2   *TNext;        /* ZEMAXTNEXT + 1 */
K_TYP2   *TCheck;       /* ZEMAXTCHECK + 1 */
K_TYP2   *TZDefault;    /* ZEANZZST + 1 */

/* Nichtterminaltabelle */

K_TYP2   *NtBase;       /* ZEANZZST + 1 */
K_TYP2   *NtNext;       /* ZEMAXNTNEXT + 1 */
K_TYP2   *LS;           /* ZEANZPROD + 1 */
K_TYP2   *LaengeRS;     /* ZEANZPROD + 1 */
K_TYP2   *FSymbol;      /* ZEANZZST + 1 */
K_TYP2   *RSymbol;      /* ZEANZZST + 1 */
M_TYP    *SemKlammer;   /* ZETINDEX + 1 */
M_TYP    *Ueberlesen;   /* ZETINDEX + 1 */

/**********************************************************************/
/*                 NamenStrings der Zerteilertabellen                 */
/**********************************************************************/

/* Terminaltabelle */

#define  S_TBase "TBase[ ZEANZZST + 1]"
#define  S_TNext "TNext[ ZEMAXTNEXT + 1]"
#define  S_TCheck "TCheck[ ZEMAXTCHECK + 1]"
#define  S_TZDefault "TZDefault[ ZEANZZST + 1]"

/* Nichtterminaltabelle */

#define  S_NtBase "NtBase[ ZEANZZST + 1]"
#define  S_NtNext "NtNext[ ZEMAXNTNEXT + 1]"
#define  S_LS "LS[ ZEANZPROD + 1 ]"
#define  S_LAENGERS "LaengeRS[ ZEANZPROD + 1 ]"
#define  S_FSYMBOL "FSymbol[ ZEANZZST + 1 ]"
#define  S_RSYMBOL "RSymbol[ ZEANZZST + 1 ]"
#define  S_SEMKLAMMER "SemKlammer[ ZETINDEX + 1 ]"
#define  S_UEBERLESEN "Ueberlesen[ ZETINDEX + 1 ]"

char  S_K_TYP1[] = "static  K_TYP1",
      S_K_TYP2[] = "static  K_TYP2",
      S_M_TYP[]  = "static  M_TYP";


#include <stdio.h>
#define  MAXBYTE 255

typedef int       D_TYP2;      /* 2 Byte Integer */
typedef long      D_TYP4;      /* 4 Byte Integer */

FILE        *ZerDat, *ZerTab, *ZuDat, *fopen();

void K_Check (K_TYP2*);
void M_Check (M_TYP*);
void ZuMenge (M_TYP*, K_TYP2);
void Ausgabe_d (register K_TYP2*, register int);
void Ausgabe_x (register M_TYP*, register int);
void Test (D_TYP2, D_TYP2);
void Lies_Konstante (void);

int
main(argc, argv)
int   argc;
char  *argv[];
{
  K_TYP2  i, j;
  D_TYP2  zd;
  D_TYP2           Next();
 
  if (argc != 4)
  { (void)fprintf(stderr,
                  "*** usage: %s <infile> <outfile> <constfile>\n",
                  *argv);
    return 1;
  }
  if ((ZerDat = fopen(*++argv, "rb")) == NULL)
  { (void)fprintf(stderr, "*** Cannot open file %s\n", *argv);
    return 1;
  }
  if ((ZerTab = fopen(*++argv, "w")) == NULL)
  { (void)fprintf(stderr, "*** Cannot open file %s\n", *argv);
    return 1;
  }
  if ((ZuDat = fopen(*++argv, "r")) == NULL)
  { (void)fprintf(stderr, "*** Cannot open file %s\n", *argv);
    return 1;
  }

  /* Einlesen der Tabellenoptionen */

  DEFAULTS = true;

  /* Einlesen der erzeugten Zerteilerkonstanten */

  Lies_Konstante();

  /* Speicherplatz fuer die Zerteilertabellen vom System beschaffen */

  TBase = (K_TYP2 *) malloc( (unsigned) (ZEANZZST+1) * sizeof(K_TYP2) );
  K_Check (TBase);
  TNext =
    (K_TYP2 *) malloc( (unsigned) (ZEMAXTNEXT+1) * sizeof(K_TYP2) );
  K_Check (TNext);
  TCheck =
    (K_TYP2 *) malloc( (unsigned) (ZEMAXTCHECK+1) * sizeof(K_TYP2) );
  K_Check (TCheck);

  if (DEFAULTS)
  { TZDefault =
      (K_TYP2 *) malloc( (unsigned) (ZEANZZST+1) * sizeof(K_TYP2) );
    K_Check (TZDefault);
  }

  NtBase =
    (K_TYP2 *) malloc( (unsigned) (ZEANZZST+1) * sizeof(K_TYP2) );
  K_Check (NtBase);
  NtNext =
    (K_TYP2 *) malloc( (unsigned) (ZEMAXNTNEXT+1) * sizeof(K_TYP2) );
  K_Check (NtNext);

  LS = (K_TYP2 *) malloc( (unsigned) (ZEANZPROD+1) * sizeof(K_TYP2) );
  K_Check (LS);
  LaengeRS =
    (K_TYP2 *) malloc( (unsigned) (ZEANZPROD+1) * sizeof(K_TYP2) );
  K_Check (LaengeRS);

  FSymbol =
    (K_TYP2 *) malloc( (unsigned) (ZEANZZST+1) * sizeof(K_TYP2) );
  K_Check (FSymbol);
  RSymbol =
    (K_TYP2 *) malloc( (unsigned) (ZEANZZST+1) * sizeof(K_TYP2) );
  K_Check (RSymbol);

  SemKlammer =
    (M_TYP *) malloc( (unsigned) (ZETINDEX+1) * sizeof(K_TYP2) );
  M_Check (SemKlammer);
  Ueberlesen =
    (M_TYP *) malloc( (unsigned) (ZETINDEX+1) * sizeof(K_TYP2) );
  M_Check (Ueberlesen);

  /* Beginn des Einlesens */

  for (i = 0; i <= ZETINDEX; i++)
  { SemKlammer[i] = (M_TYP) 0;
    Ueberlesen[i] = (M_TYP) 0;
  }

  for (i = 0; i <= ZEMAXTERMINALCODE; i++)
  {
    if (Next() == 1)
      ZuMenge(SemKlammer, i);
    if (Next() == 1)
      ZuMenge(Ueberlesen, i);
  }
  Test(Next(),-1);

  NtBase[0] = 0;
  for (i = 0; i <= ZEMAXNTNEXT; i++)
    NtNext[i] = 0;

  for (i = 1; i <= ZEANZZST; i++)
  { NtBase[i] = Next();
    while ((zd = Next()) != -2)
    { j = zd;
      NtNext[j] = Next();
    }
  }
  Test(Next(),-3);

  TBase[0] = 0;
  for (i = 0; i <= ZEMAXTCHECK; i++)
  { if (i <= ZEMAXTNEXT) TNext[i] = 0;
    TCheck[i] = 0;
  }

  for (i = 1; i <= ZEANZZST; i++)
  { TBase[i] = Next();
    while ((zd = Next()) != -4)
    { j = zd;
      TNext[j] = Next();
      TCheck[j] = i;
    }
  }
  Test(Next(),-5);

  if (DEFAULTS)
  { TZDefault[0] = 0;
    for (i = 1; i <= ZEANZZST; i++)
    { TZDefault[i] = Next();
    }
    Test(Next(),-6);
  }

  LS[0] = LaengeRS[0] = 0;

  for (i = 1; i <= ZEANZPROD; i++)
  { j = Next();
    LS[j] = Next();
    LaengeRS[j] = Next();
  }
  Test(Next(),-8);

  FSymbol[0] = RSymbol[0] = 0;

  for (i = 1; i <= ZEANZZST; i++)
  { FSymbol[i] = Next();
    RSymbol[i] = Next();
  }
  Test(Next(),-9);

  /* Beginn der Ausgabe */

  (void)fprintf(ZerTab, "&MACRO PGS_ZERTEILERTABELLEN\n");
  (void)fprintf(ZerTab, "%s    %s  =\n",
          (ZEMAXTNEXT <= MAXBYTE) ? S_K_TYP1 : S_K_TYP2, S_TBase);
  Ausgabe_d(TBase, ZEANZZST);
  (void)fprintf(ZerTab, ";\n\n");
  
  (void)fprintf(ZerTab, "%s    %s  =\n",
          (ZEMAXTEINTRAG <= MAXBYTE) ? S_K_TYP1 : S_K_TYP2, S_TNext);
  Ausgabe_d(TNext, ZEMAXTNEXT);
  (void)fprintf(ZerTab, ";\n\n");

  (void)fprintf(ZerTab, "%s    %s  =\n",
          (ZEANZZST <= MAXBYTE) ? S_K_TYP1 : S_K_TYP2, S_TCheck);
  Ausgabe_d(TCheck, ZEMAXTCHECK);
  (void)fprintf(ZerTab, ";\n\n");

  if (DEFAULTS)
  { (void)fprintf(ZerTab, "%s    %s  =\n",
            (ZEANZZST <= MAXBYTE) ? S_K_TYP1 : S_K_TYP2, S_TZDefault);
    Ausgabe_d(TZDefault, ZEANZZST);
    (void)fprintf(ZerTab, ";\n\n");
  }

  (void)fprintf(ZerTab, "\n\n");

  (void)fprintf(ZerTab, "%s    %s  =\n",
          (ZEMAXNTNEXT <= MAXBYTE) ? S_K_TYP1 : S_K_TYP2, S_NtBase);
  Ausgabe_d(NtBase, ZEANZZST);
  (void)fprintf(ZerTab, ";\n\n");
  
  (void)fprintf(ZerTab, "%s    %s  =\n",
          (ZEMAXNTEINTRAG <= MAXBYTE) ? S_K_TYP1 : S_K_TYP2, S_NtNext);
  Ausgabe_d(NtNext, ZEMAXNTNEXT);
  (void)fprintf(ZerTab, ";\n\n");

  (void)fprintf(ZerTab, "%s    %s  =\n",
          (ZEANZNT <= MAXBYTE) ? S_K_TYP1 : S_K_TYP2, S_LS);
  Ausgabe_d(LS, ZEANZPROD);
  (void)fprintf(ZerTab, ";\n\n");
  
  (void)fprintf(ZerTab, "%s    %s  =\n",
          (ZEMAXRSLAENGE <= MAXBYTE) ? S_K_TYP1 : S_K_TYP2, S_LAENGERS);
  Ausgabe_d(LaengeRS, ZEANZPROD);
  (void)fprintf(ZerTab, ";\n\n");

  (void)fprintf(ZerTab, "%s    %s  =\n",
       (ZEMAXTERMINALCODE <= MAXBYTE) ? S_K_TYP1 : S_K_TYP2, S_FSYMBOL);
  Ausgabe_d(FSymbol, ZEANZZST);
  (void)fprintf(ZerTab, ";\n\n");
  
  (void)fprintf(ZerTab, "%s    %s  =\n",
       (ZEMAXTERMINALCODE <= MAXBYTE) ? S_K_TYP1 : S_K_TYP2, S_RSYMBOL);
  Ausgabe_d(RSymbol, ZEANZZST);
  (void)fprintf(ZerTab, ";\n\n");
  
  (void)fprintf(ZerTab, "%s    %s  =\n", S_M_TYP, S_SEMKLAMMER);
  Ausgabe_x(SemKlammer, ZETINDEX);
  (void)fprintf(ZerTab, ";\n\n");
  
  (void)fprintf(ZerTab, "%s    %s  =\n", S_M_TYP, S_UEBERLESEN);
  Ausgabe_x(Ueberlesen, ZETINDEX);
  (void)fprintf(ZerTab, ";\n\n");

  return 0;
}


void
ZuMenge(M_TYP *pm, K_TYP2 i)
/* Nimmt i zur Menge *pm hinzu */
{
  ZUMENGE(pm, i);
}


D_TYP2 Next()
/* Liefert naechsten Wert von der Eingabedatei */
{
  D_TYP4  x;

  if ( fread( (char *)(&x), sizeof(x), 1, ZerDat ) == 0 )
  { (void)fprintf(stderr, "*** Error reading file ZerDat\n");
    (void)fclose(ZerDat); (void)fclose(ZerTab); (void)fclose(ZuDat);
    exit(1);
  }
  return((D_TYP2) x);
}


void
Test (zd, i)
D_TYP2  zd, i;
{
  if ( i != zd )
  { (void)fprintf(stderr, "*** Test %6d not sucessful\n", i);
    (void)fclose(ZerDat); (void)fclose(ZerTab); (void)fclose(ZuDat);
    exit(1);
  }
}


void
Ausgabe_d (feld, ende)
register K_TYP2 *feld;
register int    ende;
{
  register int i;

  (void)fprintf(ZerTab, "{");
  for (i = 0; i < ende; i++)
    (void)fprintf(ZerTab, "%4d,%c ", *feld++, i % 10 == 9 ? '\n' : ' ');
  (void)fprintf(ZerTab, "%4d }", *feld); 
}


void
Ausgabe_x (feld, ende)
register M_TYP  *feld;
register int    ende;
{
  register int i;

  (void)fprintf(ZerTab, "{");
  for (i = 0; i < ende; i++)
    (void)fprintf(ZerTab, "0X%-4x,%c ", *feld++,
                          i % 8 == 7 ? '\n' : ' ');
  (void)fprintf(ZerTab, "0X%-4x }", *feld); 
}


void
Lies_Konstante()
/* Liest die vom PGS erzeugten Zerteilerkonstanten von der */
/* Datei ZuDat ein                                         */
{ int c;
  char line[BUFSIZ];
 
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "&MACRO PGS_GEN_ZERTEILERKONSTANTE\n");
  /* Ueberlesen des Datums */
  fgets(line, BUFSIZ, ZuDat);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEMAXTERMINALCODE %d\n",
                      &ZEMAXTERMINALCODE);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEMAXRSLAENGE     %d\n",
                      &ZEMAXRSLAENGE);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEANZZST          %d\n", &ZEANZZST);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEMAXTEINTRAG     %d\n",
                      &ZEMAXTEINTRAG);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEMAXNTEINTRAG    %d\n",
                      &ZEMAXNTEINTRAG);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEMAXTE1          %d\n", &ZEMAXTE1);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEMAXTE2          %d\n", &ZEMAXTE2);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEMAXNTE          %d\n", &ZEMAXNTE);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEANZNT           %d\n", &ZEANZNT);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEANZPROD         %d\n", &ZEANZPROD);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEMAXTNEXT        %d\n", &ZEMAXTNEXT);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEMAXTCHECK       %d\n",
                      &ZEMAXTCHECK);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZEMAXNTNEXT       %d\n",
                      &ZEMAXNTNEXT);
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line,
           "#define    ZETINDEX          ZEMAXTERMINALCODE / M_BITS\n");
  ZETINDEX = ZEMAXTERMINALCODE / M_BITS;
  fgets(line, BUFSIZ, ZuDat);
  (void)sscanf(line, "#define    ZESTOPSYMBOL      %*d\n");

  if ((c = getc(ZuDat)) != EOF)
  { (void)fprintf(stderr, "*** Error reading file ZuDat\n");
    (void)fclose(ZerDat); (void)fclose(ZerTab); (void)fclose(ZuDat);
    exit(1);
  }
}


void
K_Check (z)
K_TYP2  *z;
{
  if (z == NULL)
  { (void)fprintf(stderr, "*** Malloc failed to return storage\n");
    (void)fclose(ZerDat); (void)fclose(ZerTab); (void)fclose(ZuDat);
    exit(1);
  }
}


void
M_Check (z)
M_TYP *z;
{
  if (z == NULL)
  { (void)fprintf(stderr, "*** Malloc failed to return storage\n");
    (void)fclose(ZerDat); (void)fclose(ZerTab); (void)fclose(ZuDat);
    exit(1);
  }
}
