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
	\brief cast to string implementation.

    \author Tournois Florent
	\version 1.0

    $Id: str_cast.cpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: str_cast.cpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.4  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.3  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.2  2003/11/27 15:31:55  hfp
    partially adapted to vc6.

    Revision 1.1  2003/11/18 18:54:51  tournois
    Add str_cast and drop the transformation.hpp file.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <str_cast.hpp>
#include <macros.hpp>
#include <algorithm>
#include <functional>
#include <locale>

XIMOL_BEGIN_PRIVATE_NAMESPACE

wchar_t to_wide_char(char c)
{
    using namespace std;
    typedef ctype<wchar_t> ctype_facet;
    static const ctype_facet & the_facet = XIMOL_USE_FACET(::std::locale::classic(), ctype_facet);
    return the_facet.widen(c);
};

char to_narrow_char(wchar_t xc)
{
    using namespace std;
    typedef ctype<wchar_t> ctype_facet;
    static const ctype_facet & the_facet = XIMOL_USE_FACET(::std::locale::classic(), ctype_facet);
    return the_facet.narrow(xc,' ');
};

XIMOL_END_PRIVATE_NAMESPACE

XIMOL_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
char converter<char, wchar_t>::get(wchar_t xc)
{
    return to_narrow_char(xc);
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::string converter<char, wchar_t>::get(const ::std::wstring & wstr)
{
    using namespace std;
    string str;
    str.resize(wstr.length());
    transform(wstr.begin(),wstr.end(),str.begin(),ptr_fun(to_narrow_char));
    return str;
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
char converter<char, char>::get(char c)
{
    return c;
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::string converter<char, char>::get(const ::std::string& str_)
{
    return str_;
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
wchar_t converter<wchar_t, char>::get(char c)
{    
    return to_wide_char(c);

};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::wstring converter<wchar_t, char>::get(const ::std::string& str_)
{
    using namespace std;
    wstring wstr;
    wstr.resize(str_.length());
    transform(str_.begin(), str_.end(), wstr.begin(), ptr_fun(to_wide_char));
    return wstr;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
wchar_t converter<wchar_t, wchar_t>::get(wchar_t xc)
{
    return xc;
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::wstring converter<wchar_t, wchar_t>::get(const ::std::wstring & wstr)
{
    return wstr;
};

XIMOL_END_NAMESPACE
