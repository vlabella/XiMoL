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
	\brief Define xml_decl Interface.
	
	\author Tournois Florent
	\version 1.0

    $Id: xml_decl.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: xml_decl.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 16:36:16  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:46  vlabella
    adding in ximol and xmlparser

    Revision 1.8  2004/02/25 18:59:13  tournois
    imporve the gcc compatibility.

    Revision 1.7  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.6  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.5  2004/01/19 20:40:56  tournois
    Add min, max and digits facet.
    Create the control flow file.

    Revision 1.4  2004/01/18 11:40:58  tournois
    Add the pattern facet.

    Revision 1.3  2004/01/08 20:02:30  tournois
    Add XIMOL_XML_NAMESPACE_PATH::comment and assignment mainuplator.

    Revision 1.2  2004/01/07 12:16:36  tournois
    no message

    Revision 1.1  2004/01/06 21:04:10  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_XML_XML_DECL_HPP_
#define XIMOL_XML_XML_DECL_HPP_

#include <assignment.hpp>
#include <parser/utils.hpp>

XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/// class for the qualified name
//=============================================================================
template < typename VersionInfo, typename EncodingDecl , typename SDDecl >
class xml_declaration
{
public:
    typedef VersionInfo  version_info_type;
    typedef EncodingDecl encoding_decl_type;
    typedef SDDecl       sddecl_type;

public:
    xml_declaration(version_info_type & version_info)
        :sddecl_(NULL)
        ,encoding_decl_(NULL)
        ,version_info_(version_info)
    {};

    xml_declaration(version_info_type & version_info, encoding_decl_type & encoding_decl)
        :sddecl_(NULL)
        ,encoding_decl_(&encoding_decl)
        ,version_info_(version_info)
    {};

    xml_declaration(version_info_type & version_info, sddecl_type & sddecl)
        :sddecl_(&sddecl)
        ,encoding_decl_(NULL)
        ,version_info_(version_info)
    {};

    xml_declaration(version_info_type & version_info, encoding_decl_type & encoding_decl, sddecl_type & sddecl)
        :sddecl_(&sddecl)
        ,encoding_decl_(&encoding_decl)
        ,version_info_(version_info)
    {};

    xml_declaration(const xml_declaration<VersionInfo,EncodingDecl,SDDecl> & x)
        :sddecl_(x.sddecl_)
        ,encoding_decl_(x.encoding_decl_)
        ,version_info_(x.version_info_)
    {};

    template < typename T >
    void set_version_info(const T & version_info)
    {
        assignment_to_string::equality(version_info_, version_info);
    };

    xstring get_version_info() const { return str< ::std::wstring>::cast(version_info_); };

    template < typename T >
    void set_encoding_decl(const T & encoding_decl)
    {
        if (encoding_decl_==NULL) 
            XIMOL_THROW << _xtr(L"The encoding_decl could not be set") << XIMOL_AS_ERROR; 
        assignment_to_string::equality(*encoding_decl_, encoding_decl);
    };

    bool is_encoding_decl_set() const { return encoding_decl_!=NULL; }; 
    xstring get_encoding_decl() const { return str< ::std::wstring>::cast(*encoding_decl_); };

    void set_sddecl(bool sddecl)
    {
        if (sddecl_==NULL) 
            XIMOL_THROW << _xtr(L"The sddecl could not be set") << XIMOL_AS_ERROR; 
        assignment_std::equality(*sddecl_, sddecl);
    };

    bool is_sddecl_set() const { return sddecl_!=NULL; }; 
    bool get_sddecl() const { return *sddecl_; };

private:
    const xml_declaration<VersionInfo,EncodingDecl,SDDecl> & operator=(const xml_declaration<VersionInfo,EncodingDecl,SDDecl> & x);

private:
    sddecl_type *        sddecl_;
    encoding_decl_type * encoding_decl_;
    version_info_type &  version_info_;

}; // end of class xml_declaration<VersionInfo,EncodingDecl,SDDecl>

