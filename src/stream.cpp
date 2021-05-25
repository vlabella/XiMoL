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
	\brief XML streams implementations.
	
	\author Tournois Florent
	\version 1.0

    $Id: stream.cpp,v 1.3 2009/12/30 22:12:04 vlabella Exp $
    $Log: stream.cpp,v $
    Revision 1.3  2009/12/30 22:12:04  vlabella
    commit in makefile
    Committed on the Free edition of March Hare Software CVSNT Server.
    Upgrade to CVS Suite for more features and support:
    http://march-hare.com/cvsnt/

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 16:15:12  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.11  2004/08/05 16:49:42  tournois
    no message

    Revision 1.10  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.9  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.8  2003/11/18 18:54:51  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.7  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.6  2003/10/25 18:17:38  hfp
    *** empty log message ***

    Revision 1.5  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.4  2003/10/09 16:59:45  tournois
    add the stringstream initialisation.
    add some prolog test.
    Correct code for VC6.0.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <stream.hpp>
#include <encoders/encoders.hpp>
#include <str_cast.hpp>
#include <datatypes/blob.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <sstream.hpp>



XIMOL_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// Change encoding.
//-----------------------------------------------------------------------------
xostream& use_XML(xostream& xos, const ::std::string& encoding_name)
{
	xos.encoding(encoding_name.c_str());
	return xos;
}

//-----------------------------------------------------------------------------
// Change encoding.
//-----------------------------------------------------------------------------
xistream& use_XML(xistream& xis, const ::std::string& encoding_name)
{
	xis.encoding(encoding_name.c_str());
	return xis;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xiostream::xiostream(const char* encoding_name)
	: xistream(encoding_name)
	, xostream(encoding_name)
{
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xostream::xostream(const char* encoding_name)
	:std::basic_ostream<xchar_t>(0),file_number(0)
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	prepare_ios(*this, encoding_name);

	encoding(encoding_name);

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xostream& xostream::operator<<(xchar_t c)
{
	rdbuf()->sputc((xchar_t)(c));
	return *this;
}

xostream& xostream::operator<<(char c)
{
	rdbuf()->sputc((xchar_t)((unsigned char)c));
	return *this;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xistream::xistream(const char* encoding_name)
	: std::basic_istream<xchar_t>(0)
	, buffer_()
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	prepare_ios(*this, encoding_name);
	encoding(encoding_name);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xistream& xistream::operator>>(xchar_t& c)
{
	//((::std::basic_istream<xchar_t>&)xis)>>c;
	if (! get(c))
		setstate(std::ios::failbit | std::ios::eofbit); // with this line we could acces the xstream buffer for more than one putback.
	return *this;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xistream& xistream::operator>>(char& c)
{
	xchar_t xc(0);
	*this >> xc;
	c=(char)(xc);
	return *this;
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
bool xistream::get(xchar_t & xc)
{
	if (buffer_.empty()) 
	{
		if (rdbuf()->sgetn(&xc, 1) != 1) return false;
	} else {
		xc = buffer_.front();
		pop_front();
	}
	return true;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
xchar_t xistream::front() const
{
	if (buffer_.empty()) 
	{
		xchar_t xc; 
		if (rdbuf()->sgetn(&xc, 1) == 1) rdbuf()->sputbackc(xc);
		return xc;
	}
	return buffer_.front();
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xistream::pop_front()
{
	if (buffer_.empty()) 
	{
		xchar_t xc; 
		rdbuf()->sgetn(&xc, 1);
	} else {
		buffer_.pop_front();
	}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xistream::putback(xchar_t xc)
{
	buffer_.push_front(xc);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xistream::putback(xstring const & xstr)
{
	if (xstr.empty()) return;
	xstring::const_reverse_iterator i(xstr.rbegin()), i_end(xstr.rend());
	for(;i!=i_end;++i) putback(*i);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::string xostream::encoding() const
{
	return str< ::std::string>::cast(context.get_encoding_decl());
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xostream::encoding(const char* encoding_name)
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	deep_change(*this, encoding_name);

	context.set_encoding_decl(str< ::std::wstring>::cast(encoding_name));

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
::std::string xistream::encoding() const
{
	return str< ::std::string>::cast(context.get_encoding_decl());
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void xistream::encoding(const char* encoding_name)
{
	XIMOL_ENCODERS_USING_NAMESPACE;

	deep_change(*this, encoding_name);
	context.set_encoding_decl(str< ::std::wstring>::cast(encoding_name));
}

//-----------------------------------------------------------------------------
// Test the flag to eat all white space.
//-----------------------------------------------------------------------------
bool has_skip_whitespace(xistream& xis)
{
    return xis.flags() & std::ios_base::skipws ;
};

// BLOB functions added by VL

const ximol::datatypes::_BLOB xistream::get_blob(const std::string &filename)
{
	ximol::datatypes::_citBLOBs citb = BLOBs.find(filename);
	if(citb != BLOBs.end()){
		return citb->second;
	}
	return ximol::datatypes::_BLOB(); // empty blob
}

void xistream::set_blobs(const ximol::datatypes::_BLOBs &b)
{
	BLOBs = b;
}

xstring xostream::add_blob(const ximol::datatypes::_BLOB &b,const std::string &ext)
{
	std::stringstream ss;
	//
	ss << std::setw(8) << std::setfill('0') << file_number++;
	ss << "." << ext;
	BLOBs[ss.str()] = b;
	xstringstream xss;
	xss << ss.str().c_str();
	return xss.str();
}

const ximol::datatypes::_BLOBs& xostream::get_blobs()
{
	return BLOBs;
}


XIMOL_END_NAMESPACE
