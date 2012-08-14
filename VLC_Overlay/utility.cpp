#include "stdafx.h"
#include "utility.h"

bool isTimerTick(int timer){
	if( mTimers.find(timer)==mTimers.end() )		// Key not found, create new shit
		mTimers[timer] = clock();
	float tmpClock = clock();
	if( tmpClock - mTimers[timer] > timer ){
		mTimers[timer] = tmpClock;
		return true;
	}
	return false;
}


bool isKeyPressed(UINT vk){
	if( mKeys.find(vk)==mKeys.end() )		// Key not found, create new shit
		mKeys[vk] = false;
	if( !mKeys[vk] && isKeyDown(vk) ) {
		mKeys[vk] = true;
		return true;
	} 
	if( mKeys[vk] && !isKeyDown(vk) )
		mKeys[vk] = false;
	return false;
}


void __cdecl logIt(const char * fmt, ... ){
	va_list va_alist;
	char logbuf[256];
	FILE * fp;
	struct tm * current_tm;
	time_t current_time;

	time (&current_time);
	current_tm = localtime (&current_time);

	sprintf (logbuf, "[%02d:%02d:%02d]: ", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec);

	va_start (va_alist, fmt);
	_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist);
	va_end (va_alist);

	if ( (fp = fopen ( LOGFILE, "a")) != NULL )
	{
		fprintf ( fp, "%s\n", logbuf );
		fclose (fp);
	}
}

string formatTime( int t ){
	char buf[10];
	int hour = t;
	int sec = hour%60;
	hour /= 60;
	int min = hour%60;
	hour /= 60;
	sprintf(buf, "%02d:%02d:%02d", hour, min, sec);
	return buf;
}


bool isCursorInRect( tagPOINT pos, RECT r){
	return pos.x >= r.left && pos.x <= r.right
		&& pos.y >= r.top && pos.y <= r.bottom;
}


string getCurrentProcessName(){
	char process[512];
	GetModuleFileName(GetModuleHandle(0), process, sizeof(process));
	PathStripPath( process );
	return Str(process);
}


float cTick = 0.0f;
int nFrame = 0;
int currentFPS = 0;
int getFPS(){	// Need to call it every frame.
	nFrame++;
	float nTick = clock();
	if(nTick - cTick > 1000.0f){
		currentFPS = ceil((float)(nFrame*1000) / (nTick - cTick));
		nFrame = 0;
		cTick = nTick;
	}
	return currentFPS;
}

string getBLastAndRemoveFromDirectory( string dir, string filter ){
	WIN32_FIND_DATA ffd;
	string dirFilter = dir + filter;
	HANDLE hdir = FindFirstFile(dirFilter.c_str(), &ffd);
	if( hdir == INVALID_HANDLE_VALUE )
		return "";

	string alast = "";
	string last;
	FILETIME talast = {0,0};
	FILETIME tlast = {0,0};
		// Find the file before last, sorted by creation time.
		// Delete every files that arent last or before-last.
		// Ignore & Delete the empty files.
	do {
		if( ffd.nFileSizeLow != 0 && CompareFileTime(&ffd.ftCreationTime, &talast) >= 0 ){
			string rem = dir + alast;
			remove( rem.c_str() );
			if( CompareFileTime(&ffd.ftCreationTime, &tlast) >= 0 ){
				talast = tlast;
				alast = last;
				tlast = ffd.ftCreationTime;
				last = ffd.cFileName;
			}
			else {
				talast = ffd.ftCreationTime;
				alast = ffd.cFileName;
			}
		} else {
			string rem = dir + (string)ffd.cFileName;
			remove( rem.c_str() );
		}
	} while( FindNextFile( hdir, &ffd ) != 0 );
		

	if( alast != "" ){
		string file = dir + alast;
		return file;
	}

	return "";
}