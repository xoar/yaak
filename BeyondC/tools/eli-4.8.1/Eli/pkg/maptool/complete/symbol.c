
#include "obstack.h"
#include "symbol.h"
#include "eliproto.h"

Obstack mapobstack;

/* On Exit:
 *   CreateSymbol creates and returns a newly allocated symbol structure.
 */
#ifdef PROTO_OK
SymbolP
CreateSymbol (void)
#else
SymbolP
CreateSymbol ()
#endif
{
  return (SymbolP)obstack_alloc(MapObstack, sizeof(struct Symbol));
}
