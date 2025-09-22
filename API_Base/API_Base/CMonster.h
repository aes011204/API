#pragma once
#include "CCreature.h"
class CMonster :
    public CCreature
{
public:
public:
	CMonster();
	virtual ~CMonster();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

 
	
	//void On_Collision(CObj* obj, vector<CColliderComp>& myCollider, vector<CColliderComp>& otherCollider);
	//void On_Collision(CObj* obj, ColliderType my, ColliderType other);
	//void On_Collision(CObj* obj, vector<CColliderComp>::iterator my, vector<CColliderComp>::iterator other);
	// CCreature을(를) 통해 상속됨
	void Take_Damage(int _damage) override;

	virtual void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other);
};

