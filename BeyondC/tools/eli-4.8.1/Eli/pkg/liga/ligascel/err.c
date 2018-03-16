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

static char RCSid[] = "$Id: err.c,v 4.3 1998/04/28 14:23:01 ludi Exp $";

#include <stdio.h>
#include <string.h>
#include "err.h"
#include "source.h"


	/* The following variables are exported by the Error Reporting
	   Module */

POSITION curpos = { 0, 0}; /* Current source Msgtext position */
int ErrorCount[] = {0, 0, 0, 0, 0, 0}; /* Counts at each severity level */

static char *key[]= {"NOTE", "COMMENT", "WARNING", "ERROR", "FATAL", "DEADLY"};

struct msg {
        int severity;
        POSITION loc;
        int grammar;
        char *Msgtext;
        struct msg *forward, *back;
};


static struct msg reports = {   /* Error report list */
        DEADLY, {0, 0}, 0, "",
        &reports, &reports};

static struct msg emergency;    /* In case malloc fails */

static int ImmediateOutput = 1;	/* 1 if immediate error output required */
static int GrammarLine = 1;	/* 1 to print AG line number */
static int ErrorLimit = 1;	/* 1 to abort after too many errors */

#if defined(__cplusplus) || defined(__STDC__)
void
ErrorInit(int ImmOut, int AGout, int ErrLimit)
#else
ErrorInit(ImmOut, AGout, ErrLimit)
int ImmOut, AGout, ErrLimit;
#endif
/* Initialize the error module
 *    On entry-
 *       ImmOut=1 if immediate error output required
 *       AGout=1 to print AG line number on error reports
 *       ErrLimit=1 to limit the number of errors reported
 ***/
{
	ImmediateOutput = ImmOut;
	GrammarLine = AGout; 
	ErrorLimit = ErrLimit;

	reports.severity = DEADLY;
	reports.loc.line = reports.loc.col = 0;
	reports.grammar = 0; reports.Msgtext = "";
	reports.forward = reports.back = &reports;
}

#if defined(__cplusplus) || defined(__STDC__)
void
dmperr(FILE *d)
#else
void
dmperr(d)
FILE *d;
#endif
/* Dump the error reports to a Msgtext file
 ***/
{
        struct msg *r;
 
        r = reports.forward;
        while (r->loc.line != 0) {
                (void)fprintf(d, "%d", r->severity);
		(void)fprintf(d," (%d,%d)",r->loc.line,r->loc.col);
                (void)fprintf(d, " %d %s\n", r->grammar, r->Msgtext);
                r = r->forward;
        }
}
 

#if defined(__cplusplus) || defined(__STDC__) 
int
earlier(POSITION *p, POSITION *q)
#else
int
earlier(p,q)
POSITION *p, *q;
#endif
/* Check relative position
 *    On exit-
 *       earlier != 0 if p defines a position in the source Msgtext that
 *          preceeds the position defined by q
 ***/
{
        if (p->line != q->line) return(p->line < q->line);
        return(p->col < q->col);
}



