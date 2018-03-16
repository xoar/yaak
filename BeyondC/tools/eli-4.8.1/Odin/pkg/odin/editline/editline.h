/*  $Revision: 1.1 $
**
**  Internal header file for editline library.
*/

#include "../inc/GMC.h"
#define ANSI_ARROWS
#define HIDE
#define SYS_UNIX

#include <stdio.h>

#include <sys/types.h>
#define SIZE_T	size_t

#ifdef SYS_UNIX
#include "unix.h"
#endif	/* defined(SYS_UNIX) */
#ifdef SYS_OS9
#include "os9.h"
#endif	/* defined(SYS_OS9) */

#ifndef SIZE_T
/*
#define SIZE_T	int
*/
#define SIZE_T	unsigned int
#endif	/* !defined(SIZE_T) */

typedef char	CHAR;
/*
typedef unsigned char	CHAR;
*/

typedef unsigned int 	UINT;

typedef CHAR        *(*MOVE)();

#ifdef HIDE
#define STATIC	static
#else
#define STATIC	/* NULL */
#endif	/* !defined(HIDE) */

#ifndef CONST
#ifdef __STDC__
#define CONST	const
#else
#define CONST
#endif	/* defined(__STDC__) */
#endif	/* !defined(CONST) */


#define MEM_INC		64
#define SCREEN_INC	256

#define DISPOSE(p)	free((char *)(p))
#define NEW(T, c)	\
	((T *)malloc((unsigned int)(sizeof (T) * (c))))
#define RENEW(p, T, c)	\
	(p = (T *)realloc((char *)(p), (unsigned int)(sizeof (T) * (c))))
#define COPYFROMTO(new, p, len)	\
	(void)memcpy((char *)(new), (char *)(p), (int)(len))


/*
**  Variables and routines internal to this package.
*/
extern int	rl_eof;
extern int	rl_erase;
extern int	rl_intr;
extern int	rl_kill;
extern int	rl_quit;
#ifdef DO_SIGTSTP
extern int	rl_susp;
#endif	/* defined(DO_SIGTSTP) */
extern char	*rl_complete();
extern int	rl_list_possib();
extern void	rl_ttyset();
extern void	rl_add_slash();

