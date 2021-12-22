#include "Player.h"
#include "Image.h"

HRESULT Player::Init()
{
    rabbitMotion[(int)EplayerState::Stand] = ImageManager::GetSingleton()->FindImage("Image/character/jazz_stand.bmp");
    rabbitMotion[(int)EplayerState::Walk] = ImageManager::GetSingleton()->FindImage("Image/character/jazz_walk.bmp");
    rabbitMotion[(int)EplayerState::Run] = ImageManager::GetSingleton()->FindImage("Image/character/jazz_run.bmp");
    rabbitMotion[(int)EplayerState::Jump] = ImageManager::GetSingleton()->FindImage("Image/character/jump.bmp");

    if (rabbitMotion == nullptr)
    {
        cout << "로드 실패" << endl;
        return E_FAIL;
    }
    
    player_Jazz.state = EplayerState::Stand;
    player_Jazz.frameX = 0;
    player_Jazz.frameY = 0;

    pos.x = 50;
    pos.y = 375;

    renderPos.y = pos.y;

    moveSpeed = PLAYER_MOVE_SPEED;
    velocity = JUMP_VELOCITY;
    minVelocity = -JUMP_VELOCITY;
    gravity = GRAVITY;

    return S_OK;
}

void Player::Update()
{
    inputAction();

    if (player_Jazz.state == EplayerState::Stand)
    {
        motionAnimator((int)EplayerState::Stand, 2, (float)0.1, 27);
    }
    else if (player_Jazz.state == EplayerState::Walk)
    {
        motionAnimator((int)EplayerState::Walk, 0, (float)0.1, 8);
    }
    else if (player_Jazz.state == EplayerState::Run)
    {
        motionAnimator((int)EplayerState::Run, 0, (float)0, 4);
    }

    playerJump();
    
    quickDownAnimation();
    
}

void Player::Render(HDC hdc)
{
    char test[128] = { 0 };

    Rectangle(hdc, (int)pos.x - 10, (int)renderPos.y - 32, (int)pos.x + 10, (int)renderPos.y);

    //if(player_Jazz.state == EplayerState::Stand)
    //{
    //    rabbitMotion[(int)EplayerState::Stand]->Render(hdc, (int)pos.x, (int)renderPos.y, rabbitMotion[0]->GetCurrFrameX(), rabbitMotion[0]->GetCurrFrameY());
    //}
    //else if(player_Jazz.state == EplayerState::Walk)
    //{
    //    rabbitMotion[(int)EplayerState::Walk]->Render(hdc, (int)pos.x + 3, (int)renderPos.y, rabbitMotion[1]->GetCurrFrameX(), rabbitMotion[1]->GetCurrFrameY());
    //}
    //else if (player_Jazz.state == EplayerState::Run)
    //{
    //    rabbitMotion[(int)EplayerState::Run]->Render(hdc, (int)pos.x, (int)renderPos.y, rabbitMotion[2]->GetCurrFrameX(), rabbitMotion[2]->GetCurrFrameY());
    //}
    //else if (player_Jazz.state == EplayerState::Jump)
    //{
    //    rabbitMotion[(int)EplayerState::Jump]->Render(hdc, (int)pos.x, (int)renderPos.y, rabbitMotion[3]->GetCurrFrameX(), rabbitMotion[3]->GetCurrFrameY());
    //}
    rabbitMotion[(int)player_Jazz.state]->Render(hdc, 
                                                (int)pos.x + 3, (int)renderPos.y, 
                                                rabbitMotion[(int)player_Jazz.state]->GetCurrFrameX(), 
                                                rabbitMotion[(int)player_Jazz.state]->GetCurrFrameY());

    wsprintf(test, "캐릭터 상태 : %d", player_Jazz.state);
    TextOut(hdc, WIN_SIZE_X/2, 400, test, strlen(test));
}


void Player::Release()
{
}


void Player::inputAction()
{
    if (Input::GetButton(VK_LSHIFT))
    {
        inputShiftKey = true;
        moveSpeed = PLAYER_MOVE_SPEED * 2;
    }
    if (Input::GetButtonUp(VK_LSHIFT))
    {
        inputShiftKey = false;
        moveSpeed = PLAYER_MOVE_SPEED;
        InitMotion();
    }

    if (canMove)
    {
        if (Input::GetButton(VK_LEFT))
        {
            pos.x -= moveSpeed * Timer::GetDeltaTime();
            player_Jazz.frameY = 1;

            if(!inputShiftKey)player_Jazz.state = EplayerState::Walk;
            else if(inputShiftKey) player_Jazz.state = EplayerState::Run;

        }
        if (Input::GetButtonUp(VK_LEFT))
        {
            player_Jazz.state = EplayerState::Stand;
            InitMotion();
        }
        if (Input::GetButton(VK_RIGHT))
        {
            pos.x += moveSpeed * Timer::GetDeltaTime();
            player_Jazz.frameY = 0;

            if (!inputShiftKey)player_Jazz.state = EplayerState::Walk;
            else if (inputShiftKey) player_Jazz.state = EplayerState::Run;

        }
        if (Input::GetButtonUp(VK_RIGHT))
        {
            player_Jazz.state = EplayerState::Stand;
            InitMotion();
        }
    }

    if (Input::GetButtonDown(VK_DOWN))
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
    else if (Input::GetButtonUp(VK_DOWN))
    {
        stayGetDown = false;
    }

    if (Input::GetButton(VK_SPACE))
    {
        if (!quickDown)jumpKeyPressed = true;
    }
}

void Player::playerJump()
{
    if (!jumpKeyPressed) return;

    player_Jazz.state = EplayerState::Jump;

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
            player_Jazz.state = EplayerState::Stand;
        }
    }

    jumpHeight -= velocity * Timer::GetDeltaTime();
    velocity -= gravity * Timer::GetDeltaTime();
    
    renderPos.y = pos.y + jumpHeight;
}

void Player::quickDownAnimation()
{
    if (!quickDown) return;

    renderPos.y += 450 * Timer::GetDeltaTime();

    if (renderPos.y >= pos.y)
    {
        renderPos.y = pos.y;
        
        velocity = JUMP_VELOCITY;
        minVelocity = -JUMP_VELOCITY;
        jumpHeight = 0;
        canMove = true;
        quickDown = false;
    }
}

void Player::motionAnimator(int playerState,float waitingTime, float frameTerm, int maxFrameX)
{
    playerWatingTime += Timer::GetDeltaTime();

    if (playerWatingTime > waitingTime)
    {
        motionFrameTime += Timer::GetDeltaTime();
    }

    if (motionFrameTime > frameTerm)
    {
        ++player_Jazz.frameX;
        motionFrameTime = 0;
    }

    if (player_Jazz.frameX >= maxFrameX)
    {
        player_Jazz.frameX = 0;
        playerWatingTime = 0;
    }

    rabbitMotion[playerState]->SetCurrFrameX(player_Jazz.frameX);
    rabbitMotion[playerState]->SetCurrFrameY(player_Jazz.frameY);
}

void Player::InitMotion()
{
    playerWatingTime = 0;
    motionFrameTime = 0;
    player_Jazz.frameX = 0;
}


