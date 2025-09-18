#pragma once
#include "CObj.h"
#include "CUI.h"
#include "CButton.h"
#include "CCreature.h"
#include "CTile.h"
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

	static CObj* Create(Vector2 pos, Vector2 size)
	{
		CObj* obj = new T;
		obj->Initialize();

		obj->SetPosition(pos);
		obj->SetSize(size);

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
	static CUI* CreateUIButton(Vector2 pos, Vector2 Size, const TCHAR* off, const TCHAR* on,const function<void()>& fn, float SizeMul=1.f)
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
};

