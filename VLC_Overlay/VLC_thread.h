#pragma once

#include "utility.h"

#define SENDVLC(command)		PostThreadMessage(idVLC_Thread, VLC_##command, 0, 0)
#define SENDVLC_(command,param)	PostThreadMessage(idVLC_Thread, VLC_##command, 0, (LPARAM)param)

#define VLC_REFRESH		WM_USER + 1
#define VLC_PAUSE		WM_USER + 2
#define VLC_SEEK		WM_USER + 3
#define VLC_KILLTHREAD	WM_USER + 4
#define VLC_VOLUME		WM_USER + 5
#define VLC_SEEKRELN	WM_USER + 6
#define VLC_SEEKRELP	WM_USER + 7
#define VLC_NEXT		WM_USER + 8
#define VLC_PREVIOUS	WM_USER + 9



#define statusURL		"http://127.0.0.1:8080/requests/status.json"
#define statusFile		"C:/Users/Mystic/Documents/vlc-dx9-overlay-tmp/status.txt"
#define tmpFile			"C:/Users/Mystic/Documents/vlc-dx9-overlay-tmp/tmp.txt"
#define refreshTime		50

	// bool to prevent a large REFRESH message list to handle
static bool isRefreshed;

extern DWORD idVLC_Thread;
void initVLC_Thread();

DWORD WINAPI thVLC( LPVOID );
void HandleVLCMessage( DWORD, LPARAM );
void SendCMD( string );
void LoadURL( string );
void LoadURL( string, string );