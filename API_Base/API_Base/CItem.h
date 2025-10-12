#pragma once
#include "CObj.h"
class CItem : public CObj
{
public:
	enum ITEMTYPE {TWOHAND, ONEHAND,SUBWEAPON,ACCECERY,IT_END,};
	enum  ITEMSTATE { EQUIP, UNEQUIP, ST_END };
	enum ITEMCLASS { BEGGINER, RARE, UNIQUE, IC_END };

public:
	CItem();
	virtual ~CItem();
public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;
public:

	int GetQuantity() { return iQuantity; }
	void AddQuantity(int _iQuantity);
	void MinusQuantity(int _iQuantity);
	//static Item* CreateItem( const char* _name, ITEMTYPE _type, int _hpAmount, int _MpAmount, int _attackAmount);

	virtual void ItemInfo() = 0;
	const TCHAR* GetName() { return strName; }
	void SetName(TCHAR* _name) { strName = _name; }

	ITEMTYPE GetItemType() { return itemType; }
	void SetItemType(ITEMTYPE _itemType) { itemType = _itemType; }


	ITEMSTATE GetItemState() { return m_eItemState; }
	void SetItemState(ITEMSTATE _itemState) { m_eItemState = _itemState; }

	void Set_Cost(int _cost) { iCost = _cost; }
	int Get_Cost() { return iCost; }

	int GetDamage() { return m_iDamage; }
	void SetDamage(int _iDamage) { m_iDamage = _iDamage; }
	int Get_Defense() const { return m_iDefense; }
	void Set_Defense(int value) { m_iDefense = value; }
	ITEMCLASS Get_ItemClass() const { return m_eItemClass; }
	void Set_ItemClass(ITEMCLASS eClass) { m_eItemClass = eClass; }
	void Set_IconImgSize(const Vector2& size) { m_iconImgSize = size; }

	void Set_IconKey(const TCHAR* key) { m_pIconKey = key; }
	Vector2 Get_IconImgSize() const { return m_iconImgSize; }
	const TCHAR* Get_IconKey() const { return m_pIconKey; }
	
protected:
	const TCHAR* strName;
	ITEMTYPE itemType = IT_END;
	ITEMSTATE m_eItemState = ST_END;
	ITEMCLASS m_eItemClass = IC_END;

	int m_iDefense = 0;
	float m_AttackCountSec = 0.f;
	int  m_iDamage = 0;
	int iQuantity = 0;
	int iCost = 0;

	// CObj을(를) 통해 상속됨

	void On_Collision(CObj* obj, CColliderComp& my, CColliderComp& other) ;

	Vector2 m_iconImgSize;
	//Vector2 m_
	const TCHAR* m_pIconKey ;
};

