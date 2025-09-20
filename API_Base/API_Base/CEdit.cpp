#include "pch.h"
#include "CEdit.h"
#include "CBmpMgr.h"
#include "CTileMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"

CEdit::CEdit() : m_bSelecting(false)
{
}

CEdit::~CEdit()
{
}

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
	Vector2 mouse = CKeyMgr::Get_Instance()->GetMousePos();


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CCamera::Get_Instance()->SetLookAt({ (lookat.x) - 20.f ,lookat.y });

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CCamera::Get_Instance()->SetLookAt({ (lookat.x) + 20.f ,lookat.y });

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CCamera::Get_Instance()->SetLookAt({ (lookat.x)  ,lookat.y - 20.f });

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CCamera::Get_Instance()->SetLookAt({ (lookat.x)  ,lookat.y + 20.f });


	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{

	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{

	}

	if (!m_bSelecting &&
		CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON) &&
		(CKeyMgr::Get_Instance()->Key_Pressing(VK_CONTROL)))
	{
		// 사각형 드래그
		CTileMgr::Get_Instance()->Set_StartCurser(mouse);
		CTileMgr::Get_Instance()->Set_EndCurser(mouse);
		CTileMgr::Get_Instance()->Set_Selecting(true);
		m_bSelecting = true;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON) &&
		m_bSelecting)
	{
		// 사각형 드래그
		CTileMgr::Get_Instance()->Set_EndCurser(mouse);
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON) &&
		m_bSelecting)
	{
		// 사각형 드래그
		CTileMgr::Get_Instance()->Set_EndCurser(mouse);
		CTileMgr::Get_Instance()->FillRec();
		CTileMgr::Get_Instance()->Set_Selecting(false);
		m_bSelecting = false;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)&&
		CKeyMgr::Get_Instance()->Key_Pressing(VK_MENU))
	{
		CTileMgr::Get_Instance()->Set_PipetID(mouse);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		CTileMgr::Get_Instance()->Picking(mouse, iDrawId, 1, TDIR_TOP);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		CTileMgr::Get_Instance()->Picking(mouse, iDrawId, 1, TDIR_DOWN);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		CTileMgr::Get_Instance()->Picking(mouse, iDrawId, 1, TDIR_LEFT);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('D'))
	{
		CTileMgr::Get_Instance()->Picking(mouse, iDrawId, 1, TDIR_RIGHT);
	}


	if (CKeyMgr::Get_Instance()->Key_Down('K'))
	{
		CTileMgr::Get_Instance()->Save_Data();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		CTileMgr::Get_Instance()->Load_Data();
	}

}