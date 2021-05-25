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
	\brief Declare the error class and macros.
    Define an encoders::error derived from ximol::error. 

	@ingroup exceptions encoders

	\author Tournois Florent
	\version 1.0

    $Id: error.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: error.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.11  2004/03/04 18:45:29  tournois
    Compatibility with gcc.

    Revision 1.10  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.9  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.8  2004/01/25 17:32:17  tournois
    no message

    Revision 1.7  2004/01/18 11:40:58  tournois
    Add the pattern facet.

    Revision 1.6  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.5  2003/11/15 19:06:39  tournois
    no message

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
#ifndef XIMOL_ENCODERS_ERROR_HPP_
#define XIMOL_ENCODERS_ERROR_HPP_

#include <error.hpp>

//-----------------------------------------------------------------------------
/** Macro to throw the error.
 *  @ingroup exceptions
 *   This macro create the exception, and you could put to
 *	some additional information.
 *	\code
 *	XIMOL_ENCODERS_THROW << _(L"error description") 
 *	                     << XIMOL_ENCODERS_AS_ERROR;
 * 	\endcode
 *	
 *	@see error
 *	@see XIMOL_ENCODERS_AS_ERROR 
 */
//-----------------------------------------------------------------------------
#define XIMOL_ENCODERS_THROW { XIMOL_ENCODERS_NAMESPACE_PATH::error err; err  

//-----------------------------------------------------------------------------
/** Macro to throw the error.
 *  @ingroup exceptions
 *  This macro throw effectively the exception.
 *
 *	\code
 *	XIMOL_ENCODERS_THROW << _(L"error description") 
 *	                     << XIMOL_ENCODERS_AS_ERROR;
 * 	\endcode
 *
 *	@see error
 *	@see XIMOL_ENCODERS_AS_ERROR 
 */
//-----------------------------------------------------------------------------
#define XIMOL_ENCODERS_AS_ERROR  ""; throw err; };

XIMOL_ENCODERS_BEGIN_NAMESPACE

//=============================================================================
/// Implementation of the ximol encoder error.
/** @ingroup exceptions encoders
    To use this class, you must use the macros XIMOL_ENCODERS_THROW_ERROR,
	and XIMOL_ENCODERS_AS_ERROR. You could also use the translation function.

	\code
	XIMOL_ENCODERS_THROW << _(L"error description") 
	                     << XIMOL_ENCODERS_AS_ERROR;
	\endcode

  */
//=============================================================================
class XIMOL_DECL error 
	: public XIMOL_NAMESPACE_PATH::error
{
protected: // nested types
	typedef XIMOL_NAMESPACE_PATH::error base_type;

public: // constructor(s) & destructor
    ///@name constructor(s) & destructor
    //@{
	error();
	explicit error(const ::std::wstring& str);
	error(const error& err);
	~error() throw();
    //@}
      
}; // end of class error

XIMOL_ENCODERS_END_NAMESPACE

#endif // #ifndef XIMOL_ENCODERS_ERROR_HPP_
