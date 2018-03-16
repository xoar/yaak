static char RCSid[] = "$Id: mapper.c,v 1.7 2004/08/01 01:44:25 profw Exp $";
/*##############################################################################

FUNNNELWEB COPYRIGHT
====================
FunnelWeb is a literate-programming macro preprocessor.

Copyright (C) 1992 Ross N. Williams.

   Ross N. Williams
   ross@spam.adelaide.edu.au
   16 Lerwick Avenue, Hazelwood Park 5066, Australia.

This program is free software; you can redistribute it and/or modify
it under the terms of Version 2 of the GNU General Public License as
published by the Free Software Foundation.

This program is distributed WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See Version 2 of the GNU General Public License for more details.

You should have received a copy of Version 2 of the GNU General Public
License along with this program. If not, you can FTP the license from
prep.ai.mit.edu/pub/gnu/COPYING-2 or write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

Section 2a of the license requires that all changes to this file be
recorded prominently in this file. Please record all changes here.

Programmers:
   RNW  Ross N. Williams  ross@spam.adelaide.edu.au
   AMS  Tony Sloane	  asloane@comp.mq.edu.au
   WMW  William Waite	  William.Waite@Colorado.edu

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   26-Jul-1992  AMS  Added RCS id.
   18-Dec-1992  WMW  Cast the results of mm_perm to avoid pointer
                     incompatibility.
   27-Mar-2003	WMW  Changed stan_map to standardize newlines regardless
		     of the file format

##############################################################################*/


/******************************************************************************/
/*                                   MAPPER.C                                 */
/******************************************************************************/

#include <limits.h>
#include "style.h"

#include "as.h"
#include "machin.h"
#include "mapper.h"
#include "memory.h"

/******************************************************************************/

/* When we allocate a block of memory for a mapped file, we have to allocate  */
/* a little more than the official length of the file. Here are some reasons: */
/*                                                                            */
/*    - We may wish to append an EOF character later on in the program.       */
/*    - fgets, when requested to fetch n characters, fetches n characters and */
/*      then puts an EOS on the end of them.                                  */
/*    - It is conceivable that fgets will insert a "\n" at the end of the     */
/*      block if it doesn't see a "\n" just before the end of file.           */
/*                                                                            */
/* For all these reasons, we allocate a little more memory than we need. How  */
/* much more is determined by BLK_FUDGE which is set to be on the safe side.  */
#define BLK_FUDGE (20)

/* The following fudge is useful for avoiding the limits of types.            */
#define LIM_FUDGE (10)

/* On PCs, size_t is 16 bits and malloc cannot allocate contiguous chunks of  */
/* memory of more than about 64K. This really stuffs up FunnelWeb's capacity  */
/* map in files of length greater than 64K. I didn't think of this problem    */
/* when I designed FunnelWeb because I was thinking of the VOLUME of memory   */
/* available nowadays, rather than its organization on small computers.       */
/* Anyway, this problem should really be fixed by allowing files to be read   */
/* in in segments. Perhaps the mapper should hand over a linked list of       */
/* chunks rather than a single chunk. Unfortunately, I don't have the time to */
/* do this now, so users of the PC version of FunnelWeb will have to be       */
/* content with an (approx) 64K limit to input files. This isn't as bad as it */
/* sounds, as large input files can be split using the include facility.      */
/* 63K is chosen instead of 64K so as to be paranoid.                         */
#define PCFILEMX  (63L*1024L)

/******************************************************************************/
/*                                                                            */
/* Error Strings                                                              */
/* -------------                                                              */
/* Routines in this package return pointers to error strings. These pointers  */
/* are subsequently bandied about by other packages. Therefore, they must be  */
/* pointers to constant strings. The trick of returning a pointer to a static */
/* character array containing a specific sprintf message will backfire here   */
/* if there is an error opening more than one input file. Using mm_* to       */
/* create space for each error string would work though.                      */
/* STOP PRESS: Now that the lister copies error messages, there may no longer */
/* be a problem here.                                                         */
/*                                                                            */
/******************************************************************************/

