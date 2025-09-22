#pragma once

enum class HP_DIR { LeftToRight, RightToLeft };

class CCreature;

class CUI
{
public:
	CUI();
	virtual ~CUI();
public:
	virtual void Initialize()=0;
	virtual int Update()=0;
	virtual int Late_Update()=0;
	virtual void Render(HDC hdc)=0;
	virtual void Release()=0;


public:
	const Vector2 GetPosition() const { return m_vPosition; }
	void SetPosition(const Vector2& pos) { m_vPosition = pos; }

	const Vector2 GetSize() const { return m_vSize; }
	void SetSize(const Vector2& size) { m_vSize = size; }

	const RECT* Get_Rect() { return &m_tRect; }

	void Set_Target(CCreature* tTarget) { m_tTarget = tTarget; }
protected:
	RECT			m_tRect;		// °´Ã¼ÀÇ ·»´õ ¹üÀ§

	// Core components
	Vector2			m_vPosition;	// °´Ã¼ÀÇ À§Ä¡, ÁßÁ¡
	//Vector2			m_vDirection;	// °´Ã¼ÀÇ ¹æÇâ
	Vector2			m_vSize;		// °´Ã¼ÀÇ Å©±â
	Vector2			m_vCollSize;

	CCreature* m_tTarget;

	virtual bool IsColl()= 0 ;
public:

	void Update_Rect();
	void Font(HDC hdc, RECT rc, const WCHAR* str, int nHeight, int nWidth, int nWeight, int line);
	void DrawHP(HDC hDC, float x, float y, float width, float height, float Hp, float MaxHp, HP_DIR dir = HP_DIR::LeftToRight);
};

