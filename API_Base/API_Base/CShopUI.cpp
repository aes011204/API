#include "pch.h"
#include "CShopUI.h"
#include "CBmpMgr.h"

CShopUI::CShopUI() : m_bOnShop(false)
{
}

CShopUI::~CShopUI()
{
}

void CShopUI::Initialize()
{

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Shop/ShopBase.bmp", L"ShopBase");
    m_vPosition = { WINCX * .2f + 10,WINCY * .5f };	// 객체의 위치, 중점
    m_ImgSize = { 122,188 };
    m_vSize = m_ImgSize*3;


}

int CShopUI::Update()
{
    Update_Rect();
    return 0;
}

int CShopUI::Late_Update()
{
    return 0;
}

void CShopUI::Render(HDC hdc)
{
    if (m_bOnShop)
    {

        HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"ShopBase");

        StretchBlt(hdc, m_tRect.left, m_tRect.top, m_vSize.x, m_vSize.y, hMemDC, 0, 0, m_ImgSize.x, m_ImgSize.y, SRCCOPY);
    
    }
}

void CShopUI::Release()
{
}

bool CShopUI::IsColl()
{
    return false;
}
