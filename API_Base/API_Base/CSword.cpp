

#include "pch.h"
#include "CSword.h"
#include "CBmpMgr.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
CSword::CSword()
{

}

CSword::~CSword()
{

}

void CSword::Initialize()
{

	
}

int CSword::Update()
{
	m_vPosition = m_tTarget->GetBarrelPos();

	Vector2 mouse = CKeyMgr::Get_Instance()->GetMousePos();
	Vector2 worldmouse = CCamera::Get_Instance()->GetRealPos(mouse);

	m_vDirection = Vector2::Nomalize(worldmouse - m_vPosition);


	float base = atan2f(m_vDirection.y, m_vDirection.x) + PI / 2.f + PI / 2.f;
	if (worldmouse.x >= m_vPosition.x)
		base += radian; // 너가 쓰던 미세 보정

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		m_IsFlipped = !m_IsFlipped;
		m_OffsetDst = m_IsFlipped ? PI : 0.f;
	}

	// 3) 오프셋 보간 (그대로)
	float dt = CTimeMgr::Get_Instance()->GetDeltaTime();
	float maxStep = (PI * m_AttackCountSec) * dt;
	float diff = m_OffsetDst - m_OffsetCur;
	if (diff > maxStep) diff = maxStep;
	if (diff < -maxStep) diff = -maxStep;
	m_OffsetCur += diff;


	const float kFlipEps = 0.006f; // 오프셋용 미세 보정
	if (worldmouse.x >= m_vPosition.x)
	{
		float sideEps = (worldmouse.x >= m_vPosition.x) ? +kFlipEps : -kFlipEps;
		float finalAngle = base + m_OffsetCur + (m_IsFlipped ? sideEps : 0.f);
		angle = atan2f(sinf(finalAngle), cosf(finalAngle)); // 래핑

	}
	else
	{

		float sideEps = (worldmouse.x >= m_vPosition.x) ? -kFlipEps : +kFlipEps;
		float finalAngle = base - m_OffsetCur + (m_IsFlipped ? sideEps : 0.f);
		angle = atan2f(sinf(finalAngle), cosf(finalAngle)); // 래핑

	}
	// 5) 최종 각도 = base + 오프셋 + (플립 상태일 때만 측면 보정)



	CWeapon::Update();

	return 0;
}

void CSword::Late_Update()
{
	CWeapon::Late_Update();

}

void CSword::Render(HDC hdc)
{
	CWeapon::Render(hdc);


}

void CSword::Release()
{
}
