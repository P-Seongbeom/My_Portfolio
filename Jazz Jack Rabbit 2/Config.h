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

//#pragma comment(lib, "winmm.lib")

#define WIN_START_POS_X 400
#define WIN_START_POS_Y 100
#define WIN_SIZE_X	640
#define WIN_SIZE_Y	480
#define TILEMAPTOOL_SIZE_X 1600
#define TILEMAPTOOL_SIZE_Y 900

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

typedef struct ArgumentFuncPtr
{
	string sceneName;
	string loadingSceneName;
} ARGUMENT_PTR, * LPARGUMENT_PTR;

#include "ImageManager.h"
#include "SceneManager.h"
#include "KeyManager.h"

extern HWND _hWnd;
extern HINSTANCE _hInst;
extern POINT g_ptMouse;

extern int windowSizeX;
extern int windowSizeY;

//타일맵 관련
#define TILE_SIZE	32
#define TILE_COUNT_X	20
#define TILE_COUNT_Y	15
#define SAMPLE_TILE_COUNT_X		25
#define SAMPLE_TILE_COUNT_Y		15
#define SAMPLE_IMAGE_COUNT		6

typedef struct tagTile
{
	//Terrain terrain;
	RECT rc;
	int frameX, frameY;
}TILE_INFO;

//플레이어 관련
enum class Echaracter { jazz, spaz, Lori };
enum class EplayerState { Stand, Walk, Run, Jump, Rope };
//enum class moveDir {Left, Right, Up, Down};

struct RABBIT
{
	Echaracter character;
	EplayerState state;
	RECT rc;
	int frameX, frameY;
};