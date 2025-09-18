#include "pch.h"
#include "CPlayer.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CMonster.h"
#include "CCollisionMgr.h"
CPlayer::CPlayer() : m_eCurState(PS_END), m_ePreState(PS_END)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
    m_vSize = { 78.f, 60.f };
    m_vPosition = { WINCX*.5f,WINCY*.5f };
    m_fSpeed = 500.f;
	
	m_iMaxHP = 80;
	m_iHP = m_iMaxHP;

	m_iDamage = 1;
    m_ID = PLAYER;

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerIdle.bmp", L"PlayerIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerRun.bmp", L"PlayerRun");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerJump.bmp", L"PlayerJump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerDie.bmp", L"PlayerDie");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RunEffectL.bmp", L"RushDust");

	m_pFrameKey = L"PlayerIdle";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = .05f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 78.f, 60.f };

	m_pEFFrameKey = L"RushDust";
	m_tEFFrame.iStart = 0;
	m_tEFFrame.iEnd = 5;
	m_tEFFrame.dwSpeed = .2f;
	m_tEFFrame.dwTime = 0.f;
	m_tEFFrame.vSize = {48,48};
}

int CPlayer::Update()
{

	if (m_bDead)
	{
		m_pFrameKey = L"PlayerDie";
		//return OBJ_DEAD;// 일단 플레이어는 삭제 하면 안되는데 일단 임시로
	}
    __super::Update_Rec();
	CCreature::Update();

	Motion_Change(); 


    Key_Input();
	CCreature::Move_Frame();
	CCreature::Move_EffectFrame();
    return 0;

}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC hdc)
{
    //Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

   // Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);

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
			hMemDC, srcX, m_vSize.y*(int)m_eDir, (int)m_vSize.x, (int)m_vSize.y,
			RGB(255, 0, 255));
	

		Move_EffectFrame(hdc);
	//

	m_vBarrelPos = centerS + ( m_vBarrelDir*50);

	MoveToEx(hdc, static_cast<int>(m_vPosition.x) , static_cast<int>(m_vPosition.y) , nullptr);
	LineTo(hdc, static_cast<int>(m_vBarrelPos.x) , static_cast<int>(m_vBarrelPos.y));

	
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
	m_bPlayerLanded = false;
	switch (obj->Get_ID())
	{
	case MONSTER:
	{
		CMonster* creature = dynamic_cast<CMonster*>(obj);
		Take_Damage(creature->Get_Damage());
	}
	break;
	//case MON_BULLET:
	//{
	//	{
	//		Take_Damage(obj->Get_Damage());
	//
	//		Vector2 dir = m_vPosition - pObj->Get_Position();
	//		dir = Vector2::Nomalize(dir);
	//
	//		m_vPosition.x += dir.x * 15.f;
	//		m_vPosition.y += dir.y * 30.f;
	//	}
	//}
	//break;
	case ITEM:
	{
		//todo 아이템도 다양해지면...
		/*
		 * 아이템별로 세부 태그에 따라 작업이 나뉘어야 정석임
		 * 그 작업은 새로운 아이템 분류용 enum을 만들어서,
		 * 이를 아이템용 새로운 멤버변수에 넣어줘야 할듯
		 */
	}
	break;
	case PLATFORM:
	{
		Landed_Platform(obj);
		m_bPlayerLanded = true;
		//// 충돌판정용 RECT 갱신
		CObj::Update_Rec();
	}
	break;
	default:
		break;
	}
}
void CPlayer::Landed_Platform(CObj* pObj)
{
	float fX = 0.f, fY = 0.f;

	if (CCollisionMgr::Check_Rect(this, pObj, &fX, &fY))
	{
		if (fX > fY)	// 상하 충돌
		{
			if (m_vPosition.y < pObj->GetPosition().y && m_fSpeedY >= 0.f)		//	상 충돌
			{
				m_fSpeedY = 0.f;
				m_iPlayerJumpCount = 0;
				m_vPosition.y = pObj->GetPosition().y - (pObj->GetSize().y / 2.f + m_vSize.y / 2.f);

				m_bPlayerLanded = true;
				m_bJump = false;
			}
			else //-------------------------------------------	하 충돌
			{
				//m_fSpeedY = 0.f;
				//m_vPosition.y = pObj->Get_Position().y + (pObj->Get_Size().y / 2.f + m_vSize.y / 2.f);
				//! 천장 필요하면 사용하기
			}
		}

		if (fX < fY)		// 좌우 충돌
		{
			if (m_vPosition.x < pObj->GetPosition().x)		//	좌 충돌
			{
				m_vPosition.x = pObj->GetPosition().x - (pObj->GetSize().x / 2.f + m_vSize.x / 2.f);
			}
			else //-------------------------------------------	우 충돌
			{
				m_vPosition.x = pObj->GetPosition().x + (pObj->GetSize().x / 2.f + m_vSize.x / 2.f);
			}
		}
	}
}

