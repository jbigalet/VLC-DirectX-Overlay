#pragma once

#include "stdafx.h"

#define LOGFILE "C:/Users/Mystic/Documents/vlc-dx9-overlay-tmp/log.txt"

#ifndef TEMPLSTR_H_
	#define TEMPLSTR_H_

	template <typename T>
	string Str( const T & t ) {
	   ostringstream os;
	   os << t;
	   return os.str();
	}
#endif

#define isKeyDown(key)		(GetAsyncKeyState( key ) & 0x8000)

static map<int, float> mTimers;
bool isTimerTick(int);

static map<UINT, bool> mKeys;
bool isKeyPressed( UINT );


void __cdecl logIt(const char * fmt, ... );
bool isCursorInRect( tagPOINT, RECT);
string formatTime( int );
string getCurrentProcessName();
int getFPS();		// Need to call it every frame
string getBLastAndRemoveFromDirectory( string dir, string filter );