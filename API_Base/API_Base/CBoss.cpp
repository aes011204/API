#include "pch.h"
#include "CBoss.h"
#include "CCamera.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"

CBoss::CBoss() : m_eCurState(ST_END),m_ePreState(ST_END)
{
}

CBoss::~CBoss()
{
	Release();
}

void CBoss::Initialize()
{
	m_vPosition = { 1056.f * .5f,1056.f * .5f };
	m_vSize = { 210,285 };

	m_iMaxHP = 500.f;
	m_iHP = m_iMaxHP;
	m_iDamage = 1;

	m_ID = MONSTER;

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

int CBoss::Update()
{
	if (m_bDead)
	{
		m_pFrameKey = L"BossDie";
		//return OBJ_DEAD;// 일단 플레이어는 삭제 하면 안되는데 일단 임시로
	}
	// 누적시간 제는용
	float dt = CTimeMgr::Get_Instance()->GetDeltaTime();
	accTime += dt;

	__super::UpdateColl(m_vPosition);


	__super::Update_Rec();

	//m_pFrameKey = L"BulletAttack";
	//m_eCurState = BULLETATTACK;
	
	//CCreature::Update();

	Motion_Change();

	CCreature::Move_Frame();

	Update_Rec();

	return 0;
}

void CBoss::Late_Update()
{
}

void CBoss::Render(HDC hdc)
{

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);


	Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vSize);

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


	__super::RenderColl(hdc,m_vPosition);
	//Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	//float zoom = CCamera::Get_Instance()->GetZoom();

	//float RenderSizeX = m_vSize.x * zoom;
	//float RenderSizeY = m_vSize.y * zoom;
	//// 좌상단 기준
	//float LeftTopX = RenderPos.x - RenderSizeX * .5f;
	//float LeftTopY = RenderPos.y - RenderSizeY * .5f;

	//Rectangle(hdc, LeftTopX, LeftTopY, LeftTopX + RenderSizeX, LeftTopY + RenderSizeY);
}

void CBoss::Release()
{

}

void CBoss::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{

}

void CBoss::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 9;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 210,285 };
		
			m_vSize = m_tFrame.vSize;
			break;

		case BULLETATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 9;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 210, 384 };
			m_vSize = m_tFrame.vSize;
			break;

		case SWORDATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;
			m_tFrame.dwSpeed = 2.f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 75.f, 60.f };
			m_vSize = m_tFrame.vSize;

			break;

		case HANDATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 17.f, 21.f };
			m_vSize = m_tFrame.vSize;

			break;

		case DEMAGE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 17.f, 21.f };
			m_vSize = m_tFrame.vSize;

			break;


		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 78.f, 75.f };
			m_vSize = m_tFrame.vSize;
			break;

		}

		m_ePreState = m_eCurState;
	}
}

void CBoss::Take_Damage(int _damage)
{
}
