#pragma once
#include "CNonCreature.h"
class CDoor :
    public CNonCreature
{
public:
	CDoor();
	CDoor(Vector2 pos, Vector2 size) :CNonCreature(pos, size), m_OnPlayer(false) {}
	~CDoor();

public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	// CNonCreature을(를) 통해 상속됨
	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;
protected:
	bool m_OnPlayer;
};

