
#include "envmod.h"

#if defined(__cplusplus) || defined(__STDC__)
extern void MakeSymbOccScopes (Environment env);
extern Environment AddKeyToEnv (Environment env, DefTableKey k);
#else
extern void MakeSymbOccScopes ();
extern Environment AddKeyToEnv ();
#endif
