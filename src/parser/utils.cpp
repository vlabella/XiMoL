/****************************************************************************\
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
/* \file 
	\brief All parser functions implementations.
	
	\author Tournois Florent
	\version 1.0

    $Id: utils.cpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: utils.cpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.24  2004/08/05 16:49:44  tournois
    no message

    Revision 1.23  2004/02/25 18:59:12  tournois
    imporve the gcc compatibility.

    Revision 1.22  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.21  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.20  2004/02/04 11:42:25  tournois
    no message

    Revision 1.19  2004/01/19 20:40:55  tournois
    Add min, max and digits facet.
    Create the control flow file.

    Revision 1.18  2004/01/07 12:16:36  tournois
    no message

    Revision 1.17  2003/12/10 20:32:18  tournois
    Fix somes bugs about attributes and now tests are all check.

    Revision 1.16  2003/12/09 19:57:27  tournois
    Fix some bugs about attributes classes.

    Revision 1.15  2003/12/04 14:34:34  hfp
    XIMOL_XML_NAMESPACE_PATH::attributes changed

    Revision 1.14  2003/11/27 15:31:55  hfp
    partially adapted to vc6.

    Revision 1.13  2003/11/19 20:52:54  tournois
    Add new manipulator for stag and etag.
    Correct bugs and add tests.

    Revision 1.12  2003/11/18 18:54:51  tournois
    Add str_cast and drop the transformation.hpp file.

    Revision 1.11  2003/11/17 22:06:01  tournois
    Add traits for relation stream--object.
    Change cast.

    Revision 1.10  2003/11/16 13:25:25  tournois
    Change the error to use wide string.
    Change the translation to use wide string.

    Revision 1.9  2003/11/14 11:45:04  tournois
    First try for the stag.

    Revision 1.8  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.7  2003/10/25 13:53:39  hfp
    review and separation

    Revision 1.6  2003/10/15 19:06:07  tournois
    Correct some bug arround the beforeBOM and afterBOM.

    Revision 1.5  2003/10/13 21:02:00  tournois
    no message

    Revision 1.4  2003/10/09 16:59:45  tournois
    add the stringstream initialisation.
    add some prolog test.
    Correct code for VC6.0.

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
#include <parser/utils.hpp>
#include <str_cast.hpp>
#include <parser/def_signs.hpp>
#include <encoders/encoders.hpp>
#include <translation.hpp>
#include <sstream.hpp>
#include <error.hpp>
#include <io.hpp>

#define XBET(lower,upper) ( ((xchar_t)lower <= c) && (c <= (xchar_t)upper) )
#define XEQ(val) ((xchar_t)val == c)


XIMOL_PARSER_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
// Put a char in the stream
//-----------------------------------------------------------------------------
void write_xchar(xostream& xos, xchar_t xc)
{
	xos.rdbuf()->sputc(xc);
}

//-----------------------------------------------------------------------------
// Clear the string
//-----------------------------------------------------------------------------
template <class T>
void clear_string(T &xstr)
{
	if (!xstr.empty()) xstr.erase(xstr.begin(),xstr.end()); 
}

//-----------------------------------------------------------------------------
// read Special char.
//-----------------------------------------------------------------------------
xistream& read_xchar(xistream& xis, 
				   xchar_t xc, 
				   const ::std::wstring & error_msg)
{
	xchar_t xc_read;
	if ( (xis.get(xc_read)) && (xc==xc_read) ) return xis;
	
	//failed
	xis.setstate(std::ios::failbit); 
	XIMOL_THROW << _xtr(L"Reading this char '%o' and waiting for this char '%o'. ",(char)(xc_read),(char)(xc)) 
			    << error_msg << XIMOL_AS_ERROR;
	return xis; 
}

//-----------------------------------------------------------------------------
// read Char defined by a function.
//-----------------------------------------------------------------------------
xistream& read_xchar(xistream& xis, 
				   xchar_t & xc,
				   bool (*is_good_xchar)(xchar_t),
				   const ::std::wstring & error_msg)
{
	if ( (xis.get(xc)) && (is_good_xchar(xc)) ) return xis;
	
	//failed
	xis.setstate(std::ios::failbit); 
	XIMOL_THROW << ( (xis.good()) ? _xtr(L"Reading this char '%o'.",(char)(xc)):_xtr(L"Can not read a char.")) 
					  << error_msg << XIMOL_AS_ERROR;
	return xis; 
}

//-----------------------------------------------------------------------------
// read string defined by a function.
//-----------------------------------------------------------------------------
xistream& read_xstring(xistream& xis, 
					 xstring & xstr,
					 bool (*is_good_xchar)(xchar_t),
					 bool erase_string)
{
	if (! (xis.good()) ) return xis;
	if (erase_string) clear_string(xstr);

	xchar_t xc = xis.front();
	while ( is_good_xchar(xc) && xis.good() )
	{ 
		xstr += xc;
		xis.pop_front();
		xc = xis.front();
	}
	return xis;
}

//-----------------------------------------------------------------------------
// Test string defined by a function.
//-----------------------------------------------------------------------------
bool is_xstring(xstring const & xstr, bool (*is_good_xchar)(xchar_t))
{
	xstring::const_iterator i(xstr.begin()),i_end(xstr.end());
	for(;i!=i_end;++i)
		if (!is_good_xchar(*i)) return false;
	return true;
}

//-----------------------------------------------------------------------------
// read Special string.
//-----------------------------------------------------------------------------
xistream& read_xstring(xistream& xistream_, const ::std::string& str_,
					   const ::std::wstring& strErrorMsg_, size_t size_)
{
	::std::string::const_iterator i(str_.begin()), i_end(str_.end());
	::std::wstring const new_err_msg =
		_xtr(L"Parsing for this string '%o'. %o", str_, strErrorMsg_);

    // drop the first char
	while ((size_>0)&&(i != i_end)) {
		--size_;
		++i;
	}

    // ok verify the string
	for(; i != i_end; ++i) 
        read_xchar(xistream_, *i, new_err_msg);

    return xistream_;
}

//-----------------------------------------------------------------------------
// write a ForbiddenSerie
//-----------------------------------------------------------------------------
xostream& write_string_with_forbidden_serie(xostream& xos, 
							  xstring const & xstr,
							  bool (*is_good_xchar)(xchar_t),
							  const ::std::string& forbidden_string,
							  const ::std::string& entity_test,
							  const ::std::string& entity_definition)
{
	if (! (xos.good()) ) return xos;
	if (is_string_with_forbidden_serie(xstr,is_good_xchar,forbidden_string)) 
	{
		xos << xstr;
		return xos;
	}

	//failed
	xos.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"'%o' is not a %o.",str< ::std::string>::cast(xstr),entity_test) 
					  << _xtr(L"XML Definition : %o",entity_definition) 
			          << XIMOL_AS_ERROR;
    return xos;
}

//-----------------------------------------------------------------------------
// read a ForbiddenSerie
//-----------------------------------------------------------------------------
xistream& read_string_with_forbidden_serie(xistream& xis, 
									xstring & xstr,
									 bool (*is_good_xchar)(xchar_t),
									 const ::std::string& forbidden_string)
{
	if (! (xis.good()) ) return xis;
	clear_string(xstr);
	xchar_t xc				= 0;
	int nb_forbidden_char	= 0;
	int fs_length=static_cast<int>(forbidden_string.length());
	xchar_t next_forbidden_char=(xchar_t)(forbidden_string[nb_forbidden_char]);

	while (  (xis.good())
		   &&(nb_forbidden_char<fs_length)
		   &&(xis.get(xc))
		   &&(is_good_xchar(xc))
		  )
	{
		if (xc==next_forbidden_char) 
		{
			++nb_forbidden_char;
			next_forbidden_char=(xchar_t)(forbidden_string[nb_forbidden_char]);
		} else {
			if (nb_forbidden_char>0) {
				int i;
				for(i=0;i<nb_forbidden_char;++i)
					xstr+=forbidden_string[i];
				nb_forbidden_char=0;
				next_forbidden_char=(xchar_t)(forbidden_string[nb_forbidden_char]);
			}
			xstr+=xc;
		}
	}
	if (  (xis.good())
		&&(  ((nb_forbidden_char==fs_length)&&(0!=fs_length))
		   ||(! is_good_xchar(xc))
		   )
	   )
	{
		int i;
		for(i=nb_forbidden_char-1;i>=0;--i)
			xis.putback(forbidden_string[i]);
		if (!is_good_xchar(xc)) xis.putback(xc); 
	}
	return xis;
}

//-----------------------------------------------------------------------------
// test ForbiddenSerie
//-----------------------------------------------------------------------------
bool is_string_with_forbidden_serie(xstring const & xstr,
					  bool (*is_good_xchar)(xchar_t),
				      const ::std::string& forbidden_string)
{
	xistringstream xis(xstr.c_str());
	xstring result;
	read_string_with_forbidden_serie(xis,result,is_good_xchar,forbidden_string);
	return (result.length()==xstr.length());
}

//-----------------------------------------------------------------------------
// test if a char is in the range.
//-----------------------------------------------------------------------------
bool is_in_range(xchar_t c, xchar_t lower, xchar_t upper)
{
	return XBET(lower,upper);
}

//-----------------------------------------------------------------------------
// test if a char is a space.
//-----------------------------------------------------------------------------
bool is_space(xchar_t c)
{
	return ( XEQ(0x20) || XEQ(0x9) || XEQ(0xD) || XEQ(0xA) );
}

//-----------------------------------------------------------------------------
// test if a char is a digit.
//-----------------------------------------------------------------------------
bool is_digit(xchar_t c)
{
    return  ( XBET(0x0030,0x0039) 
           || XBET(0x0660,0x0669)
           || XBET(0x06F0,0x06F9)
           || XBET(0x0966,0x096F)
           || XBET(0x09E6,0x09EF)
           || XBET(0x0A66,0x0A6F)
           || XBET(0x0AE6,0x0AEF)
           || XBET(0x0B66,0x0B6F)
           || XBET(0x0BE7,0x0BEF)
           || XBET(0x0C66,0x0C6F)
           || XBET(0x0CE6,0x0CEF)
           || XBET(0x0D66,0x0D6F)
           || XBET(0x0E50,0x0E59)
           || XBET(0x0ED0,0x0ED9)
           || XBET(0x0F20,0x0F29) );

}

//-----------------------------------------------------------------------------
// test if a char is a XML char.
//-----------------------------------------------------------------------------
bool is_char(xchar_t c)
{
    return ( XEQ(0x9) 
          || XEQ(0xA) 
          || XEQ(0xD) 
          || XBET(0x20,0xD7FF) 
          || XBET(0xE000,0xFFFD) 
          || XBET(0x10000,0x10FFFF) );
}

//-----------------------------------------------------------------------------
// test if a char is a letter.
//-----------------------------------------------------------------------------
bool is_letter(xchar_t c)
{
	return ( is_base_char(c) || is_ideographic(c) );
}

//-----------------------------------------------------------------------------
// test if a char is a combining char.
//-----------------------------------------------------------------------------
bool is_combining_char(xchar_t c)
{
    return ( XBET(0x0300,0x0345) || XBET(0x0360,0x0361) || XBET(0x0483,0x0486) 
          || XBET(0x0591,0x05A1) || XBET(0x05A3,0x05B9) || XBET(0x05BB,0x05BD) 
          || XEQ(0x05BF)  || XBET(0x05C1,0x05C2)  || XEQ(0x05C4) 
          || XBET(0x064B,0x0652) || XEQ(0x0670) || XBET(0x06D6,0x06DC) 
          || XBET(0x06DD,0x06DF) || XBET(0x06E0,0x06E4) || XBET(0x06E7,0x06E8) 
          || XBET(0x06EA,0x06ED) || XBET(0x0901,0x0903) || XEQ(0x093C) 
          || XBET(0x093E,0x094C) || XEQ(0x094D) || XBET(0x0951,0x0954) 
          || XBET(0x0962,0x0963) || XBET(0x0981,0x0983) 
          || XEQ(0x09BC) || XEQ(0x09BE) || XEQ(0x09BF) || XBET(0x09C0,0x09C4) 
          || XBET(0x09C7,0x09C8) || XBET(0x09CB,0x09CD) || XEQ(0x09D7) 
          || XBET(0x09E2,0x09E3) || XEQ(0x0A02) || XEQ(0x0A3C) || XEQ(0x0A3E) 
          || XEQ(0x0A3F) 
          || XBET(0x0A40,0x0A42) || XBET(0x0A47,0x0A48) || XBET(0x0A4B,0x0A4D) 
          || XBET(0x0A70,0x0A71) || XBET(0x0A81,0x0A83) || XEQ(0x0ABC) 
          || XBET(0x0ABE,0x0AC5) || XBET(0x0AC7,0x0AC9) || XBET(0x0ACB,0x0ACD) 
          || XBET(0x0B01,0x0B03) || XEQ(0x0B3C) || XBET(0x0B3E,0x0B43) 
          || XBET(0x0B47,0x0B48) || XBET(0x0B4B,0x0B4D) || XBET(0x0B56,0x0B57) 
          || XBET(0x0B82,0x0B83) || XBET(0x0BBE,0x0BC2) || XBET(0x0BC6,0x0BC8) 
          || XBET(0x0BCA,0x0BCD) || XEQ(0x0BD7) || XBET(0x0C01,0x0C03) 
          || XBET(0x0C3E,0x0C44) || XBET(0x0C46,0x0C48) || XBET(0x0C4A,0x0C4D) 
          || XBET(0x0C55,0x0C56) || XBET(0x0C82,0x0C83) || XBET(0x0CBE,0x0CC4) 
          || XBET(0x0CC6,0x0CC8) || XBET(0x0CCA,0x0CCD) || XBET(0x0CD5,0x0CD6) 
          || XBET(0x0D02,0x0D03) || XBET(0x0D3E,0x0D43) || XBET(0x0D46,0x0D48) 
          || XBET(0x0D4A,0x0D4D) || XEQ(0x0D57) || XEQ(0x0E31) 
          || XBET(0x0E34,0x0E3A) 
          || XBET(0x0E47,0x0E4E) || XEQ(0x0EB1) || XBET(0x0EB4,0x0EB9) 
          || XBET(0x0EBB,0x0EBC) || XBET(0x0EC8,0x0ECD) || XBET(0x0F18,0x0F19) 
          || XEQ(0x0F35) || XEQ(0x0F37) || XEQ(0x0F39) || XEQ(0x0F3E) || XEQ(0x0F3F) 
          || XBET(0x0F71,0x0F84) || XBET(0x0F86,0x0F8B) || XBET(0x0F90,0x0F95) 
          || XEQ(0x0F97) || XBET(0x0F99,0x0FAD) || XBET(0x0FB1,0x0FB7) || XEQ(0x0FB9) 
          || XBET(0x20D0,0x20DC) || XEQ(0x20E1) || XBET(0x302A,0x302F) || XEQ(0x3099) 
          || XEQ(0x309A) ); 
}

//-----------------------------------------------------------------------------
// test if a char is a base char.
//-----------------------------------------------------------------------------
bool is_base_char(xchar_t c)
{
  return ( XBET(0x0041,0x005A) || XBET(0x0061,0x007A) || XBET(0x00C0,0x00D6) 
        || XBET(0x00D8,0x00F6) || XBET(0x00F8,0x00FF) || XBET(0x0100,0x0131) 
        || XBET(0x0134,0x013E) || XBET(0x0141,0x0148) || XBET(0x014A,0x017E) 
        || XBET(0x0180,0x01C3) || XBET(0x01CD,0x01F0) || XBET(0x01F4,0x01F5) 
        || XBET(0x01FA,0x0217) || XBET(0x0250,0x02A8) || XBET(0x02BB,0x02C1) 
        || XEQ(0x0386) || XBET(0x0388,0x038A) || XEQ(0x038C) || XBET(0x038E,0x03A1) 
        || XBET(0x03A3,0x03CE) || XBET(0x03D0,0x03D6) || XEQ(0x03DA) || XEQ(0x03DC) 
        || XEQ(0x03DE) || XEQ(0x03E0) || XBET(0x03E2,0x03F3) || XBET(0x0401,0x040C) 
        || XBET(0x040E,0x044F) || XBET(0x0451,0x045C) || XBET(0x045E,0x0481) 
        || XBET(0x0490,0x04C4) || XBET(0x04C7,0x04C8) || XBET(0x04CB,0x04CC) 
        || XBET(0x04D0,0x04EB) || XBET(0x04EE,0x04F5) || XBET(0x04F8,0x04F9) 
        || XBET(0x0531,0x0556) || XEQ(0x0559) || XBET(0x0561,0x0586) 
        || XBET(0x05D0,0x05EA) || XBET(0x05F0,0x05F2) || XBET(0x0621,0x063A) 
        || XBET(0x0641,0x064A) || XBET(0x0671,0x06B7) || XBET(0x06BA,0x06BE) 
        || XBET(0x06C0,0x06CE) || XBET(0x06D0,0x06D3) || XEQ(0x06D5) 
        || XBET(0x06E5,0x06E6) || XBET(0x0905,0x0939) || XEQ(0x093D) 
        || XBET(0x0958,0x0961) || XBET(0x0985,0x098C) || XBET(0x098F,0x0990) 
        || XBET(0x0993,0x09A8) || XBET(0x09AA,0x09B0) || XEQ(0x09B2) 
        || XBET(0x09B6,0x09B9) || XBET(0x09DC,0x09DD) || XBET(0x09DF,0x09E1) 
        || XBET(0x09F0,0x09F1) || XBET(0x0A05,0x0A0A) || XBET(0x0A0F,0x0A10) 
        || XBET(0x0A13,0x0A28) || XBET(0x0A2A,0x0A30) || XBET(0x0A32,0x0A33) 
        || XBET(0x0A35,0x0A36) || XBET(0x0A38,0x0A39) || XBET(0x0A59,0x0A5C) 
        || XEQ(0x0A5E) || XBET(0x0A72,0x0A74) || XBET(0x0A85,0x0A8B) || XEQ(0x0A8D) 
        || XBET(0x0A8F,0x0A91) || XBET(0x0A93,0x0AA8) || XBET(0x0AAA,0x0AB0) 
        || XBET(0x0AB2,0x0AB3) || XBET(0x0AB5,0x0AB9) || XEQ(0x0ABD) || XEQ(0x0AE0) 
        || XBET(0x0B05,0x0B0C) || XBET(0x0B0F,0x0B10) || XBET(0x0B13,0x0B28) 
        || XBET(0x0B2A,0x0B30) || XBET(0x0B32,0x0B33) || XBET(0x0B36,0x0B39) 
        || XEQ(0x0B3D) || XBET(0x0B5C,0x0B5D) || XBET(0x0B5F,0x0B61) 
        || XBET(0x0B85,0x0B8A) || XBET(0x0B8E,0x0B90) || XBET(0x0B92,0x0B95) 
        || XBET(0x0B99,0x0B9A) || XEQ(0x0B9C) || XBET(0x0B9E,0x0B9F) 
        || XBET(0x0BA3,0x0BA4) || XBET(0x0BA8,0x0BAA) || XBET(0x0BAE,0x0BB5) 
        || XBET(0x0BB7,0x0BB9) || XBET(0x0C05,0x0C0C) || XBET(0x0C0E,0x0C10) 
        || XBET(0x0C12,0x0C28) || XBET(0x0C2A,0x0C33) || XBET(0x0C35,0x0C39) 
        || XBET(0x0C60,0x0C61) || XBET(0x0C85,0x0C8C) || XBET(0x0C8E,0x0C90) 
        || XBET(0x0C92,0x0CA8) || XBET(0x0CAA,0x0CB3) || XBET(0x0CB5,0x0CB9) 
        || XEQ(0x0CDE) || XBET(0x0CE0,0x0CE1) || XBET(0x0D05,0x0D0C) 
        || XBET(0x0D0E,0x0D10) || XBET(0x0D12,0x0D28) 
        || XBET(0x0D2A,0x0D39) || XBET(0x0D60,0x0D61) 
        || XBET(0x0E01,0x0E2E) || XEQ(0x0E30) || XBET(0x0E32,0x0E33) 
        || XBET(0x0E40,0x0E45) || XBET(0x0E81,0x0E82) || XEQ(0x0E84) 
        || XBET(0x0E87,0x0E88) || XEQ(0x0E8A) || XEQ(0x0E8D) || XBET(0x0E94,0x0E97) 
        || XBET(0x0E99,0x0E9F) || XBET(0x0EA1,0x0EA3) || XEQ(0x0EA5) || XEQ(0x0EA7) 
        || XBET(0x0EAA,0x0EAB) || XBET(0x0EAD,0x0EAE) || XEQ(0x0EB0) 
        || XBET(0x0EB2,0x0EB3) || XEQ(0x0EBD) || XBET(0x0EC0,0x0EC4) 
        || XBET(0x0F40,0x0F47) || XBET(0x0F49,0x0F69) || XBET(0x10A0,0x10C5) 
        || XBET(0x10D0,0x10F6) || XEQ(0x1100) || XBET(0x1102,0x1103) 
        || XBET(0x1105,0x1107) || XEQ(0x1109) || XBET(0x110B,0x110C) 
        || XBET(0x110E,0x1112) || XEQ(0x113C) || XEQ(0x113E) || XEQ(0x1140) || XEQ(0x114C) 
        || XEQ(0x114E) || XEQ(0x1150) || XBET(0x1154,0x1155) || XEQ(0x1159) 
        || XBET(0x115F,0x1161) || XEQ(0x1163) || XEQ(0x1165) || XEQ(0x1167) || XEQ(0x1169) 
        || XBET(0x116D,0x116E) || XBET(0x1172,0x1173) || XEQ(0x1175) || XEQ(0x119E) 
        || XEQ(0x11A8) || XEQ(0x11AB) || XBET(0x11AE,0x11AF) || XBET(0x11B7,0x11B8) 
        || XEQ(0x11BA) || XBET(0x11BC,0x11C2) || XEQ(0x11EB) || XEQ(0x11F0) || XEQ(0x11F9) 
        || XBET(0x1E00,0x1E9B) || XBET(0x1EA0,0x1EF9) || XBET(0x1F00,0x1F15) 
        || XBET(0x1F18,0x1F1D) || XBET(0x1F20,0x1F45) || XBET(0x1F48,0x1F4D) 
        || XBET(0x1F50,0x1F57) || XEQ(0x1F59) || XEQ(0x1F5B) || XEQ(0x1F5D) 
        || XBET(0x1F5F,0x1F7D) || XBET(0x1F80,0x1FB4) || XBET(0x1FB6,0x1FBC) 
        || XEQ(0x1FBE) || XBET(0x1FC2,0x1FC4) || XBET(0x1FC6,0x1FCC) 
        || XBET(0x1FD0,0x1FD3) || XBET(0x1FD6,0x1FDB) || XBET(0x1FE0,0x1FEC) 
        || XBET(0x1FF2,0x1FF4) || XBET(0x1FF6,0x1FFC) || XEQ(0x2126) 
        || XBET(0x212A,0x212B) || XEQ(0x212E) || XBET(0x2180,0x2182) 
        || XBET(0x3041,0x3094) || XBET(0x30A1,0x30FA) || XBET(0x3105,0x312C) 
        || XBET(0xAC00,0xD7A3) );
}

//-----------------------------------------------------------------------------
// test if a char is a Ideographic.
//-----------------------------------------------------------------------------
bool is_ideographic(xchar_t c)
{
	return ( XBET(0x4E00,0x9FA5) || XEQ(0x3007) || XBET(0x3021,0x3029) );
}

//-----------------------------------------------------------------------------
// test if a char is an extender.
//-----------------------------------------------------------------------------
bool is_extender(xchar_t c)
{
    return ( XEQ(0x00B7) || XEQ(0x02D0) || XEQ(0x02D1) 
          || XEQ(0x0387) || XEQ(0x0640) || XEQ(0x0E46) 
          || XEQ(0x0EC6) || XEQ(0x3005) || XBET(0x3031,0x3035) 
          || XBET(0x309D,0x309E) || XBET(0x30FC,0x30FE));  
}

//-----------------------------------------------------------------------------
// test if a char is a name character
//-----------------------------------------------------------------------------
bool is_name_char(xchar_t c)
{
	return ( is_letter(c) || is_digit(c) 
		  || XEQ(0x002e) || XEQ(0x002d) || XEQ(0x005f) || XEQ(0x003a) 
		  || is_combining_char(c) || is_extender(c) ); 
}

//-----------------------------------------------------------------------------
// test if a char is a NC name character
//-----------------------------------------------------------------------------
bool IsNCNameChar(xchar_t c)
{
	return ( is_letter(c) || is_digit(c) 
		  || XEQ(XCHAR_FULL_STOP) || XEQ(XCHAR_HYPHEN_MINUS) || XEQ(XCHAR_LOW_LINE)
		  || is_combining_char(c) || is_extender(c) ); 
}

//-----------------------------------------------------------------------------
// test if a char is a PubidChar
//-----------------------------------------------------------------------------
bool is_pubid_char(xchar_t c){
	return ( XEQ(0x0020) || XEQ(0x000D) || XEQ(0x000A) // space
		  || XBET(0x0061,0x007a) // a-z
		  || XBET(0x003F,0x005a) // ?@A-Z
		  || XBET(0x0027,0x003B) // '()*+,-./0123456789:;
		  || XEQ(0x003d)         // = 
		  || XEQ(0x0021)         // ! 
		  || XBET(0x0023,0x0025) // #$%
		  || XEQ(0x005f)         // _ 
		   ); 
}

//-----------------------------------------------------------------------------
// write a space
//-----------------------------------------------------------------------------
xostream& write_space(xostream& xos)
{
	write_xchar(xos,(xchar_t)(0x0020));
	return xos;
}

//-----------------------------------------------------------------------------
// read one or more spaces
//-----------------------------------------------------------------------------
xistream& read_space(xistream& xis)
{
	xchar_t xc;
	read_xchar(xis,xc,is_space,_xtr(L"Waiting for a space. XML Definition : S::= (#x20 | #x9 | #xD | #xA)")); 
	return read_optionnal_space(xis);
}

//-----------------------------------------------------------------------------
// read zero or more spaces
//-----------------------------------------------------------------------------
xistream& read_optionnal_space(xistream& xis)
{
	xstring xstr;
	read_xstring(xis,xstr,is_space);
	return xis;
}

//-----------------------------------------------------------------------------
// write a name
/* name    ::=    (Letter | '_' | ':') (NameChar)* */
//-----------------------------------------------------------------------------
xostream& write_name(xostream& xos, xstring const & xstr)
{
	if (! (xos.good()) ) return xos;
	if (is_name(xstr)) 
	{ 
		xos << xstr;
		return xos;
	}

	//failed
	xos.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"'%o' is not a name.",str< ::std::string>::cast(xstr)) 
					  << _xtr(L"XML Definition :  name    ::=    (Letter | '_' | ':') (NameChar)*") 
			          << XIMOL_AS_ERROR;
	return xos;
}

