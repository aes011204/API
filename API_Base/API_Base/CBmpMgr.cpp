#include "pch.h"
#include "CBmpMgr.h"
#include "CMyBmp.h"
CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (m_mapBit.end() == iter)
	{
		CMyBmp* pBmp = new CMyBmp;
		pBmp->LoadBmp(pFilePath);
		m_mapBit.insert({ pImgKey ,pBmp });

	}
}

HDC CBmpMgr::Find_Img(const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MenDC();
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), [](auto& p) {if (p.second) delete p.second; p.second = nullptr;});
	m_mapBit.clear();
}
