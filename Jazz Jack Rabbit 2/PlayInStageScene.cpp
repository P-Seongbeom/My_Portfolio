#include "PlayInStageScene.h"
#include "PlayerManager.h"
#include "Config.h"

HRESULT PlayInStageScene::Init()
{
	jumpTest = new PlayerManager;
	jumpTest->Init();

	return S_OK;
}

void PlayInStageScene::Update()
{
	jumpTest->Update();
}

void PlayInStageScene::Render(HDC hdc)
{
	jumpTest->Render(hdc);
}

void PlayInStageScene::Release()
{
	SAFE_RELEASE(jumpTest);
}
