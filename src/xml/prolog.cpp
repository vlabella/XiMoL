/*****************************************************************************\
 *                                                                           *
 * library XiMoL                                                             *
 * Copyright (C) 2002, 2003, 2004 Florent Tournois                           *
 *                                                                           *
 * This library is free software; you can redistribute it and/or             *
 * modify it under the terms of the GNU Lesser General Public                *
 * License as published by the Free Software Foundation; either              *
 * version 2.1 of the License, or (at your option) any later version.        *
 *                                                                           *
 * This library is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Lesser General Public License for more details.                           *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public          *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   *
 *                                                                           *
\*****************************************************************************/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** \file 
	\brief prolog Interface (implementation).

	\author Tournois Florent
	\version 1.0

    $Id: prolog.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: prolog.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:46  vlabella
    adding in ximol and xmlparser

    Revision 1.3  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.2  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.1  2004/01/22 22:01:35  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <xml/prolog.hpp>
#include <parser/utils.hpp>

XIMOL_XML_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// GetFrom operator for the prolog.
//-----------------------------------------------------------------------------
xistream& operator>>(xistream& xis, manip_prolog m)
{
	XIMOL_PARSER_USING_NAMESPACE;
	return read_prolog(xis);
}

//-----------------------------------------------------------------------------
// PutTo operator for the prolog.
//-----------------------------------------------------------------------------
xostream& operator<<(xostream& xos, const manip_prolog& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
	return write_prolog(xos);
}


//-----------------------------------------------------------------------------
// prolog reader-writer
//-----------------------------------------------------------------------------
manip_prolog prolog()
{
	return manip_prolog();
}

XIMOL_XML_END_NAMESPACE
