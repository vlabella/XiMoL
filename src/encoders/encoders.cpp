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
	\brief Facet access (implementation).

	\author Tournois Florent
	\version 1.0

    $Id: encoders.cpp,v 1.4 2008/05/12 18:53:46 LABELLAHOME\administrator Exp $
    $Log: encoders.cpp,v $
    Revision 1.4  2008/05/12 18:53:46  LABELLAHOME\administrator
    commit in makefile

    Revision 1.3  2005/05/13 02:08:35  vlabella
    commit in makefile

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.12  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.11  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.10  2003/11/18 18:54:51  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.9  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.8  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.7  2003/10/25 18:17:38  hfp
    *** empty log message ***

    Revision 1.6  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.5  2003/10/13 21:01:20  tournois
    no message

    Revision 1.4  2003/10/09 16:59:45  tournois
    add the stringstream initialisation.
    add some prolog test.
    Correct code for VC6.0.

    Revision 1.3  2003/10/03 17:29:41  tournois
    no message

    Revision 1.2  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <encoders/encoders.hpp>
#include <encoders/error.hpp>
#include <translation.hpp>
#include <codecvt.hpp>


XIMOL_ENCODERS_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// Interface for the ximol_encoders.
//-----------------------------------------------------------------------------
::std::codecvt<xchar_t, char, mbstate_t>* get_ximol_facet(::std::string const& encoding_name)
{
	return new XIMOL_NAMESPACE_PATH::codecvt(encoding_name);
}

//-----------------------------------------------------------------------------
// place with new placement.
//-----------------------------------------------------------------------------
void place_ximol_facet(::std::codecvt<xchar_t, char, mbstate_t>* placement, ::std::string const & encoding_name)
{
	::new (placement) XIMOL_NAMESPACE_PATH::codecvt(encoding_name);
}

//-----------------------------------------------------------------------------
// Change encoding on a unique facet.
//-----------------------------------------------------------------------------
void change_ximol_facet_encoding(::std::codecvt<xchar_t, char, mbstate_t>* facet, ::std::string const & encoding_name)
{
    if (facet==NULL) return;

	XIMOL_NAMESPACE_PATH::codecvt* the_facet=dynamic_cast<XIMOL_NAMESPACE_PATH::codecvt*>(facet);

//	XIMOL_NAMESPACE_PATH::codecvt* the_facet=static_cast<XIMOL_NAMESPACE_PATH::codecvt*>(facet);

	if (the_facet==NULL) 
		XIMOL_ENCODERS_THROW << _xtr(L"XiMoL Encoder facet problem. ") 
                             << _xtr(L"We can not retrive the XiMoL facet pointer. ")
                             << _xtr(L"And then, the encoding can not be changed to '%o'. ", encoding_name )
		                     << XIMOL_ENCODERS_AS_ERROR;


	the_facet->delete_encoding();

	the_facet->create_encoding(encoding_name);

}

//-----------------------------------------------------------------------------
// change the encoding.
//-----------------------------------------------------------------------------
void deep_change(::std::basic_ios<xchar_t>& ios, ::std::string const & encoding_name)
{
	typedef ::std::codecvt<xchar_t,char,mbstate_t> FacetType;
	const FacetType* pfacet=&(XIMOL_USE_FACET(ios.getloc(),FacetType));
    // Warning there is a const cast.
	FacetType* the_facet=const_cast<FacetType*>(pfacet);
	change_ximol_facet_encoding(the_facet,encoding_name);
}

//-----------------------------------------------------------------------------
// prepare ios.
//-----------------------------------------------------------------------------
void prepare_ios(::std::basic_ios<xchar_t>& ios, ::std::string const & encoding_name)
{
    ios.imbue(XIMOL_ADD_FACET(ios.getloc(), get_ximol_facet(encoding_name)));
}

//-----------------------------------------------------------------------------
// test ios.
//-----------------------------------------------------------------------------
bool test_ios(::std::basic_ios<xchar_t> & ios)
{
	typedef ::std::codecvt<xchar_t,char,mbstate_t> FacetType;

	const FacetType* pfacet=&(XIMOL_USE_FACET(ios.getloc(),FacetType));
	return NULL != dynamic_cast<const XIMOL_NAMESPACE_PATH::codecvt*>(pfacet);
}

XIMOL_ENCODERS_END_NAMESPACE
