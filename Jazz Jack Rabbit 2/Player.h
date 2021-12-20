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

	Image* rabbit[3][5];
	RABBIT player_Jazz = {};

	POINTFLOAT currPos = {};

	float moveSpeed = 0.0f;
	float velocity = 0.0f;
	float minVelocity = 0.0f;
	float gravity = 0.0f;
	float jumpHeight = 0.0f;

	//타이머 관련
	float jazzsFrameTime = 0.0f;
	float jazzsTime = 0.0f;

	//임시
	float prevPosY = 0.0f;

	bool jumpKeyPressed = false;
	bool stayGetDown = false;
	bool quickDown = false;
	bool canMove = true;
	bool inputShiftKey = false;

	void StandBy();
	void Action();
	void Walk();
	void Run();
	void Jump();
	void QuickDown();
	
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~Player() = default;

};

