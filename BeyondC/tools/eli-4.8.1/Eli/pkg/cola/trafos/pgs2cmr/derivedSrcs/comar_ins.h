#ifndef	COMAR_INS_H
#define	COMAR_INS_H

#include "comar.h"
#include "cmrlib.h"
#include "deftbl.h"

#ifndef ARGS
#if defined (__cplusplus) || defined(__STDC__)
#define ARGS(args)      args
#else
#define ARGS(args)      ()
#endif
#endif

typedef	enum {	P_CODE, P_STOP, P_SEPA, P_BRACKET, P_SKIP,  /*for terminals*/
		P_GRAMMAR, P_CONNECT, P_REDUCE, P_NOREDUCE,  /*for others*/
		P_START					    /*for rules */
} proptype;

typedef	enum {	ALT, OPT, PLUS, STAR, DELREP
} ebnftype;

/*---------------------------------*/
/* SECTION 0: functions for output */
/*---------------------------------*/

extern	void	write_results ARGS((char *filename));

/*------------------------------------------------*/
/* SECTION 1: functions for building symbol table */
/*------------------------------------------------*/

extern	SID	ins_property_name ARGS((proptype prop));
extern	int	ins_eof	ARGS((void));
extern	SID	ins_symbol ARGS((String str, int class));

/*----------------------------------------------------*/
/* SECTION 2: functions for building definition table */
/*----------------------------------------------------*/

#define	NoDid	0

extern def_entry NoDef;	/* initialized with NULL ? */

extern def_entry ins_def ARGS((DefTableKey key, int class, SID sid, DID lhs, SEQunit rhs));
extern def_entry ins_modification ARGS((DefTableKey key, SID sid, proptype m_op));
extern def_entry ins_connect ARGS((DefTableKey key, SID sid));
extern SEQunit	 ins_nullnt ARGS ((DefTableKey key, SEQunit connect));
extern def_entry ins_startrule ARGS((DID start, DID eof, int lhssym));

extern SEQunit	build_rhs ARGS((SEQunit l1, SEQunit l2, int opr));
extern SEQunit	build_elunit ARGS((DID did));
#endif
