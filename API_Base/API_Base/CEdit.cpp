#include "pch.h"
#include "CEdit.h"
#include "CBmpMgr.h"
#include "CTileMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"

void CEdit::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MapTile.bmp", L"Tile");
	CTileMgr::Get_Instance()->Initialize();
	CCamera::Get_Instance()->Bootstrap({ WINCX * .5f, WINCY * .5f });
	CCamera::Get_Instance()->SetBackSize({ 1920.f, 1280.f });

}

int CEdit::Update()
{
	CTileMgr::Get_Instance()->Update();
	CCamera::Get_Instance()->Update();

	return 0;
}

void CEdit::Late_Update()
{
	Key_Input();
	CTileMgr::Get_Instance()->Late_Update();

}

void CEdit::Render(HDC hdc)
{

	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
	{
		RenderBG(hdc, hGroundDC, { 0,0 }, { 1920, 1280 });
	}

	CTileMgr::Get_Instance()->Render(hdc);
}


void CEdit::Release()
{
	CTileMgr::Get_Instance()->Release();
}

void CEdit::Key_Input()
{
	Vector2 lookat = CCamera::Get_Instance()->GetLookAt();


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CCamera::Get_Instance()->SetLookAt({ (lookat.x) - 20.f ,lookat.y });

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CCamera::Get_Instance()->SetLookAt({ (lookat.x) +20.f ,lookat.y  });

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CCamera::Get_Instance()->SetLookAt({ (lookat.x)  ,lookat.y - 20.f });

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CCamera::Get_Instance()->SetLookAt({ (lookat.x)  ,lookat.y + 20.f });


	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		POINT	pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		//pt.x -= (int)ScrollMgr::Get_Instance()->Get_ScrollX();
		//pt.y -= (int)ScrollMgr::Get_Instance()->Get_ScrollY();
		
		CTileMgr::Get_Instance()->Picking(pt, {1,1}, 1);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		CTileMgr::Get_Instance()->Save_Data();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		CTileMgr::Get_Instance()->Load_Data();
	}

}