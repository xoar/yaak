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
static char RCSid[] = "$Id: source.c,v 4.3 1998/04/28 14:23:01 ludi Exp $";


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

#include "source.h"

#define READSIZ 4096	/* primitive I/O in this size bytes */
#define MAXLINE 256	/* Initial guess at maximum line length */
/* Source text buffering.
 * Designed to be fast! And guarantee that full lines are always in memory.
 * The idea is to read many lines into READBUF.  There might be the head
 * of a partial line at the end of the buffer.  Scan in reverse from the
 * end of the buffer, looking for the last newline. Save the character
 * AFTER the newline, and zap its position with NUL.  (An extra position
 * is reserved in the buffer in case the last newline is the last character
 * read.)  If there is no newline in the buffer, then extend the buffer and
 * read another block of input.  If the end of the file is reached without
 * reading a newline, then supply one at the end of the input data.
 *
 * Client routines of the source module can assume that a complete line,
 * with its terminating newline, is in the buffer.  After processing that
 * line, they must check the character following the newline.  If it is
 * NUL, refillBuf must be called.  Otherwise it is guaranteed that the next
 * line, with its associated newline, is also in the buffer.
 *
 * When refillBuf is called, the head of any partial line remaining in the
 * buffer is copied to an area in front of the buffer, and the buffer is
 * refilled.  The buffer will then contain the tail of the partial line,
 * possibly one or more full lines, and possibly another partial line.
 *
 * refillBuf(p) is called when the last character in the buffer is
 * reached.  This is known because *p == NUL.  The argument p is
 * used only for assertion checking.  It must be pointing at the last
 * character of the buffer -- that is, the one is NUL and signals the end.
 * Upon return, TokenEnd will be set to the next character of the file.
 *
 * The source module guarantees that whole lines will be available in
 * the buffer.  The input file is assumed to be ascii, with no embedded NULs.
 * Each line must be newline terminated.  Because we can't predict the
 * size of the largest line, the buffer must be able to grow.  Two
 * variables, maxline and readsiz, define the current buffer size.  These
 * variables are initialized to MAXLINE and READSIZ respectively.
 *
 *   memblock		 READBUF
 *       |		 |
 *	|---------------|---------------------------------------------------|
 *	| <--maxline-->	|  <--------readsiz ----------------------------->  |
 *	|	^	|				^	^	    |
 *	|TokenEnd	|			     charend  READBUF+count |
 *	|-------------------------------------------------------------------|
 *
 */

/* Exported variables: updated by source module, and scanners */

#define NAMSIZ 250
char SourceName[NAMSIZ] = {0};	/* to remember the name of file */
int LineNum = 1;                /* source line number */
char *StartLine=0;      	/* pointer to beginning of line */
char *TokenStart;
char *TokenEnd;


static char sentinelSav;	/* Character replaced by a sentinel */
static char *memblock;		/* Storage area */
static int maxline = MAXLINE;	/* reads occur at this offset */
#define READBUF (memblock+maxline)
static int readsiz = READSIZ;	/* Number of bytes in the read buffer */
static char *charend;		/* delimits boundary between useful lines
				   and a last partial line */
static int EndOfFile;		/* Nonzero when the end of the file has
				   been seen */
static int count;		/* number of bytes read */
static int fd;
#define NUL '\0'		/* the ASCII nul character */

#if defined(__cplusplus) || defined(__STDC__)
int
FullLine(char *p)
#else
int
FullLine(p)
char *p;
#endif
/* Test whether new information read contains a newline
 *   On entry-
 *     p addresses the first new character
 *     READBUF+count addresses the first unfilled position
 *   If the new information contains a newline then on exit-
 *     FullLine != 0
 *     charend points to the position after the last newline
 *   Otherwise on exit-
 *     FullLine == 0
 **/
{
  register char *q = READBUF + count;
  char save;

  save = p[-1]; p[-1] = '\n';
  while (*(--q) != '\n') ;
  p[-1] = save;
  charend = q + 1;
  return *q == '\n';
}

