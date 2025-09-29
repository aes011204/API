#pragma once
#include "CCreature.h"


class CBossHand :
    public CCreature
{
public:
enum	 LR {HAND_LEFT,HAND_RIGHT, HAND_END};
	enum HANDSTATE { IDLE, ATTACK, HS_END };
	CBossHand();
	CBossHand(LR leftright) : CCreature(), m_eCurState(HS_END), m_ePreState(HS_END),m_LeftRight(leftright), m_isAttack(false) {}

	virtual ~CBossHand() override;

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:

	virtual void Do_Attack();
	virtual void Take_Damage(float _fDamage) {}

	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) override;
	void Take_Damage(int _damage) override;

	void Motion_Change();

	void SetLeftRight(LR lr) { m_LeftRight = lr; }

	bool Get_IsAttack() const  { return m_isAttack; }
	void Set_IsAttack(bool v)  { m_isAttack = v; }

	void SetAttackPos(Vector2 pos) { m_AttackPos = pos; }
	//bool GetAttackDone() { return m_AttackDone; }
private:
	LR m_LeftRight;

	HANDSTATE m_ePreState;
	HANDSTATE m_eCurState;

	bool m_isAttack;
	//bool m_AttackDone;

	Vector2 m_AttackPos;


	FRAME m_tEFFrameLR;
	FRAME m_tEFFrame;

	bool m_bAttack;
};

