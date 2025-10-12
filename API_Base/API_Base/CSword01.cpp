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

	
	strName = L"ÈçÇÑ ¼ô¼Òµå";
	itemType = ONEHAND;
	 m_eItemState = UNEQUIP;
	m_eItemClass = BEGGINER;
	m_eWeaponType = SWORD;
	m_iDefense = 0;
	m_AttackCountSec = 10.f;
	m_iDamage = 10;

	m_iMoney = 100;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BasicShortSwordBMP.bmp", L"BasicShortSword");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/BasicShortSwordIcon.bmp", L"BasicShortSwordIcon");
	m_pFrameKey = L"BasicShortSword";
	m_vSize = { 96.f, 96.f };
	
	m_iconImgSize = {19,48};
	m_pIconKey = L"BasicShortSwordIcon";
	CWeapon::Initialize();
	radian = PI;
	m_OnUp = false;

	m_eWeaponType = CWeapon::SWORD;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_15.bmp", L"sprite_15");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_14.bmp", L"sprite_14");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_13.bmp", L"sprite_13");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_12.bmp", L"sprite_12");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_11.bmp", L"sprite_11");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_10.bmp", L"sprite_10");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_09.bmp", L"sprite_09");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_08.bmp", L"sprite_08");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_07.bmp", L"sprite_07");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_06.bmp", L"sprite_06");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_05.bmp", L"sprite_05");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_04.bmp", L"sprite_04");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_03.bmp", L"sprite_03");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_02.bmp", L"sprite_02");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_01.bmp", L"sprite_01");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/sprite_00.bmp", L"sprite_00");

	m_tEFFrame.iStart = 0;
	m_tEFFrame.iEnd = 2;
	m_tEFFrame.dwSpeed = .13f;
	m_tEFFrame.dwTime = 0.f;
	m_tEFFrame.vSize = { 130,120 };

}

int CSword01::Update()
{
	CSword::Update();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		float base = atan2f(m_vDirection.y, m_vDirection.x) + PI / 2.f + PI / 2.f;
		float degree = base * (180 / PI);
		Vector2 offset = (m_tTarget->GetBarrelPos()) - (m_tTarget->GetPosition());

		if(degree>=90&& degree < 112.5)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_15"));

		if (degree >= 112.5 && degree < 135)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_14"));
		
		if (degree >= 135 && degree < 157.5)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_13"));
		
		if (degree >= 157.5 && degree < 180)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_12"));
		
		if (degree >= 180 && degree < 202.5)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_11"));
		if (degree >= 202.5 && degree < 225)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_10"));
		if (degree >= 225 && degree < 247.5)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_09"));
		if (degree >= 247.5 && degree < 270)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_08"));
		if (degree >= 270 && degree < 292.5)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_07"));
		if (degree >= 292.5 && degree < 315)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_06"));
		if (degree >= 315 && degree < 337.5)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_05"));
		if (degree >= 337.5 && degree < 360)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_04"));
		if (degree >= 0 && degree < 22.5)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_03"));
		if (degree >= 22.5 && degree < 45)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_02"));
		if (degree >= 45 && degree < 67.5)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_01"));
		if (degree >= 67.5 && degree < 90)
			m_vEffect.push_back(CEffectComp(offset, this, m_tEFFrame, { m_tEFFrame.vSize.x,m_tEFFrame.vSize.y }, L"sprite_00"));

	
	}

	__super::EffUpdate();

    return 0;
}

void CSword01::Late_Update()
{
	CSword::Late_Update();

}

void CSword01::Render(HDC hdc)
{
	CSword::Render(hdc);

	__super::EffRender(hdc);

}

void CSword01::Release()
{
}
