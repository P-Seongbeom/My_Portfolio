#include "TileMapToolScene.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT TileMapToolScene::Init()
{
    SetWindowSize(20, 20, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);

    sampleImage = ImageManager::GetSingleton()->AddImage("Image/maptiles.bmp", 960, 608, 30, 19, true, RGB(255, 0, 255));
    //960, 608, 30, 19, true, RGB(255, 0, 255)
    if (sampleImage == nullptr)
    {
        cout << "로드 실패~" << endl;
        return E_FAIL;
    }

    for (int i = 0; i < TILE_COUNT_Y; ++i)
    {
        for (int j = 0; j < TILE_COUNT_X; ++j)
        {
            SetRect(&(tileInfo[i][j].rc), TILE_SIZE * j, TILE_SIZE * i, TILE_SIZE + TILE_SIZE * j, TILE_SIZE + TILE_SIZE * i);

            tileInfo[i][j].frameX = 3;
            tileInfo[i][j].frameY = 0;

            tileInfo[i][j].terrain = Terrain::Grass;
        }
    }

    for (int i = 0; i < SAMPLE_TILE_COUNT_Y; ++i)
    {
        for (int j = 0; j < SAMPLE_TILE_COUNT_X; ++j)
        {
            SetRect(&(sampleTileInfo[i][j].rc),
                TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE, TILE_SIZE * i,
                TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE + TILE_SIZE, TILE_SIZE + TILE_SIZE * i);

            sampleTileInfo[i][j].frameX = j;
            sampleTileInfo[i][j].frameY = i;
        }
    }
    
    selectedSampleTile.frameX = 0;
    selectedSampleTile.frameY = 0;

    selectedTileCountX = 1;
    selectedTileCountY = 1;

    return S_OK;
}

void TileMapToolScene::Update()
{
    RECT sampleArea;
    sampleArea.left = TILEMAPTOOL_SIZE_X - sampleImage->GetWidth();
    sampleArea.right = TILEMAPTOOL_SIZE_X;
    sampleArea.top = 0;
    sampleArea.bottom = sampleImage->GetHeight();

    if (PtInRect(&sampleArea, g_ptMouse))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            posX = g_ptMouse.x - sampleArea.left;
            selectedIdX = posX / TILE_SIZE;

            posY = g_ptMouse.y - sampleArea.top;
            selectedIdY = posY / TILE_SIZE;
        }
        if (KeyManager::GetSingleton()->IsOnceKeyUP(VK_LBUTTON))
        {
            for (int i = 0; i < selectedTileCountX; ++i)
            {
                selectedSampleTile.frameX = sampleTileInfo[selectedIdY - i][selectedIdX].frameX;
            }
            for (int i = 0; i < selectedTileCountY; ++i)
            {
                selectedSampleTile.frameY = sampleTileInfo[selectedIdY][selectedIdX - i].frameY;
            }
        }
    }

    for (int i = 0; i < TILE_COUNT_Y; ++i)
    {
        for(int j = 0; j < TILE_COUNT_X; ++j)
        if (PtInRect(&(tileInfo[i][j].rc), g_ptMouse))
        {
            if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
            {
                tileInfo[i][j].frameX = selectedSampleTile.frameX;
                tileInfo[i][j].frameY = selectedSampleTile.frameY;
                break;
            }
        }
    }
}

void TileMapToolScene::Render(HDC hdc)
{
    for (int i = 0; i < TILE_COUNT_Y; ++i)
    {
        for (int j = 0; j < TILE_COUNT_X; ++j)
        {
            sampleImage->Render(hdc,
                tileInfo[i][j].rc.left + TILE_SIZE / 2,
                tileInfo[i][j].rc.top + TILE_SIZE / 2,
                tileInfo[i][j].frameX,
                tileInfo[i][j].frameY);
        }
    }

    sampleImage->Render(hdc, TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetWidth() / 2, sampleImage->GetHeight() / 2);

    for (int i = 0; i < selectedTileCountX; i++)
    {
        sampleImage->Render(hdc, TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetFrameWidth() / 2 - (sampleImage->GetFrameWidth() * i),
            sampleImage->GetHeight() + sampleImage->GetFrameHeight() / 2 + 180,
            selectedSampleTile.frameX - i, selectedSampleTile.frameY, 1.0f);
    }
    for (int i = 0; i < selectedTileCountY; i++)
    {
        sampleImage->Render(hdc, TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetFrameWidth() / 2,
            sampleImage->GetHeight() + sampleImage->GetFrameHeight() / 2 - (sampleImage->GetFrameHeight() * i) + 180,
            selectedSampleTile.frameX, selectedSampleTile.frameY - i, 1.0f);
    }
}

void TileMapToolScene::Release()
{
}
