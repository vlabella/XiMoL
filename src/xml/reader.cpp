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
	\brief reader (implementation).

	\author Tournois Florent
	\version 1.0

    $Id: reader.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: reader.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 02:56:54  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:46  vlabella
    adding in ximol and xmlparser

    Revision 1.12  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.11  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.10  2004/01/27 21:49:52  tournois
    Add docs and tutorial.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <xml/content.hpp>
#include <xml/open_stag.hpp>

#include <xml/reader.hpp>

XIMOL_XML_BEGIN_NAMESPACE

namespace helper {
    abstract_copy_holder::abstract_copy_holder(){};
    abstract_copy_holder::abstract_copy_holder(const abstract_copy_holder & x){};
    abstract_copy_holder::~abstract_copy_holder(){};
    abstract_copy_holder& abstract_copy_holder::operator=(const abstract_copy_holder & x ){ return *this;};
};

XIMOL_XML_END_NAMESPACE
