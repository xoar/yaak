static char rcsid[] = "$Id: rdsymb.c,v 1.9 2013/10/31 15:41:18 pfahler Exp $";
/* Object file symbol extractor
   Copyright 2002, The Regents of the University of Colorado */

/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include "ofile.h"

#include <stdio.h>

#ifdef STDC_HEADERS
# include <stdlib.h>
# include <string.h>
#endif

#if HAVE_UNISTD_H
# include <sys/types.h>
# include <unistd.h>
#endif

#ifdef HAVE_MALLOC_H
# include <malloc.h>
#else
# if defined(sequent)
extern char *malloc();
# endif
#endif

#ifdef HAVE_FCNTL_H
# include <fcntl.h>
#endif

#ifdef HAVE_ELF_H
# include <elf.h>
#else
# ifdef HAVE_SYS_ELF_H
#  include <sys/elf.h>
# endif
#endif

#ifdef HAVE_A_OUT_H
# include <a.out.h>
#endif

#ifdef HAVE_MACH_O_LOADER_H
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
#endif

#if defined(sun) || defined(linux) && !defined(__ELF__)
# include <sys/file.h>
#endif

#include "symbinfo.h"

/* ELF helper functions */
#if ELF_BINARIES

static int
check_elf_type(int fd, char *file_name)
/* Determine type of ELF file
 *   On entry-
 *     fd=File descriptor to read from
 *     file_name=file from which to obtain the symbols
 *   On exit-
 *     return value=ELFCLASS* (ELFCLASSNONE on error)
 ***/
{
  size_t result;
  Elf32_Ehdr ehdr;

  if ((result = read(fd, &ehdr, sizeof(ehdr))) != sizeof(ehdr)) {
    if (result == -1) perror(file_name);
    else if (result == 0) (void)fprintf(stderr, "%s empty\n", file_name);
    else (void)fprintf(stderr, "%s is not an ELF file\n", file_name);
    return ELFCLASSNONE;
  }
  lseek(fd, SEEK_SET, 0);

  if (ehdr.e_ident[EI_MAG0] != ELFMAG0 || ehdr.e_ident[EI_MAG1] != ELFMAG1
   || ehdr.e_ident[EI_MAG2] != ELFMAG2 || ehdr.e_ident[EI_MAG3] != ELFMAG3) {
    (void)fprintf(stderr, "%s is not an ELF file\n", file_name);
    return ELFCLASSNONE;
  }

  if (EI_VERSION < 1) {
    (void)fprintf(stderr, "Not configured to handle %s\n", file_name);
    return ELFCLASSNONE;
  }

  return ehdr.e_ident[EI_CLASS];
}

