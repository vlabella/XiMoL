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
	\brief Facet white_space headers.
    @ingroup facet

    \author Tournois Florent
	\version 1.0

    $Id: white_space.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: white_space.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 16:36:16  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.6  2004/08/05 16:49:44  tournois
    no message

    Revision 1.5  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.4  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.3  2004/02/05 09:08:33  tournois
    no message

    Revision 1.2  2004/01/25 17:32:51  tournois
    no message

    Revision 1.1  2004/01/18 16:42:55  tournois
    Add the white_space facet.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_FACET_WHITE_SPACE_HPP_
#define XIMOL_FACET_WHITE_SPACE_HPP_

#include <namespace_defs.hpp>
#include <error.hpp>
#include <translation.hpp>
#include <typedefs.hpp>
#include <xml/stag.hpp>
#include <xml/etag.hpp>

XIMOL_FACET_BEGIN_NAMESPACE

//=============================================================================
/** argument for the white space facet
    @ingroup facet

    No normalization is done, the value is not changed (this is the behavior 
    required by [XML 1.0 (Second Edition)] for element content) 

 */
//=============================================================================
struct XIMOL_DECL preserve
{
    //-----------------------------------------------------------------------------
    /** value "preserve"
        @return "preserve"
     */
    //-----------------------------------------------------------------------------
    static xstring value();

    //-----------------------------------------------------------------------------
    /** format the string
        No normalization is done, the value is not changed (this is the behavior 
        required by [XML 1.0 (Second Edition)] for element content) 
        
        @param xstr : the string to format
        @return the formated string
     */
    //-----------------------------------------------------------------------------
    static xstring format(xstring const & xstr);

    //-----------------------------------------------------------------------------
    /** test the string format
     *   @param xstr : the string to test
     */
    //-----------------------------------------------------------------------------
    static bool check(xstring const & xstr);

}; // end of preserve

//=============================================================================
/** argument for the white space facet
    @ingroup facet

    All occurrences of #x9 (tab), #xA (line feed) and #xD (carriage return) 
    are replaced with #x20 (space) 

 */
//=============================================================================
struct XIMOL_DECL replace
{
    //-----------------------------------------------------------------------------
    /** value "replace"
        @return "replace"
     */
    //-----------------------------------------------------------------------------
    static xstring value();

    //-----------------------------------------------------------------------------
    /** format the string
        All occurrences of #x9 (tab), #xA (line feed) and #xD (carriage return) 
        are replaced with #x20 (space) 
        
        @param xstr : the string to format
        @return the formated string
     */
    //-----------------------------------------------------------------------------
    static xstring format(xstring const & xstr);

    //-----------------------------------------------------------------------------
    /** test the string format
     *   @param xstr : the string to test
     */
    //-----------------------------------------------------------------------------
    static bool check(xstring const & xstr);

}; // end of class replace

//=============================================================================
/** argument for the white space facet
    @ingroup facet

    After the processing implied by replace, contiguous sequences of #x20's 
    are collapsed to a single #x20, and leading and trailing #x20's are removed. 

 */
//=============================================================================
struct XIMOL_DECL collapse
{
    //-----------------------------------------------------------------------------
    /** value "collapse"
        @return "collapse"
     */
    //-----------------------------------------------------------------------------
    static xstring value();

    //-----------------------------------------------------------------------------
    /** format the string
        After the processing implied by replace, contiguous sequences of #x20's 
        are collapsed to a single #x20, and leading and trailing #x20's are removed. 
        
        @param xstr : the string to format
        @return the formated string
     */
    //-----------------------------------------------------------------------------
    static xstring format(xstring const & xstr);

    //-----------------------------------------------------------------------------
    /** test the string format
     *   @param xstr : the string to test
     */
    //-----------------------------------------------------------------------------
    static bool check(xstring const & xstr);

}; // end of class collapse

