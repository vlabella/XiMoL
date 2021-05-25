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
	\brief qualified name (declaration).

	\author Tournois Florent
	\version 1.0

    $Id: qname.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: qname.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.17  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.16  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.15  2004/02/21 20:03:58  tournois
    Change the stag, etag, open_stag, box and rebox template with macro.

    Revision 1.14  2004/01/19 20:40:55  tournois
    Add min, max and digits facet.
    Create the control flow file.

    Revision 1.13  2004/01/18 11:40:58  tournois
    Add the pattern facet.

    Revision 1.12  2004/01/08 20:02:29  tournois
    Add XIMOL_XML_NAMESPACE_PATH::comment and assignment mainuplator.

    Revision 1.11  2004/01/07 21:13:10  tournois
    no message

    Revision 1.10  2004/01/06 21:04:10  tournois
    no message

    Revision 1.9  2003/12/10 20:32:18  tournois
    Fix somes bugs about attributes and now tests are all check.

    Revision 1.8  2003/12/09 19:57:27  tournois
    Fix some bugs about attributes classes.

    Revision 1.7  2003/12/03 12:59:34  hfp
    include dependencies and type forwarding

    Revision 1.6  2003/11/27 15:31:55  hfp
    partially adapted to vc6.

    Revision 1.5  2003/11/19 20:52:54  tournois
    Add new manipulator for stag and etag.
    Correct bugs and add tests.

    Revision 1.4  2003/11/18 18:54:51  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.3  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.2  2003/11/14 11:45:04  tournois
    First try for the stag.

    Revision 1.1  2003/11/13 20:38:48  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_QNAME_HPP_
#define XIMOL_QNAME_HPP_

#include <error.hpp>
#include <typedefs.hpp>
#include <translation.hpp>
#include <str_cast.hpp>
#include <assignment.hpp>

XIMOL_BEGIN_NAMESPACE

//=============================================================================
/// class for the qualified name
//=============================================================================
template < typename Prefix, typename Local >
class qualified_name
{
public:
    typedef Prefix prefix_type;
    typedef Local  local_type;

public:
    qualified_name( prefix_type & prefix, local_type & local )
        :prefix_(&prefix)
        ,local_(local)
    {};

    qualified_name(local_type & local )
        :prefix_(NULL)
        ,local_(local)
    {};

    qualified_name(const qualified_name<Prefix, Local> & x)
        :prefix_(x.prefix_)
        ,local_(x.local_)
    {};

    template < typename T >
    void set_local(const T & local)
    {
        assignment_to_string::equality(local_, local);
    };

    xstring get_local() const { return str< ::std::wstring>::cast(local_); };

    template < typename T >
    void set_prefix(const T & prefix)
    {
        if (prefix_==NULL) 
            XIMOL_THROW << _xtr(L"The prefix could not be set") << XIMOL_AS_ERROR; 
        assignment_to_string::equality(*prefix_, prefix);
    };

    bool is_prefix_set() const { return prefix_!=NULL; }; 
    xstring get_prefix() const { return str< ::std::wstring>::cast(*prefix_); };

private:
    const qualified_name<Prefix, Local> & operator=(const qualified_name<Prefix, Local> & x);

private:
    prefix_type * prefix_;
    local_type & local_;
}; // end of class qualified_name<Uri,Name>

template < typename T, typename U >
qualified_name<T,U> qname(T & prefix, U & local)
{
    return qualified_name<T,U>(prefix,local);
};

template < typename T>
qualified_name<T,T> qname(T & local)
{
    return qualified_name<T,T>(local);
};

XIMOL_END_NAMESPACE

#endif // #ifndef XIMOL_QNAME_HPP_
