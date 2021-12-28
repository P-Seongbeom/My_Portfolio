#include "TileMapToolScene.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT TileMapToolScene::Init()
{
    SetWindowSize(20, 20, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);
    windowSizeX = TILEMAPTOOL_SIZE_X;
    windowSizeY = TILEMAPTOOL_SIZE_Y;
    
    sampleImage[0] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage1.bmp");
    sampleImage[1] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage2.bmp");
    sampleImage[2] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage3.bmp");
    sampleImage[3] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage4.bmp");
    sampleImage[4] = ImageManager::GetSingleton()->FindImage("Image/tilemap/CollisionPixel.bmp");
    sampleImage[5] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage5.bmp");
    sampleImage[6] = ImageManager::GetSingleton()->FindImage("Image/tilemap/TileMapImage6.bmp");
    
    if (sampleImage == nullptr)
    {
        return E_FAIL;
    }

    for (int idx = 0; idx < SAMPLE_IMAGE_COUNT; ++idx)
    {
        for (int i = 0; i < TILE_COUNT_Y; ++i)
        {
            for (int j = 0; j < TILE_COUNT_X; ++j)
            {
                SetRect(&(tileInfo[idx][i][j].rc), TILE_SIZE * j, TILE_SIZE * i, TILE_SIZE + TILE_SIZE * j, TILE_SIZE + TILE_SIZE * i);

                tileInfo[idx][i][j].frameX = 0;
                tileInfo[idx][i][j].frameY = 0;
            }
        }
    }

    for (int idx = 0; idx < SAMPLE_IMAGE_COUNT; ++idx)
    {
        for (int i = 0; i < SAMPLE_TILE_COUNT_Y; ++i)
        {
            for (int j = 0; j < SAMPLE_TILE_COUNT_X; ++j)
            {
                SetRect(&(sampleTileInfo[i][j].rc),
                    TILEMAPTOOL_SIZE_X - sampleImage[idx]->GetWidth() + j * TILE_SIZE, TILE_SIZE * i,
                    TILEMAPTOOL_SIZE_X - sampleImage[idx]->GetWidth() + j * TILE_SIZE + TILE_SIZE, TILE_SIZE + TILE_SIZE * i);

                sampleTileInfo[i][j].frameX = j;
                sampleTileInfo[i][j].frameY = i;
            }
        }
    }
    
    selectedSampleTile.frameX = 0;
    selectedSampleTile.frameY = 0;

    return S_OK;
}

