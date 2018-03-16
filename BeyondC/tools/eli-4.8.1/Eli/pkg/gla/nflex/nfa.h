#ifndef NFA_H
#define NFA_H
extern void add_accept( int, int, int );
extern int copysingl( int, int );
extern void dumpnfa( int );
extern int dupmachine( int );
extern int link_machines( int, int );
extern int mkbranch( int, int );
extern int mkclos( int );
extern int mkopt( int );
extern int mkor( int, int );
extern int mkposcl( int );
extern int mkrep( int, int, int );
extern int mkstate( int );
extern void mkxtion( int, int );
#endif
