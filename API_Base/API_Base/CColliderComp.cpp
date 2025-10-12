#include "pch.h"
#include "CColliderComp.h"
#include "CCamera.h"
#include "CObj.h"
#include "CKeyMgr.h"

void CColliderComp::ColUpdate(Vector2& objPos)
{

	if (CKeyMgr::Get_Instance()->Key_Down('0'))
	{
		m_visible = !m_visible;
	}
	{

		m_vDirection = m_obj->GetDirection();

		if (m_isRotation)
		{
			m_vColPosition = GetColPosition();

			float angle = atan2f(m_vDirection.y, m_vDirection.x) + PI / 2.f;;
			for (int i = 0; i < 4; ++i)
			{
				float x = corners[i].x * cosf(angle) - corners[i].y * sinf(angle);
				float y = corners[i].x * sinf(angle) + corners[i].y * cosf(angle);

				RealCorners[i] = { m_vColPosition.x + x,m_vColPosition.y + y };

			}

			Vector2 minPoint = RealCorners[0];
			Vector2 maxPoint = RealCorners[0];

			for (int i = 0; i < 4; ++i)
			{
				minPoint.x = min(minPoint.x, RealCorners[i].x);
				minPoint.y = min(minPoint.y, RealCorners[i].y);
				maxPoint.x = max(maxPoint.x, RealCorners[i].x);
				maxPoint.y = max(maxPoint.y, RealCorners[i].y);
			}
			m_tColRect = { (LONG)minPoint.x, (LONG)minPoint.y, (LONG)maxPoint.x, (LONG)maxPoint.y };

		}
		else
		{
			m_vColPosition = GetColPosition();

			Vector2 pos = objPos + m_vColOffset;
			m_tColRect.left = pos.x - m_vColSize.x * .5f;
			m_tColRect.top = pos.y - m_vColSize.y * .5f;
			m_tColRect.right = pos.x + m_vColSize.x * .5f;
			m_tColRect.bottom = pos.y + m_vColSize.y * .5f;

		}
	}
}

void CColliderComp::ColRender(HDC hdc, Vector2& objPos)
{
	if (m_visible)
	{

	HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hBluePen);

	// 브러시는 NULL (투명 처리)
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

	// 사각형 그리기

	Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(m_vColPosition);
	//Vector2 RenderPos = centerS + m_vColOffset;
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vColSize);

	if (m_isRotation)
	{
		// 색바꾸기
		SelectObject(hdc, hRedPen);

		// Vector2 → POINT 변환
		POINT pts[4];
		for (int i = 0; i < 4; ++i) {

			pts[i].x = (LONG)CCamera::Get_Instance()->GetRenderPos(RealCorners[i]).x;
			pts[i].y = (LONG)CCamera::Get_Instance()->GetRenderPos(RealCorners[i]).y;
		}

		// Polygon으로 사각형 그리기
		Polygon(hdc, pts, 4);
		SelectObject(hdc, hGreenPen);

		// 실제 충돌처리를 위한 rect
		SelectObject(hdc, hGreenPen);
		Vector2 LT = CCamera::Get_Instance()->GetRenderPos({ (int)m_tColRect.left, (int)m_tColRect.top });
		Vector2 RB = CCamera::Get_Instance()->GetRenderPos({ (int)m_tColRect.right, (int)m_tColRect.bottom });
		Rectangle(hdc, LT.x, LT.y, RB.x, RB.y);

	}
	else if (m_isCircle == false)
	{
		SelectObject(hdc, hBluePen);

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
	DeleteObject(hRedPen);
	DeleteObject(hBluePen);
	DeleteObject(hGreenPen);

	ReleaseDC(g_hWnd, hdc);
	}
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
