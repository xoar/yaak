/*
** $Id: format.c,v 1.5 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: format.c,v 1.5 1997/08/29 08:38:08 mjung Exp $";

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

/***********************************************************************
 **
 **   Filename   :  format.c
 **
 **   Author     :  Ursula Stellmacher
 **
 **   Date       :  12.11.88
 **
 **   Task       : contains functions for formatting
 **
 **********************************************************************/

#include <stdio.h>
#include <string.h>
#include "comar.h"
#include "name.h"
#include "format.h"
#include "errandio.h"


/***********************************************************************
 **
 **  function   : print_prodname
 **
 **  task       : writes, if it exists, the productionname in the outputfile
 **
 **  return     : void
 **
 **********************************************************************/

PRIVATE void print_prodname ( root , sid , fout_ptr  )

 p_comar root;
 int sid;
 FILE *fout_ptr;

 {
    SEQsymb_entry ssymb;
    symb_entry symb;
    BOOL name_gef;

    name_gef = FALSE;
    foreachinSEQsymb_entry( root->symbols , ssymb , symb )
    {
       /*
	* the productionname is stored as name in the ST
	*/

	if ( typeof( symb ) == Kp_name )
	{
	   if ( symb.Vp_name->sid == sid )
	   {
	      (void) fprintf( fout_ptr , " %s = " , symb.Vp_name->str );
	      name_gef = TRUE;
	      break;
	   }
	}
    }
    if ( !name_gef )
    {
       error_message( LHSPROD , "print_prodname" , NULL , NULL );
    }
 }  /* end of print_prodname */


/***********************************************************************
 **
 **  function   : get_sid_of_lhs
 **
 **  task       : yields the SID of the DID of the left side
 **
 **  return     : int (SID)
 **
 **********************************************************************/

PRIVATE int get_sid_of_lhs ( root , did )

p_comar root;
int did;

{
     SEQdef_entry sdef;
     def_entry def;


     foreachinSEQdef_entry( root->definitions , sdef , def )
     {
	/*
	 * the left side of a production has to be a nonterminal
	 */

    	if ( typeof( def ) == Kp_nterm )
    	{
           if ( def.Vp_nterm->did == did )
           {
              return(def.Vp_nterm->sid);
           }
        }
    }
    return(0);  /* falls SID nicht gefunden */

} /* end of get_sid_of_lhs */


/***********************************************************************
 **
 **  function   : get_sid_of_nterm_or_term
 **
 **  task       : yields the SID of the DID of a nonterminal or a terminal
 **               of the right side
 **
 **  return     : int (SID)
 **
**********************************************************************/

PRIVATE int get_sid_of_nterm_or_term ( root , did )

p_comar root;
int did;

{
    SEQdef_entry sdef;
    def_entry def;


    foreachinSEQdef_entry( root->definitions , sdef , def )
    {
       if ( def.IDLclassCommon->did == did )
       {
          if ( ( typeof( def ) == Kp_nterm ) || ( typeof( def ) == Kp_term ) )
	  {
	      return(def.IDLclassCommon->sid);
	  }
	  else
	  {
	      return (0);
	  }
       }
    }
      /* if the SID was not found */
    error_message(RHSSYMTAB, "get_sid_of_nterm_or_term" , NULL , NULL );
    return(0);
} /* end of get_sid_of_nterm_or_term */


/***********************************************************************
 **
 **  function   : print_nterm_of_lhs
 **
 **  task       : writes the nonterminal of the left side into the outputfile
 **
 **  return     : void
 **
***********************************************************************/

PRIVATE void print_nterm_of_lhs ( root , sid , fout_ptr )

p_comar root;
int sid;
FILE *fout_ptr;

{
    SEQsymb_entry ssymb;
    symb_entry symb;
    BOOL lhs_gef;

    lhs_gef = FALSE;
    foreachinSEQsymb_entry( root->symbols , ssymb , symb )
    {
      /*
       * the left side of a production is a nonterminal and stored as
       * name in the ST
       */

       if ( typeof( symb ) == Kp_name )
       {
	  if ( symb.Vp_name->sid == sid )
	  {
	    (void) fprintf( fout_ptr , "%s" , symb.Vp_name->str );
	    lhs_gef = TRUE;
	    break;
	  }
       }
    }
    if ( !lhs_gef )
    {
       error_message( LHSSYMTAB, "print_nterm_of_lhs" , NULL , NULL );
    }

} /* end of print_nterm_of_lhs */


