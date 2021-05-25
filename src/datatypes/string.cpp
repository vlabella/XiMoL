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
	\brief string (implementation).

	\author Tournois Florent
	\version 1.0

    $Id: string.cpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: string.cpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.3  2005/05/12 03:16:15  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 03:11:08  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.2  2004/08/05 16:49:43  tournois
    no message

    Revision 1.1  2004/05/18 12:23:28  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <translation.hpp>
#include <xml/content.hpp>
#include <xml/open_stag.hpp>
#include <xml/attributes.hpp>
#include <xml/stag.hpp>
#include <xml/etag.hpp>
#include <datatypes/string.hpp>

using namespace std;

XIMOL_DATATYPES_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// return the documentation of the type
//-----------------------------------------------------------------------------
xstring const & traits<string_type>::documentation()
{ 
    static const xstring doc(_xtr(
        L"    [Definition:]  The string datatype represents character strings in XML. "
        L"    The value space of string is the set of finite-length sequences of "
        L"    characters (as defined in [XML 1.0 (Second Edition)]) that match the "
        L"    Char production from [XML 1.0 (Second Edition)]. A character is an atomic "
        L"    unit of communication; it is not further specified except to note that "
        L"    every character has a corresponding Universal Character Set code point, "
        L"    which is an integer. "
        L""
        L"    NOTE: Many human languages have writing systems that require child "
        L"    elements for control of aspects such as bidirectional formating or ruby "
        L"    annotation (see [Ruby] and Section 8.2.4 Overriding the bidirectional "
        L"    algorithm: the BDO element of [HTML 4.01]). Thus, string, as a simple "
        L"    type that can contain only characters but not child elements, is often "
        L"    not suitable for representing text. In such situations, a complex type "
        L"    that allows mixed content should be considered. For more information, "
        L"    see Section 5.5 Any Element, Any Attribute "
        L"    of [XML Schema Language: Part 2 Primer]. "
        L""
        L"    NOTE: As noted in ordered, the fact that this specification does not "
        L"    specify an order-relation for string does not preclude other "
        L"    applications from treating strings as being ordered. "
        L"")); 
    return doc;
};

//-----------------------------------------------------------------------------
// Write the type schema on the stream.
//-----------------------------------------------------------------------------
xostream & traits<string_type>::schema_type(xostream & xos)
{ 
    return xos; 
};

//-----------------------------------------------------------------------------
// return the type name of the defined type.
//-----------------------------------------------------------------------------
xstring const & traits<string_type>::schema_type_name()
{ 
    static const string_type name(L"string");
    return name; 
};

//-----------------------------------------------------------------------------
// Write the type schema element on the stream.
//-----------------------------------------------------------------------------
xostream & traits<string_type>::schema_element(xostream & xos, type const & x)
{ 
    xstring schema_uri(find_short_namespace(xos, XIMOL_SCHEMA_URI, "xs"));
    XIMOL_XML_NAMESPACE_PATH::attributes att;
    set_attribute(att, XIMOL_SCHEMA_URI, "name",traits<string_type>::schema_element_name(x));
    set_attribute(att, XIMOL_SCHEMA_URI, "type",schema_uri+L":"+traits<string_type>::schema_type_name());
    set_namespace(att, schema_uri, XIMOL_SCHEMA_URI);
    xos << XIMOL_XML_NAMESPACE_PATH::stag(XIMOL_SCHEMA_URI,L"element",att)
        << XIMOL_XML_NAMESPACE_PATH::etag();
    return xos; 
};

//-----------------------------------------------------------------------------
// Write the type schema element on the stream.
//-----------------------------------------------------------------------------
xstring const & traits<string_type>::schema_element_name(type const & x)
{ 
    static const string_type name(L"string");
    return name; 
};

//-----------------------------------------------------------------------------
// Write the element on the stream.
//-----------------------------------------------------------------------------
xostream & traits<string_type>::write(xostream & xos, type const & x)
{ 
    xos << XIMOL_XML_NAMESPACE_PATH::stag(traits<string_type>::schema_element_name(x));
    traits<string_type>::write_data(xos,x);
    xos << XIMOL_XML_NAMESPACE_PATH::etag();
    return xos; 
};

//-----------------------------------------------------------------------------
// Read the element from the stream.
//-----------------------------------------------------------------------------
xistream & traits<string_type>::read(xistream & xis, type & x)
{ 
    xis >> XIMOL_XML_NAMESPACE_PATH::stag(traits<string_type>::schema_element_name(x));
    traits<string_type>::read_data(xis,x);
    xis >> XIMOL_XML_NAMESPACE_PATH::etag();
    return xis; 
};

//-----------------------------------------------------------------------------
// Write the element data on the stream.
//-----------------------------------------------------------------------------
xostream & traits<string_type>::write_data(xostream & xos, type const & x)
{ 
    return xos << xml::content(x);
};

//-----------------------------------------------------------------------------
// Read the element data from the stream.
//-----------------------------------------------------------------------------
xistream & traits<string_type>::read_data(xistream & xis, type & x)
{
    return xis >> xml::content(x);
};

XIMOL_DATATYPES_END_NAMESPACE

namespace std 
{
    ximol::xostream & operator<<(ximol::xostream & xos, XIMOL_DATATYPES_NAMESPACE_PATH::string_type const & x)
    {
        return XIMOL_DATATYPES_NAMESPACE_PATH::traits<XIMOL_DATATYPES_NAMESPACE_PATH::string_type>::write(xos,x);
    };

    ximol::xistream & operator>>(ximol::xistream & xis, XIMOL_DATATYPES_NAMESPACE_PATH::string_type & x)
    {
        return XIMOL_DATATYPES_NAMESPACE_PATH::traits<XIMOL_DATATYPES_NAMESPACE_PATH::string_type>::read(xis,x);
    }; 
};
