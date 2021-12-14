#pragma once
#include "Config.h"
#include <time.h>

class Timer
{
private:
	bool isHardware = false;
	__int64 periodFrequency = 0;

	float timeScale = 0.0f;
	__int64 currTime = 0;
	__int64 lastTime = 0;
	float deltaTime = 0.0f;

	float fpsTimeElapsed = 0.0f;
	unsigned long fpsFrameCount = 0;
	unsigned long fps = 0;

public:
	void Init();
	void Tick();

	inline unsigned long GetFPS() { return fps; }
	inline float GetDeltaTime() { return deltaTime; }
};

