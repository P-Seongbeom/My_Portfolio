#pragma once
#include "GameObject.h"

#define PLAYER_MOVE_SPEED	200.0f
#define JUMP_VELOCITY		500.0f
#define GRAVITY				965.0f

class PlayerManager : public GameObject
{
private:

	//test용 원 그리기
	int diameter = 0;

	float moveSpeed = 0.0f;
	float velocity = 0.0f;
	float minVelocity = 0.0f;
	float gravity = 0.0f;
	float jumpHeight = 0.0f;

	float prevPosY = 0.0f;

	bool jumpKeyPressed = false;
	bool stayGetDown = false;

	void Move();
	void Jump();
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~PlayerManager() = default;

};

