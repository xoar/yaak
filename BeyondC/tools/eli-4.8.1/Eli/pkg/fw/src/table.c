static char RCSid[] = "$Id: table.c,v 1.5 1999/10/20 04:56:54 tony Exp $";
/*##############################################################################

FUNNNELWEB COPYRIGHT
====================
FunnelWeb is a literate-programming macro preprocessor.

Copyright (C) 1992 Ross N. Williams.

   Ross N. Williams
   ross@spam.adelaide.edu.au
   16 Lerwick Avenue, Hazelwood Park 5066, Australia.

This program is free software; you can redistribute it and/or modify
it under the terms of Version 2 of the GNU General Public License as
published by the Free Software Foundation.

This program is distributed WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See Version 2 of the GNU General Public License for more details.

You should have received a copy of Version 2 of the GNU General Public
License along with this program. If not, you can FTP the license from
prep.ai.mit.edu/pub/gnu/COPYING-2 or write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

Section 2a of the license requires that all changes to this file be
recorded prominently in this file. Please record all changes here.

Programmers:
   RNW  Ross N. Williams  ross@spam.adelaide.edu.au
   AMS  Tony Sloane	  asloane@comp.mq.edu.au

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   26-Jul-1992  AMS  Added RCS id.

##############################################################################*/


/******************************************************************************/
/*                                   TABLE.C                                  */
/******************************************************************************/
/*                                                                            */
/* Notes                                                                      */
/* -----                                                                      */
/* - There are few comments at the start of each function. As definitions     */
/*   appear in the .H file, and it is dangerous to duplicate definitions, I   */
/*   have simply omitted them here.                                           */
/*                                                                            */
/* About The Cache                                                            */
/* ---------------                                                            */
/* A typical usage sequence for tables is for the user to first call tb_itb   */
/* to see if a key is in the table and then call either tb_loo or tb_ins      */
/* to lookup the value or to add a new (key,value) pair to the table.         */
/* In order to avoid performing TWO searches down the binary tree in such     */
/* cases, a CACHE is maintained in the table data structure between calls.    */
/*                                                                            */
/* ca_valid stores whether the cache contents are valid. If TRUE then:        */
/* ca_p_key points to a key.                                                  */
/* ca_p_node points to the node in the tree containing the key, or contains   */
/*    NULL if no such node exists.                                            */
/* ca_p_parent points to the node in the tree that is the parent of the node  */
/*    ca_p_node in the tree, or (if ca_p_node==NULL) WOULD BE the parent if a */
/*    node containing the key were inserted in the tree. If the tree is       */
/*    currently empty, ca_p_parent will be NULL.                              */
/*                                                                            */
/******************************************************************************/

#include "style.h"

#include "as.h"
#include "machin.h"
#include "memory.h"

/******************************************************************************/

/* In order to catch uninitialized and corrupted tables, the first and last   */
/* fields of legitimate table objects contain magic numbers. The following    */
/* #defines give the values of these numbers. The first thing that each       */
/* function of this package does is to check the two magic number fields of   */
/* the table it has just been passed, and bomb the package if the fields have */
/* the wrong values. This technique is likely to pick uninitialized tables,   */
/* as well as tables that have been partially overwritten.                    */
#define MAGIC_HEAD_VALUE  (53456839L)
#define MAGIC_TAIL_VALUE  (28434290L)

/* Comparing keys is messy and so we define a macro to help us out.           */
#define key_compare(a,b) ((*(p_tb->p_kycm))((a),(b)))

/******************************************************************************/

/* The functions of the table abstraction pass keys and values exclusively    */
/* using pointers. These two definitions define types for these pointers.     */
/* Although the two types are both 'p_void', the different types are useful   */
/* to indicate what is expected in each position of the parameter lists.      */
typedef p_void p_tbky_t;
typedef p_void p_tbvl_t;

