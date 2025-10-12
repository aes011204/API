#include "pch.h"
#include "CMonsterBow.h"
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
#include "CSoundManager.h"



CMonsterBow::CMonsterBow() : m_eCurState(ST_END), m_ePreState(ST_END), m_hitFlash(false), m_bSwordDone(false), SwordCountMax(5)
{
}

CMonsterBow::~CMonsterBow()
{
	Release();
}

void CMonsterBow::Initialize()
{
	//InitRand();

	//m_vPosition = { 1056.f * .5f,1056.f * .5f };
	 // 생성자 에서 무조건 넣어줘야함
	m_vSize = { 42,57 };
	m_fSpeed = 200.f;
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

	m_AttackTime = 1.f;
	m_AttackTimeMax = m_AttackTime;

	//m_TmpSword.reserve(SwordCountMax);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/Mini/SkelIdle.bmp", L"SkelIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/Mini/SkelWalk.bmp", L"SkelWalk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/Mini/SkelSword.bmp", L"SkelSword");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/Mini/SkelSwordOP.bmp", L"SkelSwordOP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/Mini/SkelSwordEffect.bmp", L"SkelSwordEffect");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/BigSkull/BansheeBullet.bmp", L"BansheeBullet");

	m_pFrameKey = L"SkelIdle";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 0;
	m_tFrame.dwSpeed = .2f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 42,57 };
	m_eCurState = IDLE;

	 m_StepbackTime = .1f;
	 m_DashTime = .5f;
	 m_DashDuration = 3.f;

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

