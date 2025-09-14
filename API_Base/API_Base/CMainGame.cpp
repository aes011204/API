#include "pch.h"
#include "CMainGame.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CBmpMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"
CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{

	m_hDC = GetDC(g_hWnd);
	CTimeMgr::Get_Instance()->Initialize();
	CCamera::Get_Instance()->SetLookAt({ WINCX * .5, WINCY * .5f });


	CSceneMgr::Get_Instance()->Change_Stage(SC_MAINMENU);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");


	

}

int CMainGame::Update()
{
	CTimeMgr::Get_Instance()->Update();

	CSceneMgr::Get_Instance()->Update();
	//CObjMgr::Get_Instance()->Update();
	CKeyMgr::Get_Instance()->Key_Update();
	//CCamera::Get_Instance()->Update();
	return 0;
}

void CMainGame::Late_Update()
{
	//CObjMgr::Get_Instance()->Late_Update();
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{

	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	//HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
	
	//BitBlt(hBackDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);


	//CObjMgr::Get_Instance()->Render(hBackDC);
	CSceneMgr::Get_Instance()->Render(hBackDC); 

	SetStretchBltMode(hBackDC, COLORONCOLOR); // (부드럽게면 HALFTONE)

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	//CObjMgr::Get_Instance()->Release();
	CSceneMgr::Get_Instance()->Release();


	ReleaseDC(g_hWnd, m_hDC);
}
