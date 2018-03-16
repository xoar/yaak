/* $Id: t.c,v 1.5 1996/03/26 23:34:54 waite Exp $ */

#include <stdio.h>
#include "t.h"

main()
{
	int i;

	for (i = 0; i < number_of_sets; i++) {
		int j;

		(void)printf("%s{", name_of_set[i]);
		for (j = 0; j < size_of_set[i]; j++) {
			(void)printf(" %s", values_of_set[i][j]);
		}
		(void)printf(" }\n");
	}

	return 0;
}
