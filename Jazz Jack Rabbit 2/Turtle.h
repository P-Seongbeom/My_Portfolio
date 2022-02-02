#pragma once
#include "GameObject.h"
#include "Config.h"

#define TURTLE_MOVE_SPEED 100.0f

class Image;
class Turtle : public GameObject
{
	enum class EturtleState{Walk, Hide, Die, End};

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

	RECT GetCollisionRect() { return collisionRect; }

	void SetRenderPos(POINTFLOAT pos1, POINTFLOAT pos2, RECT* zone1, RECT* zone2) 
	{ 
		if (freeCameraMoveZone(zone1, pos2))
		{
			this->renderPos.x = pos1.x - pos2.x + WIN_SIZE_X / 2;
		}

		if (pos2.x <= WIN_SIZE_X / 2 || pos2.x >= WIN_SIZE_X * 1.5f)
		{
			this->renderPos.x = pos1.x;
		}

		if (freeCameraMoveZone(zone2, pos2))
		{
			this->renderPos.y = pos1.y - pos2.y + WIN_SIZE_Y/2;
		}
	}


};

