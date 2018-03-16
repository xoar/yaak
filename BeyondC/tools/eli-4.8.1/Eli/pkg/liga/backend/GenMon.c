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
#include <stdio.h>
#include <string.h>

#include "global.h"
#include "LIGA.h"
#include "LIGAMacros.h"
#include "ligaconsts.h"
#include "lookup_idl.h"

#include "GenMon.h"
#include "ProdSectList.h"
#include "ProdIter.h"

#include "ptg_gen.h"

#if defined(__STDC__) || defined(__cplusplus)
void C_outstr_noquotes(PTG_OUTPUT_FILE fs, const char *s)
#else
void C_outstr_noquotes(fs, s) PTG_OUTPUT_FILE fs; char *s;
#endif
{
        char c;


        while ((c = *s++ & 0377)) {
                if (c >= '\177') (void)fprintf(fs, "\\%3o", c);
                else if (c == '\\') (void)fputs("\\\\", fs);
                else if (c == '"') (void)fputs("\\\"", fs);
                else if (c >= ' ') (void)fputc(c, fs);
                else switch (c) {
                case '\n': (void)fputs("\\n", fs); break;
                case '\t': (void)fputs("\\t", fs); break;
                case '\b': (void)fputs("\\b", fs); break;
                case '\r': (void)fputs("\\r", fs); break;
                case '\f': (void)fputs("\\f", fs); break;
                default: (void)fprintf(fs, "\\%3o", c); }
        }
        return;
}

#define IsGenAttr(aname) (strcmp (nameOfAttrdef (aname), GENTREEATTR) == 0)


/* types and functions to collect all types of terminals: */
#include "VoidPtrList.h"

/* adaption of string pointer lists to VoidPtrList implementation: */
typedef VoidPtrList StringPtrList;
#define NULLStringPtrList NULLVoidPtrList
#define HeadStringPtrList(l) ((char*)(HeadVoidPtrList(l)))
#define TailStringPtrList(l) TailVoidPtrList(l)
#define ConsStringPtrList(e,l) ConsVoidPtrList((VoidPtr)e, l)

StringPtrList termTypes = NULLStringPtrList;

#if defined(__STDC__) || defined(__cplusplus)
void AddTermType (char *name)
#else
    void AddTermType (name) char *name;
#endif

{ StringPtrList l = termTypes;
  while (l != NULLStringPtrList)
    if (strcmp (name, HeadStringPtrList(l))==0)
      return;
    else l = TailStringPtrList(l);
  termTypes = ConsStringPtrList (name, termTypes);
}

PTGNode MakeTermEvents ()
{ PTGNode res = PTGNULL;
  StringPtrList l = termTypes;
  while (l != NULLStringPtrList)
  { res = PTGSeq (res, PTGMonTermEvent (HeadStringPtrList(l)));
    l = TailStringPtrList(l);
  }
  return res;
}
/* end types and functions to collect all types of terminals */

/* Function that eliminates the marker from rule attr names: */
#define RAMARKER "_RuleAttr_"

static char* StripRuleAttrMark (nam) char* nam;
{ char *startOfMark = strstr(nam, RAMARKER);
  if (startOfMark)
  { /* remove the RAMARKER substring from a rule attribute's name */ 
    char *plainname = malloc (strlen(nam));
    char *p1, *p2;
    for (p1=nam, p2=plainname; p1 != startOfMark; p1++, p2++)
      *p2 = *p1;
    *p2 = 0;
    return plainname;
  } else return nam;
}

