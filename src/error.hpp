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
	\brief Define the main error class.
	@ingroup exceptions

	\author Tournois Florent
	\version 1.0

    $Id: error.hpp,v 1.3 2008/04/30 20:44:43 LABELLAHOME\administrator Exp $
    $Log: error.hpp,v $
    Revision 1.3  2008/04/30 20:44:43  LABELLAHOME\administrator
    commit in makefile

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.15  2004/03/04 18:45:29  tournois
    Compatibility with gcc.

    Revision 1.14  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

    Revision 1.13  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.12  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.11  2004/01/29 20:52:35  tournois
    doc and tutorial.

    Revision 1.10  2004/01/27 21:49:51  tournois
    Add docs and tutorial.

    Revision 1.9  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.8  2003/11/16 11:03:23  tournois
    no message

    Revision 1.7  2003/11/15 19:06:39  tournois
    no message

    Revision 1.6  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.5  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.4  2003/10/08 10:20:06  hfp
    Enum openmode is already qualified by class-scope (implicit).

    Revision 1.3  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef _XIMOL_ERROR_H_
#define _XIMOL_ERROR_H_

#include <namespace_defs.hpp>
#include <config.hpp>
#include <typedefs.hpp>
#include <exception>
#include <sstream>

//-----------------------------------------------------------------------------
/** Macro to throw the error.
  * @ingroup exceptions
  * This macro create the exception, and you could put to
  *	some additional information.
  *	
  *	 \code
  *	 XIMOL_THROW << L"error description" 
  *	             << XIMOL_AS_ERROR;
  *	 \endcode
  *
  *	@see error
  *	@see XIMOL_AS_ERROR 
  */
//-----------------------------------------------------------------------------
#define XIMOL_THROW { XIMOL_NAMESPACE_PATH::error err; err 

//-----------------------------------------------------------------------------
/** Macro to precise the location.
  * @ingroup exceptions
  * This macro return a string with the position in the code.
  *
  */
//-----------------------------------------------------------------------------
#define XIMOL_HERE (::std::ostringstream()<<"(file "<<__FILE__<<",line "<<__LINE__<<")").str() 

//-----------------------------------------------------------------------------
/** Macro to throw the error.
  * @ingroup exceptions
  *  This macro throw effectively the exception.
  *
  *	 \code
  *	 XIMOL_THROW << L"error description" 
  *	             << XIMOL_AS_ERROR;
  *	 \endcode
  *
  *	 @see error
  *	 @see XIMOL_AS_ERROR 
  */
//-----------------------------------------------------------------------------
// this cuases vs 2008 to bug when compiling  cant throw the err stream???
//#define XIMOL_AS_ERROR  ""; throw err; };
#define XIMOL_AS_ERROR  ""; };

XIMOL_BEGIN_NAMESPACE

//=============================================================================
/** An implementation of a simple error.
 *  @ingroup exceptions
 *  this class is streamable and have two intersting function
 *  \code
 *	  const char* what() const throw();
 *    const ::std::wstring & message() const throw();
 *  \endcode
 */
//=============================================================================
class XIMOL_DECL error : public ::std::exception
{
public: // nested types
	typedef ::std::wostringstream stream_type;
	typedef ::std::wstring        string_type;
   
public: // constructor(s) & destructor

    ///@name constructor(s) & destructor
    //@{
	error();
	explicit error(const string_type& str);
	error(const error& err);
	~error() throw();
    //@}
	    
public: // methods
	/// The most important function (return the error message).
	const char* what() const throw();

    /// Get the error message.
    const string_type & message() const throw();

	// The template function used to create insertion operators for all
    // of the various types of objects one might insert into this guy.
    //
    template<typename T>
    error& operator<<( const T& t )
    {
        m_stream <<t;
        return *this;
     }


private:
	// vlabella - moved from inherintg strintream to continaing it
	// this is to comply with C++ standardization and the fact that there 
	// is no copy contructors for stringstream objects...
	mutable ::std::wostringstream m_stream;
    mutable ::std::string buffer_;
    mutable string_type wbuffer_;
}; // end of the class error

XIMOL_END_NAMESPACE

#endif // #ifndef _XIMOL_ERROR_H_
