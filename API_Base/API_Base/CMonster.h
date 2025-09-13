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

    // CNonCreature을(를) 통해 상속됨
    void On_Collision(CObj* obj) override;
};

