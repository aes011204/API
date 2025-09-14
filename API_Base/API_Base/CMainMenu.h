#pragma once
#include "CScene.h"
class CMainMenu :
    public CScene
{
public:
    CMainMenu();
    ~CMainMenu();
public:

    // CScene을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;

private:
    void Render_MovingBG(HDC hdc, float _speed, TCHAR* name, Vector2 size);

private:
    Vector2 m_vLogoSize;
};

