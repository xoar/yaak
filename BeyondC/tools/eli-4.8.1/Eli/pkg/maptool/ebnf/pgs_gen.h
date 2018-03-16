/* Date should go here */
#define    ZEMAXTERMINALCODE 16
#define    ZEMAXRSLAENGE     4
#define    ZEANZZST          24
#define    ZEMAXTEINTRAG     64
#define    ZEMAXNTEINTRAG    33
#define    ZEMAXTE1          24
#define    ZEMAXTE2          44
#define    ZEMAXNTE          24
#define    ZEANZNT           11
#define    ZEANZPROD         20
#define    ZEMAXTNEXT        77
#define    ZEMAXTCHECK       83
#define    ZEMAXNTNEXT       45
#define    ZETINDEX          ZEMAXTERMINALCODE / M_BITS
#define    ZESTOPSYMBOL      1
static  K_TYP1    TBase[ ZEANZZST + 1]  =
{   0,    64,    67,     0,     0,    16,    12,    27,     0,     0,
    0,     0,    54,    58,    41,    32,    46,    43,    53,    55,
   31,    51,     0,    45,    45 };

static  K_TYP1    TNext[ ZEMAXTNEXT + 1]  =
{   0,    56,    51,    40,    41,    51,    51,    51,    51,    51,
   51,     5,    51,    51,    51,    51,    51,    57,     6,    57,
    7,    57,     6,     0,     7,     8,     9,    10,    57,     8,
    9,    10,    57,     6,    21,     7,    57,    20,    57,    43,
    8,     9,    10,    57,    40,    41,    40,    41,    40,    41,
   52,    20,    52,    43,    52,    21,    21,    52,    20,    20,
   20,    38,    44,    20,    44,    54,    42,    39,    55,     0,
   42,     0,     0,     0,    54,     0,     0,     4 };

static  K_TYP1    TCheck[ ZEMAXTCHECK + 1]  =
{   0,     3,    22,    11,    11,    22,    22,    22,    22,    22,
   22,     4,    22,    22,    22,    22,    22,     6,     6,     6,
    6,     5,     5,     0,     5,     6,     6,     6,     5,     5,
    5,     5,     7,     7,    15,     7,     7,    15,    20,    15,
    7,     7,     7,    20,    14,    14,    17,    17,    23,    23,
   24,    16,    24,    16,    24,    18,    12,    24,    18,    12,
   19,    21,    18,    13,    19,     1,    12,    21,     2,     0,
   13,     0,     0,     0,     1,     0,     0,     2,     0,     0,
    0,     0,     0,     0 };

static  K_TYP1    TZDefault[ ZEANZZST + 1]  =
{   0,     0,     0,     0,     0,    21,    21,    21,    21,    21,
   21,    12,     5,     0,    15,     6,     0,    18,     7,     0,
    7,     0,    17,    24,    18 };



static  K_TYP1    NtBase[ ZEANZZST + 1]  =
{   0,    35,    18,     0,     0,     0,     7,    14,    29,    33,
   34,    26,    26,     0,    26,    26,     0,    26,    26,     0,
   21,    35,     0,    26,    26 };

static  K_TYP1    NtNext[ ZEMAXNTNEXT + 1]  =
{   0,     0,     0,    13,    12,    26,    12,    11,    13,    27,
   16,    15,    26,    15,    14,    16,    27,    19,    18,    26,
   18,    17,    19,    27,    32,    24,    26,    24,    23,    25,
   27,    26,    31,    22,    28,    27,     1,     3,    29,    30,
   33,     0,     0,     0,     0,     2 };

static  K_TYP1    LS[ ZEANZPROD + 1 ]  =
{   0,    10,     9,     7,     9,     9,     9,     4,     8,     3,
   10,     2,     1,     3,     5,     5,     6,     6,    11,     7,
    7 };

static  K_TYP1    LaengeRS[ ZEANZPROD + 1 ]  =
{   0,     2,     1,     1,     2,     2,     2,     2,     3,     3,
    0,     1,     1,     0,     1,     1,     2,     2,     4,     3,
    3 };

static  K_TYP1    FSymbol[ ZEANZZST + 1 ]  =
{   0,     1,     1,     1,    11,     5,     5,     5,    16,    16,
   16,    12,    12,    12,     7,     7,     7,     9,     9,     9,
    5,    16,     2,     5,     5 };

static  K_TYP1    RSymbol[ ZEANZZST + 1 ]  =
{   0,     1,     1,     1,    11,     5,     5,     5,    16,    16,
   16,    12,    12,    12,     7,     7,     7,     9,     9,     9,
    5,    16,     2,     5,     5 };

static  M_TYP    SemKlammer[ ZETINDEX + 1 ]  =
{0X2   ,  0X0    };

static  M_TYP    Ueberlesen[ ZETINDEX + 1 ]  =
{0X0   ,  0X0    };

