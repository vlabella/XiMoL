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
	\brief GetFrom and PutTo operator for common char and xchar_t (Implementation).

    \author Tournois Florent
	\version 1.0

    $Id: error.cpp,v 1.3 2008/04/30 20:44:43 LABELLAHOME\administrator Exp $
    $Log: error.cpp,v $
    Revision 1.3  2008/04/30 20:44:43  LABELLAHOME\administrator
    commit in makefile

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.11  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

    Revision 1.10  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.9  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.8  2003/11/18 18:54:51  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.7  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.6  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.5  2003/10/29 17:51:52  tournois
    Modifie error copy constructor for the VC7.1 compiler

    Revision 1.4  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.3  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <error.hpp>
#include <str_cast.hpp>

XIMOL_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
error::error()
{
}

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
error::error(const string_type& str)
{
	m_stream << str;
}

//-----------------------------------------------------------------------------
// Copy-Constructor
//-----------------------------------------------------------------------------
error::error(const error& err)
{
	m_stream << err.m_stream.str();
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
error::~error() throw()
{
}

//-----------------------------------------------------------------------------
// The most important function.
//-----------------------------------------------------------------------------
const char* error::what() const throw()
{ 
    buffer_= XIMOL_NAMESPACE_PATH::str< ::std::string>::cast(m_stream.str());
	return buffer_.c_str();
}

//-----------------------------------------------------------------------------
/// Get the error message.
//-----------------------------------------------------------------------------
const error::string_type & error::message() const throw()
{
    wbuffer_ = m_stream.str();
	return wbuffer_;
};

XIMOL_END_NAMESPACE
