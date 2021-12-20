#pragma once
#include "GameEntity.h"

class GameObject : public GameEntity
{
protected:
	POINTFLOAT pos = {};
	RECT shape = {};

	float moveSpeed = 0.0f;
	int bodySize = 0;
public:
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos = pos; }

};

