#include "pch.h"
#include "CMonsterBigSkull.h"
#include "CCamera.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"
#include "CColliderComp.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CStateBar.h"
#include "CUIMgr.h"
#include "CUI.h"
#include "CPlayer.h"
#include "CMonsterBullet.h"
#include "CBossHand.h"
#include "CBossBullet.h"
#include "CMonsterBullet01.h"



CMonsterBigSkull::CMonsterBigSkull() : m_eCurState(ST_END), m_ePreState(ST_END), m_hitFlash(false), m_bSwordDone(false), SwordCountMax(5)
{
}

CMonsterBigSkull::~CMonsterBigSkull()
{
	Release();
}

void CMonsterBigSkull::Initialize()
{
	//InitRand();

	//m_vPosition = { 1056.f * .5f,1056.f * .5f };
	 // 생성자 에서 무조건 넣어줘야함
	m_vSize = { 99,144 };
	m_fSpeed = 350.f;
	m_iMaxHP = 100.f;
	m_iHP = m_iMaxHP;
	m_iDamage = 10;

	m_ID = MONSTER;

	idelTime = 1.5f;

	idelTimeMax = idelTime;

	SwordTime = .3f;
	SwordTimeMax = SwordTime;

	m_HitTime = .01f;
	m_HitTimeMax = m_HitTime;

	m_iBarrelNum = 12;
	m_vBarrelDir = { -1,0 };

	DeadTime = 10.f;
	DeadTimeMax = DeadTime;

	m_AttackTime = 3.f;
	m_AttackTimeMax = m_AttackTime;

	//m_TmpSword.reserve(SwordCountMax);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/BigSkull/BigWhiteSkelIdle.bmp", L"BigSkellIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/BigSkull/BigWhiteSkelAttack.bmp", L"BigWhiteSkelAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/BigSkull/BigWhiteSkelMove.bmp", L"BigWhiteSkelMove");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/BigSkull/BansheeBullet.bmp", L"BansheeBullet");

	m_pFrameKey = L"BigSkellIdle";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = .2f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 99,144 };
	m_eCurState = IDLE;

	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, m_vSize, this));
	statebar = CAbstractFactory<CStateBar>::CreateUI(this);
	CUIMgr::Get_Instance()->Add_Object(statebar);

	//m_tEFFrame.iStart = 0;
	//m_tEFFrame.iEnd = 11;
	//m_tEFFrame.dwSpeed = .1f;
	//m_tEFFrame.dwTime = 0.f;
	//m_tEFFrame.vSize = { 120,120 };
	//
	//m_tTarget = CObjMgr::Get_Instance()->Get_Player();

	m_tTarget = CObjMgr::Get_Instance()->Get_Player();
}

int CMonsterBigSkull::Update()
{
	if (m_bDead)
	{

		statebar->Set_Dead(true);
		return OBJ_DEAD;
	}
	float dt = CTimeMgr::Get_Instance()->GetDeltaTime();


	float width = fabsf(m_tTarget->GetPosition().x - m_vPosition.x);
	float height = fabsf(m_tTarget->GetPosition().y - m_vPosition.y);

	float distance = sqrt((width * width) + (height * height));

	if (m_hitFlash == true)
	{
		m_HitTime -= dt;
		if (m_HitTime <= 0.f)
			m_hitFlash = false;
	}

	m_AttackTime -= dt;
	if (m_AttackTime <= 0 && m_bOnAttack == true)
	{
		m_bOnAttack = false;
		m_AttackTime = m_AttackTimeMax;
	}

	
	__super::Update_Rec();

	CCreature::Update();
	if(distance <= 500.f)
		Move();

	switch (m_eCurState)
	{
	case MONSTATE::MOVE:
	case MONSTATE::IDLE:
		idelTime -= dt;
		if (idelTime <= 0.f && distance <= 200.f)
		{
			Do_Attack();
			m_bStart = true;
			idelTime = idelTimeMax;
		}
		break;

	case MONSTATE::SWORDATTACK:
		//SwordTime -= dt;
		if (/*SwordTime <= 0.f && */ m_bStart==false)
		{
		m_eCurState = IDLE;
		SwordTime = SwordTimeMax;
		 
		}
		else
		SwordAttack();
		break;

	case MONSTATE::DEAD:
		DeadTime -= dt;
		if (DeadTime <= 0.f)
		{
			m_bDead = true;
		}
		else
			DeadEffect();
		break;
	}
	//__super::EffUpdate();
	__super::UpdateColl(m_vPosition);


	__super::Update_Rec();

	Motion_Change();

	CCreature::Move_Frame();

	Update_Rec();

	return 0;
}

void CMonsterBigSkull::Late_Update()
{

}

