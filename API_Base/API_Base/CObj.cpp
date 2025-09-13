#include "pch.h"
#include "CObj.h"


CObj::CObj() : m_vPosition({ WINCX * .5f, WINCY * .5f }), m_vDirection({ 0,0 }), m_vSize({ 5.f,5.f }), m_fSpeed(0.f)
{
}

CObj::~CObj()
{
}

void CObj::Update_Rec()
{
	m_tRect.left = m_vPosition.x - (m_vSize.x * .5f);
	m_tRect.top = m_vPosition.y - (m_vSize.y * .5f);
	m_tRect.right = m_vPosition.x + (m_vSize.x * .5f);
	m_tRect.bottom = m_vPosition.y + (m_vSize.y * .5f);
}