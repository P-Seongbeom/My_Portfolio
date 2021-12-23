#include "Player.h"
#include "Image.h"
#include "Ammo.h"


HRESULT Player::Init()
{
    rabbitMotion[(int)EplayerState::Stand] = ImageManager::GetSingleton()->FindImage("Image/character/jazz_stand.bmp");
    rabbitMotion[(int)EplayerState::Walk] = ImageManager::GetSingleton()->FindImage("Image/character/jazz_walk.bmp");
    rabbitMotion[(int)EplayerState::Run] = ImageManager::GetSingleton()->FindImage("Image/character/jazz_run.bmp");
    rabbitMotion[(int)EplayerState::Jump] = ImageManager::GetSingleton()->FindImage("Image/character/jump.bmp");

    if (rabbitMotion == nullptr)
    {
        cout << "�ε� ����" << endl;
        return E_FAIL;
    }
    
    SetPlayerInfo(EplayerState::Stand, EmoveDir::Right);
    renderFrameX = 0;
    renderFrameY = 0;

    pos.x = WIN_SIZE_X/2;
    pos.y = WIN_SIZE_Y/2;

    renderPos.y = pos.y;

    moveSpeed = PLAYER_MOVE_SPEED;
    velocity = JUMP_VELOCITY;
    minVelocity = -JUMP_VELOCITY;
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

    if (playerState == EplayerState::Stand)
    {
        motionAnimator((int)EplayerState::Stand, 2, (float)0.1, 27);
    }
    else if (playerState == EplayerState::Walk)
    {
        motionAnimator((int)EplayerState::Walk, 0, (float)0.1, 8);
    }
    else if (playerState == EplayerState::Run)
    {
        motionAnimator((int)EplayerState::Run, 0, (float)0, 4);
    }

    playerJump();
    
    quickDownAnimation();

    for (int i = 0; i < AMMO_PACK_COUNT; ++i)
    {

        ammo[i].Update();
    }

    if (pos.x < WIN_SIZE_X / 2 || pos.x > ((TILE_COUNT_X * TILE_SIZE) - WIN_SIZE_X/2))
    {
        renderPos.x = pos.x;
        endOfHorizontal = true;
    }
    else
    {
        renderPos.x = WIN_SIZE_X / 2;
        endOfHorizontal = false;
    }
    cout << "posx : " << pos.x << endl;
    cout << "posy : " << pos.y << endl;
}

void Player::Render(HDC hdc)
{
    char test[128] = { 0 };

    Rectangle(hdc, (int)renderPos.x - 10, (int)renderPos.y - 32, (int)renderPos.x + 10, (int)renderPos.y);

    rabbitMotion[(int)playerState]->Render(hdc,
                                         renderPos.x, renderPos.y,
                                          rabbitMotion[(int)playerState]->GetCurrFrameX(),
                                          rabbitMotion[(int)playerState]->GetCurrFrameY());
    //rabbitMotion[(int)playerState]->Render(hdc,
    //                                      renderPos.x, renderPos.y,
    //                                      rabbitMotion[(int)playerState]->GetCurrFrameX(),
    //                                       rabbitMotion[(int)playerState]->GetCurrFrameY());

    for (int i = 0; i < AMMO_PACK_COUNT; ++i)
    {
        if (ammo[i].GetAlive())
        ammo[i].Render(hdc);
    }

    //wsprintf(test, "ĳ���� ���� : %d", playerState);
    //TextOut(hdc, WIN_SIZE_X/2, 450, test, strlen(test));
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
        initMotion();
    }

    if (canMove)
    {
        if (Input::GetButton(VK_LEFT))
        {
            pos.x -= moveSpeed * Timer::GetDeltaTime();
            //renderFrameY = 1;

            if(!inputShiftKey)SetPlayerInfo(EplayerState::Walk, EmoveDir::Left);
            else if(inputShiftKey) SetPlayerInfo(EplayerState::Run, EmoveDir::Left);

        }
        if (Input::GetButtonUp(VK_LEFT))
        {
            playerState = EplayerState::Stand;
            initMotion();
        }

        if (Input::GetButton(VK_RIGHT))
        {
            pos.x += moveSpeed * Timer::GetDeltaTime();

            if (!inputShiftKey)SetPlayerInfo(EplayerState::Walk, EmoveDir::Right);
            else if (inputShiftKey) SetPlayerInfo(EplayerState::Run, EmoveDir::Right);

        }
        if (Input::GetButtonUp(VK_RIGHT))
        {
            playerState = EplayerState::Stand;
            initMotion();
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

    if (Input::GetButtonDown(VK_LCONTROL))
    {
        fire();
    }
}

void Player::playerJump()
{
    if (!jumpKeyPressed) return;

    playerState = EplayerState::Jump;

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
            playerState = EplayerState::Stand;
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

void Player::initMotion()
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

}

