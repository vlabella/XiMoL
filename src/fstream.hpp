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

    $Id: fstream.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: fstream.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.5  2004/02/25 18:58:39  tournois
    imporve the gcc compatibility.

    Revision 1.4  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.3  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.2  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.1  2003/10/24 15:53:13  hfp
    separation of each public class into one file

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_FSTREAM_HPP_
#define XIMOL_FSTREAM_HPP_

#include <stream.hpp>

#include <fstream>


XIMOL_BEGIN_NAMESPACE


//=============================================================================
/// class xofstream 
//=============================================================================
class XIMOL_DECL xofstream
	: public xostream
{
public: // constructor(s) & destructor
	/// Default constructor - use open()-method to specify a file.
	xofstream();

	explicit xofstream(const char* name,
					   const char* encoding_name = XIMOL_DEFAULT_ENCODING,
                       std::ios_base::openmode mode = std::ios_base::out);

	xofstream(const char* name, std::ios_base::openmode mode,
			  const char* encoding_name = XIMOL_DEFAULT_ENCODING);

	~xofstream();

public: // methods
	::std::basic_filebuf<xchar_t>* rdbuf();

	bool is_open() const;

	void open(const char* filename, 
			  openmode mode = std::ios_base::out);

	void open(const std::string filename, 
			  openmode mode = std::ios_base::out){
		open(filename.c_str(),mode);
	};

	void close();

	inline xostream& operator<<(xchar_t c)	{ return xostream::operator<<(c); }
	inline xostream& operator<<(char c)		{ return xostream::operator<<(c); }

private: // data members
	::std::basic_filebuf<xchar_t> buf_;
};


//=============================================================================
/// class xifstream 
//=============================================================================
class XIMOL_DECL xifstream
	: public xistream
{
public: // constructor(s) & destructor
	xifstream();

	explicit xifstream(const char* name,
					   const char* encoding_name = XIMOL_DEFAULT_ENCODING,
					   std::ios_base::openmode mode = std::ios_base::in);

	xifstream(const char* name, std::ios_base::openmode mode,
			  const char* encoding_name = XIMOL_DEFAULT_ENCODING);

	~xifstream();

public: // methods
	::std::basic_filebuf<xchar_t>* rdbuf();

	bool is_open() const;

	void open(const char* filename, 
			  openmode mode = std::ios_base::in);

	void open(const std::string filename, 
			  openmode mode = std::ios_base::out){
		open(filename.c_str(),mode);
	};

	void close();

    inline xistream& operator>>(xchar_t& c)	{ return xistream::operator>>(c); }
	inline xistream& operator>>(char& c)	{ return xistream::operator>>(c); }

private: // data members
	::std::basic_filebuf<xchar_t> buf_;
};


//=============================================================================
/// class xfstream 
//=============================================================================
class XIMOL_DECL xfstream
	: public xiostream
{
public: // constructor(s) & destructor
	xfstream();

	explicit xfstream(const char* name,
					  const char* encoding_name = XIMOL_DEFAULT_ENCODING,
					  std::ios_base::openmode mode = std::ios_base::in | out);

	xfstream(const char* name, std::ios_base::openmode mode,
			 const char* encoding_name = XIMOL_DEFAULT_ENCODING);

	~xfstream();

public: // methods
	::std::basic_filebuf<xchar_t>* rdbuf();

	bool is_open() const;

	void open(const char* filename, 
			  openmode mode = std::ios_base::in | out);

	void open(const std::string filename, 
			  openmode mode = std::ios_base::out){
		open(filename.c_str(),mode);
	};


	void close();

	inline xostream& operator<<(xchar_t c)	{ return xostream::operator<<(c); }
	inline xostream& operator<<(char c)		{ return xostream::operator<<(c); }
	inline xistream& operator>>(xchar_t& c)	{ return xistream::operator>>(c); }
	inline xistream& operator>>(char& c)	{ return xistream::operator>>(c); }

private: // data members
	::std::basic_filebuf<xchar_t> buf_;
};


XIMOL_END_NAMESPACE 

#endif // #ifndef XIMOL_FSTREAM_HPP_
