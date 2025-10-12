#include "pch.h"
#include "CShopCell.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CItem.h"
#include "CWeapon.h"

CShopCell::CShopCell()
{
}

CShopCell::~CShopCell()
{
}

void CShopCell::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Shop/ShopItem.bmp", L"ShopItem");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Shop/ShopItem_Selected.bmp", L"ShopItem_Selected");
	m_vImgSize = { 107,23 };
	m_vSize = m_vImgSize*3;
	m_pFrameKeyOn = L"ShopItem_Selected";
	m_pFrameKeyOff = L"ShopItem";
}

int CShopCell::Update()
{
	Update_Rect();

	return 0;
}

int CShopCell::Late_Update()
{
	// 인밴토리 셀은 인벤토리 ui가 관리 하기떄문에 return 써도 됨
	//int tmp = 0;
	//if (IsColl() == true)
	//	tmp = -1;
	//else
	//	tmp = 0;
	return 0/*IsColl()*/;
}

void CShopCell::Render(HDC hdc)
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
			(int)m_vImgSize.x,
			(int)m_vImgSize.y,
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
			(int)m_vImgSize.x,
			(int)m_vImgSize.y,
			RGB(255, 0, 255));			// 제거할 픽셀의 색상
	}
}

void CShopCell::Release()
{
}

bool CShopCell::IsColl(POINT mouse)
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

void CShopCell::KeyInput()
{
}

void CShopCell::RenderIcon(HDC hdc, CItem* item, Vector2 pos)
{
	if (item == nullptr)
		return;
	Vector2 iconSize = item->Get_IconImgSize();
	if (pos.x == 0 && pos.y == 0)
	{
		pos = m_vPosition;
	}

	Vector2 shopIconPos = { m_vSize.x * .2f,(float)m_vPosition.y };

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(item->Get_IconKey());

	if (dynamic_cast<CWeapon*>(item)->GetWeaponType() == CWeapon::GUN)
	{
		Vector2 iconReSize = iconSize * 2;

		GdiTransparentBlt(hdc,
			shopIconPos.x - iconReSize.x * .5f,
			shopIconPos.y - iconReSize.y * .5f,
			(int)iconReSize.x,
			(int)iconReSize.y,
			hMemDC,
			0,
			0,
			(int)iconSize.x,
			(int)iconSize.y,
			RGB(255, 0, 255));
	}
	else
	{

		GdiTransparentBlt(hdc,
			shopIconPos.x - iconSize.x * .5f,
			shopIconPos.y - iconSize.y * .5f,
			(int)iconSize.x,
			(int)iconSize.y,
			hMemDC,
			0,
			0,
			(int)iconSize.x,
			(int)iconSize.y,
			RGB(255, 0, 255));			// 제거할 픽셀의 색상
	}

	WCHAR buffer[32];
	//swprintf_s(buffer, _countof(buffer), L"%s", item->GetName());
	_tcsncpy_s(buffer, _countof(buffer), item->GetName(), _TRUNCATE);
	//RECT rc = { redPos.x,redPos.y, redPos.x + redSize.x, redPos.y + redSize.y };
	CUI::text(hdc, m_tRect, buffer, 30, 20, 500);

	WCHAR buffer1[32];
	swprintf_s(buffer1, 32, L"%d", item->Get_Money());

	RECT rc = { m_tRect.left+100,m_tRect.top+10, m_tRect.right+100,m_tRect.bottom +10 };
	CUI::text(hdc, rc, buffer1, 20, 10, 500);
}

bool CShopCell::IsColl()
{
	return false;
}

