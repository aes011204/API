#include "pch.h"
#include "CWall.h"
#include "CCamera.h"

CWall::CWall()
{
	cout << m_vSize.x << endl;
}

CWall::~CWall()
{
}

void CWall::Initialize()
{
	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, m_vSize,this));
	m_ID = WALL;

}

int CWall::Update()
{
	__super::Update_Rec();



	return 0;
}

void CWall::Late_Update()
{
	__super::UpdateColl(m_vPosition);
}

void CWall::Render(HDC hdc)
{
	//HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	//HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	//
	//// 브러시는 NULL (투명 처리)
	//HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
	//
	//// 사각형 그리기
	//
	//Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	//float zoom = CCamera::Get_Instance()->GetZoom();
	//
	//float RenderSizeX = m_vSize.x * zoom;
	//float RenderSizeY = m_vSize.y * zoom;
	//// 좌상단 기준
	//float LeftTopX = RenderPos.x - RenderSizeX * .5f;
	//float LeftTopY = RenderPos.y - RenderSizeY * .5f;
	//
	//Rectangle(hdc, LeftTopX, LeftTopY, LeftTopX + RenderSizeX, LeftTopY + RenderSizeY);
	//
	//
	//// 원래 오브젝트 복원
	//SelectObject(hdc, hOldPen);
	//SelectObject(hdc, hOldBrush);
	//
	//// 만든 펜 삭제
	//DeleteObject(hPen);
	//
	//ReleaseDC(g_hWnd, hdc);


	__super::RenderColl(hdc, m_vPosition);
}

void CWall::Release()
{
}

void CWall::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
}
