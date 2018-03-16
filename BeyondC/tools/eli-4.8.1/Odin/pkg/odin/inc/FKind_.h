#ifndef TP_FKIND
#define TP_FKIND

/* host file */
#define				FK_SrcReg 1
/* host directory */
#define				FK_SrcDir 2
/* link to host file */
#define				FK_SymLinkReg 3
/* link to host directory */
#define				FK_SymLinkDir 4
/* bound host file */
#define				FK_BoundSrc 5
/* bound link to host file */
#define				FK_BoundSymLink 6
/* a dummy file that is just a string */
#define				FK_Str 7
/* produced by user tool */
#define				FK_User 8

/* element of a generated directory object */
#define				FK_DrvDirElm 9
/* element of a virtual directory object */
#define				FK_VirDirElm 10
/* an actual target */
#define				FK_ActTgt 11
/* an actual command target */
#define				FK_ActCmdTgt 12
/* a virtual target */
#define				FK_VirTgt 13
/* a virtual command target */
#define				FK_VirCmdTgt 14
/* an actual target text definition */
#define				FK_ActTgtText 15
/* a virtual target text definition */
#define				FK_VirTgtText 16
/* an actual target executable-text definition */
#define				FK_ActTgtExText 17
/* a virtual target executable-text definition */
#define				FK_VirTgtExText 18
/* pointer homomorphism */
#define				FK_PntrHo 19
/* element of a pointer */
#define				FK_PntrElm 20
/* input pointer (for trailing parameters) */
#define				FK_InpPntr 21
/* an instantiation of a generic (FK_User) */
#define				FK_Instance 22
/* 22 used */

#endif
