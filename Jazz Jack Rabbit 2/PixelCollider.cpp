#include "PixelCollider.h"
#include "Player.h"
//
//void PixelCollider::PixelCollision(HDC hdc, int checkPosX, int checkPosY, COLORREF color)
//{
//    COLORREF leftRGB, rightRGB, topRGB, bottomRGB, stairsRGB;
//    WORD r, g, b;
//
//    //좌
//    for (int i = 2; i < 16; ++i)
//    {
//        //최외각
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
//        //안쪽
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
//    //우
//    for (int i = 2; i < 16; ++i)
//    {
//        //최외각
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
//        //안쪽
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
//    //상(왼쪽)
//    for (int i = 3; i < 11; ++i)
//    {
//        topRGB = GetPixel(hdc, checkPosX - 10 + i, checkPosY - 32);
//        r = GetRValue(topRGB); g = GetGValue(topRGB); b = GetBValue(topRGB);
//        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
//        {
//            if (!(r == 34 && g == 177 && b == 76))//로프가 아닌 벽
//            {
//                collidedTopL = true;
//                player->SetTopCollision(true);
//                cout << " 왼머리 " << endl;
//                break;
//            }
//            else if (r == 34 && g == 177 && b == 76)//로프일때 r == 34 && g == 177 && b == 76
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
//    //상(오른쪽)
//    for (int i = 3; i < 11; ++i)
//    {
//        topRGB = GetPixel(hdc, checkPosX + 10 - i, checkPosY - 32);
//        r = GetRValue(topRGB); g = GetGValue(topRGB); b = GetBValue(topRGB);
//        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
//        {
//            if (collidedTopL == false && !(r == 34 && g == 177 && b == 76))//로프가 아닌 벽
//            {
//                collidedTopR = true;
//                player->SetTopCollision(true);
//                break;
//            }
//            else if (collidedTopL == false && r == 34 && g == 177 && b == 76)//로프일때 r == 34 && g == 177 && b == 76
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
//    //하
//    //왼쪽
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
//    //하
//    //중앙
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
//        if (collidedBottomL == false)//좌측계단 오름시 낙하동작 방지
//        {
//            player->SetBottomCollision(false);
//        }
//    }
//    //하
//    //오른쪽
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
//            if (collidedBottomL == false)//좌측계단 오름시 낙하동작 방지
//            {
//                player->SetBottomCollision(false);
//            }
//        }
//    }
//
//    //계단처리
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
    COLORREF RGB;
    WORD r, g, b;

    //좌
    for (int i = 2; i < 16; ++i)
    {
        //최외각
        RGB = GetPixel(hdc, pt.x - bodySizeX / 2, pt.y - bodySizeY / 2 - i);
        r = GetRValue(RGB); g = GetGValue(RGB); b = GetBValue(RGB);

        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
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
        //안쪽
        RGB = GetPixel(hdc, pt.x + 1 - bodySizeX / 2, pt.y - bodySizeY / 2 - i);
        r = GetRValue(RGB); g = GetGValue(RGB); b = GetBValue(RGB);

        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedLeft = true;
            object->SetPosX(player->GetPos().x + 1);
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
//
//void PixelCollider::CollideRight(HDC hdc, int checkPosX, int checkPosY, COLORREF color)
//{
//}
//
//void PixelCollider::CollideUpLeft(HDC hdc, int checkPosX, int checkPosY, COLORREF color)
//{
//}
//
//void PixelCollider::CollideUpRight(HDC hdc, int checkPosX, int checkPosY, COLORREF color)
//{
//}
//
//void PixelCollider::CollideDownLeft(HDC hdc, int checkPosX, int checkPosY, COLORREF color)
//{
//}
//
//void PixelCollider::CollideDownCenter(HDC hdc, int checkPosX, int checkPosY, COLORREF color)
//{
//}
//
//void PixelCollider::CollideDownRight(HDC hdc, int checkPosX, int checkPosY, COLORREF color)
//{
//}
