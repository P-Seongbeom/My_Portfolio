#include "Player.h"
#include "Image.h"

HRESULT Player::Init()
{
    rabbit[0][0] = ImageManager::GetSingleton()->AddImage("Image/character/jazz_stand.bmp", 1296, 110, 27, 2, true, RGB(44, 102, 150));
    rabbit[0][1] = ImageManager::GetSingleton()->AddImage("Image/character/jazz_walk.bmp", 448, 106, 8, 2, true, RGB(44, 102, 150));
    rabbit[0][2] = ImageManager::GetSingleton()->AddImage("Image/character/jazz_run.bmp", 277, 106, 4, 2, true, RGB(44, 102, 150));

    if (rabbit == nullptr)
    {
        cout << "로드 실패" << endl;
        return E_FAIL;
    }

    player_Jazz.state = playerState::Stand;
    player_Jazz.frameX = 0;
    player_Jazz.frameY = 0;

    pos.x = 10;
    pos.y = 350;

    currPos.y = pos.y;

    moveSpeed = PLAYER_MOVE_SPEED;
    velocity = JUMP_VELOCITY;
    minVelocity = -JUMP_VELOCITY;
    gravity = GRAVITY;

    //점프 높이 갱신
    prevPosY = pos.y + jumpHeight;

    return S_OK;
}

void Player::Update()
{
    Action();

    if (player_Jazz.state == playerState::Stand)
    {
        StandBy();
    }
    else if (player_Jazz.state == playerState::Walk)
    {
        Walk();
    }
    else if (player_Jazz.state == playerState::Run)
    {
        Run();
    }

    Jump();
    QuickDown();

    //점프 높이 갱신
    if (prevPosY > pos.y + jumpHeight)
    {
        prevPosY = pos.y + jumpHeight;
    }
}

void Player::Render(HDC hdc)
{
    char test[128] = { 0 };
    wsprintf(test, "Up Power : %d  y좌표 : %d", (int)velocity, (int)currPos.y);
    TextOut(hdc, 300, 500, test, strlen(test));
    wsprintf(test, "최대 점프 높이 : %d", (int)prevPosY);
    TextOut(hdc, 300, 525, test, strlen(test));
    wsprintf(test, "현재 점프 높이 : %d", -(int)jumpHeight);
    TextOut(hdc, 300, 550, test, strlen(test));

    Rectangle(hdc, (int)pos.x - 16, (int)currPos.y - 32, (int)pos.x + 16, (int)currPos.y);

    if(player_Jazz.state == playerState::Stand)
    {
        rabbit[0][0]->Render(hdc, (int)pos.x, (int)currPos.y, rabbit[0][0]->GetCurrFrameX(), rabbit[0][0]->GetCurrFrameY());
    }
    else if(player_Jazz.state == playerState::Walk)
    {
        rabbit[0][1]->Render(hdc, (int)pos.x, (int)currPos.y, rabbit[0][1]->GetCurrFrameX(), rabbit[0][1]->GetCurrFrameY());
    }
    else if (player_Jazz.state == playerState::Run)
    {
        rabbit[0][2]->Render(hdc, (int)pos.x, (int)currPos.y, rabbit[0][2]->GetCurrFrameX(), rabbit[0][2]->GetCurrFrameY());
    }
}


void Player::Release()
{
}

void Player::StandBy()
{
    jazzsTime += TimeManager::GetSingleton()->GetDeltaTime();

    if (jazzsTime > 2)
    {
        jazzsFrameTime += TimeManager::GetSingleton()->GetDeltaTime();
    }

    if (jazzsFrameTime > 0.1)
    {
        ++player_Jazz.frameX;
        jazzsFrameTime = 0;
    }

    if (player_Jazz.frameX >= 27)
    {
        player_Jazz.frameX = 0;
        jazzsTime = 0;
    }

    rabbit[0][0]->SetCurrFrameX(player_Jazz.frameX);
    rabbit[0][0]->SetCurrFrameY(player_Jazz.frameY);
}

