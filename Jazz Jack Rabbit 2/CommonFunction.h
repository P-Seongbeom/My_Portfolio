#pragma once

#include <Windows.h>


inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// ���ϴ� ������ �۾����� ����
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX;	rc.bottom = sizeY;

	// ��Ÿ���� ���Ե� ���� ������ ũ�� ���
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// ���� ������ �����츦 �̵���Ű�鼭 ũ�⵵ �Բ� ��ȯ
	MoveWindow(_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, true);
}