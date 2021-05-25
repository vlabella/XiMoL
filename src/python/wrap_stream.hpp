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
	\brief wrap ximol stream.

    \author Tournois Florent
	\version 1.0

    $Id: wrap_stream.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: wrap_stream.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.2  2004/05/12 17:05:19  tournois
    no message

    Revision 1.1  2004/05/11 17:11:16  tournois
    wrapping xofstream in python. the begining


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_PYTHON_WRAP_STREAM_HPP_
#define XIMOL_PYTHON_WRAP_STREAM_HPP_

#include <boost/python/object.hpp>
#include <python/proxy.hpp>
#include <fstream.hpp>

struct py_abs_xostream {
    virtual py_abs_xostream * clone() const=0;
    virtual ximol::xostream& get()=0;
    virtual boost::python::object result()=0;
};

struct py_abs_xistream {
    virtual py_abs_xistream * clone() const=0;
    virtual ximol::xistream& get()=0;
    virtual boost::python::object result()=0;
};

struct py_xostream {
    py_xostream(py_abs_xostream * pxos);
    py_xostream(const py_xostream & other);
    ~py_xostream();
    py_xostream& operator=(const py_xostream & other);

    ximol::xostream& get();
    boost::python::object result();
private:
    py_abs_xostream * p;
};

struct py_xofstream : public py_abs_xostream
{
    typedef proxy<ximol::xofstream> proxy_t;
    typedef proxy_t::index_t index_t;

    py_xofstream();
    py_xofstream(const char * filename);
    py_xofstream(const py_xofstream & other);
    ~py_xofstream();

    py_xofstream& operator=(const py_xofstream & other);

    void open(const std::string & filename);
    void close();
    long nb_ref() const;
    void write(boost::python::object obj) const;

    virtual ximol::xostream& get();
    virtual boost::python::object result();
    virtual py_abs_xostream * clone() const;

    operator py_xostream() const; 

    index_t i;
};

#endif // #ifndef XIMOL_PYTHON_WRAP_STREAM_HPP_