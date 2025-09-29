#include "pch.h"
#include "CInventoryUI.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CObjMgr.h"
#include "CCreature.h"
#include "CAbstractFactory.h"
#include "CInventoryCell.h"
#include "CInventory.h"
#include "CPlayer.h"

CInventoryUI::CInventoryUI()
{
    ZeroMemory(&m_cell, sizeof(CUI*)*15);
}

CInventoryUI::~CInventoryUI()
{
}

void CInventoryUI::Initialize()
{
  
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/inven/InventoryBase.bmp", L"InventoryBase");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/inven/EquipSlot1On.bmp", L"EquipSlot1On");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/inven/EquipSlot2On.bmp", L"EquipSlot2On");

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/inven/accessory.bmp", L"accessory");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/inven/EquippedWeaponBase.bmp", L"EquippedWeaponBase");
    m_vPosition = {WINCX*.8f+10,WINCY*.5f};	// 객체의 위치, 중점
    m_vSize = {369,564};
    m_tTarget = dynamic_cast<CCreature*>( CObjMgr::Get_Instance()->Get_Player());

    Vector2 startpos = { 645 ,303 };

    for (int i = 0; i < m_iRow;i++)
    {
        for (int j = 0; j < m_iCol;j++)
        {
            m_cell[i * m_iCol + j] = CAbstractFactory<CInventoryCell>::CreateUI({ startpos.x + 65 * j, startpos.y + 65 * i });
            
        }
    }

    Vector2 equip01pos = { 664 ,130 };
    Vector2 equip02pos = { 827 ,130 };
    Vector2 accpos = { 683 ,210 };

    for (int i = 0; i < 2;i++)
    {
        m_Equipweapon01[i] = CAbstractFactory<CInventoryCell>::CreateUI({ equip01pos.x + 60 * i, equip01pos.y });
        m_Equipweapon02[i] = CAbstractFactory<CInventoryCell>::CreateUI({ equip02pos.x + 60 * i, equip02pos.y });
    }
    for (int i = 0; i < 4;i++)
    {
        m_EquipAcc[i] = CAbstractFactory<CInventoryCell>::CreateUI({ accpos.x + 60 * i, accpos.y });
    }
   

}

int CInventoryUI::Update()
{

    GetCursorPos(&mouse);
    ScreenToClient(g_hWnd, &mouse);

    for (int i = 0; i < 2;i++)
    {
        m_Equipweapon01[i]->Update();
        CInventoryCell* cell = dynamic_cast<CInventoryCell*>(m_Equipweapon01[i]);
        if (cell->IsColl(mouse))
        {
            if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
            {
                // 드래그 시작
                m_pDragFrom = cell;
                m_pDragFromIndex = i;
                m_pDragFromType = EQUIP01;
                m_pDragItem = m_Inven->Get_InvenItem(i);
                m_isDrag = true;
            }

            if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
            {
                // 드래그 종료 / 드롭 처리
                if (m_isDrag)
                {
                    Put_Down(EQUIP01, i);
                    //  m_Inven->Swap_Item(m_pDragFromIndex, i * m_iCol + j);

                    m_isDrag = false;
                }
            }
        }

        m_Equipweapon02[i]->Update();

        CInventoryCell* cell2 = dynamic_cast<CInventoryCell*>(m_Equipweapon02[i]);
        if (cell2->IsColl(mouse))
        {
            if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
            {
                // 드래그 시작
                m_pDragFrom = cell2;
                m_pDragFromIndex = i;
                m_pDragFromType = EQUIP02;
                m_pDragItem = m_Inven->Get_InvenItem(i);
                m_isDrag = true;
            }

            if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
            {
                // 드래그 종료 / 드롭 처리
                if (m_isDrag)
                {
                    Put_Down(EQUIP02, i);
                    //  m_Inven->Swap_Item(m_pDragFromIndex, i * m_iCol + j);

                    m_isDrag = false;
                }
            }
        }

    }
    for (int i = 0; i < 4;i++)
    {
        m_EquipAcc[i]->Update();
        CInventoryCell* cell = dynamic_cast<CInventoryCell*>(m_EquipAcc[i]);
        if (cell->IsColl(mouse))
        {
            if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
            {
                // 드래그 시작
                m_pDragFrom = cell;
                m_pDragFromIndex = i;
                m_pDragFromType = ACC;
                m_pDragItem = m_Inven->Get_InvenItem(i);
                m_isDrag = true;
            }

            if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
            {
                // 드래그 종료 / 드롭 처리
                if (m_isDrag)
                {
                    Put_Down(ACC, i);
                    //  m_Inven->Swap_Item(m_pDragFromIndex, i * m_iCol + j);

                    m_isDrag = false;
                }
            }
        }

    }
    for (int i = 0; i < m_iRow;i++)
    {
        for (int j = 0; j < m_iCol;j++)
        {
            m_cell[i * m_iCol + j]->Update();
            CInventoryCell* cell = dynamic_cast<CInventoryCell*>(m_cell[i * m_iCol + j]);
            if (cell->IsColl(mouse))
            {
                if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
                {
                    // 드래그 시작
                    m_pDragFrom = cell;
                    m_pDragFromIndex = i * m_iCol + j;
                    m_pDragFromType = INVEN;
                    m_pDragItem = m_Inven->Get_InvenItem(i * m_iCol + j);
                    m_isDrag = true;
                }

                if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
                {
                    // 드래그 종료 / 드롭 처리
                    if (m_isDrag)
                    {


                        Put_Down(INVEN, i * m_iCol + j);
                        //  m_Inven->Swap_Item(m_pDragFromIndex, i * m_iCol + j);


                        m_isDrag = false;
                    }
                }
            }
        }
    }

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
    {

    }
    Update_Rect();
    KeyInput();
    return 0;

}
int CInventoryUI::Late_Update()
{

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
    {
    }
    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
    {
    }
    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
    {
        //랜더 이미지 따라 다니기 
        if (m_isDrag)
        {
            POINT mouse = {};
            GetCursorPos(&mouse);
            ScreenToClient(g_hWnd, &mouse);
        }

    }


    return 0;
}

