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
	\brief codecvt (declaration).
    @ingroup encoders
    We propose an libiconv wrapper for the C++ iostream. 

	\author Tournois Florent
	\version 1.0

    $Id: codecvt.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: codecvt.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.8  2004/02/25 18:58:39  tournois
    imporve the gcc compatibility.

    Revision 1.7  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.6  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.5  2004/01/27 21:49:51  tournois
    Add docs and tutorial.

    Revision 1.4  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.3  2003/10/27 11:29:32  hfp
    *** empty log message ***

    Revision 1.2  2003/10/27 10:36:50  hfp
    *** empty log message ***

    Revision 1.1  2003/10/25 18:20:32  hfp
    XiMoL now provides a own codecvt (interface) based on standard.
    Hides use of iconv-library as implementation detail.

    Revision 1.6  2003/10/25 13:53:39  hfp
    review and separation

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_CODECVT_HPP_
#define XIMOL_CODECVT_HPP_

#include <config.hpp>
#include <typedefs.hpp>
#include <locale>

XIMOL_BEGIN_NAMESPACE

//=============================================================================
/** Class codecvt.
 *  @ingroup encoders
 *  A small class to wrap the libiconv library.
 */
//=============================================================================
class XIMOL_DECL codecvt
	: public ::std::codecvt<xchar_t, char, mbstate_t>
{
public: // nested types
	typedef xchar_t    intern_type; //< internal char type.
	typedef char       extern_type; //< external char type.
	typedef mbstate_t  state_type;  //< state type.

public: // constructor(s) & destructor
	/**
	 * Contructor.
	 * The constructor initializes its locale::facet base 
	 *  		object with locale::facet(refs).
	 *  
	 * If refs==0, the lifetime is managed by the locale that contains this. 
	 * If refs==1, the memory must be explcitly managed. 
	 * the behavior for refs>1 is not defined.
	 */
	explicit codecvt(const ::std::string& encoding_name,
					 size_t refs = 0);

	/// Free the libiconv memory
	void delete_encoding();

	/// Allocate the libiconv memory
	void create_encoding(const ::std::string& encoding_name);

	/// Destructor.
	virtual ~codecvt();

protected:
	/**
	 * Conversion internal layer to external layer.
	 * The protected virtual member function endeavors to convert the source 
	 * sequence at [from, from_end) to a destination sequence that it stores 
	 * within [to, to_limit). It always stores in from_next a pointer to the first 
	 * unconverted element in the source sequence, and it always stores in 
	 * to_next a pointer to the first unaltered element in the destination sequence.
	 *
	 * state must represent the initial conversion state at the beginning of a 
	 * new source sequence. The function alters its stored value, as needed, to 
	 * reflect the current state of a successful conversion. Its stored value 
	 * is otherwise unspecified.
	 *
	 * The template version always returns noconv.
	 *
	 * @param state: state transmission.
	 * @param from: first internal char to convert.
	 * @param from_end: limit internal char to convert.
	 * @param from_next: next internal char to convert in return.
	 * @param to: first external char destination.
	 * @param to_limit: external char destination limit.
	 * @param to_next: next external char destination.
	 * @return The function returns: <ul>
	 *    <li> codecvt_base::error if the source sequence is ill formed. 
	 *    <li> codecvt_base::noconv if the function performs no conversion. 
	 *    <li> codecvt_base::ok if the conversion succeeds. 
	 *    <li> codecvt_base::partial if the source is insufficient, or if the 
	 * 		      destination is not large enough, for the conversion to succeed. 
	 * </ul>
	 */
	virtual result do_out(state_type& state,
						  const intern_type* from,
						  const intern_type* from_end,
						  const intern_type*& from_next,
						  extern_type* to,
						  extern_type* to_limit,
						  extern_type*& to_next) const;

	/**
	 * Conversion external layer to internal layer.
	 * The protected virtual member function endeavors to convert 
	 * the source sequence at [from, from_end) to a destination sequence 
	 * that it stores within [to, to_limit). It always stores in 
	 * from_next a pointer to the first unconverted element in the source 
	 * sequence, and it always stores in to_next a pointer to the first 
	 * unaltered element in the destination sequence.
	 *
	 * state must represent the initial conversion state at the 
	 * beginning of a new source sequence. The function alters its 
	 * stored value, as needed, to reflect the current state of a 
	 * successful conversion. Its stored value is otherwise unspecified.
	 *
	 * The template version always returns noconv.
	 *
	 * @param state: state transmission.
	 * @param from: first external char to convert.
	 * @param from_end: limit external char to convert.
	 * @param from_next: next external char to convert in return.
	 * @param to: first internal char destination.
	 * @param to_limit: internal char destination limit.
	 * @param to_next: next internal char destination.
	 * @return The function returns: <ul>
	 * 		<li> codecvt_base::error if the source sequence is ill formed. 
	 * 	    <li> codecvt_base::noconv if the function performs no conversion. 
	 * 	    <li> codecvt_base::ok if the conversion succeeds. 
	 * 		<li> codecvt_base::partial if the source is insufficient, or if the 
	 * 		         destination is not large enough, for the conversion to succeed 
	 * 	  </ul>
	 */
	virtual result do_in(state_type& state,
						 const extern_type* from,
						 const extern_type* from_end,
						 const extern_type*& from_next,
						 intern_type* to,
						 intern_type* to_limit,
						 intern_type*& to_next) const;

	/**
	 * Put unshift character.
	 * The protected virtual member function endeavors to convert the source 
	 * element intern_type(0) to a destination sequence that it stores 
	 * within [to, to_limit), except for the terminating element extern_type(0). 
	 * It always stores in to_next a pointer to the first unaltered element 
	 * in the destination sequence.
	 *
	 * state must represent the initial conversion state at the beginning 
	 * of a new source sequence. The function alters its stored value, as needed, 
	 * to reflect the current state of a successful conversion. Typically, 
	 * converting the source element intern_type(0) leaves the current state in the 
	 * initial conversion state.
	 *
	 * The template version always returns noconv.
	 *
	 * @param state: state transmission.
	 * @param to: first external char destination.
	 * @param to_limit: external char destination limit.
	 * @param to_next: next external char destination.
	 * @return The function returns:<ul>
	 *     <li> codecvt_base::error if state represents an invalid state 
	 *     <li> codecvt_base::noconv if the function performs no conversion 
	 *     <li> codecvt_base::ok if the conversion succeeds 
	 *     <li> codecvt_base::partial if the destination is not large enough for the conversion to succeed 
	 *  </ul>
	 */
	virtual result do_unshift(state_type& state,
							  extern_type* to,
							  extern_type* to_limit,
							  extern_type*& to_next) const;

	/**
	 * Encoding test.
	 * @return The protected virtual member function returns: <ul>
	 * <li> -1, if the encoding of sequences of type to_type is state dependent 
	 * <li> 0, if the encoding involves sequences of varying lengths 
	 * <li> n, if the encoding involves only sequences of length n 
	 * </ul>
	 */
	virtual int do_encoding() const throw();

	/**
	 * The protected virtual member function returns true only. 
	 * If every call to do_in or do_out returns noconv. 
	 * The template version always returns true.
	 */
	virtual bool do_always_noconv() const throw(); 
  
	/**
	 * Number of external char needed to produce less than max internal char.
	 * The protected virtual member function effectively calls 
	 * do_in(mystate, from, end, next1, buf, buf + max, next2) for 
	 * mystate a copy of state, some buffer buf, and pointers 
	 * next1 and next2. It then returns next2 - buf. 
	 * (Thus, it counts the maximum number of conversions, not 
	 * greater than max, defined by the source sequence at [from, end).)
	 *
	 * The template version always returns the lesser of last1 - first1 and len2.
	 */
	virtual int do_length(const state_type& state,
						  const extern_type* from,
						  const extern_type* end,
						  size_t max) const;

	/**
	 * Return the max length encoding.
	 * The protected virtual member function returns the largest permissible 
	 * value that can be returned by do_length(first1, last1, 1), for 
	 * arbitrary valid values of first1 and last1. 
	 *
	 * The template version always returns 1.
	 */
	virtual int do_max_length() const throw();

private:
	/// Private copy-contructor - restricted creation.
	codecvt(const codecvt&);

	/// Restricted assignment.
	codecvt& operator=(const codecvt&);  

private:
	/**
	 * State for a stream.
	 * Type isn't exported - only forwarded.
	 */
	struct codecvt_state *p_internal_state_;

}; // end of class codecvt

XIMOL_END_NAMESPACE

#endif // #ifndef XIMOL_CODECVT_HPP_
