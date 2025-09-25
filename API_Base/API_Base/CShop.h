#pragma once
#include "CNpc.h"
class CShop :
    public CNpc
{
public:
	CShop();
	~CShop();

public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();


	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;
};

