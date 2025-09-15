#include "pch.h"
#include "CUI.h"
CUI::CUI()
{
	ZeroMemory(&m_tRect, sizeof(m_tRect));
}

CUI::~CUI()
{
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