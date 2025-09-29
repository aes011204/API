#pragma once
#include "CItem.h"
#include "CPlayer.h"

class CWeapon : public CItem
{
public:

	enum WEAPONTYPE { SWORD, GUN, WT_END };
public:
	CWeapon();
	//CWeapon(CWeapon& rhs): CWeapon();

	~CWeapon();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();
public:
	void ItemInfo();

	//static CItem* CreateWeapon(LEVEL _level);

	CPlayer* Get_Target() const { return m_tTarget; }
	void Set_Target(CPlayer* pTarget) { m_tTarget = pTarget; }

	
protected:
	WEAPONTYPE m_eWeaponType = WT_END;
	CPlayer* m_tTarget = nullptr;


	Vector2 RealCorners[4];
	Vector2 half;
	Vector2 corners[4];
	POINT plgCorner[3];

	float angle=0.f;


	// CItem을(를) 통해 상속됨
	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;

};

