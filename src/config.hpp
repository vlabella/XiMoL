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
	\brief Define the export symbol for windows DLL compilation.

	if you want to build the library, you must define XIMOL_SOURCE.

	if you want to build the static librarie, you must define 
	XIMOL_STATIC_LINK.
        
        XIMOL_NO_LIB disable the auto link.
        XIMOL_DYN_LINK force the dynamic link.

	\author Tournois Florent
	\version 1.0

    $Id: config.hpp,v 1.3 2012/11/16 04:21:55 vlabella Exp $
    $Log: config.hpp,v $
    Revision 1.3  2012/11/16 04:21:55  vlabella
    commit in makefile
    Committed on the Free edition of March Hare Software CVSNT Client.
    Upgrade to CVS Suite for more features and support:
    http://march-hare.com/cvsnt/

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.3  2005/05/12 01:26:45  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 01:14:57  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_CONFIG_HPP_
#define XIMOL_CONFIG_HPP_

//#define XIMOL_STATIC_LINK
//#define XIMOL_NO_LIB
//#define XIMOL_DIAG


#include <boost/config.hpp>

//#define XIMOL_DECL
#if defined(BOOST_HAS_DECLSPEC) && (defined(XIMOL_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(XIMOL_STATIC_LINK)
#  if defined(XIMOL_SOURCE)
#     define XIMOL_DECL __declspec(dllexport)
#  else
#     define XIMOL_DECL __declspec(dllimport)
#  endif
#endif

#ifndef XIMOL_DECL
#  define XIMOL_DECL
#endif

// Auto Link
#if !defined(XIMOL_NO_LIB) && !defined(XIMOL_SOURCE) && !defined(BOOST_ALL_NO_LIB)
#  define BOOST_LIB_NAME ximol
#  if defined(BOOST_HAS_DECLSPEC) && (defined(XIMOL_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(XIMOL_STATIC_LINK)
#     define BOOST_DYN_LINK
#  endif

#  ifdef XIMOL_DIAG
#    define BOOST_LIB_DIAGNOSTIC
#  endif

#  ifdef BOOST_LIB_VERSION
#    undef BOOST_LIB_VERSION
#  else
#    define BOOST_VERSION_HPP
#  endif 
#  define BOOST_LIB_VERSION "0_8"
#  include <boost/config/auto_link.hpp>
#  undef BOOST_LIB_VERSION
#  undef BOOST_VERSION_HPP
#  include <boost/version.hpp>

#endif

#ifdef _WIN32
//Print message at compile time
#if defined(XIMOL_DIAG)
#  pragma message ("XIMOL_DECL set as " BOOST_STRINGIZE(--> XIMOL_DECL) )
#  if defined(BOOST_HAS_DECLSPEC) && (defined(XIMOL_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(XIMOL_STATIC_LINK)
#    pragma message ("XiMoL: Dynamic linking enabled")
#  endif
#  if (defined(XIMOL_NO_LIB) || defined(BOOST_ALL_NO_LIB))
#    pragma message ("XiMoL: Auto-linking disabled")
#  endif
#endif
#endif

#endif // #define XIMOL_CONFIG_HPP_