//-----------------------------------------------------------------------------
// PutTo operator for the xml declaration.
//-----------------------------------------------------------------------------
template < typename VersionInfo, typename EncodingDecl , typename SDDecl >
xostream& operator<<(xostream& xos, const xml_declaration<VersionInfo,EncodingDecl,SDDecl>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    if (m.is_sddecl_set()) {
        if (m.is_encoding_decl_set())
            write_xml_decl(xos,m.get_version_info(), m.get_encoding_decl(), m.get_sddecl() ? L"yes" : L"no");
        else 
            write_xml_decl(xos,m.get_version_info(), L"" , m.get_sddecl() ? L"yes" : L"no");
    } else {
        if (m.is_encoding_decl_set())
            write_xml_decl(xos,m.get_version_info(), m.get_encoding_decl());
        else 
            write_xml_decl(xos,m.get_version_info());
    };
	return xos;
};

//-----------------------------------------------------------------------------
// PutTo operator for the stag.
//-----------------------------------------------------------------------------
template < typename VersionInfo, typename EncodingDecl , typename SDDecl >
xistream& operator>>(xistream& xis, xml_declaration<VersionInfo,EncodingDecl,SDDecl>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
	xstring ver, enc;
	bool sd;

	read_xml_decl(xis, ver, enc, sd);
    
    m.set_version_info(ver);

    if (m.is_encoding_decl_set())
        m.set_encoding_decl(enc);

    if (m.is_sddecl_set())
        m.set_sddecl(sd);

	return xis;
};

template < typename VersionInfo, typename EncodingDecl>
xml_declaration<VersionInfo,EncodingDecl,bool> xml_decl(VersionInfo & version_info, EncodingDecl & encoding_decl, bool & sddecl )
{
    return xml_declaration<VersionInfo,EncodingDecl,bool>(version_info, encoding_decl, sddecl);
};

template < typename VersionInfo, typename EncodingDecl>
xml_declaration<VersionInfo,EncodingDecl,const bool> xml_decl(VersionInfo & version_info, EncodingDecl & encoding_decl, const bool & sddecl )
{
    return xml_declaration<VersionInfo,EncodingDecl,const bool>(version_info, encoding_decl, sddecl);
};

template < typename VersionInfo, typename EncodingDecl>
xml_declaration<VersionInfo,EncodingDecl,bool> xml_decl(VersionInfo & version_info, EncodingDecl & encoding_decl)
{
    return xml_declaration<VersionInfo,EncodingDecl,bool>(version_info, encoding_decl);
};

template < typename VersionInfo>
xml_declaration<VersionInfo, const xstring, bool> xml_decl(VersionInfo & version_info, bool & sddecl )
{
    return xml_declaration<VersionInfo, const xstring, bool>(version_info, sddecl);
};

template < typename VersionInfo>
xml_declaration<VersionInfo, const xstring, const bool> xml_decl(VersionInfo & version_info, const bool & sddecl )
{
    return xml_declaration<VersionInfo, const xstring, const bool>(version_info, sddecl);
};

template < typename VersionInfo>
xml_declaration<VersionInfo, const xstring, const bool> xml_decl(VersionInfo & version_info)
{
    return xml_declaration<VersionInfo, const xstring, const bool>(version_info);
};

struct xml_declaration_alone {};
inline xml_declaration_alone xml_decl(){ return xml_declaration_alone(); };

//-----------------------------------------------------------------------------
// PutTo operator for the xml declaration.
//-----------------------------------------------------------------------------
XIMOL_DECL xostream& operator<<(xostream& xos, const xml_declaration_alone&);

//-----------------------------------------------------------------------------
// PutTo operator for the stag.
//-----------------------------------------------------------------------------
XIMOL_DECL xistream& operator>>(xistream& xis, xml_declaration_alone&);

XIMOL_XML_END_NAMESPACE

#endif // #ifndef XIMOL_XML_XML_DECL_HPP_
