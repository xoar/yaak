
#ifndef REMOTE_H
#define REMOTE_H

#include "DefTableKeyList.h"
#include "SymbAttrList.h"
#include "err.h"

extern DefTableKeyList IncludingKeys;
extern DefTableKeyList ConstituentKeys;
extern DefTableKeyList ConstituentsKeys;

extern DefTableKey EnterIncluding 
   FEARGS ((SymbAttrList remset, DefTableKey comp, CoordPtr coord));

extern DefTableKey EnterSglConstit
   FEARGS ((SymbAttrList remset, DefTableKeyList shieldset, 
            DefTableKey comp, CoordPtr coord));

extern DefTableKey EnterMulConstit
   FEARGS ((SymbAttrList remset, DefTableKeyList shieldset, 
            DefTableKey tp, int fct2, int fct1, int fct0,
            DefTableKey comp, CoordPtr coord));
#endif