#define DEFINE_ELF_READER(SIZE) \
static void \
read_elf_##SIZE##_symbols(int fd, char *file_name) \
/* Read symbols of ELF#SIZE# file \
 *   On entry- \
 *     fd=File descriptor to read from \
 *     file_name=file from which to obtain the symbols \
 *   On exit- \
 *       SymbolInfo(symbol,external) has been invoked for each symbol \
 ***/ \
{ size_t result; \
  Elf##SIZE##_Ehdr ehdr; \
  Elf##SIZE##_Shdr *shdr; \
  Elf##SIZE##_Half shndx; \
  Elf##SIZE##_Sym *symbols = (Elf##SIZE##_Sym *)0; \
  Elf##SIZE##_Sym *limit = (Elf##SIZE##_Sym *)0; \
  Elf##SIZE##_Sym *p; \
  char *section_names, *symbol_strings = (char *)0; \
\
  if ((result = read(fd, &ehdr, sizeof(ehdr))) != sizeof(ehdr)) { \
    if (result == -1) perror(file_name); \
    else if (result == 0) (void)fprintf(stderr, "%s empty\n", file_name); \
    else (void)fprintf(stderr, "%s is not an ELF file\n", file_name); \
    return; \
  } \
\
  if (ehdr.e_type != ET_REL) { \
    (void)fprintf(stderr, "%s is not an object file\n", file_name); \
    exit(1); \
  } \
\
  if (ehdr.e_shstrndx == SHN_UNDEF) { \
    (void)fprintf(stderr, "%s has no section names\n", file_name); \
    exit(1); \
  } \
\
  if (ehdr.e_shoff == 0) return; \
  if (lseek(fd, (off_t)ehdr.e_shoff, SEEK_SET) == -1) { \
    perror(file_name); \
    exit(1); \
  } \
\
  result = ehdr.e_shentsize * ehdr.e_shnum; \
  if (!(shdr = (Elf##SIZE##_Shdr *)malloc(result))) { \
    (void)fprintf(stderr, "No space for section headers\n"); \
    exit(1); \
  } \
  if (read(fd, shdr, result) != result) { \
    (void)fprintf(stderr, "%s: Error reading section headers\n", file_name); \
    exit(1); \
  } \
\
  if (!(section_names = (char *)malloc((unsigned)shdr[ehdr.e_shstrndx].sh_size))) { \
    (void)fprintf(stderr, "No space for section names\n"); \
    exit(1); \
  } \
  if (lseek(fd, (off_t)shdr[ehdr.e_shstrndx].sh_offset, SEEK_SET) == -1) { \
    (void)fprintf (stderr, "Cannot find section names: %s\n", file_name); \
    exit(1); \
  } \
  if (read(fd, section_names, (size_t)shdr[ehdr.e_shstrndx].sh_size) != shdr[ehdr.e_shstrndx].sh_size) { \
    (void)fprintf (stderr, "Cannot read section names: %s\n", file_name); \
    exit(1); \
  } \
\
  for (shndx = 0; shndx < ehdr.e_shnum; shndx++) { \
    if (shdr[shndx].sh_type == SHT_SYMTAB && \
        strcmp(section_names + shdr[shndx].sh_name,".symtab") == 0) { \
      if (!(symbols = (Elf##SIZE##_Sym *)malloc((unsigned)shdr[shndx].sh_size))) { \
        (void)fprintf(stderr, "No space for symbol table\n"); \
        exit(1); \
      } \
      limit = symbols + (shdr[shndx].sh_size / shdr[shndx].sh_entsize); \
      if (lseek(fd, (off_t)shdr[shndx].sh_offset, SEEK_SET) == -1) { \
        (void)fprintf (stderr, "Cannot find symbol table: %s\n", file_name); \
        exit(1); \
      } \
      if (read(fd, symbols, (size_t)shdr[shndx].sh_size) != shdr[shndx].sh_size) { \
        (void)fprintf (stderr, "Cannot read symbol table: %s\n", file_name); \
        exit(1); \
      } \
    } else if (shdr[shndx].sh_type == SHT_STRTAB && \
               strcmp(section_names + shdr[shndx].sh_name,".strtab") == 0) { \
      if (shndx == ehdr.e_shstrndx) symbol_strings = section_names; \
      else { \
        if (!(symbol_strings = (char *)malloc((unsigned)shdr[shndx].sh_size))) { \
          (void)fprintf(stderr, "No space for symbol strings\n"); \
          exit(1); \
        } \
        if (lseek(fd, (off_t)shdr[shndx].sh_offset, SEEK_SET) == -1) { \
          (void)fprintf (stderr, "Cannot find symbol strings: %s\n", file_name); \
          exit(1); \
        } \
        if (read(fd, symbol_strings, (size_t)shdr[shndx].sh_size) != shdr[shndx].sh_size) { \
          (void)fprintf (stderr, "Cannot read symbol strings: %s\n", file_name); \
          exit(1); \
        } \
      } \
    } \
  } \
\
  for (p = symbols; p < limit; p++) { \
    if (ELF##SIZE##_ST_BIND(p->st_info) == STB_GLOBAL) { \
      if (p->st_shndx == SHN_UNDEF) \
        SymbolInfo(symbol_strings+p->st_name, 1); \
      else \
        SymbolInfo(symbol_strings+p->st_name, 0); \
    } \
  } \
\
  free(symbol_strings); \
  free(symbols); \
  free(shdr); \
}


DEFINE_ELF_READER(32);
DEFINE_ELF_READER(64);


#endif /* ELF_BINARIES */
/* End of ELF helper functions */


/***/
void
#if defined(__cplusplus) || defined(__STDC__)
read_symbols(char *file_name)
#else
read_symbols(file_name)
char *file_name;
#endif
/* Obtain symbol information
 *    On entry-
 *       file_name=file from which to obtain the symbols
 *    On exit-
 *       SymbolInfo(symbol,external) has been invoked for each symbol
 ***/
{
#if ELF_BINARIES

  int fd;

  if ((fd = open (file_name, O_RDONLY, 0)) == -1) {
    (void)fprintf(stderr, "Cannot open executable: %s\n", file_name);
    exit(1);
  }

  switch (check_elf_type(fd, file_name)) {

  case ELFCLASS32:
    read_elf_32_symbols(fd, file_name);
    break;

  case ELFCLASS64:
    read_elf_64_symbols(fd, file_name);
    break;

  case ELFCLASSNONE:
  default:
    exit(1); /* Fatal error, already signalled */

  }

  (void)close(fd);
#else /* Not ELF_BINARIES */

#ifdef COFF_BINARIES
# if defined(__CYGWIN__)
#   undef  FILHDR
#   define FILHDR struct external_filehdr
#   undef  FILHSZ
# endif

# if defined(__alpha) || defined(mips)
#   define SYMENT EXTR
#   define SYMESZ cbEXTR
#   define NUMSYMS symheader.iextMax
  HDRR symheader;
# endif

# ifndef O_BINARY
#   define O_BINARY 0
# endif

# ifndef FILHDR
#   define FILHDR  struct filehdr
# endif

# ifndef FILHSZ
#   define FILHSZ 20
# endif

# ifndef SYMENT
#   define SYMENT  struct syment
# endif

# ifndef SYMESZ
#   define SYMESZ 18
# endif

# ifndef NUMSYMS
#   define NUMSYMS header.f_nsyms
# endif

# ifndef C_EXT
#   define C_EXT  2
# endif

  int fd;
  FILHDR header;
  SYMENT *symbol_table;
  uint32_t string_table_size;  /* uint32_t is the type used in the object file header */
  char *string_table;
  int i;
    
  if ((fd = open(file_name, O_RDONLY|O_BINARY)) == -1) {
    (void)fprintf(stderr, "Cannot open executable: %s\n", file_name);
    exit(1);
  }
  if (read (fd, &header, FILHSZ) != FILHSZ) {
    (void)fprintf (stderr, "Cannot read header: %s\n", file_name);
    exit(1);
  }
  if (lseek (fd, (off_t)header.f_symptr, SEEK_SET) == -1) {
    perror(file_name);
    exit(1);
  }

# if defined(__alpha) || defined(mips)
  if (read (fd, &symheader, cbHDRR) != cbHDRR) {
    (void)fprintf (stderr, "Cannot read symbol header: %s\n", file_name);
    exit(1);
  }
  if (lseek (fd, (off_t)symheader.cbExtOffset, SEEK_SET) == -1) {
    perror(file_name);
    exit(1);
  }
# endif

  symbol_table = (SYMENT *)malloc(sizeof(SYMENT) * NUMSYMS);
  for (i = 0; i < NUMSYMS; i++) read(fd, &symbol_table[i], SYMESZ);

# if defined(__alpha) || defined(mips)
  if (lseek (fd, (off_t)symheader.cbSsExtOffset, SEEK_SET) == -1) {
    perror(file_name);
    exit(1);
  }
  string_table_size = symheader.issExtMax;
# else
  if (read (fd, &string_table_size, 4) != 4) {
    (void)fprintf (stderr, "Cannot read string table size: %s\n", file_name);
    exit(1);
  }
  string_table_size -= 4;
# endif

  string_table = (char *)malloc(string_table_size);
  if (read (fd, string_table, string_table_size) != string_table_size) {
    (void)fprintf (stderr, "Cannot read string table: %s\n", file_name);
    exit(1);
  }

  for (i = 0; i < NUMSYMS; i++) {
# if defined(__alpha) || defined(mips)
    if (symbol_table[i].asym.st == stGlobal ||
        symbol_table[i].asym.st == stProc) {
      SymbolInfo(string_table + symbol_table[i].asym.iss,
        symbol_table[i].asym.sc == scNil ||
        symbol_table[i].asym.sc == scUndefined ||
        symbol_table[i].asym.sc == scSUndefined);
    }
# else
    if (symbol_table[i].e_sclass[0] == C_EXT) {
      if (symbol_table[i].e.e.e_zeroes) {
        char fixer[9];
        strncpy(fixer, symbol_table[i].e.e_name, 8);
        fixer[8] = '\000';
        SymbolInfo(
          fixer,
          symbol_table[i].e_scnum == 0 && symbol_table[i].e_value == 0);
      } else {
        SymbolInfo(
          string_table + symbol_table[i].e.e.e_offset - 4,
          symbol_table[i].e_scnum == 0 && symbol_table[i].e_value == 0);
      }
    }
# endif
  }
  (void)close(fd);
#else	/* Not COFF binaries */

#ifdef MACH_O_BINARIES
  int fd, i;
  struct mach_header header;
  off_t offset, position;
  char *string_table;
#ifdef MH_MAGIC_64          
  int is64bit = 0;
#endif
    
  if ((fd = open (file_name, O_RDONLY, 0)) == -1) {
    (void)fprintf (stderr, "Cannot open executable: %s\n", file_name);
    exit(1);
  }
  if (read(fd, (char *)&header, sizeof(header)) != sizeof(header)) {
    (void)fprintf(stderr, "Cannot read exec header: %s\n", file_name);
    exit(1);
  }
  if (header.magic != MH_MAGIC) {
#ifdef MH_MAGIC_64
    if (header.magic == MH_MAGIC_64) {
      is64bit = 1;
    } else {
#endif      
      (void)fprintf(stderr, "Wrong magic number: %s\n", file_name);
      exit(1);
#ifdef MH_MAGIC_64
    }
#endif      
  }
  /* This relies on the 64 bit header being the same as the 32 bit header
     except for some reserved padding at the end so we can use the 32 bit
     header structure but adjust the offset here so that we skip the padding. */
#ifdef MH_MAGIC_64     
  if (is64bit) {
    offset = sizeof(struct mach_header_64);
    if (lseek(fd, offset, SEEK_SET) == -1) { perror(file_name); exit(1); }
  } else
#endif
    offset = sizeof(struct mach_header);
  for (i = 0; i < header.ncmds; i++) {
    struct load_command command;
    if (read(fd, (char *)&command, sizeof(command)) != sizeof(command)) {
      (void)fprintf(stderr, "Cannot read load command: %s\n", file_name);
      exit(1);
    }
    if (command.cmd == LC_SYMTAB) {
      struct symtab_command symspec;
      int j;

      if (lseek(fd, offset, SEEK_SET) == -1) { perror(file_name); exit(1); }
      if (read(fd, (char *)&symspec, sizeof(symspec)) != sizeof(symspec)) {
        (void)fprintf(stderr, "Cannot read symtab command: %s\n", file_name);
        exit(1);
      }
      string_table = (char *)malloc((size_t)symspec.strsize);
      if (lseek(fd, (off_t)symspec.stroff, SEEK_SET) == -1) {
        perror(file_name);
        exit(1);
      }
      if (read(fd, string_table, (size_t)symspec.strsize) != symspec.strsize) {
        (void)fprintf(stderr, "Cannot read string table: %s\n", file_name);
        exit(1);
      }
      if (lseek(fd, (off_t)symspec.symoff, SEEK_SET) == -1) {
        perror(file_name);
        exit(1);
      }
      
#define HANDLE_SYMBOL \
  if (read(fd, &syment, sizeof(syment)) != sizeof(syment)) { \
    (void)fprintf(stderr, "Cannot read symtab entry: %s\n", file_name); \
    exit(1); \
  } \
  /* Ignore .eh symbols (exception handlers?) */ \
  if (strncmp (string_table + syment.n_un.n_strx + \
                  strlen (string_table + syment.n_un.n_strx) - 3, ".eh", 3) == 0) \
    continue; \
  if (syment.n_type & N_EXT) \
    SymbolInfo( \
      string_table + syment.n_un.n_strx, \
      (syment.n_type & N_TYPE) == N_UNDF && syment.n_value == 0);

      for (j = 0; j < symspec.nsyms; j++) {
#ifdef MH_MAGIC_64          
        if (is64bit) {
          struct nlist_64 syment;
          HANDLE_SYMBOL
        } else {
#endif
          struct nlist syment;
          HANDLE_SYMBOL
#ifdef MH_MAGIC_64
        }
#endif
      }
      free(string_table);
      break;
    }
    offset += command.cmdsize;
    if (lseek(fd, offset, SEEK_SET) == -1) { perror(file_name); exit(1); }
  }
  (void)close(fd);
#else /* Not MACH_O_BINARIES */

#if defined(sun)
  int fd;
  struct exec header;
  struct nlist *symbol_table;
  int number_symbols;
  int string_table_size;
  char *string_table;
  int i;
    
  if ((fd = open (file_name, O_RDONLY, 0)) == -1) {
    (void)fprintf (stderr, "Cannot open executable: %s\n", file_name);
    exit(1);
  }
  if (read (fd, (char *)&header, sizeof (struct exec)) != sizeof (struct exec))
    (void)fprintf (stderr, "Cannot read exec header: %s\n", file_name);
  if (lseek (fd, (long)N_SYMOFF (header), L_SET) == -1)
    (void)fprintf (stderr, "Cannot read symbol table: %s\n", file_name);
  symbol_table = (struct nlist *) malloc ((unsigned)header.a_syms);
  if (read (fd, (char *)symbol_table, (int)header.a_syms) != header.a_syms)
    (void)fprintf (stderr, "Cannot read symbol table: %s\n", file_name);
  if (read (fd, (char *)&string_table_size, sizeof (int)) != sizeof (int))
    (void)fprintf (stderr, "Cannot read string table: %s\n", file_name);
  string_table = (char *) malloc ((unsigned)string_table_size);
  if (read (fd, (char *)string_table + sizeof(int), string_table_size - sizeof(int))
      != string_table_size - sizeof (int))
    (void)fprintf (stderr, "Cannot read string table: %s\n", file_name);
  
  number_symbols = header.a_syms / sizeof (struct nlist);
  for (i = 0; i < number_symbols; i++) {
    if (symbol_table[i].n_type & N_EXT)
      SymbolInfo(string_table + symbol_table[i].n_un.n_strx,
        (symbol_table[i].n_type == N_EXT)
        && !symbol_table[i].n_value);
  }
  if (symbol_table) free ((char *)symbol_table);
  if (string_table) free ((char *)string_table);
  (void)close (fd);
#else /* Not sun */

#if defined(hpux)
#if defined(__hp9000s800)
  int fd;
  FILHDR head;
  SYMENT symbol;
  char *symbol_strings;
  int count;
    
  if ((fd = open (file_name, O_RDONLY, 0)) == -1) {
    (void)fprintf (stderr, "Cannot open executable: %s\n", file_name);
    exit(1);
  }
  if (read (fd, (char *)&head, FILHSZ) != FILHSZ) {
    (void)fprintf (stderr, "Cannot read header: %s\n", file_name);
    exit(1);
  }

  if (lseek (fd, (off_t)(head.symbol_strings_location), SEEK_SET) == -1) {
    (void)fprintf (stderr, "Cannot find symbol strings: %s\n", file_name);
    exit(1);
  }
  symbol_strings = (char *) malloc ((unsigned)head.symbol_strings_size);
  if (read (fd, (char *)symbol_strings, (size_t)head.symbol_strings_size) != head.symbol_strings_size) {
    (void)fprintf (stderr, "Cannot read symbol strings: %s\n", file_name);
    exit(1);
  }
  
  if (lseek (fd, (off_t)(head.symbol_location), SEEK_SET) == -1) {
    (void)fprintf (stderr, "Cannot find symbol table: %s\n", file_name);
    exit(1);
  }
  for (count = 1; count <= head.symbol_total; count++) {
    if (read (fd, (char *)&symbol, SYMESZ) != SYMESZ) {
      (void)fprintf (stderr, "Cannot read symbol table: %s\n", file_name);
      exit(1);
    }
    if (symbol.symbol_type == ST_STORAGE)
      SymbolInfo(symbol_strings+symbol.name.n_strx, 0);
    else if (symbol.symbol_type == ST_CODE ||
             symbol.symbol_type == ST_DATA ||
             symbol.symbol_type == ST_ENTRY) {
      if (symbol.symbol_scope == SS_UNSAT)
        SymbolInfo(symbol_strings+symbol.name.n_strx, 1);
      if (symbol.symbol_scope == SS_UNIVERSAL)
        SymbolInfo(symbol_strings+symbol.name.n_strx, 0);
    }
  }
    
  if (symbol_strings) free ((void *)symbol_strings);
  (void)close (fd);
#else
  int fd;
  struct exec header;
  char *symbol_table, *syms, *symbol_limit;
  struct nlist_ *nl;
  char buf[257];
    
  if ((fd = open (file_name, O_RDONLY, 0)) == -1)
    (void)fprintf (stderr, "Cannot open executable: %s\n", file_name);
  if (read (fd, (char *)&header, sizeof (struct exec)) != sizeof (struct exec))
    (void)fprintf (stderr, "Cannot read exec header: %s\n", file_name);
  if (lseek (fd, (off_t)(LESYM_OFFSET(header)), SEEK_SET) == -1)
    (void)fprintf (stderr, "Cannot read symbol table: %s\n", file_name);
  symbol_table = (char *) malloc ((unsigned)header.a_lesyms);
  if (read (fd, (char *)symbol_table, (size_t)header.a_lesyms) != header.a_lesyms)
    (void)fprintf (stderr, "Cannot read symbol table: %s\n", file_name);
  symbol_limit = symbol_table + header.a_lesyms;
  
  for (syms = symbol_table; syms < symbol_limit;) {
    nl = (struct nlist_ *)syms;
    (void)strncpy (buf, ((char *)nl) + sizeof (struct nlist_), 
       (size_t)(nl->n_length));
    buf[nl->n_length] = '\0';
    SymbolInfo(buf, (nl->n_type == N_EXT) && !nl->n_value); 
    syms += sizeof (struct nlist_) + nl->n_length;
  }
    
  if (symbol_table) free ((void *)symbol_table);
  (void)close (fd);
#endif /* Not hpux */
#else

  int fd;
  struct exec header;
  struct nlist *symbol_table;
  int number_symbols;
  int string_table_size;
  char *string_table;
  int i;
    
  if ((fd = open (file_name, O_RDONLY, 0)) == -1) {
    (void)fprintf (stderr, "Cannot open executable: %s\n", file_name);
    exit(1);
  }
  if (read (fd, (char *)&header, sizeof (struct exec)) != sizeof (struct exec))
    (void)fprintf (stderr, "Cannot read exec header: %s\n", file_name);
  if (lseek (fd, (off_t)N_SYMOFF (header), SEEK_SET) == -1)
    (void)fprintf (stderr, "Cannot read symbol table: %s\n", file_name);
  symbol_table = (struct nlist *) malloc ((unsigned)header.a_syms);
  if (read (fd, (char *)symbol_table, (int)header.a_syms) != header.a_syms)
    (void)fprintf (stderr, "Cannot read symbol table: %s\n", file_name);
  if (read (fd, (char *)&string_table_size, sizeof (int)) != sizeof (int))
    (void)fprintf (stderr, "Cannot read string table: %s\n", file_name);
  string_table = (char *) malloc ((unsigned)string_table_size);
  if (read (fd, (char *)string_table + sizeof(int), string_table_size - sizeof(int))
      != string_table_size - sizeof (int))
    (void)fprintf (stderr, "Cannot read string table: %s\n", file_name);
  
  number_symbols = header.a_syms / sizeof (struct nlist);
  for (i = 0; i < number_symbols; i++) {
    if (symbol_table[i].n_type & N_EXT)
      SymbolInfo(string_table + symbol_table[i].n_un.n_strx,
        (symbol_table[i].n_type == N_EXT)
        && !symbol_table[i].n_value);
  }
  if (symbol_table) free (symbol_table);
  if (string_table) free (string_table);
  (void)close (fd);
#endif
#endif
#endif
#endif
#endif
}
