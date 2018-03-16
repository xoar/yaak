/*
** $Id: wrtfunc.c,v 1.6 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: wrtfunc.c,v 1.6 1997/08/29 08:38:08 mjung Exp $";

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

/******************************************************************************/
/* filename: wrtfunc.c                        first edit   : 29 . 8 . 89      */
/* author  : Christian Zeitel                 last  change : 10 . 7 . 90      */
/******************************************************************************/

/********************************** CONTENTS ***********************************
 *									       *
 *  This  file  is  the  implementation of module wrtfunc. It  contains the    *
 *  writing-functions which print out the parsertables on file "ptabs.h"       *
 *  in C-programcode. It is devided in two steps: function Wrt_fixtabs         *
 *  prints out all tables which do not depend on optimization. Function        *
 *  Twrt_<X>tabs where <X> is in { GCS, LES, RDS, SDS, RCS } prints            *
 *  out the terminal-table for the selected optimizationmethod, Function       *
 *  Nwrt_<X>tabs where <X> is in { GCS, LES, RDS, SDS, RCS }             
       *
 *  prints out the nonterminaltable for the selected optimizationmethod.       *
 *									       *
 ******************************* INCLUDE-FILES ********************************/
 
#include <stdio.h>

#include "tabsopttype.h"

#include "wrthelpfunc.h"

/******************************** CONSTANT-MACROS *****************************/

#define  NO  		 0

#define  YES   		 1

#define  HEX             0

#define  DEC             1

#define  NTAB 		 0

#define  TTAB		 1

#define  MAXCHARCODE   255

/******************************************************************************/
      

typedef short *readtype[];


/*============================================================================*/
/*==============                                            ==================*/
/*==============   FUNCTION  WRITING NOT OPTIMIZED TABLES   ==================*/
/*==============                                            ==================*/
/*============================================================================*/



void Wrt_fixtabs( fp, fp_sema, pt_data, addinfo )

     FILE    *fp,          /* the filepointer to file "ptabs.h"               */             *fp_sema;     /* filepointer to file with semantic informati-    */                           /* for terminals                                   */     readtype pt_data;     /* contains all important datas of the con. parser */     char     addinfo;     /* =1, if abdditional informations are printed out */     
    /*  Prints out all tables which do not depend on optimization.
     *
     ***/
     
     {
         if( addinfo ) 
                printf("    C**function Wrt_fixtabs : started!\n");
         
         print_fixtabs( fp, fp_sema, pt_data );
         
        
     }/* Wrt_fixtabs */
            

/*============================================================================*/
/*=================            				       ===============*/
/*=================   FUNCTIONS FOR OPTIMIZATION-METHOD GCS    ===============*/
/*=================            				       ===============*/
/*============================================================================*/


