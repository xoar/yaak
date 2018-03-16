/* Implementation of DeRemer's and Pennello's digraph algorithm:
 * TOPLAS, Vol.4, No.4, October 1982, section4
 */

/* $Id: digraph.h,v 1.3 1997/08/29 08:38:08 mjung Exp $ */

/* (C) Copyright 1997 University of Paderborn */

/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

typedef	unsigned int	Cardinal;

/* Let X the finite set {0,...,Max-1} and B a set of type BitSet,
 * R a relation on X and F0: X -> 2^B a function. Then Digraph computes
 * the function F(a) = union of all sets {F0(b)| a R* b}
 * see also: Theorem 2.24 in "Parsing Theory" of Sippu and Soisalon-Soininen
 *
 * Input: F0[0...Max-1]	: Array of equal sized sets of type BitSet
 *	  Max	   	: cardinality of X
 * Output: F[0...Max-1] : F0 will be recomputed to F
 */
void	DiGraph(/* Cardinal Max, BitSet *F0 */);


/* Adds the element/edge (a,b) to relation R: AddToRelation() must be
 * used to define the relation R needed for DiGraph(). Before the first
 * call of AddToRelation() function InitRelation() must be called.
 */
void	AddToRelation(/* Cardinal a,b */);


/* Initialization of A relation R on a set {0,...,card-1} */
void    InitRelation(/* Cardinal card */);


/* Frees all internal storage for representation of relation R:
 * should be used if R isn't needed any more.
 */
void    FreeRelation();
