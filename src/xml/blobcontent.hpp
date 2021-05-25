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
	\brief blob content implementation.
	
	\author Vincent LaBella
	\version 1.0

    
  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_XML_BLOB_CONTENT_HPP_
#define XIMOL_XML_BLOB_CONTENT_HPP_
#include <datatypes/blob.hpp>
#include <xml/content.hpp>
#include <xml/context.hpp>
#include <stream.hpp>
#include <sstream.hpp>
#include <error.hpp>
#include <translation.hpp>
#include <str_cast.hpp>
#include <parser/utils.hpp>
#include <parser/def_signs.hpp>

XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/// Manipulator for the BLOB data content.
//=============================================================================
template < typename T >
class manipulator_blob_content
{
public:
    typedef T blob_type;
public:
    manipulator_blob_content(blob_type & x,std::string ext="")
	:blob_(x),
	extension(ext)
	{
	};
    manipulator_blob_content(const manipulator_blob_content<blob_type> & x)
	:blob_(x.blob_),
	extension(x.extension)
	{
		*this = x;
	};
	const manipulator_blob_content<T> & operator=(const manipulator_blob_content<blob_type> & x)
	{
		if (this==&x) return *this;
		blob_ = x.blob_;
		extension = x.extension;
		return *this;
	};

    void set_blob(blob_type const & x) const
	{
		blob_ = x;
	}
   	const ximol::datatypes::_BLOB& get_blob()
	{
		return blob_;
	};
	const std::string& get_extension()
	{
		return extension;
	};

private:
    blob_type & blob_;
	std::string extension;
}; // end of class manipulator_blob_content<T>

/*
//-----------------------------------------------------------------------------
// PutTo operator for the blob_content.
//-----------------------------------------------------------------------------
//template < typename ximol::datatypes::_BLOB >
ximol::xoblobstream& operator << (ximol::xoblobstream& xos,       ximol::xml::manipulator_blob_content<ximol::datatypes::_BLOB>& m);

//-----------------------------------------------------------------------------
// PutTo operator for the blob_content.
//-----------------------------------------------------------------------------

//template < typename ximol::datatypes::_BLOB >
ximol::xiblobstream& operator >> (ximol::xiblobstream& xis, const ximol::xml::manipulator_blob_content<ximol::datatypes::_BLOB>& m);
*/

template < typename T >
ximol::xostream& operator << (ximol::xostream& xos, ximol::xml::manipulator_blob_content<T>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
	//
	// -- write blob data to blob store BLOBs and output filename to stream
	//
	xos << ximol::xml::content(xos.add_blob(m.get_blob(),m.get_extension()));
	return xos;
};

//-----------------------------------------------------------------------------
// PutTo operator for the blob_content.
//-----------------------------------------------------------------------------
template < typename T >
ximol::xistream& operator >> (ximol::xistream& xis, const ximol::xml::manipulator_blob_content<T>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
	std::string filename;
	xis >> ximol::xml::content(filename);
	m.set_blob(xis.get_blob(filename));
	// set the extension ??
	return xis;
};

inline ximol::xml::manipulator_blob_content<ximol::datatypes::_BLOB> content(ximol::datatypes::_BLOB& t, std::string s) 
{	
	return ximol::xml::manipulator_blob_content<ximol::datatypes::_BLOB>(t,s);							
};

inline ximol::xml::manipulator_blob_content<ximol::datatypes::_BLOB> content(ximol::datatypes::_BLOB& t) 
{	
	return ximol::xml::manipulator_blob_content<ximol::datatypes::_BLOB>(t);							
};


XIMOL_XML_END_NAMESPACE
#endif