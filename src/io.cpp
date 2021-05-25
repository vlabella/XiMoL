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
	\brief GetFrom and PutTo operator for common char and xchar_t (Implementation).

    \author Tournois Florent
	\version 1.0

    $Id: io.cpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: io.cpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.3  2005/05/12 01:31:48  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 01:31:10  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.13  2004/08/05 16:49:42  tournois
    no message

    Revision 1.12  2004/05/26 07:48:03  tournois
    no message

    Revision 1.11  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.10  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.9  2004/02/15 10:13:36  hfp
    an additional to_wide_char()-call is needed to compile

    Revision 1.8  2004/02/02 19:51:44  tournois
    Add a control_flow and finish the attribute tutorial.

    Revision 1.7  2003/11/27 15:31:55  hfp
    partially adapted to vc6.

    Revision 1.6  2003/11/19 20:52:54  tournois
    Add new manipulator for stag and etag.
    Correct bugs and add tests.

    Revision 1.5  2003/11/18 18:54:51  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.4  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.3  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.2  2003/10/09 16:59:45  tournois
    add the stringstream initialisation.
    add some prolog test.
    Correct code for VC6.0.

    Revision 1.1  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <io.hpp>
#include <stream.hpp>
#include <str_cast.hpp>
#include <algorithm>
#include <functional>
#include <locale>

XIMOL_BEGIN_PRIVATE_NAMESPACE

wchar_t to_wide_char(char c)
{
    XIMOL_USING_NAMESPACE;
    return converter<wchar_t,char>::get(c);
};

char to_narrow_char(wchar_t xc)
{
    XIMOL_USING_NAMESPACE;
    return converter<char,wchar_t>::get(xc);
};
/*
unused functions
wchar_t to_wide_char(char c, ::std::basic_ios<wchar_t>& ios)
{
    using namespace std;
    typedef ctype<wchar_t> ctype_facet;
    const ctype_facet & the_facet = XIMOL_USE_FACET(ios.getloc(), ctype_facet);
    return the_facet.widen(c);
};

char to_narrow_char(wchar_t xc, ::std::basic_ios<wchar_t>& ios)
{
    using namespace std;
    typedef ctype<wchar_t> ctype_facet;
    const ctype_facet & the_facet = XIMOL_USE_FACET(ios.getloc(), ctype_facet);
    return the_facet.narrow(xc,' ');
};
*/
XIMOL_END_PRIVATE_NAMESPACE

namespace std {
    ostream& operator<<(ostream& ostream_, const wchar_t* pXChar_)
    {
		if(pXChar_) while(*pXChar_ != '\0') operator<<(ostream_, to_narrow_char(*pXChar_++));
		return ostream_;
    }

/*    ostream& operator<<(ostream & os, const wchar_t xc)
    {
	    return os << to_narrow_char(xc);
    };
*/
/*    ostream& operator<<(ostream & os, const wstring & wstr)
    {
        return os << wstr.c_str();
    };*/

    wostream& operator<<(wostream& wostream_, const char* pChar_)
    {
		if(pChar_) while (*pChar_ != '\0') operator<<(wostream_, to_wide_char(*pChar_++));
        return wostream_;
    }

/*    wostream& operator<<(wostream & wos, const char c)
    {
        return wos << to_wide_char(c,wos);
    };
*/
/*    wostream& operator<<(wostream & wos, const string & str)
    {
        return wos << str.c_str();
    };
*/

/*    istream& operator>>(istream & is, wchar_t & xc)
    {
        char c;
        is >> c;
        xc=to_wide_char(c);
        return is;
    };
*/
/*    istream& operator>>(istream & is, wstring & wstr)
    {
        string str;
        is >> str;
        wstr.resize(str.length());
        transform(str.begin(),str.end(),wstr.begin(),pointer_to_unary_function<char, wchar_t>(to_wide_char));
        return is;
    };
*/

/*    wistream& operator>>(wistream & wis, char & c)
    {
        wchar_t wc;
        wis >> wc;
        c=to_narrow_char(wc,wis);
        return wis;
    };
*/
/*    wistream& operator>>(wistream & wis, string & str)
    {
        wstring wstr;
        wis >> wstr;
        str.resize(wstr.length());
        transform(wstr.begin(),wstr.end(),str.begin(),pointer_to_unary_function<wchar_t, char>(to_narrow_char));
        return wis;
    };
*/

}; // end of namespace std

XIMOL_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// XML stream put to operator.
//-----------------------------------------------------------------------------
XIMOL_TEMPLATE_NULL
xostream& operator<<(xostream& xos, const char c)
{
	//typedef ctype<char> CTypeFacet;
	//const CTypeFacet& Facet = XIMOL_USE_FACET(locale::classic(), CTypeFacet);
	xos.rdbuf()->sputc((xchar_t)((unsigned char)c));
	return xos;
}

//-----------------------------------------------------------------------------
// XML stream put to operator.
//-----------------------------------------------------------------------------
XIMOL_TEMPLATE_NULL
xostream& operator<<(xostream& xos, const char * c)
{
	//typedef ctype<char> CTypeFacet;
	//const CTypeFacet& Facet = XIMOL_USE_FACET(locale::classic(), CTypeFacet);
	while (*c != '\0') xos.rdbuf()->sputc((xchar_t)((unsigned char)*c++));
	return xos;
}

