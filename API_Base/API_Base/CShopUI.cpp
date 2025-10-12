#include "pch.h"
#include "CShopUI.h"
#include "CBmpMgr.h"
#include "CShopCell.h"
#include "CShop.h"
#include "CAbstractFactory.h"
#include "CKeyMgr.h"
#include "CNonCreature.h"

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

    Vector2 ShopSlotPos = { m_vPosition.x ,m_vPosition.y -150 };
    for (int i = 0; i < 4;i++)
    {
        m_ShopItem[i] = CAbstractFactory<CShopCell>::CreateUI({ ShopSlotPos.x , ShopSlotPos.y +i*70+10 });


    }


}

int CShopUI::Update()
{
        if (m_bDead == true)
            return -1;
    if (m_bOnShop)
    {
        GetCursorPos(&mouse);
        ScreenToClient(g_hWnd, &mouse);

        //auto* shop = dynamic_cast<CShop*>(m_tNpcTarget);
        //if (!shop) return -1; // 상점 NPC가 아니면 아무 것도 안 함

        for (int i = 0; i < 4;i++)
        {
            m_ShopItem[i]->Update();
            CShopCell* cell = dynamic_cast<CShopCell*>(m_ShopItem[i]);
            if (cell->IsColl(mouse))
            {
                if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
                {
                    // 구매
                    dynamic_cast<CShop*>(m_tNpcTarget)->Buy_Item(i);
                }
            }
        }
    }
    Update_Rect();
    return 0;
}

int CShopUI::Late_Update()
{
 
    if (m_bDead == true)
        return -1;
    if (m_bOnShop)
    {
        for (int i = 0; i < 4;i++)
        {
            m_ShopItem[i]->Late_Update();

        }
    }
    return 0;
}

void CShopUI::Render(HDC hdc)
{
    if (m_bOnShop)
    {

        HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"ShopBase");

        StretchBlt(hdc, m_tRect.left, m_tRect.top, m_vSize.x, m_vSize.y, hMemDC, 0, 0, m_ImgSize.x, m_ImgSize.y, SRCCOPY);
    

        for (int i = 0; i < 4;i++)
        {
            m_ShopItem[i]->Render(hdc);

            dynamic_cast<CShopCell*>(m_ShopItem[i])->RenderIcon(hdc, dynamic_cast<CShop*>(m_tNpcTarget)->Get_ShopItem(i));
        }

        
        
    }
}

void CShopUI::Release()
{

}

bool CShopUI::IsColl()
{
    return false;
}
