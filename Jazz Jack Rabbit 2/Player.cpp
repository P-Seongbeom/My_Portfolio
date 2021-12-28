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

    collisionRect = ImageManager::GetSingleton()->FindImage("Image/character/collisionRect.bmp");

    if (rabbitMotion == nullptr)
    {
        cout << "로드 실패" << endl;
        return E_FAIL;
    }
    
    SetPlayerInfo(EplayerState::Falling, EmoveDir::Right);
    renderFrameX = 0;
    renderFrameY = 0;

    //플레이어의 위치값 x : 캐릭터 중앙
    //플레이어의 위치값 y : 캐릭터 발밑
    pos.x = WIN_SIZE_X/2;
    pos.y = WIN_SIZE_Y/2;

    renderPos.x = pos.x;
    renderPos.y = pos.y;

    playerRect = new RECT;
    playerRect->left = pos.x - 10;
    playerRect->right = pos.x + 10;
    playerRect->top = pos.y - 32;
    playerRect->bottom = pos.y;

    fallingSpeed = 1;
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
        jumpMotionAnimator((int)EplayerState::Jump, 0, 0.065f , 9);
    }
    else if (playerState == EplayerState::Rope)
    {
        ropeMotionAnimator((int)EplayerState::Rope, 0, 0.1f, 8);
    }
    else if (playerState == EplayerState::Falling)
    {
        jumpMotionAnimator((int)EplayerState::Falling, 0, 0.06f, 3);
    }

    quickDown();
    freeFall();


    for (int i = 0; i < AMMO_PACK_COUNT; ++i)
    {

        ammo[i].Update();
    }


    //cout << "posx : " << pos.x << endl;
    //cout << "redposx : " << renderPos.x << endl;
    //cout << "posy : " << pos.y << endl;
    //cout << "redposy : " << renderPos.y << endl;
    ////cout << endOfVertical << endl;
    //cout << canfalling << endl;
    //cout << "점프속도 : " << velocity << endl;
    //cout << "점프 키 : " << jumpKeyPressed << endl;
    //cout << " fallingspeed : " << fallingSpeed << endl;
    //cout << "무브키 : " << moveKeyPressed << endl;
    //if(playerState == EplayerState::Rope)
    cout << "상태 : " << (int)playerState << endl;
    //cout << "속도 : " << moveSpeed << endl;
    //cout << playerRect->bottom << endl;
}

void Player::Render(HDC hdc)
{
    char test[128] = { 0 };

    collisionRect->Render(hdc, (int)renderPos.x, (int)renderPos.y - 16);
    //collisionRect->Render(hdc, (int)pos.x, (int)pos.y);
    if (playerState == EplayerState::Rope)
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


    //wsprintf(test, "캐릭터 상태 : %d", playerState);
    //TextOut(hdc, WIN_SIZE_X/2, 450, test, strlen(test));
}


void Player::Release()
{
}


