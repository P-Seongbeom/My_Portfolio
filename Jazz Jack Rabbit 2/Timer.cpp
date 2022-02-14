#include "Config.h"
#include "Timer.h"

using namespace std::chrono;

high_resolution_clock::time_point Timer::_prevTime = {};
float Timer::_deltaTime = 0.0f;
float Timer::_timeScale = 1.0f;
unsigned long Timer::_fps = 0;
unsigned long Timer::_fpsFrameCount = 0;
float Timer::_fpsTimeElapsed = 0.0f;

void Timer::SetTimeScale(float timeScale)
{
	_timeScale = timeScale;
}

float Timer::GetTimeScale() noexcept
{
	return _timeScale;
}

float Timer::GetDeltaTime() noexcept
{
	return _deltaTime * _timeScale;
}

void Timer::Init() noexcept
{
	_prevTime = high_resolution_clock::now();
}

bool Timer::CanUpdate() noexcept
{
	auto current = high_resolution_clock::now();

	duration<float> elapsed = current - _prevTime;

	if (MS_PER_UPDATE * 0.001f > elapsed.count())
	{
		return false;
	}

	_deltaTime = elapsed.count();

	//++_fpsFrameCount;
	//_fpsTimeElapsed += _deltaTime * _timeScale;
	//if (_fpsTimeElapsed >= 1.0f)
	//{
	//	_fps = _fpsFrameCount;
	//	_fpsFrameCount = 0;
	//	_fpsTimeElapsed = 0.0f;
	//}

	_prevTime = current;

	return true;
}