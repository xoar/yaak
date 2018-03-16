
#include "args.h"
#include "envmod.h"
#include "err.h"
#include "ptg_gen.h"

extern void InheritCompute FEARGS ((Environment chainScope));

extern Binding AddCoordToBinding FEARGS ((Binding b, CoordPtr c));
extern Binding AddAttrToBinding FEARGS ((Binding b, DefTableKey a));
extern Binding BindNewPlainComp 
   FEARGS ((Environment compScope, Environment attrScope, CoordPtr c));

extern PTGNode InhCompOutput FEARGS ((DefTableKey comp));
