
/* Collect a C compound statement as a single literal string */

#include "err.h"
#include "source.h"
#include "csm.h"
#include "gla.h"

typedef enum {                  /* Scanner states */
   InText,
   InComment,
   InCharacter,
   InString
} States;

typedef enum {                  /* Last character flags */
   Uninteresting,
   Backslash,
   Slash,
   Star
} Flags;

/***/
char *
#if defined(__cplusplus) || defined(__STDC__)
Ctext(char *start, int len)
#else
Ctext(start, len)
char *start; int len;
#endif
/* Scan a C compound statement after the opening brace
 *    On entry
 *       start points to the opening brace
 *       len=1
 *    On exit-
 *       Ctext points to the character position following the
 *          closing brace
 ***/

{
   register char c ;
   register char *p = start + len;
   int nest = 0;
   States state = InText;
   Flags last = Uninteresting;

   for (;;) {
      if (*p == '\0') {
         size_t current = p - start;
         refillBuf(start);
         TokenStart = start = TEXTSTART;
         p = start + current;
         if (*p == '\0') {
            message(DEADLY,"file ends in C text",0,&curpos);
         }
      }
      c = *p++;

      if (c == '\n') { LineNum++; StartLine = p - 1; }

      switch (last) {
      case Backslash:
         last = Uninteresting; continue;
      case Slash:
         last = Uninteresting;
         if (c == '*') { state = InComment; continue; }
         break;
      case Star:
         last = Uninteresting;
         if (c == '/') { state = InText; continue; }
      default:
         ;
      }

      switch (c) {
      case '\"':
         if (state == InText) state = InString;
         else if (state == InString) state = InText;
         break;
      case '\'':
         if (state == InText) state = InCharacter;
         else if (state == InCharacter) state = InText;
         break;
      case '\\':
         if (state == InCharacter || state == InString) last = Backslash;
         break;
      case '/':
         if (state == InText) last = Slash;
         break;
      case '*':
         if (state == InComment) last = Star;
         break;
      case '{':
         if (state == InText) nest++;
         break;
      case '}':
         if (state == InText) {
            if (nest == 0) {
                return p;
            }
            nest--;
         }
         break;
      default:
         ;
      }
   }
}
