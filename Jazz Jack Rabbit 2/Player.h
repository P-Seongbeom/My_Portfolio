#pragma once
#include "GameObject.h"
#include "Config.h"

#define PLAYER_MOVE_SPEED	200.0f
#define JUMP_VELOCITY		500.0f
#define GRAVITY				1000.0f

class Ammo;
class Image;
class Player : public GameObject
{
	enum class Echaracter { jazz, spaz, Lori };
	enum class EplayerState { Stand, Walk, Run, Jump, Rope, LookUp, LookDown, Falling };


private:
	Ammo* ammo = nullptr;

	Image* rabbitMotion[8] = {};
	Image* collisionRect = {};

	Echaracter playerCharacter = {};
	EplayerState playerState = {};
	EmoveDir playerMoveDir = {};

	POINTFLOAT renderPos = {};

	float moveSpeed = 0.0f;
	float t = 0;

	void inputAction();
	bool canMove = true;
	bool stayGetDown = false;
	bool inputShiftKey = false;
	bool endOfHorizontal = false;
	bool endOfVertical = false;
	bool collidedLeft = false;
	bool collidedRight = false;
	bool moveKeyPressed = false;

	void playerJump();
	bool jumpKeyPressed = false;
	float jumpHeight = 0.0f;
	float velocity = 0.0f;
	float minVelocity = 0.0f;
	float jumpPosY = 0;
	float gravity = 0.0f;
	bool collideTop = false;
	bool collideRope = false;

	void freeFall();
	float fallingSpeed = 0.0f;
	float fallingMaxSpeed = 0.0f;
	bool canfalling = true;
	bool collideBottom = false;

	void quickDown();
	bool quickDownState = false;

	void motionAnimator(int playerState, float waitMotionTime, float frameTerm, int maxFrameX);
	void jumpMotionAnimator(int playerState, float waitingTime, float frameTerm, int maxFrameX);
	void ropeMotionAnimator(int playerState, float waitingTime, float frameTerm, int maxFrameX);
	int renderFrameX = 0;
	int renderFrameY = 0;

	//타이머 관련
	void initMotionFrame();
	float motionFrameTime = 0.0f;
	float playerWatingTime = 0.0f;
	float stayKeyDownTime = 0.0f;

	//총알
	void fire();
	bool fireAmmo = false;

	//화면상 캐릭터 위치 설정
	void unlockingCenterPlayer();
	//void releaseLooking();
	bool releasing = false;
	bool lookUp = false;

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
	bool GetJumpKeyPressed() { return this->jumpKeyPressed; }
	void SetFalling(bool fall) { this->canfalling = fall; }
	void SetCollisionState(bool collision) { this->collideBottom = collision; }
	void SetLeftCollision(bool collision) { this->collidedLeft = collision; }
	void SetRightCollision(bool collision) { this->collidedRight = collision; }
	void SetTopCollision(bool collision) { this->collideTop = collision; }
	void SetRopeCollision(bool collision) { this->collideRope = collision; }
	void SetPosY(int posy) { this->pos.y = posy; }
	void SetPosX(int posx) { this->pos.x = posx; }
	bool GetFallingState() { return this->canfalling; }

	POINTFLOAT GetRenderPos() { return this->renderPos; }

	EmoveDir GetMoveDir() { return this->playerMoveDir; }
	float GetMoveSpeed() { return this->moveSpeed; }

	//디버깅용
	float getfallspeed() { return this->fallingSpeed; }
	bool getfall() { return this->canfalling; }
	bool getCollbot() { return this->collideBottom; }
};

