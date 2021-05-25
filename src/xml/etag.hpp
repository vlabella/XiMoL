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
	\brief Define etag Interface.
	
	\author Tournois Florent
	\version 1.0

    $Id: etag.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: etag.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.3  2005/05/12 02:54:37  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 02:53:45  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:46  vlabella
    adding in ximol and xmlparser

    Revision 1.10  2004/03/04 18:45:29  tournois
    Compatibility with gcc.

    Revision 1.9  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

    Revision 1.8  2004/02/25 18:59:13  tournois
    imporve the gcc compatibility.

    Revision 1.7  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.6  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.5  2004/02/21 20:03:58  tournois
    Change the stag, etag, open_stag, box and rebox template with macro.

    Revision 1.4  2004/02/10 12:33:46  tournois
    no message

    Revision 1.3  2003/12/03 12:50:37  hfp
    include dependencies and type forwarding

    Revision 1.2  2003/12/03 12:39:36  hfp
    include dependencies and type forwarding

    Revision 1.1  2003/11/19 20:52:54  tournois
    Add new manipulator for stag and etag.
    Correct bugs and add tests.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_XML_ETAG_HPP_
#define XIMOL_XML_ETAG_HPP_

#include <qname.hpp>
#include <xml/content.hpp>
#include <xml/open_stag.hpp>
#include <control_flow.hpp>
#include <parser/utils.hpp>


XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/// Manipulator for the start tag.
//=============================================================================
template < typename Qname >
struct manipulator_etag
{
    manipulator_etag():qname_(NULL){};
    manipulator_etag(Qname qname):qname_(new Qname(qname)){};
    manipulator_etag(const manipulator_etag<Qname> & x):qname_(new Qname(*x.qname_)){};
    ~manipulator_etag(){ delete qname_; };

    Qname * qname_;
private:
    manipulator_etag<Qname> & operator=(const manipulator_etag<Qname> & x);
};

//-----------------------------------------------------------------------------
// PutTo operator for the etag.
//-----------------------------------------------------------------------------
template < typename Qname>
xostream& operator<<(xostream& xos, const manipulator_etag<Qname>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    if (m.qname_==NULL) {
        write_etag(xos);
    } else { 
        if (m.qname_->is_prefix_set())
            write_etag(xos,m.qname_->get_local(),m.qname_->get_prefix());
        else 
            write_etag(xos,m.qname_->get_local());
    };
	return xos;
};

//-----------------------------------------------------------------------------
// PutTo operator for the etag.
//-----------------------------------------------------------------------------
template < typename Qname>
xistream& operator>>(xistream& xis, manipulator_etag<Qname> m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    xstring prefix, local;

    if (has_skip_whitespace(xis)) 
        read_optionnal_space(xis);

    read_etag(xis, local, prefix);
    if (m.qname_!=NULL) {
        m.qname_->set_local(local);
        if (m.qname_->is_prefix_set())
            m.qname_->set_prefix(prefix);
    };
	return xis;
};

// define all function etag(string1, string2)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2) \
    XIMOL_DECL manipulator_etag< qualified_name<type1, type2> > etag(type1 & prefix, type2 & local); 
#include <config/define_functions_prefix_local.hpp>

// define all function etag(string1)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1) \
    XIMOL_DECL manipulator_etag< qualified_name<type1, type1> > etag(type1 & local); 
#include <config/define_functions_local.hpp>

XIMOL_DECL manipulator_etag< qualified_name< ::std::wstring, ::std::wstring> > etag();

XIMOL_XML_END_NAMESPACE

#endif // #ifndef XIMOL_XML_ETAG_HPP_
