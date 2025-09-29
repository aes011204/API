#include "pch.h"
#include "CInventoryCell.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CItem.h"

CInventoryCell::CInventoryCell()
{
}

CInventoryCell::~CInventoryCell()
{
}

void CInventoryCell::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/inven/Cell.bmp", L"Cell");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/inven/Cell_On.bmp", L"Cell_On");
	m_vSize = {57,57};
	m_pFrameKeyOn = L"Cell_On";
	m_pFrameKeyOff = L"Cell";
}

int CInventoryCell::Update()
{
	Update_Rect();

	return 0;
}

int CInventoryCell::Late_Update()
{
	// 인밴토리 셀은 인벤토리 ui가 관리 하기떄문에 return 써도 됨
	//int tmp = 0;
	//if (IsColl() == true)
	//	tmp = -1;
	//else
	//	tmp = 0;
	return 0/*IsColl()*/;
}

void CInventoryCell::Render(HDC hdc)
{
	if (m_bOnMouse)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKeyOn);

		GdiTransparentBlt(hdc,
			m_vPosition.x - m_vSize.x * .5f,
			m_vPosition.y - m_vSize.y * .5f,
			(int)m_vSize.x,
			(int)m_vSize.y,
			hMemDC,
			0,
			0,
			(int)m_vSize.x,
			(int)m_vSize.y,
			RGB(255, 0, 255));		// 제거할 픽셀의 색상
		
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKeyOff);

		GdiTransparentBlt(hdc,
			m_vPosition.x - m_vSize.x * .5f,
			m_vPosition.y - m_vSize.y * .5f,
			(int)m_vSize.x,
			(int)m_vSize.y,
			hMemDC,
			0,
			0,
			(int)m_vSize.x,
			(int)m_vSize.y,
			RGB(255, 0, 255));			// 제거할 픽셀의 색상
	}
}

void CInventoryCell::Release()
{
}

bool CInventoryCell::IsColl(POINT mouse)
{
	//m_bOnMouse = false;
	m_bClick = false;

	//ScreenToClient(g_hWnd, &mouse);
	

	if (PtInRect(&m_tRect, mouse))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			//m_OnClick();
		}

		m_bOnMouse = true;
		return true;
	}
	else
	{
		m_bOnMouse = false;
	}
	return false;
}

void CInventoryCell::KeyInput()
{
}

void CInventoryCell::RenderIcon(HDC hdc, CItem* item)
{
	if (item == nullptr)
		return;
	Vector2 iconSize = item->Get_IconImgSize();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(item->Get_IconKey());

	GdiTransparentBlt(hdc,
		m_vPosition.x - iconSize.x * .5f,
		m_vPosition.y - iconSize.y * .5f,
		(int)iconSize.x,
		(int)iconSize.y,
		hMemDC,
		0,
		0,
		(int)iconSize.x,
		(int)iconSize.y,
		RGB(255, 0, 255));			// 제거할 픽셀의 색상
}

bool CInventoryCell::IsColl()
{
	return false;
}

 