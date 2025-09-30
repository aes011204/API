#pragma once
#include "CMonster.h"
class CUI;

class CMonsterBigSkull :
    public CMonster
{
	
	public:
		enum MONSTATE { IDLE = 0, BULLETATTACK, SWORDATTACK, DEMAGE, DEAD,MOVE, ST_END };
	public:
		CMonsterBigSkull();
		CMonsterBigSkull(Vector2 pos, Vector2 size)
			: CMonster(pos, size), m_eCurState(ST_END), m_ePreState(ST_END), m_hitFlash(false), m_bSwordDone(false), SwordCountMax(5) {
		}
		virtual ~CMonsterBigSkull();
	public:
		void Initialize();
		int Update();
		void Late_Update();
		void Render(HDC hdc);
		void Release();


		virtual void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other);

		
		void SwordAttack();


		void Motion_Change();
		void Do_Attack();


		void Take_Damage(int damage);

		Vector2 RotateVector(Vector2& v, float angle);
		void DeadEffect();

		void Move();

	private:

		MONSTATE	m_eCurState;
		MONSTATE	m_ePreState;
		int m_nextIndex = 0;

		bool m_hitFlash;

		float m_HitTime = 0.f;
		float m_HitTimeMax = 0.f;

		float accTime = 0.f;

		float idelTime = 0.f;
		float idelTimeMax = 0.f;


		int HandCount = 0;

		float SwordTime = 0.f;
		float SwordTimeMax = 0.f;
		int SwordCount = 0;
		int SwordCountMax;
		bool m_bSwordDone;


		int m_iAngle;
		int m_iBarrelNum;
		int Rand = 0;

		float DeadTime = 0.f;
		float DeadTimeMax = 0.f;

		CUI* statebar;

		FRAME m_tEFFrame;
		Vector2 m_vRealSize;
	
		bool m_bOnAttack= false;
		float m_AttackTime= 0.0f;
		float m_AttackTimeMax = 0.f;

		bool m_bStart = false;

};

