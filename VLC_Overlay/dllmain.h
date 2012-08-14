#include "stdafx.h"

#pragma once

#define D3DHOOK_API __declspec(dllexport)
D3DHOOK_API void InstallHook();
D3DHOOK_API void RemoveHook();

#define HOOK(func,addr)	o##func = nCodeHook.createHook((t##func)addr, hk##func);


BOOL APIENTRY DllMain( HMODULE, DWORD, LPVOID );
DWORD WINAPI thHook( LPVOID );
LRESULT CALLBACK MsgProc( HWND, UINT, WPARAM, LPARAM);
void DX_Init( DWORD * );

	// EndScene
typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 );
tEndScene oEndScene;
HRESULT WINAPI hkEndScene( LPDIRECT3DDEVICE9 );