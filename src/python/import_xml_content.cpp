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
	\brief python version of the xml content.
    Wrapping the xml stream.

    \author Tournois Florent
	\version 1.0

    $Id: import_xml_content.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: import_xml_content.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.4  2004/05/12 17:05:19  tournois
    no message

    Revision 1.3  2004/05/11 17:11:16  tournois
    wrapping xofstream in python. the begining

    Revision 1.2  2004/05/11 09:58:33  tournois
    doxygen css improvment.
    Writing the element readable concept.

    Revision 1.1  2004/05/07 07:50:49  tournois
    beginning the xml content in python.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <config/check_dll.msvc.hpp>
#include <python/macro.hpp>
#include <python/wrap_stream.hpp>
#include <xml/content.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/args.hpp>
#include <boost/python/object.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <boost/python/with_custodian_and_ward.hpp> 

using namespace boost::python;
using namespace ximol;

XIMOL_BEGIN_PRIVATE_NAMESPACE

struct py_content
{
    py_content(const object& obj):obj_(obj){};
    py_content(const py_content & other):obj_(other.obj_){};
    ~py_content(){};

    py_content& operator=(const py_content & other)
    { 
        if (&other == this) return *this; 
        obj_=other.obj_; 
        return *this; 
    };

    bool is_float() const   { return extract<double>(obj_).check(); };
    bool is_int() const     { return extract<long>(obj_).check(); };
    bool is_string() const  { return extract<std::string>(obj_).check(); };
# ifndef BOOST_NO_STD_WSTRING
    bool is_wstring() const { return extract<std::wstring>(obj_).check(); };
#endif

    void set_int(long x){ obj_=object(x); };
    void set_float(double x){ obj_=object(x); };
    void set_string(const std::string & x){ obj_=object(x); };
# ifndef BOOST_NO_STD_WSTRING
    void set_wstring(const std::wstring & x){ obj_=object(x); };
#endif

    long        get_int() const { return extract<long>(obj_)(); };
    double      get_float() const { return extract<double>(obj_)(); };
    std::string get_string() const { return extract<std::string>(obj_)(); };
# ifndef BOOST_NO_STD_WSTRING
    std::wstring get_wstring() const { return extract<std::wstring>(obj_)(); };
#endif

    boost::python::object __ximol_write__(py_xostream xos)
    {
        if (is_int()) { long x=get_int(); xos.get() << xml::content(x); return xos.result(); };
        if (is_float()) { double x=get_float(); xos.get() << xml::content(x); return xos.result(); };
        if (is_string()) {  xos.get() << xml::content(get_string()); return xos.result(); };
        if (is_wstring()) {  xos.get() << xml::content(get_wstring()); return xos.result(); };
        return xos.result();
    };

    void __ximol_read__(xistream & xis)
    {
    };

    object obj_;
}; // end of class py_content

XIMOL_END_PRIVATE_NAMESPACE

//-----------------------------------------------------------------------------
// common component importation
//-----------------------------------------------------------------------------
XIMOL_PYTHON_DECLARATION(xml_content)
{
    class_< py_content>(
          "content",
          "XML Content managment.",
          init<object>(args("value")))
          .def_readwrite("value", &py_content::obj_)
          .def("is_float"  , &py_content::is_float  , "Test if the content is a float")
          .def("is_int"    , &py_content::is_int    , "Test if the content is an integer")
          .def("is_string" , &py_content::is_string , "Test if the content is a string")
          .def("is_wstring", &py_content::is_wstring, "Test if the content is a wide string")
          .def("set_float"  , &py_content::set_float  , "Define the object as a float")
          .def("set_int"    , &py_content::set_int    , "Define the value as an integer")
          .def("set_string" , &py_content::set_string , "Define the value as a string")
          .def("set_wstring", &py_content::set_wstring, "Define the value as a wide string")
          .def("get_float"  , &py_content::get_float  , "return the internal float")
          .def("get_int"    , &py_content::get_int    , "return the internal integer")
          .def("get_string" , &py_content::get_string , "return the internal string")
          .def("get_wstring", &py_content::get_wstring, "return the internal wide string")
          .def("__ximol_write__", &py_content::__ximol_write__, "write to the ximol stream")
          ;
};