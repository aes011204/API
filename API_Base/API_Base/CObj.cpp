#include "pch.h"
#include "CObj.h"
#include "CColliderComp.h"


CObj::CObj() : m_vPosition({ WINCX * .5f, WINCY * .5f }), m_vDirection({ 0,0 }), m_fSpeed(0.f), m_ID(OBJ_END), m_bDead(false)
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

void CObj::UpdateColl(Vector2 pos)
{
	{
		for (auto& col : m_vCollider)
			col.ColUpdate(m_vPosition);
	}
}

void CObj::RenderColl(HDC hdc, Vector2 Pos)
{
	for (auto& col : m_vCollider)
		col.ColRender(hdc, m_vPosition);
}

void CObj::EffUpdate()
{
	for (auto& col : m_vEffect)
		col.EffUpdate();
}

void CObj::EffRender(HDC hdc)
{
	for (auto& col : m_vEffect)
		col.EffRender(hdc);
}
