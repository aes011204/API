#pragma once
#include "CCreature.h"
class CPlayer :
    public CCreature
{
public:
	enum PLAYERSTATE { IDLE, WALK, JUMP, ATTACK, DASH, DEAD, PS_END };

public:
	CPlayer();
	virtual ~CPlayer();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();



	virtual void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other);

	void Key_Input();
	void Motion_Change();

	//void Move_EffectFrame(HDC hdc);
	void Take_Damage(int damage);
	void Dash(Vector2 tmpdir);
	void LimitPlayerPos();
public:
	bool  IsDropping() const { return m_bDropDown; }
	//void  StartDrop(float t) { m_bDropDown = true; m_dropRemain = t; }
	void SetStop(bool stop) { m_bStop = stop; }
private:

	bool  m_bDropDown = false;   // 아래로 내려가는 중인가
	float m_dropRemain = 0.f;    // 충돌 무시 남은 시간(초)


	PLAYERSTATE	m_eCurState;
	PLAYERSTATE	m_ePreState;
	float m_fInvincibleTime;
	float accTime = 0.f;

	//대쉬 변수

	bool m_bDash;
	float m_DashSpeed;
	float m_DashTime;
	float m_DashDuration;
	Vector2 m_vDashDir;

	bool m_bStop;

	
	FRAME m_tEFFrame;
	float EffTime =0.f;
	float EffTimeMax=0.f;

};

