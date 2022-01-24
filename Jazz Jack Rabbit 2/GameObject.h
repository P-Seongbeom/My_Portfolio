#pragma once
#include "GameEntity.h"

class GameObject : public GameEntity
{
protected:
	POINTFLOAT pos = {};

	float moveSpeed = 0.0f;

	bool collideLeft = false;
	bool collideRight = false;
	bool collideTop = false;
	bool collideRope = false;
	bool collideBottom = false;
	bool canfalling = false;
	bool jumpSwitch = false;

public:
	void SetPos(POINTFLOAT pos) { this->pos = pos; }
	POINTFLOAT GetPos() { return this->pos = pos; }

	virtual ~GameObject();

	void SetBottomCollision(bool collision) { this->collideBottom = collision; }
	void SetLeftCollision(bool collision) { this->collideLeft = collision; }
	void SetRightCollision(bool collision) { this->collideRight = collision; }
	void SetTopCollision(bool collision) { this->collideTop = collision; }
	void SetRopeCollision(bool collision) { this->collideRope = collision; }
	void SetPosY(float posy) { this->pos.y = posy; }
	void SetPosX(float posx) { this->pos.x = posx; }
	bool GetFallingState() { return this->canfalling; }
	bool GetjumpSwitch() { return this->jumpSwitch; }
	float GetMoveSpeed() { return this->moveSpeed; }

};

