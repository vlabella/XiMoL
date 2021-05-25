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

    $Id: stream.hpp,v 1.6 2009/12/31 14:33:20 vlabella Exp $
    $Log: stream.hpp,v $
    Revision 1.6  2009/12/31 14:33:20  vlabella
    commit in makefile
    Committed on the Free edition of March Hare Software CVSNT Server.
    Upgrade to CVS Suite for more features and support:
    http://march-hare.com/cvsnt/

    Revision 1.5  2009/12/30 22:12:04  vlabella
    commit in makefile
    Committed on the Free edition of March Hare Software CVSNT Server.
    Upgrade to CVS Suite for more features and support:
    http://march-hare.com/cvsnt/

    Revision 1.4  2008/05/06 04:08:27  LABELLAHOME\kara
    commit in makefile

    Revision 1.3  2008/04/29 20:28:36  LABELLAHOME\administrator
    commit in makefile

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.3  2005/05/12 17:12:58  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 16:15:12  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.9  2004/08/05 16:49:42  tournois
    no message

    Revision 1.8  2004/02/22 10:27:33  tournois
    Add some doc.

    Revision 1.7  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.6  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.5  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.4  2003/10/09 16:59:45  tournois
    add the stringstream initialisation.
    add some prolog test.
    Correct code for VC6.0.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_STREAM_HPP_
#define XIMOL_STREAM_HPP_


#include <xml/context.hpp>
#include <macros.hpp>
#include <datatypes/blob.hpp>
#include <iostream>


XIMOL_BEGIN_NAMESPACE


//=============================================================================
/// class ostream with context.
//=============================================================================
class XIMOL_DECL xostream
	: public ::std::basic_ostream<xchar_t>
{
public: // constructor(s) & destructor
	/// Contruct and set the encoding.
	/** @see XIMOL_DEFAULT_ENCODING */
	xostream(const char* encoding_name = XIMOL_DEFAULT_ENCODING);

private: // restrict copy & assignment
	xostream(const xostream& x);
	xostream& operator=(const xostream&);

public: // methods
	::std::string encoding() const;
	void encoding(const char* encoding_name);

	xostream& operator<<(xchar_t c);
	xostream& operator<<(char c);

public: // data members
	XIMOL_XML_NAMESPACE_PATH::context context;

//
// -- blob interface
//
public: // methods
	xstring add_blob(const XIMOL_DATATYPES_NAMESPACE_PATH::_BLOB &b,const std::string &ext);
	const XIMOL_DATATYPES_NAMESPACE_PATH::_BLOBs& get_blobs();
protected:
	XIMOL_DATATYPES_NAMESPACE_PATH::_BLOBs BLOBs;
	size_t file_number;
};


//=============================================================================
/// class istream with context.
//=============================================================================
class XIMOL_DECL xistream
	: public ::std::basic_istream<xchar_t>
{
public: // constructor(s) & destructor
	xistream(const char* encoding_name = XIMOL_DEFAULT_ENCODING);

private: // restrict copy & assignment
	xistream(const xistream& x);
	xistream& operator=(const xistream&);

public: // methods
	::std::string encoding() const;
	void encoding(const char* encoding_name);

	bool get(xchar_t& xc);
	void putback(xchar_t xc);
	void putback(xstring const & xstr);
	xchar_t front() const;
	void pop_front();

	xistream& operator>>(xchar_t& c);
	xistream& operator>>(char& c);

public: // data members
	XIMOL_XML_NAMESPACE_PATH::context context;

private: // data members
	typedef class XIMOL_DECL ::std::list<xchar_t> buffer_type;
	buffer_type buffer_;

public:
	//
	// -- blob interface
	//
	const XIMOL_DATATYPES_NAMESPACE_PATH::_BLOB get_blob(const std::string &filename);
	void set_blobs(const XIMOL_DATATYPES_NAMESPACE_PATH::_BLOBs &b);

protected: // data members
	XIMOL_DATATYPES_NAMESPACE_PATH::_BLOBs BLOBs;	

};


