#pragma once
#include "CSword.h"
class CSword02 :
    public CSword
{
public:
    CSword02();
    ~CSword02();

    void Initialize();
    int Update();
    void Late_Update();
    void Render(HDC hdc);
    void Release();

};

