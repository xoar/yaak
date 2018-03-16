/* $Id: scalarlist.h,v 4.1 1997/08/29 08:26:49 peter Exp $ */
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

#ifndef SCALARLIST_H
#define SCALARLIST_H

Boolean inLfloat();
Lfloat appendfrontLfloat();
Lfloat appendrearLfloat();
Lfloat orderedinsertLfloat();
Lfloat removefirstLfloat();
Lfloat removelastLfloat();
Lfloat removeLfloat();
float retrievefirstLfloat();
float retrievelastLfloat();
float ithinLfloat();


#define SEQfloat Lfloat
#define emptySEQfloat(fseq)	(fseq == NULL)
#define initializeSEQfloat(fseq) fseq=NULL;
#define inSEQfloat(fseq, fval)	inLfloat(fseq, (float)fval)
#define appendfrontSEQfloat(fseq, fval)	fseq=appendfrontLfloat(fseq, (float)fval)
#define appendrearSEQfloat(fseq, fval)	fseq=appendrearLfloat(fseq, (float)fval)
#define orderedinsertSEQfloat(fseq, fval, fcompfn) \
	fseq=orderedinsertLfloat(fseq, (float)fval, fcompfn) 
#define retrievefirstSEQfloat(fseq, fval) fval = (float)retrievefirstLfloat(fseq)
#define retrievelastSEQfloat(fseq, fval) fval = (float)retrievelastLfloat(fseq)
#define ithinSEQfloat(fseq, index, fval) fval = (float)ithinLfloat(fseq, index)
#define removefirstSEQfloat(fseq) fseq=removefirstLfloat(fseq)
#define removelastSEQfloat(fseq) fseq =	removelastLfloat(fseq)
#define removeSEQfloat(fseq, fval) fseq = removeLfloat(fseq, (float)fval)
# define foreachinSEQfloat(floatseq,floatptr,floatvalue) for\
(floatptr=floatseq; \
		floatptr!=NULL&&((floatvalue=floatptr->value)||1); \
floatptr=floatptr->next)



	/* set of float list routines */

#define SETfloat Lfloat
#define emptySETfloat(fset)	(fset == NULL)
#define initializeSETfloat(fset) fset=NULL;
#define inSETfloat(fset, fval)	inLfloat(fset, (float)fval)
#define addSETfloat(fset, fval)		{ if (!inLfloat(fset, (float)fval)) \
		appendfrontLfloat(fset, (float)fval); }
#define removeSETfloat(fset, fval)	removeLfloat(fset, (float)fval)
# define foreachinSETfloat(floatset,floatptr,floatvalue) for\
(floatptr=floatset; \
		floatptr!=NULL&&((floatvalue=floatptr->value)||1); \
floatptr=floatptr->next)


	/* seq of String list routines */
    

# define SEQString LString
# define inSEQString(Stringseq,Stringvalue) inLString(Stringseq,Stringvalue)
#define initializeSEQString(sseq) sseq=NULL;
# define appendfrontSEQString(Stringseq,Stringvalue) Stringseq=\
		(SEQString)IDLListAddFront((pGenList)Stringseq,(int)Stringvalue)
# define appendrearSEQString(Stringseq,Stringvalue) Stringseq=\
		(SEQString)IDLListAddRear((pGenList)Stringseq,(int)Stringvalue)
# define orderedinsertSEQString(Stringseq,Stringvalue,Stringcompfn) Stringseq=\
		(SEQString)IDLListOrderedInsert((pGenList)Stringseq,(int)Stringvalue,Stringcompfn)
# define retrievefirstSEQString(Stringseq, Stringvalue) \
		Stringvalue = (String)IDLListRetrieveFirst(Stringseq)
# define retrievelastSEQString(Stringseq, Stringvalue) \
		Stringvalue = (String)IDLListRetrieveLast(Stringseq)
# define ithinSEQString(Stringseq, index, Stringvalue) \
		Stringvalue = (String)IDLListRetrieveIth(Stringseq, index)
# define removefirstSEQString(Stringseq) Stringseq=\
		(SEQString)IDLListRemoveFirstCell((pGenList)Stringseq)
# define removeSEQString(Stringseq,Stringvalue) Stringseq=\
		removeLString(Stringseq,Stringvalue)
# define removelastSEQString(Stringseq) Stringseq=\
		(SEQString)IDLListRemoveLastCell((pGenList)Stringseq)
# define foreachinSEQString(Stringseq,Stringptr,Stringvalue) for\
(Stringptr=Stringseq; \
		Stringptr!=NULL&&((Stringvalue=Stringptr->value)||1); \
Stringptr=Stringptr->next)
# define emptySEQString(Stringseq) ((Stringseq)==NULL)


	/* set of String list routines */


