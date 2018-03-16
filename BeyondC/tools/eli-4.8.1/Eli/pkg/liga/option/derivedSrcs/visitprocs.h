
#ifndef _VISITPROCS_H
#define _VISITPROCS_H

#include "HEAD.h"
#include "node.h"
#include "treecon.h"

#include "eliproto.h"


extern void LIGA_ATTREVAL ELI_ARG((NODEPTR));
extern void _VS0Empty ELI_ARG((NODEPTR _currn));
extern void _VS1BACKEND2 ELI_ARG((_TPPBACKEND2 _currn,BEOption* _AS0BEEntry));
extern void _VS1BACKEND1 ELI_ARG((_TPPBACKEND1 _currn,BEOption* _AS0BEEntry));
extern void _VS1NAMESL2 ELI_ARG((_TPPNAMESL2 _currn));
extern void _VS1NAMESL1 ELI_ARG((_TPPNAMESL1 _currn));
extern void _VS1ATTRNAMES ELI_ARG((_TPPATTRNAMES _currn,int* _AS0Id,IdList* _AS0Ids));
extern void _VS1ATTRS2 ELI_ARG((_TPPATTRS2 _currn));
extern void _VS1ATTRS1 ELI_ARG((_TPPATTRS1 _currn));
extern void _VS1ATTRTYPE2 ELI_ARG((_TPPATTRTYPE2 _currn));
extern void _VS1ATTRTYPE1 ELI_ARG((_TPPATTRTYPE1 _currn));
extern void _VS1OPTIM3 ELI_ARG((_TPPOPTIM3 _currn,OptOption* _AS0OptEntry));
extern void _VS1OPTIM2 ELI_ARG((_TPPOPTIM2 _currn,OptOption* _AS0OptEntry));
extern void _VS1OPTIM1 ELI_ARG((_TPPOPTIM1 _currn,OptOption* _AS0OptEntry));
extern void _VS1ATTR1 ELI_ARG((_TPPATTR1 _currn,int* _AS0Id1,int* _AS0Id2,int* _AS0IntVal));
extern void _VS1ARRANGE3 ELI_ARG((_TPPARRANGE3 _currn));
extern void _VS1ARRANGE2 ELI_ARG((_TPPARRANGE2 _currn));
extern void _VS1ARRANGE4 ELI_ARG((_TPPARRANGE4 _currn));
extern void _VS1ARRANGE1 ELI_ARG((_TPPARRANGE1 _currn));
extern void _VS1ORDER4 ELI_ARG((_TPPORDER4 _currn,OrdOption* _AS0OrdEntry));
extern void _VS1ORDER3 ELI_ARG((_TPPORDER3 _currn,OrdOption* _AS0OrdEntry));
extern void _VS1ORDER2 ELI_ARG((_TPPORDER2 _currn,OrdOption* _AS0OrdEntry));
extern void _VS1ORDER1 ELI_ARG((_TPPORDER1 _currn,OrdOption* _AS0OrdEntry));
extern void _VS1EXPAND2 ELI_ARG((_TPPEXPAND2 _currn,ExpOption* _AS0ExpEntry));
extern void _VS1EXPAND3 ELI_ARG((_TPPEXPAND3 _currn,ExpOption* _AS0ExpEntry));
extern void _VS1EXPAND1 ELI_ARG((_TPPEXPAND1 _currn,ExpOption* _AS0ExpEntry));
extern void _VS1BACKS2 ELI_ARG((_TPPBACKS2 _currn));
extern void _VS1BACKS1 ELI_ARG((_TPPBACKS1 _currn));
extern void _VS1OPTIMS2 ELI_ARG((_TPPOPTIMS2 _currn));
extern void _VS1OPTIMS1 ELI_ARG((_TPPOPTIMS1 _currn));
extern void _VS1ORDERS2 ELI_ARG((_TPPORDERS2 _currn));
extern void _VS1ORDERS1 ELI_ARG((_TPPORDERS1 _currn));
extern void _VS1EXPANDS2 ELI_ARG((_TPPEXPANDS2 _currn));
extern void _VS1EXPANDS1 ELI_ARG((_TPPEXPANDS1 _currn));
extern void _VS1IDENTS2 ELI_ARG((_TPPIDENTS2 _currn));
extern void _VS1IDENTS1 ELI_ARG((_TPPIDENTS1 _currn));
extern void _VS1OPTBACK ELI_ARG((_TPPOPTBACK _currn,OptCombin* _AS0Opts));
extern void _VS1OPTOPT ELI_ARG((_TPPOPTOPT _currn,OptCombin* _AS0Opts));
extern void _VS1OPTORD ELI_ARG((_TPPOPTORD _currn,OptCombin* _AS0Opts));
extern void _VS1OPTEXP ELI_ARG((_TPPOPTEXP _currn,OptCombin* _AS0Opts));
extern void _VS1OPTIONS2 ELI_ARG((_TPPOPTIONS2 _currn));
extern void _VS1OPTIONS1 ELI_ARG((_TPPOPTIONS1 _currn));
extern void _VS1START ELI_ARG((_TPPSTART _currn));
#endif
