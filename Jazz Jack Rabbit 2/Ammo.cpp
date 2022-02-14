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
    explosionEffect(0.05f, 8);
    if (!ammoAlive) return;
    fired();
    collissionRect.left = (LONG)(pos.x - 5);
    collissionRect.right = (LONG)(pos.x + 5);
    collissionRect.top = (LONG)(pos.y - 10);
    collissionRect.bottom = (LONG)pos.y;
}

void Ammo::Render(HDC hdc)
{
    if (effectSwitch)
    {
        ammoEffectImage->Render(hdc, (int)prevRenderPos.x, (int)(prevRenderPos.y + 10), renderFrameX, renderFrameY);
    }
    if (ammoAlive)
    {
        ammoImage->Render(hdc, (int)renderPos.x, (int)renderPos.y);
    }
}

void Ammo::Release()
{
    SAFE_DELETE(pixelCollider);
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
                ammoMoveDistance += AMMO_SPEED * Timer::GetDeltaTime();
            }
            else if (ammoDir == EmoveDir::Left)
            {
                pos.x -= AMMO_SPEED * Timer::GetDeltaTime();
                renderPos.x -= AMMO_SPEED * Timer::GetDeltaTime();
                ammoMoveDistance += AMMO_SPEED * Timer::GetDeltaTime();
            }

            if (ammoMoveDistance > 280 || collideObject)
            {
                isFire = false;
                ammoAlive = false;
                fireTimer = 0;
                ammoMoveDistance = 0;
                collideObject = false;
                effectSwitch = true;
                prevRenderPos = renderPos;
            }
        }
    }

}


