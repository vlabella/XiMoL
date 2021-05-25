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
	\brief GetFrom and PutTo operator for common char and xchar_t.

    \author Tournois Florent
	\version 1.0

    $Id: io.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: io.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.12  2004/08/05 16:49:42  tournois
    no message

    Revision 1.11  2004/05/26 07:48:03  tournois
    no message

    Revision 1.10  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.9  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.8  2004/02/02 19:51:44  tournois
    Add a control_flow and finish the attribute tutorial.

    Revision 1.7  2004/01/27 21:49:51  tournois
    Add docs and tutorial.

    Revision 1.6  2003/11/27 15:31:55  hfp
    partially adapted to vc6.

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
#ifndef XIMOL_IO_HPP_
#define XIMOL_IO_HPP_

#include <config.hpp>
#include <typedefs.hpp>
#include <macros.hpp>


// forwarded declarations
XIMOL_BEGIN_NAMESPACE
	class xostream;
	class xistream;
XIMOL_END_NAMESPACE

namespace std {
    XIMOL_DECL ostream& operator<<(ostream & os, const wchar_t * xc);
//  XIMOL_DECL ostream& operator<<(ostream & os, const wchar_t xc);
//	XIMOL_DECL ostream& operator<<(ostream & os, const wstring & wstr);

    XIMOL_DECL wostream& operator<<(wostream & wos, const char * c);
//  XIMOL_DECL wostream& operator<<(wostream & wos, const char c);
//  XIMOL_DECL wostream& operator<<(wostream & wos, const string & str);

//    XIMOL_DECL istream& operator>>(istream & is, wchar_t & xc);
//  XIMOL_DECL istream& operator>>(istream & is, wstring & wstr);

//    XIMOL_DECL wistream& operator>>(wistream & wis, char & c);
//  XIMOL_DECL wistream& operator>>(wistream & wis, string & str);
}; // end of namespace std

XIMOL_BEGIN_NAMESPACE // open the std namespace to put some classes

//-----------------------------------------------------------------------------
/// XML stream put to operator.
/** @ingroup encoders 
    redefinition of the put to operator
   
    @param xos : the XML ostream
    @param c : char to put
   
    @return xostream&  : the XML stream in return.
*/
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& operator<<(xostream& xos, const char c);

//-----------------------------------------------------------------------------
/// XML stream put to operator.
/** @ingroup encoders 
    redefinition of the put to operator
   
    @param xos : the XML ostream
    @param c : char * to put
   
    @return xostream&  : the XML stream in return.
*/
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& operator<<(xostream& xos, const char * c);

////-----------------------------------------------------------------------------
///// XML stream put to operator.
///** @ingroup encoders 
//    redefinition of the put to operator
//   
//    @param xos : the XML ostream
//    @param c : char * to put
//   
//    @return xostream&  : the XML stream in return.
//*/
////-----------------------------------------------------------------------------
//XIMOL_DECL
//xostream& operator<<(xostream& xostream_, const std::string& str_);

//-----------------------------------------------------------------------------
/// XML stream put to operator.
/** @ingroup encoders 
    redefinition of the put to operator
   
    @param xos : the XML ostream
    @param c : xchar_t to put
   
    @return xostream&  : the XML stream in return.
*/
//-----------------------------------------------------------------------------
//XIMOL_DECL
//xostream& operator<<(xostream& xos, xchar_t c);

//-----------------------------------------------------------------------------
/// XML stream put to operator.
/** @ingroup encoders 
    redefinition of the put to operator
   
    @param xos : the XML ostream
    @param c : xchar_t * to put
   
    @return xostream&  : the XML stream in return.
*/
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& operator<<(xostream& xos, const xchar_t * c);

////-----------------------------------------------------------------------------
///// XML stream put to operator.
///** @ingroup encoders 
//    redefinition of the put to operator
//   
//    @param xos : the XML ostream
//    @param c : xstring * to put
//   
//    @return xostream&  : the XML stream in return.
//*/
////-----------------------------------------------------------------------------
//XIMOL_TEMPLATE_NULL
//XIMOL_DECL
//xostream& operator<<(xostream& xos, xstring const & c);

//-----------------------------------------------------------------------------
/// XML stream get from operator.
/** @ingroup encoders 
    redefinition of the get from operator
   
    @param xis : the XML istream
    @param c : char to get
   
    @return xistream&  : the XML stream in return.
*/
//-----------------------------------------------------------------------------
//XIMOL_DECL
//xistream& operator>>(xistream& xis, char & c);

//-----------------------------------------------------------------------------
/// XML stream get from operator.
/** @ingroup encoders 
    redefinition of the get from operator
   
    @param xis : the XML istream
    @param c : xchar_t to get
   
    @return xistream&  : the XML stream in return.
*/
//-----------------------------------------------------------------------------
//XIMOL_DECL
//xistream& operator>>(xistream& xis, xchar_t & c);

XIMOL_DECL xistream& operator>>(xistream& xis, bool           & c);
XIMOL_DECL xistream& operator>>(xistream& xis, short          & c);
XIMOL_DECL xistream& operator>>(xistream& xis, long           & c);
XIMOL_DECL xistream& operator>>(xistream& xis, unsigned long  & c);
XIMOL_DECL xistream& operator>>(xistream& xis, int            & c);
XIMOL_DECL xistream& operator>>(xistream& xis, unsigned int   & c);
XIMOL_DECL xistream& operator>>(xistream& xis, float          & c);
XIMOL_DECL xistream& operator>>(xistream& xis, double         & c);
XIMOL_DECL xistream& operator>>(xistream& xis, long double    & c);
XIMOL_DECL xistream& operator>>(xistream& xis, ::std::wistream& (*fun)( ::std::wistream&));

XIMOL_DECL xostream& operator<<(xostream& xos, bool           c);
XIMOL_DECL xostream& operator<<(xostream& xos, short          c);
XIMOL_DECL xostream& operator<<(xostream& xos, long           c);
XIMOL_DECL xostream& operator<<(xostream& xos, unsigned long  c);
XIMOL_DECL xostream& operator<<(xostream& xos, int            c);
XIMOL_DECL xostream& operator<<(xostream& xos, unsigned int   c);
XIMOL_DECL xostream& operator<<(xostream& xos, float          c);
XIMOL_DECL xostream& operator<<(xostream& xos, double         c);
XIMOL_DECL xostream& operator<<(xostream& xos, long double    c);
XIMOL_DECL xostream& operator<<(xostream& xos, ::std::wostream& (*fun)( ::std::wostream&));

XIMOL_END_NAMESPACE 

#endif // #ifndef XIMOL_IO_HPP_
