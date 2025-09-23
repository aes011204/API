#pragma once
#include "CScene.h"
class CVillage :
    public CScene
{
public:
    CVillage();
    ~CVillage();
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;

private:
    Vector2 m_vSceneSize;

    float m_SoundTime;
};

