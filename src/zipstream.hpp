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
#ifndef XIMOL_ZIPSTREAM_HPP_
#define XIMOL_ZIPSTREAM_HPP_

#include <stream.hpp>
#include <sstream>
#include <sstream.hpp>
//#include <blobstream.hpp>

XIMOL_BEGIN_NAMESPACE

class XIMOL_DECL xozipfstream
	: public xostringstream
{
public: // constructor(s) & destructor
	explicit xozipfstream();
	explicit xozipfstream(const ::std::basic_string<xchar_t>& str);
	~xozipfstream();
public: // methods
	bool open(std::string _filename);
	void set_xml_filename_from_zip(bool b);
	bool is_open() const;
	void close();
private:
	std::string filename;			// the .zip filename
	std::string xml_filename;		// the .xml filename in the zip file defautls to manifest.xml
	bool xml_filename_from_zip;		// if true will make .xml filename match .zip filename  foo.zip ==> foo.xml
	bool opened;
	void* file;						// void type but pointer to zip file.... so no need to include zip library...
};

class XIMOL_DECL xizipfstream
	: public xistringstream
{
public: // constructor(s) & destructor
	explicit xizipfstream();
	explicit xizipfstream(const ::std::basic_string<xchar_t>& str);
	~xizipfstream();
public: // methods
	bool open(std::string filename);
	bool is_open() const;
	void close();
private:
	bool opened;
};
XIMOL_END_NAMESPACE 

#endif 
