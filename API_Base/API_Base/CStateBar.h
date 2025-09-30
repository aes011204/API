#pragma once
#include "CUI.h"

class CStateBar :
    public CUI
{
public:
    CStateBar();
    virtual ~CStateBar();

    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    int Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;
    bool IsColl() override;

    void HPBarRender(HDC hdc, const TCHAR* back, const TCHAR* base, Vector2 pos, Vector2 size, Vector2 resize);

   // void HPBarRender(HDC hdc, const TCHAR* back, const TCHAR* base, Vector2 pos, Vector2 size);

   // void HPBarRender(const TCHAR* back, const TCHAR* base);

 

private:
    int TargetCurInfo;
    int TargetMaxInfo;
    int OtherInfo;


};

