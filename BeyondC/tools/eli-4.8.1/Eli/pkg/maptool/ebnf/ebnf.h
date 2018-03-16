
#ifndef EBNF_H
#define EBNF_H

#include "PTGNodeList.h"
#include "eliproto.h"

extern PTGNodeList Concatenate ELI_ARG((PTGNodeList,PTGNodeList));
extern PTGNode     Combine ELI_ARG((PTGNode,PTGNode,PTGNodeList));

#endif
