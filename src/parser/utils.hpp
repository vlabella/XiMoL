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
	\brief All parser functions declarations.
	
	\author Tournois Florent
	\version 1.0

    $Id: utils.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: utils.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.11  2004/08/05 16:49:44  tournois
    no message

    Revision 1.10  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.9  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.8  2004/01/09 18:26:29  tournois
    Add box and content manipulator.

    Revision 1.7  2003/11/27 15:31:55  hfp
    partially adapted to vc6.

    Revision 1.6  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.5  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.4  2003/10/25 13:53:40  hfp
    review and separation

    Revision 1.3  2003/10/08 19:59:35  tournois
    no message

    Revision 1.2  2003/09/27 22:49:34  tournois
    add the UTF-7 BOM.
    UTF-7 files can have a BOM too: 2B 2F 76 38 2D (ASCII +/v8-).

    Revision 1.1  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_PARSER_UTILS_HPP_
#define XIMOL_PARSER_UTILS_HPP_

#include <typedefs.hpp>
#include <config.hpp>


// forwarded declarations
XIMOL_BEGIN_NAMESPACE
	class xostream;
	class xistream;
XIMOL_END_NAMESPACE

XIMOL_XML_BEGIN_NAMESPACE
	class attributes;
XIMOL_XML_END_NAMESPACE


XIMOL_PARSER_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
/** Put a char in the stream
 *  Do not use this function.
 *  @param xos : the output stream
 *  @param xc : the charater
 */
//-----------------------------------------------------------------------------
XIMOL_DECL void write_xchar(xostream& xos, xchar_t xc);

//-----------------------------------------------------------------------------
/** read Special char.
 *  @ingroup parser_read 
 *  read the first char from the stream and throw an error if this char is not
 *  xc
 *  @param xis : the input stream
 *  @param xc : the waited charater
 *  @param error_msg : the error message
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_xchar(xistream& xis, 
						  xchar_t xc, 
						  const ::std::wstring & error_msg = L"");

//-----------------------------------------------------------------------------
/** read Char defined by a function.
 *  @ingroup parser_read 
 *  read a character defined by a function. This function test if 
 *  the character is valid.
 *
 *  @param xis : the input stream
 *  @param xc : the readed character in return
 *  @param is_good_xchar : the test function that define a set of character
 *  @param error_msg : the error message
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_xchar(xistream& xis, 
						  xchar_t & xc,
						  bool (*is_good_xchar)(xchar_t),
						  const ::std::wstring & error_msg = L"");

//-----------------------------------------------------------------------------
/** read string defined by a function.
 *  @ingroup parser_read 
 *  read char x from input until is_good_xchar(x)==false
 *  
 *  @param xis : the input stream
 *  @param xstr : the readed string in return
 *  @param is_good_xchar : the test function that define a set of character
 *  @param erase_string : true if you want to erase the string before reading.
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_xstring(xistream& xis, 
						    xstring & xstr,
						    bool (*is_good_xchar)(xchar_t),
							bool erase_string = true);

//-----------------------------------------------------------------------------
/** Test string defined by a function.
 *  @ingroup parser_is 
 *  Test if each char of the string return true with the function.
 * 
 *  @param xstr : the string to test
 *  @param is_good_xchar : the test function that define a set of character
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_xstring(xstring const & xstr, bool (*is_good_xchar)(xchar_t));

//-----------------------------------------------------------------------------
/** read Special string.
 *  @ingroup parser_read 
 *  read a constant string and verifie the exact math
 * 
 *  @param xis : the input stream
 *  @param xstr : the constant string to verifie
 *  @param error_msg : the error message
 *  @param nb_read : number of character already verifie.
 */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_xstring(xistream& xistream_, const ::std::string& str_,
					   const ::std::wstring& strErrorMsg_ = L"",
					   size_t size_ = 0);

//-----------------------------------------------------------------------------
/// write a ForbiddenSerie
/** @ingroup parser_write
	ForbiddenSerie    ::=    SetByFunction - (SetByFunction forbidden_string SetByFunction) 

    @param xos : the ouput stream.
	@param xstr : the string to write
	@param is_good_xchar : function for testing char
    @param forbidden_string :  the forbidden string
	@param entity_test : name of the tested string (for example : "CharData"). For error message.
	@param entity_definition : Definition For error message. (for example : "CharData    ::=    [^<&]* - ([^<&]* ']]>' [^<&]*)").
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_string_with_forbidden_serie(xostream& xos, 
									        xstring const & xstr,
									        bool (*is_good_xchar)(xchar_t),
									        const ::std::string& forbidden_string,
									        const ::std::string& entity_test,
									        const ::std::string& entity_definition);

//-----------------------------------------------------------------------------
/// read a ForbiddenSerie
/** @ingroup parser_read
	ForbiddenSerie    ::=    SetByFunction - (SetByFunction forbidden_string SetByFunction) 
	the reading is stop by the last char of the forbidden string 
	and we putback only the last char of this forbidden string.
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_string_with_forbidden_serie(xistream& xis, 
                                           xstring & xstr,
                                           bool (*is_good_xchar)(xchar_t),
                                           const ::std::string& forbidden_string);

//-----------------------------------------------------------------------------
/// test ForbiddenSerie
/** @ingroup parser_test
	ForbiddenSerie    ::=    SetByFunction - (SetByFunction forbidden_string SetByFunction) 
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_string_with_forbidden_serie(xstring const & xstr,
                                    bool (*is_good_xchar)(xchar_t),
                                    const ::std::string& forbidden_string);

//-----------------------------------------------------------------------------
/// test if a char is in the range.
/** @ingroup parser_is
	test if lower <= c <= upper
   
    @param c : char to test
    @param lower : lower bound
    @param upper : upper bound
   
    @return bool  : result (lower <= c <= upper)
*/
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_in_range(xchar_t c, xchar_t lower, xchar_t upper);

