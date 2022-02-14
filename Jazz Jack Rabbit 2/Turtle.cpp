#include "Turtle.h"
#include "Image.h"

HRESULT Turtle::Init()
{
    turtleMotion[(int)EturtleState::Walk] = ImageManager::GetSingleton()->FindImage("Image/enemy/turtle/turtlegoon_walk.bmp");
    turtleMotion[(int)EturtleState::Hide] = ImageManager::GetSingleton()->FindImage("Image/enemy/turtle/turtlegoon_hide.bmp");
    turtleMotion[(int)EturtleState::Die] = ImageManager::GetSingleton()->FindImage("Image/enemy/turtle/turtlegoon_die.bmp");

    pos.x = WIN_SIZE_X / 2;
    pos.y = WIN_SIZE_Y * 1.5f;

    turtleState = EturtleState::Walk;
    turtleMoveDir = EmoveDir::Right;

    moveSpeed = TURTLE_MOVE_SPEED;

    fallingSpeed = 0.0f;
    fallingMaxSpeed = 500.0f;

    hp = 1;

    return S_OK;
}

void Turtle::Update()
{
    getDamage();
    die();
    action();
    freeFall();
}

void Turtle::Render(HDC hdc)
{
    turtleMotion[(int)turtleState]->Render(hdc, (int)renderPos.x, (int)renderPos.y + 5,
                                            turtleMotion[(int)turtleState]->GetCurrFrameX(), 
                                            turtleMotion[(int)turtleState]->GetCurrFrameY());
}

void Turtle::Release()
{
}


void Turtle::action()
{
    switch (turtleState)
    {
    case EturtleState::Walk:
    {
        moveTimer += Timer::GetDeltaTime();

        collisionRect.left = (LONG)(pos.x - 16);
        collisionRect.right = (LONG)(pos.x + 16);
        collisionRect.top = (LONG)(pos.y - 32);
        collisionRect.bottom = (LONG)pos.y;

        if (turtleMoveDir == EmoveDir::Right)
        {
            pos.x += moveSpeed * Timer::GetDeltaTime();

            walkingMotion(0.1f, 12);

            if (moveTimer > 2)
            {
                initMotionFrame();
                turtleState = EturtleState::Hide;
                stickOutHead = false;
                motionChange = false;
            }
        }
        else if(turtleMoveDir == EmoveDir::Left)
        {
            pos.x -= moveSpeed * Timer::GetDeltaTime();

            walkingMotion(0.1f, 12);

            if (moveTimer > 2)
            {
                initMotionFrame();
                turtleState = EturtleState::Hide;
                stickOutHead = false;
                motionChange = false;
            }
        }
        break;
    }
    case EturtleState::Hide:
    {
        collisionRect.left = (LONG)(pos.x - 16);
        collisionRect.right = (LONG)(pos.x + 16);
        collisionRect.top = (LONG)(pos.y - 16);
        collisionRect.bottom = (LONG)pos.y;

        hidingMotion(0.1f, 12);

        if (motionChange)
        {
            turtleState = EturtleState::Walk;

            if (turtleMoveDir == EmoveDir::Right && renderFrameY != 1)
            {
                turtleMoveDir = EmoveDir::Left;
            }
            else if (turtleMoveDir == EmoveDir::Left && renderFrameY != 3)
            {
                turtleMoveDir = EmoveDir::Right;
            }
            motionChange = false;
        }
        break;
    }
    case EturtleState::Die:
    {
        collisionRect.left = (LONG)(pos.x - 16);
        collisionRect.right = (LONG)(pos.x + 16);
        collisionRect.top = (LONG)(pos.y - 16);
        collisionRect.bottom = (LONG)pos.y;

        deadMotion();
        break;
    }
    }
}

