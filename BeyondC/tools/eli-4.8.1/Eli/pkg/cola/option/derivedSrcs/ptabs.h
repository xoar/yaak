#ifndef PTABS_H
#define PTABS_H

/* generated constants */


#define BASE		1

#define PAEOF		1

#define STPROD		45



/* generated tables which are not */
/* changable by optimization      */


static unsigned char conncode[]  =  {

  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,
  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,
  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,   0 
};



static unsigned char lhs [] =  {

      1,     1,     1,     1,     1,     1,     1,     1,     1,     1,     1
,     3,     3,     3,     4,     4,     4,     6,     6,     6,     7,     7
,     7,     7,     7,     7,     7,     7,     2,     2,     8,     8,     9
,     9,     8,     5,     5,     5,     5,     5,     5,     0,    10,    10
,    10,    11
};



static unsigned char len [] =  {

      2,     2,     2,     4,     3,     2,     1,     3,     3,     3,     1
,     2,     2,     2,     1,     2,     1,     3,     3,     2,     1,     1
,     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,     0
,     2,     1,     2,     2,     2,     3,     2,     2,     1,     2,     3
,     2,     2
};



static unsigned char cont[]  =  {

   1,  31,  31,  23,  33,  22,  15,  15,  19,   1,   1,  13,  37,  33,  33,  33,
  13,  33,   8,   8,  11,  33,   7,  33,  33,   3,  33,   8,  33,  33,  13,  13,
  33,  13,  33,  33 
};



static char terminf[]  =  {

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 
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
,    21,    22,    23,    24,    25,    26,    27,    28,    29,    30,    31
,    32,    33,    34,    35,    36,    37,    38,    39,    40
};



static unsigned char sigrowind [] =  {

      0,     1,     1,     2,     3,     4,     5,     6,     7,     0,     8
,     9,    10,     3,     3,     3,     9,     3,    11,    11,    12,     3
,    13,     3,     3,    14,     3,    11,     3,     3,     9,     9,     3
,     9,     3,     3
};



static unsigned char sigcolind [] =  {

      0,     1,     2,     1,     1,     1,     3,     4,     5,     1,     6
,     1,     7,     1,     8,     9,     9,     9,    10,    11,     9,    12
,    13,    14,    14,    14,    14,    14,    14,    14,    14,    15,    15
,    16,    16,    16,    17,    16,     9,     9,     9
};



static unsigned char sigmap[][3] =  {

 0x01,0x22,0x00,0x00,0x40,0x00,0x00,0x20,0x00,0x00,0x80,0x00,0x00,0x10,0x00,0x04
,0x0d,0x00,0x26,0x01,0x00,0x20,0x04,0x01,0x01,0x00,0x00,0x80,0x00,0x00,0x00,0x00
,0x02,0x10,0x00,0x00,0x40,0x00,0x00,0x18,0x00,0x00,0x04,0x00,0x00
};



static unsigned char trowptr[] = {

     0,     0,     0,     9,     1,     0,     0,    40,    28,     0,     1,
     0,     1,     1,     1,     1,     1,     1,     0,     1,     0,     1,
    28,     1,     1,     1,     1,     2,     1,     1,    35,    38,     1,
    40,     1,     1 
};



static unsigned short ttab [] =  {

 0x2020,0x8000,0x400e,0x4000,0x0000,0x0000,0x0000,0x101f,0x101e,0x101c,0x101d
,0x0000,0x4027,0x4028,0x4010,0x1007,0x1006,0x1008,0x1021,0x1020,0x1005,0x1022
,0x1004,0x4014,0x4015,0x4016,0x4017,0x4018,0x4019,0x401a,0x401b,0x1023,0x401c
,0x401d,0x101b,0x101a,0x100f,0x1011,0x1002,0x1003,0x1001,0x1019,0x4006,0x1018
,0x1017,0x1016,0x1010,0x4008,0x1015,0x1014,0x4009,0x1013,0x400f,0x1012,0x400a
,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x100e,0x100d,0x100c,0x0000,0x100b
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

     0,     0,     4,     0,     0,     0,     0,     0,     0,     9,     0,
     0,     0,    11,    12,    14,     0,    18,     0,     0,     0,    19,
     0,    20,    21,     0,    22,     0,    23,    24,     0,     0,    25,
     0,    26,    27 
};



static unsigned short ntab [] =  {

 0x600a,0x900b,0x9013,0x901e,0x900c,0x900d,0x901f,0x902c,0x6009,0x9029,0x9022
,0x902a,0x901e,0x9024,0x9023,0x901f,0x9025,0x6009,0x9021,0x9022,0x9026,0x9005
,0x9002,0x9001,0x9004,0x9003,0x9007,0x9011,0x9012,0x902b
};





#endif

static	char *state2terms[] = {
	(char *)NULL,	/* state 1 */
	(char *)NULL,	/* state 2 */
	(char *)NULL,	/* state 3 */
	"\"INFO\"",	/* state 4 */
	"\"ON\" or \"OFF\"",	/* state 5 */
	"\"POS\"",	/* state 6 */
	"\"SWITCH\", \"IF\", \"SIZE\" or \"AUTOMATIC\"",	/* state 7 */
	(char *)NULL,	/* state 8 */
	(char *)NULL,	/* state 9 */
	(char *)NULL,	/* state 10 */
	"\"EOF\"",	/* state 11 */
	"\"integer\"",	/* state 12 */
	"\"PUSH\"",	/* state 13 */
	"\"ON\" or \"OFF\"",	/* state 14 */
	"\"ON\" or \"OFF\"",	/* state 15 */
	"\"ON\" or \"OFF\"",	/* state 16 */
	"\"integer\"",	/* state 17 */
	"\"ON\" or \"OFF\"",	/* state 18 */
	"\"ROWS\"",	/* state 19 */
	"\"ROWS\"",	/* state 20 */
	"\"REDUCE\"",	/* state 21 */
	"\"ON\" or \"OFF\"",	/* state 22 */
	"\"NT\" or \"ROWS\"",	/* state 23 */
	"\"ON\" or \"OFF\"",	/* state 24 */
	"\"ON\" or \"OFF\"",	/* state 25 */
	"\"IF\"",	/* state 26 */
	"\"ON\" or \"OFF\"",	/* state 27 */
	"\"ROWS\"",	/* state 28 */
	"\"ON\" or \"OFF\"",	/* state 29 */
	"\"ON\" or \"OFF\"",	/* state 30 */
	"\"integer\"",	/* state 31 */
	"\"integer\"",	/* state 32 */
	"\"ON\" or \"OFF\"",	/* state 33 */
	"\"integer\"",	/* state 34 */
	"\"ON\" or \"OFF\"",	/* state 35 */
	"\"ON\" or \"OFF\"",	/* state 36 */
	(char *)NULL
}; /* of array state2terms[] */
