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

    $Id: xml_decl.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: xml_decl.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:46  vlabella
    adding in ximol and xmlparser

    Revision 1.3  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.2  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.1  2004/01/06 21:04:10  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <xml/xml_decl.hpp>
#include <xml/context.hpp>
#include <stream.hpp>
#include <str_cast.hpp>
#include <parser/utils.hpp>

XIMOL_XML_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// Common manipulator.
//-----------------------------------------------------------------------------
xostream& operator<<(xostream& xos, const xml_declaration_alone&)
{
	XIMOL_PARSER_USING_NAMESPACE;
	write_xml_decl(xos,
				 xos.context.get_version_num(),
				 xos.context.get_encoding_decl(),
			     xos.context.get_sd_decl() ? L"yes" : L"no"
	);

	return xos;
}

//-----------------------------------------------------------------------------
// Common manipulator.
//-----------------------------------------------------------------------------
xistream& operator>>(xistream& xis, xml_declaration_alone&)
{
	XIMOL_PARSER_USING_NAMESPACE;

	xstring ver_, enc_;
	bool sdd_;

	read_xml_decl(xis, ver_, enc_, sdd_);

	xis.context.set_version_num(ver_),
	xis.context.set_encoding_decl(enc_),
	xis.context.set_sd_decl(sdd_);

	if (enc_.length() > 1) 
		xis.encoding(str< ::std::string>::cast(enc_).c_str());

	return xis;
}

XIMOL_XML_END_NAMESPACE
