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
	\brief Facet list headers.
    @ingroup facet

    \author Tournois Florent
	\version 1.0

    $Id: list.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: list.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:44  vlabella
    adding in ximol and xmlparser

    Revision 1.6  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.5  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.4  2004/02/05 09:08:33  tournois
    no message

    Revision 1.3  2004/01/25 17:32:38  tournois
    no message

    Revision 1.2  2004/01/18 11:40:58  tournois
    Add the pattern facet.

    Revision 1.1  2004/01/16 21:05:03  tournois
    Beginning the databinbding stuff
    Add the first facets and datatype.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_FACET_LIST_HPP_
#define XIMOL_FACET_LIST_HPP_

#include <namespace_defs.hpp>
#include <typedefs.hpp>
#include <error.hpp>
#include <translation.hpp>
#include <facet/none.hpp>
#include <boost/static_assert.hpp>

XIMOL_FACET_BEGIN_NAMESPACE

//=============================================================================
/** constraining facet list
    @ingroup facet
 */
//=============================================================================
template < 
    typename T01 = none, 
    typename T02 = none, 
    typename T03 = none, 
    typename T04 = none, 
    typename T05 = none, 
    typename T06 = none, 
    typename T07 = none, 
    typename T08 = none, 
    typename T09 = none, 
    typename T10 = none 
    >
class list
{
public:
    template < typename T >
    static bool check(T const & x, bool throw_error = true)
    {
        if (throw_error) return check_throw(x);
        return check_no_throw(x);
    };

private:
    template < typename T >
    static bool check_throw(T const & x)
    {
        xstring err_msg;
        try { T01::check(x); } catch ( error & e ) { err_msg+= e.message(); };
        try { T02::check(x); } catch ( error & e ) { err_msg+= e.message(); };
        try { T03::check(x); } catch ( error & e ) { err_msg+= e.message(); };
        try { T04::check(x); } catch ( error & e ) { err_msg+= e.message(); };
        try { T05::check(x); } catch ( error & e ) { err_msg+= e.message(); };
        try { T06::check(x); } catch ( error & e ) { err_msg+= e.message(); };
        try { T07::check(x); } catch ( error & e ) { err_msg+= e.message(); };
        try { T08::check(x); } catch ( error & e ) { err_msg+= e.message(); };
        try { T09::check(x); } catch ( error & e ) { err_msg+= e.message(); };
        try { T10::check(x); } catch ( error & e ) { err_msg+= e.message(); };

        if (err_msg.empty()) return true;
        XIMOL_THROW << err_msg << XIMOL_AS_ERROR;
        return false;
    };

    template < typename T >
    static bool check_no_throw(T const & x)
    {
        if (!T01::check(x)) return false;
        if (!T02::check(x)) return false;
        if (!T03::check(x)) return false;
        if (!T04::check(x)) return false;
        if (!T05::check(x)) return false;
        if (!T06::check(x)) return false;
        if (!T07::check(x)) return false;
        if (!T08::check(x)) return false;
        if (!T09::check(x)) return false;
        if (!T10::check(x)) return false;
        return true;
    };

}; // end of list<T01, ... >

XIMOL_FACET_END_NAMESPACE

#endif // #ifndef XIMOL_FACET_LIST_HPP_
