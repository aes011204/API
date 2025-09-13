#pragma once
class CCreature;
class CNonCreature;
class CObj;
class CObjMgr
{
private:
	CObjMgr();
	CObjMgr(CObjMgr& rhs) = delete;
	CObjMgr& operator = (CObjMgr& rMgr) = delete;
	~CObjMgr();

public:
	//void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	void Add_Object(CObj* pObj);
	CCreature* Get_Player() { if (!m_CreatureList[PLAYER].empty()) { return m_CreatureList[PLAYER].front(); } else { assert(false); } }

private:
	list<CCreature*> m_CreatureList[CID_END];
	list<CNonCreature*> m_NonCreatureList[NCID_END];

#pragma region Singleton
public:
	static CObjMgr* Get_Instance() //멤버 함수 자체를 정적으로 만들어서, 객체 없이 호출 가능
	{
		static CObjMgr* m_Instance = new CObjMgr; // 지역 정적 변수를 만들어서, 싱글톤 인스턴스를 단 한 번만 생성

		return m_Instance;
	}
#pragma endregion
};

