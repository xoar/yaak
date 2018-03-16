
#ifndef SCANSWITCH_H
#define SCANSWITCH_H

#include "args.h"

typedef enum {want_p_strings, want_c_chars} scan_switch_type;

extern scan_switch_type scan_switch;

extern void scan_p_strings FEARGS(( void ));
extern void scan_c_chars FEARGS(( void ));

extern char* aux_p_string_or_c_char FEARGS(( char *start, int length ));

#endif
