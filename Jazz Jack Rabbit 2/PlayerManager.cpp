#include "PlayerManager.h"
#include "Jazz.h"
#include "Config.h"


HRESULT PlayerManager::Init()
{
    jazz = new Jazz;
    jazz->Init();
    jazzPos = jazz->GetPos();

    velocity = 300.f;
    gravity = 400.f;

    return S_OK;
}

void PlayerManager::Update()
{
    Move();
    Jump();

 
}

void PlayerManager::Render(HDC hdc)
{
    char test[128] = { 0 };
    wsprintf(test, "Up Power : %d  y좌표 : %d", (int)velocity, (int)jazzPos.y + (int)jumpHeight);
    TextOut(hdc, 300, 500, test, strlen(test));
    wsprintf(test, "점프 높이 : %d", (int)jumpHeight);
    TextOut(hdc, 300, 550, test, strlen(test));

    jazz->Render(hdc);
}


void PlayerManager::Release()
{
}

void PlayerManager::Move()
{
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
    {
        jazzPos.x -= 3.0f;
    }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
    {
        jazzPos.x += 3.0f;
    }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
    {
        jazzPos.y -= 3.0f;
    }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
    {
        jazzPos.y += 3.0f;
    }
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
    {
        jumpKeyPressed = true;
    }

    jazz->SetPos(jazzPos);
}

void PlayerManager::Jump()
{
    if (!jumpKeyPressed) return;

    if (velocity <= -300.f)
    {
        velocity = 300.f;
        jumpKeyPressed = false;
        jumpHeight = 0;
    }

    jumpHeight -= velocity * 0.0004f;
    velocity -= gravity * 0.02f;
    
    jazzPos.y = jazzPos.y + jumpHeight;

}


