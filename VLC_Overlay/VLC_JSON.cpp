#include "stdafx.h"
#include "VLC_JSON.h"
#include "VLC_thread.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filestream.h"

tVLCStatus VLC_Status;

void updateVLC_JSON(){
	VLC_Status.isInit = false;

	SENDVLC( REFRESH );

	FILE* fStatus = fopen( statusFile, "r");
	if( fStatus == NULL ){
		//logIt("VLC-parsing: ERROR: Impossible to open status.json temp file");
		return ;
	}

	rapidjson::FileStream fsStatus( fStatus );
	rapidjson::Document dStatus;

	if( dStatus.ParseStream<0>( fsStatus ).HasParseError() )
		JSONERROR(Impossible to parse status.json)
	
	JSONGET2(VLC_Status.state, dStatus, state, String);

	JSONSIMPLEGET(dStatus, information);
	JSONSIMPLEGET(information, category);
	JSONSIMPLEGET(category, meta);
	JSONGET2(VLC_Status.filename, meta, filename, String);

	JSONGET(category, str0, "Stream 0");
	JSONGET2(VLC_Status.type, str0, Type, String);

	if( VLC_Status.type == "Video" ){
		JSONGET2(string tmp_res, str0, Resolution, String);
			// Parse resolution
		int pos = int(tmp_res.find("x"));
		VLC_Status.resX = atoi( tmp_res.substr(0, pos).c_str() );
		VLC_Status.resY = atoi( tmp_res.substr(pos+1).c_str() );
	}

	JSONGET2( VLC_Status.time, dStatus, time, Int );
	JSONGET2( VLC_Status.length, dStatus, length, Int );
	JSONGET2( VLC_Status.volume, dStatus, volume, Int );

	fclose( fStatus );
	VLC_Status.isInit = true;
}