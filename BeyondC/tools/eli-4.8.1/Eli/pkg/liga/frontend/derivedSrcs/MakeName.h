
#ifndef MAKENAME_H
#define MAKENAME_H

#if defined(__STDC__) || defined (__cplusplus)
extern int GenerateName (const char *prefix);
extern int MakeName (const char *str);
extern int IdnNumb (int id, int num);
extern int PreIdnPost (const char *pre, int id, const char *post);
#else
extern int GenerateName ();
extern int MakeName ();
extern int IdnNumb ();
extern int PreIdnPost ();
#endif

#endif
