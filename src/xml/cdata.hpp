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
	\brief Define cdata Interface.
	
	\author Tournois Florent
	\version 1.0

    $Id: cdata.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: cdata.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.8  2004/08/05 16:49:44  tournois
    no message

    Revision 1.7  2004/02/25 18:59:13  tournois
    imporve the gcc compatibility.

    Revision 1.6  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.5  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.4  2004/01/29 20:52:35  tournois
    doc and tutorial.

    Revision 1.3  2004/01/19 20:40:55  tournois
    Add min, max and digits facet.
    Create the control flow file.

    Revision 1.2  2004/01/08 20:02:30  tournois
    Add XIMOL_XML_NAMESPACE_PATH::comment and assignment mainuplator.

    Revision 1.1  2004/01/07 21:13:10  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_XML_CDATA_HPP_
#define XIMOL_XML_CDATA_HPP_

#include <parser/utils.hpp>
#include <assignment.hpp>
#include <str_cast.hpp>

XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/// class for the qualified name
//=============================================================================
template < typename T >
class manipulator_cdata
{
public:
    typedef T object_type;

public:
    manipulator_cdata(object_type & x)
        :x_(x)
    {};

    manipulator_cdata(const manipulator_cdata<T> & x)
        :x_(x.x_)
    {};

    void set(const object_type & x)
    {
        assignment_std::equality(x_, x);
    };

    void set_string(xstring const & xstr)
    {
        assignment_char_serialization::equality(x_, xstr);
    };

    const object_type & get() const
    {
        return x_;
    };

    xstring get_string() const
    {
        return str<std::wstring>::cast(x_);
    };

private:
    const manipulator_cdata<T> & operator=(const manipulator_cdata<T> & x);

private:
    object_type & x_;

}; // end of class manipulator_cdata<T>

//-----------------------------------------------------------------------------
// PutTo operator for the cdata.
//-----------------------------------------------------------------------------
template < typename T >
xostream& operator<<(xostream& xos, const manipulator_cdata<T>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    write_cd_sect(xos,m.get_string());
	return xos;
};

//-----------------------------------------------------------------------------
// PutTo operator for the cdata.
//-----------------------------------------------------------------------------
template < typename T >
xistream& operator>>(xistream& xis, manipulator_cdata<T>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    xstring xstr;
    read_cd_sect(xis,xstr);
    m.set_string(xstr);
	return xis;
};

template < typename T > manipulator_cdata<T> cdata( T & t) 
{ 
    return manipulator_cdata<T>(t); 
};

/// Start the CDATA section.
/** @ingroup xml */
XIMOL_DECL
xostream& cdata_start(xostream& xos);

/// Start the CDATA section.
/** @ingroup xml */
XIMOL_DECL
xistream& cdata_start(xistream& xis);

/// Finish the CDATA section.
/** @ingroup xml */
XIMOL_DECL
xostream& cdata_end(xostream& xos);

/// Finish the CDATA section.
/** @ingroup xml */
XIMOL_DECL
xistream& cdata_end(xistream& xis);

XIMOL_XML_END_NAMESPACE

#endif // #ifndef XIMOL_XML_CDATA_HPP_
