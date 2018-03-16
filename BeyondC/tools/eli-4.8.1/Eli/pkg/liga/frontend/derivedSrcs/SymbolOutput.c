
#include "SymbolOutput.h"
#include "GrammarRules.h"
#include "Attribute.h"
#include "csm.h"
#include "pdl_gen.h"

/* is set to the global scope by the call of OutputSymbols: */
static Environment globalEnv = NoEnv;

#if defined(__cplusplus) || defined(__STDC__)
PTGNode OutCoord (DefTableKey k)
#else
PTGNode OutCoord (k) DefTableKey k;
#endif
{ CoordPtr c = GetCoord (k, NoPosition);
  if (c == NoPosition)
    return PTGCoord (0, 0);
  else
    return PTGCoord (LineOf(*c),ColOf(*c));
}

#if defined(__cplusplus) || defined(__STDC__)
PTGNode OutAllInherits (DefTableKey sym)
#else
PTGNode OutAllInherits (sym) DefTableKey sym;
#endif
/* outputs a list of symbols that sym inherits from */
{ PTGNode res = PTGNULL;
  Environment symEnv = GetUpperScope (sym, NoEnv);

  Binding b = DefinitionsOf (globalEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsSymbol (k, 0)) 
    { Environment fromEnv = GetUpperScope (k, NoEnv);
      if (symEnv != fromEnv && Inheritsfrom (symEnv, fromEnv))
         res = PTGCommaSeq 
           (res, PTGAsIs (StringTable (IdnOf (b))));
    }
    b = NextDefinition (b);
  }
  return res;
}

#if defined(__cplusplus) || defined(__STDC__)
PTGNode OutDirectInherits (DefTableKey sym)
#else
PTGNode OutDirectInherits (sym) DefTableKey sym;
#endif
/* outputs a list of symbols that sym inherits from */
{ PTGNode res = PTGNULL;
  Environment symEnv = GetUpperScope (sym, NoEnv);

  InheritPtr inh = DirectInherits (symEnv);
  while (inh != NoInherit)
  { 
    res = PTGCommaSeq (res, 
       PTGAsIs 
         (StringTable 
            (GetNameSym (KeyOfEnv (EnvOfInherit (inh)), 0))));
    inh = NextInherit (inh);
  }
  return res;
}

#if defined(__cplusplus) || defined(__STDC__)
PTGNode OutAttributes (DefTableKey sym)
#else
PTGNode OutAttributes (sym) DefTableKey sym;
#endif
/* outputs the list of attributes of sym */
{ PTGNode res = PTGNULL;
  Environment symEnv = GetAttrScope (sym, NoEnv);

  Binding b = DefinitionsOf (symEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    DefTableKey tp = GetAttrType (k, NoKey);
    PTGNode outtp =
      (tp == NoKey ? PTGAsIs ("No Type") :
         PTGAsIs (StringTable (GetNameSym (tp, 0))));
    int cl = GetAttrClass (k, NoClass);
    PTGNode outcl =
      (cl == SYNTClass ? PTGAsIs ("SYNT") :
       cl == INHClass  ? PTGAsIs ("INH")  : 
       PTGAsIs ("No Class"));

    res = PTGSeq (res,
      PTGAttribute
        (StringTable (IdnOf (b)),
         OutCoord (k),
         outcl,
         outtp,
         GetAttrTypeDefault (k, 0) ? PTGDefaultType() : PTGNULL));

    b = NextDefinition (b);
  }
  return res;
}

#if defined(__cplusplus) || defined(__STDC__)
PTGNode OutputSymbols (Environment globenv)
#else
PTGNode OutputSymbols (globenv) Environment globenv;
#endif
{ PTGNode treeSyms = PTGNULL, classSyms = PTGNULL,
          rules = PTGNULL;
  Binding b;
  globalEnv = globenv;
  
  b = DefinitionsOf (globalEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsSymbol (k, 0) && GetIsUsed (k, 0))
    { PTGNode outsym = 
        PTGSymbol 
           (StringTable (IdnOf (b)), 
            OutCoord (k),
            OutDirectInherits (k),
            OutAllInherits (k),
            OutAttributes (k));
      if (GetIsTreeSym (k, 0))
        treeSyms = PTGSeq (outsym, treeSyms);
      else /* assumed: IsCLASSSym set to 1 or unset */
        classSyms = PTGSeq (outsym, classSyms);
    } else
    if (GetIsRule (k, 0))
      rules = PTGSeq (rules, 
        PTGRule
          (StringTable (IdnOf (b)),
           OutCoord (k),
           OutAttributes (k)));

    b = NextDefinition (b);
  }
  return PTGUsedSymbols (treeSyms, classSyms, rules);
}
