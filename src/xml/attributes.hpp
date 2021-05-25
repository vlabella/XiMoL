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
	\brief attributes declaration.
	
	\author Tournois Florent
	\version 1.0

    $Id: attributes.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: attributes.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.20  2004/02/25 18:59:13  tournois
    imporve the gcc compatibility.

    Revision 1.19  2004/02/22 22:36:24  hfp
    *** empty log message ***

    Revision 1.18  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.17  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.16  2004/02/19 18:59:28  tournois
    attribute doc

    Revision 1.15  2004/01/29 20:52:35  tournois
    doc and tutorial.

    Revision 1.14  2004/01/18 11:40:58  tournois
    Add the pattern facet.

    Revision 1.13  2003/12/10 20:45:51  tournois
    no message

    Revision 1.12  2003/12/09 19:57:28  tournois
    Fix some bugs about attributes classes.

    Revision 1.11  2003/12/05 13:04:41  hfp
    adapt supplied functions

    Revision 1.10  2003/12/04 14:44:10  hfp
    shortcut/uri-mapping includes default namespace
    ns_map swaps key with value -> faster find for main use-case
    throwing error in some cases
    interface is based on map (insert, fiind)
    mis-use of special values on return removed (find etc.)
    size() returns an size_t (unsigned)

    Revision 1.9  2003/12/03 12:28:46  hfp
    swap, copy construction and assignment

    Revision 1.8  2003/11/19 20:52:54  tournois
    Add new manipulator for stag and etag.
    Correct bugs and add tests.

    Revision 1.7  2003/11/18 18:54:52  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.6  2003/11/15 22:52:57  tournois
    Add somes function arround attributes and tests for attributes.

    Revision 1.5  2003/11/14 13:30:20  tournois
    change the attributes class and fix some bugs.

    Revision 1.4  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.3  2003/10/25 13:53:40  hfp
    review and separation

    Revision 1.2  2003/09/28 16:46:13  hfp
    The "uri" default argument of the add()-method has changed the construction of default-value (::str::string() -> xstring()), because of non-existing conversion path from string to xstring.

    Revision 1.1  2003/09/24 08:28:18  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_ATTRIBUTES_HPP_
#define XIMOL_ATTRIBUTES_HPP_

#include <config.hpp>
#include <str_cast.hpp>
#include <typedefs.hpp>

#include <map>


// forwarded declarations
XIMOL_BEGIN_NAMESPACE
	class xistream;
	class xostream;
	class xistringstream;
	class xostringstream;
XIMOL_END_NAMESPACE


XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/** A simple class to contain attributes of a tag.
  * @ingroup xml
  * This class can read and write attributes for an XML tag.
  * This class contain :
  *      - a map ((uri,name),value)
  *      - a map (uri, short_cut)
  *
  *  the short_cut for the default uri is an empty string.
  */ 
//=============================================================================
class XIMOL_DECL attributes {
public: // nested types
	typedef xstring attribute_type; // should be a variant

private: // nested types
	typedef struct XIMOL_DECL ::std::pair<xstring, xstring> qname_type;

    typedef class XIMOL_DECL ::std::map<qname_type, attribute_type> map_type;

	typedef class XIMOL_DECL ::std::map<
		xstring,	// the short cut type
		xstring		// the uri type
	> map_uri_type;

public: // nested types
	typedef map_type::const_iterator const_iterator;
    typedef map_type::iterator iterator;

    typedef map_uri_type::const_iterator const_ns_iterator;
    typedef map_uri_type::iterator ns_iterator;

private: // class attributes
	static xstring const shortcut_default_uri_;

public: // constructor(s) & destructor
    attributes();

    attributes(attributes const& rhs);

    ~attributes();

public: // methods
	/**
	 * Exchange the contents of this object and
	 * the right-hand-side one.
	 * This is also a root of exception safety.
	 */
	void swap(attributes& rhs) throw();

