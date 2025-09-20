#include "pch.h"
#include "CTile.h"
#include "CBmpMgr.h"
#include "CCamera.h"
//#include "ScrollMgr.h"

CTile::CTile() : m_iOption(0)
{
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{

	m_vReSize = m_vSize * 3;

	// m_tInfo.fCX = TILECX;
	// m_tInfo.fCY = TILECY;
}

int CTile::Update()
{
	m_vReSize = m_vSize * 3;

	__super::Update_Rec();

	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{


	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vReSize);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Tile");

	//StretchBlt(hDC, RenderPos.x - RenderSize.x * .5f, RenderPos.y - RenderSize.y * .5f,
	//	RenderSize.x, RenderSize.y, hMemDC, m_iDrawID.x * m_vSize.x, m_iDrawID.y * m_vSize.y,
	//	m_vSize.x, m_vSize.y, SRCCOPY);
	GdiTransparentBlt(
		hDC,
		RenderPos.x - RenderSize.x * .5f, 
		RenderPos.y - RenderSize.y * .5f,
		RenderSize.x,  RenderSize.y,
		hMemDC, 
		m_iDrawID.x * m_vSize.x, 
		m_iDrawID.y * m_vSize.y,
		m_vSize.x, m_vSize.y,
		RGB(255, 0, 255));

}

void CTile::Release()
{
}

void CTile::On_Collision(CObj* obj)
{
}
