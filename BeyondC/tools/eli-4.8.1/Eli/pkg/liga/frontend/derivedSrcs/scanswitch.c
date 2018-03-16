
#include "scanswitch.h"
#include "args.h"

extern char* auxPascalString FEARGS((char *start, int length));
extern char* auxCChar FEARGS((char *start, int length));

scan_switch_type scan_switch = want_c_chars;

void scan_p_strings()
{ 
  scan_switch = want_p_strings;
}

void scan_c_chars()
{ 
  scan_switch = want_c_chars;
}

#if defined(__cplusplus) || defined(__STDC__)
char* aux_p_string_or_c_char(char* start, int length)
#else
char* aux_p_string_or_c_char(start, length)
char *start;
int length;
#endif
{ 
  if (scan_switch == want_p_strings)
    return auxPascalString(start, length);
  else  
    return auxCChar(start, length);
}
