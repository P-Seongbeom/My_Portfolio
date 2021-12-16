#include "PlayerManager.h"
#include "Config.h"


HRESULT PlayerManager::Init()
{
    diameter = 20;
    pos.x = 10;
    pos.y = 500;

    moveSpeed = PLAYER_MOVE_SPEED;
    velocity = JUMP_VELOCITY;
    minVelocity = -JUMP_VELOCITY;
    gravity = GRAVITY;

    //점프 높이 갱신
    prevPosY = pos.y + jumpHeight;

    return S_OK;
}

void PlayerManager::Update()
{
    Move();
    Jump();

    //점프 높이 갱신
    if (prevPosY > pos.y + jumpHeight)
    {
        prevPosY = pos.y + jumpHeight;
    }
}

void PlayerManager::Render(HDC hdc)
{
    char test[128] = { 0 };
    wsprintf(test, "Up Power : %d  y좌표 : %d", (int)velocity, (int)pos.y + (int)jumpHeight);
    TextOut(hdc, 300, 500, test, strlen(test));
    wsprintf(test, "최대 점프 높이 : %d", (int)prevPosY);
    TextOut(hdc, 300, 525, test, strlen(test));
    wsprintf(test, "현재 점프 높이 : %d", -(int)jumpHeight);
    TextOut(hdc, 300, 550, test, strlen(test));

    Ellipse(hdc, (int)pos.x, (int)pos.y + (int)jumpHeight, (int)pos.x + (int)diameter, (int)pos.y + (int)jumpHeight + (int)diameter);
}


void PlayerManager::Release()
{
}

void PlayerManager::Move()
{
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
    {
        pos.x -= moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();;
    }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
    {
        pos.x += moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();;
    }
    //if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
    //{
    //    jazzPos.y -= 3.0f;
    //}
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
    {
        if (!jumpKeyPressed)
        {
            stayGetDown = true;
            velocity = JUMP_VELOCITY + 150;
            minVelocity = -(JUMP_VELOCITY + 150);
        }
        else if (jumpKeyPressed)
        {
            velocity = JUMP_VELOCITY;
            minVelocity = -JUMP_VELOCITY;
            jumpKeyPressed = false;
            jumpHeight = 0;
        }

    }
    else if (KeyManager::GetSingleton()->IsOnceKeyUP(VK_DOWN))
    {
        stayGetDown = false;
    }

    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_SPACE))
    {
        jumpKeyPressed = true;
    }
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LSHIFT))
    {
        moveSpeed = moveSpeed * 2;
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyUP(VK_LSHIFT))
    {
        moveSpeed = moveSpeed / 2;
    }
}

void PlayerManager::Jump()
{
    if (!jumpKeyPressed) return;

    jumpHeight -= velocity * TimeManager::GetSingleton()->GetDeltaTime();
    velocity -= gravity * TimeManager::GetSingleton()->GetDeltaTime();

    if (velocity <= minVelocity)
    {
        if (stayGetDown)
        {
            velocity = JUMP_VELOCITY + 150;
            minVelocity = -(JUMP_VELOCITY + 150);
        }
        else
        {
            velocity = JUMP_VELOCITY;
            minVelocity = -JUMP_VELOCITY;
        }
        jumpKeyPressed = false;
        jumpHeight = 0;
    }
    //else if (velocity <= minVelocity && stayGetDown == true)
    //{
    //    velocity = JUMP_VELOCITY + 150;
    //    minVelocity = -JUMP_VELOCITY + 150;
    //    jumpKeyPressed = false;
    //    jumpHeight = 0;
    //}

}


