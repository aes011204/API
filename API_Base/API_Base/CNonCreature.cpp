#include "pch.h"
#include "CNonCreature.h"
#include "CCamera.h"

CNonCreature::CNonCreature(): m_ID(NCID_END)
{
}

CNonCreature::~CNonCreature()
{
}

void CNonCreature::Initialize()
{
}

int CNonCreature::Update()
{
	return 0;
}

void CNonCreature::Late_Update()
{
}

void CNonCreature::Render(HDC hdc)
{
	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);

	//Rectangle(hdc, RenderPos.x - m_vSize.x,
	//	RenderPos.y - m_vSize.y,
	//	RenderPos.x + m_vSize.x,
	//	RenderPos.y + m_vSize.y);
}

void CNonCreature::Release()
{
}
