
#include "args.h"

#include "ComputationRepr.h"

extern PExpr wrongExpr;

extern PExpr copyExpr FEARGS ((PExpr ex));

extern PExpr newCall FEARGS ((int name, PExprList params, CoordPtr coord));
extern PExpr newExprList FEARGS ((PExprList subList, CoordPtr coord));
extern PExpr newName FEARGS ((int name, CoordPtr coord));
extern PExpr newIntValue FEARGS ((int val, CoordPtr coord));
extern PExpr newStrValue FEARGS ((int val, CoordPtr coord));
extern PExpr newChrValue FEARGS ((int val, CoordPtr coord));
extern PExpr newFltValue FEARGS ((int val, CoordPtr coord));
extern PExpr newAttrAccRule 
   FEARGS ((ProdSymbol prodSymb, DefTableKey attrKey, int isChain, CoordPtr coord));
extern PExpr newRuleAttrAcc FEARGS ((DefTableKey attrKey, CoordPtr coord));
extern PExpr newAttrAccSymb
   FEARGS ((DefTableKey symbKey, DefTableKey attrKey, int isChain, CoordPtr coord));
extern PExpr newIncluding FEARGS ((DefTableKey inclKey, CoordPtr coord));
extern PExpr newConstituent FEARGS ((DefTableKey constKey, int subtree, CoordPtr coord));
extern PExpr newConstituents FEARGS ((DefTableKey constKey, int subtree, CoordPtr coord));
extern PExpr newSymbTermAcc FEARGS ((int index, CoordPtr coord));
extern PExpr newRuleTermAcc FEARGS ((int symbNo, DefTableKey termKey, CoordPtr coord));
extern PExpr newRHS FEARGS ((int attrIdn, CoordPtr coord));
extern PExpr newHeadAcc FEARGS ((DefTableKey chnKey, CoordPtr coord));
extern PExpr newTailAcc FEARGS ((DefTableKey chnKey, CoordPtr coord));
extern PExpr newLoop 
  FEARGS ((PExpr cond, PExpr attr, PExpr iter, CoordPtr coord));
extern PExpr newDepend FEARGS ((PExpr ex, PExprList deps, CoordPtr coord));
extern PExpr newAssign FEARGS ((PExpr left, PExpr right, CoordPtr coord));
