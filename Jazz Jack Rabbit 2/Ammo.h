#pragma once
#include "GameObject.h"
#include "Config.h"

class Image;
class PixelCollider;
class Turtle;
class QueenEarlong;
class Ammo : public GameObject
{
	enum class EammoType { Normal, Bounce };

private:
	Image* ammoImage = nullptr;
	Image* ammoEffectImage = nullptr;

	EammoType ammoType = {};

	POINTFLOAT renderPos = {};

	EmoveDir ammoDir = {};

	RECT collissionRect = {};


	PixelCollider* pixelCollider = {};

	void fired();
	float fireTimer = 0.0f;
	int ammoMoveDis = 0;
	bool isFire = false;
	bool ammoAlive = false;
	bool changeAmmo = false;
	bool collideObject = false;

	void explosionEffect(float waitingTime, int maxFrameX);
	float ammoEffectTimer = 0.0f;
	int renderFrameX = 0;
	int renderFrameY = 0;
	bool effectSwitch = false;

	bool freeCameraMoveZone(RECT* zone, POINTFLOAT ptf);
	POINTFLOAT prevRenderPos = {};

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~Ammo() = default;

	void CollideObject(HDC mapPixel, Turtle* enemy, QueenEarlong* boss, GameObject ammo);

	void SetIsFire(bool fire) { this->isFire = fire; }
	bool GetIsFire() { return this->isFire; }
	void SetAlive(bool alive) { this->ammoAlive = alive; }
	bool GetAlive() { return this->ammoAlive; }
	void SetAmmoDir(EmoveDir dir) { this->ammoDir = dir; }
	void SetPosY(float posy) { this->pos.y = posy; }
	void SetRenderPos(POINTFLOAT pt) { this->renderPos = pt; }
	void SetRenderPosY(float renderPosY) { this->renderPos.y = renderPosY; }

};

