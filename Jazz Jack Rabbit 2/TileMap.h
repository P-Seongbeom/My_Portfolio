#pragma once
#include "GameObject.h"
#include "Config.h"

class Image;
class TileMap : public GameObject
{
private:
	Image* mapTile[SAMPLE_IMAGE_COUNT] = {};
	Image* pixelImage = {};

	TILE_INFO tileInfo[SAMPLE_IMAGE_COUNT][TILE_COUNT_Y][TILE_COUNT_X] = {};

	bool renderOnOff = false;

	void LoadMapFile(int mapNum);
	void adjustRenderRatio(HDC hdc, int renderIdx, float cameraX, float cameraY, float ratio, float scale = (1.0F));
public:
	virtual ~TileMap() = default;
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void BackGroundRender(HDC hdc, float cameraX, float cameraY);
	void FrontStructureRender(HDC hdc, float cameraX, float cameraY);

	Image* GetImageInfo() { return this->pixelImage; }
};

