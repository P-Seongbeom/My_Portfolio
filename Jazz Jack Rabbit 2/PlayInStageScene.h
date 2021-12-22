#pragma once
#include "GameEntity.h"
#include "Config.h"

class TileMap;
class Player;
class Image;
class PlayInStageScene : public GameEntity
{
private:
	TileMap* tileMap = nullptr;

	Player* jumpTest = nullptr;

	Image* testImg;

	TILE_INFO tileInfo[SAMPLE_IMAGE_COUNT][TILE_COUNT_Y][TILE_COUNT_X] = { 0 };

	//void LoadMap();
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~PlayInStageScene() = default;

};

