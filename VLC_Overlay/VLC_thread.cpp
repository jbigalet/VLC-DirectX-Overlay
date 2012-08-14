#include "stdafx.h"
#include "vlc_thread.h"


DWORD idVLC_Thread;
void initVLC_Thread(){
	CreateThread(0, 0, thVLC, 0, 0, &idVLC_Thread);
}

DWORD WINAPI thVLC( LPVOID ){
	while(1){
		isRefreshed = false;
		MSG msg;
		while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) == TRUE ){
			HandleVLCMessage( msg.message, msg.lParam );
			//TranslateMessage( &msg );
			//DispatchMessage( &msg );
		}
		//Sleep( 10 );

		//	If Translate/Dispatch or Sleep, the thread
		//	can't handle ExitThread during dll_process_detach
		//	( the ExitThread method is still random-ish exiting )
	}
	return 0;
}


void HandleVLCMessage( DWORD Id, LPARAM lparam ){
	switch( Id ){
		case VLC_KILLTHREAD:
			logIt("VLC Thread killed.");
			ExitThread(0);
			break;			// For clarity
		case VLC_REFRESH:
			if( isRefreshed )
				break;
			isRefreshed = true;
			remove( statusFile );
			LoadURL( statusURL, statusFile );
			break;
		case VLC_PAUSE:
			SendCMD( "pl_pause" );
			break;
		case VLC_SEEK:
			SendCMD( "seek&val=" + Str( lparam ) );
			break;
		case VLC_SEEKRELN:
			SendCMD( "seek&val=-" + Str( lparam ) );
			break;
		case VLC_SEEKRELP:
			SendCMD( "seek&val=+" + Str( lparam ) );
			break;
		case VLC_NEXT:
			SendCMD( "pl_next" );
			break;
		case VLC_PREVIOUS:
			SendCMD( "pl_previous" );
			break;
		case VLC_VOLUME:
			SendCMD( "volume&val=" + Str( lparam ) );
			break;
		default:
			logIt( "VLC-handle: ERROR: %i command undefined", Id );
	}
}

void SendCMD( string cmd ){
	string urlCmd = statusURL + (string)"?command=" + cmd;
	LoadURL( urlCmd ); 
}

void LoadURL( string url ){
	LoadURL( url, tmpFile );
}

void LoadURL( string url, string file ){
	URLDownloadToFile(NULL, url.c_str(), file.c_str(), 0, NULL);
}