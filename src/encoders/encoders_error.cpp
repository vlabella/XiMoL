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
	\brief error class implementation.

	\author Tournois Florent
	\version 1.0

    $Id: encoders_error.cpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: encoders_error.cpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.9  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.8  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.7  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.6  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.5  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.4  2003/10/09 16:59:45  tournois
    add the stringstream initialisation.
    add some prolog test.
    Correct code for VC6.0.

    Revision 1.3  2003/09/28 16:39:11  hfp
    Constructors of class error has overqualified construction of base class

    Revision 1.2  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <encoders/error.hpp>


XIMOL_ENCODERS_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// Constructor.
//-----------------------------------------------------------------------------
error::error()
{
}

//-----------------------------------------------------------------------------
// Constructor.
//-----------------------------------------------------------------------------
error::error(const ::std::wstring& xS)
	: base_type(xS)
{
}

//-----------------------------------------------------------------------------
// Constructor.
//-----------------------------------------------------------------------------
error::error(const error& x)
	: base_type(x)
{
}

//-----------------------------------------------------------------------------
// Destructor.
//-----------------------------------------------------------------------------
error::~error() throw()
{
}
   
XIMOL_ENCODERS_END_NAMESPACE