void Twrt_GCStabs(fp, pt_data, opt_data, addinfo)

     FILE     *fp;         /* the filepointer to file "ptabs.h"               */
     readtype  pt_data;    /* contains all important datas of the con. parser */
     opttype  *opt_data;   /* contains allimportant datas of the optimized    */
     			   /* parsertables				      */
     char      addinfo;    /* =1, if additional informations are printed out  */
     
    /*  Prints the optimized terminal-table with the helping-vectors trowind
     *  tcolind, conv and the negated error-matrix sigmap with the helping-
     *  vectors sigrowind and sigcolind on file ptabs.h.
     *
     ***/
     
     {  short    *ttab, /* terminaltable       */
     		  nos,  /* number of states    */
     		  not;  /* number of terminals */
     		  
     		 
     	if( addinfo )
     		printf("    C**function Twrt_GCStabs: started!\n");
     	
     	print_label( TTAB, fp, _MGCS );
     			
     	nos  = *pt_data[9];
     	not  = *pt_data[0];
     	ttab =  pt_data[1];	 
     	
     	/***************************************************************/
        /********* print out helping vector conv  **********************/
        /***************************************************************/
        print_table( 
        	      opt_data->ttabopt.GCS.convtermlist,
        	      "conv",
        	      fp,
        	      (not - 1) > MAXCHARCODE,
        	      DEC,
        	      maxterm + 1
        	    );

	/***************************************************************/
        /********* print out helping vector sigrowind  *****************/
        /***************************************************************/
        print_table(
        	      opt_data->ttabopt.GCS.sigrowind,
        	      "sigrowind",
        	      fp,
        	      opt_data->ttabopt.GCS.sigmaxrowind > MAXCHARCODE,
        	      DEC,
        	      nos
        	    );
        
        /***************************************************************/
        /********* print out helping vector sigcolind  *****************/
        /***************************************************************/
        print_table(
        	      opt_data->ttabopt.GCS.sigcolind,
        	      "sigcolind",
        	      fp,
        	      opt_data->ttabopt.GCS.sigmaxcolind > MAXCHARCODE,
        	      DEC,
        	      not
        	   );
         
        /***************************************************************/
        /********* print out the negated error-matrix  *****************/
        /***************************************************************/
        print_errmat(
        	      fp, 
        	      not, 
        	      nos, 
        	      (opt_data->ttabopt.GCS.sigmaxcolind + 8) >> 3,
        	      opt_data->ttabopt.GCS.sigrowptr,
        	      opt_data->ttabopt.GCS.sigcolptr,
        	      ttab
        	    );

        /***************************************************************/
        /********* print out helping vector trowptr  *******************/
        /***************************************************************/
        print_table(
        	      opt_data->ttabopt.GCS.rowind,
        	      "trowptr",
        	      fp,
        	      opt_data->ttabopt.GCS.maxrowind > MAXCHARCODE,
        	      DEC,
        	      nos
        	    );
        
        /***************************************************************/
        /********* print out helping vector tcolptr  *******************/
        /***************************************************************/
        print_table(
        	      opt_data->ttabopt.GCS.colind,
        	      "tcolptr",
        	      fp,
        	      opt_data->ttabopt.GCS.maxcolind > MAXCHARCODE,
        	      DEC,
        	      not
        	    );
        			
     	
     	/***************************************************************/
        /********* print out the compressed terminal-table *************/
        /***************************************************************/
        print_GCSptab(
        		fp,
        		TTAB,
        		( opt_data->ttabopt.GCS.maxrowind + 1 ) *
                        ( opt_data->ttabopt.GCS.maxcolind + 1 ),
                        opt_data->ttabopt.GCS.maxcolind + 1,
                        opt_data->ttabopt.GCS.ttab
                      );
                      
                      
     }/* Twrt_GCStabs */
        
        				




     				
     	
void Nwrt_GCStabs(fp, pt_data, opt_data, addinfo)

     FILE     *fp;         /* the filepointer to file "ptabs.h"               */
     readtype  pt_data;    /* contains all important datas of the con. parser */
     opttype  *opt_data;   /* contains allimportant datas of the optimized    */
     			   /* parsertables				      */
     char      addinfo;    /* =1, if additional informations are printed out  */
     
    /*  Prints the optimized nonterminal-table with the
     *  helping-vectors nrowind and ncolind on file "ptabs.h" .
     *
     ***/
     
     {  short     nos,  /* number of states       */
     		  non;  /* number of nonterminals */
                
     		 
     	if( addinfo )
     		printf("    C**function Nwrt_GCStabs: started!\n");
     	
     	print_label( NTAB, fp, _MGCS);
     	
     	nos  = *pt_data[9];
     	non  = *pt_data[3];
        
        /***************************************************************/
        /********* print out helping vector nrowptr  *******************/
        /***************************************************************/
        print_table(
        	      opt_data->ntabopt.GCS.rowind,
        	      "nrowptr",
        	      fp,
        	      opt_data->ntabopt.GCS.maxrowind > MAXCHARCODE,
        	      DEC,
        	      nos
        	    );
        
        /***************************************************************/
        /********* print out helping vector ncolptr  *******************/
        /***************************************************************/
        print_table(
        	      opt_data->ntabopt.GCS.colind,
        	      "ncolptr",
        	      fp,
        	      opt_data->ntabopt.GCS.maxcolind > MAXCHARCODE,
        	      DEC,
        	      non
        	    );
        			
     	/***************************************************************/
        /********* print out the compressed nonterminal-table **********/
        /***************************************************************/
        print_GCSptab(
        		fp,
        		NTAB,
        		( opt_data->ntabopt.GCS.maxrowind + 1 ) *
                        ( opt_data->ntabopt.GCS.maxcolind + 1 ),
                        opt_data->ntabopt.GCS.maxcolind + 1,
                        opt_data->ntabopt.GCS.ntab
                      );
        
        
     }/* Nwrt_GCStabs */     	






