
#ifndef COMPREPR_H
#define COMPREPR_H

#include "deftbl.h"
#include "err.h"
#include "PExprList.h"
#include "Prod.h"

typedef struct TExpr
  { int exprKind;
    CoordPtr coord;
    union
    { 
#define CallKind                1
      struct                            /* call of functions, predefined or users */
        { int idn;                      /* StringTable index of function name */
          PExprList params;
        } call;
#define NameKind                2
      int               name;
#define IntValueKind            3
      int               intValue;
#define StrValueKind            4
      int               strValue;
#define ChrValueKind            5
      int               chrValue;
#define FltValueKind            6
      int               fltValue;
#define AttrAccRuleKind         7
      struct                            /* attribute access in rule context */
        { ProdSymbol  prodSymb;         /* symbol occurrence */
          DefTableKey attrKey;
          int         isChain;
        } attrAccRule;
#define RuleAttrAccKind         8
      struct                            /* rule attribute access in rule context */
        { DefTableKey attrKey;
        } ruleAttrAcc;
#define AttrAccSymbKind         9
      struct                            /* attribute access in symbol context */
        { DefTableKey symbKey;          /* symbol key or HEADKey or TAILKey */
          DefTableKey attrKey;
          int         isChain;
        } attrAccSymb;
#define IncludingKind           10
#define ConstituentKind         11
#define ConstituentsKind        12
      struct
        { DefTableKey   remKey;
          int subtree;                  /* for CONSTITUENT(S) only */
        } remote;
#define SymbTermAccKind         13
      int               symbTerm;
#define RuleTermAccKind         14
      struct                            /* terminal access in rule context */
        { int symbNo;                   /* position in production */
          DefTableKey symbKey;
        } ruleTerm;
#define RHSKind                 15
      int               attrIdn;
#define HeadAccKind             16
#define TailAccKind             17
      DefTableKey       chnKey;
#define LoopKind                18
      struct
        { PExpr         cond;
          PExpr         attr;
          PExpr         iter;
        } loop;
#define DependKind              19
      struct
        { PExpr         ex;
          PExprList     deps;
        } depend;
#define AssignKind              20
      struct
        { PExpr         left;
          PExpr         right;
        } assign;
#define ExprListKind            21
        PExprList       subList;
    } u;
#define wrongExprKind           22
  } _SExpr;

#define NULLPExpr ((PExpr)0)

#endif
