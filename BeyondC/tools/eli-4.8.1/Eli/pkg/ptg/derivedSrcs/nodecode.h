
/* encoding of tree node types and symbols */

#ifndef NODECODE_H
#define NODECODE_H

extern int LHSMAP[];

#define IsSymb(_n,_c) (LHSMAP[(_n)->_prod] == (_c))

#define SYMBG3 0
#define SYMBG2 1
#define SYMBG1 2
#define SYMBG4 3
#define SYMBArgument 4
#define SYMBOptional 5
#define SYMBItem 6
#define SYMBCStringNode 7
#define SYMBPTGSpec 8
#define SYMBPatternName 9
#define SYMBArguments 10
#define SYMBFunctionName 11
#define SYMBFunctionCall 12
#define SYMBPatternBody 13
#define SYMBPatternSpec 14
#define SYMBType 15
#define SYMBIndex 16
#define SYMBInsertion 17
#define RULErule_19 0
#define RULErule_20 1
#define RULErule_31 2
#define RULErule_10 3
#define RULErule_21 4
#define RULErule_22 5
#define RULErule_23 6
#define RULErule_30 7
#define RULErule_32 8
#define RULErule_16 9
#define RULErule_17 10
#define RULErule_18 11
#define RULErule_24 12
#define RULErule_25 13
#define RULErule_26 14
#define RULErule_27 15
#define RULErule_28 16
#define RULErule_29 17
#define RULErule_15 18
#define RULErule_12 19
#define RULErule_9 20
#define RULErule_34 21
#define RULErule_11 22
#define RULErule_7 23
#define RULErule_6 24
#define RULErule_5 25
#define RULErule_4 26
#define RULErule_3 27
#define RULErule_2 28
#define RULErule_1 29
#define RULErule_33 30
#define RULErule_14 31
#define RULErule_13 32
#define RULErule_8 33
#endif
