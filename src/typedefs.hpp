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
	\brief All type definition.
    Definition of the xchar_t, xstring, ...

	\author Tournois Florent
	\version 1.0

    $Id: typedefs.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: typedefs.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.9  2004/05/27 20:24:01  tournois
    no message

    Revision 1.8  2004/03/04 18:45:29  tournois
    Compatibility with gcc.

    Revision 1.7  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

    Revision 1.6  2004/02/22 10:27:33  tournois
    Add some doc.

    Revision 1.5  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.4  2004/01/25 17:20:24  tournois
    no message

    Revision 1.3  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.2  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_TYPEDEFS_HPP_
#define XIMOL_TYPEDEFS_HPP_

//#include <boost/config.hpp>
#include <namespace_defs.hpp>
#include <string>
#include <sstream>

#ifdef BOOST_NO_STD_WSTRING
namespace std {
    typedef basic_string<wchar_t> wstring;
    typedef basic_ostream<wchar_t> wostream;
    typedef basic_istream<wchar_t> wistream;
    typedef basic_iostream<wchar_t>  wstream;
    typedef basic_ostringstream<wchar_t> wostringstream;
    typedef basic_istringstream<wchar_t> wistringstream;
    typedef basic_stringstream<wchar_t>  wstringstream;
};
#endif

XIMOL_BEGIN_NAMESPACE

/// definition of our character (in XiMoL).
typedef wchar_t xchar_t;

/// definition of our string.
typedef ::std::basic_string<xchar_t> xstring;

XIMOL_END_NAMESPACE

#endif // #ifndef XIMOL_TYPEDEFS_HPP_
