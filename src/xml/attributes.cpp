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
	\brief attributes implementation.
	
	\author Tournois Florent
	\version 1.0

    $Id: attributes.cpp,v 1.3 2008/04/30 20:44:44 LABELLAHOME\administrator Exp $
    $Log: attributes.cpp,v $
    Revision 1.3  2008/04/30 20:44:44  LABELLAHOME\administrator
    commit in makefile

    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.19  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.18  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.17  2004/01/29 20:52:35  tournois
    doc and tutorial.

    Revision 1.16  2004/01/18 11:40:58  tournois
    Add the pattern facet.

    Revision 1.15  2003/12/10 20:32:18  tournois
    Fix somes bugs about attributes and now tests are all check.

    Revision 1.14  2003/12/09 19:57:28  tournois
    Fix some bugs about attributes classes.

    Revision 1.13  2003/12/05 13:04:41  hfp
    adapt supplied functions

    Revision 1.12  2003/12/05 10:42:53  hfp
    completed

    Revision 1.11  2003/12/04 14:44:10  hfp
    shortcut/uri-mapping includes default namespace
    ns_map swaps key with value -> faster find for main use-case
    throwing error in some cases
    interface is based on map (insert, fiind)
    mis-use of special values on return removed (find etc.)
    size() returns an size_t (unsigned)

    Revision 1.10  2003/12/03 12:28:46  hfp
    swap, copy construction and assignment

    Revision 1.9  2003/11/19 20:52:54  tournois
    Add new manipulator for stag and etag.
    Correct bugs and add tests.

    Revision 1.8  2003/11/18 18:54:52  tournois
    Add str_cast and drop the transformation.hpp file.
  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <xml/attributes.hpp>
#include <parser/utils.hpp>
#include <translation.hpp>
#include <str_cast.hpp>
#include <sstream.hpp>
#include <error.hpp>

#include <algorithm>


XIMOL_BEGIN_PRIVATE_NAMESPACE
///////////////////////////////////////////////////////////////////////////////
// module level stuff (private)
///////////////////////////////////////////////////////////////////////////////

// helper for comparison
template<class MapT>
struct second_comp {
	second_comp(typename MapT::value_type::second_type const& second)
	: second_(second) {}

	bool operator()(typename MapT::value_type const& value) const {
		return value.second == second_;
	}

	typename MapT::value_type::second_type const &second_;
};

///////////////////////////////////////////////////////////////////////////////
XIMOL_END_PRIVATE_NAMESPACE


XIMOL_XML_BEGIN_NAMESPACE
///////////////////////////////////////////////////////////////////////////////
// class attributes (private)
///////////////////////////////////////////////////////////////////////////////

xstring const attributes::shortcut_default_uri_; // empty string


///////////////////////////////////////////////////////////////////////////////
// constructor(s) & destructor
///////////////////////////////////////////////////////////////////////////////

attributes::attributes()
{
}

///////////////////////////////////////////////////////////////////////////////

attributes::attributes(attributes const& rhs)
: map_(rhs.map_)
, map_uri_(rhs.map_uri_)
{
}

///////////////////////////////////////////////////////////////////////////////

attributes::~attributes()
{
}


///////////////////////////////////////////////////////////////////////////////
// methods (public)
///////////////////////////////////////////////////////////////////////////////

void attributes::swap(attributes& rhs) throw()
{
	map_.swap(rhs.map_);
	map_uri_.swap(rhs.map_uri_);
}

///////////////////////////////////////////////////////////////////////////////

void attributes::clear()
{
	map_.clear();
	map_uri_.clear();
}

///////////////////////////////////////////////////////////////////////////////

