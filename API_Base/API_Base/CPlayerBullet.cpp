#include "pch.h"
#include "CPlayerBullet.h"

CPlayerBullet::CPlayerBullet()
{
}

CPlayerBullet::~CPlayerBullet()
{
}

void CPlayerBullet::Initialize()
{
	CBullet::Initialize();
}

int CPlayerBullet::Update()
{
	CBullet::Update();
	return 0;
}

void CPlayerBullet::Late_Update()
{
	CBullet::Late_Update();

}

void CPlayerBullet::Render(HDC hDC)
{
	CBullet::Render(hDC);

}

void CPlayerBullet::Release()
{
	CBullet::Release();

}

void CPlayerBullet::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	if (obj->Get_ID() == PLAYER)
		return;

	CBullet::On_Collision(obj,my,other);
}

void CPlayerBullet::Take_Damage(int _damage)
{
}
