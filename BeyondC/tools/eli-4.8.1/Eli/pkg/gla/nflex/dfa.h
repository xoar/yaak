#ifndef DFA_H
#define DFA_H
extern int *epsclosure( int*, int*, int[], int*, int* );
extern void increase_max_dfas( void );
extern int snstods( int[], int, int[], int, int, int* );
extern int symfollowset( int[],  int,  int, int[] );
extern void sympartition( int[], int, int[], int[] );
#endif
