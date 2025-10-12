#pragma once
class CItem;
class CObj;
class Item;
class CInventory
{
public:
	CInventory();
	~CInventory();
public:
	void Initialize();
	void Update();
	void Render();
	void Release();

public:
	void Set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }
	void Remove_Item(int index);
	bool Get_Is_Full();
	void Swap_Item(int src, int dst);
	int Check_emptySlot();
	int Put_Item(CItem* _BuyItem);
	//void Put_Item(CItem* pBuyItem);
	CItem* Get_InvenItem(int index);

	void moved_Item(int index);

	void Equip_Item(int iInput, int equipInput);

	int Check_IsEmpty(int dst);

	int Unequip_Item(CItem* item, int dst);

	bool Is_Sell_Item(int _ItemIndex, int& iMoney);

	
	//void Equip_Item();
	//void Unequip_Item();

	size_t Get_InvenSize() { return m_vecInvenSlot.size(); }

	int Get_SlotNum() const { return m_iSlotNum; }
	void Set_SlotNum(int iSlotNum) { m_iSlotNum = iSlotNum; }

private:
	bool Is_Full;
	CObj* m_pPlayer;


	vector<CItem*> m_vecInvenSlot;
	int m_iSlotNum;
};

