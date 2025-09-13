#include "pch.h"
#include "CCreature.h"
#include "CCamera.h"
#include "CTimeMgr.h"
CCreature::CCreature() : m_ID(CID_END), m_bDead(false), m_tTarget(nullptr), m_eDir(DIR_END)
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

	//_tprintf(_T("dwTim ->. %d\n"), m_tFrame.dwTime);


	if (m_tFrame.dwTime >= m_tFrame.dwSpeed)
	{
		++m_tFrame.iStart;
		//_tprintf(_T("executed. %d\n"), m_tFrame.iStart);

		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;

		m_tFrame.dwTime = 0.f;
	}

}