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
	\brief Assignment declaration.
    In this file, we define all helper for the equality/assignment problem.
    In some cases, we need to assign a const string and then we just want to
    test the equality. All these helpers are here for this problem.

    \author Tournois Florent
	\version 1.0

    $Id: assignment.hpp,v 1.3 2008/04/30 20:44:43 LABELLAHOME\administrator Exp $
    $Log: assignment.hpp,v $
    Revision 1.3  2008/04/30 20:44:43  LABELLAHOME\administrator
    commit in makefile

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:39  vlabella
    adding in ximol and xmlparser

    Revision 1.13  2004/05/31 16:36:16  tournois
    introduce BOOST_DEDUCED_TYPENAME.

    Revision 1.3  2004/05/28 19:20:06  tournois
    no message

    Revision 1.12  2004/05/27 20:24:01  tournois
    no message

    Revision 1.11  2004/02/25 18:58:39  tournois
    imporve the gcc compatibility.

    Revision 1.10  2004/02/25 15:57:06  tournois
    no message

    Revision 1.9  2004/02/22 22:36:23  hfp
    *** empty log message ***

    Revision 1.8  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.7  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.6  2004/02/15 10:04:36  hfp
    * assignment_private_helper: all the things are already part of boost...
       * select -> mpl::if_c
       * equal -> now use of equal is more specified to boost::type_traits:
         is_const, is_convertible, ...
       * assignment (struct) is more special: test_equality is also selected
          in case of arrays

    Revision 1.5  2004/01/29 20:52:35  tournois
    doc and tutorial.

    Revision 1.4  2004/01/27 21:49:51  tournois
    Add docs and tutorial.

    Revision 1.3  2004/01/19 20:40:55  tournois
    Add min, max and digits facet.
    Create the control flow file.

    Revision 1.2  2004/01/18 11:40:58  tournois
    Add the pattern facet.

    Revision 1.1  2004/01/08 20:02:29  tournois
    Add XIMOL_XML_NAMESPACE_PATH::comment and assignment mainuplator.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_ASSIGNMENT_HPP_
#define XIMOL_ASSIGNMENT_HPP_

#include <str_cast.hpp>
#include <error.hpp>
#include <translation.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits.hpp>
#include <boost/config.hpp>

XIMOL_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
/** A small namespace to hide the dirty stuff.
 *  In this namespace we have define some classic type manipulation.
 */
//-----------------------------------------------------------------------------
namespace assignment_private_helper {

    /// test the character type for the serialisation
    template<typename T>
    struct char_type_choice {
		typedef typename ::boost::mpl::if_c<
			::boost::is_convertible<T, ::std::string const&>::value, // condition
			::std::string, // if true
			::std::wstring // else case
		>::type type;
	};

}; // end of the namespace assignment_private_helper

//-----------------------------------------------------------------------------
/** Namespace for the assignment test option.
 *  If we need to test the equality, here are some possibility. 
 */
//-----------------------------------------------------------------------------
namespace assignment_test_equality_policy 
{
    /// throw error when test are false
    struct error_policy_throw {
        static void object_are_different(){
            XIMOL_THROW << _xtr(L"The two value should be equal") << XIMOL_AS_ERROR;
        };
	
    };

    /// standard equality (x==y)
    template < typename policy = error_policy_throw >
    struct standard {
        template<typename T, typename U>
		static void value(T const& t_, U const& u_)
		{
            if (! (u_==t_) )
                policy::object_are_different();
        };
    };

    /// test with small char serialisation
    template < typename policy = error_policy_throw >
    struct char_serialization {
        template<typename T, typename U>
		static void value(T const& t_, U const& u_)
		{
            if(str< ::std::string>::cast(u_)!=str< ::std::string>::cast(t_))
                policy::object_are_different();
        }
    };

    /// test with wide char serialisation
    template < typename policy = error_policy_throw >
    struct wchar_serialization {
        template<typename T, typename U>
		static void value(T const& t_, U const& u_)
		{
            if(str< ::std::wstring>::cast(u_)!=str< ::std::wstring>::cast(t_))
                policy::object_are_different();
        }
    };

    /// test with char (choose at compile time serialisation)
    template < typename policy = error_policy_throw >
    struct serialization {
        template<typename T, typename U>
		static void value(T const& t_, U const& u_)
		{
            using namespace assignment_private_helper;
            if(str< BOOST_DEDUCED_TYPENAME char_type_choice<T>::type >::cast(u_)!=str< BOOST_DEDUCED_TYPENAME char_type_choice<T>::type >::cast(t_))
                policy::object_are_different();
        }
    };
}; // end of namespace assignment_test_equality_policy

//-----------------------------------------------------------------------------
/** Namespace for the assignment option.
 *  If we need to assign something, here are some possibility. 
 */
//-----------------------------------------------------------------------------
namespace assignment_equality_policy 
{
    /// standard assignment (x=y)
    struct standard {
        template<typename T, typename U>
        static void value(T& t_, U const& u_)
        { t_ = u_ ; }
    };

    /// assignment with small char serialization
    struct char_serialization {
        template<typename T, typename U>
		static void value(T& t_, U const& u_)
        { 
            ::std::istringstream is(str<std::string>::cast(u_));
            is >> t_;
        }
    };

    /// assignment with wide char serialization
    struct wchar_serialization {
        template<typename T, typename U>
		static void value(T& t_, U const& u_)
        { 
            ::std::wistringstream is(str<std::wstring>::cast(u_));
            is >> t_; 
        }
    };

    /// assignment to a string
    struct to_string {
        template<typename T, typename U>
		static void value(T& t_, U const& u_)
        { 
            using namespace assignment_private_helper;
            t_ = str< BOOST_DEDUCED_TYPENAME char_type_choice<T>::type >::cast(u_).c_str();
        }
    };
}; // end of namespace assignment_equality_policy

//=============================================================================
/** Assignment struct with options.
 *  assign type is the assignment option
 *  test_equality is the test type option
 */
//=============================================================================
template<typename assign, typename test_equality>
struct assignment {
    template<typename T, typename U>
    static T& equality(T& t_, U const& u_) {
		::boost::mpl::if_c<
			::boost::is_const<T>::value ||	// condition A
			::boost::is_array<T>::value,	// condition B: an assign could be specialized for arrays, but...
            test_equality, // true
            assign // false
        >::type::value(t_, u_);
        return t_;
    }
};

///@name assignment type defined
//@{

/// assignment for string type
typedef assignment<assignment_equality_policy::to_string, assignment_test_equality_policy::serialization<> > assignment_to_string;
/// assignment standard
typedef assignment<assignment_equality_policy::standard, assignment_test_equality_policy::standard<> > assignment_std;
/// assignment with small char serialization
typedef assignment<assignment_equality_policy::char_serialization, assignment_test_equality_policy::char_serialization<> > assignment_char_serialization;
/// assignment with wide char serialization
typedef assignment<assignment_equality_policy::char_serialization, assignment_test_equality_policy::char_serialization<> > assignment_wchar_serialization;

//@}

XIMOL_END_NAMESPACE

#endif // #ifndef XIMOL_ASSIGNMENT_HPP_
