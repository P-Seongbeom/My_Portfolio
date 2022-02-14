#include "PixelCollider.h"

void PixelCollider::PixelCollision(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{
    CollideLeft(hdc, object, pt, bodySizeX, bodySizeY, color);
    CollideRight(hdc, object, pt, bodySizeX, bodySizeY, color);
    CollideUpLeft(hdc, object, pt, bodySizeX, bodySizeY, color);
    CollideUpRight(hdc, object, pt, bodySizeX, bodySizeY, color);
    CollideDownLeft(hdc, object, pt, bodySizeX, bodySizeY, color);
    CollideDownCenter(hdc, object, pt, bodySizeX, bodySizeY, color);
    CollideDownRight(hdc, object, pt, bodySizeX, bodySizeY, color);
    GoUpStairs(hdc, object, pt, bodySizeX, bodySizeY, color);
}

void PixelCollider::CollideLeft(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{
    for (int i = 2; i < bodySizeY / 2; ++i)
    {
        if (checkPixel(hdc, (int)pt.x - bodySizeX / 2, (int)pt.y - bodySizeY / 2 - i, color) == false)
        {
            collidedLeft = true;
            object->SetLeftCollision(true);
            break;
        }
        else
        {
            collidedLeft = false;
            object->SetLeftCollision(false);
            break;
        }

        if (checkPixel(hdc, (int)pt.x - bodySizeX / 2 + 1, (int)pt.y - bodySizeY / 2 - i, color) == false)
        {
            collidedLeft = true;
            object->SetPosX(object->GetPos().x + 1);
            object->SetLeftCollision(true);
            break;
        }
        else
        {
            collidedLeft = false;
            object->SetLeftCollision(false);
            break;
        }
    }
}

void PixelCollider::CollideRight(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{
    for (int i = 2; i < bodySizeY / 2; ++i)
    {
    
        if (checkPixel(hdc, (int)pt.x + bodySizeX / 2, (int)pt.y - bodySizeY / 2 - i, color) == false)
        {
            collidedRight = true;
            object->SetRightCollision(true);
            break;
        }
        else
        {
            collidedRight = false;
            object->SetRightCollision(false);
            break;
        }
    
        if (checkPixel(hdc, (int)pt.x + bodySizeX / 2 - 1, (int)pt.y - bodySizeY / 2 - i, color) == false)
        {
            collidedRight = true;
            object->SetPosX(object->GetPos().x - 1);
            object->SetRightCollision(true);
            break;
        }
        else
        {
            collidedRight = false;
            object->SetRightCollision(false);
            break;
        }
    }
}

void PixelCollider::CollideUpLeft(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{
    for (int i = 3; i < bodySizeX / 2 + 1; ++i)
    {
        if (checkPixel(hdc, (int)pt.x - bodySizeX / 2 + i, (int)pt.y - bodySizeY, color) == false)
        {
            if (!(r == 34 && g == 177 && b == 76))//로프가 아닌 벽
            {
                collidedUpLeft = true;
                object->SetTopCollision(true);
                break;
            }
            else if (r == 34 && g == 177 && b == 76)//로프일때
            {
                collidedUpLeft = true;
                object->SetRopeCollision(true);
                break;
            }
        }
        else
        {
            collidedUpLeft = false;
            object->SetTopCollision(false);
        }
    }
}

void PixelCollider::CollideUpRight(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{

    for (int i = 3; i < bodySizeX / 2 + 1; ++i)
    {
        if (checkPixel(hdc, (int)pt.x + bodySizeX / 2 - i, (int)pt.y - bodySizeY, color) == false)
        {
            if (!(r == 34 && g == 177 && b == 76))//로프가 아닌 벽
            {
                collidedUpRight = true;
                object->SetTopCollision(true);
                break;
            }
            else if (r == 34 && g == 177 && b == 76)//로프일때
            {
                collidedUpRight = true;
                object->SetRopeCollision(true);
                break;
            }
        }
        else
        {
            collidedUpRight = false;

            if (collidedUpLeft == false)
            {
                object->SetTopCollision(false);
            }

        }
    }

}

void PixelCollider::CollideDownLeft(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{
    for (int i = 3; i < bodySizeX / 2 + 1; ++i)
    {
        if (checkPixel(hdc, (int)pt.x - bodySizeX / 2 + i, (int)pt.y, color) == false)
        {
            collidedDownLeft = true;

            if (collidedLeft == false && (r == 0 && g == 0 && b == 0))
            {
                object->SetBottomCollision(true);
            }
            else if (collidedLeft == false && (r == 237 && g == 28 && b == 36))
            {
                if (object->GetHittedState() == false)
                {
                    object->GetHit(true);
                }
                object->SetBottomCollision(true);
            }
            break;
        }
        else if (checkPixel(hdc, (int)pt.x - bodySizeX / 2 + i, (int)pt.y, color) == false && (r == 34 && g == 177 && b == 76))
        {
            collidedDownLeft = false;
            object->SetBottomCollision(false);
        }
        else
        {
            collidedDownLeft = false;

            object->SetBottomCollision(false);

        }
    }
}

void PixelCollider::CollideDownCenter(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{
    if (checkPixel(hdc, (int)pt.x, (int)pt.y, color) == false)
    {
        collidedDownCenter = true;
        if (object->GetjumpSwitch() == false && (r == 0 && g == 0 && b == 0))
        {
            object->SetBottomCollision(true);
        }

    }
    else if (checkPixel(hdc, (int)pt.x - bodySizeX / 2, (int)pt.y, color) == false && (r == 237 && g == 28 && b == 36))
    {
        collidedDownCenter = true;
        if (object->GetHittedState() == false)
        {
            object->GetHit(true);
        }
        object->SetBottomCollision(true);
    }
    else if (checkPixel(hdc, (int)pt.x - bodySizeX / 2, (int)pt.y, color) == false && (r == 34 && g == 177 && b == 76))
    {
        collidedDownCenter = false;

        if (collidedDownLeft == false)
        {
            object->SetBottomCollision(false);
        }
    }
    else
    {
        collidedDownCenter = false;
        if (collidedDownLeft == false)//좌측계단 오름시 낙하동작 방지
        {
            object->SetBottomCollision(false);
        }
    }
}

void PixelCollider::CollideDownRight(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{
    for (int i = 3; i < bodySizeX / 2 + 1; ++i)
    {
        if (checkPixel(hdc, (int)pt.x + bodySizeX/2 - i, (int)pt.y, color) == false)
        {
            collidedDownRight = true;
            if (collidedRight == false && (r == 0 && g == 0 && b == 0))
            {
                object->SetBottomCollision(true);
            }
            break;
        }
        else if (checkPixel(hdc, (int)pt.x - bodySizeX / 2 + i, (int)pt.y, color) == false && collidedRight == false && (r == 237 && g == 28 && b == 36))
        {
            collidedDownRight = true;
            if (object->GetHittedState() == false)
            {
                object->GetHit(true);
            }
            object->SetBottomCollision(true);
            break;
        }
        else if (checkPixel(hdc, (int)pt.x - bodySizeX / 2 + i, (int)pt.y, color) == false && (r == 34 && g == 177 && b == 76))
        {
            collidedDownRight = false;

            if (collidedDownLeft == false)
            {
                object->SetBottomCollision(false);
            }
        }
        else
        {
            collidedDownRight = false;

            if (collidedDownLeft == false)//좌측계단 오름시 낙하동작 방지
            {
                object->SetBottomCollision(false);
            }
        }
    }
}

void PixelCollider::GoUpStairs(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{
    if (collidedLeft == false && collidedDownCenter == true && collidedDownLeft == true)
    {
        for (int i = 3; i < 5; ++i)
        {
            if (checkPixel(hdc, (int)pt.x - bodySizeX / 2, (int)pt.y - i, RGB(0,0,0)) == true)
            {
                object->SetPosY(pt.y - object->GetMoveSpeed() * Timer::GetDeltaTime());
                break;
            }
        }
    }

    if (collidedRight == false && collidedDownCenter == true && collidedDownRight == true)
    {
        for (int i = 3; i < 5; ++i)
        {
            if (checkPixel(hdc, (int)pt.x + bodySizeX / 2, (int)pt.y - i, RGB(0, 0, 0)) == true)
            {
                object->SetPosY(pt.y - object->GetMoveSpeed() * Timer::GetDeltaTime());
                break;
            }
        }
    }
}

bool PixelCollider::checkPixel(HDC hdc, int pointX, int pointY, COLORREF color)
{
    pointCheckRGB = GetPixel(hdc, pointX, pointY);
    r = GetRValue(pointCheckRGB); g = GetGValue(pointCheckRGB); b = GetBValue(pointCheckRGB);

    if ((r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool PixelCollider::CollideAmmo(HDC hdc, GameObject object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{
    for (int i = 0; i < bodySizeY / 2; ++i)
    {
        if (checkPixel(hdc, (int)pt.x - bodySizeX / 2, (int)pt.y - bodySizeY / 2 - i, color) == false)
        {
            return true;
            break;
        }
        else
        {
            return false;
            break;
        }

        if (checkPixel(hdc, (int)pt.x - bodySizeX / 2 + 1, (int)pt.y - bodySizeY / 2 - i, color) == false)
        {
            return true;
            break;
        }
        else
        {
            return false;
            break;
        }
    }

    for (int i = 0; i < bodySizeY / 2; ++i)
    {

        if (checkPixel(hdc, (int)pt.x + bodySizeX / 2, (int)pt.y - bodySizeY / 2 - i, color) == false)
        {
            return true;
            break;
        }
        else
        {
            return false;
            break;
        }

        if (checkPixel(hdc, (int)pt.x + bodySizeX / 2 - 1, (int)pt.y - bodySizeY / 2 - i, color) == false)
        {
            return true;
            break;
        }
        else
        {
            return false;
            break;
        }
    }

    return false;
}