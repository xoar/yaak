
/* encoding of tree node types and symbols */

#ifndef NODECODE_H
#define NODECODE_H

extern int LHSMAP[];

#define IsSymb(_n,_c) (LHSMAP[(_n)->_prod] == (_c))

#define SYMBErrorOpt 0
#define SYMBCodeOpt 1
#define SYMBStackOpt 2
#define SYMBMode 3
#define SYMBOnOff 4
#define SYMBDirect 5
#define SYMBTable 6
#define SYMBFrontend 7
#define SYMBOption 8
#define SYMBStart 9
#define RULERoot 0
#define RULEOpt1 1
#define RULEOpt2 2
#define RULEOpt3 3
#define RULEOpt4 4
#define RULEOpt5 5
#define RULEF1 6
#define RULEF2 7
#define RULEF3 8
#define RULET1 9
#define RULET2 10
#define RULET3 11
#define RULEM1 12
#define RULEM2 13
#define RULEM3 14
#define RULEM4 15
#define RULEM5 16
#define RULEM6 17
#define RULEM7 18
#define RULEM8 19
#define RULED1 20
#define RULED2 21
#define RULED3 22
#define RULEDS1 23
#define RULEDS2 24
#define RULEDS3 25
#define RULEDS4 26
#define RULEDS5 27
#define RULEDS6 28
#define RULEDC1 29
#define RULEDC2 30
#define RULEDC3 31
#define RULEDC4 32
#define RULEDC5 33
#define RULEDC6 34
#define RULEDC7 35
#define RULEDC8 36
#define RULEDC9 37
#define RULEDC10 38
#define RULEDC11 39
#define RULEDE1 40
#define RULEDE2 41
#define RULEDE3 42
#define RULESW1 43
#define RULESW2 44
#endif
