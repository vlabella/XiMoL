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
	\brief element tree (implementation).

	\author Tournois Florent
	\version 1.0

    $Id: element_tree.cpp,v 1.4 2008/04/30 20:44:43 LABELLAHOME\administrator Exp $
    $Log: element_tree.cpp,v $
    Revision 1.4  2008/04/30 20:44:43  LABELLAHOME\administrator
    commit in makefile

    Revision 1.3  2008/04/29 20:28:36  LABELLAHOME\administrator
    commit in makefile

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.4  2004/08/05 16:49:43  tournois
    no message

    Revision 1.3  2004/03/04 18:45:29  tournois
    Compatibility with gcc.

    Revision 1.2  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <list>
#include <dom/element_tree.hpp>
#include <xml/stag.hpp>
#include <xml/etag.hpp>
#include <xml/content.hpp>
//#include <control_flow.hpp>

using namespace std;

XIMOL_DOM_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
element_tree::element_tree()
  :content_()
  ,tag_()
{};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
element_tree::element_tree(xstring const & tag)
  :content_()
  ,tag_(tag)
{};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
element_tree::~element_tree()
{};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
element_tree& element_tree::operator=(const element_tree & x)
{
    if (&x==this) return *this;
    element_tree inter(x);
    swap(inter);
    return *this;
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void element_tree::swap(element_tree & x)
{
    list<element_tree>::swap(x);
    std::swap(content_,x.content_);
    std::swap(tag_,x.tag_);
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xstring const & element_tree::content() const
{
    return content_;
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void element_tree::content(xstring const & x)
{
    content_=x;
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xstring const & element_tree::tag() const
{
    return tag_;
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void element_tree::tag(xstring const & x)
{
    tag_=x;
};

//-----------------------------------------------------------------------------
// Put To operator for the element tree.
//-----------------------------------------------------------------------------
std::ostream& operator<<(std::ostream & os, const element_tree & x)
{
    os << "<" << x.tag().c_str() << ">" << x.content().c_str() << endl;
    if (!x.empty()) {
        list<element_tree>::const_iterator i(x.begin()), i_end(x.end());
        for(;i!=i_end;++i)
            os << *i; 
    };
    os << "</" << x.tag().c_str() << ">" << endl;
    return os;
	
};

//-----------------------------------------------------------------------------
// Put To operator for the element tree.
//-----------------------------------------------------------------------------
ximol::xostream& operator<<(ximol::xostream & xos, const element_tree & x)
{
	
    bool has_tag=(! x.tag().empty());
    if (has_tag) 
        xos << xml::stag(x.tag());
    xos << x.content().c_str();
    element_tree::const_iterator i(x.begin()), i_end(x.end());
    for(;i!=i_end;++i)
        xos << *i;
    if (has_tag) 
        xos << xml::etag();
    return xos;
	
};

//-----------------------------------------------------------------------------
// Get from operator for the element tree.
//-----------------------------------------------------------------------------
ximol::xistream& operator>>(ximol::xistream & xis, element_tree & x)
{
	
    XIMOL_XML_USING_NAMESPACE;
    bool has_etag=is_stag(xis);
    xstring the_tag;
    if (has_etag) {
        xis >> stag(the_tag);
        x.tag(the_tag);
    };
    while (!is_etag(xis))
    {
        if (is_stag(xis))
        {
            element_tree e;
            xis >> e;
            x.push_back(e);
        } else {
            xstring val;
            xis >> xml::content(val);
            x.content(val);
        };
    };

    if (has_etag)
        xis >> xml::etag();
    return xis;
	
};

XIMOL_DOM_END_NAMESPACE
