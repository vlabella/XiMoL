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
//#include <datatypes/blob.hpp>
//#include <xml/blobcontent.hpp>

//=============================================================================
/// Manipulator for the BLOB data content.
//=============================================================================

//XIMOL_XML_BEGIN_NAMESPACE
/*
ximol::xoblobstream& operator<<(ximol::xoblobstream& xos, ximol::xml::manipulator_blob_content<ximol::datatypes::_BLOB>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
	//
	// -- write blob data to blob store BLOBs and output filename to stream
	//
	xos << ximol::xml::content(xos.add_blob(m.get_blob(),m.get_extension()));
	return xos;
}

//-----------------------------------------------------------------------------
// PutTo operator for the blob_content.
//-----------------------------------------------------------------------------

ximol::xiblobstream& operator>>(ximol::xiblobstream& xis, const ximol::xml::manipulator_blob_content<ximol::datatypes::_BLOB>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
	std::string filename;
	xis >> ximol::xml::content(filename);
	m.set_blob(xis.get_blob(filename));
	// set the extension ??
	return xis;
}
*/
//XIMOL_XML_END_NAMESPACE

