#
# CMakeLists.txt for XiMol C++ Library - Stream based XML parsing
#
cmake_minimum_required (VERSION 3.18)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckIncludeFileCXX)
project(ximol)
#
# -- options
#
# for windows builds 
if(NOT DEFINED USE_STATIC_RUNTIME)
	set(USE_STATIC_RUNTIME OFF)
endif()
#
# -- find zlib for zipstream
#
# must set ZLIB_ROOT
# Searches for shared library by default
# force to static if user is building a static library
find_package(ZLIB)
#
# -- find boost
#
# user must define BOOST_ROOT
# only headers are needed
find_package(Boost)

set(CMAKE_DEBUG_POSTFIX "d")

if(WIN32)
	#
	# -- Windows option for runtime library - assume DLL /MD unless USE_STATIC_RUNTIME=ON then use static /MT
	#
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
	if(DEFINED USE_STATIC_RUNTIME AND USE_STATIC_RUNTIME)
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	endif()
endif()

set(SOURCE_FILES
	myzip/ioapi.c 
	myzip/zip.c 
	myzip/unzip.c
	error.cpp
	fstream.cpp
	io.cpp
	sstream.cpp
	zipstream.cpp
	str_cast.cpp
	stream.cpp
	translation.cpp
	xml/cdata.cpp
	xml/attributes.cpp
	xml/content.cpp
	xml/blobcontent.cpp
	xml/context.cpp
	xml/etag.cpp
	xml/open_stag.cpp
	xml/prolog.cpp
	xml/reader.cpp
	xml/stag.cpp
	xml/xml_decl.cpp
	dom/element_tree.cpp
	facet/white_space.cpp
	parser/utils.cpp
	control_flow.cpp
	codecvt.cpp
	encoders/encoders.cpp
	encoders/encoders_error.cpp
	encoders/libiconv/iconv.c
	encoders/libcharset/localcharset.c
	datatypes/string.cpp
)
# set global options for all targets
CHECK_INCLUDE_FILE(stdlib.h    HAVE_STDLIB_H)
CHECK_INCLUDE_FILE(string.h    HAVE_STRING_H)
CHECK_INCLUDE_FILE(stddef.h 	HAVE_STDDEF_H)
CHECK_INCLUDE_FILE_CXX(stddef.h 	HAVE_STDDEF_H)
CHECK_INCLUDE_FILE_CXX(stdlib.h    HAVE_STDLIB_H)
CHECK_INCLUDE_FILE_CXX(string.h    HAVE_STRING_H)
add_compile_definitions(XIMOL_SOURCE)
add_compile_definitions(XIMOL_NO_LIB)
add_compile_definitions(LIBDIR="tmp")

if(WIN32)
	add_compile_options($<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Release>:/GL>>)
	add_compile_definitions(WIN32)
	# add_compile_options(/wd4005) # macro redfinition
	add_compile_options(/wd4421)
	add_compile_options(/wd4018)
	add_compile_options(/wd4028)
	add_compile_options(/wd4090)
	add_compile_options(/wd4133)
	add_compile_options(/wd4244)
	add_compile_options(/wd4251)
elseif(UNIX)
	add_compile_definitions(__LINUX__)
	add_compile_options($<$<COMPILE_LANGUAGE:C>:-Wno-incompatible-pointer-types>)
	add_compile_options($<$<COMPILE_LANGUAGE:C>:-Wno-implicit-function-declaration>)
	add_compile_options($<$<COMPILE_LANGUAGE:C>:-Wno-int-conversion>)
elseif(APPLE)
	add_compile_definitions(__LINUX__)
endif()
# define the two targets
add_library (ximol SHARED ${SOURCE_FILES})
add_library (ximolstatic STATIC ${SOURCE_FILES})
#target specific options
target_compile_definitions(ximolstatic PUBLIC XIMOL_STATIC_LINK)
target_compile_definitions(ximol PUBLIC XIMOL_DYN_LINK)
if(WIN32)
    set_target_properties(ximolstatic PROPERTIES STATIC_LIBRARY_OPTIONS $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Release>:/LTCG>>)
    target_link_options(ximol PUBLIC $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Release>:/LTCG>>)
endif()

target_include_directories(ximol 
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ZLIB_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)

target_link_libraries (ximol 
	LINK_PUBLIC 
	${ZLIB_LIBRARIES}
)

target_include_directories(ximolstatic
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ZLIB_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)

