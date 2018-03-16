
/* encoding of tree node types and symbols */

#ifndef NODECODE_H
#define NODECODE_H

extern int LHSMAP[];

#define IsSymb(_n,_c) (LHSMAP[(_n)->_prod] == (_c))

#define SYMBBackendOpt 0
#define SYMBNamesList 1
#define SYMBAttrNames 2
#define SYMBAttrList 3
#define SYMBAttrType 4
#define SYMBOptimOpt 5
#define SYMBAttrSpec 6
#define SYMBArrangeType 7
#define SYMBOrderOpt 8
#define SYMBExpandOpt 9
#define SYMBBackendOpts 10
#define SYMBOptimOpts 11
#define SYMBOrderOpts 12
#define SYMBExpandOpts 13
#define SYMBIdentList 14
#define SYMBOption 15
#define SYMBOptions 16
#define SYMBStart 17
#define RULESTART 0
#define RULEOPTIONS1 1
#define RULEOPTIONS2 2
#define RULEOPTEXP 3
#define RULEOPTORD 4
#define RULEOPTOPT 5
#define RULEOPTBACK 6
#define RULEIDENTS1 7
#define RULEIDENTS2 8
#define RULEEXPANDS1 9
#define RULEEXPANDS2 10
#define RULEORDERS1 11
#define RULEORDERS2 12
#define RULEOPTIMS1 13
#define RULEOPTIMS2 14
#define RULEBACKS1 15
#define RULEBACKS2 16
#define RULEEXPAND1 17
#define RULEEXPAND3 18
#define RULEEXPAND2 19
#define RULEORDER1 20
#define RULEORDER2 21
#define RULEORDER3 22
#define RULEORDER4 23
#define RULEARRANGE1 24
#define RULEARRANGE4 25
#define RULEARRANGE2 26
#define RULEARRANGE3 27
#define RULEATTR1 28
#define RULEOPTIM1 29
#define RULEOPTIM2 30
#define RULEOPTIM3 31
#define RULEATTRTYPE1 32
#define RULEATTRTYPE2 33
#define RULEATTRS1 34
#define RULEATTRS2 35
#define RULEATTRNAMES 36
#define RULENAMESL1 37
#define RULENAMESL2 38
#define RULEBACKEND1 39
#define RULEBACKEND2 40
#endif