//-----------------------------------------------------------------------------
// intermediate function
//-----------------------------------------------------------------------------
bool is_first_char_name(xchar_t xc)
{
	return ( ((xc)==XCHAR_LOW_LINE) // '_'=0x005f 
		  || ((xc)==XCHAR_COLON) // ':'=0x003a 
          || (is_letter(xc))
		   );
}

//-----------------------------------------------------------------------------
// read a name
/* name    ::=    (Letter | '_' | ':') (NameChar)* */
//-----------------------------------------------------------------------------
xistream& read_name(xistream& xis, xstring & xstr)
{
	if (! (xis.good()) ) return xis;
	clear_string(xstr);
	xchar_t xc;
	read_xchar(xis,xc,is_first_char_name,_xtr(L"Parsing the first char of a name. XML Definition :  name    ::=    (Letter | '_' | ':') (NameChar)*"));

	xstr+=xc;
	read_xstring(xis,xstr,is_name_char,false);

	return xis;
}

//-----------------------------------------------------------------------------
// test name
/* name    ::=    (Letter | '_' | ':') (NameChar)* */
//-----------------------------------------------------------------------------
bool is_name(xstring const & xstr)
{
	if (xstr.empty()) return false;
	xstring::const_iterator i=xstr.begin(), i_end=xstr.end();
	if ( ! is_first_char_name(*i)) return false;
	++i;
	for(;i!=i_end;++i) if (!is_name_char(*i)) return false;
	return true;
}

//-----------------------------------------------------------------------------
// write a NCName
/* NCName    ::=    (Letter | '_') (NCNameChar)* */
//-----------------------------------------------------------------------------
xostream& write_ncname(xostream& xos, xstring const & xstr)
{
	if (! (xos.good()) ) return xos;
	if (is_ncname(xstr)) 
	{ 
		xos << xstr;
		return xos;
	}

	//failed
	xos.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"'%o' is not a name.",str< ::std::string>::cast(xstr)) 
					  << _xtr(L"XML Definition :  NCName    ::=    (Letter | '_') (NCNameChar)*") 
			          << XIMOL_AS_ERROR;
	return xos;
}

//-----------------------------------------------------------------------------
// intermediate function
//-----------------------------------------------------------------------------
bool is_first_char_ncname(xchar_t xc)
{
	return ( ((xc)==XCHAR_LOW_LINE) // '_'=0x005f 
		  || ((xc)==XCHAR_COLON) // ':'=0x003a 
          || (is_letter(xc))
		   );
}

//-----------------------------------------------------------------------------
// read a name
/* NCName    ::=    (Letter | '_') (NCNameChar)* */
//-----------------------------------------------------------------------------
xistream& read_ncname(xistream& xis, xstring & xstr)
{
	if (! (xis.good()) ) return xis;
	clear_string(xstr);
	xchar_t xc;
	read_xchar(xis,xc,is_first_char_ncname,_xtr(L"Parsing the first char of a NCName. XML Definition :  name    ::=    (Letter | '_' | ':') (NameChar)*"));

	xstr+=xc;
	read_xstring(xis,xstr,IsNCNameChar,false);

	return xis;
}

//-----------------------------------------------------------------------------
// test NCName
/* NCName    ::=    (Letter | '_') (NCNameChar)* */
//-----------------------------------------------------------------------------
bool is_ncname(xstring const & xstr)
{
	if (xstr.empty()) return false;
	xstring::const_iterator i=xstr.begin(), i_end=xstr.end();
	if ( ! is_first_char_ncname(*i)) return false;
	++i;
	for(;i!=i_end;++i) if (!IsNCNameChar(*i)) return false;
	return true;
}

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
xostream& write_qname(xostream& xos, xstring const & localPart, xstring const & prefix)
{
	if (! (xos.good()) ) return xos;
	if (! prefix.empty())
	{
		write_ncname(xos,prefix);
		write_xchar(xos,XCHAR_COLON);
	}
	write_ncname(xos,localPart);
	return xos;
}

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
xistream& read_qname(xistream& xis, xstring & localPart, xstring & prefix)
{
	if (! (xis.good()) ) return xis;
    clear_string(prefix);
	read_ncname(xis,localPart);
	if (xis.front()==XCHAR_COLON)
	{
        xis.pop_front();
		prefix=localPart;
		read_ncname(xis,localPart);
	}
	return xis;
}

//-----------------------------------------------------------------------------
// test QName
//-----------------------------------------------------------------------------
bool is_qname(xstring const & localPart, xstring const & prefix)
{
	return ((is_ncname(localPart))&&(prefix.empty() || is_ncname(prefix)));
}

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
xostream& write_ns_att_name(xostream& xos, xstring const & xstr)
{
	if (! (xos.good()) ) return xos;
	if (is_ns_att_name(xstr)) 
	{ 
		write_xchar(xos,XCHAR_LATIN_SMALL_LETTER_X); 
		write_xchar(xos,XCHAR_LATIN_SMALL_LETTER_M); 
		write_xchar(xos,XCHAR_LATIN_SMALL_LETTER_L); 
		write_xchar(xos,XCHAR_LATIN_SMALL_LETTER_N); 
		write_xchar(xos,XCHAR_LATIN_SMALL_LETTER_S);
		if (! xstr.empty()) {
			write_xchar(xos,XCHAR_COLON);
			xos << xstr;
		}
		return xos;
	}

	//failed
	xos.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"'%o' is not a name.",str< ::std::string>::cast(xstr)) 
					  << _xtr(L"XML Definition :  	NSAttName ::=  PrefixedAttName | DefaultAttName \nPrefixedAttName ::=  'xmlns:' NCName\nDefaultAttName ::=  'xmlns' ") 
			          << XIMOL_AS_ERROR;
	return xos;
}

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
xistream& read_ns_att_name(xistream& xis, xstring & xstr, int nb_read)
{
	if (! (xis.good()) ) return xis;
	switch (nb_read){
		case 0: read_xchar(xis,XCHAR_LATIN_SMALL_LETTER_X,_xtr(L"XML Definition :  	NSAttName ::=  PrefixedAttName | DefaultAttName \nPrefixedAttName ::=  'xmlns:' NCName\nDefaultAttName ::=  'xmlns' "));
		case 1:	read_xchar(xis,XCHAR_LATIN_SMALL_LETTER_M,_xtr(L"XML Definition :  	NSAttName ::=  PrefixedAttName | DefaultAttName \nPrefixedAttName ::=  'xmlns:' NCName\nDefaultAttName ::=  'xmlns' "));
		case 2:	read_xchar(xis,XCHAR_LATIN_SMALL_LETTER_L,_xtr(L"XML Definition :  	NSAttName ::=  PrefixedAttName | DefaultAttName \nPrefixedAttName ::=  'xmlns:' NCName\nDefaultAttName ::=  'xmlns' "));
		case 3:	read_xchar(xis,XCHAR_LATIN_SMALL_LETTER_N,_xtr(L"XML Definition :  	NSAttName ::=  PrefixedAttName | DefaultAttName \nPrefixedAttName ::=  'xmlns:' NCName\nDefaultAttName ::=  'xmlns' "));
		case 4:	read_xchar(xis,XCHAR_LATIN_SMALL_LETTER_S,_xtr(L"XML Definition :  	NSAttName ::=  PrefixedAttName | DefaultAttName \nPrefixedAttName ::=  'xmlns:' NCName\nDefaultAttName ::=  'xmlns' "));
	}
	clear_string(xstr);
	xchar_t xc=xis.front();
	if (xc==XCHAR_COLON) 
	{
		xis.pop_front();
		read_ncname(xis,xstr);
	}
	return xis;
}

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
bool is_ns_att_name(xstring const & xstr)
{
	if (xstr.empty()) return true;
	return is_ncname(xstr);
}

//-----------------------------------------------------------------------------
// Intermediate function
//-----------------------------------------------------------------------------
bool IsNotAndOrInf(xchar_t xc)
{
	return ((is_char(xc)) && 
			(xc != XCHAR_AMPERSAND) && 
			(xc != XCHAR_LESS_THAN_SIGN));
}

