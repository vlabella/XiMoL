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
	\brief white_sapce facet implementation.

    \author Tournois Florent
	\version 1.0

    $Id: white_space.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: white_space.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 03:09:53  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.5  2004/08/05 16:49:44  tournois
    no message

    Revision 1.4  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.3  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.2  2004/02/05 09:08:33  tournois
    no message

    Revision 1.1  2004/01/18 16:42:55  tournois
    Add the white_space facet.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <xml/content.hpp>
#include <xml/open_stag.hpp>
#include <facet/white_space.hpp>
#include <parser/utils.hpp>
#include <parser/def_signs.hpp>

XIMOL_FACET_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// return the value
//-----------------------------------------------------------------------------
xstring preserve::value()
{
    return L"preserve";
};

//-----------------------------------------------------------------------------
// format the string
//-----------------------------------------------------------------------------
xstring preserve::format(xstring const & xstr)
{
    return xstr;
};

//-----------------------------------------------------------------------------
// test the string format
//-----------------------------------------------------------------------------
bool preserve::check(xstring const & xstr)
{
    return true;
};

//-----------------------------------------------------------------------------
// return the value
//-----------------------------------------------------------------------------
xstring replace::value()
{
    return L"replace";
};

//-----------------------------------------------------------------------------
// format the string
//-----------------------------------------------------------------------------
xstring replace::format(xstring const & xstr)
{
    XIMOL_PARSER_USING_NAMESPACE;

    xstring::const_iterator i(xstr.begin()), i_end(xstr.end());
    xstring result;
    for(;i!=i_end;++i)
        result+=(is_space(*i))?((xchar_t)0x0020):(*i);
    return result;
};

//-----------------------------------------------------------------------------
// test the string format
//-----------------------------------------------------------------------------
bool replace::check(xstring const & xstr)
{
    xstring::const_iterator i(xstr.begin()), i_end(xstr.end());
    for(;i!=i_end;++i)
        if ( (*i == (xchar_t)0x0009) ||
            (*i == (xchar_t)0x000A) ||
            (*i == (xchar_t)0x000D) )
            return false;
    return true;
};

//-----------------------------------------------------------------------------
// return the value
//-----------------------------------------------------------------------------
xstring collapse::value()
{
    return L"collapse";
};

//-----------------------------------------------------------------------------
// format the string
//-----------------------------------------------------------------------------
xstring collapse::format(xstring const & xstr)
{
    XIMOL_PARSER_USING_NAMESPACE;

    xstring::const_iterator i(xstr.begin()), i_end(xstr.end());
    xstring result;
    while ((i!=i_end) && (is_space(*i))) ++i;
    bool add_space=false;
    for(;i!=i_end;++i)
        if (is_space(*i))
        {
            add_space=true;
        } else {
            if (add_space)
            {
                result+=XCHAR_SPACE;
                add_space=false;
            };
            result+=*i;
        };
        return result;
};

//-----------------------------------------------------------------------------
// test the string format
//-----------------------------------------------------------------------------
bool collapse::check(xstring const & xstr)
{
    XIMOL_PARSER_USING_NAMESPACE;
    if (xstr.empty()) return true;

    xstring::const_iterator i(xstr.begin()), i_end(xstr.end());
    if (is_space(*i)) return false;
    if (is_space(*xstr.rbegin())) return false;

    bool lastchar_is_space=false;
    for(;i!=i_end;++i)
        if (is_space(*i))
        {   
            if (lastchar_is_space) return false;
            if ( (*i == (xchar_t)0x0009) ||
                (*i == (xchar_t)0x000A) ||
                (*i == (xchar_t)0x000D) )
                return false;
            lastchar_is_space=true;
        } else {
            lastchar_is_space=false;
        };

        return true;
};

XIMOL_FACET_END_NAMESPACE
