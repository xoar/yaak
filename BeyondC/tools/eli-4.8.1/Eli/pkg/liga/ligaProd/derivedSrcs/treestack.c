static char RCSid[] = "$Id: treestack.c,v 1.9 2012/04/10 22:16:09 profw Exp $";
/* Tree construction module
   Copyright 1997, The Regents of the University of Colorado */

/* This file is part of the Eli Module Library.

The Eli Module Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The Eli Module Library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the Eli Module Library; see the file COPYING.LIB.
If not, write to the Free Software Foundation, Inc., 59 Temple Place -
Suite 330, Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Eli into the
   directory resulting from a :source derivation, you may use that
   created file as a part of that directory without restriction. */

#include <stdlib.h>
#include "err.h"
#include "treestack.h"

int _nodestacksize = 0;
int _nsp = 0;
NODEPTR *_nst = 0;
#ifdef _COORDSTACK
POSITION *_pst = NoPosition;

POSITION SpanOf(POSITION left, POSITION right)
{ POSITION span;

  LineOf(span) = LineOf(left); ColOf(span) = ColOf(left);
#ifdef RIGHTCOORD
  RLineOf(span) = LineOf(right); RColOf(span) = RColOf(right);
#ifdef MONITOR
  CumColOf(span) = ColOf(span); RCumColOf(span) = RColOf(span);
#endif
#endif
  return span;
}
#endif

void _incrnodestack ()
{
  _nsp++;
  if (_nsp >= _nodestacksize) {
    _nodestacksize += _MAXNODESTACK;
    _nst = _nst ? (NODEPTR *)realloc(_nst, _nodestacksize * sizeof(NODEPTR))
                : (NODEPTR *)malloc(_nodestacksize * sizeof(NODEPTR));
    if (!_nst)
      message(DEADLY, "out of memory for node stack\n", 0, &curpos);
#ifdef _COORDSTACK
    _pst = _pst ? (POSITION *)realloc(_pst, _nodestacksize * sizeof(POSITION))
                : (POSITION *)malloc(_nodestacksize * sizeof(POSITION));
    if (!_pst)
      message(DEADLY, "out of memory for coordinate stack\n", 0, &curpos);
#endif
  }
}

void FreeNodestack()
{
  _nsp = 0;
  _nodestacksize = 0;
  if (_nst) free(_nst);
  _nst = 0;
#ifdef _COORDSTACK
  if (_pst) free(_pst);
  _pst = 0;
#endif
}
