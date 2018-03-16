static char rcsid[] = "$Id: oiladt2c.c,v 1.15 1998/02/22 23:32:58 waite Exp $";
/* Special cases of Oil functions
   Copyright, 1989, The Regents of the University of Colorado */

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

#include "tOilTypeSetList.h"


/*****************************************************
  These are buffers for the usual ops
  */
#ifdef WithIDs
#define InitID 0,0,
#else
#define InitID 
#endif

static struct _VoidPtrLE SetArg3={ (VoidPtr)0, (VoidPtrList)0 };
static struct _VoidPtrLE SetArg2={ (VoidPtr)0, &SetArg3 };
static struct _VoidPtrLE SetArg1={ (VoidPtr)0, &SetArg2 };


/*****************************************************
  OilIdResultTS<n> - allow for convient use of general routines
      Identify the possible result types of an applied occurance of 'id'
      using sets of types to describe the operands.
  */

tOilTypeSet
#ifdef PROTO_OK
OilIdResultTS1(tOilOp id, tOilTypeSet as1 )
#else
OilIdResultTS1( id, as1 ) tOilOp id; tOilTypeSet as1;
#endif
  {
      SetArg3.head= (VoidPtr)as1;
      return ( OilIdResultSet( id, &SetArg3 ));
  }

tOilTypeSet
#ifdef PROTO_OK
OilIdResultTS2(tOilOp id, tOilTypeSet as1, tOilTypeSet as2 )
#else
OilIdResultTS2( id, as1, as2 ) tOilOp id; tOilTypeSet as1, as2;
#endif
  {
      SetArg3.head= (VoidPtr)as2;
      SetArg2.head= (VoidPtr)as1;
      return ( OilIdResultSet( id, &SetArg2 ));
  }

tOilTypeSet
#ifdef PROTO_OK
OilIdResultTS3(tOilOp id, tOilTypeSet as1, tOilTypeSet as2, tOilTypeSet as3 )
#else
OilIdResultTS3( id, as1, as2, as3 ) tOilOp id; tOilTypeSet as1, as2, as3;
#endif
  {
      SetArg3.head= (VoidPtr)as3;
      SetArg2.head= (VoidPtr)as2;
      SetArg1.head= (VoidPtr)as1;
      return ( OilIdResultSet( id, &SetArg1 ));
  }



/*****************************************************
  OilIdOpTS<n> - allow for convienent use of general routines
      Identify an operator using type sets to describe arguments.
  */

tOilOp
#ifdef PROTO_OK
OilIdOpTS1(tOilType rt, tOilOp id, tOilTypeSet as1 )
#else
OilIdOpTS1( rt, id, as1 ) tOilType rt; tOilOp id; tOilTypeSet as1;
#endif
  {
      SetArg3.head= (VoidPtr)as1;
      return ( OilIdOpTSn( id, &SetArg3, rt ));
  }

tOilOp
#ifdef PROTO_OK
OilIdOpTS2(tOilType rt, tOilOp id, tOilTypeSet as1, tOilTypeSet as2 )
#else
OilIdOpTS2( rt, id, as1, as2 ) tOilType rt; tOilOp id; tOilTypeSet as1, as2;
#endif
  {
      SetArg3.head= (VoidPtr)as2;
      SetArg2.head= (VoidPtr)as1;
      return ( OilIdOpTSn( id, &SetArg2, rt ));
  }

tOilOp
#ifdef PROTO_OK
OilIdOpTS3(tOilType rt, tOilOp id, tOilTypeSet as1, tOilTypeSet as2, tOilTypeSet as3 )
#else
OilIdOpTS3( rt, id, as1, as2, as3 ) tOilType rt; tOilOp id;
    tOilTypeSet as1, as2, as3;
#endif
  {
      SetArg3.head= (VoidPtr)as3;
      SetArg2.head= (VoidPtr)as2;
      SetArg1.head= (VoidPtr)as1;
      return ( OilIdOpTSn( id, &SetArg1, rt ));
  }