void GenAttrMon (ae) AttrEval ae;
/* Generate attribution monitoring 
   Two functions are generated, one for symbol attributes
   and one for rule attributes.
*/
{ SEQDef defs; Def def;
  PTGNode MonGetAttrCases = PTGNULL;
  PTGNode MonAttrComps = PTGNULL;
  PTGNode MonGetAttrs;

/* Generate cases of get_symb_attrs function: */
  foreachinSEQDef (defseqOfAttrEval (ae), defs, def)
  if (typeof (def) == KSymb)
  { Symb symbol = DefToSymb (def);
    SEQAttrdef attrs; Attrdef attr;
    PTGNode MonAttrDescrs = PTGNULL;

    foreachinSEQAttrdef (attrsOfSymb (symbol), attrs, attr)
    /* The following attributes are not considered: 
       rule attributes
       generated attributes for 
       INCLUDING, CONSTITUENTS, and for coordinates
       and terminals
    */
    if (typeidOfAttrdef (attr) != DIDVOID &&
        typeidOfAttrdef (attr) != DIDVOLI &&
        prodidOfAttrdef (attr) == 0 &&
	genOfAttrdef (attr) != GENCONST &&
	genOfAttrdef (attr) != GENINCL &&
        !IsGenAttr (attr))
    {  Def tpdef;
       tpdef = lookup_def (typeidOfAttrdef (attr));
       MonAttrDescrs =
         PTGSeq 
           (MonAttrDescrs,
            PTGMonAttrDescr 
               (nameOfAttrdef (attr), 
                dnameOfDef (tpdef)));
    }
    MonGetAttrCases =
      PTGSeq 
        (MonGetAttrCases,
         PTGMonGetAttrSymbCase 
           (dnameOfDef (def), MonAttrDescrs));
  }
  MonGetAttrs = PTGMonGetSymbAttrs (MonGetAttrCases);
  MonGetAttrCases = PTGNULL;

/* Generate cases of get_rule_attrs function: */
  foreachinSEQDef (defseqOfAttrEval (ae), defs, def)
  if (typeof (def) == KProd)
  { int prodid = didOfDef (def);
    Prod prod = DefToProd (def);
    int lhsdid = lhsOfProd(prod);
    Symb symbol;
    SEQAttrdef attrs; Attrdef attr;
    PTGNode MonAttrDescrs = PTGNULL;
    Def lhsdef;
    lhsdef = lookup_def (lhsdid);
    symbol = DefToSymb (lhsdef);
    foreachinSEQAttrdef (attrsOfSymb (symbol), attrs, attr)
    /* only non-VOID rule attributes of this rule are considered,
       generated terminal attributes are ignored
    */
    if (typeidOfAttrdef (attr) != DIDVOID &&
        typeidOfAttrdef (attr) != DIDVOLI &&
        prodidOfAttrdef (attr) == prodid &&
	genOfAttrdef (attr) != GENTERM &&
        !IsGenAttr (attr))
    {  Def tpdef;
       tpdef = lookup_def (typeidOfAttrdef (attr));
       MonAttrDescrs =
         PTGSeq 
           (MonAttrDescrs,
            PTGMonAttrDescr 
               (StripRuleAttrMark (nameOfAttrdef (attr)), 
                dnameOfDef (tpdef)));
    }
    MonGetAttrCases =
      PTGSeq 
        (MonGetAttrCases,
         PTGMonGetAttrRuleCase 
           (dnameOfDef (def), MonAttrDescrs));
  }
  MonGetAttrs = 
    PTGSeq (MonGetAttrs, PTGMonGetRuleAttrs (MonGetAttrCases));

{ /* generate the terminal information for rules: */
  ProdSectPtrList prods;
  PTGNode rulecases = PTGNULL;

  for (prods = prodsectlist; prods != NULLProdSectPtrList;
	    prods = TailProdSectPtrList (prods)) 
  {
    Prod prod = (HeadProdSectPtrList (prods))->proddef;
    int	did = lhsOfProd (prod);
    SEQEntity ents; Entity ent;
    char *termname, *typename;
    PTGNode ruleterms = PTGNULL;
    int isGen, isNonLit;
    Def ldef;
    ldef = lookup_def (did);

    ents = rhsOfProd (prod);
    while (HasMoreEntities (&ents))
    { NextEntity (&ents, &ent, &isGen, &isNonLit, &typename);
      if (typeof (ent) == KLiteral && isNonLit) 
      { int index = GetIndexInProd (prod, ent);
        Literal tmpLiteral = EntityToLiteral(ent);
	termname = strOfLiteral (tmpLiteral);
        ruleterms = PTGSeq (ruleterms, 
           PTGMonTermDescr 
             (termname, 
              index == 0 ? PTGNULL : PTGMonIndex (index),
              typename));
        AddTermType (typename); /* keep the terminal type name */
      }
    }

    rulecases =
      PTGSeq (rulecases,PTGMonGetTermCase (dnameOfProd(prod), ruleterms));
  }
  MonGetAttrs = 
    PTGSeq (MonGetAttrs, PTGMonGetTerms (rulecases));
  MonGetAttrs =
    PTGSeq (MonGetAttrs, MakeTermEvents ());
}

  /* Generate attr computation functions: */
  foreachinSEQDef (defseqOfAttrEval (ae), defs, def)
  if (typeof (def) == KTypedef &&
      didOfDef (def) != DIDVOID && 
      didOfDef (def) != DIDVOLI &&      
      strcmp (dnameOfDef (def), TNBUMARK) != 0 &&
      strcmp (dnameOfDef (def), "$TERM") != 0 &&
      (*(dnameOfDef (def)) != '$' &&
      strlen (extnameOfTypedef (DefToTypedef (def))) == 0))

     MonAttrComps =
       PTGSeq
         (MonAttrComps,
          PTGMonAttrComp (dnameOfDef (def)));

  PTGOutFile 
    ("attr_mon.dapto",
     PTGMonAttrFile
       (MonGetAttrs,
        MonAttrComps,
        PTGMonPlainComp ()));

}/* GenAttrMon */

