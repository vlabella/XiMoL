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
	\brief Facet pattern headers.
    @ingroup facet

    \author Tournois Florent
	\version 1.0

    $Id: pattern.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: pattern.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 16:36:16  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:44  vlabella
    adding in ximol and xmlparser

    Revision 1.7  2004/05/15 09:22:40  tournois
    no message

    Revision 1.6  2004/02/22 22:36:23  hfp
    *** empty log message ***

    Revision 1.5  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.4  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.3  2004/01/25 17:32:51  tournois
    no message

    Revision 1.2  2004/01/18 12:06:20  tournois
    Add the enumeration facet.

    Revision 1.1  2004/01/18 11:40:58  tournois
    Add the pattern facet.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_FACET_PATTERN_HPP_
#define XIMOL_FACET_PATTERN_HPP_

#include <namespace_defs.hpp>
#include <error.hpp>
#include <translation.hpp>
#include <typedefs.hpp>
#include <boost/regex.hpp>

XIMOL_FACET_BEGIN_NAMESPACE

//=============================================================================
/** constraining facet pattern
    @ingroup facet

    [Definition:]   pattern is a constraint on the ·value space· of a datatype 
    which is achieved by constraining the ·lexical space· to literals which 
    match a specific pattern. The value of pattern  ·must· be 
    a ·regular expression·. 

    ·pattern· provides for: 
        Constraining a ·value space· to values that are denoted by literals 
        which match a specific ·regular expression·. 

    Example
    The following is the definition of a ·user-derived· datatype which is a 
    better representation of postal codes in the United States, by limiting 
    strings to those which are matched by a specific ·regular expression·. 
    \code
        <simpleType name='better-us-zipcode'>
        <restriction base='string'>
            <pattern value='[0-9]{5}(-[0-9]{4})?'/>
        </restriction>
        </simpleType>
    \endcode

    The pattern Schema Component
        Schema Component: pattern 
            - {value} A ·regular expression·. 
            - {annotation} Optional. An annotation. 

    XML Representation of pattern Schema Components
    The XML representation for a pattern schema component is a <pattern> 
    element information item. The correspondences between the properties 
    of the information item and properties of the component are as follows: 

    XML Representation Summary: pattern Element Information Item
    \code
        <pattern 
            id = ID 
            value = anySimpleType 
            {any attributes with non-schema namespace . . .}>
            Content: (annotation?)
        </pattern>
    \endcode

     - {value} ·must· be a valid ·regular expression·. pattern Schema Component 
        Property Representation 
     - {value} The actual value of the value   [attribute]  
     - {annotation} The annotations corresponding to all the <annotation> 
            element information items in the  [children], if any.  
 

    Constraints on XML Representation of pattern
        Schema Representation Constraint: Multiple patterns 

    If multiple <pattern> element information items appear as  [children] 
    of a <simpleType>, the  [value]s should be combined as if they 
    appeared in a single ·regular expression· as separate ·branch·es. 
    NOTE: It is a consequence of the schema representation constraint 
    Multiple patterns (§4.3.4.3) and of the rules for ·restriction· that 
    ·pattern· facets specified on the same step in a type derivation are 
    ORed together, while ·pattern· facets specified on different steps 
    of a type derivation are ANDed together. 

    Thus, to impose two ·pattern· constraints simultaneously, schema 
    authors may either write a single ·pattern· which expresses the 
    intersection of the two ·pattern·s they wish to impose, or define 
    each ·pattern· on a separate type derivation step. 

    pattern Validation Rules
    Validation Rule: pattern valid 
    A literal in a ·lexical space· is facet-valid with respect to ·pattern· if: 
    the literal is among the set of character sequences denoted by 
    the ·regular expression· specified in {value}. 

 */
//=============================================================================
template < wchar_t const * regular_expression >
class pattern
{
	static ::boost::wregex const& GetExpression() {
		static ::boost::wregex const expression(wstring(L"(")+regular_expression+wstring(L")"));
		return expression;
	}

public:
    template < typename T >
    static bool check(T const & x, bool throw_error = true)
    {
        using namespace boost;
        using namespace std;
        wcmatch what;
        xstring litteral=str<xstring>::cast(x.litteral());
        if(regex_match(litteral.c_str(), what, GetExpression()))
        {
            //cout << "what[0]=" << str<string>::cast(wstring(what[0])) << endl;
            //cout << "what[1]=" << str<string>::cast(wstring(what[1])) << endl;
            //cout << "what[2]=" << str<string>::cast(wstring(what[2])) << endl;
            //cout << "what[3]=" << str<string>::cast(wstring(what[3])) << endl;
            //cout << "expression=" << str<string>::cast(GetExpression().str()) << endl;
            if (what[0] == what[1]) return true;
        };

        if (throw_error)
            XIMOL_THROW << _xtr(L"The pattern %o is not respected by %o.",GetExpression().str(),x.litteral()) << XIMOL_AS_ERROR;

        return false;
    };

}; // end of pattern<regular_expression>

XIMOL_FACET_END_NAMESPACE

#endif // #ifndef XIMOL_FACET_PATTERN_HPP_
