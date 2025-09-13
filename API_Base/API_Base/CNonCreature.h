#pragma once
#include "CObj.h"

class CNonCreature : public CObj
{
public:
	CNonCreature();
	virtual ~CNonCreature();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	virtual void On_Collision(CObj* obj) = 0;
public:
	NONCREATURE_ID Get_ID() { return m_ID; }
	void Set_ID(NONCREATURE_ID id) { m_ID = id; }

protected:
	NONCREATURE_ID m_ID;

};

