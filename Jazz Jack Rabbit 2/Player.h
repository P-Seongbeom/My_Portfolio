#pragma once
#include "GameObject.h"
#include "Config.h"

#define PLAYER_MOVE_SPEED	200.0f
#define JUMP_VELOCITY		500.0f
#define GRAVITY				965.0f

class Ammo;
class Image;
class Player : public GameObject
{
	enum class Echaracter { jazz, spaz, Lori };
	enum class EplayerState { Stand, Walk, Run, Jump, Rope };


private:
	Ammo* ammo = nullptr;

	Image* rabbitMotion[5] = {};

	Echaracter playerCharacter = {};
	EplayerState playerState = {};
	EmoveDir playerMoveDir = {};

	POINTFLOAT renderPos = {};

	float moveSpeed = 0.0f;


	void inputAction();
	bool canMove = true;
	bool stayGetDown = false;
	bool inputShiftKey = false;
	bool endOfHorizontal = false;
	bool endOfVertical = false;

	void playerJump();
	bool jumpKeyPressed = false;
	float jumpHeight = 0.0f;
	float gravity = 0.0f;
	float velocity = 0.0f;
	float minVelocity = 0.0f;

	void quickDownAnimation();
	bool quickDown = false;

	void motionAnimator(int playerState, float waitMotionTime, float frameTerm, int maxFrameX);
	int renderFrameX = 0;
	int renderFrameY = 0;

	//타이머 관련
	void initMotion();
	float motionFrameTime = 0.0f;
	float playerWatingTime = 0.0f;

	//총알
	void fire();
	bool fireAmmo = false;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~Player() = default;

	void SetPlayerInfo(EplayerState state, EmoveDir dir) { this->playerState = state; 
														   this->playerMoveDir = dir; }
	bool GetEndOfHorizntal() { return this->endOfHorizontal; }
	bool GetEndOfVertical() { return this->endOfVertical; }

	EmoveDir GetMoveDir() { return this->playerMoveDir = playerMoveDir; }
};

