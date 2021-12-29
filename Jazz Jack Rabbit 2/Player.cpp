#include "Player.h"
#include "Image.h"
#include "Ammo.h"


HRESULT Player::Init()
{
    rabbitMotion[(int)EplayerState::Stand] = ImageManager::GetSingleton()->FindImage("Image/character/jazz_stand.bmp");
    rabbitMotion[(int)EplayerState::Walk] = ImageManager::GetSingleton()->FindImage("Image/character/jazz_walk.bmp");
    rabbitMotion[(int)EplayerState::Run] = ImageManager::GetSingleton()->FindImage("Image/character/jazz_run.bmp");
    rabbitMotion[(int)EplayerState::Jump] = ImageManager::GetSingleton()->FindImage("Image/character/jump.bmp");
    rabbitMotion[(int)EplayerState::Rope] = ImageManager::GetSingleton()->FindImage("Image/character/rope.bmp");
    rabbitMotion[(int)EplayerState::Falling] = ImageManager::GetSingleton()->FindImage("Image/character/falling.bmp");
    rabbitMotion[(int)EplayerState::QuickDown] = ImageManager::GetSingleton()->FindImage("Image/character/quick_down.bmp");
    rabbitMotion[(int)EplayerState::UpperCut] = ImageManager::GetSingleton()->FindImage("Image/character/uppercut.bmp");

    collisionRect = ImageManager::GetSingleton()->FindImage("Image/character/collisionRect.bmp");

    if (rabbitMotion == nullptr)
    {
        cout << "로드 실패" << endl;
        return E_FAIL;
    }
    
    SetPlayerInfo(EplayerState::Falling, EmoveDir::Right);
    renderFrameX = 0;
    renderFrameY = 0;

    pos.x = WIN_SIZE_X/2;
    pos.y = WIN_SIZE_Y/2;

    renderPos.x = pos.x;
    renderPos.y = pos.y;

    //playerRect = new RECT;
    //playerRect->left = pos.x - 10;
    //playerRect->right = pos.x + 10;
    //playerRect->top = pos.y - 32;
    //playerRect->bottom = pos.y;

    fallingSpeed = 0;
    fallingMaxSpeed = 500;

    moveSpeed = PLAYER_MOVE_SPEED;
    jumpVelocity = JUMP_VELOCITY;
    gravity = GRAVITY;

    ammo = new Ammo[AMMO_PACK_COUNT];
    for (int i = 0; i < AMMO_PACK_COUNT; ++i)
    {
        ammo[i].Init();
    }

    return S_OK;
}

void Player::Update()
{
    inputAction();
    playerJump();
    freeFall();
    characterMotion();

    for (int i = 0; i < AMMO_PACK_COUNT; ++i)
    {

        ammo[i].Update();
    }
}

void Player::Render(HDC hdc)
{
    char test[128] = { 0 };

    collisionRect->Render(hdc, (int)renderPos.x, (int)renderPos.y - 16);

    if (playerState == EplayerState::Rope)  //귀로 매달리게
    {
        rabbitMotion[(int)playerState]->Render(hdc,
                                              (int)renderPos.x, (int)renderPos.y + 16,
                                              rabbitMotion[(int)playerState]->GetCurrFrameX(),
                                              rabbitMotion[(int)playerState]->GetCurrFrameY());
    }
    else
    {
        rabbitMotion[(int)playerState]->Render(hdc,
                                              (int)renderPos.x, (int)renderPos.y,
                                               rabbitMotion[(int)playerState]->GetCurrFrameX(),
                                               rabbitMotion[(int)playerState]->GetCurrFrameY());
    }

    for (int i = 0; i < AMMO_PACK_COUNT; ++i)
    {
        if (ammo[i].GetAlive())
        ammo[i].Render(hdc);
    }
}


void Player::Release()
{
    delete[] ammo;
    ammo = nullptr;
}