/* Finding The Length of a File                                               */
/* ----------------------------                                               */
/* We have to be able to find out the length of a file before reading it in   */
/* because, in this version of FunnelWeb, the entire file must be read into   */
/* one contiguous block of memory.                                            */
/*                                                                            */
/* As it turns out, finding the length of a file in portable C turns out to   */
/* be a very hard problem. Here are some possible solutions:                  */
/*                                                                            */
/*    1. Read the entire file in and see how long it is.                      */
/*    2. Use fseek to move to the end of the file and then use ftell.         */
/*    3. Use the Unix 'stat' call.                                            */
/*                                                                            */
/* Of these, only the first is portable. The second alternative is            */
/* non-portable because some environments do not support the SEEK_END symbol  */
/* required to perform a seek to the end of file.                             */
/* Alternatives to needing the length are as follows:                         */
/*                                                                            */
/*    4. Read the file/allocate memory in 64K blocks.                         */
/*    5. Read the file in 64K blocks and then copy them to a contiguous one.  */
/*                                                                            */
/* Perhaps options 4 or 5 could be implemented later. However, right now I    */
/* haven't got the time to do anything except strive for portability, so      */
/* option 1 it is.                                                            */

LOCAL char *file_len P_((char *,ulong *));
LOCAL char *file_len (p_name,p_length)
/* Given a filename (in 'p_name'), returns the length of the binary image of  */
/* the file in *p_length. Returns NULL upon success or a pointer to a string  */
/* describing an error upon failure. The length is measured in bytes.         */
char  *p_name;
ulong *p_length;
{
 FILE *infile;
 STAVAR char *p_buf = NULL;
 
/* The length of the buffer handed to fgets is non-critical. However, it      */
/* mustn't be bigger than 15 bits, as we are passing it as an int to fgets.   */
#define LENBUFLEN (1024L)
#if LENBUFLEN > 30000L
   #error "mapper.c: LENBUFLEN must be less than 15 bits."
#endif

 /* Allocate the buffer if it has not already been allocated. */
 if (p_buf == NULL)
    p_buf=(char *)mm_perm((size_t) LENBUFLEN);

 /* Open for TEXT reading. Earlier, I tried this using a binary read, but     */
 /* I had problems with this on the VAX (I forget what the problems were) and */
 /* so I have switched back to a text read which is slower, but more reliable.*/
 infile=fopen(p_name,"r");
 if (infile == FOPEN_F)
    return "Error fopen()ing input file (to determine its length).";

 /* Start with a zero length. */
 *p_length=0;

 /* Read the file as text and count the number of bytes it contains. */
 while (!feof(infile))
   {
    /* Set the buffer to the empty string so it is valid even if fgets fails. */
    p_buf[0]=EOS;
    
    /* Read in a whole lot of bytes. */
    fgets(p_buf,LENBUFLEN,infile);
    
    /* If there is an error, abort. */
    if (ferror(infile))
      {
       fclose(infile);
       return "Error fgets()ing input file (as part of determining its length).";
      }
      
    /* Count the bytes that we have got. If EOF occurred above AND no bytes   */
    /* were read, the EOS we planted earlier saves us.                        */
    (*p_length)+=strlen(p_buf);
   }

 if (fclose(infile) == FCLOSE_F)
    return "Error fclose()ing input file (as part of determining its length).";

 return NULL;
}

/******************************************************************************/

#if PC & UNIX_EOL
   #error Attempt to use unix_map function on a PC!
#endif

