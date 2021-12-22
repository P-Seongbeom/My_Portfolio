#pragma once

#include <Windows.h>


inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 원하는 윈도우 작업영역 설정
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX;	rc.bottom = sizeY;

	// 스타일이 포함된 실제 윈도우 크기 계산
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 계산된 값으로 윈도우를 이동시키면서 크기도 함께 변환
	MoveWindow(_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, true);
}