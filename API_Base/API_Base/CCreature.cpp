#include "pch.h"
#include "CCreature.h"
#include "CCamera.h"
CCreature::CCreature() : m_ID(CID_END), m_bDead(false), m_tTarget(nullptr)
{
}

CCreature::~CCreature()
{
	Release();
}

void CCreature::Initialize()
{
}

int CCreature::Update()
{
	return 0;
}

void CCreature::Late_Update()
{
}

void CCreature::Render(HDC hdc)
{
	// 디버그 용
	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);


	Rectangle(hdc, RenderPos.x - m_vSize.x*.5f,
		RenderPos.y - m_vSize.y * .5f,
		RenderPos.x + m_vSize.x * .5f,
		RenderPos.y + m_vSize.y * .5f);

}

void CCreature::Release()
{
}