# define SETString LString
# define inSETString(Stringset,Stringvalue) (inLString(Stringset,Stringvalue))
#define initializeSETString(sset) sset=NULL;
# define addSETString(Stringset,Stringvalue) \
		{ if (!inSETString(Stringset, Stringvalue)) Stringset=\
	     (SETString)IDLListAddFront((pGenList)Stringset,(int)Stringvalue);}
# define removeSETString(Stringset,Stringvalue) Stringset=\
		removeLString(Stringset,Stringvalue)
# define foreachinSETString(Stringset,Stringptr,Stringvalue) for\
(Stringptr=Stringset; \
		Stringptr!=NULL&&((Stringvalue=Stringptr->value)||1); \
Stringptr=Stringptr->next)
# define emptySETString(Stringset) ((Stringset)==NULL)


	/* sequence of Integer list routines */


# define SEQInteger LInteger
# define inSEQInteger(Integerseq,Integervalue) IDLInList((pGenList)Integerseq,(int)Integervalue)
#define initializeSEQInteger(Integerseq) Integerseq=NULL;
# define appendfrontSEQInteger(Integerseq,Integervalue) Integerseq=\
		(SEQInteger)IDLListAddFront((pGenList)Integerseq,(int)Integervalue)
# define appendrearSEQInteger(Integerseq,Integervalue) Integerseq=\
		(SEQInteger)IDLListAddRear((pGenList)Integerseq,(int)Integervalue)
# define orderedinsertSEQInteger(Integerseq,Integervalue,Integercompfn) Integerseq=\
		(SEQInteger)IDLListOrderedInsert((pGenList)Integerseq,(int)Integervalue,Integercompfn)
# define retrievefirstSEQInteger(Integerseq, Integerval) \
		Integerval = (int)IDLListRetrieveFirst(Integerseq)
# define retrievelastSEQInteger(Integerseq, Integerval) \
		Integerval = (int)IDLListRetrieveLast(Integerseq)
# define ithinSEQInteger(Integerseq, index, Integervalue) \
		Integervalue = (int)IDLListRetrieveIth(Integerseq, index)
# define removefirstSEQInteger(Integerseq) Integerseq=\
		(SEQInteger)IDLListRemoveFirstCell((pGenList)Integerseq)
# define removeSEQInteger(Integerseq,Integervalue) Integerseq=\
		(SEQInteger)IDLListRemoveCell((pGenList)Integerseq,(int)Integervalue)
# define removelastSEQInteger(Integerseq) Integerseq=\
		(SEQInteger)IDLListRemoveLastCell((pGenList)Integerseq)
# define foreachinSEQInteger(Integerseq,Integerptr,Integervalue) for\
(Integerptr=Integerseq; \
		Integerptr!=NULL&&((Integervalue=Integerptr->value)||1); \
Integerptr=Integerptr->next)
# define emptySEQInteger(Integerseq) ((Integerseq)==NULL)




	/* sequence of Boolean list routines */


# define SEQBoolean LBoolean
# define inSEQBoolean(Booleanseq,Booleanvalue) IDLInList((pGenList)Booleanseq,(int)Booleanvalue)
#define initializeSEQBoolean(Booleanseq) Booleanseq=NULL;
# define appendfrontSEQBoolean(Booleanseq,Booleanvalue) Booleanseq=\
		(SEQBoolean)IDLListAddFront((pGenList)Booleanseq,(int)Booleanvalue)
# define appendrearSEQBoolean(Booleanseq,Booleanvalue) Booleanseq=\
		(SEQBoolean)IDLListAddRear((pGenList)Booleanseq,(int)Booleanvalue)
# define orderedinsertSEQBoolean(Booleanseq,Booleanvalue,Booleancompfn) Booleanseq=\
		(SEQBoolean)IDLListOrderedInsert((pGenList)Booleanseq,(int)Booleanvalue,Booleancompfn)
# define removefirstSEQBoolean(Booleanseq) Booleanseq=\
		(SEQBoolean)IDLListRemoveFirstCell((pGenList)Booleanseq)
# define removeSEQBoolean(Booleanseq,Booleanvalue) Booleanseq=\
		(SEQBoolean)IDLListRemoveCell((pGenList)Booleanseq,(int)Booleanvalue)
# define removelastSEQBoolean(Booleanseq) Booleanseq=\
		(SEQBoolean)IDLListRemoveLastCell((pGenList)Booleanseq)
# define foreachinSEQBoolean(Booleanseq,Booleanptr,Booleanvalue) for\
(Booleanptr=Booleanseq; \
		Booleanptr!=NULL&&((Booleanvalue=Booleanptr->value)||1); \
Booleanptr=Booleanptr->next)
# define emptySEQBoolean(Booleanseq) ((Booleanseq)==NULL)

#endif
