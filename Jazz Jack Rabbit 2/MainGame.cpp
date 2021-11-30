#include "MainGame.h"
#include "Image.h"

HRESULT MainGame::Init()
{
	//srand((unsigned int)time(nullptr));

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// 백버퍼
	backBuffer = new Image;
	//int maxSizeX = WIN_SIZE_X > TILEMAPTOOL_SIZE_X ? WIN_SIZE_X : TILEMAPTOOL_SIZE_X;
	//int maxSizeY = WIN_SIZE_Y > TILEMAPTOOL_SIZE_Y ? WIN_SIZE_Y : TILEMAPTOOL_SIZE_Y;

	backBuffer->Init("Image/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	return S_OK;
}

void MainGame::Update()
{
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	wsprintf(text, "MousePosX : %d", mousePosX);
	TextOut(hBackBufferDC, 200, 10, text, strlen(text));

	wsprintf(text, "MousePosY : %d", mousePosY);
	TextOut(hBackBufferDC, 200, 40, text, strlen(text));

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		clickedMousePosX = LOWORD(lParam);
		clickedMousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
