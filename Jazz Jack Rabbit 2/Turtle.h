#pragma once
#include "GameObject.h"
#include "Config.h"

#define TURTLE_MOVE_SPEED 100.0f

class Image;
class Turtle : public GameObject
{
	enum class EturtleState{Walk, Hide, End};

private:
	Image* turtleMotion[(int)EturtleState::End] = {};
	
	EturtleState turtleState = {};
	EmoveDir turtleMoveDir = {};

	void action();
	float moveSpeed = 0.0f;
	float moveTimer = 0.0f;


	void walkingMotion(float frameTerm, int maxFrameX);
	void hidingMotion(float frameTerm, int maxFrameX);
	int renderFrameX = 0;
	int renderFrameY = 0;
	float motionFrameTime = 0.0f;
	bool stickOutHead = false;
	bool motionChange = false;

	bool updateZone(RECT* zone, POINTFLOAT ptf);

	void initMotionFrame();

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~Turtle() = default;
};