/* Define a type for a function to compare two keys. Such functions are       */
/* needed to organize the storage of (key,value) pairs inside the table.      */
/* Given the arguments are (a,b), the function should return:                 */
/*    -1 if a<b                                                               */
/*     0 if a==b                                                              */
/*     1 if a>b                                                               */
/* The user must create such a function and hand it to the 'tb_create'        */
/* function when creating new a new table.                                    */
typedef sign (*p_kycm_t) P_((p_tbky_t,p_tbky_t));

/* The (key,value) pairs in the table are stored in a binary tree. The tree   */
/* is ordered by the key ordering function passed in at table creation.       */
typedef struct node_t_
  {
   struct node_t_ *p_left;
   struct node_t_ *p_right;
   struct node_t_ *p_parent;
   p_tbky_t        p_key;
   p_tbvl_t        p_value;
  }
  node_t;
typedef node_t *p_node_t;

/* The type tb_t (table type) defines the root table data record. This      */
/* record stores attributes of the table along with the main binary tree of */
/* (key,value) pairs.                                                       */
typedef struct
  {
   ulong     magic_head;       /* Magic number to allow corruption checks.  */
   size_t    key_bytes;        /* Number of bytes in a key.                 */
   size_t    value_bytes;      /* Number of bytes in a value.               */
   p_kycm_t  p_kycm;           /* Pointer to function to compare keys.      */
   p_node_t  tree;             /* Ptr to root of (key,value) binary tree.   */
   ulong     num_keys;         /* Number of (k,v) pairs in the table.       */
   bool      ca_valid;         /* Cache: TRUE iff cache contents are valid. */
   p_tbky_t  ca_p_key;         /* Cache: Key value cache contents refer to. */
   p_node_t  ca_p_node;        /* Cache: Pointer to node in binary tree.    */
   p_node_t  ca_p_parent;      /* Cache: Pointer to parent of ca_p_node.    */
   p_node_t  p_read_next;      /* Pointer to next node to be read.          */
   ulong     magic_tail;       /* Magic number to allow corruption checks.  */
  } tb_t;

typedef tb_t *p_tb_t;           /* Pointer to main table record.            */

/* Defining INTABLEC hides the abstract definition. */
#define INTABLEC
#include "table.h"

/******************************************************************************/
/*                              PRIVATE FUNCTIONS                             */
/******************************************************************************/

LOCAL p_node_t new_node P_((p_tb_t,p_tbky_t,p_tbvl_t));
LOCAL p_node_t new_node(p_tb,p_tbky,p_tbvl)
/* Creates a new tree node and returns a pointer to it.                       */
/* p_tb is the table for which the new node is to be created.                 */
/* p_tbky and p_tbvl point to the key and value to go in the new node.        */
/* Assumes that a tb_check(p_tb) has already been performed by the caller.    */
p_tb_t   p_tb;
p_tbky_t p_tbky;
p_tbvl_t p_tbvl;
{
 p_node_t p_node;

 p_node=(p_node_t) mm_temp(sizeof(node_t));

 p_node->p_left   = NULL;
 p_node->p_right  = NULL;
 p_node->p_parent = NULL;
 p_node->p_key    = mm_temp(p_tb->key_bytes  );
 p_node->p_value  = mm_temp(p_tb->value_bytes);

 memcpy(p_node->p_key  ,p_tbky,p_tb->key_bytes  );
 memcpy(p_node->p_value,p_tbvl,p_tb->value_bytes);

 return p_node;
}

/******************************************************************************/

LOCAL void tb_check P_((p_tb_t));
LOCAL void tb_check(p_tb)
/* Accepts a pointer to a table and performs a series of checks to make sure  */
/* that the table has not been corrupted in some way.                         */
p_tb_t p_tb;
{
 as_cold(p_tb!=NULL,"tb_check: Table pointer is NULL.");
 as_cold(p_tb->magic_head==MAGIC_HEAD_VALUE,
         "tb_check: Magic number at head of record is incorrect.");
 as_cold(p_tb->magic_tail==MAGIC_TAIL_VALUE,
         "tb_check: Magic number at tail of record is incorrect.");
}