//-----------------------------------------------------------------------------
/// test if a char is a space.
/** @ingroup parser_is
	White Space
<pre>
    S    ::=    (#x20 | #x9 | #xD | #xA)
</pre>
*/
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_space(xchar_t c);

//-----------------------------------------------------------------------------
/// test if a char is a digit.
/** @ingroup parser_is
<pre>
	Digit    ::=    [#x0030-#x0039] 
                  | [#x0660-#x0669] 
				  | [#x06F0-#x06F9] 
				  | [#x0966-#x096F] 
				  | [#x09E6-#x09EF] 
				  | [#x0A66-#x0A6F] 
				  | [#x0AE6-#x0AEF] 
				  | [#x0B66-#x0B6F] 
				  | [#x0BE7-#x0BEF] 
				  | [#x0C66-#x0C6F] 
				  | [#x0CE6-#x0CEF] 
				  | [#x0D66-#x0D6F] 
				  | [#x0E50-#x0E59] 
				  | [#x0ED0-#x0ED9] 
				  | [#x0F20-#x0F29] 
</pre>
*/
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_digit(xchar_t c);

//-----------------------------------------------------------------------------
/// test if a char is a XML char.
/** @ingroup parser_is
<pre>
	Char    ::=    #x9 | #xA | #xD | [#x20-#xD7FF] | [#xE000-#xFFFD] 
                 | [#x10000-#x10FFFF]  
</pre>
*/
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_char(xchar_t c);

//-----------------------------------------------------------------------------
/// test if a char is a letter.
/** @ingroup parser_is
<pre>
	Letter    ::=    BaseChar | Ideographic 
</pre>
*/
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_letter(xchar_t c);

//-----------------------------------------------------------------------------
/// test if a char is a combining char.
/** @ingroup parser_is
<pre>
	CombiningChar    ::=  [#x0300-#x0345] | [#x0360-#x0361] | [#x0483-#x0486] 
                        | [#x0591-#x05A1] | [#x05A3-#x05B9] | [#x05BB-#x05BD] 
						| #x05BF | [#x05C1-#x05C2] | #x05C4 | [#x064B-#x0652] 
						| #x0670 | [#x06D6-#x06DC] | [#x06DD-#x06DF] 
						| [#x06E0-#x06E4] | [#x06E7-#x06E8] | [#x06EA-#x06ED] 
						| [#x0901-#x0903] | #x093C | [#x093E-#x094C] | #x094D 
						| [#x0951-#x0954] | [#x0962-#x0963] | [#x0981-#x0983] 
						| #x09BC | #x09BE | #x09BF | [#x09C0-#x09C4] 
						| [#x09C7-#x09C8] | [#x09CB-#x09CD] | #x09D7 
						| [#x09E2-#x09E3] | #x0A02 | #x0A3C | #x0A3E | #x0A3F 
						| [#x0A40-#x0A42] | [#x0A47-#x0A48] | [#x0A4B-#x0A4D] 
						| [#x0A70-#x0A71] | [#x0A81-#x0A83] | #x0ABC 
						| [#x0ABE-#x0AC5] | [#x0AC7-#x0AC9] | [#x0ACB-#x0ACD] 
						| [#x0B01-#x0B03] | #x0B3C | [#x0B3E-#x0B43] 
						| [#x0B47-#x0B48] | [#x0B4B-#x0B4D] | [#x0B56-#x0B57] 
						| [#x0B82-#x0B83] | [#x0BBE-#x0BC2] | [#x0BC6-#x0BC8] 
						| [#x0BCA-#x0BCD] | #x0BD7 | [#x0C01-#x0C03] 
						| [#x0C3E-#x0C44] | [#x0C46-#x0C48] | [#x0C4A-#x0C4D] 
						| [#x0C55-#x0C56] | [#x0C82-#x0C83] | [#x0CBE-#x0CC4] 
						| [#x0CC6-#x0CC8] | [#x0CCA-#x0CCD] | [#x0CD5-#x0CD6] 
						| [#x0D02-#x0D03] | [#x0D3E-#x0D43] | [#x0D46-#x0D48] 
						| [#x0D4A-#x0D4D] | #x0D57 | #x0E31 | [#x0E34-#x0E3A] 
						| [#x0E47-#x0E4E] | #x0EB1 | [#x0EB4-#x0EB9] 
						| [#x0EBB-#x0EBC] | [#x0EC8-#x0ECD] | [#x0F18-#x0F19] 
						| #x0F35 | #x0F37 | #x0F39 | #x0F3E | #x0F3F 
						| [#x0F71-#x0F84] | [#x0F86-#x0F8B] | [#x0F90-#x0F95] 
						| #x0F97 | [#x0F99-#x0FAD] | [#x0FB1-#x0FB7] | #x0FB9 
						| [#x20D0-#x20DC] | #x20E1 | [#x302A-#x302F] | #x3099 
						| #x309A 
</pre>
*/
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_combining_char(xchar_t c);

