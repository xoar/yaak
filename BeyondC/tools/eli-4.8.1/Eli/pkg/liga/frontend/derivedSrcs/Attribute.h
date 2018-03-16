
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "DefTableKeyList.h"
#include "envmod.h"
#include "err.h"
#include "args.h"

#define NoClass   0
#define SYNTClass 1
#define INHClass  2

extern Binding SetCoordSymToBinding FEARGS ((Binding b, CoordPtr c, int sym));

extern void BindDefAttrs 
  FEARGS ((int attrid, 
           DefTableKeyList symkeys, 
           Environment chainscope,
           int attrclass,
           DefTableKey attrtype,
           CoordPtr coord));

extern void SetChkAttrClass
  FEARGS ((DefTableKey attr, int attrid, int attrclass, CoordPtr coord));

extern void SetChkAttrType
  FEARGS ((DefTableKey attr, int attrid, 
           DefTableKey attrtype, CoordPtr coord));

extern void InheritAttributes
  FEARGS ((Environment globenv, Environment attrenv));

#endif
