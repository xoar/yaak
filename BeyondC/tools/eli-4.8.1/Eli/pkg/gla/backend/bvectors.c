static char RCSid[] = "$Id: bvectors.c,v 1.8 2009/08/23 19:33:44 profw Exp $";
/* Copyright, 1989, The Regents of the University of Colorado */

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

#include "dj.h"
 
#define bool int
#define BITSperBYTE 8
 
static unsigned char *ScanTbl = NULL;    /* The Scan Table. */
static int TableNum = 0;                 /* The # of Scan Table sections. */


/*******************************************************************************
 *
 *  createSet -- Takes a vector and inserts it in the Scan Table.  Returns
 *               the table section number and the bit offset in the table
 *               section (each section is 8 bits wide).  We don't use 32 bit
 *               longs because of endian byte order differs on machines.
 *
 *  Inputs -- SetArray, an array of length SETSIZE, each element of which is
 *            either a zero or a one.
 *
 *  Outputs -- bitOff, the bit offset within a table section.
 *
 *             tblOff, the table section number.
 *
 *             returns a zero if a new vector was inserted, a one if the
 *             table offset and bit offset of an existing vector was
 *             returned (compaction feature).
 *
 *  Notes -- 
 *
 *  Calls --
 *
 *******************************************************************************/

int createSet(SetArray, bitOff, tblOff)
   char *SetArray;
   int *bitOff;
   int *tblOff;
{
   static int BitPoss = 0;       /* Current bit position. */
   static bool expand = TRUE;    /* New table section needs to be added. */
   int I;
   int J;
   int K;
   bool match;                   /* Identical existing vector found. */
   bool compact = FALSE;         /* Existing vector coordinates returned. */


                                 /************************************************
                                  *                                              *
                                  * New table section generated and initialized. *
                                  *                                              *
                                  ************************************************/
   if (expand)
     {
      if (ScanTbl == NULL)
         ScanTbl = (unsigned char *)
                   malloc( (unsigned) SETSIZE * sizeof(unsigned char));
      else
         ScanTbl = (unsigned char *)
                   realloc( (char *) ScanTbl, (unsigned) ((TableNum + 1)
                                                  * SETSIZE * sizeof(char)));
      if(ScanTbl == NULL)
         {
          printf("cannot allocate memory\n");
          exit(1);
        }
      for (I = TableNum * SETSIZE; I < ((TableNum +1) * SETSIZE); I++)
         ScanTbl[I] = (unsigned char) 0;
      expand = FALSE;
    }


                                 /*************************************************
                                  *                                               *
                                  * Incoming vector inserted at current position. *
                                  *                                               *
                                  *************************************************/

   for (I = 0; I < SETSIZE; I++)
      if (SetArray[I])
         ScanTbl[TableNum * SETSIZE + I] |= (unsigned char) 1 << BitPoss;


                                 /*****************************************
                                  *                                       *
                                  * Search for identical existing vector. *
                                  *                                       *
                                  *****************************************/

   I = 0;
   J = 0;
   if (TableNum != 0 || BitPoss != 0)
      do
        {
         match = TRUE;
         K = 0;
         do
           {
            if (((ScanTbl[(I * SETSIZE) + K] >> J) & (unsigned char) 1)
                  != ((ScanTbl[TableNum * SETSIZE + K] >> BitPoss)
                        & (unsigned char) 1))
               match = FALSE;
            K++;
          }
         while (match && (K < SETSIZE));
         if (!match)
           {
            J++;
            if (J == BITSperBYTE)
              {
               I++;
               J = 0;
              }
           }
       }
      while (!match && (I < TableNum || J < BitPoss));


                                 /********************************************
                                  *                                          *
                                  * If identical vector found compact table. *
                                  *                                          *
                                  ********************************************/

   if (I < TableNum || J < BitPoss)
     {
      for (K = 0; K < SETSIZE; K++)
         ScanTbl[TableNum * SETSIZE + K] &= ~((unsigned char) 1 << BitPoss);
      compact = TRUE;
    }
   else
     {
      BitPoss++;
      if (BitPoss == BITSperBYTE)
        {
         TableNum++;
         BitPoss = 0;
         expand = TRUE;
       }
    }


                                 /*******************
                                  *                 *
                                  * Return results. *
                                  *                 *
                                  *******************/
   
   *bitOff = J;
   *tblOff = I;
   return compact;
 }



/*******************************************************************************
 *
 *  out ScanTbl -- Writes out the Scan Table to file Ft.
 *
 *  Inputs -- None.
 *
 *  Outputs -- writes c declaration of Scan Table to file whose handle is Ft.
 *
 *  Notes -- 
 *
 *  Calls --
 *
 *******************************************************************************/
 

void outScanTbl()
{
   int I;
   (void) fprintf(Ft, "\nstatic unsigned char ScanTbl[] = {\n");
 
   for (I = 0; I < SETSIZE * (TableNum + 1) - 4; I += 4){
      (void) fprintf(Ft, "0x%02X, 0x%02X, 0x%02X, 0x%02X,\n",
      ScanTbl[I], ScanTbl[I + 1], ScanTbl[I + 2], ScanTbl[I + 3]);
      }
   (void) fprintf(Ft, "0x%02X, 0x%02X, 0x%02X, 0x%02X };\n",
                       ScanTbl[SETSIZE * (TableNum + 1) - 4],
                       ScanTbl[SETSIZE * (TableNum + 1) - 3],
                       ScanTbl[SETSIZE * (TableNum + 1) - 2],
                       ScanTbl[SETSIZE * (TableNum + 1) - 1]);



#ifdef diagnostics
   fprintf(Ft, "/*\n7\t3 2 1 0\n");
   for (I = 0; I < SETSIZE * (TableNum +1); I++)
     {
      for (J = 0; J < BITSperBYTE; J++)
        {
         if (ScanTbl[I] & ((unsigned char) 1 << (BITSperBYTE-1 - J)))
            K = 1;
         else
            K = 0;
         (void) fprintf(Ft, "%d ", K);
        }
      GPNT(Ft, I, "    ", "\n");
     }
   fprintf(Ft, "  */\n");
#endif
}