#ifndef NOLISEDIT
/***/
#if defined(__cplusplus) || defined(__STDC__) 
void
lisedit(char *name, FILE *stream, int cutoff, int erronly)
#else
void
lisedit(name, stream, cutoff, erronly)
char *name; FILE *stream; int cutoff, erronly;
#endif
/* Output the listing with embedded error messages
 *    On entry-
 *       name is the source file name
 *       stream specifies the listing file
 *       cutoff=lowest severity level that will be listed
 *    If erronly != 0 then on exit-
 *       Source file lines containing errors have been added to file stream
 *          with error messages attached
 *    Else on exit-
 *       All source file lines have been added to file stream
 *          with error messages attached to those containing errors
 ***/
{
        register char *p;
        int fd;
        struct msg *r;
 
        if (name == NULL || *name == '\0') {
                (void)fprintf(stderr, "lisedit: Null source file name\n");
                exit(1);
        }
        if ((fd = open(name,0)) < 0) {
                (void)fprintf(stderr, "lisedit: Cannot open file %s\n", name);
                exit(1);
        }
        initBuf(name, fd);	/* set TokenEnd as side effect */
	p = TokenEnd;
        r = reports.forward;
        while (r != &reports && r->loc.line == 0) {
                if (r->severity >= cutoff){
                        (void)fprintf(stream, "*** %s: %s\n",
				key[r->severity], r->Msgtext);
			(void)fflush(stream); /* in case I/O redirected to a file */
			}
                r = r->forward;
        }
        while (r != &reports || (!erronly && *p != 0)) {
                if (r != &reports && LineNum > r->loc.line) {
			/* Output reports for the last line printed */
                        char buf[BUFSIZ];
                        int l, s;
 
                        if (r->severity >= cutoff) {
                                (void)sprintf(buf, "*** %s: %s",
                                        key[r->severity], r->Msgtext);
                                l = strlen(buf);
                                s = r->loc.col - 1 + (erronly?8:0);
                                if (l > s) {
                                        while (s--) (void)putc(' ', stream);
                                        (void)fprintf(stream, "^\n%s\n", buf);
					(void)fflush(stream);
                                } else {
                                        (void)fprintf(stream, "%s", buf);
                                        while (l < (s--))
                                                (void)putc('-', stream);
                                        (void)fprintf(stream, "^\n");
					(void)fflush(stream);
                                }
                        }
                        r = r->forward;
                } else {
			/* Print up through the next line with a report */
			register char c;

			while ((c = *p++) && c != '\n') ;
			if (c == '\n') {
				if (!erronly || LineNum == r->loc.line) {
					if (erronly)
					    (void)fprintf(stream, "%6d |", LineNum);
					(void)fwrite(StartLine+1,p-StartLine-1,
								1,stream);
					(void)fflush(stream);
					}
				StartLine = p-1;
				if (*p == 0) {
					refillBuf(p);
					p = TokenEnd;
				}
			} else /* c == 0 */ {
				if (erronly) (void)fprintf(stream, "%6d |", LineNum);
                        	(void)fputs("(End-of-file)\n", stream);
				(void)fflush(stream);
				p--;
			}
			LineNum++;
                }
        }/*endwhile*/
        (void)close(fd);
}        
#endif

#if defined(__cplusplus) || defined(__STDC__) 
void
message(int severity, char *Msgtext, int grammar, POSITION *source)
#else
void
message(severity, Msgtext, grammar, source)
int severity; char *Msgtext; int grammar; POSITION *source;
#endif
/* Report an error
 *    On entry-
 *      severity=error severity
 *      Msgtext=message text
 *      grammar=identification of the test that failed
 *      source=source coordinates at which the error was detected
 ***/
{
        int fail = 0;
        struct msg *r, *c;

	if (severity < NOTE || severity > DEADLY) {
		(void)fprintf(stderr, "Invalid severity code %d for \"%s\"\n",
			severity, Msgtext);
		severity = DEADLY;
		}

	if (source == NULL) source = &curpos;

	if (ImmediateOutput) {
		(void)fprintf(stderr, "\"%s\", line %d:%d %s: %s",
	  		SourceName, source->line,source->col,
			key[severity], Msgtext);
		if (grammar>0 && GrammarLine)
			(void)fprintf(stderr," AG=%d\n", grammar);
		else
			(void)putc('\n', stderr);
	}

	ErrorCount[severity]++;
	
        if ((r = (struct msg *) malloc(sizeof(struct msg))) == NULL) {
                r = &emergency;
                (void)fprintf(stderr, "No storage for error report at");
                fail = 1;
		}
        r->loc = *source;
        r->severity = severity;
        r->Msgtext = Msgtext;
        r->grammar = grammar;

        c = reports.back; while (earlier(&r->loc,&c->loc)) c = c->back;
        r->forward = c->forward; c->forward = r;
        r->back = c; (r->forward)->back = r;

	
	if(ErrorLimit && (ErrorCount[ERROR] + ErrorCount[FATAL]) > LineNum/20 +10) {
		(void)fprintf(stderr, "\"%s\", line %d:%d %s: %s",
	  		SourceName, source->line,source->col,
			key[DEADLY], "Too many ERRORs + FATALs");
                fail = 1;
		}
	if (severity == DEADLY || fail ) {
		(void)putc('\n', stderr);
                exit(1);
		}
}
