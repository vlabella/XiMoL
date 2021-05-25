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
	\brief Define comment Interface.
	
	\author Tournois Florent
	\version 1.0

    $Id: comment.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: comment.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.5  2004/08/05 16:49:44  tournois
    no message

    Revision 1.4  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.3  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.2  2004/01/19 20:40:55  tournois
    Add min, max and digits facet.
    Create the control flow file.

    Revision 1.1  2004/01/08 20:02:30  tournois
    Add XIMOL_XML_NAMESPACE_PATH::comment and assignment mainuplator.

    Revision 1.1  2004/01/07 21:13:10  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_XML_COMMENT_HPP_
#define XIMOL_XML_COMMENT_HPP_

#include <sstream.hpp>
#include <parser/utils.hpp>
#include <assignment.hpp>

XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/// class for the qualified name
//=============================================================================
template < typename T >
class manipulator_comment
{
public:
    typedef T object_type;

public:
    manipulator_comment(object_type & x)
        :x_(x)
    {};

    manipulator_comment(const manipulator_comment<T> & x)
        :x_(x.x_)
    {};

    void set(xstring const & x)
    {
        assignment_to_string::equality(x_, x);
    };

    xstring get() const
    {
        return str<std::wstring>::cast(x_);
    };

private:
    const manipulator_comment<T> & operator=(const manipulator_comment<T> & x);

private:
    object_type & x_;

}; // end of class manipulator_comment<T>

//-----------------------------------------------------------------------------
// PutTo operator for the comment.
//-----------------------------------------------------------------------------
template < typename T >
xostream& operator<<(xostream& xos, const manipulator_comment<T>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    write_comment(xos,m.get());
	return xos;
};

//-----------------------------------------------------------------------------
// PutTo operator for the comment.
//-----------------------------------------------------------------------------
template < typename T >
xistream& operator>>(xistream& xis, manipulator_comment<T>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    xstring xstr;
    read_comment(xis,xstr);
    m.set(xstr);
	return xis;
};

template < typename T > manipulator_comment<T> comment( T & t) 
{ 
    return manipulator_comment<T>(t); 
};

XIMOL_XML_END_NAMESPACE

#endif // #ifndef XIMOL_XML_COMMENT_HPP_