/*============================================================================*/
/*=================            				       ===============*/
/*=================   FUNCTIONS FOR OPTIMIZATION-METHOD LES    ===============*/
/*=================            				       ===============*/
/*============================================================================*/


void Twrt_LEStabs(fp, pt_data, opt_data, addinfo)

     FILE     *fp;         /* the filepointer to file "ptabs.h"               */
     readtype  pt_data;    /* contains all important datas of the con. parser */
     opttype  *opt_data;   /* contains allimportant datas of the optimized    */
     			   /* parsertables				      */
     char      addinfo;    /* =1, if additional informations are printed out  */
     
    /*  Prints the optimized terminal-table with the helping-vectors trowval,
     *  tcolval, decrow, deccol on file "ptabs.h". Further the negated and
     *  compressed error-matrix with its helping-vectors and the vector conv,
     *  who converts external to internal sxcodes are printed on file "ptabs.h".
     *
     ***/
     
     {  short   nos,  /* number of states    */
     	        not,  /* number of terminals */
     	       *ttab; /* terminaltable       */
   
        
        if( addinfo )
        	printf("    C**function Twrt_LEStabs: started !\n");
        
        print_label( TTAB, fp, _MLES );
        
        nos  = *pt_data[9];
     	not  = *pt_data[0];
     	ttab =  pt_data[1];	 
     	
     	/***************************************************************/
        /********* print out helping vector conv  **********************/
        /***************************************************************/
        print_table( 
        	      opt_data->ttabopt.LES.convtermlist,
        	      "conv",
        	      fp,
        	      (not - 1) > MAXCHARCODE,
        	      DEC,
        	      maxterm + 1
        	    );
        
        /***************************************************************/
        /********* print out helping vector sigrowind  *****************/
        /***************************************************************/
        print_table(
        	      opt_data->ttabopt.LES.sigrowind,
        	      "sigrowind",
        	      fp,
        	      opt_data->ttabopt.LES.sigmaxrowind > MAXCHARCODE,
        	      DEC,
        	      nos
        	    );
        
        /***************************************************************/
        /********* print out helping vector sigcolind  *****************/
        /***************************************************************/
        print_table(
        	      opt_data->ttabopt.LES.sigcolind,
        	      "sigcolind",
        	      fp,
        	      opt_data->ttabopt.LES.sigmaxcolind > MAXCHARCODE,
        	      DEC,
        	      not
        	   );
         
        /***************************************************************/
        /********* print out the negated error-matrix  *****************/
        /***************************************************************/
        print_errmat( 
        	      fp, 
        	      not, 
        	      nos, 
        	      (opt_data->ttabopt.LES.sigmaxcolind + 8) >> 3,
        	      opt_data->ttabopt.LES.sigrowptr,
        	      opt_data->ttabopt.LES.sigcolptr,
        	      ttab
        	    );
        
        /***************************************************************/
        /************* print out helping vector tdecrow  ***************/
        /***************************************************************/
        print_table( 
        	     opt_data->ttabopt.LES.decrow,
        	     "tdecrow",
        	     fp,
        	     opt_data->ttabopt.LES.scans > MAXCHARCODE,
        	     DEC,
        	     nos
        	   );
        
        /***************************************************************/
        /************* print out helping vector trowval  ***************/
        /***************************************************************/
        print_LESeltab(
        	        opt_data->ttabopt.LES.rowval,
        	        opt_data->ttabopt.LES.decrow,
        	        opt_data->ttabopt.LES.scans,
        	        "trowval",
        	        fp,
        	        nos
        	      );
        	   
        /***************************************************************/
        /************* print out helping vector tdeccol  ***************/
        /***************************************************************/
        print_table( 
        	     opt_data->ttabopt.LES.deccol,
        	     "tdeccol",
        	     fp,
        	     opt_data->ttabopt.LES.scans > MAXCHARCODE,
        	     DEC,
        	     not
        	   );
        
        /***************************************************************/
        /************* print out helping vector tcolval  ***************/
        /***************************************************************/
        print_LESeltab(
        	        opt_data->ttabopt.LES.colval,
        	        opt_data->ttabopt.LES.deccol,
        	        opt_data->ttabopt.LES.scans,
        	        "tcolval",
        	        fp,
        	        not
        	      );
        
        /***************************************************************/
        /************ print out the optimized terminaltable    *********/
        /***************************************************************/
        print_LESptab( fp, TTAB, nos, not, ttab, opt_data );
        
         
      }/* Twrt_LEStabs */     				 
        				      	         




        				 		
        				 		
