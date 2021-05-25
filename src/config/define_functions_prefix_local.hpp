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
	\brief Define all boring function like stag.
	
    this header define function

    XIMOL_HEADER_DEFINE_FUNCTION(T1,T2)
    for T1 in { std::string, ximol::xstring, const std::string, 
    const ximol::xstring, const char *, const ximol::xchar_t *}

    for T2 in { std::string, ximol::xstring, const std::string, 
    const ximol::xstring, const char *, const ximol::xchar_t *}

	\author Tournois Florent
	\version 1.0

    $Id: define_functions_prefix_local.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: define_functions_prefix_local.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.3  2004/02/22 10:27:33  tournois
    Add some doc.

    Revision 1.2  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.1  2004/02/21 20:03:58  tournois
    Change the stag, etag, open_stag, box and rebox template with macro.


  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_HEADER_DEFINE_FUNCTION
#error You must define XIMOL_HEADER_DEFINE_FUNCTION(T1,T2) before include this header
#endif 

#define XIMOL_TEMP_CREATOR_1(type1)\
    XIMOL_HEADER_DEFINE_FUNCTION(type1, std::string             )\
    XIMOL_HEADER_DEFINE_FUNCTION(type1, std::string const       )\
    XIMOL_HEADER_DEFINE_FUNCTION(type1, ximol::xstring          )\
    XIMOL_HEADER_DEFINE_FUNCTION(type1, ximol::xstring const    )\
    XIMOL_HEADER_DEFINE_FUNCTION(type1, char const *            )\
    XIMOL_HEADER_DEFINE_FUNCTION(type1, ximol::xchar_t const *  )

XIMOL_TEMP_CREATOR_1(std::string             )
XIMOL_TEMP_CREATOR_1(std::string const       )
XIMOL_TEMP_CREATOR_1(ximol::xstring          )
XIMOL_TEMP_CREATOR_1(ximol::xstring const    )
XIMOL_TEMP_CREATOR_1(char const *            )
XIMOL_TEMP_CREATOR_1(ximol::xchar_t const *  )

#undef XIMOL_TEMP_CREATOR_1

#undef XIMOL_HEADER_DEFINE_FUNCTION
