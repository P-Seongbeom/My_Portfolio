#include "PlayInStageScene.h"
#include "Player.h"
#include "Config.h"
#include "CommonFunction.h"
#include "Image.h"
#include "TileMap.h"
#include "Physics.h"


HRESULT PlayInStageScene::Init()
{
    SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X * 1.5, WIN_SIZE_Y * 1.5);
    windowSizeX = WIN_SIZE_X;
    windowSizeY = WIN_SIZE_Y;

    tileMap = new TileMap;
    tileMap->Init();

	jumpTest = new Player;
	jumpTest->Init();

    playerPos.x = jumpTest->GetPos().x;
    playerPos.y = jumpTest->GetPos().y;

    cameraMoveXZone = new RECT;
    cameraMoveXZone->left = WIN_SIZE_X / 2.0;
    cameraMoveXZone->right = WIN_SIZE_X * 1.5;
    cameraMoveXZone->top = 0;
    cameraMoveXZone->bottom = WIN_SIZE_Y * 2.0;

    cameraMoveYZone = new RECT;
    cameraMoveYZone->left = 0;
    cameraMoveYZone->right = WIN_SIZE_X * 2.0;
    cameraMoveYZone->top = WIN_SIZE_Y / 2.0;
    cameraMoveYZone->bottom = WIN_SIZE_Y * 1.5;

    cameraRenderPos.x = jumpTest->GetPos().x - WIN_SIZE_X / 2;
    cameraRenderPos.y = jumpTest->GetPos().y - WIN_SIZE_Y / 2;

    cameraSpeed = PLAYER_MOVE_SPEED;
    glanceSpeed = TILE_SIZE * 2;

	return S_OK;
}

void PlayInStageScene::Update()
{
    tileMap->Update();
	jumpTest->Update();
    playerPos.x = jumpTest->GetPos().x;
    playerPos.y = jumpTest->GetPos().y;
    moveCamera();
    //pixelCollider->SetPos(jumpTest->GetRenderPos());
    //cout << endl;
    //cout << "카메라 x : " << cameraRenderPos.x << endl;
    //cout << "카메라 y : " << cameraRenderPos.y << endl;
}

void PlayInStageScene::Render(HDC hdc)
{
    tileMap->BackGroundRender(hdc, cameraRenderPos.x / TILE_SIZE, cameraRenderPos.y / TILE_SIZE);
	jumpTest->Render(hdc);
    tileMap->FrontStructureRender(hdc, cameraRenderPos.x / TILE_SIZE, cameraRenderPos.y / TILE_SIZE);
}

void PlayInStageScene::Release()
{
    SAFE_RELEASE(tileMap);
    SAFE_RELEASE(jumpTest);
}

void PlayInStageScene::PhysicsUpdate()
{
    collision(tileMap->GetImageInfo()->GetMemDC(),
        jumpTest->GetPos().x,
        jumpTest->GetPos().y,
        RGB(87, 0, 203));
}


