#include "Ammo.h"
#include "Image.h"
#include "PixelCollider.h"
#include "Turtle.h"
#include "QueenEarlong.h"


HRESULT Ammo::Init()
{
    ammoImage = ImageManager::GetSingleton()->FindImage("Image/object/Ammo.bmp");
    ammoEffectImage = ImageManager::GetSingleton()->FindImage("Image/object/ammo_effect.bmp");

    ammoType = EammoType::Normal;

    pixelCollider = new PixelCollider;

    return S_OK;
}

void Ammo::Update()
{
    explosionEffect(0.1, 8);
    fired();
    if (!ammoAlive) return;
    collissionRect.left = pos.x - 5;
    collissionRect.right = pos.x + 5;
    collissionRect.top = pos.y - 10;
    collissionRect.bottom = pos.y;
    //cout << "¿Þ : " << collideLeft << endl;
    //cout << "¿À : " << collideRight << endl;
}

void Ammo::Render(HDC hdc)
{
    if (effectSwitch)
    {
        ammoEffectImage->Render(hdc, prevRenderPos.x, prevRenderPos.y + 10, renderFrameX, renderFrameY);
    }
    if (ammoAlive)
    {
        Rectangle(hdc, renderPos.x - 5, renderPos.y - 5, renderPos.x + 5, renderPos.y + 5);
        ammoImage->Render(hdc, renderPos.x, renderPos.y);
    }
}

void Ammo::Release()
{
    SAFE_DELETE(pixelCollider);
    //SAFE_DELETE(collissionRect);
}

void Ammo::CollideObject(HDC mapPixel, Turtle* enemy, QueenEarlong* boss, GameObject ammo)
{
    RECT rect;
    RECT enemyRect = enemy->GetCollisionRect();
    RECT bossRect = boss->GetCollisionRect();

    if(pixelCollider->CollideAmmo(mapPixel, ammo, pos, 10, 10, RGB(87, 0, 203)))
    {
        collideObject = true;
    }
    else if (IntersectRect(&rect, &enemyRect, &collissionRect))
    {
        enemy->GetHit(true);
        collideObject = true;
    }
    else if (IntersectRect(&rect, &bossRect, &collissionRect))
    {
        boss->GetHit(true);
        collideObject = true;
    }

}

void Ammo::explosionEffect(float frameTerm, int maxFrameX)
{
    if (effectSwitch == false) return;

    ammoEffectTimer += Timer::GetDeltaTime();

    if (ammoEffectTimer > frameTerm)
    {
        ++renderFrameX;
        ammoEffectTimer = 0;
    }

    if (renderFrameX >= maxFrameX)
    {
        renderFrameX = 0;
        effectSwitch = false;
    }
}

bool Ammo::freeCameraMoveZone(RECT* zone, POINTFLOAT ptf)
{
    if (zone->left <= ptf.x && zone->right >= ptf.x && zone->top <= ptf.y && zone->bottom >= ptf.y)
    {
        return true;
    }

    return false;
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
                effectSwitch = true;
                prevRenderPos = renderPos;
            }
        }
    }

}


