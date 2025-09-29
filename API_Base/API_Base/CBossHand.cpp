#include "pch.h"
#include "CBossHand.h"
#include "CBmpMgr.h"
#include "CCamera.h"
#include "CObjMgr.h"
#include "CTimeMgr.h"


CBossHand::CBossHand() : m_eCurState(HS_END), m_ePreState(HS_END), m_LeftRight(HAND_END), m_isAttack(false), m_bAttack(false)//, m_AttackDone (false)
{
}

CBossHand::~CBossHand()
{
}

void CBossHand::Initialize()
{

	m_fSpeed = 400.f;
	m_fSpeedY = 400.f;

	m_iDamage = 10.f;
	m_ID = BOSS;

	m_vPosition = { 300,300 };
	m_vSize = { 171, 189 };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/HandAttack.bmp", L"HandAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/HandIdle.bmp", L"HandIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/LaserHeadL.bmp", L"LaserHeadL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/LaserHeadR.bmp", L"LaserHeadR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/LaserBody.bmp", L"LaserBody");

	m_pFrameKey = L"HandIdle";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 9;
	m_tFrame.dwSpeed = .2f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 171, 189 };

	m_eCurState = IDLE;


	m_tEFFrame.iStart = 0;
	m_tEFFrame.iEnd = 6;
	m_tEFFrame.dwSpeed = .2f;
	m_tEFFrame.dwTime = 0.f;
	m_tEFFrame.vSize = { 96,142 };


		m_tEFFrameLR.iStart = 0;
		m_tEFFrameLR.iEnd = 6;
		m_tEFFrameLR.dwSpeed = .2f;
		m_tEFFrameLR.dwTime = 0.f;
		m_tEFFrameLR.vSize = { 81,132 };


	if (m_LeftRight == HAND_RIGHT)
	{
		m_vPosition = { 900,700 };
		m_vCollider.push_back(CColliderComp(ColliderType::ATTACK, { -450,0 }, { 171 * 5.5f,189 * .5f }, this));
	}
	else
	{
		m_vPosition = { 200,700 };
		m_vCollider.push_back(CColliderComp(ColliderType::ATTACK, { 450,0 }, { 171 * 5.5f,189 * .5f }, this));
	}

}

int CBossHand::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_isAttack == true)
	{
		Do_Attack();
		
	}

	Motion_Change();


	CCreature::Move_Frame();

	__super::EffUpdate();
	__super::UpdateColl(m_vPosition);
	return 0;
}

void CBossHand::Late_Update()
{

}

void CBossHand::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);


	Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vSize);

	// 스프라이트시트에서 가져올 소스 사각형(프레임)
	int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스
	int height=0;

	if (m_LeftRight == HAND_LEFT)
	{
		height = (int)m_vSize.y;
	}
	else if (m_LeftRight == HAND_RIGHT)
	{
		height = 0;
	}


	// 투명색 키(마젠타)로 블릿
	GdiTransparentBlt(
		hDC,
		centerS.x - RenderSize.x * 0.5f,
		centerS.y - RenderSize.y * 0.5f,
		RenderSize.x, RenderSize.y,
		hMemDC, srcX, height, (int)m_vSize.x, (int)m_vSize.y,
		RGB(255, 0, 255));


	/*if (m_eCurState == ATTACK)
	{
		Vector2 size = { 81,132 };
		Vector2 pos = { m_vPosition.x - 50, m_vPosition.y };
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"LaserHeadR");


		Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(pos);
		Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(size);
		GdiTransparentBlt(
			hDC,
			centerS.x - RenderSize.x * 0.5f,
			centerS.y - RenderSize.y * 0.5f,
			RenderSize.x, RenderSize.y,
			hMemDC, 0, 0, size.x, size.y,
			RGB(255, 0, 255));

	}*/

	__super::RenderColl(hDC, m_vPosition);
	__super::EffRender(hDC);
}

void CBossHand::Release()
{
}

void CBossHand::Do_Attack()
{
	// 받아온 y 포지션으로 한 번쏘는 거 
	float m_AttackSpeed = 800.f;

	if (m_AttackPos.y + 10 >= m_vPosition.y && m_AttackPos.y - 10 <= m_vPosition.y)
	{
		m_eCurState = ATTACK;
		Motion_Change();
		if (m_LeftRight == HAND_LEFT)
		{
			if (m_tFrame.iStart == 10)
			{
				m_vEffect.push_back(CEffectComp({ 120,5 }, this, m_tEFFrameLR, { m_tEFFrameLR.vSize.x,m_tEFFrameLR.vSize.y }, L"LaserHeadL"));
				m_vEffect.push_back(CEffectComp({ 100 + m_tEFFrame.vSize.x  ,0.f }, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"LaserBody"));
		
				for (int i = 2; i < 10;i++)
				{
				m_vEffect.push_back(CEffectComp({ 100 + m_tEFFrame.vSize.x *i ,0.f }, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"LaserBody"));
		
				}
				m_bAttack = true;
			}
		
		}
		else if (m_LeftRight == HAND_RIGHT)
		{
			if (m_tFrame.iStart == 10)
			{
				m_vEffect.push_back(CEffectComp({ -120,5 }, this, m_tEFFrameLR, { m_tEFFrameLR.vSize.x,m_tEFFrameLR.vSize.y }, L"LaserHeadR"));
				
					m_vEffect.push_back(CEffectComp({-100 - m_tEFFrame.vSize.x  ,0.f }, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y },L"LaserBody"));
		
				for (int i = 2; i < 10;i++)
				{
					m_vEffect.push_back(CEffectComp({ -100 - m_tEFFrame.vSize.x * i ,0.f }, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"LaserBody"));
		
				}
				m_bAttack = true;
			}

		}


		if (m_tFrame.iStart >= m_tFrame.iEnd && m_eCurState == ATTACK)
		{
			m_eCurState = IDLE;
			m_isAttack = false;
			m_bAttack = false;
		}
	}
	else if (m_AttackPos.y >= m_vPosition.y)
	{
		m_vPosition.y += m_AttackSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
	}
	else if (m_AttackPos.y <= m_vPosition.y)
	{
		m_vPosition.y -= m_AttackSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
	}



}

void CBossHand::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	if (obj->Get_ID() == PLAYER&& other.GetType() == ColliderType::BODY)
	{
		if (m_bAttack == true)
		{
			dynamic_cast <CCreature*>(obj)->Take_Damage(m_iDamage);
		}
	}
}

void CBossHand::Take_Damage(int _damage)
{
}


void CBossHand::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_pFrameKey = L"HandIdle";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 9;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 171, 189 };

			m_vSize = m_tFrame.vSize;
			break;


		case ATTACK:
			m_pFrameKey = L"HandAttack";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 17;
			m_tFrame.dwSpeed = .1f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 195,213 };
			m_vSize = m_tFrame.vSize;
			break;

		}

		m_ePreState = m_eCurState;
	}
}