#pragma once
#include "Config.h"
#include "GameEntity.h"

enum class Terrain { Earth, Wall, Water, Grass, Breakablewall, End };

#define TILE_SIZE	32
#define TILE_COUNT_X	20
#define TILE_COUNT_Y	20
#define SAMPLE_TILE_COUNT_X		20
#define SAMPLE_TILE_COUNT_Y		9

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
	TILE_INFO tileInfo[TILE_COUNT_Y][TILE_COUNT_X];

	Image* sampleImage = nullptr;

	int posX, posY = 0;
	int selectedIdX, selectedIdY = 0;
	int selectedTileCountX, selectedTileCountY;

	SAMPLE_TILE_INFO	selectedSampleTile;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	//void Save();
	//void Load();
};

