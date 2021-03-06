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
#include "GameData.h"

extern HWND _hWnd;
extern HINSTANCE _hInst;

extern int windowSizeX;
extern int windowSizeY;

//타일맵 관련
#define TILE_SIZE	32
#define TILE_COUNT_X	40
#define TILE_COUNT_Y	30
#define SAMPLE_TILE_COUNT_X		10
#define SAMPLE_TILE_COUNT_Y		30
#define SAMPLE_IMAGE_COUNT		7
#define RENDER_TILE_COUNT_X		20
#define RENDER_TILE_COUNT_Y		15

typedef struct tagTile
{
	RECT rc;
	int frameX, frameY;
}TILE_INFO;

//이동하는 object 관련
enum class EmoveDir { Left, Right, Up, Down };
#define GRAVITY				1000.0f
#define FALLING_MAX_SPEED	500.0f

//플레이어 관련
#define PLAYER_POS_X		WIN_SIZE_X * 0.5f
#define PLAYER_POS_Y		WIN_SIZE_Y * 0.5f
#define PLAYER_MAX_SPEED	200.0f
#define PLAYER_ACCELATE		600.0f
#define JUMP_VELOCITY		500.0f
#define PLAYER_BODYSIZE_X	20
#define PLAYER_BODYSIZE_Y	32
#define QUICK_DOWN_SPEED	450.0f

//총알 관련
#define AMMO_PACK_COUNT		10
#define AMMO_SPEED			640.0f

//거북이 관련
#define TURTLE_POS_X		WIN_SIZE_X * 0.5f
#define TURTLE_POS_Y		WIN_SIZE_Y * 1.5f
#define TURTLE_MOVE_SPEED	100.0f
#define TURTLE_BODYSIZE_X	32
#define TURTLE_BODYSIZE_Y	32

//보스 관련
#define BOSS_POS_X			1166
#define BOSS_POS_Y			720
#define BOSS_DIE_POS_X		1216
#define BOSS_BODYSIZE_X		32
#define BOSS_BODYSIZE_Y		40
#define BRICK_SIZE_X		28
#define BRICK_SIZE_Y		24
