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
	\brief Define the XML context.

	\author Tournois Florent
	\version 1.0

    $Id: context.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: context.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:46  vlabella
    adding in ximol and xmlparser

    Revision 1.8  2004/08/05 16:49:44  tournois
    no message

    Revision 1.7  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.6  2004/02/22 09:54:21  tournois
    Change years on the copyright.

    Revision 1.5  2004/01/29 20:52:35  tournois
    doc and tutorial.

    Revision 1.4  2003/11/16 11:03:35  tournois
    no message

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
#ifndef XIMOL_CONTEXT_HPP_
#define XIMOL_CONTEXT_HPP_

#include <xml/attributes.hpp>

#include <list>


XIMOL_XML_BEGIN_NAMESPACE

//=============================================================================
/// Class context.
/** @ingroup xml parser

	This class contains all information about reading and write XML.
	Entity and parameter entity are saved into this class.

	\author Tournois Florent.
	\todo this class must be commented.
  */
//=============================================================================
class XIMOL_DECL context
{
	public:
		/// Small struct for Notation Declartion.
		struct XIMOL_DECL notation_decl_type
		{
			xstring system_literal_;
			xstring pubid_literal_;
		}; // end of struct notation_decl_type

		/// Small struct for Parameter Entity Declartion.
		struct XIMOL_DECL pe_def_type
		{
			xstring entity_value;
			xstring system_literal_;
			xstring pubid_literal_;
		}; // end of struct Parameter Entity Declartion

		/// Small struct for Entity Definition.
		struct XIMOL_DECL entity_def_type
		{
			xstring entity_value;
			xstring system_literal_;
			xstring pubid_literal_;
			xstring name_;
		}; // end of struct Entity Definition


		/// struct to save information about the XML level.
		struct XIMOL_DECL level
		{
			xstring tag_;        ///<name fo the tag.
			xstring uri_tag_;
			bool           is_open_stag;  ///<Test if the tag is still open.
			bool           is_open_etag;  ///<Test if the tag is still open.
			XIMOL_XML_NAMESPACE_PATH::attributes att_;         ///<attributes of this level.
		}; // End of class level.

		typedef class XIMOL_DECL ::std::map<xstring,xstring>          map_type;
		typedef class XIMOL_DECL ::std::map<xstring,entity_def_type>    entity_def_map_type;
		typedef class XIMOL_DECL ::std::map<xstring,pe_def_type>        pe_def_map_type;
		typedef class XIMOL_DECL ::std::map<xstring,notation_decl_type> notation_decl_map_type;
		typedef class XIMOL_DECL ::std::list<level>                   levels_type;
		typedef class XIMOL_DECL ::std::map<xstring,void*>            key_map_type;

	public:
		/// add some predefined entities
		/** <pre>
			<!ENTITY lt     "&#38;#60;">
            <!ENTITY gt     "&#62;">
            <!ENTITY amp    "&#38;#38;">
            <!ENTITY apos   "&#39;">
            <!ENTITY quot   "&#34;">
			</pre>
          */
		context();

		///@name add functions
		//@{
		bool add_entity(xstring const & entity_name, xstring const & entity_value, xstring const & system_literal = L"", xstring const & pubid_literal = L"", xstring const & ndata_name = L"");
		bool add_paramter_entity(xstring const & entity_name, xstring const & entity_value, xstring const & system_literal = L"", xstring const & pubid_literal = L"");
		bool add_notation_decl(xstring const & name, xstring const & system_literal, xstring const & pubid_literal);
		bool add_processing_instruction(xstring const & pi_target, xstring const & value);
		//@}

		///@name Get functions
		//@{
		xstring const &          get_entity               (xstring const & entity_name) const;
		xstring const &          get_parameter_entity      (xstring const & entity_name) const;
		const notation_decl_type& get_notation_decl         (xstring const & name) const;
		xstring const &          get_processing_instruction(xstring const & pi_target) const;
		xstring const &          get_version_num           () const;
		bool                    get_sd_decl               () const;
		xstring const &          get_encoding_decl         () const;
		//@}

		///@name Set functions
		//@{
		void set_version_num  (xstring const & ver);
		void set_sd_decl      (bool           sddecl);
		void set_encoding_decl(xstring const & encoding_name);
		//@}

		///\name level functions
		//@{
		context& add_new_level(xstring const & uri, xstring const &tag, const XIMOL_XML_NAMESPACE_PATH::attributes& att, bool open_start=false, bool open_end=false);
		context& destroy_level();
		bool is_open_stag() const;
		bool is_open_etag() const;
		context& close_open_stag();
		context& close_open_etag();
		context& set_open_stag();
		context& set_open_etag();
		xstring const & get_level_tag() const;
		xstring const & get_level_ns_tag() const;
		xstring const & get_level_short_ns_tag() const;
		const XIMOL_XML_NAMESPACE_PATH::attributes & get_level_attributes() const;
		XIMOL_XML_NAMESPACE_PATH::attributes get_attributes() const;
		int get_depth() const;
		context& add_level_attributes(const XIMOL_XML_NAMESPACE_PATH::attributes & att);

		xstring const & get_namespace(xstring const &short_ns) const;
		xstring const & get_short_namespace(xstring const &uri) const;
		xstring const & get_default_namespace() const;
		//@}

		///\name doctype functions.
		//@{
		xstring const &          get_doc_type_name() const;
		void                     set_doc_type_name(xstring const & name);
		const notation_decl_type & get_doctype_external_id() const;
		void                     set_doctype_external_id(xstring const & system_literal, xstring const & pubid_literal);
		//@}

		///\name keyType functions.
		//@{
		template<class T>
		bool set_id(xstring const & key, T* t)
		{
			if (key_map_.find(key)!=key_map_.end()) return false;
			key_map_[key]=(void*)t;
			return true;
		};

		template<class T>
		bool get_id(xstring const & key, T* t)
		{
			key_map_type::const_iterator i(key_map_.find(key));
			if (i==key_map_.end()) return false;
			t=dynamic_cast<T*>((*i).second);
			return (t!=NULL);
		};
		//@}

	private:
		entity_def_map_type    entities_;               ///<Map entities <-> values
		pe_def_map_type        parameter_entities_;      ///<Map PEntities <-> values
		map_type             processing_instructions_; ///<Map PI <-> values
		notation_decl_map_type notations_decl_;          ///<Map Notations <-> values
		xstring				version_num_;             ///<Version number of the doc
		bool				standalone_decl_;         ///<SDDL of the doc
		xstring				encoding_decl_;           ///<encoding of the doc
		levels_type          levels_;                 ///<All level open
		xstring				doctype_name_;
		notation_decl_type    doctype_external_id_;
		key_map_type          key_map_;

}; // end of class context

XIMOL_XML_END_NAMESPACE


#endif // #ifndef XIMOL_CONTEXT_H
