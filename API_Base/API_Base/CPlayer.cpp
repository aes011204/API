#include "pch.h"
#include "CPlayer.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
CPlayer::CPlayer() 
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
    m_vSize = { 15.f, 20.f };
    m_vPosition = { WINCX*.5f,WINCY*.5f };
    m_fSpeed = 300.f;

    m_ID = PLAYER;

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/player_idle.bmp", L"PlayerIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerRun.bmp", L"PlayerRun");

	m_pFrameKey = L"PlayerIdle";

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = .2f;
	m_tFrame.dwTime = 0.f;
}

int CPlayer::Update()
{
    __super::Update_Rec();
	CCreature::Move_Frame();

    Key_Input();
    return 0;
	Motion_Change();

}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC hdc)
{
    //Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	{
		//gpt의 손길
		Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
		float   zoom = CCamera::Get_Instance()->GetZoom(); // 또는 m_fZoom
	
		// 목적지(그려질) 크기 = 원본 프레임 크기 * 줌
		int dstW = (int)(m_vSize.x * zoom);
		int dstH = (int)(m_vSize.y * zoom);
	
		// 화면에 찍을 좌상단 (중심 기준 반 사이즈만큼 빼기)
		int dstX = (int)(centerS.x - dstW * 0.5f);
		int dstY = (int)(centerS.y - dstH * 0.5f);
	
		// 스프라이트시트에서 가져올 소스 사각형(프레임)
		int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스
		int srcY = m_tFrame.iMotion * (int)m_vSize.y; // 행 인덱스
	
		// 픽셀아트면 선명하게(해당 dc에 한번만)
		//SetStretchBltMode(hdc, COLORONCOLOR); // (부드럽게면 HALFTONE)
	
		// 투명색 키(마젠타)로 블릿
		GdiTransparentBlt(
			hdc, dstX, dstY, dstW, dstH,
			hMemDC, srcX, srcY, (int)m_vSize.x, (int)m_vSize.y,
			RGB(255, 255, 255));
	
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

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
        m_vPosition.x -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
		m_pFrameKey = L"PlayerRun";
		m_eCurState = WALK;


	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
        m_vPosition.x += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
		m_pFrameKey = L"PlayerRun";


		m_eCurState = WALK;

	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
        m_vPosition.y -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
		m_pFrameKey = L"Player_UP";


		//m_eCurState = WALK;

	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)/* && CKeyMgr::Get_Instance()->Key_Up(VK_SPACE)*/)
	{
        m_vPosition.y += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
		m_pFrameKey = L"Player_DOWN";
		m_eCurState = WALK;

	}

	else  if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		//m_bJump = true;
	}

	else
	{
		m_pFrameKey = L"PlayerIdle";

		m_eCurState = IDLE;
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
			m_tFrame.iEnd = 5;
			//m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			break;

		case WALK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 8;
			//m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			break;

		case ATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			//m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			break;

		case HIT:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			break;

		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed =.2f;
			m_tFrame.dwTime = 0.f;
			break;

		}

		m_ePreState = m_eCurState;
	}

}
