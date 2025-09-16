#pragma once
#include "CUI.h"
class CMainUI :
    public CUI
{
public:
    CMainUI();
    ~CMainUI();

    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    int Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;
    bool IsColl() override;
};