//=============================================================================
/// class derived bfrom xistream and xostream.
//=============================================================================
class XIMOL_DECL xiostream
	: public xistream
	, public xostream
{
public: // constructor(s) & destructor
	xiostream(const char* encoding_name = XIMOL_DEFAULT_ENCODING);

public: // methods
	inline xostream& operator<<(xchar_t c)	{ return xostream::operator<<(c); }
	inline xostream& operator<<(char c)		{ return xostream::operator<<(c); }
	inline xistream& operator>>(xchar_t& c)	{ return xistream::operator>>(c); }
	inline xistream& operator>>(char& c)	{ return xistream::operator>>(c); }
};


//-----------------------------------------------------------------------------
/// Change encoding.
//-----------------------------------------------------------------------------
XIMOL_DECL xostream& use_XML(xostream& xos,
							   const ::std::string& encoding_name = XIMOL_DEFAULT_ENCODING);


//-----------------------------------------------------------------------------
/// Change encoding.
//-----------------------------------------------------------------------------
XIMOL_DECL xistream& use_XML(xistream& xis,
							   const ::std::string& encoding_name = XIMOL_DEFAULT_ENCODING);

//-----------------------------------------------------------------------------
/** Get the uri shortcut.
 *  @ingroup user
 *  With this function, you can retrieve the shortcut from an uri.
 *  @param xis the stream containing a context
 *  @param ns  the long version of the namespace
 *  @return the shortcut. If there is no shortcut, ns is returned.
 */
//-----------------------------------------------------------------------------
template < typename String >
xstring get_short_namespace(xistream& xis, String const & ns)
{
    return xis.context.get_short_namespace(str<xstring>::cast(ns));
};

//-----------------------------------------------------------------------------
/** Get the uri shortcut.
 *  @ingroup user
 *  With this function, you can retrieve the shortcut from an uri.
 *  @param xis the stream containing a context
 *  @param ns  the long version of the namespace
 *  @return the shortcut. If there is no shortcut, ns is returned.
 */
//-----------------------------------------------------------------------------
template < typename String >
xstring get_short_namespace(xostream& xos, String const & ns)
{
    return xos.context.get_short_namespace(str<xstring>::cast(ns));
};

//-----------------------------------------------------------------------------
/** Get the uri.
 *  @ingroup user
 *  With this function, you can retrieve the uri from a shortcut.
 *  @param xis the stream containing a context
 *  @param uri_shortcut  the uri shortcut
 *  @return the uri. if there is no uri, the shortcut is returned.
 */
//-----------------------------------------------------------------------------
template < typename String >
xstring get_namespace(xistream& xis, String const & uri_shortcut)
{
    return xis.context.get_namespace(str<xstring>::cast(uri_shortcut));
};

//-----------------------------------------------------------------------------
/** Get the uri.
 *  @ingroup user
 *  With this function, you can retrieve the uri from a shortcut.
 *  @param xis the stream containing a context
 *  @param uri_shortcut  the uri shortcut
 *  @return the uri. if there is no uri, the shortcut is returned.
 */
//-----------------------------------------------------------------------------
template < typename String >
xstring get_namespace(xostream& xos, String const & uri_shortcut)
{
    return xos.context.get_namespace(str<xstring>::cast(uri_shortcut));
};

//-----------------------------------------------------------------------------
/** Test if a shortcut exists.
 *  @ingroup user
 *  With this function, you can test a shortcut.
 *  @param xs the stream containing a context
 *  @param uri_shortcut  the uri shortcut
 *  @return true if the shortcut exist.
 */
//-----------------------------------------------------------------------------
template < typename X, typename String >
bool has_short_namespace(X& xs, String const & uri_shortcut)
{
    return get_namespace(xs,uri_shortcut)!=str<xstring>::cast(uri_shortcut);
};

//-----------------------------------------------------------------------------
/** Test if an uri exists.
 *  @ingroup user
 *  With this function, you can test a uri.
 *  @param xs the stream containing a context
 *  @param uri  the uri to test
 *  @return true if the uri exists.
 */
//-----------------------------------------------------------------------------
template < typename X, typename String >
bool has_namespace(X& xs, String const & uri)
{
    return get_short_namespace(xs,uri)!=str<xstring>::cast(uri);
};

//-----------------------------------------------------------------------------
/** find a short_cut if necessary.
 *  @ingroup user
 *  This function find a free shortcut for an uri if the shortcut does not exist.
 *  @param xs the stream containing a context
 *  @param uri  the uri to test
 *  @return the uri shortcut.
 */