//-----------------------------------------------------------------------------
// write a CharData
/* CharData    ::=    [^<&]* - ([^<&]* ']]>' [^<&]*) */
//-----------------------------------------------------------------------------
xostream& write_char_data(xostream& xos, xstring const & xstr)
{
	if (! (xos.good()) ) return xos;
	if (is_char_data(xstr)) 
	{
		xos << xstr;
		return xos;
	}

	// failed
	xos.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"'%o' is not a CharData.",str< ::std::string>::cast(xstr)) 
					  << _xtr(L"XML Definition :  CharData    ::=    [^<&]* - ([^<&]* ']]>' [^<&]*) ") 
		              << XIMOL_AS_ERROR;
	return xos;
}

//-----------------------------------------------------------------------------
// read a CharData
/* CharData    ::=    [^<&]* - ([^<&]* ']]>' [^<&]*) 
	the reading is stop by '<' or '&' or ']]>' 
	and we putback only one char '<' or '&' or '>'
*/
//-----------------------------------------------------------------------------
xistream& read_char_data(xistream& xis, xstring & xstr)
{
	return read_string_with_forbidden_serie(xis,xstr,IsNotAndOrInf,"]]>");
}

//-----------------------------------------------------------------------------
// test CharData
/* CharData    ::=    [^<&]* - ([^<&]* ']]>' [^<&]*)  */
//-----------------------------------------------------------------------------
bool is_char_data(xstring const & xstr)
{
	return is_string_with_forbidden_serie(xstr,IsNotAndOrInf,"]]>");
}

//-----------------------------------------------------------------------------
// write a Nmtoken
/* Nmtoken    ::=    (NameChar)+  */
//-----------------------------------------------------------------------------
xostream& write_nm_token(xostream& xos, xstring const & xstr)
{
	if (! (xos.good()) ) return xos;
	if (is_nm_token(xstr)) 
	{
		xos << xstr;
		return xos;
	}

	// failed
	xos.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"'%o' is not a Nmtoken.",str< ::std::string>::cast(xstr)) 
					  << _xtr(L"XML Definition : Nmtoken    ::=    (NameChar)+") 
		              << XIMOL_AS_ERROR;
	return xos; 
}

//-----------------------------------------------------------------------------
// read a Nmtoken
/* Nmtoken    ::=    (NameChar)+  */
//-----------------------------------------------------------------------------
xistream& read_nm_token(xistream& xis, xstring & xstr)
{
	clear_string(xstr);
	xchar_t xc;
	read_xchar(xis,xc,is_name_char,_xtr(L"Parsing the first char of a Nmtoken. XML Definition :  Nmtoken ::= (NameChar)+"));
	xstr+=xc;
	return read_xstring(xis,xstr,is_name_char,false);
}

//-----------------------------------------------------------------------------
// test Nmtoken
/* Nmtoken    ::=    (NameChar)+  */
//-----------------------------------------------------------------------------
bool is_nm_token(xstring const & xstr)
{
	if (xstr.empty()) return false;
	xstring::const_iterator i=xstr.begin(), i_end=xstr.end();
	if ( ! (is_name_char(*i)) ) return false;
	for(;i!=i_end;++i) if (!is_name_char(*i)) return false;
	return true;
}

//-----------------------------------------------------------------------------
// write a CharRef
/* CharRef    ::=    '&#' [0-9]+ ';'  
                    | '&#x' [0-9a-fA-F]+ ';' 
  */
//-----------------------------------------------------------------------------
xostream& write_char_ref(xostream& xos, xchar_t xc)
{
	if (! (xos.good()) ) return xos;
	if (! is_char(xc)) 
	{ 
		xos.setstate(std::ios::failbit); 
		XIMOL_THROW << _xtr(L"write a char reference, '%o' is not a Standard Char.",xc) 
						  << XIMOL_AS_ERROR;
		return xos; 
	}
	write_xchar(xos, XCHAR_AMPERSAND); 
	write_xchar(xos, XCHAR_NUMBER_SIGN); 
	::std::dec(xos);
	xos << static_cast<unsigned>(xc);
	write_xchar(xos, XCHAR_SEMICOLON);
	return xos;
}

//-----------------------------------------------------------------------------
// read a CharRef
/* CharRef    ::=    '&#' [0-9]+ ';'  
                    | '&#x' [0-9a-fA-F]+ ';' 
	if read_first_char==true then the char '&' is not read.
  */
//-----------------------------------------------------------------------------
xistream& read_char_ref(xistream& xis, xchar_t & xc_read, int nb_read)
{
	if (! (xis.good()) ) return xis;
	xchar_t xc;
	switch (nb_read){
		case 0: read_xchar(xis,XCHAR_AMPERSAND  ,_xtr(L"XML Definition : CharRef    ::=    ('&#' [0-9]+ ';') | ('&#x' [0-9a-fA-F]+ ';')"));
		case 1:	read_xchar(xis,XCHAR_NUMBER_SIGN,_xtr(L"XML Definition : CharRef    ::=    ('&#' [0-9]+ ';') | ('&#x' [0-9a-fA-F]+ ';')"));
	}

	xc=xis.front();
	long nb_char;
	bool is_hex=false;
	if ((xc)==XCHAR_LATIN_SMALL_LETTER_X)  // test 'x'
	{ 
		is_hex=true;
		xis.pop_front();
	}

	::std::basic_stringstream<xchar_t> buf;
	while ( (xis.get(xc)) 
		  &&(  (is_digit(xc)) 
		     ||(is_in_range(xc,XCHAR_LATIN_CAPITAL_LETTER_A,XCHAR_LATIN_CAPITAL_LETTER_F)) 
			 ||(is_in_range(xc,XCHAR_LATIN_SMALL_LETTER_A,XCHAR_LATIN_SMALL_LETTER_F))
		    )) 
		buf << xc;
	xis.putback(xc);
	buf >> ((is_hex)?(std::hex):(std::dec))>> nb_char;
	xc_read=(xchar_t)nb_char;

	// parsing ';'
	return read_xchar(xis,XCHAR_SEMICOLON,_xtr(L"XML Definition : CharRef    ::=    ('&#' [0-9]+ ';') | ('&#x' [0-9a-fA-F]+ ';')"));
}

//-----------------------------------------------------------------------------
// replace all Charref in the string
/** @ingroup parser_read
<pre>
	CharRef    ::=    '&#' [0-9]+ ';'  
                    | '&#x' [0-9a-fA-F]+ ';' 
</pre>
  */
//-----------------------------------------------------------------------------
xstring replace_char_ref(xstring const & xstr)
{
	xstring result;
	xstring::const_iterator i(xstr.begin()), i_end(xstr.end());
	while (i!=i_end)
	{
		if (*i == XCHAR_AMPERSAND)
		{
			xstring temp(i,i_end);
			xistringstream xistr(temp);
			xchar_t xc;
			try {
				read_char_ref(xistr,xc);
				result+=xc;
			} catch (...) {
				result+=*i;
			}
			++i;
		}
		else
		{
			result+=*i;
			++i;
		}
	}
	return result;
}

//-----------------------------------------------------------------------------
// write a EntityRef
/* EntityRef    ::=    '&' name ';' 
	xtr is the name.
  */
//-----------------------------------------------------------------------------
xostream& write_entity_ref(xostream& xos, xstring const & xstr)
{
	if (! (xos.good()) ) return xos;
	
	write_xchar(xos,XCHAR_AMPERSAND); // '&'
	write_name(xos,xstr);
	write_xchar(xos,XCHAR_SEMICOLON); // ';'
	return xos;

}

//-----------------------------------------------------------------------------
// read a EntityRef
/* EntityRef    ::=    '&' name ';' 
	this function return name as xstr.
  */
//-----------------------------------------------------------------------------
xistream& read_entity_ref(xistream& xis, int nb_read)
{
	if (! (xis.good()) ) return xis;

	switch (nb_read) {
	case 0:	read_xchar(xis,XCHAR_AMPERSAND,_xtr(L"XML Definition : EntityRef    ::=    '&' name ';'"));
	}

	xstring name;
	read_name(xis,name);

	//parse ';'
	read_xchar(xis,XCHAR_SEMICOLON,_xtr(L"XML Definition : EntityRef    ::=    '&' name ';'"));

	xis.putback(xis.context.get_entity(name));
	return xis;
}

//-----------------------------------------------------------------------------
// write a PEReference
/* PEReference    ::=    '%' name ';'  
	xtr is the name.
  */
//-----------------------------------------------------------------------------
xostream& write_pe_reference(xostream& xos, xstring const & xstr)
{
	if (! (xos.good()) ) return xos;
	
	write_xchar(xos,XCHAR_PERCENT_SIGN); // '%'
	write_name(xos,xstr);
	write_xchar(xos,XCHAR_SEMICOLON); // ';'
	return xos;
}

//-----------------------------------------------------------------------------
// read a PEReference
/* PEReference    ::=    '%' name ';'  
	this function return name as xstr.
  */
//-----------------------------------------------------------------------------
xistream& read_pe_reference(xistream& xis, xstring & xstr, int nb_read)
{
	if (! (xis.good()) ) return xis;
	clear_string(xstr);

	switch (nb_read) {
	case 0:	read_xchar(xis,XCHAR_PERCENT_SIGN,_xtr(L"XML Definition : PEReference    ::=    '%' name ';'"));
	}

	read_name(xis,xstr);
	//parsing ';'
	read_xchar(xis,XCHAR_SEMICOLON,_xtr(L"XML Definition : PEReference    ::=    '%' name ';'"));

	xstr=xis.context.get_parameter_entity(xstr);
	return xis;
}

//-----------------------------------------------------------------------------
// read a Reference
/* Reference    ::=    EntityRef | CharRef  
  */
//-----------------------------------------------------------------------------
xistream& read_reference(xistream& xis, xstring & xstr, int nb_read)
{
	if (! (xis.good()) ) return xis;
	clear_string(xstr);

	switch (nb_read){ 
	case 0:	read_xchar(xis,XCHAR_AMPERSAND,_xtr(L"XML Definition : Reference    ::=    EntityRef | CharRef\nXML Definition : EntityRef    ::=    '&' name ';'\nXML Definition : CharRef    ::=    ('&#' [0-9]+ ';') | ('&#x' [0-9a-fA-F]+ ';')") );
	}

	xchar_t xc=xis.front();

	if ((xc)==XCHAR_NUMBER_SIGN)  // test '#'
	{ 
		read_char_ref(xis,xc,1);
		xstr+=xc;
	} else {
		read_entity_ref(xis,1);
	}

	return xis;
}

//-----------------------------------------------------------------------------
// write a pubid_literal
/* pubid_literal    ::=    '"' PubidChar* '"' | "'" (PubidChar - "'")* "'" 
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
xostream& write_pubid_literal(xostream& xos, xstring const & xstr)
{
	if (! (xos.good()) ) return xos;
	xstring::const_iterator i=xstr.begin(), i_end=xstr.end();
	write_xchar(xos,XCHAR_QUOTATION_MARK);
	
	for(;i!=i_end;++i)
	{ 
		if (is_pubid_char(*i)) 
			write_xchar(xos,*i);
		else {
			xos.setstate(std::ios::failbit);  
			XIMOL_THROW << _xtr(L"write pubid_literal, '%o' is not a PubidChar.",(char)*i) 
							  << _xtr(L"XML Definition : pubid_literal    ::=    '\"' PubidChar* '\"' | \"'\" (PubidChar - \"'\")* \"'\"") 
							  << _xtr(L"XML Definition :  PubidChar    ::=    #x20 | #xD | #xA | [a-zA-Z0-9] | [-'()+,./:=?;!*#@$_%] ") 
				              << XIMOL_AS_ERROR;
		}
	}
	write_xchar(xos,XCHAR_QUOTATION_MARK);
	return xos;
}

//-----------------------------------------------------------------------------
// Intermediate function
//-----------------------------------------------------------------------------
bool IsQuote(xchar_t c)
{
	return ( XEQ(0x0022) || XEQ(0x0027) );
}

//-----------------------------------------------------------------------------
// read a pubid_literal
/* pubid_literal    ::=    '"' PubidChar* '"' | "'" (PubidChar - "'")* "'"   
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
xistream& read_pubid_literal(xistream& xis, xstring & xstr)
{
	if (! (xis.good()) ) return xis;

	xchar_t xquote;
	
	read_xchar(xis,xquote,IsQuote,_xtr(L"pubid_literal parsing first char.\nXML Definition : pubid_literal    ::=    '\"' PubidChar* '\"' | \"'\" (PubidChar - \"'\")* \"'\""));

	if (xquote==XCHAR_APOSTROPHE)
	{
		read_string_with_forbidden_serie(xis,xstr,is_pubid_char,"'");
		read_xchar(xis,XCHAR_APOSTROPHE,_xtr(L"pubid_literal parsing last char (').\nXML Definition : pubid_literal    ::=    '\"' PubidChar* '\"' | \"'\" (PubidChar - \"'\")* \"'\""));
	} else { 
		read_string_with_forbidden_serie(xis,xstr,is_pubid_char,"\"");
		read_xchar(xis,XCHAR_QUOTATION_MARK,_xtr(L"pubid_literal parsing last char (\").\nXML Definition : pubid_literal    ::=    '\"' PubidChar* '\"' | \"'\" (PubidChar - \"'\")* \"'\""));
	}
	return xis;
}

//-----------------------------------------------------------------------------
// write a system_literal
/* system_literal    ::=    ('"' [^"]* '"') | ("'" [^']* "'")  
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
xostream& write_system_literal(xostream& xos, xstring const & xstr, xchar_t quote)
{
	if (! (xos.good()) ) return xos;
	xstring::const_iterator i=xstr.begin(), i_end=xstr.end();
	write_xchar(xos,quote);
	
	for(;i!=i_end;++i)
	{ 
		if ( (is_char(*i)) && (*i!=quote) ) 
			write_xchar(xos,*i);
		else {
			xos.setstate(std::ios::failbit);  
			XIMOL_THROW << _xtr(L"write system_literal, '%o' is not a Char or equal to the quote '%o'.",(char)*i,(char)quote) 
							  << _xtr(L"XML Definition : system_literal    ::=    ('\"' [^\"]* '\"') | (\"'\" [^']* \"'\")") 
				              << XIMOL_AS_ERROR;
		}
	}
	write_xchar(xos,quote);
	return xos;
}

//-----------------------------------------------------------------------------
// read a system_literal
/* system_literal    ::=    ('"' [^"]* '"') | ("'" [^']* "'")    
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
xistream& read_system_literal(xistream& xis, xstring & xstr)
{
	if (! (xis.good()) ) return xis;
	clear_string(xstr);
	xchar_t xquote;

	read_xchar(xis,xquote,IsQuote,_xtr(L"system_literal parsing first char.\nXML Definition : system_literal    ::=    ('\"' [^\"]* '\"') | (\"'\" [^']* \"'\")"));
	if (xquote==XCHAR_APOSTROPHE)
	{
		read_string_with_forbidden_serie(xis,xstr,is_char,"'");
		read_xchar(xis,XCHAR_APOSTROPHE,_xtr(L"system_literal parsing last char (').\nXML Definition : system_literal    ::=    ('\"' [^\"]* '\"') | (\"'\" [^']* \"'\")"));
	} else { 
		read_string_with_forbidden_serie(xis,xstr,is_char,"\"");
		read_xchar(xis,XCHAR_QUOTATION_MARK,_xtr(L"system_literal parsing last char (\").\nXML Definition : system_literal    ::=    ('\"' [^\"]* '\"') | (\"'\" [^']* \"'\")"));
	}
	return xis;
}

//-----------------------------------------------------------------------------
// write a entity_value
/* entity_value    ::=    '"' ([^%&"] | PEReference | Reference)* '"'  
                       |  "'" ([^%&'] | PEReference | Reference)* "'" 
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
xostream& write_entity_value(xostream& xos, xstring const & xstr, xchar_t quote)
{
	if (! (xos.good()) ) return xos;
	xstring::const_iterator i=xstr.begin(), i_end=xstr.end();
	write_xchar(xos,quote);
	
	for(;i!=i_end;++i)
	{ 
		if (  (*i!=XCHAR_PERCENT_SIGN) 
			&&(*i!=XCHAR_AMPERSAND) 
			&&(*i!=quote)) 
			write_xchar(xos,*i);
		else 
			write_char_ref(xos,*i);
	}
	write_xchar(xos,quote);
	return xos;
}

//-----------------------------------------------------------------------------
// transforme quote in string into charRef
//-----------------------------------------------------------------------------
xstring ToQuoteRef(xstring const & xstr)
{
	xstring::const_iterator i=xstr.begin(), i_end=xstr.end();
	xstring result; 
	for(;i!=i_end;++i) switch (*i)
	{
		case XCHAR_QUOTATION_MARK: result+=str< ::std::wstring>::cast("&#x22;"); break;
		case XCHAR_APOSTROPHE:     result+=str< ::std::wstring>::cast("&#x27;"); break;
		default:                   result+=*i;
	}
	return result;
}

//-----------------------------------------------------------------------------
// read a entity_value
/* entity_value    ::=    '"' ([^%&"] | PEReference | Reference)* '"'  
                       |  "'" ([^%&'] | PEReference | Reference)* "'" 
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
xistream& read_entity_value(xistream& xis, xstring & xstr)
{
	if (! (xis.good()) ) return xis;
	clear_string(xstr);
	xchar_t xc,xquote;
	xstring xtemp;
	
	read_xchar(xis,xquote,IsQuote,_xtr(L"entity_value parsing first char.\nXML Definition : entity_value    ::=    '\"' ([^%&\"] | PEReference | Reference)* '\"'   |  \"'\" ([^%&'] | PEReference | Reference)* \"'\" "));

	while ( (xis.get(xc)) && (xc!=xquote) && (is_char(xc)) )
	{
		switch (xc) 
		{
		case XCHAR_AMPERSAND : //'&'
			if ((xis.get(xc))&&(is_char(xc)))
			{
				if (xc==XCHAR_NUMBER_SIGN) {
					read_char_ref(xis,xc,2);
					xstr+=xc;
				} else {
					xis.putback(xc);
					read_name(xis,xtemp);
					read_xchar(xis,XCHAR_SEMICOLON,_xtr(L"XML Definition : PEReference    ::=    '%' name ';'"));
					xstr+=XCHAR_AMPERSAND + xtemp + XCHAR_SEMICOLON;
				}
			} else {
				XIMOL_THROW << _xtr(L"entity_value parsing : '%o' is not a Char.",(char)(xc)) 
					<< _xtr(L"XML Definition : entity_value    ::=    '\"' ([^%&\"] | PEReference | Reference)* '\"'   |  \"'\" ([^%&'] | PEReference | Reference)* \"'\" ") 
					<< XIMOL_AS_ERROR;
			}
			break;
		case XCHAR_PERCENT_SIGN : //'%'
			read_pe_reference(xis,xtemp,1);
			xis.putback(ToQuoteRef(xtemp));
			break;
		default: xstr+=xc;
		}
	}
	
	if ((xis.good()) && (xc==xquote)) return xis;
	
	//failed
	xis.setstate(std::ios::failbit); 
	XIMOL_THROW << _xtr(L"entity_value parsing : '%o' is not a quote.",(char)(xc)) 
					  << _xtr(L"XML Definition : entity_value    ::=    '\"' ([^%&\"] | PEReference | Reference)* '\"'   |  \"'\" ([^%&'] | PEReference | Reference)* \"'\" ") 
			          << XIMOL_AS_ERROR;
	return xis; 
}

//-----------------------------------------------------------------------------
// write a AttValue
/* AttValue    ::=    '"' ([^<&"] | Reference)* '"'  
                    |  "'" ([^<&'] | Reference)* "'" 
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
xostream& write_att_value(xostream& xos, xstring const & xstr, xchar_t quote)
{
	if (! (xos.good()) ) return xos;
	xstring::const_iterator i=xstr.begin(), i_end=xstr.end();
	write_xchar(xos,quote);
	
	for(;i!=i_end;++i)
	{ 
		if (is_char(*i))
		{
			if ((*i!=XCHAR_LESS_THAN_SIGN) && 
			    (*i!=XCHAR_AMPERSAND) && 
			    (*i!=quote) ) 
				write_xchar(xos,*i);
			else write_char_ref(xos,*i);
		} else {
			xos.setstate(std::ios::failbit);  
			XIMOL_THROW << _xtr(L"write AttValue, '%o' is not a Char.",(char)*i) 
							  << _xtr(L"XML Definition : AttValue    ::=    '\"' ([^<&\"] | Reference)* '\"'  |  \"'\" ([^<&'] | Reference)* \"'\"") 
				              << XIMOL_AS_ERROR;
			
		}
	}
	write_xchar(xos,quote);
	return xos;
}

//-----------------------------------------------------------------------------
// read a AttValue
/* AttValue    ::=    '"' ([^<&"] | Reference)* '"'  
                    |  "'" ([^<&'] | Reference)* "'" 
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
xistream& read_att_value(xistream& xis, xstring & xstr)
{
	if (! (xis.good()) ) return xis;
	clear_string(xstr);
	xchar_t xc,xquote;
	xstring xtemp;

	read_xchar(xis,xquote,IsQuote,_xtr(L"AttValue parsing first char.\nXML Definition : AttValue    ::=    '\"' ([^<&\"] | Reference)* '\"'  |  \"'\" ([^<&'] | Reference)* \"'\""));

	while ( (xis.get(xc)) && (xc!=xquote) && (is_char(xc)))
	{
		switch (xc) 
		{
		case XCHAR_AMPERSAND : //'&'
			if ((xis.get(xc))&&(is_char(xc)))
			{
				if (xc==XCHAR_NUMBER_SIGN) {
					read_char_ref(xis,xc,2);
					xstr+=xc;
				} else {
					read_reference(xis,xtemp,1);
					xis.putback(ToQuoteRef(xtemp));
				}
			} else {
				XIMOL_THROW << _xtr(L"AttValue parsing : '%o' is not a Char.",(char)(xc)) 
					<< _xtr(L"XML Definition : AttValue    ::=    '\"' ([^<&\"] | Reference)* '\"'  |  \"'\" ([^<&'] | Reference)* \"'\"") 
					<< XIMOL_AS_ERROR;
			}
			break;
		default: xstr+=xc;
		}
	}
	
	if ((xis.good()) && (xc==xquote)) return xis;

	//failed
	xis.setstate(std::ios::failbit); 
	XIMOL_THROW << _xtr(L"AttValue parsing : '%o' is not a quote.",(char)(xc)) 
					  << _xtr(L"XML Definition : AttValue    ::=    '\"' ([^<&\"] | Reference)* '\"'  |  \"'\" ([^<&'] | Reference)* \"'\"") 
			          << XIMOL_AS_ERROR;
	return xis; 
}

//-----------------------------------------------------------------------------
// write a Attribute
/* Attribute    ::=    name Eq AttValue  
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
xostream& write_attribute(xostream& xos, xstring const & name, xstring const & att_value, xstring const & short_ns, xchar_t quote)
{
	write_qname(xos,name,short_ns);
	write_eq(xos);
	write_att_value(xos,att_value,quote);
	return xos;
}

//-----------------------------------------------------------------------------
// read a Attribute
/* Attribute    ::=    name Eq AttValue 
	we use only the value without quote.  
  */
