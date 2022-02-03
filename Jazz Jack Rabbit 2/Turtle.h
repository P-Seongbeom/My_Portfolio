#pragma once
#include "GameObject.h"
#include "Config.h"

#define TURTLE_MOVE_SPEED 100.0f

class Image;
class Turtle : public GameObject
{
	enum class EturtleState{Walk, Hide, Die, Wobble, End};

private:
	Image* turtleMotion[(int)EturtleState::End] = {};
	
	EturtleState turtleState = {};
	EmoveDir turtleMoveDir = {};

	POINTFLOAT renderPos = {};

	RECT collisionRect = {};

	void action();
	float moveTimer = 0.0f;

	void walkingMotion(float frameTerm, int maxFrameX);
	void hidingMotion(float frameTerm, int maxFrameX);
	void deadMotion();
	int renderFrameX = 0;
	int renderFrameY = 0;
	float motionFrameTime = 0.0f;
	bool stickOutHead = false;
	bool motionChange = false;

	void initMotionFrame();

	void freeFall();
	float fallingSpeed = 0.0f;
	float fallingMaxSpeed = 0.0f;

	void getDamage();
	void die();

	bool freeCameraMoveZone(RECT* zone, POINTFLOAT ptf);

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~Turtle() = default;

	RECT GetCollisionRect() { return this->collisionRect; }

	void SetRenderPos(POINTFLOAT pos1, POINTFLOAT pos2, RECT* zone1, RECT* zone2);
};

