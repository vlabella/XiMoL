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
	\brief Facet fraction_digits headers.
    @ingroup facet

    \author Tournois Florent
	\version 1.0

    $Id: fraction_digits.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: fraction_digits.hpp,v $
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

    Revision 1.1  2004/01/19 20:40:55  tournois
    Add min, max and digits facet.
    Create the control flow file.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_FACET_FRACTION_DIGITS_HPP_
#define XIMOL_FACET_FRACTION_DIGITS_HPP_

#include <namespace_defs.hpp>
#include <error.hpp>
#include <translation.hpp>
#include <boost/static_assert.hpp>

XIMOL_FACET_BEGIN_NAMESPACE

//=============================================================================
/** constraining facet fraction_digits
    @ingroup facet

    [Definition:]   fractionDigits is the maximum number of digits in the 
    fractional part of values of datatypes ·derived· from decimal. The value 
    of fractionDigits  ·must· be a nonNegativeInteger . 

    ·fractionDigits· provides for: 
    Constraining a ·value space· to values with a specific maximum number of 
    decimal digits in the fractional part. 
    
    Example
    The following is the definition of a ·user-derived· datatype which could 
    be used to represent the magnitude of a person's body temperature on the 
    Celsius scale. This definition would appear in a schema authored by an 
    "end-user" and shows how to define a datatype by specifying facet values 
    which constrain the range of the ·base type·. 
    \code
        <simpleType name='celsiusBodyTemp'>
            <restriction base='decimal'>
                <totalDigits value='4'/>
                <fractionDigits value='1'/>
                <minInclusive value='36.4'/>
                <maxInclusive value='40.5'/>
            </restriction>
        </simpleType>
    \endcode

    The fractionDigits Schema Component
    Schema Component: fractionDigits 
     - {value} A nonNegativeInteger. 
     - {fixed} A boolean. If {fixed} is true, then types for which the 
        current type is the {base type definition} cannot specify a value 
        for fractionDigits other than {value}. 
     - {annotation} Optional. An annotation. 
    
    XML Representation of fractionDigits Schema Components
    The XML representation for a fractionDigits schema component is a 
    <fractionDigits> element information item. The correspondences between 
    the properties of the information item and properties of the 
    component are as follows: 

    XML Representation Summary: fractionDigits Element Information Item
    \code
        <fractionDigits 
            fixed = boolean : false
            id = ID 
            value = nonNegativeInteger 
            {any attributes with non-schema namespace . . .}>
            Content: (annotation?)
        </fractionDigits>
    \endcode

    fractionDigits Schema Component 
    Property Representation 
     - {value} The actual value of the value   [attribute]  
     - {fixed} The actual value of the fixed   [attribute], 
        if present, otherwise false  
     - {annotation} The annotations corresponding to all the <annotation> 
        element information items in the  [children], if any.  
     
    fractionDigits Validation Rules
    Validation Rule: fractionDigits Valid 

    A value in a ·value space· is facet-valid with respect to 
    ·fractionDigits· if: 
    1 the number of decimal digits in the fractional part of the value 
        is less than or equal to {value}; 
    
    Constraints on fractionDigits Schema Components
    Schema Component Constraint: fractionDigits less than or equal to 
    totalDigits 

    It is an ·error· for ·fractionDigits· to be greater than ·totalDigits·. 

 */
//=============================================================================
template < long max>
class fraction_digits
{
    BOOST_STATIC_ASSERT(max >= 0);
public:
    template < typename T >
    static bool check(T const & x, bool throw_error = true)
    {
        if (x.fraction_digits()<=max) return true;
        if (throw_error)
            XIMOL_THROW << _xtr(L"The fraction_digits should be less than or equal to %o and it is %o.",max,x.fraction_digits()) << XIMOL_AS_ERROR;
        return false;
    };

}; // end of fraction_digits<max>

XIMOL_FACET_END_NAMESPACE

#endif // #ifndef XIMOL_FACET_FRACTION_DIGITS_HPP_