void CInventoryUI::Render(HDC hdc)
{

    m_Inven = dynamic_cast<CPlayer*>(m_tTarget)->Get_Inven();

    if (m_bOnInven)
    {
        HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"InventoryBase");

        BitBlt(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom, hMemDC, 0, 0, SRCCOPY); // 지우는 거 안쓸거면 이거 해야 랜더링됨

        for (int i = 0; i < 2;i++)
        {

            m_Equipweapon01[i]->Render(hdc);
            dynamic_cast<CInventoryCell*>(m_Equipweapon01[i])->RenderIcon(hdc,dynamic_cast<CPlayer*>(m_tTarget)->Get_InvenItem(i, 0));
        }
        for (int i = 0; i < 2;i++)
        {
            m_Equipweapon02[i]->Render(hdc);
            dynamic_cast<CInventoryCell*>(m_Equipweapon02[i])->RenderIcon(hdc, dynamic_cast<CPlayer*>(m_tTarget)->Get_InvenItem(i, 1));

        }
        for (int i = 0; i < 4;i++)
        {
            m_EquipAcc[i]->Render(hdc);
            dynamic_cast<CInventoryCell*>(m_EquipAcc[i])->RenderIcon(hdc, dynamic_cast<CPlayer*>(m_tTarget)->Get_InvenItem(i, 2));

        }

        for (int i = 0; i < m_iRow;i++)
        {
            for (int j = 0; j < m_iCol;j++)
            {
                m_cell[i * m_iCol + j]->Render(hdc);

                dynamic_cast<CInventoryCell*>(m_cell[i * m_iCol + j])->RenderIcon(hdc,m_Inven->Get_InvenItem(i * m_iCol + j));
            }
        }

        

    }

   
}

void CInventoryUI::Release()
{
    for (int i = 0; i < m_iRow;i++)
    {
        for (int j = 0; j < m_iCol;j++)
        {
            m_cell[i * m_iCol + j]->Release();

        }
    }
}

bool CInventoryUI::IsColl()
{
    return false;
}
void CInventoryUI::KeyInput()
{

    if (CKeyMgr::Get_Instance()->Key_Down('V'))
    {
        // 인벤토리 
        m_bOnInven = !m_bOnInven;
    }

}

void CInventoryUI::Put_Down(CInventoryUI::INVENTYPE type, int index)
{
    if(type==ACC)

    if (m_pDragFromIndex == index)
        return;

    if (m_pDragFromType == INVEN && type == INVEN)
        m_Inven->Swap_Item(m_pDragFromIndex, index);

    if (m_pDragFromType == INVEN && type != INVEN)
        dynamic_cast<CPlayer*>(m_tTarget)->Equip_Item(m_pDragFromIndex,m_pDragItem, index);

    if (m_pDragFromType != INVEN && type == INVEN)
        dynamic_cast<CPlayer*>(m_tTarget)->Unequip_Item(m_pDragFromIndex, m_pDragFromType, index);
}
