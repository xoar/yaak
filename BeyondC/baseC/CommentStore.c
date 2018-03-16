#include "CommentStore.h"

int commentVar = -1;

void storeComment
      (const char *start, int length, int *syncode, int *intrinsic)
    /* Make an internal string value from a character string
     *    On entry-
     *       start points to a character string of length l
     *       syncode points to a location containing the initial terminal code
     *    On exit-
     *       The proper terminal code for the string
     *          has been stored at the location pointed to by syncode
     *       An internal string value representing the character string
     *          has been stored at the location pointed to by intrinsic
     ***/
{
      commentVar = stostr (start, length);
      *intrinsic = commentVar;
}

int getComment () 
{
      int res = commentVar;
      commentVar = -1;
      return (res > 0? res : 0);
}