#pragma once
#include "Config.h"
#include "GameObject.h"

class PixelCollider
{
private:
	COLORREF pointCheckRGB = {};
	WORD r = {};
	WORD g = {};
	WORD b = {};

	bool collidedLeft = false;
	bool collidedRight = false;
	bool collidedUpLeft = false;
	bool collidedUpRight = false;
	bool collidedDownLeft = false;
	bool collidedDownCenter = false;
	bool collidedDownRight = false;

	bool checkPixel(HDC hdc, int pointX, int pointY, COLORREF color);
public:
	void PixelCollision(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color);
	void CollideLeft(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color);
	void CollideRight(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color);
	void CollideUpLeft(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color);
	void CollideUpRight(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color);
	void CollideDownLeft(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color);
	void CollideDownCenter(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color);
	void CollideDownRight(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color);
	void GoUpStairs(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color);
};

