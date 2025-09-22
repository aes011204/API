#pragma once
#include "CColliderComp.h"

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

	void UpdateColl(Vector2 pos)
	{
		for (auto& col : m_vCollider)
			col.ColUpdate(m_vPosition);
	}

	void RenderColl(HDC hdc, Vector2 Pos)
	{
		for (auto& col : m_vCollider)
		col.ColRender(hdc, m_vPosition);
	}

	vector<CColliderComp>& Get_Collider() { return m_vCollider; }

protected:

	OBJID m_ID;


	// Renderer
	RECT			m_tRect;		// °´Ã¼ÀÇ ·»´õ ¹üÀ§

	// Core components
	Vector2			m_vPosition;	// °´Ã¼ÀÇ À§Ä¡, ÁßÁ¡
	Vector2			m_vDirection;	// °´Ã¼ÀÇ ¹æÇâ
	Vector2			m_vSize;		// °´Ã¼ÀÇ Å©±â


	float m_fSpeed;
	
	bool m_bDead;

	vector<CColliderComp> m_vCollider;
};

