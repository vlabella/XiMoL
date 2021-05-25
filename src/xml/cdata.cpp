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
	\brief xml_decl implementation.
	
	\author Tournois Florent
	\version 1.0

    $Id: cdata.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: cdata.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.3  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.2  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.1  2004/01/07 21:13:10  tournois
    no message

    Revision 1.1  2004/01/06 21:04:10  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <xml/cdata.hpp>

XIMOL_XML_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// Start the CDATA section.
//-----------------------------------------------------------------------------
xostream& cd_start(xostream& xos)
{
	XIMOL_PARSER_USING_NAMESPACE;
	return write_cd_start(xos);
}

//-----------------------------------------------------------------------------
// Start the CDATA section.
//-----------------------------------------------------------------------------
xistream& cd_start(xistream& xis)
{
	XIMOL_PARSER_USING_NAMESPACE;
	return read_cd_start(xis);
}

//-----------------------------------------------------------------------------
// Finish the CDATA section.
//-----------------------------------------------------------------------------
xostream& cd_end(xostream& xos)
{
	XIMOL_PARSER_USING_NAMESPACE;
	return write_cd_end(xos);
}

//-----------------------------------------------------------------------------
// Finish the CDATA section.
//-----------------------------------------------------------------------------
xistream& cd_end(xistream& xis)
{
	XIMOL_PARSER_USING_NAMESPACE;
	return read_cd_end(xis);
}

XIMOL_XML_END_NAMESPACE
