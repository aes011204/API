#include "pch.h"
#include "Define.h"
#include "CDungeonDoor.h"
#include "CColliderComp.h"
#include "CBmpMgr.h"
#include "CCamera.h"
#include "CPlayer.h"
#include"CSceneMgr.h"

void CDungeonDoor::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	if(obj->Get_ID() == PLAYER)
		{
			if (other.GetType() == ColliderType::BODY)
			{
				RECT otherRec = *other.Get_Rect();
				RECT myRec = *my.Get_Rect();
				if (otherRec.left >= myRec.left
					&& otherRec.top >= myRec.top
					&& otherRec.right <= myRec.right
					&& otherRec.bottom <= myRec.bottom)
				{
					m_OnPlayer = true;
				dynamic_cast<CPlayer*>(obj)->SetStop(true);

				}
			}

		}
}

CDungeonDoor::CDungeonDoor() : m_OnPlayer(false)
{
}

CDungeonDoor::~CDungeonDoor()
{
}

void CDungeonDoor::Initialize()
{
	m_vSize = { 120.f, 90.f };
	m_vPosition = { 2926,720 };
	m_ID = DOOR;

	//idelTime = 10.f;


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Village/DungeonEat.bmp", L"DungeonEat");
	

	m_pFrameKey = L"DungeonEat";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 27;
	m_tFrame.dwSpeed = .1f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 120.f, 90.f };
	
	

	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { -15,100 }, { 60.f,80.f }, this));
}

int CDungeonDoor::Update()
{

	if (m_OnPlayer == true)
	{
		CNonCreature::Move_Frame();

		if (m_tFrame.iStart == m_tFrame.iEnd)
		{
			CSceneMgr::Get_Instance()->Rq_changeScene(SC_STAGE01);
		}
	}


	__super::UpdateColl(m_vPosition);
	return 0;
}

void CDungeonDoor::Late_Update()
{
}

void CDungeonDoor::Render(HDC hdc)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"DungeonEat");
	if (m_OnPlayer)
	{
	Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 reSize = m_vSize * 3;
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(reSize);

	// 스프라이트시트에서 가져올 소스 사각형(프레임)
	int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스

	// 투명색 키(마젠타)로 블릿
	GdiTransparentBlt(
		hdc,
		centerS.x - RenderSize.x * 0.5f,
		centerS.y - RenderSize.y * 0.5f,
		RenderSize.x, RenderSize.y,
		hMemDC, srcX, 0, (int)m_vSize.x, (int)m_vSize.y,
		RGB(255, 255, 255));

	}
	__super::RenderColl(hdc,m_vPosition);


}

void CDungeonDoor::Release()
{
}
