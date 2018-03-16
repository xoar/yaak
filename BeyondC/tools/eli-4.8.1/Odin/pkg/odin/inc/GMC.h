#ifndef GMC_HEADER
#define GMC_HEADER

typedef int		boolean;
#ifndef FALSE
#define			FALSE 0
#endif
#if (FALSE != 0)
#define			FALSE 0
#endif
#ifndef TRUE
#define			TRUE 1
#endif
#if (TRUE != 1)
#define			TRUE 1
#endif

#ifndef ERROR
#define			ERROR 0
#endif
#if (ERROR != 0)
#define			ERROR 0
#endif

#ifndef NIL
#define			NIL 0
#endif
#if (NIL != 0)
#define			NIL 0
#endif

#if defined(__cplusplus) || defined(__STDC__) || defined(__ANSI__) || \
    defined(__GNUC__) || defined(__STRICT_ANSI__)
#define GMC_ARG(x, y) x y
#define GMC_DCL(x, y)
#define GMC_ARG_VOID void
#define GMC_P1(x) x
#define GMC_PN(x) ,x
#else
#define GMC_ARG(x, y) y
#define GMC_DCL(x, y) x y;
#define GMC_ARG_VOID
#define GMC_P1(x)
#define GMC_PN(x)
#endif

#include "System.hh"
#include "Type.hh"
#include "Var.hh"
#include "Func.hh"
#include "Macro.h"

#endif
