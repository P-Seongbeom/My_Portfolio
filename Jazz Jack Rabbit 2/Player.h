#pragma once
#include "GameObject.h"
#include "Config.h"

class Ammo;
class Image;
class Turtle;
class QueenEarlong;
class Player : public GameObject
{
	enum class Echaracter { jazz, spaz, Lori };
	enum class EplayerState { Stand, Walk, Run, Jump, Rope, Fire, Falling, QuickDown, UpperCut, End };

private:
	Ammo* ammo = nullptr;
	Image* playerMotion[(int)EplayerState::End] = {};
	Image* collisionRect = {};

	Echaracter playerCharacter = {};
	EplayerState playerState = {};
	EmoveDir playerMoveDir = {};

	POINTFLOAT renderPos = {};
	POINTFLOAT prevPos = {};

	RECT playerRect = {};

	int playerLife = 0;

	void inputAction();
	void skiddingPlayer();
	//float moveSpeed = 0.0f;
	float moveMaxSpeed = 0.0f;
	float accel = 0.0f;
	float moveKeyPressTime = 0.0f;
	bool canMove = true;
	bool stayGetDown = false;
	bool shiftKeyPressed = false;
	bool moveKeyPressed = false;
	//bool collideLeft = false;
	//bool collideRight = false;

	void jumpPlayer();
	void initJump();
	//bool jumpSwitch = false;
	float jumpVelocity = 0.0f;
	float gravity = 0.0f;
	//bool collideTop = false;
	//bool collideRope = false;
	bool upperCut = false;
	float stayJumpKeyTime = 0;

	void freeFall();
	float fallingSpeed = 0.0f;
	float fallingMaxSpeed = 0.0f;
	//bool canfalling = true;
	//bool collideBottom = false;

	void quickDown();
	bool quickDownSwitch = false;
	float quickDownWatingTime = 0.0f;

	void characterMotion();
	void motionAnimator(int playerState, float waitMotionTime, float frameTerm, int maxFrameX);
	void airMotionAnimator(int playerState, float waitingTime, float frameTerm, int maxFrameX);
	void ropeMotionAnimator(int playerState, float waitingTime, float frameTerm, int maxFrameX);
	int renderFrameX = 0;
	int renderFrameY = 0;

	//모션 프레임 관련
	void initMotionFrame();
	float motionFrameTime = 0.0f;
	float playerWatingTime = 0.0f;

	//총알
	void fire();
	void fireMotionSwitch();
	bool canFire = true;
	bool fireAmmo = false;
	bool fireMotion = false;
	float fireMotionTimer = false;

	//화면상 캐릭터 위치 설정
	void unlockingCenterPlayer();
	//void releaseLooking();
	bool releasing = false;
	bool lookUp = false;

	void getDamage();
	float hitCoolTime = 0.0f;
	bool blinking = true;
	float blinkingTime = 0.0f;
	bool isDead = false;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~Player() = default;

	void SetAmmoCollision(HDC mapPixel, Turtle* enemy, QueenEarlong* boss);

	void SetPlayerInfo(EplayerState state, EmoveDir dir) 
	{
		this->playerState = state;
		this->playerMoveDir = dir;
	}

	int GetPlayerLife() { return this->playerLife; }

	POINTFLOAT GetRenderPos() { return this->renderPos; }

	EmoveDir GetMoveDir() { return this->playerMoveDir; }

	RECT GetCollisionRect() { return this->playerRect; }

	//디버깅용
	float getfallspeed() { return this->fallingSpeed; }
	bool getfall() { return this->canfalling; }
	bool getCollbot() { return this->collideBottom; }
};

