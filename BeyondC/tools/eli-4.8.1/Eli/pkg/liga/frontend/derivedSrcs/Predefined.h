
#include "args.h"
#include "envmod.h"

extern int IsPredefSym FEARGS ((int idn));

extern void MakePredef 
FEARGS ((Environment globenv, 
         Environment attrenv, Environment attrnameenv, Environment symbolenv));
