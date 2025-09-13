#include "pch.h"
#include "CLine.h"
#include "CCamera.h"


CLine::CLine()
{
}

CLine::CLine(Vector2& _leftPoint, Vector2& _rIghtPoint)
	: m_tLine(_leftPoint, _rIghtPoint)
{
}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{


	Vector2 RenderPosL = CCamera::Get_Instance()->GetRenderPos(m_tLine.tLeft);
	Vector2 RenderPosR = CCamera::Get_Instance()->GetRenderPos(m_tLine.tRight);

	MoveToEx(hDC, static_cast<int>(RenderPosL.x) , static_cast<int>(RenderPosL.y) , NULL);
	LineTo(hDC, static_cast<int>(RenderPosR.x) , static_cast<int>(RenderPosR.y) );
}
