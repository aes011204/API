#include "pch.h"
#include "CBoss.h"
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
#include "CSoundManager.h"



CBoss::CBoss() : m_eCurState(ST_END), m_ePreState(ST_END), m_RHand(nullptr), m_LHand(nullptr), m_hitFlash(false), m_bSwordDone(false), SwordCountMax(5)
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
	m_fSpeed = 500.f;
	m_iMaxHP = 100.f;
	m_iHP = m_iMaxHP;
	m_iDamage = 10;

	m_ID = BOSS;

	idelTime = 3.f;
	bulletTime = 5.f;
	idelTimeMax = idelTime;
	bulletTimeMax = bulletTime;

	HandTime = 15.f;
	HandTimeMax = HandTime;

	SwordTime = .3f;
	SwordTimeMax = SwordTime;

	m_HitTime = .01f;
	m_HitTimeMax = m_HitTime;

	m_iBarrelNum = 4;
	m_vBarrelDir = { -1,0 };

	DeadTime = 5.f;
	DeadTimeMax = DeadTime;

	//m_TmpSword.reserve(SwordCountMax);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossIdle.bmp", L"BossIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossAttack.bmp", L"BulletAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/HandIdle.bmp", L"HandIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/HandAttack.bmp", L"HandAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/SkellBossDead.bmp", L"BossDead");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/SkellBossAttackHit.bmp", L"AttackHit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/SkellBossIdleHit.bmp", L"IdleHit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossFinish.bmp", L"BossFinish");

	m_pFrameKey = L"BossIdle";
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 9;
	m_tFrame.dwSpeed = .3f;
	m_tFrame.dwTime = 0.f;
	m_tFrame.vSize = { 210,285 };
	m_eCurState = IDLE;

	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 20,30 }, { 150.f,200.f }, this));
	statebar = CAbstractFactory<CStateBar>::CreateUI(this);
	CUIMgr::Get_Instance()->Add_Object(statebar);

	m_LHand = CAbstractFactory<CBossHand>::CreateHand(CBossHand::LR::HAND_LEFT);
	m_RHand = CAbstractFactory<CBossHand>::CreateHand(CBossHand::LR::HAND_RIGHT);


	CObjMgr::Get_Instance()->Add_Object(m_RHand);
	CObjMgr::Get_Instance()->Add_Object(m_LHand);

	m_tEFFrame.iStart = 0;
	m_tEFFrame.iEnd =11;
	m_tEFFrame.dwSpeed = .1f;
	m_tEFFrame.dwTime = 0.f;
	m_tEFFrame.vSize = { 120,120 };
}

