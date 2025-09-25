#include "pch.h"
#include "CCreature.h"
#include "CCamera.h"
#include "CTimeMgr.h"
#include "CLineManager.h"
#include "CCollisionMgr.h"
CCreature::CCreature() : m_bDead(false), m_tTarget(nullptr),  m_eDir(DIR_END),m_iDamage(0), m_iLevel(0), m_iMaxHP(0), m_iHP(0),
			m_bJump(false),
			m_fSpeedY(0.f),
			m_iPlayerJumpCount(0),
			m_iPlayerMaxJump(2),
			m_fGroundY(0.f),
			m_bPlayerLanded(false)
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));

}

CCreature::~CCreature()
{
	Release();
}

void CCreature::Initialize()
{
}

int CCreature::Update()
{

	//bool groundedPrev = m_bPlayerLanded;
	//m_bPlayerLanded = false;

	// 낙하속도 상한 설정
	if (m_fSpeedY > 1000.f)
		m_fSpeedY = 1000.f;


	if (m_bJump && m_iPlayerJumpCount < m_iPlayerMaxJump)
	{
		m_fSpeedY = -850.f; 
		// 임의로 준 점프 스피드, 점프할때만 필요하므로 이 때 값을 집어넣는다.
		m_iPlayerJumpCount += 1;
		// 플레이어가 점프를 하는 중일때 점프 하나 증가, 현재 2 이상이 되면 점프 제한
		
		m_bPlayerLanded = false;
		//groundedPrev = false;
	}

	//if(groundedPrev == false)
	if(m_bPlayerLanded== false)
	{
		m_fSpeedY += 2500.f * CTimeMgr::Get_Instance()->GetDeltaTime();
		//! Y속도 += 가속도(중력가속도 * 화면 보정값) * dt : 속도의 적분
		m_vPosition.y += m_fSpeedY * CTimeMgr::Get_Instance()->GetDeltaTime();
	}
	//else
	//{
	//	m_fSpeedY = 0.f;
	//}


	// Collision_Line이 제대로 수행되지 않았을 경우 떨어질 높이를 설정
	m_fGroundY = WINCY + 500.f;

	CLineManager::Get_Instance()->Collision_Line(m_vPosition, &m_fGroundY);

	//bool landedThisFrame = false;
	if (m_fSpeedY >= 0.f
		&& m_vPosition.y + (m_vSize.y / 2.f) >= m_fGroundY)
	{
		m_vPosition.y = m_fGroundY - (m_vSize.y / 2.f);
		m_fSpeedY = 0.f;
		m_iPlayerJumpCount = 0;

		//landedThisFrame = true;

		m_bJump = false;
	}
	m_bPlayerLanded = false;
	//m_bPlayerLanded = m_bPlayerLanded || landedThisFrame;
	

	return 0;
}

void CCreature::Late_Update()
{
	
}

void CCreature::Render(HDC hdc)
{
	// 디버그 용
	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);


	Rectangle(hdc, RenderPos.x - m_vSize.x*.5f,
		RenderPos.y - m_vSize.y * .5f,
		RenderPos.x + m_vSize.x * .5f,
		RenderPos.y + m_vSize.y * .5f);

}

void CCreature::Release()
{

}
void CCreature::Landed_Platform(CObj* pObj, CColliderComp& my, CColliderComp& other)
{
	float fX = 0.f, fY = 0.f;

	

	if (CCollisionMgr::Check_Rect(my, other, &fX, &fY))
	{
		if (fX >= fY)	// 상하 충돌
		{
			if (m_vPosition.y <= pObj->GetPosition().y && m_fSpeedY >= 0.f)		//	상 충돌
			{
				m_fSpeedY = 0.f;
				m_iPlayerJumpCount = 0;
				//m_vPosition.y = pObj->GetPosition().y - (pObj->GetSize().y / 2.f + m_vSize.y / 2.f)+.1f;
				SetPosition({GetPosition().x ,GetPosition().y - fY+1}); //(** 일부로 1 을 더해서 계속 충돌 체크가 가능하도록 함 덜덜 떨리는 현상 없엊;ㅁ)

				m_bPlayerLanded = true;
				m_bJump = false;

			}
			else //-------------------------------------------	하 충돌
			{
				//m_fSpeedY = 0.f;
				//m_vPosition.y = pObj->Get_Position().y + (pObj->Get_Size().y / 2.f + m_vSize.y / 2.f);
				//! 천장 필요하면 사용하기
				//! 

			}
		}

		if (fX < fY)		// 좌우 충돌
		{
			//if (m_vPosition.x <= pObj->GetPosition().x)		//	좌 충돌
			//{
			//	m_vPosition.x = pObj->GetPosition().x - (pObj->GetSize().x / 2.f + m_vSize.x / 2.f);
			//}
			//else //-------------------------------------------	우 충돌
			//{
			//	m_vPosition.x = pObj->GetPosition().x + (pObj->GetSize().x / 2.f + m_vSize.x / 2.f);
			//}
		}
	}
}

void CCreature::Move_Frame()
{
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetDeltaTime();

	if (m_tFrame.dwTime >= m_tFrame.dwSpeed)
	{
		++m_tFrame.iStart;
		//_tprintf(_T("executed. %d\n"), m_tFrame.iStart);

		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;

		m_tFrame.dwTime = 0.f;
	}

 }

//void CCreature::Move_EffectFrame()
//{
//	if (m_tEFFrame.dwTime == 0)
//	{
//		m_vEFPos = m_vPosition;
//	}
//	m_tEFFrame.dwTime += CTimeMgr::Get_Instance()->GetDeltaTime();
//
//
//
//	if (m_tEFFrame.dwTime >= m_tEFFrame.dwSpeed)
//	{
//		++m_tEFFrame.iStart;
//		
//		if (m_tEFFrame.iStart > m_tEFFrame.iEnd)
//			m_tEFFrame.iStart = 0;
//
//		m_tEFFrame.dwTime = 0.f;
//	}
//
//}


