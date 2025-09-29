#include "pch.h"
#include "CSword01.h"
#include "CBmpMgr.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
CSword01::CSword01()
{

}

CSword01::~CSword01()
{

}

void CSword01::Initialize()
{

	strName;
	itemType = ONEHAND;
	 m_eItemState = UNEQUIP;
	m_eItemClass = BEGGINER;
	m_eWeaponType = SWORD;
	m_iDefense = 0;
	m_AttackCountSec = 10.f;
	m_iDamage = 10;

	iCost = 100;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BasicShortSwordBMP.bmp", L"BasicShortSword");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BasicShortSwordIcon.bmp", L"BasicShortSwordIcon");
	m_pFrameKey = L"BasicShortSword";
	m_vSize = { 96.f, 96.f };
	
	m_iconImgSize = {19,48};
	m_pIconKey = L"BasicShortSwordIcon";
	CWeapon::Initialize();
	radian = PI;
	m_OnUp = false;
}

int CSword01::Update()
{
 
	CSword::Update();

    return 0;
}

void CSword01::Late_Update()
{
	CSword::Late_Update();

}

void CSword01::Render(HDC hdc)
{
	CSword::Render(hdc);


}

void CSword01::Release()
{
}
