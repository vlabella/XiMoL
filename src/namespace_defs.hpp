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
	\brief Define all macros for the namespaces.

    These macro are only here to let you put ximol in your own namespace.

	\author Tournois Florent
	\version 1.0

    $Id: namespace_defs.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: namespace_defs.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.13  2004/05/27 20:24:01  tournois
    no message

    Revision 1.12  2004/05/15 09:22:40  tournois
    no message

    Revision 1.11  2004/03/03 22:05:30  tournois
    Add a short roadmap.
    Add BOOST_NO_STD_WSTRING for gcc.

    Revision 1.10  2004/02/22 10:27:32  tournois
    Add some doc.

    Revision 1.9  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.8  2004/01/16 21:05:02  tournois
    Beginning the databinbding stuff
    Add the first facets and datatype.

    Revision 1.7  2003/11/19 20:52:54  tournois
    Add new manipulator for stag and etag.
    Correct bugs and add tests.

    Revision 1.6  2003/11/16 11:03:23  tournois
    no message

    Revision 1.5  2003/11/14 11:45:04  tournois
    First try for the stag.

    Revision 1.4  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.3  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_NAMESPACE_DEFS_HPP_
#define XIMOL_NAMESPACE_DEFS_HPP_

/// macro definition for the namespace
#define XIMOL_BEGIN_PRIVATE_NAMESPACE namespace {
#define XIMOL_END_PRIVATE_NAMESPACE   };

/// macro definition for the namespace
#define XIMOL_NAMESPACE       ximol
#define XIMOL_NAMESPACE_PATH  ::XIMOL_NAMESPACE
#define XIMOL_BEGIN_NAMESPACE namespace XIMOL_NAMESPACE {
#define XIMOL_END_NAMESPACE   };
#define XIMOL_USING_NAMESPACE using namespace XIMOL_NAMESPACE_PATH;

/// macro definition for the namespace
#define XIMOL_XML_NAMESPACE       xml
#define XIMOL_XML_NAMESPACE_PATH  XIMOL_NAMESPACE_PATH::XIMOL_XML_NAMESPACE
#define XIMOL_XML_BEGIN_NAMESPACE XIMOL_BEGIN_NAMESPACE namespace XIMOL_XML_NAMESPACE {
#define XIMOL_XML_END_NAMESPACE   }; XIMOL_END_NAMESPACE
#define XIMOL_XML_USING_NAMESPACE using namespace XIMOL_XML_NAMESPACE_PATH;

/// macro definition for the namespace
#define XIMOL_PARSER_NAMESPACE       parser
#define XIMOL_PARSER_NAMESPACE_PATH  XIMOL_NAMESPACE_PATH::XIMOL_PARSER_NAMESPACE
#define XIMOL_PARSER_BEGIN_NAMESPACE XIMOL_BEGIN_NAMESPACE namespace XIMOL_PARSER_NAMESPACE {
#define XIMOL_PARSER_END_NAMESPACE   }; XIMOL_END_NAMESPACE
#define XIMOL_PARSER_USING_NAMESPACE using namespace XIMOL_PARSER_NAMESPACE_PATH;

/// macro definition for the namespace
#define XIMOL_ENCODERS_NAMESPACE       encoders
#define XIMOL_ENCODERS_NAMESPACE_PATH  XIMOL_NAMESPACE_PATH::XIMOL_ENCODERS_NAMESPACE
#define XIMOL_ENCODERS_BEGIN_NAMESPACE XIMOL_BEGIN_NAMESPACE namespace XIMOL_ENCODERS_NAMESPACE {
#define XIMOL_ENCODERS_END_NAMESPACE   };  XIMOL_END_NAMESPACE
#define XIMOL_ENCODERS_USING_NAMESPACE using namespace XIMOL_ENCODERS_NAMESPACE_PATH;

/// macro definition for the namespace
#define XIMOL_DATATYPES_NAMESPACE       datatypes
#define XIMOL_DATATYPES_NAMESPACE_PATH  XIMOL_NAMESPACE_PATH::XIMOL_DATATYPES_NAMESPACE
#define XIMOL_DATATYPES_BEGIN_NAMESPACE XIMOL_BEGIN_NAMESPACE namespace XIMOL_DATATYPES_NAMESPACE {
#define XIMOL_DATATYPES_END_NAMESPACE   }; XIMOL_END_NAMESPACE
#define XIMOL_DATATYPES_USING_NAMESPACE using namespace XIMOL_DATATYPES_NAMESPACE_PATH;

/// macro definition for the namespace
#define XIMOL_FACET_NAMESPACE       facet
#define XIMOL_FACET_NAMESPACE_PATH  XIMOL_NAMESPACE_PATH::XIMOL_FACET_NAMESPACE
#define XIMOL_FACET_BEGIN_NAMESPACE XIMOL_BEGIN_NAMESPACE namespace XIMOL_FACET_NAMESPACE {
#define XIMOL_FACET_END_NAMESPACE   }; XIMOL_END_NAMESPACE
#define XIMOL_FACET_USING_NAMESPACE using namespace XIMOL_FACET_NAMESPACE_PATH;

/// macro definition for the namespace
#define XIMOL_DOM_NAMESPACE       dom
#define XIMOL_DOM_NAMESPACE_PATH  XIMOL_NAMESPACE_PATH::XIMOL_DOM_NAMESPACE
#define XIMOL_DOM_BEGIN_NAMESPACE XIMOL_BEGIN_NAMESPACE namespace XIMOL_DOM_NAMESPACE {
#define XIMOL_DOM_END_NAMESPACE   }; XIMOL_END_NAMESPACE
#define XIMOL_DOM_USING_NAMESPACE using namespace XIMOL_DOM_NAMESPACE_PATH;

/** The ximol namespace. 
 *  All functions and class related to ximol are in this namespace.
 */
XIMOL_BEGIN_NAMESPACE

/// Namespace for all XiMoL Interface functions.
namespace XIMOL_XML_NAMESPACE {
};

/// Namespace for all XiMoL Interface functions.
namespace XIMOL_PARSER_NAMESPACE {
};

/// Namespace for all XiMoL encoders functions.
namespace XIMOL_ENCODERS_NAMESPACE {
};

/// Namespace for all XiMoL datatype.
namespace XIMOL_DATATYPES_NAMESPACE {
};

/// Namespace for all XiMoL datatype.
namespace XIMOL_FACET_NAMESPACE {
};

/// Namespace for all XiMoL DOM.
namespace XIMOL_DOM_NAMESPACE {
};

XIMOL_END_NAMESPACE

#endif // #ifndef XIMOL_NAMESPACE_DEFS_HPP_
