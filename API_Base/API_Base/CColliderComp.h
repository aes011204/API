#pragma once
class CObj;

enum class ColliderType
{
BODY,FOOT,ATTACK,
};

class CColliderComp
{
public:

	CColliderComp(ColliderType type ,Vector2 offset, Vector2 size, CObj* obj, bool circle = false) :m_tCollType(type), m_vColOffset(offset), m_vColSize(size), m_fRadius(m_vColSize.x*.5), m_obj(obj), m_isCircle(circle)
	{
	}
	virtual ~CColliderComp() {};

public:
	void ColUpdate(Vector2& objPos)
	{
		Vector2 pos = objPos + m_vColOffset;
		m_tColRect.left = pos.x - m_vColSize.x * .5f;
		m_tColRect.top = pos.y - m_vColSize.y * .5f;
		m_tColRect.right = pos.x + m_vColSize.x * .5f;
		m_tColRect.bottom = pos.y + m_vColSize.y * .5f;
	}

	
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

	CObj* m_obj;

};

