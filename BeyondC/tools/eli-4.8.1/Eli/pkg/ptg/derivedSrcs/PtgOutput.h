
#ifndef _PTGOUTPUT_H
#define _PTGOUTPUT_H


#ifdef ELI_ARG
#undef ELI_ARG
#endif
#if defined(__STDC__) || defined(__cplusplus)
#define ELI_ARG(p) p
#else
#define ELI_ARG(p) ()
#endif


typedef struct PtgFile_s *PtgFilePtr;

typedef void (*PrintStringFct) ELI_ARG((PtgFilePtr, const char *));
typedef void (*PrintIntFct) ELI_ARG((PtgFilePtr, int));
typedef void (*PrintLongFct) ELI_ARG((PtgFilePtr, long));
typedef void (*PrintShortFct) ELI_ARG((PtgFilePtr, short));
typedef void (*PrintCharFct) ELI_ARG((PtgFilePtr, char));
typedef void (*PrintFloatFct) ELI_ARG((PtgFilePtr, float));
typedef void (*PrintDoubleFct) ELI_ARG((PtgFilePtr, double));

typedef struct PtgFile_s {
        PrintStringFct PrintString;
        PrintIntFct PrintInt;
        PrintLongFct PrintLong;
        PrintShortFct PrintShort;
        PrintCharFct PrintChar;
        PrintFloatFct PrintFloat;
        PrintDoubleFct PrintDouble;

        void *destinfo;
} PtgFile;


extern PtgFilePtr NewPtgFile ELI_ARG((void *destination, PrintStringFct printstring));
extern void FreePtgFile ELI_ARG((PtgFilePtr file));


#endif
