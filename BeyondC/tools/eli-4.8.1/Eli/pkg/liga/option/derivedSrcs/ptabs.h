#ifndef PTABS_H
#define PTABS_H

/* generated constants */


#define BASE		1

#define PAEOF		1

#define STPROD		41



/* generated tables which are not */
/* changable by optimization      */


static unsigned char conncode[]  =  {

  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,
  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,
  42,  43,  44,  45,  46,  47,  48,  49,  50,   0 
};



static unsigned char lhs [] =  {

      1,     1,     1,     1,     3,     3,     4,     2,     6,     6,     7
,     7,     8,     8,     9,     9,     9,    10,    10,    11,    11,     5
,     5,    12,    12,    12,    13,    13,    14,    14,    14,    14,    16
,    16,    17,    17,    17,    15,    15,    17,     0,    18
};



static unsigned char len [] =  {

      1,     1,     7,     7,     0,     2,     4,     6,     2,     1,     1
,     2,     1,     3,     1,     2,     2,     1,     3,     0,     2,     1
,     2,     3,     2,     1,     1,     3,     3,     3,     3,     3,     0
,     3,     2,     3,     2,     1,     3,     2,     1,     2
};



static unsigned char cont[]  =  {

   1,  21,  21,  21,  21,  25,   1,   1,  28,   6,   4,   6,   6,  25,  28,  10,
   5,   6,   7,   6,   8,   6,   6,   7,   6,  11,   8,   6,  13,  12,  14,   6,
  25,  25,   6,  13,  25,   6,  17,   6,   6,  25,  17,   6,   6,  15,  25,   6,
   6,  25,  11,  25,   6,  12,  12 
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

      0,     1,     1,     1,     1,     2,     3,     0,     4,     5,     6
,     5,     5,     7,     4,     8,     9,     5,    10,     5,    11,     5
,     5,    10,     5,    12,    11,     5,    13,    14,    15,     5,    16
,    16,     5,    17,     7,     5,    18,    16,     5,     7,    18,    19
,     5,    20,     7,    19,     5,    16,    12,    16,     5,    21,    14
};



static unsigned char sigcolind [] =  {

      0,     1,     1,     1,     2,     3,     4,     5,     1,     6,     7
,     8,     9,    10,    11,    12,    13,    14,    14,    15,    16,    15
,    15,    15,    17,    18,    18,    18
};



static unsigned char sigmap[][3] =  {

 0x01,0x80,0x00,0x00,0x00,0x01,0x00,0x00,0x02,0x01,0x00,0x00,0x08,0x00,0x04,0x08
,0x00,0x00,0x02,0x00,0x00,0x00,0x10,0x02,0x40,0x00,0x00,0x04,0x00,0x00,0x10,0x00
,0x00,0x20,0x00,0x00,0x80,0x00,0x00,0x00,0x02,0x00,0x00,0x01,0x00,0x00,0x04,0x00
,0x08,0x10,0x02,0x00,0x12,0x02,0x08,0x20,0x00,0x08,0x40,0x00,0x08,0x08,0x00,0x08
,0x01,0x00
};



static unsigned char trowptr[] = {

     0,     0,     4,     5,     6,     3,     1,     0,     3,     0,     1,
     1,     2,    16,     3,     1,     7,     7,     7,     9,     8,    11,
    12,    12,    27,    23,    27,    27,    23,    25,    24,    33,    34,
    34,    36,    30,    28,    36,    39,    41,    42,    33,    39,    45,
    46,    54,    45,    45,    48,    56,    54,    56,    61,    61,    56 
};



static unsigned short ttab [] =  {

 0x2020,0x8000,0x4000,0x4001,0x1010,0x1020,0x4024,0x4027,0x100b,0x100f,0x1016
,0x1011,0x1012,0x1013,0x1014,0x1015,0x4002,0x1017,0x1018,0x1003,0x102b,0x1002
,0x1001,0x1004,0x1026,0x1022,0x1008,0x1007,0x100a,0x1009,0x100c,0x100e,0x1019
,0x101c,0x101b,0x101d,0x101e,0x101f,0x4007,0x1021,0x2025,0x1023,0x400b,0x1025
,0x1027,0x200a,0x400f,0x4010,0x102a,0x2013,0x4019,0x4018,0x200c,0x4008,0x200a
,0x1028,0x200e,0x2011,0x2013,0x1030,0x102f,0x1032,0x102d,0x102c,0x1034,0x200e
,0x1035,0x4006,0x4009,0x201a,0x0000,0x2004,0x2015,0x0000,0x0000,0x0000,0x0000
,0x0000,0x0000,0x0000,0x2004
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

     0,     0,     0,     0,     0,     0,     0,     1,     3,     0,     0,
     0,     0,     0,     4,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
     1,     0,     0,     0,     2,    13,     0,     0,     0,    15,    14,
     0,     0,     0,    16,     0,     1,     0,    27,     8,    27,     0 
};



