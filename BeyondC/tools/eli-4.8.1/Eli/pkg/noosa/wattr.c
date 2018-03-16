/*
 * $Id: wattr.c,v 2.11 2005/02/10 09:55:10 asloane Exp $
 * wattr.c
 * Copyright (c) 1995-1999, Anthony M. Sloane
 * The code herein is based on code from:
 *   A. Juutistenaho
 *   "Linear Time Algorithms for Layout of Generalized Trees"
 *   Report A-1994-6, Dept. of Computer Science, University of Tampere
 * with the bugs fixed, code improved and altered a bit to match my data
 * structures.
 */

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

#include <string.h>
#include <stdlib.h>
#include "tcl.h"
#include "tk.h"
#include "noosa.h"

extern Tk_Window noosawin;
extern char *strdup _ANSI_ARGS_ ((const char *));

/*
#define TDEBUG
*/

#define DX 20
#define DY 10

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

typedef struct edgenode_struct edgenode;
typedef struct vertexnode_struct vertexnode;

struct edgenode_struct {
    vertexnode *ToVertex;
    edgenode *Next;
};

struct vertexnode_struct {
    char *Node;
    int Prod, w, e, a, z, RelX, RelY, Xl, g, h;
    edgenode  *EdgeList;
    vertexnode *Next;
};

static int MaxX, MaxY;
static int CurrX, CurrY;
static char strbuf[BUFSIZ];
static Tk_Font font;
static vertexnode *VertexList, *Root;
static int VertexCount;

/* Vertex stack */

static Obstack vstack_obstk;
static vertexnode **vstack;
static int vstacktop;

#define INIT_VSTACK() { \
    vstacktop = 0; \
    obstack_init (&vstack_obstk); \
}
#define PUSH_VSTACK(v) { \
    obstack_ptr_grow (&vstack_obstk, v); \
    vstacktop++; \
    vstack = (vertexnode **) obstack_base (&vstack_obstk); \
}
#define TOPIND_VSTACK()    (vstacktop-1)
#define POP_VSTACK() { \
    if (vstacktop == 0) { \
        Tcl_AppendResult (interp, "vertex stack underflow", (char *) NULL); \
        return TCL_ERROR; \
    } \
    obstack_next_free (&vstack_obstk) -= sizeof (void *); \
    vstacktop--; \
}
#define MULTIPOP_VSTACK(n) { \
    if (vstacktop < (n)) { \
        Tcl_AppendResult (interp, "vertex stack underflow", (char *) NULL); \
        return TCL_ERROR; \
    } \
    obstack_next_free (&vstack_obstk) -= (n) * sizeof (void *); \
    vstacktop -= (n); \
}
#define VSTACK(n)	   (vstack[n])

#ifdef TDEBUG
#define LineTo(i,w,x,y) \
    printf ("LineTo (%d,%d)\n", (x), (y))
#define MoveTo(i,w,x,y) \
    printf ("MoveTo (%d,%d)\n", (x), (y))
#define DrawBox(i,w,x,y,wd,ht) \
    printf ("DrawBox (%d,%d,%d,%d)\n", (x), (y), (wd), (ht))
#define DrawTrName(i,w,r,m,p,x,y,wd,ht) \
    printf ("Name (%s,%s,%d,%d,%d,%d,%d)\n", (r), (m), (p), (x), (y), \
	    (wd), (ht))
#else
#define LineTo(i,w,x,y) { \
    sprintf (strbuf, "n_lrtree_lineto %s %d %d %d %d", w, CurrX, CurrY, \
	     (x), (y)); \
    if (Tcl_Eval (interp, strbuf) == TCL_ERROR) return TCL_ERROR; \
}
#define MoveTo(i,w,x,y)		{ CurrX = (x); CurrY = (y); }
#define DrawBox(i,w,x,y,wd,ht) 
#define DrawTrName(i,w,r,m,p,x,y,wd,ht)	{\
    sprintf (strbuf, "n_lrtree_drawnode %s %s %s %d %d %d\n", (w), (r), \
	     (m), (p), (x)+(wd/2), (y)+(ht/2)); \
    if (Tcl_Eval (interp, strbuf) == TCL_ERROR) return TCL_ERROR; \
}
#endif

/*
 * CalcSubTree
 */

#ifdef PROTO_OK
static void CalcSubTree (vertexnode *v, int *Unseenp)
#else
static void CalcSubTree (v, Unseenp)
    vertexnode *v;
    int *Unseenp;
