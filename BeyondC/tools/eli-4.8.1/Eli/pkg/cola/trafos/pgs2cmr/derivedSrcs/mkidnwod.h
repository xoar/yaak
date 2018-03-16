
/* mkidnwod: mkidn WithOut Delimiters */
/* Make an internal string value from a character string
 * This function uses the original function 'mkidn' but
 * leaves the delimiters (first and last character) out.
 * The value of *class will NOT be modified!
 */
extern  void
#if defined(__STDC__) || defined(__cplusplus)
        mkidnwod(char *start, int length, int *class, int *intrinsic);
#else
        mkidnwod();
#endif
