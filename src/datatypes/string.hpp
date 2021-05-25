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
	\brief Datatype String headers.

    \author Tournois Florent
	\version 1.0

    $Id: string.hpp,v 1.4 2013/02/10 21:08:10 vlabella Exp $
    $Log: string.hpp,v $
    Revision 1.4  2013/02/10 21:08:10  vlabella
    commit in makefile
    Committed on the Free edition of March Hare Software CVSNT Client.
    Upgrade to CVS Suite for more features and support:
    http://march-hare.com/cvsnt/

    Revision 1.3  2010/01/05 22:43:55  vlabella
    commit in makefile
    Committed on the Free edition of March Hare Software CVSNT Server.
    Upgrade to CVS Suite for more features and support:
    http://march-hare.com/cvsnt/

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.3  2005/05/12 03:14:24  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 03:12:50  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.9  2004/08/05 16:49:43  tournois
    no message

    Revision 1.8  2004/05/15 09:22:40  tournois
    no message

    Revision 1.7  2004/02/23 19:13:05  tournois
    no message

    Revision 1.6  2004/02/22 10:27:33  tournois
    Add some doc.

    Revision 1.5  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.4  2004/02/04 11:42:24  tournois
    no message

    Revision 1.3  2004/01/26 20:44:19  tournois
    no message

    Revision 1.2  2004/01/25 17:31:46  tournois
    no message

    Revision 1.1  2004/01/16 21:05:03  tournois
    Beginning the databinbding stuff
    Add the first facets and datatype.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_DATATYPES_STRING_HPP_
#define XIMOL_DATATYPES_STRING_HPP_

#include <namespace_defs.hpp>
#include <typedefs.hpp>
#include <datatypes/traits.hpp>
#include <iostream>

XIMOL_DATATYPES_BEGIN_NAMESPACE

//=============================================================================
/** string
    [Definition:]  The string datatype represents character strings in XML. 
    The ·value space· of string is the set of finite-length sequences of 
    characters (as defined in [XML 1.0 (Second Edition)]) that ·match· the 
    Char production from [XML 1.0 (Second Edition)]. A character is an atomic 
    unit of communication; it is not further specified except to note that 
    every character has a corresponding Universal Character Set code point, 
    which is an integer. 

    NOTE: Many human languages have writing systems that require child 
    elements for control of aspects such as bidirectional formating or ruby 
    annotation (see [Ruby] and Section 8.2.4 Overriding the bidirectional 
    algorithm: the BDO element of [HTML 4.01]). Thus, string, as a simple 
    type that can contain only characters but not child elements, is often 
    not suitable for representing text. In such situations, a complex type 
    that allows mixed content should be considered. For more information, 
    see Section 5.5 Any Element, Any Attribute 
    of [XML Schema Language: Part 2 Primer]. 

    NOTE: As noted in ordered, the fact that this specification does not 
    specify an ·order-relation· for ·string· does not preclude other 
    applications from treating strings as being ordered. 

    Constraining facets
    string has the following ·constraining facets·: 

    length 
    minLength 
    maxLength 
    pattern 
    enumeration 
    whiteSpace 

 */
//=============================================================================
typedef xstring string_type;

//=============================================================================
/** datatype traits for the string type
 */
//=============================================================================
template <>
struct XIMOL_DECL traits<string_type>
{
    /// the type
    typedef string_type type;

    /// Facet
    typedef XIMOL_FACET_NAMESPACE_PATH::none facet;

    /// return the documentation of the type
    static xstring const & documentation();

    /// Write the type schema on the stream.
    static xostream & schema_type(xostream & xos);

    /// return the type name of the defined type.
    static xstring const & schema_type_name();

    /// Write the type schema element on the stream.
    static xostream & schema_element(xostream & xos, type const & x);

    /// Write the type schema element on the stream.
    static xstring const & schema_element_name(type const & x);

    /// Write the element on the stream.
    static xostream & write(xostream & xos, type const & x);

    /// Read the element from the stream.
    static xistream & read(xistream & xis, type & x);

    /// Write the element data on the stream.
    static xostream & write_data(xostream & xos, type const & x);

    /// Read the element data from the stream.
    static xistream & read_data(xistream & xis, type & x);

}; // end of class traits<string_type>

XIMOL_DATATYPES_END_NAMESPACE

namespace std 
{
    XIMOL_DECL ximol::xostream & operator<<(ximol::xostream & xos, XIMOL_DATATYPES_NAMESPACE_PATH::string_type const & x); 
    XIMOL_DECL ximol::xistream & operator>>(ximol::xistream & xis, XIMOL_DATATYPES_NAMESPACE_PATH::string_type & x); 
};

