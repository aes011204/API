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

void CBossStage::Initialize()
{


	{
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossMap.bmp", L"BossMap");
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create());
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonster>::Create());

		CCamera::Get_Instance()->Bootstrap(CObjMgr::Get_Instance()->Get_Player()->GetPosition());
		CCamera::Get_Instance()->SetBackSize({ 1380.f,1180.f });
		CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());
		

	}
		CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CStateBar>::CreateUI((CCreature*)CObjMgr::Get_Instance()->Get_Player()));

	CObjMgr::Get_Instance()
		->Add_Object(CAbstractFactory<CPlatform>::Create({ WINCX*.5f, WINCY*.9f }, { 1000, 20 }));

	float Ystart = WINCY * 0.8f;
	Vector2 tPoint[2] =
	{ {0.f,(Ystart)}, {150.f,Ystart} };
	CLineManager::Get_Instance()->Create_Line(tPoint, 2);
}

int CBossStage::Update()
{
	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CCamera::Get_Instance()->Update();


	return 0;
}

void CBossStage::Late_Update()
{
	CUIMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	
}

void CBossStage::Render(HDC hdc)
{

	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"BossMap");
	

	//StretchBlt(hdc, 0, 0, 2000.f, 2000.f, hGroundDC, 0, 0, 300, 300, SRCCOPY);
	//HDC hMemDC = CreateCompatibleDC(hdc);
	//HBITMAP hBitmap = CreateBitmap(2000.f, 2000.f, 1, 24, NULL); // 300x300, 32비트
	//HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDC, hBitmap);
	//StretchBlt(hdc, 0, 0, 2000.f, 2000.f, hGroundDC, 0, 0, 300, 300, SRCCOPY);
	////BitBlt(hdc, 0, 0, 1000.f, 1000.f, hGroundDC, 0, 0, SRCCOPY);
	//
	//RenderBG(hdc, hGroundDC, { 0.f,0.f }, { 2000.f, 2000.f });
	//
	//SelectObject(hMemDC, hOldBmp);
	//DeleteObject(hBitmap);
	//DeleteDC(hMemDC);
	{
		SetStretchBltMode(hdc, COLORONCOLOR);
				
		Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos({0,0});
		Vector2 brS = CCamera::Get_Instance()->GetRenderPos({ 1380,1180 });

		float dstX = RenderPos.x;
		float dstY = RenderPos.y;
		float dstW = (brS.x - RenderPos.x);
		float dstH = (brS.y - RenderPos.y);

		// 필요하면 dstW/dstH가 음수면 tl/br 스왑
		if (dstW < 0) { dstX += dstW; dstW = -dstW; }
		if (dstH < 0) { dstY += dstH; dstH = -dstH; }

		StretchBlt(hdc, dstX, dstY, dstW, dstH, hGroundDC, 0, 0, 320, 320, SRCCOPY);
	}


	CObjMgr::Get_Instance()->Render(hdc);
	CUIMgr::Get_Instance()->Render(hdc);

	//Line 테스트
	CLineManager::Get_Instance()->Render(hdc);
}

void CBossStage::Release()
{
	CObjMgr::Get_Instance()->Release();
	CUIMgr::Get_Instance()->Release();
}
