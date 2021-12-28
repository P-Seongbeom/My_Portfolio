#include "TiltleScene.h"
#include "Image.h"


HRESULT TiltleScene::Init()
{
    titleImage = ImageManager::GetSingleton()->FindImage("Image/title/title_x-mas.bmp");
    guideWord = ImageManager::GetSingleton()->FindImage("Image/title/press_space.bmp");

    return S_OK;
}

void TiltleScene::Update()
{
    if (Input::GetButtonDown(VK_SPACE))
    {
        SceneManager::GetSingleton()->ChangeScene("PlayInStage");
    }
}

void TiltleScene::Render(HDC hdc)
{
    titleImage->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
    guideWord->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y - 40);
}

void TiltleScene::Release()
{
}