//-----------------------------------------------------------------------------
/// test if a char is a base char.
/** @ingroup parser_is
<pre>
	BaseChar    ::=    [#x0041-#x005A] | [#x0061-#x007A] | [#x00C0-#x00D6] 
                     | [#x00D8-#x00F6] | [#x00F8-#x00FF] | [#x0100-#x0131] 
					 | [#x0134-#x013E] | [#x0141-#x0148] | [#x014A-#x017E] 
					 | [#x0180-#x01C3] | [#x01CD-#x01F0] | [#x01F4-#x01F5] 
					 | [#x01FA-#x0217] | [#x0250-#x02A8] | [#x02BB-#x02C1] 
					 | #x0386 | [#x0388-#x038A] | #x038C | [#x038E-#x03A1] 
					 | [#x03A3-#x03CE] | [#x03D0-#x03D6] | #x03DA | #x03DC 
					 | #x03DE | #x03E0 | [#x03E2-#x03F3] | [#x0401-#x040C] 
					 | [#x040E-#x044F] | [#x0451-#x045C] | [#x045E-#x0481] 
					 | [#x0490-#x04C4] | [#x04C7-#x04C8] | [#x04CB-#x04CC] 
					 | [#x04D0-#x04EB] | [#x04EE-#x04F5] | [#x04F8-#x04F9] 
					 | [#x0531-#x0556] | #x0559 | [#x0561-#x0586] 
					 | [#x05D0-#x05EA] | [#x05F0-#x05F2] | [#x0621-#x063A] 
					 | [#x0641-#x064A] | [#x0671-#x06B7] | [#x06BA-#x06BE] 
					 | [#x06C0-#x06CE] | [#x06D0-#x06D3] | #x06D5 
					 | [#x06E5-#x06E6] | [#x0905-#x0939] | #x093D 
					 | [#x0958-#x0961] | [#x0985-#x098C] | [#x098F-#x0990] 
					 | [#x0993-#x09A8] | [#x09AA-#x09B0] | #x09B2 
					 | [#x09B6-#x09B9] | [#x09DC-#x09DD] | [#x09DF-#x09E1] 
					 | [#x09F0-#x09F1] | [#x0A05-#x0A0A] | [#x0A0F-#x0A10] 
					 | [#x0A13-#x0A28] | [#x0A2A-#x0A30] | [#x0A32-#x0A33] 
					 | [#x0A35-#x0A36] | [#x0A38-#x0A39] | [#x0A59-#x0A5C] 
					 | #x0A5E | [#x0A72-#x0A74] | [#x0A85-#x0A8B] | #x0A8D 
					 | [#x0A8F-#x0A91] | [#x0A93-#x0AA8] | [#x0AAA-#x0AB0] 
					 | [#x0AB2-#x0AB3] | [#x0AB5-#x0AB9] | #x0ABD | #x0AE0 
					 | [#x0B05-#x0B0C] | [#x0B0F-#x0B10] | [#x0B13-#x0B28] 
					 | [#x0B2A-#x0B30] | [#x0B32-#x0B33] | [#x0B36-#x0B39] 
					 | #x0B3D | [#x0B5C-#x0B5D] | [#x0B5F-#x0B61] 
                     | [#x0B85-#x0B8A] | [#x0B8E-#x0B90] | [#x0B92-#x0B95] 
					 | [#x0B99-#x0B9A] | #x0B9C | [#x0B9E-#x0B9F] 
					 | [#x0BA3-#x0BA4] | [#x0BA8-#x0BAA] | [#x0BAE-#x0BB5] 
                     | [#x0BB7-#x0BB9] | [#x0C05-#x0C0C] | [#x0C0E-#x0C10] 
                     | [#x0C12-#x0C28] | [#x0C2A-#x0C33] | [#x0C35-#x0C39] 
					 | [#x0C60-#x0C61] | [#x0C85-#x0C8C] | [#x0C8E-#x0C90] 
					 | [#x0C92-#x0CA8] | [#x0CAA-#x0CB3] | [#x0CB5-#x0CB9] 
					 | #x0CDE | [#x0CE0-#x0CE1] | [#x0D05-#x0D0C] 
					 | [#x0D0E-#x0D10] | [#x0D12-#x0D28] 
                     | [#x0D2A-#x0D39] | [#x0D60-#x0D61] 
					 | [#x0E01-#x0E2E] | #x0E30 | [#x0E32-#x0E33] 
					 | [#x0E40-#x0E45] | [#x0E81-#x0E82] | #x0E84 
					 | [#x0E87-#x0E88] | #x0E8A | #x0E8D | [#x0E94-#x0E97] 
					 | [#x0E99-#x0E9F] | [#x0EA1-#x0EA3] | #x0EA5 | #x0EA7 
                     | [#x0EAA-#x0EAB] | [#x0EAD-#x0EAE] | #x0EB0 
					 | [#x0EB2-#x0EB3] | #x0EBD | [#x0EC0-#x0EC4] 
					 | [#x0F40-#x0F47] | [#x0F49-#x0F69] | [#x10A0-#x10C5] 
					 | [#x10D0-#x10F6] | #x1100 | [#x1102-#x1103] 
					 | [#x1105-#x1107] | #x1109 | [#x110B-#x110C] 
                     | [#x110E-#x1112] | #x113C | #x113E | #x1140 | #x114C 
					 | #x114E | #x1150 | [#x1154-#x1155] | #x1159 
					 | [#x115F-#x1161] | #x1163 | #x1165 | #x1167 | #x1169 
					 | [#x116D-#x116E] | [#x1172-#x1173] | #x1175 | #x119E 
					 | #x11A8 | #x11AB | [#x11AE-#x11AF] | [#x11B7-#x11B8] 
                     | #x11BA | [#x11BC-#x11C2] | #x11EB | #x11F0 | #x11F9 
					 | [#x1E00-#x1E9B] | [#x1EA0-#x1EF9] | [#x1F00-#x1F15] 
					 | [#x1F18-#x1F1D] | [#x1F20-#x1F45] | [#x1F48-#x1F4D] 
					 | [#x1F50-#x1F57] | #x1F59 | #x1F5B | #x1F5D 
					 | [#x1F5F-#x1F7D] | [#x1F80-#x1FB4] | [#x1FB6-#x1FBC] 
                     | #x1FBE | [#x1FC2-#x1FC4] | [#x1FC6-#x1FCC] 
					 | [#x1FD0-#x1FD3] | [#x1FD6-#x1FDB] | [#x1FE0-#x1FEC] 
					 | [#x1FF2-#x1FF4] | [#x1FF6-#x1FFC] | #x2126 
					 | [#x212A-#x212B] | #x212E | [#x2180-#x2182] 
					 | [#x3041-#x3094] | [#x30A1-#x30FA] | [#x3105-#x312C] 
                     | [#xAC00-#xD7A3] 
</pre>
*/
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_base_char(xchar_t c);

