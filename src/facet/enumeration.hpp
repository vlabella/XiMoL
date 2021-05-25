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
	\brief Facet enumeration headers.
    @ingroup facet

    \author Tournois Florent
	\version 1.0

    $Id: enumeration.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: enumeration.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 16:36:16  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:44  vlabella
    adding in ximol and xmlparser

    Revision 1.5  2004/08/05 16:49:44  tournois
    no message

    Revision 1.4  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.3  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.2  2004/01/25 17:32:37  tournois
    no message

    Revision 1.1  2004/01/18 12:06:20  tournois
    Add the enumeration facet.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_FACET_ENUMERATION_HPP_
#define XIMOL_FACET_ENUMERATION_HPP_

#include <namespace_defs.hpp>
#include <error.hpp>
#include <translation.hpp>
#include <typedefs.hpp>
#include <stream.hpp>

#include <list>
#include <algorithm>

XIMOL_FACET_BEGIN_NAMESPACE

//=============================================================================
/** constraining facet enumeration
    @ingroup facet
    
    [Definition:]   enumeration constrains the ·value space· to a 
        specified set of values. 

    enumeration does not impose an order relation on the ·value space· it 
    creates; the value of the ·ordered· property of the ·derived· datatype 
    remains that of the datatype from which it is ·derived·. 

    ·enumeration· provides for: 

    Constraining a ·value space· to a specified set of values. 
    Example
    The following example is a datatype definition for a ·user-derived· 
    datatype which limits the values of dates to the three US holidays 
    enumerated. This datatype definition would appear in a schema authored by 
    an "end-user" and shows how to define a datatype by enumerating the values 
    in its ·value space·. The enumerated values must be type-valid literals for 
    the ·base type·. 
    \code
        <simpleType name='holidays'>
            <annotation>
                <documentation>some US holidays</documentation>
            </annotation>
            <restriction base='gMonthDay'>
            <enumeration value='--01-01'>
                <annotation>
                    <documentation>New Year's day</documentation>
                </annotation>
            </enumeration>
            <enumeration value='--07-04'>
                <annotation>
                    <documentation>4th of July</documentation>
                </annotation>
            </enumeration>
            <enumeration value='--12-25'>
                <annotation>
                    <documentation>Christmas</documentation>
                </annotation>
            </enumeration>
            </restriction>  
        </simpleType>
    \endcode

    The enumeration Schema Component
    Schema Component: enumeration 
     - {value} A set of values from the ·value space· of the {base type definition}. 
     - {annotation} Optional. An annotation. 

    XML Representation of enumeration Schema Components
    The XML representation for an enumeration schema component 
    is an <enumeration> element information item. The correspondences 
    between the properties of the information item and properties 
    of the component are as follows: 

    XML Representation Summary: enumeration Element Information Item
    \code
        <enumeration 
            id = ID 
            value = anySimpleType 
            {any attributes with non-schema namespace . . .}>
            Content: (annotation?)
        </enumeration>
    \endcode

    {value} ·must· be in the ·value space· of {base type definition}. 

    enumeration Schema Component 
    Property Representation 
     - {value} The actual value of the value   [attribute]  
     - {annotation} The annotations corresponding to all the <annotation> 
            element information items in the  [children], if any.  
 
    Constraints on XML Representation of enumeration
    Schema Representation Constraint: Multiple enumerations 

    If multiple <enumeration> element information items appear 
    as  [children] of a <simpleType> the {value} of the enumeration 
    component should be the set of all such  [value]s. 

    enumeration Validation Rules
    Validation Rule: enumeration valid 

    A value in a ·value space· is facet-valid with respect to ·enumeration· if the value is one of the values specified in {value} 

    Constraints on enumeration Schema Components
    Schema Component Constraint: enumeration valid restriction 

    It is an ·error· if any member of {value} is not in the ·value space· 
    of {base type definition}. 

 */
//=============================================================================
template < typename T, std::list<T> const * value_set>
class enumeration
{
public:
    typedef enumeration<T,value_set> type;

public:
    static xstring const & documentation()
    {
        static const xstring doc(_(
            L"[Definition:]   enumeration constrains the ·value space· to a specified set of values. "
            L""
            L"enumeration does not impose an order relation on the ·value space· it creates; the value of the ·ordered· property of the ·derived· datatype remains that of the datatype from which it is ·derived·. "
            L""
            L"·enumeration· provides for: "
            L""
            L"Constraining a ·value space· to a specified set of values." 
                )); 
        return doc;
    };

    /// Write the element on the stream.
    static xostream & write(xostream & xos, type const & x)
    {
        return xos;
    };

    /// Write the element data on the stream.
    static xostream & write_data(xostream & xos, type const & x)
    {
        return xos;
    };

    static bool check(T const & x, bool throw_error = true)
    {
        using namespace std;
        if ( find(value_set->begin(), value_set->end(), x) != value_set->end() ) 
              return true;
        if (throw_error)
            XIMOL_THROW << _xtr(L"The value is not in the value set of the enumeration.") << XIMOL_AS_ERROR;
        return false;
    };

}; // end of enumeration<regular_expression>

XIMOL_FACET_END_NAMESPACE

#endif // #ifndef XIMOL_FACET_ENUMERATION_HPP_
