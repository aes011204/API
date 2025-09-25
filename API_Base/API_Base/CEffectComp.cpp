#include "pch.h"
#include "CEffectComp.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObj.h"

void CEffectComp::EffRender(HDC hdc)
{
	if (m_Start)
	{
	HDC	hEFMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pEffFrameKey);

	// 먼지 효과 (발생하는 순간 의 좌표 움직이면 안더ㅣㅁ) 지금은 1번 돌떄중복으로 생기지 않음

	Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos({ m_vEffPosition.x ,m_vEffPosition.y  });


	Vector2 RenderEFSize = CCamera::Get_Instance()->GetRenderSize(m_tEffFrame.vSize);


	GdiTransparentBlt(
		hdc, RenderPos.x - RenderEFSize.x * .5f, RenderPos.y - RenderEFSize.y * .5f,
		RenderEFSize.x, RenderEFSize.y,
		hEFMemDC,
		m_tEffFrame.iStart * m_tEffFrame.vSize.x,
		0,
		m_tEffFrame.vSize.x, m_tEffFrame.vSize.y,
		RGB(255, 0, 255));

	}
}



Vector2 CEffectComp::GetEffPosition()
{
	Vector2 pos = {};
	if (m_obj->Get_Dead() == false)
	{
		pos = m_vEffOffset + (m_obj->GetPosition());

	}
	return pos;
}



void CEffectComp::Move_EffectFrame()
{
	if (m_tEffFrame.dwTime == 0)
	{
		m_vEffPosition = GetEffPosition();
	}
	m_tEffFrame.dwTime += CTimeMgr::Get_Instance()->GetDeltaTime();



	if (m_tEffFrame.dwTime >= m_tEffFrame.dwSpeed)
	{
		++m_tEffFrame.iStart;

		if (m_tEffFrame.iStart > m_tEffFrame.iEnd)
		{
			m_Start = false;
			//m_tEffFrame.iStart = 0;
			return;
		}

		m_tEffFrame.dwTime = 0.f;
	}

}