#endif
{
    edgenode *Edge_i;
    vertexnode *u;
    int Sx, Sy, maxy = 0;
    int leftest = 1000000 /* FIXME: INT_MAX */, rightest = 0;

    if (v->g == 0) {
	/* a leaf */
	v->a = v->w;
	v->z = v->e;
    } else {
	Edge_i = v->EdgeList;
	Sx = -DX;
	Sy = DY + v->e;
	while (Edge_i != (edgenode *) NULL) {
	    /* Edge to child */
	    Sx += DX;
	    u = Edge_i->ToVertex;
	    u->RelX = Sx;
	    u->RelY = Sy;
	    if (u->h == 0)
		CalcSubTree (u, Unseenp);
	    Sx += u->a;
	    maxy = MAX (maxy, u->z);
	    leftest = MIN (leftest, u->RelX + u->Xl);
	    rightest = MAX (rightest, u->RelX + u->Xl + u->w);
	    Edge_i = Edge_i->Next;
	}
	v->z = Sy + maxy;
	if (Sx >= v->w) {
	    v->a = Sx;
	    v->Xl = (rightest + leftest - v->w) / 2;
	} else {
	    /* The width of the parent is larger than that of the children,
	       so the children are located in the middle of the area. */
	    Edge_i = v->EdgeList;
	    while (Edge_i != (edgenode *) NULL) {
		Edge_i->ToVertex->RelX += (v->w - Sx) / 2;
		Edge_i = Edge_i->Next;
	    } 
	    v->a = v->w;
	}
    }

    (*Unseenp)--;
    v->h--;
    MaxY = MAX (v->z, MaxY);
    MaxX = MAX (v->a, MaxX);
}

/*
 * CountTree
 */

#ifdef PROTO_OK
static vertexnode *CountTree (vertexnode *VertexList, int VertexCount)
#else
static vertexnode *CountTree (VertexList, VertexCount)
    vertexnode *VertexList;
    int VertexCount;
#endif
{
    vertexnode *v, *w;
    
    MaxX = MaxY = 0;
    v = VertexList;
    do {
	if (v->h == 0)
	    CalcSubTree (v, &VertexCount);
	w = v;
	v = v->Next;
    } while (VertexCount > 0);
    return w;
}

/*
 * DrawSubTree
 */

#ifdef PROTO_OK
static int DrawSubTree (Tcl_Interp *interp, char *w, char *par,
                        vertexnode *v, int px, int py)
#else
static int DrawSubTree (interp, w, par, v, px, py)
    Tcl_Interp *interp;
    char *w, *par;
    vertexnode *v;
    int px, py;
#endif
{
    edgenode *e;
    int x2;

    px += v->RelX;
    py += v->RelY;
    x2 = px;
    px += v->Xl;
    LineTo (interp, w, px + v->w/2, py);
    DrawBox (interp, w, px, py, v->w, v->e);
    DrawTrName (interp, w, par, v->Node, v->Prod, px, py, v->w, v->e);

    if (v->g > 0) {
	e = v->EdgeList;
	while (e != (edgenode *) NULL) {
	    MoveTo (interp, w, px + v->w/2, py + v->e);
	    if (DrawSubTree (interp, w, v->Node, e->ToVertex,
			     x2, py) == TCL_ERROR)
		return TCL_ERROR;
	    e = e->Next;
	} 
    }
    return TCL_OK;
}

/*
 * DrawTree
 */

#ifdef PROTO_OK
static int DrawTree (Tcl_Interp *interp, char *w, vertexnode *VertexList)
#else
static int DrawTree (interp, w, VertexList)
    Tcl_Interp *interp;
    char *w;
    vertexnode *VertexList;
#endif
{
    MoveTo (interp, w,
	    DX + VertexList->RelX + VertexList->Xl + VertexList->w/2, DY);
    return DrawSubTree (interp, w, "-1", VertexList, DX, DY);
}

/* 
 * BuildListsRoot
 */

#ifdef PROTO_OK
int BuildListsRoot (Tcl_Interp *interp, Tcl_Obj *CONST *objvp[],
                    vertexnode **vertexnodepp, int *countp,
                    vertexnode **rootnodepp)
#else
int BuildListsRoot (interp, objvp, vertexnodepp, countp, rootnodepp)
    Tcl_Interp *interp;
    int *countp;
    vertexnode **vertexnodepp, **rootnodepp;
    Tcl_Obj *CONST *objvp[];
