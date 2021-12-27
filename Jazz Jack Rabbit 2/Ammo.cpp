#include "Ammo.h"
#include "Image.h"

HRESULT Ammo::Init()
{
    ammo = ImageManager::GetSingleton()->FindImage("Image/object/temp_Ammo.bmp");

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

    ammo->Render(hdc, pos.x, pos.y - 30);

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
            }
            else if (ammoDir == EmoveDir::Left)
            {
                pos.x -= AMMO_SPEED * Timer::GetDeltaTime();
            }
        
            if (fireTimer > 0.5)
            {
                isFire = false;
                ammoAlive = false;
                fireTimer = 0;
            }
        }
    }

}

void Ammo::ChangeAmmoType(EammoType type)
{
    //if (!changeAmmo) return;
}
