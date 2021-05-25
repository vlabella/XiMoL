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
	\brief Define XiMoL prolog Interface.

	\author Tournois Florent
	\version 1.0

    $Id: prolog.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: prolog.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:46  vlabella
    adding in ximol and xmlparser

    Revision 1.3  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.2  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.1  2004/01/22 22:01:35  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_XML_PROLOG_HPP_
#define XIMOL_XML_PROLOG_HPP_

#include <config.hpp>
#include <namespace_defs.hpp>
#include <typedefs.hpp>

// forwarded declarations
XIMOL_BEGIN_NAMESPACE
	class xostream;
	class xistream;
XIMOL_END_NAMESPACE
XIMOL_XML_BEGIN_NAMESPACE
	class attributes;
XIMOL_XML_END_NAMESPACE

XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/// Manipulator for the prolog.
//=============================================================================
struct XIMOL_DECL manip_prolog {};

//-----------------------------------------------------------------------------
/// GetFrom operator for the prolog.
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream&
operator>>(xistream& xis, manip_prolog m);

//-----------------------------------------------------------------------------
/// PutTo operator for the prolog.
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream&
operator<<(xostream& xos, const manip_prolog& m);

//-----------------------------------------------------------------------------
/// prolog reader-Writer
//-----------------------------------------------------------------------------
XIMOL_DECL
manip_prolog prolog();

XIMOL_XML_END_NAMESPACE

#endif // #ifndef XIMOL_XML_PROLOG_HPP_
