#include "pch.h"
#include "CButton.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"

CButton::CButton(): m_bClick(false), m_bOnMouse(false), m_vSizeMul(0.f)
{
	ZeroMemory(&m_ResizeRect, sizeof(m_ResizeRect));

}

CButton::~CButton()
{
}

void CButton::Initialize()
{
	resize = m_vSize * m_vSizeMul;
}

int CButton::Update()
{
	CUI::Update_Rect();
    return 0;
}

int CButton::Late_Update()
{
	
	if(true==IsColl())
		return OBJ_DEAD;
	
}

void CButton::Render(HDC hdc)
{



	if (m_bOnMouse)
	{
	HDC	hMemDC =CBmpMgr::Get_Instance()->Find_Img(m_pFrameKeyOn);

	GdiTransparentBlt(hdc,
		m_vPosition.x - resize.x * .5f,
		m_vPosition.y - resize.y * .5f,
		(int)resize.x,
		(int)resize.y,
		hMemDC,
		0,
		0,
		(int)m_vSize.x,
		(int)m_vSize.y,
		RGB(255, 255, 255));		// 제거할 픽셀의 색상

	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKeyOff);

		GdiTransparentBlt(hdc,
			m_vPosition.x - resize.x * .5f,
			m_vPosition.y - resize.y * .5f,
			(int)resize.x,
			(int)resize.y,
			hMemDC,
			0,
			0,
			(int)m_vSize.x,
			(int)m_vSize.y,
			RGB(255, 255, 255));			// 제거할 픽셀의 색상
	}

}

void CButton::Release()
{
}

bool CButton::IsColl()
{
	m_bOnMouse = false;
	m_bClick = false;

	POINT mouse;
	mouse.x = (LONG)CKeyMgr::Get_Instance()->GetMousePos().x;
	mouse.y = (LONG)CKeyMgr::Get_Instance()->GetMousePos().y;

	Update_ResizeRect();

	if (PtInRect(&m_ResizeRect, mouse))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			m_OnClick();
			return true;
		}

		m_bOnMouse = true;
	}
	else
	{
		m_bOnMouse = false;
	}
	return false;
}


void CButton::Update_ResizeRect()
{
	m_ResizeRect.left = m_vPosition.x - (resize.x * .5f);
	m_ResizeRect.top = m_vPosition.y - (resize.y * .5f);
	m_ResizeRect.right = m_vPosition.x + (resize.x * .5f);
	m_ResizeRect.bottom = m_vPosition.y + (resize.y * .5f);

}