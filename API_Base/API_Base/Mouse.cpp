#include "pch.h"
#include "Mouse.h"
#include "CBmpMgr.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
	Release();
}

void Mouse::Initialize()
{

	m_ID = MOUSE;
	m_vSize = { 63,63 };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ShootingCursor.bmp", L"ShootingCursor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BasicCursor.bmp", L"BasicCursor");

}

int Mouse::Update()
{
	if (isShoot == 0)
	{
		m_vSize = { 27,33 };
	}
	else
	{
		m_vSize = { 63,63 };
	}
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	m_vPosition.x = (float)ptMouse.x;
	m_vPosition.y = (float)ptMouse.y;


	__super::Update_Rec();

	ShowCursor(false);

	return OBJ_NOEVENT;
}

void Mouse::Late_Update()
{

}

void Mouse::Render(HDC hDC)
{
	if (isShoot == 0)
	{

		m_pFrameKey = L"BasicCursor";
	}
	else
	{
		m_pFrameKey = L"ShootingCursor";
		
	}
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	Vector2 centerS = (m_vPosition);
	Vector2 RenderSize = (m_vSize);

	// Åõ¸í»ö Å°(¸¶Á¨Å¸)·Î ºí¸´
	GdiTransparentBlt(
		hDC,
		centerS.x - RenderSize.x * 0.5f,
		centerS.y - RenderSize.y * 0.5f,
		RenderSize.x, RenderSize.y,
		hMemDC, 0, 0, (int)m_vSize.x, (int)m_vSize.y,
		RGB(255, 0, 255));


}

void Mouse::Release()
{
}

void Mouse::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
}
