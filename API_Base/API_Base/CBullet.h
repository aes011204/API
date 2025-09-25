#pragma once
#include "CCreature.h"
class CBullet: public CCreature
{
public:

	enum BULLETSTATE {IDLE,DEAD,BS_END};
	CBullet();
	
	virtual ~CBullet() override;

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	BULLETSTATE Get_CurState() { return m_eCurState; }
public:

	virtual void Do_Attack() {}
	virtual void Take_Damage(float _fDamage) {}

	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;
	void Take_Damage(int _damage) override;

	BULLETSTATE m_ePreState;
	BULLETSTATE m_eCurState;
	
	// 플레이어가 주는 데미지를 받는 함수
};

