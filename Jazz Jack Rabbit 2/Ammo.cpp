#include "Ammo.h"
#include "Image.h"
#include "PixelCollider.h"
#include "Turtle.h"

HRESULT Ammo::Init()
{
    ammoImage = ImageManager::GetSingleton()->FindImage("Image/object/Ammo.bmp");

    ammoType = EammoType::Normal;

    pixelCollider = new PixelCollider;

    return S_OK;
}

void Ammo::Update()
{
    if (!ammoAlive) return;
    collissionRect.left = pos.x - 5;
    collissionRect.right = pos.x + 5;
    collissionRect.top = pos.y - 10;
    collissionRect.bottom = pos.y;
    fired();
    //cout << "�� : " << collideLeft << endl;
    //cout << "�� : " << collideRight << endl;
}

void Ammo::Render(HDC hdc)
{
    Rectangle(hdc, renderPos.x - 5, renderPos.y - 5, renderPos.x + 5, renderPos.y + 5);
    ammoImage->Render(hdc, renderPos.x, renderPos.y);
}

void Ammo::Release()
{
    SAFE_DELETE(pixelCollider);
    //SAFE_DELETE(collissionRect);
}

void Ammo::CollideObject(HDC mapPixel, Turtle* enemy, GameObject ammo)
{
    RECT rect;
    RECT enemyRect = enemy->GetCollisionRect();

    if(pixelCollider->CollideAmmo(mapPixel, ammo, pos, 10, 10, RGB(87, 0, 203)))
    {
        collideObject = true;
    }
    else if (IntersectRect(&rect, &enemyRect, &collissionRect))
    {
        enemy->GetHit(true);
        collideObject = true;
    }

}

void Ammo::fired()
{
    if (isFire)
    {
        if (ammoType == EammoType::Normal)
        {
            fireTimer += Timer::GetDeltaTime();
            if (ammoDir == EmoveDir::Right)
            {
                pos.x += AMMO_SPEED * Timer::GetDeltaTime();
                renderPos.x += AMMO_SPEED * Timer::GetDeltaTime();
                ammoMoveDis += AMMO_SPEED * Timer::GetDeltaTime();
            }
            else if (ammoDir == EmoveDir::Left)
            {
                pos.x -= AMMO_SPEED * Timer::GetDeltaTime();
                renderPos.x -= AMMO_SPEED * Timer::GetDeltaTime();
                ammoMoveDis += AMMO_SPEED * Timer::GetDeltaTime();
            }

            if (ammoMoveDis > 280 || collideObject)
            {
                isFire = false;
                ammoAlive = false;
                fireTimer = 0;
                ammoMoveDis = 0;
                collideObject = false;
            }
        }
    }

}


