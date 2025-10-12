#include "pch.h"
#include "CBossBullet.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"
#include "CSoundManager.h"

CBossBullet::CBossBullet() :tmpboo(false),endtime(0.f)
{
}

CBossBullet::~CBossBullet()
{
}

void CBossBullet::Initialize()
{
    CBullet::Initialize();
    m_vSize = { 190,190 };
    m_fSpeed = 800.f;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/SwordEffect.bmp", L"SwordEffect");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossSword2.bmp", L"BossSword");

    m_tEffFrame.iStart = 0;
    m_tEffFrame.iEnd = 2;
    m_tEffFrame.dwSpeed = .3f;
    m_tEffFrame.dwTime = 0.f;
    m_tEffFrame.vSize = { 146,200 };
    m_vDirection = { -1,1 };
    delayT = 4.f;
    delayTMax = delayT;
    
    m_iDamage = 3;

    m_vCollider.push_back(CColliderComp(ColliderType::BODY, { 0,0 }, m_vSize, this,m_vDirection));
    m_vEffect.push_back(CEffectComp({ 0,0 }, this, m_tEffFrame,{ m_tEffFrame.vSize.x,m_tEffFrame.vSize.y }, L"SwordEffect"));

    endtime = m_tEffFrame.dwSpeed * (m_tEffFrame.iEnd + 1);


    {
        half = { m_vSize.x * 0.5f, m_vSize.y * 0.5f };

        corners[0] = { -half.x, -half.y }; // 좌상
        corners[1] = { half.x, -half.y }; // 우상
        corners[2] = { half.x, half.y }; // 우하
        corners[3] = { -half.x, half.y }; // 좌하
    }
}

int CBossBullet::Update()
{
    CBullet::Update();


   // Motion_Change();
	delayT -= CTimeMgr::Get_Instance()->GetDeltaTime();
	if (delayT >= 0)
	{

        Vector2 pos = CObjMgr::Get_Instance()->Get_Player()->GetPosition();
        m_vDirection = pos - m_vPosition;
        m_vDirection=m_vDirection.GetNomalized();

		//tmpDir = m_vDirection;
		//cout << m_vDirection.x << " , " << m_vDirection.x  << endl;
		if (delayT <= 0)
			delayT = -1;
	}

	if (m_eCurState == DEAD)
	{
		endtime -= CTimeMgr::Get_Instance()->GetDeltaTime();
		if (endtime > 0)
		{
			if (tmpboo == false)
			{
				m_vEffect.push_back(CEffectComp({ 0,0 }, this, m_tEffFrame, { m_tEffFrame.vSize.x,m_tEffFrame.vSize.y }, L"SwordEffect"));
				tmpboo = true;

			}
		}
        else
            m_bDead = true;
		//tmp = CEffectComp({ 0,0 }, this, m_tEffFrame, L"SwordEffect");
   
	}

	__super::EffUpdate();
	CCreature::Move_Frame();
    //if (m_bDead)
    //    return OBJ_DEAD;
    if (m_bDead)
        return OBJ_DEAD;
    return 0;
}