void Player::inputAction()  //플레이어 행동 입력
{
    unlockingCenterPlayer();

    if (Input::GetButton(VK_LSHIFT))
    {
        shiftKeyPressed = true;
        moveSpeed = PLAYER_MOVE_SPEED * 2;
    }
    if (Input::GetButtonUp(VK_LSHIFT))
    {
        shiftKeyPressed = false;
        moveSpeed = PLAYER_MOVE_SPEED;
        initMotionFrame();
    }

    if (canMove == true)
    {
        if (Input::GetButton(VK_LEFT))
        {
            moveKeyPressed = true;

            if (!collidedLeft)
            {
                pos.x -= moveSpeed * Timer::GetDeltaTime();
            }

            if (collideBottom)
            {
                if (!shiftKeyPressed)
                {
                    SetPlayerInfo(EplayerState::Walk, EmoveDir::Left);
                }
                else if (shiftKeyPressed)
                {
                    SetPlayerInfo(EplayerState::Run, EmoveDir::Left);
                }
            }
            else if (!collideBottom)
            {
                playerMoveDir = EmoveDir::Left;
            }
        }
        if (Input::GetButtonUp(VK_LEFT))
        {
            moveKeyPressed = false;

            if (collideBottom)
            {
                playerState = EplayerState::Stand;
            }
            initMotionFrame();
        }

        if (Input::GetButton(VK_RIGHT))
        {
            moveKeyPressed = true;

            if (!collidedRight)
            {
                pos.x += moveSpeed * Timer::GetDeltaTime();
            }

            if (collideBottom)
            {
                if (!shiftKeyPressed)
                {
                    SetPlayerInfo(EplayerState::Walk, EmoveDir::Right);
                }
                else if (shiftKeyPressed)
                {
                    SetPlayerInfo(EplayerState::Run, EmoveDir::Right);
                }
            }
            else if (!collideBottom)
            {
                playerMoveDir = EmoveDir::Right;
            }
        }
        if (Input::GetButtonUp(VK_RIGHT))
        {
            moveKeyPressed = false;
            if (collideBottom)
            {
                playerState = EplayerState::Stand;
            }
            initMotionFrame();
        }
    }

    if (Input::GetButtonDown(VK_DOWN))
    {
        initMotionFrame();

        if (playerState == EplayerState::Jump || playerState == EplayerState::Falling)
        {
            quickDownSwitch = true;
            jumpSwitch = false;
            canMove = false;
            stayGetDown = false;
        }
        if (playerState != EplayerState::Jump)
        {
            stayGetDown = true;

            if (collideRope)
            {
                playerState = EplayerState::Falling;
                collideRope = false;
                pos.y += 10;
            }
        }
    }
    else if (Input::GetButtonUp(VK_DOWN))
    {
        stayGetDown = false;
    }

    if (Input::GetButton(VK_SPACE))
    {
        stayJumpKeyTime += Timer::GetDeltaTime();

        if (collideBottom == true)
        {
            jumpSwitch = true;
            playerState = EplayerState::Jump;
        }
    }
    if (Input::GetButtonUp(VK_SPACE))
    {
        if (stayJumpKeyTime > 0.1 && playerState != EplayerState::UpperCut)
        {
            jumpSwitch = false;
            canfalling = true;
            jumpVelocity = JUMP_VELOCITY;
            stayJumpKeyTime = 0;
            initMotionFrame();
        }
    }

    if (Input::GetButtonDown(VK_LCONTROL))
    {
        fire();
    }

    //releaseLooking();

}

void Player::playerJump()
{
    if (!jumpSwitch) return;

    if (!upperCut)
    {
        playerState = EplayerState::Jump;
    }
    else if (upperCut)
    {
        playerState = EplayerState::UpperCut;
    }

    if (collideRope)    //점프 중 로프가 머리와 충돌
    {
        canMove = true;
        initJump();
        fallingSpeed = 0;
        playerState = EplayerState::Rope;
    }

    if (stayGetDown)    //아래 입력 후 점프 = jazz 특수공격
    {
        canMove = false;
        upperCut = true;
        jumpVelocity = JUMP_VELOCITY + 150;
        stayGetDown = false;
        playerState = EplayerState::UpperCut;
    }

    if (playerState == EplayerState::Jump || playerState == EplayerState::UpperCut)
    {
        if (jumpVelocity > 0)   //점프
        {
            pos.y -= jumpVelocity * Timer::GetDeltaTime();
            jumpVelocity -= gravity * Timer::GetDeltaTime();
        }

        if (jumpVelocity <= 0)  //점프높이 최대치
        {
            canMove = true;
            upperCut = false;
            initJump();
            initMotionFrame();
            playerState = EplayerState::Falling;
        }
        if (collideTop)     //점프 도중 머리 충돌
        {
            canMove = true;
            upperCut = false;
            initJump();
            fallingSpeed = 0;
            playerState = EplayerState::Falling;
        }
    }
}

