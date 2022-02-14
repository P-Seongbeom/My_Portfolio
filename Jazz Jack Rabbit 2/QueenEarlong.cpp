#include "QueenEarlong.h"
#include "Image.h"
#include "Player.h"

HRESULT QueenEarlong::Init()
{
	QueenMotion[(int)EQueenState::Idle] = ImageManager::GetSingleton()->FindImage("Image/enemy/boss/queen_idle.bmp");
	QueenMotion[(int)EQueenState::Shouting] = ImageManager::GetSingleton()->FindImage("Image/enemy/boss/queen_shouting.bmp");
	QueenMotion[(int)EQueenState::StompFoot] = ImageManager::GetSingleton()->FindImage("Image/enemy/boss/queen_stompfoot.bmp");
	QueenMotion[(int)EQueenState::Wobble] = ImageManager::GetSingleton()->FindImage("Image/enemy/boss/queen_wobble.bmp");
	QueenMotion[(int)EQueenState::Die] = ImageManager::GetSingleton()->FindImage("Image/enemy/boss/queen_die.bmp");

    QueensBrick = ImageManager::GetSingleton()->FindImage("Image/enemy/boss/queens_brick.bmp");

	queenState = EQueenState::Idle;

	pos.x = BOSS_POS_X;
	pos.y = BOSS_POS_Y;

    updateRect.left = (WIN_SIZE_X * 2) - (TILE_SIZE * 15);
    updateRect.top = (WIN_SIZE_Y * 2) - (TILE_SIZE * 15);
    updateRect.right = WIN_SIZE_X * 2;
    updateRect.bottom = WIN_SIZE_Y * 2;

	fallingSpeed = 0.0f;
	fallingMaxSpeed = 500.0f;

    brickFallingSpeed = 0.0f;
    brickFallingMaxSpeed = 500.0f;

    hp = 10;

	pushingDistance = 5;

	return S_OK;
}

void QueenEarlong::Update()
{
    if (canUpdate() == true)
    {
        action();

        dropBrick();

        shouting();

        getDamage();

        freeFall();

        queenCollisionRect.left = (LONG)(pos.x - 16);
        queenCollisionRect.right = (LONG)(pos.x + 16);
        queenCollisionRect.top = (LONG)(pos.y - 40);
        queenCollisionRect.bottom = (LONG)pos.y;

        brickCollisionRect.left = (LONG)(brickPos.x - 14);
        brickCollisionRect.right = (LONG)(brickPos.x + 14);
        brickCollisionRect.top = (LONG)(brickPos.y - 24);
        brickCollisionRect.bottom = (LONG)brickPos.y;
    }
}

void QueenEarlong::Render(HDC hdc)
{
    if (blinking == false)
    {
        QueenMotion[(int)queenState]->Render(hdc, (int)renderPos.x, (int)renderPos.y,
                                             QueenMotion[(int)queenState]->GetCurrFrameX(),
                                             QueenMotion[(int)queenState]->GetCurrFrameY());

    }

    QueensBrick->Render(hdc, (int)brickRenderPos.x, (int)brickRenderPos.y);
}

void QueenEarlong::Release()
{
}


void QueenEarlong::makeBrick()
{
    brickPos = playerPos;
    brickPos.y = playerPos.y - WIN_SIZE_Y / 2;
    brickFallingSpeed = 0.0f;
    makedBirck = true;
}

void QueenEarlong::dropBrick()
{
    if (makedBirck == false) return;

    brickFallingSpeed += GRAVITY * Timer::GetDeltaTime();
    brickFallingSpeed = min(brickFallingSpeed, brickFallingMaxSpeed);

    brickPos.y += brickFallingSpeed * Timer::GetDeltaTime();

    brickRenderPos.x = brickPos.x - playerPos.x + WIN_SIZE_X / 2;
    if (playerPos.x >= WIN_SIZE_X * 1.5)
    {
        brickRenderPos.x = brickPos.x - WIN_SIZE_X;
    }
    brickRenderPos.y = brickPos.y - playerPos.y + WIN_SIZE_Y / 2;

    RECT rect;
    RECT targetRect = target->GetCollisionRect();
    if (IntersectRect(&rect, &targetRect, &brickCollisionRect))
    {
        target->GetHit(true);
    }
}

void QueenEarlong::shouting()
{
    if (queenState != EQueenState::Shouting || target->GetIsCollidedLeft()) return;

    if (renderFrameX >= 2 && renderFrameX <= 4)
    {
        pushPlayerPos = target->GetPos().x - (PLAYER_MAX_SPEED * 0.8f * Timer::GetDeltaTime());
        target->SetPosX(pushPlayerPos);
    }
}

void QueenEarlong::randomStateSetting()
{
    queenState = (EQueenState)(rand() % 3);
}