#if defined(__cplusplus) || defined(__STDC__)
void
refillBuf(char *p)
#else
void
refillBuf(p)
char *p;
#endif
{
  if( SourceName[0] == 0 )  /* make sure initBuf was called first!! */
    (void)fprintf(stderr,"Source module never initialized with initBuf\n");

	/* refillBuf only called when necessary and file doesn't contain NUL */
  if( p != charend ){	/* make sure user and I agree on the end */
   (void)fprintf(stderr,"refillBuf:sentinel problem, may be NUL in file\n");
   TokenEnd = p+1;	/* skip over unexpected null */
   return;
  }

  /* Calculate new beginning of buffer:
   * 		 ...# chars to be copied.............  ALGEBRA
   * TokenEnd = READBUF - (READBUF+count-1 - charend + 1)
   * TokenEnd = READBUF - (READBUF+count   - charend    )
   * TokenEnd = READBUF -  READBUF-count   + charend 
   */
  TokenEnd = 			  -count   + charend;

  if(charend <= READBUF+count-1) {  /* need to copy down bytes */
    /* Copy backwards and let NUL byte terminate loop,
     * then replace this NUL with the saved character.
     *
     *		|<---------------READBUF------------>
     *		|	charend
     *		|	|
     *		|	0ABC	upon entry to refillBuf
     *	    0ABC|		after copy down
     *	    sABC|		after replacing nul with char s
     *      ^    
     *      TokenEnd
     */
    register char *src = READBUF+count;		/* one beyond */
    register char *dest = READBUF;		/* one beyond */

    if( charend <= READBUF+count-maxline) {	/* re-size buffer */
    	char *temp = memblock;

    	maxline = READBUF + count - charend;
    	memblock = (char *)malloc((unsigned)(maxline+readsiz+1));
    	dest = READBUF;
    	while(( *--dest = *--src)) ;
    	(void)free(temp);
    } else while(( *--dest = *--src)) ;

    *dest = sentinelSav;
    TokenEnd = dest;
  }

  /* Obtain more input information.  The additional input is concatenated
   * to the partial line by virtue of where it is read.
   */
  if (EndOfFile) count = 0;
  else if ((count = read(fd, READBUF, readsiz)) == 0) EndOfFile = 1;
  if (count < 0) {
    (void)fprintf(stderr, "refillBuf: Error reading file %s\n", SourceName);
    perror("refillBuf");
    exit(1);
  }

  /* Guarantee that if the buffer contains any information at all, then
   * there is at least one newline.
   */
  if (count == 0) {	/* No new information was read into the buffer */
    if (TokenEnd != READBUF) {	/* Terminate the unprocessed information */
      READBUF[0] = '\n'; count = 1;
    }
    charend = READBUF + count;
  } else {		/* New information was read into the buffer */
    char *start = READBUF;
    int text = TokenEnd - memblock;

    while (!FullLine(start)) {	/* Read more information */
      int newcount;

      readsiz += READSIZ;	/* Obtain space for another block */
      if (!(memblock = (char *)realloc(memblock, (unsigned)(maxline+readsiz+1)))) {
         (void)fprintf(stderr, "refillBuf: memory exhausted\n");
         exit(1);
      }

      start = READBUF + count;	/* Read the block */
      if ((newcount = read(fd, start, READSIZ)) == 0) {
        /* If end-of-file has been reached, terminate the buffer */
        EndOfFile = 1; *start = '\n'; newcount = 1;
      }
      count += newcount;
    }
    TokenEnd = memblock + text;
  }

  /* Mark the end of the information in the buffer by planting a NUL after
   * the last newline.
   */
  sentinelSav = *charend; *charend = NUL;
}


#if defined(__cplusplus) || defined(__STDC__) 
void
initBuf(const char *name, int f)
#else
void
initBuf(name, f)
char *name; int f;
#endif
/* Set to the first source text line
 *    On entry-
 *       name=name of the file to be processed
 *       f=file descriptor of the file to be processed
 *    On exit-
 *       If the source text is empty then on exit-
 *           TokenEnd addresses a location containing the null character
 *	 else
 *           TokenEnd addresses the first character of the line
 ***/
{
  fd = f;
  (void)strncpy(SourceName,name,NAMSIZ);
  memblock = (char *)malloc((unsigned)(maxline+readsiz+1)); /* one extra
  			in case the last character read is a newline
  			(then we want to zap the next location) */
  EndOfFile = 0;		/* no end-of-file read */
  count=0;		/* no characters have been previously read */
  *READBUF = '\0';	/* in case of empty file */
  TokenEnd = charend = READBUF;  /* make refillBuf happy */
  refillBuf(TokenEnd);
  StartLine = TokenEnd - 1;	/* initialize the start of line 1 */
  LineNum = 1;
}