////-----------------------------------------------------------------------------
//// XML stream put to operator.
////-----------------------------------------------------------------------------
//XIMOL_TEMPLATE_NULL
//xostream& operator<<(xostream& xostream_, const std::string& str_)
//{
//	return xostream_ << str_.c_str();
//}

//-----------------------------------------------------------------------------
// XML stream put to operator.
//-----------------------------------------------------------------------------
//XIMOL_TEMPLATE_NULL
//xostream& operator<<(xostream& xos, const string& c)
//{
//	return xos<<c.c_str();
//}

//-----------------------------------------------------------------------------
// XML stream put to operator.
//-----------------------------------------------------------------------------
//XIMOL_TEMPLATE_NULL
//xostream& operator<<(xostream& xos, xchar_t c)
//{
//	xos.rdbuf()->sputc((xchar_t)(c));
//	return xos;
//}

//-----------------------------------------------------------------------------
// XML stream put to operator.
//-----------------------------------------------------------------------------
XIMOL_TEMPLATE_NULL
xostream& operator<<(xostream& xos, const xchar_t * c)
{
	while (*c != '\0') xos.rdbuf()->sputc((xchar_t)(*c++));
	return xos;
}

//-----------------------------------------------------------------------------
// XML stream put to operator.
//-----------------------------------------------------------------------------
XIMOL_TEMPLATE_NULL
xostream& operator<<(xostream& xos, xstring const & c)
{
	return xos<<c.c_str();
}

//-----------------------------------------------------------------------------
// XML stream get from operator.
//-----------------------------------------------------------------------------
//XIMOL_TEMPLATE_NULL
//xistream& operator>>(xistream& xis, char & c)
//{
//	xchar_t xc;
//	xis >> xc;
//	c=(char)(xc);
//	return xis;
//}

//-----------------------------------------------------------------------------
// XML stream get from operator.
//-----------------------------------------------------------------------------
//XIMOL_TEMPLATE_NULL
//xistream& operator>>(xistream& xis, xchar_t & c)
//{
//	//((::std::basic_istream<xchar_t>&)xis)>>c;
//	if (! xis.get(c))
//		xis.setstate(std::ios::failbit | std::ios::eofbit); // with this line we could acces the xstream buffer for more than one putback.
//	return xis;
//}

using namespace std;

xistream& operator>>(xistream& xis, bool& c){ (basic_istream<xchar_t>&)xis>>c; return xis;}
xistream& operator>>(xistream& xis, short& c){ (basic_istream<xchar_t>&)xis>>c; return xis;}
xistream& operator>>(xistream& xis, long& c){ (basic_istream<xchar_t>&)xis>>c; return xis;}
xistream& operator>>(xistream& xis, unsigned long& c){ (basic_istream<xchar_t>&)xis>>c; return xis;}
xistream& operator>>(xistream& xis, int& c){ (basic_istream<xchar_t>&)xis>>c; return xis;}
xistream& operator>>(xistream& xis, unsigned int& c){ (basic_istream<xchar_t>&)xis>>c; return xis;}
xistream& operator>>(xistream& xis, float& c){ (basic_istream<xchar_t>&)xis>>c; return xis;}
xistream& operator>>(xistream& xis, double& c){ (basic_istream<xchar_t>&)xis>>c; return xis;}
xistream& operator>>(xistream& xis, long double& c){ (basic_istream<xchar_t>&)xis>>c; return xis;}
xistream& operator>>(xistream& xis, ::std::basic_istream<xchar_t>& (*fun)( ::std::basic_istream<xchar_t>&)){ fun(xis); return xis;}

xostream& operator<<(xostream& xos, const bool           c){ (basic_ostream<xchar_t>&)xos<<c; return xos;}
xostream& operator<<(xostream& xos, const short          c){ (basic_ostream<xchar_t>&)xos<<c; return xos;}
xostream& operator<<(xostream& xos, const long           c){ (basic_ostream<xchar_t>&)xos<<c; return xos;}
xostream& operator<<(xostream& xos, const unsigned long  c){ (basic_ostream<xchar_t>&)xos<<c; return xos;}
xostream& operator<<(xostream& xos, const int            c){ (basic_ostream<xchar_t>&)xos<<c; return xos;}
xostream& operator<<(xostream& xos, const unsigned int   c){ (basic_ostream<xchar_t>&)xos<<c; return xos;}
xostream& operator<<(xostream& xos, const float          c){ (basic_ostream<xchar_t>&)xos<<c; return xos;}
xostream& operator<<(xostream& xos, const double         c){ (basic_ostream<xchar_t>&)xos<<c; return xos;}
xostream& operator<<(xostream& xos, const long double    c){ (basic_ostream<xchar_t>&)xos<<c; return xos;}
xostream& operator<<(xostream& xos, ::std::basic_ostream<xchar_t>& (*fun)( ::std::basic_ostream<xchar_t>&)){ fun(xos); return xos;}

XIMOL_END_NAMESPACE
