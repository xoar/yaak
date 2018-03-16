static char rcs_id[] = "$Id: printst2ter.c,v 1.4 1997/08/29 08:38:08 mjung Exp $";
/* printst2ter.c	-- Karl Prott Thu Nov  3 1994
 */

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

#include <assert.h>
#include <stdio.h>

#include "printst2ter.h"
#include "privatlib.h"		/* for priv_deftostr() */

/* idl declarations */
#include "comar.h"
#include "comarMacros.h"
#include "prsiface.h"
#include "prsifaceM.h"

#include "cmrlib.h"		/* for cmrlib_getdef() */

static	char *	TERMINALS[MAXTERMINALS];
static	FILE *	F;

#define ERROPNMAIL(str) \
        (void)fprintf(stderr, "Cannot open file %s for writing.\n", str)

static void
#if defined(__STDC__) || defined(__cplusplus)
C_outstr(FILE *fs, char *s)
#else
C_outstr(fs, s) FILE *fs; char *s;
#endif
{
  char c;

  /* C string must be bracketed into \" ... \" */
  (void)fputs("\\\"", fs);	/* prints \" */

  while ((c = *s++ & 0377)) 
  {
    if (c >= '\177') (void)fprintf(fs, "\\%3o", c);
    else if (c == '\\') (void)fputs("\\\\", fs);
    else if (c == '"') (void)fputs("\\\"", fs);
    else if (c >= ' ') (void)fputc(c, fs);
    else switch (c) 
         {
	  case '\n': (void)fputs("\\n", fs); break;
	  case '\t': (void)fputs("\\t", fs); break;
	  case '\b': (void)fputs("\\b", fs); break;
	  case '\r': (void)fputs("\\r", fs); break;
	  case '\f': (void)fputs("\\f", fs); break;
	  default: (void)fprintf(fs, "\\%3o", c); 
         }
  }

  (void)fputs("\\\"", fs);	/* prints \" */
  return;
}

#if defined(__cplusplus) || defined(__STDC__)
static	void	printHeadAndOpen(void)
#else
static	void	printHeadAndOpen()
#endif
{
  if ( (F = fopen(FILENAME, "w"))  ==  (FILE *)NULL )
  {
    ERROPNMAIL(FILENAME);
    exit(1);
  } /* of if */

  fputs("static\tchar *state2terms[] = {\n", F);
  return;
}  /* of printHeadAndOpen() */

#if defined(__cplusplus) || defined(__STDC__)
static	void	printTailAndClose(void)
#else
static	void	printTailAndClose()
#endif
{
  fputs("\t(char *)NULL\n}; /* of array state2terms[] */\n", F);
  fclose(F);
  return;
}  /* of printTailAndClose() */

#if defined(__cplusplus) || defined(__STDC__)
static	void	printTerminals(int cnt)
#else
static	void	printTerminals(cnt)
int	cnt;
#endif
{
  int	i;
static	int	q=1;

  if ( cnt==0 )
    fputs("\t(char *)NULL", F);
  else 
  {
    (void)fputs("\t\"", F);

    if ( cnt == 1 )
	C_outstr(F, TERMINALS[0]);
    else  /* cnt >= 2 */
    {
      for (i=0; i<cnt-2; i++)
      {
        C_outstr(F, TERMINALS[i]);
        (void)fputs(", ", F);
      }
      C_outstr(F, TERMINALS[i]);
      (void)fputs(" or ", F);
      C_outstr(F, TERMINALS[i+1]);
    }  /* of else */

    (void)fputc('"', F);
  }  /* of else */

  fprintf(F, ",\t/* state %d */\n", q);
  q++;
  return;
}  /* of printTerminals() */


#if defined(__cplusplus) || defined(__STDC__)
void	printstate2terms	(absparsertype autom, p_comar cmr)
#else
void	printstate2terms	(autom, cmr)
absparsertype	autom;
p_comar		cmr;
#endif
{
  SEQRowtype	rtravel;
  Rowtype	state;
  SEQEntrytype	etravel;
  Entrytype	entry;
  def_entry	def;
  int		cnt;

  printHeadAndOpen();

  foreachinSEQRowtype(ParsingTabOfabsparsertype(autom), rtravel, state)
  {
    cnt=0;
    foreachinSEQEntrytype(EntriesOfRowtype(state), etravel, entry)
    {
      def = cmrlib_getdef(definitionsOfp_comar(cmr),
			  CMR_DT_indexOfEntrytype(entry));
      assert(def.IDLclassCommon);

      if ( typeof(def) == Kp_term ) /* terminal action found */
      {
	cnt++;
	if ( cnt > MAXTERMINALS )
	{
	  cnt=0;
	  break;
	} /* of if */
	TERMINALS[cnt-1] = priv_deftostr(def);
      } /* of if */
    } /* of for */

    printTerminals(cnt);
  } /* of for */

  printTailAndClose();

  return;
} /* of printstate2terms() */
