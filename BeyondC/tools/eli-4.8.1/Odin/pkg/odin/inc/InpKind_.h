#ifndef TP_INPKIND
#define TP_INPKIND

#define		IK_Simple 1	/* depends on input obj */
#define		IK_Trans 2	/* depends on all elements of input obj */
#define		IK_Name 3	/* depends on the name of the input object */
#define		IK_TransName 4	/* depends on the names of all elements */
#define		IK_Pntr 5	/* IK_Simple, but Pntrs are not deref'ed */
#define		IK_AnyOK 6	/* IK_Trans, but can have error status */

#endif
