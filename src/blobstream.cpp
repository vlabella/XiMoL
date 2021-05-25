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

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stream.hpp>
#include <sstream.hpp>
#include <datatypes/blob.hpp>
#include <blobstream.hpp>
XIMOL_BEGIN_NAMESPACE

xoblobstream::xoblobstream(std::ios_base::openmode mode)
	:file_number(0),
	xostringstream(mode)
{}

xoblobstream::xoblobstream(const ::std::basic_string<xchar_t>& str, std::ios_base::openmode mode)
	:file_number(0),
	xostringstream(str,mode)
{}

xoblobstream::~xoblobstream()
{}

xstring xoblobstream::add_blob(const ximol::datatypes::_BLOB &b,const std::string &ext){
	std::stringstream ss;
	ss << std::setw(8) << std::setfill('0') << file_number++;
	ss << "." << ext;
	BLOBs[ss.str()] = b;
	xstringstream xss;
	xss << ss.str().c_str();
	return xss.str();
}

const ximol::datatypes::_BLOBs& xoblobstream::get_blobs()
{
	return BLOBs;
}

xiblobstream::xiblobstream(std::ios_base::openmode mode)
	:xistringstream(mode)
{

}

xiblobstream::xiblobstream(const ::std::basic_string<xchar_t>& str,std::ios_base::openmode mode )
	:xistringstream(str,mode)
{

}

xiblobstream::~xiblobstream()
{

}

const ximol::datatypes::_BLOB xiblobstream::get_blob(const std::string &filename)
{
	ximol::datatypes::_citBLOBs citb = BLOBs.find(filename);
	if(citb != BLOBs.end()){
		return citb->second;
	}
	return ximol::datatypes::_BLOB(); // empty blob
}

void xiblobstream::set_blobs(const ximol::datatypes::_BLOBs &b)
{
	BLOBs = b;
}
XIMOL_END_NAMESPACE