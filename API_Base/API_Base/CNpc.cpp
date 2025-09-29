#include "pch.h"
#include "CNpc.h"
#include "CPlayer.h"
#include "CBmpMgr.h"
#include "CCamera.h"

CNpc::CNpc() :m_OnPlayer(false)
{
}

CNpc::~CNpc()
{
}

void CNpc::Initialize()
{
	//m_vSize = { 13.f, 21.f };
	//m_vPosition = { 5046,395 };
	m_ID = NPC;
	
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Village/Keyboard_F.bmp", L"F");
	
	
	//m_pFrameKey = L"Shop";
	//m_tFrame.iStart = 0;
	//m_tFrame.iEnd = 5;
	//m_tFrame.dwSpeed = .1f;
	//m_tFrame.dwTime = 0.f;
	//m_tFrame.vSize = { 13.f, 21.f };

	

}

int CNpc::Update()
{
	m_OnPlayer = false;
	CNonCreature::Move_Frame();


	__super::UpdateColl(m_vPosition);
	return 0;
}

void CNpc::Late_Update()
{
	
}

void CNpc::Render(HDC hdc)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

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
			RGB(255, 0, 255));

	

	if (m_OnPlayer)
	{
		//TODO : F ui 출력 
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"F");
		Vector2 PosOffSet = { 0,-80 };
		Vector2 size = { 13,14 };
		Vector2 reSize = size * 3;
		Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition+PosOffSet);
		Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(reSize);
		GdiTransparentBlt(
			hdc,
			RenderPos.x - RenderSize.x * 0.5f,
			RenderPos.y - RenderSize.y * 0.5f,
			RenderSize.x, RenderSize.y,
			hMemDC, 0, 0, size.x, size.y,
			RGB(255, 0, 255));

	}

	__super::RenderColl(hdc, m_vPosition);
}

void CNpc::Release()
{
}

void CNpc::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	
	if (obj->Get_ID() == PLAYER)
	{
		if (other.GetType() == ColliderType::BODY)
		{
				m_OnPlayer = true;

		}



	}

}