void Player::initJump()
{
    jumpVelocity = JUMP_VELOCITY;
    jumpSwitch = false;
}

//자유낙하
void Player::freeFall()
{
    quickDown();

    if (quickDownSwitch) return;

    if (collideBottom || jumpSwitch || playerState == EplayerState::Rope)
    {
        canfalling = false;
        fallingSpeed = 0;
    }
    else canfalling = true;

    //자유낙하 가능
    if (canfalling)
    {
        fallingSpeed += gravity * Timer::GetDeltaTime();
        fallingSpeed = min(fallingSpeed, fallingMaxSpeed);

        pos.y += fallingSpeed * Timer::GetDeltaTime();
 
        playerState = EplayerState::Falling;
    }
    else if (!canfalling)
    {
        fallingSpeed = 0;

        if (!(playerState == EplayerState::Walk || playerState == EplayerState::Run || 
              playerState == EplayerState::Jump || playerState == EplayerState::Rope||
              playerState == EplayerState::UpperCut))
        {
            if (playerState != EplayerState::Stand)
            {
                initMotionFrame();
            }
            playerState = EplayerState::Stand;
        }
    }
}

void Player::quickDown()
{
    if (!quickDownSwitch ) return;

    quickDownWatingTime += Timer::GetDeltaTime();
    playerState = EplayerState::QuickDown;

    if (quickDownWatingTime > 0.5)
    {
        pos.y += 500 * Timer::GetDeltaTime();
    }

    if (collideBottom)
    {
        quickDownWatingTime = 0;
        jumpVelocity = JUMP_VELOCITY;
        canMove = true;
        jumpSwitch = false;
        canfalling = false;
        playerState = EplayerState::Stand;
        fallingSpeed = 0;
        quickDownSwitch = false;
        initMotionFrame();
    }
}

void Player::characterMotion()
{
    if (playerState == EplayerState::Stand)
    {
        motionAnimator((int)EplayerState::Stand, 2, 0.1f, 27);
    }
    else if (playerState == EplayerState::Walk)
    {
        motionAnimator((int)EplayerState::Walk, 0, 0.1f, 8);
    }
    else if (playerState == EplayerState::Run)
    {
        motionAnimator((int)EplayerState::Run, 0, 0.0f, 4);
    }
    else if (playerState == EplayerState::Jump)
    {
        jumpMotionAnimator((int)EplayerState::Jump, 0, 0.065f, 9);
    }
    else if (playerState == EplayerState::Rope)
    {
        ropeMotionAnimator((int)EplayerState::Rope, 0, 0.1f, 8);
    }
    else if (playerState == EplayerState::Falling)
    {
        jumpMotionAnimator((int)EplayerState::Falling, 0, 0.06f, 3);
    }
    else if (playerState == EplayerState::QuickDown)
    {
        motionAnimator((int)EplayerState::QuickDown, 0, 0.0f, 8);
    }
    else if (playerState == EplayerState::UpperCut)
    {
        motionAnimator((int)EplayerState::UpperCut, 0, 0.05f, 10);
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
        ++renderFrameX;
        motionFrameTime = 0;
    }

    if (renderFrameX >= maxFrameX)
    {
        renderFrameX = 0;
        playerWatingTime = 0;
    }

    if (playerMoveDir == EmoveDir::Right)
    {
        renderFrameY = 0;
    }
    else if (playerMoveDir == EmoveDir::Left)
    {
        renderFrameY = 1;
    }

    rabbitMotion[playerState]->SetCurrFrameX(renderFrameX);
    rabbitMotion[playerState]->SetCurrFrameY(renderFrameY);
}

void Player::jumpMotionAnimator(int playerState, float waitingTime, float frameTerm, int maxFrameX)
{
    playerWatingTime += Timer::GetDeltaTime();

    if (playerWatingTime > waitingTime)
    {
        motionFrameTime += Timer::GetDeltaTime();
    }

    if (motionFrameTime > frameTerm)
    {
        ++renderFrameX;
        motionFrameTime = 0;
    }

    if (renderFrameX >= maxFrameX)
    {
        renderFrameX = 0;
        playerWatingTime = 0;
    }

    if (moveKeyPressed  == true && playerMoveDir == EmoveDir::Left)
    {
        renderFrameY = 2;
    }
    else if (moveKeyPressed == true && playerMoveDir == EmoveDir::Right)
    {
        renderFrameY = 1;
    }
    else if(moveKeyPressed == false)
    {
        renderFrameY = 0;
    }

    rabbitMotion[playerState]->SetCurrFrameX(renderFrameX);
    rabbitMotion[playerState]->SetCurrFrameY(renderFrameY);
}

