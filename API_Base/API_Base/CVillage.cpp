#include "pch.h"
#include "CVillage.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CCamera.h"
#include "CBmpMgr.h"
#include "CMonster.h"
#include "CKeyMgr.h"
#include "CLineManager.h"
#include "CUIMgr.h"
#include "CStateBar.h"
#include "CSceneMgr.h"
#include "CSoundManager.h"
#include "CDungeonDoor.h"
#include "CNpc.h"
#include "CShop.h"
#include "CStat.h"
#include "CSmith.h"
#include "CInventoryUI.h"
#include "Mouse.h"



CVillage::CVillage() : m_SoundTime(0.f)
{
}

CVillage::~CVillage()
{
	Release();
}

void CVillage::Initialize()
{
	m_vSceneSize = { 2038.f * 3, 295.f * 3  };
	//CCamera::Get_Instance()->SetViewport({ 960.f, 540.f });
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Village/Cloud.bmp", L"VillageCloud");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Village/TownBG_Day.bmp", L"VillageBG1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Village/TownLayer_Day.bmp", L"VillageBG2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Village/Village.bmp", L"Village");

	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create());
	//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonster>::Create());
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CDungeonDoor>::Create());
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CStat>::Create());
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CSmith>::Create());
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CShop>::Create());
	//
	CCamera::Get_Instance()->Bootstrap(CObjMgr::Get_Instance()->Get_Player()->GetPosition());
	CCamera::Get_Instance()->SetBackSize(m_vSceneSize);
	CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());

	
	//CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CStateBar>::CreateUI(dynamic_cast<CCreature*>(CObjMgr::Get_Instance()->Get_Player())));
	//CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CInventoryUI>::CreateUI(dynamic_cast<CCreature*>(CObjMgr::Get_Instance()->Get_Player())));

	//Line 테스트
	float Ystart = m_vSceneSize.y -29.f;

	Vector2 tPoint[2] =
	{ {-30.f,Ystart},{ (2038.f * 3)+30,Ystart} };
	CLineManager::Get_Instance()->Create_Line(tPoint, 2);


//	Vector2 tPoint1[2] =
//	{ {-30.f,Ystart - 30.f},{ (295.f * 3) + 30.f,Ystart - 30.f} };
//	CLineManager::Get_Instance()->Create_Line(tPoint1, 2);


	Vector2 tPoint2[5] =
	{ {-30.f,Ystart - 370.f},{32.f,Ystart - 430.f} ,{ 1260.f,Ystart - 430.f },{ 1640.f ,Ystart - 50.f},{1690.f ,Ystart - 50.f} };
	CLineManager::Get_Instance()->Create_Line(tPoint2, 5);

	
	Vector2 tPoint4[6] =
	{ { 1923.f,Ystart - 50.f},{2018.f,Ystart - 50.f} ,{ 2305.f,Ystart - 337.f },{ 3600.f ,Ystart - 337.f},{3888.f ,Ystart - 50.f},{3984.f ,Ystart - 50.f} };
	CLineManager::Get_Instance()->Create_Line(tPoint4, 6);

	Vector2 tPoint5[5] =
	{ {4278.f,Ystart - 45.f},{ 4324.f,Ystart - 45.f },{4710.f,Ystart - 430.f} ,{ 5931.f ,Ystart - 430.f},{6153.f ,Ystart - 230.f} };
	CLineManager::Get_Instance()->Create_Line(tPoint5, 5);

	float m_fVolume = 20.f;
	CSoundManager::Get_Instance()->PlayBGM(L"BGM_Town.wav", m_fVolume);

	m_SoundTime = 1.5f;

	Mouse::Get_Instance()->SetIsShoot(1);

}

int CVillage::Update()
{
	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CCamera::Get_Instance()->Update();

	Vector2 tmp = CCamera::Get_Instance()->GetRealPos(CKeyMgr::Get_Instance()->GetMousePos());
	

	{
		// 테스트 용
	
		if (GetAsyncKeyState('3'))//CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
		{
			CSceneMgr::Get_Instance()->Change_Stage(SC_BOSS);
			return 0;
		}
	}
	// 테스트
	//if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	//{
	//	float m_fVolume = 20.f;

	//	CSoundManager::Get_Instance()->PlaySound(L"DungeonEat2.wav", SOUND_EAT2, m_fVolume);
	//	
	//	CSoundManager::Get_Instance()->PlaySound(L"DungeonEat.wav", SOUND_EAT1,m_fVolume);

	//	Vector2  lookat = CCamera::Get_Instance()->GetRealPos( CKeyMgr::Get_Instance()->GetMousePos());
	//	CCamera::Get_Instance()->SetLookAt(lookat); 
	//}

	return 0;
}

void CVillage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();

}

void CVillage::Render(HDC hdc)
{

	{
		// 원래 거
		//Vector2 bgWorldPos = { 0,0 };
		//Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(bgWorldPos);
		//BitBlt(hdc, RenderPos.x, RenderPos.y, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
	}
	{
		HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"VillageCloud");
		BitBlt(hdc, 0, 0, 960, 540, hGroundDC, 0, 0, SRCCOPY);
	}
	{
		HDC	hGroundDC2 = CBmpMgr::Get_Instance()->Find_Img(L"VillageBG1");
		Vector2 size = { 320 * 3, 142 * 3 };
		Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(size);

		Vector2 RenderPos1 = CCamera::Get_Instance()->GetRenderPos({size.x*.5f, m_vSceneSize.y-(size.y*.5f)});
		GdiTransparentBlt(hdc, RenderPos1.x - size.x * .5f, RenderPos1.y- size.y*.5f, size.x, size.y, hGroundDC2, 0, 0, 320, 142, RGB(255, 0, 255));
		//GdiTransparentBlt(hdc, RenderPos1.x+size.x, RenderPos1.y+size.y, size.x, size.y, hGroundDC2, 0, 0, 320, 142, RGB(255, 0, 255));

	}
	
	HDC	hGroundDC1 = CBmpMgr::Get_Instance()->Find_Img(L"Village");
	Vector2 VillSize = { 2038.f, 300.f };
	Vector2 VillReSize = { 2038.f*3, 300.f*3 };
	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos({ VillReSize.x * .5f , VillReSize.y * .5f  });
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(VillReSize);
	
	//BitBlt(hdc, 0, 600 - 300 , 2038, 600, hGroundDC1, 0, 0, SRCCOPY);
	GdiTransparentBlt(hdc, 
		(RenderPos.x - RenderSize.x*.5f),(RenderPos.y - RenderSize.y * .5f),
		RenderSize.x, RenderSize.y, hGroundDC1, 0, 0, VillSize.x, VillSize.y, RGB(255,255,255));
	
	
	//{
	//	RenderBG(hdc, hGroundDC, { 0,0 }, { 960, 540 });
	//}

	CObjMgr::Get_Instance()->Render(hdc);

	//Line 테스트
	CLineManager::Get_Instance()->Render(hdc);
	CUIMgr::Get_Instance()->Render(hdc);


}

void CVillage::Release()
{
	CObjMgr::Get_Instance()->Release();
	//CUIMgr::Get_Instance()->Release();
	CLineManager::Get_Instance()->Release();
	CSoundManager::Get_Instance()->StopAll();



}
