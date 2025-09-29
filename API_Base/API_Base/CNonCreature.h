#pragma once
#include "CObj.h"

class CNonCreature : public CObj
{
public:
	CNonCreature();
	CNonCreature(Vector2 pos, Vector2 size) : CObj(pos, size) {}

	virtual ~CNonCreature();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	//virtual void On_Collision(CObj* obj, ColliderType my, ColliderType other) = 0;
	//virtual void On_Collision(CObj* obj, vector<CColliderComp>::iterator my, vector<CColliderComp>::iterator other) = 0;
	virtual void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) = 0;

protected:


};

