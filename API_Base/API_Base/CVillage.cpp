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

CVillage::CVillage()
{
}

CVillage::~CVillage()
{
}

void CVillage::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMonster>::Create());
	
	CCamera::Get_Instance()->Bootstrap({WINCX*.5f, WINCY*.5f});
	//CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());


	//Line 테스트
	Vector2 tPoint[2] =
	{ {0.f,(500.f)}, {150.f,500.f} };
	CLineManager::Get_Instance()->Create_Line(tPoint, 2);
}

int CVillage::Update()
{
	CObjMgr::Get_Instance()->Update();
	CCamera::Get_Instance()->Update();

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
}

void CVillage::Render(HDC hdc)
{

	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
	{
		// 원래 거
		//Vector2 bgWorldPos = { 0,0 };
		//Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(bgWorldPos);
		//BitBlt(hdc, RenderPos.x, RenderPos.y, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
	}


	{
		// gpt의 도움...
		Vector2 tlS = CCamera::Get_Instance()->GetRenderPos({ 0.f,    0.f });
		Vector2 brS = CCamera::Get_Instance()->GetRenderPos({ 1920.f, 1280.f });
		
		int dstX = (int)tlS.x;
		int dstY = (int)tlS.y;
		int dstW = (int)(brS.x - tlS.x);
		int dstH = (int)(brS.y - tlS.y);
		
		// 필요하면 dstW/dstH가 음수면 tl/br 스왑
		if (dstW < 0) { dstX += dstW; dstW = -dstW; }
		if (dstH < 0) { dstY += dstH; dstH = -dstH; }
		
		StretchBlt(hdc, dstX, dstY, dstW, dstH, hGroundDC, 0, 0, 1920, 1280, SRCCOPY);
	}
	CObjMgr::Get_Instance()->Render(hdc);

	//Line 테스트
	CLineManager::Get_Instance()->Render(hdc);


}

void CVillage::Release()
{
	CObjMgr::Get_Instance()->Release();
}
