#pragma once
#include "CNonCreature.h"
class CPlatform :
    public CNonCreature
{
public:
	CPlatform();
	CPlatform(Vector2 pos, Vector2 size) : CNonCreature(pos, size) {}
	virtual ~CPlatform();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	void On_Collision(CObj* obj, vector<CColliderComp>::iterator my, vector<CColliderComp>::iterator other);
	virtual void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other);
	//void On_Collision(CObj* obj, ColliderType my, ColliderType other);

	

};

