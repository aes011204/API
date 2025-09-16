#include "pch.h"
#include "CStateBar.h"
#include "CBmpMgr.h"

CStateBar::CStateBar() :TargetCurInfo(0.f), TargetMaxInfo(0.f)
{
}

CStateBar::~CStateBar()
{
}

void CStateBar::Initialize()
{
	TargetCurInfo = 10.f;
	TargetMaxInfo = 100.f;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PlayerLifeBase.bmp", L"base");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PlayerLifeBack.bmp", L"back");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/LifeWave.bmp", L"wave");
}

int CStateBar::Update()
{
    return 0;
}

int CStateBar::Late_Update()
{
    return 0;
}


void CStateBar::Render(HDC hdc)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"back");
	Vector2 pos = {20 , 20 };// 좌상단 기준
	Vector2 size = { 296,64 };
	

		// 스프라이트시트에서 가져올 소스 사각형(프레임)
		//int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스

		// 투명색 키(마젠타)로 블릿
		GdiTransparentBlt(
			hdc,
			pos.x,
			pos.y,
			size.x, size.y-10,
			hMemDC, 0, 0, size.x, size.y,
			RGB(255, 0, 255));

		CUI::DrawHP(hdc, pos.x+100, pos.y, size.x, size.y - 10-1, TargetCurInfo, TargetMaxInfo);
		

		HDC	hMemDC2 = CBmpMgr::Get_Instance()->Find_Img(L"base");


		GdiTransparentBlt(
			hdc,
			pos.x,
			pos.y,
			size.x, size.y - 10,
			hMemDC2, 0, 0, size.x, size.y,
			RGB(255, 0, 255));


    //Vector2 pos1 = { 50,50 };
    //CUI::Font(hdc, pos1, L"안녀ㅑㅇ",30,0,700, 3);
}

void CStateBar::Release()
{
}

bool CStateBar::IsColl()
{
    return false;
}