	/**
	 * Assignment operator based on swap.
	 */
	attributes& operator=(attributes const& rhs) {
		attributes temp(rhs);
		swap(temp);
		return *this;
	}


	/// delete all members.
	void clear();


	/// number of attributes
	size_t size() const						{ return map_.size(); }


	///@name iterator
	//@{
	iterator begin()						{ return map_.begin(); }
	const_iterator	begin() const			{ return map_.begin(); }

	iterator end()							{ return map_.end(); }
	const_iterator end() const				{ return map_.end(); }


	ns_iterator ns_begin()					{ return map_uri_.begin(); }
	const_ns_iterator ns_begin() const		{ return map_uri_.begin(); }

	ns_iterator ns_end()					{ return map_uri_.end(); }
	const_ns_iterator ns_end() const		{ return map_uri_.end(); }
	//@}


	/** add attributes.
	  * This function add all the attributes and namespace.
      * All value of the argument will replace the value of the cuurent object.
      */
	attributes& operator+=(attributes const& rhs);


	/// Find a namespace (uri) for a given short cut.
	const_ns_iterator find_namespace(xstring const& short_ns) const;

	/// Find a short cut for a full namespace (uri).
	const_ns_iterator find_short_namespace(xstring const& uri) const;


	/// Insert a namespace mapping.
	std::pair<ns_iterator, bool> // return type
	insert_namespace(xstring const& short_ns, xstring const& uri);


	/// Find the default namespace.
	const_ns_iterator find_namespace() const	{ return find_namespace(shortcut_default_uri_); }

	/// Set the default namespace.
	void set_namespace(xstring const& uri)		{ insert_namespace(shortcut_default_uri_, uri); }

	
	/** Insert an attribute.
     *  If the attribute does not exist, it set the value
     */
	std::pair<iterator, bool> // return type
	insert(
		/** Can be the uri or a short cut */
		xstring const& namespace_name,
		/** The name of the attribute */
		xstring const& name,
		/** To be completed: Should be a variant. */
		xstring const& value);

	/// Set an attribute.
	void // return type
	set(
		/** Can be the uri or a short cut */
		xstring const& namespace_name,
		/** The name of the attribute */
		xstring const& name,
		/** To be completed: Should be a variant. */
		xstring const& value);

	/// Get an attribute.
	const_iterator find(
		/** Can be the uri or a short cut */
		xstring const& namespace_name,
		/** The name of the attribute */
		xstring const& name) const;


	/// PutTo operator.
	xostream& write(xostream& xos) const;

	/// GetFrom operator.
	xistream& read(xistream& xis);

private: // data members
	/// map ((uri,name), value).
	map_type map_;

	/// map (uri, short_ns).
	map_uri_type map_uri_;
}; // end  of the class attributes


//-----------------------------------------------------------------------------
/// put to operator for attributes
//-----------------------------------------------------------------------------
inline xostream& operator<<(xostream& xos, attributes const& rhs)
{
	return rhs.write(xos);
}

//-----------------------------------------------------------------------------
/// get from operator for attributes
//-----------------------------------------------------------------------------
inline xistream& operator>>(xistream& xis, attributes& rhs)
{
	return rhs.read(xis);
}

//-----------------------------------------------------------------------------
/// put to operator for attributes on standard stream
//-----------------------------------------------------------------------------
XIMOL_DECL ::std::ostream& operator<<(::std::ostream& os, attributes const& x);

XIMOL_XML_END_NAMESPACE

XIMOL_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
/** insert an attribute
 *  @ingroup xml
 *  insert a attribute in the attribute list.
 *  if the attribute name already exist, nothing is done.
 *  If an insertion occurred, the function returns pair(where, true). 
 *  Otherwise, it returns pair(it, false).
 * 
 * 
 *  @param att: the attributes list
 *  @param namespace_name: the namespace or shortcut for the inserted attribute
 *  @param name: the name for the inserted attribute
 *  @param value: the value for the inserted attribute (serialize with str<xstring>::cast(value))
 *  @return If an insertion occurred, the function returns pair(where, true). Otherwise, it returns pair(it, false).
 */
