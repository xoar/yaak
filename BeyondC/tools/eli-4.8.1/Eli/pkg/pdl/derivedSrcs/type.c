
/* Attribute computations for PDL type analysis */

#include <stdio.h>
#include "ptg_gen.h"    /* output generation definitions */
#include "deftbl.h"     /* definition table module */
#include "envmod.h"     /* environment module */
#include "func.h"       /* declarations required for db.h */
#include "pdl_gen.h"    /* PDL generated header for exported functions */
#include "type.h"       /* constants and exported functions */

/***/
#if defined(__cplusplus) || defined(__STDC__)
void
TypeIs (DefTableKey key, DefTableKey type)
#else
void
TypeIs(key,type)
DefTableKey key, type;
#endif
/* Verify the type of an entity
 *    On entry-
 *       key defines the entity
 *       type specifies the type of entity
 *    On exit-
 *       The Type property has been set
 ***/
{
   switch (GetDefine(key, Unknown)) {
   case Defined:
      if (GetType(key, NoKey) != type)
         SetDefine(key, MultDefined, MultDefined);
   case MultDefined:
      return;
   case Unknown:
      SetDefine(key, Defined, MultDefined);
      SetType(key, type, NoKey);
   }
}
