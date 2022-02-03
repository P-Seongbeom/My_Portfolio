#pragma once
#include "GameEntity.h"

class Image;
class StageClearScene : public GameEntity
{
private:
	Image* stageClearScene = nullptr;
	Image* background = nullptr;

	float frameTimer = 0.0f;
	int renderFrameX = 0;
	int renderFrameY = 0;

	POINTFLOAT renderPos = {};

public:
	virtual ~StageClearScene() = default;
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

