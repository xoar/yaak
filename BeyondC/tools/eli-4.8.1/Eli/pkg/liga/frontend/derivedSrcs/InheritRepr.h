
#include "args.h"

#include "ComputationRepr.h"
extern DefTableKey CreateBUAssignAttr 
  FEARGS ((DefTableKey context, DefTableKey attr, CoordPtr coord));

extern PExpr TurnPlainBUIntoAssign
  FEARGS ((DefTableKey context, DefTableKey attr, PExpr plain, CoordPtr coord));

extern void InheritRepr ();
