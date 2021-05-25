/*****************************************************************************\
 *                                                                           *
 * library XiMoL                                                             *
 * Copyright (C) 2009 Vincent LaBella                                        *
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
	\brief XML streams declarations.
	
	\author Vincent LaBella
	\version 1.0

  */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <stream.hpp>
#include <time.h>
#include <sstream>
#include <sstream.hpp>
#include <datatypes/blob.hpp>
#include <zlib.h>
#include <myzip/ioapi.h>
#include <myzip/zip.h>
#include <myzip/unzip.h>
#include <zipstream.hpp>
using namespace std;

XIMOL_BEGIN_NAMESPACE

xozipfstream::xozipfstream()
	:xostringstream()
	,xml_filename("manifest.xml")
	,xml_filename_from_zip(false)
	,opened(false)
{}

xozipfstream::xozipfstream(const ::std::basic_string<xchar_t>& str)
	:xostringstream(str)
	,xml_filename("manifest.xml")
	,xml_filename_from_zip(false)
	,opened(false)
{}

xozipfstream::~xozipfstream()
{}

void xozipfstream::set_xml_filename_from_zip(bool b)
{
	xml_filename_from_zip = b;
}

bool xozipfstream::open(std::string _filename){
	// doesn't do anything just sets the filename
	// and creates the zip file
	filename = _filename;
	file = zipOpen(filename.c_str(),APPEND_STATUS_CREATE);
	if(file == NULL){
		opened = false;
		return false;
	}
	opened = true;
	if(xml_filename_from_zip){
		xml_filename = _filename;
		size_t pos = xml_filename.rfind(".");
		if( pos != xml_filename.npos) xml_filename.erase(pos);
		xml_filename += ".xml";
	}
	tm* filedate;
	time_t tm_t; time(&tm_t);
	filedate = localtime(&tm_t);
	zip_fileinfo zipfileinfo;
	zipfileinfo.tmz_date.tm_sec  = filedate->tm_sec;
	zipfileinfo.tmz_date.tm_min  = filedate->tm_min;
	zipfileinfo.tmz_date.tm_hour = filedate->tm_hour;
	zipfileinfo.tmz_date.tm_mday = filedate->tm_mday;
	zipfileinfo.tmz_date.tm_mon  = filedate->tm_mon ;
	zipfileinfo.tmz_date.tm_year = filedate->tm_year;
	zipfileinfo.dosDate = 0;
	zipfileinfo.internal_fa = 0;
	zipfileinfo.external_fa = 0;
	zipOpenNewFileInZip(file,xml_filename.c_str(),&zipfileinfo,NULL,0,NULL,0,NULL,Z_DEFLATED,1);//low level for speed
	return true;
}

bool xozipfstream::is_open() const
{ 
	return opened;
}

void xozipfstream::close()
{
	// this is where all the writing happens
	zipWriteInFileInZip(file,ximol::str<std::string>::cast(this->str()).c_str(),
		static_cast<unsigned int>(ximol::str<std::string>::cast(this->str()).length())
		);
	zipCloseFileInZip(file);

	tm* filedate;
	time_t tm_t; time(&tm_t);
	filedate = localtime(&tm_t);
	zip_fileinfo zipfileinfo;
	zipfileinfo.tmz_date.tm_sec  = filedate->tm_sec;
	zipfileinfo.tmz_date.tm_min  = filedate->tm_min;
	zipfileinfo.tmz_date.tm_hour = filedate->tm_hour;
	zipfileinfo.tmz_date.tm_mday = filedate->tm_mday;
	zipfileinfo.tmz_date.tm_mon  = filedate->tm_mon ;
	zipfileinfo.tmz_date.tm_year = filedate->tm_year;
	zipfileinfo.dosDate = 0;
	zipfileinfo.internal_fa = 0;
	zipfileinfo.external_fa = 0;

	ximol::datatypes::_itBLOBs itb = BLOBs.begin();
	while(itb != BLOBs.end()){
		if(!itb->second.empty()){
			zipOpenNewFileInZip(file,itb->first.c_str(),&zipfileinfo,NULL,0,NULL,0,NULL,Z_DEFLATED,1);//low level for speed
		//cout << itb->first << " "<< itb->second.size() <<endl;
			zipWriteInFileInZip(file,static_cast<void*>(&itb->second[0]),static_cast<unsigned int>(itb->second.size()));
			zipCloseFileInZip(file);
		}
		itb++;
	}
	zipClose(file,NULL);
}

xizipfstream::xizipfstream()
	:xistringstream()
	,opened(false)
{}

xizipfstream::xizipfstream(const ::std::basic_string<xchar_t>& str)
	:xistringstream(str)
	,opened(false)
{}

xizipfstream::~xizipfstream()
{}

bool xizipfstream::open(std::string filename)
{
	// opens and reads it all into the stream and blob map
	unzFile file = unzOpen(filename.c_str());
	if(file == NULL) return false;
	opened = true;
	bool go = true;
	string xml_filename; // first .xml file encountered will be the xml file - maybe change this with some optionin the future
	while(go){
		if(UNZ_OK == unzOpenCurrentFile(file)){
			unz_file_info zfi;
			char Filename[256];
			unzGetCurrentFileInfo(file,&zfi,Filename,256,NULL,0,NULL,0);
			string sFilename = Filename;
			if((sFilename.rfind(".xml") == sFilename.length()-4) && xml_filename == ""){
				xml_filename = Filename;
				//cout << "xml filename = "<<xml_filename<<endl;
			}
			const size_t chunk_size = 40960;
			const int ichunk_size = 40960;  // make sure this is same as above
			char dest[40970]; int err;
			ximol::datatypes::_BLOB blob;
			do{
				err = unzReadCurrentFile(file,dest,chunk_size);
				if (err<0) return false;
				if (err >= 0 && err <= ichunk_size){
					dest[err] = '\0';
					blob.insert(blob.end(),&dest[0],&dest[err]);
				}
			}while ( err > 0 );
			unzCloseCurrentFile(file);
			BLOBs[Filename] = blob;
			//cout << Filename << " "<<blob.size()<<endl;
		}
		go = (UNZ_OK == unzGoToNextFile(file));
	}
	unzClose(file);
	//
	// -- find the xml file and store it in the string buffer
	//
	ximol::datatypes::_itBLOBs itb = BLOBs.find(xml_filename);
	if(itb != BLOBs.end()){
		xostringstream xos;
		xos << &(itb->second[0]);
		str(xos.str());
	}
	return true;

}
bool xizipfstream::is_open() const
{ 
	return opened;
}

void xizipfstream::close()
{

}

XIMOL_END_NAMESPACE




