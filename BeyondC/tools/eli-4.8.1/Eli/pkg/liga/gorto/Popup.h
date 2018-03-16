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
/* $Id: Popup.h,v 4.1 1997/08/29 08:06:05 peter Exp $ */

/*======================================================================*
 *									*
 *	FILE:		Popup/Popup.h					*
 *									*
 *	CONTENTS:	Shared Header-File for the directory Popup	*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/


/************************************************************************
 *				  Hide.c				*
 ************************************************************************/

EXTERN Widget HidePopup;

EXTERN void HideName();
	/* String	name;	*/
	/* Boolean	hide;	*/

EXTERN void HideCB();
	/* Callback		*/


/************************************************************************
 *				  Lido.c				*
 ************************************************************************/

EXTERN Widget LidoTop;

EXTERN void LidoCB();
	/* Callback	*/

EXTERN void ShowLidoPosition();
	/* int	row;	*/


/************************************************************************
 *				Message.c				*
 ************************************************************************/

EXTERN void Message();
	/* int		did;		*/
	/* String	message;	*/


/************************************************************************
 *			       PopupUtil.c				*
 ************************************************************************/

EXTERN void GetPopupPositions();
	/* int		did;		*/
	/* Position	*x_return;	*/
	/* Position	*y_return;	*/

