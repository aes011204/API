#include "pch.h"
#include "CSceneMgr.h"
#include "CMainMenu.h"
#include "CStage.h"
#include "CVillage.h"

CSceneMgr::CSceneMgr() : m_pScene(nullptr), m_eCurSceneID(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();

}

void CSceneMgr::Change_Stage(SCENEID eID)
{
	if (m_eCurSceneID == eID)
		return;
	if (m_pScene)
	{
		m_pScene->Release();
		Safe_Delete<CScene*>(m_pScene);

	}

	switch (eID)
	{
	case SC_MAINMENU:
		m_pScene = new CMainMenu;
		break;
	case SC_VILLAGE:
		m_pScene = new CVillage;
		break;
	case SC_STAGE:
		m_pScene = new CStage;
		break;
	//case SC_MAINMENU:
	//	m_pScene = new CMainMenu;
	//	break;
	//case SC_MAINMENU:
	//	m_pScene = new CMainMenu;
	//	break;
	//case SC_MAINMENU:
	//	m_pScene = new CMainMenu;
	//	break;
	}

	m_pScene->Initialize();

	m_eCurSceneID = eID;

}

int CSceneMgr::Update()
{
	if (m_pScene)
		m_pScene->Update();
	return 0;
}

void CSceneMgr::Late_Update()
{
	if (m_pScene)
		m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	if (m_pScene)
		m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
