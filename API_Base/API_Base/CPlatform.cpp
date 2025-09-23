#include "pch.h"
#include "CPlatform.h"
#include "CCamera.h"
#include "CColliderComp.h"



CPlatform::CPlatform()
{

}

CPlatform::~CPlatform()
{
	Release();
}

void CPlatform::Initialize()
{

	m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, m_vSize, this));
	m_ID = PLATFORM;
}

int CPlatform::Update()
{
	if (m_bDead)
		return OBJ_DEAD;



	__super::Update_Rec();

	__super::UpdateColl(m_vPosition);

	return OBJ_NOEVENT;

}

void CPlatform::Late_Update()
{
}

void CPlatform::Render(HDC hdc)
{

	//HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
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
	//CNonCreature::Render(hdc);

	__super::RenderColl(hdc,m_vPosition);


}

void CPlatform::Release()
{
}


void CPlatform::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
}