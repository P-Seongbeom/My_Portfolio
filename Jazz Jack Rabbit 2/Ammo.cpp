#include "Ammo.h"
#include "Image.h"

HRESULT Ammo::Init()
{
    ammo = ImageManager::GetSingleton()->FindImage("Image/object/Ammo.bmp");

    ammoType = EammoType::Normal;

    return S_OK;
}

void Ammo::Update()
{
    if (!ammoAlive) return;
    Fire();
}

void Ammo::Render(HDC hdc)
{
    ammo->Render(hdc, pos.x, pos.y);
}

void Ammo::Release()
{
}

void Ammo::Fire()
{
    if (isFire)
    {
        if (ammoType == EammoType::Normal)
        {
            fireTimer += Timer::GetDeltaTime();
            if (ammoDir == EmoveDir::Right)
            {
                pos.x += AMMO_SPEED * Timer::GetDeltaTime();
                ammoMoveDis += AMMO_SPEED * Timer::GetDeltaTime();
            }
            else if (ammoDir == EmoveDir::Left)
            {
                pos.x -= AMMO_SPEED * Timer::GetDeltaTime();
                ammoMoveDis += AMMO_SPEED * Timer::GetDeltaTime();
            }

            if (ammoMoveDis > 280)
            {
                isFire = false;
                ammoAlive = false;
                fireTimer = 0;
                ammoMoveDis = 0;
            }
        }
    }

}

void Ammo::ChangeAmmoType(EammoType type)
{
    //if (!changeAmmo) return;
}
