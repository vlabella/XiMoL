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
	\brief cast to string.

    \author Tournois Florent
	\version 1.0

    $Id: str_cast.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: str_cast.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.9  2004/03/04 18:45:29  tournois
    Compatibility with gcc.

    Revision 1.8  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

    Revision 1.7  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.6  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.5  2004/02/09 12:41:25  tournois
    Fix bug about error message.
    Add a read_optionnal_space before the stag read.

    Revision 1.4  2004/01/18 11:40:58  tournois
    Add the pattern facet.

    Revision 1.3  2003/12/09 19:57:27  tournois
    Fix some bugs about attributes classes.

    Revision 1.2  2003/11/27 15:31:55  hfp
    partially adapted to vc6.

    Revision 1.1  2003/11/18 18:54:51  tournois
    Add str_cast and drop the transformation.hpp file.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_STR_CAST_HPP_
#define XIMOL_STR_CAST_HPP_

#include <namespace_defs.hpp>
#include <config.hpp>
#include <typedefs.hpp>


XIMOL_BEGIN_NAMESPACE

template < typename Char_dest, typename Char_source > struct converter
{
    static Char_dest get(Char_source);
    static ::std::basic_string<Char_dest> get(const ::std::basic_string<Char_source> & wstr);
};

template <> struct XIMOL_DECL converter<char, wchar_t>
{
    static char get(wchar_t);
    static ::std::string get(const ::std::wstring & wstr);
};

template <> struct XIMOL_DECL converter<char, char>
{
    static char get(char);
    static ::std::string get(const ::std::string & str);
};

template <> struct XIMOL_DECL converter<wchar_t, char>
{
    static wchar_t get(char);
    static ::std::wstring get(const ::std::string & str);
};

template <> struct XIMOL_DECL converter<wchar_t, wchar_t>
{
    static wchar_t get(wchar_t);
    static ::std::wstring get(const ::std::wstring & wstr);
};

// full generic: undefined
template<typename T> struct str {};

// specialized for string
template<> struct str< ::std::string >
{
	template<typename T>
	static ::std::string cast(const T& t)
	{
		::std::ostringstream ss;
		ss << t;
		return ss.str();
	};

	static ::std::string cast(const ::std::string & t)		{ return converter<char,char>::get(t); };
	static ::std::string cast(const ::std::wstring & t)		{ return converter<char,wchar_t>::get(t); };

	static ::std::string cast(const char * t)				{ return converter<char,char>::get(t); };
	static ::std::string cast(const wchar_t * t)			{ return converter<char,wchar_t>::get(t); };

	static ::std::string cast(char t)						{ return ::std::string(1,converter<char,char>::get(t)); };
	static ::std::string cast(wchar_t t)					{ return ::std::string(1,converter<char,wchar_t>::get(t)); };
};

// specialized for const string
template<> struct str< ::std::string const>: public str< ::std::string> {};
template<> struct str<char const *>: public str< ::std::string> {};
template<> struct str<char const []>: public str< ::std::string> {};

template<> struct str< ::std::wstring>
{
	template<typename T>
	static ::std::wstring cast(const T& t)
	{
		::std::ostringstream ss;
		ss << t;
		return converter<wchar_t, char>::get(ss.str());
	};

	static ::std::wstring cast(const ::std::string & t)		{ return converter<wchar_t,char>::get(t); };
	static ::std::wstring cast(const ::std::wstring & t)	{ return converter<wchar_t,wchar_t>::get(t); };

	static ::std::wstring cast(const char * t)				{ return converter<wchar_t,char>::get(t); };
	static ::std::wstring cast(const wchar_t * t)			{ return converter<wchar_t,wchar_t>::get(t); };

	static ::std::wstring cast(char t)						{ return ::std::wstring(1,converter<wchar_t,char>::get(t)); };
	static ::std::wstring cast(wchar_t t)					{ return ::std::wstring(1,converter<wchar_t,wchar_t>::get(t)); };
};

// specialized for const wstring
template<> struct str< ::std::wstring const>: public str< ::std::wstring> {};
template<> struct str<wchar_t const *>: public str< ::std::wstring> {};
template<> struct str<wchar_t const []>: public str< ::std::wstring> {};

XIMOL_END_NAMESPACE

#endif // #ifndef XIMOL_STR_CAST_HPP_
