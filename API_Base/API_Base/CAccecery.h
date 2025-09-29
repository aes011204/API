#pragma once
#include "CItem.h"
class CAccecery :
    public CItem
{
public:
    CAccecery();
    ~CAccecery();

    void Initialize();
    int Update();
    void Late_Update();
    void Render(HDC hdc);
    void Release();



    // CItem을(를) 통해 상속됨
    void ItemInfo() override;
};

