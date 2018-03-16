char rcsid_zalloc[] = "$Id: zalloc.c,v 1.3 2005/07/29 18:46:44 profw Exp $";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "b.h"

int
fatal(name, line) char *name; int line;
{
	fprintf(stderr, "assertion failed: file %s, line %d\n", name, line);
	exit(1);
	return 0;
}

void *
zalloc(size) unsigned int size;
{
	void *t = (void *) malloc(size);
	if (!t) {
		fprintf(stderr, "Malloc failed---PROGRAM ABORTED\n");
		exit(1);
	}
	memset(t, 0, size);
	return t;
}

void
zfree(p) void *p;
{
	free(p);
}