void Player::ropeMotionAnimator(int playerState, float waitingTime, float frameTerm, int maxFrameX)
{
    playerWatingTime += Timer::GetDeltaTime();

    if (playerWatingTime > waitingTime)
    {
        motionFrameTime += Timer::GetDeltaTime();
    }

    if (motionFrameTime > frameTerm)
    {
        ++renderFrameX;
        motionFrameTime = 0;
    }

    if (renderFrameX >= maxFrameX)
    {
        renderFrameX = 0;
        playerWatingTime = 0;
    }

    if (moveKeyPressed == false && playerMoveDir == EmoveDir::Right)
    {
        renderFrameY = 0;
    }
    if (moveKeyPressed == false && playerMoveDir == EmoveDir::Left)
    {
        renderFrameY = 1;
    }
    if (moveKeyPressed == true && playerMoveDir == EmoveDir::Right)
    {
        renderFrameY = 2;
    }
    if (moveKeyPressed == true && playerMoveDir == EmoveDir::Left)
    {
        renderFrameY = 3;
    }

    rabbitMotion[playerState]->SetCurrFrameX(renderFrameX);
    rabbitMotion[playerState]->SetCurrFrameY(renderFrameY);
}

//도중에 동작이 취소되었을 때 모션과 관련된 값 초기화
void Player::initMotionFrame()
{
    playerWatingTime = 0;
    motionFrameTime = 0;
    renderFrameX = 0;
}

void Player::fire()
{
    for (int i = 0; i < AMMO_PACK_COUNT; ++i)
    {
        if (ammo[i].GetIsFire() && ammo[i].GetAlive())
            continue;
        
            ammo[i].SetAlive(true);
            if (playerState == EplayerState::Rope)
            {
                ammo[i].SetPos(renderPos);
                ammo[i].SetPosY(renderPos.y + 10);
            }
            else
            {
                ammo[i].SetPos(renderPos);
            }
            ammo[i].SetAmmoDir(playerMoveDir);
            ammo[i].SetIsFire(true);
        
            break;
    }
    if (playerState == EplayerState::Stand)
    {
        //motionAnimator
    }
}

//맵 가장자리부분에서 캐릭터 화면 중앙고정 풀기

void Player::unlockingCenterPlayer()
{
    if (pos.x < WIN_SIZE_X / 2)
    {
        renderPos.x = pos.x;
    }
    else if (pos.x > ((TILE_COUNT_X * TILE_SIZE) - WIN_SIZE_X / 2))
    {
        renderPos.x = pos.x - (TILE_COUNT_X * TILE_SIZE) + WIN_SIZE_X;
    }
    else
    {
        renderPos.x = WIN_SIZE_X / 2;
    }

    if (pos.y < WIN_SIZE_Y / 2)
    {
        renderPos.y = pos.y;
    }
    else if (pos.y > ((TILE_COUNT_Y * TILE_SIZE) - WIN_SIZE_Y / 2))
    {
        renderPos.y = pos.y - (TILE_COUNT_Y * TILE_SIZE) + WIN_SIZE_Y;
    }
    else
    {
        renderPos.y = WIN_SIZE_Y / 2;
    }
    
}

//void Player::releaseLooking()
//{
//    if (!releasing) return;
//
//    if (lookUp == false)
//    {
//        renderPos.y += moveSpeed * Timer::GetDeltaTime();
//
//        if (renderPos.y > WIN_SIZE_Y / 2)
//        {
//            renderPos.y = WIN_SIZE_Y / 2;
//            releasing = false;
//        }
//    }
//    else if (lookUp == true)
//    {
//        renderPos.y -= moveSpeed * Timer::GetDeltaTime();
//
//        if (renderPos.y < WIN_SIZE_Y / 2)
//        {
//            renderPos.y = WIN_SIZE_Y / 2;
//            releasing = false;
//        }
//    }
//}

