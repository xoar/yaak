#define FATALERROR(msg) FatalError(msg, __FILE__, __LINE__)

#ifndef NDEBUG
#ifdef __STDC__
#define FORBIDDEN(test) if (test) FatalError(#test, __FILE__, __LINE__)
#else
#define FORBIDDEN(test) if (test) FatalError("test", __FILE__, __LINE__)
#endif
#else
#define FORBIDDEN(test)
#endif

#define FOREACH_SON(son,root) \
   for (son=Nod_FirstSon(root); son!=NIL; son=Nod_Brother(son))

#define FOREACH_BROTHER(brother, nod) \
   for (brother=Nod_Brother(nod); brother!=NIL; brother=Nod_Brother(brother))

