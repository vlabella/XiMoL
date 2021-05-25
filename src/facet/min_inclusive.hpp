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
	\brief Facet min_inclusive headers.
    @ingroup facet

    \author Tournois Florent
	\version 1.0

    $Id: min_inclusive.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: min_inclusive.hpp,v $
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

    Revision 1.2  2004/01/25 17:32:50  tournois
    no message

    Revision 1.1  2004/01/19 20:40:55  tournois
    Add min, max and digits facet.
    Create the control flow file.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_FACET_MIN_INCLUSIVE_HPP_
#define XIMOL_FACET_MIN_INCLUSIVE_HPP_

#include <namespace_defs.hpp>
#include <error.hpp>
#include <translation.hpp>
#include <typedefs.hpp>

XIMOL_FACET_BEGIN_NAMESPACE

//=============================================================================
/** constraining facet min_inclusive
    @ingroup facet

    [Definition:]   minInclusive is the ·inclusive lower bound· of the 
    ·value space· for a datatype with the ·ordered· property. The value of 
    minInclusive  ·must· be in the ·value space· of the ·base type·. 

    ·minInclusive· provides for: 

    Constraining a ·value space· to values with a specific ·inclusive lower bound·. 
    Example
    The following is the definition of a ·user-derived· datatype which limits 
    values to integers greater than or equal to 100, using ·minInclusive·. 
    \code
        <simpleType name='one-hundred-or-more'>
            <restriction base='integer'>
                <minInclusive value='100'/>
            </restriction>
        </simpleType>
    \endcode

    The minInclusive Schema Component
    Schema Component: minInclusive 
     - {value} A value from the ·value space· of the {base type definition}. 
     - {fixed} A boolean. If {fixed} is true, then types for which the current 
        type is the {base type definition} cannot specify a value for 
        minInclusive other than {value}. 
     - {annotation} Optional. An annotation. 
    
    XML Representation of minInclusive Schema Components
    The XML representation for a minInclusive schema component is a <minInclusive> 
    element information item. The correspondences between the properties of the 
    information item and properties of the component are as follows: 

    XML Representation Summary: minInclusive Element Information Item
    \code
        <minInclusive 
            fixed = boolean : false
            id = ID 
            value = anySimpleType 
            {any attributes with non-schema namespace . . .}>
            Content: (annotation?)
        </minInclusive>
    \endcode

    {value} ·must· be in the ·value space· of {base type definition}. 

    minInclusive Schema Component 
    Property Representation 
     - {value} The actual value of the value   [attribute]  
     - {fixed} The actual value of the fixed   [attribute], if present, 
        otherwise false  
     - {annotation} The annotations corresponding to all the <annotation> 
        element information items in the  [children], if any.  
     
    minInclusive Validation Rules
    Validation Rule: minInclusive Valid 

    A value in an ·ordered· ·value space· is facet-valid with respect 
    to ·minInclusive· if: 
    1 if the ·numeric· property in {fundamental facets} is true, then the 
        value ·must· be numerically greater than or equal to {value}; 
    2 if the ·numeric· property in {fundamental facets} is false (i.e., 
        {base type definition} is one of the date and time related datatypes), 
        then the value ·must· be chronologically greater than or equal to {value}; 
    4.3.10.4 Constraints on minInclusive Schema Components
    Schema Component Constraint: minInclusive < maxExclusive 

    It is an ·error· for the value specified for ·minInclusive· to be greater 
    than or equal to the value specified for ·maxExclusive· for the same datatype. 
    Schema Component Constraint: minInclusive valid restriction 

    It is an ·error· if any of the following conditions is true: 
    1 minInclusive is among the members of {facets} of {base type definition} 
        and {value} is less than the {value} of the parent minInclusive 
    2 maxInclusive is among the members of {facets} of {base type definition} 
        and {value} is greater the {value} of the parent maxInclusive 
    3 minExclusive is among the members of {facets} of {base type definition} 
        and {value} is less than or equal to the {value} of the parent minExclusive 
    4 maxExclusive is among the members of {facets} of {base type definition} 
        and {value} is greater than or equal to the {value} of the parent maxExclusive 

 */
//=============================================================================
template < typename T, T const * min >
class min_inclusive
{
public:
    typedef T value_type;

    static bool check(T const & x, bool throw_error = true)
    {
        if (( *min < x ) || ( *min == x )) return true;

        if (throw_error)
            XIMOL_THROW << _xtr(L"The lower bound of the value space is not respected.") << XIMOL_AS_ERROR;

        return false;    
    };

}; // end of min_inclusive<T,min>

XIMOL_FACET_END_NAMESPACE

#endif // #ifndef XIMOL_FACET_MIN_INCLUSIVE_HPP_
