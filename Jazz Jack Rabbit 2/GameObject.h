#pragma once
#include "GameEntity.h"

class GameObject : public GameEntity
{
protected:
	POINTFLOAT pos = {};

	int bodySize = 0;
public:
	void SetPos(POINTFLOAT pos) { this->pos = pos; }
	POINTFLOAT GetPos() { return this->pos = pos; }

	virtual ~GameObject();

};

