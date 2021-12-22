#pragma once
#include "GameEntity.h"
#include "Config.h"

class TileMap;
class Player;
class PlayInStageScene : public GameEntity
{
private:
	TileMap* tileMap = nullptr;
	TILE_INFO tileInfo[SAMPLE_IMAGE_COUNT][TILE_COUNT_Y][TILE_COUNT_X] = { 0 };

	Player* jumpTest = nullptr;

	bool canMove = true;
	POINTFLOAT cameraRenderPos = {};
	float cameraSpeed = 0.0f;
	float glanceSpeed = 0.0f;
	float stayKeyDownTime = 0.0f;

	bool jumpKeyPressed = false;

	void cameraMove();
	
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~PlayInStageScene() = default;

	virtual void PhysicsUpdate() override;

};

