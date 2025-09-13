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
	static CLineManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLineManager;

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CLineManager* m_pInstance;
#pragma endregion
};