void QueenEarlong::action()
{
    switch (queenState)
    {
    case EQueenState::Idle:
    {
        motionAnimator((int)queenState, 0.1f, 0, 9 ,9, 2.0f);
        randomMotionChange = true;
        break;
    }
    case EQueenState::Shouting:
    {
        motionAnimator((int)queenState, 0.1f, 2, 4, 8, 2.0f);

        randomMotionChange = true;
        break;
    }
    case EQueenState::StompFoot:
    {
        motionAnimator((int)queenState, 0.1f, 0, 9, 9, 1.0f);
        if (renderFrameX == 5)
        {
            makeBrick();
        }
        randomMotionChange = true;
        break;
    }
    case EQueenState::Wobble:
    {
        motionAnimator((int)queenState, 0.1f, 3, 11, 11, 5.0f);
        randomMotionChange = false;
        break;
    }
    case EQueenState::Die:
    {
        motionAnimator((int)queenState, 0.1f, 9, 11, 11, 5.0f);
        die();
        randomMotionChange = false;
        break;
    }
    }
}

void QueenEarlong::motionAnimator(int bossState, float frameTerm, int cycleMinFrameX, int cycleMaxFrameX, int maxFrameX, float playTime)
{
    motionFrameTime += Timer::GetDeltaTime();
    stateHoldingTime += Timer::GetDeltaTime();


    if (motionFrameTime > frameTerm)
    {
        ++renderFrameX;
        motionFrameTime = 0;
    }

    if (stateHoldingTime > playTime)
    {
        if (renderFrameX >= maxFrameX)
        {
            stateHoldingTime = 0;
            initMotionFrame();

            if (randomMotionChange)
            {
                randomStateSetting();
            }
            else if (queenState == EQueenState::Wobble)
            {
                queenState = EQueenState::Die;
            }
        }
    }
    else 
    {
        if (renderFrameX >= cycleMaxFrameX)
        {
            renderFrameX = cycleMinFrameX;
        }
    }


    QueenMotion[(int)queenState]->SetCurrFrameX(renderFrameX);
    QueenMotion[(int)queenState]->SetCurrFrameY(renderFrameY);
}

void QueenEarlong::initMotionFrame()
{
    motionFrameTime = 0;
    renderFrameX = 0;
}

void QueenEarlong::freeFall()
{
    if (collideBottom)
    {
        canfalling = false;
        fallingSpeed = 0;
    }
    else canfalling = true;

    if (canfalling)
    {
        fallingSpeed += GRAVITY * Timer::GetDeltaTime();
        fallingSpeed = min(fallingSpeed, fallingMaxSpeed);

        pos.y += fallingSpeed * Timer::GetDeltaTime();
    }
    else if (!canfalling)
    {
        fallingSpeed = 0;
    }
}

void QueenEarlong::getDamage()
{
    if (queenState == EQueenState::Idle 
        || queenState == EQueenState::Wobble 
        || queenState == EQueenState::Die) return;

    if (getHit && hp != 0)
    {
        --hp;
        getHit = false;
    }
    
    if (hp == 0 && pos.x < BOSS_DIE_POS_X)
    {
        hp = 10;
        pos.x += 10;
    }
    else if (hp == 0 && pos.x >= BOSS_DIE_POS_X)
    {
        queenState = EQueenState::Wobble;
    }
}

void QueenEarlong::die()
{
    pos.x += 1;
    renderPos.y += 1;
    blinkingTime += Timer::GetDeltaTime();
    deadTime += Timer::GetDeltaTime();

    if (blinkingTime > 0.1)
    {
        if (blinking == false)
        {
            blinking = true;
        }
        else
        {
            blinking = false;
        }
        blinkingTime = 0.0f;
    }

    if (deadTime > 7)
    {
        isDead = true;
    }
}

bool QueenEarlong::freeCameraMoveZone(RECT* zone, POINTFLOAT ptf)
{
    if (zone->left <= ptf.x && zone->right >= ptf.x && zone->top <= ptf.y && zone->bottom >= ptf.y)
    {
        return true;
    }

    return false;
}

bool QueenEarlong::canUpdate()
{
    if (updateRect.left <= playerPos.x && updateRect.right >= playerPos.x && updateRect.top <= playerPos.y && updateRect.bottom >= playerPos.y)
    {
        return true;
    }
    return false;
}

void QueenEarlong::SetTarget(Player* player)
{
    target = player;
}

void QueenEarlong::SetRenderPos(POINTFLOAT pos1, POINTFLOAT pos2, RECT* zone1, RECT* zone2)
{
    playerPos = pos2;

    if (freeCameraMoveZone(zone1, pos2))
    {
        this->renderPos.x = pos1.x - pos2.x + WIN_SIZE_X / 2;
        //brickRenderPos.x = brickPos.x - playerPos.x + WIN_SIZE_X / 2;
    }

    if (pos2.x <= WIN_SIZE_X / 2)
    {
        this->renderPos.x = pos1.x;
        //brickRenderPos.x = brickPos.x;
    }
    else if (pos2.x >= WIN_SIZE_X * 1.5)
    {
        this->renderPos.x = pos1.x - WIN_SIZE_X;
        //brickRenderPos.x = brickPos.x - WIN_SIZE_X;
    }

    if (freeCameraMoveZone(zone2, pos2))
    {
        this->renderPos.y = pos1.y - pos2.y + WIN_SIZE_Y / 2;
        //brickRenderPos.y = brickPos.y - playerPos.y + WIN_SIZE_Y / 2;
    }
}