void Nwrt_LEStabs(fp, pt_data, opt_data, addinfo)

     FILE     *fp;         /* the filepointer to file "ptabs.h"               */
     readtype  pt_data;    /* contains all important datas of the con. parser */
     opttype  *opt_data;   /* contains allimportant datas of the optimized    */
     			   /* parsertables				      */
     char      addinfo;    /* =1, if additional informations are printed out  */
     
    /*  Prints the optimized nonterminal-table with the helping-vectors trowval,
     *  tcolval, decrow, deccol on file "ptabs.h".
     *
     ***/
     
     {  short  nos,  /* number of states       */
               non,  /* number of nonterminals */
              *ntab; /* noterminaltable        */
          
               
        if( addinfo )
        	printf("    C**function Nwrt_LEStabs: started !\n");
        
        print_label( NTAB, fp, _MLES );
        
        nos  = *pt_data[9];
     	non  = *pt_data[3];
     	ntab =  pt_data[4];
     
        /***************************************************************/
        /************* print out helping vector ndecrow  ***************/
        /***************************************************************/
        print_table( 
        	     opt_data->ntabopt.LES.decrow,
        	     "ndecrow",
        	     fp,
        	     opt_data->ntabopt.LES.scans > MAXCHARCODE,
        	     DEC,
        	     nos
        	   );
        
        /***************************************************************/
        /************* print out helping vector nrowval  ***************/
        /***************************************************************/
        print_LESeltab(
        	        opt_data->ntabopt.LES.rowval,
        	        opt_data->ntabopt.LES.decrow,
        	        opt_data->ntabopt.LES.scans,
        	        "nrowval",
        	        fp,
        	        nos
        	      );
        	   
        /***************************************************************/
        /************* print out helping vector ndeccol  ***************/
        /***************************************************************/
        print_table( 
        	     opt_data->ntabopt.LES.deccol,
        	     "ndeccol",
        	     fp,
        	     opt_data->ntabopt.LES.scans > MAXCHARCODE,
        	     DEC,
        	     non
        	   );
        
        /***************************************************************/
        /************* print out helping vector ncolval  ***************/
        /***************************************************************/
        print_LESeltab(
        	        opt_data->ntabopt.LES.colval,
        	        opt_data->ntabopt.LES.deccol,
        	        opt_data->ntabopt.LES.scans,
        	        "ncolval",
        	        fp,
        	        non
        	      );
        
        /***************************************************************/
        /*********** print out the optimized nonterminaltable    *******/
        /***************************************************************/
        print_LESptab( fp, NTAB, nos, non, ntab, opt_data );
        		
         
      }/* Nwrt_LEStabs */       	




     	        

