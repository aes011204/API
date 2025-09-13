#pragma once
#include "CObj.h"
#include "Define.h"
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

	void Move_Frame();

	virtual void On_Collision(CObj* obj) = 0;

public:
	CREATURE_ID Get_ID() { return m_ID; }
	void Set_ID(CREATURE_ID id) { m_ID = id; }
	bool Get_Dead() { return m_bDead; }

	void			Set_FrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	void			Set_Direction(DIRECTION eDir) { m_eDir = eDir; }




protected:
	CREATURE_ID m_ID;

	Vector2 m_vBarrelDir;

	CObj* m_tTarget;

	bool m_bDead;

	FRAME		m_tFrame;

	DIRECTION	m_eDir;
	const TCHAR* m_pFrameKey;
};

