
#ifndef DYNSPACE_H
#define DYNSPACE_H

#if defined(__cplusplus) || defined(__STDC__)

/* 
 * Returns: Get a new Environment for the allocation of dynamic Space. 
 */
extern void* InitDynSpace (void);

/* 
 * on Entry:
 *   space points to an Environment that was allocated by InitDynSpace().
 *   size  is the amount of Bytes that have to be allocated dynamically.
 * Returns: A pointer to a dynamically allocated memory portion of size Bytes.
 */
extern void* DynAlloc (void *space, int size);

/*
 * on Entry:
 *   space points to an Environment allocated by InitDynSpace(). There have
 *      been calls to DynAlloc() to allocate dynamic memory in space.
 * on Exit:
 *   all the memory portions returned by DynAlloc() are freed. space now
 *   points to an empty Environment that may be used for DynAlloc() again.
 *   ! None of the pointers previously returned by DynAlloc with space as
 *   ! first parameter may be used afterwards. 
 */
extern void DynClear (void *space);
  
#else

extern void* InitDynSpace ();
extern void* DynAlloc ();
extern void DynClear ();

#endif
#endif
