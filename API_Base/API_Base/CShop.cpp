#include "pch.h"
#include "CShop.h"
#include "CBmpMgr.h"

CShop::CShop()
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
}

int CShop::Update()
{
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
