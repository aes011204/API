#include "pch.h"
#include "CSceneMgr.h"
#include "CMainMenu.h"
#include "CStage01.h"
#include "CVillage.h"
#include "CBossStage.h"
#include "CEdit.h"
CSceneMgr::CSceneMgr() : m_pScene(nullptr), m_eCurSceneID(SC_END),  nextScene(SC_END)
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
		//m_pScene->Release();
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
	case SC_STAGE01:
		m_pScene = new CStage01;
		break;
	case SC_BOSS:
		m_pScene = new CBossStage;
		break;
	case SC_STAGE02:
	//	m_pScene = new CStage02;
		break;
	case SC_EDIT:
		m_pScene = new CEdit;
		break;
	}

	m_pScene->Initialize();

	m_eCurSceneID = eID;

}

int CSceneMgr::Update()
{
	if (m_pScene)
		m_pScene->Update();

	if (m_bChange == true)
	{
		Change_Stage(nextScene);
		m_bChange = false;
	}
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

void CSceneMgr::Rq_changeScene(SCENEID next)
{
	m_bChange = true;
	nextScene = next;
}

