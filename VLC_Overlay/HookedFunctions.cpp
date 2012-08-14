#include "HookedFunctions.h"
#include "utility.h"
#include "VLC_Overlay.h"
#include "VLC_thread.h"
#include "VLC_JSON.h"
#include "../GUI_Engine/GUI_Engine.h"


bool isInit = false;
void nEndScene( LPDIRECT3DDEVICE9 pDevice ) {
	
	if( !isInit ){
		logIt("Initialisation of VLC_Overlay...");
		VLC_Overlay_Init( pDevice );
		isInit = true;
	}

	if( isTimerTick( refreshTime ) )
		updateVLC_JSON();

	m_engine.completeProcess();
}