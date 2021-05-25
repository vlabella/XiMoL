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
	\brief Define some macros for boost python.
    Those macro simplify the life. That's all.

    \author Tournois Florent
	\version 1.0

    $Id: macro.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: macro.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.1  2004/04/27 16:45:42  tournois
    Beginning the python version.
    Add the project, and some files
    Add the boost::python lib


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_PYTHON_MACRO_HPP_
#define XIMOL_PYTHON_MACRO_HPP_

/// Function name for declaration
#define XIMOL_PYTHON_NAME(xxx) import_##xxx
/// the declaration of a function
#define XIMOL_PYTHON_DECLARATION(xxx) void XIMOL_PYTHON_NAME(xxx)()

#endif // #ifndef XIMOL_PYTHON_MACRO_HPP_