//-----------------------------------------------------------------------------
xistream& read_attribute(xistream& xis, xstring & name, xstring & att_value, xstring & short_ns)
{
	read_qname(xis,name,short_ns);
	read_eq(xis);
	read_att_value(xis,att_value);
	return xis;
}

//-----------------------------------------------------------------------------
// Test comment
/* comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->' 
  */
//-----------------------------------------------------------------------------
bool is_comment(xstring const & xstr)
{
	if (xstr.empty()) return true;
	bool first_test=is_string_with_forbidden_serie(xstr,is_char,"--");
	bool second_test=true;
	if (xstr[xstr.length()-1]==XCHAR_HYPHEN_MINUS) second_test=false;
	return ( first_test && second_test );
}

//-----------------------------------------------------------------------------
// write a comment
/* comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->' 
  */
//-----------------------------------------------------------------------------
xostream& write_comment(xostream& xos, xstring const & xstr)
{
	if (! (xos.good()) ) return xos;
	xstring::const_iterator i=xstr.begin(), i_end=xstr.end();
	write_xchar(xos,XCHAR_LESS_THAN_SIGN);    // '<' 
	write_xchar(xos,XCHAR_EXCLAMATION_MARK);  // '!'
	write_xchar(xos,XCHAR_HYPHEN_MINUS);      // '-'
	write_xchar(xos,XCHAR_HYPHEN_MINUS);      // '-'

	if (is_comment(xstr)) xos<<xstr;
	else {
		xos.setstate(std::ios::failbit);  
		XIMOL_THROW << _xtr(L"write comment, '%o' is not a comment.",str< ::std::string>::cast(xstr)) 
						  << _xtr(L"XML Definition : comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'") 
			              << XIMOL_AS_ERROR;
	}
	write_xchar(xos,XCHAR_HYPHEN_MINUS);   // '-'
	write_xchar(xos,XCHAR_HYPHEN_MINUS);   // '-'
	write_xchar(xos,XCHAR_GREATER_THAN_SIGN); // '>' 
	return xos;
}

//-----------------------------------------------------------------------------
// read a comment
/* comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->' 
  */
//-----------------------------------------------------------------------------
xistream& read_comment(xistream& xis, xstring & xstr, int nb_read)
{
	if (! (xis.good()) ) return xis;
	clear_string(xstr);

	switch(nb_read){
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN,  _xtr(L"comment parsing a '<'.XML Definition : comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'") );
	case 1: read_xchar(xis,XCHAR_EXCLAMATION_MARK,_xtr(L"comment parsing a '!'.XML Definition : comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'") );
	case 2: read_xchar(xis,XCHAR_HYPHEN_MINUS,    _xtr(L"comment parsing a '-'.XML Definition : comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'") );
	case 3: read_xchar(xis,XCHAR_HYPHEN_MINUS,    _xtr(L"comment parsing a '-'.XML Definition : comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'") );
	}

	read_string_with_forbidden_serie(xis,xstr,is_char,"--");
	
	read_xchar(xis,XCHAR_HYPHEN_MINUS,     _xtr(L"comment parsing a '-'.XML Definition : comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'") );
	read_xchar(xis,XCHAR_HYPHEN_MINUS,     _xtr(L"comment parsing a '-'.XML Definition : comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'") );
	read_xchar(xis,XCHAR_GREATER_THAN_SIGN,_xtr(L"comment parsing a '>'.XML Definition : comment    ::=    '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'") );
	return xis;
}

//-----------------------------------------------------------------------------
// read a comment
//-----------------------------------------------------------------------------
xistream& read_comment(xistream& xis, int nb_read)
{
	xstring dummy;
	return read_comment(xis,dummy,nb_read);
}

//-----------------------------------------------------------------------------
// Test pi_target
/* pi_target    ::=    name - (('X' | 'x') ('M' | 'm') ('L' | 'l')) 
  */
//-----------------------------------------------------------------------------
bool is_pi_target(xstring const & xstr)
{
	if (! is_name(xstr)) return false;
	xstring::const_iterator i(xstr.begin()), i_end(xstr.end());
	int nb_char_forbidden=0;
	while ((i!=i_end) && (nb_char_forbidden<3))
	{
		if ((nb_char_forbidden==0)&&
			((*i==XCHAR_LATIN_CAPITAL_LETTER_X)||(*i==XCHAR_LATIN_SMALL_LETTER_X))) 
			++nb_char_forbidden;
		if ((nb_char_forbidden==1)&&
			((*i==XCHAR_LATIN_CAPITAL_LETTER_M)||(*i==XCHAR_LATIN_SMALL_LETTER_M))) 
			++nb_char_forbidden;
		else nb_char_forbidden=0;
		if ((nb_char_forbidden==2)&&
			((*i==XCHAR_LATIN_CAPITAL_LETTER_L)||(*i==XCHAR_LATIN_SMALL_LETTER_L))) 
			++nb_char_forbidden;
		else nb_char_forbidden=0;
		++i;
	}
	if (nb_char_forbidden==3) return false;
	return true;
}

//-----------------------------------------------------------------------------
// write a pi_target
/* pi_target    ::=    name - (('X' | 'x') ('M' | 'm') ('L' | 'l')) 
  */
//-----------------------------------------------------------------------------
xostream& write_pi_target(xostream& xos, xstring const & xstr)
{
	if (is_pi_target(xstr)) return write_name(xos,xstr);
	xos.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"write pi_target, '%o' is not a pi_target.",str< ::std::string>::cast(xstr)) 
							  << _xtr(L"XML Definition : pi_target    ::=    name - (('X' | 'x') ('M' | 'm') ('L' | 'l'))") 
							  << _xtr(L"XML Definition :  name    ::=    (Letter | '_' | ':') (NameChar)*") 
				              << XIMOL_AS_ERROR;
	return xos;
}

//-----------------------------------------------------------------------------
// read a pi_target
/* pi_target    ::=    name - (('X' | 'x') ('M' | 'm') ('L' | 'l')) 
  */
//-----------------------------------------------------------------------------
xistream& read_pi_target(xistream& xis, xstring & xstr)
{
	read_name(xis,xstr);
	if (is_pi_target(xstr)) return xis;
	xis.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"Parse pi_target, '%o' is not a pi_target.",str< ::std::string>::cast(xstr)) 
							  << _xtr(L"XML Definition : pi_target    ::=    name - (('X' | 'x') ('M' | 'm') ('L' | 'l'))") 
							  << _xtr(L"XML Definition :  name    ::=    (Letter | '_' | ':') (NameChar)*") 
				              << XIMOL_AS_ERROR;
	return xis;
}

//-----------------------------------------------------------------------------
// write a PI
/* PI    ::=    '<?' pi_target (S (Char* - (Char* '?>' Char*)))? '?>' 
  */
//-----------------------------------------------------------------------------
xostream& write_pi(xostream& xos, xstring const & pi_target, xstring const & xext)
{
	if (! (xos.good()) ) return xos;
	write_xchar(xos,XCHAR_LESS_THAN_SIGN);
	write_xchar(xos,XCHAR_QUESTION_MARK);
	write_pi_target(xos,pi_target);
	if (xext.length()>0)
	{
		write_space(xos);
		if (is_string_with_forbidden_serie(xext,is_char,"?>"))
		{
			xos<<xext;
		} else {
			xos.setstate(std::ios::failbit);  
			XIMOL_THROW << _xtr(L"Writing PI, '%o' is not a PI extension.",str< ::std::string>::cast(xext)) 
							  << _xtr(L"XML Definition : PI    ::=    '<?' pi_target (S (Char* - (Char* '?>' Char*)))? '?>'") 
				              << XIMOL_AS_ERROR;
			return xos;
		}
	}
	write_xchar(xos,XCHAR_QUESTION_MARK);
	write_xchar(xos,XCHAR_LESS_THAN_SIGN);
	return xos;
}

//-----------------------------------------------------------------------------
// read a PI
/* PI    ::=    '<?' pi_target (S (Char* - (Char* '?>' Char*)))? '?>' 
  */
//-----------------------------------------------------------------------------
xistream& read_pi(xistream& xis, xstring & xstr,xstring & xext, int nb_read)
{
	if (! (xis.good()) ) return xis;
	clear_string(xstr);
	clear_string(xext);
	
	switch(nb_read){
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN, _xtr(L"comment parsing a '<'.XML Definition : PI    ::=    '<?' pi_target (S (Char* - (Char* '?>' Char*)))? '?>'") );
	case 1: read_xchar(xis,XCHAR_QUESTION_MARK,  _xtr(L"comment parsing a '?'.XML Definition : PI    ::=    '<?' pi_target (S (Char* - (Char* '?>' Char*)))? '?>'") );
	}

	read_pi_target(xis,xstr);
	read_optionnal_space(xis);
	read_string_with_forbidden_serie(xis,xext,is_char,"?>");

	read_xchar(xis,XCHAR_QUESTION_MARK,
					         _xtr(L"comment parsing a '>'.XML Definition : PI    ::=    '<?' pi_target (S (Char* - (Char* '?>' Char*)))? '?>'") );
	read_xchar(xis,XCHAR_GREATER_THAN_SIGN,
					         _xtr(L"comment parsing a '>'.XML Definition : PI    ::=    '<?' pi_target (S (Char* - (Char* '?>' Char*)))? '?>'") );
	return xis;
}

//-----------------------------------------------------------------------------
// read a PI
/* PI    ::=    '<?' pi_target (S (Char* - (Char* '?>' Char*)))? '?>' 
  */
//-----------------------------------------------------------------------------
xistream& read_pi(xistream& xis, int nb_read)
{
	xstring xstr,xext;
	read_pi(xis,xstr,xext,nb_read);
	xis.context.add_processing_instruction(xstr,xext);
	return xis;
}

//-----------------------------------------------------------------------------
// write a cd_end
/* cd_end    ::=    ']]>' 
  */
//-----------------------------------------------------------------------------
xostream& write_cd_end(xostream& xos)
{
	write_xchar(xos,XCHAR_RIGHT_SQUARE_BRACKET);
	write_xchar(xos,XCHAR_RIGHT_SQUARE_BRACKET);
	write_xchar(xos,XCHAR_GREATER_THAN_SIGN);
	return xos;
}

//-----------------------------------------------------------------------------
// read a cd_end
/* cd_end    ::=    ']]>' 
  */
//-----------------------------------------------------------------------------
xistream& read_cd_end(xistream& xis, int nb_read)
{
	if (! (xis.good()) ) return xis;
	switch(nb_read){
	case 0: read_xchar(xis,XCHAR_RIGHT_SQUARE_BRACKET, _xtr(L"comment parsing a ']'.XML Definition : cd_end    ::=    ']]>'") );
	case 1: read_xchar(xis,XCHAR_RIGHT_SQUARE_BRACKET, _xtr(L"comment parsing a ']'.XML Definition : cd_end    ::=    ']]>'") );
	case 2: read_xchar(xis,XCHAR_GREATER_THAN_SIGN,    _xtr(L"comment parsing a '>'.XML Definition : cd_end    ::=    ']]>'") );
	}
	return xis;
}

//-----------------------------------------------------------------------------
// write a cd_start
/* cd_start    ::=    '<![CDATA[' 
  */
//-----------------------------------------------------------------------------
xostream& write_cd_start(xostream& xos)
{
	write_xchar(xos,XCHAR_LESS_THAN_SIGN);
	write_xchar(xos,XCHAR_EXCLAMATION_MARK);
	write_xchar(xos,XCHAR_LEFT_SQUARE_BRACKET);
	write_xchar(xos,XCHAR_LATIN_CAPITAL_LETTER_C);
	write_xchar(xos,XCHAR_LATIN_CAPITAL_LETTER_D);
	write_xchar(xos,XCHAR_LATIN_CAPITAL_LETTER_A);
	write_xchar(xos,XCHAR_LATIN_CAPITAL_LETTER_T);
	write_xchar(xos,XCHAR_LATIN_CAPITAL_LETTER_A);
	write_xchar(xos,XCHAR_LEFT_SQUARE_BRACKET);
	return xos;
}

//-----------------------------------------------------------------------------
// read a cd_start
/* cd_start    ::=    '<![CDATA[' 
  */
