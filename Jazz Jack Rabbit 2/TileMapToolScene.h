#pragma once
#include "Config.h"
#include "GameEntity.h"

typedef struct tagSampleTile
{
	RECT rc;
	int frameX, frameY;
}SAMPLE_TILE_INFO;

class Image;
class TileMapToolScene : public GameEntity
{
private:
	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TILE_COUNT_Y][SAMPLE_TILE_COUNT_X] = {};
	TILE_INFO tileInfo[SAMPLE_IMAGE_COUNT][TILE_COUNT_Y][TILE_COUNT_X] = {};

	Image* sampleImage[SAMPLE_IMAGE_COUNT] = {};

	int posX = 0;
	int	posY = 0;
	int posX2 = 0;
	int posY2 = 0;
	int selectedIdX = 0;
	int	selectedIdY = 0;
	int selectedIdX2 = 0;
	int selectedIdY2 = 0;
	int selectedTileCountX = 0;
	int selectedTileCountY = 0;
	int sampleAreaIdx = 0;

	SAMPLE_TILE_INFO	selectedSampleTile;

	//RECT sampleArea[SAMPLE_IMAGE_COUNT];

public:
	virtual ~TileMapToolScene() = default;
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void SaveMap();
	void LoadMap();
};