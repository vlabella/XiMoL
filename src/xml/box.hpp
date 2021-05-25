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
	\brief Define box Interface.
	
	\author Tournois Florent
	\version 1.0

    $Id: box.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: box.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.7  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.6  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.5  2004/02/21 20:03:58  tournois
    Change the stag, etag, open_stag, box and rebox template with macro.

    Revision 1.4  2004/02/04 11:42:25  tournois
    no message

    Revision 1.3  2004/01/25 17:32:56  tournois
    no message

    Revision 1.2  2004/01/15 21:26:01  tournois
    no message

    Revision 1.1  2004/01/09 18:26:29  tournois
    Add box and content manipulator.

    Revision 1.5  2003/12/10 20:32:18  tournois
    Fix somes bugs about attributes and now tests are all check.

    Revision 1.4  2003/12/09 19:57:28  tournois
    Fix some bugs about attributes classes.

    Revision 1.3  2003/12/03 12:50:37  hfp
    include dependencies and type forwarding

    Revision 1.2  2003/11/27 15:31:55  hfp
    partially adapted to vc6.

    Revision 1.1  2003/11/19 20:52:54  tournois
    Add new manipulator for stag and etag.
    Correct bugs and add tests.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_XML_BOX_HPP_
#define XIMOL_XML_BOX_HPP_

#include <xml/stag.hpp>
#include <xml/etag.hpp>
#include <parser/utils.hpp>

XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/// Manipulator for the start tag.
//=============================================================================
template < typename String1, typename String2, typename Att, typename T >
struct manipulator_box 
{
public:
    typedef qualified_name<String1,String2> qname_type;
    typedef manipulator_stag< qname_type, Att> stag_type;
public:
    manipulator_box(const stag_type & stag, T & t):stag_(stag),t_(t){};
    manipulator_box(const manipulator_box<String1, String2, Att, T> & x):stag_(x.stag_),t_(x.t_){};

    stag_type stag_;
    T & t_;
private:
    manipulator_box<String1, String2, Att, T> & operator=(const manipulator_box<String1, String2, Att, T> & x);
};

//-----------------------------------------------------------------------------
// PutTo operator for the box.
//-----------------------------------------------------------------------------
template < typename String1, typename String2, typename Att, typename T >
xostream& operator<<(xostream& xos, const manipulator_box<String1, String2, Att, T>& m)
{
    return xos << m.stag_ << m.t_ << xml::etag();
};

//-----------------------------------------------------------------------------
// PutTo operator for the box.
//-----------------------------------------------------------------------------
template < typename String1, typename String2, typename Att, typename T >
xistream& operator>>(xistream& xis, manipulator_box<String1, String2, Att, T>& m)
{
	return xis >> m.stag_ >> m.t_ >> xml::etag();
};

// define all function box(string1, string2, attributes,t)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2, type3) \
    template < typename T > \
    manipulator_box < type1, type2, type3, T > \
    box( type1 & prefix, type2 & local, type3 & att, T& t) { \
    return manipulator_box< type1, type2, type3, T >(stag(prefix,local,att),t);  };

#include <config/define_functions_prefix_local_attributes.hpp>

// define all function box(string1, string2,t)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2) \
    template < typename T > \
    manipulator_box < type1, type2, xml::attributes, T > \
    box( type1 & prefix, type2 & local, T& t) { \
    return manipulator_box< type1, type2, xml::attributes, T >(stag(prefix,local),t);  };
#include <config/define_functions_prefix_local.hpp>

// define all function box(string1, attribute,t)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type3) \
    template < typename T > \
    manipulator_box < type1, type1, type3, T > \
    box( type1 & local, type3 & att, T& t) { \
    return manipulator_box< type1, type1, type3, T >(stag(local,att),t);  };
#include <config/define_functions_local_attributes.hpp>

// define all function box(string1,t)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1) \
    template < typename T > \
    manipulator_box < type1, type1, xml::attributes, T > \
    box( type1 & local, T& t) { \
    return manipulator_box< type1, type1, xml::attributes, T >(stag(local),t);  };
#include <config/define_functions_local.hpp>

// define all function rebox(string1, string2, attributes,t)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2, type3) \
    template < typename T > \
    manipulator_box < type1, type2, type3, T > \
    rebox( type1 & prefix, type2 & local, type3 & att, T& t) { \
    return manipulator_box< type1, type2, type3, T >(open_stag(prefix,local,att),t);  };

#include <config/define_functions_prefix_local_attributes.hpp>

// define all function rebox(string1, string2,t)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2) \
    template < typename T > \
    manipulator_box < type1, type2, xml::attributes, T > \
    rebox( type1 & prefix, type2 & local, T& t) { \
    return manipulator_box< type1, type2, xml::attributes, T >(open_stag(prefix,local),t);  };
#include <config/define_functions_prefix_local.hpp>

// define all function rebox(string1, attribute,t)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type3) \
    template < typename T > \
    manipulator_box < type1, type1, type3, T > \
    rebox( type1 & local, type3 & att, T& t) { \
    return manipulator_box< type1, type1, type3, T >(open_stag(local,att),t);  };
#include <config/define_functions_local_attributes.hpp>

// define all function rebox(string1,t)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1) \
    template < typename T > \
    manipulator_box < type1, type1, xml::attributes, T > \
    rebox( type1 & local, T& t) { \
    return manipulator_box< type1, type1, xml::attributes, T >(open_stag(local),t);  };
#include <config/define_functions_local.hpp>

XIMOL_XML_END_NAMESPACE

#endif // #ifndef XIMOL_XML_BOX_HPP_
