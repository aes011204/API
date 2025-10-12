#pragma once
class CObj;

enum class ColliderType
{
BODY,FOOT,ATTACK,HAND
};

class CColliderComp
{
public:

	CColliderComp(ColliderType type, Vector2 offset, Vector2 size, CObj* obj, bool circle = false) :m_tCollType(type), m_vColOffset(offset), m_vColSize(size), m_fRadius(m_vColSize.x * .5), m_obj(obj), m_isCircle(circle), m_vDirection({0,0})
	{
		if (m_vDirection.x == 0 && m_vDirection.y == 0)
			m_isRotation = false;
		else
			m_isRotation = true;
	}
	CColliderComp(ColliderType type, Vector2 offset, Vector2 size, CObj* obj,Vector2 dir) :m_tCollType(type), m_vColOffset(offset), m_vColSize(size), m_fRadius(m_vColSize.x * .5), m_obj(obj), m_vDirection(dir),m_isCircle(false)
	{
		half = { m_vColSize.x * 0.5f, m_vColSize.y * 0.5f };

		corners[0] = { -half.x, -half.y }; // 좌상
		corners[1] = { half.x, -half.y }; // 우상
		corners[2] = { half.x, half.y }; // 우하
		corners[3] = { -half.x, half.y }; // 좌하

		if (m_vDirection.x == 0 && m_vDirection.y == 0)
			m_isRotation = false;
		else
			m_isRotation = true;
	}
	virtual ~CColliderComp() {};

public:
	void ColUpdate(Vector2& objPos);


	
	void ColRender(HDC hdc, Vector2& objPos);

	const RECT* Get_Rect() {return &m_tColRect;}


	Vector2 GetColPosition();
	Vector2 GetColSize() { return m_vColSize; }
	float GetRadius() { return m_fRadius; }
	ColliderType GetType() { return m_tCollType; }
private:
	bool m_isCircle;
	const ColliderType m_tCollType;
	RECT m_tColRect;
	Vector2 m_vColSize;
	Vector2 m_vColOffset;

	Vector2 m_vColPosition;
	float m_fRadius;

	// 로테이션
	bool m_isRotation;
	Vector2  m_vDirection;
	Vector2 RealCorners[4];
	Vector2 half;
	Vector2 corners[4];

	CObj* m_obj;
	bool m_visible= false;

};

