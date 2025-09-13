#include "pch.h"
#include "CKeyMgr.h"

CKeyMgr::CKeyMgr()
{
	bool m_bKeyState[VK_MAX];
	ZeroMemory(m_bCurKeyState, sizeof(m_bCurKeyState));
	ZeroMemory(m_bPrevKeyState, sizeof(m_bPrevKeyState));
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Pressing(int iKey)
{
	if (m_bPrevKeyState[iKey] && m_bCurKeyState[iKey])
		return true;
	else
		return false;
}

bool CKeyMgr::Key_Up(int iKey)
{
	if (!m_bPrevKeyState[iKey] && m_bCurKeyState[iKey])
		return true;
	else
		return false;
}

bool CKeyMgr::Key_Down(int iKey)
{
	if (m_bPrevKeyState[iKey] && !m_bCurKeyState[iKey])
		return true;
	else
		return false;
}

void CKeyMgr::Key_Update()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		SHORT KeyState = GetAsyncKeyState(i);

		m_bPrevKeyState[i] = m_bCurKeyState[i];
		m_bCurKeyState[i] = (KeyState & 0x8000) != 0;
	}

	POINT ptPos = {};
	GetCursorPos(&ptPos);
	ScreenToClient(g_hWnd, &ptPos);

	Vector2 tmp = { (float)ptPos.x,(float) ptPos.y };
	m_vCurMousePos = tmp;
}
