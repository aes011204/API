#pragma once
#include "CItem.h"
class CItemDB
{

private:
	CItemDB();
	~CItemDB();

	CItemDB(const CItemDB& rhs) = delete;
	CItemDB& operator=(CItemDB& rMgr) = delete;

public:
	void Initialize();

	CItem* Get_ItemBase();
private:
	unordered_map<const TCHAR*, CItem*> m_ItemBase;
		//map<const TCHAR*, CItem*> m_ItemBase;
#pragma region Singleton
public:
	static CItemDB* Get_Instance() //멤버 함수 자체를 정적으로 만들어서, 객체 없이 호출 가능
	{
		static CItemDB m_Instance; // 지역 정적 변수를 만들어서, 싱글톤 인스턴스를 단 한 번만 생성

		return &m_Instance;
	}
#pragma endregion

};

