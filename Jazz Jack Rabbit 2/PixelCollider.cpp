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

//#include "GameObject.h"
//
//void PixelCollider::PixelCollision(HDC hdc, int checkPosX, int checkPosY, COLORREF color)
//{
//    COLORREF leftRGB, rightRGB, topRGB, bottomRGB, stairsRGB;
//    WORD r, g, b;
//
//    //��
//    for (int i = 2; i < 16; ++i)
//    {
//        //�ֿܰ�
//        leftRGB = GetPixel(hdc, checkPosX - 10, checkPosY - 16 - i);
//        r = GetRValue(leftRGB); g = GetGValue(leftRGB); b = GetBValue(leftRGB);
//
//        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
//        {
//            collidedLeft = true;
//            player->SetLeftCollision(true);
//            break;
//        }
//        else
//        {
//            collidedLeft = false;
//            player->SetLeftCollision(false);
//            break;
//        }
//        //����
//        leftRGB = GetPixel(hdc, checkPosX + 1 - 10, checkPosY - 16 - i);
//        r = GetRValue(leftRGB); g = GetGValue(leftRGB); b = GetBValue(leftRGB);
//
//        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
//        {
//            collidedLeft = true;
//            player->SetPosX(player->GetPos().x + 1);
//            player->SetLeftCollision(true);
//            break;
//        }
//        else
//        {
//            collidedLeft = false;
//            player->SetLeftCollision(false);
//            break;
//        }
//    }
//
//    //��
//    for (int i = 2; i < 16; ++i)
//    {
//        //�ֿܰ�
//        rightRGB = GetPixel(hdc, checkPosX + 10, checkPosY - 16 - i);
//        r = GetRValue(rightRGB); g = GetGValue(rightRGB); b = GetBValue(rightRGB);
//
//        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
//        {
//            collidedRight = true;
//            player->SetRightCollision(true);
//            break;
//        }
//        else
//        {
//            collidedRight = false;
//            player->SetRightCollision(false);
//            break;
//        }
//        //����
//        rightRGB = GetPixel(hdc, checkPosX - 1 + 10, checkPosY - 16 - i);
//        r = GetRValue(rightRGB); g = GetGValue(rightRGB); b = GetBValue(rightRGB);
//
//        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
//        {
//            collidedRight = true;
//            player->SetPosX(player->GetPos().x - 1);
//            player->SetRightCollision(true);
//            break;
//        }
//        else
//        {
//            collidedRight = false;
//            player->SetRightCollision(false);
//            break;
//        }
//    }
//
//    //��(����)
//    for (int i = 3; i < 11; ++i)
//    {
//        topRGB = GetPixel(hdc, checkPosX - 10 + i, checkPosY - 32);
//        r = GetRValue(topRGB); g = GetGValue(topRGB); b = GetBValue(topRGB);
//        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
//        {
//            if (!(r == 34 && g == 177 && b == 76))//������ �ƴ� ��
//            {
//                collidedTopL = true;
//                player->SetTopCollision(true);
//                cout << " �޸Ӹ� " << endl;
//                break;
//            }
//            else if (r == 34 && g == 177 && b == 76)//�����϶� r == 34 && g == 177 && b == 76
//            {
//                collidedTopL = true;
//                player->SetRopeCollision(true);
//                break;
//            }
//        }
//        else
//        {
//            collidedTopL = false;
//            player->SetTopCollision(false);
//        }
//    }
//    //��(������)
//    for (int i = 3; i < 11; ++i)
//    {
//        topRGB = GetPixel(hdc, checkPosX + 10 - i, checkPosY - 32);
//        r = GetRValue(topRGB); g = GetGValue(topRGB); b = GetBValue(topRGB);
//        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
//        {
//            if (collidedTopL == false && !(r == 34 && g == 177 && b == 76))//������ �ƴ� ��
//            {
//                collidedTopR = true;
//                player->SetTopCollision(true);
//                break;
//            }
//            else if (collidedTopL == false && r == 34 && g == 177 && b == 76)//�����϶� r == 34 && g == 177 && b == 76
//            {
//                collidedTopR = true;
//                player->SetRopeCollision(true);
//                break;
//            }
//        }
//        else
//        {
//            collidedTopR = false;
//
//            if (collidedTopL == false)
//            {
//                player->SetTopCollision(false);
//            }
//
//        }
//    }
//
//
//    //��
//    //����
//    for (int i = 2; i < 11; ++i)
//    {
//        bottomRGB = GetPixel(hdc, checkPosX - 10 + i, checkPosY);
//        r = GetRValue(bottomRGB); g = GetGValue(bottomRGB); b = GetBValue(bottomRGB);
//        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
//        {
//            collidedBottomL = true;
//
//            if (collidedLeft == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0) || !(r == 237 && g == 28 && b == 36)))
//            {
//                player->SetBottomCollision(true);
//            }
//            break;
//        }
//        else
//        {
//            collidedBottomL = false;
//
//            player->SetBottomCollision(false);
//
//        }
//    }
//    //��
//    //�߾�
//    bottomRGB = GetPixel(hdc, checkPosX, checkPosY);
//    r = GetRValue(bottomRGB); g = GetGValue(bottomRGB); b = GetBValue(bottomRGB);
//    if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
//    {
//        collidedBottomC = true;
//        if (player->GetjumpSwitch() == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0) || !(r == 237 && g == 28 && b == 36)))
//        {
//            player->SetBottomCollision(true);
//        }
//    }
//    else
//    {
//        collidedBottomC = false;
//        if (collidedBottomL == false)//������� ������ ���ϵ��� ����
//        {
//            player->SetBottomCollision(false);
//        }
//    }
//    //��
//    //������
//    for (int i = 2; i < 11; ++i)
//    {
//        bottomRGB = GetPixel(hdc, checkPosX + 10 - i, checkPosY);
//        r = GetRValue(bottomRGB); g = GetGValue(bottomRGB); b = GetBValue(bottomRGB);
//        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
//        {
//            collidedBottomR = true;
//            if (collidedRight == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0) || !(r == 237 && g == 28 && b == 36)))
//            {
//                player->SetBottomCollision(true);
//            }
//            break;
//        }
//        else
//        {
//            collidedBottomR = false;
//            if (collidedBottomL == false)//������� ������ ���ϵ��� ����
//            {
//                player->SetBottomCollision(false);
//            }
//        }
//    }
//
//    //���ó��
//    if (collidedLeft == false && collidedBottomC == true && collidedBottomL == true)
//    {
//        for (int i = 3; i < 5; ++i)
//        {
//            stairsRGB = GetPixel(hdc, checkPosX - 10, checkPosY - i);
//            r = GetRValue(stairsRGB); g = GetGValue(stairsRGB); b = GetBValue(stairsRGB);
//
//            if ((r == 0 && g == 0 && b == 0))
//            {
//                player->SetPosY(checkPosY - player->GetMoveSpeed() * Timer::GetDeltaTime());
//                break;
//            }
//        }
//    }
//
//    if (collidedRight == false && collidedBottomC == true && collidedBottomR == true)
//    {
//        for (int i = 3; i < 5; ++i)
//        {
//            stairsRGB = GetPixel(hdc, checkPosX + 10, checkPosY - i);
//            r = GetRValue(stairsRGB); g = GetGValue(stairsRGB); b = GetBValue(stairsRGB);
//
//            if ((r == 0 && g == 0 && b == 0))
//            {
//                player->SetPosY(checkPosY - player->GetMoveSpeed() * Timer::GetDeltaTime());
//                break;
//            }
//        }
//    }
//
//
//}
//
void PixelCollider::CollideLeft(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{
    for (int i = 2; i < bodySizeY / 2; ++i)
    {
        if (checkPixel(hdc, pt.x - bodySizeX / 2, pt.y - bodySizeY / 2 - i, color) == false)
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

        if (checkPixel(hdc, pt.x - bodySizeX / 2 + 1, pt.y - bodySizeY / 2 - i, color) == false)
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
    
        if (checkPixel(hdc, pt.x + bodySizeX / 2, pt.y - bodySizeY / 2 - i, color) == false)
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
    
        if (checkPixel(hdc, pt.x + bodySizeX / 2 - 1, pt.y - bodySizeY / 2 - i, color) == false)
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
        if (checkPixel(hdc, pt.x - bodySizeX / 2 + i, pt.y - bodySizeY, color) == false)
        {
            if (!(r == 34 && g == 177 && b == 76))//������ �ƴ� ��
            {
                collidedUpLeft = true;
                object->SetTopCollision(true);
                break;
            }
            else if (r == 34 && g == 177 && b == 76)//�����϶� r == 34 && g == 177 && b == 76
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
        if (checkPixel(hdc, pt.x + bodySizeX / 2 - i, pt.y - bodySizeY, color) == false)
        {
            if (!(r == 34 && g == 177 && b == 76))//������ �ƴ� ��
            {
                collidedUpRight = true;
                object->SetTopCollision(true);
                break;
            }
            else if (r == 34 && g == 177 && b == 76)//�����϶� r == 34 && g == 177 && b == 76
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
        if (checkPixel(hdc, pt.x - bodySizeX / 2 + i, pt.y, color) == false)
        {
            collidedDownLeft = true;

            if (collidedLeft == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0) || !(r == 237 && g == 28 && b == 36)))
            {
                object->SetBottomCollision(true);
            }
            break;
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
    if (checkPixel(hdc, pt.x, pt.y, color) == false)
    {
        collidedDownCenter = true;
        if (object->GetjumpSwitch() == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0) || !(r == 237 && g == 28 && b == 36)))
        {
            object->SetBottomCollision(true);
        }
    }
    else
    {
        collidedDownCenter = false;
        if (collidedDownLeft == false)//������� ������ ���ϵ��� ����
        {
            object->SetBottomCollision(false);
        }
    }
}

void PixelCollider::CollideDownRight(HDC hdc, GameObject* object, POINTFLOAT pt, int bodySizeX, int bodySizeY, COLORREF color)
{
    for (int i = 3; i < bodySizeX / 2 + 1; ++i)
    {
        if (checkPixel(hdc, pt.x + bodySizeX/2 - i, pt.y, color) == false)
        {
            collidedDownRight = true;
            if (collidedRight == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0) || !(r == 237 && g == 28 && b == 36)))
            {
                object->SetBottomCollision(true);
            }
            break;
        }
        else
        {
            collidedDownRight = false;
            if (collidedDownLeft == false)//������� ������ ���ϵ��� ����
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
            if (checkPixel(hdc, pt.x - bodySizeX / 2, pt.y - i, RGB(0,0,0)) == true)
            {
                object->SetPosY(pt.y - object->GetMoveSpeed() * Timer::GetDeltaTime());
                cout << object->GetMoveSpeed() << "����??" << endl;
                break;
            }
        }
    }

    if (collidedRight == false && collidedDownCenter == true && collidedDownRight == true)
    {
        for (int i = 3; i < 5; ++i)
        {
            if (checkPixel(hdc, pt.x + bodySizeX / 2, pt.y - i, RGB(0, 0, 0)) == true)
            {
                object->SetPosY(pt.y - object->GetMoveSpeed() * Timer::GetDeltaTime());
                cout << object->GetMoveSpeed() << "������??" << endl;
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