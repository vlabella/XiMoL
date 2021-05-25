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

/** \page faq Frequently Asked Questions (FAQs)

\section whyNotDom Why XiMoL is not really a DOM parser ? 

There is no data object model defined by the library.<br>
When you load your XML file, you use only your data structure and not your data structure and the DOM structure.<br>

\section whyNotSax Why XiMoL is not really a SAX parser ? 
There is nothing like event handler.<br>

\section whyDom Why XiMoL is close to a DOM parser? 
XiMoL is close to the Object model.<br>

\section WhySax Why XiMoL is close to a SAX parser ?
For a huge file, you could only choose an element.<br>

\section faq-char Which character encoding are managed by XiMoL ?

We use the standard wchar and libiconv for the conversion. This library is wrapped in the class codecvt_ximol 
derived from the ::std::codecvt<wchar_t, char, mbstate_t>. 	
Here is the list of all supported encoding (from the libiconv manual):

		\li \b European languages 
			ASCII, ISO-8859-{1,2,3,4,5,7,9,10,13,14,15,16}, KOI8-R, KOI8-U, KOI8-RU, CP{1250,1251,1252,1253,1254,1257}, CP{850,866}, Mac{Roman,CentralEurope,Iceland,Croatian,Romania}, Mac{Cyrillic,Ukraine,Greek,Turkish}, Macintosh 
		\li \b Semitic languages 
			ISO-8859-{6,8}, CP{1255,1256}, CP862, Mac{Hebrew,Arabic} 
		\li \b Japanese 
			EUC-JP, SHIFT_JIS, CP932, ISO-2022-JP, ISO-2022-JP-2, ISO-2022-JP-1 
		\li \b Chinese 
			EUC-CN, HZ, GBK, GB18030, EUC-TW, BIG5, CP950, BIG5-HKSCS, ISO-2022-CN, ISO-2022-CN-EXT 
		\li \b Korean 
			EUC-KR, CP949, ISO-2022-KR, JOHAB 
		\li \b Armenian 
			ARMSCII-8 
		\li \b Georgian 
			Georgian-Academy, Georgian-PS 
		\li \b Tajik 
			KOI8-T 
		\li \b Thai 
			TIS-620, CP874, MacThai 
		\li \b Laotian 
			MuleLao-1, CP1133 
		\li \b Vietnamese 
			VISCII, TCVN, CP1258 
		\li \b Platform specifics 
			HP-ROMAN8, NEXTSTEP 
		\li \b Full Unicode 
			UTF-8 
			UCS-2, UCS-2BE, UCS-2LE 
			UCS-4, UCS-4BE, UCS-4LE 
			UTF-16, UTF-16BE, UTF-16LE 
			UTF-32, UTF-32BE, UTF-32LE 
			UTF-7 
			C99, JAVA 
		\li \b European languages 
			CP{437,737,775,852,853,855,857,858,860,861,863,865,869,1125}
		\li \b Semitic languages 
			CP864 
		\li \b Japanese 
			EUC-JISX0213, Shift_JISX0213, ISO-2022-JP-3 
		\li \b Turkmen 
			TDS565 
		\li \b Platform specifics 
			RISCOS-LATIN1 

*/
