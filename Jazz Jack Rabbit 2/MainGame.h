#pragma once
#include "Config.h"
#include "GameEntity.h"

class Image;
class MainGame : public GameEntity
{
private:
	HANDLE hTimer;

	char text[128];

	int mousePosX = 0;
	int mousePosY = 0;
	int clickedMousePosX = 0;
	int clickedMousePosY = 0;

	Image* backBuffer = nullptr;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	virtual ~MainGame() = default;

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

