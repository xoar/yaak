
#include "idn.h"
#include "mkidnwod.h"

void
#if defined(__STDC__) || defined(__cplusplus)
        mkidnwod(char *start, int length, int *class, int *intrinsic)
#else
        mkidnwod(start, length, class, intrinsic)
        char *start; int length, *class; int *intrinsic;
#endif
{
        int     dummy;

        dummy = *class;
        if ( *start == '\'')
                mkidn (start+1, length-2, &dummy, intrinsic);
        else
                mkidn (start, length, &dummy, intrinsic);
} /* of mkidnwod() */