void PlayInStageScene::moveCamera()
{
    //if (!jumpTest->GetEndOfHorizntal())
    //{
    //    if (Input::GetButton(VK_LEFT))
    //    {
    //        activateReturnCamera = true;
    //        cameraRenderPos.x = jumpTest->GetPos().x - WIN_SIZE_X / 2;
    //         if (cameraRenderPos.x < 0) cameraRenderPos.x = 0;
    //    }
    //    if (Input::GetButtonUp(VK_LEFT))
    //    {
    //        activateReturnCamera = false;
    //    }

    //    if (Input::GetButton(VK_RIGHT))
    //    {
    //        activateReturnCamera = true;
    //        cameraRenderPos.x = jumpTest->GetPos().x - WIN_SIZE_X / 2;
    //        if (cameraRenderPos.x > WIN_SIZE_X) cameraRenderPos.x = WIN_SIZE_X;
    //    }
    //    if (Input::GetButtonUp(VK_RIGHT))
    //    {
    //        activateReturnCamera = false;
    //    }
    //}

    //if (!jumpTest->GetEndOfVertical() && jumpTest->GetJumpKeyPressed())
    //{
    //    cameraRenderPos.y = jumpTest->GetPos().y - WIN_SIZE_Y / 2;
    //}
    //else
    //{
    //    if (cameraRenderPos.y < 0) cameraRenderPos.y = 0;
    //}

    //if (Input::GetButton(VK_DOWN) && cameraRenderPos.y < WIN_SIZE_Y)
    //{
    //    stayKeyDownTime += Timer::GetDeltaTime();

    //    if (stayKeyDownTime > 0.5)
    //    {
    //        cameraRenderPos.y += glanceSpeed * Timer::GetDeltaTime();
    //        if (cameraRenderPos.y > jumpTest->GetPos().y - WIN_SIZE_Y / 2 + (TILE_SIZE * 2))
    //        {
    //            cameraRenderPos.y = jumpTest->GetPos().y - WIN_SIZE_Y / 2 + (TILE_SIZE * 2);
    //            stayKeyDownTime = 0;
    //        }

    //    }
    //}
    //else if (Input::GetButtonUp(VK_DOWN))
    //{
    //    activateReturnCamera = true;
    //    stayKeyDownTime = 0;
    //}

    //if(Input::GetButton(VK_UP) && cameraRenderPos.y > WIN_SIZE_Y / 2)
    //{
    //    stayKeyDownTime += Timer::GetDeltaTime();

    //    if (stayKeyDownTime > 0.5)
    //    {
    //        cameraRenderPos.y -= glanceSpeed * Timer::GetDeltaTime();
    //        if (cameraRenderPos.y < jumpTest->GetPos().y - WIN_SIZE_Y / 2 + (TILE_SIZE * 2))
    //        {
    //            cameraRenderPos.y = jumpTest->GetPos().y - WIN_SIZE_Y / 2 + (TILE_SIZE * 2);
    //            stayKeyDownTime = 0;
    //        }

    //    }
    //}
    //else if (Input::GetButtonUp(VK_UP))
    //{
    //    activateReturnCamera = true;
    //    stayKeyDownTime = 0;
    //}

        if (PtInRect(cameraMoveXZone, playerPos))
        {
            if (Input::GetButton(VK_LEFT))
            {
                activateReturnCamera = true;
                if (cameraRenderPos.x < 0) cameraRenderPos.x = 0;

                cameraRenderPos.x = jumpTest->GetPos().x - WIN_SIZE_X / 2;
            }
            if (Input::GetButtonUp(VK_LEFT))
            {
                activateReturnCamera = false;
            }

            if (Input::GetButton(VK_RIGHT))
            {
                activateReturnCamera = true;
                if (cameraRenderPos.x > WIN_SIZE_X) cameraRenderPos.x = WIN_SIZE_X;

                cameraRenderPos.x = jumpTest->GetPos().x - WIN_SIZE_X / 2;
            }
            if (Input::GetButtonUp(VK_RIGHT))
            {
                activateReturnCamera = false;
            }
        }

        if (PtInRect(cameraMoveYZone, playerPos))
        {
            cameraRenderPos.y = jumpTest->GetPos().y - WIN_SIZE_Y / 2;
        }

        //if (Input::GetButton(VK_DOWN) && cameraRenderPos.y < WIN_SIZE_Y)
        //{
        //    stayKeyDownTime += Timer::GetDeltaTime();

        //    if (stayKeyDownTime > 0.5)
        //    {
        //        cameraRenderPos.y += glanceSpeed * Timer::GetDeltaTime();
        //        if (cameraRenderPos.y > jumpTest->GetPos().y - WIN_SIZE_Y / 2 + (TILE_SIZE * 2))
        //        {
        //            cameraRenderPos.y = jumpTest->GetPos().y - WIN_SIZE_Y / 2 + (TILE_SIZE * 2);
        //            stayKeyDownTime = 0;
        //        }

        //    }
        //}
        //else if (Input::GetButtonUp(VK_DOWN))
        //{
        //    activateReturnCamera = true;
        //    stayKeyDownTime = 0;
        //}

        //if (Input::GetButton(VK_UP) && cameraRenderPos.y > WIN_SIZE_Y / 2)
        //{
        //    stayKeyDownTime += Timer::GetDeltaTime();

        //    if (stayKeyDownTime > 0.5)
        //    {
        //        cameraRenderPos.y -= glanceSpeed * Timer::GetDeltaTime();
        //        if (cameraRenderPos.y < jumpTest->GetPos().y - WIN_SIZE_Y / 2 + (TILE_SIZE * 2))
        //        {
        //            cameraRenderPos.y = jumpTest->GetPos().y - WIN_SIZE_Y / 2 + (TILE_SIZE * 2);
        //            stayKeyDownTime = 0;
        //        }

        //    }
        //}
        //else if (Input::GetButtonUp(VK_UP))
        //{
        //    activateReturnCamera = true;
        //    stayKeyDownTime = 0;
        //}

   //returnCamera();
}

