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
	\brief Define open_stag Interface.
	
	\author Tournois Florent
	\version 1.0

    $Id: open_stag.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: open_stag.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:46  vlabella
    adding in ximol and xmlparser

    Revision 1.7  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

    Revision 1.6  2004/02/25 18:59:13  tournois
    imporve the gcc compatibility.

    Revision 1.5  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.4  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.3  2004/02/21 20:03:58  tournois
    Change the stag, etag, open_stag, box and rebox template with macro.

    Revision 1.2  2004/02/10 12:33:46  tournois
    no message

    Revision 1.1  2004/01/15 21:26:01  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_XML_OPEN_STAG_HPP_
#define XIMOL_XML_OPEN_STAG_HPP_

#include <qname.hpp>
#include <parser/utils.hpp>

XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/// Manipulator for the start tag.
//=============================================================================
template < typename Qname, typename Attributes >
struct manipulator_open_stag
{
    manipulator_open_stag(Qname qname):qname_(new Qname(qname)),att_(NULL){};
    manipulator_open_stag(Qname qname, Attributes & att):qname_(new Qname(qname)),att_(&att){};
    manipulator_open_stag(const manipulator_open_stag<Qname, Attributes> & x):qname_(new Qname(*x.qname_)),att_(x.att_){};
    ~manipulator_open_stag(){ delete qname_; };

    Qname * qname_;
    Attributes * att_;
private:
    manipulator_open_stag<Qname, Attributes> & operator=(const manipulator_open_stag<Qname, Attributes> & x);
};

//-----------------------------------------------------------------------------
// PutTo operator for the open_stag.
//-----------------------------------------------------------------------------
template < typename Qname, typename Attributes >
xostream& operator<<(xostream& xos, const manipulator_open_stag<Qname,Attributes>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    if (m.att_==NULL) {
        if (m.qname_->is_prefix_set())
            write_open_stag(xos,m.qname_->get_local(),m.qname_->get_prefix());
        else 
            write_open_stag(xos,m.qname_->get_local());
    } else {
        if (m.qname_->is_prefix_set())
            write_open_stag(xos,m.qname_->get_local(),*(m.att_),m.qname_->get_prefix());
        else {
            write_open_stag(xos,m.qname_->get_local(),*(m.att_));
        };
    };
	return xos;
};

//-----------------------------------------------------------------------------
// PutTo operator for the open_stag.
//-----------------------------------------------------------------------------
template < typename Qname, typename Attributes >
xistream& operator>>(xistream& xis, const manipulator_open_stag<Qname,Attributes>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    xstring prefix, local;

    if (has_skip_whitespace(xis)) 
        read_optionnal_space(xis);

    if (m.att_==NULL) {
        read_open_stag(xis, local, prefix);
    } else {
        read_open_stag(xis, local, *(m.att_), prefix);
    };
    m.qname_->set_local(local);

    if (m.qname_->is_prefix_set())
    {
        try {
            m.qname_->set_prefix(prefix);
        } catch (std::exception&) {
            m.qname_->set_prefix(xis.context.get_short_namespace(prefix));
        };
    };

	return xis;
};

// define all function open_stag(string1, string2, attributes)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2, type3) \
    XIMOL_DECL manipulator_open_stag< qualified_name<type1, type2>, type3> open_stag(type1 & prefix, type2 & local, type3 & att); 
#include <config/define_functions_prefix_local_attributes.hpp>

// define all function open_stag(string1, string2)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2) \
    XIMOL_DECL manipulator_open_stag< qualified_name<type1, type2>, xml::attributes> open_stag(type1 & prefix, type2 & local); 
#include <config/define_functions_prefix_local.hpp>

// define all function open_stag(string1, attribute)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type3) \
    XIMOL_DECL manipulator_open_stag< qualified_name<type1, type1>, type3> open_stag(type1 & local, type3 & att); 
#include <config/define_functions_local_attributes.hpp>

// define all function open_stag(string1)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1) \
    XIMOL_DECL manipulator_open_stag< qualified_name<type1, type1>, xml::attributes> open_stag(type1 & local); 
#include <config/define_functions_local.hpp>

XIMOL_XML_END_NAMESPACE

#endif // #ifndef XIMOL_XML_OPEN_STAG_HPP_
