
#ifndef __CHAIN_H__
#define __CHAIN_H__

#ifndef ARGS
#if defined (__cplusplus) || defined(__STDC__)
#define ARGS(args)      args
#else
#define ARGS(args)      ()
#endif
#endif

#include "deftbl.h"

typedef struct Tchain
{
  DefTableKey   lhs;
  DefTableKey   rhs;
}       *Tchain;

extern  void    Initchain ARGS((void));
extern  void    Freechain ARGS((void));
extern  void    Addchain ARGS((DefTableKey lhs, DefTableKey rhs));
extern  DefTableKey     GetReplKey ARGS((DefTableKey lhs));

#endif
