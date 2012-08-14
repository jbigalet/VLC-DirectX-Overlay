#include "dllmain.h"
#include "utility.h"
#include "HookedFunctions.h"
#include "VLC_thread.h"
#include "../GUI_Engine/GUI_Engine.h"
#include "NCodeHook\NCodeHookInstantiation.h"

HINSTANCE hDLL;
NCodeHookIA32 nCodeHook;
bool isHookActive;

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved ) {
	//char targetProcess[512] = "test.exe";
	//char targetProcess[512] = "ut3.exe";
	//char targetProcess[512] = "TmForever.exe";

	ifstream fName ("C:/Users/Mystic/Documents/vlc-dx9-overlay-tmp/name.txt");
	string exename = "plop";
	getline(fName, exename);
	fName.close();
	exename += ".exe";
	const char * targetProcess = exename.c_str();

	if(dwReason == DLL_PROCESS_ATTACH){
		hDLL = hModule;
		DisableThreadLibraryCalls( hModule );

		string process = getCurrentProcessName();
		if(_strnicmp( targetProcess, process.c_str(), 512) == 0) {
			logIt("Hook started on: %s", process.c_str());
			CreateThread(0, 0, thHook, 0, 0, 0);
			initVLC_Thread();
			isHookActive = true;
		}

	} else if(dwReason == DLL_PROCESS_DETACH){
		string process = getCurrentProcessName();
		if(_strnicmp( targetProcess, process.c_str(), 512) == 0){
			logIt("Hook exiting process: %s", process.c_str());
			isHookActive = false;
			//m_engine.release();
			nCodeHook.removeHook( hkEndScene );
			//unInitialize();
			SENDVLC( KILLTHREAD );
			logIt("Hook successfully unitialized.\n");
		}
	}

	return TRUE;
}





#pragma data_seg (".HookSection")		
HHOOK hHook = NULL;	
#pragma data_seg ()

D3DHOOK_API LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
    return CallNextHookEx( hHook, nCode, wParam, lParam); 
}

D3DHOOK_API void InstallHook()
{
    hHook = SetWindowsHookEx( WH_CBT, HookProc, hDLL, 0 ); 
}

D3DHOOK_API void RemoveHook()
{
    if( !UnhookWindowsHookEx( hHook ) )
		logIt("Problem during unhooking all windows.");
}







DWORD WINAPI thHook( LPVOID ){
	DWORD VTable[1] = {0};

	while( GetModuleHandle("d3d9.dll") == NULL )
		Sleep( 250 );

	DX_Init( VTable );
	HOOK( EndScene, VTable[0] );

	//Initialize();

	return 0;
}

LRESULT CALLBACK MsgProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam ){
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
} 


void DX_Init( DWORD* table ){
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "DX", NULL};
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindow( "DX", NULL, WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	LPDIRECT3D9 pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	logIt( "DirectX hooked [ Direct3DCreate9: 0x%X ] - [ SDKVersion: 0x%X ]", pD3D, D3D_SDK_VERSION );

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	LPDIRECT3DDEVICE9 pd3dDevice;
	pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice);
	DWORD* pVTable = (DWORD*)pd3dDevice;
	logIt( "DirectX device hooked [0x%X]", pVTable );
	pVTable = (DWORD*)pVTable[0];

	table[0] = pVTable[42];		// EndScene

	DestroyWindow(hWnd);
}


HRESULT WINAPI hkEndScene( LPDIRECT3DDEVICE9 pDevice )
{	
	if( isHookActive ) nEndScene(pDevice);
	return oEndScene(pDevice);
}
