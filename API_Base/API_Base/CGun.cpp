#include "pch.h"
#include "CGun.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayerBullet.h"
#include "CSoundManager.h"

CGun::CGun()
{
}

CGun::~CGun()
{
}

void CGun::Initialize()
{
	CWeapon::Initialize();


	strName = L"총";
	itemType = TWOHAND;
	m_eItemState = UNEQUIP;
	m_eItemClass = BEGGINER;
	m_eWeaponType = GUN;
	m_iDefense = 0;
	m_AttackCountSec = 10.f;
	m_iDamage = 10;
	m_iMoney = 10;

	
	iCost = 100;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/MatchlockGunBMP.bmp", L"MatchlockGun");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/MatchlockGunBMPL.bmp", L"MatchlockGunL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/MatchlockGunIcon.bmp", L"MatchlockGunIcon");
	m_pFrameKey = L"MatchlockGun";
	m_vSize = { 54.f, 54.f };
	

	m_iconImgSize = { 27,8 };
	
	m_pIconKey = L"MatchlockGunIcon";

	CWeapon::Initialize();
	m_Length = 70.f;

}

int CGun::Update()
{
	m_vPosition = m_tTarget->GetBarrelPos();

	Vector2 mouse = CKeyMgr::Get_Instance()->GetMousePos();
	Vector2 worldmouse = CCamera::Get_Instance()->GetRealPos(mouse);

	m_vDirection = Vector2::Nomalize(worldmouse - m_vPosition);


	angle = atan2f(m_vDirection.y, m_vDirection.x);

	Vector2 endBarrel = m_vDirection * m_Length;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		float m_fVolume = 20.f;
		CSoundManager::Get_Instance()->PlayFX(L"Gun.wav", SOUND_EFFECT, m_fVolume);

		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayerBullet>::Create((endBarrel+m_vPosition), {16,3}, m_vDirection));

	}

	CWeapon::Update();

	if (worldmouse.x < m_vPosition.x)
	{
		m_pFrameKey = L"MatchlockGunL";
	}
	else
		m_pFrameKey = L"MatchlockGun";

	return 0;
}

void CGun::Late_Update()
{
	CWeapon::Late_Update();

}

void CGun::Render(HDC hdc)
{
	//CWeapon::Render(hdc);
	if (m_eItemState == EQUIP)
	{
		Vector2 m_vReSize = m_vSize * 2.5f;
		HDC hSrcDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

		//  CBullet::Render(hDC);
		{
			// 1. 임시 DC + 투명 배경 비트맵 생성
			HDC hMemDC = CreateCompatibleDC(hdc);
			HBITMAP hTempBmp = CreateCompatibleBitmap(hdc, m_vSize.x, m_vSize.y);
			HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDC, hTempBmp);

			// 임시 DC의 배경 초기화 (흰색)
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
			RECT rect = { 0,0, m_vSize.x, m_vSize.y };
			FillRect(hMemDC, &rect, hBrush);

			Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(m_vPosition);
			Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vReSize);

			PlgBlt(hMemDC,
				plgCorner,
				hSrcDC,
				0, 0,
				m_vSize.x, m_vSize.y,
				NULL, NULL, NULL);


			GdiTransparentBlt(hdc,
				RenderPos.x - RenderSize.x * .5f,
				RenderPos.y - RenderSize.y * .5f,
				RenderSize.x, RenderSize.y, // 줌을 안함
				hMemDC,
				0,
				0,
				m_vSize.x, m_vSize.y,
				RGB(255, 0, 255));


			//DC 정리
			DeleteObject(hBrush);
			SelectObject(hMemDC, hOldBmp);
			DeleteObject(hTempBmp);
			DeleteDC(hMemDC);


		}
	}
}


void CGun::Release()
{
	CWeapon::Release();

}
