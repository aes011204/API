#pragma once
class CObj;
class CColliderComp;

class CCollisionMgr
{
public:
	static void Collision_Rect(list<CObj*> src, list<CObj*> dst);
	static void Collision_Circle(list<CObj*> src, list<CObj*> dst);
	static bool Check_Circle(CColliderComp& src, CColliderComp& dst);
	//static bool Check_Circle(auto& src, auto& dst);

	static void Collision_RectEx(list<CObj*> src, list<CObj*> dst);
	static bool Check_Rect(CColliderComp& src, CColliderComp& dst, float* pX, float* pY);
	//static bool Check_Rect(auto& src, auto& dst, float* pX, float* pY);

};

