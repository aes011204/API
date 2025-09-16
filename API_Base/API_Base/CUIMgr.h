#pragma once

class CObj;
class CUI;

class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

public:
	void	Add_Object(CUI* pUI);
	int Update();
	int Late_Update();
	void Render(HDC hDC);
	void Release();

public:
	list<CUI*>	m_UIList;

#pragma region Singleton
public:
	static CUIMgr* Get_Instance() //멤버 함수 자체를 정적으로 만들어서, 객체 없이 호출 가능
	{
		static CUIMgr m_Instance; // 지역 정적 변수를 만들어서, 싱글톤 인스턴스를 단 한 번만 생성

		return &m_Instance;
	}
#pragma endregion
};