/***********************************************************************
 **
 **  function   : print_lhs_of_prod
 **
 **  task       : writes the left side into the outputfile
 **
 **  return     : void
 **
 **********************************************************************/


 PRIVATE void print_lhs_of_prod ( root , did , fout_ptr )

 p_comar root;
 int did;
 FILE *fout_ptr;

 {
      int sid;


      sid = get_sid_of_lhs( root , did );
      if ( sid != 0 )
      {
	  print_nterm_of_lhs(  root , sid , fout_ptr );
	  (void) fprintf( fout_ptr, " :  ");
      }
      else
      {
	/*
	 * the left side is not stored as a nonterminal in the DT
	 */

	  error_message( LHSDEFTAB, "print_lhs_of_prod" , NULL , NULL );
      }

 } /* end of print_lhs_of_prod */


/***********************************************************************
 **
 **  function   : print_nterm_or_term_of_rhs
 **
 **  task       : writes the terminals and the nonterminals of the right
 **               side of a production into the outputfile
 **
 **  return     : void
 **
**********************************************************************/


 PRIVATE void print_nterm_or_term_of_rhs( root , sid , fout_ptr )

 p_comar root;
 int sid;
 FILE *fout_ptr;

 {
     SEQsymb_entry ssymb;
     symb_entry symb;
     BOOL rhs_gef;


     rhs_gef = FALSE;
     foreachinSEQsymb_entry( root->symbols , ssymb , symb )
     {
        if ( symb.IDLclassCommon->sid == sid )
	{
           if ( typeof( symb ) == Kp_name )
           {
	      /*
	       * nonterminals and nonliteral terminals are stored as name
	       *
	       * writing the nonterminal
	       */

	      (void) fprintf( fout_ptr , " %s" , symb.Vp_name->str );
	      rhs_gef = TRUE;
	      break;
	   }
	   else
	   {
	      if ( typeof( symb ) == Kp_string )
	      {

	       /*
	        * literal terminals are stored as string in the ST
		*
		* writing the terminal
	        */

		 (void) fprintf( fout_ptr , " '%s'" , symb.Vp_string->str );
		 rhs_gef = TRUE;
		 break;
	      }
	   }
	}
     }
     if ( !rhs_gef )
     {
	error_message( RHSSYMTAB, "print_nterm_or_term_of_rhs" , NULL , NULL );
     }

 } /* end of print_nterm_or_term_of_rhs */


/***********************************************************************
 **
 **  function   : get_kind_of_other
 **
 **  task       : yields the kind of an other element
 **
 **  return     : int
 **
 **********************************************************************/

 PRIVATE int get_kind_of_other( root , sid )

 p_comar root;
 int sid;

 {
    SEQsymb_entry ssymb;
    symb_entry symb;

    foreachinSEQsymb_entry( root->symbols , ssymb , symb )
    {
	  if ( symb.IDLclassCommon->sid == sid )
	  {
	     if ( strcmp( symb.IDLclassCommon->str , "connect" ) == 0 )
             {
		return(CONNECT);
	     }
	     if ( strcmp( symb.IDLclassCommon->str , "reducemod" ) == 0 )
	     {
		return(REDUCEMOD);
	     }
	     if ( strcmp( symb.IDLclassCommon->str , "noreducemod" ) == 0 )
	     {
		return(NOREDUCEMOD);
	     }

	  }
       }
    return(0);
 } /* end of get_kind_of_other */


