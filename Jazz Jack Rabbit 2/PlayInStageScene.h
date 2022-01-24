#pragma once
#include "GameEntity.h"
#include "Config.h"

class PixelCollider;
class TileMap;
class Player;
class Turtle;
class Image;
class PlayInStageScene : public GameEntity
{
private:
	PixelCollider* collider = nullptr;

	TileMap* tileMap = nullptr;
	TILE_INFO tileInfo[SAMPLE_IMAGE_COUNT][TILE_COUNT_Y][TILE_COUNT_X] = { 0 };

	Player* player = nullptr;
	Turtle* turtle = nullptr;

	RECT* cameraMoveXZone = {};
	RECT* cameraMoveYZone = {};

	bool canMove = true;
	POINTFLOAT cameraRenderPos = {};
	float cameraSpeed = 0.0f;
	float glanceSpeed = 0.0f;
	float stayKeyDownTime = 0.0f;

	bool freeCameraMoveZone(RECT* zone, POINTFLOAT ptf);
	void moveCamera();
	bool moveHorizontal = true;
	bool moveVertical = true;

	//void returnCamera();
	//bool activateReturnCamera = false;

	void collision(HDC hdc, int checkPosX, int checkPosY, COLORREF color);
	bool collidedLeft = false;
	bool collidedRight = false;
	bool collidedTopL = false;
	bool collidedTopR = false;
	bool collidedBottomL = false;
	bool collidedBottomR = false;
	bool collidedBottomC = false;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~PlayInStageScene() = default;

	virtual void PhysicsUpdate() override;

};

