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
	m_vSize.x = TILECX;
	m_vSize.y = TILECY;

	// m_tInfo.fCX = TILECX;
	// m_tInfo.fCY = TILECY;
}

int CTile::Update()
{

	__super::Update_Rec();

	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{
	// int iScrollX = (int)ScrollMgr::Get_Instance()->Get_ScrollX();
	// int iScrollY = (int)ScrollMgr::Get_Instance()->Get_ScrollY();
	//

	//HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Tile");
	//BitBlt(hDC,
	//	m_tRect.left /* + iScrollX*/,
	//	m_tRect.top /* + iScrollY*/,
	//	TILECX,
	//	TILECY,
	//	hMemDC,
	//	m_iDrawID.x * TILECX,
	//	m_iDrawID.y * TILECX,
	//	SRCCOPY);



	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vSize*2);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Tile");

	//StretchBlt(hDC, RenderPos.x - RenderSize.x * .5f, RenderPos.y - RenderSize.y * .5f,
	//	RenderSize.x, RenderSize.y, hMemDC, m_iDrawID.x * m_vSize.x, m_iDrawID.y * m_vSize.y,
	//	m_vSize.x, m_vSize.y, SRCCOPY);
	GdiTransparentBlt(
		hDC,
		RenderPos.x - RenderSize.x * .5f, 
		RenderPos.y - RenderSize.y * .5f,
		RenderSize.x, RenderSize.y, 
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
