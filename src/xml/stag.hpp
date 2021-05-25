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
	\brief Define stag Interface.
	
	\author Tournois Florent
	\version 1.0

    $Id: stag.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: stag.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:46  vlabella
    adding in ximol and xmlparser

    Revision 1.17  2004/03/19 18:28:39  tournois
    packaging for the version 0.8

    Revision 1.16  2004/03/04 18:45:29  tournois
    Compatibility with gcc.

    Revision 1.15  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

    Revision 1.14  2004/02/25 18:59:13  tournois
    imporve the gcc compatibility.

    Revision 1.13  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.12  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.11  2004/02/21 20:03:58  tournois
    Change the stag, etag, open_stag, box and rebox template with macro.

    Revision 1.10  2004/02/09 12:41:25  tournois
    Fix bug about error message.
    Add a read_optionnal_space before the stag read.

    Revision 1.9  2004/01/27 21:49:52  tournois
    Add docs and tutorial.

    Revision 1.8  2004/01/25 17:33:09  tournois
    no message

    Revision 1.7  2004/01/15 21:26:01  tournois
    no message

    Revision 1.6  2004/01/09 18:26:29  tournois
    Add box and content manipulator.

    Revision 1.5  2003/12/10 20:32:18  tournois
    Fix somes bugs about attributes and now tests are all check.

    Revision 1.4  2003/12/09 19:57:28  tournois
    Fix some bugs about attributes classes.

    Revision 1.3  2003/12/03 12:50:37  hfp
    include dependencies and type forwarding

    Revision 1.2  2003/11/27 15:31:55  hfp
    partially adapted to vc6.

    Revision 1.1  2003/11/19 20:52:54  tournois
    Add new manipulator for stag and etag.
    Correct bugs and add tests.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_XML_STAG_HPP_
#define XIMOL_XML_STAG_HPP_

#include <qname.hpp>
#include <parser/utils.hpp>


XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/// Manipulator for the start tag.
//=============================================================================
template < typename Qname, typename Attributes >
struct manipulator_stag
{
    manipulator_stag(Qname qname):qname_(new Qname(qname)),att_(NULL){};
    manipulator_stag(Qname qname, Attributes & att):qname_(new Qname(qname)),att_(&att){};
    manipulator_stag(const manipulator_stag<Qname, Attributes> & x):qname_(new Qname(*x.qname_)),att_(x.att_){};
    ~manipulator_stag(){ delete qname_; };

    Qname * qname_;
    Attributes * att_;
private:
    manipulator_stag<Qname, Attributes> & operator=(const manipulator_stag<Qname, Attributes> & x);
};

//-----------------------------------------------------------------------------
// PutTo operator for the stag.
//-----------------------------------------------------------------------------
template < typename Qname, typename Attributes >
xostream& operator<<(xostream& xos, const manipulator_stag<Qname,Attributes>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    if (m.att_==NULL) {
        if (m.qname_->is_prefix_set())
            write_stag(xos,m.qname_->get_local(),m.qname_->get_prefix());
        else 
            write_stag(xos,m.qname_->get_local());
    } else {
        if (m.qname_->is_prefix_set())
            write_stag(xos,m.qname_->get_local(),*(m.att_),m.qname_->get_prefix());
        else {
            write_stag(xos,m.qname_->get_local(),*(m.att_));
        };
    };
	return xos;
};

//-----------------------------------------------------------------------------
// PutTo operator for the stag.
//-----------------------------------------------------------------------------
template < typename Qname, typename Attributes >
xistream& operator>>(xistream& xis, manipulator_stag<Qname,Attributes> m)
{
	XIMOL_PARSER_USING_NAMESPACE;

    if (has_skip_whitespace(xis)) 
        read_optionnal_space(xis);

    xstring prefix, local;
    bool has_an_open_stag=xis.context.is_open_stag();
    if (m.att_==NULL) {
        read_stag(xis, local, prefix);
    } else {
        read_stag(xis, local, *(m.att_), prefix);
    };

    try {
        m.qname_->set_local(local);
    } catch ( std::exception & ) {
        if (!has_an_open_stag) throw;
    };

    try {
        if (m.qname_->is_prefix_set())
        {
            try {
                m.qname_->set_prefix(prefix);
            } catch (std::exception&) {
                m.qname_->set_prefix(xis.context.get_short_namespace(prefix));
            };
        };
    } catch (std::exception&) {
        if (!has_an_open_stag) throw;
    }; 

	return xis;
};

//-----------------------------------------------------------------------------
/** Start tag manipulator creator.
 * This function create the start tag manipulator with the adjusted type.
 * Only the local part of the tag name will be written or read from the stream.
 * This manipulator read or write start tag on the stream. The writer does not
 * make any problem, but the reader could. If the lement is const, the 
 * manipulator only check the equality.
 *
 * The following code write the start tag on the stream:
 * \code
 *   xos << xml::stag("tag");
 * \code
 * If you want to read the tag, you could write:
 * \code 
 *   std::string tag;
 *   xis >> xml::stag(tag);
 * \endcode
 * The probleme is the wide character conversion, because with this code,
 * you could not read the wide character tag. You could also write:
 * \code 
 *   std::xstring tag;
 *   xis >> xml::stag(tag);
 * \endcode
 * And if you only want to verify the tag, you could write:
 * \code
 *   xis >> xml::stag("Tag");
 * \endcode
 * or 
 * \code
 *   xis >> xml::stag(L"Tag");
 * \endcode
 *
 * requirement: The character of the String1 must be managed by str<T>::cast
 *
 * You could see examples.
 */
//-----------------------------------------------------------------------------
// define all function stag(string1, string2, attributes)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2, type3) \
    XIMOL_DECL manipulator_stag< qualified_name<type1, type2>, type3> stag(type1 & prefix, type2 & local, type3 & att); 
#include <config/define_functions_prefix_local_attributes.hpp>

// define all function stag(string1, string2)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type2) \
    XIMOL_DECL manipulator_stag< qualified_name<type1, type2>, xml::attributes> stag(type1 & prefix, type2 & local); 
#include <config/define_functions_prefix_local.hpp>

// define all function stag(string1, attribute)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1, type3) \
    XIMOL_DECL manipulator_stag< qualified_name<type1, type1>, type3> stag(type1 & local, type3 & att); 
#include <config/define_functions_local_attributes.hpp>

// define all function stag(string1)
#define XIMOL_HEADER_DEFINE_FUNCTION(type1) \
    XIMOL_DECL manipulator_stag< qualified_name<type1, type1>, xml::attributes> stag(type1 & local); 
#include <config/define_functions_local.hpp>

XIMOL_XML_END_NAMESPACE

#endif // #ifndef XIMOL_XML_STAG_HPP_
