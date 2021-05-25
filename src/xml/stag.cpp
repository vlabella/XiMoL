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
	\brief Define stag Implementation.
	
	\author Tournois Florent
	\version 1.0

    $Id: stag.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: stag.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 02:58:23  vlabella
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
#include <xml/content.hpp>
#include <xml/open_stag.hpp>
#include <xml/stag.hpp>

XIMOL_XML_BEGIN_NAMESPACE

// define all function stag(string1, string2, attributes)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2, type3) \
    manipulator_stag< qualified_name<type1, type2>, type3> stag(type1 & prefix, type2 & local, type3 & att){ \
    return manipulator_stag< qualified_name<type1,type2>, type3>(qname(prefix, local),att); }; 
#include <config/define_functions_prefix_local_attributes.hpp>

// define all function stag(string1, string2)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2) \
    manipulator_stag< qualified_name<type1, type2>, xml::attributes> stag(type1 & prefix, type2 & local){ \
    return manipulator_stag< qualified_name<type1,type2>, xml::attributes>(qname(prefix, local)); }; 
#include <config/define_functions_prefix_local.hpp>

// define all function stag(string1, attribute)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type3) \
    manipulator_stag< qualified_name<type1, type1>, type3> stag(type1 & local, type3 & att){ \
    return manipulator_stag< qualified_name<type1,type1>, type3>(qname(local),att); }; 
#include <config/define_functions_local_attributes.hpp>

// define all function stag(string1)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1) \
    manipulator_stag< qualified_name<type1, type1>, xml::attributes> stag(type1 & local){ \
    return manipulator_stag< qualified_name<type1,type1>, xml::attributes>(qname(local)); }; 
#include <config/define_functions_local.hpp>

XIMOL_XML_END_NAMESPACE

