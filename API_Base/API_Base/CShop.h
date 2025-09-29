#pragma once
#include "CNpc.h"
class CItem;
class CUI;
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

	void Buy_Item(CItem* _pItem);

	void Sell_Item(int iInput);

	//void Sell_Item();

private:
	CUI* m_ShopUI;
	bool m_OnShop;

	vector<CItem*> m_vecShop;
};

