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
	\brief datatype traits headers.

    \author Tournois Florent
	\version 1.0

    $Id: traits.hpp,v 1.3 2013/02/11 02:12:58 vlabella Exp $
    $Log: traits.hpp,v $
    Revision 1.3  2013/02/11 02:12:58  vlabella
    commit in makefile
    Committed on the Free edition of March Hare Software CVSNT Client.
    Upgrade to CVS Suite for more features and support:
    http://march-hare.com/cvsnt/

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.5  2004/08/05 16:49:43  tournois
    no message

    Revision 1.4  2004/05/15 09:22:40  tournois
    no message

    Revision 1.3  2004/02/22 10:27:33  tournois
    Add some doc.

    Revision 1.2  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.1  2004/02/05 09:08:33  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_DATATYPES_TRAITS_HPP_
#define XIMOL_DATATYPES_TRAITS_HPP_

#include <namespace_defs.hpp>
#include <typedefs.hpp>
#include <facet/none.hpp>
#include <stream.hpp>

XIMOL_DATATYPES_BEGIN_NAMESPACE

//=============================================================================
/** default datatype traits
 */
//=============================================================================
template < typename T >
struct traits
{
    /// the type
    typedef T type;

    /// Facet
    typedef XIMOL_FACET_NAMESPACE_PATH::none facet;

    /// return the documentation of the type
//    static xstring const & documentation(){ return L"There is no documentation"; };
    static xstring const documentation(){ return L"There is no documentation"; };

    /// Write the type schema on the stream.
    static xostream & schema_type(xostream & xos){ return xos; };

    /// return the type name of the defined type.
//    static xstring const & schema_type_name(){ return L""; };
    static xstring const schema_type_name(){ return L""; };

    /// Write the type schema element on the stream.
    static xostream & schema_element(xostream & xos, type const & x){ return xos; };

    /// Write the type schema element on the stream.
//    static xstring const & schema_element_name(type const & x){ return L""; };
    static xstring const  schema_element_name(type const & x){ return L""; };

    /// Write the element on the stream.
    static xostream & write(xostream & xos, type const & x){ return xos; };

    /// Read the element from the stream.
    static xistream & read(xistream & xis, type & x){ return xis; };

    /// Write the element data on the stream.
    static xostream & write_data(xostream & xos, type const & x){ return xos; };

    /// Read the element data from the stream.
    static xistream & read_data(xistream & xis, type & x){ return xis; };

}; // end of class traits<T>

XIMOL_DATATYPES_END_NAMESPACE

#endif // #ifndef XIMOL_DATATYPES_TRAITS_HPP_