/***********************************************************************
 **
 **  function   : print_connect
 **
 **  task       : writes the connections of a production into the
 **               outputfile
 **
 **  return     : void
 **
 **********************************************************************/

 PRIVATE void print_connect( root , sid , fout_ptr )

 p_comar root;
 int sid;
 FILE *fout_ptr;

 {
    SEQsymb_entry ssymb;
    symb_entry symb;
    BOOL connect_gef;

    connect_gef = FALSE;
    foreachinSEQsymb_entry( root->symbols , ssymb , symb )
    {
	  if ( symb.IDLclassCommon->sid == sid )
	  {
	     if ( typeof( symb ) == Kp_string )
	     {
	        (void) fprintf( fout_ptr , "'%s'" , symb.Vp_string->str );
	        connect_gef = TRUE;
	        break;
             }
             else
             {
	        if ( typeof( symb ) == Kp_name )
	        {
		   (void) fprintf( fout_ptr , "%s" , symb.Vp_name->str );
	       	   connect_gef = TRUE;
		   break;
	        }
	     }
          }
    }
    if ( ! connect_gef )
    {
       error_message( RHSOTHER, "print_connect" , NULL , NULL );
    }
 }  /* end of print_connect */



/***********************************************************************
 **
 **  function   : print_others_of_rhs
 **
 **  task       : writes the others ( Connnection & Modifications ) of
 **               the right side into the outputfile
 **
 **  return     : void
 **
 **********************************************************************/

 PRIVATE void print_others_of_rhs(  root , did , fout_ptr )

 p_comar root;
 int did;
 FILE *fout_ptr;

 {
    SEQdef_entry sdef;
    def_entry def;
    SEQprop_entry sprop;
    prop_entry prop;


    foreachinSEQdef_entry( root->definitions , sdef , def )
    {
       if ( typeof( def ) == Kp_other )
       {
	   if ( def.Vp_other->did == did )
	   {
	      foreachinSEQprop_entry ( def.Vp_other->prop , sprop , prop )
	      {
		 if ( typeof( prop ) == Kp_prop )
                 {
		    if ( get_kind_of_other( root , prop.Vp_prop->sid ) == CONNECT )
                    {
		       (void) fprintf( fout_ptr , " &" );
		       print_connect( root , def.Vp_other->sid , fout_ptr );
		       break;
                    }
                  }
                  else
		  {
		    if ( typeof( prop ) == Kp_prop_val )
		    {
		       if ( get_kind_of_other( root , prop.Vp_prop_val->sid ) == REDUCEMOD )
		       {
                          if ( typeof( prop.Vp_prop_val->val ) == Kp_dval )
			  {
			     (void) fprintf( fout_ptr , " @" );
			     print_connect( root , get_sid_of_nterm_or_term( root , prop.Vp_prop_val->val.Vp_dval->did ) , fout_ptr );
			     break;
			  }
		       }
		       else
		       {
			  if ( get_kind_of_other( root , prop.Vp_prop_val->sid ) == NOREDUCEMOD )
			  {
			     if ( typeof( prop.Vp_prop_val->val ) == Kp_dval )
			     {
			        (void) fprintf( fout_ptr , " $" );
				print_connect( root , get_sid_of_nterm_or_term( root , prop.Vp_prop_val->val.Vp_dval->did ) , fout_ptr );
				break;
                             }
			  }
		       }
                     }
	          }
	      }
	   }
       }
   }
} /* end of print_others_of_rhs */

/***********************************************************************
 **
 **  function   : print_rhs_of_prod
 **
 **  task       : writes the right side of a production into the outputfile
 **
 **  return     : void
 **
 **********************************************************************/

PRIVATE void print_rhs_of_prod( root , seq , altnewline , delaltpar , fout_ptr )

p_comar root;
SEQunit *seq;
BOOL altnewline;  /* direction of the linechange by '/' items */
BOOL delaltpar;   /* direction of the quotes by '//' items */
FILE *fout_ptr;