XIMOL_DATATYPES_BEGIN_NAMESPACE

//=============================================================================
/** string
    [Definition:]  The string datatype represents character strings in XML. 
    The ·value space· of string is the set of finite-length sequences of 
    characters (as defined in [XML 1.0 (Second Edition)]) that ·match· the 
    Char production from [XML 1.0 (Second Edition)]. A character is an atomic 
    unit of communication; it is not further specified except to note that 
    every character has a corresponding Universal Character Set code point, 
    which is an integer. 

    NOTE: Many human languages have writing systems that require child 
    elements for control of aspects such as bidirectional formating or ruby 
    annotation (see [Ruby] and Section 8.2.4 Overriding the bidirectional 
    algorithm: the BDO element of [HTML 4.01]). Thus, string, as a simple 
    type that can contain only characters but not child elements, is often 
    not suitable for representing text. In such situations, a complex type 
    that allows mixed content should be considered. For more information, 
    see Section 5.5 Any Element, Any Attribute 
    of [XML Schema Language: Part 2 Primer]. 

    NOTE: As noted in ordered, the fact that this specification does not 
    specify an ·order-relation· for ·string· does not preclude other 
    applications from treating strings as being ordered. 

    Constraining facets
    string has the following ·constraining facets·: 

    length 
    minLength 
    maxLength 
    pattern 
    enumeration 
    whiteSpace 

 */
//=============================================================================
template < typename F >
class restricted_string
{
public:
    typedef string_type::traits_type traits_type;
    typedef string_type::allocator_type allocator_type;
    typedef string_type::iterator iterator;
    typedef string_type::const_iterator const_iterator;
    typedef string_type::size_type size_type;
    typedef string_type::difference_type difference_type;
    typedef string_type::const_reverse_iterator const_reverse_iterator;
    typedef string_type::reverse_iterator reverse_iterator;
    typedef string_type::pointer pointer;
    typedef string_type::const_pointer const_pointer;
    typedef string_type::reference reference;
    typedef string_type::const_reference const_reference;
    typedef string_type::value_type value_type;
    static const size_type npos;

    restricted_string():x(){};
    explicit restricted_string(const allocator_type& al):x(al){ check(); };
    explicit restricted_string(const string_type& right):x(right){ check(); };
    restricted_string(const string_type& right, size_type roff, size_type count = npos):x(right,roff,npos){ check(); };
    restricted_string(const string_type& right, size_type roff, size_type count, const allocator_type& al):x(right,roff,npos,al){ check(); };
    restricted_string(const restricted_string<F>& right):x(right.x){ check(); };
    restricted_string(const restricted_string<F>& right, size_type roff, size_type count = npos):x(right.x,roff,npos){ check(); };
    restricted_string(const restricted_string<F>& right, size_type roff, size_type count, const allocator_type& al):x(right.x,roff,npos,al){ check(); };
    restricted_string(const value_type *ptr, size_type count):x(ptr,count){ check(); };
    restricted_string(const value_type *ptr, size_type count, const allocator_type& al):x(ptr,count,al){ check(); };
    restricted_string(const value_type *ptr):x(ptr){ check(); };
    restricted_string(const value_type *ptr, const allocator_type& al):x(ptr,al){ check(); };
    restricted_string(size_type count, value_type ch):x(count,ch){ check(); };
    restricted_string(size_type count, value_type ch, const allocator_type& al):x(count,ch){ check(); };
    template <class InIt>
        restricted_string(InIt first, InIt last):x(first,last){ check(); };
    template <class InIt>
        restricted_string(InIt first, InIt last, const allocator_type& al):x(first,last,al){ check(); };

    restricted_string<F>& operator=(const restricted_string<F>& right){ x=right.x; check(); return *this; };
    restricted_string<F>& operator=(const string_type& right){ x=right; check(); return *this; };
    restricted_string<F>& operator=(const value_type *ptr){ x=ptr; check(); return *this; };
    restricted_string<F>& operator=(value_type ch){ x=ch; check(); return *this; };

    //iterator begin(){ return x.begin(); };
    const_iterator begin() const{ return x.begin(); };
    //iterator end(){ return x.end(); };
    const_iterator end() const{ return x.end(); };
    //reverse_iterator rbegin(){ return x.rbegin(); };
    const_reverse_iterator rbegin() const{ return x.rbegin(); };
    //reverse_iterator rend(){ return x.rend(); };
    const_reverse_iterator rend() const{ return x.rend(); };