/*****************************************************
  OilIdOp<n> - allow for convienent use of general routines
      Identify an operator using simple types to describe arguments.
  */

tOilOp
#ifdef PROTO_OK
OilIdOp1(tOilOp id, tOilType at1 )
#else
OilIdOp1( id, at1 ) tOilOp id; tOilType at1;
#endif
  {
      SetArg3.head= OilTypeToSet(at1);
      return ( OilIdOpTSn( id, &SetArg3, (tOilType)0 ));
  }

tOilOp
#ifdef PROTO_OK
OilIdOp2(tOilOp id, tOilType at1, tOilType at2 )
#else
OilIdOp2( id, at1, at2 ) tOilOp id; tOilType at1, at2;
#endif
  {
      SetArg3.head= OilTypeToSet(at2);
      SetArg2.head= OilTypeToSet(at1);
      return ( OilIdOpTSn( id, &SetArg2, (tOilType)0 ));
  }

tOilOp
#ifdef PROTO_OK
OilIdOp3(tOilOp id, tOilType at1, tOilType at2, tOilType at3 )
#else
OilIdOp3( id, at1, at2, at3 ) tOilOp id; tOilType at1, at2, at3;
#endif
  {
      SetArg3.head= OilTypeToSet(at3);
      SetArg2.head= OilTypeToSet(at2);
      SetArg1.head= OilTypeToSet(at1);
      return ( OilIdOpTSn( id, &SetArg1, (tOilType)0 ));
  }


/*****************************************************
  OilClassInst<n> - instantiate a class with the designated number of
        parameter types.
  */

tOilType
#ifdef PROTO_OK
OilClassInst0(tOilClass c, oilName id)
#else
OilClassInst0(c, id) tOilClass c; oilName id;
#endif
{ tOilType rt;
  tOilArgSig as;

  rt = OilNewType( id );
  as = OilNewArgSig();
  as = OilAddArgSig(rt, as);
  OilDefClassOps(c, as);
  return rt;
}

tOilType
#ifdef PROTO_OK
OilClassInst1(tOilClass c, oilName id, tOilType at1)
#else
OilClassInst1(c, id, at1) tOilClass c; oilName id; tOilType at1;
#endif
{ tOilType rt;
  tOilArgSig as;

  if (at1 == OilInvalidType) return OilInvalidType;

  rt = OilNewType(id);
  as = OilNewArgSig();
  as = OilAddArgSig(at1, as);
  as = OilAddArgSig(rt, as);
  OilDefClassOps(c, as);
  return rt;
}

tOilType
#ifdef PROTO_OK
OilClassInst2(tOilClass c, oilName id, tOilType at1, tOilType at2)
#else
OilClassInst2(c, id, at1, at2) tOilClass c; oilName id; tOilType at1, at2;
#endif
{ tOilType rt;
  tOilArgSig as;

  if (at1 == OilInvalidType || at2 == OilInvalidType) return OilInvalidType;

  rt = OilNewType(id);
  as = OilNewArgSig();
  as = OilAddArgSig(at2, as);
  as = OilAddArgSig(at1, as);
  as = OilAddArgSig(rt, as);
  OilDefClassOps(c, as);
  return rt;
}



/*****************************************************
  OilTypeName, OilOpName, OilClassName - return the name attached to the 
      object
  */
oilName
#ifdef PROTO_OK
OilTypeName(tOilType obj )
#else
OilTypeName( obj ) tOilType obj;
#endif
    {
	return obj ? obj->sName : NoName;
    }

oilName
#ifdef PROTO_OK
OilOpName(tOilOp obj )
#else
OilOpName( obj ) tOilOp obj;
#endif
    {
	return obj ? obj->sName : NoName;
    }

oilName
#ifdef PROTO_OK
OilClassName(tOilClass obj )
#else
OilClassName( obj ) tOilClass obj;
#endif
    {
	return obj ? obj->sName : NoName;
    }

/*	* *  the end of oiladt2c.c  * *		*/
