#include "TileMap.h"
#include "Image.h"
//#include "TileMapToolScene.h"


HRESULT TileMap::Init()
{
    mapTile[0] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage1.bmp");
    mapTile[1] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage2.bmp");
    mapTile[2] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage3.bmp");
    mapTile[3] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage4.bmp");
    mapTile[4] = ImageManager::GetSingleton()->FindImage("Image/tilemap/CollisionPixel.bmp");
    mapTile[5] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage5.bmp");
    mapTile[6] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage6.bmp");

    pixelImage = ImageManager::GetSingleton()->FindImage("Image/tilemap/pixelMap1.bmp");

    LoadMapFile(1);

    return S_OK;
}

void TileMap::Update()
{
    if (Input::GetButtonDown('0') && renderOnOff == false)
    {
        renderOnOff = true;
    }
    else if (Input::GetButtonDown('0') && renderOnOff == true)
    {
        renderOnOff = false;
    }
        
}

void TileMap::Render(HDC hdc)
{
}

void TileMap::Release()
{
}

void TileMap::BackGroundRender(HDC hdc, float cameraX, float cameraY)
{
    adjustRenderRatio(hdc, 0, cameraX, cameraY, 0);
    adjustRenderRatio(hdc, 1, cameraX, cameraY, 0.5);
    adjustRenderRatio(hdc, 2, cameraX, cameraY, 0.8);
    adjustRenderRatio(hdc, 3, cameraX, cameraY, 1);

    if (renderOnOff)
    pixelImage->Render(hdc, pixelImage->GetWidth()/2 - cameraX * 32, pixelImage->GetHeight()/2 - cameraY * 32);
}

void TileMap::FrontStructureRender(HDC hdc, float cameraX, float cameraY)
{
    adjustRenderRatio(hdc, 5, cameraX, cameraY, 1);
    adjustRenderRatio(hdc, 6, cameraX, cameraY, 1.5, 1.5);
}

void TileMap::LoadMapFile(int mapNum)
{
    string loadFileName = "Save/saveMapData_" + to_string(mapNum);
    loadFileName += ".map";

    HANDLE hFile = CreateFile(loadFileName.c_str(),
        GENERIC_READ,
        0, NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    DWORD readByte;
    if (ReadFile(hFile, tileInfo, sizeof(tileInfo), &readByte, NULL) == false)
    {
        MessageBox(_hWnd, "맵 데이터 불러오기 실패", "에러", MB_OK);
    }

    CloseHandle(hFile);
}

void TileMap::adjustRenderRatio(HDC hdc, int renderIdx, float cameraX, float cameraY, float ratio, float scale)
{
    for (int i = cameraY * ratio; i < RENDER_TILE_COUNT_Y + cameraY * ratio; ++i)
    {
        for (int j = cameraX * ratio; j < RENDER_TILE_COUNT_X + cameraX * ratio; ++j)
        {
            mapTile[renderIdx]->Render(hdc,
                tileInfo[renderIdx][i][j].rc.left + TILE_SIZE / 2 - cameraX * TILE_SIZE * ratio,
                tileInfo[renderIdx][i][j].rc.top + TILE_SIZE - cameraY * TILE_SIZE * ratio,
                tileInfo[renderIdx][i][j].frameX,
                tileInfo[renderIdx][i][j].frameY,
                scale);
        }
    }
}
