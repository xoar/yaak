/* $Id: file.h,v 1.2 1994/06/22 06:13:14 waite Exp $ */

#if defined(__cplusplus) || defined(__STDC__)
extern char *pathname(char *partial);
/* Obtain a full path name for a file
 *    On entry-
 *       partial=tail of the desired path name
 *    If the file is in a directory named by INFO_PATHS then on exit-
 *       pathname=full path name
 *    Else on exit-
 *       pathname=partial
 ***/


extern char *make_temp_filename(char *starter);
/* Make a temporary file name
 *    On entry-
 *       starter=initial characters for the file name
 ***/


extern void file_error(char *file);
/* Display system error message
 *    On entry-
 *       filename is the file being processed when the error occurred
 ***/


extern boolean deletefile(char *filename);
/* Delete a file
 *    On entry-
 *       filename is to be deleted
 *    If the deletion is carried out correctly then on exit-
 *       deletefile=true
 *    Else on exit-
 *       deletefile=false
 *       The error has been reported
 ***/


extern boolean printfile(char *filename);
/* Print documentation
 *    On entry-
 *       filename contains the documentation to be printed
 *    If the printing was carried out without errors then on exit-
 *       printfile=true
 *    Else on exit-
 *       printfile=false
 *       The error has been reported
 ***/
#else
extern char * pathname();
extern char * make_temp_filename();
extern void file_error();
extern boolean deletefile();
extern boolean printfile();
#endif
