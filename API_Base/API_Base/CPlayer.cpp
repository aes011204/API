#include "pch.h"
#include "CPlayer.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
CPlayer::CPlayer() : m_eCurState(PS_END), m_ePreState(PS_END)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
    m_vSize = { 15.f, 20.f };
    m_vPosition = { WINCX*.5f,WINCY*.5f };
    m_fSpeed = 200.f;

    m_ID = PLAYER;

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/player_idle.bmp", L"PlayerIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/player_run.bmp", L"PlayerRun");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/player_jump.bmp", L"PlayerJump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/player_die.bmp", L"PlayerDie");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/DustEffect.bmp", L"RushDust");

	m_pFrameKey = L"PlayerIdle";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = .05f;
	m_tFrame.dwTime = 0.f;

	m_pEFFrameKey = L"RushDust";
	m_tEFFrame.iStart = 0;
	m_tEFFrame.iEnd = 5;
	m_tEFFrame.dwSpeed = .2f;
	m_tEFFrame.dwTime = 0.f;
	m_tEFFrame.vSize = {14,13};
}

int CPlayer::Update()
{

	if (m_bDead)
	{
		m_pFrameKey = L"PlayerDie";
		return OBJ_DEAD;// 일단 플레이어는 삭제 하면 안되는데 일단 임시로
	}
    __super::Update_Rec();
	CCreature::Update();

    Key_Input();
	CCreature::Move_Frame();
	CCreature::Move_EffectFrame();
    return 0;

}

void CPlayer::Late_Update()
{
	Motion_Change(); 
}

void CPlayer::Render(HDC hdc)
{
    //Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

   // Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	{
		
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
			RGB(255, 255, 255));
	

		Move_EffectFrame(hdc);
	}
	{
		// 원래 거
    //GdiTransparentBlt(hdc,
    //    RenderPos.x - m_vSize.x*.5f,
    //    RenderPos.y - m_vSize.y*.5f,
    //    (int)m_vSize.x,
    //    (int)m_vSize.y,
    //    hMemDC,
	//	m_tFrame.iStart * (int)m_vSize.x,
	//	m_tFrame.iMotion * (int)m_vSize.y,
    //    (int)m_vSize.x,
    //    (int)m_vSize.y,
    //    RGB(255, 0, 255));
	}

   // BitBlt(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom, hMemDC, 0, 0, SRCCOPY); // 지우는 거 안쓸거면 이거 해야 랜더링됨
}

void CPlayer::Release()
{
}

void CPlayer::On_Collision(CObj* obj)
{
}


void CPlayer::Key_Input()
{
	float fY(0.f);
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
			m_bJump = true;

		m_pFrameKey = L"PlayerJump";
		m_eCurState = JUMP;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
        m_vPosition.x -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
		m_pFrameKey = L"PlayerRun";
		m_eCurState = WALK;

		m_bJump = false;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
        m_vPosition.x += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
		m_pFrameKey = L"PlayerRun";
		m_eCurState = WALK;

		m_bJump = false;
	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
        m_vPosition.y -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

		m_bJump = false;
	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN) && CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
        m_vPosition.y += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
		m_pFrameKey = L"Player_DOWN";
		m_eCurState = WALK;
		m_bJump = false;
	}
	else
	{
		m_pFrameKey = L"PlayerIdle";

		m_eCurState = IDLE;
		m_bJump = false;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('V'))
	{
		// 인벤토리 
	}

	if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		// 능력치 정보창
	}
}

void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 15.f, 20.f };
			m_vSize = m_tFrame.vSize;
			break;

		case WALK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 7;
			
			m_tFrame.dwSpeed = .1f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 17.f, 20.f };
			m_vSize = m_tFrame.vSize;
			break;

		case JUMP:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;			
			m_tFrame.dwSpeed = 2.f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 17.f, 21.f };
			m_vSize = m_tFrame.vSize;

			break;

		case ATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 17.f, 21.f };
			m_vSize = m_tFrame.vSize;

			break;

		case HIT:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 17.f, 21.f };
			m_vSize = m_tFrame.vSize;
			break;

		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.dwSpeed =.2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 23.f, 14.f };
			m_vSize = m_tFrame.vSize;
			break;

		}

		m_ePreState = m_eCurState;
	}



}


void CPlayer::Move_EffectFrame(HDC hdc)
{
	HDC	hEFMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pEFFrameKey);

	// 먼지 효과 (발생하는 순간 의 좌표 움직이면 안더ㅣㅁ) 지금은 1번 돌떄중복으로 생기지 않음

	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos({ m_vEFPos.x ,m_vEFPos.y + m_tEFFrame.vSize.y * .5f });


	Vector2 RenderEFSize = CCamera::Get_Instance()->GetRenderSize(m_tEFFrame.vSize);


	GdiTransparentBlt(
		hdc, RenderPos.x - RenderEFSize.x*.5f, RenderPos.y - RenderEFSize.y * .5f,
		RenderEFSize.x, RenderEFSize.y,
		hEFMemDC,
		m_tEFFrame.iStart * m_tEFFrame.vSize.x,
		0,
		m_tEFFrame.vSize.x, m_tEFFrame.vSize.y,
		RGB(255, 255, 255));
}