void CBossBullet::Late_Update()
{

    Vector2 world = CCamera::Get_Instance()->Get_WorldSize();
    if (m_vPosition.x < 0 || m_vPosition.x>world.x || m_vPosition.y < 0 || m_vPosition.y > world.y)
        m_bDead = true;

    if (m_eCurState == DEAD)
        return;

    if (delayT <= 0)
    {

        float m_fVolume = 20.f;
        CSoundManager::Get_Instance()->PlayFX(L"Belial_sword_shoot.wav", SOUND_EFFECT, m_fVolume);

       // cout << tmpDir.x << " , " << tmpDir.x  << endl;
        m_vPosition += m_vDirection * (m_fSpeed * (float)CTimeMgr::Get_Instance()->GetDeltaTime());
    }

  
    
   float angle = atan2f(m_vDirection.y, m_vDirection.x) - PI / 2.f;
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
            plgCorner[i-1].x = x + m_vSize.x * .5f;
            plgCorner[i-1].y = y + m_vSize.y * .5f;
        }
    }

    //float angle = atan2f(m_vDirection.y, m_vDirection.x) - PI / 2.f;
    //float cx = m_vSize.x * 0.5f;
    //float cy = m_vSize.y * 0.5f;
    //
    //plgCorner[0].x = (LONG)(cx + (-cx) * cosf(angle) - (-cy) * sinf(angle));
    //plgCorner[0].y = (LONG)(cy + (-cx) * sinf(angle) + (-cy) * cosf(angle));
    //
    //// UR (cx, -cy)
    //plgCorner[1].x = (LONG)(cx + (cx)*cosf(angle) - (-cy) * sinf(angle));
    //plgCorner[1].y = (LONG)(cy + (cx)*sinf(angle) + (-cy) * cosf(angle));
    //
    //// LL (-cx, cy)  <-- 여기가 핵심: lower-left (not lower-right)
    //plgCorner[2].x = (LONG)(cx + (-cx) * cosf(angle) - (cy)*sinf(angle));
    //plgCorner[2].y = (LONG)(cy + (-cx) * sinf(angle) + (cy)*cosf(angle));

}

void CBossBullet::Render(HDC hDC)
{


    HDC hSrcDC = CBmpMgr::Get_Instance()->Find_Img(L"BossSword");

  //  CBullet::Render(hDC);
    {
        // 1. 임시 DC + 투명 배경 비트맵 생성
        HDC hMemDC = CreateCompatibleDC(hDC);
        HBITMAP hTempBmp = CreateCompatibleBitmap(hDC, m_vSize.x, m_vSize.y);
        HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDC, hTempBmp);

        // 임시 DC의 배경 초기화 (흰색)
        HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
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


        GdiTransparentBlt(hDC,
            RenderPos.x - m_vSize.x*.5f,
            RenderPos.y - m_vSize.y * .5f,
            RenderSize.x, RenderSize.y, // 줌을 안함
            hMemDC,
            0,
            0,
            m_vSize.x, m_vSize.y,
            RGB(0, 0, 0));


        //DC 정리
        SelectObject(hMemDC, hOldBmp);
        DeleteObject(hTempBmp);
        DeleteDC(hMemDC);
       
        //DeleteDC(hSrcDC);
    }

    __super::RenderColl(hDC, m_vPosition);
    __super::EffRender(hDC);


}

void CBossBullet::Release()
{
    CBullet::Release();

}


void CBossBullet::On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other)
{
    if (obj->Get_ID() == MONSTER || obj->Get_ID() == BOSS)
        return;

    switch (OBJID id = obj->Get_ID())
    {
    case PLAYER:
    {
        dynamic_cast <CCreature*> (obj)->Take_Damage(m_iDamage);
    }
    break;
    case PLATFORM:
    {
       // m_bDead = true;
    }
    break;
    case WALL:
    {

        if (my.GetColPosition().x >= other.Get_Rect()->left
            && my.GetColPosition().y >= other.Get_Rect()->top
            && my.GetColPosition().x <= other.Get_Rect()->right
            && my.GetColPosition().y <= other.Get_Rect()->bottom)
        {
  
             m_eCurState = DEAD;


        }
       
    }
    break;
    default:
        break;
    }

}

void CBossBullet::Take_Damage(int _damage)
{
}

void CBossBullet::Motion_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 1;
            m_tFrame.dwSpeed = .3f;
            m_tFrame.dwTime = 0.f;
            m_tFrame.vSize = { 39,39 };



            m_vSize = m_tFrame.vSize;
            break;


        case DEAD:
            m_pFrameKey = L"BossBulletDead";
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.dwSpeed = .2f;
            m_tFrame.dwTime = 0.f;
            m_tFrame.vSize = { 39,39 };
            m_vSize = m_tFrame.vSize;
            break;

        }

        m_ePreState = m_eCurState;
    }
}