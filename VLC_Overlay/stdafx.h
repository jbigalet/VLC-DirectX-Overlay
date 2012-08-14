#pragma once

#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_WARNINGS
// Windows Header Files:

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <fstream>
#include <detours.h>
#include <time.h>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <map>

#include <urlmon.h>
#include <shlwapi.h>

//#include <strsafe.h>

using namespace std;