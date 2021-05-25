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

    $Id: fstream.cpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: fstream.cpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.6  2004/05/15 09:22:40  tournois
    no message

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
#include <fstream.hpp>
#include <encoders/encoders.hpp>


XIMOL_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xofstream::xofstream()
  :buf_()
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	this->init(&buf_);
	prepare_ios(*this);
	encoding(XIMOL_DEFAULT_ENCODING);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xofstream::xofstream(const char* name, const char* encoding_name, std::ios_base::openmode mode)
  :buf_()
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	this->init(&buf_);
	prepare_ios(*this);
	encoding(encoding_name);
	open(name, mode | binary);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xofstream::xofstream(const char* name, std::ios_base::openmode mode, const char* encoding_name)
  :buf_()
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	this->init(&buf_);
	prepare_ios(*this);
	encoding(encoding_name);
	open(name, mode | binary);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xofstream::~xofstream()
{
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::basic_filebuf<xchar_t>* xofstream::rdbuf()
{
	return &buf_;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
bool xofstream::is_open() const
{
	return buf_.is_open();
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xofstream::open(const char* filename, openmode mode )
{
	if (!buf_.open(filename, mode | out | binary))
      this->setstate(failbit);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xofstream::close()
{
    if (!buf_.close())
      this->setstate(failbit);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xifstream::xifstream()
  :buf_()
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	this->init(&buf_);
	prepare_ios(*this);
	encoding(XIMOL_DEFAULT_ENCODING);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xifstream::xifstream(const char* name, const char* encoding_name, std::ios_base::openmode mode)
  :buf_()
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	this->init(&buf_);
	prepare_ios(*this);
	encoding(encoding_name);
	open(name, mode | binary);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xifstream::xifstream(const char* name, std::ios_base::openmode mode, const char* encoding_name)
  :buf_()
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	this->init(&buf_);
	prepare_ios(*this);
	encoding(encoding_name);
	open(name, mode | binary);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xifstream::~xifstream()
{
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::basic_filebuf<xchar_t>* xifstream::rdbuf()
{
	return &buf_;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
bool xifstream::is_open() const
{
	return buf_.is_open();
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xifstream::open(const char* filename, openmode mode )
{
	if (!buf_.open(filename, mode | in | binary))
      this->setstate(failbit);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xifstream::close()
{
    if (!buf_.close())
      this->setstate(failbit);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xfstream::xfstream()
  :xiostream()
  ,buf_()
{
	this->init(&buf_);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xfstream::xfstream(const char* name, const char* encoding_name, std::ios_base::openmode mode)
  :buf_()
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	this->init(&buf_);
	prepare_ios(*this);
	xostream::encoding(encoding_name);
	xistream::encoding(encoding_name);
	open(name, mode | binary);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xfstream::xfstream(const char* name, std::ios_base::openmode mode, const char* encoding_name)
  :buf_()
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	this->init(&buf_);
	prepare_ios(*this);
	xostream::encoding(encoding_name);
	xistream::encoding(encoding_name);
	open(name, mode | binary);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xfstream::~xfstream()
{
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::basic_filebuf<xchar_t>* xfstream::rdbuf()
{
	return &buf_;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
bool xfstream::is_open() const
{
	return buf_.is_open();
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xfstream::open(const char* filename, openmode mode )
{
	if (!buf_.open(filename, mode | binary))
		this->setstate(failbit);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xfstream::close()
{
    if (!buf_.close())
      this->setstate(failbit);
}

XIMOL_END_NAMESPACE
