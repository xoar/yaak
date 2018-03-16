
#include "PtgOutput.h"
#include <stdio.h>
#include <stdlib.h>


extern void _PTGPrintint ELI_ARG((PtgFilePtr file, int param));
extern void _PTGPrintlong ELI_ARG((PtgFilePtr file, long param));
extern void _PTGPrintshort ELI_ARG((PtgFilePtr file, short param));
extern void _PTGPrintchar ELI_ARG((PtgFilePtr file, char param));
extern void _PTGPrintfloat ELI_ARG((PtgFilePtr file, float param));
extern void _PTGPrintdouble ELI_ARG((PtgFilePtr file, double param));


static char buffer[40];


#if defined(__STDC__) || defined(__cplusplus)
void _PTGPrintint(PtgFilePtr file, int param)
#else
void _PTGPrintint(file, param)
        PtgFilePtr file;
        int param;
#endif
{
        sprintf(buffer, "%d", param);
        file->PrintString(file, buffer);
}


#if defined(__STDC__) || defined(__cplusplus)
void _PTGPrintlong(PtgFilePtr file, long param)
#else
void _PTGPrintlong(file, param)
        PtgFilePtr file;
        long param;
#endif
{
        sprintf(buffer, "%ld", param);
        file->PrintString(file, buffer);
}


#if defined(__STDC__) || defined(__cplusplus)
void _PTGPrintshort(PtgFilePtr file, short param)
#else
void _PTGPrintshort(file, param)
        PtgFilePtr file;
        short param;
#endif
{
        sprintf(buffer, "%d",(int) param);
        file->PrintString(file, buffer);
}


#if defined(__STDC__) || defined(__cplusplus)
void _PTGPrintchar(PtgFilePtr file, char param)
#else
void _PTGPrintchar(file, param)
        PtgFilePtr file;
        char param;
#endif
{
        sprintf(buffer, "%c", param);
        file->PrintString(file, buffer);
}


#if defined(__STDC__) || defined(__cplusplus)
void _PTGPrintfloat(PtgFilePtr file, float param)
#else
void _PTGPrintfloat(file, param)
        PtgFilePtr file;
        float param;
#endif
{
        sprintf(buffer, "%g",(double) param);
        file->PrintString(file, buffer);
}


#if defined(__STDC__) || defined(__cplusplus)
void _PTGPrintdouble(PtgFilePtr file, double param)
#else
void _PTGPrintdouble(file, param)
        PtgFilePtr file;
        double param;
#endif
{
        sprintf(buffer, "%g", param);
        file->PrintString(file, buffer);
}



#if defined(__STDC__) || defined(__cplusplus)
PtgFilePtr NewPtgFile(void *destination, PrintStringFct printstring)
#else
PtgFilePtr NewPtgFile(destination, printstring)
        void *destination;
        PrintStringFct printstring;
#endif
{
        PtgFilePtr n = (PtgFilePtr)malloc(sizeof(PtgFile));
        if (!n)
        {
                fputs("DEADLY: Out of Memory.\n", stderr);
                exit(1);
        }
        n->PrintString = printstring;
        n->PrintInt = _PTGPrintint;
        n->PrintShort = _PTGPrintshort;
        n->PrintLong = _PTGPrintlong;
        n->PrintChar = _PTGPrintchar;
        n->PrintFloat = _PTGPrintfloat;
        n->PrintDouble = _PTGPrintdouble;
        n->destinfo = destination;
        return n;
}

#if defined(__STDC__) || defined(__cplusplus)
void FreePtgFile(PtgFilePtr file)
#else
void FreePtgFile(file)
        PtgFilePtr file;
#endif
{
        free(file);
}

