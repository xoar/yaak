
#include "RuleProdList.h"
#include "envmod.h"

extern RuleProd MakeRuleProd 
  FEARGS ((DefTableKey rulekey, ProdSymbolList prod, 
           int islistof, CoordPtr coord));

/* list of all rules, no duplicate instances, each named,
   names generated for unnamed rules that are not matched to
   a named rule:
*/
extern RuleProdList GrammarRules;

extern void MakeGrammar (Environment env);