    operator string_type(){ return x; };

    const_reference at(size_type off) const{ return x.at(off); };
    //reference at(size_type off){ return x.at(off); };
    const_reference operator[](size_type off) const{ return x[off]; };
    //reference operator[](size_type off){ return x[off]; };

    void push_back(value_type ch){ x.push_back(ch); check(); };
    const value_type *c_str() const{ return x.c_str(); };
    const value_type *data() const{ return x.data(); };
    size_type length() const{ return x.length(); };
    size_type size() const{ return x.size(); };
    size_type max_size() const{ return x.max_size(); };
    void resize(size_type newsize, value_type ch = value_type()){ return x.resize(newsize,ch); };
    size_type capacity() const{ return x.capacity(); };
    void reserve(size_type count = 0){ return x.reserve(count); };
    bool empty() const{ return x.empty(); };

    restricted_string<F>& operator+=(const restricted_string<F>& right){ x+=right.x; check(); return *this;};
    restricted_string<F>& operator+=(const string_type& right){ x+=right; check(); return *this;};
    restricted_string<F>& operator+=(const value_type *ptr){ x+=ptr; check(); return *this;};
    restricted_string<F>& operator+=(value_type ch){ x+=ch; check(); return *this;};
    restricted_string<F>& append(const string_type& right){ x.append(right); check(); return *this;};
    restricted_string<F>& append(const string_type& right, size_type roff, size_type count){ x.append(right,roff,count); check(); return *this;};
    restricted_string<F>& append(const restricted_string<F>& right){ x.append(right.x); check(); return *this; };
    restricted_string<F>& append(const restricted_string<F>& right, size_type roff, size_type count){ x.append(right.x,roff,count); check(); return *this;};
    restricted_string<F>& append(const value_type *ptr, size_type count){ x.append(ptr,count); check(); return *this; };
    restricted_string<F>& append(const value_type *ptr){ x.append(ptr); check(); check(); return *this; };
    restricted_string<F>& append(size_type count, value_type ch){ x.append(count,ch); check(); return *this;};
    template<class InIt>
        restricted_string<F>& append(InIt first, InIt last){ x.append(first,last); check(); return *this;};

    restricted_string<F>& assign(const restricted_string<F>& right){ x.assign(right.x); check(); return *this;};
    restricted_string<F>& assign(const restricted_string<F>& right, size_type roff, size_type count){ x.assign(right.x,roff,count); check(); return *this;};
    restricted_string<F>& assign(const string_type& right){ x.assign(right); check(); return *this;};
    restricted_string<F>& assign(const string_type& right, size_type roff, size_type count){ x.assign(right,roff,count); check(); return *this;};
    restricted_string<F>& assign(const value_type *ptr, size_type count){ x.assign(ptr,count); check(); return *this;};
    restricted_string<F>& assign(const value_type *ptr){ x.assign(ptr); check(); return *this;};
    restricted_string<F>& assign(size_type count, value_type ch){ x.assign(count,ch); check(); return *this;};
    template<class InIt>
        restricted_string<F>& assign(InIt first, InIt last){ x.assign(first,last); check(); return *this;};

    restricted_string<F>& insert(size_type off, const restricted_string<F>& right){ x.insert(off,right.x); check(); return *this;};
    restricted_string<F>& insert(size_type off, const restricted_string<F>& right, size_type roff, size_type count){ x.insert(off,right.x,roff,count); check(); return *this;};
    restricted_string<F>& insert(size_type off, const string_type& right){ x.insert(off,right); check(); return *this;};
    restricted_string<F>& insert(size_type off, const string_type& right, size_type roff, size_type count){ x.insert(off,right,roff,count); check(); return *this;};
    restricted_string<F>& insert(size_type off, const value_type *ptr, size_type count){ x.insert(off,ptr,count); check(); return *this;};
    restricted_string<F>& insert(size_type off, const value_type *ptr){ x.insert(off,ptr); check(); return *this;};
    restricted_string<F>& insert(size_type off, size_type count, value_type ch){ x.insert(off,count,ch); check(); return *this;};
    iterator insert(iterator where, value_type ch = value_type()){ iterator i=x.insert(where,ch); check(); return i;};
    void insert(iterator where, size_type count, value_type ch){ x.insert(where,count,ch); check(); };
    template<class InIt>
        void insert(iterator where, InIt first, InIt last){ x.insert(where,first,last); check(); };

