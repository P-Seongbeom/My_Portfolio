#include "PlayInStageScene.h"
#include "Player.h"
#include "Config.h"
#include "CommonFunction.h"
#include "Image.h"
#include "TileMap.h"


HRESULT PlayInStageScene::Init()
{
    SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X * 1.5, WIN_SIZE_Y * 1.5);
    windowSizeX = WIN_SIZE_X;
    windowSizeY = WIN_SIZE_Y;

    tileMap = new TileMap;
    tileMap->Init();

	jumpTest = new Player;
	jumpTest->Init();

	return S_OK;
}

void PlayInStageScene::Update()
{
	jumpTest->Update();
}

void PlayInStageScene::Render(HDC hdc)
{
    tileMap->BackGroundRender(hdc);
	jumpTest->Render(hdc);
    tileMap->FrontStructureRender(hdc);
}

void PlayInStageScene::Release()
{
    SAFE_RELEASE(tileMap);
	SAFE_RELEASE(jumpTest);
}
