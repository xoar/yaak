#ifndef PTABS_H
#define PTABS_H

/* generated constants */


#define BASE		1

#define PAEOF		1

#define STPROD		33



/* generated tables which are not */
/* changable by optimization      */


static unsigned char conncode[]  =  {

  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,
  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,
  42,   0 
};



static unsigned char lhs [] =  {

      1,     3,     5,     6,     7,     7,     9,     9,     9,    12,    12
,     4,     4,    13,    13,     2,    10,    10,    10,    11,    15,    16
,     8,     0,    14,    14,    14,    14,    14,    14,    14,    14,    14
,    17
};



static unsigned char len [] =  {

      1,     1,     4,     1,     0,     2,     0,     2,     2,     2,     1
,     0,     2,     0,     1,     3,     1,     1,     1,     3,     1,     1
,     3,     1,     0,     1,     1,     1,     1,     1,     1,     1,     1
,     2
};



static unsigned char cont[]  =  {

   4,   1,   1,  10,   8,   4,   7,   4,   5,  18,   6,   3,   3,   9 
};



static char terminf[]  =  {

0x00,0x00,0x00,0x00,0x00 
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
,    10,    11,    12,    13,    14,    15,    16,    17
};



static unsigned char sigrowind [] =  {

      0,     0,     1,     2,     3,     3,     4,     5,     6,     7,     8
,     8,     9,    10
};



static unsigned char sigcolind [] =  {

      0,     1,     2,     3,     4,     5,     1,     6,     7,     8,     9
,     9,     9,     9,     9,     9,     9,     9
};



static unsigned char sigmap[][2] =  {

 0x09,0x00,0x01,0x00,0x00,0x01,0x6b,0x00,0x22,0x00,0x08,0x00,0xff,0x02,0xef,0x02
,0x24,0x00,0x04,0x00,0xa2,0x00
};



static unsigned char trowptr[] = {

     0,     1,     2,     0,     5,    21,    12,     4,    29,    47,    14,
    12,    13,    12 
};



static unsigned short ttab [] =  {

 0x2004,0x2017,0x8000,0x2004,0x4015,0x2006,0x2006,0x4003,0x2006,0x1004,0x2006
,0x2006,0x2006,0x1007,0x2001,0x4002,0x200b,0x1008,0x4010,0x200b,0x4013,0x2014
,0x1007,0x0000,0x2014,0x0000,0x1008,0x4010,0x1006,0x200d,0x200d,0x200d,0x200d
,0x400e,0x200d,0x200d,0x200d,0x200d,0x0000,0x200d,0x200d,0x200d,0x200d,0x200d
,0x200d,0x200d,0x200d,0x2018,0x2018,0x2018,0x2018,0x0000,0x2018,0x2018,0x2018
,0x2018,0x0000,0x4019,0x401a,0x401b,0x401c,0x401d,0x401e,0x401f,0x4020
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

     0,     0,     0,     0,     0,     0,    12,     0,     0,     4,     0,
    18,     0,    21 
};



static unsigned short ntab [] =  {

 0x6002,0x0000,0x9012,0x600c,0x600b,0x9011,0x600a,0x6001,0x9005,0x6005,0x9007
,0x9008,0x0000,0x6009,0x9012,0x9016,0x6003,0x9011,0x900f,0x900c,0x9000,0x0000
,0x900a,0x9012,0x600d,0x0000,0x9011,0x0000,0x0000,0x0000,0x0000,0x9009
};





#endif

static	char *state2terms[] = {
	"\"EOF\" or \"Identifier\"",	/* state 1 */
	"\"Identifier\" or \"EOF\"",	/* state 2 */
	"\"EOF\"",	/* state 3 */
	"\":\"",	/* state 4 */
	(char *)NULL,	/* state 5 */
	(char *)NULL,	/* state 6 */
	"\"CString\", \"$\" or \"[\"",	/* state 7 */
	"\"Identifier\"",	/* state 8 */
	(char *)NULL,	/* state 9 */
	(char *)NULL,	/* state 10 */
	"\"]\" or \"$\"",	/* state 11 */
	"\"$\" or \"]\"",	/* state 12 */
	"\"]\"",	/* state 13 */
	"\"}\", \"CString\", \"$\" or \"[\"",	/* state 14 */
	(char *)NULL
}; /* of array state2terms[] */
