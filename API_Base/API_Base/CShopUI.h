#pragma once
#include "CUI.h"
class CShopUI :
    public CUI
{
public:
    CShopUI();
        ~CShopUI();
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    int Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;
    bool IsColl() override;

    bool Get_OnShop() const { return m_bOnShop; }
    void Set_OnShop(bool value) { m_bOnShop = value; }

private:
    bool m_bOnShop;
    Vector2 m_ImgSize;
};

