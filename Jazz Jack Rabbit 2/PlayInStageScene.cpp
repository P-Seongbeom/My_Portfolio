#include "PlayInStageScene.h"
#include "Player.h"
#include "Turtle.h"
#include "QueenEarlong.h"
#include "Config.h"
#include "Image.h"
#include "TileMap.h"
#include "PixelCollider.h"
#include "RectCollider.h"

HRESULT PlayInStageScene::Init()
{
    MapPixelCollider = new PixelCollider;
    rectCollider = new RectCollider;

    tileMap = new TileMap;
    tileMap->Init();

    player = new Player;
    player->Init();

    turtle = new Turtle;
    turtle->Init();

    boss = new QueenEarlong;
    boss->Init();

    cameraMoveXZone = new RECT;
    cameraMoveXZone->left = WIN_SIZE_X / 2.0;
    cameraMoveXZone->right = WIN_SIZE_X * 1.5;
    cameraMoveXZone->top = 0;
    cameraMoveXZone->bottom = WIN_SIZE_Y * 2.0;

    cameraMoveYZone = new RECT;
    cameraMoveYZone->left = 0;
    cameraMoveYZone->right = WIN_SIZE_X * 2.0;
    cameraMoveYZone->top = WIN_SIZE_Y / 2.0;
    cameraMoveYZone->bottom = WIN_SIZE_Y * 1.5;

    cameraRenderPos.x = player->GetPos().x - WIN_SIZE_X / 2;
    cameraRenderPos.y = player->GetPos().y - WIN_SIZE_Y / 2;

    cameraSpeed = PLAYER_MAX_SPEED;
    glanceSpeed = TILE_SIZE * 2;

    return S_OK;
}

void PlayInStageScene::Update()
{
    tileMap->Update();
    player->Update();
    moveCamera();
    turtle->Update();
    boss->Update();
    boss->SetBrickTarget(player);
    turtle->SetRenderPos(turtle->GetPos(), player->GetPos(), cameraMoveXZone, cameraMoveYZone);
    boss->SetRenderPos(boss->GetPos(), player->GetPos(), cameraMoveXZone, cameraMoveYZone);
    if (boss->GetIsDead())
    {
        GameData::GetSingleton()->SavePlayerData(player->GetPlayerLife(), player->GetPos(), player->GetRenderPos());
        SceneManager::GetSingleton()->ChangeScene("StageClearScene");
    }
}

void PlayInStageScene::Render(HDC hdc)
{
    tileMap->BackGroundRender(hdc, cameraRenderPos.x / TILE_SIZE, cameraRenderPos.y / TILE_SIZE);
    turtle->Render(hdc);
    boss->Render(hdc);
    player->Render(hdc);
    tileMap->FrontStructureRender(hdc, cameraRenderPos.x / TILE_SIZE, cameraRenderPos.y / TILE_SIZE);
}

void PlayInStageScene::Release()
{
    SAFE_RELEASE(tileMap);
    SAFE_RELEASE(player);
    SAFE_RELEASE(turtle);
    SAFE_RELEASE(boss);
    SAFE_DELETE(MapPixelCollider);
    SAFE_DELETE(rectCollider);
    SAFE_DELETE(cameraMoveXZone);
    SAFE_DELETE(cameraMoveYZone);
}

void PlayInStageScene::PhysicsUpdate()
{
    MapPixelCollider->PixelCollision(tileMap->GetImageInfo()->GetMemDC(), player, player->GetPos(), 20, 32, RGB(87, 0, 203));
    MapPixelCollider->PixelCollision(tileMap->GetImageInfo()->GetMemDC(), turtle, turtle->GetPos(), 32, 20, RGB(87, 0, 203));
    MapPixelCollider->PixelCollision(tileMap->GetImageInfo()->GetMemDC(), boss, boss->GetPos(), 32, 40, RGB(87, 0, 203));
    player->SetAmmoCollision(tileMap->GetImageInfo()->GetMemDC(), turtle, boss);
    rectCollider->GiveDamageObject1(player, 20, 32, turtle, 32, 20);
    rectCollider->CollideObjects(player, 20, 32, boss, 32, 40);
}

bool PlayInStageScene::freeCameraMoveZone(RECT* zone, POINTFLOAT ptf)
{
    if (zone->left <= ptf.x && zone->right >= ptf.x && zone->top <= ptf.y && zone->bottom >= ptf.y)
    {
        return true;
    }

    return false;
}

void PlayInStageScene::moveCamera()
{
    if (freeCameraMoveZone(cameraMoveXZone, player->GetPos()))
    {
        cameraRenderPos.x = player->GetPos().x - WIN_SIZE_X / 2;
    }

    if (freeCameraMoveZone(cameraMoveYZone, player->GetPos()))
    {
        cameraRenderPos.y = player->GetPos().y - WIN_SIZE_Y / 2;
    }

}
