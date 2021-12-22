#pragma once
#include "GameObject.h"
#include "Config.h"

#define PLAYER_MOVE_SPEED	200.0f
#define JUMP_VELOCITY		500.0f
#define GRAVITY				965.0f

class Image;
class Player : public GameObject
{
private:

	Image* rabbitMotion[5];
	RABBIT player_Jazz = {};

	POINTFLOAT renderPos = {};

	float moveSpeed = 0.0f;


	void inputAction();
	bool canMove = true;
	bool stayGetDown = false;
	bool inputShiftKey = false;

	void playerJump();
	bool jumpKeyPressed = false;
	float jumpHeight = 0.0f;
	float gravity = 0.0f;
	float velocity = 0.0f;
	float minVelocity = 0.0f;

	void quickDownAnimation();
	bool quickDown = false;

	void motionAnimator(int playerState, float waitMotionTime, float frameTerm, int maxFrameX);
	
	//타이머 관련
	void InitMotion();
	float motionFrameTime = 0.0f;
	float playerWatingTime = 0.0f;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~Player() = default;

};

