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

dependancies:

* boost
* zlib

prior to building with cmake set ZLIB_ROOT and BOOST_ROOT to appropriate folders as environment variables or pass them to the cmake command.  For example on Windows


	cd ximol
	cmake -S ./src -B ./build -A x64 -T host=x64 -DBOOST_ROOT=... -DZLIB_ROOT=...
	cmake --build ./build --config Release

On windows set USE_STATIC_RUNTIMES=ON to link to static runtimes: /MT instead of /MD.

On Mac or Linux

	cd ximol
	cmake -S ./src -B ./build -DCMAKE_BUILD_TYPE=Release -DBOOST_ROOT=... -DZLIB_ROOT=...
	cd build ; make

## Example

the following XML file

	<MyXML Foo="some_info">
	<Double>
		3.14159
	</Double>
	...
	</MyXML>


is read like this

	try{
		double Double;
		int Int;
		string String;
		float Float;
		char Char;
		time_t Time;
		size_t Size;
		ximol::xifstream xis;
		xis.encoding("UTF-8");
		xis.open(filename);
		if(xis.is_open()){
			xis >> ximol::xml::prolog();
			while( is_stag(xis) ){
			ximol::xstring s;
			ximol::xml::attributes att;
			ximol::parser::read_stag(xis,s,att);
			if( ximol::str<std::string>::cast(s) == "MyInfo" ){
				std::string temps;
				temps = ximol::extract_attribute<std::string>::get(att,"Foo");
			}else if( ximol::str<std::string>::cast(s) == "Double" ){
				xis >> ximol::xml::content(Double) >> ximol::xml::etag();
			}else if( ximol::str<std::string>::cast(s) == "Int" ){
				xis >> ximol::xml::content(Int) >> ximol::xml::etag();
			}else if( ximol::str<std::string>::cast(s) == "Float" ){
				xis >> ximol::xml::content(Float) >> ximol::xml::etag();
			}else if( ximol::str<std::string>::cast(s) == "String" ){
				xis >> ximol::xml::content(String) >> ximol::xml::etag();
			}else if( ximol::str<std::string>::cast(s) == "Char" ){
				xis >> ximol::xml::content(Char) >> ximol::xml::etag();
			}else if( ximol::str<std::string>::cast(s) == "Time" ){
				xis >> ximol::xml::content(Time) >> ximol::xml::etag();
			}else if( ximol::str<std::string>::cast(s) == "Size" ){
				xis >> ximol::xml::content(Size) >> ximol::xml::etag();
			} // -- end while
			xis >> ximol::xml::etag();
			xis.close();
		}
	}
	catch(std::exception &){
		...
	}

