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
	\brief Facet length headers.
    @ingroup facet

    \author Tournois Florent
	\version 1.0

    $Id: length.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: length.hpp,v $
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

    Revision 1.2  2004/01/25 17:32:37  tournois
    no message

    Revision 1.1  2004/01/16 21:05:03  tournois
    Beginning the databinbding stuff
    Add the first facets and datatype.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_FACET_LENGTH_HPP_
#define XIMOL_FACET_LENGTH_HPP_

#include <namespace_defs.hpp>
#include <error.hpp>
#include <translation.hpp>
#include <boost/static_assert.hpp>

XIMOL_FACET_BEGIN_NAMESPACE

//=============================================================================
/** constraining facet length
    @ingroup facet

    [Definition:]   length is the number of units of length, where units of 
        length varies depending on the type that is being ·derived· from. 
        The value of length ·must· be a nonNegativeInteger. 

    For string and datatypes ·derived· from string, length is measured in 
    units of characters as defined in [XML 1.0 (Second Edition)]. 
    For anyURI, length is measured in units of characters (as for string). 
    For hexBinary and base64Binary and datatypes ·derived· from them, 
    length is measured in octets (8 bits) of binary data. For datatypes 
    ·derived· by ·list·, length is measured in number of list items. 

    NOTE: For string and datatypes ·derived· from string, length will 
    not always coincide with "string length" as perceived by some users 
    or with the number of storage units in some digital representation. 
    Therefore, care should be taken when specifying a value for length 
    and in attempting to infer storage requirements from a given value for length. 

    ·length· provides for: 
        - Constraining a ·value space· to values with a specific number of units of length, where units of length varies depending on {base type definition}. 

        Example
        The following is the definition of a ·user-derived· datatype to represent product codes which must be exactly 8 characters in length. By fixing the value of the length facet we ensure that types derived from productCode can change or set the values of other facets, such as pattern, but cannot change the length. 

        \code
        <simpleType name='productCode'>
            <restriction base='string'>
                <length value='8' fixed='true'/>
            </restriction>
        </simpleType>
        \endcode

    The length Schema Component
        Schema Component: length 
             - {value} A nonNegativeInteger. 
             - {fixed} A boolean. If {fixed} is true, then types for which the current type is the {base type definition} cannot specify a value for length other than {value}. 
             - {annotation} Optional. An annotation. 

    XML Representation of length Schema Components
    The XML representation for a length schema component is 
    a <length> element information item. The correspondences 
    between the properties of the information item and properties of the component are as follows: 

    XML Representation Summary: length Element Information Item
    \code
<length 
  fixed = boolean : false
  id = ID 
  value = nonNegativeInteger 
  {any attributes with non-schema namespace . . .}>
  Content: (annotation?)
</length>
    \endcode

    length Schema Component 
    Property Representation 
        - {value} The actual value of the value   [attribute]  
        - {fixed} The actual value of the fixed   [attribute], if present, otherwise false  
        - {annotation} The annotations corresponding to all the <annotation> element information items in the  [children], if any.  
 

    length Validation Rules
    Validation Rule: Length Valid 

    A value in a ·value space· is facet-valid with respect to ·length·, determined as follows: 
        1 if the {variety} is ·atomic· then 
        1.1 if {primitive type definition} is string, then the length of the value, as measured in characters ·must· be equal to {value}; 
        1.2 if {primitive type definition} is hexBinary or base64Binary, then the length of the value, as measured in octets of the binary data, ·must· be equal to {value}; 
        2 if the {variety} is ·list·, then the length of the value, as measured in list items, ·must· be equal to {value} 

    Constraints on length Schema Components
    Schema Component Constraint: length and minLength or maxLength 

    It is an ·error· for both length and either of minLength or maxLength to be members of {facets}. 
    Schema Component Constraint: length valid restriction 

    It is an ·error· if length is among the members of {facets} of {base type definition} and {value} is not equal to the {value} of the parent length. 

 */
//=============================================================================
template < long len>
class length
{
    BOOST_STATIC_ASSERT(len >= 0);
public:
    template < typename T >
    static bool check(T const & x, bool throw_error = true)
    {
        if (x.length()==len) return true;
        if (throw_error)
            XIMOL_THROW << _xtr(L"The length should be %o and it is %o.",len,x.length()) << XIMOL_AS_ERROR;
        return false;
    };

}; // end of length<len>

XIMOL_FACET_END_NAMESPACE

#endif // #ifndef XIMOL_FACET_LENGTH_HPP_
