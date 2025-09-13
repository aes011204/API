#pragma once
class CObj;
class CCollisionMgr
{
public:
	static void Collision_Rect(list<CObj*> src, list<CObj*> dst);
	static void Collision_Circle(list<CObj*> src, list<CObj*> dst);
	static bool Check_Circle(CObj* src, CObj* dst);

	static void Collision_RectEx(list<CObj*> src, list<CObj*> dst);
	static bool Check_Rect(CObj* src, CObj* dst, float* pX, float* pY);

};

