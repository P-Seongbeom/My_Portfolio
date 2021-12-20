#include "TileMap.h"
#include "Image.h"
//#include "TileMapToolScene.h"


HRESULT TileMap::Init()
{
    mapTile[0] = ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage1.bmp", 320, 192, 10, 6, true, RGB(255, 0, 255));
    mapTile[1] = ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage2.bmp", 160, 160, 5, 5, true, RGB(255, 0, 255));
    mapTile[2] = ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage3.bmp", 160, 160, 5, 5, true, RGB(255, 0, 255));
    mapTile[3] = ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage4.bmp", 800, 480, 25, 15, true, RGB(255, 0, 255));
    mapTile[4] = ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage5.bmp", 290, 320, 9, 10, true, RGB(255, 0, 255));
    mapTile[5] = ImageManager::GetSingleton()->AddImage("Image/tilemap/TileMapImage6.bmp", 320, 224, 10, 7, true, RGB(255, 0, 255));

    LoadMapFile(1);

    //for (int idx = 0; idx < SAMPLE_IMAGE_COUNT; ++idx)
    //{
    //    for (int i = 0; i < TILE_COUNT_Y; ++i)
    //    {
    //        for (int j = 0; j < TILE_COUNT_X; ++j)
    //        {
    //            tileInfo[idx][i][j] = 
    //        }
    //    }
    //}

    return S_OK;
}

void TileMap::Update()
{
}

void TileMap::Render(HDC hdc)
{
    for (int idx = 0; idx < SAMPLE_IMAGE_COUNT; ++idx)
    {
        for (int i = 0; i < TILE_COUNT_Y; ++i)
        {
            for (int j = 0; j < TILE_COUNT_X; ++j)
            {
                mapTile[idx]->Render(hdc,
                    tileInfo[idx][i][j].rc.left + TILE_SIZE / 2,
                    tileInfo[idx][i][j].rc.top + TILE_SIZE / 2,
                    tileInfo[idx][i][j].frameX,
                    tileInfo[idx][i][j].frameY);
            }
        }
    }
}

void TileMap::Release()
{
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
        MessageBox(g_hWnd, "맵 데이터 불러오기 실패", "에러", MB_OK);
    }

    CloseHandle(hFile);
}