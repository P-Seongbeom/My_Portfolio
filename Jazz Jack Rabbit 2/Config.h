#pragma once
#include <Windows.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

#define WIN_START_POS_X 400
#define WIN_START_POS_Y 100
#define WIN_SIZE_X	1000
#define WIN_SIZE_Y	800

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }



extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;