/******************************************************************************/

LOCAL p_node_t min_leaf P_((p_node_t));
LOCAL p_node_t min_leaf(p_node)
/* Returns a pointer to the node that is leftmost (has the smallest value     */
/* according to the ordering function) in the specified node's subtree.       */
p_node_t p_node;
{
 if (p_node==NULL)
    return NULL;
 while (p_node->p_left != NULL)
    p_node=p_node->p_left;
 return p_node;
}

/******************************************************************************/

LOCAL p_node_t next_node P_((p_node_t));
LOCAL p_node_t next_node(p_node)
/* Give a pointer to a node in the binary tree, returns a pointer to the next */
/* node (in sequence defined by the order function) or NULL if the given node */
/* is the last node in the ordered sequence.                                  */
p_node_t p_node;
{
 /* If there is a right subtree, we need the minimum node of that subtree.    */
 if (p_node->p_right != NULL)
    return min_leaf(p_node->p_right);

 /* Otherwise go up as far as possible through right arcs. */
 while (p_node->p_parent!=NULL && p_node->p_parent->p_right==p_node)
    p_node=p_node->p_parent;
 return p_node->p_parent;
}

/******************************************************************************/

LOCAL void tb_search P_((p_tb_t,p_tbky_t));
LOCAL void tb_search(p_tb,p_tbky)
/* Calling this function with a particular key value results in the cache     */
/* becoming valid and containing the specified key.                           */
p_tb_t   p_tb;
p_tbky_t p_tbky;
{
 p_node_t p,p_parent;

 tb_check(p_tb);

 /* Return if the cache is already up to date. */
 if (p_tb->ca_valid)
   if (key_compare(p_tbky,p_tb->ca_p_key) == 0)
      return;

  p_parent=NULL;
  p=p_tb->tree;
  while (p != NULL)
     switch(key_compare(p_tbky,p->p_key))
       {
        case -1: p_parent=p; p=p->p_left;  break;
        case  1: p_parent=p; p=p->p_right; break;
        case  0: goto found;
        default:
           as_bomb("tb_search: Key comparison function returned bad value.");
       }
  found:
  p_tb->ca_valid    = TRUE;
  memcpy(p_tb->ca_p_key,p_tbky,p_tb->key_bytes);
  p_tb->ca_p_node   = p;
  p_tb->ca_p_parent = p_parent;
}

/******************************************************************************/

LOCAL void des_tree P_((p_node_t));
LOCAL void des_tree(p_root)
p_node_t p_root;
{
 if (p_root==NULL)
    return;
 des_tree(p_root->p_left);
 des_tree(p_root->p_right);

 /* This is what we would need if it wasn't for the MM watermark system.      */
 /* DEALLOCATE(PV p_root); */
}

/******************************************************************************/
/*                              EXPORTED FUNCTIONS                            */
/******************************************************************************/

EXPORT p_tb_t tb_cre(key_bytes,value_bytes,p_kycm)
size_t   key_bytes;
size_t   value_bytes;
p_kycm_t p_kycm;
{
 p_tb_t p_tb;

 p_tb              = (p_tb_t) mm_temp(sizeof(tb_t));
 p_tb->magic_head  = MAGIC_HEAD_VALUE;
 p_tb->key_bytes   = key_bytes;
 p_tb->value_bytes = value_bytes;
 p_tb->p_kycm      = p_kycm;
 p_tb->tree        = NULL;
 p_tb->num_keys    = 0;
 p_tb->ca_valid    = FALSE;
 p_tb->ca_p_key    = (p_tbky_t) mm_temp(key_bytes);
 p_tb->ca_p_node   = NULL; /* This initialization not strictly necessary. */
 p_tb->ca_p_parent = NULL; /* This initialization not strictly necessary. */
 p_tb->p_read_next = NULL;
 p_tb->magic_tail  = MAGIC_TAIL_VALUE;

 return p_tb;
}

