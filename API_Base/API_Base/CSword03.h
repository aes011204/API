#pragma once
#include "CSword.h"
class CSword03 :
    public CSword
{
public:
    CSword03();
    ~CSword03();

    void Initialize();
    int Update();
    void Late_Update();
    void Render(HDC hdc);
    void Release();
};

