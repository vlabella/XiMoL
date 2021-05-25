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
	\brief Facet access declaration.
    All function about facet encoding are in this file. We use the libiconv
    librairie for the encoding.

	@ingroup encoders

	\author Tournois Florent
	\version 1.0

    $Id: encoders.hpp,v 1.2 2005/05/13 00:05:24 vlabella Exp $
    $Log: encoders.hpp,v $
    Revision 1.2  2005/05/13 00:05:24  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:40  vlabella
    adding in ximol and xmlparser

    Revision 1.14  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.13  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.12  2004/01/27 21:49:52  tournois
    Add docs and tutorial.

    Revision 1.11  2004/01/25 17:32:17  tournois
    no message

    Revision 1.10  2003/11/18 18:54:51  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.9  2003/11/15 22:52:57  tournois
    Add somes function arround attributes and tests for attributes.

    Revision 1.8  2003/11/14 15:44:05  tournois
    Add some comments.

    Revision 1.7  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.6  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.5  2003/10/13 21:01:20  tournois
    no message

    Revision 1.4  2003/10/09 16:59:45  tournois
    add the stringstream initialisation.
    add some prolog test.
    Correct code for VC6.0.

    Revision 1.3  2003/10/03 17:29:41  tournois
    no message

    Revision 1.2  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_ENCODERS_XIMOL_ENCODERS_HPP_
#define XIMOL_ENCODERS_XIMOL_ENCODERS_HPP_

#include <config.hpp>
#include <typedefs.hpp>
#include <macros.hpp>

#include <locale>

XIMOL_ENCODERS_BEGIN_NAMESPACE 

//-----------------------------------------------------------------------------
/** Interface for the ximol_encoders.
 *  This interface is based on libiconv 1-8.
 *	The memory must be freed. If you use the imbue method with the result, 
 *	you must not free the memory.
 *
 *	Here is the list of all supported encoding (from the libiconv manual):
 *
 *		\li \b European languages 
 *			ASCII, ISO-8859-{1,2,3,4,5,7,9,10,13,14,15,16}, KOI8-R, KOI8-U, KOI8-RU, CP{1250,1251,1252,1253,1254,1257}, CP{850,866}, Mac{Roman,CentralEurope,Iceland,Croatian,Romania}, Mac{Cyrillic,Ukraine,Greek,Turkish}, Macintosh 
 *		\li \b Semitic languages 
 *			ISO-8859-{6,8}, CP{1255,1256}, CP862, Mac{Hebrew,Arabic} 
 *		\li \b Japanese 
 *			EUC-JP, SHIFT_JIS, CP932, ISO-2022-JP, ISO-2022-JP-2, ISO-2022-JP-1 
 *		\li \b Chinese 
 *			EUC-CN, HZ, GBK, GB18030, EUC-TW, BIG5, CP950, BIG5-HKSCS, ISO-2022-CN, ISO-2022-CN-EXT 
 *		\li \b Korean 
 *			EUC-KR, CP949, ISO-2022-KR, JOHAB 
 *		\li \b Armenian 
 *			ARMSCII-8 
 *		\li \b Georgian 
 *			Georgian-Academy, Georgian-PS 
 *		\li \b Tajik 
 *			KOI8-T 
 *		\li \b Thai 
 *			TIS-620, CP874, MacThai 
 *		\li \b Laotian 
 *			MuleLao-1, CP1133 
 *		\li \b Vietnamese 
 *			VISCII, TCVN, CP1258 
 *		\li \b Platform specifics 
 *			HP-ROMAN8, NEXTSTEP 
 *		\li \b Full Unicode 
 *			UTF-8 
 *			UCS-2, UCS-2BE, UCS-2LE 
 *			UCS-4, UCS-4BE, UCS-4LE 
 *			UTF-16, UTF-16BE, UTF-16LE 
 *			UTF-32, UTF-32BE, UTF-32LE 
 *			UTF-7 
 *			C99, JAVA 
 *		\li \b European languages 
 *			CP{437,737,775,852,853,855,857,858,860,861,863,865,869,1125}
 *		\li \b Semitic languages 
 *			CP864 
 *		\li \b Japanese 
 *			EUC-JISX0213, Shift_JISX0213, ISO-2022-JP-3 
 *		\li \b Turkmen 
 *			TDS565 
 *		\li \b Platform specifics 
 *			RISCOS-LATIN1 
 *
 *	@param encoding_name : the encoding name from the list above.
 *	@return ::std::codecvt<xchar_t, char, mbstate_t>* : NULL or the codecvt facet pointer.
 * 	@ingroup encoders
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
::std::codecvt<xchar_t, char, mbstate_t> *
get_ximol_facet(::std::string const & encoding_name);

//-----------------------------------------------------------------------------
/** place with new placement operator (difficult to use).
 *  @ingroup encoders
 *	@warning This function is only here for expert.
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
void
place_ximol_facet(::std::codecvt<xchar_t, char, mbstate_t>* placement, 
                  ::std::string const & encoding_name);

//-----------------------------------------------------------------------------
/** Change encoding on a unique facet.
 *  @ingroup encoders
 *	This function change the encoding on the facet.
 *  If the facet is not a ximol facet then an exception is raise.
 *  If facet is NULL then nothing is done.
 *  
 *  @exception encoders::error
 *  @param facet : the ximol facet
 *  @param encoding_name : the standard encoding name
 *  @see use_xml, prepare_ios
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
void
change_ximol_facet_encoding(::std::codecvt<xchar_t, char, mbstate_t> * facet, 
                            ::std::string const & encoding_name);

//-----------------------------------------------------------------------------
/** Change the encoding method for the stream.
 *  @ingroup encoders
 *  \warning This function work if the ios have already a ximol facet.
 *  If you do not know the nature of the facet, you could use the prepare_ios.
 *  The facet will be change.
 *
 *  If there is not any ximol facet then the function raise an exception.
 * 
 *  @exception encoders::error
 *  @param ios : the ios in reference
 *  @param encoding_name : the standard encoding name
 *  @see use_xml, prepare_ios
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
void deep_change(::std::basic_ios<xchar_t> & ios, 
				 ::std::string const & encoding_name);

//-----------------------------------------------------------------------------
/** prepare ios.
 *  @ingroup encoders
 *  put a ximol facet to the ios. 
 *  This is a low-level function, and you should consider to use 
 *  the use_xml function. 
 * 
 *  The default encoding name is "UTF-8". You could change the default encoding
 *  name at compile time with the macro XIMOL_DEFAULT_ENCODING.
 *  
 *  @param ios : the ios in reference
 *  @param encoding_name : the standard encoding name
 *  @see use_xml, XIMOL_DEFAULT_ENCODING
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
void prepare_ios(::std::basic_ios<xchar_t> & ios, 
                 ::std::string const & encoding_name = XIMOL_DEFAULT_ENCODING);

//-----------------------------------------------------------------------------
/** test ios.
 *  @ingroup encoders
 *  Test if the ximol facet is set on the stream. This function is only 
 *  interessting for test.
 * 
 *  In normal condition we have \code test_ios(xstream)==true \endcode
 * 
 *  @param ios : the ios in reference.
 *  @return : true if the ximol facet is set and false otherwise.
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool test_ios(::std::basic_ios<xchar_t> & ios);

XIMOL_ENCODERS_END_NAMESPACE 

#endif // #ifndef XIMOL_ENCODERS_XIMOL_ENCODERS_HPP_