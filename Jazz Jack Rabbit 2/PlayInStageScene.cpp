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

    cameraRenderPos.x = jumpTest->GetPos().x - WIN_SIZE_X / 2;
    cameraRenderPos.y = jumpTest->GetPos().y - WIN_SIZE_Y / 2;

    cameraSpeed = PLAYER_MOVE_SPEED;
    glanceSpeed = TILE_SIZE * 2;

	return S_OK;
}

void PlayInStageScene::Update()
{
    cameraMove();
	jumpTest->Update();
    cout << endl;
    cout << cameraRenderPos.x << endl;
    cout << cameraRenderPos.y << endl;
}

void PlayInStageScene::Render(HDC hdc)
{
    tileMap->BackGroundRender(hdc, cameraRenderPos.x / TILE_SIZE, cameraRenderPos.y / TILE_SIZE);
	jumpTest->Render(hdc);
    tileMap->FrontStructureRender(hdc, cameraRenderPos.x / TILE_SIZE, cameraRenderPos.y / TILE_SIZE);
}

void PlayInStageScene::Release()
{
    SAFE_RELEASE(tileMap);
    SAFE_RELEASE(jumpTest);
}

void PlayInStageScene::PhysicsUpdate()
{

}

void PlayInStageScene::cameraMove()
{
    //if (cameraRenderPos.x < 0 || cameraRenderPos.x >((TILE_COUNT_X * TILE_SIZE) - WIN_SIZE_X / 2))
    //{
    //    moveHorizontal = false;
    //    if (cameraRenderPos.x < 0)
    //    {
    //        cameraRenderPos.x = 0;
    //    }
    //    else
    //    {
    //        cameraRenderPos.x = ((TILE_COUNT_X * TILE_SIZE) - WIN_SIZE_X / 2);
    //    }
    //}
    //else
    //{
    //    moveHorizontal = true;
    //}
    //if (cameraRenderPos.y < 0 || cameraRenderPos.y >((TILE_COUNT_Y * TILE_SIZE) - WIN_SIZE_Y / 2))
    //{
    //    moveVertical = false;
    //}
    //else
    //{
    //    moveVertical = true;
    //}

    if (Input::GetButton(VK_LSHIFT))
    {
        cameraSpeed = PLAYER_MOVE_SPEED * 2;
    }
    if (Input::GetButtonUp(VK_LSHIFT))
    {
        cameraSpeed = PLAYER_MOVE_SPEED;
    }

    if (!jumpTest->GetEndOfHorizntal())
    {
        if (Input::GetButton(VK_LEFT))
        {
            cameraRenderPos.x -= cameraSpeed * Timer::GetDeltaTime();
        }
        if (Input::GetButton(VK_RIGHT))
        {
            cameraRenderPos.x += cameraSpeed * Timer::GetDeltaTime();
        }
    }
    if (moveVertical)
    {

    }

    //if (Input::GetButtonDown(VK_DOWN))
    //{
    //    stayKeyDownTime += Timer::GetDeltaTime();

    //    if (stayKeyDownTime > 0.5)
    //    {
    //        cameraRenderPos.y += glanceSpeed * Timer::GetDeltaTime();

    //        if (cameraRenderPos.y > jumpTest->GetPos().y + (TILE_SIZE * 2))
    //        {
    //            cameraRenderPos.y = jumpTest->GetPos().y + (TILE_SIZE * 2);
    //        }
    //    }
    //}
    //else if (Input::GetButtonUp(VK_DOWN))
    //{
    //    cameraRenderPos.y = jumpTest->GetPos().y - WIN_START_POS_Y/2;
    //    stayKeyDownTime = 0;
    //}

    //if (Input::GetButtonDown(VK_UP))
    //{
    //    stayKeyDownTime += Timer::GetDeltaTime();

    //    if (stayKeyDownTime > 0.5)
    //    {
    //        cameraRenderPos.y -= glanceSpeed * Timer::GetDeltaTime();

    //        if (cameraRenderPos.y > jumpTest->GetPos().y + (TILE_SIZE * 2))
    //        {
    //            cameraRenderPos.y = jumpTest->GetPos().y + (TILE_SIZE * 2);
    //        }
    //    }
    //}
    //else if (Input::GetButtonUp(VK_UP))
    //{
    //    cameraRenderPos.y = jumpTest->GetPos().y;
    //    stayKeyDownTime = 0;
    //}

    //if (Input::GetButton(VK_SPACE))
    //{
    //}
}