/*============================================================================*/
/*=================            				       ===============*/
/*=================   FUNCTIONS FOR OPTIMIZATION-METHOD RDS    ===============*/
/*=================            				       ===============*/
/*============================================================================*/

void Twrt_RDStabs(fp, pt_data, opt_data, addinfo)

     FILE     *fp;         /* the filepointer to file "ptabs.h"               */
     readtype  pt_data;    /* contains all important datas of the con. parser */
     opttype  *opt_data;   /* contains allimportant datas of the optimized    */
     			   /* parsertables				      */
     char      addinfo;    /* =1, if additional informations are printed out  */
     
    /*  Prints the optimized terminal-table
     *  with helping-vector trowptr on file "ptabs.h". Further the negated and
     *  compressed error-matrix with its helping-vectors and the vector conv,
     *  who converts external to internal sxcodes are printed on file "ptabs.h".
     *
     ***/
     
     {  short    *ttab, /* terminaltable       */
     		  nos,  /* number of states    */
     		  not;  /* number of terminals */
     		  
     		 
     	if( addinfo )
     		printf("    C**function Twrt_RDStabs: started!\n");
     	
     	print_label( TTAB, fp, _MRDS );
     			
     	nos  = *pt_data[9];
     	not  = *pt_data[0];
     	ttab =  pt_data[1];	 
     	
     	/***************************************************************/
        /********* print out helping vector conv  **********************/
        /***************************************************************/
        print_table( 
        	      opt_data->ttabopt.RDS.convtermlist,
        	      "conv",
        	      fp,
        	      (not - 1) > MAXCHARCODE,
        	      DEC,
        	      maxterm + 1
        	    );
        
        /***************************************************************/
        /********* print out helping vector sigrowind  *****************/
        /***************************************************************/
        print_table(
        	      opt_data->ttabopt.RDS.sigrowind,
        	      "sigrowind",
        	      fp,
        	      opt_data->ttabopt.RDS.sigmaxrowind > MAXCHARCODE,
        	      DEC,
        	      nos
        	    );
        
        /***************************************************************/
        /********* print out helping vector sigcolind  *****************/
        /***************************************************************/
        print_table(
        	      opt_data->ttabopt.RDS.sigcolind,
        	      "sigcolind",
        	      fp,
        	      opt_data->ttabopt.RDS.sigmaxcolind > MAXCHARCODE,
        	      DEC,
        	      not
        	   );
         
        /***************************************************************/
        /********* print out the negated error-matrix  *****************/
        /***************************************************************/
        print_errmat( 
                      fp, 
        	      not, 
        	      nos, 
        	      (unsigned short)(opt_data->ttabopt.RDS.sigmaxcolind + 8) >> 3,
        	      opt_data->ttabopt.RDS.sigrowptr,
        	      opt_data->ttabopt.RDS.sigcolptr,
        	      ttab
        	    );
        	    
         /***************************************************************/
         /*****************  print out helping-vector trowptr   *********/
         /***************************************************************/
         print_rptrtab(
         		fp,
         		TTAB,
         		nos,
         		opt_data->ttabopt.RDS.rowptr
         	       );
         
         /***************************************************************/
         /*************  print the optimized terminal-table  ************/
         /***************************************************************/
         print_table(
    		       opt_data->ttabopt.RDS.ttab,
    		       "ttab",
    		       fp,
    		       YES,
    		       HEX,
    		       opt_data->ttabopt.RDS.size
    		    );
       
      }/* Twrt_RDStabs */






