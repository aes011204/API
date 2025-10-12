#include "pch.h"
#include "CSword02.h"
#include "CBmpMgr.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CSword02::CSword02()
{

}

CSword02::~CSword02()
{

}

void CSword02::Initialize()
{
	strName = L"양손 무기";
	itemType = TWOHAND;
	m_eItemState = UNEQUIP;
	m_eItemClass = BEGGINER;
	m_eWeaponType = SWORD;
	m_iDefense = 0;
	m_AttackCountSec = 10.f;
	m_iDamage = 10;

	m_iMoney = 200;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/LightSaberBMP.bmp", L"LightSaber");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/LightSaberIcon.bmp", L"LightSaberIcon");
	m_pFrameKey = L"LightSaber";
	m_vSize = { 168.f,168.f };

	m_iconImgSize = { 12,84 };
	m_pIconKey = L"LightSaberIcon";
	CWeapon::Initialize();

	radian = PI;
	m_OnUp = false;

	m_eWeaponType = CWeapon::SWORD;
}

int CSword02::Update()
{
	CSword::Update();

	return 0;
}

void CSword02::Late_Update()
{
	CSword::Late_Update();
}

void CSword02::Render(HDC hdc)
{
	CSword::Render(hdc);

}

void CSword02::Release()
{
}