//-----------------------------------------------------------------------------
/// test if a char is a Ideographic.
/** @ingroup parser_is
<pre>
	Ideographic    ::=    [#x4E00-#x9FA5] | #x3007 | [#x3021-#x3029]  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_ideographic(xchar_t c);

//-----------------------------------------------------------------------------
/// test if a char is an extender.
/** @ingroup parser_is
<pre>
	Extender    ::=    #x00B7 | #x02D0 | #x02D1 | #x0387 | #x0640 | #x0E46 
      | #x0EC6 | #x3005 | [#x3031-#x3035] | [#x309D-#x309E] | [#x30FC-#x30FE]  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_extender(xchar_t c);

//-----------------------------------------------------------------------------
/// test if a char is a name character
/** @ingroup parser_is
<pre>
	NameChar    ::=    Letter | Digit | '.' | '-' | '_' | ':' | CombiningChar | Extender   
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_name_char(xchar_t c);

//-----------------------------------------------------------------------------
/// test if a char is a PubidChar
/** @ingroup parser_is
<pre>
	PubidChar    ::=    #x20 | #xD | #xA | [a-zA-Z0-9] | [-'()+,./:=?;!*#@$_%] 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_pubid_char(xchar_t c);

//-----------------------------------------------------------------------------
/// write a space
/** @ingroup parser_write
<pre>
	S ::= (x20 | x9 | xD | xA) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_space(xostream& xos);

//-----------------------------------------------------------------------------
/// read one or more spaces
/** @ingroup parser_read
<pre>
	S ::= (x20 | x9 | xD | xA) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_space(xistream& xis);

//-----------------------------------------------------------------------------
/// read zero or more spaces
/** @ingroup parser_read
<pre>
	S ::= (x20 | x9 | xD | xA) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_optionnal_space(xistream& xis);

//-----------------------------------------------------------------------------
/// write a name
/** @ingroup parser_write
<pre>
	name    ::=    (Letter | '_' | ':') (NameChar)* 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_name(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a name
/** @ingroup parser_read
<pre>
	name    ::=    (Letter | '_' | ':') (NameChar)* 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_name(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// test name
/** @ingroup parser_is
<pre>
	name    ::=    (Letter | '_' | ':') (NameChar)* 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_name(xstring const & xstr);

//-----------------------------------------------------------------------------
/// write a NCName
/** @ingroup parser_write
<pre>
	NCName    ::=    (Letter | '_') (NCNameChar)* 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_ncname(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a NCName
/** @ingroup parser_read
<pre>
	NCName    ::=    (Letter | '_') (NCNameChar)* 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_ncname(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// test NCName
/** @ingroup parser_is
<pre>
	NCName    ::=    (Letter | '_') (NCNameChar)* 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_ncname(xstring const & xstr);

//-----------------------------------------------------------------------------
/// write a QName
/** @ingroup parser_write
<pre>
	QName ::=  (Prefix ':')? LocalPart 
	Prefix ::=  NCName 
	LocalPart ::=  NCName 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_qname(xostream& xos, xstring const & localPart, xstring const & prefix = xstring());

//-----------------------------------------------------------------------------
/// read a QName
/** @ingroup parser_read
<pre>
	QName ::=  (Prefix ':')? LocalPart 
	Prefix ::=  NCName 
	LocalPart ::=  NCName 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_qname(xistream& xis, xstring & localPart, xstring & prefix);

//-----------------------------------------------------------------------------
/// test QName
/** @ingroup parser_is
<pre>
	QName ::=  (Prefix ':')? LocalPart 
	Prefix ::=  NCName 
	LocalPart ::=  NCName 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_qname(xstring const & localPart, xstring const & prefix = xstring());

//-----------------------------------------------------------------------------
/// write a NSAttName
/** @ingroup parser_write
@param xstr : NCName.
<pre>
	NSAttName ::=  PrefixedAttName | DefaultAttName 
	PrefixedAttName ::=  'xmlns:' NCName
	DefaultAttName ::=  'xmlns' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_ns_att_name(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a NSAttName
/** @ingroup parser_read
@return only the NCName.
<pre>
	NSAttName ::=  PrefixedAttName | DefaultAttName 
	PrefixedAttName ::=  'xmlns:' NCName
	DefaultAttName ::=  'xmlns' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_ns_att_name(xistream& xis, xstring & xstr, int nb_read = 0);

//-----------------------------------------------------------------------------
/// test NSAttName
/** @ingroup parser_is
test only the NCName. In the Default case, NCName=="".
<pre>
	NSAttName ::=  PrefixedAttName | DefaultAttName 
	PrefixedAttName ::=  'xmlns:' NCName
	DefaultAttName ::=  'xmlns' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_ns_att_name(xstring const & xstr);

//-----------------------------------------------------------------------------
/// Test first char of a name
/** @ingroup parser_is
<pre>
	char    ::=    (Letter | '_' | ':') 
</pre>
  */ 
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_first_char_name(xchar_t xc);

//-----------------------------------------------------------------------------
/// Test first char of a name
/** @ingroup parser_is
<pre>
	char    ::=    (Letter | '_' ) 
</pre>
  */ 
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_first_char_ncname(xchar_t xc);

