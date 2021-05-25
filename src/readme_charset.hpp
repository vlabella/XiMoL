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

/** \page character-sets Ref: Character sets
\code
===================================================================
CHARACTER SETS

(last updated 2002-09-30)

These are the official names for character sets that may be used in
the Internet and may be referred to in Internet documentation.  These
names are expressed in ANSI_X3.4-1968 which is commonly called
US-ASCII or simply ASCII.  The character set most commonly use in the
Internet and used especially in protocol standards is US-ASCII, this
is strongly encouraged.  The use of the name US-ASCII is also
encouraged.

The character set names may be up to 40 characters taken from the
printable characters of US-ASCII.  However, no distinction is made
between use of upper and lower case letters.

The MIBenum value is a unique value for use in MIBs to identify coded
character sets.

The value space for MIBenum values has been divided into three
regions. The first region (3-999) consists of coded character sets
that have been standardized by some standard setting organization.
This region is intended for standards that do not have subset
implementations. The second region (1000-1999) is for the Unicode and
ISO/IEC 10646 coded character sets together with a specification of a
(set of) sub-repertoires that may occur.  The third region (>1999) is
intended for vendor specific coded character sets.

	Assigned MIB enum Numbers
	-------------------------
	0-2		Reserved
	3-999		Set By Standards Organizations
	1000-1999	Unicode / 10646
	2000-2999	Vendor

The aliases that start with "cs" have been added for use with the
Printer MIB (see RFC 1759) and contain the standard numbers along with
suggestive names in order to facilitate applications that want to
display the names in user interfaces.  The "cs" stands for character
set and is provided for applications that need a lower case first
letter but want to use mixed case thereafter that cannot contain any
special characters, such as underbar ("_") and dash ("-").  If the
character set is from an ISO standard, its cs alias is the ISO
standard number or name.  If the character set is not from an ISO
standard, but is registered with ISO (IPSJ/ITSCJ is the current ISO
Registration Authority), the ISO Registry number is specified as
ISOnnn followed by letters suggestive of the name or standards number
of the code set.  When a national or international standard is
revised, the year of revision is added to the cs alias of the new
character set entry in the IANA Registry in order to distinguish the
revised character set from the original character set.


Character Set                                               Reference
-------------                                               ---------

name: ANSI_X3.4-1968                                   [RFC1345,KXS2]
MIBenum: 3
Source: ECMA registry
Alias: iso-ir-6
Alias: ANSI_X3.4-1986
Alias: ISO_646.irv:1991
Alias: ASCII
Alias: ISO646-US
Alias: US-ASCII (preferred MIME name)
Alias: us
Alias: IBM367
Alias: cp367
Alias: csASCII

name: ISO-10646-UTF-1
MIBenum: 27
Source: Universal Transfer Format (1), this is the multibyte
        encoding, that subsets ASCII-7. It does not have byte
        ordering issues.
Alias: csISO10646UTF1

name: ISO_646.basic:1983                                [RFC1345,KXS2]
MIBenum: 28
Source: ECMA registry
Alias: ref
Alias: csISO646basic1983

name: INVARIANT                                         [RFC1345,KXS2]
MIBenum: 29
Alias: csINVARIANT

name: ISO_646.irv:1983                                  [RFC1345,KXS2]
MIBenum: 30
Source: ECMA registry
Alias: iso-ir-2
Alias: irv
Alias: csISO2IntlRefVersion

name: BS_4730                                           [RFC1345,KXS2]
MIBenum: 20
Source: ECMA registry
Alias: iso-ir-4
Alias: ISO646-GB
Alias: gb
Alias: uk
Alias: csISO4UnitedKingdom

name: NATS-SEFI                                         [RFC1345,KXS2]
MIBenum: 31
Source: ECMA registry
Alias: iso-ir-8-1
Alias: csNATSSEFI

name: NATS-SEFI-ADD                                     [RFC1345,KXS2]
MIBenum: 32
Source: ECMA registry
Alias: iso-ir-8-2
Alias: csNATSSEFIADD

name: NATS-DANO                                         [RFC1345,KXS2]
MIBenum: 33
Source: ECMA registry
Alias: iso-ir-9-1
Alias: csNATSDANO

name: NATS-DANO-ADD                                     [RFC1345,KXS2]
MIBenum: 34
Source: ECMA registry
Alias: iso-ir-9-2
Alias: csNATSDANOADD

name: SEN_850200_B                                      [RFC1345,KXS2]
MIBenum: 35
Source: ECMA registry
Alias: iso-ir-10
Alias: FI
Alias: ISO646-FI
Alias: ISO646-SE
Alias: se
Alias: csISO10Swedish

name: SEN_850200_C                                      [RFC1345,KXS2]
MIBenum: 21
Source: ECMA registry
Alias: iso-ir-11
Alias: ISO646-SE2
Alias: se2
Alias: csISO11SwedishForNames

name: KS_C_5601-1987                                    [RFC1345,KXS2]
MIBenum: 36
Source: ECMA registry
Alias: iso-ir-149
Alias: KS_C_5601-1989
Alias: KSC_5601
Alias: korean
Alias: csKSC56011987

name: ISO-2022-KR  (preferred MIME name)                [RFC1557,Choi]
MIBenum: 37
Source: RFC-1557 (see also KS_C_5601-1987)
Alias: csISO2022KR

name: EUC-KR  (preferred MIME name)                     [RFC1557,Choi]
MIBenum: 38
Source: RFC-1557 (see also KS_C_5861-1992)
Alias: csEUCKR

name: ISO-2022-JP  (preferred MIME name)               [RFC1468,Murai]
MIBenum: 39
Source: RFC-1468 (see also RFC-2237)
Alias: csISO2022JP

name: ISO-2022-JP-2  (preferred MIME name)              [RFC1554,Ohta]
MIBenum: 40
Source: RFC-1554
Alias: csISO2022JP2

name: ISO-2022-CN                                            [RFC1922]
MIBenum: 104
Source: RFC-1922

name: ISO-2022-CN-EXT                                        [RFC1922]
MIBenum: 105
Source: RFC-1922

name: JIS_C6220-1969-jp                                 [RFC1345,KXS2]
MIBenum: 41
Source: ECMA registry
Alias: JIS_C6220-1969
Alias: iso-ir-13
Alias: katakana
Alias: x0201-7
Alias: csISO13JISC6220jp

name: JIS_C6220-1969-ro                                 [RFC1345,KXS2]
MIBenum: 42
Source: ECMA registry
Alias: iso-ir-14
Alias: jp
Alias: ISO646-JP
Alias: csISO14JISC6220ro

name: IT                                                [RFC1345,KXS2]
MIBenum: 22
Source: ECMA registry
Alias: iso-ir-15
Alias: ISO646-IT
Alias: csISO15Italian

name: PT                                                [RFC1345,KXS2]
MIBenum: 43
Source: ECMA registry
Alias: iso-ir-16
Alias: ISO646-PT
Alias: csISO16Portuguese

name: ES                                                [RFC1345,KXS2]
MIBenum: 23
Source: ECMA registry
Alias: iso-ir-17
Alias: ISO646-ES
Alias: csISO17Spanish

name: greek7-old                                        [RFC1345,KXS2]
MIBenum: 44
Source: ECMA registry
Alias: iso-ir-18
Alias: csISO18Greek7Old

name: latin-greek                                       [RFC1345,KXS2]
MIBenum: 45
Source: ECMA registry
Alias: iso-ir-19
Alias: csISO19LatinGreek

name: DIN_66003                                         [RFC1345,KXS2]
MIBenum: 24
Source: ECMA registry
Alias: iso-ir-21
Alias: de
Alias: ISO646-DE
Alias: csISO21German

name: NF_Z_62-010_(1973)                                [RFC1345,KXS2]
MIBenum: 46
Source: ECMA registry
Alias: iso-ir-25
Alias: ISO646-FR1
Alias: csISO25French

name: Latin-greek-1                                     [RFC1345,KXS2]
MIBenum: 47
Source: ECMA registry
Alias: iso-ir-27
Alias: csISO27LatinGreek1

name: ISO_5427                                          [RFC1345,KXS2]
MIBenum: 48
Source: ECMA registry
Alias: iso-ir-37
Alias: csISO5427Cyrillic

name: JIS_C6226-1978                                    [RFC1345,KXS2]
MIBenum: 49
Source: ECMA registry
Alias: iso-ir-42
Alias: csISO42JISC62261978

name: BS_viewdata                                       [RFC1345,KXS2]
MIBenum: 50
Source: ECMA registry
Alias: iso-ir-47
Alias: csISO47BSViewdata

name: INIS                                              [RFC1345,KXS2]
MIBenum: 51
Source: ECMA registry
Alias: iso-ir-49
Alias: csISO49INIS

name: INIS-8                                            [RFC1345,KXS2]
MIBenum: 52
Source: ECMA registry
Alias: iso-ir-50
Alias: csISO50INIS8

name: INIS-cyrillic                                     [RFC1345,KXS2]
MIBenum: 53
Source: ECMA registry
Alias: iso-ir-51
Alias: csISO51INISCyrillic

name: ISO_5427:1981                                     [RFC1345,KXS2]
MIBenum: 54
Source: ECMA registry
Alias: iso-ir-54
Alias: ISO5427Cyrillic1981

name: ISO_5428:1980                                     [RFC1345,KXS2]
MIBenum: 55
Source: ECMA registry
Alias: iso-ir-55
Alias: csISO5428Greek

name: GB_1988-80                                        [RFC1345,KXS2]
MIBenum: 56
Source: ECMA registry
Alias: iso-ir-57
Alias: cn
Alias: ISO646-CN
Alias: csISO57GB1988

name: GB_2312-80                                        [RFC1345,KXS2]
MIBenum: 57
Source: ECMA registry
Alias: iso-ir-58
Alias: chinese
Alias: csISO58GB231280

name: NS_4551-1                                         [RFC1345,KXS2]
MIBenum: 25
Source: ECMA registry
Alias: iso-ir-60
Alias: ISO646-NO
Alias: no
Alias: csISO60DanishNorwegian
Alias: csISO60Norwegian1

name: NS_4551-2                                          [RFC1345,KXS2]
MIBenum: 58
Source: ECMA registry
Alias: ISO646-NO2
Alias: iso-ir-61
Alias: no2
Alias: csISO61Norwegian2

name: NF_Z_62-010                                        [RFC1345,KXS2]
MIBenum: 26
Source: ECMA registry
Alias: iso-ir-69
Alias: ISO646-FR
Alias: fr
Alias: csISO69French

name: videotex-suppl                                     [RFC1345,KXS2]
MIBenum: 59
Source: ECMA registry
Alias: iso-ir-70
Alias: csISO70VideotexSupp1

name: PT2                                                [RFC1345,KXS2]
MIBenum: 60
Source: ECMA registry
Alias: iso-ir-84
Alias: ISO646-PT2
Alias: csISO84Portuguese2

name: ES2                                                [RFC1345,KXS2]
MIBenum: 61
Source: ECMA registry
Alias: iso-ir-85
Alias: ISO646-ES2
Alias: csISO85Spanish2

name: MSZ_7795.3                                         [RFC1345,KXS2]
MIBenum: 62
Source: ECMA registry
Alias: iso-ir-86
Alias: ISO646-HU
Alias: hu
Alias: csISO86Hungarian

name: JIS_C6226-1983                                     [RFC1345,KXS2]
MIBenum: 63
Source: ECMA registry
Alias: iso-ir-87
Alias: x0208
Alias: JIS_X0208-1983
Alias: csISO87JISX0208

name: greek7                                             [RFC1345,KXS2]
MIBenum: 64
Source: ECMA registry
Alias: iso-ir-88
Alias: csISO88Greek7

name: ASMO_449                                           [RFC1345,KXS2]
MIBenum: 65
Source: ECMA registry
Alias: ISO_9036
Alias: arabic7
Alias: iso-ir-89
Alias: csISO89ASMO449

name: iso-ir-90                                          [RFC1345,KXS2]
MIBenum: 66
Source: ECMA registry
Alias: csISO90

name: JIS_C6229-1984-a                                   [RFC1345,KXS2]
MIBenum: 67
Source: ECMA registry
Alias: iso-ir-91
Alias: jp-ocr-a
Alias: csISO91JISC62291984a

name: JIS_C6229-1984-b                                   [RFC1345,KXS2]
MIBenum: 68
Source: ECMA registry
Alias: iso-ir-92
Alias: ISO646-JP-OCR-B
Alias: jp-ocr-b
Alias: csISO92JISC62991984b

name: JIS_C6229-1984-b-add                               [RFC1345,KXS2]
MIBenum: 69
Source: ECMA registry
Alias: iso-ir-93
Alias: jp-ocr-b-add
Alias: csISO93JIS62291984badd

name: JIS_C6229-1984-hand                                [RFC1345,KXS2]
MIBenum: 70
Source: ECMA registry
Alias: iso-ir-94
Alias: jp-ocr-hand
Alias: csISO94JIS62291984hand

name: JIS_C6229-1984-hand-add                            [RFC1345,KXS2]
MIBenum: 71
Source: ECMA registry
Alias: iso-ir-95
Alias: jp-ocr-hand-add
Alias: csISO95JIS62291984handadd

name: JIS_C6229-1984-kana                                [RFC1345,KXS2]
MIBenum: 72
Source: ECMA registry
Alias: iso-ir-96
Alias: csISO96JISC62291984kana

name: ISO_2033-1983                                      [RFC1345,KXS2]
MIBenum: 73
Source: ECMA registry
Alias: iso-ir-98
Alias: e13b
Alias: csISO2033

name: ANSI_X3.110-1983                                   [RFC1345,KXS2]
MIBenum: 74
Source: ECMA registry
Alias: iso-ir-99
Alias: CSA_T500-1983
Alias: NAPLPS
Alias: csISO99NAPLPS

name: ISO_8859-1:1987                                    [RFC1345,KXS2]
MIBenum: 4
Source: ECMA registry
Alias: iso-ir-100
Alias: ISO_8859-1
Alias: ISO-8859-1 (preferred MIME name)
Alias: latin1
Alias: l1
Alias: IBM819
Alias: CP819
Alias: csISOLatin1

name: ISO_8859-2:1987                                    [RFC1345,KXS2]
MIBenum: 5
Source: ECMA registry
Alias: iso-ir-101
Alias: ISO_8859-2
Alias: ISO-8859-2 (preferred MIME name)
Alias: latin2
Alias: l2
Alias: csISOLatin2

name: T.61-7bit                                          [RFC1345,KXS2]
MIBenum: 75
Source: ECMA registry
Alias: iso-ir-102
Alias: csISO102T617bit

name: T.61-8bit                                          [RFC1345,KXS2]
MIBenum: 76
Alias: T.61
Source: ECMA registry
Alias: iso-ir-103
Alias: csISO103T618bit

name: ISO_8859-3:1988                                    [RFC1345,KXS2]
MIBenum: 6
Source: ECMA registry
Alias: iso-ir-109
Alias: ISO_8859-3
Alias: ISO-8859-3 (preferred MIME name)
Alias: latin3
Alias: l3
Alias: csISOLatin3

name: ISO_8859-4:1988                                    [RFC1345,KXS2]
MIBenum: 7
Source: ECMA registry
Alias: iso-ir-110
Alias: ISO_8859-4
Alias: ISO-8859-4 (preferred MIME name)
Alias: latin4
Alias: l4
Alias: csISOLatin4

name: ECMA-cyrillic                                      [RFC1345,KXS2]
MIBenum: 77
Source: ECMA registry
Alias: iso-ir-111
Alias: csISO111ECMACyrillic

name: CSA_Z243.4-1985-1                                  [RFC1345,KXS2]
MIBenum: 78
Source: ECMA registry
Alias: iso-ir-121
Alias: ISO646-CA
Alias: csa7-1
Alias: ca
Alias: csISO121Canadian1

name: CSA_Z243.4-1985-2                                  [RFC1345,KXS2]
MIBenum: 79
Source: ECMA registry
Alias: iso-ir-122
Alias: ISO646-CA2
Alias: csa7-2
Alias: csISO122Canadian2

name: CSA_Z243.4-1985-gr                                 [RFC1345,KXS2]
MIBenum: 80
Source: ECMA registry
Alias: iso-ir-123
Alias: csISO123CSAZ24341985gr

name: ISO_8859-6:1987                                    [RFC1345,KXS2]
MIBenum: 9
Source: ECMA registry
Alias: iso-ir-127
Alias: ISO_8859-6
Alias: ISO-8859-6 (preferred MIME name)
Alias: ECMA-114
Alias: ASMO-708
Alias: arabic
Alias: csISOLatinArabic

name: ISO_8859-6-E                                       [RFC1556,IANA]
MIBenum: 81
Source: RFC1556
Alias: csISO88596E
Alias: ISO-8859-6-E (preferred MIME name)

name: ISO_8859-6-I                                       [RFC1556,IANA]
MIBenum: 82
Source: RFC1556
Alias: csISO88596I
Alias: ISO-8859-6-I (preferred MIME name)

name: ISO_8859-7:1987                            [RFC1947,RFC1345,KXS2]
MIBenum: 10
Source: ECMA registry
Alias: iso-ir-126
Alias: ISO_8859-7
Alias: ISO-8859-7 (preferred MIME name)
Alias: ELOT_928
Alias: ECMA-118
Alias: greek
Alias: greek8
Alias: csISOLatinGreek

name: T.101-G2                                            [RFC1345,KXS2]
MIBenum: 83
Source: ECMA registry
Alias: iso-ir-128
Alias: csISO128T101G2

name: ISO_8859-8:1988                                     [RFC1345,KXS2]
MIBenum: 11
Source: ECMA registry
Alias: iso-ir-138
Alias: ISO_8859-8
Alias: ISO-8859-8 (preferred MIME name)
Alias: hebrew
Alias: csISOLatinHebrew

name: ISO_8859-8-E                                  [RFC1556,Nussbacher]
MIBenum: 84
Source: RFC1556
Alias: csISO88598E
Alias: ISO-8859-8-E (preferred MIME name)

name: ISO_8859-8-I                                  [RFC1556,Nussbacher]
MIBenum: 85
Source: RFC1556
Alias: csISO88598I
Alias: ISO-8859-8-I (preferred MIME name)

name: CSN_369103                                          [RFC1345,KXS2]
MIBenum: 86
Source: ECMA registry
Alias: iso-ir-139
Alias: csISO139CSN369103

name: JUS_I.B1.002                                        [RFC1345,KXS2]
MIBenum: 87
Source: ECMA registry
Alias: iso-ir-141
Alias: ISO646-YU
Alias: js
Alias: yu
Alias: csISO141JUSIB1002

name: ISO_6937-2-add                                      [RFC1345,KXS2]
MIBenum: 14
Source: ECMA registry and ISO 6937-2:1983
Alias: iso-ir-142
Alias: csISOTextComm

name: IEC_P27-1                                           [RFC1345,KXS2]
MIBenum: 88
Source: ECMA registry
Alias: iso-ir-143
Alias: csISO143IECP271

name: ISO_8859-5:1988                                     [RFC1345,KXS2]
MIBenum: 8
Source: ECMA registry
Alias: iso-ir-144
Alias: ISO_8859-5
Alias: ISO-8859-5 (preferred MIME name)
Alias: cyrillic
Alias: csISOLatinCyrillic

name: JUS_I.B1.003-serb                                   [RFC1345,KXS2]
MIBenum: 89
Source: ECMA registry
Alias: iso-ir-146
Alias: serbian
Alias: csISO146Serbian

name: JUS_I.B1.003-mac                                    [RFC1345,KXS2]
MIBenum: 90
Source: ECMA registry
Alias: macedonian
Alias: iso-ir-147
Alias: csISO147Macedonian

name: ISO_8859-9:1989                                     [RFC1345,KXS2]
MIBenum: 12
Source: ECMA registry
Alias: iso-ir-148
Alias: ISO_8859-9
Alias: ISO-8859-9 (preferred MIME name)
Alias: latin5
Alias: l5
Alias: csISOLatin5

name: greek-ccitt                                         [RFC1345,KXS2]
MIBenum: 91
Source: ECMA registry
Alias: iso-ir-150
Alias: csISO150
Alias: csISO150GreekCCITT

name: NC_NC00-10:81                                       [RFC1345,KXS2]
MIBenum: 92
Source: ECMA registry
Alias: cuba
Alias: iso-ir-151
Alias: ISO646-CU
Alias: csISO151Cuba

name: ISO_6937-2-25                                       [RFC1345,KXS2]
MIBenum: 93
Source: ECMA registry
Alias: iso-ir-152
Alias: csISO6937Add

name: GOST_19768-74                                       [RFC1345,KXS2]
MIBenum: 94
Source: ECMA registry
Alias: ST_SEV_358-88
Alias: iso-ir-153
Alias: csISO153GOST1976874

name: ISO_8859-supp                                       [RFC1345,KXS2]
MIBenum: 95
Source: ECMA registry
Alias: iso-ir-154
Alias: latin1-2-5
Alias: csISO8859Supp

name: ISO_10367-box                                       [RFC1345,KXS2]
MIBenum: 96
Source: ECMA registry
Alias: iso-ir-155
Alias: csISO10367Box

name: ISO-8859-10 (preferred MIME name)			  [RFC1345,KXS2]
MIBenum: 13
Source: ECMA registry
Alias: iso-ir-157
Alias: l6
Alias: ISO_8859-10:1992
Alias: csISOLatin6
Alias: latin6

name: latin-lap                                           [RFC1345,KXS2]
MIBenum: 97
Source: ECMA registry
Alias: lap
Alias: iso-ir-158
Alias: csISO158Lap

name: JIS_X0212-1990                                      [RFC1345,KXS2]
MIBenum: 98
Source: ECMA registry
Alias: x0212
Alias: iso-ir-159
Alias: csISO159JISX02121990

name: DS_2089                                             [RFC1345,KXS2]
MIBenum: 99
Source: Danish Standard, DS 2089, February 1974
Alias: DS2089
Alias: ISO646-DK
Alias: dk
Alias: csISO646Danish

name: us-dk                                               [RFC1345,KXS2]
MIBenum: 100
Alias: csUSDK

name: dk-us                                               [RFC1345,KXS2]
MIBenum: 101
Alias: csDKUS

name: JIS_X0201                                           [RFC1345,KXS2]
MIBenum: 15
Source: JIS X 0201-1976.   One byte only, this is equivalent to 
        JIS/Roman (similar to ASCII) plus eight-bit half-width 
        Katakana
Alias: X0201
Alias: csHalfWidthKatakana

name: KSC5636                                             [RFC1345,KXS2]
MIBenum: 102
Alias: ISO646-KR
Alias: csKSC5636

name: ISO-10646-UCS-2
MIBenum: 1000
Source: the 2-octet Basic Multilingual Plane, aka Unicode
        this needs to specify network byte order: the standard
        does not specify (it is a 16-bit integer space)
Alias: csUnicode

name: ISO-10646-UCS-4
MIBenum: 1001
Source: the full code space. (same comment about byte order,
        these are 31-bit numbers.
Alias: csUCS4

name: DEC-MCS                                             [RFC1345,KXS2]
MIBenum: 2008
Source: VAX/VMS User's Manual, 
        Order Number: AI-Y517A-TE, April 1986.
Alias: dec
Alias: csDECMCS

name: hp-roman8                                  [HP-PCL5,RFC1345,KXS2]
MIBenum: 2004
Source: LaserJet IIP Printer User's Manual, 
        HP part no 33471-90901, Hewlet-Packard, June 1989.
Alias: roman8
Alias: r8
Alias: csHPRoman8

name: macintosh                                           [RFC1345,KXS2]
MIBenum: 2027
Source: The Unicode Standard ver1.0, ISBN 0-201-56788-1, Oct 1991
Alias: mac
Alias: csMacintosh

name: IBM037                                              [RFC1345,KXS2]
MIBenum: 2028
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp037
Alias: ebcdic-cp-us
Alias: ebcdic-cp-ca
Alias: ebcdic-cp-wt
Alias: ebcdic-cp-nl
Alias: csIBM037

name: IBM038                                              [RFC1345,KXS2]
MIBenum: 2029
Source: IBM 3174 Character Set Ref, GA27-3831-02, March 1990
Alias: EBCDIC-INT
Alias: cp038
Alias: csIBM038

name: IBM273                                              [RFC1345,KXS2]
MIBenum: 2030
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: CP273
Alias: csIBM273

name: IBM274                                              [RFC1345,KXS2]
MIBenum: 2031
Source: IBM 3174 Character Set Ref, GA27-3831-02, March 1990
Alias: EBCDIC-BE
Alias: CP274
Alias: csIBM274

name: IBM275                                              [RFC1345,KXS2]
MIBenum: 2032
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: EBCDIC-BR
Alias: cp275
Alias: csIBM275

name: IBM277                                              [RFC1345,KXS2]
MIBenum: 2033
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: EBCDIC-CP-DK
Alias: EBCDIC-CP-NO
Alias: csIBM277

name: IBM278                                              [RFC1345,KXS2]
MIBenum: 2034
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: CP278
Alias: ebcdic-cp-fi
Alias: ebcdic-cp-se
Alias: csIBM278

name: IBM280                                              [RFC1345,KXS2]
MIBenum: 2035
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: CP280
Alias: ebcdic-cp-it
Alias: csIBM280

name: IBM281                                              [RFC1345,KXS2]
MIBenum: 2036
Source: IBM 3174 Character Set Ref, GA27-3831-02, March 1990
Alias: EBCDIC-JP-E
Alias: cp281
Alias: csIBM281

name: IBM284                                              [RFC1345,KXS2]
MIBenum: 2037
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: CP284
Alias: ebcdic-cp-es
Alias: csIBM284

name: IBM285                                              [RFC1345,KXS2]
MIBenum: 2038
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: CP285
Alias: ebcdic-cp-gb
Alias: csIBM285

name: IBM290                                              [RFC1345,KXS2]
MIBenum: 2039
Source: IBM 3174 Character Set Ref, GA27-3831-02, March 1990
Alias: cp290
Alias: EBCDIC-JP-kana
Alias: csIBM290

name: IBM297                                              [RFC1345,KXS2]
MIBenum: 2040
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp297
Alias: ebcdic-cp-fr
Alias: csIBM297

name: IBM420                                              [RFC1345,KXS2]
MIBenum: 2041
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990, 
        IBM NLS RM p 11-11
Alias: cp420
Alias: ebcdic-cp-ar1
Alias: csIBM420

name: IBM423                                              [RFC1345,KXS2]
MIBenum: 2042
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp423
Alias: ebcdic-cp-gr
Alias: csIBM423

name: IBM424                                              [RFC1345,KXS2]
MIBenum: 2043
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp424
Alias: ebcdic-cp-he
Alias: csIBM424

name: IBM437                                              [RFC1345,KXS2]
MIBenum: 2011
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp437
Alias: 437
Alias: csPC8CodePage437

name: IBM500                                              [RFC1345,KXS2]
MIBenum: 2044
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: CP500
Alias: ebcdic-cp-be
Alias: ebcdic-cp-ch
Alias: csIBM500

name: IBM775                                                   [HP-PCL5]
MIBenum: 2087
Source: HP PCL 5 Comparison Guide (P/N 5021-0329) pp B-13, 1996
Alias: cp775
Alias: csPC775Baltic

name: IBM850                                              [RFC1345,KXS2]
MIBenum: 2009
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp850
Alias: 850
Alias: csPC850Multilingual

name: IBM851                                              [RFC1345,KXS2]
MIBenum: 2045
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp851
Alias: 851
Alias: csIBM851

name: IBM852                                              [RFC1345,KXS2]
MIBenum: 2010
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp852
Alias: 852
Alias: csPCp852

name: IBM855                                              [RFC1345,KXS2]
MIBenum: 2046
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp855
Alias: 855
Alias: csIBM855

name: IBM857                                              [RFC1345,KXS2]
MIBenum: 2047
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp857
Alias: 857
Alias: csIBM857

name: IBM860                                              [RFC1345,KXS2]
MIBenum: 2048
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp860
Alias: 860
Alias: csIBM860

name: IBM861                                              [RFC1345,KXS2]
MIBenum: 2049
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp861
Alias: 861
Alias: cp-is
Alias: csIBM861

name: IBM862                                              [RFC1345,KXS2]
MIBenum: 2013
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp862
Alias: 862
Alias: csPC862LatinHebrew

name: IBM863                                              [RFC1345,KXS2]
MIBenum: 2050
Source: IBM Keyboard layouts and code pages, PN 07G4586 June 1991
Alias: cp863
Alias: 863
Alias: csIBM863

name: IBM864                                              [RFC1345,KXS2]
MIBenum: 2051
Source: IBM Keyboard layouts and code pages, PN 07G4586 June 1991
Alias: cp864
Alias: csIBM864

name: IBM865                                              [RFC1345,KXS2]
MIBenum: 2052
Source: IBM DOS 3.3 Ref (Abridged), 94X9575 (Feb 1987)
Alias: cp865
Alias: 865
Alias: csIBM865

name: IBM866                                                     [Pond]
MIBenum: 2086
Source: IBM NLDG Volume 2 (SE09-8002-03) August 1994
Alias: cp866
Alias: 866
Alias: csIBM866

name: IBM868                                              [RFC1345,KXS2]
MIBenum: 2053
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: CP868
Alias: cp-ar
Alias: csIBM868

name: IBM869                                              [RFC1345,KXS2]
MIBenum: 2054
Source: IBM Keyboard layouts and code pages, PN 07G4586 June 1991
Alias: cp869
Alias: 869
Alias: cp-gr
Alias: csIBM869

name: IBM870                                              [RFC1345,KXS2]
MIBenum: 2055
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: CP870
Alias: ebcdic-cp-roece
Alias: ebcdic-cp-yu
Alias: csIBM870

name: IBM871                                              [RFC1345,KXS2]
MIBenum: 2056
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: CP871
Alias: ebcdic-cp-is
Alias: csIBM871

name: IBM880                                              [RFC1345,KXS2]
MIBenum: 2057
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp880
Alias: EBCDIC-Cyrillic
Alias: csIBM880

name: IBM891                                              [RFC1345,KXS2]
MIBenum: 2058
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp891
Alias: csIBM891

name: IBM903                                              [RFC1345,KXS2]
MIBenum: 2059
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp903
Alias: csIBM903

name: IBM904                                              [RFC1345,KXS2]
MIBenum: 2060
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: cp904
Alias: 904
Alias: csIBBM904

name: IBM905                                              [RFC1345,KXS2]
MIBenum: 2061
Source: IBM 3174 Character Set Ref, GA27-3831-02, March 1990
Alias: CP905
Alias: ebcdic-cp-tr
Alias: csIBM905

name: IBM918                                              [RFC1345,KXS2]
MIBenum: 2062
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: CP918
Alias: ebcdic-cp-ar2
Alias: csIBM918

name: IBM1026                                             [RFC1345,KXS2]
MIBenum: 2063
Source: IBM NLS RM Vol2 SE09-8002-01, March 1990
Alias: CP1026
Alias: csIBM1026

name: EBCDIC-AT-DE                                        [RFC1345,KXS2]
MIBenum: 2064
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csIBMEBCDICATDE

name: EBCDIC-AT-DE-A                                      [RFC1345,KXS2]
MIBenum: 2065 
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987 
Alias: csEBCDICATDEA

name: EBCDIC-CA-FR                                        [RFC1345,KXS2]
MIBenum: 2066
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICCAFR

name: EBCDIC-DK-NO                                        [RFC1345,KXS2]
MIBenum: 2067
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICDKNO

name: EBCDIC-DK-NO-A                                      [RFC1345,KXS2]
MIBenum: 2068
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICDKNOA

name: EBCDIC-FI-SE                                        [RFC1345,KXS2]
MIBenum: 2069
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICFISE

name: EBCDIC-FI-SE-A                                      [RFC1345,KXS2]
MIBenum: 2070
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICFISEA

name: EBCDIC-FR                                           [RFC1345,KXS2]
MIBenum: 2071
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICFR

name: EBCDIC-IT                                           [RFC1345,KXS2]
MIBenum: 2072
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICIT

name: EBCDIC-PT                                           [RFC1345,KXS2]
MIBenum: 2073
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICPT

name: EBCDIC-ES                                           [RFC1345,KXS2]
MIBenum: 2074
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICES

name: EBCDIC-ES-A                                         [RFC1345,KXS2]
MIBenum: 2075
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICESA

name: EBCDIC-ES-S                                         [RFC1345,KXS2]
MIBenum: 2076
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICESS

name: EBCDIC-UK                                           [RFC1345,KXS2]
MIBenum: 2077
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICUK

name: EBCDIC-US                                           [RFC1345,KXS2]
MIBenum: 2078
Source: IBM 3270 Char Set Ref Ch 10, GA27-2837-9, April 1987
Alias: csEBCDICUS

name: UNKNOWN-8BIT                                             [RFC1428]
MIBenum: 2079
Alias: csUnknown8BiT

name: MNEMONIC                                            [RFC1345,KXS2]
MIBenum: 2080
Source: RFC 1345, also known as "mnemonic+ascii+38"
Alias: csMnemonic

name: MNEM                                                [RFC1345,KXS2]
MIBenum: 2081
Source: RFC 1345, also known as "mnemonic+ascii+8200"
Alias: csMnem

name: VISCII                                                   [RFC1456]
MIBenum: 2082
Source: RFC 1456
Alias: csVISCII

name: VIQR                                                     [RFC1456]
MIBenum: 2083
Source: RFC 1456
Alias: csVIQR

name: KOI8-R  (preferred MIME name)                            [RFC1489]
MIBenum: 2084
Source: RFC 1489, based on GOST-19768-74, ISO-6937/8, 
        INIS-Cyrillic, ISO-5427.
Alias: csKOI8R

name: KOI8-U                                                   [RFC2319]
MIBenum: 2088
Source: RFC 2319

name: IBM00858
MIBenum: 2089
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM00858)    [Mahdi]
Alias: CCSID00858
Alias: CP00858
Alias: PC-Multilingual-850+euro

name: IBM00924
MIBenum: 2090
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM00924)    [Mahdi]
Alias: CCSID00924
Alias: CP00924
Alias: ebcdic-Latin9--euro

name: IBM01140
MIBenum: 2091
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM01140)    [Mahdi]
Alias: CCSID01140
Alias: CP01140
Alias: ebcdic-us-37+euro

name: IBM01141
MIBenum: 2092
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM01141)    [Mahdi]
Alias: CCSID01141
Alias: CP01141
Alias: ebcdic-de-273+euro

name: IBM01142
MIBenum: 2093
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM01142)    [Mahdi]
Alias: CCSID01142
Alias: CP01142
Alias: ebcdic-dk-277+euro
Alias: ebcdic-no-277+euro

name: IBM01143
MIBenum: 2094
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM01143)    [Mahdi]
Alias: CCSID01143
Alias: CP01143
Alias: ebcdic-fi-278+euro
Alias: ebcdic-se-278+euro

name: IBM01144
MIBenum: 2095
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM01144)    [Mahdi]
Alias: CCSID01144
Alias: CP01144
Alias: ebcdic-it-280+euro

name: IBM01145
MIBenum: 2096
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM01145)    [Mahdi]
Alias: CCSID01145
Alias: CP01145
Alias: ebcdic-es-284+euro

name: IBM01146
MIBenum: 2097
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM01146)    [Mahdi]
Alias: CCSID01146
Alias: CP01146
Alias: ebcdic-gb-285+euro

name: IBM01147
MIBenum: 2098
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM01147)    [Mahdi]
Alias: CCSID01147
Alias: CP01147
Alias: ebcdic-fr-297+euro

name: IBM01148
MIBenum: 2099
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM01148)    [Mahdi]
Alias: CCSID01148
Alias: CP01148
Alias: ebcdic-international-500+euro

name: IBM01149
MIBenum: 2100
Source: IBM See (http://www.iana.org/assignments/charset-reg/IBM01149)    [Mahdi]
Alias: CCSID01149
Alias: CP01149
Alias: ebcdic-is-871+euro

name: Big5-HKSCS                                                  [Yick]
MIBenum: 2101
Source:   See (http://www.iana.org/assignments/charset-reg/Big5-HKSCS) 
Alias: None

name: IBM1047                                                [Robrigado]
MIBenum: 2102
Source: IBM1047 (EBCDIC Latin 1/Open Systems)
http://www-1.ibm.com/servers/eserver/iseries/software/globalization/pdf/cp01047z.pdf
Alias: IBM-1047

name: PTCP154                                                    [Uskov]
MIBenum: 2103
Source: See (http://www.iana.org/assignments/charset-reg/PTCP154)
Alias: csPTCP154
Alias: PT154
Alias: CP154
Alias: Cyrillic-Asian

name: UNICODE-1-1                                              [RFC1641]
MIBenum: 1010
Source: RFC 1641
Alias: csUnicode11

name: SCSU
MIBenum: 1011
Source: SCSU See (http://www.iana.org/assignments/charset-reg/SCSU)     [Scherer]
Alias: None 

name: UTF-7                                                    [RFC2152]
MIBenum: 1012
Source: RFC 2152
Alias: None

name: UTF-16BE                                                 [RFC2781]
MIBenum: 1013
Source: RFC 2781
Alias: None

name: UTF-16LE                                                 [RFC2781]
MIBenum: 1014
Source: RFC 2781
Alias: None

name: UTF-16                                                   [RFC2781]
MIBenum: 1015
Source: RFC 2781
Alias: None

name: CESU-8                                                    [Phipps]
MIBenum: 1016
Source: <http://www.unicode.org/unicode/reports/tr26>
Alias: csCESU-8

name: UTF-32                                                     [Davis] 
MIBenum: 1017
Source: <http://www.unicode.org/unicode/reports/tr19/>
Alias: None

name: UTF-32BE                                                   [Davis]
MIBenum: 1018
Source: <http://www.unicode.org/unicode/reports/tr19/>
Alias: None

name: UTF-32LE                                                   [Davis]
MIBenum: 1019
Source: <http://www.unicode.org/unicode/reports/tr19/>
Alias: None

name: BOCU-1                                                   [Scherer]
MIBenum: 1020
Source: http://www.unicode.org/notes/tn6/
Alias: csBOCU-1

name: UNICODE-1-1-UTF-7                                        [RFC1642]
MIBenum: 103
Source: RFC 1642
Alias: csUnicode11UTF7

name: UTF-8                                                    [RFC2279]
MIBenum: 106
Source: RFC 2279
Alias: None 

name: ISO-8859-13
MIBenum: 109
Source: ISO See (http://www.iana.org/assignments/charset-reg/iso-8859-13)[Tumasonis] 
Alias: None

name: ISO-8859-14
MIBenum: 110
Source: ISO See (http://www.iana.org/assignments/charset-reg/iso-8859-14) [Simonsen]
Alias: iso-ir-199
Alias: ISO_8859-14:1998
Alias: ISO_8859-14
Alias: latin8
Alias: iso-celtic
Alias: l8

name: ISO-8859-15
MIBenum: 111
Source: ISO 
        Please see: <http://www.iana.org/assignments/charset-reg/ISO-8859-15>
Alias: ISO_8859-15
Alias: Latin-9

name: ISO-8859-16
MIBenum: 112
Source: ISO
Alias: iso-ir-226
Alias: ISO_8859-16:2001
Alias: ISO_8859-16
Alias: latin10
Alias: l10 

name: GBK                                                 
MIBenum: 113
Source: Chinese IT Standardization Technical Committee  
        Please see: <http://www.iana.org/assignments/charset-reg/GBK>
Alias: CP936
Alias: MS936
Alias: windows-936

name: GB18030
MIBenum: 114
Source: Chinese IT Standardization Technical Committee
        Please see: <http://www.iana.org/assignments/charset-reg/GB18030>
Alias: None

name: JIS_Encoding
MIBenum: 16
Source: JIS X 0202-1991.  Uses ISO 2022 escape sequences to
        shift code sets as documented in JIS X 0202-1991.
Alias: csJISEncoding

name: Shift_JIS  (preferred MIME name)
MIBenum: 17
Source: This charset is an extension of csHalfWidthKatakana by
        adding graphic characters in JIS X 0208.  The CCS's are
        JIS X0201:1997 and JIS X0208:1997.  The
        complete definition is shown in Appendix 1 of JIS
        X0208:1997.
        This charset can be used for the top-level media type "text".
Alias: MS_Kanji 
Alias: csShiftJIS

name: Extended_UNIX_Code_Packed_Format_for_Japanese
MIBenum: 18
Source: Standardized by OSF, UNIX International, and UNIX Systems
        Laboratories Pacific.  Uses ISO 2022 rules to select
               code set 0: US-ASCII (a single 7-bit byte set)
               code set 1: JIS X0208-1990 (a double 8-bit byte set)
                           restricted to A0-FF in both bytes
               code set 2: Half Width Katakana (a single 7-bit byte set)
                           requiring SS2 as the character prefix
               code set 3: JIS X0212-1990 (a double 7-bit byte set)
                           restricted to A0-FF in both bytes
                           requiring SS3 as the character prefix
Alias: csEUCPkdFmtJapanese
Alias: EUC-JP  (preferred MIME name)

name: Extended_UNIX_Code_Fixed_Width_for_Japanese
MIBenum: 19
Source: Used in Japan.  Each character is 2 octets.
                code set 0: US-ASCII (a single 7-bit byte set)
                              1st byte = 00
                              2nd byte = 20-7E
                code set 1: JIS X0208-1990 (a double 7-bit byte set)
                            restricted  to A0-FF in both bytes 
                code set 2: Half Width Katakana (a single 7-bit byte set)
                              1st byte = 00
                              2nd byte = A0-FF
                code set 3: JIS X0212-1990 (a double 7-bit byte set)
                            restricted to A0-FF in 
                            the first byte
                and 21-7E in the second byte
Alias: csEUCFixWidJapanese

name: ISO-10646-UCS-Basic
MIBenum: 1002
Source: ASCII subset of Unicode.  Basic Latin = collection 1
        See ISO 10646, Appendix A
Alias: csUnicodeASCII

name: ISO-10646-Unicode-Latin1
MIBenum: 1003
Source: ISO Latin-1 subset of Unicode. Basic Latin and Latin-1 
         Supplement  = collections 1 and 2.  See ISO 10646, 
         Appendix A.  See RFC 1815.
Alias: csUnicodeLatin1
Alias: ISO-10646

name: ISO-10646-J-1
Source: ISO 10646 Japanese, see RFC 1815.

name: ISO-Unicode-IBM-1261
MIBenum: 1005
Source: IBM Latin-2, -3, -5, Extended Presentation Set, GCSGID: 1261
Alias: csUnicodeIBM1261

name: ISO-Unicode-IBM-1268
MIBenum: 1006
Source: IBM Latin-4 Extended Presentation Set, GCSGID: 1268
Alias: csUnicodeIBM1268

name: ISO-Unicode-IBM-1276
MIBenum: 1007
Source: IBM Cyrillic Greek Extended Presentation Set, GCSGID: 1276
Alias: csUnicodeIBM1276

name: ISO-Unicode-IBM-1264
MIBenum: 1008
Source: IBM Arabic Presentation Set, GCSGID: 1264
Alias: csUnicodeIBM1264

name: ISO-Unicode-IBM-1265
MIBenum: 1009
Source: IBM Hebrew Presentation Set, GCSGID: 1265
Alias: csUnicodeIBM1265

name: ISO-8859-1-Windows-3.0-Latin-1                           [HP-PCL5] 
MIBenum: 2000
Source: Extended ISO 8859-1 Latin-1 for Windows 3.0.  
        PCL Symbol Set id: 9U
Alias: csWindows30Latin1

name: ISO-8859-1-Windows-3.1-Latin-1                           [HP-PCL5] 
MIBenum: 2001
Source: Extended ISO 8859-1 Latin-1 for Windows 3.1.  
        PCL Symbol Set id: 19U
Alias: csWindows31Latin1

name: ISO-8859-2-Windows-Latin-2                               [HP-PCL5] 
MIBenum: 2002
Source: Extended ISO 8859-2.  Latin-2 for Windows 3.1.
        PCL Symbol Set id: 9E
Alias: csWindows31Latin2

name: ISO-8859-9-Windows-Latin-5                               [HP-PCL5] 
MIBenum: 2003
Source: Extended ISO 8859-9.  Latin-5 for Windows 3.1
        PCL Symbol Set id: 5T
Alias: csWindows31Latin5

name: Adobe-Standard-Encoding                                    [Adobe]
MIBenum: 2005
Source: PostScript Language Reference Manual
        PCL Symbol Set id: 10J
Alias: csAdobeStandardEncoding

name: Ventura-US                                               [HP-PCL5]
MIBenum: 2006
Source: Ventura US.  ASCII plus characters typically used in 
        publishing, like pilcrow, copyright, registered, trade mark, 
        section, dagger, and double dagger in the range A0 (hex) 
        to FF (hex).  
        PCL Symbol Set id: 14J
Alias: csVenturaUS  

name: Ventura-International                                    [HP-PCL5]
MIBenum: 2007
Source: Ventura International.  ASCII plus coded characters similar 
        to Roman8.
        PCL Symbol Set id: 13J
Alias: csVenturaInternational

name: PC8-Danish-Norwegian                                     [HP-PCL5]
MIBenum: 2012
Source: PC Danish Norwegian
        8-bit PC set for Danish Norwegian
        PCL Symbol Set id: 11U
Alias: csPC8DanishNorwegian

name: PC8-Turkish                                              [HP-PCL5]
MIBenum: 2014
Source: PC Latin Turkish.  PCL Symbol Set id: 9T
Alias: csPC8Turkish

name: IBM-Symbols                                             [IBM-CIDT] 
MIBenum: 2015
Source: Presentation Set, CPGID: 259
Alias: csIBMSymbols

name: IBM-Thai                                                [IBM-CIDT] 
MIBenum: 2016
Source: Presentation Set, CPGID: 838
Alias: csIBMThai

name: HP-Legal                                                 [HP-PCL5]
MIBenum: 2017
Source: PCL 5 Comparison Guide, Hewlett-Packard,
        HP part number 5961-0510, October 1992
        PCL Symbol Set id: 1U
Alias: csHPLegal

name: HP-Pi-font                                               [HP-PCL5]
MIBenum: 2018
Source: PCL 5 Comparison Guide, Hewlett-Packard,
        HP part number 5961-0510, October 1992
        PCL Symbol Set id: 15U
Alias: csHPPiFont

name: HP-Math8                                                 [HP-PCL5]
MIBenum: 2019
Source: PCL 5 Comparison Guide, Hewlett-Packard,
        HP part number 5961-0510, October 1992
        PCL Symbol Set id: 8M
Alias: csHPMath8

name: Adobe-Symbol-Encoding                                      [Adobe]
MIBenum: 2020
Source: PostScript Language Reference Manual
        PCL Symbol Set id: 5M
Alias: csHPPSMath

name: HP-DeskTop                                               [HP-PCL5]
MIBenum: 2021
Source: PCL 5 Comparison Guide, Hewlett-Packard,
        HP part number 5961-0510, October 1992
        PCL Symbol Set id: 7J
Alias: csHPDesktop

name: Ventura-Math                                             [HP-PCL5]
MIBenum: 2022
Source: PCL 5 Comparison Guide, Hewlett-Packard,
        HP part number 5961-0510, October 1992
        PCL Symbol Set id: 6M
Alias: csVenturaMath

name: Microsoft-Publishing                                     [HP-PCL5]
MIBenum: 2023
Source: PCL 5 Comparison Guide, Hewlett-Packard,
        HP part number 5961-0510, October 1992
        PCL Symbol Set id: 6J
Alias: csMicrosoftPublishing

name: Windows-31J
MIBenum: 2024
Source: Windows Japanese.  A further extension of Shift_JIS
        to include NEC special characters (Row 13), NEC
        selection of IBM extensions (Rows 89 to 92), and IBM
        extensions (Rows 115 to 119).  The CCS's are
        JIS X0201:1997, JIS X0208:1997, and these extensions.
        This charset can be used for the top-level media type "text",
        but it is of limited or specialized use (see RFC2278).
        PCL Symbol Set id: 19K
Alias: csWindows31J

name: GB2312  (preferred MIME name)
MIBenum: 2025
Source: Chinese for People's Republic of China (PRC) mixed one byte, 
        two byte set: 
          20-7E = one byte ASCII 
          A1-FE = two byte PRC Kanji 
        See GB 2312-80 
        PCL Symbol Set Id: 18C
Alias: csGB2312

name: Big5  (preferred MIME name)
MIBenum: 2026
Source: Chinese for Taiwan Multi-byte set.
        PCL Symbol Set Id: 18T
Alias: csBig5

name: windows-1250
MIBenum: 2250
Source: Microsoft  (http://www.iana.org/assignments/charset-reg/windows-1250) [Lazhintseva]
Alias: None

name: windows-1251
MIBenum: 2251
Source: Microsoft  (http://www.iana.org/assignments/charset-reg/windows-1251) [Lazhintseva]
Alias: None

name: windows-1252
MIBenum: 2252
Source: Microsoft  (http://www.iana.org/assignments/charset-reg/windows-1252)       [Wendt]
Alias: None

name: windows-1253
MIBenum: 2253
Source: Microsoft  (http://www.iana.org/assignments/charset-reg/windows-1253) [Lazhintseva]
Alias: None

name: windows-1254
MIBenum: 2254
Source: Microsoft  (http://www.iana.org/assignments/charset-reg/windows-1254) [Lazhintseva]
Alias: None

name: windows-1255
MIBenum: 2255
Source: Microsoft  (http://www.iana.org/assignments/charset-reg/windows-1255) [Lazhintseva]
Alias: None

name: windows-1256
MIBenum: 2256
Source: Microsoft  (http://www.iana.org/assignments/charset-reg/windows-1256) [Lazhintseva]
Alias: None 

name: windows-1257
MIBenum: 2257
Source: Microsoft  (http://www.iana.org/assignments/charset-reg/windows-1257) [Lazhintseva]
Alias: None

name: windows-1258
MIBenum: 2258
Source: Microsoft  (http://www.iana.org/assignments/charset-reg/windows-1258) [Lazhintseva]
Alias: None

name: TIS-620
MIBenum: 2259
Source: Thai Industrial Standards Institute (TISI)	     [Tantsetthi]

name: HZ-GB-2312
MIBenum: 2085
Source: RFC 1842, RFC 1843                              [RFC1842, RFC1843]


REFERENCES
----------

[RFC1345]  Simonsen, K., "Character Mnemonics & Character Sets",
           RFC 1345, Rationel Almen Planlaegning, Rationel Almen
           Planlaegning, June 1992.

[RFC1428]  Vaudreuil, G., "Transition of Internet Mail from
           Just-Send-8 to 8bit-SMTP/MIME", RFC1428, CNRI, February
           1993.

[RFC1456]  Vietnamese Standardization Working Group, "Conventions for
           Encoding the Vietnamese Language VISCII: VIetnamese 
           Standard Code for Information Interchange VIQR: VIetnamese 
           Quoted-Readable Specification Revision 1.1", RFC 1456, May
           1993.

[RFC1468]  Murai, J., Crispin, M., and E. van der Poel, "Japanese
           Character Encoding for Internet Messages", RFC 1468,
           Keio University, Panda Programming, June 1993.

[RFC1489]  Chernov, A., "Registration of a Cyrillic Character Set",
           RFC1489, RELCOM Development Team, July 1993. 

[RFC1554]  Ohta, M., and K. Handa, "ISO-2022-JP-2: Multilingual
           Extension of ISO-2022-JP", RFC1554, Tokyo Institute of
           Technology, ETL, December 1993. 

[RFC1556]  Nussbacher, H., "Handling of Bi-directional Texts in MIME",
           RFC1556, Israeli Inter-University, December 1993. 

[RFC1557]  Choi, U., Chon, K., and H. Park, "Korean Character Encoding
           for Internet Messages", KAIST, Solvit Chosun Media,
           December 1993.

[RFC1641]  Goldsmith, D., and M. Davis, "Using Unicode with MIME",
           RFC1641, Taligent, Inc., July 1994. 

[RFC1642]  Goldsmith, D., and M. Davis, "UTF-7", RFC1642, Taligent,
           Inc., July 1994.

[RFC1815]  Ohta, M., "Character Sets ISO-10646 and ISO-10646-J-1",
           RFC 1815, Tokyo Institute of Technology, July 1995.


[Adobe]    Adobe Systems Incorporated, PostScript Language Reference
           Manual, second edition, Addison-Wesley Publishing Company,
           Inc., 1990.

[ECMA Registry]  ISO-IR: International Register of Escape Sequences
           http://www.itscj.ipsj.or.jp/ISO-IE/  Note: The current
           registration authority is IPSJ/ITSCJ, Japan.

[HP-PCL5]  Hewlett-Packard Company, "HP PCL 5 Comparison Guide", 
           (P/N 5021-0329) pp B-13, 1996.

[IBM-CIDT] IBM Corporation, "ABOUT TYPE: IBM's Technical Reference
           for Core Interchange Digitized Type", Publication number
           S544-3708-01

[RFC1842]  Wei, Y., J. Li, and Y. Jiang, "ASCII Printable
           Characters-Based Chinese Character Encoding for Internet
           Messages", RFC 1842, Harvard University, Rice University,
           University of Maryland, August 1995.

[RFC1843]  Lee, F., "HZ - A data Format for Exchanging Files of
           Arbitrarily Mixed Chinese and ASCII Characters", RFC 1843,
           Stanford University, August 1995.

[RFC2152]  Goldsmith, D., M. Davis, "UTF-7: A Mail-Safe Transformation
	   Format of Unicode", RFC 2152, Apple Computer, Inc.,
	   Taligent Inc., May 1997.

[RFC2279]  Yergeau, F., "UTF-8, A Transformation Format of ISO 10646",
           RFC 2279, Alis Technologies, January, 1998.

[RFC2781]  Hoffman, P., Yergeau, F., "UTF-16, an encoding of ISO 10646",
           RFC 2781, February 2000.


PEOPLE
------

[KXS2] Keld Simonsen <Keld.Simonsen@dkuug.dk>

[Choi] Woohyong Choi <whchoi@cosmos.kaist.ac.kr>

[Davis] Mark Davis, <mark@unicode.org>, April 2002.

[Lazhintseva] Katya Lazhintseva, <katyal@MICROSOFT.com>, May 1996.

[Mahdi] Tamer Mahdi, <tamer@ca.ibm.com>, August 2000.

[Murai] Jun Murai <jun@wide.ad.jp>

[Nussbacher] Hank Nussbacher, <hank@vm.tau.ac.il>

[Ohta] Masataka Ohta, <mohta@cc.titech.ac.jp>, July 1995.

[Phipps] Toby Phipps, <tphipps@peoplesoft.com>, March 2002.

[Pond] Rick Pond, <rickpond@vnet.ibm.com>, March 1997.

[Robrigado] Reuel Robrigado, <reuelr@ca.ibm.com>, September 2002.

[Scherer] Markus Scherer, <markus.scherer@jtcsv.com>, August 2000, 
          September 2002.

[Simonsen] Keld Simonsen, <Keld.Simonsen@rap.dk>, August 2000.

[Tantsetthi] Trin Tantsetthi, <trin@mozart.inet.co.th>, September 1998.

[Tumasonis] Vladas Tumasonis, <vladas.tumasonis@maf.vu.lt>, August 2000.

[Uskov] Alexander Uskov, <auskov@idc.kz>, September 2002.

[Wendt] Chris Wendt, <christw@microsoft.com>, December 1999.

[Yick] Nicky Yick, <cliac@itsd.gcn.gov.hk>, October 2000.

\endcode
*/
