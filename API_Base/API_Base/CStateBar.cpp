#include "pch.h"
#include "CStateBar.h"
#include "CBmpMgr.h"

CStateBar::CStateBar() :TargetCurInfo(0), TargetMaxInfo(0), OtherInfo(0)
{
}

CStateBar::~CStateBar()
{
	Release();
}

void CStateBar::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PlayerLifeBase.bmp", L"base");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PlayerLifeBack.bmp", L"back");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/LifeWave.bmp", L"wave");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/BossLifeBase.bmp", L"BossBase");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/BossLifeBack.bmp", L"BossBack");
}

int CStateBar::Update()
{
	if (m_tTarget->Get_Dead())
		return 1;

	if (m_tTarget)
	{
		TargetCurInfo = m_tTarget->Get_HP();
		TargetMaxInfo = m_tTarget->Get_MaxHP();
		if (m_tTarget->Get_ID() == PLAYER)
			OtherInfo = m_tTarget->Get_Level();

		// 추후 수저 ㅇ 주소 값으로
	}

    return 0;
}

int CStateBar::Late_Update()
{
	if (m_bDead)
		return 1;
    return 0;
}


void CStateBar::Render(HDC hdc)
{
	if (m_tTarget == nullptr)
		return;


	if (m_tTarget->Get_ID() == PLAYER)
	{
		Vector2 pos = { 20 , 20 };// 좌상단 기준
		Vector2 size = { 296,64 };

		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"back");


		// 스프라이트시트에서 가져올 소스 사각형(프레임)
		//int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스

		// 투명색 키(마젠타)로 블릿
		GdiTransparentBlt(
			hdc,
			pos.x,
			pos.y,
			size.x, size.y,
			hMemDC, 0, 0, size.x, size.y,
			RGB(255, 0, 255));

		Vector2 redPos = { pos.x + 80 , pos.y };// 좌상단 기준
		Vector2 redSize = { size.x - 80 - 5,size.y - 1 };

		CUI::DrawHP(hdc, redPos.x, redPos.y, redSize.x, redSize.y, TargetCurInfo, TargetMaxInfo);


		HDC	hMemDC2 = CBmpMgr::Get_Instance()->Find_Img(L"base");


		GdiTransparentBlt(
			hdc,
			pos.x,
			pos.y,
			size.x, size.y,
			hMemDC2, 0, 0, size.x, size.y,
			RGB(255, 0, 255));

		WCHAR buffer[32];
		swprintf_s(buffer, 32, L"%d / %d", TargetCurInfo, TargetMaxInfo);

		RECT rc = { redPos.x,redPos.y, redPos.x + redSize.x, redPos.y + redSize.y };
		CUI::Font(hdc, rc, buffer, 40, 30, 1000, 6);

		if (OtherInfo != 0)
		{
			WCHAR tmpBuffer[8];
			swprintf_s(tmpBuffer, 8, L"%d ", OtherInfo);
			RECT tmp = { pos.x + 10, pos.y, pos.x + 80 + 10, pos.y + size.y };
			CUI::Font(hdc, tmp, tmpBuffer, 40, 30, 1000, 6);
		}
	}
	else if (m_tTarget->Get_ID()==BOSS)
	{
		Vector2 size = { 600,77 };
		Vector2 resize = size * .8f;
		HPBarRender(hdc, L"BossBack", L"BossBase", { WINCX * .5f  -resize.x * .5f ,WINCY - 90.f}, size, resize);
	}
	
}

void CStateBar::Release()
{
}

bool CStateBar::IsColl()
{
    return false;
}


void CStateBar::HPBarRender(HDC hdc, const TCHAR* back,const TCHAR* base, Vector2 pos, Vector2 size, Vector2 resize)
{

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(back);

	// 스프라이트시트에서 가져올 소스 사각형(프레임)
	//int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스

	// 투명색 키(마젠타)로 블릿
	GdiTransparentBlt(
		hdc,
		pos.x,
		pos.y,
		resize.x, resize.y,
		hMemDC, 0, 0, size.x, size.y,
		RGB(255, 0, 255));

	Vector2 redPos = { pos.x + 80 , pos.y };// 좌상단 기준
	Vector2 redSize = { resize.x - 80 - 5,resize.y - 1 };

	CUI::DrawHP(hdc, redPos.x, redPos.y, redSize.x, redSize.y, TargetCurInfo, TargetMaxInfo);


	HDC	hMemDC2 = CBmpMgr::Get_Instance()->Find_Img(base);


	GdiTransparentBlt(
		hdc,
		pos.x,
		pos.y,
		resize.x, resize.y,
		hMemDC2, 0, 0, size.x, size.y,
		RGB(255, 0, 255));
}