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
	\brief Facet none headers.
    @ingroup facet

    \author Tournois Florent
	\version 1.0

    $Id: none.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: none.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:44  vlabella
    adding in ximol and xmlparser

    Revision 1.3  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.2  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.1  2004/02/05 09:08:33  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_FACET_NONE_HPP_
#define XIMOL_FACET_NONE_HPP_

#include <namespace_defs.hpp>
#include <stream.hpp>

XIMOL_FACET_BEGIN_NAMESPACE

//=============================================================================
/** facet without any constraint
    @ingroup facet
 */
//=============================================================================
struct none
{
    template < typename T >
    static bool check(T const & x, bool throw_error = true)
    {
        return true;
    };

    /// Outout the facet schema
    static xostream& schema(xostream & xos){ return xos; };
};

XIMOL_FACET_END_NAMESPACE

#endif // #ifndef XIMOL_FACET_NONE_HPP_
