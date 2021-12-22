#pragma once

#include <chrono>

class Timer
{
	using TimePoint = std::chrono::high_resolution_clock::time_point;

	static constexpr INT32 FPS = 60;
	static constexpr float MS_PER_UPDATE = 1000.0f / static_cast<float>(FPS) - 0.1f;
public:
	Timer() = delete;

	static void		SetTimeScale(float timeScale);
	static float	GetTimeScale() noexcept;
	static float	GetDeltaTime() noexcept;

	static void		Init() noexcept;
	static bool		CanUpdate() noexcept;

	static unsigned long GetFPS() { return fps; }

private:
	static TimePoint	_prevTime;
	static float		_deltaTime;
	static float		_timeScale;

	static float fpsTimeElapsed;
	static unsigned long fpsFrameCount;
	static unsigned long fps;
};