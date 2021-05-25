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
/* \file 
	\brief translation implementations.
	
	\author Tournois Florent
	\version 1.0

    $Id: translation.cpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: translation.cpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.9  2004/02/25 18:58:39  tournois
    imporve the gcc compatibility.

    Revision 1.8  2004/02/25 15:57:06  tournois
    no message

    Revision 1.7  2004/02/22 10:27:33  tournois
    Add some doc.

    Revision 1.6  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.5  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.4  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.3  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.2  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <translation.hpp>

XIMOL_BEGIN_PRIVATE_NAMESPACE

//------------------------------------------------------------------------------
// translation initialisation
//------------------------------------------------------------------------------
void start_translation()
{
};

XIMOL_END_PRIVATE_NAMESPACE

XIMOL_BEGIN_NAMESPACE

//------------------------------------------------------------------------------
// Function for the translation
//------------------------------------------------------------------------------
const wchar_t * translate(const wchar_t * x)
{
    static bool init=true;
    if (init) {
        start_translation();
        init=false;
    }

    // nothing at this moment.
    return x;
}

//------------------------------------------------------------------------------
/// Function for the translation with 0 argument.
//------------------------------------------------------------------------------
std::wstring _xtr(const std::wstring& x)
{
    return translate(x.c_str());
};

//------------------------------------------------------------------------------
// Translate the base string and place arguments.
//------------------------------------------------------------------------------
std::wstring translate(const std::wstring & x, const std::list<std::wstring> & args)
{
    std::wstring x_translated(translate(x.c_str()));
    std::list<std::wstring>::const_iterator arg(args.begin()), arg_end(args.end());
    std::wstring::const_iterator pos(x_translated.begin()), pos_end(x_translated.end());
    std::wstring result;

    while (pos!=pos_end) 
    {
        if (*pos!='%') 
        {
            result+=*pos;
            ++pos;
        } else {
            ++pos;
            if ((pos!=pos_end)&&(*pos=='o'))
            {
                if (arg!=arg_end)
                {
                    result+=*arg;
                    ++arg;
                }
            } else {
                if (*pos!='%') --pos;
                result+=*pos;
            };
        };
    };
    return result;
}

XIMOL_END_NAMESPACE
