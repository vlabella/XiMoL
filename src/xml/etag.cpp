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
	\brief Define etag Implementation.
	
	\author Tournois Florent
	\version 1.0

    $Id: etag.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: etag.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:46  vlabella
    adding in ximol and xmlparser

    Revision 1.3  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.2  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.1  2004/02/21 20:03:58  tournois
    Change the stag, etag, open_stag, box and rebox template with macro.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <xml/etag.hpp>

XIMOL_XML_BEGIN_NAMESPACE

// define all function etag(string1, string2)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2) \
    manipulator_etag< qualified_name<type1, type2> > etag(type1 & prefix, type2 & local){ \
    return manipulator_etag< qualified_name<type1,type2> >(qname(prefix, local)); }; 
#include <config/define_functions_prefix_local.hpp>

// define all function etag(string1)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1) \
    manipulator_etag< qualified_name<type1, type1> > etag(type1 & local){ \
    return manipulator_etag< qualified_name<type1,type1> >(qname(local)); }; 
#include <config/define_functions_local.hpp>

manipulator_etag< qualified_name< ::std::wstring, ::std::wstring> > 
etag() 
{ 
    return manipulator_etag< qualified_name< ::std::wstring, ::std::wstring> >(); 
};

XIMOL_XML_END_NAMESPACE

