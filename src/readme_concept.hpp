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
/** \page concept The XiMoL Concepts

\section concept_element_read Element Readable concept
In the table, \b x denotes an object whose type P is a model of element readable, \b xos denotes a XiMoL output stream.

@concept_begin
@concept_exp        xos << x and traits<P>::write(xos,x)
@concept_type       A ximol output stream reference
@concept_semantic   write the element on the stream. All data are encapsulated in the element tag. 
@concept_end_line
@concept_end


\section concept_element_write Element Writable concept
In the table, \b x denotes an object whose type P is a model of element readable, \b xos denotes a XiMoL output stream.

@concept_begin
@concept_exp        xis >> x and traits<P>::read(xis,x)
@concept_type       A ximol input stream reference
@concept_semantic   read the element from the stream. 
@concept_end_line
@concept_end

\section concept_element_rw Element Serializable concept
It's only the Element Writable concept and the Element Readable concept
@concept_begin
@concept_exp        xis >> x and traits<P>::read(xis,x)
@concept_type       A ximol input stream reference
@concept_semantic   read the element from the stream. 
@concept_end_line
@concept_exp        xos << x and traits<P>::write(xos,x)
@concept_type       A ximol output stream reference
@concept_semantic   write the element on the stream. All data are encapsulated in the element tag. 
@concept_end_line
@concept_end

\section concept_type_read Type Readable concept
In the table, \b x denotes an object whose type P is a model of element readable, \b xos denotes a XiMoL output stream.

@concept_begin
@concept_exp        traits<P>::write_data(xos,x)
@concept_type       A ximol output stream reference
@concept_semantic   Write the element type data on the stream. All data are not encapsulated in a unique element tag.  
@concept_end_line
@concept_end


\section concept_type_write Type Writable concept
In the table, \b x denotes an object whose type P is a model of element readable, \b xos denotes a XiMoL output stream.

@concept_begin
@concept_exp        traits<P>::read_data(xis,x)
@concept_type       A ximol input stream reference
@concept_semantic   Read the element type data from the stream.  All data are not encapsulated in a unique element tag.
@concept_end_line
@concept_end

\section concept_type_rw Type Serializable concept
It's only the Type Writable concept and the Type Readable concept

@concept_begin
@concept_exp        traits<P>::write_data(xos,x)
@concept_type       A ximol output stream reference
@concept_semantic   Write the element type data on the stream. All data are not encapsulated in a unique element tag.  
@concept_end_line
@concept_exp        traits<P>::read_data(xis,x)
@concept_type       A ximol input stream reference
@concept_semantic   Read the element type data from the stream.  All data are not encapsulated in a unique element tag.
@concept_end_line
@concept_end

\section concept_schema Schema Documentation concept
In the table, \b x denotes an object whose type P is a model of schema documentation, \b xos denotes a XiMoL output stream.

@concept_begin
@concept_exp        traits<P>::schema_type(xos)
@concept_type       A ximol output stream reference
@concept_semantic   Write the type schema on the stream.
@concept_end_line
@concept_exp        traits<P>::schema_type_name()
@concept_type       A wide string
@concept_semantic   return the type name of the defined type.
@concept_end_line
@concept_exp        traits<P>::schema_documentation()
@concept_type       A wide string
@concept_semantic   return the documentation of the type.
@concept_end_line
@concept_exp        traits<P>::schema_element(xos,x)
@concept_type       A ximol output stream reference
@concept_semantic   return the schema element.
@concept_end_line
@concept_exp        traits<P>::schema_element_name(x)
@concept_type       A wide string
@concept_semantic   return the schema element name.
@concept_end_line
@concept_end

*/
//-----------------------------------------------------------------------------
