#pragma once
#include "CNonCreature.h"
class CNpc : public CNonCreature
{
public:
	CNpc();
	~CNpc();

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hdc) override; 
	void Release() override;

	// CNonCreature을(를) 통해 상속됨
	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;
protected:
	bool m_OnPlayer;
};

