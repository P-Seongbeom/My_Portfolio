#pragma once
#include "Config.h"
#include "GameObject.h"

class RectCollider
{
private:
	RECT rect1;
	RECT rect2;
	RECT rect3;

public:
	void GiveDamageObject1(GameObject* object1, int sizeX1, int sizeY1, GameObject* object2, int sizeX2, int sizeY2);
	void CollideObjects(GameObject* object1, int sizeX1, int sizeY1, GameObject* object2, int sizeX2, int sizeY2);
};