//-----------------------------------------------------------------------------
xistream& read_cd_start(xistream& xis, int nb_read)
{
	if (! (xis.good()) ) return xis;
	
	switch(nb_read){
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN,         _xtr(L"comment parsing a '<'.XML Definition : cd_start    ::=    '<![CDATA['") );
	case 1: read_xchar(xis,XCHAR_EXCLAMATION_MARK,       _xtr(L"comment parsing a '!'.XML Definition : cd_start    ::=    '<![CDATA['") );
	case 2: read_xchar(xis,XCHAR_LEFT_SQUARE_BRACKET,    _xtr(L"comment parsing a '['.XML Definition : cd_start    ::=    '<![CDATA['") );
	case 3: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_C, _xtr(L"comment parsing a 'C'.XML Definition : cd_start    ::=    '<![CDATA['") );
	case 4: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_D, _xtr(L"comment parsing a 'D'.XML Definition : cd_start    ::=    '<![CDATA['") );
	case 5: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_A, _xtr(L"comment parsing a 'A'.XML Definition : cd_start    ::=    '<![CDATA['") );
	case 6: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : cd_start    ::=    '<![CDATA['") );
	case 7: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_A, _xtr(L"comment parsing a 'A'.XML Definition : cd_start    ::=    '<![CDATA['") );
	case 8: read_xchar(xis,XCHAR_LEFT_SQUARE_BRACKET,    _xtr(L"comment parsing a '['.XML Definition : cd_start    ::=    '<![CDATA['") );
	}
	return xis;
}

//-----------------------------------------------------------------------------
// write a CData
/* CData    ::=    (Char* - (Char* ']]>' Char*))  
  */
//-----------------------------------------------------------------------------
xostream& write_cdata(xostream& xos, xstring const & xstr)
{
	if (is_string_with_forbidden_serie(xstr,is_char,"]]>")) 
	{
		xos<<xstr;
		return xos;
	}
	
	//failed
	xos.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"write CData '%o'.",str< ::std::string>::cast(xstr)) 
					  << _xtr(L"XML Definition : CData    ::=    (Char* - (Char* ']]>' Char*))") 
		              << XIMOL_AS_ERROR;
	return xos;
}

//-----------------------------------------------------------------------------
// read a CData
/* CData    ::=    (Char* - (Char* ']]>' Char*))  
  */
//-----------------------------------------------------------------------------
xistream& read_cdata(xistream& xis, xstring & xstr)
{
	return read_string_with_forbidden_serie(xis,xstr,is_char,"]]>");
}


//-----------------------------------------------------------------------------
// write a cd_sect
/* cd_sect    ::=    cd_start CData cd_end 
  */
//-----------------------------------------------------------------------------
xostream& write_cd_sect(xostream& xos, xstring const & xstr)
{
	write_cd_start(xos);
	write_cdata(xos,xstr);
	write_cd_end(xos);
	return xos;
}

//-----------------------------------------------------------------------------
// read a cd_sect
/* cd_sect    ::=    cd_start CData cd_end 
  */
//-----------------------------------------------------------------------------
xistream& read_cd_sect(xistream& xis, xstring & xstr, int nb_char)
{
	read_cd_start(xis,nb_char);
	read_cdata(xis,xstr);
	read_cd_end(xis); 
	return xis;
}

//-----------------------------------------------------------------------------
// write a Eq
/* Eq    ::=    S? '=' S?  
  */
//-----------------------------------------------------------------------------
xostream& write_eq(xostream& xos)
{
	write_xchar(xos,XCHAR_EQUALS_SIGN);
	return xos;
}

//-----------------------------------------------------------------------------
// read a Eq
/* Eq    ::=    S? '=' S?  
  */
//-----------------------------------------------------------------------------
xistream& read_eq(xistream& xis)
{
	read_optionnal_space(xis);
	read_xchar(xis,XCHAR_EQUALS_SIGN,_xtr(L"Parsing an equality"));
	read_optionnal_space(xis);
	return xis;
}

//-----------------------------------------------------------------------------
// Intermediate function
//-----------------------------------------------------------------------------
bool IsVersionNumChar(xchar_t c)
{
	return ( XBET(0x0041,0x005a)
		  || XBET(0x0061,0x007a)
		  || XBET(0x0030,0x0039)
		  || XEQ(0x005f)
		  || XEQ(0x002e)
		  || XEQ(0x003a)
		  || XEQ(0x002d)
			);
}

//-----------------------------------------------------------------------------
// Test VersionNum
/* VersionNum    ::=    ([a-zA-Z0-9_.:] | '-')+ 
  */
//-----------------------------------------------------------------------------
bool is_version_num(xstring const & xstr)
{
	if (xstr.empty()) return false;
	return is_xstring(xstr,IsVersionNumChar);
}

//-----------------------------------------------------------------------------
// write a VersionNum
/* VersionNum    ::=    ([a-zA-Z0-9_.:] | '-')+ 
  */
//-----------------------------------------------------------------------------
xostream& write_version_num(xostream& xos, xstring const & xstr)
{
	if (is_version_num(xstr)) 
	{
		xos<<xstr;
		return xos;
	}

	//failed
	xos.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"write VersionNum '%o'.",str< ::std::string>::cast(xstr)) 
					  << _xtr(L"XML Definition : VersionNum    ::=    ([a-zA-Z0-9_.:] | '-')+") 
		              << XIMOL_AS_ERROR;
	return xos;
}

//-----------------------------------------------------------------------------
// read a VersionNum
/* VersionNum    ::=    ([a-zA-Z0-9_.:] | '-')+ 
  */
//-----------------------------------------------------------------------------
xistream& read_version_num(xistream& xis, xstring & xstr)
{
	read_xstring(xis,xstr,IsVersionNumChar);
	if (!xstr.empty()) return xis;

	//failed
	xis.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"Parsing VersionNum, and it seem to be empty.") 
					  << _xtr(L"XML Definition : VersionNum    ::=    ([a-zA-Z0-9_.:] | '-')+") 
		              << XIMOL_AS_ERROR;
	return xis;
}

//-----------------------------------------------------------------------------
// write a VersionInfo
/* VersionInfo    ::=    S 'version' Eq ("'" VersionNum "'" | '"' VersionNum '"')  
  */
//-----------------------------------------------------------------------------
xostream& write_version_info(xostream& xos, xstring const & xstr)
{
	write_space(xos);
	xos<<"version";
	write_eq(xos);
	write_xchar(xos,XCHAR_APOSTROPHE);
	write_version_num(xos,xstr);
	write_xchar(xos,XCHAR_APOSTROPHE);
    xos.context.set_version_num(xstr);
	return xos;
}

//-----------------------------------------------------------------------------
// read a VersionInfo
/* VersionInfo    ::=    S 'version' Eq ("'" VersionNum "'" | '"' VersionNum '"')  
  */
//-----------------------------------------------------------------------------
xistream& read_version_info(xistream& xis, xstring & xstr, bool read_first_space)
{
	if (read_first_space) read_space(xis);
	read_xstring(xis,"version",_xtr(L"Parsing version number."));
	read_eq(xis);

	xchar_t xquote;
	read_xchar(xis,xquote,IsQuote,_xtr(L"Version parsing first quote.\nXML Definition : VersionInfo    ::=    S 'version' Eq (\"'\" VersionNum \"'\" | '\"' VersionNum '\"')"));
	read_version_num(xis,xstr);
	read_xchar(xis,xquote,_xtr(L"Version parsing last quote.\nXML Definition : VersionInfo    ::=    S 'version' Eq (\"'\" VersionNum \"'\" | '\"' VersionNum '\"')"));

    xis.context.set_version_num(xstr);

	return xis;
}

//-----------------------------------------------------------------------------
// read a VersionInfo
/* VersionInfo    ::=    S 'version' Eq ("'" VersionNum "'" | '"' VersionNum '"')  
  */
//-----------------------------------------------------------------------------
xistream& read_version_info(xistream& xis, bool read_first_space)
{
	xstring xstr;
	read_version_info(xis,xstr);
	xis.context.set_version_num(xstr);
	return xis;
}

//-----------------------------------------------------------------------------
// intermediate function
//-----------------------------------------------------------------------------
bool IsFirstEncNameChar(xchar_t c)
{
	return ( XBET(0x0041,0x005a)
		  || XBET(0x0061,0x007a)
		   );
}

//-----------------------------------------------------------------------------
// intermediate function
//-----------------------------------------------------------------------------
bool IsSecondEncNameChar(xchar_t c)
{
	return ( XBET(0x0041,0x005a)
		  || XBET(0x0061,0x007a)
		  || XBET(0x0030,0x0039)
		  || XEQ(0x005f)
		  || XEQ(0x002e)
		  || XEQ(0x002d)
			);
}

//-----------------------------------------------------------------------------
// Test EncName
/* EncName    ::=    [A-Za-z] ([A-Za-z0-9._] | '-')* 
  */
//-----------------------------------------------------------------------------
bool is_enc_name(xstring const & xstr)
{
	if (xstr.empty()) return false;
	return ( (IsFirstEncNameChar(xstr[0]))
		   &&(is_xstring(xstr,IsSecondEncNameChar)));
}

//-----------------------------------------------------------------------------
// write a EncName
/* EncName    ::=    [A-Za-z] ([A-Za-z0-9._] | '-')* 
  */
//-----------------------------------------------------------------------------
xostream& write_enc_name(xostream& xos, xstring const & xstr)
{
	if (is_enc_name(xstr)) 
	{
		xos<<xstr;
		return xos;
	}

	//failed
	xos.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"write EncName '%o'.",str< ::std::string>::cast(xstr)) 
					  << _xtr(L"XML Definition : EncName    ::=    [A-Za-z] ([A-Za-z0-9._] | '-')*") 
		              << XIMOL_AS_ERROR;
	return xos;
}

//-----------------------------------------------------------------------------
// read a EncName
/* EncName    ::=    [A-Za-z] ([A-Za-z0-9._] | '-')* 
  */
//-----------------------------------------------------------------------------
xistream& read_enc_name(xistream& xis, xstring & xstr)
{
	if (! (xis.good()) ) return xis;
	clear_string(xstr);
	xchar_t xc;
	read_xchar(xis,xc,IsFirstEncNameChar,_xtr(L"Parsing  first char of EncName.\nXML Definition : EncName    ::=    [A-Za-z] ([A-Za-z0-9._] | '-')*"));
	xstr+=xc;
	read_xstring(xis,xstr,IsSecondEncNameChar,false);

	return xis;
}

//-----------------------------------------------------------------------------
// write a EncodingDecl
/* EncodingDecl    ::=    S 'encoding' Eq ('"' EncName '"' | "'" EncName "'" ) 
  */
//-----------------------------------------------------------------------------
xostream& write_encoding_decl(xostream& xos, xstring const & xstr)
{
	write_space(xos);
	xos<<"encoding";
	write_eq(xos);
	write_xchar(xos,XCHAR_APOSTROPHE);
	write_enc_name(xos,xstr);
	write_xchar(xos,XCHAR_APOSTROPHE);
	xos.context.set_encoding_decl(xstr);
	return xos;
}

//-----------------------------------------------------------------------------
// read a EncodingDecl
/* EncodingDecl    ::=    S 'encoding' Eq ('"' EncName '"' | "'" EncName "'" ) 
  */
//-----------------------------------------------------------------------------
xistream& read_encoding_decl(xistream& xis, xstring & xstr, bool read_first_space)
{
	if (read_first_space) read_space(xis);
	read_xstring(xis,"encoding",_xtr(L"Parsing encoding declaration."));
	read_eq(xis);

	xchar_t xquote;
	read_xchar(xis,xquote,IsQuote,_xtr(L"Encoding declaration parsing first quote.\nXML Definition : EncodingDecl    ::=    S 'encoding' Eq ('\"' EncName '\"' | \"'\" EncName \"'\" )"));
	read_enc_name(xis,xstr);
	xis.context.set_encoding_decl(xstr);
	// xis.encoding(str< ::std::string>::cast(xstr));
	read_xchar(xis,xquote,_xtr(L"Encoding declaration parsing first quote.\nXML Definition : EncodingDecl    ::=    S 'encoding' Eq ('\"' EncName '\"' | \"'\" EncName \"'\" )"));
	return xis;
}

//-----------------------------------------------------------------------------
// write a SDDecl
/* SDDecl    ::=    S 'standalone' Eq (("'" ('yes' | 'no') "'") | ('"' ('yes' | 'no') '"')) 
  */
//-----------------------------------------------------------------------------
xostream& write_sd_decl(xostream& xos, bool standalone)
{
	write_space(xos);
	xos<<"standalone";
	write_eq(xos);
	write_xchar(xos,XCHAR_APOSTROPHE);
	if (standalone) xos<<"yes";
	else xos<<"no";
	write_xchar(xos,XCHAR_APOSTROPHE);
    xos.context.set_sd_decl(standalone);
	return xos;
}

//-----------------------------------------------------------------------------
// read a SDDecl
/* SDDecl    ::=    S 'standalone' Eq (("'" ('yes' | 'no') "'") | ('"' ('yes' | 'no') '"')) 
  */
//-----------------------------------------------------------------------------
xistream& read_sd_decl(xistream& xis, bool & standalone, bool read_first_space)
{
	if (read_first_space) read_space(xis);
	read_xstring(xis,"standalone",_xtr(L"Parsing standalone declaration."));
	read_eq(xis);

	xchar_t xquote;
	read_xchar(xis,xquote,IsQuote,_xtr(L"Standalone declaration parsing first quote.\nXML Definition : SDDecl    ::=    S 'standalone' Eq ((\"'\" ('yes' | 'no') \"'\") | ('\"' ('yes' | 'no') '\"'))"));
	xstring xstr;
	xstring xyes=str< ::std::wstring>::cast("yes");
	xstring xno=str< ::std::wstring>::cast("no");

	read_xstring(xis,xstr,IsFirstEncNameChar);
	
	read_xchar(xis,xquote,IsQuote,_xtr(L"Standalone declaration parsing last quote.\nXML Definition : SDDecl    ::=    S 'standalone' Eq ((\"'\" ('yes' | 'no') \"'\") | ('\"' ('yes' | 'no') '\"'))"));

	standalone=(xstr==xyes);
	xis.context.set_sd_decl(standalone);

	if (xstr==xyes) { return xis; }
	if (xstr==xno) { return xis; }

	//failed
	xis.setstate(std::ios::failbit);  
	XIMOL_THROW << _xtr(L"Parsing SDDecl, and it seem to be wrong ('%o').",str< ::std::string>::cast(xstr)) 
					  << _xtr(L"XML Definition : SDDecl    ::=    S 'standalone' Eq ((\"'\" ('yes' | 'no') \"'\") | ('\"' ('yes' | 'no') '\"'))") 
		              << XIMOL_AS_ERROR;
	return xis;
}

//-----------------------------------------------------------------------------
// write a XMLDecl
/* XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>' 
  */
//-----------------------------------------------------------------------------
xostream& write_xml_decl(xostream& xos, 
							  xstring const & version_info, 
							  xstring const & encoding_decl, 
							  xstring const & standalone_decl)
{
	xos<<"<?xml";
	write_version_info(xos,str< ::std::wstring>::cast(version_info));
	if (!encoding_decl.empty()) write_encoding_decl(xos,str< ::std::wstring>::cast(encoding_decl));
	if (standalone_decl==str< ::std::wstring>::cast("yes")) write_sd_decl(xos,true);
	if (standalone_decl==str< ::std::wstring>::cast("no")) write_sd_decl(xos,false);
	write_space(xos);
	xos<<"?>";
    if (!encoding_decl.empty())
        xos.encoding(str< ::std::string>::cast(xos.context.get_encoding_decl()).c_str());
	return xos;
}

//-----------------------------------------------------------------------------
// write a XMLDecl
/** @ingroup parser_write
<pre>
	XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>' 
</pre>
  */
//-----------------------------------------------------------------------------
xostream& write_xml_decl(xostream& xos)
{
	return write_xml_decl(xos,
						xos.context.get_version_num(),
						xos.context.get_encoding_decl(),
						xos.context.get_sd_decl()?( str< ::std::wstring>::cast("yes")): (str< ::std::wstring>::cast("no")));
}

//-----------------------------------------------------------------------------
// Intermediate function
//-----------------------------------------------------------------------------
bool IsCharESQ(xchar_t c)
{
	return ( XEQ(0x0065) || XEQ(0x0073) || XEQ(0x003f) ); // test 'es?'
}

//-----------------------------------------------------------------------------
// Intermediate function
//-----------------------------------------------------------------------------
bool IsCharSQ(xchar_t c)
{
	return ( XEQ(0x0073) || XEQ(0x003f) );  // test 's?'
}

//-----------------------------------------------------------------------------
// read a XMLDecl
/* XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>' 
  */
