
#include <stdio.h>
#include <stdlib.h>
#include "obstack.h"
#include "DynSpace.h"

typedef struct {
  Obstack space;
  void *baseptr;
} Dyn, *DynP;

#if defined(__STDC__) || defined(__cplusplus)
void *DynAlloc (void *space, int size)
#else
void* DynAlloc (space, size)
        void*   space;
        int     size;
#endif
{
    DynP spc;

    spc = (DynP) space;
    return ((void*)obstack_alloc(&(spc->space), size));
}/* DynAlloc */

#if defined(__STDC__) || defined(__cplusplus)
void DynClear(void *space)
#else
void DynClear (space)
     void *space;
#endif
{
    DynP spc;

    spc = (DynP) space;
    obstack_free(&(spc->space), spc->baseptr);
    spc->baseptr = obstack_alloc(&(spc->space), 0);
} /* DynClear */

#if defined(__STDC__) || defined(__cplusplus)
void *InitDynSpace(void)
#else
void* InitDynSpace ()
#endif
{
    DynP New;

    New = (DynP) malloc (sizeof(Dyn));
    if (!New) {
        fprintf (stderr, "no space for DynSpace\n");
        exit (1);
    }

    obstack_init(&(New->space));
    New->baseptr = obstack_alloc(&(New->space), 0);

    return ((void*)New);
}/* InitDynSpace */
