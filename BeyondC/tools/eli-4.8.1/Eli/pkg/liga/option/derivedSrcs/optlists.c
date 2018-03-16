/* $Id: optlists.c,v 1.1 1996/02/06 13:30:25 cogito Exp $ */
/* $Log: optlists.c,v $
 * Revision 1.1  1996/02/06 13:30:25  cogito
 * Initial revision
 *
 * Revision 1.1  1992/11/13  12:43:32  cogito
 * Initial revision
 *
 * Revision 2.2  1991/01/15  18:00:11  cogito
 * new IDL interface
 *
 * Revision 2.1  90/12/04  14:43:40  cogito
 * new version of option handler
 *  */
static char rcs_id[]= "$Id: optlists.c,v 1.1 1996/02/06 13:30:25 cogito Exp $";


/***********************************************************************\
*	lists.c								*
*	functions to build various lists				*
*									*
*	Written 06/21/90 - 10/15/90	by HaDeS			*
\***********************************************************************/

#include <stdio.h>
#include "opt_liga.h"

IdList nullIdList()
/* Return empty IdList	*/
{
	return (NULL);
} /* nullIdList */

IdList creatIdList(e)
SYMB e;
/* Create IdList with the element e	*/
{
	IdList il;

	il= (IdList) malloc (sizeof(struct _idlist));
	il->ident= getelistring (e);
	il->next= NULL;
	return (il);
} /* creatIdList */

IdList concatIdList(l1, l2)
IdList l1, l2;
/* Concatenate IdList l1 and IdList l2	*/
{
	IdList il;

	if (l1==NULL)
		return (l2);
	if (l2==NULL)
		return (l1);
	il= l1;
	while (il->next != NULL)
		il= il->next;
	il->next= l2;
	return (l1);
} /* concatIdList */


ANamesList nullNamesList()
/* Return empty ANamesList	*/
{
	return (NULL);
} /* nullNamesList */

ANamesList creatNamesList(id, ids)
SYMB id;
IdList ids;
/* Create ANameslist with given elements */
{
	ANamesList result;

	result= (ANamesList) malloc (sizeof(struct _anameslist));
	result->symbname= getelistring (id);
	result->names= ids;
	result->next= NULL;
	return (result);
} /* creatNamesList */

ANamesList concatNamesList(l1, l2)
ANamesList l1, l2;
/* Concatenate ANamesList l1 and ANameslIst l2	*/
{
	ANamesList anl;

	if (l1==NULL)
		return (l2);
	if (l2==NULL)
		return (l1);
	anl= l1;
	while (anl->next != NULL)
		anl= anl->next;
	anl->next= l2;
	return (l1);
} /* concatNamesList */

ExpList creatExpOList(e)
ExpOption e;
/* Create List with the element e	*/
{
	ExpList il;

	il= (ExpList) malloc (sizeof(struct _explist));
	il->entry= e;
	il->next= NULL;
	return (il);
} /* creatExpOList */

ExpList concatExpOList(l1, l2)
ExpList l1, l2;
/* Concatenate ExpList l1 and ExpList l2	*/
{
	ExpList il;

	if (l1==NULL)
		return (l2);
	if (l2==NULL)
		return (l1);
	il= l1;
	while (il->next != NULL)
		il= il->next;
	il->next= l2;
	return (l1);
} /* concatExpOList */

OrdList creatOrdOList(e)
OrdOption e;
/* Create OrdList with the element e	*/
{
	OrdList il;

	il= (OrdList) malloc (sizeof(struct _ordlist));
	il->entry= e;
	il->next= NULL;
	return (il);
} /* creatOrdOList */

OrdList concatOrdOList(l1, l2)
OrdList l1, l2;
/* Concatenate OrdList l1 and OrdList l2	*/
{
	OrdList il;

	if (l1==NULL)
		return (l2);
	if (l2==NULL)
		return (l1);
	il= l1;
	while (il->next != NULL)
		il= il->next;
	il->next= l2;
	return (l1);
} /* concatOrdOList */

OptList creatOptOList(e)
OptOption e;
/* Create OptList with the element e	*/
{
	OptList il;

	il= (OptList) malloc (sizeof(struct _optlist));
	il->entry= e;
	il->next= NULL;
	return (il);
} /* creatOptOList */

OptList concatOptOList(l1, l2)
OptList l1, l2;
/* Concatenate OptList l1 and OptList l2	*/
{
	OptList il;

	if (l1==NULL)
		return (l2);
	if (l2==NULL)
		return (l1);
	il= l1;
	while (il->next != NULL)
		il= il->next;
	il->next= l2;
	return (l1);
} /* concatOptOList */

BEList creatBEOList(e)
BEOption e;
/* Create BEList with the element e	*/
{
	BEList il;

	il= (BEList) malloc (sizeof(struct _belist));
	il->entry= e;
	il->next= NULL;
	return (il);
} /* creatBEOList */

BEList concatBEOList(l1, l2)
BEList l1, l2;
/* Concatenate BEList l1 and BEList l2	*/
{
	BEList il;

	if (l1==NULL)
		return (l2);
	if (l2==NULL)
		return (l1);
	il= l1;
	while (il->next != NULL)
		il= il->next;
	il->next= l2;
	return (l1);
} /* concatBEOList */