{
    SEQunit sunit;
    unit unit1, unit2;
    int sid;
    int eofdid = -1;

    /* Don't print symbol EOF with property STOP!
     * Therefore eofdid is computed here.
     */
    if ( eofdid < 0 )
    {
      SEQsymb_entry seq;
      symb_entry s;
      SEQdef_entry dseq;
      def_entry d;
      SEQprop_entry pseq;
      prop_entry p;
      int EOFsid = -1, eofsid = -1;

      foreachinSEQsymb_entry(root->symbols, seq, s)
      {
	if ( typeof(s) == Kp_string && !strcmp(s.Vp_string->str, STOP) )
	  eofsid = s.Vp_string->sid;
	if ( typeof(s) == EOFTYPE && !strcmp(s.Vp_name->str, EOFSTRING) )
	  EOFsid = s.Vp_name->sid;
      } /* for */
      if ( eofsid > 0 )
	foreachinSEQdef_entry(root->definitions, dseq, d)
	{
	  if ( typeof(d) == Kp_term )
	    if (d.Vp_term->sid == EOFsid)
	      foreachinSEQprop_entry(d.Vp_term->prop, pseq, p)
	      {
		if ( typeof(p) == Kp_prop  &&  p.Vp_prop->sid == eofsid )
		  eofdid = d.Vp_term->did;
		break;
	      }
	  if ( eofdid > 0 )
	    break;
	}
      if ( eofdid < 0 ) eofdid = 0;
    } /* if (eofdid < 0) */

    if ( emptySEQunit( *seq ) )
    {
       (void) fprintf(fout_ptr , "  " );
    }

    foreachinSEQunit( *seq , sunit , unit1 )
    {
    	switch ( typeof( unit1 ) )
    	{
           case Kp_alt    : if ( (lengthSEQunit( *seq ) == 1)
                                 && (!delaltpar) )
			    {
			       /*
				* without quotas
				*/
				print_rhs_of_prod( root , &(unit1.Vp_alt->rhs1), altnewline , FALSE , fout_ptr );
			        if ( altnewline )
			        {
				   /*
				    * linechange
				    */
			           (void) fprintf(fout_ptr , "\n   /\t" );
			        }
			        else
			        {
			           (void) fprintf(fout_ptr , " /" );
			        }
			        print_rhs_of_prod( root , &(unit1.Vp_alt->rhs2), altnewline , FALSE , fout_ptr );
                            }
			    else
			    {
			       if ( (lengthSEQunit( *seq ) > 1) || delaltpar )
			       {
				   /*
				    * with quotas
				    */
				  (void) fprintf(fout_ptr , " (" );
                                  print_rhs_of_prod( root , &(unit1.Vp_alt->rhs1) , FALSE , FALSE , fout_ptr );
				  (void) fprintf(fout_ptr , " /" );
				  print_rhs_of_prod( root , &(unit1.Vp_alt->rhs2) , FALSE , FALSE , fout_ptr );
				  (void) fprintf(fout_ptr , " )" );
			       }
			    }
			    break;

           case Kp_opt    : altnewline = FALSE;
			    (void) fprintf(fout_ptr , " [" );
			    print_rhs_of_prod( root , &(unit1.Vp_opt->rhs), altnewline , FALSE , fout_ptr );
			    (void) fprintf(fout_ptr , " ]" );
			    altnewline = TRUE;
			    break;

           case Kp_plus   : altnewline = FALSE;
			    if ( lengthSEQunit ( unit1.Vp_plus->rhs ) == 1 )
			    {
				   /*
				    * no quotes by one element
				    */
			       retrievefirstSEQunit( unit1.Vp_plus->rhs , unit2 );
			       if ( ( typeof( unit2 ) == Kp_elunit ) ||
			            ( typeof( unit2 ) == Kp_opt )    ||
				    ( typeof( unit2 ) == Kp_delrep ) )
			       {
			          print_rhs_of_prod( root , &(unit1.Vp_plus->rhs), altnewline , FALSE , fout_ptr );
                                  (void) fprintf(fout_ptr , "+" );
                               }
			       else
			       {
			          (void) fprintf(fout_ptr, " (" );
        		          print_rhs_of_prod( root , &(unit1.Vp_plus->rhs) , altnewline , FALSE , fout_ptr );
                                  (void) fprintf(fout_ptr, " )+" );
			       }
			    }
			    else
			    {
			        (void) fprintf(fout_ptr , " (" );
        		        print_rhs_of_prod( root , &(unit1.Vp_plus->rhs), altnewline , FALSE , fout_ptr );
			        (void) fprintf(fout_ptr , " )+" );
			    }
			    altnewline = TRUE;
			    break;

           case Kp_star   : altnewline = FALSE;
			    if ( lengthSEQunit ( unit1.Vp_star->rhs ) == 1 )
			    {
				   /*
				    * no quotes by one element
				    */
			       retrievefirstSEQunit( unit1.Vp_plus->rhs , unit2 );
			       if ( ( typeof( unit2 ) == Kp_elunit ) ||
			            ( typeof( unit2 ) == Kp_opt )    ||
			            ( typeof( unit2 ) == Kp_delrep ) )
			       {
			          print_rhs_of_prod( root , &(unit1.Vp_star->rhs), altnewline , FALSE , fout_ptr );
			          (void) fprintf(fout_ptr , "*" );
                               }
			       else
			       {
			          (void) fprintf(fout_ptr , " (" );
			          print_rhs_of_prod( root , &(unit1.Vp_star->rhs), altnewline , FALSE , fout_ptr );
			          (void) fprintf(fout_ptr , " )*" );
			       }
                            }
			    else
			    {
			       (void) fprintf(fout_ptr , " (" );
			       print_rhs_of_prod( root , &(unit1.Vp_star->rhs), altnewline , FALSE , fout_ptr );
                               (void) fprintf(fout_ptr , " )*" );
			    }
			    altnewline = TRUE;
			    break;

           case Kp_delrep : altnewline = FALSE;
	                    (void) fprintf(fout_ptr , " (" );
		            if ( lengthSEQunit( unit1.Vp_delrep->rhs ) == 1 )
		            {
		               retrievefirstSEQunit( unit1.Vp_delrep->rhs , unit2 );
			       if ( typeof( unit2 ) == Kp_alt )
			       {
			          print_rhs_of_prod( root , &(unit1.Vp_delrep->rhs), altnewline , TRUE , fout_ptr );
                               }
			       else
			       {
			          print_rhs_of_prod( root , &(unit1.Vp_delrep->rhs), altnewline , FALSE , fout_ptr );
			       }
                             }
			     else
			     {
				print_rhs_of_prod( root , &(unit1.Vp_delrep->rhs), altnewline , FALSE , fout_ptr );
                             }
			     (void) fprintf(fout_ptr , " //" );
                             if ( lengthSEQunit( unit1.Vp_delrep->sep ) == 1 )
			     {
			         retrievefirstSEQunit( unit1.Vp_delrep->sep , unit2 );
			         if ( typeof( unit2 ) == Kp_alt )
			         {
			            print_rhs_of_prod( root , &(unit1.Vp_delrep->sep), altnewline , TRUE , fout_ptr );
			         }
				 else
				 {
				   print_rhs_of_prod( root , &(unit1.Vp_delrep->sep), altnewline , FALSE , fout_ptr );
				 }
			      }
			      else
			      {
			         print_rhs_of_prod( root , &(unit1.Vp_delrep->sep), altnewline , FALSE , fout_ptr );
			      }
			    (void) fprintf(fout_ptr , " )" );
			    altnewline = TRUE;
			    break;

           case Kp_elunit : sid = get_sid_of_nterm_or_term( root , unit1.Vp_elunit->did );
			    if ( sid != 0 )
                            {
			      if (unit1.Vp_elunit->did != eofdid)
				print_nterm_or_term_of_rhs(root, sid, fout_ptr);
			    }
			    else
			    {
			       print_others_of_rhs( root , unit1.Vp_elunit->did , fout_ptr );
			    }
			    break;
           default:
			    break;

        } /* end of switch */
  }

} /* end of print_rhs_of_prod */

