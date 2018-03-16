
/* encoding of tree node types and symbols */

#ifndef NODECODE_H
#define NODECODE_H

extern int LHSMAP[];

#define IsSymb(_n,_c) (LHSMAP[(_n)->_prod] == (_c))

#define SYMBnonLitDesc 0
#define SYMBG1 1
#define SYMBspec 2
#define SYMBlibrRef 3
#define SYMBoptProcessor 4
#define SYMBoptAuxScanner 5
#define SYMBrest 6
#define RULErule_5 0
#define RULErule_6 1
#define RULErule_7 2
#define RULErule_8 3
#define RULErule_9 4
#define RULErule_10 5
#define RULErule_11 6
#define RULErule_12 7
#define RULErule_4 8
#define RULErule_3 9
#define RULErule_2 10
#define RULErule_1 11
#endif
