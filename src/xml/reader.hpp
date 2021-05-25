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
	\brief Define XiMoL Interface.

	This is the most important file in the project. Here we define
	the user interface of the library.
	
	\author Tournois Florent
	\version 1.0

    $Id: reader.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: reader.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:46  vlabella
    adding in ximol and xmlparser

    Revision 1.14  2004/08/05 16:49:44  tournois
    no message

    Revision 1.13  2004/02/25 18:59:13  tournois
    imporve the gcc compatibility.

    Revision 1.12  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.11  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.10  2004/01/29 20:52:35  tournois
    doc and tutorial.

    Revision 1.9  2004/01/26 20:44:21  tournois
    no message

    Revision 1.8  2004/01/25 17:32:56  tournois
    no message

    Revision 1.7  2004/01/22 22:01:35  tournois
    no message

    Revision 1.6  2004/01/19 20:40:56  tournois
    Add min, max and digits facet.
    Create the control flow file.

    Revision 1.5  2003/11/19 20:52:54  tournois
    Add new manipulator for stag and etag.
    Correct bugs and add tests.

    Revision 1.4  2003/11/18 18:54:52  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.3  2003/11/14 11:45:05  tournois
    First try for the stag.

    Revision 1.2  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.1  2003/10/26 14:49:32  hfp
    reader separated

    Revision 1.4  2003/10/25 13:53:40  hfp
    review and separation
  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_XML_READER_HPP_
#define XIMOL_XML_READER_HPP_

#include <config.hpp>
#include <typedefs.hpp>
#include <parser/utils.hpp>
#include <control_flow.hpp>

#include <map>


// forwarded declarations
XIMOL_BEGIN_NAMESPACE
	class xostream;
	class xistream;
XIMOL_END_NAMESPACE

XIMOL_XML_BEGIN_NAMESPACE

namespace helper {

    /// Small struct to Grap the reference to read.
    struct XIMOL_DECL abstract_copy_holder {
        abstract_copy_holder();
        abstract_copy_holder(const abstract_copy_holder & x);
		virtual ~abstract_copy_holder();
        abstract_copy_holder& operator=(const abstract_copy_holder & x );

		virtual abstract_copy_holder* clone() = 0;
		virtual xistream& read(xistream&) = 0;
        
    };

    /// Small struct to Grap the reference to read.
    template < typename T >
    struct copy_holder : public abstract_copy_holder {
        copy_holder(const T& x):x_(x){};
        copy_holder(const copy_holder<T>& x):x_(x.x_){};
        ~copy_holder(){};
        abstract_copy_holder* clone(){ return new copy_holder<T>(*this);}
        xistream& read(xistream & xis){ return xis >> x_; };
        T x_;
    };

}; // end of namespace helper

/// namespace for the reader policy
namespace reader_policy {
    template < typename qname_type = ::std::pair<xstring,xstring>, typename abs_reader_type = helper::abstract_copy_holder >
    struct by_default
    {
        typedef ::std::map<qname_type, abs_reader_type * > map_type;
        static xistream & read(const map_type & map, xistream & xis)
        {
            attributes att;
            qname_type qname(L"",L"");
            typename map_type::const_iterator i_end=map.end();
            typename map_type::const_iterator i;

            XIMOL_PARSER_USING_NAMESPACE;

            while (drop_content(xis) && is_stag(xis))
            {
                read_open_stag(xis,qname.second,att,qname.first);
                i=map.find(qname);
                if (i!=i_end)           
                    ((*i).second)->read(xis);
                else {
                    read_stag(xis,qname.second,qname.first);
                    drop_element_until_etag(xis);
                    read_etag(xis,qname.second,qname.first);
                }
            }
            return xis;
        };
    };
}; // end of reader_policy

//=============================================================================
/// Class to read some shuffled stuff in XML.
/** You must set all tags and launch the reader on an istream.
	@ingroup xml
    \todo make copie contructor and assignment operator.
  */
//=============================================================================
template < typename reading_policy_type = reader_policy::by_default<> >
class reader
{
public:
    typedef helper::abstract_copy_holder abs_reader_type;
	typedef ::std::pair<xstring,xstring> qname_type;
    typedef ::std::map<qname_type, abs_reader_type * > map_type;

protected:
    typedef map_type::iterator iterator;
    typedef map_type::const_iterator const_iterator;

public:

    reader()
    {};

    template < typename String1, typename String2, typename T >
        reader(const String1 & uri, const String2 tag, const T& x)
    {
        operator()(uri,tag,x); 
    };

    template < typename String1, typename T >
        reader(const String1 & tag, const T& x)
    {
        operator()(tag,x); 
    };

    /// delete all pointer
    ~reader()
    {
        const_iterator i_end=end();
        const_iterator i=begin();
        for(;i!=i_end;++i) delete (*i).second;
    };

    template < typename String1, typename String2, typename T >
        reader & operator()(const String1 & uri, const String2 tag, const T& x)
    {
        return add_reader(str<xstring>::cast(uri), str<xstring>::cast(tag), new helper::copy_holder<T>(x)); 
    };

    template < typename String1, typename T >
        reader & operator()(const String1 & tag, const T& x)
    {
        return add_reader(str<xstring>::cast(""), str<xstring>::cast(tag), new helper::copy_holder<T>(x)); 
    };

    xistream& read(xistream& xis)
    {   
        return reading_policy_type::read(map_,xis);
    };

protected:
    iterator       begin()       { return map_.begin(); };
    iterator       end  ()       { return map_.end(); };
    const_iterator begin() const { return map_.begin(); };
    const_iterator end  () const { return map_.end(); };

private:

    reader& add_reader(xstring const & uri, xstring const & tag_name, abs_reader_type * p)
    {
	    qname_type qname(uri,tag_name);
	    const_iterator i_end=end();
	    const_iterator i=map_.find(qname);
	    if (i!=i_end) delete (*i).second;
	    map_[qname]=p;
	    return *this;
    };

private:
    /// Map(tag, reference to read).
    map_type map_;
}; // end of class reader

//-----------------------------------------------------------------------------
/// GetFrom operator for the reader
//-----------------------------------------------------------------------------
template < typename T >
xistream& operator>>(xistream& xis, reader<T>& t)
{
    return t.read(xis);
};

XIMOL_XML_END_NAMESPACE

XIMOL_BEGIN_NAMESPACE

template < typename T >
struct ref_holder
{
    ref_holder(T & t):x(t){};
    ref_holder(const ref_holder<T> & r):x(r.x){};
    ~ref_holder(){};
    T& get_ref(){return x; };
private:
    ref_holder& operator=(const ref_holder<T> & r);
    T & x;
};

template < typename T > 
xistream& operator>>(xistream& xis, ref_holder<T> & r)
{ 
    return xis >> r.get_ref();
};

template < typename T > 
ref_holder<T> by_ref(T & x)
{ 
    return ref_holder<T>(x); 
};

template < typename T, typename callback_type>
struct read_and_callback_type
{
    read_and_callback_type(const callback_type & fun):f(fun){};
    callback_type f;
};

template < typename T, typename callback_type> 
xistream& operator>>(xistream& xis, read_and_callback_type<T,callback_type> & r)
{ 
    T t;
    xis >> t;
    r.f(t);
    return xis;
};

template < typename T, typename callback_type >
read_and_callback_type<T,callback_type> read_and_callback(T*, const callback_type & f)
{
    return read_and_callback_type<T,callback_type>(f);
};

XIMOL_END_NAMESPACE

#endif // #ifndef XIMOL_XML_READER_HPP_
