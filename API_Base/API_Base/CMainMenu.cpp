#include "pch.h"
#include "CMainMenu.h"
#include "CBmpMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CUIMgr.h"
#include "CAbstractFactory.h"
#include "CButton.h"
#include "CTimeMgr.h"
#include "CSoundManager.h"

float	g_fVolume = 20.f;

CMainMenu::CMainMenu() : m_vLogoSize({  156.f,75.f  }),m_fMovePosX1(0.f), m_fMovePosX2(0.f)
{
}
CMainMenu::~CMainMenu()
{
    Release();
}
void CMainMenu::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BG/Cloud1.bmp", L"CloudBack");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BG/Cloud2.bmp", L"CloudFront");

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BG/MainLogo.bmp", L"MainLogo");
    // UI
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BG/OptionOn_Kor.bmp", L"OptionOn");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BG/OptionOff_Kor.bmp", L"OptionOff");
    CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CButton>::
        CreateUIButton({ WINCX * .5f, WINCY * .7f }, { 20.f, 12.f }, L"OptionOff", L"OptionOn", []() {CSceneMgr::Get_Instance()->Rq_changeScene(SC_EDIT);}, 3.f));

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BG/PlayOn_Kor.bmp", L"PlayOn");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BG/PlayOff_Kor.bmp", L"PlayOff");
    CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CButton>::
        CreateUIButton({ WINCX * .5f, WINCY * .6f }, { 36.f, 12.f }, L"PlayOff", L"PlayOn", []() {CSceneMgr::Get_Instance()->Rq_changeScene(SC_VILLAGE);}, 3.f));

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BG/ExitOn_Kor.bmp", L"ExitOn");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BG/ExitOff_Kor.bmp", L"ExitOff");
    CUIMgr::Get_Instance()->Add_Object(CAbstractFactory<CButton>::
        CreateUIButton({ WINCX * .5f, WINCY * .8f }, { 21.f, 12.f }, L"ExitOff", L"ExitOn", []() {DestroyWindow(g_hWnd);}, 3.f));


    CSoundManager::Get_Instance()->PlayBGM(L"Title.wav", g_fVolume);

}

int CMainMenu::Update()
{

        // if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
        //{
        //    CSoundMgr::Get_Instance()->PlaySound(L"Success.wav", SOUND_EFFECT, g_fVolume);
        //    return;
        //}


    CUIMgr::Get_Instance()->Update();
    if (GetAsyncKeyState('1'))//CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
    {
        CSceneMgr::Get_Instance()->Change_Stage(SC_VILLAGE);
        return 0;
    }



    return 0;
}

void CMainMenu::Late_Update()
{
    CUIMgr::Get_Instance()->Late_Update();


}

void CMainMenu::Render(HDC hdc)
{

    {

    // Brush  세팅
    HBRUSH newBrush = CreateSolidBrush(RGB(122, 182, 247));
    HPEN newPen = CreatePen(PS_SOLID, 1, RGB(122, 182, 247));

    HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, newBrush);
    HPEN prevPen = (HPEN)SelectObject(hdc, newPen);

    Rectangle(hdc, 0, 0, WINCX, WINCY);

    // 사용한 Brush 삭제하고 원래대로 돌리기
    SelectObject(hdc, prevBrush);
    SelectObject(hdc, prevPen);
    DeleteObject(newBrush);
    DeleteObject(newPen);

    }
    Render_MovingBG(hdc, 150, L"CloudBack", { 2564, 768 }, m_fMovePosX1);

    Render_MovingBG(hdc, 300, L"CloudFront", { 2304, 768 },m_fMovePosX2);
    {
        // 렌더 메인 로고 
        Vector2 logoPos{ (WINCX * .5f),(WINCY * .5f) * 3.f / 5.f };
        HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"MainLogo");
        Vector2 resize = m_vLogoSize * 3.f;
        //SetStretchBltMode(hdc, COLORONCOLOR); // (부드럽게면 HALFTONE)

        //BitBlt(hdc, WINCX- m_vLogoSize.x*.5f, logoPosY - m_vLogoSize.y * .5f, WINCX + m_vLogoSize.x * .5f, logoPosY + m_vLogoSize.y * .5f, hMemDC, 0, 0, SRCCOPY); // 지우는 거 안쓸거면 이거 해야 랜더링됨
        GdiTransparentBlt(hdc,
            logoPos.x - resize.x * .5f,
            logoPos.y - resize.y * .5f,
            (int)resize.x,
            (int)resize.y,
            hMemDC,
            0, 0,
            (int)m_vLogoSize.x,
            (int)m_vLogoSize.y,
            RGB(255, 255, 255));
    }
   
    {
        //함수 만들어야 할듯 스피드를 받아서 오른쪽으로 가게 하기, 화면 끝나면 다시 처음으로 


    }
    CUIMgr::Get_Instance()->Render(hdc);

}

void CMainMenu::Release()
{
    CUIMgr::Get_Instance()->Release();
    //?? bmp매니져는 release 해야하나?? 여기서?? 씬마다?? 근대 그럼 다시못만들지 않나? static이니까

    CSoundManager::Get_Instance()->StopAll();
}

void CMainMenu::Render_MovingBG(HDC hdc, float _speed, const TCHAR* name, Vector2 size, float& accSpeed)
{
    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(name);
    
    
    accSpeed += _speed * (float)(CTimeMgr::Get_Instance()->GetDeltaTime());
    
     if (accSpeed >= size.x)
         accSpeed = 0.f;

    GdiTransparentBlt(hdc,
        -accSpeed,
        0,
        (int)size.x,
        (int)size.y,
        hMemDC,
        0, 0,
        (int)size.x,
        (int)size.y,
        RGB(255, 0, 255));

    GdiTransparentBlt(hdc,
        size.x- accSpeed,
        0,
        (int)size.x,
        (int)size.y,
        hMemDC,
        0, 0,
        (int)size.x,
        (int)size.y,
        RGB(255, 0, 255));


}
