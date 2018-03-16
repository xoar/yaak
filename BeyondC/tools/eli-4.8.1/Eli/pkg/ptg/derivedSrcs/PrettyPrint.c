
#include <stdlib.h>
#include <string.h>
#include "PrettyPrint.h"


#ifndef PROTO_OK
static void MEMMOVE(dest, src, len)
char *dest, *src;
int len;
{
   while (len--) *(dest++) = *(src++);
}
#else
#define MEMMOVE(dest,src,len) memmove(dest,src,len)
#endif
 


static char *buffer = 0;
static struct _flagstruct {
        short start;
        short end;
        short lbreak;
} *flags = 0;
static int width = 80;
static int nextwidth = 80;
static int offset = 0;
static int bol_printed = 0;

static int region_top = 0;        /* Indentation level at current position */
static int startline_region = 0;  /* Indentation level at beginning of line */
static int indent = 2;
static char *eol = "\n";

static int linewidth = 80;

static char SoftBreakShortcut = '\0';

static char *unique = "";
static FILE *outputfile = 0;



#ifdef PROTO_OK
void PP_SetLineWidth(int newwidth)
#else
void PP_SetLineWidth(newwidth) int newwidth;
#endif
{
    linewidth = newwidth;
}

#ifdef PROTO_OK
void PP_SetIndentationWidth(int newindent)
#else
void PP_SetIndentationWidth(newindent) int newindent;
#endif
{
    indent = newindent;
}

#ifdef PROTO_OK
void PP_SetEndline(char *new_eol)
#else
void PP_SetEndline(new_eol) char *new_eol;
#endif
{
    eol = new_eol;
}

#ifdef PROTO_OK
void PP_SetSoftBreakShortcut(char sbc)
#else
void PP_SetSoftBreakShortcut(sbc) char sbc;
#endif
{
    SoftBreakShortcut = sbc;
}


static void AcceptChar ELI_ARG((char c));
static void PrintBuffer ELI_ARG((void));

static void PrintNewLine ELI_ARG((int region));static void AcceptSoftBreak ELI_ARG((void));
static void AcceptHardBreak ELI_ARG((void));
static void AcceptOpenRegion ELI_ARG((void));

static void AcceptCloseRegion ELI_ARG((void));
static void Init ELI_ARG((void));
static void PP_PrintString ELI_ARG((PTG_OUTPUT_FILE f, const char *s));
static void PP_PrintChar ELI_ARG((PTG_OUTPUT_FILE f, char c));


#ifdef PROTO_OK
static void AcceptChar(char c)
#else
static void AcceptChar(c) char c;
#endif 
{   
    if (offset >= width && !bol_printed) /* Will exeed buffer now. */
        PrintBuffer();                  /* Print beginning of line */
    
    if (offset < width)            /* Inside of buffer. */
    {   
        buffer[offset++] = c;  /* Store only. */
        return;
    }
    else
    {
        putc(c, outputfile);       /* Print directly if overflow */
        offset++;
    }
}

static void PrintBuffer()
{ 
   register int col;
   int lastcol = -1;



   if (bol_printed)
      return;

   for (col = offset; col >= 0; col--)
      if (flags[col].lbreak)
      {
         lastcol = col;
         break;
      }

   if (lastcol == -1)
   {
      if (offset >= width)
      {
         buffer[offset] = '\0';
         fputs(buffer, outputfile);
         bol_printed = 1;
      }
   }
   else
   {

      col = 0;
      while(42)
      {
         startline_region += flags[col].start;
         startline_region -= flags[col].end;
         if (col == lastcol)
            break;
         putc(buffer[col], outputfile);
         col++;
      }

      PrintNewLine(startline_region);

      if (lastcol < offset)
      {
         offset = (offset - lastcol);   /* #remaining characters */
         MEMMOVE(buffer, buffer+lastcol, sizeof(char)*offset);
         MEMMOVE(flags, flags+lastcol, sizeof(struct _flagstruct)*(offset+1));
         memset(flags+offset+1, 0, (width+1-offset)*sizeof(struct _flagstruct));
         flags[0].lbreak = 0;
      }
      else
      {
         offset = 0;
         memset(flags, 0, (width+1) * sizeof(struct _flagstruct));
      }
      bol_printed = 0;

   }

}

#ifdef PROTO_OK
static void PrintNewLine(int region)
#else
static void PrintNewLine(region) int region;
#endif
{
   static char *spaces = "                                                                                ";
   fputs(eol, outputfile);

   if (indent > 0)
   {
      int required = indent * region;
      while (required > 0)
      {
         char *s = spaces;
         if (required < 80)
            s += (80-required);

         fputs(s, outputfile);
         required -= 80;
      }
   }
   else
   {
      int level;
        
      for (level = 0; level < region; level++)
         putc('\t', outputfile);
   }
   width = nextwidth;
}

static void AcceptSoftBreak()
{
   if (offset < width)
   {  /* Has room in current buffer. */
      flags[offset].lbreak = 1;
   }
   else 
   {  /* Print some piece of the buffer */
      PrintBuffer();

      if (bol_printed)
      {  /* Current line too long */
         PrintNewLine(region_top);
         startline_region = region_top;
         offset = 0;
         memset(flags, 0, (width+1) * sizeof(struct _flagstruct));
         bol_printed = 0;
      }
      else
        flags[offset].lbreak = 1;
   }
}

