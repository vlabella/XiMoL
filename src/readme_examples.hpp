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

//-----------------------------------------------------------------------------
/** \example quickstart_01.cpp
	A first program to output some data in an xml stream.

    In this first example, we could see how to put a start tag into the stream. 
    We only need to use xml::stag("tag_name"). To close the tag, we use the 
    xml::etag(). We do not need to put the end tag name, ximol automagically 
    put it into the stream.

*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/** \example tutorial_hello.cpp
	A first program to serialize a small struct.

    With this example, we see how to put data on a xml stream. We could
    notice the xml::content function which read only the tag content.

    Here is the ouput of the program
    \code

    \endcode

*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/** \example tutorial_attribute.cpp
	A short program to learn all attribute feature

    With this example, we see how to put and extract data from the attribute 
    object. We also learn how to deal with namespace.

*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/** \example tutorial_stag.cpp
	A short program to learn all stag feature

    With this example, we see how to deal with tag.

*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/** \example example_vector.cpp
	A short program with vector.

*/
//-----------------------------------------------------------------------------

