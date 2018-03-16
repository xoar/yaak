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

#define FOREACH_CLIENT(Client) for(Client=FirstClient;Client!=NIL;Client=Client_Next(Client)) if (Is_ActiveClient(Client))