//-----------------------------------------------------------------------------
template<typename StringT1, typename StringT2, typename T>
std::pair<xml::attributes::iterator, bool> // return type
insert_attribute(xml::attributes& att,
				 StringT1 const& namespace_name,
				 StringT2 const& name,
				 T const& value)
{
	return att.insert(
		str<xstring>::cast(namespace_name),
		str<xstring>::cast(name),
        str<xstring>::cast(value));
}

//-----------------------------------------------------------------------------
/** insert an attribute
 *  @ingroup xml
 *  insert a attribute in the attribute list.
 *  if the attribute name already exist, nothing is done.
 */
//-----------------------------------------------------------------------------
template<typename StringT, typename T>
std::pair<xml::attributes::iterator, bool> // return type
insert_attribute(xml::attributes& att,
				 StringT const& name,
				 T const& value)
{
    return insert_attribute(att, L"", name, value);
}

//-----------------------------------------------------------------------------
/// set an attribute
//-----------------------------------------------------------------------------
template<typename StringT1, typename StringT2, typename T>
void 
set_attribute(xml::attributes& att,
				 StringT1 const& namespace_name,
				 StringT2 const& name,
				 T const& value)
{
	att.set(
		str<xstring>::cast(namespace_name),
		str<xstring>::cast(name),
        str<xstring>::cast(value));
}

//-----------------------------------------------------------------------------
/// set an xml::attributes
//-----------------------------------------------------------------------------
template<typename StringT, typename T>
void
set_attribute(xml::attributes& att,
				 StringT const& name,
				 T const& value)
{
    set_attribute(att, L"", name, value);
}

//-----------------------------------------------------------------------------
/**
 * Deserialize the attribute value.
 */
//-----------------------------------------------------------------------------
template<typename StringT1, typename StringT2, typename T>
bool get_attribute(xml::attributes const& att,
				   StringT1 const& namespace_name,
				   StringT2 const& name,
				   /**
					* Type requirements: copy constructable, serializable.
					* T doesn't need to be default constructable.
				    */
				   T& value)
{
	xml::attributes::const_iterator const i_value = att.find(
		str< ::std::wstring>::cast(namespace_name),
		str< ::std::wstring>::cast(name));

	if(i_value != att.end()) {
		::std::basic_istringstream<xchar_t> is(i_value->second+L" *");

		T temp(value); // copy constructable
		is >> temp;

		if(is.good()) {
			std::swap(temp, value);
			return true;
		}
	}

	return false;
}

/**
 * Deserialize the attribute from the name.
 */
template<typename StringT, typename T>
bool get_attribute(xml::attributes const& att, StringT const& name, T& value)
{
	return get_attribute(att, L"", name, value);
}

/**
 * Deserialize the attribute from the name.
 */
template<typename StringT1, typename StringT2 >
xstring get_raw_attribute(xml::attributes const& att, StringT1 const& namespace_name, StringT2 const& name)
{
	xml::attributes::const_iterator const i_value = att.find(
		str< ::std::wstring>::cast(namespace_name),
		str< ::std::wstring>::cast(name));

	if(i_value != att.end()) return i_value->second;

	return L"";
}

/**
 * Deserialize the attribute from the name.
 */
template<typename StringT>
xstring get_raw_attribute(xml::attributes const& att, StringT const& name)
{
	return get_raw_attribute(att, L"", name);
}

/**
 * Deserialize the attribute from the name.
 */
template < typename T>
struct extract_attribute
{
    template <typename StringT>
    static T get(xml::attributes const& att, StringT const& name)
    {
        T result;
        get_attribute(att, name, result);
        return result;
    };
    template <typename StringT1, typename StringT2>
    static T get(xml::attributes const& att, StringT1 const& namespace_name, StringT2 const& name)
    {
        T result;
        get_attribute(att, namespace_name, name, result);
        return result;
    };
};