void Player::inputAction()
{
    //if (!stayKeyDownTime && !releasing)
    if(!stayKeyDownTime)
        unlockingCenterPlayer();

    if (Input::GetButton(VK_LSHIFT))
    {
        inputShiftKey = true;
        moveSpeed = PLAYER_MOVE_SPEED * 2;
    }
    if (Input::GetButtonUp(VK_LSHIFT))
    {
        inputShiftKey = false;
        moveSpeed = PLAYER_MOVE_SPEED;
        initMotionFrame();
    }

    if (canMove)
    {
        if (Input::GetButton(VK_LEFT))
        {
            moveKeyPressed = true;
            if(collidedLeft == false)
            pos.x -= moveSpeed * Timer::GetDeltaTime();

            if (!(playerState == EplayerState::Jump || playerState == EplayerState::Rope))
            {
                if(!inputShiftKey && !canfalling)
                    SetPlayerInfo(EplayerState::Walk, EmoveDir::Left);
                else if(inputShiftKey && !canfalling) 
                    SetPlayerInfo(EplayerState::Run, EmoveDir::Left);
            }
            else if (playerState == EplayerState::Jump || playerState == EplayerState::Rope || playerState == EplayerState::Falling)
            {
                playerMoveDir = EmoveDir::Left;
            }
        }
        if (Input::GetButtonUp(VK_LEFT))
        {
            moveKeyPressed = false;
            if (!canfalling)
            {
                if (playerState != EplayerState::Rope)
                {
                    playerState = EplayerState::Stand;
                }
            }
            initMotionFrame();
        }

        if (Input::GetButton(VK_RIGHT))
        {
            moveKeyPressed = true;
            if(collidedRight == false)
            pos.x += moveSpeed * Timer::GetDeltaTime();

            if (!(playerState == EplayerState::Jump || playerState == EplayerState::Rope))
            {
                if (!inputShiftKey && !canfalling)
                    SetPlayerInfo(EplayerState::Walk, EmoveDir::Right);
                else if (inputShiftKey && !canfalling)
                    SetPlayerInfo(EplayerState::Run, EmoveDir::Right);
            }
            else if (playerState == EplayerState::Jump || playerState == EplayerState::Rope || playerState == EplayerState::Falling)
            {
                playerMoveDir = EmoveDir::Right;
            }
            //else if (canfalling)
            //{
            //    SetPlayerInfo(EplayerState::Falling, EmoveDir::Right);
            //}

        }
        if (Input::GetButtonUp(VK_RIGHT))
        {
            moveKeyPressed = false;
            if (!canfalling)
            {
                if (playerState != EplayerState::Rope)
                {
                    playerState = EplayerState::Stand;
                }
            }
            initMotionFrame();
        }
    }

    if (Input::GetButtonDown(VK_DOWN))
    {
        initMotionFrame();
        if (!jumpKeyPressed)
        {
            stayGetDown = true;
            collideTop = false;
            if (collideRope)
            {
                playerState = EplayerState::Falling;
                collideRope = false;
                pos.y += 10;
            }
        }
        if (playerState == EplayerState::Jump || playerState == EplayerState::Falling)
        {
            cout << "아래키------------" << endl;
            jumpKeyPressed = false;
            stayGetDown = false;
            quickDownState = true;
            canMove = false;
        }
    }
    else if (Input::GetButtonUp(VK_DOWN))
    {
        //canMove = true;
        stayGetDown = false;
        //releasing = true;
        stayKeyDownTime = 0;
    }

    //if (Input::GetButtonUp(VK_UP))
    //{
    //    canMove = true;
    //    stayGetDown = false;
    //    //releasing = true;
    //    stayKeyDownTime = 0;
    //}

    if (Input::GetButton(VK_SPACE))
    {
        if (!quickDownState && !jumpKeyPressed && (collideBottom))
        {
            jumpKeyPressed = true;
            playerState = EplayerState::Jump;
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
    if (!jumpKeyPressed) return;

    playerState = EplayerState::Jump;

    if (collideRope)
    {
        cout << "로프" << endl;
        //cout << "충돌!!!!!!" << endl;
        canMove = true;
        jumpVelocity = JUMP_VELOCITY;
        jumpKeyPressed = false;
        //canfalling = true;
        playerState = EplayerState::Rope;
        fallingSpeed = 0;
    }

    if (playerState == EplayerState::Jump)
    {
        if (jumpVelocity > 0)
        {
            canfalling = false;
            pos.y -= jumpVelocity * Timer::GetDeltaTime();
            jumpVelocity -= gravity * Timer::GetDeltaTime();
        }

        if (stayGetDown)    //아래 입력 후 점프 = 특수공격
        {
            jumpVelocity = JUMP_VELOCITY + 150;
            canMove = false;
            stayGetDown = false;
        }

        if (jumpVelocity <= 0)
        {
            canfalling = true;
            canMove = true;
            jumpKeyPressed = false;
            playerState = EplayerState::Falling;
            initMotionFrame();
            jumpVelocity = JUMP_VELOCITY;
        }
        if (collideTop)
        {
            cout << "낙하시작" << endl;
            //cout << "충돌!!!!!!" << endl;
            canMove = true;
            jumpVelocity = JUMP_VELOCITY;
            jumpKeyPressed = false;
            canfalling = true;
            playerState = EplayerState::Falling;
            fallingSpeed = 0;
        }
    }

    
    t += Timer::GetDeltaTime();
    //cout << pos.y << endl;
    //cout << "상태 : " << (int)playerState << endl;
    //cout << "낙하 속도 : " << fallingSpeed << endl;
    //cout << velocity << endl;
    //cout << t << endl;
    //cout << canMove << endl << endl;
}

void Player::freeFall()
{
    if (quickDownState) return;

    if (collideBottom || jumpKeyPressed || playerState == EplayerState::Rope)
    {
        canfalling = false;
        fallingSpeed = 0;
    }
    else canfalling = true;

    if (collideTop)
    {
        canfalling = true;
        collideTop = false;
    }

    if (collideRope)
    {
        fallingSpeed = 0;
        canMove = true;
    }

    if (canfalling)
    {
        //cout << "낙하" << endl;
        playerState = EplayerState::Falling;

        fallingSpeed += gravity * Timer::GetDeltaTime();
        fallingSpeed = min(fallingSpeed, fallingMaxSpeed);

        pos.y += fallingSpeed * Timer::GetDeltaTime();
 
        //checkCollsion = false;
    }
    else if (!canfalling)
    {
        //cout << "바꿈~~~" << endl;
        fallingSpeed = 0;
        if (!(playerState == EplayerState::Walk || playerState == EplayerState::Run || playerState == EplayerState::Jump || playerState == EplayerState::Rope))
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
    if (!quickDownState) return;

    quickDownWatingTime += Timer::GetDeltaTime();
    playerState = EplayerState::QuickDown;

    if (quickDownWatingTime > 0.5)
    {
        pos.y += 400 * Timer::GetDeltaTime();
    }

    if (collideBottom)
    {
        cout << "-------" << endl;
        //cout << "충돌!!!!!!" << endl;
        quickDownWatingTime = 0;
        jumpVelocity = JUMP_VELOCITY;
        canMove = true;
        jumpKeyPressed = false;
        canfalling = false;
        playerState = EplayerState::Stand;
        fallingSpeed = 0;
        quickDownState = false;
        initMotionFrame();
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
    if (moveKeyPressed == true && playerMoveDir == EmoveDir::Right)
    {
        renderFrameY = 1;
    }
    if(moveKeyPressed == false)
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
            ammo[i].SetPos(renderPos);
            ammo[i].SetAmmoDir(playerMoveDir);
            ammo[i].SetIsFire(true);
        
            break;
    }
    if (playerState == EplayerState::Stand)
    {
        //motionAnimator
    }
}

void Player::unlockingCenterPlayer()
{
    if (pos.x < WIN_SIZE_X / 2)
    {
        renderPos.x = pos.x;
        endOfHorizontal = true;
    }
    else if (pos.x > ((TILE_COUNT_X * TILE_SIZE) - WIN_SIZE_X / 2))
    {
        renderPos.x = pos.x - (TILE_COUNT_X * TILE_SIZE) + WIN_SIZE_X;
        endOfHorizontal = true;
    }
    else
    {
        renderPos.x = WIN_SIZE_X / 2;
        endOfHorizontal = false;
    }

    if (pos.y < WIN_SIZE_Y / 2)
    {
        renderPos.y = pos.y;
        endOfVertical = true;
    }
    else if (pos.y > ((TILE_COUNT_Y * TILE_SIZE) - WIN_SIZE_Y / 2))
    {
        renderPos.y = pos.y - (TILE_COUNT_Y * TILE_SIZE) + WIN_SIZE_Y;
        endOfVertical = true;
    }
    else
    {
        renderPos.y = WIN_SIZE_Y / 2;
        endOfVertical = false;
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

