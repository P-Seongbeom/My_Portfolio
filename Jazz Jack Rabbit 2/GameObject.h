#pragma once
#include "GameEntity.h"

class GameObject : public GameEntity
{
protected:
	POINTFLOAT pos = {};

	float moveSpeed = 0.0f;
	int hp = 0;

	bool collideLeft = false;
	bool collideRight = false;
	bool collideTop = false;
	bool collideRope = false;
	bool collideBottom = false;
	bool canfalling = true;
	bool jumpSwitch = false;
	bool getHit = false;

public:
	virtual ~GameObject();

	void SetPos(POINTFLOAT pos) { this->pos = pos; }
	POINTFLOAT GetPos() { return this->pos = pos; }
	void SetPosX(float posx) { this->pos.x = posx; }
	void SetPosY(float posy) { this->pos.y = posy; }

	void SetBottomCollision(bool collision) { this->collideBottom = collision; }
	void SetLeftCollision(bool collision) { this->collideLeft = collision; }
	void SetRightCollision(bool collision) { this->collideRight = collision; }
	void SetTopCollision(bool collision) { this->collideTop = collision; }
	void SetRopeCollision(bool collision) { this->collideRope = collision; }
	bool GetFallingState() { return this->canfalling; }
	bool GetjumpSwitch() { return this->jumpSwitch; }
	bool GetHittedState() { return this->getHit; }
	float GetMoveSpeed() { return this->moveSpeed; }

	void GetHit(bool hit) { this->getHit = hit; }
	int GetHpValue() { return this->hp; }

};

