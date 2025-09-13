#include "pch.h"
#include "CVillage.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CCamera.h"
#include "CBmpMgr.h"
#include "CMonster.h"
#include "CKeyMgr.h"

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
	//CCamera::Get_Instance()->SetLookAt({ WINCX * .5, WINCY * .5f });
	//CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());
	CCamera::Get_Instance()->Bootstrap({WINCX*.5f, WINCY*.5f});

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
	Vector2 bgWorldPos = { 0,0 };
	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(bgWorldPos);

	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
	BitBlt(hdc, RenderPos.x, RenderPos.y, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hdc);

}

void CVillage::Release()
{
	CObjMgr::Get_Instance()->Release();
}