#if UNIX_EOL
LOCAL char *unix_map P_((char *,char **,ulong *));
LOCAL char *unix_map(p_name,pp_mem,p_length)
/* If we know that the enclosing environment represents text files in UNIX    */
/* form, then there is no need to process the file on the way in. All we need */
/* to do is map it directly into memory. This will be very fast.              */
char   *p_name;
char  **pp_mem;
ulong  *p_length;
{
 ulong  file_length;  /* Number of bytes in the target input file.            */
 char  *p_err;        /* Temporary to store pointer to error message.         */
 FILE  *infile;       /* The file variable for the input file we are reading. */
 ulong  num_bytes;    /* Number of bytes actually read in (may be different). */
 char  *p_bytes;      /* Pointer to the memory block where all the action is. */

 /* Obtain the length of the file we are about to map in. */
 p_err=file_len(p_name,&file_length);
 if (p_err != NULL)
    return p_err;
 
 /* Allocate memory to hold the mapped file.                                  */
 /* Note: The memory allocation package bombs if there is no more memory.     */
 p_bytes=(char *) mm_temp((size_t) file_length+BLK_FUDGE);

 /* Open the file in BINARY mode. */
 infile=fopen(p_name,"rb");
 if (infile==FOPEN_F)
    return "Error fopen()ing the input file (binary open).";

 /* Read in the file and complain if we haven't read in enough bytes. */
 num_bytes=fread(p_bytes,(size_t) 1L,(size_t) file_length,infile);
 if (num_bytes != file_length)
    return "Error fread()ing the input file.";

 if (fclose(infile) == FCLOSE_F)
    return "Error fclose()ing the input file.";

 /* Success. We got through the IO calls. Now fill in the blanks and go home. */
 *pp_mem   =p_bytes;
 *p_length =num_bytes;
 return NULL;
}
#endif

/******************************************************************************/

