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

   // void Render_MovingBG(HDC hdc, float _speed,const TCHAR* name, Vector2 size);
    void Render_MovingBG(HDC hdc, float _speed, const TCHAR* name, Vector2 size, float& accSpeed);
private:
    Vector2 m_vLogoSize;
    float m_fMovePosX1;
    float m_fMovePosX2;
};

