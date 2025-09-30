#pragma once
//class CColliderComp;
#include "CColliderComp.h" // 정의 포함
#include "CEffectComp.h"
class CObj
{
public:
	CObj();
	CObj(Vector2 pos, Vector2 size) : m_vPosition(pos), m_vSize(size),
		m_vDirection({ 0,0 }), m_fSpeed(0.f), m_ID(OBJ_END), m_bDead(false) {}
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;



	virtual void On_Collision(CObj* obj,CColliderComp& my, CColliderComp& other) = 0;



public:

	void Update_Rec();

	const Vector2& GetPosition() const { return m_vPosition; }
	void SetPosition(const Vector2& pos) { m_vPosition = pos; }
	const Vector2& GetDirection() const { return m_vDirection; }
	void SetDirection(const Vector2& dir) { m_vDirection = dir; }
	const Vector2& GetSize() const { return m_vSize; }
	void SetSize(const Vector2& size) { m_vSize = size; }

	const RECT* Get_Rect() { return &m_tRect; }

	OBJID Get_ID() { return m_ID; }
	void Set_ID(OBJID id) { m_ID = id; }

	bool Get_Dead() { return m_bDead; }
	void Set_Dead(bool dead) { m_bDead = dead; }

	void UpdateColl(Vector2 pos);
	void RenderColl(HDC hdc, Vector2 Pos);


	void EffUpdate();
	//void EffUpdate(Vector2& objPos);
	void EffRender(HDC hdc);


	void Move_Frame();

	vector<CColliderComp>& Get_Collider() { return m_vCollider; }

	int Get_Money() const { return m_iMoney; }
	void Set_Money(int iMoney) { m_iMoney = iMoney; }

protected:

	OBJID m_ID;


	// Renderer
	RECT			m_tRect;		// 객체의 렌더 범위

	// Core components
	Vector2			m_vPosition;	// 객체의 위치, 중점
	Vector2			m_vDirection;	// 객체의 방향
	Vector2			m_vSize;		// 객체의 크기

	int m_iMoney = 0;

	float m_fSpeed;
	
	bool m_bDead;

	vector<CColliderComp> m_vCollider;
	vector<CEffectComp> m_vEffect;

	const TCHAR* m_pFrameKey;
	FRAME		m_tFrame;
};

