# XiMoL C++ XML Parsing Library

XiMoL is a C++ API for XML data-binding, i.e., put in plain english, a library to write and read XML documents to and from C++ structures. It complies to a double standard: the XML 1.0 standard and the C++ standard, more specifically to the STL iostream specification. This double filiation will hopefully fill a gap that a lot of experienced C++ programmers have probably suffered from as much as the author did. XiMoL is also a paradigm shift from the DOM and SAX approach. If DOM can be seen as a "whole document" approach and SAX as a "per element" approach, XiMoL is in between, a sort of object-oriented approach to XML treatment, with all the wealth of expressiveness that comes with it. With SAX, it shares the property that code must be written to read-in the XML document and that XiMoL is not a validating processing of the document. At least not out of the box. But contrarily to SAX, it allows validation to be written and contrarily to DOM, it allows partial validation of a document. For all these reasons, XiMoL is more than a C++ library, or for what it is, any particular computer language. It is a new approach to XML treatment. XiMoL can also be described rather accurately as an XML serialization library where a dedicated XML stream is written to and read from. XiMoL brings you all the power of XML with all the power of the STL iostreams. 

XiMoL is an XML reader/writer (non-validating) library written in C++. It is a iostream-oriented library based on the STL and not a SAX or DOM library (like Xerces, ...). Each object has its own reader/writer (operator<< and operator>>).

## Main points:

* XiMoL is not really a DOM or a SAX,
* The STL (iostream (Why iostream is good for you ?)) for the interface and the encoding method (std::facet),
* Characters are converted by libiconv,
* XiMoL is adapted for the databinding.

## History

This is a slightly modified version of the library from sourceforge.

## Build instructions

This project uses cmake and can be built on Windows, Mac, and Linux