/******************************************************************************/

EXPORT bool tb_itb(p_tb,p_tbky)
p_tb_t   p_tb;
p_tbky_t p_tbky;
{
 tb_check(p_tb);

 tb_search(p_tb,p_tbky);
 return p_tb->ca_p_node != NULL;
}

/******************************************************************************/

EXPORT void tb_loo(p_tb,p_tbky,p_tbvl)
p_tb_t   p_tb;
p_tbky_t p_tbky;
p_tbvl_t p_tbvl;
{
 tb_check(p_tb);

 tb_search(p_tb,p_tbky);
 as_cold(p_tb->ca_p_node!=NULL,"tb_loo: Requested key is absent.");
 memcpy(p_tbvl,p_tb->ca_p_node->p_value,p_tb->value_bytes);
}

/******************************************************************************/

EXPORT void tb_ins(p_tb,p_tbky,p_tbvl)
p_tb_t   p_tb;
p_tbky_t p_tbky;
p_tbvl_t p_tbvl;
{
 p_node_t p_new;

 tb_check(p_tb);

 /* Validate the cache. Note: tb_search does it's own cache check. */
 tb_search(p_tb,p_tbky);

 /* Ensure that the table does not already contain the key. */
 as_cold(p_tb->ca_p_node==NULL,"tb_ins: Key is already present in the p_tb.");

 /* Create the new node. */
 p_new=new_node(p_tb,p_tbky,p_tbvl);

 /* Insert the new node into the tree. */
 if (p_tb->ca_p_parent==NULL)
    p_tb->tree=p_new;
 else
    switch(key_compare(p_tbky,p_tb->ca_p_parent->p_key))
      {
       case -1: p_tb->ca_p_parent->p_left =p_new; break;
       case  1: p_tb->ca_p_parent->p_right=p_new; break;
       default: as_bomb("tb_ins: Key comparison function is inconsistent.");
      }
 p_new->p_parent=p_tb->ca_p_parent;

 /* Need to fiddle cache to make it correct, and inc num_keys. */
 p_tb->ca_p_node=p_new;
 p_tb->num_keys++;
}

/******************************************************************************/

EXPORT ulong tb_len(p_tb)
p_tb_t p_tb;
{
 tb_check(p_tb);
 return p_tb->num_keys;
}

/******************************************************************************/

EXPORT void tb_fir(p_tb)
p_tb_t p_tb;
{
 tb_check(p_tb);

 p_tb->p_read_next=min_leaf(p_tb->tree);
}

/******************************************************************************/

EXPORT bool tb_rea(p_tb,p_tbky,p_tbvl)
p_tb_t    p_tb;
p_tbky_t  p_tbky;
p_tbvl_t  p_tbvl;
{
 tb_check(p_tb);

 if (p_tb->p_read_next == NULL)
    return FALSE;

 memcpy(p_tbky,p_tb->p_read_next->p_key  ,p_tb->key_bytes  );
 memcpy(p_tbvl,p_tb->p_read_next->p_value,p_tb->value_bytes);

 p_tb->p_read_next=next_node(p_tb->p_read_next);

 return TRUE;
}

/******************************************************************************/

#if FALSE
EXPORT void tb_des(p_tb)
p_tb_t p_tb;
{
 /* This routine now unused because of the watermark system. */
 return;

 /* tb_check(p_tb); */

 /* Zap the magic numbers in case the memory is re-used in same alignment. */
 /* p_tb->magic_head=0; */
 /* p_tb->magic_tail=0; */

 /* This is what we would need if it wasn't for the MM watermark system.      */
 /* des_tree(p_tb->tree); */  /* Zap the binary tree. */
 /* DEALLOCATE(PV p_tb);  */  /* Zap the node itself. */
}
#endif

/******************************************************************************/
/*                                   TABLE.C                                  */
/******************************************************************************/

