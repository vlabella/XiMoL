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
	\brief control flow (declaration).
    @ingroup stream
    In this file we group all function to control the xml stream, 
    like wait a tag, test the incoming tag, etc. 
    
	\author Tournois Florent
	\version 1.0

    $Id: control_flow.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: control_flow.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 16:15:12  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.13  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

    Revision 1.12  2004/02/25 15:57:06  tournois
    no message

    Revision 1.11  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.10  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.9  2004/02/09 12:41:25  tournois
    Fix bug about error message.
    Add a read_optionnal_space before the stag read.

    Revision 1.8  2004/02/02 19:51:44  tournois
    Add a control_flow and finish the attribute tutorial.

    Revision 1.7  2004/01/29 20:52:35  tournois
    doc and tutorial.

    Revision 1.6  2004/01/27 21:49:51  tournois
    Add docs and tutorial.

    Revision 1.5  2004/01/22 22:06:52  tournois
    no message

    Revision 1.4  2004/01/21 21:06:41  tournois
    no message

    Revision 1.3  2004/01/19 20:40:55  tournois
    Add min, max and digits facet.
    Create the control flow file.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_CONTROL_FLOW_HPP_
#define XIMOL_CONTROL_FLOW_HPP_

#include <namespace_defs.hpp>
#include <config.hpp>
#include <stream.hpp>

XIMOL_BEGIN_NAMESPACE


//-----------------------------------------------------------------------------
/** Turn on the flag to eat all white space.
 *  Drop first white spaces in the stream before reading stag and etag
 *  <pre>
 *  	S ::= (x20 | x9 | xD | xA) 
 *  </pre>
 *  
 *  @ingroup stream 
 *  @param xis the stream
 *  @return the input stream
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& skip_whitespace(xistream& xis);

//-----------------------------------------------------------------------------
/** Turn off the flag to eat all white space.
 *  Drop first white spaces in the stream before reading stag and etag
 *  <pre>
 *  	S ::= (x20 | x9 | xD | xA) 
 *  </pre>
 *  
 *  @ingroup stream 
 *  @param xis the stream
 *  @return the input stream
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& no_skip_whitespace(xistream& xis);

//-----------------------------------------------------------------------------
/** Eat all white space.
 *  Drop first white spaces in the stream. White space are defined by:
 *  <pre>
 *  	S ::= (x20 | x9 | xD | xA) 
 *  </pre>
 *  
 *  @ingroup stream 
 *  @param xis the stream
 *  @return the input stream
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& drop_space(xistream& xis);

//-----------------------------------------------------------------------------
/** Eat the content until the next end or start tag.
 *  @ingroup stream 
 *  
 *  Following the W3C definition:
 *  \code
 *      [Definition: The text between the start-tag and end-tag 
 *                              is called the element's content:]
 *      [content    ::=    CharData? ((element | Reference | CDSect | 
 *                                                   PI | Comment) CharData?)* 
 *  \endcode
 *  This function is really usefull to drop the comment or wait a precise tag. 
 *
 *  @param xis the stream
 *  @return the input stream
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& drop_content(xistream& xis);

//-----------------------------------------------------------------------------
/** Test next element.
 *  @ingroup stream 
 *  test if the incoming element is a start tag. This function could be use 
 *  with the drop_content to do some loop.
 *  \code
 *    while ((drop_content(xis) && (is_stag(xis)) 
 *      ...;
 *  \endcode
 * 
 *  @param xis the stream
 *  @return the result of the test
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_stag(xistream& xis);

//-----------------------------------------------------------------------------
/** Test next element.
 *  @ingroup stream 
 *  test if the incoming element is a start tag. 
 *
 *  @param xis the stream
 *  @return the result of the test
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_etag(xistream& xis);

//-----------------------------------------------------------------------------
/** Drop next element
 *  @ingroup stream 
 *  This function drop the nest element if the stream is at a start tag.
 *  If an element is useless, then it is a good way to drop it.
 *
 *  @param xis the stream
 *  @return the input stream
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& drop_next_element(xistream& xis);

//-----------------------------------------------------------------------------
/** Drop next element
 *  @ingroup stream
 *  a simple combinaison of function to control the flow. 
 *  Here is the equivalent code
 *  \code
 *    while (drop_content(xis) && is_stag(xis)) drop_next_element(xis);
 *  \endcode
 *
 *  @param xis the stream
 *  @return the input stream
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& drop_element_until_etag(xistream& xis);

//-----------------------------------------------------------------------------
/** Wait for a pricise tag at this level.
 *  @ingroup stream
 *  drop the content and elements until it find an end tag or the tag.
 *
 *  @param xis the stream
 *  @param ns the namespace
 *  @param tag the tag
 *  @return true if the tag is found false if not.
 */
//-----------------------------------------------------------------------------
template < typename String1, typename String2 >
bool wait_stag(xistream& xis, String1 ns, String2 tag)
{
    xstring tag_read, ns_read;
    xstring real_ns=xis.context.get_short_namespace(ns);
    bool ok_find=false;
    while ((ok_find==false) && drop_content(xis) && is_stag(xis))
    {
        xis >> xml::open_stag(ns_read,tag_read);
        if((ns_read==str<xstring>::cast(real_ns)) && (tag_read==str<xstring>::cast(tag)))
        {
            ok_find=true;
        } else {
            drop_next_element(xis);
        };
    };
    return ok_find;
};

//-----------------------------------------------------------------------------
/** Wait for a pricise tag at this level.
 *  @ingroup stream
 *  drop the content and elements until it find an end tag or the tag.
 *
 *  @param xis the stream
 *  @param tag the tag
 *  @return true if the tag is found false if not.
 */
//-----------------------------------------------------------------------------
template < typename String1 >
bool wait_stag(xistream& xis, String1 tag)
{
    xstring tag_read, ns_read;
    bool ok_find=false;
    while ((ok_find==false) && drop_content(xis) && is_stag(xis))
    {
        xis >> xml::open_stag(ns_read,tag_read);
	// xis >> xml::open_stag (tag_read);
        if (tag_read==str<xstring>::cast(tag))
        {
            ok_find=true;
        } else {
            drop_next_element(xis);
        };
    };
    return ok_find;
};

XIMOL_END_NAMESPACE

#endif // #ifndef XIMOL_CONTROL_FLOW_HPP_
