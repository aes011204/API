#include "pch.h"
#include "CCoin.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"

CCoin::CCoin()
{
}

CCoin::~CCoin()
{
}

void CCoin::Initialize()
{
    m_ID = ITEM;


	strName = L"총";

	m_iMoney = 100;


	iCost = 100;
	m_vSize = { 21.f,21.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin.bmp", L"Coin");
	
	m_pFrameKey = L"Coin";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 7;
	m_tFrame.dwSpeed = .2f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 21.f,21.f };
	m_fSpeed = 400;

	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, m_tFrame.vSize*2, this));

}

int CCoin::Update()
{
	
	if (m_bDead == true)
	{
		return OBJ_DEAD;
	}
	Update_Rec();
	Move_Frame();

	__super::UpdateColl(m_vPosition);
    return 0;
}

void CCoin::Late_Update()
{
	if (m_move == true)
	{
		m_vPosition.y += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
	}
}

void CCoin::Render(HDC hdc)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 reSize = m_vSize;
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

	__super::RenderColl(hdc, m_vPosition);


}

void CCoin::Release()
{
}

void CCoin::ItemInfo()
{
}

void CCoin::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	if (obj->Get_ID() == PLATFORM || obj->Get_ID() == WALL)
	{
		m_move = false;
	}
}
