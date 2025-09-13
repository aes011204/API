#pragma once
#include "CScene.h"

class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

public:
public:
	void		Change_Stage(SCENEID eID);
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

private:

	CScene* m_pScene;

	SCENEID		m_eCurSceneID;
	//SCENEID		m_ePreSceneID;


#pragma region Singleton
public:
	static CSceneMgr* Get_Instance() //멤버 함수 자체를 정적으로 만들어서, 객체 없이 호출 가능
	{
		static CSceneMgr* m_Instance = new CSceneMgr; // 지역 정적 변수를 만들어서, 싱글톤 인스턴스를 단 한 번만 생성

		return m_Instance;
	}
#pragma endregion
};

