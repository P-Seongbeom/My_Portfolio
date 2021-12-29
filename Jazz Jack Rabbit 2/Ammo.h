#pragma once
#include "GameObject.h"
#include "Config.h"

class Image;
class Ammo : public GameObject
{
	enum class EammoType{ Normal, Bounce };

private:
	Image* ammo = nullptr;

	EammoType ammoType = {};

	POINT firedPos = {};

	EmoveDir ammoDir = {};

	float fireTimer = 0.0f;
	int ammoMoveDis = 0;
	bool isFire = false;
	bool ammoAlive = false;
	bool changeAmmo = false;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~Ammo() = default;

	void Fire();
	void ChangeAmmoType(EammoType type);

	void SetIsFire(bool fire) { this->isFire = fire; }
	bool GetIsFire() { return isFire; }
	void SetAlive(bool alive) { this->ammoAlive = alive; }
	bool GetAlive() { return ammoAlive; }
	void SetAmmoDir(EmoveDir dir) { this->ammoDir = dir; }
	void SetPosY(float posy) { this->pos.y = posy; }
};

