#pragma once
#include "CLine.h"

// For testing in Stage04. Can be modified or deleted freely.
// Currently empty
class CLineManager
{
public:
	//enum SIDE { LEFT, RIGHT, SIDE_END };

private:
	CLineManager();
	~CLineManager();

	CLineManager(const CLineManager& rhs)       = delete;
	CLineManager& operator=(CLineManager& rMgr) = delete;

public:
	void Initialize();
	int  Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	bool Collision_Line(Vector2 PlayerPos, float* pY);

public:

	void Create_Line(Vector2* tPoint, int Num);


public:
	//void Save_Data();
	//bool Load_Data();

private:
	list<CLine*> m_LineList;
	//Vector2    m_tLinePoint;

	float prevDistance = 0.f;
	float Distance = 0.f;
	float prevY = 0.f;

#pragma region Singleton
public:
	static CLineManager* Get_Instance() //멤버 함수 자체를 정적으로 만들어서, 객체 없이 호출 가능
	{
		static CLineManager m_Instance; // 지역 정적 변수를 만들어서, 싱글톤 인스턴스를 단 한 번만 생성

		return &m_Instance;
	}
#pragma endregion
};
