#pragma once
#include "CWeapon.h"
class CGun :
    public CWeapon
{
public:
    CGun();
    ~CGun();

    void Initialize();
    int Update();
    void Late_Update();
    void Render(HDC hdc);
    void Release();
};

