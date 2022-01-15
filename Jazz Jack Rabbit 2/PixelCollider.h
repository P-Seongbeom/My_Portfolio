#pragma once
#include "Config.h"

class PixelCollider
{
private:
	bool collidedLeft = false;
	bool collidedRight = false;
	bool collidedUpLeft = false;
	bool collidedUpRight = false;
	bool collidedDownLeft = false;
	bool collidedDownCenter = false;
	bool collidedDownRight = false;

public:
	void PixelCollision(HDC hdc, int checkPosX, int checkPosY, COLORREF color);
	void CollideLeft(HDC hdc, int checkPosX, int checkPosY, int bodySizeX, int bodySizeY, COLORREF color);
	void CollideRight(HDC hdc, int checkPosX, int checkPosY, COLORREF color);
	void CollideUpLeft(HDC hdc, int checkPosX, int checkPosY, COLORREF color);
	void CollideUpRight(HDC hdc, int checkPosX, int checkPosY, COLORREF color);
	void CollideDownLeft(HDC hdc, int checkPosX, int checkPosY, COLORREF color);
	void CollideDownCenter(HDC hdc, int checkPosX, int checkPosY, COLORREF color);
	void CollideDownRight(HDC hdc, int checkPosX, int checkPosY, COLORREF color);
};