//-----------------------------------------------------------------------------
xistream& read_xml_decl(xistream& xis, 
							 xstring& version_info, 
							 xstring& encoding_decl, 
							 bool & standalone_decl, 
							 int nb_read)
{
	if (! (xis.good()) ) return xis;
	clear_string(version_info);
	clear_string(encoding_decl);
	standalone_decl=false;
	
	switch(nb_read){
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN,       _xtr(L"comment parsing a '<'.XML Definition : XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'") );
	case 1: read_xchar(xis,XCHAR_QUESTION_MARK,        _xtr(L"comment parsing a '?'.XML Definition : XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'") );
	case 2: read_xchar(xis,XCHAR_LATIN_SMALL_LETTER_X, _xtr(L"comment parsing a 'x'.XML Definition : XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'") );
	case 3: read_xchar(xis,XCHAR_LATIN_SMALL_LETTER_M, _xtr(L"comment parsing a 'm'.XML Definition : XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'") );
	case 4: read_xchar(xis,XCHAR_LATIN_SMALL_LETTER_L, _xtr(L"comment parsing a 'l'.XML Definition : XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'") );
	}
	read_version_info(xis,version_info);
	read_optionnal_space(xis);

	xchar_t xc;
	read_xchar(xis,xc,IsCharESQ,_xtr(L"comment parsing a ('e'|'s'|'?').XML Definition : XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'") );
	xis.putback(xc);

	if (xc==XCHAR_LATIN_SMALL_LETTER_E) 
	{
		read_encoding_decl(xis,encoding_decl,false);
		read_optionnal_space(xis);
		read_xchar(xis,xc,IsCharSQ,_xtr(L"comment parsing a ('s'|'?').XML Definition : XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'") );
		xis.putback(xc);
	}
	
	if (xc==XCHAR_LATIN_SMALL_LETTER_S) 
	{
		read_sd_decl(xis,standalone_decl,false);
	}
	
	read_optionnal_space(xis);

	read_xstring(xis,"?>",_xtr(L"comment parsing a '?>'.XML Definition : XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'") );

    if (!encoding_decl.empty())
        xis.encoding(str< ::std::string>::cast(xis.context.get_encoding_decl()).c_str());
    return xis;
}

//-----------------------------------------------------------------------------
// read a XMLDecl
/** @ingroup parser_read
<pre>
	XMLDecl    ::=    '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>' 
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_xml_decl(xistream& xis, int nb_read)
{
	xstring version_info;
	xstring encoding_decl;
	bool    standalone_decl;
	return read_xml_decl(xis,version_info,encoding_decl,standalone_decl,nb_read);
}

//-----------------------------------------------------------------------------
// write a ExternalID
/* ExternalID    ::=    'SYSTEM' S system_literal | 'PUBLIC' S pubid_literal S system_literal  
  */
//-----------------------------------------------------------------------------
xostream& write_external_id(xostream& xos, xstring const & system_literal, xstring const & pub_id_literal)
{
	if (!pub_id_literal.empty())
	{
		xos<<"PUBLIC";
		write_space(xos);
		write_pubid_literal(xos,pub_id_literal);
	} else {
		xos<<"SYSTEM";
	}
	write_space(xos);
	write_system_literal(xos,system_literal);

	return xos;
}

//-----------------------------------------------------------------------------
// intermediate function
//-----------------------------------------------------------------------------
bool IsExternalCharSP(xchar_t c)
{
	return ( XEQ(0x0053) || XEQ(0x0050) );
}

//-----------------------------------------------------------------------------
// read a ExternalID
/* ExternalID    ::=    'SYSTEM' S system_literal | 'PUBLIC' S pubid_literal S system_literal  
  */
//-----------------------------------------------------------------------------
xistream& read_external_id(xistream& xis, xstring& system_literal, xstring& pub_id_literal)
{
	if (! (xis.good()) ) return xis;
	clear_string(system_literal);
	clear_string(pub_id_literal);
	
	xchar_t xc;
	read_xchar(xis,xc,IsExternalCharSP,_xtr(L"Parsing a char 'S' or 'P' for an external id.\nXML Definition : ExternalID    ::=    'SYSTEM' S system_literal | 'PUBLIC' S pubid_literal S system_literal  "));
	xis.putback(xc);

	if (xc==XCHAR_LATIN_CAPITAL_LETTER_P)
	{
		read_xstring(xis,"PUBLIC",_xtr(L"Parsing 'PUBLIC' for an external id.\nXML Definition : ExternalID    ::=    'SYSTEM' S system_literal | 'PUBLIC' S pubid_literal S system_literal  "));
		read_space(xis);
		read_pubid_literal(xis,pub_id_literal);
	} else {
		read_xstring(xis,"SYSTEM",_xtr(L"Parsing 'SYSTEM' for an external id.\nXML Definition : ExternalID    ::=    'SYSTEM' S system_literal | 'PUBLIC' S pubid_literal S system_literal  "));
	}
	
	read_space(xis);
	read_system_literal(xis,system_literal);

	return xis;
}

//-----------------------------------------------------------------------------
// write a PublicID
/* PublicID    ::=    'PUBLIC' S pubid_literal 
  */
//-----------------------------------------------------------------------------
xostream& write_public_id(xostream& xos, xstring const & pub_id_literal)
{
	xos<<"PUBLIC";
	write_space(xos);
	write_pubid_literal(xos,pub_id_literal);
	return xos;
}

//-----------------------------------------------------------------------------
// read a PublicID
/* PublicID    ::=    'PUBLIC' S pubid_literal 
  */
//-----------------------------------------------------------------------------
xistream& read_public_id(xistream& xis, xstring& pub_id_literal)
{
	if (! (xis.good()) ) return xis;
	clear_string(pub_id_literal);
	
	read_xstring(xis,"PUBLIC",_xtr(L"Parsing 'PUBLIC' for a public id.\nXML Definition : PublicID    ::=    'PUBLIC' S pubid_literal "));
	read_space(xis);
	read_pubid_literal(xis,pub_id_literal);

	return xis;
}

//-----------------------------------------------------------------------------
// write a NotationDecl
/* NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>' 
  */
//-----------------------------------------------------------------------------
xostream& write_notation_decl(xostream& xos, xstring const & name, xstring const & system_literal, xstring const & pub_id_literal)
{
	xos<<"<!NOTATION";
	write_space(xos);
	write_name(xos,name);
	write_space(xos);
	if (system_literal.empty()) write_public_id(xos,pub_id_literal);
	else write_external_id(xos,system_literal,pub_id_literal);
	write_xchar(xos,XCHAR_GREATER_THAN_SIGN);
	return xos;
}

//-----------------------------------------------------------------------------
// read a NotationDecl
/* NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>' 
  */
//-----------------------------------------------------------------------------
xistream& read_notation_decl(xistream& xis, xstring& name, xstring& system_literal, xstring& pub_id_literal, int nb_read)
{
	if (! (xis.good()) ) return xis;
	clear_string(name);
	clear_string(system_literal);
	clear_string(pub_id_literal);
	
	
	switch(nb_read){
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN,         _xtr(L"comment parsing a '<'.XML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>'") );
	case 1: read_xchar(xis,XCHAR_EXCLAMATION_MARK,       _xtr(L"comment parsing a '!'.XML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>'") );
	case 2: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_N, _xtr(L"comment parsing a 'N'.XML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>'") );
	case 3: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_O, _xtr(L"comment parsing a 'O'.XML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>'") );
	case 4: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>'") );
	case 5: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_A, _xtr(L"comment parsing a 'A'.XML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>'") );
	case 6: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>'") );
	case 7: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_I, _xtr(L"comment parsing a 'I'.XML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>'") );
	case 8: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_O, _xtr(L"comment parsing a 'O'.XML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>'") );
	case 9: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_N, _xtr(L"comment parsing a 'N'.XML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>'") );
	}

	read_space(xis);
	read_name(xis,name);
	read_space(xis);
	xchar_t xc;
	read_xchar(xis,xc,IsExternalCharSP,_xtr(L"Parsing a char 'S' or 'P' for a notation declaration.\nXML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>' "));
	xis.putback(xc);

	if (xc==XCHAR_LATIN_CAPITAL_LETTER_P)
	{
		read_xstring(xis,"PUBLIC",_xtr(L"Parsing 'PUBLIC' for a notation declaration.\nXML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>' "));
		read_space(xis);
		read_pubid_literal(xis,pub_id_literal);
		read_optionnal_space(xis);
		xchar_t xc;
		if (xis.get(xc)) 
		{
			xis.putback(xc);
			if (xc!=XCHAR_GREATER_THAN_SIGN) read_system_literal(xis,system_literal);
		}
	} else {
		read_xstring(xis,"SYSTEM",_xtr(L"Parsing 'SYSTEM' for a notation declaration.\nXML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>' "));
		read_space(xis);
		read_system_literal(xis,system_literal);
	}

	read_optionnal_space(xis);
	read_xchar(xis,XCHAR_GREATER_THAN_SIGN,_xtr(L"Parsing a char '>' for a notation declaration.\nXML Definition : NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>' "));
	
	return xis;
}

//-----------------------------------------------------------------------------
// read a NotationDecl
/** @ingroup parser_read
<pre>
	NotationDecl    ::=    '<!NOTATION' S name S (ExternalID | PublicID) S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_notation_decl(xistream& xis, int nb_read)
{
	xstring name, system_literal, pub_id_literal;
	read_notation_decl(xis,name,system_literal,pub_id_literal,nb_read);
	xis.context.add_notation_decl(name,system_literal,pub_id_literal);
	return xis;
}

//-----------------------------------------------------------------------------
// write an open stag
/* @ingroup parser_write
	stag    ::=    '<' QName (S Attribute)* S? '>' 
  */
//-----------------------------------------------------------------------------
xostream& write_open_stag(xostream& xos, xstring const & name, const XIMOL_XML_NAMESPACE_PATH::attributes& att, xstring const & uri)
{
	if (xos.context.is_open_stag()) 
		write_stag(xos,xos.context.get_level_tag(),xos.context.get_level_short_ns_tag());
			
	xos.context.add_new_level(uri,name,att).set_open_stag();
	return xos;
}

//-----------------------------------------------------------------------------
// write an open stag
/* @ingroup parser_write
	stag    ::=    '<' QName (S Attribute)* S? '>' 
  */
//-----------------------------------------------------------------------------
xostream& write_open_stag(xostream& xos, xstring const & name, xstring const & uri)
{
	XIMOL_XML_NAMESPACE_PATH::attributes att;
	return write_open_stag(xos,name,att,uri);
}

//-----------------------------------------------------------------------------
// write a stag
/* @ingroup parser_write
	stag    ::=    '<' name (S Attribute)* S? '>' 
  */
//-----------------------------------------------------------------------------
xostream& write_stag(xostream& xos, xstring const & name, const XIMOL_XML_NAMESPACE_PATH::attributes& att, xstring const & uri)
{
	write_xchar(xos,XCHAR_LESS_THAN_SIGN);
	if (xos.context.is_open_stag()) 
	{
		// add attributes but do not change the name.
		xos.context.add_level_attributes(att); 
	} else {
		xos.context.add_new_level(uri,name,att);
	}
	write_qname(xos,xos.context.get_level_tag(),xos.context.get_level_short_ns_tag());
	xos << xos.context.get_level_attributes();
	write_xchar(xos,XCHAR_GREATER_THAN_SIGN);

	xos.context.close_open_stag();
	return xos;
}

//-----------------------------------------------------------------------------
// write a stag
/* @ingroup parser_write
	stag    ::=    '<' name (S Attribute)* S? '>' 
  */
//-----------------------------------------------------------------------------
xostream& write_stag(xostream& xos, xstring const & name)
{
	XIMOL_XML_NAMESPACE_PATH::attributes att;
	return write_stag(xos,name,att);
}

//-----------------------------------------------------------------------------
// write a stag
/* @ingroup parser_write
	stag    ::=    '<' name (S Attribute)* S? '>' 
  */
//-----------------------------------------------------------------------------
xostream& write_stag(xostream& xos, xstring const & name, xstring const & uri)
{
	XIMOL_XML_NAMESPACE_PATH::attributes att;
	return write_stag(xos,name,att,uri);
}

//-----------------------------------------------------------------------------
// read an open stag
/* @ingroup parser_read
	stag    ::=    '<' QName (S Attribute)* S? '>'  
  */
//-----------------------------------------------------------------------------
xistream& read_open_stag(xistream& xis, xstring& name, XIMOL_XML_NAMESPACE_PATH::attributes& att, xstring& uri, int nb_read)
{
	if (! (xis.good()) ) return xis;
	clear_string(uri);
	clear_string(name);
	att.clear();

	if (xis.context.is_open_stag()) 
	{
		name=xis.context.get_level_tag();
		uri=xis.context.get_level_ns_tag();
		att=xis.context.get_level_attributes();
		return xis;
	}
	
	switch(nb_read){
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN, _xtr(L"comment parsing a '<'.XML Definition : stag    ::=    '<' name (S Attribute)* S? '>'") );
	}

	xstring short_ns;
	read_qname(xis,name,short_ns);
	read_optionnal_space(xis);
	xis>>att;
	read_optionnal_space(xis);

	XIMOL_XML_NAMESPACE_PATH::attributes::const_ns_iterator itr_uri =
		att.find_namespace(short_ns);

	if(itr_uri != att.ns_end())
		uri = itr_uri->first;

	if(uri.empty()) uri = xis.context.get_namespace(short_ns);
	if(uri.empty()) uri = short_ns;

	if(uri.empty()) {
		itr_uri = att.find_namespace();

		if(itr_uri != att.ns_end())
			uri = itr_uri->first;
	}

	if(uri.empty()) uri = xis.context.get_default_namespace();

	xis.context.add_new_level(uri,name,att).set_open_stag();

	xchar_t xc;
	if (! xis.get(xc)) 
		XIMOL_THROW << _xtr(L"Parsing a char '>' for a notation declaration.\nSTag    ::=    '<' name (S Attribute)* S? '>'")
					<< XIMOL_AS_ERROR;
	
	if (xc==XCHAR_SOLIDUS) 
	{
		xis.context.set_open_etag();
	} else {
		xis.putback(xc);
	}
	
	read_xchar(xis,XCHAR_GREATER_THAN_SIGN,_xtr(L"Parsing a char '>' for a notation declaration.\nSTag    ::=    '<' name (S Attribute)* S? '>'"));

	return xis;
}

//-----------------------------------------------------------------------------
// read an open stag
/* @ingroup parser_read
	stag    ::=    '<' QName (S Attribute)* S? '>'  
  */
//-----------------------------------------------------------------------------
xistream& read_open_stag(xistream& xis, xstring& name, xstring & uri, int nb_read)
{
	XIMOL_XML_NAMESPACE_PATH::attributes att;
	return read_open_stag(xis,name,att,uri,nb_read);
}

//-----------------------------------------------------------------------------
// read an open stag
/* @ingroup parser_read
	stag    ::=    '<' QName (S Attribute)* S? '>'  
  */
//-----------------------------------------------------------------------------
xistream& read_open_stag(xistream& xis, xstring& name, int nb_read)
{
	xstring uri;
	return read_open_stag(xis,name,uri,nb_read);
}

//-----------------------------------------------------------------------------
// read a stag
/* @ingroup parser_read
	stag    ::=    '<' QName (S Attribute)* S? '>'  
  */
//-----------------------------------------------------------------------------
xistream& read_stag(xistream& xis, xstring& name, XIMOL_XML_NAMESPACE_PATH::attributes& att, xstring& uri, int nb_read)
{
	if (! (xis.good()) ) return xis;
	clear_string(uri);
	clear_string(name);
	att.clear();
	
	if (xis.context.is_open_stag()) 
	{
		name=xis.context.get_level_tag();
		uri=xis.context.get_level_ns_tag();
		att=xis.context.get_level_attributes();
	} else {
		read_open_stag(xis,name,att,uri,nb_read);
	}

	xis.context.close_open_stag();

	return xis;
}

//-----------------------------------------------------------------------------
// read a stag
/* @ingroup parser_read
	stag    ::=    '<' QName (S Attribute)* S? '>'  
  */
//-----------------------------------------------------------------------------
xistream& read_stag(xistream& xis, xstring& name, xstring& uri, int nb_read)
{
	XIMOL_XML_NAMESPACE_PATH::attributes att;
	return read_stag(xis,name,att,uri,nb_read);
}

//-----------------------------------------------------------------------------
// read a stag
/* @ingroup parser_read
	stag    ::=    '<' QName (S Attribute)* S? '>'  
  */
//-----------------------------------------------------------------------------
xistream& read_stag(xistream& xis, xstring& name, XIMOL_XML_NAMESPACE_PATH::attributes& att, int nb_read)
{
	xstring uri;
	return read_stag(xis,name,att,uri,nb_read);
}

//-----------------------------------------------------------------------------
// read a stag
/* @ingroup parser_read
	stag    ::=    '<' QName (S Attribute)* S? '>'  
  */
//-----------------------------------------------------------------------------
xistream& read_stag(xistream& xis, xstring& name, int nb_read)
{
	xstring uri;
	return read_stag(xis,name,uri,nb_read);
}

//-----------------------------------------------------------------------------
// write a etag
/* @ingroup parser_write
	'</' QName S? '>'
  */
//-----------------------------------------------------------------------------
xostream& write_etag(xostream& xos, xstring const & name)
{
	write_xchar(xos,XCHAR_LESS_THAN_SIGN);
	write_xchar(xos,XCHAR_SOLIDUS);
	write_qname(xos,name,xos.context.get_level_short_ns_tag());
	xos.context.destroy_level();
	write_xchar(xos,XCHAR_GREATER_THAN_SIGN);
	return xos;
}

//-----------------------------------------------------------------------------
// write a etag
/* @ingroup parser_write
	'</' QName S? '>'
  */
//-----------------------------------------------------------------------------
xostream& write_etag(xostream& xos, xstring const & name, xstring const & uri)
{
	write_xchar(xos,XCHAR_LESS_THAN_SIGN);
	write_xchar(xos,XCHAR_SOLIDUS);
	write_qname(xos,name,xos.context.get_short_namespace(uri));
	xos.context.destroy_level();
	write_xchar(xos,XCHAR_GREATER_THAN_SIGN);
	return xos;
}

//-----------------------------------------------------------------------------
// write a etag
/* @ingroup parser_write
	'</' QName S? '>'
  */
