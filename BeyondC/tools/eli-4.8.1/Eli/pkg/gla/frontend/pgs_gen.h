/* Date should go here */
#define    ZEMAXTERMINALCODE 16
#define    ZEMAXRSLAENGE     3
#define    ZEANZZST          25
#define    ZEMAXTEINTRAG     89
#define    ZEMAXNTEINTRAG    42
#define    ZEMAXTE1          25
#define    ZEMAXTE2          57
#define    ZEMAXNTE          25
#define    ZEANZNT           17
#define    ZEANZPROD         32
#define    ZEMAXTNEXT        87
#define    ZEMAXTCHECK       87
#define    ZEMAXNTNEXT       31
#define    ZETINDEX          ZEMAXTERMINALCODE / M_BITS
#define    ZESTOPSYMBOL      1
static  K_TYP1    TBase[ ZEANZZST + 1]  =
{   0,    42,    60,     0,     5,     7,     2,     0,     0,    14,
    0,     0,    57,     0,    44,     9,     0,    28,    71,    19,
   37,     0,    46,     0,    41,    20 };

static  K_TYP1    TNext[ ZEMAXTNEXT + 1]  =
{   0,    79,    82,    82,    82,    14,    82,    13,    82,    82,
   82,    82,    19,    82,    82,    82,    83,    83,    83,    48,
   15,    49,    83,    83,    83,    83,    55,    83,    83,    83,
   85,    85,    85,     4,    46,     5,    85,    85,    85,    20,
   24,    85,    85,    85,    75,    75,    75,    50,     9,    56,
   75,    75,    75,    57,     0,    75,    75,    75,    84,    10,
   84,    84,    10,     7,     9,    44,    11,    45,    44,    11,
   45,     0,    86,    84,    23,    21,     0,     0,     0,     0,
    0,     0,     0,     0,     0,     0,     0,    22 };

static  K_TYP1    TCheck[ ZEMAXTCHECK + 1]  =
{   0,     3,     7,     7,     7,     7,     7,     6,     7,     7,
    7,     7,    15,     7,     7,     7,     9,     9,     9,     4,
    9,     5,     9,     9,     9,     9,    19,     9,     9,     9,
   17,    17,    17,    25,    25,    25,    17,    17,    17,    17,
   20,    17,    17,    17,     1,     1,     1,    14,    14,    22,
    1,     1,     1,    24,     0,     1,     1,     1,    12,    12,
   12,    12,     2,     2,     2,    12,    12,    12,     2,     2,
    2,     0,    18,    12,    18,    18,     0,     0,     0,     0,
    0,     0,     0,     0,     0,     0,     0,    18 };

static  K_TYP1    TZDefault[ ZEANZZST + 1]  =
{   0,     0,    25,     0,     0,     0,     0,     0,     9,     0,
   25,    25,     0,    14,     0,     0,    17,     0,     0,     0,
    0,    25,     0,    25,     0,     0 };



static  K_TYP1    NtBase[ ZEANZZST + 1]  =
{   0,     0,     0,     0,     0,     0,     0,     0,     0,     9,
   15,    17,    10,     9,    10,     0,    10,    11,     0,     0,
    0,    20,    12,    22,     0,    23 };

static  K_TYP1    NtNext[ ZEMAXNTNEXT + 1]  =
{   0,     1,     3,    37,    38,    39,     0,    26,     6,     8,
   27,    28,     2,    16,    29,    12,    18,    26,     8,     8,
   33,    34,    17,    30,    32,    31,    35,    36,    40,    25,
   41,    42 };

static  K_TYP1    LS[ ZEANZPROD + 1 ]  =
{   0,    14,    12,    10,    15,     7,    14,    15,    10,    10,
   11,    11,     6,     3,     3,     4,     5,     5,    12,    14,
   14,     8,     1,     8,     8,     9,    13,     6,    16,     2,
   13,    17,    16 };

static  K_TYP1    LaengeRS[ ZEANZPROD + 1 ]  =
{   0,     1,     2,     1,     1,     2,     2,     2,     3,     3,
    3,     3,     2,     1,     1,     2,     2,     3,     0,     1,
    1,     1,     1,     2,     2,     1,     0,     0,     0,     3,
    3,     1,     3 };

static  K_TYP1    FSymbol[ ZEANZZST + 1 ]  =
{   0,     2,    10,     1,    14,    14,     5,     2,     2,     2,
   14,    14,     1,     4,     4,     3,     2,     2,     1,     7,
    3,    14,     3,    14,    12,    14 };

static  K_TYP1    RSymbol[ ZEANZZST + 1 ]  =
{   0,     2,    10,     1,    14,    14,     5,     2,     2,     2,
   14,    14,     1,     4,     4,     3,     2,     2,     1,     7,
    3,    14,     3,    14,    12,    14 };

static  M_TYP    SemKlammer[ ZETINDEX + 1 ]  =
{0X2   ,  0X0    };

static  M_TYP    Ueberlesen[ ZETINDEX + 1 ]  =
{0X0   ,  0X0    };

