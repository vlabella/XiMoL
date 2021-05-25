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
	\brief Force the link under msvc.
	
	\author Tournois Florent
	\version 1.0

    $Id: force_link_ximol.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: force_link_ximol.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.11  2004/06/07 20:10:17  tournois
    no message

    Revision 1.4  2004/05/31 20:51:27  tournois
    no message

    Revision 1.8  2004/02/25 18:59:12  tournois
    imporve the gcc compatibility.

    Revision 1.7  2004/02/22 10:27:33  tournois
    Add some doc.

    Revision 1.6  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.5  2004/01/19 20:40:55  tournois
    Add min, max and digits facet.
    Create the control flow file.

    Revision 1.4  2004/01/08 20:02:29  tournois
    Add XIMOL_XML_NAMESPACE_PATH::comment and assignment mainuplator.

    Revision 1.3  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.2  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_CONFIG_CONFIG_FORCE_LINK_XIMOL_CONFIG_HPP_
#define XIMOL_CONFIG_CONFIG_FORCE_LINK_XIMOL_CONFIG_HPP_

#if (!defined(XIMOL_BUILD)) && (!defined(XIMOL_STATIC_BUILD))

    #define BOOST_LIB_DIAGNOSTIC
    #define BOOST_LIB_NAME ximol

    #ifdef BOOST_LIB_VERSION
        #undef BOOST_LIB_VERSION
    #else
        #define BOOST_VERSION_HPP
    #endif 

    #define BOOST_LIB_VERSION "0_8"

    #include <boost/config/auto_link.hpp>

    #undef BOOST_LIB_VERSION
    #undef BOOST_VERSION_HPP
    #include <boost/version.hpp>

#endif 

#endif // #ifndef XIMOL_CONFIG_CONFIG_FORCE_LINK_XIMOL_CONFIG_HPP_