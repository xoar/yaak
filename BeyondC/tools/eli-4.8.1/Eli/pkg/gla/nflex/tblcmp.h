#ifndef TBLCMP_H
#define TBLCMP_H
extern void bldtbl( int[], int, int, int, int );
extern void cmptmps( void );
extern void expand_nxt_chk( void );
extern int find_table_space( int*, int );
extern void genctbl( void );
extern void gentabs( void );
extern void genecs( void );
extern void inittbl( void );
extern void make_tables( void );
extern void mkdeftbl( void );
extern void mkentry( register int*, int, int, int, int );
extern void mk1tbl( int, int, int, int );
extern void mkprot( int[], int, int );
extern void mktemplate( int[], int, int );
extern void mv2front( int );
extern void ntod( void );
extern void place_state( int*, int, int );
extern void stack1( int, int, int, int );
extern int tbldiff( int[], int, int[] );
#endif
