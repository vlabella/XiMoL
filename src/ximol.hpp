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
	\brief Include include all ximol headers.
    A common header for easier include.

    \author Tournois Florent
	\version 1.0

    $Id: ximol.hpp,v 1.5 2009/12/31 14:33:21 vlabella Exp $
    $Log: ximol.hpp,v $
    Revision 1.5  2009/12/31 14:33:21  vlabella
    commit in makefile
    Committed on the Free edition of March Hare Software CVSNT Server.
    Upgrade to CVS Suite for more features and support:
    http://march-hare.com/cvsnt/

    Revision 1.4  2009/12/30 22:12:04  vlabella
    commit in makefile
    Committed on the Free edition of March Hare Software CVSNT Server.
    Upgrade to CVS Suite for more features and support:
    http://march-hare.com/cvsnt/

    Revision 1.3  2009/12/17 22:02:23  vlabella
    commit in makefile
    Committed on the Free edition of March Hare Software CVSNT Server.
    Upgrade to CVS Suite for more features and support:
    http://march-hare.com/cvsnt/

    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.2  2005/05/12 16:01:21  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.15  2004/05/27 20:24:01  tournois
    no message

    Revision 1.14  2004/02/22 10:27:33  tournois
    Add some doc.

    Revision 1.13  2004/02/22 09:54:19  tournois
    Change years on the copyright.

    Revision 1.12  2004/01/29 20:52:35  tournois
    doc and tutorial.

    Revision 1.11  2004/01/26 20:44:19  tournois
    no message

    Revision 1.10  2004/01/22 22:06:53  tournois
    no message

    Revision 1.9  2004/01/07 21:13:10  tournois
    no message

    Revision 1.8  2004/01/06 21:04:10  tournois
    no message

    Revision 1.7  2003/12/03 13:36:13  hfp
    include dependencies and type forwarding

    Revision 1.6  2003/12/03 13:21:58  hfp
    include dependencies and type forwarding

    Revision 1.5  2003/11/18 18:54:51  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.4  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.3  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.2  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_HPP_
#define XIMOL_HPP_
#include <str_cast.hpp>
#include <fstream.hpp>
#include <datatypes/blob.hpp>
#include <sstream.hpp>
#include <zipstream.hpp>
#include <error.hpp>
#include <io.hpp>
#include <xml/attributes.hpp>
#include <xml/box.hpp>
#include <xml/cdata.hpp>
#include <xml/comment.hpp>
#include <xml/content.hpp>
#include <xml/blobcontent.hpp>
#include <xml/etag.hpp>
#include <xml/open_stag.hpp>
#include <xml/prolog.hpp>
#include <xml/reader.hpp>
#include <xml/stag.hpp>
#include <xml/xml_decl.hpp>
#include <control_flow.hpp>
#endif // #ifndef XIMOL_HPP_
