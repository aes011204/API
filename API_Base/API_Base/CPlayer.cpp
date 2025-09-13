#include "pch.h"
#include "CPlayer.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
CPlayer::CPlayer() 
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
    m_vSize = { 22.f,22.f };
    m_vPosition = { WINCX*.5f,WINCY*.5f };
    m_fSpeed = 200.f;

    m_ID = PLAYER;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"..\\Image\\Heart.bmp", L"Heart");
}

int CPlayer::Update()
{
    __super::Update_Rec();

    Key_Input();
    return 0;

}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC hdc)
{
    //Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    //CCreature::Render(hdc);

    Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);

    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Heart");

    GdiTransparentBlt(hdc,
        RenderPos.x - m_vSize.x,
        RenderPos.y - m_vSize.y,
        (int)m_vSize.x,
        (int)m_vSize.y,
        hMemDC,
        0,
        0,
        (int)m_vSize.x,
        (int)m_vSize.y,
        RGB(255, 255, 255));

   // BitBlt(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom, hMemDC, 0, 0, SRCCOPY); // 지우는 거 안쓸거면 이거 해야 랜더링됨
}

void CPlayer::Release()
{
}

void CPlayer::On_Collision(CObj* obj)
{
}


void CPlayer::Key_Input()
{
	float fY(0.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
        m_vPosition.x -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
        m_vPosition.x += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
        m_vPosition.y -= m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
        m_vPosition.y += m_fSpeed * CTimeMgr::Get_Instance()->GetDeltaTime();

	}
}