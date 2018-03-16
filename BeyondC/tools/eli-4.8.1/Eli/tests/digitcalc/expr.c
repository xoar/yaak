static char rcsid[] = "$Id: expr.c,v 1.2 1994/08/25 18:21:45 waite Exp $";
/* Postfix calculator */

#include <stdio.h>
#include <stdlib.h>

static int stack[100];		/* Evaluation stack */
static int top = 0;		/* Initially empty */

void
#if defined(__cplusplus) || defined(__STDC__)
ExprInt(int i)
#else
ExprInt(i) int i;
#endif
/* Place an integer value onto the stack */
{
   top++; if (top == 100) { fprintf(stderr, "Stack overflow\n"); exit(1); }
   stack[top] = i;
}

				/* Computations */
void
ExprPlus()
{ top--; stack[top] += stack[top+1]; }

void
ExprMinus()
{ top--; stack[top] -= stack[top+1]; }

void
ExprTimes()
{ top--; stack[top] *= stack[top+1]; }

void
ExprDiv()
{ top--; stack[top] /= stack[top+1]; }

void
ExprFinl()
/* Calculator finalization: Print the top element of the stack */
{ (void)printf("%d\n", stack[top]); }
