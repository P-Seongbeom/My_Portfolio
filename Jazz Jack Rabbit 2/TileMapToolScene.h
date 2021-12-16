#pragma once
#include "Config.h"
#include "GameEntity.h"

enum class Terrain { Earth, Wall, Water, Grass, Breakablewall, End };

#define TILE_SIZE	32
#define TILE_COUNT_X	20
#define TILE_COUNT_Y	15
#define SAMPLE_TILE_COUNT_X		25
#define SAMPLE_TILE_COUNT_Y		15
#define SAMPLE_IMAGE_COUNT		6

typedef struct tagSampleTile
{
	RECT rc;
	int frameX, frameY;
}SAMPLE_TILE_INFO;

typedef struct tagTile
{
	Terrain terrain;
	RECT rc;
	int frameX, frameY;
}TILE_INFO;

class Image;
class TileMapToolScene : public GameEntity
{
private:
	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TILE_COUNT_Y][SAMPLE_TILE_COUNT_X];
	TILE_INFO tileInfo[SAMPLE_IMAGE_COUNT][TILE_COUNT_Y][TILE_COUNT_X];

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
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void MapSave();
	void MapLoad();
};