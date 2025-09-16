#include "pch.h"
#include "CMainUI.h"

CMainUI::CMainUI()
{
}

CMainUI::~CMainUI()
{
}

void CMainUI::Initialize()
{
}

int CMainUI::Update()
{

	return 0;
}

int CMainUI::Late_Update()
{
	return 0;
}

void CMainUI::Render(HDC hdc)
{
	Vector2 pos = { 50,50 };
	//ont(hdc, pos, L"20",);
}

void CMainUI::Release()
{
}

bool CMainUI::IsColl()
{
	return false;
}
