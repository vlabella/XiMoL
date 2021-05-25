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

    $Id: wrap_stream.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: wrap_stream.cpp,v $
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
#include <config/check_dll.msvc.hpp>
#include <python/wrap_stream.hpp>

using namespace ximol;

py_xostream::py_xostream(py_abs_xostream * pxos):p(pxos){};
py_xostream::py_xostream(const py_xostream & other):p(other.p->clone()){};
py_xostream::~py_xostream(){ delete p; };
py_xostream& py_xostream::operator=(const py_xostream & other)
{ 
    if (&other == this) return *this;
    delete p;
    p=other.p->clone();
    return *this;
};
ximol::xostream& py_xostream::get(){ return p->get(); };
boost::python::object py_xostream::result(){ return p->result(); };

py_xofstream::py_xofstream():i(-1){};
py_xofstream::py_xofstream(const char * filename):i(-1){ open(filename); };
py_xofstream::py_xofstream(const py_xofstream & other):i(other.i){ proxy_t::Singleton().add_ref(i); };
py_xofstream::~py_xofstream(){ close();};

py_xofstream& py_xofstream::operator=(const py_xofstream & other)
{
    if (&other==this) return *this;
    if (i==other.i) return *this;
    close();
    i=other.i;
    proxy_t::Singleton().add_ref(i);
    return *this;
};

void py_xofstream::open(const std::string & filename)
{
    close();
    i=proxy_t::Singleton().set_new(new xofstream(filename.c_str()));
};

void py_xofstream::close()
{
    if (i!=-1) {
        if (proxy_t::Singleton().is_last_ref(i))
            proxy_t::Singleton()[i].close();
        proxy_t::Singleton().del_ref(i);
    };
    i=-1;
};

long py_xofstream::nb_ref() const{ return proxy_t::Singleton().nb_ref(i); };

void py_xofstream::write(boost::python::object obj) const
{
    obj.attr("__ximol_write__")(*this);
};

ximol::xostream& py_xofstream::get()
{
    return proxy_t::Singleton()[i];
};

boost::python::object py_xofstream::result()
{
    return boost::python::object(*this);
};

py_abs_xostream * py_xofstream::clone() const
{
    return new py_xofstream(*this);
};

py_xofstream::operator py_xostream() const
{
    return py_xostream(this->clone());
}; 

