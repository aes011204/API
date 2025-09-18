#pragma once
#include "CScene.h"
class CEdit :
    public CScene
{
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;
    void Key_Input();
};

