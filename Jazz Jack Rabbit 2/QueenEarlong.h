#pragma once
#include "Config.h"
#include "GameObject.h"

#define BOSS_POS_X	1166
#define BOSS_POS_Y	720
#define BOSS_DIE_POS_X 1216

class Image;
class Player;
class QueenEarlong : public GameObject
{
	enum class EQueenState { Idle, Shouting, StompFoot, Wobble, Die, End};
private:
	Image* QueenMotion[(int)EQueenState::End] = {};
	Image* QueensBrick = nullptr;

	POINTFLOAT renderPos = {};
	POINTFLOAT brickPos = {};
	POINTFLOAT brickRenderPos = {};
	POINTFLOAT playerPos = {};

	RECT queenCollisionRect = {};
	RECT brickCollisionRect = {};
	RECT updateRect = {};

	Player* target = nullptr;

	void makeBrick();
	void dropBrick();
	float brickFallingSpeed = 0.0f;
	float brickFallingMaxSpeed = 0.0f;
	bool makedBirck = false;
	float dropBrickTimer = 0.0f;

	void shouting();
	float pushPlayerPos = 0.0f;

	void randomStateSetting();
	EQueenState queenState = {};

	void action();

	void motionAnimator(int bossState, float frameTerm, int cycleFrameX, int cycleMaxFrameX, int maxFrameX, float playTime);
	void initMotionFrame();
	int renderFrameX = 0;
	int renderFrameY = 0;
	int motionCount = 0;
	float motionFrameTime = 0.0f;
	float stateHoldingTime = 0.0f;
	bool randomMotionChange = false;

	void freeFall();
	float fallingSpeed = 0.0f;
	float fallingMaxSpeed = 0.0f;

	void getDamage();
	void die();
	float blinkingTime = 0.0f;
	bool blinking = false;
	float deadTime = 0.0f;
	bool isDead = false;
	

	int pushingDistance = 0;

	bool freeCameraMoveZone(RECT* zone, POINTFLOAT ptf);

	bool canUpdate();

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~QueenEarlong() = default;

	RECT GetCollisionRect() { return this->queenCollisionRect; }

	void SetTarget(Player* player);

	void SetRenderPos(POINTFLOAT pos1, POINTFLOAT pos2, RECT* zone1, RECT* zone2);

	bool GetIsDead() { return this->isDead; }
};

