#ifndef UTIL_H
#define UTIL_H
/* $Id: util.h,v 1.2 1998/02/11 16:43:38 waite Exp $ */

#include "eliproto.h"

extern void set_search_constraints ELI_ARG((char *buffer, size_t extent));
extern size_t to_beg_line ELI_ARG((size_t from));
extern size_t to_end_line ELI_ARG((size_t from));
extern size_t to_end_file_line ELI_ARG((size_t from));
extern size_t back_lines ELI_ARG((size_t count, size_t starting_pos));
extern size_t forward_lines ELI_ARG((size_t count, size_t starting_pos));
extern int search_forward ELI_ARG((char *string, size_t *starting_pos));
extern int search_backward ELI_ARG((char *string, size_t *starting_pos));
extern int string_in_line ELI_ARG((char *string, size_t *pointer));
extern size_t skip_whitespace ELI_ARG((size_t offset));
extern size_t skip_whitespace_and_cr ELI_ARG((size_t offset));
extern boolean
  extract_field ELI_ARG((char *field_name, char *nodename, size_t offset));
extern boolean looking_at ELI_ARG((char *string, size_t pointer));
extern int
  strnicmp ELI_ARG((const char *string1, const char *string2, size_t count));
extern void clean_up ELI_ARG((char *string));

#endif