void TileMapToolScene::Update()
{
    RECT sampleArea[SAMPLE_IMAGE_COUNT];
    
    for (int i = 0; i < SAMPLE_IMAGE_COUNT; ++i)
    {
        sampleArea[i].left = TILEMAPTOOL_SIZE_X - sampleImage[i]->GetWidth();
        sampleArea[i].right = TILEMAPTOOL_SIZE_X;
        sampleArea[i].top = 0;
        sampleArea[i].bottom = sampleImage[i]->GetHeight();
    }

    if (Input::GetButtonDown(VK_F1))
    {
        sampleAreaIdx = 0;
    }
    else if (Input::GetButtonDown(VK_F2))
    {
        sampleAreaIdx = 1;
    }
    else if (Input::GetButtonDown(VK_F3))
    {
        sampleAreaIdx = 2;
    }
    else if (Input::GetButtonDown(VK_F4))
    {
        sampleAreaIdx = 3;
    }
    else if (Input::GetButtonDown(VK_F5))
    {
        sampleAreaIdx = 4;
    }
    else if (Input::GetButtonDown(VK_F6))
    {
        sampleAreaIdx = 5;
    }
    else if (Input::GetButtonDown(VK_F7))
    {
        sampleAreaIdx = 6;
    }

    //드래그로 원하는 만큼 타일 선택
    if (PtInRect(&sampleArea[sampleAreaIdx], Input::GetMousePosition()))
    {
        if (Input::GetButtonDown(VK_LBUTTON))
        {
            selectedTileCountX = 1;
            selectedTileCountY = 1;

            posX = Input::GetMousePosition().x - sampleArea[sampleAreaIdx].left;
            selectedIdX = posX / TILE_SIZE;

            posY = Input::GetMousePosition().y - sampleArea[sampleAreaIdx].top;
            selectedIdY = posY / TILE_SIZE;
        }
        if (Input::GetButtonUp(VK_LBUTTON))
        {
            posX2 = Input::GetMousePosition().x - sampleArea[sampleAreaIdx].left;
            selectedIdX2 = posX2 / TILE_SIZE;

            posY2 = Input::GetMousePosition().y - sampleArea[sampleAreaIdx].top;
            selectedIdY2 = posY2 / TILE_SIZE;


            selectedTileCountX += (selectedIdX2 - selectedIdX);
            selectedTileCountY += (selectedIdY2 - selectedIdY);

            if (selectedTileCountX <= 0)
            {
                selectedTileCountX = selectedIdX2 - selectedIdX;
                selectedTileCountX *= -1;
                ++selectedTileCountX;
                selectedSampleTile.frameX = sampleTileInfo[selectedIdY][selectedIdX].frameX;
            }
            else
            {
                selectedSampleTile.frameX = sampleTileInfo[selectedIdY2][selectedIdX2].frameX;
            }

            if (selectedTileCountY <= 0)
            {
                selectedTileCountY = selectedIdY2 - selectedIdY;
                selectedTileCountY *= -1;
                ++selectedTileCountY;
                selectedSampleTile.frameY = sampleTileInfo[selectedIdY][selectedIdX].frameY;
            }
            else
            {
                selectedSampleTile.frameY = sampleTileInfo[selectedIdY2][selectedIdX2].frameY;
            }
            
        }
    }

    //칠하기
    for (int i = 0; i < TILE_COUNT_Y; ++i)
    {
        for (int j = 0; j < TILE_COUNT_X; ++j)
        {
            if (PtInRect(&(tileInfo[sampleAreaIdx][i][j].rc), Input::GetMousePosition()))
            {
                if (Input::GetButton(VK_LBUTTON))
                {
                    for (int x = 0; x < selectedTileCountX; ++x)
                    {
                        for (int y = 0; y < selectedTileCountY; ++y)
                        {
                            if (!(j - x < 0) && !(i - y < 0))
                            {
                                tileInfo[sampleAreaIdx][i - y][j - x].frameX = selectedSampleTile.frameX - x;
                                tileInfo[sampleAreaIdx][i - y][j - x].frameY = selectedSampleTile.frameY - y;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    if (Input::GetButtonDown('O'))
    {
        SaveMap();
    }
    if (Input::GetButtonDown('P'))
    {
        LoadMap();
    }

}

void TileMapToolScene::Render(HDC hdc)
{
    //타일맵툴
    for (int i = 0; i < TILE_COUNT_Y; ++i)
    {
        for (int j = 0; j < TILE_COUNT_X; ++j)
        {
            sampleImage[sampleAreaIdx]->Render(hdc,
                tileInfo[sampleAreaIdx][i][j].rc.left + TILE_SIZE / 2,
                tileInfo[sampleAreaIdx][i][j].rc.top + TILE_SIZE,
                tileInfo[sampleAreaIdx][i][j].frameX,
                tileInfo[sampleAreaIdx][i][j].frameY);
        }
    }

    //우측 샘플 이미지
    sampleImage[sampleAreaIdx]->Render(hdc, 
        TILEMAPTOOL_SIZE_X - sampleImage[sampleAreaIdx]->GetWidth() + sampleImage[sampleAreaIdx]->GetWidth() / 2,
        sampleImage[sampleAreaIdx]->GetHeight() / 2);

    //선택된 샘플 이미지
    for (int j = 0; j < selectedTileCountY; ++j)
    {
        for (int i = 0; i < selectedTileCountX; ++i)
        {
            sampleImage[sampleAreaIdx]->Render(hdc,
                TILEMAPTOOL_SIZE_X  - sampleImage[sampleAreaIdx]->GetFrameWidth()/2 - (sampleImage[sampleAreaIdx]->GetFrameWidth() * i),
                sampleImage[sampleAreaIdx]->GetHeight() + sampleImage[sampleAreaIdx]->GetFrameHeight() / 2 - (sampleImage[sampleAreaIdx]->GetFrameHeight() * j) + 200,
                selectedSampleTile.frameX - i, 
                selectedSampleTile.frameY - j, 1.0f);
        }

    }

}

void TileMapToolScene::Release()
{
}

void TileMapToolScene::SaveMap()
{
    int saveNum;
    cout << "저장할 맵 번호 입력" << endl;
    cin >> saveNum;

    string saveFileName = "Save/saveMapData_" + to_string(saveNum);
    saveFileName += ".map";

    HANDLE hFile = CreateFile(saveFileName.c_str(),
        GENERIC_WRITE,
        0, NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    DWORD writtenByte;
    if (WriteFile(hFile, tileInfo, sizeof(tileInfo), &writtenByte, NULL) == false)
    {
        MessageBox(_hWnd, "맵 데이터 저장 실패", "에러", MB_OK);
    }

    MessageBox(_hWnd, saveFileName.c_str() , "저장 완료", MB_OK);

    CloseHandle(hFile);
}

void TileMapToolScene::LoadMap()
{
    int loadNum;
    cout << "불러올 맵 번호 입력" << endl;
    cin >> loadNum;

    string loadFileName = "Save/saveMapData_" + to_string(loadNum);
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
