#include "pch.h"
#include "CInventory.h"
#include "CItem.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CSword01.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CGun.h"
#include "CAccecery.h"
#include "CKeyMgr.h"

CInventory::CInventory() : m_iSlotNum(15)
{
	m_vecInvenSlot.resize(m_iSlotNum, nullptr);
	//m_vecInvenSlot.reserve(m_iSlotNum);
}

CInventory::~CInventory()
{
	Release();
}

void CInventory::Initialize()
{

CItem* tmp = (CAbstractFactory<CSword01>::CreateItem(CItem::ONEHAND,CItem::UNEQUIP, CItem::BEGGINER));
//tmp->Set_Target(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player()));
//tmp->SetItemState(CItem::EQUIP);
m_vecInvenSlot[0]=(tmp);
CItem* tmp1 = (CAbstractFactory<CSword01>::CreateItem(CItem::ONEHAND, CItem::UNEQUIP, CItem::BEGGINER));
m_vecInvenSlot[1] = (tmp1);
CItem* tmp2 = (CAbstractFactory<CGun>::CreateItem(CItem::ONEHAND, CItem::UNEQUIP, CItem::BEGGINER));
m_vecInvenSlot[2] = (tmp2);
}

void CInventory::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down('0'))
	{
		Equip_Item(0, 0);
	}

	//for (int i = 0; i < m_vecInvenSlot.size(); ++i)
	//{
	//	if (m_vecInvenSlot[i] != nullptr)
	//	{
	//		m_vecInvenSlot[i]->GetItemState() == CItem::EQUIP;
	//		m_vecInvenSlot[i] = nullptr;
	//	}
	//
	//}
}

void CInventory::Render()
{
	
}

void CInventory::Release()
{
	for_each(m_vecInvenSlot.begin(), m_vecInvenSlot.end(), Safe_Delete<CItem*>);
	m_vecInvenSlot.clear();
}

void CInventory::Remove_Item(int index)
{
	if (index < 0 || index >= m_iSlotNum)
		return;
	if (m_vecInvenSlot[index] != nullptr)
	{
		m_vecInvenSlot[index] = nullptr;
	}
}
bool CInventory::Get_Is_Full()
{
	if (m_vecInvenSlot.size() >= m_iSlotNum)
	{
		return true;
	}
	return false;
}

void CInventory::Swap_Item(int src, int dst)
{
	
		swap(m_vecInvenSlot[src], m_vecInvenSlot[dst]);

}
int CInventory::Check_emptySlot()
{
	if (m_vecInvenSlot.empty())
		return 0;
	for (size_t i = 0; i < m_vecInvenSlot.size(); ++i)
	{
		if (m_vecInvenSlot[i] == nullptr)
			return static_cast<int>(i);
	}

	return -1;
}
int CInventory::Put_Item(CItem* _BuyItem)
{

	int slot = Check_emptySlot();
	if (slot != -1)
	{

		if (auto* w = dynamic_cast<CSword01*>(_BuyItem)) {
			m_vecInvenSlot[slot] = new CSword01(*w);
		}
		else if (auto* g = dynamic_cast<CGun*>(_BuyItem)) 
		{
			m_vecInvenSlot[slot] = new CGun(*g);
		}
		else if (auto* a = dynamic_cast<CAccecery*>(_BuyItem)) 
		{
			m_vecInvenSlot[slot] = new CAccecery(*a);
		}
		else if (auto* a = dynamic_cast<CGun*>(_BuyItem))
		{
			m_vecInvenSlot[slot] = new CGun(*a);
		}


		return 0;
	}
	else
		return -1;
	
}


void CInventory::Equip_Item(int iInput, int equipInput)
{
//	int result = ( dynamic_cast<CPlayer*>(m_pPlayer)->Equip_Item(m_vecInvenSlot[iInput], equipInput));
//	if(result != -1)
//	 Remove_Item(iInput);
}

int CInventory::Check_IsEmpty(int dst)
{
	if (m_vecInvenSlot[dst] != nullptr)
		return -1;
	else
		return 0;
}
int CInventory::Unequip_Item(CItem* item, int dst)
{
	if (dst < m_vecInvenSlot.size())
	{
		if (m_vecInvenSlot[dst] == nullptr)
		{
			m_vecInvenSlot[dst] = item;
			return 0;
		}
		else
		{
			return -1;
		}
		//dynamic_cast<CPlayer*>(m_pPlayer)->Unequip_Item(iInput,m_vecInvenSlot[iInput]);
	}

}

bool CInventory::Is_Sell_Item(int _ItemIndex, int& iMoney)
{
//
//	CItem* item = dynamic_cast<CItem*>(m_vecInvenSlot[_ItemIndex]);
//
//	if (item->GetItemState() == CItem::EQUIP)
//	{
//		dynamic_cast<CPlayer*>(m_pPlayer)->Unequip_Item(m_vecInvenSlot[_ItemIndex]);
//	}
//
//	vector<CItem*>::iterator iter = m_vecInvenSlot.begin();
//
//	iter += _ItemIndex;
//
//	iMoney = (*iter)->Get_Cost() >> 1; // 비트연산 /2 와 같음
//
//	Safe_Delete<CItem*>(*iter);
//	m_vecInvenSlot.erase(iter);
//
return true;

}


CItem* CInventory::Get_InvenItem(int index)
{
	if (index <0 && index > m_vecInvenSlot.size())
		return nullptr;
	else
		return m_vecInvenSlot[index];
}

void CInventory::moved_Item(int index)
{

	m_vecInvenSlot[index] = nullptr;
}

