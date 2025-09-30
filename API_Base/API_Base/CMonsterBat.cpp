#include "pch.h"
#include "CMonsterBat.h"
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



CMonsterBat::CMonsterBat() : m_eCurState(ST_END), m_ePreState(ST_END), m_hitFlash(false), m_bSwordDone(false), SwordCountMax(5)
{
}

CMonsterBat::~CMonsterBat()
{
	Release();
}

void CMonsterBat::Initialize()
{
	//InitRand();

	//m_vPosition = { 1056.f * .5f,1056.f * .5f };
	 // 생성자 에서 무조건 넣어줘야함
	m_vSize = { 60,66 };
	m_fSpeed = 500.f;
	m_iMaxHP = 100.f;
	m_iHP = m_iMaxHP;
	m_iDamage = 10;

	m_ID = MONSTER;

	idelTime = 1.5f;
	bulletTime = 5.f;
	idelTimeMax = idelTime;
	bulletTimeMax = bulletTime;

	HandTime = 15.f;
	HandTimeMax = HandTime;

	SwordTime = .3f;
	SwordTimeMax = SwordTime;

	m_HitTime = .01f;
	m_HitTimeMax = m_HitTime;

	m_iBarrelNum = 12;
	m_vBarrelDir = { -1,0 };

	DeadTime = 10.f;
	DeadTimeMax = DeadTime;

	//m_TmpSword.reserve(SwordCountMax);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/Bat/BansheeIdle.bmp", L"BansheeIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/Bat/BansheeAttack.bmp", L"BansheeAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/Bat/BansheeBulletBoom.bmp", L"BansheeBulletBoom");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mon/Bat/BansheeBullet.bmp", L"BansheeBullet");

	m_pFrameKey = L"BansheeIdle";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = .3f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 60,66 };
	m_eCurState = IDLE;

	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, m_vSize, this));
	statebar = CAbstractFactory<CStateBar>::CreateUI(this);
	CUIMgr::Get_Instance()->Add_Object(statebar);

	m_tEFFrame.iStart = 0;
	m_tEFFrame.iEnd = 11;
	m_tEFFrame.dwSpeed = .1f;
	m_tEFFrame.dwTime = 0.f;
	m_tEFFrame.vSize = { 120,120 };

	m_tTarget = CObjMgr::Get_Instance()->Get_Player();
}

int CMonsterBat::Update()
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

	switch (m_eCurState)
	{
	case MONSTATE::IDLE:
		idelTime -= dt;
		if (idelTime <= 0.f && distance <= 400.f)
		{
			Do_Attack();
			idelTime = idelTimeMax;
		}
		break;
	case MONSTATE::BULLETATTACK:
		//bulletTime -= dt;
		if (/*m_pFrameKey == L"BansheeAttack" && */m_tFrame.iStart >= m_tFrame.iEnd)
		{
			m_eCurState = IDLE;
			//bulletTime = bulletTimeMax;
		}
		else
			BulletAttack();
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
	__super::EffUpdate();
	__super::UpdateColl(m_vPosition);


	__super::Update_Rec();

	Motion_Change();

	CCreature::Move_Frame();

	Update_Rec();

	return 0;
}

void CMonsterBat::Late_Update()
{

}

void CMonsterBat::Render(HDC hdc)
{
	

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);


	Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vSize);

	// 스프라이트시트에서 가져올 소스 사각형(프레임)
	int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스
	int LR = 1;
	//Vector2 tmp = CObjMgr::Get_Instance()->Get_Player()->GetPosition()
	if (m_tTarget->GetPosition().x > m_vPosition.x)// 왼쪽
	{
		LR = 0;
	}


	// 투명색 키(마젠타)로 블릿
	GdiTransparentBlt(
		hdc,
		centerS.x - RenderSize.x * 0.5f,
		centerS.y - RenderSize.y * 0.5f,
		RenderSize.x, RenderSize.y,
		hMemDC, srcX, LR* m_vSize.y, (int)m_vSize.x, (int)m_vSize.y,
		RGB(255, 0, 255));


	__super::RenderColl(hdc, m_vPosition);

	__super::EffRender(hdc);

}

void CMonsterBat::Release()
{

}

void CMonsterBat::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{

	switch (obj->Get_ID())
	{
		//case PLAYER:
		//{
		//	if (other.GetType() == ColliderType::ATTACK)
		//	{
		//		if (CPlayer* creature = dynamic_cast<CPlayer*>(obj))
		//			Take_Damage(creature->Get_Damage());
		//
		//	}
		//}
		//break;
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


	default:
		break;
	}
}

void CMonsterBat::BulletAttack()
{
	accTime += CTimeMgr::Get_Instance()->GetDeltaTime();
	if (1.8f < accTime)
	{
		//m_iAngle += 10.0;
		//m_iAngle %= 360;
		//
		for (int j = 0; j < m_iBarrelNum; j++)
		{
			m_iAngle = (/*m_iAngle +*/ (30 * j)) % 360;
			Vector2 dir = RotateVector(m_vBarrelDir, m_iAngle);
			CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonsterBullet01>::Create({ m_vPosition.x ,m_vPosition.y  }, {13, 16}, dir));
		}
		accTime = 0.f;
	}


}

void CMonsterBat::SwordAttack()
{
	if (SwordCount != SwordCountMax)
	{
		SwordTime -= CTimeMgr::Get_Instance()->GetDeltaTime();

		if (SwordTime <= 0.f)
		{
			Vector2 dir = { 0,-1 };
			CObj* tmp = CAbstractFactory<CBossBullet>::Create({ m_vPosition.x - 150 + 80 * SwordCount,m_vPosition.y - 200 }, { 20,20 }, dir);

			tmp->Initialize();
			CObjMgr::Get_Instance()->Add_Object(tmp);
			//m_TmpSword.push_back(tmp);
			SwordCount++;


			SwordTime = SwordTimeMax;
		}

	}
	else if (SwordCount == SwordCountMax)
	{

		m_bSwordDone = true;
		const auto& bullet = CObjMgr::Get_Instance()->Get_Bullet();
		if (bullet.empty())
		{

			return;
		}
		for (auto& tmp : bullet)
		{
			if (dynamic_cast<CBossBullet*>(tmp))
			{
				m_bSwordDone = false;
				break;
			}

		}

	}



}



void CMonsterBat::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_pFrameKey = L"BansheeIdle";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = .3f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 60,66 };

			m_vSize = m_tFrame.vSize;
			break;

		case BULLETATTACK:
			m_pFrameKey = L"BansheeAttack";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = .3f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 60,66 };
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

void CMonsterBat::Do_Attack()
{
	m_eCurState = BULLETATTACK;
}

void CMonsterBat::Take_Damage(int _damage)
{
	if (m_iHP - _damage > 0)
		Set_HP(m_iHP - _damage);
	else
	{
		Set_HP(0);
		m_eCurState = DEAD;
		//todo 죽었어! 플레이어 사망 조건 true로 설정
	}

	m_hitFlash = true;
	m_HitTime = m_HitTimeMax;

	cout << m_iHP << endl;

}

Vector2 CMonsterBat::RotateVector(Vector2& v, float angle)
{
	float radian = angle * (PI / 180.f);

	float cosX = cosf(radian);
	float sinY = sinf(radian);

	Vector2 result;
	result.x = v.x * cosX - v.y * sinY;
	result.y = v.x * sinY - v.y * cosX;
	return result;
}

void CMonsterBat::DeadEffect()
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
