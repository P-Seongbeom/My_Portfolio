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

    testImg = ImageManager::GetSingleton()->AddImage("Image/asdhaetfg.bmp", 1316, 751, false, RGB(255, 0, 255));

	return S_OK;
}

void PlayInStageScene::Update()
{
	jumpTest->Update();
}

void PlayInStageScene::Render(HDC hdc)
{
    testImg->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
    tileMap->Render(hdc);
	jumpTest->Render(hdc);
}

void PlayInStageScene::Release()
{
    SAFE_RELEASE(tileMap);
	SAFE_RELEASE(jumpTest);
}

//void PlayInStageScene::LoadMap()
//{
//    int loadNum;
//    cout << "불러올 맵 번호 입력" << endl;
//    cin >> loadNum;
//
//    string loadFileName = "Save/saveMapData_" + to_string(loadNum);
//    loadFileName += ".map";
//
//    HANDLE hFile = CreateFile(loadFileName.c_str(),
//        GENERIC_READ,
//        0, NULL,
//        OPEN_EXISTING,
//        FILE_ATTRIBUTE_NORMAL,
//        NULL);
//
//    DWORD readByte;
//    if (ReadFile(hFile, tileInfo, sizeof(tileInfo), &readByte, NULL) == false)
//    {
//        MessageBox(g_hWnd, "맵 데이터 불러오기 실패", "에러", MB_OK);
//    }
//
//    CloseHandle(hFile);
//}
