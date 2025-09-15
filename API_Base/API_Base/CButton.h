#pragma once
#include "CUI.h"
#include <functional>
class CButton :
    public CUI
{
public:

    CButton();
    ~CButton();
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    int Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;

public:

    bool IsColl() override;

    void Update_ResizeRect();

    void			Set_FrameKeyOff(const TCHAR* pFrameKey) { m_pFrameKeyOff = pFrameKey; }
    void			Set_FrameKeyOn(const TCHAR* pFrameKey) { m_pFrameKeyOn = pFrameKey; }

    void SetOnClick(std::function<void()> callback) { m_OnClick = callback; }

    void SetSizeMul(float sizeMul) { m_vSizeMul = sizeMul; }

private:
    std::function<void()> m_OnClick;

    const TCHAR* m_pFrameKeyOff;	
    const TCHAR* m_pFrameKeyOn;

    bool m_bClick;
    bool m_bOnMouse;

    float m_vSizeMul;
    Vector2 resize;
    RECT m_ResizeRect;

};

