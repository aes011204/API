#pragma once
#include "CNonCreature.h"
class CDungeonDoor: public CNonCreature
{
public:
	CDungeonDoor();
	~CDungeonDoor();

public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	// CNonCreature을(를) 통해 상속됨
	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;
};