//-----------------------------------------------------------------------------
xostream& write_etag(xostream& xos)
{
	write_xchar(xos,XCHAR_LESS_THAN_SIGN);
	write_xchar(xos,XCHAR_SOLIDUS);
	write_qname(xos,xos.context.get_level_tag(),xos.context.get_level_short_ns_tag());
	xos.context.destroy_level();
	write_xchar(xos,XCHAR_GREATER_THAN_SIGN);
	return xos;
}

//-----------------------------------------------------------------------------
// read a etag
/* @ingroup parser_read
	'</' QName S? '>' 
  */
//-----------------------------------------------------------------------------
xistream& read_etag(xistream& xis, xstring& name, xstring& uri, int nb_read)
{
	if (! (xis.good()) ) return xis;
	clear_string(uri);
	clear_string(name);
	
	if (xis.context.is_open_etag()) 
	{
		uri=xis.context.get_level_ns_tag();
		name=xis.context.get_level_tag();
		xis.context.close_open_etag();
		xis.context.destroy_level();
		return xis;
	}

	
	switch(nb_read){
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN, _xtr(L"comment parsing a '<'.XML Definition : stag    ::=    '<' name (S Attribute)* S? '>'") );
	case 1: read_xchar(xis,XCHAR_SOLIDUS,        _xtr(L"comment parsing a '/'.XML Definition : stag    ::=    '<' name (S Attribute)* S? '>'") );
	}
	xstring short_ns;
	read_qname(xis,name,short_ns);
	uri=xis.context.get_namespace(short_ns);

	read_optionnal_space(xis);
	read_xchar(xis,XCHAR_GREATER_THAN_SIGN,_xtr(L"Parsing a char '>' for a notation declaration.\nSTag    ::=    '<' name (S Attribute)* S? '>'"));
	
	xis.context.destroy_level();

	return xis;
}

//-----------------------------------------------------------------------------
// read a etag
/* @ingroup parser_read
	'</' QName S? '>' 
  */
//-----------------------------------------------------------------------------
xistream& read_etag(xistream& xis, xstring& name, int nb_read)
{
	xstring uri;
	return read_etag(xis,name,uri,nb_read);
}

//-----------------------------------------------------------------------------
// read a etag
/* @ingroup parser_read
	'</' QName S? '>' 
  */
//-----------------------------------------------------------------------------
xistream& read_etag(xistream& xis, int nb_read)
{
	if (! (xis.good()) ) return xis;
	xstring tag,result_tag(xis.context.get_level_tag()),uri,result_uri(xis.context.get_level_ns_tag());

	read_etag(xis,tag,uri,nb_read);
	
	if ((tag==result_tag)&&
		(uri==result_uri)) 
		return xis;
	
	xis.setstate(std::ios::failbit);
	return xis;
}

//-----------------------------------------------------------------------------
// write a PEDef
/** @ingroup parser_write
<pre>
	PEDef    ::=    entity_value | ExternalID 
</pre>
  */
//-----------------------------------------------------------------------------
xostream& write_pe_def(xostream& xos, xstring const & entity_value, xstring const & system_literal, xstring const & pub_id_literal)
{
	if (! entity_value.empty()) return write_entity_value(xos,entity_value);
	return write_external_id(xos,system_literal,pub_id_literal);
}

//-----------------------------------------------------------------------------
// read a PEDef
/** @ingroup parser_read
<pre>
	PEDef    ::=    entity_value | ExternalID 
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_pe_def(xistream& xis, xstring& entity_value, xstring& system_literal, xstring& pub_id_literal)
{
	if (! (xis.good()) ) return xis;
	clear_string(entity_value);
	clear_string(system_literal);
	clear_string(pub_id_literal);

	xchar_t xc;
	if ( (xis.get(xc)) 
	   &&(  (xc==XCHAR_LATIN_CAPITAL_LETTER_P)
	      ||(xc==XCHAR_LATIN_CAPITAL_LETTER_S) 
		 ))
	{
		xis.putback(xc);
		read_external_id(xis,system_literal,pub_id_literal);
	} else {
		xis.putback(xc);
		read_entity_value(xis,entity_value);
	}

	return xis;
}

//-----------------------------------------------------------------------------
// write a NDataDecl
/* @ingroup parser_write
<pre>
	NDataDecl    ::=    S 'NDATA' S name 
</pre>
  */
//-----------------------------------------------------------------------------
xostream& write_ndata_decl(xostream& xos, xstring const & name)
{
	write_space(xos);
	write_xchar(xos,XCHAR_LATIN_CAPITAL_LETTER_N);
	write_xchar(xos,XCHAR_LATIN_CAPITAL_LETTER_D);
	write_xchar(xos,XCHAR_LATIN_CAPITAL_LETTER_A);
	write_xchar(xos,XCHAR_LATIN_CAPITAL_LETTER_T);
	write_xchar(xos,XCHAR_LATIN_CAPITAL_LETTER_A);
	write_space(xos);
	write_name(xos,name);
	return xos;
}

//-----------------------------------------------------------------------------
// read a NDataDecl
/* @ingroup parser_read
<pre>
	NDataDecl    ::=    S 'NDATA' S name 
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_ndata_decl(xistream& xis, xstring& name, int nb_read)
{
	switch (nb_read) {
	case 0: read_space(xis);
	case 1: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_N, _xtr(L"comment parsing a 'N'.XML Definition : NDataDecl    ::=    S 'NDATA' S name ") );
	case 2: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_D, _xtr(L"comment parsing a 'D'.XML Definition : NDataDecl    ::=    S 'NDATA' S name ") );
	case 3: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_A, _xtr(L"comment parsing a 'A'.XML Definition : NDataDecl    ::=    S 'NDATA' S name ") );
	case 4: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : NDataDecl    ::=    S 'NDATA' S name ") );
	case 5: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_A, _xtr(L"comment parsing a 'A'.XML Definition : NDataDecl    ::=    S 'NDATA' S name ") );
	case 6: read_space(xis);
	}

	read_name(xis,name);
	return xis;
}

//-----------------------------------------------------------------------------
// write a EntityDef
/** @ingroup parser_write
<pre>
	EntityDef    ::=    entity_value | (ExternalID NDataDecl?) 
</pre>
  */
//-----------------------------------------------------------------------------
xostream& write_entity_def(xostream& xos, xstring const & entity_value, xstring const & system_literal, xstring const & pub_id_literal, xstring const & ndata_name)
{
	if (! entity_value.empty()) return write_entity_value(xos,entity_value);
	write_external_id(xos,system_literal,pub_id_literal);
	if (! ndata_name.empty()) write_ndata_decl(xos,ndata_name);
	return xos;
}

//-----------------------------------------------------------------------------
// read a EntityDef
/** @ingroup parser_read
<pre>
	EntityDef    ::=    entity_value | (ExternalID NDataDecl?) 
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_entity_def(xistream& xis, xstring& entity_value, xstring& system_literal, xstring& pub_id_literal, xstring& ndata_name)
{
	if (! (xis.good()) ) return xis;
	clear_string(entity_value);
	clear_string(system_literal);
	clear_string(pub_id_literal);
	clear_string(ndata_name);

	xchar_t xc;
	if ( (xis.get(xc)) 
	   &&(  (xc==XCHAR_LATIN_CAPITAL_LETTER_P)
	      ||(xc==XCHAR_LATIN_CAPITAL_LETTER_S) 
		 ))
	{
		xis.putback(xc);
		read_external_id(xis,system_literal,pub_id_literal);
		read_optionnal_space(xis);
		if (! xis.get(xc)) return xis;
		xis.putback(xc);
		if (xc!=XCHAR_LATIN_CAPITAL_LETTER_N) return xis;
		read_ndata_decl(xis,ndata_name,1);
		
	} else {
		xis.putback(xc);
		read_entity_value(xis,entity_value);
	}

	return xis;
}

//-----------------------------------------------------------------------------
// write a PEDecl
/** @ingroup parser_write
<pre>
	PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
xostream& write_pe_decl(xostream& xos, xstring const & entity_name, xstring const & entity_value, xstring const & system_literal, xstring const & pubid_literal)
{
	xos<<"<!ENTITY";
	write_space(xos);
	write_xchar(xos,XCHAR_PERCENT_SIGN);
	write_space(xos);
	write_name(xos,entity_name);
	write_space(xos);
	write_pe_def(xos,entity_value,system_literal,pubid_literal);
	write_xchar(xos,XCHAR_GREATER_THAN_SIGN);
	return xos;
}

//-----------------------------------------------------------------------------
// read a PEDecl
/** @ingroup parser_read
<pre>
	PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_pe_decl(xistream& xis, xstring& entity_name, xstring& entity_value, xstring& system_literal, xstring & pubid_literal, int nb_read)
{
	
	switch (nb_read){
	case  0: read_xchar(xis,XCHAR_LESS_THAN_SIGN,         _xtr(L"comment parsing a '<'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case  1: read_xchar(xis,XCHAR_EXCLAMATION_MARK,       _xtr(L"comment parsing a '!'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case  2: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_E, _xtr(L"comment parsing a 'E'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case  3: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_N, _xtr(L"comment parsing a 'N'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case  4: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case  5: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_I, _xtr(L"comment parsing a 'I'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case  6: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case  7: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_Y, _xtr(L"comment parsing a 'Y'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case  8: read_space(xis);
	case  9: read_xchar(xis,XCHAR_PERCENT_SIGN,           _xtr(L"comment parsing a '%'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case 10: read_space(xis);
	}

	read_name(xis,entity_name);
	read_space(xis);
	read_pe_def(xis,entity_value,system_literal,pubid_literal);
	read_optionnal_space(xis);
	read_xchar(xis,XCHAR_GREATER_THAN_SIGN, _xtr(L"comment parsing a '>'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );

	xis.context.add_paramter_entity(entity_name,entity_value,system_literal,pubid_literal);
	return xis;
}

//-----------------------------------------------------------------------------
// read a PEDecl
/** @ingroup parser_read
<pre>
	PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_pe_decl(xistream& xis,int nb_read)
{
	xstring name, entity_value,system_literal,pubidliteral;
	return read_pe_decl(xis,name, entity_value,system_literal,pubidliteral,nb_read);
}

//-----------------------------------------------------------------------------
// write a GEDecl
/** @ingroup parser_write
<pre>
	GEDecl    ::=    '<!ENTITY' S name S EntityDef S? '>'  
</pre>
  */
//-----------------------------------------------------------------------------
xostream& write_ge_decl(xostream& xos, xstring const & entity_name, xstring const & entity_value, xstring const & system_literal, xstring const & pubid_literal, xstring const & ndata_name)
{
	xos<<"<!ENTITY";
	write_space(xos);
	write_name(xos,entity_name);
	write_space(xos);
	write_entity_def(xos,entity_value,system_literal,pubid_literal,ndata_name);
	write_xchar(xos,XCHAR_GREATER_THAN_SIGN);
	return xos;
}

//-----------------------------------------------------------------------------
// read a GEDecl
/** @ingroup parser_read
<pre>
	GEDecl    ::=    '<!ENTITY' S name S EntityDef S? '>'  
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_ge_decl(xistream& xis, xstring& entity_name, xstring& entity_value, xstring& system_literal, xstring & pubid_literal, xstring & ndata_name, int nb_read)
{
	
	switch (nb_read){
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN,         _xtr(L"comment parsing a '<'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case 1: read_xchar(xis,XCHAR_EXCLAMATION_MARK,       _xtr(L"comment parsing a '!'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case 2: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_E, _xtr(L"comment parsing a 'E'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case 3: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_N, _xtr(L"comment parsing a 'N'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case 4: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case 5: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_I, _xtr(L"comment parsing a 'I'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case 6: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case 7: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_Y, _xtr(L"comment parsing a 'Y'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );
	case 8: read_space(xis);
	}

	read_name(xis,entity_name);
	read_space(xis);
	read_entity_def(xis,entity_value,system_literal,pubid_literal,ndata_name);
	read_optionnal_space(xis);
	read_xchar(xis,XCHAR_GREATER_THAN_SIGN, _xtr(L"comment parsing a '>'.XML Definition : PEDecl    ::=    '<!ENTITY' S '%' S name S PEDef S? '>'") );

	xis.context.add_entity(entity_name,entity_value,system_literal,pubid_literal,ndata_name);
	return xis;
}

//-----------------------------------------------------------------------------
// read a GEDecl
/** @ingroup parser_read
<pre>
	GEDecl    ::=    '<!ENTITY' S name S EntityDef S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_ge_decl(xistream& xis,int nb_read)
{
	xstring name, entity_value,system_literal,pubidliteral,ndata_name;
	return read_ge_decl(xis,name, entity_value,system_literal,pubidliteral,ndata_name,nb_read);
}

//-----------------------------------------------------------------------------
// read Misc
/** @ingroup parser_read
<pre>
	Misc    ::=    comment | PI | S 
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_misc(xistream& xis)
{
	xchar_t xc;
	if (! xis.get(xc)) 
		XIMOL_THROW << _xtr(L"Reading Misc, and there is no more char aviable")
		            <<XIMOL_AS_ERROR;
	if (is_space(xc)) return read_optionnal_space(xis);
	if (xc==XCHAR_LESS_THAN_SIGN)
	{
		xc=xis.front();
		xis.putback(XCHAR_LESS_THAN_SIGN);
		if (xc==XCHAR_EXCLAMATION_MARK) return read_comment(xis);
		if (xc==XCHAR_QUESTION_MARK)    return read_pi(xis);
	}
	return xis;
}

//-----------------------------------------------------------------------------
// write a prolog
/** @ingroup parser_write
<pre>
	prolog    ::=    XMLDecl? Misc* (doctypedecl Misc*)? 
</pre>
  */
//-----------------------------------------------------------------------------
xostream& write_prolog(xostream& xos)
{
	write_xml_decl(xos);
	return xos;
}

//=============================================================================
// codecvt_ximol.
//=============================================================================
class codecvt_ximol_raw_data
  :public ::std::codecvt<wchar_t, char, mbstate_t>
{
public:
  typedef wchar_t    intern_type; //< internal char type.

  typedef char       extern_type; //< external char type.
  typedef mbstate_t  state_type;  //< state type.
public:
  explicit codecvt_ximol_raw_data(size_t refs = 0)
	    :std::codecvt<wchar_t, char, mbstate_t>(refs)
  {}
	virtual ~codecvt_ximol_raw_data(){}
protected:
  virtual result do_out          (state_type&         state,
                                  const intern_type*  from,
                                  const intern_type*  from_end,
                                  const intern_type*& from_next,
                                  extern_type*        to,
                                  extern_type*        to_limit,
                                  extern_type*&       to_next) const
  {
	  ptrdiff_t len = XIMOL_MIN(from_end - from, to_limit - to);
	  ::std::copy(from, from + len, to);
	  to_next   = to   + len;
	  return ok;
  }
  virtual result do_in           (state_type&         state,
                                  const extern_type*  from,
                                  const extern_type*  from_end,
                                  const extern_type*& from_next,
                                  intern_type*        to,
                                  intern_type*        to_limit,
                                  intern_type*&       to_next) const
  {
	  ptrdiff_t len = XIMOL_MIN((from_end - from), (to_limit - to));
	  ::std::copy((unsigned char*)from, (unsigned char*)(from + len), to);
	  from_next = from + len;
	  to_next   = to   + len;
	  return ok;
  }
  
  virtual result do_unshift      (state_type&   state,
                                  extern_type*  to, 
                                  extern_type*  to_limit,
                                  extern_type*& to_next) const
  {to_next = to; return noconv;}

  virtual int    do_encoding     () const throw ()
  {return 1;}
  
  virtual bool   do_always_noconv() const throw ()
  {return false;}
  
  virtual int    do_length       (const state_type&  state,
				                  const extern_type* from, 
				                  const extern_type* end,
				                  size_t             max) const
  {return (int)XIMOL_MIN((size_t) (end - from), max);}

  virtual int    do_max_length   () const throw (){return 1;} 

private:
  codecvt_ximol_raw_data(const codecvt_ximol_raw_data&){}
  codecvt_ximol_raw_data& operator = (const codecvt_ximol_raw_data&){ return *this; }  
}; // end of class codecvt_ximol_raw_data.

void BeforeBOM(xistream& xis)
{
	typedef ::std::codecvt<xchar_t, char, mbstate_t> FacetType;
    xis.imbue(XIMOL_ADD_FACET(xis.getloc(), static_cast<FacetType*>(new codecvt_ximol_raw_data())));

/*	FacetType* pfacet=(FacetType*)(&(XIMOL_USE_FACET(xis.getloc(),FacetType)));
	if (pfacet==NULL) 
		XIMOL_THROW<<_xtr(L"Can not find the right facet")<<XIMOL_AS_ERROR;

	call_destruct_ximol_facet(pfacet);
	new (pfacet) codecvt_ximol_raw_data();
*/
}

void AfterBOM(xistream& xis)
{
	XIMOL_ENCODERS_USING_NAMESPACE;

    prepare_ios(xis,"UTF-8");
/*	typedef ::std::codecvt<xchar_t, char, mbstate_t> FacetType;
	FacetType* pfacet=(FacetType*)(&(XIMOL_USE_FACET(xis.getloc(),FacetType)));
	if (pfacet==NULL) 
		XIMOL_THROW<<_xtr(L"Can not find the right facet")<<XIMOL_AS_ERROR;

	((codecvt_ximol_raw_data*)pfacet)->~codecvt_ximol_raw_data();
	place_ximol_facet(pfacet, "UTF-8");
*/
}

//-----------------------------------------------------------------------------
// Byte Order Mark
/** @ingroup parser_read
	@return number of char crunch. char of the '<?xml'
  */
