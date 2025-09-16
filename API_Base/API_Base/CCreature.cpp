#include "pch.h"
#include "CCreature.h"
#include "CCamera.h"
#include "CTimeMgr.h"
#include "CLineManager.h"
CCreature::CCreature() : m_ID(CID_END), m_bDead(false), m_tTarget(nullptr), m_eDir(DIR_END),
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
	
	// 낙하속도 상한 설정
	if (m_fSpeedY > 1000.f)
		m_fSpeedY = 1000.f;

	if (m_bJump && m_iPlayerJumpCount < m_iPlayerMaxJump)
	{
		m_fSpeedY = -900.f; 
		// 임의로 준 점프 스피드, 점프할때만 필요하므로 이 때 값을 집어넣는다.
		m_iPlayerJumpCount += 1;
		// 플레이어가 점프를 하는 중일때 점프 하나 증가, 현재 2 이상이 되면 점프 제한
		m_bPlayerLanded = false;
	}


	m_fSpeedY += 3000.f *CTimeMgr::Get_Instance()->GetDeltaTime();
	//! Y속도 += 가속도(중력가속도 * 화면 보정값) * dt : 속도의 적분
	m_vPosition.y += m_fSpeedY * CTimeMgr::Get_Instance()->GetDeltaTime();


	// Collision_Line이 제대로 수행되지 않았을 경우 떨어질 높이를 설정
	m_fGroundY = WINCY + 100.f;

	CLineManager::Get_Instance()->Collision_Line(m_vPosition, &m_fGroundY);

	if (m_fSpeedY >= 0.f
		&& m_vPosition.y + (m_vSize.y / 2.f) >= m_fGroundY)
	{
		m_vPosition.y = m_fGroundY - (m_vSize.y / 2.f);
		m_fSpeedY = 0.f;
		m_iPlayerJumpCount = 0;

		m_bPlayerLanded = true;
		
	}
	cout << m_vPosition.x << endl;

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

void CCreature::Move_EffectFrame()
{
	if (m_tEFFrame.dwTime == 0)
	{
		m_vEFPos = m_vPosition;
	}
	m_tEFFrame.dwTime += CTimeMgr::Get_Instance()->GetDeltaTime();



	if (m_tEFFrame.dwTime >= m_tEFFrame.dwSpeed)
	{
		++m_tEFFrame.iStart;
		
		if (m_tEFFrame.iStart > m_tEFFrame.iEnd)
			m_tEFFrame.iStart = 0;

		m_tEFFrame.dwTime = 0.f;
	}

}