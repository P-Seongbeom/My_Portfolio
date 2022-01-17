#include "Turtle.h"
#include "Image.h"

HRESULT Turtle::Init()
{
    turtleMotion[(int)EturtleState::Walk] = ImageManager::GetSingleton()->FindImage("Image/enemy/turtlegoon_walk.bmp");
    turtleMotion[(int)EturtleState::Hide] = ImageManager::GetSingleton()->FindImage("Image/enemy/turtlegoon_hide.bmp");

    pos.x = WIN_SIZE_X / 2;
    //pos.y = WIN_SIZE_Y * 1.5f;
    pos.y = WIN_SIZE_Y / 2;

    turtleState = EturtleState::Walk;
    turtleMoveDir = EmoveDir::Right;

    moveSpeed = TURTLE_MOVE_SPEED;

    return S_OK;
}

void Turtle::Update()
{
    action();
}

void Turtle::Render(HDC hdc)
{
    turtleMotion[(int)turtleState]->Render(hdc, pos.x, pos.y, 
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

bool Turtle::updateZone(RECT* zone, POINTFLOAT ptf)
{
    if (zone->left <= ptf.x && zone->right >= ptf.x && zone->top <= ptf.y && zone->bottom >= ptf.y)
    {
        return true;
    }

    return false;
}

void Turtle::initMotionFrame()
{
    moveTimer = 0;
    motionFrameTime = 0;
    renderFrameX = 0;
}