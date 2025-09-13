#include "pch.h"
#include "CMainMenu.h"
#include "CBmpMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
CMainMenu::CMainMenu()
{
}
CMainMenu::~CMainMenu()
{
    Release();
}
void CMainMenu::Initialize()
{
   //CBmpMgr::Get_Instance()->Insert_Bmp(,)
}

int CMainMenu::Update()
{

    if (GetAsyncKeyState('1'))//CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
    {
        CSceneMgr::Get_Instance()->Change_Stage(SC_VILLAGE);
        return 0;
    }
    return 0;
}

void CMainMenu::Late_Update()
{
}

void CMainMenu::Render(HDC hdc)
{
    Rectangle(hdc, 100, 100, WINCX-100, WINCY-100);
}

void CMainMenu::Release()
{
}
