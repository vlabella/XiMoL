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
	\brief Traits.

    \author Tournois Florent
	\version 1.0

    $Id: traits.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: traits.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.4  2004/02/22 10:27:33  tournois
    Add some doc.

    Revision 1.3  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.2  2003/12/03 13:21:58  hfp
    include dependencies and type forwarding

    Revision 1.1  2003/11/17 22:06:59  tournois
    Add traits for relation stream--object.
    Change cast.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_TRAITS_HPP_
#define XIMOL_TRAITS_HPP_

#include <iosfwd>


XIMOL_BEGIN_NAMESPACE

namespace private_detail_about_traits 
{
    typedef char yes;
    struct no { char dummy[2]; };

    template <typename T>
    struct make { static T& type(); };

    template <typename U>
    struct is
    {
        static no   type(...);
        static yes  type(U);
    };

    struct does_not_exist { char dummy[17]; };
    template < typename T, typename U> does_not_exist operator<<(T&,U&);
    template < typename T, typename U> does_not_exist operator>>(T&,U&);
    template<typename T>
    T& insert_in_nslookup(T&,does_not_exist&);

    template < typename T, typename U>
    struct has_inserter
    {
        enum { value= (sizeof(is<does_not_exist>::type(operator<<(insert_in_nslookup(make<T>::type(),make<does_not_exist>::type()),make<U>::type()))) == sizeof(no)) };
    };

    template < typename T, typename U>
    struct has_extractor
    {
        enum { value= (sizeof(is<does_not_exist>::type(operator>>(insert_in_nslookup(make<T>::type(),make<does_not_exist>::type()),make<U>::type()))) == sizeof(no)) };
    };
};

template < typename Stream, typename Object >
struct stream_and_object_traits
{
    enum { is_extractible = private_detail_about_traits::has_extractor<Stream,Object>::value };
    enum { is_insertible = private_detail_about_traits::has_inserter<Stream,Object>::value };
};

#define XIMOL_TRAITS_STANDARD_OSTREAM(type) template <> struct stream_and_object_traits< ::std::ostream, type> { enum { is_extractible = false }; enum { is_insertible = true }; };
#define XIMOL_TRAITS_STANDARD_WOSTREAM(type) template <> struct stream_and_object_traits< ::std::wostream, type> { enum { is_extractible = false }; enum { is_insertible = true }; };
#define XIMOL_TRAITS_STANDARD_ISTREAM(type) template <> struct stream_and_object_traits< ::std::istream, type> { enum { is_extractible = true }; enum { is_insertible = false }; };
#define XIMOL_TRAITS_STANDARD_WISTREAM(type) template <> struct stream_and_object_traits< ::std::wistream, type> { enum { is_extractible = true }; enum { is_insertible = false }; };

#define XIMOL_TRAITS_STANDARD(type) XIMOL_TRAITS_STANDARD_OSTREAM(type) XIMOL_TRAITS_STANDARD_WOSTREAM(type) XIMOL_TRAITS_STANDARD_ISTREAM(type) XIMOL_TRAITS_STANDARD_WISTREAM(type)

XIMOL_TRAITS_STANDARD(bool           )
XIMOL_TRAITS_STANDARD(short          )
XIMOL_TRAITS_STANDARD(long           )
XIMOL_TRAITS_STANDARD(unsigned long  )
XIMOL_TRAITS_STANDARD(int            )
XIMOL_TRAITS_STANDARD(unsigned int   )
XIMOL_TRAITS_STANDARD(float          )
XIMOL_TRAITS_STANDARD(double         )
XIMOL_TRAITS_STANDARD(long double    )

XIMOL_END_NAMESPACE

#endif // #ifndef XIMOL_TRAITS_HPP_
