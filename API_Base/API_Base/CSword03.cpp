#include "pch.h"
#include "CSword03.h"
#include "CBmpMgr.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CSword03::CSword03()
{

}

CSword03::~CSword03()
{

}

void CSword03::Initialize()
{
	strName = L"³°Àº ´Ü°Ë";
	itemType = SUBWEAPON;
	m_eItemState = UNEQUIP;
	m_eItemClass = BEGGINER;
	m_eWeaponType = SWORD;
	m_iDefense = 0;
	m_AttackCountSec = 10.f;
	m_iDamage = 10;

	m_iMoney = 50;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/LightSaberBMP.bmp", L"LightSaber");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/ShortSword001Icon.bmp", L"ShortSword001Icon");
	m_pFrameKey = L"LightSaber";
	m_vSize = { 0,0 };

	m_iconImgSize = { 15,16 };
	m_pIconKey = L"ShortSword001Icon";
	CWeapon::Initialize();

	radian = PI;
	m_OnUp = false;

	m_eWeaponType = CWeapon::SWORD;
}

int CSword03::Update()
{
	CSword::Update();

	return 0;
}

void CSword03::Late_Update()
{
	CSword::Late_Update();
}

void CSword03::Render(HDC hdc)
{
	CSword::Render(hdc);

}

void CSword03::Release()
{
}