int CMonsterBow::Update()
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


	__super::Update_Rec();

	CCreature::Update();



	m_DashDuration -= CTimeMgr::Get_Instance()->GetDeltaTime();;

	if (!m_isDash && 400 >= (fabs(distance)) && m_DashDuration <= 0.f)
	{
		Vector2 pos= m_tTarget->GetPosition();
		m_vDirection = Vector2::Nomalize(pos - m_vPosition);
		
		m_isDash = true;
		m_DashDuration = 5.f;

	}

	Dash(m_vDirection);

	if (m_isDash == true)
	{
		m_pFrameKey = L"SkelIdle";
	}

	if (distance <= 500.f)
		Move();

	switch (m_eCurState)
	{
	//case MONSTATE::MOVE:
	//case MONSTATE::IDLE:
	//	idelTime -= dt;
	//	if (idelTime <= 0.f && distance <= 200.f)
	//	{
	//		//Do_Attack();
	//		m_bStart = true;
	//		idelTime = idelTimeMax;
	//	}
	//	break;

	//case MONSTATE::SWORDATTACK:
	//	//SwordTime -= dt;
	//	if (/*SwordTime <= 0.f && */ m_bStart == false)
	//	{
	//		m_eCurState = IDLE;
	//		SwordTime = SwordTimeMax;
	//
	//	}
	//	else
	//		SwordAttack();
	//	break;

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

void CMonsterBow::Late_Update()
{

}

void CMonsterBow::Render(HDC hdc)
{


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);


	Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vSize);

	// 스프라이트시트에서 가져올 소스 사각형(프레임)
	int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스
	int LR = 0;


	HDC	hMemDC1 = CBmpMgr::Get_Instance()->Find_Img(L"SkelSword");
	HDC	hMemDC2 = CBmpMgr::Get_Instance()->Find_Img(L"SkelSwordOP");

	
	Vector2 Ssize = { 108, 90 };
	Vector2 centerS1 = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 RenderSize1 = CCamera::Get_Instance()->GetRenderSize(Ssize);


	//Vector2 tmp = CObjMgr::Get_Instance()->Get_Player()->GetPosition()
	if (m_tTarget->GetPosition().x < m_vPosition.x)// 왼쪽
	{
		srcX = m_tFrame.iStart  * (int)m_vSize.x;
		LR = 1;
		// 투명색 키(마젠타)로 블릿
		GdiTransparentBlt(
			hdc,
			centerS1.x - RenderSize1.x * 0.5f,
			centerS1.y - RenderSize1.y * 0.5f,
			RenderSize1.x, RenderSize1.y,
			hMemDC2, 0, 0, (int)Ssize.x, (int)Ssize.y,
			RGB(255, 0, 255));

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

		GdiTransparentBlt(
			hdc,
			centerS1.x - RenderSize1.x * 0.5f,
			centerS1.y - RenderSize1.y * 0.5f,
			RenderSize1.x, RenderSize1.y,
			hMemDC1, 0, 0, (int)Ssize.x, (int)Ssize.y,
			RGB(255, 0, 255));


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

void CMonsterBow::Release()
{
	statebar->Set_Dead(true);
}

void CMonsterBow::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{

	switch (obj->Get_ID())
	{
	case PLAYER:
	{

		if (other.GetType() == ColliderType::ATTACK)
		{
			
				if (CPlayer* creature = dynamic_cast<CPlayer*>(obj))
					creature->Take_Damage(m_iDamage);

			

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



void CMonsterBow::SwordAttack()
{

	if (m_tFrame.iStart >= 2 && m_tFrame.iStart <= 5)
	{
		m_bOnAttack = true;
		if (m_tFrame.iStart >= 0)
		{

			float m_fVolume = 20.f;
			CSoundManager::Get_Instance()->PlaySound(L"swing0.wav", CHANNELID::SOUND_EAT1, m_fVolume);

		}
	}
	else
		m_bOnAttack = false;

	if (m_tFrame.iStart >= m_tFrame.iEnd)
		m_bStart = false;



}



void CMonsterBow::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_pFrameKey = L"SkelIdle";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 42,57 };

			m_vSize = m_tFrame.vSize;
			break;

		case MOVE:
			m_pFrameKey = L"SkelWalk";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 42,57 };
			m_vSize = m_tFrame.vSize;
			break;

		//case MOVE:
		//	m_pFrameKey = L"SkelWalk";
		//	m_tFrame.iStart = 0;
		//	m_tFrame.iEnd = 5;
		//	m_tFrame.dwSpeed = .2f;
		//	m_tFrame.dwTime = 0.f;
		//	m_tFrame.vSize = { 99,144 };
		//	m_vSize = m_tFrame.vSize;
		//	break;

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

void CMonsterBow::Do_Attack()
{
	m_eCurState = SWORDATTACK;
}

void CMonsterBow::Take_Damage(int _damage)
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


}

Vector2 CMonsterBow::RotateVector(Vector2& v, float angle)
{
	float radian = angle * (PI / 180.f);

	float cosX = cosf(radian);
	float sinY = sinf(radian);

	Vector2 result;
	result.x = v.x * cosX - v.y * sinY;
	result.y = v.x * sinY - v.y * cosX;
	return result;
}

void CMonsterBow::DeadEffect()
{
	
	m_bDead = true;

}

void CMonsterBow::Move()
{
	if (m_bStart == true || m_eCurState == DEAD || m_eCurState == SWORDATTACK|| m_isDash == true)
		return;
	m_eCurState = MOVE;

	//Dash(m_tTarget->GetDirection());

	if (m_tTarget->GetPosition().x - 130 >= m_vPosition.x)// 왼쪽
	{
		m_vPosition.x += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();
	}
	else if (m_tTarget->GetPosition().x + 130 <= m_vPosition.x)
	{
		m_vPosition.x -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}
	else
		m_eCurState = IDLE;

}
void CMonsterBow::Dash(Vector2 tmpdir)
{
	if (m_isDash == true )
	{
		m_eCurState = IDLE;

		if (m_Stepback == false)
		{
			m_vPosition.x += 100 * (-tmpdir.x) *CTimeMgr::Get_Instance()->GetDeltaTime();

			m_StepbackTime -= CTimeMgr::Get_Instance()->GetDeltaTime();


			if (m_StepbackTime <= 0.f)
			{
				m_StepbackTime = .5f;
				m_Stepback = true;
			}


		}
		else
		{
			if (tmpdir.y >= 0)
			{
				tmpdir.y = 0;
			}

			m_vPosition.x += 600 * tmpdir.x * CTimeMgr::Get_Instance()->GetDeltaTime();
			//m_vPosition.y += 1200 * tmpdir.y * m_fDeltaTime;

			m_DashTime -= CTimeMgr::Get_Instance()->GetDeltaTime();
			if (m_DashTime <= 0.f)
			{
				m_isDash = false;
				m_DashTime = 1.0f;
				m_Stepback = false;
			}

		}
	}

}