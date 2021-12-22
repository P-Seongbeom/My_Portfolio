#pragma once
#include "GameObject.h"
#include "Config.h"

class Image;
class TileMap : public GameObject
{
private:
	Image* mapTile[SAMPLE_IMAGE_COUNT] = {};

	TILE_INFO tileInfo[SAMPLE_IMAGE_COUNT][TILE_COUNT_Y][TILE_COUNT_X] = {};

	void LoadMapFile(int mapNum);
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void BackGroundRender(HDC hdc);
	void FrontStructureRender(HDC hdc);
};

