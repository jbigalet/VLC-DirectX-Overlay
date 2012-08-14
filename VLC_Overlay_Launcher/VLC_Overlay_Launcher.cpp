#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <TCHAR.h>
#include <fstream>
#include "..\VLC_Overlay\dllmain.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::string exename = argv[0];
	size_t f = exename.rfind("\\");
	exename = exename.substr(f+1, exename.size()-f-6);

	std::cout << "Exe Name: " << exename << std::endl;

	ofstream file;
	file.open("C:/Users/Mystic/Documents/vlc-dx9-overlay-tmp/name.txt");
	file << exename;
	file.close();

	std::cout << "Hooking Direct3D... " << exename;

	InstallHook();
	
	std::cout<< "Done."<< std::endl
		<< "Press enter to unhook and exit."<< std::endl;
	std::cin.ignore();
	
	RemoveHook();

	return 0;
}