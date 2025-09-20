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
CMainGame::CMainGame() :m_hDC(nullptr)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{

	m_hDC = GetDC(g_hWnd);

	
	{
		GetClientRect(g_hWnd, &m_rect);


		hBackDC = CreateCompatibleDC(m_hDC);
		m_bmpBack = CreateCompatibleBitmap(m_hDC, m_rect.right, m_rect.bottom);
		{
			hBackDC = CreateCompatibleDC(m_hDC);
			m_bmpBack = CreateCompatibleBitmap(m_hDC, m_rect.right, m_rect.bottom);
			HBITMAP prev = (HBITMAP)::SelectObject(hBackDC, m_bmpBack);
			DeleteObject(prev);
		}
	}
	CTimeMgr::Get_Instance()->Initialize();
	CCamera::Get_Instance()->SetLookAt({ WINCX * .5, WINCY * .5f });
	CSceneMgr::Get_Instance()->Change_Stage(SC_MAINMENU);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Back");



}

int CMainGame::Update()
{
	CTimeMgr::Get_Instance()->Update();

	CSceneMgr::Get_Instance()->Update();

	CKeyMgr::Get_Instance()->Key_Update();
	
	return 0;
}

void CMainGame::Late_Update()
{
	
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{

	//HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
	//
	//BitBlt(hBackDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);
	
	
	//HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");

	CSceneMgr::Get_Instance()->Render(hBackDC); 

	SetStretchBltMode(hBackDC, COLORONCOLOR); // (부드럽게면 HALFTONE)

	//BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	// 기존 Rectangle을 그려서 깜빡임 최소화 한걸 더블 버퍼링으로 바꿈
	{
		//Rectangle(m_hDC, 0, 0, WINCX, WINCY);
		BitBlt(m_hDC, 0, 0, m_rect.right, m_rect.bottom, hBackDC, 0, 0, SRCCOPY);
		PatBlt(hBackDC, 0, 0, m_rect.right, m_rect.bottom, WHITENESS);
	}
}

void CMainGame::Release()
{
	
	CSceneMgr::Get_Instance()->Release();


	ReleaseDC(g_hWnd, m_hDC);
}
