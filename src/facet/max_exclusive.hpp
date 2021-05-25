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
	\brief Facet max_exclusive headers.
    @ingroup facet

    \author Tournois Florent
	\version 1.0

    $Id: max_exclusive.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: max_exclusive.hpp,v $
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
#ifndef XIMOL_FACET_MAX_EXCLUSIVE_HPP_
#define XIMOL_FACET_MAX_EXCLUSIVE_HPP_

#include <namespace_defs.hpp>
#include <error.hpp>
#include <translation.hpp>
#include <typedefs.hpp>

XIMOL_FACET_BEGIN_NAMESPACE

//=============================================================================
/** constraining facet max_exclusive
    @ingroup facet

    [Definition:]   maxExclusive is the ·exclusive upper bound· of the 
    ·value space· for a datatype with the ·ordered· property. The value of 
    maxExclusive  ·must· be in the ·value space· of the ·base type·. 

    ·maxExclusive· provides for: 
    Constraining a ·value space· to values with a specific ·exclusive upper bound·. 
    Example
    The following is the definition of a ·user-derived· datatype which limits 
    values to integers less than or equal to 100, using ·maxExclusive·. 
    \code
        <simpleType name='less-than-one-hundred-and-one'>
            <restriction base='integer'>
                <maxExclusive value='101'/>
            </restriction>
        </simpleType>
    \endcode

    Note that the ·value space· of this datatype is identical to the 
    previous one (named 'one-hundred-or-less'). 
    
    The maxExclusive Schema Component
    Schema Component: maxExclusive 
     - {value} A value from the ·value space· of the {base type definition}. 
     - {fixed} A boolean. If {fixed} is true, then types for which the 
        current type is the {base type definition} cannot specify a value 
        for maxExclusive other than {value}. 
     - {annotation} Optional. An annotation. 
    
    XML Representation of maxExclusive Schema Components
    The XML representation for a maxExclusive schema component is a 
    <maxExclusive> element information item. The correspondences between 
    the properties of the information item and properties of the component 
    are as follows: 

    XML Representation Summary: maxExclusive Element Information Item
    \code
        <maxExclusive 
            fixed = boolean : false
            id = ID 
            value = anySimpleType 
            {any attributes with non-schema namespace . . .}>
            Content: (annotation?)
        </maxExclusive>
    \endcode

     - {value} ·must· be in the ·value space· of {base type definition}. 
    maxExclusive Schema Component 
    Property Representation 
     - {value} The actual value of the value   [attribute]  
     - {fixed} The actual value of the fixed   [attribute], if present, otherwise false  
     - {annotation} The annotations corresponding to all the <annotation> 
        element information items in the  [children], if any.  

    maxExclusive Validation Rules
    Validation Rule: maxExclusive Valid 

    A value in an ·ordered· ·value space· is facet-valid with respect 
    to ·maxExclusive·, determined as follows: 
    1 if the ·numeric· property in {fundamental facets} is true, 
        then the value ·must· be numerically less than {value}; 
    2 if the ·numeric· property in {fundamental facets} is false 
        (i.e., {base type definition} is one of the date and time related 
        datatypes), then the value ·must· be chronologically less than {value}; 
    
    Constraints on maxExclusive Schema Components
    Schema Component Constraint: maxInclusive and maxExclusive 

    It is an ·error· for both ·maxInclusive· and ·maxExclusive· to be specified 
    in the same derivation step of a datatype definition. 
    Schema Component Constraint: minExclusive <= maxExclusive 

    It is an ·error· for the value specified for ·minExclusive· to be greater 
    than the value specified for ·maxExclusive· for the same datatype. 
    Schema Component Constraint: maxExclusive valid restriction 

    It is an ·error· if any of the following conditions is true: 
    1 maxExclusive is among the members of {facets} of {base type definition} 
        and {value} is greater than the {value} of the parent maxExclusive 
    2 maxInclusive is among the members of {facets} of {base type definition} 
        and {value} is greater than the {value} of the parent maxInclusive 
    3 minInclusive is among the members of {facets} of {base type definition} 
        and {value} is less than or equal to the {value} of the parent minInclusive 
    4 minExclusive is among the members of {facets} of {base type definition} 
        and {value} is less than or equal to the {value} of the parent minExclusive 

 */
//=============================================================================
template < typename T, T const * max >
class max_exclusive
{
public:
    typedef T value_type;

    static bool check(T const & x, bool throw_error = true)
    {
        if (x < *max) return true;

        if (throw_error)
            XIMOL_THROW << _xtr(L"The upper bound of the value space is not respected.") << XIMOL_AS_ERROR;

        return false;    
    };

}; // end of max_exclusive<T,max>

XIMOL_FACET_END_NAMESPACE

#endif // #ifndef XIMOL_FACET_MAX_EXCLUSIVE_HPP_
