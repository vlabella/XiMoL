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
	\brief python version of the xml stream.
    Wrapping the xml stream.

    \author Tournois Florent
	\version 1.0

    $Id: import_stream.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: import_stream.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.3  2004/05/12 17:05:18  tournois
    no message

    Revision 1.2  2004/05/11 17:11:16  tournois
    wrapping xofstream in python. the begining

    Revision 1.1  2004/04/27 16:45:42  tournois
    Beginning the python version.
    Add the project, and some files
    Add the boost::python lib


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <config/check_dll.msvc.hpp>
#include <python/macro.hpp>
#include <python/wrap_stream.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/args.hpp>
#include <boost/python/return_arg.hpp>
#include <boost/python/implicit.hpp>

using namespace boost::python;
using namespace ximol;

//-----------------------------------------------------------------------------
// common component importation
//-----------------------------------------------------------------------------
XIMOL_PYTHON_DECLARATION(stream)
{
    class_< py_xofstream >(
          "xofstream",
          "XML Ouput File Stream",
          init<const char *>(args("filename")))
          .def("open", &py_xofstream::open, "Open a file in a XML stream", args("filename"))
          .def("close", &py_xofstream::close, "Close the file")
          .def("nb_ref", &py_xofstream::nb_ref, "number of reference to the file")
          .def("__lshift__", &py_xofstream::write, "Write the object", return_self<>())
          ;

    implicitly_convertible<py_xofstream, py_xostream>();
};