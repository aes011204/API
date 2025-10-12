#include "pch.h"
#include "CText.h"
#include "CBmpMgr.h"
#include "CCreature.h"
CText::CText() :TargetCurInfo(0), TargetMaxInfo(0), OtherInfo(0)
{
}


CText::~CText()
{
	Release();
}

void CText::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Base_0.bmp", L"TEXTbase");
	m_vSize = { WINCX, 200 };
	m_vPosition = { WINCX*.5f,WINCY - m_vSize.y*.5f };// 좌상단 기준
	Imgsize = { 111,132 };
}

int CText::Update()
{
	


	Update_Rect();
	return 0;
}

int CText::Late_Update()
{
	if (m_bDead)
		return 1;
	return 0;
}


void CText::Render(HDC hdc)
{



		{

		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(51, 43, 62));
		HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

		HBRUSH hBrush = CreateSolidBrush(RGB(51, 43, 62));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBrush);

		DeleteObject(hPen);
		DeleteObject(hBrush);
		}

		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"TEXTbase");

		// 투명색 키(마젠타)로 블릿
		GdiTransparentBlt(
			hdc,
			m_tRect.left,
			m_tRect.top,
			m_vSize.x, m_vSize.y,
			hMemDC, 0, 0, Imgsize.x, Imgsize.y,
			RGB(255, 0, 255));


		


		

		WCHAR buffer[32];
		swprintf_s(buffer, 32,L"안녕하세요! 좋은 물건 많이 있어요!");

		//RECT rc = { redPos.x,redPos.y, redPos.x + redSize.x, redPos.y + redSize.y };
		CUI::text(hdc, m_tRect, buffer, 40, 30, 800);

	//	if (OtherInfo != 0)
	//	{
	//		WCHAR tmpBuffer[8];
	//		swprintf_s(tmpBuffer, 8, L"%d ", OtherInfo);
	//		RECT tmp = { pos.x + 10, pos.y, pos.x + 80 + 10, pos.y + size.y };
	//		CUI::Font(hdc, tmp, tmpBuffer, 40, 30, 1000, 6);
	//	}
	
	
}

void CText::Release()
{

}

bool CText::IsColl()
{
	return false;
}


//void CText::TextRecRender(HDC hdc, const TCHAR* back, const TCHAR* base, Vector2 pos, Vector2 size, Vector2 resize)
//{
//
//	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(back);
//
//	// 스프라이트시트에서 가져올 소스 사각형(프레임)
//	//int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스
//
//	// 투명색 키(마젠타)로 블릿
//	GdiTransparentBlt(
//		hdc,
//		pos.x,
//		pos.y,
//		resize.x, resize.y,
//		hMemDC, 0, 0, size.x, size.y,
//		RGB(255, 0, 255));
//
//	Vector2 redPos = { pos.x + 80 , pos.y };// 좌상단 기준
//	Vector2 redSize = { resize.x - 80 - 5,resize.y - 1 };
//
//
//	HDC	hMemDC2 = CBmpMgr::Get_Instance()->Find_Img(base);
//
//	GdiTransparentBlt(
//		hdc,
//		pos.x,
//		pos.y,
//		resize.x, resize.y,
//		hMemDC2, 0, 0, size.x, size.y,
//		RGB(255, 0, 255));
//}