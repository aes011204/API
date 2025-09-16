#pragma once
#include "CObj.h"
#include "CUI.h"
#include "CButton.h"

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

	static CObj* Create(Vector2 pos)
	{
		CObj* obj = new T;
		obj->Initialize();

		obj->SetPosition(pos);

		return obj;
	}

	static CUI* CreateUI()
	{
		CUI* ui = new T;
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

