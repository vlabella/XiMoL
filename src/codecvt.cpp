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

    $Id: codecvt.cpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: codecvt.cpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.6  2004/02/25 18:58:39  tournois
    imporve the gcc compatibility.

    Revision 1.5  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.4  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.3  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.2  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.1  2003/10/25 18:20:32  hfp
    XiMoL now provides a own codecvt (interface) based on standard.
    Hides use of iconv-library as implementation detail.

    Revision 1.6  2003/10/25 13:53:39  hfp
    review and separation

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <codecvt.hpp>
#include <encoders/error.hpp>
#include <translation.hpp>
#include <macros.hpp>

#include <encoders/libiconv/iconv.h>


XIMOL_BEGIN_NAMESPACE
///////////////////////////////////////////////////////////////////////////////
// nested types (private)
///////////////////////////////////////////////////////////////////////////////

struct codecvt_state { // not exported
	iconv_t conv_in_out;
	iconv_t conv_out_in;
};


///////////////////////////////////////////////////////////////////////////////
// constructor(s) & destructor
///////////////////////////////////////////////////////////////////////////////

codecvt::codecvt(const ::std::string& encoding_name, size_t refs)
	: ::std::codecvt<xchar_t, char, mbstate_t>(refs)
	, p_internal_state_(NULL) // exception safety
{
	p_internal_state_ = new codecvt_state; // should be created before create_encoding

	create_encoding(encoding_name);
}

///////////////////////////////////////////////////////////////////////////////

codecvt::~codecvt()
{
	delete_encoding();

	delete p_internal_state_; // should be delete after delete_encoding
}


///////////////////////////////////////////////////////////////////////////////
// methods (public)
///////////////////////////////////////////////////////////////////////////////

void codecvt::create_encoding(const ::std::string& encoding_name)
{
	::std::string const strIntern(sizeof(xchar_t) == 2
		? "UCS-2-INTERNAL"
		: "UCS-4-INTERNAL");

	p_internal_state_->conv_in_out = iconv_open(encoding_name.c_str(), strIntern.c_str());
	if (p_internal_state_->conv_in_out == (iconv_t)-1) 
        XIMOL_ENCODERS_THROW
		    << _xtr(L"Encoding '%o' not found. ", encoding_name)
		    << XIMOL_ENCODERS_AS_ERROR;

	p_internal_state_->conv_out_in = iconv_open(strIntern.c_str(), encoding_name.c_str());
	if (p_internal_state_->conv_out_in == (iconv_t)-1) XIMOL_ENCODERS_THROW
		<< _xtr(L"Encoding '%o' not found. ", encoding_name)
		<< XIMOL_ENCODERS_AS_ERROR;
}

///////////////////////////////////////////////////////////////////////////////

void codecvt::delete_encoding()
{
	iconv_close(p_internal_state_->conv_in_out);
	iconv_close(p_internal_state_->conv_out_in);
}

///////////////////////////////////////////////////////////////////////////////

codecvt::result codecvt::do_out(state_type& state,
								const intern_type* from,
								const intern_type* from_end,
								const intern_type*& from_next,
								extern_type* to,
								extern_type* to_limit,
								extern_type*& to_next) const
{
	to_next=to;
	from_next=from;
	size_t inbuf=from_end-from_next;
	inbuf*=sizeof(intern_type);
	size_t outbuf=to_limit-to_next;
	outbuf*=sizeof(extern_type);
	
	size_t init_inbuf=inbuf, init_outbuf=outbuf;

	typedef const char** from_next_type;

	size_t result = iconv(p_internal_state_->conv_in_out,(from_next_type)(&from_next),&inbuf,(char**)(&to_next),&outbuf);
	
	if (  (inbuf==init_inbuf) 
		||(outbuf==init_outbuf))
	{
		from_next = from;
		to_next   = to;
		return partial;
	}

	if (result==(size_t)(-1)) 
	{
		from_next = from;
		to_next   = to;
		if (errno==EINVAL) return partial;
		if (errno==EILSEQ) return error;
		if (errno==E2BIG)  return partial;
		return error;
	}

	return ok;
}

///////////////////////////////////////////////////////////////////////////////
		                 
codecvt::result codecvt::do_in(state_type& state,
							   const extern_type* from,
							   const extern_type* from_end,
							   const extern_type*& from_next,
							   intern_type* to,
							   intern_type* to_limit,
							   intern_type*& to_next) const
{
	to_next=to;
	from_next=from;
	size_t inbuf=from_end-from_next;
	inbuf*=sizeof(extern_type);
	size_t outbuf=to_limit-to_next;
	outbuf*=sizeof(intern_type);

	size_t init_inbuf=inbuf, init_outbuf=outbuf;
	
	typedef const char** from_next_type;

	size_t result = iconv(p_internal_state_->conv_out_in,(from_next_type)(&from_next),&inbuf,(char**)(&to_next),&outbuf);
	
	if (  (inbuf==init_inbuf) 
		||(outbuf==init_outbuf))
	{
		from_next = from;
		to_next   = to;
		return partial;
	}

	if (result==(size_t)(-1)) 
	{
		from_next = from;
		to_next   = to;
		if (errno==EINVAL) return partial;
		if (errno==EILSEQ) return error;
		if (errno==E2BIG)  return partial;
		return error;
	}

	return ok;
}

///////////////////////////////////////////////////////////////////////////////
			         
codecvt::result codecvt::do_unshift(state_type& state,
									extern_type* to,
									extern_type* to_limit,
									extern_type*& to_next) const
{
	to_next = to;
	return noconv;
}
			         
///////////////////////////////////////////////////////////////////////////////

int codecvt::do_encoding() const throw()
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////

bool codecvt::do_always_noconv() const throw()
{
	return false;
}
  
///////////////////////////////////////////////////////////////////////////////

int codecvt::do_length(const state_type& state,
					   const extern_type* from,
					   const extern_type* end,
					   size_t max) const
{
	return (int)XIMOL_MIN((size_t) (end - from), max);
}

///////////////////////////////////////////////////////////////////////////////

int codecvt::do_max_length() const throw()
{
	return 6;
}

///////////////////////////////////////////////////////////////////////////////
XIMOL_END_NAMESPACE
