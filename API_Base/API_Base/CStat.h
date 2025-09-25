#pragma once
#include "CNpc.h"
class CStat :
    public CNpc
{
public:
	CStat();
	~CStat();

public:
	void Initialize()override;
	int Update()override;
	void Late_Update()override;
	void Render(HDC hdc)override;
	void Release()override;


	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;
};

