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
	\brief Define XiMoL macros.
	
	\author Tournois Florent
	\version 1.0

    $Id: macros.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: macros.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.7  2004/08/05 16:49:42  tournois
    no message

    Revision 1.6  2004/05/26 07:48:04  tournois
    no message

    Revision 1.5  2004/05/15 09:22:40  tournois
    no message

    Revision 1.4  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.3  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.2  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.1  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_MACRO_HPP_
#define XIMOL_MACRO_HPP_

/// Default value for the encoding in XiMoL.
#define XIMOL_DEFAULT_ENCODING "UTF-8"

#define XIMOL_NO_THROW 
//#define XIMOL_NO_THROW throw()

#define XIMOL_TEMPLATE_NULL
//#define XIMOL_TEMPLATE_NULL template <>

#define XIMOL_MIN(a,b) ((b) < (a) ? (b) : (a)) 

#ifndef _MSC_VER
#define XIMOL_STANDARD_FACET
#endif

// for the microsoft stl
// vc 2017 now complies with std
//#if (defined(XIMOL_STANDARD_FACET))
#  define XIMOL_HAS_FACET(locale_name,facet_name) ::std::has_facet< facet_name >( locale_name )
#  define XIMOL_USE_FACET(locale_name,facet_name) ::std::use_facet< facet_name >( locale_name )
#  define XIMOL_ADD_FACET(locale_name,facet_name) ::std::locale( locale_name , facet_name )
//#else
//#  define XIMOL_HAS_FACET(locale_name,facet_name) ::std::_HAS(locale_name,facet_name)    
//#  define XIMOL_USE_FACET(locale_name,facet_name) ::std::_USE(locale_name,facet_name)    
//#  define XIMOL_ADD_FACET(locale_name,facet_name) ::std::_ADDFAC(locale_name,facet_name)
//#endif

#define XIMOL_SCHEMA_URI L"http://www.w3.org/2001/XMLSchema"
#define XIMOL_HFP_URI    L"http://www.w3.org/2001/XMLSchema-hasFacetAndProperty"
#define XIMOL_XIMOL_URI  L"http://www.ximol.org/2004/XMLSchema"

#endif // #ifndef XIMOL_MACRO_HPP_