attributes& attributes::operator+=(attributes const& rhs)
{
	for(const_iterator i = rhs.begin(), i_end = rhs.end();
		i != i_end; ++i)
	{
		insert(i->first.first, i->first.second, i->second);
	}

	for(const_ns_iterator ns_i = rhs.ns_begin(), ns_i_end = rhs.ns_end();
		ns_i != ns_i_end; ++ns_i)
	{
		insert_namespace(ns_i->second, /* short cut*/ 
                         ns_i->first); /* uri      */
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////

attributes::const_ns_iterator 
attributes::find_namespace(xstring const& short_ns) const
{ 
    return std::find_if(map_uri_.begin(), map_uri_.end(),
		second_comp<map_uri_type>(short_ns)); 
}

attributes::const_ns_iterator // return type
attributes::find_short_namespace(xstring const& uri) const
{
	return map_uri_.find(uri);
}

///////////////////////////////////////////////////////////////////////////////

std::pair<attributes::ns_iterator, bool> // return type
attributes::insert_namespace(xstring const& short_ns, xstring const& uri)
{
	if ((!XIMOL_PARSER_NAMESPACE_PATH::is_ncname(short_ns))&&
        (shortcut_default_uri_!=short_ns)){
		XIMOL_THROW << _xtr(L"There is no ncname") << XIMOL_AS_ERROR;
    }
    if (find_namespace(short_ns)!=map_uri_.end())
    { 
        map_uri_.erase(find_namespace(short_ns)->first);
    };

    if (find_short_namespace(uri)!=map_uri_.end())
    {
        map_uri_.erase(find_short_namespace(uri)->first);
    };

	return map_uri_.insert(map_uri_type::value_type(uri, short_ns));
}

///////////////////////////////////////////////////////////////////////////////

std::pair<attributes::iterator, bool> // return type
attributes::insert(xstring const& namespace_name, xstring const& name, xstring const& value)
{
	if(!XIMOL_PARSER_NAMESPACE_PATH::is_ncname(name)){
		XIMOL_THROW << _xtr(L"There is no ncname") << XIMOL_AS_ERROR;
	}

    const_ns_iterator const itr_uri = find_namespace(namespace_name);

	qname_type qname(itr_uri != ns_end() // is namespace_name a short cut?
		? itr_uri->first	// the mapped uri
		: namespace_name,	// is already an uri
		name);

	return map_.insert(map_type::value_type(qname, value));
}

void attributes::set(xstring const& namespace_name, xstring const& name, xstring const& value)
{
	insert(namespace_name,name,value).first->second = value;
}

///////////////////////////////////////////////////////////////////////////////

attributes::const_iterator // return type
attributes::find(xstring const& namespace_name, xstring const& name) const
{
    const_ns_iterator const itr_uri = find_namespace(namespace_name);

	return map_.find(qname_type(itr_uri != ns_end() // short cut?
		? itr_uri->first	// the mapped uri
		: namespace_name,	// is already an uri
		name));;
}

///////////////////////////////////////////////////////////////////////////////

xostream& attributes::write(xostream& xos) const
{
	XIMOL_PARSER_USING_NAMESPACE;

    // write the attributes 
    xstring short_ns;
	for(const_iterator i = begin(), i_end = end();
		i != i_end; ++i)
	{
		write_space(xos);

        // try to get the short namspace in the attributes list
		const_ns_iterator const i_short_ns = find_short_namespace(i->first.first);

        if (i_short_ns != ns_end()) {
            short_ns = i_short_ns->second; // the short cut define in this attributes list
        } else {
			short_ns = xos.context.get_short_namespace(i->first.first); // the short cut define in the xos
        };

		write_attribute(xos, i->first.second, i->second, short_ns);
	}

    // write the namespace declaration: the default namespace is also included
	for(const_ns_iterator ns_i = ns_begin(), ns_i_end = ns_end();
		ns_i != ns_i_end; ++ns_i)
	{
		write_space(xos);
		write_ns_att_name(xos, ns_i->second);
		write_eq(xos);
		write_att_value(xos, ns_i->first);
	}


	return xos;
}

///////////////////////////////////////////////////////////////////////////////

xistream& attributes::read(xistream& xis)
{
	clear();

	xchar_t xc = L'a';
	xstring name, short_ns, att_value;
	map_type att_waiting; // attributes that we need to find the ns

	XIMOL_PARSER_USING_NAMESPACE;
	read_optionnal_space(xis);

	static xstring const NAME_xmlns(L"xmlns");

    while(xis.get(xc) && is_first_char_ncname(xc)) {
		xis.putback(xc);
		read_attribute(xis, name, att_value, short_ns);
		read_optionnal_space(xis);


        // test if it is a namespace declaration
        if (short_ns == NAME_xmlns) 
        {
		    insert_namespace(name, att_value); // std namespace
        } else {
            if (name == NAME_xmlns && short_ns.empty())
                insert_namespace(L"", att_value);    // global namespace
            else 
			    att_waiting[qname_type(short_ns, name)] = att_value; // std attributes
        }
	}

	for(iterator i = att_waiting.begin(), i_end = att_waiting.end();
		i != i_end; ++i)
	{
        // try to find the real namespace
		const_ns_iterator i_uri_ns = find_namespace(i->first.first); // true in the attributes value

		xstring uri;
		if(i_uri_ns != ns_end() && i_uri_ns->second == i->first.first)
			uri = xis.context.get_namespace(i->first.first); // try in the context

		if(uri == i->first.first) {
			i_uri_ns = find_namespace(); // the default attributes namespace

			if(i_uri_ns != ns_end())
				uri = i_uri_ns->second;
		}

		if(uri.empty()) uri = xis.context.get_default_namespace();	// the default xos namespace

		insert(uri, i->first.second, i->second);
	}

	if(!is_first_char_ncname(xc)) xis.putback(xc);

	return xis;
}


//-----------------------------------------------------------------------------
// PutTo operator for the attributes
//-----------------------------------------------------------------------------
::std::ostream& operator<<(::std::ostream& os, const attributes& x)
{
    xostringstream xos;
    xos << x;
    return os << str< ::std::string>::cast(xos.str());
}

///////////////////////////////////////////////////////////////////////////////
XIMOL_XML_END_NAMESPACE
