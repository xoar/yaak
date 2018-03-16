#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER

#include "config.hh"

#ifdef STDC_HEADERS
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#else
extern int errno;
char *getenv();
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_PROCESS_H
#include <process.h>
#endif

#ifdef HAVE_UNIX_H
#include <unix.h>
#endif

#ifndef FD_SETSIZE
#include <sys/select.h>
#endif

#endif
