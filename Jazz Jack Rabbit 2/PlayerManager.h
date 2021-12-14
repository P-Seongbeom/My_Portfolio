#pragma once
#include "GameObject.h"

class Jazz;
class PlayerManager : public GameObject
{
private:
	Jazz* jazz = nullptr;

	POINTFLOAT jazzPos;

	float velocity = 0.0f;
	float gravity = 0.0f;
	float jumpHeight = 0.0f;

	bool jumpKeyPressed = false;

	void Move();
	void Jump();
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~PlayerManager() = default;

};

