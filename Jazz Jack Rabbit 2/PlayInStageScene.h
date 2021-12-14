#pragma once
#include "GameEntity.h"

class PlayerManager;

class PlayInStageScene : public GameEntity
{
private:
	PlayerManager* jumpTest = nullptr;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~PlayInStageScene() = default;
};

