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
	\brief Define some macros for signs.
    All ascii character are define here with macros.
    We need it to avoid error in the parser by confusing two character.

	\author Tournois Florent
	\version 1.0

    $Id: def_signs.hpp,v 1.2 2005/05/13 00:05:27 vlabella Exp $
    $Log: def_signs.hpp,v $
    Revision 1.2  2005/05/13 00:05:27  vlabella
    commit in makefile

    Revision 1.1.2.1  2005/05/11 15:49:45  vlabella
    adding in ximol and xmlparser

    Revision 1.4  2004/02/22 10:27:34  tournois
    Add some doc.

    Revision 1.3  2004/02/22 09:54:20  tournois
    Change years on the copyright.

    Revision 1.2  2003/11/02 19:23:01  tournois
    Go to the boost coding standard.
    Change all name to lower case.

    Revision 1.1  2003/09/24 08:28:17  tournois
    Create the namespace Encoders, Parser, Xml
    Change the library organization.
    add VC7.1 project for this organization.

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef XIMOL_PARSER_DEF_SIGNS_HPP_
#define XIMOL_PARSER_DEF_SIGNS_HPP_

#define XCHAR_SPACE                    (xchar_t)0x0020 /**< character ' ' */
#define XCHAR_EXCLAMATION_MARK         (xchar_t)0x0021 /**< character '!' */
#define XCHAR_QUOTATION_MARK           (xchar_t)0x0022 /**< character '"' */
#define XCHAR_NUMBER_SIGN              (xchar_t)0x0023 /**< character '#' */
#define XCHAR_DOLLAR_SIGN              (xchar_t)0x0024 /**< character '$' */
#define XCHAR_PERCENT_SIGN             (xchar_t)0x0025 /**< character '%' */
#define XCHAR_AMPERSAND                (xchar_t)0x0026 /**< character '&' */
#define XCHAR_APOSTROPHE               (xchar_t)0x0027 /**< character ''' */
#define XCHAR_LEFT_PARENTHESIS         (xchar_t)0x0028 /**< character '(' */
#define XCHAR_RIGHT_PARENTHESIS        (xchar_t)0x0029 /**< character ')' */
#define XCHAR_ASTERISK                 (xchar_t)0x002a /**< character '*' */
#define XCHAR_PLUS_SIGN                (xchar_t)0x002b /**< character '+' */
#define XCHAR_COMMA                    (xchar_t)0x002c /**< character ',' */
#define XCHAR_HYPHEN_MINUS             (xchar_t)0x002d /**< character '-' */
#define XCHAR_FULL_STOP                (xchar_t)0x002e /**< character '.' */
#define XCHAR_SOLIDUS                  (xchar_t)0x002f /**< character '/' */
#define XCHAR_DIGIT_ZERO               (xchar_t)0x0030 /**< character '0' */
#define XCHAR_DIGIT_ONE                (xchar_t)0x0031 /**< character '1' */
#define XCHAR_DIGIT_TWO                (xchar_t)0x0032 /**< character '2' */
#define XCHAR_DIGIT_THREE              (xchar_t)0x0033 /**< character '3' */
#define XCHAR_DIGIT_FOUR               (xchar_t)0x0034 /**< character '4' */
#define XCHAR_DIGIT_FIVE               (xchar_t)0x0035 /**< character '5' */
#define XCHAR_DIGIT_SIX                (xchar_t)0x0036 /**< character '6' */
#define XCHAR_DIGIT_SEVEN              (xchar_t)0x0037 /**< character '7' */
#define XCHAR_DIGIT_EIGHT              (xchar_t)0x0038 /**< character '8' */
#define XCHAR_DIGIT_NINE               (xchar_t)0x0039 /**< character '9' */
#define XCHAR_COLON                    (xchar_t)0x003a /**< character ':' */
#define XCHAR_SEMICOLON                (xchar_t)0x003b /**< character ';' */
#define XCHAR_LESS_THAN_SIGN           (xchar_t)0x003c /**< character '<' */
#define XCHAR_EQUALS_SIGN              (xchar_t)0x003d /**< character '=' */
#define XCHAR_GREATER_THAN_SIGN        (xchar_t)0x003e /**< character '>' */
#define XCHAR_QUESTION_MARK            (xchar_t)0x003f /**< character '?' */
#define XCHAR_COMMERCIAL_AT            (xchar_t)0x0040 /**< character '@' */
#define XCHAR_LATIN_CAPITAL_LETTER_A   (xchar_t)0x0041 /**< character 'A' */
#define XCHAR_LATIN_CAPITAL_LETTER_B   (xchar_t)0x0042 /**< character 'B' */
#define XCHAR_LATIN_CAPITAL_LETTER_C   (xchar_t)0x0043 /**< character 'C' */
#define XCHAR_LATIN_CAPITAL_LETTER_D   (xchar_t)0x0044 /**< character 'D' */
#define XCHAR_LATIN_CAPITAL_LETTER_E   (xchar_t)0x0045 /**< character 'E' */
#define XCHAR_LATIN_CAPITAL_LETTER_F   (xchar_t)0x0046 /**< character 'F' */
#define XCHAR_LATIN_CAPITAL_LETTER_G   (xchar_t)0x0047 /**< character 'G' */
#define XCHAR_LATIN_CAPITAL_LETTER_H   (xchar_t)0x0048 /**< character 'H' */
#define XCHAR_LATIN_CAPITAL_LETTER_I   (xchar_t)0x0049 /**< character 'I' */
#define XCHAR_LATIN_CAPITAL_LETTER_J   (xchar_t)0x004a /**< character 'J' */
#define XCHAR_LATIN_CAPITAL_LETTER_K   (xchar_t)0x004b /**< character 'K' */
#define XCHAR_LATIN_CAPITAL_LETTER_L   (xchar_t)0x004c /**< character 'L' */
#define XCHAR_LATIN_CAPITAL_LETTER_M   (xchar_t)0x004d /**< character 'M' */
#define XCHAR_LATIN_CAPITAL_LETTER_N   (xchar_t)0x004e /**< character 'N' */
#define XCHAR_LATIN_CAPITAL_LETTER_O   (xchar_t)0x004f /**< character 'O' */
#define XCHAR_LATIN_CAPITAL_LETTER_P   (xchar_t)0x0050 /**< character 'P' */
#define XCHAR_LATIN_CAPITAL_LETTER_Q   (xchar_t)0x0051 /**< character 'Q' */
#define XCHAR_LATIN_CAPITAL_LETTER_R   (xchar_t)0x0052 /**< character 'R' */
#define XCHAR_LATIN_CAPITAL_LETTER_S   (xchar_t)0x0053 /**< character 'S' */
#define XCHAR_LATIN_CAPITAL_LETTER_T   (xchar_t)0x0054 /**< character 'T' */
#define XCHAR_LATIN_CAPITAL_LETTER_U   (xchar_t)0x0055 /**< character 'U' */
#define XCHAR_LATIN_CAPITAL_LETTER_V   (xchar_t)0x0056 /**< character 'V' */
#define XCHAR_LATIN_CAPITAL_LETTER_W   (xchar_t)0x0057 /**< character 'W' */
#define XCHAR_LATIN_CAPITAL_LETTER_X   (xchar_t)0x0058 /**< character 'X' */
#define XCHAR_LATIN_CAPITAL_LETTER_Y   (xchar_t)0x0059 /**< character 'Y' */
#define XCHAR_LATIN_CAPITAL_LETTER_Z   (xchar_t)0x005a /**< character 'Z' */
#define XCHAR_LEFT_SQUARE_BRACKET      (xchar_t)0x005b /**< character '[' */
#define XCHAR_REVERSE_SOLIDUS          (xchar_t)0x005c /**< character '\' */
#define XCHAR_RIGHT_SQUARE_BRACKET     (xchar_t)0x005d /**< character ']' */
#define XCHAR_CIRCUMFLEX_ACCENT        (xchar_t)0x005e /**< character '^' */
#define XCHAR_LOW_LINE                 (xchar_t)0x005f /**< character '_' */
#define XCHAR_GRAVE_ACCENT             (xchar_t)0x0060 /**< character '`' */
#define XCHAR_LATIN_SMALL_LETTER_A     (xchar_t)0x0061 /**< character 'a' */
#define XCHAR_LATIN_SMALL_LETTER_B     (xchar_t)0x0062 /**< character 'b' */
#define XCHAR_LATIN_SMALL_LETTER_C     (xchar_t)0x0063 /**< character 'c' */
#define XCHAR_LATIN_SMALL_LETTER_D     (xchar_t)0x0064 /**< character 'd' */
#define XCHAR_LATIN_SMALL_LETTER_E     (xchar_t)0x0065 /**< character 'e' */
#define XCHAR_LATIN_SMALL_LETTER_F     (xchar_t)0x0066 /**< character 'f' */
#define XCHAR_LATIN_SMALL_LETTER_G     (xchar_t)0x0067 /**< character 'g' */
#define XCHAR_LATIN_SMALL_LETTER_H     (xchar_t)0x0068 /**< character 'h' */
#define XCHAR_LATIN_SMALL_LETTER_I     (xchar_t)0x0069 /**< character 'i' */
#define XCHAR_LATIN_SMALL_LETTER_J     (xchar_t)0x006a /**< character 'j' */
#define XCHAR_LATIN_SMALL_LETTER_K     (xchar_t)0x006b /**< character 'k' */
#define XCHAR_LATIN_SMALL_LETTER_L     (xchar_t)0x006c /**< character 'l' */
#define XCHAR_LATIN_SMALL_LETTER_M     (xchar_t)0x006d /**< character 'm' */
#define XCHAR_LATIN_SMALL_LETTER_N     (xchar_t)0x006e /**< character 'n' */
#define XCHAR_LATIN_SMALL_LETTER_O     (xchar_t)0x006f /**< character 'o' */
#define XCHAR_LATIN_SMALL_LETTER_P     (xchar_t)0x0070 /**< character 'p' */
#define XCHAR_LATIN_SMALL_LETTER_Q     (xchar_t)0x0071 /**< character 'q' */
#define XCHAR_LATIN_SMALL_LETTER_R     (xchar_t)0x0072 /**< character 'r' */
#define XCHAR_LATIN_SMALL_LETTER_S     (xchar_t)0x0073 /**< character 's' */
#define XCHAR_LATIN_SMALL_LETTER_T     (xchar_t)0x0074 /**< character 't' */
#define XCHAR_LATIN_SMALL_LETTER_U     (xchar_t)0x0075 /**< character 'u' */
#define XCHAR_LATIN_SMALL_LETTER_V     (xchar_t)0x0076 /**< character 'v' */
#define XCHAR_LATIN_SMALL_LETTER_W     (xchar_t)0x0077 /**< character 'w' */
#define XCHAR_LATIN_SMALL_LETTER_X     (xchar_t)0x0078 /**< character 'x' */
#define XCHAR_LATIN_SMALL_LETTER_Y     (xchar_t)0x0079 /**< character 'y' */
#define XCHAR_LATIN_SMALL_LETTER_Z     (xchar_t)0x007a /**< character 'z' */
#define XCHAR_LEFT_CURLY_BRACKET       (xchar_t)0x007b /**< character '{' */
#define XCHAR_VERTICAL_LINE            (xchar_t)0x007c /**< character '|' */
#define XCHAR_RIGHT_CURLY_BRACKET      (xchar_t)0x007d /**< character '}' */
#define XCHAR_TILDE                    (xchar_t)0x007e /**< character '~' */
#define XCHAR_DELETE                   (xchar_t)0x007f /**< character ' ' */

#endif // #define XIMOL_PARSER_DEF_SIGNS_HPP_

