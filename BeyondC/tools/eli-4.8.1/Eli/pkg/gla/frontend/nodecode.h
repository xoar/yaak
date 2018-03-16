
/* encoding of tree node types and symbols */

#ifndef NODECODE_H
#define NODECODE_H

extern int LHSMAP[];

#define IsSymb(_n,_c) (LHSMAP[(_n)->_prod] == (_c))

#define SYMBoptions 0
#define SYMBoption 1
#define SYMBnonLitDescs 2
#define SYMBencodings 3
#define SYMBEofOption 4
#define SYMBlibrRef 5
#define SYMBoptProcessor 6
#define SYMBoptAuxScanner 7
#define SYMBencoding 8
#define SYMBLitEncoding 9
#define SYMBspec 10
#define SYMBvalue 11
#define SYMBIdUse 12
#define SYMBNonlitEncoding 13
#define SYMBrest 14
#define SYMBIdDef 15
#define SYMBnonLitDesc 16
#define RULErule_19 0
#define RULErule_20 1
#define RULErule_21 2
#define RULErule_22 3
#define RULErule_24 4
#define RULErule_25 5
#define RULErule_18 6
#define RULErule_17 7
#define RULErule_10 8
#define RULErule_9 9
#define RULErule_8 10
#define RULErule_23 11
#define RULErule_26 12
#define RULErule_27 13
#define RULErule_28 14
#define RULErule_29 15
#define RULErule_30 16
#define RULErule_31 17
#define RULErule_32 18
#define RULErule_16 19
#define RULErule_15 20
#define RULErule_14 21
#define RULErule_13 22
#define RULErule_12 23
#define RULErule_11 24
#define RULErule_7 25
#define RULErule_6 26
#define RULErule_5 27
#define RULErule_4 28
#define RULErule_3 29
#define RULErule_2 30
#define RULErule_1 31
#endif
