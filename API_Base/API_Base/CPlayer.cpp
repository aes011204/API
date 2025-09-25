#include "pch.h"
#include "CPlayer.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CMonster.h"
#include "CCollisionMgr.h"
#include "CColliderComp.h"
#include "CMonsterBullet.h"

CPlayer::CPlayer() :
	m_eCurState(PS_END), m_ePreState(PS_END), m_fInvincibleTime(0.f), m_bDash(false), m_DashDuration(0.f), m_DashSpeed(0.f), m_DashTime(0.f),
	m_bDropDown(false), m_dropRemain(0.f)
	,m_bStop(false)
{
	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, { 48.f,60.f }, this));
	m_vCollider.push_back(CColliderComp(ColliderType::ATTACK, { 0,0 }, { 110.f,110.f },this, true));
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

	m_fInvincibleTime = 0.5f;


	m_DashSpeed = 500.f;
	m_DashDuration = 5.f;
	m_DashTime = .5f;


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerIdle.bmp", L"PlayerIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerRun.bmp", L"PlayerRun");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerJump.bmp", L"PlayerJump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerDie.bmp", L"PlayerDie");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RunEffectL.bmp", L"RushDust");

	m_pFrameKey = L"PlayerIdle";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = .2f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 78.f, 60.f };

	
	m_tEFFrame.iStart = 0;
	m_tEFFrame.iEnd = 5;
	m_tEFFrame.dwSpeed = .1f;
	m_tEFFrame.dwTime = 0.f;
	m_tEFFrame.vSize = { 48,48 };

	EffTime = .5f;
	EffTimeMax = EffTime;

	


}

int CPlayer::Update()
{

	if (m_bDead)
	{
		m_pFrameKey = L"PlayerDie";
		//return OBJ_DEAD;// 일단 플레이어는 삭제 하면 안되는데 일단 임시로
	}
	// 누적시간 제는용
	float dt = CTimeMgr::Get_Instance()->GetDeltaTime();
	accTime += dt;

	__super::UpdateColl(m_vPosition);
	__super::EffUpdate();


	if (m_bDash)
	{
		Dash(m_vDashDir);
	}

    __super::Update_Rec();


    Key_Input();
	CCreature::Update();

	Motion_Change(); 

	LimitPlayerPos();

	CCreature::Move_Frame();
	//CCreature::Move_EffectFrame();
    return 0;

}

void CPlayer::Late_Update()
{
	if (m_bDropDown)
	{
		m_dropRemain -= CTimeMgr::Get_Instance()->GetDeltaTime();

		if (m_dropRemain <= 0)
			m_bDropDown = false;
	}
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
	

		//Move_EffectFrame(hdc);
	//
		

	m_vBarrelPos = centerS + ( m_vBarrelDir*30);

	MoveToEx(hdc, static_cast<int>(centerS.x) , static_cast<int>(centerS.y) , nullptr);
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

	__super::RenderColl(hdc, m_vPosition);
	__super::EffRender(hdc);
}

void CPlayer::Release()
{
}

void CPlayer::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	//if (obj->Get_ID() != PLATFORM)
	//{
	//	m_bPlayerLanded = false;
	//}

	

	
	switch (obj->Get_ID())
	{
	case MONSTER:
	{
		if(CMonster* creature = dynamic_cast<CMonster*>(obj))
			Take_Damage(creature->Get_Damage());
	}
	break;
	case BULLET:
	{
		if(CMonsterBullet* mon = dynamic_cast<CMonsterBullet*>(obj))
		{
			Take_Damage(mon->Get_Damage());
	
			//Vector2 dir = m_vPosition - mon->Get_Position();
			//dir = Vector2::Nomalize(dir);
			//
			//m_vPosition.x += dir.x * 15.f;
			//m_vPosition.y += dir.y * 30.f;
		}
	}
	break;
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
			//CObj::Update_Rec();
		
		
		if (!m_bDropDown)
		{
			if(my.GetType()==ColliderType::BODY)
 				Landed_Platform(obj, my, other);
		//m_bPlayerLanded = true;
			//// 충돌판정용 RECT 갱신
		}
	}
	break;
	default:
		break;
	}

	
}

