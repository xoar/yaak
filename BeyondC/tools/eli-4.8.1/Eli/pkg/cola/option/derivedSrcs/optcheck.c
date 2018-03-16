#include "err.h"

int testval(number, boundary, pos)
int number, boundary;
POSITION *pos;
{
    if (number < boundary)
    {
        char errmsg[50];
	sprintf (errmsg, "This Value must not be smaller than %d", boundary);
	message (ERROR, errmsg, 0, pos);
	return boundary;
    }
    return number;
}

    
