
#include "csm.h"
#include "p_mkstr.h"

#define DYNAMICSIZE 2048        /* handle strings up to this length */
#define SQ      '\''

/*
 * p_mkstr
 *
 * Make an internal string value from a character string by
 * colapsing escape sequences.
 *
 * On entry, c points to a character string of length 
 *           t points to a location containing the initial terminal code
 * On exit, t points to a location containing the correct terminal code
 *          an internal string value representing the character string has been
 *          stored at the location pointed to by v.
 */
#if defined(__cplusplus) || defined(__STDC__)
extern void mkstr(char *c, int l, int *t, int *p);
#endif

#if defined(__cplusplus) || defined(__STDC__)
void p_mkstr(char* c, int length, int* t, int* v)
#else
void p_mkstr(c, length, t, v)
char *c;
int length, *t;
int *v;
#endif
{
        char *from , *to;
        char converted[DYNAMICSIZE];    /* converted string */

        from = c;
        to = &converted[0];

        from++; /* skip leading quote */
        length -= 2; /* throw away both quotes */
        for (; (length> 0);){
                if( *from == SQ)
                        if( *(from+1) == SQ ) { /* '' --> ' */
                                length -= 2;
                                *to++ = *from++;
                                from++;
                                }
                        else    {
                                /* This shouldn't happen! */
                                }
                else    {
                        *to++ = *from++;
                        length--;
                        }
                }/*endfor*/

        mkstr( converted, to-converted, t, v ); /* save the string */
}
