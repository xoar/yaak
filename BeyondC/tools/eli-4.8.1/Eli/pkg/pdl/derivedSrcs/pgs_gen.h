/* Date should go here */
#define    ZEMAXTERMINALCODE 16
#define    ZEMAXRSLAENGE     6
#define    ZEANZZST          35
#define    ZEMAXTEINTRAG     117
#define    ZEMAXNTEINTRAG    55
#define    ZEMAXTE1          35
#define    ZEMAXTE2          76
#define    ZEMAXNTE          35
#define    ZEANZNT           24
#define    ZEANZPROD         41
#define    ZEMAXTNEXT        47
#define    ZEMAXTCHECK       57
#define    ZEMAXNTNEXT       40
#define    ZETINDEX          ZEMAXTERMINALCODE / M_BITS
#define    ZESTOPSYMBOL      1
static  K_TYP1    TBase[ ZEANZZST + 1]  =
{   0,     0,    14,    16,     0,    26,     2,     5,     0,    25,
   28,     0,     0,    28,    33,     0,     6,    31,    26,    17,
   34,    16,     0,    31,    37,     0,    21,    33,    23,    36,
   40,    41,    21,     0,    38,    40 };

static  K_TYP1    TNext[ ZEMAXTNEXT + 1]  =
{   0,   101,    97,   112,    97,    10,    29,   112,   102,   103,
  104,   107,    11,    97,    97,   102,    57,    12,     7,    26,
   24,    22,   109,    27,    34,    62,    30,    99,    75,     8,
    9,    15,    61,    64,   106,    59,    67,    23,    25,    73,
   70,    18,    72,    74,    69,    33,    35,    76 };

static  K_TYP1    TCheck[ ZEMAXTCHECK + 1]  =
{   0,     4,     1,    33,     1,     6,    33,    33,     7,     7,
    7,    16,     6,     1,     1,     7,     2,     7,     2,    21,
   19,    16,    19,    21,    32,    26,    28,     2,    32,     3,
    5,     9,    10,    13,    14,    26,    17,    18,    20,    28,
   23,    24,    27,    29,    30,    31,    34,    35,     0,     0,
    0,     0,     0,     0,     0,     0,     0,     0 };

static  K_TYP1    TZDefault[ ZEANZZST + 1]  =
{   0,     0,    26,     0,     0,     0,     0,     0,    26,     0,
    0,    26,    24,     0,    26,    26,     0,     0,     0,     0,
    0,     0,    30,     0,     0,    33,     0,     0,     0,    26,
    0,    33,     0,     0,    26,     0 };



static  K_TYP1    NtBase[ ZEANZZST + 1]  =
{   0,     0,     0,     0,     0,     0,     0,     2,     4,     0,
   11,    19,     0,     0,     5,    12,     0,     0,     0,     0,
    0,     0,    11,     0,     7,    24,    16,     0,     0,     2,
   20,    27,     0,    28,    18,     0 };

static  K_TYP1    NtNext[ ZEMAXNTNEXT + 1]  =
{   0,     1,     4,    36,    37,     2,    38,    39,    19,    43,
   41,    45,    13,     5,    32,    31,    48,     5,     5,    14,
    6,    51,    40,    44,     3,    20,    21,    47,    28,    20,
   46,    31,    16,    42,    50,    49,    52,    55,    53,    54,
   17 };

static  K_TYP1    LS[ ZEANZPROD + 1 ]  =
{   0,     5,     3,     5,     5,    20,    15,    20,     8,    10,
   15,    14,    17,     8,    18,    14,    12,    17,    19,    19,
   12,     5,     3,    24,    13,     1,    22,    13,    10,     4,
    2,    21,     7,    23,    16,     9,    11,     6,    21,    11,
   11,    11 };

static  K_TYP1    LaengeRS[ ZEANZPROD + 1 ]  =
{   0,     2,     1,     2,     2,     1,     1,     3,     1,     2,
    2,     1,     1,     3,     3,     3,     1,     3,     2,     3,
    3,     0,     1,     1,     1,     1,     1,     1,     0,     3,
    3,     1,     4,     1,     1,     3,     0,     6,     4,     2,
    3,     5 };

static  K_TYP1    FSymbol[ ZEANZZST + 1 ]  =
{   0,     2,    13,    13,     1,     4,    10,     5,    14,     6,
    4,    14,     4,     5,     1,    14,     5,     5,    11,     5,
    4,     7,     4,     9,     4,     3,    14,     9,    16,     7,
    4,     3,     7,     3,    14,     7 };

static  K_TYP1    RSymbol[ ZEANZZST + 1 ]  =
{   0,     2,    13,    13,     1,     4,    10,     5,    14,     6,
    4,    14,     4,     5,     1,    14,     5,     5,    11,     5,
    4,     7,     4,     9,     4,     3,    14,     9,    16,     7,
    4,     3,     7,     3,    14,     7 };

static  M_TYP    SemKlammer[ ZETINDEX + 1 ]  =
{0X2   ,  0X0    };

static  M_TYP    Ueberlesen[ ZETINDEX + 1 ]  =
{0X0   ,  0X0    };