void CPlayer::Key_Input()
{
	if (m_bStop == true)
	{
		m_pFrameKey = L"PlayerIdle";
		m_eCurState = IDLE;
		return;
	}

	float dt = CTimeMgr::Get_Instance()->GetDeltaTime();

	float fY(0.f);
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		Vector2 mos = CKeyMgr::Get_Instance()->GetMousePos();
		mos = CCamera::Get_Instance()->GetRealPos(mos);
		m_vDashDir = (mos - m_vPosition).GetNomalized();
		m_bDash = true;
	}
	else if ( CKeyMgr::Get_Instance()->Key_Down(VK_SPACE) && (CKeyMgr::Get_Instance()->Key_Pressing('S')))
	{
		m_bDropDown = true;
		m_dropRemain = .2f;
			m_pFrameKey = L"PlayerJump";
		m_eCurState = JUMP;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
	}
	 else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
        m_vPosition.x -= m_fSpeed * dt;
		m_pFrameKey = L"PlayerRun";
		m_eCurState = WALK;
		EffTime -= dt;
		if (EffTime < 0.f)
		{
			m_vEffect.push_back(CEffectComp({ 24,10 }, this, m_tEFFrame, L"RushDust"));
			EffTime = EffTimeMax;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
        m_vPosition.x += m_fSpeed * dt;
		m_pFrameKey = L"PlayerRun";
		m_eCurState = WALK;
		EffTime -= dt;
		if (EffTime < 0.f)
		{
			m_vEffect.push_back(CEffectComp({ -24,10 }, this, m_tEFFrame, L"RushDust"));
			EffTime = EffTimeMax;
		}

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
        m_vPosition.y -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}
	else
	{
		m_pFrameKey = L"PlayerIdle";
		m_eCurState = IDLE;
	}



	if (m_bJump||m_bDash)
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



void CPlayer::Take_Damage(int damage)
{

	
	if (accTime > m_fInvincibleTime)
	{
		if (m_iHP - damage > 0)
			Set_HP(m_iHP - damage);
		else
		{
			Set_HP(0);
			m_bDead = true;
			//todo 죽었어! 플레이어 사망 조건 true로 설정
		}
		accTime = 0.f;
	}
}

void CPlayer::Dash(Vector2 tmpdir)
{
	//if (m_bDash == true /*&& m_bJump == false*/)
	{
		//if (m_Stepback == false)
		//{
		//	m_vPosition.x += m_StepBackSpeed * (-tmpdir.x) * m_fDeltaTime;
		//
		//	m_StepbackTime -= m_fDeltaTime;
		//
		//
		//	if (m_StepbackTime <= 0.f)
		//	{
		//		m_StepbackTime = .5f;
		//		m_Stepback = true;
		//	}
		//
		//
		//}
		//else
		{
			//if (tmpdir.y >= 0)
			//{
			//	tmpdir.y = 0;
			//}

			m_vPosition.x += m_DashSpeed *( tmpdir.x * CTimeMgr::Get_Instance()->GetDeltaTime());
			m_vPosition.y += 1200 *( tmpdir.y * CTimeMgr::Get_Instance()->GetDeltaTime());
		
			m_DashTime -= CTimeMgr::Get_Instance()->GetDeltaTime();
			if (m_DashTime <= 0.f)
			{
				m_bDash = false;
				m_DashTime = .5f;
				//m_Stepback = false;
			}
			m_bPlayerLanded = false;

		}
	}
}


void CPlayer::LimitPlayerPos()
{
	Vector2 pos = m_vPosition;
	pos.x = Clamp(pos.x, CCamera::Get_Instance()->GetLookAt().x - WINCX * .5f, CCamera::Get_Instance()->GetLookAt().x + WINCX * .5f);
	pos.y = Clamp(pos.y, CCamera::Get_Instance()->GetLookAt().y- WINCY * .5f, CCamera::Get_Instance()->GetLookAt().y + WINCY * .5f);

	m_vPosition = pos;
}