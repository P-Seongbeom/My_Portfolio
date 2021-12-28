#pragma once
#include "GameEntity.h"
#include "Config.h"

class Image;
class TiltleScene : public GameEntity
{
private:
	Image* titleImage = {};
	Image* guideWord = {};

public:
	virtual ~TiltleScene() = default;
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

