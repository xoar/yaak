/*  $Revision: 1.2 $
**
**  Editline system header file for Unix.
*/

#define CRLF		"\r\n"
#define FORWARD		STATIC

#include <sys/types.h>
#include <sys/stat.h>

#ifdef HAVE_DIRENT_H
#include <dirent.h>
typedef struct dirent	DIRENTRY;
#else
#include <sys/dir.h>
typedef struct direct	DIRENTRY;
#endif

#ifndef S_ISDIR
#define S_ISDIR(m)		(((m) & S_IFMT) == S_IFDIR)
#endif	/* !defined(S_ISDIR) */
