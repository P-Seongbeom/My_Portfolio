#pragma once
#include "Singleton.h"
#include "Config.h"

class GameData : public Singleton<GameData>
{
private:
	int playerLife = 3;
	POINTFLOAT playerPosition = {};
	POINTFLOAT playerRenderPosition = {};

public:
	void Release() {};

	void SavePlayerData(int life, POINTFLOAT pos, POINTFLOAT renderPos) 
	{ 
		this->playerLife = life;
		this->playerPosition = pos;
		this->playerRenderPosition = renderPos;
	}

	int GetPlayerLife() { return this->playerLife; }

	POINTFLOAT GetPlayerPos() { return this->playerPosition; }
	POINTFLOAT GetPlayerRenderPos() { return this->playerRenderPosition; }
};