
#include "chain.h"
#include "TchainList.h"
#include "deftbl.h"
#include "obstack.h"
#include "err.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

static  Obstack Space;
static  void    *Base;
static  TchainList      ChainList = NULLTchainList;
static  struct Tchain   ChainElem[1];

/* TRUE iff ChainElem->lhs == b->lhs.
 * Sets ChainElem->rhs to X.
 */
static  int
#if defined (__cplusplus) || defined(__STDC__)
ChainCmp(Tchain ChainElem, Tchain b)
#else
ChainCmp(ChainElem, b)
Tchain ChainElem, b;
#endif
{
  /* The following implementation of ChainCmp() assumes that it
   * is always called from ElemInTChainList(ChainElem, list, ChainCmp) as
   * ChainCmp(ChainElem, listel).
   */
  if ( ChainElem->lhs == b->lhs )
    {
      ChainElem->rhs = b->rhs;
      return(FALSE);
    } /* of if */
  return(TRUE);
} /* of ChainCmp */


/* ChainMap((A,B)) returns (A,C) if ChainElem == (B,C)
 *                         (A,B) otherwise
 */
static  Tchain
#if defined (__cplusplus) || defined(__STDC__)
ChainMap(Tchain ch)
#else
ChainMap(ch)
Tchain  ch;
#endif
{
  if ( ch->rhs == ChainElem->lhs )
    ch->rhs = ChainElem->rhs;

  return(ch);
} /* of ChainMap */


#ifdef DEBUG
static  Tchain
#if defined (__cplusplus) || defined(__STDC__)
PrintChain(Tchain ch)
#else
PrintChain()
Tchain  ch;
#endif
{
  printf("(%d,%d),\t", ch->lhs, ch->rhs);
  return(ch);
} /* of PrintChain */
#endif

void
#if defined (__cplusplus) || defined(__STDC__)
Initchain(void)
#else
Initchain()
#endif
{
  obstack_init(&Space);
  Base=obstack_alloc(&Space,0);
} /* of Initchain() */

void
#if defined (__cplusplus) || defined(__STDC__)
Freechain(void)
#else
Freechain()
#endif
{
  obstack_free(&Space, Base);
  Base=obstack_alloc(&Space,0);
  FinlTchainList();
} /* of Initchain() */


void
#if defined (__cplusplus) || defined(__STDC__)
Addchain(DefTableKey lhs, DefTableKey rhs)
#else
Addchain(lhs, rhs)
DefTableKey lhs, rhs;
#endif
{
  Tchain        new;

  /* create new chain rule */
  if ( (new = (Tchain)obstack_alloc(&Space, sizeof(*new))) == (Tchain)0)
      message(DEADLY, "No Space for Addchain()", 0, NoPosition);
  new->lhs = lhs;
  new->rhs = rhs;

#ifdef DEBUG
  printf("Add: (%d,%d)", lhs, rhs);
#endif

  ChainElem->lhs = rhs;
  ChainElem->rhs = NoKey;
  if ( ElemInTchainList(ChainElem, ChainList, ChainCmp) )
    new->rhs = ChainElem->rhs;
  else
    ChainElem->rhs = new->rhs;

  ChainElem->lhs = new->lhs;

#ifdef DEBUG
  printf("  =>   (%d,%d)\n", new->lhs, new->rhs);
#endif

  ChainList = MapTchainList(ChainList, ChainMap);

  ChainList = ConsTchainList(new, ChainList);
#ifdef DEBUG
  ChainList = MapTchainList(ChainList, PrintChain);
  printf("\n\n");
#endif

  return;
} /* of  Addchain() */


DefTableKey
#if defined (__cplusplus) || defined(__STDC__)
GetReplKey(DefTableKey lhs)
#else
GetReplKey(lhs)
DefTableKey lhs;
#endif
{
  ChainElem->lhs = lhs;
  ChainElem->rhs = NoKey;
#ifdef DEBUG
  if ( ElemInTchainList(ChainElem, ChainList, ChainCmp) )
    printf("Get(%d): %d\n", lhs,
           (ChainElem->rhs == ChainElem->lhs)? NoKey : ChainElem->rhs );
  else
    printf("Get(%d): %d\n", lhs, lhs);
#endif
  if ( ElemInTchainList(ChainElem, ChainList, ChainCmp) )
    return( (ChainElem->rhs == ChainElem->lhs)? NoKey : ChainElem->rhs );
  else
    return( lhs );
} /* of  GetReplKey() */

