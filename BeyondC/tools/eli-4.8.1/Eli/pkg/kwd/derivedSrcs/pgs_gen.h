/* Date should go here */
#define    ZEMAXTERMINALCODE 8
#define    ZEMAXRSLAENGE     3
#define    ZEANZZST          13
#define    ZEMAXTEINTRAG     39
#define    ZEMAXNTEINTRAG    19
#define    ZEMAXTE1          13
#define    ZEMAXTE2          26
#define    ZEMAXNTE          13
#define    ZEANZNT           8
#define    ZEANZPROD         13
#define    ZEMAXTNEXT        24
#define    ZEMAXTCHECK       27
#define    ZEMAXNTNEXT       15
#define    ZETINDEX          ZEMAXTERMINALCODE / M_BITS
#define    ZESTOPSYMBOL      1
static  K_TYP1    TBase[ ZEANZZST + 1]  =
{   0,     5,     0,     0,     8,    12,    14,     3,    17,     0,
   16,    15,    19,    16 };

static  K_TYP1    TNext[ ZEMAXTNEXT + 1]  =
{   0,    33,    33,     7,    33,    20,    33,     2,    33,    34,
   34,     4,     8,    35,    34,    36,    34,    37,    37,    11,
   25,    13,    12,    26,    37 };

static  K_TYP1    TCheck[ ZEMAXTCHECK + 1]  =
{   0,     2,     2,     2,     2,     7,     2,     1,     2,     4,
    4,     7,     4,     5,     4,     6,     4,    10,    10,     8,
   11,    12,    10,    13,    10,     0,     0,     0 };

static  K_TYP1    TZDefault[ ZEANZZST + 1]  =
{   0,     7,     0,     4,     0,     1,     0,     0,     0,    10,
    0,     0,     0,     0 };



static  K_TYP1    NtBase[ ZEANZZST + 1]  =
{   0,     0,     0,     5,     6,     3,     0,     5,     0,     6,
    7,     0,     0,     0 };

static  K_TYP1    NtNext[ ZEMAXNTNEXT + 1]  =
{   0,     1,     6,     5,    14,     3,    15,    16,     3,    15,
    3,    17,     9,    10,    18,    19 };

static  K_TYP1    LS[ ZEANZPROD + 1 ]  =
{   0,     3,     4,     3,     4,     6,     6,     5,     7,     2,
    1,     8,     7,     8 };

static  K_TYP1    LaengeRS[ ZEANZPROD + 1 ]  =
{   0,     1,     1,     2,     3,     3,     3,     1,     0,     1,
    1,     0,     3,     3 };

static  K_TYP1    FSymbol[ ZEANZZST + 1 ]  =
{   0,     8,     1,     1,     1,     1,     1,     8,     2,     1,
    1,     5,     2,     7 };

static  K_TYP1    RSymbol[ ZEANZZST + 1 ]  =
{   0,     8,     1,     1,     1,     1,     1,     8,     2,     1,
    1,     5,     2,     7 };

static  M_TYP    SemKlammer[ ZETINDEX + 1 ]  =
{0X2    };

static  M_TYP    Ueberlesen[ ZETINDEX + 1 ]  =
{0X0    };

