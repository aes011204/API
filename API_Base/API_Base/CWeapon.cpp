#include "pch.h"
#include "CWeapon.h"
#include "CCreature.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"

CWeapon::CWeapon()
{
}

CWeapon::~CWeapon()
{
}

void CWeapon::Initialize()
{
    m_ID = ITEM;
    {
        half = { m_vSize.x * 0.5f, m_vSize.y * 0.5f };

        corners[0] = { -half.x, -half.y }; // 좌상
        corners[1] = { half.x, -half.y }; // 우상
        corners[2] = { half.x, half.y }; // 우하
        corners[3] = { -half.x, half.y }; // 좌하
    }
    
}

int CWeapon::Update()
{
   
    for (int i = 0; i < 4; ++i)
    {
        float x = corners[i].x * cosf(angle) - corners[i].y * sinf(angle);
        float y = corners[i].x * sinf(angle) + corners[i].y * cosf(angle);

        RealCorners[i] = { m_vPosition.x + x,m_vPosition.y + y };

        if (i <= 1) // index (0~3) pigblt는 LT, RT, LB(좌하)(3개만)/ corners[i]의 순서는  LT, RT, RB, LB
        {
            //x,y에 각각 사이즈 반만큼 더하는 이유는 corner 지금 위치는( - ~ + )  화면 밖임 그래서 더해서 수평이동 필요
            plgCorner[i].x = x + m_vSize.x * .5f;
            plgCorner[i].y = y + m_vSize.y * .5f;
        }
        else if (i == 3)
        {
            plgCorner[i - 1].x = x + m_vSize.x * .5f;
            plgCorner[i - 1].y = y + m_vSize.y * .5f;
        }
    }


   
   // __super::Move_Frame();
    __super::Update_Rec();
	return 0;
}

void CWeapon::Late_Update()
{
   

   // float angle = atan2f(m_vDirection.y, m_vDirection.x) + PI / 2.f;


}

void CWeapon::Render(HDC hdc)
{
    if (m_eItemState == EQUIP)
    {

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
            Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vSize);

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

        /*__super::RenderColl(hdc, m_vPosition);
        __super::EffRender(hdc);*/


    }

}

void CWeapon::Release()
{
}

void CWeapon::ItemInfo()
{
}

void CWeapon::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
}
