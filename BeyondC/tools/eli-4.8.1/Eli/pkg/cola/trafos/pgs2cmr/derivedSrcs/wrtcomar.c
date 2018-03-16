#include "clp.h"
#include "csm.h"
#include "comar_ins.h"

void WriteCmrFile()
{
  if (CmrFile != NoKey)
    write_results(StringTable(GetClpValue(CmrFile, 0)));
}