void Turtle::walkingMotion(float frameTerm, int maxFrameX)
{
    motionFrameTime += Timer::GetDeltaTime();

    if (motionFrameTime > frameTerm)
    {
        ++renderFrameX;
        motionFrameTime = 0;
    }

    if (renderFrameX >= maxFrameX)
    {
        renderFrameX = 0;
    }

    if (turtleMoveDir == EmoveDir::Right)
    {
        renderFrameY = 0;
    }
    else if (turtleMoveDir == EmoveDir::Left)
    {
        renderFrameY = 1;
    }

    turtleMotion[(int)turtleState]->SetCurrFrameX(renderFrameX);
    turtleMotion[(int)turtleState]->SetCurrFrameY(renderFrameY);
}

void Turtle::hidingMotion(float frameTerm, int maxFrameX)
{
    motionFrameTime += Timer::GetDeltaTime();

    if (motionFrameTime > frameTerm)
    {
        ++renderFrameX;
        motionFrameTime = 0;
    }

    if (renderFrameX >= maxFrameX)
    {
        if (stickOutHead == false)
        {
            stickOutHead = true;
        }
        else
        {
            motionChange = true;
        }

        if (stickOutHead)
        {
            if (turtleMoveDir == EmoveDir::Right && renderFrameY != 1)
            {
                turtleMoveDir = EmoveDir::Left;
            }
            else if (turtleMoveDir == EmoveDir::Left && renderFrameY != 3)
            {
                turtleMoveDir = EmoveDir::Right;
            }
        }

        renderFrameX = 0;
    }

    if (turtleMoveDir == EmoveDir::Right)
    {
        if (stickOutHead)
        {
            renderFrameY = 1;
        }
        else if (!stickOutHead)
        {
            renderFrameY = 0;
        }
    }
    else if (turtleMoveDir == EmoveDir::Left)
    {
        if (stickOutHead)
        {
            renderFrameY = 3;
        }
        else if (!stickOutHead)
        {
            renderFrameY = 2;
        }
    }

    turtleMotion[(int)turtleState]->SetCurrFrameX(renderFrameX);
    turtleMotion[(int)turtleState]->SetCurrFrameY(renderFrameY);
    turtleMotion[(int)EturtleState::Walk]->SetCurrFrameX(renderFrameX);
    turtleMotion[(int)EturtleState::Walk]->SetCurrFrameY(renderFrameY/2);
}

void Turtle::deadMotion()
{
    renderFrameX = 0;
    renderFrameY = 0;

    turtleMotion[(int)turtleState]->SetCurrFrameX(renderFrameX);
    turtleMotion[(int)turtleState]->SetCurrFrameY(renderFrameY);
}

void Turtle::initMotionFrame()
{
    moveTimer = 0;
    motionFrameTime = 0;
    renderFrameX = 0;
}

void Turtle::freeFall()
{
    if (collideBottom || jumpSwitch)
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
    else if(!canfalling)
    {
        fallingSpeed = 0;
    }
}

void Turtle::getDamage()
{
    if (getHit && hp != 0)
    {
        --hp;
        getHit = false;
    }
}

void Turtle::die()
{
    if (hp == 0)
    {
        turtleState = EturtleState::Die;
    }
}

bool Turtle::freeCameraMoveZone(RECT* zone, POINTFLOAT ptf)
{
    if (zone->left <= ptf.x && zone->right >= ptf.x && zone->top <= ptf.y && zone->bottom >= ptf.y)
    {
        return true;
    }

    return false;
}

void Turtle::SetRenderPos(POINTFLOAT pos1, POINTFLOAT pos2, RECT* zone1, RECT* zone2)
{
    if (freeCameraMoveZone(zone1, pos2))
    {
        this->renderPos.x = pos1.x - pos2.x + WIN_SIZE_X / 2;
    }

    if (pos2.x <= WIN_SIZE_X / 2)
    {
        this->renderPos.x = pos1.x;
    }
    else if (pos2.x >= WIN_SIZE_X * 1.5)
    {
        this->renderPos.x = pos1.x - WIN_SIZE_X;
    }

    if (freeCameraMoveZone(zone2, pos2))
    {
        this->renderPos.y = pos1.y - pos2.y + WIN_SIZE_Y / 2;
    }
}