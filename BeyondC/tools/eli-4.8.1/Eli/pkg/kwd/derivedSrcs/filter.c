
#include "csm.h"
#include "err.h"
#include "can.h"
#include "filter.h"

PTGNode
#ifdef PROTO_OK
Canned(int symbol, POSITION *loc)
#else
Canned(symbol, loc) int symbol; POSITION *loc;
#endif
{ CannedDescrPtr i;

  i = libLookup(StringTable(symbol));
  if (i == NullDescr) {
    message(ERROR, "No such canned description", 0, loc);
    return PTGId(symbol);
  }
  if (i->Lscanner)
    message(ERROR, "Keyword definition cannot specify a scanner", 0, loc);
  return PTGRegExp(PTGAsIs(i->Lpattern));
}

