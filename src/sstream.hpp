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
	\brief XML streams declarations.
	
	\author Tournois Florent
	\version 1.0

    $Id: sstream.hpp,v 1.3 2008/04/29 20:28:36 LABELLAHOME\administrator Exp $
    $Log: sstream.hpp,v $
    Revision 1.3  2008/04/29 20:28:36  LABELLAHOME\administrator
    commit in makefile

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.6  2004/02/25 18:58:39  tournois
    imporve the gcc compatibility.

    Revision 1.5  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.4  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.3  2003/11/17 22:06:01  tournois
    Add traits for relation stream--object.
    Change cast.

    Revision 1.2  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.1  2003/10/24 15:53:13  hfp
    separation of each public class into one file

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_SSTREAM_HPP_
#define XIMOL_SSTREAM_HPP_

#include <stream.hpp>

#include <sstream>

XIMOL_BEGIN_NAMESPACE



//=============================================================================
/// class xistringstream 
//=============================================================================
class XIMOL_DECL xistringstream
	: public xistream
{
public: // constructor(s) & destructor
	explicit xistringstream(std::ios_base::openmode mode = std::ios_base::in);

	explicit xistringstream(const ::std::basic_string<xchar_t>& str,
		                    std::ios_base::openmode mode = std::ios_base::in);

	~xistringstream();
	
public: // methods
	::std::basic_stringbuf<xchar_t>* rdbuf();
	::std::basic_string<xchar_t> str() const;
	void str(const ::std::basic_string<xchar_t>& s);
	
	inline xistream& operator>>(xchar_t& c)	{ return xistream::operator>>(c); }
	inline xistream& operator>>(char& c)	{ return xistream::operator>>(c); }

private: // data members
	::std::basic_stringbuf<xchar_t> buf_;
};

//=============================================================================
/// class xostringstream 
//=============================================================================
class XIMOL_DECL xostringstream
	: public xostream
{
public: // constructor(s) & destructor
	explicit xostringstream(std::ios_base::openmode mode = std::ios_base::out);

	explicit xostringstream(const ::std::basic_string<xchar_t>& str,
		                    std::ios_base::openmode mode = std::ios_base::out);

	~xostringstream();
	
public: // methods
	::std::basic_stringbuf<xchar_t>* rdbuf();
	::std::basic_string<xchar_t> str() const;
	void str(const ::std::basic_string<xchar_t>& s);
	
	inline xostream& operator<<(xchar_t c)	{ return xostream::operator<<(c); }
	inline xostream& operator<<(char c)		{ return xostream::operator<<(c); }

private: // data members
	::std::basic_stringbuf<xchar_t> buf_;
};


//=============================================================================
/// class xstringstream
//=============================================================================
class XIMOL_DECL xstringstream
	: public xiostream
{
public: // constructor(s) & destructor
	explicit xstringstream(std::ios_base::openmode mode = std::ios_base::in | out);

	explicit xstringstream(const ::std::basic_string<xchar_t>& str,
		                   std::ios_base::openmode mode = std::ios_base::in | out);

	~xstringstream();
	
public: // methods
	::std::basic_stringbuf<xchar_t>* rdbuf();
	::std::basic_string<xchar_t> str() const;
	void str(const ::std::basic_string<xchar_t>& s);
	
	inline xostream& operator<<(xchar_t c)	{ return xostream::operator<<(c); }
	inline xostream& operator<<(char c)		{ return xostream::operator<<(c); }
	inline xistream& operator>>(xchar_t& c)	{ return xistream::operator>>(c); }
	inline xistream& operator>>(char& c)	{ return xistream::operator>>(c); }

private: // data members
	::std::basic_stringbuf<xchar_t> buf_;
};


XIMOL_END_NAMESPACE 

#endif // #ifndef XIMOL_SSTREAM_HPP_
