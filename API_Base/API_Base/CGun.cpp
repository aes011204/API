#include "pch.h"
#include "CGun.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayerBullet.h"

CGun::CGun()
{
}

CGun::~CGun()
{
}

void CGun::Initialize()
{
	CWeapon::Initialize();


	strName = "GUN01";
	itemType = TWOHAND;
	m_eItemState = UNEQUIP;
	m_eItemClass = BEGGINER;
	m_eWeaponType = GUN;
	m_iDefense = 0;
	m_AttackCountSec = 10.f;
	m_iDamage = 10;

	iCost = 100;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BambooSwordBMP.bmp", L"BambooSword");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BambooSwordIcon.bmp", L"BambooSwordIcon");
	m_pFrameKey = L"BambooSword";
	m_vSize = { 120.f, 120.f };


	m_iconImgSize = { 15,60 };
	m_pIconKey = L"BambooSwordIcon";

	CWeapon::Initialize();
	m_Length = 70.f;

}

int CGun::Update()
{
	m_vPosition = m_tTarget->GetBarrelPos();

	Vector2 mouse = CKeyMgr::Get_Instance()->GetMousePos();
	Vector2 worldmouse = CCamera::Get_Instance()->GetRealPos(mouse);

	m_vDirection = Vector2::Nomalize(worldmouse - m_vPosition);


	angle = atan2f(m_vDirection.y, m_vDirection.x) + PI / 2.f ;

	Vector2 endBarrel = m_vDirection * m_Length;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayerBullet>::Create((endBarrel+m_vPosition), {16,3}, m_vDirection));

	}

	CWeapon::Update();
	return 0;
}

void CGun::Late_Update()
{
	CWeapon::Late_Update();

}

void CGun::Render(HDC hdc)
{
	CWeapon::Render(hdc);

}

void CGun::Release()
{
	CWeapon::Release();

}
