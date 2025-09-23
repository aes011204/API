#include "pch.h"
#include "Define.h"
#include "CDungeonDoor.h"
#include "CColliderComp.h"
#include "CBmpMgr.h"

void CDungeonDoor::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{

}

CDungeonDoor::CDungeonDoor()
{
}

CDungeonDoor::~CDungeonDoor()
{
}

void CDungeonDoor::Initialize()
{
	m_ID = MONSTER;

	//idelTime = 10.f;


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossIdle.bmp", L"BossIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossAttack.bmp", L"BulletAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/HandIdle.bmp", L"HandIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/HandAttack.bmp", L"HandAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/PlayerDie.bmp", L"PlayerDie");

	m_pFrameKey = L"BossIdle";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 9;
	m_tFrame.dwSpeed = .2f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 210,285 };

	m_eCurState = IDLE;

	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, { 48.f,60.f }, this));
}

int CDungeonDoor::Update()
{
	return 0;
}

void CDungeonDoor::Late_Update()
{
}

void CDungeonDoor::Render(HDC hdc)
{
}

void CDungeonDoor::Release()
{
}