    restricted_string<F>& erase(size_type off = 0, size_type count = npos){  x.erase(off,count); check(); return *this; };
    iterator erase(iterator where){ iterator i=x.erase(where); check(); return i;};
    iterator erase(iterator first, iterator last){ iterator i=x.erase(first,last); check(); return i;};
    void clear(){ x.clear(); check(); };

    restricted_string<F>& replace(size_type off, size_type n0,
        const restricted_string<F>& right){ x.replace(off,n0,right.x); check(); return *this;};
    restricted_string<F>& replace(size_type off, size_type n0,
        const restricted_string<F>& right, size_type roff,
            size_type count){ x.replace(off,n0,right.x,roff,count); check(); return *this;};
    restricted_string<F>& replace(size_type off, size_type n0,
        const string_type& right){ x.replace(off,n0,right); check(); return *this;};
    restricted_string<F>& replace(size_type off, size_type n0,
        const string_type& right, size_type roff,
            size_type count){ x.replace(off,n0,right,roff,count); check(); return *this;};
    restricted_string<F>& replace(size_type off, size_type n0,
        const value_type *ptr, size_type count){ x.replace(off,n0,ptr,count); check(); return *this;};
    restricted_string<F>& replace(size_type off, size_type n0,
        const value_type *ptr){ x.replace(off,n0,ptr); check(); return *this;};
    restricted_string<F>& replace(size_type off, size_type n0,
        size_type count, value_type ch){ x.replace(off,n0,count,ch); check(); return *this;};
    restricted_string<F>& replace(iterator first, iterator last,
        const restricted_string<F>& right){ x.replace(first,last,right.x); check(); return *this;};
    restricted_string<F>& replace(iterator first, iterator last,
        const string_type& right){ x.replace(first,last,right); check(); return *this;};
    restricted_string<F>& replace(iterator first, iterator last,
        const value_type *ptr, size_type count){ x.replace(first,last,ptr,count); check(); return *this;};
    restricted_string<F>& replace(iterator first, iterator last,
        const value_type *ptr){ x.replace(first,last,ptr); check(); return *this;};
    restricted_string<F>& replace(iterator first, iterator last,
        size_type count, value_type ch){ x.replace(first,last,count,ch); check(); return *this;};
    template<class InIt>
        restricted_string<F>& replace(iterator first, iterator last, InIt first2, InIt last2){ x.replace(first,last,first2,last2); check(); return *this;};
    size_type copy(value_type *ptr, size_type count, size_type off = 0) const{ size_type s=x.copy(ptr,count,off); check(); return s;};

    void swap(restricted_string<F>& right){ x.swap(right.x); };
    void swap(string_type& right){ x.swap(right); check(); };

    size_type find(const restricted_string<F>& right, size_type off = 0) const{ return x.find(right.x,off); };
    size_type find(const string_type& right, size_type off = 0) const{ return x.find(right,off); };
    size_type find(const value_type *ptr, size_type off, size_type count) const{ return x.find(ptr,off,count); };
    size_type find(const value_type *ptr, size_type off = 0) const{ return x.find(ptr,off); };
    size_type find(value_type ch, size_type off = 0) const{ return x.find(ch,off); };
    size_type rfind(const restricted_string<F>& right, size_type off = npos) const{ return x.rfind(right.x,off); };
    size_type rfind(const string_type& right, size_type off = npos) const{ return x.rfind(right,off); };
    size_type rfind(const value_type *ptr, size_type off, size_type count = npos) const{ return x.rfind(ptr,off,count); };
    size_type rfind(const value_type *ptr, size_type off = npos) const{ return x.rfind(ptr,off); };
    size_type rfind(value_type ch, size_type off = npos) const{ return x.rfind(ch,off); };
    size_type find_first_of(const restricted_string<F>& right, size_type off = 0) const{ return x.find_first_of(right.x,off); };
    size_type find_first_of(const string_type& right, size_type off = 0) const{ return x.find_first_of(right,off); };
    size_type find_first_of(const value_type *ptr, size_type off, size_type count) const{ return x.find_first_of(ptr,off,count); };
    size_type find_first_of(const value_type *ptr, size_type off = 0) const{ return x.find_first_of(ptr,off); };
    size_type find_first_of(value_type ch, size_type off = 0) const{ return x.find_first_of(ch,off); };
    size_type find_last_of(const restricted_string<F>& right, size_type off = npos) const{ return x.find_last_of(right.x,off); };
    size_type find_last_of(const value_type *ptr, size_type off, size_type count = npos) const{ return x.find_last_of(ptr,off,count); };
    size_type find_last_of(const value_type *ptr, size_type off = npos) const{ return x.find_last_of(ptr,off); };
    size_type find_last_of(value_type ch, size_type off = npos) const{ return x.find_last_of(ch,off); };
    size_type find_first_not_of(const restricted_string<F>& right, size_type off = 0) const{ return x.find_first_not_of(right.x,off); };
    size_type find_first_not_of(const string_type& right, size_type off = 0) const{ return x.find_first_not_of(right,off); };
    size_type find_first_not_of(const value_type *ptr, size_type off, size_type count) const{ return x.find_first_not_of(ptr,off,count); };
    size_type find_first_not_of(const value_type *ptr, size_type off = 0) const{ return x.find_first_not_of(ptr,off); };
    size_type find_first_not_of(value_type ch, size_type off = 0) const{ return x.find_first_not_of(ch,off); };
    size_type find_last_not_of(const restricted_string<F>& right, size_type off = npos) const{ return x.find_last_not_of(right.x,off); };
    size_type find_last_not_of(const string_type& right, size_type off = npos) const{ return x.find_last_not_of(right,off); };
    size_type find_last_not_of(const value_type *ptr, size_type off, size_type count) const{ return x.find_last_not_of(ptr,off,count); };
    size_type find_last_not_of(const value_type *ptr, size_type off = npos) const{ return x.find_last_not_of(ptr,off); };
    size_type find_last_not_of(value_type ch, size_type off = npos) const{ return x.find_last_not_of(ch,off); };
    restricted_string<F> substr(size_type off = 0, size_type count = npos) const{ return x.substr(off,count); };

