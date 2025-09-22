#include "pch.h"
#include "CBossStage.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCamera.h"
#include "CAbstractFactory.h"
#include "CCollisionMgr.h"
#include "CPlatform.h"
#include "CUIMgr.h"
#include "CLineManager.h"
#include "CStateBar.h"
#include "CTileMgr.h"
#include "CBoss.h"
#include "CWall.h"
#include "CKeyMgr.h"

void CBossStage::Initialize()
{

	{
		//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossMap.bmp", L"BossMap");
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create({ WINCX * .5f,800.f}));
		//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonster>::Create());

		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CBoss>::Create());

		CCamera::Get_Instance()->Bootstrap(CObjMgr::Get_Instance()->Get_Player()->GetPosition());
		CCamera::Get_Instance()->SetBackSize({ 1056.f,1056.f });
		CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());


	}
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MapTile.bmp", L"Tile");

	//CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Data();

	PlatformInit();

	CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CStateBar>::CreateUI((CCreature*)CObjMgr::Get_Instance()->Get_Player()));


	float Ystart = WINCY * 0.8f;
	Vector2 tPoint[2] =
	{ {0.f,(Ystart)}, {150.f,Ystart} };
	CLineManager::Get_Instance()->Create_Line(tPoint, 2);

}

int CBossStage::Update()
{
	CTileMgr::Get_Instance()->Update();

	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CCamera::Get_Instance()->Update();

	Vector2 pos = CCamera::Get_Instance()->GetRealPos(CKeyMgr::Get_Instance()->GetMousePos());
	
	return 0;
}

void CBossStage::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	
}

void CBossStage::Render(HDC hdc)
{

	//HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"BossMap");
	//
	//{
	//	SetStretchBltMode(hdc, COLORONCOLOR);
	//			
	//	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos({0,0});
	//	Vector2 brS = CCamera::Get_Instance()->GetRenderPos({ 1380,1180 });
	//
	//	float dstX = RenderPos.x;
	//	float dstY = RenderPos.y;
	//	float dstW = (brS.x - RenderPos.x);
	//	float dstH = (brS.y - RenderPos.y);
	//
	//	// 필요하면 dstW/dstH가 음수면 tl/br 스왑
	//	if (dstW < 0) { dstX += dstW; dstW = -dstW; }
	//	if (dstH < 0) { dstY += dstH; dstH = -dstH; }
	//
	//	StretchBlt(hdc, dstX, dstY, dstW, dstH, hGroundDC, 0, 0, 320, 320, SRCCOPY);
	//}

	CTileMgr::Get_Instance()->Render(hdc);

	CObjMgr::Get_Instance()->Render(hdc);
	CUIMgr::Get_Instance()->Render(hdc);

	//Line 테스트
	CLineManager::Get_Instance()->Render(hdc);
}

void CBossStage::Release()
{
	CTileMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Release();
	CUIMgr::Get_Instance()->Release();
}

void CBossStage::PlatformInit()
{
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ WINCX * .5f, 925.f }, { 1100,25 }));

	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1056.f * .5f, 825.f }, { 380,20 }));

	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1056.f * .5f - 261.f, 680.f }, { 142,20 }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1056.f * .5f + 261.f, 680.f }, { 142,20 }));

	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1056.f * .5f - 312.f, 535.f }, { 142,20 }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1056.f * .5f + 312.f, 535.f }, { 142,20 }));

	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1056.f * .5f - 312.f, 392.f }, { 142,20 }));
	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1056.f * .5f + 312.f, 392.f }, { 142,20 }));


	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ 1056.f * .5f, 297.f }, { 380*.5f,20.f }));

	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CWall>::Create({ 0, 388 }, { 195,670 }));


	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CWall>::Create({ 1056, 388 }, { 195,670 }));


	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CWall>::Create({ 1056 * .5f , 45.f }, { 857,100 }));

}
