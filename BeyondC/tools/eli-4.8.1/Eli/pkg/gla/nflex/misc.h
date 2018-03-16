#ifndef MISC_H
#define MISC_H
extern void action_out( void );
extern void skelout( void );
extern void mkdata( int );
extern int myctoi( char[] );
extern int otoi( char[] );
extern void mk2data( int );
extern void flexerror( char[] );
extern void flexfatal( char[] );
extern void bubble( int[], int );
extern void cshell( short[], int );
extern void dataend( void );
extern void line_directive_out( FILE* );
extern void transition_struct_out( int, int );
extern void lerrif( char[], int );
extern void lerrsf( char[], unsigned char[] );
#endif
