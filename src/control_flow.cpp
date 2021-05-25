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
	\brief control flow (Implementation).

    \author Tournois Florent
	\version 1.0

    $Id: control_flow.cpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: control_flow.cpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.4  2005/05/12 16:15:12  vlabella
    commit in makefile

    Revision 1.1.2.3  2005/05/12 01:30:01  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 01:27:42  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.10  2004/08/05 16:49:42  tournois
    no message

    Revision 1.9  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

    Revision 1.8  2004/02/25 18:58:39  tournois
    imporve the gcc compatibility.

    Revision 1.7  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.6  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.5  2004/02/09 12:41:25  tournois
    Fix bug about error message.
    Add a read_optionnal_space before the stag read.

    Revision 1.4  2004/01/29 20:52:35  tournois
    doc and tutorial.

    Revision 1.3  2004/01/22 22:06:45  tournois
    no message

    Revision 1.2  2004/01/21 21:06:41  tournois
    no message

    Revision 1.1  2004/01/19 20:40:55  tournois
    Add min, max and digits facet.
    Create the control flow file.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <parser/def_signs.hpp>
#include <parser/utils.hpp>
#include <xml/content.hpp>
#include <xml/open_stag.hpp>
#include <translation.hpp>
#include <error.hpp>
#include <control_flow.hpp>

XIMOL_BEGIN_NAMESPACE


//-----------------------------------------------------------------------------
// Turn on the flag to eat all white space.
//-----------------------------------------------------------------------------
xistream& skip_whitespace(xistream& xis)
{
    std::skipws(xis);
    return xis;
};

//-----------------------------------------------------------------------------
// Turn off the flag to eat all white space.
//-----------------------------------------------------------------------------
xistream& no_skip_whitespace(xistream& xis)
{
    std::noskipws(xis);
    return xis;
};

//-----------------------------------------------------------------------------
// Eat all white space.
//-----------------------------------------------------------------------------
xistream& drop_space(xistream& xis)
{
    XIMOL_PARSER_USING_NAMESPACE;
    return read_optionnal_space(xis);
};

//-----------------------------------------------------------------------------
// Eat the content.
//-----------------------------------------------------------------------------
xistream& drop_content(xistream& xis)
{
    XIMOL_XML_NAMESPACE_PATH::char_data_content(xis);
    return xis; 
};

//-----------------------------------------------------------------------------
// Test next element.
//-----------------------------------------------------------------------------
bool is_stag(xistream& xis)
{
    XIMOL_PARSER_USING_NAMESPACE;
	if (!xis.good()) return false;
	if (xis.context.is_open_etag()) return false;
	if (xis.context.is_open_stag()) return true;

    if (has_skip_whitespace(xis)) 
        read_optionnal_space(xis);

	xchar_t xc1,xc2;
	xis.get(xc1);
	xis.get(xc2);
	xis.putback(xc2);
	xis.putback(xc1);
    return ((xc1==XCHAR_LESS_THAN_SIGN) && (is_letter(xc2))); 
};

//-----------------------------------------------------------------------------
// Test next element.
//-----------------------------------------------------------------------------
bool is_etag(xistream& xis)
{
    XIMOL_PARSER_USING_NAMESPACE;
	if (!xis.good()) return false;
	if (xis.context.is_open_etag()) return true;
	if (xis.context.is_open_stag()) return false;

    if (has_skip_whitespace(xis)) 
        read_optionnal_space(xis);

	xchar_t xc1,xc2;
	xis.get(xc1);
	xis.get(xc2);
	xis.putback(xc2);
	xis.putback(xc1);
    return ((xc1==XCHAR_LESS_THAN_SIGN) && (xc2==XCHAR_SOLIDUS)); 
};

//-----------------------------------------------------------------------------
// Drop next element
//-----------------------------------------------------------------------------
xistream& drop_next_element(xistream& xis)
{
	XIMOL_PARSER_USING_NAMESPACE;

	if (!is_stag(xis)) return xis;

	xstring name1, name2, uri1, uri2;
	read_stag(xis, name1, uri1);
	drop_element_until_etag(xis);
	read_etag(xis, name2, uri2);

	if (name1 != name2)
		XIMOL_THROW << _xtr(L"Waiting for an end tag with name='%o' and there is '%o'",str< ::std::string>::cast(name2),str< ::std::string>::cast(name1))
					<< XIMOL_AS_ERROR;
	return xis;
}

//-----------------------------------------------------------------------------
// Drop next element
//-----------------------------------------------------------------------------
xistream& drop_element_until_etag(xistream& xis)
{
	while (drop_content(xis) && is_stag(xis)) drop_next_element(xis);
	return xis;
}

XIMOL_END_NAMESPACE


