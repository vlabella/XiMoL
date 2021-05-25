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
	\brief element tree (declaration).

	\author Tournois Florent
	\version 1.0

    $Id: element_tree.hpp,v 1.3 2008/04/30 20:44:43 LABELLAHOME\administrator Exp $
    $Log: element_tree.hpp,v $
    Revision 1.3  2008/04/30 20:44:43  LABELLAHOME\administrator
    commit in makefile

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.3  2004/08/05 16:49:43  tournois
    no message

    Revision 1.2  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_DOM_ELEMENT_TREE_HPP_
#define XIMOL_DOM_ELEMENT_TREE_HPP_

#include <namespace_defs.hpp>
#include <config.hpp>
#include <typedefs.hpp>
#include <stream.hpp>

XIMOL_DOM_BEGIN_NAMESPACE

//=============================================================================
/** A very simple implementation of DOM.
 *  @ingroup user
 */
//=============================================================================
class XIMOL_DECL element_tree 
  :public std::list<element_tree>
{
public:
    element_tree();
    element_tree(xstring const & tag);
    ~element_tree();

    element_tree& operator=(const element_tree & x);
    void swap(element_tree & x);

	xstring const & content() const;
	void content(xstring const & x);

	xstring const & tag() const;
	void tag(xstring const & x);

private:
	xstring         content_;
	xstring         tag_;
}; // end of class element_tree

//-----------------------------------------------------------------------------
/// Put To operator for the element tree.
//-----------------------------------------------------------------------------
XIMOL_DECL std::ostream& operator<<(std::ostream & os, const element_tree & x);

//-----------------------------------------------------------------------------
/// Put To operator for the element tree.
//-----------------------------------------------------------------------------
XIMOL_DECL ximol::xostream& operator<<(ximol::xostream & xos, const element_tree & x);

//-----------------------------------------------------------------------------
/// Get from operator for the element tree.
//-----------------------------------------------------------------------------
XIMOL_DECL ximol::xistream& operator>>(ximol::xistream & xis, element_tree & x);

XIMOL_DOM_END_NAMESPACE

#endif // #ifndef XIMOL_DOM_ELEMENT_TREE_HPP_
