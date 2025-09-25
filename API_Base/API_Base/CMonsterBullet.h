#pragma once
#include "CBullet.h"
class CMonsterBullet :
    public CBullet
{
public:


	CMonsterBullet();
	~CMonsterBullet() override;

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:

	virtual void Do_Attack() {}
	virtual void Take_Damage(float _fDamage) {}

	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;
	void Take_Damage(int _damage) override;
	void Motion_Change();

	
};

