#ifndef PARAMETER_H
#define PARAMETER_H
/* $Id: parameter.h,v 1.8 2009/03/13 19:16:41 profw Exp $ */

#define Maxdruckspalte  72
#define Maxdruckzeile   55
#define Maxsymlaenge    70
    /* If this is changed, change all string constants!! */
#define Maxbits2        256   /* IMPL.ABH */
#define Maxbit2         255   /* IMPLEMENTIERUNGSABHAENGIG */
#define Izeiteinheit    1000
#define Maxlaengeallerrs  20000
/*6000*/
/* SCHAETZWERT: 3*MAXPRODNR */
/*  >= MAX(AKTMAXPRODNR,AKTMAXZUSTAND), SIEHE TUEBERLISTTYP */
#define Unendlich       10000   /* WILLKUERLICH, ABER > MAXSYMNR */
#define Maxhash         127
#define Zlies           0
#define Zliesreduziere  1
#define Zreduziere      2
#define Datumsgrenze    24

#define Maxsymsetindex  7   /*0<=SYMNR<(MAXSYMSETINDEX+1)*Maxbits2*/
#define Maxsymnr        2040   /* MAXSYMNR<=(MAXSYMSETINDEX+1)*MAXBITS2-1 */
#define Maxprodnr       1536   /* ANZAHL DER BNF-PRODUKTIONEN */
#define Maxprodindex    5   /*0<PRODNRBEREICH<(MAXPRODINDEX+1) *MAXBITS2 */
#define Maxlaengers     15
/*LAENGE DER RECHTEN SEITE EINER
                         PRODUKTION. MINDEST  >=3 ! */
#define Maxterm         1023   /* <= (MAXTERMINDEX+1)*MAXBITS2-1 */
#define Maxnterm        1023   /* <=(MAXNTERMINDEX+1)*MAXBITS2-1 */
#define Maxntermindex   3
    /*0<NTERMINALBEREICH<(MAXNTERMINDEX+1) *MAXBITS2 */
#define Maxtermindex    3   /*0<TERMINALBEREICH<(MAXTERMINDEX+1) *MAXBITS2 */
#define Maxzustand      4000   /* = MAXVEKTOR <= (MAXZUINDEX+1)*MAXBITS2-1 */
#define Maxzuindex      15   /*0<ZUSTANDSBEREICH<(MAXZUINDEX+1)*MAXBITS2 */
#define Maxspalte       300
#define Maxvektor       Maxzustand
#define Maxtermwort     31   /* 8*(MAXTERMINDEX + 1) - 1 */
#define Prim            1009


/*STEUERGROESSE FUER HASHFUNKTION
                           =  1. PRIMZAHL > 1000 */

/* MAXSYMNR,MAXPRODNR,MAXTERM,MAXNTERM,MAXZUSTAND SOLLTEN MOEGLICHST
   GUT GESCHAETZT ODER AM BESTEN EXAKT BESTIMMT WERDEN.
   DIE GENANNTEN KONSTANTEN HABEN DEN HAUPTEINFLUSS AUF DEN
   HAUPTSPEICHERBEDARF. */

#endif
