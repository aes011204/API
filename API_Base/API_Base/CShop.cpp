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


CShop::CShop(): m_OnShop(false)
{
}

CShop::~CShop()
{
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
	CUIMgr::Get_Instance()->Add_Object(m_ShopUI);

	m_vecShop.push_back(dynamic_cast <CItem*>(CAbstractFactory<CSword01>::Create()));
	m_vecShop.push_back(dynamic_cast <CItem*>(CAbstractFactory<CSword01>::Create()));
	m_vecShop.push_back(dynamic_cast <CItem*>(CAbstractFactory<CSword01>::Create()));


}

int CShop::Update()
{

	CShopUI* shop = dynamic_cast<CShopUI*>(m_ShopUI);
	if (m_OnPlayer)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('F'))
		{
			shop->Set_OnShop(!(shop->Get_OnShop()));
		}
	}
	else
	{
		shop->Set_OnShop(false);
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
	CNpc::Release();
}

void CShop::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	CNpc::On_Collision(obj, my, other);
}

void CShop::Buy_Item(CItem* _pItem)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player());
	CInventory* pInven = pPlayer->Get_Inven();
	if (pPlayer->Get_Money() >= _pItem->Get_Cost()
		&& pInven->Get_Is_Full() == false)
	{
		cout << "구매 성공" << endl;
		// 돈 뺴기
		pPlayer->Set_Money(pPlayer->Get_Money() - _pItem->Get_Cost());
		// 아이템 넣기
		pInven->Put_Item(_pItem);

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

	if (pInven->Get_InvenSize() <= pInven->Get_SlotNum())
		return;

		int iMoney(0);

		if (pInven->Is_Sell_Item(iInput, iMoney))
		{
			dynamic_cast<CPlayer*>(pPlayer)->Set_Money(pPlayer->Get_Money() - iMoney);
			cout << "판매 성공" << endl;
		}
		else
		{
			cout << "판매 실패" << endl;
		}

		system("pause");

}