void Player::Action()
{
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LSHIFT))
    {
        inputShiftKey = true;
        moveSpeed = PLAYER_MOVE_SPEED * 2;
    }
    if (KeyManager::GetSingleton()->IsOnceKeyUP(VK_LSHIFT))
    {
        inputShiftKey = false;
        moveSpeed = PLAYER_MOVE_SPEED;
        jazzsTime = 0;
        jazzsFrameTime = 0;
        player_Jazz.frameX = 0;
        player_Jazz.frameY = 0;
    }

    if (canMove)
    {
        if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
        {
            pos.x -= moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();
            player_Jazz.frameY = 1;

            if(!inputShiftKey)player_Jazz.state = playerState::Walk;
            else if(inputShiftKey) player_Jazz.state = playerState::Run;

        }
        if (KeyManager::GetSingleton()->IsOnceKeyUP(VK_LEFT))
        {
            player_Jazz.state = playerState::Stand;
            jazzsTime = 0;
            jazzsFrameTime = 0;
            player_Jazz.frameX = 0;
        }
        if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
        {
            pos.x += moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();
            player_Jazz.frameY = 0;

            if (inputShiftKey) player_Jazz.state = playerState::Run;
            else player_Jazz.state = playerState::Walk;

        }
        if (KeyManager::GetSingleton()->IsOnceKeyUP(VK_RIGHT))
        {
            player_Jazz.state = playerState::Stand;
            jazzsTime = 0;
            jazzsFrameTime = 0;
            player_Jazz.frameX = 0;
        }
    }

    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
    {
        if (!jumpKeyPressed)
        {
            stayGetDown = true;
        }
        else if (jumpKeyPressed)
        {
            jumpKeyPressed = false;
            stayGetDown = false;
            quickDown = true;
            canMove = false;
        }
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyUP(VK_DOWN))
    {
        stayGetDown = false;
    }

    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_SPACE))
    {
       if(!quickDown) jumpKeyPressed = true;
    }
}

void Player::Walk()
{
    jazzsFrameTime += TimeManager::GetSingleton()->GetDeltaTime();

    if (jazzsFrameTime > 0.1)
    {
        ++player_Jazz.frameX;
        jazzsFrameTime = 0;
    }

    if (player_Jazz.frameX >= 8)
    {
        player_Jazz.frameX = 0;
        jazzsTime = 0;
    }

    rabbit[0][1]->SetCurrFrameX(player_Jazz.frameX);
    rabbit[0][1]->SetCurrFrameY(player_Jazz.frameY);
}

void Player::Run()
{
    jazzsFrameTime += TimeManager::GetSingleton()->GetDeltaTime();

    if (jazzsFrameTime > 0.1)
    {
        ++player_Jazz.frameX;
        jazzsFrameTime = 0;
    }

    if (player_Jazz.frameX >= 4)
    {
        player_Jazz.frameX = 0;
        jazzsTime = 0;
    }

    rabbit[0][2]->SetCurrFrameX(player_Jazz.frameX);
    rabbit[0][2]->SetCurrFrameY(player_Jazz.frameY);
}

void Player::Jump()
{
    if (!jumpKeyPressed) return;

    player_Jazz.state = playerState::Jump;

    if (stayGetDown)
    {
        velocity = JUMP_VELOCITY + 150;
        minVelocity = -(JUMP_VELOCITY + 150);
        canMove = false;
        stayGetDown = false;
    }
    else if(!stayGetDown)
    {
        if (velocity <= 0) canMove = true;

        if (velocity <= minVelocity)
        {
            velocity = JUMP_VELOCITY;
            minVelocity = -JUMP_VELOCITY;
            canMove = true;
            jumpKeyPressed = false;
            jumpHeight = 0;
            player_Jazz.state = playerState::Stand;
        }
    }

    jumpHeight -= velocity * TimeManager::GetSingleton()->GetDeltaTime();
    velocity -= gravity * TimeManager::GetSingleton()->GetDeltaTime();
    
    currPos.y = pos.y + jumpHeight;
}

void Player::QuickDown()
{
    if (!quickDown) return;

    currPos.y += 500 * TimeManager::GetSingleton()->GetDeltaTime();
    pos.y = currPos.y;

    if (currPos.y >= 500)
    {
        currPos.y = 500;
        
        velocity = JUMP_VELOCITY;
        minVelocity = -JUMP_VELOCITY;
        jumpHeight = 0;
        canMove = true;
        quickDown = false;
    }
}



