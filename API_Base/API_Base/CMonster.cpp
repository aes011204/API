#include "pch.h"
#include "CMonster.h"
#include "CCamera.h"

void CMonster::On_Collision(CObj* obj)
{
}

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_vPosition = { 600,600 };
	m_vSize = { 100,100 };

	m_ID = MONSTER;
}

int CMonster::Update()
{
	return 0;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC hdc)
{
	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);

	Rectangle(hdc, RenderPos.x-m_vSize.x, RenderPos.y - m_vSize.y, RenderPos.x + m_vSize.x, RenderPos.y + m_vSize.y );




}

void CMonster::Release()
{
}