//-----------------------------------------------------------------------------
/**
 * Deserialize the attribute from the name.
 */
//-----------------------------------------------------------------------------
template <>
struct extract_attribute<std::string>
{
    template <typename StringT>
    static std::string get(xml::attributes const& att, StringT const& name)
    {
        return str<std::string>::cast(get_raw_attribute(att, name));
    };
    template <typename StringT1, typename StringT2>
    static std::string get(xml::attributes const& att, StringT1 const& namespace_name, StringT2 const& name)
    {
        return str<std::string>::cast(get_raw_attribute(att, namespace_name, name));
    };
};

//-----------------------------------------------------------------------------
/**
 * Deserialize the attribute from the name.
 */
//-----------------------------------------------------------------------------
template <>
struct extract_attribute<std::wstring>
{
    template <typename StringT>
    static std::wstring get(xml::attributes const& att, StringT const& name)
    {
        return str<std::wstring>::cast(get_raw_attribute(att, name));
    };
    template <typename StringT1, typename StringT2>
    static std::wstring get(xml::attributes const& att, StringT1 const& namespace_name, StringT2 const& name)
    {
        return str<std::wstring>::cast(get_raw_attribute(att, namespace_name, name));
    };
};

//-----------------------------------------------------------------------------
/** define a short_namespace for an uri.
  * @param att the xml::attributes.
  * @param short_namespace the short cut  
  * @param uri the namespace or uri.  
  */
//-----------------------------------------------------------------------------
template < typename String1, typename String2>
bool set_namespace(xml::attributes & att, String1 & short_namespace, const String2 & uri)
{
    return att.insert_namespace(str< ::std::wstring>::cast(short_namespace), str< ::std::wstring>::cast(uri)).second;
}

//-----------------------------------------------------------------------------
/** define the default namespace.
  * @param att the xml::attributes.
  * @param uri the futur default namespace.  
  */
//-----------------------------------------------------------------------------
template < typename String >
void set_namespace(xml::attributes & att, const String & uri)
{
    att.set_namespace(str< ::std::wstring>::cast(uri));
}

//-----------------------------------------------------------------------------
/** Get the uri from the short namespace.
  * @param att the xml::attributes.
  * @param short_namespace the short namespace.
  * @return the uri or the short_namespace (in input) if the uri is not found. 
  */
//-----------------------------------------------------------------------------
template < typename String >
xstring get_namespace(xml::attributes & att, String & short_namespace)
{
    xml::attributes::const_ns_iterator i=att.find_namespace(str< ::std::wstring>::cast(short_namespace));
    if (i==att.ns_end())
        return str<xstring>::cast(short_namespace);
    return i->first;
}

//-----------------------------------------------------------------------------
/** get the default namespace.
  * @param att the xml::attributes.
  * @return return the default namespace of the xml::attributes.
  */
//-----------------------------------------------------------------------------
inline xstring get_namespace(xml::attributes & att)
{
    xml::attributes::const_ns_iterator i=att.find_namespace();
    if (i==att.ns_end())
        return L"";
    return i->first;
}

//-----------------------------------------------------------------------------
/** get the uri from the short namespace.
  * This template version call the internal function of the xml::attributes.
  *
  * @param att the xml::attributes.
  * @param uri the long version of the namespace.
  * @return the short namespace or the uri (in input) if the short namespace is not found. 
  */
//-----------------------------------------------------------------------------
template < typename String >
xstring get_short_namespace(xml::attributes & att, String & uri)
{
    xml::attributes::const_ns_iterator i=att.find_short_namespace(str< ::std::wstring>::cast(uri));
    if (i==att.ns_end())
        return str<xstring>::cast(uri);
    return i->second;
}

XIMOL_END_NAMESPACE

#endif // #ifndef XIMOL_ATTRIBUTES_HPP_
