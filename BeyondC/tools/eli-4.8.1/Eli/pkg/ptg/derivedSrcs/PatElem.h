
#ifndef PATELEM_H
#define PATELEM_H
#include "deftbl.h"

typedef enum {INSERT, CSTRING, CALL, OPTION} PatKind;
typedef struct 
 { PatKind kind;
   union { DefTableKey key;
           int         index;
         } data;
 } *PatElem, PatElemStruct;

extern 
PatElem newPatElem (PatKind kd, DefTableKey k, int i);

extern 
int cmpPatElem (PatElem, PatElem);

#endif
