#include "pch.h"
#include "CStat.h"
#include "CBmpMgr.h"

CStat::CStat()
{
}

CStat::~CStat()
{
}

void CStat::Initialize()
{
	CNpc::Initialize();

	m_vSize = { 23.f, 25.f };
	m_vPosition = {520,820 };
	m_ID = NPC;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Village/NPC_Commander.bmp", L"Stat");

	m_pFrameKey = L"Stat";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = .2f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 23.f, 26.f };

	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, { 80.f,25.f }, this));
}

int CStat::Update()
{
	CNpc::Update();

    return 0;
}

void CStat::Late_Update()
{
	CNpc::Late_Update();

}

void CStat::Render(HDC hdc)
{
	CNpc::Render(hdc);

}

void CStat::Release()
{
	CNpc::Release();

}

void CStat::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	CNpc::On_Collision(obj, my, other);

}
