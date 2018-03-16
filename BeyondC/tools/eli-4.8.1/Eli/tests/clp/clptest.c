/* $Id: clptest.c,v 1.15 2009/08/12 22:11:12 profw Exp $ */

#include <stdio.h>
#include <string.h>
#include "clp.h"
#include "csm.h"

static int count = 0;

static DefTableKey 
#if defined(__STDC__) || defined(__cplusplus)
countone (DefTableKey k)
#else
countone (k)
  DefTableKey k;
#endif
{
   count++;
   return k;
}

static DefTableKey
#if defined(__STDC__) || defined(__cplusplus)
printnl (DefTableKey k)
#else
printnl (k)
  DefTableKey k;
#endif
{
  (void) printf ("NumLines option, value = '%d'\n", GetClpValue (k, 0));
  return k;
}

static DefTableKey
#if defined(__STDC__) || defined(__cplusplus)
printnz (DefTableKey k)
#else
printnz (k)
  DefTableKey k;
#endif
{
  (void) printf ("NumZaps option, value = '%d'\n", GetClpValue (k, 0));
  return k;
}

static DefTableKey 
#if defined(__STDC__) || defined(__cplusplus)
printmp (DefTableKey k)
#else
printmp (k)
  DefTableKey k;
#endif
{
  (void) printf ("MacroPackage option, value = '%s'\n",
		 StringTable (GetClpValue (k, 0)));
  return k;		 
}

static DefTableKey 
#if defined(__STDC__) || defined(__cplusplus)
printo (DefTableKey k)
#else
printo (k)
  DefTableKey k;
#endif
{
  CONST char *str, *rstr;

  str = StringTable (GetClpValue (k, 0));
  if ((rstr = strrchr (str, '/')) == (char *)NULL)
    rstr = str;
  else
    rstr++;
  (void)printf ("Positional param = '%s'\n", rstr);
  return k;
}

void
#if defined(__STDC__) || defined(__cplusplus)
show(int dummy)
#else
show (dummy)
  int dummy;
#endif
{
  CONST char *str, *rstr;

  if (CompileOnly) (void)printf ("CompileOnly option specified\n");
  if (GenAssembly) (void)printf ("GenAssembly option specified\n");
  (void)printf ("WideListing specified %d time(s)\n", WideListing);
  if (OutputFile != NoKey)
    (void)printf ("Outputfile option, value = '%s'\n",
		  StringTable (GetClpValue (OutputFile, 0)));
  if (TmpFile != NoKey)
    (void)printf ("TmpFile option, value = '%s'\n",
		  StringTable (GetClpValue (TmpFile, 0)));
  if (NumCopies != NoKey)
    (void)printf ("NumCopies option, value = '%d'\n",
		  GetClpValue (NumCopies, 0));
  (void)MapDefTableKeyList (NumLines, printnl);
  if (NumCols != NoKey)
    (void)printf ("NumCols option, value = '%d'\n",
		  GetClpValue (NumCols, 0));
  (void)MapDefTableKeyList (NumZaps, printnz);
  (void)MapDefTableKeyList (MacroPackage, printmp);
  str = StringTable (GetClpValue (InputFile, 0));
  if ((rstr = strrchr (str, '/')) == (char *)NULL)
    rstr = str;
  else
    rstr++;
  (void)printf ("InputFile = '%s'\n", rstr);
  (void)MapDefTableKeyList (Others, printo);
}
