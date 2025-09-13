#include "pch.h"
#include "CObjMgr.h"
#include "CCreature.h"
#include "CNonCreature.h"
#include "CObj.h"
CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}



int CObjMgr::Update()
{
	for (int i = 0; i < CID_END; i++)
	{
		for (auto it = m_CreatureList[i].begin(); it != m_CreatureList[i].end();)
		{
			int result =(*it)->Update();
			if (result == OBJ_DEAD)
			{
				Safe_Delete<CCreature*>(*it);
				m_CreatureList[i].erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	//

	for (int i = 0; i < NCID_END; i++)
	{
		for (auto it = m_NonCreatureList[i].begin(); it != m_NonCreatureList[i].end();)
		{
			int result = (*it)->Update();
			if (result == OBJ_DEAD)
			{
				Safe_Delete<CNonCreature*>(*it);
				m_NonCreatureList[i].erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	return 0;
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < CID_END; i++)
	{
		for (auto& iter : m_CreatureList[i])
		{
			iter->Late_Update();
		}
	}


	for (int i = 0; i < NCID_END; i++)
	{
		for (auto& iter : m_NonCreatureList[i])
		{
			iter->Late_Update();
		}
	}
}

void CObjMgr::Render(HDC hdc)
{
	for (int i = 0; i < CID_END; i++)
	{
		for (auto& iter : m_CreatureList[i])
		{
			iter->Render(hdc);
		}
	}

	for (int i = 0; i < NCID_END; i++)
	{
		for (auto& iter : m_NonCreatureList[i])
		{
			iter->Render(hdc);
		}
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < CID_END; i++)
	{
		for_each(m_CreatureList[i].begin(), m_CreatureList[i].end(),
			[](auto& p) {if (p) { delete p; p = nullptr; }});

		m_CreatureList[i].clear();
	}


	for (int i = 0; i < NCID_END; i++)
	{
		for_each(m_NonCreatureList[i].begin(), m_NonCreatureList[i].end(), [](auto& p) {if (p) { delete p; p = nullptr; }});
	}

}

void CObjMgr::Add_Object(CObj* pObj)
{
	if (pObj == nullptr)
		return;
	if (CCreature* creature = dynamic_cast<CCreature*>(pObj) )
	{

		m_CreatureList[creature->Get_ID()].push_back(creature);

	}
	else if (CNonCreature* creature = dynamic_cast<CNonCreature*>(pObj))
	{
		m_NonCreatureList[creature->Get_ID()].push_back(creature);
	}
}