void CMonsterBigSkull::Render(HDC hdc)
{


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);


	Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vSize);

	// 스프라이트시트에서 가져올 소스 사각형(프레임)
	int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스
	int LR = 0;
	//Vector2 tmp = CObjMgr::Get_Instance()->Get_Player()->GetPosition()
	if (m_tTarget->GetPosition().x < m_vPosition.x)// 왼쪽
	{
		srcX = (abs(m_tFrame.iStart -m_tFrame.iEnd))* (int)m_vSize.x;
		LR = 1;
		// 투명색 키(마젠타)로 블릿
		GdiTransparentBlt(
			hdc,
			centerS.x - RenderSize.x * 0.5f,
			centerS.y - RenderSize.y * 0.5f,
			RenderSize.x, RenderSize.y,
			hMemDC, srcX, LR * m_vSize.y, (int)m_vSize.x, (int)m_vSize.y,
			RGB(255, 0, 255));
	}
	else
	{

	// 투명색 키(마젠타)로 블릿
	GdiTransparentBlt(
		hdc,
		centerS.x - RenderSize.x * 0.5f,
		centerS.y - RenderSize.y * 0.5f,
		RenderSize.x, RenderSize.y,
		hMemDC, srcX, LR * m_vSize.y, (int)m_vSize.x, (int)m_vSize.y,
		RGB(255, 0, 255));
	}



	__super::RenderColl(hdc, m_vPosition);

	//__super::EffRender(hdc);

}

void CMonsterBigSkull::Release()
{

}

void CMonsterBigSkull::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{

	switch (obj->Get_ID())
	{
		case PLAYER:
		{
		
			if (other.GetType() == ColliderType::ATTACK)
			{
				if (m_bOnAttack == true)
				{
				if (CPlayer* creature = dynamic_cast<CPlayer*>(obj))
					creature->Take_Damage(m_iDamage);

				}
		
			}
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
	case PLATFORM:
	{
		//CObj::Update_Rec();


		
			if (my.GetType() == ColliderType::BODY)
				Landed_Platform(obj, my, other);
			//m_bPlayerLanded = true;
				//// 충돌판정용 RECT 갱신
		
	}
	break;

	default:
		break;
	}
}



void CMonsterBigSkull::SwordAttack()
{

	if(m_tFrame.iStart >= 2 && m_tFrame.iStart <= 5)
	m_bOnAttack = true;
	else
		m_bOnAttack = false;

	if (m_tFrame.iStart >= m_tFrame.iEnd)
		m_bStart = false;


}



void CMonsterBigSkull::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_pFrameKey = L"BigSkellIdle";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 99,144 };

			m_vSize = m_tFrame.vSize;
			break;

		case SWORDATTACK:
			m_pFrameKey = L"BigWhiteSkelAttack";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 11;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 183,144 };
			m_vSize = m_tFrame.vSize;
			break;

		case MOVE:
			m_pFrameKey = L"BigWhiteSkelMove";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 99,144 };
			m_vSize = m_tFrame.vSize;
			break;

		case DEAD:
			m_pFrameKey = L"BossDead";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;
			m_tFrame.dwSpeed = .0f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 210.f, 231.f };
			m_vSize = m_tFrame.vSize;
			break;

		}

		m_ePreState = m_eCurState;
	}
}

void CMonsterBigSkull::Do_Attack()
{
	m_eCurState = SWORDATTACK;
}

void CMonsterBigSkull::Take_Damage(int _damage)
{
	if (m_iHP - _damage > 0)
		Set_HP(m_iHP - _damage);
	else
	{
		Set_HP(0);
		m_eCurState = DEAD;
		//todo 죽었어! 플레이어 사망 조건 true로 설정
	}

//	m_hitFlash = true;
//	m_HitTime = m_HitTimeMax;
//
	cout << m_iHP << endl;

}

Vector2 CMonsterBigSkull::RotateVector(Vector2& v, float angle)
{
	float radian = angle * (PI / 180.f);

	float cosX = cosf(radian);
	float sinY = sinf(radian);

	Vector2 result;
	result.x = v.x * cosX - v.y * sinY;
	result.y = v.x * sinY - v.y * cosX;
	return result;
}

void CMonsterBigSkull::DeadEffect()
{
	//int k = RandInt(-150, 150);
	//int j = RandInt(-150, 150);
	//
	//for (int i = 0; i < 10; i++)
	//{
	//	m_vEffect.push_back(CEffectComp({ k,j }, this, m_tEFFrame, { 40,40 }, L"BossFinish"));
	//
	//}
	//
	//if (m_vPosition.y <= (528.f + 170.f))
	//	m_vPosition.y += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	m_bDead = true;

}

void CMonsterBigSkull::Move()
{
	if (m_bStart == true || m_eCurState == DEAD || m_eCurState == SWORDATTACK)
		return;
	m_eCurState = MOVE;
	if (m_tTarget->GetPosition().x -50 >= m_vPosition.x)// 왼쪽
	{
		m_vPosition.x += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
	}
	else if (m_tTarget->GetPosition().x + 50 <= m_vPosition.x)
	{
		m_vPosition.x -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}
	else
		m_eCurState = IDLE;

}
