#include "pch.h"
#include "CMonster.h"
#include "CCamera.h"

void CMonster::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
}

void CMonster::Take_Damage(int _damage)
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
	m_vPosition = { 600,300 };
	m_vSize = { 100,100 };

	m_iMaxHP = 500.f;
	m_iHP = m_iMaxHP;
	m_iDamage = 1;
	m_ID = MONSTER;
}

int CMonster::Update()
{

	Update_Rec();
	return 0;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC hdc)
{
	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	float zoom = CCamera::Get_Instance()->GetZoom();

	float RenderSizeX = m_vSize.x * zoom;
	float RenderSizeY = m_vSize.y * zoom;
	// 좌상단 기준
	float LeftTopX = RenderPos.x - RenderSizeX * .5f;
	float LeftTopY = RenderPos.y - RenderSizeY* .5f;

	Rectangle(hdc, LeftTopX, LeftTopY, LeftTopX + RenderSizeX, LeftTopY + RenderSizeY );




}

void CMonster::Release()
{
}