    int compare(const restricted_string<F>& right) const{ return x.compare(right.x); };
    int compare(size_type off, size_type n0, const restricted_string<F>& right){ return x.compare(off,n0,right.x); };
    int compare(size_type off, size_type n0, const restricted_string<F>& right, size_type roff, size_type count){ return x.compare(off,n0,right.x,roff,count); };
    int compare(const string_type& right) const{ return x.compare(right); };
    int compare(size_type off, size_type n0, const string_type& right){ return x.compare(off,n0,right); };
    int compare(size_type off, size_type n0, const string_type& right, size_type roff, size_type count){ return x.compare(off,n0,right,roff,count); };
    int compare(const value_type *ptr) const{ return x.compare(ptr); };
    int compare(size_type off, size_type n0, const value_type *ptr) const{ return x.compare(off,n0,ptr); };
    int compare(size_type off, size_type n0, const value_type *ptr, size_type count) const{ return x.compare(off,n0,ptr,count); };

    allocator_type get_allocator() const{ return x.get_allocator(); };

    bool check(bool throw_error = true){ return F::check(*this,throw_error); };
    const string_type & litteral() const{ return x; };
private:
    string_type x;
}; // end of class restricted_string<Facet>

template < typename F >
const typename restricted_string<F>::size_type restricted_string<F>::npos=-1;

template < typename F >
std::ostream & operator<<( std::ostream & os, const restricted_string<F> & s)
{
    return os << s.litteral();
};

template < typename F >
ximol::xostream & operator<<( ximol::xostream & xos, const restricted_string<F> & s)
{
    return traits<restricted_string<F> >::write(xos,s);
};

template < typename F >
ximol::xistream & operator>>( ximol::xistream & xis, restricted_string<F> & s)
{
    return traits<restricted_string<F> >::read(xis,s);
};

//=============================================================================
/** datatype traits for the string type
 */
//=============================================================================
template < typename F >
struct traits<restricted_string<F> >
{
    /// The type
    typedef restricted_string<F> type;

    /// Facet
    typedef F facet;

    /// return the documentation of the type
    static xstring const & documentation()
    {	
		static const xstring doc;
		return doc;
    };

    /// Write the type schema on the stream.
    static xostream & schema_type(xostream & xos);

    /// return the type name of the defined type.
    static xstring const & schema_type_name();

    /// Write the type schema element on the stream.
    static xostream & schema_element(xostream & xos, type const & x);

    /// Write the type schema element on the stream.
    static xstring const & schema_element_name(type const & x);

    /// Write the element on the stream.
    static xostream & write(xostream & xos, type const & x);

    /// Read the element from the stream.
    static xistream & read(xistream & xis, type & x);

    /// Write the element data on the stream.
    static xostream & write_data(xostream & xos, type const & x);

    /// Read the element data from the stream.
    static xistream & read_data(xistream & xis, type & x);

}; // end of class traits<string_type>

XIMOL_DATATYPES_END_NAMESPACE

#endif // #ifndef XIMOL_DATATYPES_STRING_HPP_
