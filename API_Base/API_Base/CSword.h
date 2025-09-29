#pragma once
#include "CWeapon.h"
class CSword :
    public CWeapon
{

    public:
        CSword();
        ~CSword();

        void Initialize();
        int Update();
        void Late_Update();
        void Render(HDC hdc);
        void Release();

        bool m_OnUp = false;
        float radian = 0.f;
        float m_TargetRadian = 0.f;
        float m_OffsetCur = 0.f;
        bool m_InFlip = false;
        bool  m_IsFlipped = false;
        float m_FlipDir = 0.f; // 현재 적용된 오프셋(보간 대상)
        float m_OffsetDst = 0.f; // 목표 오프셋(0 또는 PI)
  

};

