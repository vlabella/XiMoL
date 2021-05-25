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
	\brief xml_decl implementation.
	
	\author Tournois Florent
	\version 1.0

    $Id: content.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: content.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.4  2004/08/05 16:49:44  tournois
    no message

    Revision 1.3  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.2  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.1  2004/01/09 18:26:29  tournois
    Add box and content manipulator.

    Revision 1.1  2004/01/06 21:04:10  tournois
    no message


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <xml/content.hpp>
#include <xml/context.hpp>
#include <stream.hpp>
#include <error.hpp>
#include <translation.hpp>
#include <str_cast.hpp>
#include <parser/utils.hpp>
#include <parser/def_signs.hpp>

XIMOL_XML_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
manipulator_char_data_content::manipulator_char_data_content(xstring const & xstr)
  :content_(xstr)
{}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
manipulator_char_data_content::manipulator_char_data_content(const manipulator_char_data_content& x)
  :content_(x.xstr())
{}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
manipulator_char_data_content& manipulator_char_data_content::operator=(const manipulator_char_data_content& x)
{
	if (this==&x) return *this;
	content_.str(x.xstr());
	return *this;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
manipulator_char_data_content& manipulator_char_data_content::operator=(xstring const & xstr)
{
	content_.str(xstr);
	return *this;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
::std::basic_istringstream<xchar_t>& manipulator_char_data_content::istr()
{
	return content_;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring manipulator_char_data_content::xstr() const
{
	return content_.str();
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void manipulator_char_data_content::xstr(xstring const & xstr)
{
	content_.str(xstr);
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
::std::string manipulator_char_data_content::str() const
{
    return XIMOL_NAMESPACE_PATH::str< ::std::string>::cast(content_.str());
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void manipulator_char_data_content::str(const ::std::string & str)
{
	content_.str( XIMOL_NAMESPACE_PATH::str< ::std::wstring>::cast(str));
}

//-----------------------------------------------------------------------------
// content manipulator
//-----------------------------------------------------------------------------
manipulator_char_data_content char_data_content(xistream& xis)
{
	XIMOL_PARSER_USING_NAMESPACE;

	xstring result;

    if (xis.context.is_open_stag()) 
        return result; //there is an open_stag before.

	xstring temp;
	xchar_t xc;

	bool end_loop=false;
	while ( (!end_loop) && (xis.get(xc)) )
	{
		switch (xc)
		{
		case XCHAR_AMPERSAND:
			read_reference(xis, temp, 1);
			result += temp;
			break;
		case XCHAR_LESS_THAN_SIGN:
			xis.get(xc);
			switch (xc) 
			{
				case XCHAR_EXCLAMATION_MARK: // comment
					xis.get(xc);
					switch (xc)
					{
					case XCHAR_HYPHEN_MINUS: 
						read_comment(xis, temp, 3);
						break;
					case XCHAR_LEFT_SQUARE_BRACKET:
						read_cd_sect(xis, temp, 3);
						result += temp;
						break;
					default:
						XIMOL_THROW << _xtr(L"Waiting for '-' or '['") << XIMOL_AS_ERROR;
					}
					break;
				case XCHAR_QUESTION_MARK: // PI
					read_pi(xis,2);
					break;
				default: // element
					xis.putback(xc);
					xis.putback(XCHAR_LESS_THAN_SIGN);
					end_loop=true;
					break;
			}
			break;
		default:
			result+=xc;
		}
	}
	return result;
}

XIMOL_XML_END_NAMESPACE
