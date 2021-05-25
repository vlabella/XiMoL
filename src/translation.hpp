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
	\brief translation function for the library.
	
	\warning This file must be include only in cpp file.
  
	\author Tournois Florent
	\version 1.0

    $Id: translation.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: translation.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.15  2004/05/27 20:24:01  tournois
    no message

    Revision 1.14  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

    Revision 1.13  2004/02/25 15:57:06  tournois
    no message

    Revision 1.12  2004/02/22 10:27:33  tournois
    Add some doc.

    Revision 1.11  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.10  2004/02/19 18:59:27  tournois
    attribute doc

    Revision 1.9  2003/12/03 12:59:34  hfp
    include dependencies and type forwarding

    Revision 1.8  2003/11/18 18:54:51  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.7  2003/11/17 22:06:01  tournois
    Add traits for relation stream--object.
    Change cast.

    Revision 1.6  2003/11/16 18:15:54  tournois
    Write operator>> et operator<< for (wostream and char,string) and (ostream and wchar_t, wstring).

    Revision 1.5  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.4  2003/11/16 11:03:23  tournois
    no message

    Revision 1.3  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.2  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_TRANSLATION_HPP_
#define XIMOL_TRANSLATION_HPP_

#include <namespace_defs.hpp>
#include <config.hpp>
#include <str_cast.hpp>
#include <string>
#include <list>


XIMOL_BEGIN_NAMESPACE

//------------------------------------------------------------------------------
/** base function for the translation.
 *  @param x: the input string in english.
 *  @return the output string in other langage.
 */
//------------------------------------------------------------------------------
XIMOL_DECL
const wchar_t * translate(const wchar_t * x);

//------------------------------------------------------------------------------
/** Translate the base string and place arguments.
 *  @param x: the input string in english.
 *  @param args: arguments serialized in wstring.
 *  @return the output string in other langage.
 */
//------------------------------------------------------------------------------
XIMOL_DECL
std::wstring translate(const std::wstring & x, const std::list<std::wstring> & args);

//------------------------------------------------------------------------------
/// Function for the translation with 0 argument.
//------------------------------------------------------------------------------
XIMOL_DECL
std::wstring _xtr(const std::wstring& x);

//------------------------------------------------------------------------------
/** Function for the translation with 1 argument.
 *  %o to print an object.
 *  %% to print %
 */
//------------------------------------------------------------------------------
template < typename T1>
std::wstring _xtr(const std::wstring& x_start, const T1& t1)
{
    std::list<std::wstring> args;
    args.push_back(str< ::std::wstring>::cast(t1));
    return translate(x_start,args);
};

//------------------------------------------------------------------------------
/** Function for the translation with 2 arguments.
 *  %o to print an object.
 *  %% to print %
 */
//------------------------------------------------------------------------------
template < typename T1, typename T2>
std::wstring _xtr(const std::wstring& x_start, const T1& t1, const T2& t2)
{
    std::list<std::wstring> args;
    args.push_back(str< ::std::wstring>::cast(t1));
    args.push_back(str< ::std::wstring>::cast(t2));
    return translate(x_start,args);
};

//------------------------------------------------------------------------------
/** Function for the translation with 3 arguments.
 *  %o to print an object.
 *  %% to print %
 */
//------------------------------------------------------------------------------
template < typename T1, typename T2, typename T3>
std::wstring _xtr(const std::wstring& x_start, const T1& t1, const T2& t2, const T3& t3)
{
    std::list<std::wstring> args;
    args.push_back(str< ::std::wstring>::cast(t1));
    args.push_back(str< ::std::wstring>::cast(t2));
    args.push_back(str< ::std::wstring>::cast(t3));
    return translate(x_start,args);
};

//------------------------------------------------------------------------------
/** Function for the translation with 4 arguments.
 *  %o to print an object.
 *  %% to print %
 */
//------------------------------------------------------------------------------
template < typename T1, typename T2, typename T3, typename T4>
std::wstring _xtr(const std::wstring& x_start, const T1& t1, const T2& t2, const T3& t3, const T4& t4)
{
    std::list<std::wstring> args;
    args.push_back(str< ::std::wstring>::cast(t1));
    args.push_back(str< ::std::wstring>::cast(t2));
    args.push_back(str< ::std::wstring>::cast(t3));
    args.push_back(str< ::std::wstring>::cast(t4));
    return translate(x_start,args);
};

XIMOL_END_NAMESPACE

#endif // #ifndef XIMOL_TRANSLATION_HPP_
