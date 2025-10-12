#pragma once
#include "CUI.h"
class CItem;
class CInventoryCell :
    public CUI
{
public:

    CInventoryCell();
    ~CInventoryCell();

    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    int Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;
    bool IsColl(POINT mouse);
    //bool IsColl() override;
    void KeyInput();

    void RenderIcon(HDC hdc, CItem* item, Vector2 pos = {0,0});

    //void RenderIcon(HDC hdc, CItem* item);

   //  void RenderIcon(CItem* item);
    bool m_bOnMouse= false;
    bool m_bClick = false;

    const TCHAR* m_pFrameKeyOff;
    const TCHAR* m_pFrameKeyOn;

    // CUI을(를) 통해 상속됨
    bool IsColl() override;
};

