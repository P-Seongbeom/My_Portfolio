#include "PlayInStageScene.h"
#include "Player.h"
#include "Config.h"
#include "Image.h"
#include "TileMap.h"

HRESULT PlayInStageScene::Init()
{
    tileMap = new TileMap;
    tileMap->Init();

	player = new Player;
	player->Init();

    playerPos.x = player->GetPos().x;
    playerPos.y = player->GetPos().y;

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

    cameraRenderPos.x = player->GetPos().x - WIN_SIZE_X / 2;
    cameraRenderPos.y = player->GetPos().y - WIN_SIZE_Y / 2;

    cameraSpeed = PLAYER_MAX_SPEED;
    glanceSpeed = TILE_SIZE * 2;

	return S_OK;
}

void PlayInStageScene::Update()
{
    tileMap->Update();
	player->Update();
    playerPos.x = player->GetPos().x;
    playerPos.y = player->GetPos().y;
    moveCamera();
}

void PlayInStageScene::Render(HDC hdc)
{
    tileMap->BackGroundRender(hdc, cameraRenderPos.x / TILE_SIZE, cameraRenderPos.y / TILE_SIZE);
	player->Render(hdc);
    tileMap->FrontStructureRender(hdc, cameraRenderPos.x / TILE_SIZE, cameraRenderPos.y / TILE_SIZE);
}

void PlayInStageScene::Release()
{
    SAFE_RELEASE(tileMap);
    SAFE_RELEASE(player);
    SAFE_DELETE(cameraMoveXZone);
    SAFE_DELETE(cameraMoveYZone);
}

void PlayInStageScene::PhysicsUpdate()
{
    collision(tileMap->GetImageInfo()->GetMemDC(),
        player->GetPos().x,
        player->GetPos().y,
        RGB(87, 0, 203));
}


void PlayInStageScene::moveCamera()
{
    if (PtInRect(cameraMoveXZone, playerPos))
    {
        if (cameraRenderPos.x < 0) cameraRenderPos.x = 0;
    
        cameraRenderPos.x = player->GetPos().x - WIN_SIZE_X / 2;
        
        if (cameraRenderPos.x > WIN_SIZE_X) cameraRenderPos.x = WIN_SIZE_X;
    
        cameraRenderPos.x = player->GetPos().x - WIN_SIZE_X / 2;
    }
    
    if (PtInRect(cameraMoveYZone, playerPos))
    {
        cameraRenderPos.y = player->GetPos().y - WIN_SIZE_Y / 2;
    }

}

//위 아래 바라본 후
void PlayInStageScene::returnCamera()
{
    if (!activateReturnCamera) return;

    if (cameraRenderPos.y > player->GetPos().y - WIN_SIZE_Y / 2)
    {
        cameraRenderPos.y -= cameraSpeed * Timer::GetDeltaTime();

        if (cameraRenderPos.y < player->GetPos().y - WIN_SIZE_Y / 2)
        {
            cameraRenderPos.y = player->GetPos().y - WIN_SIZE_Y / 2;
            activateReturnCamera = false;
        }
    }
    else if (cameraRenderPos.y < player->GetPos().y - WIN_SIZE_Y / 2)
    {
        cameraRenderPos.y += cameraSpeed * Timer::GetDeltaTime();

        if (cameraRenderPos.y > player->GetPos().y - WIN_SIZE_Y / 2)
        {
            cameraRenderPos.y = player->GetPos().y - WIN_SIZE_Y / 2;
            activateReturnCamera = false;
        }
    }
    
}