void CPlayer::Key_Input()
{
	float fY(0.f);
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
        m_vPosition.x -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
		m_pFrameKey = L"PlayerRun";
		m_eCurState = WALK;

		//m_bJump = false;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
        m_vPosition.x += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
		m_pFrameKey = L"PlayerRun";
		m_eCurState = WALK;

		//m_bJump = false;
	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
        m_vPosition.y -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

		//m_bJump = false;
	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN) && CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
        m_vPosition.y += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
		m_pFrameKey = L"Player_DOWN";
		m_eCurState = WALK;
		//m_bJump = false;
	}
	else
	{
		m_pFrameKey = L"PlayerIdle";

		m_eCurState = IDLE;
		//m_bJump = false;
	}

	if (m_bJump)
	{
	m_pFrameKey = L"PlayerJump";
	m_eCurState = JUMP;

	}


	if (CKeyMgr::Get_Instance()->Key_Down('V'))
	{
		// 인벤토리 
	}

	if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		// 능력치 정보창
	}

	// 마우스 정보 가져오기
	Vector2 mouse = CKeyMgr::Get_Instance()->GetMousePos();
	
	//CCamera::Get_Instance()->GetRealPos(LeftRight);
	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	{
		
		m_vBarrelDir = Vector2::Nomalize(mouse - RenderPos);
	}
	if (mouse.x > RenderPos.x)
	{
		m_eDir = RIGHT;
	}
	else
	{
		m_eDir = LEFT;
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
			m_tFrame.vSize = { 78.f, 60.f };
			m_vSize = m_tFrame.vSize;
			break;

		case WALK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 7;
			
			m_tFrame.dwSpeed = .1f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 78.f, 60.f };
			m_vSize = m_tFrame.vSize;
			break;

		case JUMP:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;			
			m_tFrame.dwSpeed = 2.f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 75.f, 60.f };
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

		case DASH:
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
			m_tFrame.vSize = { 78.f, 75.f };
			m_vSize = m_tFrame.vSize;
			break;

		}

		m_ePreState = m_eCurState;
	}



}


void CPlayer::Move_EffectFrame(HDC hdc)
{
//	HDC	hEFMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pEFFrameKey);
//
//	// 먼지 효과 (발생하는 순간 의 좌표 움직이면 안더ㅣㅁ) 지금은 1번 돌떄중복으로 생기지 않음
//
//	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos({ m_vEFPos.x ,m_vEFPos.y + m_tEFFrame.vSize.y * .5f });
//
//
//	Vector2 RenderEFSize = CCamera::Get_Instance()->GetRenderSize(m_tEFFrame.vSize);
//
//
//	GdiTransparentBlt(
//		hdc, RenderPos.x - RenderEFSize.x*.5f, RenderPos.y - RenderEFSize.y * .5f,
//		RenderEFSize.x, RenderEFSize.y,
//		hEFMemDC,
//		m_tEFFrame.iStart * m_tEFFrame.vSize.x,
//		0,
//		m_tEFFrame.vSize.x, m_tEFFrame.vSize.y,
//		RGB(255, 0, 255));
}

void CPlayer::Take_Damage(int damage)
{

	if (m_iHP - damage > 0)
		Set_HP(m_iHP - damage);
	else
	{
		Set_HP(0);
		m_bDead = true;
		//todo 죽었어! 플레이어 사망 조건 true로 설정
	}
}