void Nwrt_RDStabs(fp, pt_data, opt_data, addinfo)

     FILE     *fp;         /* the filepointer to file "ptabs.h"               */
     readtype  pt_data;    /* contains all important datas of the con. parser */
     opttype  *opt_data;   /* contains allimportant datas of the optimized    */
     			   /* parsertables				      */
     char      addinfo;    /* =1, if additional informations are printed out  */
     
    /*  Prints the optimized nonterminal-table
     *  with helping-vectorntrowptr on file "ptabs.h".
     *
     ***/
     
     {  short   nos;  /* number of states       */
     		  
     		 
     	if( addinfo )
     		printf("    C**function Nwrt_RDStabs: started!\n");
     	
     	print_label( NTAB, fp, _MRDS );
     			
     	nos  = *pt_data[9];	 
     	
        /***************************************************************/
        /*****************  print out helping-vector nrowptr   *********/
        /***************************************************************/
        print_rptrtab(
        		fp,
        		NTAB,
         		nos,
         		opt_data->ntabopt.RDS.rowptr
         	     );
         
        /***************************************************************/
        /***********  print the optimized nonterminal-table  ***********/
        /***************************************************************/
        print_table(
    		       opt_data->ntabopt.RDS.ntab,
    		       "ntab",
    		       fp,
    		       YES,
    		       HEX,
    		       opt_data->ntabopt.RDS.size
    		    );

       
     }/* Nwrt_RDStabs */







/*============================================================================*/
/*=================            				       ===============*/
/*=================   FUNCTIONS FOR OPTIMIZATION-METHOD SDS    ===============*/
/*=================            				       ===============*/
/*============================================================================*/


void Twrt_SDStabs(fp, pt_data, opt_data, addinfo)

     FILE     *fp;         /* the filepointer to file "ptabs.h"               */
     readtype  pt_data;    /* contains all important datas of the con. parser */
     opttype  *opt_data;   /* contains allimportant datas of the optimized    */
     			   /* parsertables				      */
     char      addinfo;    /* =1, if additional informations are printed out  */
     
    /*  Prints the optimized terminal-table with the helping-vectors tfirstptr
     *  tlastptr and trowptr on file ptabs.h. Further the vector conv, which
     *  maps external to internal syntaxcodes is printed on file "ptabs.h".
     *
     ***/
     
     {  short    *ttab, /* terminaltable       */
     		  nos,  /* number of states    */
     		  not;  /* number of terminals */
     		  
     		 
     	if( addinfo )
     		printf("    C**function Twrt_SDStabs: started!\n");
     	
     	print_label( TTAB, fp, _MSDS );
     			
     	nos  = *pt_data[9];
     	not  = *pt_data[0];
     	ttab =  pt_data[1];	 
     	
     	/***************************************************************/
        /********* print out helping vector conv  **********************/
        /***************************************************************/
        print_table( 
        	      opt_data->ttabopt.SDS.convtermlist,
        	      "conv",
        	      fp,
        	      (not - 1) > MAXCHARCODE,
        	      DEC,
        	      maxterm + 1
        	    ); 
        	   
        /***************************************************************/
        /*********** print out helping vector tfirstptr  ***************/
        /***************************************************************/
        print_table(  
        	      opt_data->ttabopt.SDS.firstptr,
        	      "tfirstptr",
        	      fp,
        	      (not - 1) > MAXCHARCODE,
        	      DEC,
        	      nos
        	   );
        	   
        /***************************************************************/
        /************ print out helping vector tlastptr  ***************/
        /***************************************************************/
        print_table(  
        	      opt_data->ttabopt.SDS.lastptr,
        	      "tlastptr",
        	      fp,
        	      (not - 1) > MAXCHARCODE,
        	      DEC,
        	      nos
        	   );
        
        /***************************************************************/
        /*****************  print out helping-vector trowptr   *********/
        /***************************************************************/
        print_rptrtab(
         		fp,
         		TTAB,
         		nos,
         		opt_data->ttabopt.SDS.rowptr
         	     );
         
        /***************************************************************/
        /*************  print out optimized terminal-table  ************/
        /***************************************************************/
        print_SDSptab( 
                       fp,
        	       TTAB, 
        	       nos,
        	       not,  
        	       ttab,
        	       opt_data->ttabopt.SDS.firstptr,
        	       opt_data->ttabopt.SDS.lastptr
        	     );
        
        
     }/* Twrt_SDStabs */
     




