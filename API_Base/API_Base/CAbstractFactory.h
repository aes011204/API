#pragma once
#include "CObj.h"

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
};