//-----------------------------------------------------------------------------
template < typename X, typename String1, typename String2 >
xstring find_short_namespace(X& xs, String1 const & uri, String2 const & shortcut_proposition = String2())
{
    if (has_namespace(xs,uri))
        return get_short_namespace(xs,uri);
    xstring shortcut_start=str<xstring>::cast(shortcut_proposition);
    if (shortcut_start.empty())
        shortcut_start=L"xns";
    int shortcut_ext=0;
    xstring shortcut = shortcut_start;
    while (has_short_namespace(xs,shortcut))
    {
        shortcut = shortcut_start+str<xstring>::cast(++shortcut_ext);
    };
    return shortcut;
};

//-----------------------------------------------------------------------------
/** iterator for the xstream.
 *  @ingroup user
 *  This is the ostream_iterator equivalent for the xstream.
 *  
 */
//-----------------------------------------------------------------------------
template<typename T>
class xostream_iterator
    :public std::iterator<std::output_iterator_tag, void, void, void, void> 
{
public:
    typedef xchar_t char_type;
    typedef xostream ostream_type;

public:
    xostream_iterator(ostream_type& ostr)
      :delim_()
	,xos_(ostr)
	  {};

    xostream_iterator(ostream_type& ostr, const char * delim)
      :delim_(str<xstring>::cast(delim))
		,xos_(ostr)
    {};

    xostream_iterator(ostream_type& ostr, const xchar_t * delim)
     :xos_(ostr)
      ,delim_(delim)
    {};

    xostream_iterator<T>& operator=(const T& val)
    {
        xos_ << val;
        if (! delim_.empty())
            xos_ << delim_;
        return *this;
    };

    xostream_iterator<T>& operator*(){ return *this; };
    xostream_iterator<T>& operator++(){ return *this; };
    xostream_iterator<T> operator++(int){ return *this; };

protected:
    xstring delim_;
    ostream_type & xos_;
};

//-----------------------------------------------------------------------------
/** iterator for the xstream.
 *  @ingroup user
 *  This is the istream_iterator equivalent for the xstream.
 *  
 */
//-----------------------------------------------------------------------------
template<typename T, typename _Diff = std::ptrdiff_t>
class xistream_iterator
    :public std::iterator<std::input_iterator_tag, T, _Diff, const T*, const T&>
{
public:
	typedef xistream_iterator<T, _Diff> this_t;
	typedef xistream istream_type;

	xistream_iterator()
	  :xis_(NULL)
    {};

	xistream_iterator(istream_type & xis)
	  :xis_(&xis)
    {
        get_val();
    }

	const T& operator*() const { return (val_); };

	const T *operator->() const { return (&**this);};

    // preincrement
    this_t& operator++()
    {	
		get_val();
		return (*this);
	}

	// postincrement
    this_t operator++(int)
	{
		this_t tmp = *this;
		++*this;
		return (tmp);
	}

	bool equal(const this_t& rhs) const
	{
		return (xis_ == rhs.xis_);
	}

protected:
	void get_val()
	{	
	    if (xis_ != NULL && !(*xis_ >> val_))
			xis_ = NULL;
		}

	istream_type * xis_;
	T val_;	
};

template<typename T, typename _Diff>
bool operator==(const xistream_iterator<T, _Diff>& lhs, const xistream_iterator<T, _Diff>& rhs)
{	
	return (lhs.equal(rhs));
};

template<typename T, typename _Diff>
bool operator!=(const xistream_iterator<T, _Diff>& lhs, const xistream_iterator<T, _Diff>& rhs)
{	
	return (!(lhs==rhs));
};

//-----------------------------------------------------------------------------
/** Test the flag to eat all white space.
 *  Drop first white spaces in the stream before reading stag and etag
 *  <pre>
 *  	S ::= (x20 | x9 | xD | xA) 
 *  </pre>
 *  
 *  @ingroup stream 
 *  @param xis the stream
 *  @return the test result
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool has_skip_whitespace(xistream& xis);


XIMOL_END_NAMESPACE 

#endif // #ifndef XIMOL_STREAM_HPP_