/***********************************************************************
 **  function   : print_prod
 **
 **  task       : writes exactly one production into the outputfile
 **
 **  return     : void
 **
 **********************************************************************/

 PUBLIC void print_prod( root , did , fout_ptr )

 p_comar root;
 int did;
 FILE *fout_ptr;

 {
     BOOL altnewline, delaltpar;  /* s. print_rhs_of_prod */
     SEQdef_entry sdef;
     def_entry def;


     altnewline = TRUE;
     delaltpar = FALSE;

     foreachinSEQdef_entry( root->definitions , sdef , def )
     {
       if (typeof(def) == Kp_prod)
       {
	 if (def.Vp_prod->did == did)
	 {

            if ( ( def.Vp_prod->sid != 1 ) && ( def.Vp_prod->sid != 0 ) )
            {
                print_prodname( root , def.Vp_prod->sid , fout_ptr );
            }
            print_lhs_of_prod( root , def.Vp_prod->lhsdid  , fout_ptr);
            print_rhs_of_prod( root , &(def.Vp_prod->rhs) , altnewline , delaltpar , fout_ptr );
            (void) fprintf( fout_ptr , ".\n" );
	    break;
         }
       }
    }

 } /* end of print_prod */

/***********************************************************************
 **  function   : print_string
 **
 **  task       : prints the string of the given sid
 **
 **  return     : void
 **
 **********************************************************************/

