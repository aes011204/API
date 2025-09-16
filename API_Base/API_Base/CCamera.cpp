#include "pch.h"
#include "CCamera.h"
#include "CCreature.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include <algorithm>

CCamera::CCamera() : m_tTargetObj(nullptr), m_fTime(1.f), m_fSpeed(0.f), m_fAccTime(0.f), m_fZoom(1.f)
{

}

CCamera::~CCamera()
{
}

void CCamera::SetLookAt(Vector2 vLook)
{
	{
		m_vLookAt = vLook;
		//float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		//m_fSpeed = fMoveDist / m_fTime;
		//m_fAccTime = 0.f;
	}
}

void CCamera::Bootstrap(const Vector2& startLookAt)
{
	m_vLookAt = startLookAt;
	m_vCurLookAt = startLookAt;
	m_vPrevLookAt = startLookAt;

	m_fAccTime = 0.f;
	m_fSpeed = 0.f;

	Vector2 vCenter = { WINCX * .5f, WINCY * .5f };
	m_vDiff = m_vCurLookAt - vCenter;   // ★ 첫 프레임부터 정확히 맞춤
}

void CCamera::Update()
{
	CalDiff();
	
	//카메라 가 화면밖으로 나가지 않게 하는 보정  
	if (m_tTargetObj)
	{
		CCreature* creature = dynamic_cast<CCreature*>(m_tTargetObj);
		
		if (creature->Get_Dead())
		{
			m_tTargetObj = nullptr;
		}
		else
		{
			m_vCurLookAt = m_tTargetObj->GetPosition();
		}
	}
	//if (m_vBackSize.x && m_vBackSize.y)
	//{
	//	if (m_vCurLookAt.x <= 0 + WINCX * .5f)
	//	{
	//		m_vCurLookAt.x = 0 + WINCX * .5f;
	//	}
	//	if (m_vCurLookAt.y <= 0 + WINCY * .5f)
	//	{
	//		m_vCurLookAt.y = 0 + WINCY * .5f;
	//	}
	//	if (m_vCurLookAt.x >= m_vBackSize.x - WINCX * .5f)
	//	{
	//		m_vCurLookAt.x = m_vBackSize.x - WINCX * .5f;
	//	}
	//	if (m_vCurLookAt.y >= m_vBackSize.y - WINCY * .5f)
	//	{
	//		m_vCurLookAt.y = m_vBackSize.y - WINCY * .5f;
	//	}
	//}

	// 화면 크기가 스크린 보다 작을 경우 대비 필요
	if (m_vBackSize.x)
		m_vCurLookAt.x = std::clamp(m_vCurLookAt.x, (WINCX / m_fZoom) * .5f, m_vBackSize.x - (WINCX / m_fZoom) * .5f);
	if (m_vBackSize.y)
		m_vCurLookAt.y = std::clamp(m_vCurLookAt.y, (WINCY / m_fZoom) * .5f, m_vBackSize.y - (WINCY / m_fZoom) * .5f);

	//TODO : 미세떨림 보정 기능추가
	

	if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		//const int STEP = 2;
		const float STEP = 1.25f;  // 한 번에 25% 확대
		const float MINZ = 0.25f;  // 최소/최대 보호 (선택)
		const float MAXZ = 4.0f;

		m_fZoom *= STEP;
		if (m_fZoom > MAXZ) m_fZoom = MAXZ;  // 클램프
		if (m_fZoom < MINZ) m_fZoom = MINZ;
	}
	

}

void CCamera::CalDiff()
{

	
	// 이전 프레임과 현제 look 차이 값을 보정해서 현제의 lookat을 구한다

	//m_fAccTime += CTimeMgr::Get_Instance()->GetDeltaTime();
	//if ( m_fTime <= m_fAccTime)
	//{
	//	m_vCurLookAt = m_vLookAt;
	//}
	//else
	//{
	//Vector2 vLookAtDir = m_vLookAt - m_vPrevLookAt;
	//m_vCurLookAt = m_vPrevLookAt + vLookAtDir.Nomalize(vLookAtDir) * m_fSpeed * (float)CTimeMgr::Get_Instance()->GetDeltaTime();
	//
	//
	//}
	//Vector2 vCenter = vWinResolution * .5f;
	//
	//m_vDiff = m_vCurLookAt - vCenter;
	//
	//m_vPrevLookAt = m_vCurLookAt;


	//const float dt = CTimeMgr::Get_Instance()->GetDeltaTime();
	//// t = 1 - exp(-k*dt) : 프레임레이트에 덜 민감, k=6 정도가 따라가는 감도 적당
	//const float t = 1.f - expf(-6.f * dt);
	//
	//// ★ 한 줄! 현재값을 목표로 스무스하게
	//m_vCurLookAt += (m_vLookAt - m_vCurLookAt) * t;
}


