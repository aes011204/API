#pragma once
#include "CObj.h"

class CCreature :
    public CObj
{
public:
	CCreature();
	virtual ~CCreature();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	virtual void On_Collision(CObj* obj) = 0;

public:
	CREATURE_ID Get_ID() { return m_ID; }
	void Set_ID(CREATURE_ID id) { m_ID = id; }
	bool Get_Dead() { return m_bDead; }

protected:
	CREATURE_ID m_ID;

	Vector2 m_vBarrelDir;

	CObj* m_tTarget;

	bool m_bDead;
};

