#ifndef PTABS_H
#define PTABS_H

/* generated constants */


#define BASE		1

#define PAEOF		1

#define STPROD		67



/* generated tables which are not */
/* changable by optimization      */


static unsigned char conncode[]  =  {

  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,
  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,
  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,   0,  53,  54,  55,  56,
  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,
  73,  74,  75,   0 
};



static unsigned char lhs [] =  {

      1,     2,     2,     3,     3,     5,     5,     7,     9,    11,    11
,    12,    13,    13,    14,     4,    14,    14,    14,    20,     8,     8
,    23,    23,    25,    25,    16,    16,    16,    16,    28,    29,    29
,    32,    27,    33,    33,    34,    35,    17,    36,    15,    15,    18
,    18,     0,    31,    38,    26,    26,    21,    21,    39,    39,    22
,    22,    30,    30,    37,    37,    37,     6,    24,    10,    10,    19
,    19,    40
};



static unsigned char len [] =  {

      0,     3,     1,     1,     1,     0,     2,     1,     4,     0,     2
,     2,     1,     1,     2,     1,     1,     3,     1,     3,     0,     2
,     0,     2,     0,     2,     0,     2,     2,     2,     1,     5,     3
,     1,     2,     1,     1,     1,     1,     3,     4,     1,     1,     1
,     3,     2,     1,     1,     4,     6,     0,     2,     1,     1,     0
,     2,     0,     4,     0,     1,     3,     1,     2,     1,     1,     1
,     1,     2
};



static unsigned char cont[]  =  {

  28,  28,  28,   1,   1,  26,  26,  26,  26,  16,   5,  25,  15,  15,  15,  15,
   1,   5,  25,  25,  19,  20,  20,   7,  15,  20,  15,  20,  19,  20,  10,  14,
  20,  15,  25,  19,   7,  15,   7,  26,  16,  16,  26,   7,   7,  28,   5,   6,
   7 
};



static char terminf[]  =  {

0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};



/* macro for accessing the terminal-table */
/* the Row Displacement Scheme is performed for the terminal-table */

#define SIGMAP(row , col) (sigmap[row][col >> 3] >> (col & 0x0007)) & 0x01

#define GET_TTABENTRY( RorS, Act, term ) \
	{\
	  register    U_SHORT j;\
	  j = conv[ term ]; \
	  if( SIGMAP( sigrowind[RorS], sigcolind[j] ) )  { \
	    j = ttab[ trowptr[RorS] + j ]; \
	    Act  = j & ACTIONMASK; \
	    RorS = j & OPERANDMASK; \
	  }\
	  else \
	    Act  = 0; \
	}

static unsigned char conv [] =  {

      0,     0,     1,     2,     3,     4,     5,     6,     7,     8,     9
,    10,    11,    12,    13,    14,    15,    16,    17,    18,    19,    20
,    21,    22,    23,    24,    25,    26,    27
};



static unsigned char sigrowind [] =  {

      0,     1,     2,     3,     3,     4,     5,     6,     7,     8,     9
,    10,    11,    12,    13,    11,    11,    14,    15,    10,    16,    17
,    18,    19,    20,    17,    20,    21,    22,    23,    24,    25,    26
,    12,    10,    16,    19,    12,    27,    28,    29,    30,     6,    27
,    27,     1,    14,    31,    27
};



static unsigned char sigcolind [] =  {

      0,     1,     1,     2,     3,     4,     5,     6,     7,     8,     9
,     9,     7,    10,    11,    12,     7,     7,     7,    13,    14,    14
,    15,    16,    16,    17,    18,    19
};



static unsigned char sigmap[][3] =  {

 0x44,0x90,0x0a,0x04,0x99,0x0a,0x04,0x90,0x0a,0x01,0x00,0x00,0x04,0x99,0x02,0x04
,0x90,0x02,0x04,0x19,0x02,0x04,0x10,0x02,0x00,0x10,0x00,0x09,0x08,0x04,0x00,0x00
,0x01,0x01,0x08,0x00,0x00,0x08,0x00,0x01,0x08,0x04,0x08,0x00,0x00,0x08,0x00,0x01
,0xa2,0x0b,0x00,0xa2,0x2f,0x00,0x22,0x26,0x00,0x20,0x02,0x00,0x00,0x09,0x00,0x82
,0x2b,0x00,0x82,0x0f,0x00,0xa2,0x6f,0x00,0x00,0x01,0x00,0x00,0x06,0x00,0x00,0x22
,0x00,0x20,0x00,0x00,0x00,0x19,0x02,0x00,0x10,0x02,0x00,0x19,0x00,0x10,0x00,0x00

};



