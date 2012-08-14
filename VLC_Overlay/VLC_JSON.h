#pragma once

#include "utility.h"


#define JSONERROR(error)	{												\
		logIt("VLC-parsing: ERROR: %s", #error);							\
		fclose( fStatus );													\
		return;																\
	}

#define JSONCHECK(value,tocheck)											\
	if( !##value##.HasMember(tocheck))										\
		JSONERROR( [status.json > value > tocheck] parsing failed )

#define JSONGET(value,newvar,toget)											\
	JSONCHECK(value,toget);													\
	rapidjson::Value &##newvar = value##[toget]

#define JSONSIMPLEGET(value,toget)	JSONGET(value,toget,#toget)
#define JSONGET2(var,value,toget,param)										\
	JSONCHECK(value,#toget);												\
	var = value##[#toget].Get##param##()



struct tVLCStatus{
	boolean isInit;
	string filename;
	string state;
	int resX;
	int resY;
	int time;
	int length;
	int volume;
	string type;
};

extern tVLCStatus VLC_Status;
void updateVLC_JSON();