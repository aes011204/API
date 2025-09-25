#include "pch.h"
#include "CNonCreature.h"
#include "CCamera.h"
#include "CCreature.h"
#include "CTimeMgr.h"

CNonCreature::CNonCreature()
{
}

CNonCreature::~CNonCreature()
{
}

void CNonCreature::Initialize()
{
}

int CNonCreature::Update()
{
	return 0;
}

void CNonCreature::Late_Update()
{
}

void CNonCreature::Render(HDC hdc)
{
	//Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	//Vector2 RenderSize = CCamera::Get_Instance()->GetRenderPos(m_vSize);

	//Rectangle(hdc, RenderPos.x - RenderSize.x*.5f,
	//	RenderPos.y - RenderSize.y * .5f,
	//	RenderPos.x + RenderSize.x,
	//	RenderPos.y + RenderSize.y);

	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	float zoom = CCamera::Get_Instance()->GetZoom();

	float RenderSizeX = m_vSize.x * zoom;
	float RenderSizeY = m_vSize.y * zoom;
	// ÁÂ»ó´Ü ±âÁØ
	float LeftTopX = RenderPos.x - RenderSizeX * .5f;
	float LeftTopY = RenderPos.y - RenderSizeY * .5f;

	Rectangle(hdc, LeftTopX, LeftTopY, LeftTopX + RenderSizeX, LeftTopY + RenderSizeY);



}

void CNonCreature::Release()
{
}

void CNonCreature::Move_Frame()
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