void GenMon (ae) AttrEval ae;
/* Generate monitoring support for attribution */
{
    ProdSectPtrList prods;
    SEQDef defs;
    Def ldef, def;
    Prod prod;
    SEQEntity ents;
    Entity ent;
    int did, symbno, i;
    char *name;
    PTGNode genprods = PTGNULL, 
            gennchild = PTGNULL, 
            genchild = PTGNULL, gentmp;

    GenAttrMon (ae);

    /* Produce an array of the production texts */
    for (prods = prodsectlist; prods != NULLProdSectPtrList;
	    prods = TailProdSectPtrList (prods))
    {	prod = (HeadProdSectPtrList (prods))->proddef;
	did = lhsOfProd (prod);
	ldef = lookup_def (did);
	gentmp = PTGNULL;

        ents = rhsOfProd (prod);
        while (HasMoreEntities (&ents))
        { int isGen, isNonLit; char *typename;
          NextEntity (&ents, &ent, &isGen, &isNonLit, &typename);

	  if (typeof (ent) == KSymbol) 
          { Symbol symb = EntityToSymbol (ent);
	    did = didOfSymbol (symb);
	    def = lookup_def (did);
            if (isGen)
              gentmp = PTGSseq (gentmp, "$");
	    gentmp = PTGSseq (gentmp, dnameOfDef (def));
	  } else 
          if (typeof (ent) == KLiteral)
	  { Literal tmpLiteral = EntityToLiteral(ent);
	    name = strOfLiteral (tmpLiteral);
            if (isNonLit)
	         gentmp = PTGSseq (gentmp, name);
            else gentmp = PTGLseq (gentmp, name);
	  }
	}
	genprods = PTGSeq (genprods, 
              PTGProds (dnameOfProd (prod), 
                        dnameOfDef (ldef),
			gentmp));
    }

    /* Produce an array of children counts for each production */
    for (prods = prodsectlist; prods != NULLProdSectPtrList;
	    prods = TailProdSectPtrList (prods)) {
	prod = (HeadProdSectPtrList (prods))->proddef;
	i = 0;
        foreachinSEQEntity (rhsOfProd (prod), ents, ent)
	    if (typeof (ent) == KSymbol)
		i++;
	gennchild = PTGSeq (gennchild, PTGNchild (i));
    }

    /* Produce a routine to return the children */
    for (prods = prodsectlist; prods != NULLProdSectPtrList;
	    prods = TailProdSectPtrList (prods)) {
	prod = (HeadProdSectPtrList (prods))->proddef;
	symbno = 0;
	foreachinSEQEntity (rhsOfProd (prod), ents, ent)
	    if (typeof (ent) == KSymbol)
		symbno++;
	if (symbno != 0) {
	    gentmp = PTGNULL;
	    for (i = 1; i <= symbno; i++)
		gentmp = PTGSeq (gentmp, PTGDesc (i));
	    genchild = PTGSeq (genchild, PTGChild (dnameOfProd (prod), gentmp));
	}
    }

    PTGOutFile ("mon_aprods.c",
		PTGMonAprods (PTGAbsProds (genprods),
			      PTGAbsNchild (gennchild),
			      PTGAbsChild (genchild)));
}

