#pragma once
#include "CObj.h"
#include "Define.h"
class CCreature :
    public CObj
{
public:
	CCreature();
	virtual ~CCreature();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	void Move_Frame();

	void Move_EffectFrame();

	virtual void On_Collision(CObj* obj) = 0;

public:
	CREATURE_ID Get_ID() { return m_ID; }
	void Set_ID(CREATURE_ID id) { m_ID = id; }
	bool Get_Dead() { return m_bDead; }

	void			Set_FrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	void			Set_Direction(DIRECTION eDir) { m_eDir = eDir; }

public: // Object's stats getter-setter 
	float			Get_HP() { return m_fHP; }
	float			Get_MaxHP() { return m_fMaxHP; }
	float			Get_Damage() { return m_fDamage; }

	void			Set_HP(float _HP) { m_fHP = _HP; }
	void			Set_MaxHP(float _HP) { m_fMaxHP = _HP; }
	void			Set_Damage(float _damage) { m_fDamage = _damage; }

protected:
	CREATURE_ID m_ID;

	Vector2 m_vBarrelDir;

	CObj* m_tTarget;

	bool m_bDead;
	DIRECTION	m_eDir;

	// 애니메이션
	FRAME		m_tFrame;
	const TCHAR* m_pFrameKey;

	//이팩트 애니메이션
	Vector2 m_vEFPos;
	FRAME		m_tEFFrame;
	const TCHAR* m_pEFFrameKey;

	// 점프 및 착지 관련 변수
	bool  m_bJump;
	float m_fSpeedY;
	int   m_iPlayerJumpCount;		// 플레이어가 점프 입력 카운트. 착지하면 0이 됨
	int   m_iPlayerMaxJump;			// 한 번 체공 중 점프 몇 번 가능하게 만들건지
	float m_fGroundY;				// Collision_Line이 전달해 주는, 착지해야 할 y좌표 저장
	bool  m_bPlayerLanded;			// 플레이어가 착지 중일 때 true


	float			m_fHP;
	float			m_fMaxHP;
	float			m_fDamage;
};

