#include "TimeManager.h"
#include "Timer.h"

void TimeManager::Init()
{
    timer = new Timer;
    timer->Init();
}

void TimeManager::Update()
{
    timer->Tick();
}

void TimeManager::Render(HDC hdc)
{
    wsprintf(szText, "FPS : %d", timer->GetFPS());
    TextOut(hdc, WIN_SIZE_X - 150, 30, szText, strlen(szText));
}

void TimeManager::Release()
{
    SAFE_DELETE(timer);
}

float TimeManager::GetDeltaTime()
{
    if (timer) return timer->GetDeltaTime();

    return 0.0f;
}
