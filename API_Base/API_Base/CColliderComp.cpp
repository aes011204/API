#include "pch.h"
#include "CColliderComp.h"
#include "CCamera.h"
#include "CObj.h"

void CColliderComp::ColRender(HDC hdc, Vector2& objPos)
{

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	// 브러시는 NULL (투명 처리)
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

	// 사각형 그리기
	
	Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(objPos+ m_vColOffset);
	//Vector2 RenderPos = centerS + m_vColOffset;
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vColSize);
	
	if (m_isCircle == false)
	{
	Rectangle(hdc, centerS.x - RenderSize.x * 0.5f,
		centerS.y - RenderSize.y * 0.5f,
		centerS.x + RenderSize.x * 0.5f, centerS.y + RenderSize.y * 0.5f);

	}
	else
	{
		Ellipse(hdc, centerS.x - RenderSize.x * 0.5f,
			centerS.y - RenderSize.y * 0.5f,
			centerS.x + RenderSize.x * 0.5f, centerS.y + RenderSize.y * 0.5f);
	}


	// 원래 오브젝트 복원
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);

	// 만든 펜 삭제
	DeleteObject(hPen);

	ReleaseDC(g_hWnd, hdc);
}

Vector2 CColliderComp::GetColPosition()
{
	Vector2 pos = {};
	if (m_obj->Get_Dead() == false)
	{
		pos = m_vColOffset + (m_obj->GetPosition());

	}
	return pos;
}