static void AcceptHardBreak()
{
   if (offset == 0)
   {  /* More than one Hardbreak. */
      PrintNewLine(region_top);
   }
   else
   {
      while (offset > 0)
      {
         if (offset < width)
            flags[offset].lbreak = 1;
         PrintBuffer();

         if (bol_printed)
         {  /* Current line too long */
            PrintNewLine(region_top);
            startline_region = region_top;
            offset = 0;
            memset(flags, 0, (width+1) * sizeof(struct _flagstruct));
            bol_printed = 0;
         }
      }
   }
}

#ifdef PROTO_OK
static void AcceptOpenRegion()
#else
static void AcceptOpenRegion()
#endif
{
   int abs_indentation = (indent < 0 ? 8 : indent);
   if (abs_indentation >= nextwidth)
      return;

   if (offset >= width)
      PrintBuffer();

   region_top++;
   if (offset < width)
        flags[offset].start++;

   nextwidth -= abs_indentation;
   if (offset >= width)
      PrintBuffer();
}

static void AcceptCloseRegion()
{
   int abs_indentation = (indent < 0 ? 8 : indent);
        
   if (region_top == 0)
      return;

   if (offset >= width && !bol_printed)
      PrintBuffer();

   if (offset < width)
      flags[offset].end++;
   region_top--;    
   nextwidth += abs_indentation;
}

static void Init()
{
   width = nextwidth = linewidth;
   if (buffer)
      free(buffer);
   buffer = (char *)malloc((width+1) * sizeof(char));
   if (flags)
      free(flags);    
   flags = (struct _flagstruct *)malloc((width+2) * sizeof(struct _flagstruct));
   if (!buffer || !flags)
   {
      fprintf (stderr, "*** No more memory!\n");
      exit(1);
   }
   memset(flags, '\0', sizeof(struct _flagstruct) * (width+1));

   offset = 0;
   bol_printed = 0;

   region_top = 0;
   startline_region = 0;
}



#ifdef PROTO_OK
void PP_Newline(PTG_OUTPUT_FILE f)
#else
void PP_Newline(f) PTG_OUTPUT_FILE f;
#endif
{
#ifndef NO_CHECK
    if ((char *)(f->destinfo) != unique)
        PTG_OUTPUT_STRING(f, "\n");
    else
#endif
        AcceptHardBreak();
}

#ifdef PROTO_OK
void PP_BreakLine(PTG_OUTPUT_FILE f)
#else
void PP_BreakLine(f) PTG_OUTPUT_FILE f;
#endif
{
#ifndef NO_CHECK
    if ((char *)(f->destinfo) != unique)
        PTG_OUTPUT_STRING(f, "\n");
    else
#endif
        AcceptSoftBreak();
}

#ifdef PROTO_OK
void PP_Indent(PTG_OUTPUT_FILE f)
#else
void PP_Indent(f) PTG_OUTPUT_FILE f;
#endif
{
#ifndef NO_CHECK
    if ((char *)(f->destinfo) != unique)
        return;
#endif
    AcceptOpenRegion();
}

#ifdef PROTO_OK
void PP_Exdent(PTG_OUTPUT_FILE f)
#else
void PP_Exdent(f) PTG_OUTPUT_FILE f;
#endif
{
#ifndef NO_CHECK
    if ((char *)(f->destinfo) != unique)
        return;
#endif
    AcceptCloseRegion();
}       

#ifdef PROTO_OK
static void PP_PrintString(PTG_OUTPUT_FILE f, const char *s)
#else
static void PP_PrintString(f, s) PTG_OUTPUT_FILE f; char *s;
#endif
{
    while (*s)
    {
       
       if (*s == SoftBreakShortcut)
           AcceptSoftBreak();
       else if (*s == '\n')
           AcceptHardBreak();
       else
           AcceptChar(*s);
       
       s++;
    }
}

#ifdef PROTO_OK
static void PP_PrintChar(PTG_OUTPUT_FILE f, char c)
#else
static void PP_PrintChar(f, c) PTG_OUTPUT_FILE f; char c;
#endif
{
   
   if (c == SoftBreakShortcut)
       AcceptSoftBreak();
   else if (c == '\n')
       AcceptHardBreak();
   else
       AcceptChar(c);
   
}

#ifdef PROTO_OK
PTGNode PP_OutFPtr(FILE *f, PTGNode root)
#else
PTGNode PP_OutFPtr(f, root) FILE *f; PTGNode root;
#endif
{
    PtgFilePtr ptgfile = NewPtgFile(unique, PP_PrintString);
    outputfile = f;
    ptgfile->PrintChar = PP_PrintChar;
    
    Init();
    
    PTGProcess(ptgfile, root);
    if (offset > 0)
    {
        if (offset < width)
            flags[offset].lbreak++;
        PrintBuffer();
    }
    FreePtgFile(ptgfile);
    
    return root;
}

#ifdef PROTO_OK
PTGNode PP_Out (PTGNode r)
#else
PTGNode PP_Out (r)
        PTGNode r;
#endif
{
        return PP_OutFPtr(stdout, r);
}

#ifdef PROTO_OK
PTGNode PP_OutFile (char *filename, PTGNode root)
#else
PTGNode PP_OutFile (filename, root)
        char * filename; PTGNode root;
#endif
{
        FILE *f = fopen(filename, "w");
        if (!f)
        {
                fprintf(stderr, "DEADLY: PP_OutFile: output file '%s' can't be opened.\n",
                        filename);
                exit(1);
        }
        PP_OutFPtr(f, root);
        fclose(f);
        return root;
}

