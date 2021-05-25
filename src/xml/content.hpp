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
	\brief Define content Interface.
	
    \todo make a function boxed_content

	\author Tournois Florent
	\version 1.0

    $Id: content.hpp,v 1.3 2009/12/30 22:12:05 vlabella Exp $
    $Log: content.hpp,v $
    Revision 1.3  2009/12/30 22:12:05  vlabella
    commit in makefile
    Committed on the Free edition of March Hare Software CVSNT Server.
    Upgrade to CVS Suite for more features and support:
    http://march-hare.com/cvsnt/

    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.8  2004/08/05 16:49:44  tournois
    no message

    Revision 1.7  2004/03/04 18:45:29  tournois
    Compatibility with gcc.

    Revision 1.6  2004/02/25 18:59:13  tournois
    imporve the gcc compatibility.

    Revision 1.5  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.4  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.3  2004/02/15 10:07:03  hfp
    content-functions (some) needs an ambiguity-buster ("hidden" arg as defaulted param) to compile

    Revision 1.2  2004/01/29 20:52:35  tournois
    doc and tutorial.

    Revision 1.1  2004/01/09 18:26:29  tournois
    Add box and content manipulator.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_XML_CONTENT_HPP_
#define XIMOL_XML_CONTENT_HPP_

#include <stream.hpp>
#include <assignment.hpp>
#include <parser/utils.hpp>
#include <parser/def_signs.hpp>
#include <sstream>

XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/// Manipulator for the char data content.
//=============================================================================
class XIMOL_DECL manipulator_char_data_content
{
public:
    manipulator_char_data_content(xstring const & xstr);
    manipulator_char_data_content(const manipulator_char_data_content& x);

    manipulator_char_data_content& operator=(const manipulator_char_data_content& x);
    manipulator_char_data_content& operator=(xstring const & xstr);

    ::std::basic_istringstream<xchar_t>& istr();
    xstring xstr() const;
    void xstr(xstring const & xstr);

    ::std::string str() const;
    void str(const ::std::string & str);

private:
    ::std::basic_istringstream<xchar_t> content_;
}; // End of class manipulator_char_data_content

//-----------------------------------------------------------------------------
// content manipulator
/*  @ingroup xml 
    content    ::=    CharData? ((element | Reference | cd_sect | PI | comment) CharData?)* 
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
manipulator_char_data_content char_data_content(xistream& xis);

//=============================================================================
/// Manipulator for the char data content.
//=============================================================================
template < typename T >
class manipulator_char_content
{
public:
    typedef T string_type;

public:
    manipulator_char_content(string_type & x)
        :x_(x)
    {};

    manipulator_char_content(const manipulator_char_content<T> & x)
        :x_(x.x_)
    {};

    void set(xstring const & x) const
    {
        assignment_to_string::equality(x_, x);
    };

    xstring get() const
    {
        return str<std::wstring>::cast(x_);
    };

private:
    const manipulator_char_content<T> & operator=(const manipulator_char_content<T> & x);

private:
    string_type & x_;

}; // end of class manipulator_char_content<T>

//-----------------------------------------------------------------------------
// PutTo operator for the char_content.
//-----------------------------------------------------------------------------
template < typename T >
xostream& operator<<(xostream& xos, const manipulator_char_content<T>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;

    xstring buffer(m.get());
	xstring::const_iterator i(buffer.begin()), i_end(buffer.end());

	for(;i!=i_end;++i)
	{
		switch (*i)
		{
		case XCHAR_AMPERSAND: 
		case XCHAR_LESS_THAN_SIGN:
		case XCHAR_RIGHT_SQUARE_BRACKET:
			write_char_ref(xos,*i);
			break;
		default:
			write_xchar(xos,*i);
		}
	}
	return xos;
};

//-----------------------------------------------------------------------------
// PutTo operator for the char_content.
//-----------------------------------------------------------------------------
template < typename T >
xistream& operator>>(xistream& xis, const manipulator_char_content<T>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    m.set(char_data_content(xis).xstr());
	return xis;
};

//=============================================================================
/// class for the qualified name
//=============================================================================
template < typename T >
class manipulator_data_content
{
public:
    typedef T object_type;

public:
    manipulator_data_content(object_type & x)
        :x_(x)
    {};

    manipulator_data_content(const manipulator_data_content<T> & x)
        :x_(x.x_)
    {};

    void set(const object_type & x) const
    {
        assignment_std::equality(x_, x);
    };

    void set_string(xstring const & xstr) const
    {
        assignment_char_serialization::equality(x_, xstr);
    };

    const object_type & get() const
    {
        return x_;
    };

    xstring get_string() const
    {
        return str<std::wstring>::cast(x_);
    };

private:
    const manipulator_data_content<T> & operator=(const manipulator_data_content<T> & x);

private:
    object_type & x_;

}; // end of class manipulator_data_content<T>




//-----------------------------------------------------------------------------
// PutTo operator for the cdata.
//-----------------------------------------------------------------------------
template < typename T >
xostream& operator<<(xostream& xos, const manipulator_data_content<T>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    xstring xs = m.get_string();
    xos << manipulator_char_content<xstring>(xs);
    // xos << manipulator_char_content<xstring>(m.get_string());
    
	return xos;
};

//-----------------------------------------------------------------------------
// PutTo operator for the cdata.
//-----------------------------------------------------------------------------
template < typename T >
xistream& operator>>(xistream& xis, const manipulator_data_content<T>& m)
{
	XIMOL_PARSER_USING_NAMESPACE;
    xstring xstr;
    manipulator_char_content<xstring> manip(xstr);
    xis >> manip;
    m.set_string(xstr);
	return xis;
};


#define XIMOL_CONTENT_CHAR_SPECIALIZATION(type)								\
	inline manipulator_char_content<type> content(type& t, bool = false) {	\
		return manipulator_char_content<type>(t);							\
	}

	XIMOL_CONTENT_CHAR_SPECIALIZATION(std::string)
	XIMOL_CONTENT_CHAR_SPECIALIZATION(const std::string)
	XIMOL_CONTENT_CHAR_SPECIALIZATION(std::wstring)
	XIMOL_CONTENT_CHAR_SPECIALIZATION(const std::wstring)
	XIMOL_CONTENT_CHAR_SPECIALIZATION(char *)
	XIMOL_CONTENT_CHAR_SPECIALIZATION(const char *)
	XIMOL_CONTENT_CHAR_SPECIALIZATION(wchar_t *)
	XIMOL_CONTENT_CHAR_SPECIALIZATION(const wchar_t *)

#undef XIMOL_CONTENT_CHAR_SPECIALIZATION


template<typename T>
manipulator_data_content<T> content(T& t)
{ 
    return manipulator_data_content<T>(t);
}


XIMOL_XML_END_NAMESPACE

#endif // #ifndef XIMOL_XML_CONTENT_HPP_
