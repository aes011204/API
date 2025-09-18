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

CVillage::CVillage()
{
}

CVillage::~CVillage()
{
	Release();
}

void CVillage::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonster>::Create());
	
	CCamera::Get_Instance()->Bootstrap(CObjMgr::Get_Instance()->Get_Player()->GetPosition());
	CCamera::Get_Instance()->SetBackSize({ 1920.f, 1280.f });
	CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());

	
	CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CStateBar>::CreateUI(dynamic_cast<CCreature*>(CObjMgr::Get_Instance()->Get_Player())));

	//Line 테스트
	float Ystart = WINCY * 0.8f;
	Vector2 tPoint[2] =
	{ {0.f,(Ystart)}, {150.f,Ystart} };
	CLineManager::Get_Instance()->Create_Line(tPoint, 2);
	Vector2 tPoint2[6] =
	{ {350.f,Ystart},{500.f,Ystart},{700.f,Ystart - 200.f},{1000.f,Ystart - 200.f} ,{ 1000.f ,Ystart },{3000.f ,Ystart} };
	CLineManager::Get_Instance()->Create_Line(tPoint2, 6);

	Vector2 tPoint3[2] =
	{ {400.f,Ystart - 200.f}, {600.f,Ystart - 200.f} };
	CLineManager::Get_Instance()->Create_Line(tPoint3, 2);
}

int CVillage::Update()
{
	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CCamera::Get_Instance()->Update();


	{
		// 테스트 용
		CUIMgr::Get_Instance()->Update();
		if (GetAsyncKeyState('3'))//CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
		{
			CSceneMgr::Get_Instance()->Change_Stage(SC_BOSS);
			return 0;
		}
	}
	// 테스트
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
	
		Vector2  lookat = CCamera::Get_Instance()->GetRealPos( CKeyMgr::Get_Instance()->GetMousePos());
		CCamera::Get_Instance()->SetLookAt(lookat); 
	}

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

	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
	{
		RenderBG(hdc, hGroundDC, { 0,0 }, { 1920, 1280 });
	}

	CObjMgr::Get_Instance()->Render(hdc);

	//Line 테스트
	CLineManager::Get_Instance()->Render(hdc);
	CUIMgr::Get_Instance()->Render(hdc);


}

void CVillage::Release()
{
	CObjMgr::Get_Instance()->Release();
	CUIMgr::Get_Instance()->Release();
	CLineManager::Get_Instance()->Release();


}