void Nwrt_SDStabs(fp, pt_data, opt_data, addinfo)

     FILE     *fp;         /* the filepointer to file "ptabs.h"               */
     readtype  pt_data;    /* contains all important datas of the con. parser */
     opttype  *opt_data;   /* contains allimportant datas of the optimized    */
     			   /* parsertables				      */
     char      addinfo;    /* =1, if additional informations are printed out  */
     
    /*  Prints the optimized nonterminal-table with the helping-vector
     *  nrowptr on file "ptabs.h".
     *
     ***/
     
     {  short    *ntab, /* nonterminaltable       */
     		  nos,  /* number of states       */
     		  non;  /* number of nonterminals */
     		  
     		 
     	if( addinfo )
     		printf("    C**function Nwrt_SDStabs: started!\n");
     	
     	print_label( NTAB, fp, _MSDS );
     			
     	nos  = *pt_data[9];
     	non  = *pt_data[3];
     	ntab =  pt_data[4];	 
        	   
   
        /***************************************************************/
        /*****************  print out helping-vector nrowptr   *********/
        /***************************************************************/
        print_rptrtab(
         		fp,
         		NTAB,
         		nos,
         		opt_data->ntabopt.SDS.rowptr
         	     );
         
        /***************************************************************/
        /*************  print the optimized nonterminal-table  *********/
        /***************************************************************/
        print_SDSptab( 
        	       fp,
        	       NTAB, 
        	       nos,
        	       non,  
        	       ntab,
        	       opt_data->ntabopt.SDS.firstptr,
        	       opt_data->ntabopt.SDS.lastptr
        	     );
        
        
     }/* Nwrt_SDStabs */



 

/*============================================================================*/
/*=================            				       ===============*/
/*=================   FUNCTIONS FOR OPTIMIZATION-METHOD RCS    ===============*/
/*=================            				       ===============*/
/*============================================================================*/


void Twrt_RCStabs(fp, pt_data, opt_data, addinfo, mrginfo )

     FILE     *fp;         /* the filepointer to file "ptabs.h"               */
     readtype  pt_data;    /* contains all important datas of the con. parser */
     opttype  *opt_data;   /* contains allimportant datas of the optimized    */
     			   /* parsertables				      */
     char      addinfo,    /* =1, if additional informations are printed out  */
               mrginfo;    /* if =1, equal rows are merged                    */
     
    /*  Prints the optimized terminal-table with the helping-vectors trowind
     *  and trowprt on file ptabs.h.
     *
     ***/
     
     {	short   *termlist,/* list to convert internal to external sxcode */
     		*ttab,    /* notoptimized terminal-table                 */
     		 nos,     /* number of states                            */
     		 not;     /* number of terminals                         */
     		 
     		 
        if( addinfo )
        	printf("    C**function Twrt_RCStabs: started !\n");

        
        ttab       =   pt_data[1];
        not        =  *pt_data[0];
        nos        =  *pt_data[9];
        termlist   =   pt_data[2]; 
     	
     	if( mrginfo ) {
     	
     	    print_label( TTAB, fp, _MRCSB );

     	    /***************************************************************/
            /*************  print the optimized terminal-table  ************/
            /***************************************************************/
            print_RCSBptab(
   			    fp,
   			    TTAB,
   			    nos,
   			    not,
   			    ttab,
   			    opt_data->ttabopt.RCS.rowptr,
   			    termlist
   		          );
        		
            /***************************************************************/
            /*****************  print helping-vector tbase   ***************/
            /***************************************************************/
            print_RCSBbase(
         		    fp,
         		    TTAB,
         		    nos,
         		    not,
         		    ttab,
         		    opt_data->ttabopt.RCS.rowptr
         	          );
     		 
            /***************************************************************/
            /*****************  print helping-vector trpt  *****************/
            /***************************************************************/
     	    print_table(
     		         opt_data->ttabopt.RCS.rowind,
     		         "trpt",
     		         fp,
     		         opt_data->ttabopt.RCS.maxrowind > MAXCHARCODE,
     		         DEC,
     		         nos
     		       );
     	 }
     	 else  {
     	 
     	     print_label( TTAB, fp, _MRCSA );
  
     	     /**************************************************************/  
     	     /************** print out the terminaltable *******************/
             /**************************************************************/
             print_RCSAptab( fp, TTAB, nos, not, ttab, termlist );
                        
             /**************************************************************/
             /************** print out helping vector tbase ****************/
             /**************************************************************/
             print_RCSAbase( fp, TTAB, nos, not, ttab );
             
         }

      }/* Twrt_RCStabs */
      



      
     		 
     	