static unsigned char trowptr[] = {

     0,     9,    13,     0,     1,    30,    26,     5,    34,     2,    42,
    30,    43,     7,    42,    43,    47,     0,    46,    30,    65,    83,
   102,     0,    30,   116,    30,    63,    63,   135,     0,     0,    95,
    12,    30,    65,    52,    12,    26,     5,    63,     5,   154,    54,
    80,   156,     1,    82,    84 
};



static unsigned short ttab [] =  {

 0x2000,0x8000,0x0000,0x2009,0x1021,0x102f,0x4030,0x1001,0x2016,0x400b,0x400c
,0x400d,0x2014,0x4011,0x2016,0x2009,0x203a,0x100a,0x2014,0x2016,0x2016,0x401e
,0x2009,0x2014,0x2014,0x2009,0x4026,0x2009,0x203a,0x2032,0x2016,0x2014,0x4039
,0x203b,0x2014,0x203a,0x2014,0x1027,0x203a,0x4021,0x1005,0x2032,0x2038,0x2018
,0x4025,0x203b,0x100d,0x202e,0x1007,0x2005,0x202f,0x2032,0x203b,0x4034,0x4035
,0x203b,0x2038,0x2018,0x4031,0x2005,0x403e,0x1012,0x400c,0x400d,0x201a,0x201a
,0x201a,0x201a,0x100b,0x2026,0x2026,0x201a,0x201a,0x201a,0x201a,0x201a,0x201a
,0x201a,0x2036,0x201a,0x201a,0x201a,0x201a,0x201a,0x200f,0x200f,0x403c,0x1030
,0x1029,0x200f,0x4008,0x101e,0x4021,0x200f,0x200f,0x101c,0x200f,0x4025,0x0000
,0x4023,0x4024,0x101b,0x200f,0x4003,0x4004,0x400c,0x400d,0x0000,0x202b,0x0000
,0x0000,0x0000,0x202b,0x202b,0x4027,0x202b,0x0000,0x201a,0x201a,0x0000,0x0000
,0x202b,0x201a,0x0000,0x201a,0x201a,0x201a,0x201a,0x201a,0x201a,0x201a,0x0000
,0x201a,0x201a,0x201a,0x201a,0x201c,0x201c,0x0000,0x0000,0x0000,0x201c,0x0000
,0x201c,0x201c,0x201c,0x201c,0x201c,0x201c,0x201c,0x0000,0x201c,0x201c,0x201c
,0x201c,0x4029,0x402a,0x203d,0x0000,0x2007,0x0000,0x0000,0x0000,0x4021,0x0000
,0x4021,0x0000,0x0000,0x4025,0x203d,0x4025,0x2007,0x0000,0x0000,0x0000,0x0000
,0x0000,0x0000,0x2007,0x203d,0x0000,0x2007,0x0000,0x2007
};



/* macro for accessing the nonterminal-table */
/* the Row Displacement Scheme is performed for the nonterminal-table */

#define GET_NTABENTRY(RorS, Act, State, lhsnt) \
	{\
	  register      U_SHORT j;\
	  j = ntab[ nrowptr[State] + lhsnt ]; \
	  Act = j & ACTIONMASK; \
	  RorS = j & OPERANDMASK; \
	}

static unsigned char nrowptr[] = {

     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     3,    10,    12,     0,     0,     1,     0,    32,
     0,     0,    35,     8,    38,    58,    59,     0,     0,     0,     0,
     7,     4,    69,     0,    17,     0,     3,     0,    72,    58,     0,
     0,    47,     0,     0,     0 
};