static unsigned short ntab [] =  {

 0x6006,0x9022,0x601a,0x9003,0x9017,0x6033,0x6031,0x6024,0x901c,0x6024,0x900d
,0x9023,0x9014,0x6036,0x6005,0x6005,0x9028,0x9021,0x901f,0x9026,0x600d,0x600d
,0x6029,0x901d,0x6029,0x9012,0x602e,0x901e,0x602e,0x901b,0x9005,0x6033,0x9016
};





#endif

static	char *state2terms[] = {
	"\"ORDER\", \"BACKEND\", \"EXPAND\", \"OPTIM\" or \"EOF\"",	/* state 1 */
	"\":\"",	/* state 2 */
	"\":\"",	/* state 3 */
	"\":\"",	/* state 4 */
	"\":\"",	/* state 5 */
	"\";\"",	/* state 6 */
	"\"EOF\"",	/* state 7 */
	"\"ORDER\", \"BACKEND\", \"EXPAND\", \"OPTIM\" or \"EOF\"",	/* state 8 */
	"\"TREE\", \"Identifier\", \"ARRANGE\" or \"GRAPH\"",	/* state 9 */
	"\"Identifier\"",	/* state 10 */
	"\"FOR\", \"AUTOMATICALLY\", \"FAST\" or \"IN\"",	/* state 11 */
	"\"Identifier\"",	/* state 12 */
	"\"Identifier\"",	/* state 13 */
	"\",\" or \";\"",	/* state 14 */
	"\"TREE\", \"Identifier\", \"ARRANGE\" or \"GRAPH\"",	/* state 15 */
	"\"RULE\"",	/* state 16 */
	"\"SYMB\"",	/* state 17 */
	"\"Identifier\"",	/* state 18 */
	"\"EVAL\"",	/* state 19 */
	"\"Identifier\"",	/* state 20 */
	"\"BEFORE\"",	/* state 21 */
	"\"Identifier\"",	/* state 22 */
	"\"Identifier\"",	/* state 23 */
	"\"EVAL\"",	/* state 24 */
	"\"Identifier\"",	/* state 25 */
	"\"[\"",	/* state 26 */
	"\"BEFORE\"",	/* state 27 */
	"\"Identifier\"",	/* state 28 */
	"\"IntNumber\"",	/* state 29 */
	"\"]\"",	/* state 30 */
	"\".\"",	/* state 31 */
	"\"Identifier\"",	/* state 32 */
	"\"Identifier\", \",\" or \";\"",	/* state 33 */
	"\"Identifier\", \",\" or \";\"",	/* state 34 */
	"\"Identifier\"",	/* state 35 */
	"\"IntNumber\", \",\" or \";\"",	/* state 36 */
	"\",\" or \";\"",	/* state 37 */
	"\"Identifier\"",	/* state 38 */
	"\"INCLUDING\" or \"Identifier\"",	/* state 39 */
	"\"Identifier\", \",\" or \";\"",	/* state 40 */
	"\"Identifier\"",	/* state 41 */
	"\",\" or \";\"",	/* state 42 */
	"\"INCLUDING\" or \"Identifier\"",	/* state 43 */
	"\"Identifier\", \"ATTRSPEZ\" or \"GROUPING\"",	/* state 44 */
	"\"Identifier\"",	/* state 45 */
	"\"TREE_NODE\" or \"Identifier\"",	/* state 46 */
	"\",\" or \";\"",	/* state 47 */
	"\"Identifier\", \"ATTRSPEZ\" or \"GROUPING\"",	/* state 48 */
	"\"Identifier\"",	/* state 49 */
	"\"Identifier\", \",\" or \";\"",	/* state 50 */
	"\"[\"",	/* state 51 */
	"\"Identifier\", \",\" or \";\"",	/* state 52 */
	"\"Identifier\"",	/* state 53 */
	"\"Identifier\" or \"]\"",	/* state 54 */
	"\"]\"",	/* state 55 */
	(char *)NULL
}; /* of array state2terms[] */
