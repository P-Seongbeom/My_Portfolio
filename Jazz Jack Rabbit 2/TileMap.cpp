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

    LoadMapFile(1);

    return S_OK;
}

void TileMap::Update()
{
}

void TileMap::Render(HDC hdc)
{
}

void TileMap::Release()
{
}

void TileMap::BackGroundRender(HDC hdc)
{
    for (int idx = 0; idx < SAMPLE_IMAGE_COUNT - 2; ++idx)
    {
        for (int i = 0; i < TILE_COUNT_Y; ++i)
        {
            for (int j = 0; j < TILE_COUNT_X; ++j)
            {
                if(idx != 4)
                mapTile[idx]->Render(hdc,
                    tileInfo[idx][i][j].rc.left + TILE_SIZE / 2,
                    tileInfo[idx][i][j].rc.top + TILE_SIZE,
                    tileInfo[idx][i][j].frameX,
                    tileInfo[idx][i][j].frameY);
                if (Input::GetButton('0'))
                {
                    mapTile[4]->Render(hdc,
                        tileInfo[4][i][j].rc.left + TILE_SIZE / 2,
                        tileInfo[4][i][j].rc.top + TILE_SIZE,
                        tileInfo[4][i][j].frameX,
                        tileInfo[4][i][j].frameY);
                }
            }
        }
    }
}

void TileMap::FrontStructureRender(HDC hdc)
{
    for (int idx = SAMPLE_IMAGE_COUNT - 2; idx < SAMPLE_IMAGE_COUNT; ++idx)
    {
        for (int i = 0; i < TILE_COUNT_Y; ++i)
        {
            for (int j = 0; j < TILE_COUNT_X; ++j)
            {
                mapTile[idx]->Render(hdc,
                    tileInfo[idx][i][j].rc.left + TILE_SIZE / 2,
                    tileInfo[idx][i][j].rc.top + TILE_SIZE,
                    tileInfo[idx][i][j].frameX,
                    tileInfo[idx][i][j].frameY);
            }
        }
    }
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