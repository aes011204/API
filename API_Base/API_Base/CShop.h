#pragma once
#include "CNpc.h"
class CItem;
class CUI;
class CText;
class CShop :
    public CNpc
{
public:
	CShop();
	~CShop();

public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();


	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;

	void Buy_Item(int buyIndex);

	//void Buy_Item(CItem* _pItem);

	void Sell_Item(int iInput);

	CItem* Get_ShopItem(int index);

	//void Sell_Item();

private:
	CUI* m_ShopUI;
	bool m_OnShop;

	//vector<CItem*> m_vecShop;
	CItem* m_ShopItem[4];

	bool m_StartText = false;
	CText* m_Text = nullptr;
	
	bool m_isSellShop = false;
};

