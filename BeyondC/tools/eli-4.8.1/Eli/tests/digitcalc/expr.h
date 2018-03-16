#ifndef PAREN_H
#define PAREN_H

#if defined(__STDC__) || defined(__cplusplus)
extern void ExprInt(int i);
#else
extern void ExprInt();
#endif

extern void ExprPlus();
extern void ExprMinus();
extern void ExprTimes();
extern void ExprDiv();
extern void ExprFinl();

#endif