static unsigned short ntab [] =  {

 0x6004,0x902d,0x6016,0x6019,0x9002,0x6028,0x9033,0x900a,0x602d,0x9006,0x602c
,0x6002,0x9001,0x6018,0x0000,0x900e,0x6015,0x0000,0x6017,0x0000,0x6009,0x6008
,0x9013,0x602a,0x6015,0x6010,0x602a,0x0000,0x600e,0x9028,0x600c,0x9020,0x903f
,0x600f,0x9040,0x6010,0x6003,0x6006,0x9019,0x6025,0x6014,0x901f,0x6022,0x6023
,0x901b,0x902c,0x601d,0x6013,0x9022,0x9010,0x6011,0x9012,0x6026,0x0000,0x0000
,0x0000,0x9015,0x602e,0x0000,0x901d,0x6016,0x6016,0x9002,0x9002,0x9041,0x601a
,0x9042,0x903f,0x602b,0x9040,0x903f,0x6016,0x9040,0x9002,0x6015,0x6015,0x6020
,0x601f,0x9037,0x903f,0x0000,0x9040,0x9017,0x0000,0x0000,0x6015,0x0000,0x6024
,0x0000,0x0000,0x903f,0x0000,0x9040,0x0000,0x0000,0x602a
};





#endif

static	char *state2terms[] = {
	(char *)NULL,	/* state 1 */
	(char *)NULL,	/* state 2 */
	"\"$STOP\", \"$BRACKET\", \"$GRAMMAR\", \"$SEPA\" or \"$SKIP\"",	/* state 3 */
	"\"EOF\"",	/* state 4 */
	"\"EOF\"",	/* state 5 */
	(char *)NULL,	/* state 6 */
	"\"$SEPA\", \"$BRACKET\", \"$GRAMMAR\" or \"$SKIP\"",	/* state 7 */
	"\"$BRACKET\", \"STRING\", \"NAME\", \"$GRAMMAR\" or \"$SKIP\"",	/* state 8 */
	"\"$BRACKET\", \"$GRAMMAR\" or \"$SKIP\"",	/* state 9 */
	"\"$GRAMMAR\"",	/* state 10 */
	"\"=\", \"<$START_SYMBOL>\", \"EOF\" or \"NAME\"",	/* state 11 */
	"\":\" or \"::=\"",	/* state 12 */
	"\"EOF\" or \"NAME\"",	/* state 13 */
	"\"NAME\"",	/* state 14 */
	"\"<$START_SYMBOL>\", \"EOF\" or \"NAME\"",	/* state 15 */
	"\"EOF\" or \"NAME\"",	/* state 16 */
	"\"NAME\" or \"EOF\"",	/* state 17 */
	"\"=\"",	/* state 18 */
	"\"::=\", \":\" or \"=\"",	/* state 19 */
	"\":\" or \"::=\"",	/* state 20 */
	(char *)NULL,	/* state 21 */
	(char *)NULL,	/* state 22 */
	(char *)NULL,	/* state 23 */
	"\".\", \"//\" or \"||\"",	/* state 24 */
	"\"NAME\" or \"STRING\"",	/* state 25 */
	(char *)NULL,	/* state 26 */
	"\"NAME\" or \"STRING\"",	/* state 27 */
	(char *)NULL,	/* state 28 */
	(char *)NULL,	/* state 29 */
	(char *)NULL,	/* state 30 */
	"\"STRING\"",	/* state 31 */
	"\")\", \"//\" or \"||\"",	/* state 32 */
	"\"]\", \"//\" or \"||\"",	/* state 33 */
	"\"NAME\"",	/* state 34 */
	"\":\" or \"::=\"",	/* state 35 */
	(char *)NULL,	/* state 36 */
	"\".\", \"//\" or \"||\"",	/* state 37 */
	"\"NAME\"",	/* state 38 */
	"\".\"",	/* state 39 */
	"\"STRING\", \"NAME\", \"$GRAMMAR\" or \"$SKIP\"",	/* state 40 */
	"\"$SKIP\" or \"$GRAMMAR\"",	/* state 41 */
	"\"STRING\", \"NAME\" or \"$GRAMMAR\"",	/* state 42 */
	"\"NAME\", \"STRING\", \"$BRACKET\", \"$GRAMMAR\" or \"$SKIP\"",	/* state 43 */
	"\".\"",	/* state 44 */
	"\".\"",	/* state 45 */
	(char *)NULL,	/* state 46 */
	"\"=\"",	/* state 47 */
	"\"CARDINAL\"",	/* state 48 */
	"\".\"",	/* state 49 */
	(char *)NULL
}; /* of array state2terms[] */
