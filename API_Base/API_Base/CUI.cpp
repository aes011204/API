#include "pch.h"
#include "CUI.h"
#include "CCreature.h"
#include "CNonCreature.h"
CUI::CUI() : m_tTarget(nullptr), m_bDead(false)
{
	ZeroMemory(&m_tRect, sizeof(m_tRect));
}

CUI::~CUI()
{
	Release();
}

void CUI::Initialize()
{
}

int CUI::Update()
{
	return 0;
}

int CUI::Late_Update()
{
	return 0;
}

void CUI::Render(HDC hdc)
{
}

void CUI::Release()
{
	
}

void CUI::Update_Rect()
{
	m_tRect.left = m_vPosition.x - (m_vSize.x * .5f);
	m_tRect.top = m_vPosition.y - (m_vSize.y * .5f);
	m_tRect.right = m_vPosition.x + (m_vSize.x * .5f);
	m_tRect.bottom = m_vPosition.y + (m_vSize.y * .5f);

}

void CUI::Font(HDC hdc, RECT rc, const WCHAR* str, int nHeight, int nWidth, int nWeight, int line) // weight 0~1000
{
	AddFontResource((L"../Font/AaCassiopeia.ttf"));
	HFONT currentFont = CreateFont(nHeight, nWidth, 0, 0, nWeight, 0, 0, 0,
		HANGEUL_CHARSET,0, 0,0, VARIABLE_PITCH | FF_ROMAN, TEXT("AaCassiopeia"));
	HFONT oldFont = (HFONT)SelectObject(hdc, currentFont);

	SetBkMode(hdc, TRANSPARENT); // 뒷배경 투명

	SetTextColor(hdc, 0x00ffffff);

	// 그림자 , 상하 좌우로 같은 스타일의 글자를 뿌려준다.
	//TextOut(hdc, pos.x + line, pos.y, str, wcslen(str));
	//TextOut(hdc, pos.x - line, pos.y, str, wcslen(str));
	//TextOut(hdc, pos.x, pos.y + line, str, wcslen(str));
	//TextOut(hdc, pos.x, pos.y - line, str, wcslen(str));
	RECT rcTop = { rc.left, rc.top - line, rc.right, rc.bottom };
	DrawText(hdc, str, -1, &rcTop, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT rcLeft = { rc.left - line, rc.top, rc.right, rc.bottom };
	DrawText(hdc, str, -1, &rcLeft, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT rcBottom = { rc.left, rc.top, rc.right, rc.bottom + line };
	DrawText(hdc, str, -1, &rcBottom, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT rcRight = { rc.left, rc.top, rc.right + line, rc.bottom };
	DrawText(hdc, str, -1, &rcRight, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SetTextColor(hdc, 0x00000000);
	
	//TextOut(hdc, pos.x, pos.y, str, wcslen(str));
	DrawText(hdc, str, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(hdc, oldFont);
	DeleteObject(currentFont);
}

void CUI::DrawHP(HDC hDC, float x, float y, float width, float height, float Hp, float MaxHp, HP_DIR dir)
{
	//Rectangle(hDC, (int)x - 1.0f, (int)(y - 1.0f), (int)(x + width + 1.0f), (int)(y + height + 1.2f));

	// Brush 빨간색으로 세팅
	HBRUSH newBrush = CreateSolidBrush(RGB(255, 0, 0));
	HPEN newPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	HBRUSH prevBrush = (HBRUSH)SelectObject(hDC, newBrush);
	HPEN prevPen = (HPEN)SelectObject(hDC, newPen);

	float value = width * Hp / MaxHp;
	int left = 0, right = 0;

	// 왼쪽 기준
	if (dir == HP_DIR::LeftToRight)
	{
		left = (int)x;
		right = (int)(x + value);
	}
	// 오른쪽 기준
	else
	{
		left = (int)(x + (width - value));
		right = (int)(x + width);
	}

	Rectangle(hDC, left, (int)y, right, (int)(y + height));

	// 사용한 Brush 삭제하고 원래대로 돌리기
	SelectObject(hDC, prevBrush);
	SelectObject(hDC, prevPen);
	DeleteObject(newBrush);
	DeleteObject(newPen);
}
void CUI::text(HDC hdc, RECT rc, const WCHAR* str, int nHeight, int nWidth, int nWeight )
{
	AddFontResource((L"../Font/AaCassiopeia.ttf"));
	HFONT currentFont = CreateFont(nHeight, nWidth, 0, 0, nWeight, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("AaCassiopeia"));
	HFONT oldFont = (HFONT)SelectObject(hdc, currentFont);

	SetBkMode(hdc, TRANSPARENT); // 뒷배경 투명

	SetTextColor(hdc, 0x00ffffff);

	
	//RECT rcTop = { rc.left, rc.top, rc.right, rc.bottom };
	//DrawText(hdc, str, -1, &rcTop, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//
	//SetTextColor(hdc, 0x00000000);

	//TextOut(hdc, pos.x, pos.y, str, wcslen(str));
	DrawText(hdc, str, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(hdc, oldFont);
	DeleteObject(currentFont);
}