#pragma once
#include "CObj.h"
#include "CUI.h"
#include "CButton.h"
#include "CCreature.h"
#include "CTile.h"
#include "CBossHand.h"
#include "CItem.h"
template<typename T>
class CAbstractFactory
{
public:

	static CObj* Create()
	{
		CObj* obj = new T;
		obj->Initialize();

		return obj;
	}
	static CBossHand* CreateHand(CBossHand::LR lr)
	{
		CBossHand* obj = new T(lr);
		obj->Initialize();

		return obj;
	}
	static CObj* Create(Vector2 pos)
	{
		CObj* obj = new T;
		obj->Initialize();

		obj->SetPosition(pos);


		return obj;
	}

	static CObj* Create(Vector2 pos, Vector2 size, Vector2 _dir)
	{
		CObj* obj = new T;
		obj->Initialize();

		obj->SetPosition(pos);
		obj->SetSize(size);
		obj->SetDirection(_dir);

		return obj;
	}

	static CObj* CreateTile(Vector2 pos, Vector2 size)
	{
		CObj* obj = new T();
		obj->Initialize();

		obj->SetPosition(pos);
		obj->SetSize(size);

		return obj;
	}
	static CObj* Create(Vector2 pos, Vector2 size)
	{
		CObj* obj = new T(pos, size);
		obj->Initialize();



		//obj->SetPosition(pos);
		//obj->SetSize(size);

		return obj;
	}

	//static CTile* CreateTile(Vector2 pos, Vector2 size)
	//{
	//	CTile* obj = new T;
	//	obj->Initialize();
	//
	//	obj->SetPosition(pos);
	//	obj->SetSize(size);
	//
	//	return obj;
	//}

	static CUI* CreateUI(CCreature* creature)
	{
		CUI* ui = new T;
		ui->Set_Target(creature);

		ui->Initialize();

		return ui;
	}

	static CUI* CreateUI()
	{
		CUI* ui = new T;


		ui->Initialize();

		return ui;
	}	
	static CUI* CreateUI(Vector2 pos)
	{
		CUI* ui = new T;


		ui->Initialize();
		ui->SetPosition(pos);

		return ui;
	}
	static CUI* CreateUIButton(Vector2 pos, Vector2 Size, const TCHAR* off, const TCHAR* on, const function<void()>& fn, float SizeMul = 1.f)
	{
		CButton* ui = new T;

		ui->SetPosition(pos);
		ui->SetSize(Size);

		ui->Set_FrameKeyOff(off);
		ui->Set_FrameKeyOn(on);

		ui->SetOnClick(fn);
		ui->SetSizeMul(SizeMul);

		ui->Initialize();
		return ui;
	}

	static CItem* CreateItem(CItem::ITEMTYPE itemType, CItem::ITEMSTATE m_eItemState , CItem::ITEMCLASS m_eItemClass)
	{
		CItem* tmp = new T;
		tmp->Initialize();

		tmp->SetItemState(m_eItemState);
		tmp->SetItemType(itemType);
		tmp->Set_ItemClass(m_eItemClass);

		return tmp;
	}

};