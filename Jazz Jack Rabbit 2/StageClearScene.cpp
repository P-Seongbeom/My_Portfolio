#include "StageClearScene.h"
#include "Image.h"

HRESULT StageClearScene::Init()
{
	stageClearScene = ImageManager::GetSingleton()->FindImage("Image/scene/stage_clear.bmp");
	background = ImageManager::GetSingleton()->FindImage("Image/scene/background_black.bmp");

	renderPos = GameData::GetSingleton()->GetPlayerRenderPos();


	return S_OK;
}

void StageClearScene::Update()
{
	frameTimer += Timer::GetDeltaTime();

	if (frameTimer > 0.1)
	{
		++renderFrameX;
		frameTimer = 0;
	}

	if (renderFrameX > 1)
	{
		renderFrameX = 0;
		++renderFrameY;
	}

	if (renderFrameY > 11)
	{
		SceneManager::GetSingleton()->ChangeScene("TiltleScene");
	}

	stageClearScene->SetCurrFrameX(renderFrameX);
	stageClearScene->SetCurrFrameY(renderFrameY);
}

void StageClearScene::Render(HDC hdc)
{
	background->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	stageClearScene->Render(hdc, (int)renderPos.x, (int)renderPos.y,
							stageClearScene->GetCurrFrameX(),
							stageClearScene->GetCurrFrameY());
}

void StageClearScene::Release()
{
}
