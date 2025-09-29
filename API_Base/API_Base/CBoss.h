#pragma once
#include "CMonster.h"
#include "CBossHand.h"
class CUI;
class CBoss :
	public CCreature
{
public:
	enum BOSSSTATE { IDLE = 0, BULLETATTACK, SWORDATTACK, HANDATTACK, DEMAGE, DEAD, ST_END };
public:
	CBoss();
	virtual ~CBoss();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();


	virtual void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other);

	void BulletAttack();
	void SwordAttack();
	void HandAttack();

	void Motion_Change();
	void Do_Attack();


	void Take_Damage(int damage);

	Vector2 RotateVector(Vector2& v, float angle);
	void DeadEffect();

private:

	BOSSSTATE	m_eCurState;
	BOSSSTATE	m_ePreState;
	int m_nextIndex = 0;

	bool m_hitFlash;

	float m_HitTime = 0.f;
	float m_HitTimeMax = 0.f;

	float accTime = 0.f;

	float idelTime = 0.f;
	float idelTimeMax = 0.f;

	float bulletTime = 0.f;
	float bulletTimeMax = 0.f;

	float HandTime = 0.f;
	float HandTimeMax = 0.f;

	int HandCount = 0;

	float SwordTime = 0.f;
	float SwordTimeMax = 0.f;
	int SwordCount = 0;
	int SwordCountMax;
	bool m_bSwordDone;
	vector<CObj*>* m_TmpSword;

	int m_iAngle;
	int m_iBarrelNum;
	int Rand = 0;

	float DeadTime = 0.f;
	float DeadTimeMax = 0.f;

	Vector2 LeftHandPos;
	Vector2 RightHandPos;

	CBossHand* m_RHand;
	CBossHand* m_LHand;

	CUI* statebar;

	FRAME m_tEFFrame;

};

