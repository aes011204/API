#pragma once
#include "CCreature.h"
#include "CItem.h"
#include "CInventory.h"
#include "CInventoryUI.h"
class CWeapon;
class CAccecery;
//class CInventoryUI;
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


	void Take_Damage(int damage);
	void Dash(Vector2 tmpdir);
	void LimitPlayerPos();

	int Equip_Item(int invenIndex, CItem* pInvenItem, int num, int setIndex);

	//int Equip_Item(int invenIndex, CItem* pInvenItem, int num);

	//int Equip_Item(CItem* pInvenItem, int num);

	//int Unequip_Item(int num, array<CItem*, 2> Equipinven, int dst);
	int Unequip_Item(int num, CInventoryUI::INVENTYPE type, int dst);
	void Item_Ability(int _Attack, int _Hp);
	CItem* Get_InvenItem(int index, int EquipInvenNum);
	//CInventory& Get_Inven() { return *m_Inven; }
	//void Set_Inven(CInventory* pInven) { m_Inven = pInven; }
public:
	bool  IsDropping() const { return m_bDropDown; }

	void SetStop(bool stop) { m_bStop = stop; }

	CInventory* Get_Inven() { return m_Inven; }

	bool Get_OnAttack() const { return m_bOnAttack; }
	void Set_OnAttack(bool value) { m_bOnAttack = value; }

	bool GetVisible() { return m_visible; }
	void SetVisible(bool visible) { m_visible = visible; }

	bool GetChangeEquip() { return m_ChangeEquip; }

	void SetQuest(bool accept) { m_quest = accept; }


	int GetFromInven() { return fromInven; }
	void SetFromInven(int index) {fromInven = index; }

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

	
	array<CItem*, 2> m_Equipweapon01;
	array<CItem*, 2> m_Equipweapon02;
	array<CItem*, 4> m_EquipAcc;
	CInventory* m_Inven;
	bool m_ChangeEquip = false; //
	int m_equipSlot = 4;

	bool m_bOnAttack =false; 

	float m_AttackTime = 0.f;

	float m_AttackTimeMax =0.f;

	CItem* weapon;

	bool m_visible = true;

	bool m_quest = false;

	int fromInven = -1;
	
};

