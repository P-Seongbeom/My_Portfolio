#pragma once
#include "GameEntity.h"
#include "Config.h"

class PixelCollider;
class RectCollider;
class TileMap;
class Player;
class Turtle;
class QueenEarlong;
class Image;
class PlayInStageScene : public GameEntity
{
private:
	PixelCollider* MapPixelCollider = nullptr;
	RectCollider* rectCollider = nullptr;

	TileMap* tileMap = nullptr;
	TILE_INFO tileInfo[SAMPLE_IMAGE_COUNT][TILE_COUNT_Y][TILE_COUNT_X] = { 0 };

	Player* player = nullptr;
	Turtle* turtle = nullptr;
	QueenEarlong* boss = nullptr;

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

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual void PhysicsUpdate();

	virtual ~PlayInStageScene() = default;


};

