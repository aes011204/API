#include "pch.h"
#include "CCamera.h"
#include "CCreature.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"


CCamera::CCamera() : m_tTargetObj(nullptr), m_fTime(1.f), m_fSpeed(0.f), m_fAccTime(0.f)
{
	//m_vCurLookAt = {}
}

CCamera::~CCamera()
{
}

void CCamera::SetLookAt(Vector2 vLook)
{
	{
		m_vLookAt = vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
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
	if (m_tTargetObj)
	{
		CCreature* creature = dynamic_cast<CCreature*>(m_tTargetObj);
		if (creature->Get_Dead())
		{
			m_tTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_tTargetObj->GetPosition();
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		m_vLookAt.x -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		m_vLookAt.x += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
	{
		m_vLookAt.y -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		m_vLookAt.y += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}


	

	CalDiff();
}

void CCamera::CalDiff()
{

	
	// 이전 프레임과 현제 look 차이 값을 보정해서 현제의 lookat을 구한다

	m_fAccTime += CTimeMgr::Get_Instance()->GetDeltaTime();
	if ( m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
	Vector2 vLookAtDir = m_vLookAt - m_vPrevLookAt;
	m_vCurLookAt = m_vPrevLookAt + vLookAtDir.Nomalize(vLookAtDir) * m_fSpeed * (float)CTimeMgr::Get_Instance()->GetDeltaTime();


	}
	Vector2 vCenter = vWinResolution * .5f;
	
	m_vDiff = m_vCurLookAt - vCenter;

	m_vPrevLookAt = m_vCurLookAt;
	
}


