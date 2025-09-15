#pragma once
#include "CCreature.h"
class CPlayer :
    public CCreature
{
public:
	enum PLAYERSTATE { IDLE, WALK, JUMP, ATTACK, HIT, DEAD, PS_END };

public:
	CPlayer();
	virtual ~CPlayer();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	virtual void On_Collision(CObj* obj);

	void Key_Input();
	void Motion_Change();

private:

	PLAYERSTATE	m_eCurState;
	PLAYERSTATE	m_ePreState;
	
};

