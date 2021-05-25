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
	\brief initialisation of the module.
    initialisation of the python module

    \author Tournois Florent
	\version 1.0

    $Id: main_init.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: main_init.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.2  2004/05/07 07:50:49  tournois
    beginning the xml content in python.

    Revision 1.1  2004/04/27 16:45:42  tournois
    Beginning the python version.
    Add the project, and some files
    Add the boost::python lib


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <config/force_link_boost_python.hpp>
#include <python/macro.hpp>
#include <boost/python/module.hpp>

XIMOL_PYTHON_DECLARATION(stream);
XIMOL_PYTHON_DECLARATION(xml_content);

//-----------------------------------------------------------------------------
// Initialisation of the module required by python
//-----------------------------------------------------------------------------
#if (defined(WIN32)) && (defined(_DEBUG))
BOOST_PYTHON_MODULE(ximol_d)
#else
BOOST_PYTHON_MODULE(ximol)
#endif
{
    XIMOL_PYTHON_NAME(stream)();
    XIMOL_PYTHON_NAME(xml_content)();

}; // End of the initialisation.