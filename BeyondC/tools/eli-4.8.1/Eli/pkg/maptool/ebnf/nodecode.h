
/* encoding of tree node types and symbols */

#ifndef NODECODE_H
#define NODECODE_H

extern int LHSMAP[];

#define IsSymb(_n,_c) (LHSMAP[(_n)->_prod] == (_c))

#define SYMBLST_EBNF 0
#define SYMBAtomic 1
#define SYMBSymbol 2
#define SYMBExpression 3
#define SYMBRule 4
#define SYMBEBNF 5
#define RULErule_16 0
#define RULErule_15 1
#define RULErule_14 2
#define RULErule_13 3
#define RULErule_12 4
#define RULErule_11 5
#define RULErule_10 6
#define RULErule_9 7
#define RULErule_8 8
#define RULErule_7 9
#define RULErule_6 10
#define RULErule_5 11
#define RULErule_4 12
#define RULErule_3 13
#define RULErule_2 14
#define RULErule_1 15
#define RULELST_0rule_16 16
#define RULELST_Rulerule_16 17
#endif
