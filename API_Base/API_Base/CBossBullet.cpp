#include "pch.h"
#include "CBossBullet.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"

CBossBullet::CBossBullet() :tmpboo(false),endtime(0.f)
{
}

CBossBullet::~CBossBullet()
{
}

void CBossBullet::Initialize()
{
    CBullet::Initialize();
    m_vSize = { 62,190 };
    m_fSpeed = 800.f;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/SwordEffect.bmp", L"SwordEffect");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossBulletEffect.bmp", L"BossSword");

    m_tEffFrame.iStart = 0;
    m_tEffFrame.iEnd = 2;
    m_tEffFrame.dwSpeed = .3f;
    m_tEffFrame.dwTime = 0.f;
    m_tEffFrame.vSize = { 146,200 };

    delayT = 4.f;
    delayTMax = delayT;
    
    m_iDamage = 3;

    m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, m_vSize, this));
    m_vEffect.push_back(CEffectComp({ 0,0 }, this, m_tEffFrame, L"SwordEffect"));

    endtime = m_tEffFrame.dwSpeed * (m_tEffFrame.iEnd + 1);
}

int CBossBullet::Update()
{
    CBullet::Update();

    Vector2 pos = CObjMgr::Get_Instance()->Get_Player()->GetPosition();
    m_vDirection = pos - m_vPosition;
    m_vDirection=m_vDirection.GetNomalized();

   // Motion_Change();
	delayT -= CTimeMgr::Get_Instance()->GetDeltaTime();
	if (delayT >= 0)
	{
		tmpDir = m_vDirection;
		//cout << m_vDirection.x << " , " << m_vDirection.x  << endl;
		if (delayT <= 0)
			delayT = -1;
	}

	if (m_eCurState == DEAD)
	{
		endtime -= CTimeMgr::Get_Instance()->GetDeltaTime();
		if (endtime > 0)
		{
			if (tmpboo == false)
			{
				m_vEffect.push_back(CEffectComp({ 0,0 }, this, m_tEffFrame, L"SwordEffect"));
				tmpboo = true;

			}
		}
        else
            m_bDead = true;
		//tmp = CEffectComp({ 0,0 }, this, m_tEffFrame, L"SwordEffect");
   
	}

	__super::EffUpdate();
	CCreature::Move_Frame();
    //if (m_bDead)
    //    return OBJ_DEAD;
    if (m_bDead)
        return OBJ_DEAD;
    return 0;
}

void CBossBullet::Late_Update()
{


    if (m_eCurState == DEAD)
        return;

    if (delayT <= 0)
    {
       // cout << tmpDir.x << " , " << tmpDir.x  << endl;
        m_vPosition += tmpDir * (m_fSpeed * (float)CTimeMgr::Get_Instance()->GetDeltaTime());
    }


}

void CBossBullet::Render(HDC hDC)
{


  //  CBullet::Render(hDC);
    __super::RenderColl(hDC, m_vPosition);
    __super::EffRender(hDC);


}

void CBossBullet::Release()
{
    CBullet::Release();

}


void CBossBullet::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
    if (obj->Get_ID() == MONSTER || obj->Get_ID() == BOSS)
        return;

    switch (OBJID id = obj->Get_ID())
    {
    case PLAYER:
    {
        dynamic_cast <CCreature*> (obj)->Take_Damage(m_iDamage);
    }
    break;
    case PLATFORM:
    {
       // m_bDead = true;
    }
    break;
    case WALL:
    {

        if (my.GetColPosition().x >= other.Get_Rect()->left
            && my.GetColPosition().y >= other.Get_Rect()->top
            && my.GetColPosition().x <= other.Get_Rect()->right
            && my.GetColPosition().y <= other.Get_Rect()->bottom)
        {
  
             m_eCurState = DEAD;


        }
       
    }
    break;
    default:
        break;
    }

}

void CBossBullet::Take_Damage(int _damage)
{
}

void CBossBullet::Motion_Change()
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
            m_tFrame.vSize = { 39,39 };
            m_vSize = m_tFrame.vSize;
            break;

        }

        m_ePreState = m_eCurState;
    }
}