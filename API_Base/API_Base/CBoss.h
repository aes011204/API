#pragma once
#include "CMonster.h"
class CBoss :
    public CCreature
{
public:
	enum BOSSSTATE { IDLE=0, BULLETATTACK, SWORDATTACK, HANDATTACK , DEMAGE, DEAD, ST_END };
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

private:

	BOSSSTATE	m_eCurState;
	BOSSSTATE	m_ePreState;
	//BOSSSTATE m_pattern = BOSSSTATE::IDLE;
	float accTime = 0.f;
	float idelTime = 0.f;
};

