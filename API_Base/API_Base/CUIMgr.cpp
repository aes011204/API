#include "pch.h"
#include "CUIMgr.h"
#include "CBmpMgr.h"
#include "CUI.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{
	Release();
}

//void CUIMgr::Initialize()
//{
//
//
//}
//
void CUIMgr::Add_Object(CUI* pUI)
{
	if (pUI == nullptr)
		return;
	m_UIList.push_back(pUI);
}

int CUIMgr::Update()
{
	for (auto& iter : m_UIList)
	{
		iter->Update();
	}
	return 0;
}

int CUIMgr::Late_Update()
{
	//for (auto& iter : m_UIList)
	//{
	//	iter->Late_Update();
	//}

	for (auto it = m_UIList.begin(); it != m_UIList.end();)
	{
		int result = (*it)->Late_Update();
		if (result == OBJ_DEAD)
		{
			//if (!m_UIList.empty())
			{
				Safe_Delete<CUI*>(*it);
				m_UIList.erase(it);

			}
			//else
				//return OBJ_DEAD;
		}
		else
		{
			++it;
		}
	}
	return 0;
}

void CUIMgr::Render(HDC hDC)
{
	for (auto& iter : m_UIList)
	{
		iter->Render(hDC);
	}
}

void CUIMgr::Release()
{
	//for_each(m_UIList.begin(), m_UIList.end(), [](auto& p) {if (p) { delete p; p = nullptr; }});
	//m_UIList.clear();

	for (auto& p : m_UIList)
	{
		delete p;   // 메모리 해제
		p = nullptr; // 포인터 초기화
	}
	m_UIList.clear(); // 컨테이너 초기화
}
