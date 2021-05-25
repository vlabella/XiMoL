/*****************************************************************************\
 *                                                                           *
 * library XiMoL                                                             *
 * Copyright (C) 2009 Vincent LaBella                                        *
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
	\brief XML streams declarations.
	
	\author Vincent LaBella
	\version 1.0


NOTEUSED ANYMORE page or ostream and istream
  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_BLOBSTREAM_HPP_
#define XIMOL_BLOBSTREAM_HPP_

#include <stream.hpp>
#include <sstream>
#include <sstream.hpp>

XIMOL_BEGIN_NAMESPACE

class XIMOL_DECL xoblobstream
	: public xostringstream
{
public: // constructor(s) & destructor
	explicit xoblobstream(std::ios_base::openmode mode = std::ios_base::out);
	explicit xoblobstream(const ::std::basic_string<xchar_t>& str, std::ios_base::openmode mode);
	xoblobstream::~xoblobstream();
public: // methods
	xstring add_blob(const ximol::datatypes::_BLOB &b,const std::string &ext);
	const ximol::datatypes::_BLOBs& get_blobs();
protected:
	ximol::datatypes::_BLOBs BLOBs;
	size_t file_number;
};

class XIMOL_DECL xiblobstream
	: public xistringstream
{
public: // constructor(s) & destructor
	explicit xiblobstream(std::ios_base::openmode mode = std::ios_base::in);
	explicit xiblobstream(const ::std::basic_string<xchar_t>& str,std::ios_base::openmode mode = std::ios_base::in);
	~xiblobstream();
	
public: // methods
	//
	// -- blob interface
	//
	const ximol::datatypes::_BLOB get_blob(const std::string &filename);
	void set_blobs(const ximol::datatypes::_BLOBs &b);
protected: // data members
	ximol::datatypes::_BLOBs BLOBs;	
};

XIMOL_END_NAMESPACE 
#endif // #ifndef XIMOL_SSTREAM_HPP_
