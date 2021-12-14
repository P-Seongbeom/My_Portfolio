#include "Jazz.h"



HRESULT Jazz::Init()
{
    diameter = 20;
    pos.x = 10;
    pos.y = 500;
    return S_OK;
}

void Jazz::Update()
{
}

void Jazz::Render(HDC hdc)
{
    Ellipse(hdc, (int)pos.x, (int)pos.y, (int)pos.x + diameter, (int)pos.y + diameter);
}

void Jazz::Release()
{
}
