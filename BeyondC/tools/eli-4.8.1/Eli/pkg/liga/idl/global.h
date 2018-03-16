/* $Id: global.h,v 4.1 1997/08/29 08:26:49 peter Exp $ */
/*	global.h :: declarations file for every IDL C process	*/
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
#ifndef GLOBAL_DEF
#define GLOBAL_DEF

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#include <stdlib.h>

/* common fields in nodes and classes */

typedef struct
{	short TypeID;
	unsigned int Touched:1, Shared:1;
} IDLnodeHeader;

typedef struct HgenericHeader { IDLnodeHeader IDLhidden; } *HgenericHeader;

# define NodeType HgenericHeader	/* NodeType is only used internally */

/* accessors for common fields */

/* for classes (plain, empty, and null) */
# define typeof(c) ((!(c).IDLinternal) || ((unsigned long)(c).IDLinternal&1)?\
	((unsigned long)(c).IDLinternal): ((c).IDLclassCommon->IDLhidden.TypeID))

# define ClassTouched(this) ((this).IDLclassCommon->IDLhidden.Touched)
# define ClassShared(this) ((this).IDLclassCommon->IDLhidden.Shared)
# define MarkClassTouched(this) ((this).IDLclassCommon->IDLhidden.Touched=1)
# define MarkClassShared(this) ((this).IDLclassCommon->IDLhidden.Shared=1)
# define UnmarkClassTouched(this) ((this).IDLclassCommon->IDLhidden.Touched=0)
# define UnmarkClassShared(this) ((this).IDLclassCommon->IDLhidden.Shared=0)

/* for nodes */
# define TypeNode(NT) ((NT)->IDLhidden.TypeID)
# define AtNode(NT) (NT)
# define SetNType(NT,typ)
# define SetNPtr(NT,addr) (NT = (HgenericHeader) addr)
# define NodeTouched(ptr) ((ptr)->IDLhidden.Touched)
# define NodeShared(ptr) ((ptr)->IDLhidden.Shared)
# define MarkTouched(ptr) ((ptr)->IDLhidden.Touched=1)
# define MarkShared(ptr) ((ptr)->IDLhidden.Shared=1)
# define UnmarkTouched(ptr) ((ptr)->IDLhidden.Touched=0)
# define UnmarkShared(ptr) ((ptr)->IDLhidden.Shared=0)

/* reader modes */

# define FLAT 1
# define TWOPASS 2

/* Initialization and deletion macros */

# define GetListCell(siz) (GetHeap(siz))
# define GetNode(siz,typ) ((n_type) GetHeap(siz))
# define FreeListCell(cell,siz) (FreeHeap(cell))
# define FreeNode(n,typ) (FreeHeap(n))
typedef void *someptr;
someptr GetHeap();

# define FreeHeap(x) free(x)

typedef struct
{	IDLnodeHeader IDLhidden;
	int attributes;
} *n_type;
n_type N_INIT();

/* basic types */

typedef char *String;
typedef char Boolean;
typedef int Integer;

/* String Macros */
String NewString();
String NewReaderString();
# define FreeString(s) s=NULL
# define StringEqual(s1, s2) (s1 == s2)
char *StringToChar();

/* List management */

extern struct ncell
{	struct ncell *next;
	HgenericHeader value;
} *doList, *doneList;

struct GenList {
struct GenList *next;
someptr value;
};
typedef struct GenList * pGenList;

extern pGenList IDLListReverse(), IDLListConnect(), IDLListInsertAfter(),
	IDLListAddRear(), IDLListAddFront(), IDLListCopy(),
	IDLListRemoveCell(), IDLListRemoveFirstCell(), IDLListRemoveLastCell();
extern someptr IDLListLastElem();
extern someptr IDLListRetrieveFirst();
extern Boolean IDLInList();

/* sets and sequences of basic types */

/* Set => bit array */
# define WordWidth 32	/* vax */
typedef int SETBitArray;	/* excludes array dimensions */
# define inSETBitArray(s,v) (s[v/WordWidth]&1<<v%WordWidth)
# define addSETBitArray(s,v) (s[v/WordWidth]|=1<<v%WordWidth)
# define removeSETBitArray(s,v) (s[v/WordWidth]&=~(1<<v%WordWidth))
# define foreachinSETBitArray(s,t, var,max) \
for ( var = _nextOne(s,-1,max); var > 0; var = _nextOne(s,var,max))

/* Set of Rational and String => binary search tree */
/********************************************************************
******************--this portion not implemented yet ****************
******************--these types are implemented as linked lists *****

# define bstreeType(t,n) typedef struct { int left, right; t value; } n;
bstreeType(float,SetFloat)
bstreeType(double,SetDouble)
bstreeType(String,SetString)

# define IDLMemGeneric(v,s,b,T,S,ord,eq) \
{ register T val; register S *set; val=v; b=FALSE; \
for(set=&(s);!((eq?b=TRUE:0)||(set->left==NULL)); \
set=(ord?set->left:set->right));}

# define NUMEQ set->value==val
# define NUMORD set->value<val
# define STREQ streq(set->value,val)
# define STRORD strcmp(set->value,val)

# define MemFloat(v,s,b) IDLMemGeneric(v,s,b,float,SetFloat,NUMORD,NUMEQ)
# define MemDouble(v,s,b) IDLMemGeneric(v,s,b,double,SetDouble,NUMORD,NUMEQ)
# define MemString(v,s,b) IDLMemGeneric(v,s,b,String,SetString,STRORD,STREQ)

***********************************************************************/

/* Sequence of Basic => linked list */
# define linkedType(t,c,l,tag) \
typedef struct tag { struct tag *next; t value; } c, *l;

/*
linkedType(Boolean,CBoolean,LBoolean,_IDL_Boolean_cell_)
linkedType(int,CInteger,LInteger,_IDL_int_cell_)
linkedType(String,CString,LString,_IDL_string_cell_)
linkedType(float,Cfloat,Lfloat,_IDL_float_cell_)
linkedType(double,Cdouble,Ldouble,_IDL_double_cell_)
*/

extern int _nextOne();




/* array implementation of sets and sequencs */
typedef struct {
    int size; 	/* size of storage for array */
    int length; /* number of elements in array */
    int *array;
} GenArray;
# define IDLNewArray(siz) (int *)(GetHeap(sizeof(int)*siz))
extern Boolean IDLInArray();
extern GenArray IDLArrayTail(), IDLArrayCopy(), IDLArraySort();
extern void IDLArrayOrderedInsert(), IDLArrayAddFront(),
	    IDLArrayAddRear(),
	    IDLArrayRemoveFirstElem(), IDLArrayRemoveElem();
#define foreachinArray(a, t, elem) \
    for (t.length = 0, elem = *((a).array), t.array = (a).array; \
    t.length < (a).length; \
    ++(t.length), elem = *(++(t.array)) )
#define IDLInitializeArray(a,siz)	\
	{if (siz) (a).array = IDLNewArray(siz); (a).size=siz; (a).length=0;}
#define IDLEmptyArray(a)	((a).length == 0)
#define IDLLengthArray(a)	((a).length)
#define IDLArrayRemoveLast(a)	{if ((a).length) --(a).length;}

#define IthInArray(a, i)	((i<=(a).length) ? (a).array[i-1] : (a).array[(a).length-1])
#define IDLArrayRetrieveLast(a)	\
	(((a).length) ? (a).array[(a).length-1] : (a).array[0])
#define IDLArrayRetrieveFirst(a)	(a).array[0]

/* typedefs for alternate representations */
#include <sys/types.h>

#endif /* GLOBAL_DEF */
