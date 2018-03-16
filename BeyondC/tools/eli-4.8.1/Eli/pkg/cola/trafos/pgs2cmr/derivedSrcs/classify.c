
#include "classify.h"
#include "pdl_gen.h"

void
#if defined(__STDC__) || defined(__cplusplus)
        Classify(DefTableKey key, int class)
#else
        Classify(key, class)
        int     class;
        DefTableKey key;
#endif
{
   switch ( GetClass(key, UNDEF) )
   {
        case FAULT      : break;
        case UNDEF      : ResetClass(key, class);
                          break;
        case TERMINAL   : if ( class == NONTERMINAL )
                                ResetClass(key, FAULT);
                          break;
        case NONTERMINAL: if ( class == TERMINAL )
                                ResetClass(key, FAULT);
                          break;
   } /* of switch */
   return;
} /* of Classify() */