void PlayInStageScene::collision(HDC hdc, int checkPosX, int checkPosY, COLORREF color)
{
    COLORREF leftRGB, rightRGB, topRGB, bottomRGB, stairsRGB;
    WORD r, g, b;

    //좌
    for (int i = 2; i < 31; ++i)
    {
        //최외각
        leftRGB = GetPixel(hdc, checkPosX - 10, checkPosY - 16 - i);
        r = GetRValue(leftRGB); g = GetGValue(leftRGB); b = GetBValue(leftRGB);

        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedLeft = true;
            player->SetLeftCollision(true);
            break;
        }
        else
        {
            collidedLeft = false;
            player->SetLeftCollision(false);
            break;
        }
        //안쪽
        leftRGB = GetPixel(hdc, checkPosX + 1 - 10, checkPosY - 16 - i);
        r = GetRValue(leftRGB); g = GetGValue(leftRGB); b = GetBValue(leftRGB);

        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedLeft = true;
            player->SetPosX(player->GetPos().x + 1);
            player->SetLeftCollision(true);
            break;
        }
        else
        {
            collidedLeft = false;
            player->SetLeftCollision(false);
            break;
        }
    }

    //우
    for (int i = 2; i < 31; ++i)
    {
        //최외각
        rightRGB = GetPixel(hdc, checkPosX + 10, checkPosY - 16 - i);
        r = GetRValue(rightRGB); g = GetGValue(rightRGB); b = GetBValue(rightRGB);

        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedRight = true;
            player->SetRightCollision(true);
            break;
        }
        else
        {
            collidedRight = false;
            player->SetRightCollision(false);
            break;
        }
        //안쪽
        rightRGB = GetPixel(hdc, checkPosX - 1 + 10, checkPosY - 16 - i);
        r = GetRValue(rightRGB); g = GetGValue(rightRGB); b = GetBValue(rightRGB);

        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedRight = true;
            player->SetPosX(player->GetPos().x - 1);
            player->SetRightCollision(true);
            break;
        }
        else
        {
            collidedRight = false;
            player->SetRightCollision(false);
            break;
        }
    }

    //상(왼쪽)
    for (int i = 5; i < 11; ++i)
    {
        topRGB = GetPixel(hdc, checkPosX - 10 + i, checkPosY - 32);
        r = GetRValue(topRGB); g = GetGValue(topRGB); b = GetBValue(topRGB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            if (!(r == 34 && g == 177 && b == 76))//로프가 아닌 벽
            {
                collidedTop = true;
                player->SetTopCollision(true);
                break;
            }
            else if (r == 34 && g == 177 && b == 76)//로프일때 r == 34 && g == 177 && b == 76
            {
                collidedTop = true;
                player->SetRopeCollision(true);
                break;
            }
        }
        else
        {
            collidedTop = false;
            player->SetTopCollision(false);
        }
    }
    //상(오른쪽)
    for (int i = 5; i < 11; ++i)
    {
        topRGB = GetPixel(hdc, checkPosX + 10 - i, checkPosY - 32);
        r = GetRValue(topRGB); g = GetGValue(topRGB); b = GetBValue(topRGB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            if (!(r == 34 && g == 177 && b == 76))//로프가 아닌 벽
            {
                collidedTop = true;
                player->SetTopCollision(true);
                break;
            }
            else if(r == 34 && g == 177 && b == 76)//로프일때 r == 34 && g == 177 && b == 76
            {
                collidedTop = true;
                player->SetRopeCollision(true);
                break;
            }
        }
        else
        {
            collidedTop = false;
            player->SetTopCollision(false);
        }
    }


    //하
    //왼쪽
    for (int i = 2; i < 11; ++i)
    {
        bottomRGB = GetPixel(hdc, checkPosX - 10 + i, checkPosY);
        r = GetRValue(bottomRGB); g = GetGValue(bottomRGB); b = GetBValue(bottomRGB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedBottomL = true;
            if (collidedLeft == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0)))
            {
                player->SetBottomCollision(true);
            }
            break;
        }
        else
        {
            collidedBottomL = false;

            player->SetBottomCollision(false);

        }
    }
    //하
    //중앙
    bottomRGB = GetPixel(hdc, checkPosX, checkPosY);
    r = GetRValue(bottomRGB); g = GetGValue(bottomRGB); b = GetBValue(bottomRGB);
    if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
    {
        collidedBottomC = true;
        if (player->GetjumpSwitch() == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0)))
        {
            player->SetBottomCollision(true);
        }
    }
    else
    {
        collidedBottomC = false;
        if (collidedBottomL == false)//좌측계단 오름시 낙하동작 방지
        {
            player->SetBottomCollision(false);
        }
    }
    //하
    //오른쪽
    for(int i = 2; i < 11; ++i)
    {
        bottomRGB = GetPixel(hdc, checkPosX + 10 - i, checkPosY);
        r = GetRValue(bottomRGB); g = GetGValue(bottomRGB); b = GetBValue(bottomRGB);
        if (!(r == GetRValue(color) && g == GetGValue(color) && b == GetBValue(color)))
        {
            collidedBottomR = true;
            if (collidedRight == false && (!(r == 34 && g == 177 && b == 76) || !(r == 255 && g == 242 && b == 0)))
            {
                player->SetBottomCollision(true);
            }
            break;
        }
        else
        {
            collidedBottomR = false;
            if (collidedBottomL == false)//좌측계단 오름시 낙하동작 방지
            {
                player->SetBottomCollision(false);
            }
        }
    }


    //계단처리
    if (collidedLeft == false && collidedBottomC == true && collidedBottomL == true)
    {
        for (int i = 3; i < 5; ++i)
        {
            stairsRGB = GetPixel(hdc, checkPosX - 10, checkPosY - i);
            r = GetRValue(stairsRGB); g = GetGValue(stairsRGB); b = GetBValue(stairsRGB);

            if ((r == 0 && g == 0 && b == 0))
            {
                player->SetPosY(checkPosY - player->GetMoveSpeed() * Timer::GetDeltaTime());
                break;
            }
        }
    }

    if (collidedRight == false && collidedBottomC == true && collidedBottomR == true)
    {
        for (int i = 3; i < 5; ++i)
        {
            stairsRGB = GetPixel(hdc, checkPosX + 10, checkPosY - i);
            r = GetRValue(stairsRGB); g = GetGValue(stairsRGB); b = GetBValue(stairsRGB);

            if ((r == 0 && g == 0 && b == 0))
            {
                player->SetPosY(checkPosY - player->GetMoveSpeed() * Timer::GetDeltaTime());
                break;
            }
        }
    }
    
    
}