PRIVATE void print_string( root , sid , fout_ptr )
p_comar root;
int     sid;
FILE    *fout_ptr;
{
   SEQsymb_entry  ssymb;
   symb_entry     symb;

   foreachinSEQsymb_entry( root->symbols , ssymb , symb )
   {
      if ( symb.IDLclassCommon->sid == sid )
      {
	  if ( typeof( symb ) == Kp_string )
	  {
	     (void) fprintf( fout_ptr , "'%s'\n" , symb.Vp_string->str );
          }
	  else
	  {
	     (void) fprintf( fout_ptr , "%s\n" , symb.Vp_string->str );
	  }
      }
   }
} /* end of print_string */


/***********************************************************************
 **  function   : print_grammar_name
 **
 **  task       : prints  the name of the grammar
 **
 **  return     : void
 **
 **********************************************************************/

PRIVATE void print_grammar_name( root , grsid , fout_ptr )
p_comar root;
int     grsid;
FILE *  fout_ptr;

{
   SEQdef_entry  sdef;
   def_entry     def;
   prop_entry    prop;

   foreachinSEQdef_entry( root->definitions , sdef , def )
   {
      if ( typeof( def ) == Kp_other )
      {
	 if ( !emptySEQprop_entry( def.Vp_other->prop ) )
	 {
	     retrievefirstSEQprop_entry( def.Vp_other->prop , prop );
	     if ( typeof(prop) == Kp_prop )
	     {
		if ( prop.Vp_prop->sid == grsid )
		{
		   (void) fprintf(fout_ptr , "$GRAMMAR = ");
		   print_string( root , def.Vp_other->sid , fout_ptr );
		}
	     }
	 }
      }
   }
} /* end of print_grammar_name */


/***********************************************************************
 **  function   : grammar_name_ex
 **
 **  task       : checks whether a grammar name exist
 **
 **  return     : BOOL
 **
 **********************************************************************/

PRIVATE BOOL grammar_name_ex( root , grsid )
p_comar root;
int     *grsid;
{
   SEQsymb_entry  ssymb;
   symb_entry     symb;

   foreachinSEQsymb_entry( root->symbols , ssymb , symb )
   {
      if ( typeof(symb) == Kp_string )
      {
	 if ( strcmp( symb.Vp_string->str , "PGS_GRAMNAME" ) == 0 )
	 {
	     *grsid = symb.Vp_string->sid;
	     return( TRUE );
	 }
      }
   }
   return( FALSE );
} /* grammar_name_ex */

/***********************************************************************
 **  function   : print_grammar
 **
 **  task       : writes all productions into the outputfile
 **
 **  return     : void
 **
 **********************************************************************/

PUBLIC void print_grammar( root , fout_ptr )

p_comar root;
FILE *fout_ptr;

{
      SEQdef_entry sdef;
      def_entry def;
      int        grsid;

      BOOL altnewline, delaltpar;  /* s. print_rhs_of_prod */

      altnewline = TRUE;
      delaltpar = FALSE;

      if ( grammar_name_ex( root , &grsid ) )
      {
	 print_grammar_name( root , grsid , fout_ptr );
      }
      else
      {
	 (void) fprintf( fout_ptr , "$GRAMMAR\n" );
      }

      foreachinSEQdef_entry( root->definitions , sdef , def )
      {
          if ( typeof( def ) == Kp_prod )
          {
               if ( ( def.Vp_prod->sid != 1 ) && ( def.Vp_prod->sid != 0 ) )
	       {
		  print_prodname( root , def.Vp_prod->sid , fout_ptr );
	       }
	       print_lhs_of_prod( root , def.Vp_prod->lhsdid , fout_ptr );
	       print_rhs_of_prod( root , &(def.Vp_prod->rhs) , altnewline , delaltpar , fout_ptr );
	       (void) fprintf( fout_ptr , ".\n" );
          }
      }
} /* end of print_grammar */
