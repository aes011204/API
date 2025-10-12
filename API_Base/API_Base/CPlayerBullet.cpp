#include "pch.h"
#include "CPlayerBullet.h"
#include "CBmpMgr.h"

CPlayerBullet::CPlayerBullet()
{
}

CPlayerBullet::~CPlayerBullet()
{
}

void CPlayerBullet::Initialize()
{
    CBullet::Initialize();
    m_vSize = { 18,10 };
    m_fSpeed = 800;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Bullet02.bmp", L"Bullet07");
    //CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BossBulletEffect.bmp", L"BossBulletDead");

    m_pFrameKey = L"Bullet07";
    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 0;
    m_tFrame.dwSpeed = .3f;
    m_tFrame.dwTime = 0.f;
    m_tFrame.vSize = { 18,10 };

    m_eCurState = IDLE;

    m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, m_vSize, this, true));

}

int CPlayerBullet::Update()
{
    CBullet::Update();
    if (m_bDead)
        return OBJ_DEAD;

    Motion_Change();


    CCreature::Move_Frame();


    return 0;
}

void CPlayerBullet::Late_Update()
{
    CBullet::Late_Update();

    if (m_eCurState == DEAD)
    {

        if (m_tFrame.iStart == m_tFrame.iEnd)
            m_bDead = true;
    }


}

void CPlayerBullet::Render(HDC hDC)
{


    CBullet::Render(hDC);



}

void CPlayerBullet::Release()
{
    CBullet::Release();

}

void CPlayerBullet::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
    if (obj->Get_ID() == PLAYER )
        return;
    CBullet::On_Collision(obj, my, other);

}

void CPlayerBullet::Take_Damage(int _damage)
{
}

void CPlayerBullet::Motion_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.dwSpeed = .3f;
            m_tFrame.dwTime = 0.f;
            m_tFrame.vSize = { 18,10 };

            m_vSize = m_tFrame.vSize;
            break;


        case DEAD:
            m_pFrameKey = L"BossBulletDead";
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.dwSpeed = .2f;
            m_tFrame.dwTime = 0.f;
            m_tFrame.vSize = { 16,3 };
            m_vSize = m_tFrame.vSize;
            break;

        }

        m_ePreState = m_eCurState;
    }
}