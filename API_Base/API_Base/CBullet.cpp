#include "pch.h"
#include "CBullet.h"
#include "CTimeMgr.h"
#include "CCamera.h"
#include "CBmpMgr.h"

void CBullet::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
	//CObject::On_Collision(pObj);

	switch (OBJID id = obj->Get_ID())
	{
	case PLAYER:
	{
		if(other.GetType() == ColliderType::BODY)
			m_eCurState = DEAD;

	}
	break;
	case MONSTER:
	{
		if (other.GetType() == ColliderType::BODY)
			dynamic_cast<CCreature*>(obj)->Take_Damage(m_iDamage);
			m_bDead = true;
	}
	break;
	case BOSS:
	{

		 m_bDead = true;
	}
	break;

	case ITEM:					  break;
		break;

	case PLATFORM:
	{
		m_bDead = true;
	}
	break;
	case WALL:
	{
		m_bDead = true;
	}
	break;
	default:
		break;
	}
}

void CBullet::Take_Damage(int _damage)
{
}

CBullet::CBullet() :m_eCurState(BS_END), m_ePreState(BS_END)
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	//m_vSize = Vector2(20, 20);

	m_fSpeed = 400.f;
	m_fSpeedY = 400.f;

	m_iDamage = 5.f;
	m_ID = BULLET;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::UpdateColl(m_vPosition);
	return 0;
}

void CBullet::Late_Update()
{
	if (m_eCurState == DEAD)
		return;
	m_vPosition += m_vDirection * (m_fSpeed * (float)CTimeMgr::Get_Instance()->GetDeltaTime());


	Vector2 world = CCamera::Get_Instance()->Get_WorldSize();
	if (m_vPosition.x < 0 || m_vPosition.x>world.x || m_vPosition.y < 0 || m_vPosition.y > world.y)
		m_bDead = true;
	__super::Update_Rec();

}

void CBullet::Render(HDC hDC)
{
	//Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	//float zoom = CCamera::Get_Instance()->GetZoom();
	//
	//float RenderSizeX = m_vSize.x * zoom;
	//float RenderSizeY = m_vSize.y * zoom;
	//// 좌상단 기준
	//float LeftTopX = RenderPos.x - RenderSizeX * .5f;
	//float LeftTopY = RenderPos.y - RenderSizeY * .5f;
	//
	//Ellipse(hDC, LeftTopX, LeftTopY, LeftTopX + RenderSizeX, LeftTopY + RenderSizeY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);


	Vector2 centerS = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vSize);

	// 스프라이트시트에서 가져올 소스 사각형(프레임)
	int srcX = m_tFrame.iStart * (int)m_vSize.x; // 열 인덱스


	// 투명색 키(마젠타)로 블릿
	GdiTransparentBlt(
		hDC,
		centerS.x - RenderSize.x * 0.5f,
		centerS.y - RenderSize.y * 0.5f,
		RenderSize.x, RenderSize.y,
		hMemDC, srcX, 0, (int)m_vSize.x, (int)m_vSize.y,
		RGB(255, 0, 255));

	__super::RenderColl(hDC, m_vPosition);

}

void CBullet::Release()
{
}
