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
	\brief Datatype BLOB (binary large object) headers.

    \author Vincent LaBella
	\version 1.0

    
  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_DATATYPES_BLOB_HPP_
#define XIMOL_DATATYPES_BLOB_HPP_

#include <namespace_defs.hpp>
#include <typedefs.hpp>
#include <datatypes/traits.hpp>
#include <vector>
#include <map>

XIMOL_DATATYPES_BEGIN_NAMESPACE

typedef std::vector<char>				_BLOB;
typedef _BLOB::iterator					_itBLOB;
typedef _BLOB::const_iterator			_citBLOB;

typedef std::map<std::string,_BLOB>		_BLOBs;
typedef _BLOBs::iterator				_itBLOBs;
typedef _BLOBs::const_iterator			_citBLOBs;

XIMOL_DATATYPES_END_NAMESPACE

#endif // #ifndef XIMOL_DATATYPES_BOOLEAN_HPP_