//-----------------------------------------------------------------------------
/// write a CharData
/** @ingroup parser_write
<pre>
	CharData    ::=    [^<&]* - ([^<&]* ']]>' [^<&]*) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_char_data(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a CharData
/** @ingroup parser_read
<pre>
	CharData    ::=    [^<&]* - ([^<&]* ']]>' [^<&]*) 
</pre>
	the reading is stop by '<' or '&' or ']]>' 
	and we putback only one char '<' or '&' or '>'
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_char_data(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// test CharData
/** @ingroup parser_is
<pre>
	CharData    ::=    [^<&]* - ([^<&]* ']]>' [^<&]*)  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_char_data(xstring const & xstr);

//-----------------------------------------------------------------------------
/// write a Nmtoken
/** @ingroup parser_write
<pre>
	Nmtoken    ::=    (NameChar)+  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_nm_token(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a Nmtoken
/** @ingroup parser_read
<pre>
	Nmtoken    ::=    (NameChar)+  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_nm_token(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// test Nmtoken
/** @ingroup parser_is
<pre>
	Nmtoken    ::=    (NameChar)+  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_nm_token(xstring const & xstr);

//-----------------------------------------------------------------------------
/// write a CharRef
/** @ingroup parser_write
<pre>
	CharRef    ::=    '&#' [0-9]+ ';'  
                    | '&#x' [0-9a-fA-F]+ ';' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_char_ref(xostream& xos, xchar_t xc);

//-----------------------------------------------------------------------------
/// read a CharRef
/** @ingroup parser_read
<pre>
	CharRef    ::=    '&#' [0-9]+ ';'  
                    | '&#x' [0-9a-fA-F]+ ';' 
</pre>
	if read_first_char==true then the char '&' is not read.
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_char_ref(xistream& xis, xchar_t & xc, int nb_read = 0);

//-----------------------------------------------------------------------------
/// replace all Charref in the string
/** @ingroup parser_read
<pre>
	CharRef    ::=    '&#' [0-9]+ ';'  
                    | '&#x' [0-9a-fA-F]+ ';' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xstring replace_char_ref(xstring const & xstr);

//-----------------------------------------------------------------------------
/// write a EntityRef
/** @ingroup parser_write
<pre>
	EntityRef    ::=    '&' name ';' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_entity_ref(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a EntityRef
/** @ingroup parser_read
<pre>
	EntityRef    ::=    '&' name ';' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_entity_ref(xistream& xis, int nb_read = 0);

//-----------------------------------------------------------------------------
/// write a PEReference
/** @ingroup parser_write
<pre>
	PEReference    ::=    '%' name ';'  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_pe_reference(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a PEReference
/** @ingroup parser_read
<pre>
	PEReference    ::=    '%' name ';'  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_pe_reference(xistream& xis, xstring & xstr, int nb_read = 0);

//-----------------------------------------------------------------------------
/// read a Reference
/** @ingroup parser_read
<pre>
	Reference    ::=    EntityRef | CharRef  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_reference(xistream& xis, xstring & xstr, int nb_read = 0);

//-----------------------------------------------------------------------------
/// write a pubid_literal
/** @ingroup parser_write
<pre>
	pubid_literal    ::=    '"' PubidChar* '"' | "'" (PubidChar - "'")* "'" 
	we use only the value without quote.  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_pubid_literal(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a pubid_literal
/** @ingroup parser_read
<pre>
	pubid_literal    ::=    '"' PubidChar* '"' | "'" (PubidChar - "'")* "'"   
</pre>
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_pubid_literal(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// write a system_literal
/** @ingroup parser_write
<pre>
	system_literal    ::=    ('"' [^"]* '"') | ("'" [^']* "'")  
</pre>
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_system_literal(xostream& xos, xstring const & xstr, xchar_t quote=0x0022);

//-----------------------------------------------------------------------------
/// read a system_literal
/** @ingroup parser_read
<pre>
	system_literal    ::=    ('"' [^"]* '"') | ("'" [^']* "'")    
</pre>
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_system_literal(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// write a entity_value
/** @ingroup parser_write
<pre>
	entity_value    ::=    '"' ([^%&"] | PEReference | Reference)* '"'  
                       |  "'" ([^%&'] | PEReference | Reference)* "'" 
</pre>
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_entity_value(xostream& xos, xstring const & xstr, xchar_t quote=0x0022);

//-----------------------------------------------------------------------------
/// read a entity_value
/** @ingroup parser_read
<pre>
	entity_value    ::=    '"' ([^%&"] | PEReference | Reference)* '"'  
                       |  "'" ([^%&'] | PEReference | Reference)* "'" 
</pre>
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_entity_value(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// write a AttValue
/** @ingroup parser_write
<pre>
	AttValue    ::=    '"' ([^<&"] | Reference)* '"'  
                    |  "'" ([^<&'] | Reference)* "'" 
</pre>
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_att_value(xostream& xos, xstring const & xstr, xchar_t quote=0x0022);

//-----------------------------------------------------------------------------
/// read a AttValue
/** @ingroup parser_read
<pre>
	AttValue    ::=    '"' ([^<&"] | Reference)* '"'  
                    |  "'" ([^<&'] | Reference)* "'" 
</pre>
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_att_value(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// write a Attribute
/** @ingroup parser_write
<pre>
	Attribute    ::=    name Eq AttValue  
</pre>
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_attribute(xostream& xos, xstring const & name, xstring const & att_value, xstring const & short_ns, xchar_t quote=0x0022);

//-----------------------------------------------------------------------------
/// read a Attribute
/** @ingroup parser_read
<pre>
	Attribute    ::=    name Eq AttValue 
</pre>
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_attribute(xistream& xis, xstring & name, xstring & att_value, xstring& short_ns);

//-----------------------------------------------------------------------------
/// Test comment
/** @ingroup parser_is
<pre>
	comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_comment(xstring const & xstr);

//-----------------------------------------------------------------------------
/// write a comment
/** @ingroup parser_write
<pre>
	comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_comment(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a comment
/** @ingroup parser_read
<pre>
	comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_comment(xistream& xis, xstring & xstr, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a comment
/** @ingroup parser_read
<pre>
	comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_comment(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// Test pi_target
/** @ingroup parser_is
<pre>
	pi_target    ::=    name - (('X' | 'x') ('M' | 'm') ('L' | 'l')) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_pi_target(xstring const & xstr);

//-----------------------------------------------------------------------------
/// write a pi_target
/** @ingroup parser_write
<pre>
	pi_target    ::=    name - (('X' | 'x') ('M' | 'm') ('L' | 'l')) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_pi_target(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a pi_target
/** @ingroup parser_read
<pre>
	pi_target    ::=    name - (('X' | 'x') ('M' | 'm') ('L' | 'l')) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_pi_target(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// write a PI
/** @ingroup parser_write
<pre>
	PI    ::=    '<?' pi_target (S (Char* - (Char* '?>' Char*)))? '?>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_pi(xostream& xos, xstring const & pi_target, xstring const & xext);

//-----------------------------------------------------------------------------
/// read a PI
/** @ingroup parser_read
<pre>
	PI    ::=    '<?' pi_target (S (Char* - (Char* '?>' Char*)))? '?>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_pi(xistream& xis, xstring & pi_target,xstring & xext, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a PI
/** @ingroup parser_read
<pre>
	PI    ::=    '<?' pi_target (S (Char* - (Char* '?>' Char*)))? '?>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_pi(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// write a cd_end
/** @ingroup parser_write
<pre>
	cd_end    ::=    ']]>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_cd_end(xostream& xos);

//-----------------------------------------------------------------------------
/// read a cd_end
/** @ingroup parser_read
<pre>
	cd_end    ::=    ']]>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_cd_end(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// write a cd_start
/** @ingroup parser_write
<pre>
	cd_start    ::=    '<![CDATA[' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_cd_start(xostream& xos);

//-----------------------------------------------------------------------------
/// read a cd_start
/** @ingroup parser_read
<pre>
	cd_start    ::=    '<![CDATA[' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_cd_start(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// write a CData
/** @ingroup parser_write
<pre>
	CData    ::=    (Char* - (Char* ']]>' Char*))  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_cdata(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a CData
/** @ingroup parser_read
<pre>
	CData    ::=    (Char* - (Char* ']]>' Char*))  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_cdata(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// write a cd_sect
/** @ingroup parser_write
<pre>
	cd_sect    ::=    cd_start CData cd_end 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_cd_sect(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a cd_sect
/** @ingroup parser_read
<pre>
	cd_sect    ::=    cd_start CData cd_end 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_cd_sect(xistream& xis, xstring & xstr, int nb_char=0);

//-----------------------------------------------------------------------------
/// write a Eq
/** @ingroup parser_write
<pre>
	Eq    ::=    S? '=' S?  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_eq(xostream& xos);

//-----------------------------------------------------------------------------
/// read a Eq
/** @ingroup parser_read
<pre>
	Eq    ::=    S? '=' S?  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_eq(xistream& xis);

//-----------------------------------------------------------------------------
/// Test VersionNum
/** @ingroup parser_is
<pre>
	VersionNum    ::=    ([a-zA-Z0-9_.:] | '-')+ 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_version_num(xstring const & xstr);

//-----------------------------------------------------------------------------
/// write a VersionNum
/** @ingroup parser_write
<pre>
	VersionNum    ::=    ([a-zA-Z0-9_.:] | '-')+ 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_version_num(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a VersionNum
/** @ingroup parser_read
<pre>
	VersionNum    ::=    ([a-zA-Z0-9_.:] | '-')+ 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_version_num(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// write a VersionInfo
/** @ingroup parser_write
<pre>
	VersionInfo    ::=    S 'version' Eq ("'" VersionNum "'" | '"' VersionNum '"')  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_version_info(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a VersionInfo
/** @ingroup parser_read
<pre>
	VersionInfo    ::=    S 'version' Eq ("'" VersionNum "'" | '"' VersionNum '"')  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_version_info(xistream& xis, xstring & xstr, bool read_first_space=true);

//-----------------------------------------------------------------------------
/// read a VersionInfo
/** @ingroup parser_read
<pre>
	VersionInfo    ::=    S 'version' Eq ("'" VersionNum "'" | '"' VersionNum '"')  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_version_info(xistream& xis, bool read_first_space=true);

//-----------------------------------------------------------------------------
/// Test EncName
/** @ingroup parser_is
<pre>
	EncName    ::=    [A-Za-z] ([A-Za-z0-9._] | '-')* 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
bool is_enc_name(xstring const & xstr);

//-----------------------------------------------------------------------------
/// write a EncName
/** @ingroup parser_write
<pre>
	EncName    ::=    [A-Za-z] ([A-Za-z0-9._] | '-')* 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_enc_name(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a EncName
/** @ingroup parser_read
<pre>
	EncName    ::=    [A-Za-z] ([A-Za-z0-9._] | '-')* 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_enc_name(xistream& xis, xstring & xstr);

//-----------------------------------------------------------------------------
/// write a EncodingDecl
/** @ingroup parser_write
<pre>
	EncodingDecl    ::=    S 'encoding' Eq ('"' EncName '"' | "'" EncName "'" ) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_encoding_decl(xostream& xos, xstring const & xstr);

//-----------------------------------------------------------------------------
/// read a EncodingDecl
/** @ingroup parser_read
<pre>
	EncodingDecl    ::=    S 'encoding' Eq ('"' EncName '"' | "'" EncName "'" ) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_encoding_decl(xistream& xis, xstring & xstr, bool read_first_space=true);

//-----------------------------------------------------------------------------
/// write a SDDecl
/** @ingroup parser_write
<pre>
	SDDecl    ::=    S 'standalone' Eq (("'" ('yes' | 'no') "'") | ('"' ('yes' | 'no') '"')) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_sd_decl(xostream& xos, bool standalone);

//-----------------------------------------------------------------------------
/// read a SDDecl
/** @ingroup parser_read
<pre>
	SDDecl    ::=    S 'standalone' Eq (("'" ('yes' | 'no') "'") | ('"' ('yes' | 'no') '"')) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_sd_decl(xistream& xis, bool & standalone, bool read_first_space=true);

//-----------------------------------------------------------------------------
/// write a XMLDecl
/** @ingroup parser_write
<pre>
	XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_xml_decl(xostream& xos, xstring const & version_info, xstring const & encoding_decl = L"", xstring const & standalone_decl = L"");

//-----------------------------------------------------------------------------
/// write a XMLDecl
/** @ingroup parser_write
<pre>
	XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_xml_decl(xostream& xos);

//-----------------------------------------------------------------------------
/// read a XMLDecl
/** @ingroup parser_read
<pre>
	XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_xml_decl(xistream& xis, xstring& version_info, xstring& encoding_decl, bool & standalone_decl, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a XMLDecl
/** @ingroup parser_read
<pre>
	XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_xml_decl(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// write a ExternalID
/** @ingroup parser_write
<pre>
	ExternalID    ::=    'SYSTEM' S system_literal | 'PUBLIC' S pubid_literal S system_literal  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_external_id(xostream& xos, xstring const & system_literal, xstring const & pub_id_literal=xstring());

//-----------------------------------------------------------------------------
/// read a ExternalID
/** @ingroup parser_read
<pre>
	ExternalID    ::=    'SYSTEM' S system_literal | 'PUBLIC' S pubid_literal S system_literal  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_external_id(xistream& xis, xstring& system_literal, xstring& pub_id_literal);

//-----------------------------------------------------------------------------
/// write a PublicID
/** @ingroup parser_write
<pre>
	PublicID    ::=    'PUBLIC' S pubid_literal 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_public_id(xostream& xos, xstring const & pub_id_literal);

//-----------------------------------------------------------------------------
/// read a PublicID
/** @ingroup parser_read
<pre>
	PublicID    ::=    'PUBLIC' S pubid_literal 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_public_id(xistream& xis, xstring& pub_id_literal);

//-----------------------------------------------------------------------------
/// write a NotationDecl
/** @ingroup parser_write
<pre>
	NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_notation_decl(xostream& xos, xstring const & name, xstring const & system_literal, xstring const & pub_id_literal);

//-----------------------------------------------------------------------------
/// read a NotationDecl
/** @ingroup parser_read
<pre>
	NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_notation_decl(xistream& xis, xstring& name, xstring& system_literal, xstring& pub_id_literal, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a NotationDecl
/** @ingroup parser_read
<pre>
	NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_notation_decl(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// write a PEDef
/** @ingroup parser_write
<pre>
	PEDef    ::=    entity_value | ExternalID 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_pe_def(xostream& xos, xstring const & entity_value, xstring const & system_literal, xstring const & pub_id_literal);

//-----------------------------------------------------------------------------
/// read a PEDef
/** @ingroup parser_read
<pre>
	PEDef    ::=    entity_value | ExternalID 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_pe_def(xistream& xis, xstring& entity_value, xstring& system_literal, xstring& pub_id_literal);

//-----------------------------------------------------------------------------
/// write an open stag
/** @ingroup parser_write
<pre>
	stag    ::=    '<' name (S Attribute)* S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_open_stag(xostream& xos, xstring const & name, const XIMOL_XML_NAMESPACE_PATH::attributes& att, xstring const & uri=xstring());

//-----------------------------------------------------------------------------
/// write an open stag
/** @ingroup parser_write
<pre>
	stag    ::=    '<' name (S Attribute)* S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_open_stag(xostream& xos, xstring const & name, xstring const & uri = xstring());

//-----------------------------------------------------------------------------
/// write a stag
/** @ingroup parser_write
<pre>
	stag    ::=    '<' QName (S Attribute)* S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_stag(xostream& xos, xstring const & name, const XIMOL_XML_NAMESPACE_PATH::attributes& att, xstring const & uri = xstring());

//-----------------------------------------------------------------------------
/// write a stag
/** @ingroup parser_write
<pre>
	stag    ::=    '<' QName (S Attribute)* S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_stag(xostream& xos, xstring const & name);

//-----------------------------------------------------------------------------
/// write a stag
/** @ingroup parser_write
<pre>
	stag    ::=    '<' QName (S Attribute)* S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_stag(xostream& xos, xstring const & name, xstring const & uri);

//-----------------------------------------------------------------------------
/// read an open stag
/** @ingroup parser_read
<pre>
	stag    ::=    '<' QName (S Attribute)* S? '>'  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_open_stag(xistream& xis, xstring& name, XIMOL_XML_NAMESPACE_PATH::attributes& att, xstring& uri, int nb_read=0);

//-----------------------------------------------------------------------------
/// read an open stag
/** @ingroup parser_read
<pre>
	stag    ::=    '<' QName (S Attribute)* S? '>'  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_open_stag(xistream& xis, xstring& name, xstring &uri, int nb_read=0);

//-----------------------------------------------------------------------------
/// read an open stag
/** @ingroup parser_read
<pre>
	stag    ::=    '<' QName (S Attribute)* S? '>'  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_open_stag(xistream& xis, xstring& name, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a stag
/** @ingroup parser_read
<pre>
	stag    ::=    '<' QName (S Attribute)* S? '>'  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_stag(xistream& xis, xstring& name, XIMOL_XML_NAMESPACE_PATH::attributes& att, xstring& uri, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a stag
/** @ingroup parser_read
<pre>
	stag    ::=    '<' QName (S Attribute)* S? '>'  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_stag(xistream& xis, xstring& name, XIMOL_XML_NAMESPACE_PATH::attributes& att, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a stag
/** @ingroup parser_read
<pre>
	stag    ::=    '<' QName (S Attribute)* S? '>'  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_stag(xistream& xis, xstring& name, xstring& uri, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a stag
/** @ingroup parser_read
<pre>
	stag    ::=    '<' QName (S Attribute)* S? '>'  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_stag(xistream& xis, xstring& name, int nb_read=0);

//-----------------------------------------------------------------------------
/// write a etag
/** @ingroup parser_write
<pre>
	etag    ::=    '</' name S? '>'
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_etag(xostream& xos, xstring const & name, xstring const & uri);

//-----------------------------------------------------------------------------
/// write a etag
/** @ingroup parser_write
<pre>
	etag    ::=    '</' name S? '>'
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_etag(xostream& xos, xstring const & name);

//-----------------------------------------------------------------------------
/// write a etag
/** @ingroup parser_write
<pre>
	etag    ::=    '</' name S? '>'
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_etag(xostream& xos);

//-----------------------------------------------------------------------------
/// read a etag
/** @ingroup parser_read
<pre>
	etag    ::=    '</' QName S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_etag(xistream& xis, xstring& name, xstring& uri, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a etag
/** @ingroup parser_read
<pre>
	etag    ::=    '</' QName S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_etag(xistream& xis, xstring& name, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a etag
/** @ingroup parser_read
<pre>
	etag    ::=    '</' QName S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_etag(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// write a NDataDecl
/** @ingroup parser_write
<pre>
	NDataDecl    ::=    S 'NDATA' S name 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_ndata_decl(xostream& xos, xstring const & name);

//-----------------------------------------------------------------------------
/// read a NDataDecl
/** @ingroup parser_read
<pre>
	NDataDecl    ::=    S 'NDATA' S name 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_ndata_decl(xistream& xis, xstring& name, int nb_read=0);

//-----------------------------------------------------------------------------
/// write a EntityDef
/** @ingroup parser_write
<pre>
	EntityDef    ::=    entity_value | (ExternalID NDataDecl?) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_entity_def(xostream& xos, xstring const & entity_value, xstring const & system_literal, xstring const & pub_id_literal, xstring const & ndata_name);

//-----------------------------------------------------------------------------
/// read a EntityDef
/** @ingroup parser_read
<pre>
	EntityDef    ::=    entity_value | (ExternalID NDataDecl?) 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_entity_def(xistream& xis, xstring& entity_value, xstring& system_literal, xstring& pub_id_literal, xstring& ndata_name);

//-----------------------------------------------------------------------------
/// write a PEDecl
/** @ingroup parser_write
<pre>
	PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_pe_decl(xostream& xos, xstring const & entity_name, xstring const & entity_value, xstring const & system_literal = L"", xstring const & pubid_literal = L"");

//-----------------------------------------------------------------------------
/// read a PEDecl
/** @ingroup parser_read
<pre>
	PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_pe_decl(xistream& xis, xstring& entity_name, xstring& entity_value, xstring& system_literal, xstring & pubid_literal, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a PEDecl
/** @ingroup parser_read
<pre>
	PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_pe_decl(xistream& xis,int nb_read=0);

//-----------------------------------------------------------------------------
/// write a GEDecl
/** @ingroup parser_write
<pre>
	GEDecl    ::=    '<!ENTITY' S name S EntityDef S? '>'  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_ge_decl(xostream& xos, xstring const & entity_name, xstring const & entity_value, xstring const & system_literal = L"", xstring const & pubid_literal = L"", xstring const & ndata_name = L"");

//-----------------------------------------------------------------------------
/// read a GEDecl
/** @ingroup parser_read
<pre>
	GEDecl    ::=    '<!ENTITY' S name S EntityDef S? '>'  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_ge_decl(xistream& xis, xstring& entity_name, xstring& entity_value, xstring& system_literal, xstring & pubid_literal, xstring & ndata_name, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a GEDecl
/** @ingroup parser_read
<pre>
	GEDecl    ::=    '<!ENTITY' S name S EntityDef S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_ge_decl(xistream& xis,int nb_read=0);

//-----------------------------------------------------------------------------
/// read Misc
/** @ingroup parser_read
<pre>
	Misc    ::=    comment | PI | S 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_misc(xistream& xis);

//-----------------------------------------------------------------------------
/// write a prolog
/** @ingroup parser_write
<pre>
	prolog    ::=    XMLDecl? Misc* (doctypedecl Misc*)? 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xostream& write_prolog(xostream& xos);

//-----------------------------------------------------------------------------
/// Byte Order Mark
/** @ingroup parser_read
    Finally, as a side note, and not of any importance, UTF-7 files can 
    have a BOM too: 2B 2F 76 38 2D
	@return number of xchar_t crunch. xchar_t of the '<?xml'
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
size_t read_bom(xistream& xis);

//-----------------------------------------------------------------------------
/// read a prolog question tag
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_prolog_question(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a prolog exclamation tag
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_prolog_exclamation(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// read doctype elements
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_doctype_element(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// read doctypedecl
/** @ingroup parser_read
<pre>
	doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_doctype_decl(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a prolog
/** @ingroup parser_read
<pre>
	prolog    ::=    XMLDecl? Misc* (doctypedecl Misc*)?  
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_prolog(xistream& xis);

//-----------------------------------------------------------------------------
/// read a elementdecl
/** @ingroup parser_read
	\todo write this function
<pre>
	elementdecl    ::=    '<!ELEMENT' S name S contentspec S? '>'   
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_element_decl(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a AttlistDecl
/** @ingroup parser_read
	\todo write this function
<pre>
	AttlistDecl    ::=    '<!ATTLIST' S name AttDef* S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_att_list_decl(xistream& xis, int nb_read=0);

//-----------------------------------------------------------------------------
/// read a EntityDecl
/** @ingroup parser_read
  <pre>
	EntityDecl    ::=    GEDecl | PEDecl    
</pre>
  */
//-----------------------------------------------------------------------------
XIMOL_DECL
xistream& read_entity_decl(xistream& xis, int nb_read=0);

XIMOL_PARSER_END_NAMESPACE

#endif // #ifndef XIMOL_PARSER_UTILS_HPP_
