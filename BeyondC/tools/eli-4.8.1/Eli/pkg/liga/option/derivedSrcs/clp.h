#ifndef CLP_H

#define CLP_H
#include "clplib.h"
#include "pdl_gen.h"
#include "DefTableKeyList.h"

extern DefTableKey CLP_InputFile;
#ifdef PROTO_OK
extern void clp_usage (char *);
#else
extern void clp_usage ();
#endif

extern DefTableKey lclfile;
extern DefTableKey expfile;
extern DefTableKey ordfile;
extern DefTableKey optfile;
extern DefTableKey befile;

#endif
