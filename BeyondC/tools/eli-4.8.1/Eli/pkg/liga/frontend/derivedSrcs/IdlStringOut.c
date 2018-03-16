
#include "IdlStringOut.h"

#define TILDE 0176
#define DEL 0177
#define QUOTE '"'

#if defined(__cplusplus) || defined(__STDC__)
void IdlStringTrafo (FILE* F, const char* S)
#else
void IdlStringTrafo (F, S) FILE* F; char* S;
#endif
/* This function outputs strings and single characters
   in the encoding used by Idl
*/
{
        while (*S != '\0')
        {
            if((*S > 0) && (*S <= 037)) /* character is between '@' and '_' */
            {
                putc(TILDE,F);
                putc(*S + '@',F);
            }
            else if(*S == TILDE)  
                 {
                     putc(TILDE,F);
                     putc(TILDE,F);
                 }
            else if(*S == DEL)
                 {
                     putc(TILDE,F);
                     putc('{',F);
                 }
            else if(*S == QUOTE)
                 {
                     putc('"',F);
                     putc('"',F);
                 }
            else putc(*S,F);
            ++S;
        }
}
