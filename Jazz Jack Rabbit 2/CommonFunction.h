#pragma once

#include <Windows.h>


inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// ���ϴ� ������ �۾����� ����
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX;	rc.bottom = sizeY;

	SetWindowPos(_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
}