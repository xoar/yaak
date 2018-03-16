/*
Copyright (C) 1991 Geoffrey M. Clemm

This file is part of the Odin system.

The Odin system is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation (see the file COPYING).

The Odin system is distributed WITHOUT ANY WARRANTY, without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

geoff@boulder.colorado.edu
*/

#include "inc/GMC.h"

typedef struct {
   tp_Nod Node;
   int Offset;
   }		tps_Dummy;

#define		MAX_DummyStack 100
tps_Dummy	DummyStack [MAX_DummyStack];
int		num_DummyStack = 0;

boolean
Empty_DummyStack()
{
   return (num_DummyStack == 0);
   }/*Empty_DummyStack*/


void
Push_DummyStack(Node, Offset)
   tp_Nod Node;
   int Offset;
{
   if (Node == ERROR) FATALERROR("illegal arg to Push_DummyStack");
   if (num_DummyStack == MAX_DummyStack) FATALERROR("DummyStack overflow");
   DummyStack[num_DummyStack].Node = Node;
   DummyStack[num_DummyStack].Offset = Offset;
   num_DummyStack += 1;
   }/*Push_DummyStack*/


void
Pop_DummyStack(NodePtr, OffsetPtr)
   tp_Nod *NodePtr;
   int *OffsetPtr;
{
   if (num_DummyStack == 0) FATALERROR("DummyStack underflow");
   num_DummyStack -= 1;
   *NodePtr = DummyStack[num_DummyStack].Node;
   *OffsetPtr = DummyStack[num_DummyStack].Offset;
   }/*Pop_DummyStack*/


