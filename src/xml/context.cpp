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
	\brief context (implementation).

	\author Tournois Florent
	\version 1.0

    $Id: context.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: context.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.13  2004/08/05 16:49:44  tournois
    no message

    Revision 1.12  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.11  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.10  2004/01/19 20:40:55  tournois
    Add min, max and digits facet.
    Create the control flow file.

    Revision 1.9  2003/12/10 20:32:18  tournois
    Fix somes bugs about attributes and now tests are all check.

    Revision 1.8  2003/12/04 14:34:52  hfp
    XIMOL_XML_NAMESPACE_PATH::attributes changed

    Revision 1.7  2003/11/19 20:52:54  tournois
    Add new manipulator for stag and etag.
    Correct bugs and add tests.

    Revision 1.6  2003/11/18 18:54:52  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.5  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.4  2003/11/15 22:52:57  tournois
    Add somes function arround attributes and tests for attributes.

    Revision 1.3  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.2  2003/10/25 13:53:40  hfp
    review and separation

    Revision 1.1  2003/09/24 08:28:18  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <xml/context.hpp>
#include <str_cast.hpp>
#include <translation.hpp>
#include <error.hpp>
#include <macros.hpp>


XIMOL_XML_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// Clear the string
//-----------------------------------------------------------------------------
template <class T>
void clear_string(T &xstr)
{
	if (!xstr.empty()) xstr.erase(xstr.begin(),xstr.end()); 
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
context::context()
	: entities_()
	, parameter_entities_()
	, processing_instructions_()
	, notations_decl_()
	, version_num_(L"1.0")
	, standalone_decl_(false)
	, encoding_decl_(str< ::std::wstring>::cast(XIMOL_DEFAULT_ENCODING))
	, levels_()
{
	add_entity(L"lt"  , L"&#60;");
	add_entity(L"gt"  , L">");
	add_entity(L"amp" , L"&#38;");
	add_entity(L"apos", L"'");
	add_entity(L"quot", L"\"");
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
bool context::add_entity(xstring const & entity_name, xstring const & entity_value, xstring const & system_literal, xstring const & pubid_literal, xstring const & ndata_name)
{
	entity_def_type& entity=entities_[entity_name];
	clear_string(entity.entity_value);
	clear_string(entity.name_);
	clear_string(entity.pubid_literal_);
	clear_string(entity.system_literal_);

	if (entity_value.length()>0) 
	{
		entity.entity_value=entity_value;
		return true;
	}
	entity.pubid_literal_=pubid_literal;
	entity.system_literal_=system_literal;
	entity.name_=ndata_name;
	return true;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
bool context::add_paramter_entity(xstring const & entity_name, xstring const & entity_value, xstring const & system_literal, xstring const & pubid_literal)
{
	pe_def_type& entity=parameter_entities_[entity_name];
	clear_string(entity.entity_value);
	clear_string(entity.pubid_literal_);
	clear_string(entity.system_literal_);

	if (entity_value.length()>0) 
	{
		entity.entity_value=entity_value;
		return true;
	}
	entity.pubid_literal_=pubid_literal;
	entity.system_literal_=system_literal;
	return true;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
bool context::add_notation_decl(xstring const & name, xstring const & system_literal, xstring const & pubid_literal)
{
	notation_decl_type ndt;
	ndt.system_literal_=system_literal;
	ndt.pubid_literal_=pubid_literal;
	notations_decl_[name]=ndt;
	return true;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
bool context::add_processing_instruction(xstring const & pi_target, xstring const & value)
{
	processing_instructions_[pi_target]=value;
	return true;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
const context::notation_decl_type& context::get_notation_decl(xstring const & name) const
{
	notation_decl_map_type::const_iterator i(notations_decl_.find(name));
	if (i==notations_decl_.end()) {
		static notation_decl_type sResult;
		return sResult;
	}
	return i->second;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_entity(xstring const & entity_name) const
{
	entity_def_map_type::const_iterator i(entities_.find(entity_name));
	if (i==entities_.end()) return entity_name;
	return i->second.entity_value;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_parameter_entity(xstring const & entity_name) const
{
	pe_def_map_type::const_iterator i(parameter_entities_.find(entity_name));
	if (i==parameter_entities_.end()) return entity_name;
	return i->second.entity_value;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_processing_instruction(xstring const & pi_target) const
{
	map_type::const_iterator i(processing_instructions_.find(pi_target));
	if (i==processing_instructions_.end()) return pi_target;
	return i->second;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_version_num           () const
{
	return version_num_;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
bool context::get_sd_decl               () const
{
	return standalone_decl_;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_encoding_decl         () const
{
	return encoding_decl_;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void context::set_version_num  (xstring const & ver)
{
	version_num_=ver;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void context::set_sd_decl      (bool           sddecl)
{
	standalone_decl_=sddecl;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void context::set_encoding_decl(xstring const & encoding_name)
{
	encoding_decl_=encoding_name;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
context& context::add_new_level(xstring const & uri,
							  xstring const &tag, 
							  const XIMOL_XML_NAMESPACE_PATH::attributes& att, 
						      bool open_start, 
						      bool open_end)
{
	level level;
	level.att_+=att;
	level.tag_=tag;
    level.uri_tag_ = uri;

	XIMOL_XML_NAMESPACE_PATH::attributes::const_ns_iterator itr_uri =
		att.find_namespace(uri);

	if(itr_uri != att.ns_end())
		level.uri_tag_ = itr_uri->first;

    if(level.uri_tag_ == uri) {
		itr_uri = att.find_short_namespace(uri);

		if(itr_uri != att.ns_end() && itr_uri->first == uri)
		    level.uri_tag_ = get_namespace(uri);
	}

	level.is_open_stag=open_start;
	level.is_open_etag=open_end;

	levels_.push_back(level);
	return *this;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
context& context::destroy_level()
{
	if (get_depth()>0)
		levels_.pop_back();
	return *this;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
bool context::is_open_stag() const
{
	if (get_depth()>0)
		return levels_.back().is_open_stag;
	return false;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
bool context::is_open_etag() const
{
	if (get_depth()>0)
		return levels_.back().is_open_etag;
	return false;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
context& context::close_open_stag()
{
	if (get_depth()>0)
		levels_.back().is_open_stag=false;
	return *this;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
context& context::close_open_etag()
{
	if (get_depth()>0)
		levels_.back().is_open_etag=false;
	return *this;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
context& context::set_open_stag()
{
	if (get_depth()>0)
		levels_.back().is_open_stag=true;
	return *this;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
context& context::set_open_etag()
{
	if (get_depth()>0)
		levels_.back().is_open_etag=true;
	return *this;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_level_tag() const
{
	if (get_depth()==0) 
		XIMOL_THROW << _xtr(L"There is no tag") << XIMOL_AS_ERROR;

	return levels_.back().tag_;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_level_short_ns_tag() const
{
	if (get_depth()==0) 
		XIMOL_THROW << _xtr(L"There is no namespace tag") << XIMOL_AS_ERROR;

	return get_short_namespace(levels_.back().uri_tag_);
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_level_ns_tag() const
{
	if (get_depth()==0) 
		XIMOL_THROW << _xtr(L"There is no namespace tag") << XIMOL_AS_ERROR;

	return levels_.back().uri_tag_;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
const XIMOL_XML_NAMESPACE_PATH::attributes & context::get_level_attributes() const
{
	if (get_depth()==0) 
		XIMOL_THROW << "There is no attributes" << XIMOL_AS_ERROR;
		
	return levels_.back().att_;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
XIMOL_XML_NAMESPACE_PATH::attributes context::get_attributes() const
{
	levels_type::const_reverse_iterator i(levels_.rbegin()), i_end(levels_.rend());
	XIMOL_XML_NAMESPACE_PATH::attributes result;
	for(;i!=i_end;++i) 
		result+=i->att_;
	return result;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
int context::get_depth() const
{
	if (levels_.empty()) return 0;
	return static_cast<int>(levels_.size());
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
context& context::add_level_attributes(const XIMOL_XML_NAMESPACE_PATH::attributes & att)
{
	if (get_depth()>0)
		levels_.back().att_+=att;
	return *this;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_namespace(xstring const &short_ns) const
{
	levels_type::const_reverse_iterator i = levels_.rbegin();
	levels_type::const_reverse_iterator const i_end = levels_.rend();
	XIMOL_XML_NAMESPACE_PATH::attributes::const_ns_iterator i_uri;
	while(i != i_end && (i_uri = i->att_.find_namespace(short_ns)) == i->att_.ns_end()) ++i;

	if(i == i_end) return short_ns;

	static xstring const str_empty;
	return i_uri != i->att_.ns_end()
		? i_uri->first
		: str_empty;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_short_namespace(xstring const &uri) const
{	
	if (uri.empty()) return uri;

	levels_type::const_reverse_iterator i = levels_.rbegin();
	levels_type::const_reverse_iterator const i_end = levels_.rend();
	XIMOL_XML_NAMESPACE_PATH::attributes::const_ns_iterator i_short;
	while ( (i != i_end) && 
            ((i_short = i->att_.find_short_namespace(uri)) == i->att_.ns_end())
           ) ++i;

	if(i == i_end) 
        return uri;

	if (i_short == i->att_.ns_end())
        return uri;

    // i_short->second is the candidat
    if (get_namespace(i_short->second) == uri)
        return i_short->second;
  
    return uri;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_default_namespace() const
{
	levels_type::const_reverse_iterator i = levels_.rbegin();
	levels_type::const_reverse_iterator const i_end = levels_.rend();
	XIMOL_XML_NAMESPACE_PATH::attributes::const_ns_iterator i_default;
	while(i != i_end && (i_default = i->att_.find_namespace()) == i->att_.ns_end()) ++i;

	static xstring const str_empty;
	if(i == i_end) return str_empty;

	return i_default != i->att_.ns_end()
		? i_default->second
		: str_empty;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
xstring const & context::get_doc_type_name() const
{
	return doctype_name_;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void context::set_doc_type_name(xstring const & name)
{
	doctype_name_=name;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
const context::notation_decl_type & context::get_doctype_external_id() const
{
	return doctype_external_id_;
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void context::set_doctype_external_id(xstring const & system_literal, xstring const & pubid_literal)
{
	doctype_external_id_.system_literal_=system_literal;
	doctype_external_id_.pubid_literal_=pubid_literal;
}

XIMOL_XML_END_NAMESPACE
