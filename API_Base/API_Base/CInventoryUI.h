#pragma once
#include "CUI.h"
class CInventory;
class CInventoryCell;
class CItem;
class CInventoryUI :
    public CUI
{
public:
    enum INVENTYPE{
        EQUIP01, EQUIP02, ACC, INVEN, IVT_END,
    };
    CInventoryUI();
    ~CInventoryUI();

    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    int Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;
    bool IsColl() override;
    void KeyInput();
    void Put_Down(CInventoryUI::INVENTYPE type, int index);

    void SetOnInven(bool b) { m_bOnInven = b; }
public:

private:
    CInventory* m_Inven = nullptr;
    
    bool m_bOnInven= false;
    //CUI* m_Equipweapon01[2];

    CUI* m_Equipweapon01[2];
    CUI* m_Equipweapon02[2];
    CUI* m_EquipAcc[4];

    CUI* m_cell[15];
    int m_iCol = 5;      
    int m_iRow = 3;      

    POINT mouse{};
    bool m_isDrag=false;
    CItem* m_pDragItem = nullptr;
    CInventoryCell* m_pDragFrom = nullptr;
    int m_pDragFromIndex = 0;
    INVENTYPE m_pDragFromType = IVT_END;

};