#endif
{
    vertexnode *v, *cv;
    edgenode *e;
    int i, w, h;
    Tcl_Obj *CONST *objv = *objvp;
    CONST char *label;
    char index[20];
    Tk_TextLayout layout;

    if ((v = (vertexnode *) malloc (sizeof (vertexnode))) == NULL) {
	Tcl_AppendResult (interp, "can't allocate memory for vertexnode",
			  (char *) NULL);
	return TCL_ERROR;
    }
    PUSH_VSTACK (v);
    v->Node = strdup (Tcl_GetStringFromObj (objv[0], NULL));
    if (Tcl_GetIntFromObj (interp, objv[1], &(v->Prod)) == TCL_ERROR)
        return TCL_ERROR;
    sprintf (index, "attr,%d,label", v->Prod);
    label = Tcl_GetVar2 (interp, "n", index, TCL_GLOBAL_ONLY);
    (void) Tk_ComputeTextLayout (font, label, strlen (label), -1,
				 TK_JUSTIFY_CENTER, 0, &w, &h);
    v->w = w;
    v->e = h;
    if (Tcl_GetIntFromObj (interp, objv[2], &(v->g)) == TCL_ERROR)
        return TCL_ERROR;
    v->a = v->z = v->h = v->RelX = v->RelY = v->Xl = 0;
    v->Next = *vertexnodepp;
    *vertexnodepp = v;
    (*countp)++;
    if (rootnodepp != (vertexnode **) NULL)
	*rootnodepp = v;
    *objvp += 3;
    
    /* Build the lists for the children */
    v->EdgeList = NULL;
    for (i = 0; i < v->g; i++)
	if (BuildListsRoot (interp, objvp, vertexnodepp, countp, &cv)
	        == TCL_ERROR)
	    return TCL_ERROR;

    /* At this point immediate children are top v->g items on stack */
    for (i = TOPIND_VSTACK () - v->g + 1; i <= TOPIND_VSTACK (); i++) {
	if ((e = (edgenode *) malloc (sizeof (edgenode))) == NULL) {
	    Tcl_AppendResult (interp, "can't allocate memory for edgenode",
			      (char *) NULL);
	    return TCL_ERROR;
	}
	e->ToVertex = VSTACK (i);
	e->Next = v->EdgeList;
	v->EdgeList = e;
    }
    MULTIPOP_VSTACK (v->g);

    return TCL_OK;
}    

/*
 * BuildLists
 */

#ifdef PROTO_OK
int BuildLists (Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[],
                vertexnode **vertexnodepp, int *countp)
#else
int BuildLists (interp, objc, objv, vertexnodepp, countp)
    Tcl_Interp *interp;
    int objc, *countp;
    vertexnode **vertexnodepp;
    Tcl_Obj *CONST objv[];
#endif
{
    /* Check args */
    if (objc % 3 != 0) {
	Tcl_AppendResult (interp, "badly formatted node list", (char *) NULL);
	return TCL_ERROR;
    }

    /* Build a list for the root node and all its children */
    INIT_VSTACK ();
    return BuildListsRoot (interp, &objv, vertexnodepp, countp, NULL);
}

/*
 * FreeTree
 */

#ifdef PROTO_OK
static void FreeTree (vertexnode **vertexnodep, int *countp)
#else
static void FreeTree (vertexnodep, countp)
    vertexnode **vertexnodep;
    int *countp;
#endif
{
    vertexnode *v = *vertexnodep;
    edgenode *e;

    while (v != (vertexnode *) NULL) {
	vertexnode *nv = v->Next;
	e = v->EdgeList;
	while (e != (edgenode *) NULL) {
	    v->EdgeList = e->Next;
	    free ((char *) e);
	    e = v->EdgeList;
	}
	free (v->Node);
	free ((char *) v);
	v = nv;
    }
    *vertexnodep = (vertexnode *) NULL;
    *countp = 0;
}

/*
 * n_lrtree_buildCmd
 */

#ifdef PROTO_OK
int n_lrtree_buildCmd (ClientData notUsed, Tcl_Interp *interp,
                       int objc, Tcl_Obj *CONST objv[])
#else
int n_lrtree_buildCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    Tk_Uid uid;
    static char buf[30];

    if (objc < 3) {
        Tcl_WrongNumArgs (interp, 1, objv, "fontname treenodes...");
	return TCL_ERROR;
    }

    uid = Tk_GetUid (Tcl_GetStringFromObj (objv[1], NULL));
    font = Tk_GetFont (interp, noosawin, uid);

    VertexList = (vertexnode *) NULL;
    VertexCount = 0;
    if (BuildLists (interp, objc-2, objv+2, &VertexList, &VertexCount) ==
	    TCL_ERROR)
	return TCL_ERROR;
    Root = CountTree (VertexList, VertexCount);

    Tk_FreeFont (font);

    sprintf (buf, "%d %d", MaxX + DX, MaxY + DY);
    Tcl_SetResult (interp, buf, TCL_STATIC);
    return TCL_OK;
}

/*
 * n_lrtree_drawCmd
 */

#ifdef PROTO_OK
int n_lrtree_drawCmd (ClientData notUsed, Tcl_Interp *interp,
                      int objc, Tcl_Obj *CONST objv[])
#else
int n_lrtree_drawCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    if (objc != 2) {
        Tcl_WrongNumArgs (interp, 1, objv, "window");
	return TCL_ERROR;
    }

    if (DrawTree (interp, Tcl_GetStringFromObj (objv[1], NULL), Root)
            == TCL_ERROR)
	return TCL_ERROR;
    FreeTree (&VertexList, &VertexCount);

    return TCL_OK;
}
