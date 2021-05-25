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

    $Id: force_link_boost_python.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: force_link_boost_python.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.1  2004/04/27 16:45:41  tournois
    Beginning the python version.
    Add the project, and some files
    Add the boost::python lib


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_CONFIG_FORCE_LINK_BOOST_PYTHON_HPP_
#define XIMOL_CONFIG_FORCE_LINK_BOOST_PYTHON_HPP_

#ifdef _MSC_VER

#define BOOST_LIB_DIAGNOSTIC
#define BOOST_DYN_LINK
#define BOOST_LIB_NAME boost_python
#include <boost/config/auto_link.hpp>

#endif 

#endif // #ifndef XIMOL_CONFIG_FORCE_LINK_BOOST_PYTHON_HPP_