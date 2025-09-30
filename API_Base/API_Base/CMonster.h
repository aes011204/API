#pragma once
#include "CCreature.h"
class CMonster :
    public CCreature
{
public:
public:
	CMonster();
	CMonster(Vector2 pos, Vector2 size) : CCreature(pos, size) {}

	virtual ~CMonster();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	void Take_Damage(int _damage) override;

	virtual void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other);
};

