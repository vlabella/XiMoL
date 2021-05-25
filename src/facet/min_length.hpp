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
	\brief Facet min_length headers.
    @ingroup facet

    \author Tournois Florent
	\version 1.0

    $Id: min_length.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: min_length.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 16:36:16  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:44  vlabella
    adding in ximol and xmlparser

    Revision 1.4  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.3  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.2  2004/01/25 17:32:51  tournois
    no message

    Revision 1.1  2004/01/16 21:05:03  tournois
    Beginning the databinbding stuff
    Add the first facets and datatype.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_FACET_MIN_LENGTH_HPP_
#define XIMOL_FACET_MIN_LENGTH_HPP_

#include <namespace_defs.hpp>
#include <error.hpp>
#include <translation.hpp>
#include <boost/static_assert.hpp>

XIMOL_FACET_BEGIN_NAMESPACE

//=============================================================================
/** constraining facet min_length
    @ingroup facet

    [Definition:]   minLength is the minimum number of units of length, where 
    units of length varies depending on the type that is being ·derived· from. 
    The value of minLength  ·must· be a nonNegativeInteger. 

    For string and datatypes ·derived· from string, minLength is measured in 
    units of characters as defined in [XML 1.0 (Second Edition)]. For hexBinary 
    and base64Binary and datatypes ·derived· from them, minLength is measured in 
    octets (8 bits) of binary data. For datatypes ·derived· by ·list·, 
    minLength is measured in number of list items. 

    NOTE: For string and datatypes ·derived· from string, minLength will not 
    always coincide with "string length" as perceived by some users or with 
    the number of storage units in some digital representation. Therefore, 
    care should be taken when specifying a value for minLength and in 
    attempting to infer storage requirements from a given value for minLength. 

    
    ·minLength· provides for: Constraining a ·value space· to values with at 
    least a specific number of units of length, where units of length varies 
    depending on {base type definition}. 

    Example
    The following is the definition of a ·user-derived· datatype which 
    requires strings to have at least one character (i.e., the empty string is 
    not in the ·value space· of this datatype). 
    \code
        <simpleType name='non-empty-string'>
        <restriction base='string'>
            <minLength value='1'/>
        </restriction>
        </simpleType>
    \endcode

    The minLength Schema Component
    Schema Component: minLength 
        - {value} A nonNegativeInteger. 
        - {fixed} A boolean. If {fixed} is true, then types for which the current 
            type is the {base type definition} cannot specify a value for 
            minLength other than {value}. 
        - {annotation} Optional. An annotation. 

    XML Representation of minLength Schema Component
    The XML representation for a minLength schema component is a <minLength> element 
    information item. The correspondences between the properties of the information 
    item and properties of the component are as follows: 

    XML Representation Summary: minLength Element Information Item
    \code
        <minLength 
        fixed = boolean : false
        id = ID 
        value = nonNegativeInteger 
        {any attributes with non-schema namespace . . .}>
        Content: (annotation?)
        </minLength>
    \endcode

    minLength Schema Component Property Representation 
        - {value} The actual value of the value   [attribute]  
        - {fixed} The actual value of the fixed   [attribute], 
                    if present, otherwise false  
        - {annotation} The annotations corresponding to all 
                    the <annotation> element information 
                    items in the  [children], if any.  
 

    minLength Validation Rules
    Validation Rule: minLength Valid 

    A value in a ·value space· is facet-valid with respect to ·minLength·, 
    determined as follows: 
    1 if the {variety} is ·atomic· then 
    1.1 if {primitive type definition} is string, then the 
        length of the value, as measured in characters ·must· be 
        greater than or equal to {value}; 
    1.2 if {primitive type definition} is hexBinary or base64Binary, 
        then the length of the value, as measured in octets of the binary 
        data, ·must· be greater than or equal to {value}; 
    2 if the {variety} is ·list·, then the length of the value, as measured 
        in list items, ·must· be greater than or equal to {value} 
    4.3.2.4 Constraints on minLength Schema Components
    Schema Component Constraint: minLength <= maxLength 

    If both minLength and maxLength are members of {facets}, then the {value} 
    of minLength  ·must· be less than or equal to the {value} of maxLength. 
    Schema Component Constraint: minLength valid restriction 

    It is an ·error· if minLength is among the members of {facets} of 
    {base type definition} and {value} is less than the {value} 
    of the parent minLength. 

 */
//=============================================================================
template < long len>
class min_length
{
    BOOST_STATIC_ASSERT(len >= 0);
public:
    template < typename T >
    static bool check(T const & x, bool throw_error = true)
    {
        if (x.length()>=len) return true;
        if (throw_error)
            XIMOL_THROW << _xtr(L"The length should be greater than or equal to %o and it is %o.",len,x.length()) << XIMOL_AS_ERROR;
        return false;
    };

}; // end of length<len>

XIMOL_FACET_END_NAMESPACE

#endif // #ifndef XIMOL_FACET_MIN_LENGTH_HPP_