int CBoss::Update()
{
	if (m_bDead)
	{
		m_pFrameKey = L"BossDie";
		statebar->Set_Dead(true);
		return OBJ_DEAD;
	}
	float dt = CTimeMgr::Get_Instance()->GetDeltaTime();

	

	if (m_hitFlash == true)
	{
		m_HitTime -= dt;
		if (m_HitTime <= 0.f)
			m_hitFlash = false;
	}

	switch (m_eCurState)
	{
	case BOSSSTATE::IDLE:
		idelTime -= dt;
		if (idelTime <= 0.f)
		{

			Do_Attack();
			idelTime = idelTimeMax;
		}
		break;
	case BOSSSTATE::BULLETATTACK:
		bulletTime -= dt;
		if (bulletTime <= 0.f)
		{
			m_eCurState = IDLE;
			bulletTime = bulletTimeMax;
		}
		else
			BulletAttack();
		break;
	case BOSSSTATE::SWORDATTACK:

		if (m_bSwordDone)
		{
			m_eCurState = IDLE;
			SwordCount = 0;
			m_bSwordDone = false;
		}
		else
			SwordAttack();
		break;
	case BOSSSTATE::HANDATTACK:
		//HandTime -= dt;
		if (/*HandTime <= 0.f*/HandCount >= 4)
		{
			m_eCurState = IDLE;

			//HandTime = HandTimeMax;
			HandCount = 0;
		}
		else
			HandAttack();
		break;
	case BOSSSTATE::DEAD:
		DeadTime -= dt;
		if (DeadTime <= 0.f)
		{
			CCamera::Get_Instance()->Set_Shack(false);
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

void CBoss::Late_Update()
{

}

void CBoss::Render(HDC hdc)
{
	if (m_hitFlash == true)
	{
		if (m_eCurState == IDLE || m_eCurState == SWORDATTACK || m_eCurState == HANDATTACK)
			m_pFrameKey = L"IdleHit";
		else if (m_eCurState == BULLETATTACK)
			m_pFrameKey = L"AttackHit";

	}
	else
	{
		if (m_eCurState == IDLE || m_eCurState == SWORDATTACK || m_eCurState == HANDATTACK)
			m_pFrameKey = L"BossIdle";
		else if (m_eCurState == BULLETATTACK)
			m_pFrameKey = L"BulletAttack";
	}

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


	__super::RenderColl(hdc, m_vPosition);
	//Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	//float zoom = CCamera::Get_Instance()->GetZoom();

	//float RenderSizeX = m_vSize.x * zoom;
	//float RenderSizeY = m_vSize.y * zoom;
	//// 좌상단 기준
	//float LeftTopX = RenderPos.x - RenderSizeX * .5f;
	//float LeftTopY = RenderPos.y - RenderSizeY * .5f;

	//Rectangle(hdc, LeftTopX, LeftTopY, LeftTopX + RenderSizeX, LeftTopY + RenderSizeY);

	__super::EffRender(hdc);

}

void CBoss::Release()
{

}

void CBoss::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
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

void CBoss::BulletAttack()
{
	accTime += CTimeMgr::Get_Instance()->GetDeltaTime();
	if (.15f < accTime)
	{
		m_iAngle += 10.0;
		m_iAngle %= 360;

		float m_fVolume = 20.f;
		CSoundManager::Get_Instance()->PlayFX(L"BelialBullet.wav", SOUND_EFFECT, m_fVolume);

		for (int j = 0; j < m_iBarrelNum; j++)
		{
			m_iAngle = (m_iAngle + (90 * j)) % 360;
			Vector2 dir = RotateVector(m_vBarrelDir, m_iAngle);
			CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonsterBullet>::Create({ m_vPosition.x + 15,m_vPosition.y+90 }, { 20,20 }, dir));

		}
		accTime = 0.f;
	}

}

void CBoss::SwordAttack()
{
	if (SwordCount != SwordCountMax)
	{
		SwordTime -= CTimeMgr::Get_Instance()->GetDeltaTime();

		if (SwordTime <= 0.f)
		{
			float m_fVolume = 20.f;
			CSoundManager::Get_Instance()->PlayFX(L"Belial_sword.wav", SOUND_EFFECT, m_fVolume);

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

void CBoss::HandAttack()
{
	Vector2 pos = CObjMgr::Get_Instance()->Get_Player()->GetPosition();


	if (m_LHand->Get_IsAttack() == false && m_RHand->Get_IsAttack() == false)
	{
		Rand = RandInt(0, 1);

		if (Rand == 0)
		{
			m_LHand->SetAttackPos(pos);
			m_LHand->Set_IsAttack(true);
		}
		else
		{

			m_RHand->SetAttackPos(pos);
			m_RHand->Set_IsAttack(true);
		}
		HandCount++;

	}

	// 다음 손 결정

//m_RHand->SetAttackPos(pos);
//m_RHand->Set_IsAttack(true);
//


}

void CBoss::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_pFrameKey = L"BossIdle";

			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 9;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 210,285 };

			m_vSize = m_tFrame.vSize;
			break;

		case BULLETATTACK:
			m_pFrameKey = L"BulletAttack";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 9;
			m_tFrame.dwSpeed = .4f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 210, 384 };
			m_vSize = m_tFrame.vSize;
			break;

		case SWORDATTACK:
			m_pFrameKey = L"BossIdle";

			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 9;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 210,285 };

			m_vSize = m_tFrame.vSize;

			break;

		case HANDATTACK:
			m_pFrameKey = L"BossIdle";

			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 9;
			m_tFrame.dwSpeed = .2f;
			m_tFrame.dwTime = 0.f;
			m_tFrame.vSize = { 210,285 };

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

void CBoss::Do_Attack()
{


	m_nextIndex = (m_nextIndex + 1) % 4;
	m_eCurState = static_cast<BOSSSTATE>(m_nextIndex);
	//m_eCurState = HANDATTACK;


}

void CBoss::Take_Damage(int _damage)
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

	

}

Vector2 CBoss::RotateVector(Vector2& v, float angle)
{
	float radian = angle * (PI / 180.f);

	float cosX = cosf(radian);
	float sinY = sinf(radian);

	Vector2 result;
	result.x = v.x * cosX - v.y * sinY;
	result.y = v.x * sinY - v.y * cosX;
	return result;
}

void CBoss::DeadEffect()
{
	int k = RandInt(-150, 150);
	int j = RandInt(-150, 150);
	
	for (int i = 0; i < 10; i++)
	{
		m_vEffect.push_back(CEffectComp({ k,j }, this, m_tEFFrame, { 40,40 }, L"BossFinish"));

	}
	if (m_LHand)
	{
	m_LHand->Set_Dead(true);
	m_LHand = nullptr;
	}
	if (m_RHand)
	{
	m_RHand->Set_Dead(true);
	m_RHand = nullptr;
	}

	if(m_vPosition.y <= (528.f + 170.f))
	m_vPosition.y += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	tmp += CTimeMgr::Get_Instance()->GetDeltaTime();

	CCamera::Get_Instance()->Set_Shack(true);


		

}
