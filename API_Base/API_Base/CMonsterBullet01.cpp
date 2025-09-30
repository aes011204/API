#include "pch.h"
#include "CMonsterBullet01.h"
#include "CBmpMgr.h"
#include "CCamera.h"

CMonsterBullet01::CMonsterBullet01()
{
}

CMonsterBullet01::~CMonsterBullet01()
{
}

void CMonsterBullet01::Initialize()
{
    CBullet::Initialize();
    m_vSize = { 13,16 };
    m_fSpeed = 300.f;
    m_fSpeedY = 300.f;

    m_iDamage = 1.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/Bat/BansheeBulletSprite.bmp", L"BansheeBullet");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/Bat/BansheeBulletBoomSprite.bmp", L"BansheeBulletBoom");

    m_pFrameKey = L"BansheeBullet";
    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 3;
    m_tFrame.dwSpeed = .3f;
    m_tFrame.dwTime = 0.f;
    m_tFrame.vSize = { 13,16 };

    m_eCurState = IDLE;

    m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, m_vSize, this, true));

}

int CMonsterBullet01::Update()
{
    CBullet::Update();
    if (m_bDead)
        return OBJ_DEAD;

    Motion_Change();


    CCreature::Move_Frame();


    return 0;
}

void CMonsterBullet01::Late_Update()
{
    CBullet::Late_Update();

    if (m_eCurState == DEAD)
    {

        if (m_tFrame.iStart == m_tFrame.iEnd)
            m_bDead = true;
    }


}

void CMonsterBullet01::Render(HDC hDC)
{


    CBullet::Render(hDC);



}

void CMonsterBullet01::Release()
{
    CBullet::Release();

}

void CMonsterBullet01::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
    if (obj->Get_ID() == MONSTER || obj->Get_ID() == BOSS)
        return;
    CBullet::On_Collision(obj, my, other);

}

void CMonsterBullet01::Take_Damage(int _damage)
{
}

void CMonsterBullet01::Motion_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case IDLE:
            m_pFrameKey = L"BansheeBullet";
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.dwSpeed = .3f;
            m_tFrame.dwTime = 0.f;
            m_tFrame.vSize = { 13,16 };
            m_vSize = m_tFrame.vSize;
            break;


        case DEAD:
            m_pFrameKey = L"BansheeBulletBoom";
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 5;
            m_tFrame.dwSpeed = .2f;
            m_tFrame.dwTime = 0.f;
            m_tFrame.vSize = { 20,27 };
            m_vSize = m_tFrame.vSize;
            break;

        }

        m_ePreState = m_eCurState;
    }
}