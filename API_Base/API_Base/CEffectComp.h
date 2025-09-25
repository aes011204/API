#pragma once
#include "CCamera.h"
class CEffectComp
{

public:
	CEffectComp() {}
	CEffectComp( Vector2 offset, CObj* obj, FRAME	frame, const TCHAR* FrameKey) : m_vEffOffset(offset)/*, m_vEffSize(size)*/,  m_obj(obj), m_tEffFrame(frame), m_pEffFrameKey(FrameKey)
	{
	}
	virtual ~CEffectComp() {};

public:
	void EffUpdate()
	{
		//Vector2 pos = objPos + m_vEffOffset;
		//m_tEffRect.left = pos.x - m_tEffFrame.vSize.x * .5f;
		//m_tEffRect.top = pos.y - m_tEffFrame.vSize.y * .5f;
		//m_tEffRect.right = pos.x + m_tEffFrame.vSize.x * .5f;
		//m_tEffRect.bottom = pos.y + m_tEffFrame.vSize.y * .5f;

		Move_EffectFrame();
	
	}


	//void EffRender(HDC hdc, Vector2& objPos);

	const RECT* Get_Rect() { return &m_tEffRect; }


	void EffRender(HDC hdc);
	//void EffRelease();

	Vector2 GetEffPosition();
	
	void Move_EffectFrame();
	bool Get_Start() { return m_Start; }
	const TCHAR* Get_FrameKey() { return m_pEffFrameKey; }

private:

	RECT m_tEffRect;
	Vector2 m_vEffOffset;
	Vector2 m_vEffPosition;


	CObj* m_obj;

	//이팩트 애니메이션
;
	FRAME		m_tEffFrame;
	const TCHAR* m_pEffFrameKey;
	bool m_Start = true;

};

