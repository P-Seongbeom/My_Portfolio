#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>

#include "Input.h"
#include "Timer.h"

using namespace std;

#define WIN_START_POS_X 400
#define WIN_START_POS_Y 100
#define WIN_SIZE_X	640
#define WIN_SIZE_Y	480
#define TILEMAPTOOL_SIZE_X 1600
#define TILEMAPTOOL_SIZE_Y 1000

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

typedef struct ArgumentFuncPtr
{
	string sceneName;
	string loadingSceneName;
} ARGUMENT_PTR, * LPARGUMENT_PTR;

#include "ImageManager.h"
#include "SceneManager.h"

extern HWND _hWnd;
extern HINSTANCE _hInst;
//extern POINT g_ptMouse;

extern int windowSizeX;
extern int windowSizeY;

//Å¸ÀÏ¸Ê °ü·Ã
#define TILE_SIZE	32
#define TILE_COUNT_X	40
#define TILE_COUNT_Y	30
#define SAMPLE_TILE_COUNT_X		10
#define SAMPLE_TILE_COUNT_Y		30
#define SAMPLE_IMAGE_COUNT		7

typedef struct tagTile
{
	//Terrain terrain;
	RECT rc;
	int frameX, frameY;
}TILE_INFO;

//ÃÑ¾Ë °ü·Ã
#define AMMO_PACK_COUNT		10
#define AMMO_SPEED			640