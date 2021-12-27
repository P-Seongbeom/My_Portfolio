#pragma once

#include "GameEntity.h"
#include "GameObject.h"

class Image;
class Player;
class Physics : public GameObject
{
private:
	Image* rect = {};
	Image* tileMapPixel = {};

	POINT rectPos = {};

	float fallingSpeed = 0.0f;
	float fallingMaxSpeed = 0.0f;
	float accelate = 0.0f;

	

public:
	virtual ~Physics() = default;
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual void PhysicsUpdate();

	void FallingPhysics(float posf);

};

