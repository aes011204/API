#include "pch.h"
#include "CMonsterBullet.h"
#include "CBmpMgr.h"
#include "CCamera.h"

CMonsterBullet::CMonsterBullet()
{
}

CMonsterBullet::~CMonsterBullet()
{
}

void CMonsterBullet::Initialize()
{
    CBullet::Initialize();
    m_vSize = { 39,39 };

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossBullet.bmp", L"BossBullet");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossBulletEffect.bmp", L"BossBulletDead");

    m_pFrameKey = L"BossBullet";
    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 1;
    m_tFrame.dwSpeed = .3f;
    m_tFrame.dwTime = 0.f;
    m_tFrame.vSize = { 39,39 };

    m_eCurState = IDLE;

    m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, m_vSize, this ,true));

}

int CMonsterBullet::Update()
{
    CBullet::Update();
    if (m_bDead)
        return OBJ_DEAD;

    Motion_Change();


    CCreature::Move_Frame();


    return 0;
}

void CMonsterBullet::Late_Update()
{
    CBullet::Late_Update();

    if (m_eCurState == DEAD)
    {

        if (m_tFrame.iStart == m_tFrame.iEnd)
            m_bDead = true;
    }


}

void CMonsterBullet::Render(HDC hDC)
{


    CBullet::Render(hDC);



}

void CMonsterBullet::Release()
{
    CBullet::Release();

}

void CMonsterBullet::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
    if (obj->Get_ID() == MONSTER || obj->Get_ID() == BOSS)
        return;
    CBullet::On_Collision(obj, my, other);

}

void CMonsterBullet::Take_Damage(int _damage)
{
}

void CMonsterBullet::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 1;
            m_tFrame.dwSpeed = .3f;
            m_tFrame.dwTime = 0.f;
            m_tFrame.vSize = { 39,39 };

			m_vSize = m_tFrame.vSize;
			break;


		case DEAD:
            m_pFrameKey = L"BossBulletDead";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = {  39,39 };
			m_vSize = m_tFrame.vSize;
			break;

		}

		m_ePreState = m_eCurState;
	}
}