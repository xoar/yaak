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
/* $Id: middle_mem.h,v 4.1 1997/08/29 09:07:44 peter Exp $ */

/********************************************************
*	Module	: middle_mem.h         			*
*	Functions for allocation  and           	*
*       deallocation of memory in liga's middle passes  *
********************************************************/

#ifndef _MIDDLE_MEM_H
#define _MIDDLE_MEM_H
#if defined(__STDC__) || defined(__cplusplus)
extern void init_middle_mem(void);
extern void finish_middle_mem(void);
extern char * middle_Malloc(char *file, int line , unsigned int size);
extern char * middle_tempMalloc(char *file, int line, unsigned int size);
extern void middle_Free(char *file, int line, void *ptr);
extern void middle_tempFree(char *file, int line , void* ptr);
#else
extern void init_middle_mem();
extern void finish_middle_mem();
extern char * middle_Malloc();
extern char * middle_tempMalloc();
extern void middle_Free();
extern void middle_tempFree();
#endif
#endif