#if !UNIX_EOL
LOCAL char *stan_map P_((char *,char **,ulong *));
LOCAL char *stan_map(p_name,pp_mem,p_length)
/* Maps in a file using refined text stream IO calls. */
char   *p_name;
char  **pp_mem;
ulong  *p_length;
{
 ulong  file_length;  /* Number of bytes in the target input file.            */
 char  *p_err;        /* Temporary to store pointer to error message.         */
 FILE  *infile;       /* The file variable for the input file we are reading. */
 ulong  num_bytes;    /* Number of bytes actually read in (may be different). */
 char  *p_bytes;      /* Pointer to the memory block where all the action is. */
 char  *p_curr;       /* Pointer to current position in memory block.         */
 long  bytes_left;    /* Number of bytes still left to read.                  */

 /* Obtain the length of the file we are about to map in. */
 p_err=file_len(p_name,&file_length);
 if (p_err != NULL)
    return p_err;

 /* Complain on the PC if the file is too big to fit in one 64K segment. */
#if PC
 if (file_length+BLK_FUDGE > PCFILEMX)
    return
      "Error: Input file too big for PC FunnelWeb. Split using include files.";
#endif

 /* TRACE printf("MAPPER: LENGTH OF INPUT FILE=%lu\n",file_length); */
 
 /* Allocate memory to hold the mapped file.                                  */
 /* Note: The memory allocation package bombs if there is no more memory.     */
 /* Note: As Unix stream format (the format to which we are converting) uses  */
 /*       just one byte to mark the end of file, it seems highly unlikely     */
 /*       that the file read in will be longer than the binary image.         */
 p_bytes=(char *) mm_temp((size_t) file_length+BLK_FUDGE);

 /* If the file is of zero length, we already know its contents!              */
 /* This is probably not strictly necessary, but why pressure the code below? */
 if (file_length==0)
   {
    *pp_mem   = p_bytes;
    *p_length = 0;
    return NULL;
   }

 /* Open the file afresh in TEXT mode for portable reading. */
 infile=fopen(p_name,"r");
 if (infile==FOPEN_F)
    return "Error fopen()ing input file (for reading).";

 /* Read in as much of the file as we can without actually overflowing the    */
 /* buffer. If the file finished before the buffer, things have probably gone */
 /* OK. If the buffer finishes before the file, we have a problem.            */
 /* Note: bytes_left = file_length+1 because in the following loop, we might  */
 /* read exactly up to the EOF and then be unable to actually trigger the EOF */
 /* condition without another read. So we add one on to allow this extra read */
 /* to take place. I don't know if this is necessary, but I certainly can't   */
 /* find anything in all my C books that will tell me. Anyway, it doesn't     */
 /* matter because we fudged in a few extra bytes earlier.                    */

 p_curr     = p_bytes;        /* p_curr runs through the memory.              */
 bytes_left = file_length+1;  /* Bytes left in memory allocated to hold file. */
 
 while (!feof(infile))
   {
    int bytes_try;
    int bytes_read;
    
    /* Try to read as much as we possibly can, but not more than the integer  */
    /* limit (which can be as low as 15 bits).                                */
    bytes_try = bytes_left >= ((ulong) (INT_MAX-LIM_FUDGE)) ?
                  (int) INT_MAX-LIM_FUDGE : (int) bytes_left;
    
    /* Plan an EOS to cover the EOF case. */
    *p_curr=EOS;
    
    /* Attempt to read bytes_try bytes. +1 is because fgets reads n-1 bytes.  */
    fgets(p_curr,bytes_try+1,infile);
    if (ferror(infile))
      {
       fclose(infile);
       return "Error fgets()ing the input file.";
      }
      
    /* fgets doesn't return a length so we have to hobble behind with strlen. */
    /* It's still probably better than using lots of fgetc calls.             */
    /* If we hit EOF and no bytes were read, the EOS we planted saves us.     */
    /* bytes_read  = strlen(p_curr);                                          */
    /* p_curr     += bytes_read;                                              */
    /* WMW -- Replace the lines above with the following standardization code */
    for (bytes_read = 0; *p_curr != EOS; bytes_read++) {
      if (p_curr[0] == '\r') {
        p_curr[0] = EOL;
        if (p_curr[1] == EOL) p_curr[1] = EOS;
      }
      p_curr++;
    }
    bytes_left -= bytes_read;

    /* If we have run out of bytes in our allocated memory zone, then the     */
    /* file is longer than the length reported earlier. This is a bad thing.  */
    as_cold(bytes_left >=0,
            "stan_map: Text representation was longer than binary rep.");
   }
   
 num_bytes=(file_length+1)-bytes_left; /* See earlier to undserstand +1.      */
 
 /* Note: We can't get fussy here and check the read in length with the       */
 /* official length, as the read-in length is the text representation which   */
 /* is allowed to be shorter than the physical (binary) length of the file.   */

 if (fclose(infile) == FCLOSE_F)
    return "Error fclose()ing input file.";

 /* Success. We got through the IO calls. Now fill in the blanks and go home. */
 *pp_mem   = p_bytes;
 *p_length = num_bytes;
 return NULL;
}
#endif

/******************************************************************************/

EXPORT char *map_file(p_name,pp_mem,p_length)
char   *p_name;
char  **pp_mem;
ulong  *p_length;
{
 /* We choose one of two mapper routines depending on where the operating     */
 /* system represents text files using EOL (\n) as end of line markers.       */
 /* The UNIX_EOL symbol is defined in the machin.h file.                      */
 /* Note: I thought of using sprintf to test to see what "\n" translated into */
 /* so I wouldn't need the UNIXEOL symbol. However, unlike printf (which it   */
 /* is supposed to be like), sprintf does not translate "\n" into its outside */
 /* form. The only other alternative is writing a short text file and reading */
 /* it back in binary - an action that would probably take longer than        */
 /* reading the original file to be read using fgetc()!                       */

#if UNIX_EOL
   return unix_map(p_name,pp_mem,p_length);
#else
   return stan_map(p_name,pp_mem,p_length);
#endif
}

/******************************************************************************/
/*                               End of MAPPER.C                              */
/******************************************************************************/

