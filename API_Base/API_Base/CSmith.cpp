#include "pch.h"
#include "CSmith.h"
#include "CBmpMgr.h"

CSmith::CSmith()
{
}

CSmith::~CSmith()
{
}

void CSmith::Initialize()
{
	CNpc::Initialize();

	m_vSize = { 24.f, 26.f };
	m_vPosition = { 5400,817 };
	m_ID = NPC;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Village/NPC_BlackSmith.bmp", L"Smith");

	m_pFrameKey = L"Smith";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = .2f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 24.f, 26.f };

	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, { 80.f,25.f }, this));
}

int CSmith::Update()
{
	CNpc::Update();
    return 0;
}

void CSmith::Late_Update()
{
	CNpc::Late_Update();

}

void CSmith::Render(HDC hdc)
{
	CNpc::Render(hdc);

}

void CSmith::Release()
{
	CNpc::Release();

}

void CSmith::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	CNpc::On_Collision(obj, my, other);

}
