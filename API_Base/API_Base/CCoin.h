#pragma once
#include "CItem.h"
class CCoin :
    public CItem
{
public:
	CCoin();
	virtual ~CCoin();
public:
	 void Initialize();
	 int Update();
	 void Late_Update();
	 void Render(HDC hdc);
	 void Release();

	 bool m_move = true;

	 // CItem을(를) 통해 상속됨
	 void ItemInfo() override;
	 void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other);
};