//=============================================================================
/** constraining facet white_space
    @ingroup facet
    
    [Definition:]   whiteSpace constrains the ·value space· of types ·derived· 
    from string such that the various behaviors specified in Attribute Value 
    Normalization in [XML 1.0 (Second Edition)] are realized. The value of 
    whiteSpace must be one of {preserve, replace, collapse}. 

     - preserve : No normalization is done, the value is not changed 
        (this is the behavior required by [XML 1.0 (Second Edition)] 
        for element content) 
     - replace :  All occurrences of #x9 (tab), #xA (line feed) and #xD 
        (carriage return) are replaced with #x20 (space) 
     - collapse : After the processing implied by replace, contiguous 
        sequences of #x20's are collapsed to a single #x20, and leading 
        and trailing #x20's are removed. 

    NOTE: The notation #xA used here (and elsewhere in this specification) 
    represents the Universal Character Set (UCS) code point hexadecimal A 
    (line feed), which is denoted by U+000A. This notation is to be 
    distinguished from &#xA;, which is the XML character reference to 
    that same UCS code point. 

    whiteSpace is applicable to all ·atomic· and ·list· datatypes. For 
    all ·atomic· datatypes other than string (and types ·derived· by 
    ·restriction· from it) the value of whiteSpace is collapse and cannot 
    be changed by a schema author; for string the value of whiteSpace 
    is preserve; for any type ·derived· by ·restriction· from string 
    the value of whiteSpace can be any of the three legal values. For 
    all datatypes ·derived· by ·list· the value of whiteSpace is 
    collapse and cannot be changed by a schema author. For all datatypes 
    ·derived· by ·union·  whiteSpace does not apply directly; however, 
    the normalization behavior of ·union· types is controlled by the 
    value of whiteSpace on that one of the ·memberTypes· against which 
    the ·union· is successfully validated. 

    NOTE: For more information on whiteSpace, see the discussion on 
    white space normalization in Schema Component Details in 
    [XML Schema Part 1: Structures]. 

    ·whiteSpace· provides for: 
    Constraining a ·value space· according to the white space normalization rules. 

    Example
    The following example is the datatype definition for the token ·built-in·  
    ·derived· datatype. 
    \code
        <simpleType name='token'>
            <restriction base='normalizedString'>
            <whiteSpace value='collapse'/>
            </restriction>  
        </simpleType>
    \endcode

        The whiteSpace Schema Component

        Schema Component: whiteSpace 
         - {value} One of {preserve, replace, collapse}. 
         - {fixed} A boolean. If {fixed} is true, then types for which 
            the current type is the {base type definition} 
            cannot specify a value for whiteSpace other than {value}. 
         - {annotation} Optional. An annotation. 

    XML Representation of whiteSpace Schema Components
    The XML representation for a whiteSpace schema component is 
    a <whiteSpace> element information item. The correspondences 
    between the properties of the information item and properties 
    of the component are as follows: 

    XML Representation Summary: whiteSpace Element Information Item
    \code
    <whiteSpace 
        fixed = boolean : false
        id = ID 
        value = (collapse | preserve | replace)
        {any attributes with non-schema namespace . . .}>
        Content: (annotation?)
    </whiteSpace>
    \endcode

    whiteSpace Schema Component 
    Property Representation 
         - {value} The actual value of the value   [attribute]  
         - {fixed} The actual value of the fixed   [attribute], 
            if present, otherwise false  
         - {annotation} The annotations corresponding to 
            all the <annotation> element information items in 
            the  [children], if any.  
 
    whiteSpace Validation Rules
    NOTE: There are no ·Validation Rule·s associated ·whiteSpace·. 
    For more information, see the discussion on white space 
    normalization in Schema Component Details in [XML Schema Part 1: Structures]. 

    Constraints on whiteSpace Schema Components
    Schema Component Constraint: whiteSpace valid restriction 

    It is an ·error· if whiteSpace is among the members of {facets} of 
    {base type definition} and any of the following conditions is true: 
        1 {value} is replace or preserve and the {value} of the parent whiteSpace is collapse 
        2 {value} is preserve and the {value} of the parent whiteSpace is replace 
 */
//=============================================================================
template < typename value >
class white_space
{
public:
    typedef value value_type;

    template < typename T >
    static bool check(T const & x, bool throw_error = true)
    {
        if (value_type::check(str<xstring>::cast(x.litteral()))) return true;

        if (throw_error)
            XIMOL_THROW << _xtr(L"The white space facet is not respected.") << XIMOL_AS_ERROR;

        return false;    
    };

    /// Outout the facet schema
    static xostream& schema(xostream & xos)
    { 
        XIMOL_XML_USING_NAMESPACE;
        attributes att;
        set_namespace(att, L"xs", L"http://www.w3.org/2001/XMLSchema");
        set_attribute(att, L"value", value_type::value());
        return xos << stag(L"xs",L"whiteSpace",att) << etag(); 
    };

}; // end of white_space<value>

XIMOL_FACET_END_NAMESPACE

#endif // #ifndef XIMOL_FACET_WHITE_SPACE_HPP_