void PlayInStageScene::returnCamera()
{
    if (!activateReturnCamera) return;

    if (cameraRenderPos.y > jumpTest->GetPos().y - WIN_SIZE_Y / 2)
    {
        cameraRenderPos.y -= cameraSpeed * Timer::GetDeltaTime();

        if (cameraRenderPos.y < jumpTest->GetPos().y - WIN_SIZE_Y / 2)
        {
            cameraRenderPos.y = jumpTest->GetPos().y - WIN_SIZE_Y / 2;
            activateReturnCamera = false;
        }
    }
    else if (cameraRenderPos.y < jumpTest->GetPos().y - WIN_SIZE_Y / 2)
    {
        cameraRenderPos.y += cameraSpeed * Timer::GetDeltaTime();

        if (cameraRenderPos.y > jumpTest->GetPos().y - WIN_SIZE_Y / 2)
        {
            cameraRenderPos.y = jumpTest->GetPos().y - WIN_SIZE_Y / 2;
            activateReturnCamera = false;
        }
    }
    
}

void PlayInStageScene::collision(HDC hdc, int checkPosX, int checkPosY, COLORREF color)
{
    COLORREF leftRGB, rightRGB, topRGB, bottomRGB, stairsRGB1, stairsRGB2, bottomRGBLB;
    WORD r, g, b;

    //좌
    for (int i = 2; i < 31; ++i)
    {
        leftRGB = GetPixel(hdc, checkPosX - 10, checkPosY - 16 - i);
        r = GetRValue(leftRGB); g = GetGValue(leftRGB); b = GetBValue(leftRGB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedLeft = true;
            jumpTest->SetLeftCollision(true);
            //cout << "좌충돌" << endl;
            break;
        }
        else
        {
            collidedLeft = false;
            jumpTest->SetLeftCollision(false);
            break;
        }
        
        leftRGB = GetPixel(hdc, checkPosX + 1 - 10, checkPosY - 16 - i);
        r = GetRValue(leftRGB); g = GetGValue(leftRGB); b = GetBValue(leftRGB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedLeft = true;
            jumpTest->SetPosX(jumpTest->GetPos().x + 1);
            jumpTest->SetLeftCollision(true);
            //cout << "좌충돌" << endl;
            break;
        }
        else
        {
            collidedLeft = false;
            jumpTest->SetLeftCollision(false);
            break;
        }
    }

    //우
    for (int i = 2; i < 31; ++i)
    {
        rightRGB = GetPixel(hdc, checkPosX + 10, checkPosY - 16 - i);
        r = GetRValue(rightRGB); g = GetGValue(rightRGB); b = GetBValue(rightRGB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedRight = true;
            jumpTest->SetRightCollision(true);
            cout << "우충돌" << endl;
            break;
        }
        else
        {
            collidedRight = false;
            jumpTest->SetRightCollision(false);
            break;
        }

        rightRGB = GetPixel(hdc, checkPosX - 1 + 10, checkPosY - 16 - i);
        r = GetRValue(rightRGB); g = GetGValue(rightRGB); b = GetBValue(rightRGB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedRight = true;
            jumpTest->SetPosX(jumpTest->GetPos().x - 1);
            jumpTest->SetRightCollision(true);
            cout << "우충돌" << endl;
            break;
        }
        else
        {
            collidedRight = false;
            jumpTest->SetRightCollision(false);
            break;
        }
    }

    //상(벽충돌)
    for (int i = 5; i < 11; ++i)
    {
        topRGB = GetPixel(hdc, checkPosX - 10 + i, checkPosY - 32);
        r = GetRValue(topRGB); g = GetGValue(topRGB); b = GetBValue(topRGB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            if (!(r == 34 && g == 177 && b == 76))
            {
                collidedTop = true;
                jumpTest->SetTopCollision(true);
                cout << "머리" << endl;
                break;
            }
            else if (r == 34 && g == 177 && b == 76)//로프일때 r == 34 && g == 177 && b == 76
            {
                collidedTop = true;
                jumpTest->SetRopeCollision(true);
                cout << "픽셀 머리" << endl;
                break;
            }
        }
        else
        {
            collidedTop = false;
            jumpTest->SetTopCollision(false);
        }
    }

    for (int i = 5; i < 11; ++i)
    {
        topRGB = GetPixel(hdc, checkPosX + 10 - i, checkPosY - 32);
        r = GetRValue(topRGB); g = GetGValue(topRGB); b = GetBValue(topRGB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            if (!(r == 34 && g == 177 && b == 76))
            {
                collidedTop = true;
                jumpTest->SetTopCollision(true);
                cout << "머리" << endl;
                break;
            }
            else //로프일때 r == 34 && g == 177 && b == 76
            {
                collidedTop = true;
                jumpTest->SetRopeCollision(true);
                break;
            }
        }
        else
        {
            collidedTop = false;
            jumpTest->SetTopCollision(false);
            //jumpTest->SetRopeCollision(false);
        }
    }


    //하
    //왼쪽
    for (int i = 2; i < 11; ++i)
    {
        bottomRGBLB = GetPixel(hdc, checkPosX - 10 + i, checkPosY);
        r = GetRValue(bottomRGBLB); g = GetGValue(bottomRGBLB); b = GetBValue(bottomRGBLB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedBottomL = true;
            if (collidedLeft == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0)))
            {
                jumpTest->SetCollisionState(true);
            }
            //cout << "왼바닥" << endl;
            break;
        }
        else
        {
            collidedBottomL = false;

            jumpTest->SetCollisionState(false);

        }
    }
    //중앙
    bottomRGB = GetPixel(hdc, checkPosX, checkPosY);
    r = GetRValue(bottomRGB); g = GetGValue(bottomRGB); b = GetBValue(bottomRGB);
    if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
    {
        collidedBottomC = true;
        if(jumpTest->GetJumpKeyPressed() == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0)))
        jumpTest->SetCollisionState(true);
        //cout << "우바닥" << endl;
    }
    else
    {
        collidedBottomC = false;
        if (collidedBottomL == false)//좌측계단 오름시 낙하동작 방지
        {
            jumpTest->SetCollisionState(false);
        }
    }
    //오른쪽
    for(int i = 2; i < 11; ++i)
    {
        bottomRGB = GetPixel(hdc, checkPosX + 10 - i, checkPosY);
        r = GetRValue(bottomRGB); g = GetGValue(bottomRGB); b = GetBValue(bottomRGB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedBottomR = true;
            if(collidedRight == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0)))
            jumpTest->SetCollisionState(true);
            //cout << "우바닥" << endl;
            break;
        }
        else
        {
            collidedBottomR = false;
            if (collidedBottomL == false)//좌측계단 오름시 낙하동작 방지
            {
                jumpTest->SetCollisionState(false);
            }
        }
    }


    //계단처리
    {
        if (collidedLeft == false && collidedBottomC == true && collidedBottomL == true)
        {
            for (int i = 3; i < 5; ++i)
            {
                stairsRGB1 = GetPixel(hdc, checkPosX - 10, checkPosY - i);
                r = GetRValue(stairsRGB1); g = GetGValue(stairsRGB1); b = GetBValue(stairsRGB1);
                if ((r == 0 && g == 0 && b == 0))
                {
                    jumpTest->SetPosY(checkPosY - jumpTest->GetMoveSpeed() * Timer::GetDeltaTime());
                    cout << "----좌계단" << endl;
                    break;
                }
            }
        }

        if (collidedRight == false && collidedBottomC == true && collidedBottomR == true)
        {
            for (int i = 3; i < 5; ++i)
            {
                stairsRGB2 = GetPixel(hdc, checkPosX + 10, checkPosY - i);
                r = GetRValue(stairsRGB2); g = GetGValue(stairsRGB2); b = GetBValue(stairsRGB2);
                if ((r == 0 && g == 0 && b == 0))
                {
                    jumpTest->SetPosY(checkPosY - jumpTest->GetMoveSpeed() * Timer::GetDeltaTime());
                    cout << "----우계단" << endl;
                    break;
                }
            }
        }
    }
    
}
