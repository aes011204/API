#pragma once
#include "CObj.h"
#include "Define.h"
class CCreature :
    public CObj
{
public:
	CCreature();
	CCreature(Vector2 pos, Vector2 size) : CObj(pos, size), m_tTarget(nullptr), m_eDir(DIR_END), m_iDamage(0), m_iLevel(0), m_iMaxHP(0), m_iHP(0),
		m_bJump(false),
		m_fSpeedY(0.f),
		m_iPlayerJumpCount(0),
		m_iPlayerMaxJump(2),
		m_fGroundY(0.f),
		m_bPlayerLanded(false) 
	{}
	virtual ~CCreature();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	void Landed_Platform(CObj* pObj, CColliderComp& my, CColliderComp& other);

	//void Landed_Platform(CObj* pObj);



	

	//virtual void On_Collision(CObj* obj, ColliderType my, ColliderType other) = 0;
	//virtual void On_Collision(CObj* obj, vector<CColliderComp>::iterator my, vector<CColliderComp>::iterator other) = 0;
	virtual void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) = 0;
public:

	void			Set_FrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	virtual void	Take_Damage(int _damage)=0;
	//void			Set_Direction(DIRECTION eDir) { m_eDir = eDir; }

public: // Object's stats getter-setter 
	int			Get_HP() { return m_iHP; }
	int			Get_MaxHP() { return m_iMaxHP; }
	int			Get_Damage() { return m_iDamage; }
	DR				Get_Dir()	const { return m_eDir; }
	int			Get_Level() { return m_iLevel; }

	void			Set_HP(int _HP) { m_iHP = _HP; }
	void			Set_MaxHP(int _HP) { m_iMaxHP = _HP; }
	void			Set_Damage(int _damage) { m_iDamage = _damage; }
	void			Set_Dir(DR dir) { m_eDir = dir; }

	bool Get_Jump() const { return m_bJump; }
	bool Get_PlayerLanded() const { return m_bPlayerLanded; }

	void Set_PlayerLanded(bool bLanded) { m_bPlayerLanded = bLanded; }
	void Set_Jump(bool bJump) { m_bJump = bJump; }
	void Set_JumpCount(int JumpCount) { m_iPlayerJumpCount = JumpCount; }
	void Set_SpeedY(float SpeedY) { m_fSpeedY = SpeedY; }

	Vector2 GetBarrelDir() const { return m_vBarrelDir; }
	Vector2 GetBarrelPos() const { return m_vBarrelPos; }

	void SetBarrelDir(const Vector2& vDir) { m_vBarrelDir = vDir; }
	void SetBarrelPos(const Vector2& vPos) { m_vBarrelPos = vPos; }
protected:

	Vector2 m_vBarrelDir;
	Vector2 m_vBarrelPos;
	CObj* m_tTarget;


	// 애니메이션

	DR		m_eDir;

	////이팩트 애니메이션
	//Vector2 m_vEFPos;
	//FRAME		m_tEFFrame;
	//const TCHAR* m_pEFFrameKey;

	// 점프 및 착지 관련 변수
	bool  m_bJump;
	float m_fSpeedY;
	int   m_iPlayerJumpCount;		// 플레이어가 점프 입력 카운트. 착지하면 0이 됨
	int   m_iPlayerMaxJump;			// 한 번 체공 중 점프 몇 번 가능하게 만들건지
	float m_fGroundY;				// Collision_Line이 전달해 주는, 착지해야 할 y좌표 저장
	bool  m_bPlayerLanded;			// 플레이어가 착지 중일 때 true


	int			m_iHP;
	int			m_iMaxHP;
	int			m_iDamage;
	int			m_iLevel;
};

