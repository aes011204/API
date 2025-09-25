#include "pch.h"
#include "CObjMgr.h"
#include "CCreature.h"
#include "CNonCreature.h"
#include "CObj.h"
#include "CCollisionMgr.h"
CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}



int CObjMgr::Update()
{
	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto it = m_ObjList[i].begin(); it != m_ObjList[i].end();)
		{
			int result =(*it)->Update();

			if (result == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*it);
				it = m_ObjList[i].erase(it);
				
			}
			else
			{
				++it;
			}
		}
	}
	//


	return 0;
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();
		}
	}

	CCollisionMgr::Collision_Rect(m_ObjList[PLAYER], m_ObjList[ITEM]);
	//CCollisionMgr::Collision_Circle(m_ObjList[PL_BULLET], m_ObjList[MONSTER]);
	//CCollisionMgr::Collision_Circle(m_ObjList[MON_BULLET], m_ObjList[PLAYER]);
	CCollisionMgr::Collision_Rect(m_ObjList[MONSTER], m_ObjList[PLAYER]);
	CCollisionMgr::Collision_Rect(m_ObjList[BOSS], m_ObjList[PLAYER]);
	CCollisionMgr::Collision_Rect(m_ObjList[BULLET], m_ObjList[PLAYER]);

	CCollisionMgr::Collision_Rect(m_ObjList[PLAYER], m_ObjList[DOOR]);
	CCollisionMgr::Collision_Rect(m_ObjList[PLAYER], m_ObjList[NPC]);
	
	CCollisionMgr::Collision_Rect(m_ObjList[BULLET], m_ObjList[WALL]);


#pragma region ÇÃ·¹ÀÌ¾î - ÇÃ·§Æû °£ Ãæµ¹
	CCollisionMgr::Collision_Rect(m_ObjList[PLAYER], m_ObjList[PLATFORM]);
#pragma endregion

#pragma region ¸ó½ºÅÍ - ÇÃ·§Æû °£ Ãæµ¹
	CCollisionMgr::Collision_Rect(m_ObjList[MONSTER], m_ObjList[PLATFORM]);
#pragma endregion


	CCollisionMgr::Collision_RectEx(m_ObjList[PLAYER], m_ObjList[WALL]);


#pragma region ÃÑ¾Ë - ÇÃ·§Æû °£ Ãæµ¹
	//CCollisionMgr::Collision_Rect(m_ObjList[PL_BULLET], m_ObjList[PLATFORM]);
	//CCollisionMgr::Collision_Rect(m_ObjList[MON_BULLET], m_ObjList[PLATFORM]);
#pragma endregion


}

void CObjMgr::Render(HDC hdc)
{
	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Render(hdc);
		}
	}

}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJ_END; i++)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(),
			[](auto& p) {if (p) { delete p; p = nullptr; }});

		m_ObjList[i].clear();
	}




}

void CObjMgr::Add_Object(CObj* pObj)
{
	if (pObj == nullptr)
		return;

		m_ObjList[pObj->Get_ID()].push_back(pObj);



}


