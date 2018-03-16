#ifndef SYM_H
#define SYM_H
extern void cclinstal( unsigned char[], int );
extern int ccllookup( unsigned char[] );
extern int hashfunct( register unsigned char[], int );
extern void ndinstal( unsigned char[], unsigned char[] );
extern unsigned char *ndlookup( unsigned char[] );
extern void scinstal( unsigned char[], int );
extern int sclookup( unsigned char[] );
#endif
