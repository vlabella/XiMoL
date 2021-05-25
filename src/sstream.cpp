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
	\brief XML streams implementations.
	
	\author Tournois Florent
	\version 1.0

    $Id: sstream.cpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: sstream.cpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.5  2004/02/25 18:58:39  tournois
    imporve the gcc compatibility.

    Revision 1.4  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.3  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.2  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.1  2003/10/24 15:53:13  hfp
    separation of each public class into one file

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <sstream.hpp>
#include <encoders/encoders.hpp>


XIMOL_ENCODERS_USING_NAMESPACE;


XIMOL_BEGIN_NAMESPACE


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xostringstream::xostringstream(std::ios_base::openmode mode)
  :buf_(mode)
{
	this->init(&buf_);
	prepare_ios(*this);
	encoding(XIMOL_DEFAULT_ENCODING);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xostringstream::xostringstream(const ::std::basic_string<xchar_t>& str, std::ios_base::openmode mode)
  :buf_(mode)
{
	this->init(&buf_);
	prepare_ios(*this);
	encoding(XIMOL_DEFAULT_ENCODING);
	this->str(str);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xostringstream::~xostringstream()
{
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::basic_stringbuf<xchar_t>* xostringstream::rdbuf()
{
	return &buf_;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::basic_string<xchar_t> xostringstream::str() const
{
	return buf_.str();
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xostringstream::str(const ::std::basic_string<xchar_t>& s)
{
	buf_.str(s);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xistringstream::xistringstream(std::ios_base::openmode mode)
  :buf_(mode)
{
	this->init(&buf_);
	prepare_ios(*this);
	encoding(XIMOL_DEFAULT_ENCODING);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xistringstream::xistringstream(const ::std::basic_string<xchar_t>& str, std::ios_base::openmode mode)
  :buf_(mode)
{
	this->init(&buf_);
	prepare_ios(*this);
	encoding(XIMOL_DEFAULT_ENCODING);
	this->str(str);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xistringstream::~xistringstream()
{
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::basic_stringbuf<xchar_t>* xistringstream::rdbuf()
{
	return &buf_;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::basic_string<xchar_t> xistringstream::str() const
{
	return buf_.str();
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xistringstream::str(const ::std::basic_string<xchar_t>& s)
{
	buf_.str(s);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xstringstream::xstringstream(std::ios_base::openmode mode)
  :xiostream()
  ,buf_(mode)
{
	this->init(&buf_);
	prepare_ios(*this);
	xostream::encoding(XIMOL_DEFAULT_ENCODING);
	xistream::encoding(XIMOL_DEFAULT_ENCODING);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xstringstream::xstringstream(const ::std::basic_string<xchar_t>& str, std::ios_base::openmode mode)
  :buf_(mode)
{
	this->init(&buf_);
	prepare_ios(*this);
	xostream::encoding(XIMOL_DEFAULT_ENCODING);
	xistream::encoding(XIMOL_DEFAULT_ENCODING);
	this->str(str);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xstringstream::~xstringstream()
{
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::basic_stringbuf<xchar_t>* xstringstream::rdbuf()
{
	return &buf_;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::basic_string<xchar_t> xstringstream::str() const
{
	return buf_.str();
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xstringstream::str(const ::std::basic_string<xchar_t>& s)
{
	buf_.str(s);
}


XIMOL_END_NAMESPACE