//-----------------------------------------------------------------------------
size_t read_bom(xistream& xis)
{
	BeforeBOM(xis);
	xchar_t BOM[5];
	xis.get(BOM[0]);

	switch (BOM[0])
	{
	case 0x00:
		xis.get(BOM[1]);
		switch (BOM[1])
		{
		case 0x00:
			xis.get(BOM[2]);
			xis.get(BOM[3]);
			if (BOM[3]==0x3C) xis.putback(0x3C);
			AfterBOM(xis);
			xis.encoding("UCS-4BE");
			return 0;
			break;
		default:
			xis.putback(BOM[1]);
			AfterBOM(xis);
			xis.encoding("UTF-16BE");
			return 0;
		}
		break;

    // UTF-7 files can have a BOM too: 2B 2F 76 38 2D (ASCII +/v8-). 
    case 0x2B:
		xis.get(BOM[1]);
        if (BOM[1]!=0x2F) 
        {
            xis.putback(BOM[1]);
	        xis.putback(BOM[0]);
	        AfterBOM(xis);
	        xis.encoding("UTF-8");
	        return 0;
        }
        xis.get(BOM[2]);
        if (BOM[2]!=0x76) 
        {
            xis.putback(BOM[2]);
            xis.putback(BOM[1]);
	        xis.putback(BOM[0]);
	        AfterBOM(xis);
	        xis.encoding("UTF-8");
	        return 0;
        }
        xis.get(BOM[3]);
        if (BOM[3]!=0x38) 
        {
            xis.putback(BOM[3]);
            xis.putback(BOM[2]);
            xis.putback(BOM[1]);
	        xis.putback(BOM[0]);
	        AfterBOM(xis);
	        xis.encoding("UTF-8");
	        return 0;
        }
        xis.get(BOM[4]);
        if (BOM[4]!=0x2D) 
        {
            xis.putback(BOM[4]);
            xis.putback(BOM[3]);
            xis.putback(BOM[2]);
            xis.putback(BOM[1]);
	        xis.putback(BOM[0]);
	        AfterBOM(xis);
	        xis.encoding("UTF-8");
	        return 0;
        }

        AfterBOM(xis);
        xis.encoding("UTF-7");
        return 0;

    case 0x3C:
		xis.get(BOM[1]);
		switch (BOM[1])
		{
		case 0x00:
			xis.get(BOM[2]);
			xis.get(BOM[3]);
			if (BOM[2]==0x00) {
				xis.putback(0x3C);
				AfterBOM(xis);
				xis.encoding("UCS-4LE");
				return 0;
			}
			xis.putback(BOM[3]);
			AfterBOM(xis);
			xis.encoding("UTF-16LE");
			return 1;
			break;
		default:
			xis.putback(BOM[1]);
			AfterBOM(xis);
			xis.encoding("UTF-8");
			return 1;
		}
		break;
	case 0xEF:
		xis.get(BOM[1]);
		xis.get(BOM[2]);
		if ((BOM[1]!=0xBB) || (BOM[2]!=0xBF)) 
			XIMOL_THROW << _xtr(L"Bad Byte Order Mark for UTF-8.")
			                     << XIMOL_AS_ERROR;
		AfterBOM(xis);
		xis.encoding("UTF-8");
		return 0;
		break;
	case 0xFE:
		xis.get(BOM[1]);
		if (BOM[1]!=0xFF) 
			XIMOL_THROW << _xtr(L"Bad Byte Order Mark for UTF-16.")
			                     << XIMOL_AS_ERROR;
		AfterBOM(xis);
		xis.encoding("UTF-16BE");
		return 0;
		break;
	case 0xFF:
		xis.get(BOM[1]);
		xis.get(BOM[2]);
		xis.get(BOM[3]);
		if (BOM[1]!=0xFE) 
			XIMOL_THROW << _xtr(L"Bad Byte Order Mark for UTF-16.")
			            << XIMOL_AS_ERROR;
		if (BOM[2]==0x00)
		{
			AfterBOM(xis);
			xis.encoding("UCS-4LE");
			return 0;
		}
		xis.putback( * ((xchar_t*)(&(BOM[2]))) );
		AfterBOM(xis);
		xis.encoding("UTF-16LE");
		return 0;
		break;
	}
	xis.putback(BOM[0]);
	AfterBOM(xis);
	xis.encoding("UTF-8");
	return 0;
}

//-----------------------------------------------------------------------------
// read a prolog question tag
//-----------------------------------------------------------------------------
xistream& read_prolog_question(xistream& xis, int nb_read)
{
	
	switch (nb_read){
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN, _xtr(L"comment parsing a '<'.") );
	case 1: read_xchar(xis,XCHAR_QUESTION_MARK, _xtr(L"comment parsing a '?'.") );
	}
	xchar_t xc(xis.front());
	switch(xc)
	{
	case XCHAR_LATIN_CAPITAL_LETTER_X:
	case XCHAR_LATIN_SMALL_LETTER_X:
		read_xml_decl(xis,2);
		//xis.encoding(str< ::std::string>::cast(xis.context.get_encoding_decl()).c_str());
		break;
	default:
		read_pi(xis,2);
	}
	return xis;
}

//-----------------------------------------------------------------------------
// read doctypedecl
/** @ingroup parser_read
<pre>
	doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_doctype_decl(xistream& xis, int nb_read)
{
	if (! (xis.good()) ) return xis;
	
	
	switch (nb_read){
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN,         _xtr(L"comment parsing a '<'.XML Definition : doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>'") );
	case 1: read_xchar(xis,XCHAR_EXCLAMATION_MARK,       _xtr(L"comment parsing a '!'.XML Definition : doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>'") );
	case 2: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_D, _xtr(L"comment parsing a 'D'.XML Definition : doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>'") );
	case 3: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_O, _xtr(L"comment parsing a 'O'.XML Definition : doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>'") );
	case 4: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_C, _xtr(L"comment parsing a 'C'.XML Definition : doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>'") );
	case 5: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>'") );
	case 6: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_Y, _xtr(L"comment parsing a 'Y'.XML Definition : doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>'") );
	case 7: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_P, _xtr(L"comment parsing a 'P'.XML Definition : doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>'") );
	case 8: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_E, _xtr(L"comment parsing a 'E'.XML Definition : doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>'") );
	case 9: read_space(xis);
	}

	xstring name;
	read_name(xis,name);
	xis.context.set_doc_type_name(name);
	read_optionnal_space(xis);

	xchar_t xc(xis.front());
	if (xc==XCHAR_GREATER_THAN_SIGN) return xis;
	if (xc!=XCHAR_LEFT_SQUARE_BRACKET) 
	{
		xstring sys,pubid;
		read_external_id(xis,sys,pubid);
		xis.context.set_doctype_external_id(sys,pubid);
		read_optionnal_space(xis);
		xc=xis.front();
	}
	xis.pop_front();
	if (xc==XCHAR_GREATER_THAN_SIGN) return xis;
	if (xc!=XCHAR_LEFT_SQUARE_BRACKET) 
				XIMOL_THROW << _xtr(L"Error in the doctypedecl of the stream. witing for '['.")
				            << XIMOL_AS_ERROR;
	bool loop_cont=true;
	while (loop_cont) {
		read_optionnal_space(xis);
		xc=xis.front();
		switch (xc)
		{
		case XCHAR_PERCENT_SIGN:
			read_pe_reference(xis,name);
			xis.putback(name); // included in literal.
			break;
		case XCHAR_RIGHT_SQUARE_BRACKET:
			xis.get(xc); // we have a putbackc(xc);
			loop_cont=false;
			break;
		case XCHAR_LESS_THAN_SIGN:
			xis.pop_front(); // we have a putbackc(xc);
			xis.get(xc);
			switch(xc)
			{
			case XCHAR_QUESTION_MARK:
				read_pi(xis,2);
				break;
			case XCHAR_EXCLAMATION_MARK:
				read_doctype_element(xis,2);
				break;
			default:
				XIMOL_THROW << _xtr(L"Error in the doctypedecl of the stream. witing for '?' or '!'.")
				            << XIMOL_AS_ERROR;
			}
			break;
		default:
				XIMOL_THROW << _xtr(L"Error in the doctypedecl of the stream. witing for '<' or '%' or ']'.")
				            << XIMOL_AS_ERROR;
		}
	}	
	read_xchar(xis,XCHAR_GREATER_THAN_SIGN, _xtr(L"comment parsing a '>'.XML Definition : doctypedecl    ::=    '<!DOCTYPE' S name (S ExternalID)? S? ('[' (markupdecl | DeclSep)* ']' S?)? '>'") );
	return xis;
}

//-----------------------------------------------------------------------------
// read a prolog exclamation tag
//-----------------------------------------------------------------------------
xistream& read_prolog_exclamation(xistream& xis, int nb_read)
{
	
	switch (nb_read){
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN, _xtr(L"comment parsing a '<'.") );
	case 1: read_xchar(xis,XCHAR_EXCLAMATION_MARK, _xtr(L"comment parsing a '!'.") );
	}

	xchar_t xc(xis.front());
	switch(xc)
	{
	case XCHAR_HYPHEN_MINUS:
		read_comment(xis,2);
		break;
	case XCHAR_LATIN_CAPITAL_LETTER_D:
		read_doctype_decl(xis,2);
	}
	return xis;
}

//-----------------------------------------------------------------------------
// read doctype elements
//-----------------------------------------------------------------------------
xistream& read_doctype_element(xistream& xis, int nb_read)
{
	
	switch (nb_read) {
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN, _xtr(L"comment parsing a '<'.") );
	case 1: read_xchar(xis,XCHAR_EXCLAMATION_MARK, _xtr(L"comment parsing a '!'.") );
	}
	xchar_t xc(xis.front());
	switch(xc)
	{
	case XCHAR_HYPHEN_MINUS:
		read_comment(xis,2);
		break;
	case XCHAR_LATIN_CAPITAL_LETTER_N:
		read_notation_decl(xis,2);
		break;
	case XCHAR_LATIN_CAPITAL_LETTER_E:
		xis.pop_front(); // we have a putbackc(xc);
		xis.get(xc);
		switch(xc)
		{
		case XCHAR_LATIN_CAPITAL_LETTER_L:
			read_element_decl(xis,4);
			break;
		case XCHAR_LATIN_CAPITAL_LETTER_N:
			read_entity_decl(xis,4);
			break;
		default:
			XIMOL_THROW << _xtr(L"Error in the doctypedecl of the stream. witing for 'N' or 'L'.")
				            << XIMOL_AS_ERROR;
		}
		break;
	case XCHAR_LATIN_CAPITAL_LETTER_A:
		read_att_list_decl(xis,2);
		break;
	default:
			XIMOL_THROW << _xtr(L"Error in the doctypedecl of the stream. witing for '-' or 'A' or 'E' or 'N'.")
				            << XIMOL_AS_ERROR;
	}
	return xis;
}

//-----------------------------------------------------------------------------
// read a prolog
/** @ingroup parser_read
<pre>
	prolog    ::=    XMLDecl? Misc* (doctypedecl Misc*)?  
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_prolog(xistream& xis)
{
	int nb_read=0;
	nb_read=static_cast<int>(read_bom(xis));
	xchar_t xc;
	if (nb_read>=1) xis.putback(XCHAR_LESS_THAN_SIGN);
	bool loop_cont=true;
	while (loop_cont) {
		read_optionnal_space(xis);
		if ((! xis.get(xc)) || (xc != XCHAR_LESS_THAN_SIGN)) // drop the '<'
            break;
		
		xc=xis.front();
		xis.putback(XCHAR_LESS_THAN_SIGN);
		switch (xc)
		{
		case XCHAR_QUESTION_MARK:
			read_prolog_question(xis);
			break;

		case XCHAR_EXCLAMATION_MARK:
			read_prolog_exclamation(xis);
			break;
		default:
			loop_cont=false;
		}
	}
	return xis;
}

//-----------------------------------------------------------------------------
// read a elementdecl
/** @ingroup parser_read
<pre>
	elementdecl    ::=    '<!ELEMENT' S name S contentspec S? '>'   
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_element_decl(xistream& xis, int nb_read)
{
	if (! (xis.good()) ) return xis;
	
	
	switch (nb_read) {
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN,         _xtr(L"comment parsing a '<'.XML Definition : elementdecl    ::=    '<!ELEMENT' S name S contentspec S? '>'") );
	case 1: read_xchar(xis,XCHAR_EXCLAMATION_MARK,       _xtr(L"comment parsing a '!'.XML Definition : elementdecl    ::=    '<!ELEMENT' S name S contentspec S? '>'") );
	case 2: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_E, _xtr(L"comment parsing a 'E'.XML Definition : elementdecl    ::=    '<!ELEMENT' S name S contentspec S? '>'") );
	case 3: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_L, _xtr(L"comment parsing a 'L'.XML Definition : elementdecl    ::=    '<!ELEMENT' S name S contentspec S? '>'") );
	case 4: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_E, _xtr(L"comment parsing a 'E'.XML Definition : elementdecl    ::=    '<!ELEMENT' S name S contentspec S? '>'") );
	case 5: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_M, _xtr(L"comment parsing a 'M'.XML Definition : elementdecl    ::=    '<!ELEMENT' S name S contentspec S? '>'") );
	case 6: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_E, _xtr(L"comment parsing a 'E'.XML Definition : elementdecl    ::=    '<!ELEMENT' S name S contentspec S? '>'") );
	case 7: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_N, _xtr(L"comment parsing a 'N'.XML Definition : elementdecl    ::=    '<!ELEMENT' S name S contentspec S? '>'") );
	case 8: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : elementdecl    ::=    '<!ELEMENT' S name S contentspec S? '>'") );
	case 9: read_space(xis);
	}

	// TODO
	xchar_t xc;
	while ( (xis.get(xc)) && (xc!=XCHAR_GREATER_THAN_SIGN) )
		;
	return xis;
}

//-----------------------------------------------------------------------------
// read a AttlistDecl
/** @ingroup parser_read
<pre>
	AttlistDecl    ::=    '<!ATTLIST' S name AttDef* S? '>' 
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_att_list_decl(xistream& xis, int nb_read)
{
	if (! (xis.good()) ) return xis;
	
	
	switch (nb_read) {
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN,         _xtr(L"comment parsing a '<'.XML Definition : AttlistDecl    ::=    '<!ATTLIST' S name AttDef* S? '>' ") );
	case 1: read_xchar(xis,XCHAR_EXCLAMATION_MARK,       _xtr(L"comment parsing a '!'.XML Definition : AttlistDecl    ::=    '<!ATTLIST' S name AttDef* S? '>' ") );
	case 2: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_A, _xtr(L"comment parsing a 'A'.XML Definition : AttlistDecl    ::=    '<!ATTLIST' S name AttDef* S? '>' ") );
	case 3: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : AttlistDecl    ::=    '<!ATTLIST' S name AttDef* S? '>' ") );
	case 4: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : AttlistDecl    ::=    '<!ATTLIST' S name AttDef* S? '>' ") );
	case 5: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_L, _xtr(L"comment parsing a 'L'.XML Definition : AttlistDecl    ::=    '<!ATTLIST' S name AttDef* S? '>' ") );
	case 6: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_I, _xtr(L"comment parsing a 'I'.XML Definition : AttlistDecl    ::=    '<!ATTLIST' S name AttDef* S? '>' ") );
	case 7: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_S, _xtr(L"comment parsing a 'S'.XML Definition : AttlistDecl    ::=    '<!ATTLIST' S name AttDef* S? '>' ") );
	case 8: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : AttlistDecl    ::=    '<!ATTLIST' S name AttDef* S? '>' ") );
	case 9: read_space(xis);
	}

	// TODO
	xchar_t xc;
	while ( (xis.get(xc)) && (xc!=XCHAR_GREATER_THAN_SIGN) )
		;
	return xis;
}

//-----------------------------------------------------------------------------
// read a EntityDecl
/** @ingroup parser_read
<pre>
	EntityDecl    ::=    GEDecl | PEDecl    
</pre>
  */
//-----------------------------------------------------------------------------
xistream& read_entity_decl(xistream& xis, int nb_read)
{
	if (! (xis.good()) ) return xis;
	
	
	switch (nb_read) {
	case 0: read_xchar(xis,XCHAR_LESS_THAN_SIGN,         _xtr(L"comment parsing a '<'.XML Definition : EntityDecl    ::=    GEDecl | PEDecl    ") );
	case 1: read_xchar(xis,XCHAR_EXCLAMATION_MARK,       _xtr(L"comment parsing a '!'.XML Definition : EntityDecl    ::=    GEDecl | PEDecl    ") );
	case 2: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_E, _xtr(L"comment parsing a 'E'.XML Definition : EntityDecl    ::=    GEDecl | PEDecl    ") );
	case 3: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_N, _xtr(L"comment parsing a 'N'.XML Definition : EntityDecl    ::=    GEDecl | PEDecl    ") );
	case 4: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : EntityDecl    ::=    GEDecl | PEDecl    ") );
	case 5: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_I, _xtr(L"comment parsing a 'I'.XML Definition : EntityDecl    ::=    GEDecl | PEDecl    ") );
	case 6: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_T, _xtr(L"comment parsing a 'T'.XML Definition : EntityDecl    ::=    GEDecl | PEDecl    ") );
	case 7: read_xchar(xis,XCHAR_LATIN_CAPITAL_LETTER_Y, _xtr(L"comment parsing a 'Y'.XML Definition : EntityDecl    ::=    GEDecl | PEDecl    ") );
	case 8: read_space(xis);
	}
	xchar_t xc(xis.front());
	if (xc!=XCHAR_PERCENT_SIGN) read_ge_decl(xis,9);
	else read_pe_decl(xis,9);
	return xis;
}

XIMOL_PARSER_END_NAMESPACE

