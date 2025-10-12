#include "pch.h"
#include "CShop.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CUIMgr.h"
#include "CAbstractFactory.h"

#include "CShopUI.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CSword01.h"
#include "CText.h"
#include "CSoundManager.h"
#include "CSword02.h"
#include "CGun.h"
#include "CSword03.h"


CShop::CShop(): m_OnShop(false)
{
}

CShop::~CShop()
{
	Release();
}

void CShop::Initialize()
{
	CNpc::Initialize();

	m_vSize = { 13.f, 21.f };
	m_vPosition = { 5046,395 };
	m_ID = NPC;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Village/NPC_Merchant.bmp", L"Shop");

	m_pFrameKey = L"Shop";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = .2f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 13.f, 21.f };

	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, { 80.f,25.f }, this));
	
	m_ShopUI = CAbstractFactory<CShopUI>::CreateUI();
	m_ShopUI->Set_NpcTarget(this);

	CUIMgr::Get_Instance()->Add_Object(m_ShopUI);

	//m_vecShop.push_back(dynamic_cast <CItem*>(CAbstractFactory<CSword01>::Create()));
	//m_vecShop.push_back(dynamic_cast <CItem*>(CAbstractFactory<CSword01>::Create()));
	//m_vecShop.push_back(dynamic_cast <CItem*>(CAbstractFactory<CSword01>::Create()));
	m_ShopItem[0] = dynamic_cast <CItem*>(CAbstractFactory<CSword01>::CreateItem(CItem::ONEHAND, CItem::UNEQUIP, CItem::BEGGINER));
		m_ShopItem[1] = dynamic_cast <CItem*>(CAbstractFactory<CSword02>::CreateItem(CItem::TWOHAND, CItem::UNEQUIP, CItem::BEGGINER));
		m_ShopItem[2] = dynamic_cast <CItem*>(CAbstractFactory<CGun>::CreateItem(CItem::ONEHAND, CItem::UNEQUIP, CItem::BEGGINER));
		m_ShopItem[3] = dynamic_cast <CItem*>(CAbstractFactory<CSword03>::CreateItem(CItem::SUBWEAPON, CItem::UNEQUIP, CItem::BEGGINER));

}

int CShop::Update()
{

	CShopUI* shop = dynamic_cast<CShopUI*>(m_ShopUI);
	if (m_OnPlayer)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('F'))
		{
			m_Text = dynamic_cast<CText*>(CAbstractFactory<CText>::CreateUI());
			CUIMgr::Get_Instance()->Add_Object(m_Text);
			m_StartText = true;
		}
	}
	else
	{
		shop->Set_OnShop(false);
	}

	if (m_StartText)
	{

	if (CKeyMgr::Get_Instance()->Key_Down('I'))
	{
		// 퀘스트 수락
		dynamic_cast <CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->SetQuest(true);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('O'))
	{

		shop->Set_OnShop(!(shop->Get_OnShop()));

		if (m_Text != nullptr)
		{
			m_Text->Set_Dead(true);
			m_Text = nullptr;
		}
	}
	if (shop->Get_OnShop() == true)
	{

			int index = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->GetFromInven();
				if (index != -1)
				{
					Sell_Item(index);
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->SetFromInven(-1);
				}
	}
	//else if (CKeyMgr::Get_Instance()->Key_Down('P'))
	//{
	//	// 판매
	//	if (m_Text != nullptr)
	//	{
	//		m_Text->Set_Dead(true);
	//		m_Text = nullptr;
	//	}
	//}
	}

	CNpc::Update();

	return 0;
}

void CShop::Late_Update()
{
	CNpc::Late_Update();

}

void CShop::Render(HDC hdc)
{
	CNpc::Render(hdc);


}

void CShop::Release()
{
	m_ShopUI->Set_Dead(true);
	CNpc::Release();
	
}

void CShop::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	if (obj->Get_ID() == PLAYER)
	{
		if (other.GetType() == ColliderType::BODY)
		{
			m_OnPlayer = true;

			if (m_isSellShop == true)
			{
				if (dynamic_cast <CPlayer*>(obj)->GetFromInven() != -1)
				{
					Sell_Item(dynamic_cast <CPlayer*>(obj)->GetFromInven());
					dynamic_cast <CPlayer*>(obj)->SetFromInven(-1);

				}
			}
		}



	}
}

void CShop::Buy_Item(int buyIndex)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player());
	CInventory* pInven = pPlayer->Get_Inven();
	if (pPlayer->Get_Money() >= m_ShopItem[buyIndex]->Get_Money()
		&& pInven->Get_Is_Full() == false)
	{
		cout << "구매 성공" << endl;
		// 돈 뺴기
		pPlayer->Set_Money(pPlayer->Get_Money() - m_ShopItem[buyIndex]->Get_Money());
		// 아이템 넣기
		int index = pInven->Check_emptySlot();
		pInven->Put_Item(m_ShopItem[buyIndex]);

		float m_fVolume = 20.f;
		CSoundManager::Get_Instance()->PlayFX(L"sell.wav", SOUND_EFFECT, m_fVolume);

	}
	else
	{
		cout << "구매 실패" << endl;
	}
}

void CShop::Sell_Item(int iInput)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player());
	CInventory* pInven = pPlayer->Get_Inven();

	//if (pInven->Get_InvenSize() <= pInven->Get_SlotNum())
	//	return;

		int iMoney(0);

		if (pInven->Is_Sell_Item(iInput, iMoney))
		{
			dynamic_cast<CPlayer*>(pPlayer)->Set_Money(pPlayer->Get_Money() + iMoney);
			cout << "판매 성공" << endl;
		}
		else
		{
			cout << "판매 실패" << endl;
		}

		

}

CItem* CShop::Get_ShopItem(int index)
{
	if (index < 0 || index > 4)
		return nullptr;
	else
		return m_ShopItem[index];
}