void Nwrt_RCStabs(fp, pt_data, opt_data, addinfo, mrginfo)

     FILE     *fp;         /* the filepointer to file "ptabs.h"               */
     readtype  pt_data;    /* contains all important datas of the con. parser */
     opttype  *opt_data;   /* contains allimportant datas of the optimized    */
     			   /* parsertables				      */
     char      addinfo,    /* =1, if additional informations are printed out  */
               mrginfo;    /* if =1, equal rows are merged                    */
     
    /*  Prints the optimized nonterminal-table with the helping-vectors nrowind
     *  and nrowprt on file ptabs.h.
     *
     ***/
     
     {  short   *ntab,    /* notoptimized terminal-table */
     		 nos,     /* number of states            */
     		 non;     /* number of nonterminals      */
     		 
     		 
        if( addinfo )
        	printf("    C**function Nwrt_RCStabs: started !\n");
        
        
        nos  = *pt_data[9];
     	non  = *pt_data[3];
     	ntab =  pt_data[4];
     	
     	if( mrginfo ) {
     	    
     	    print_label( NTAB, fp, _MRCSB );
     	
     	    /***************************************************************/
            /*************  print the optimized nonterminal-table  *********/
            /***************************************************************/
            print_RCSBptab(
   			   fp,
   			   NTAB,
   			   nos,
   			   non,
   			   ntab,
   			   opt_data->ntabopt.RCS.rowptr,
   			   NULL
   		          );
             
            /***************************************************************/
            /*****************  print helping-vector nbase   ***************/
            /***************************************************************/
            print_RCSBbase(
         		   fp,
         		   NTAB,
         		   nos,
         		   non,
         	           ntab,
         		   opt_data->ntabopt.RCS.rowptr
         	          );
     		 	 
            /***************************************************************/
            /*****************  print helping-vector nrpt  *****************/
            /***************************************************************/
       	    print_table(
     		         opt_data->ntabopt.RCS.rowind,
     		         "nrpt",
     		         fp,
     		         opt_data->ntabopt.RCS.maxrowind > MAXCHARCODE,
     		         DEC,
     		         nos
     		       );
         }
         else {
         
            print_label( NTAB, fp, _MRCSA );
         
            /*****************************************************************/
            /**************** print out the nonterminaltable *****************/
            /*****************************************************************/
            print_RCSAptab( fp, NTAB, nos, non, ntab, NULL );
         
            /*****************************************************************/
            /**************** print out helping vector nbase *****************/
            /*****************************************************************/
 	    print_RCSAbase( fp, NTAB, nos, non, ntab );
 	 
 	 }
     	
      }/* Nwrt_RCStabs */        
     	

