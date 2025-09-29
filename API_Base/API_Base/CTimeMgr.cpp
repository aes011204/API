#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr() : m_dDeltaTime(0.) , m_dAcc(0.), m_iCallCount(0), m_iFPS(0)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Initialize()
{
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

int CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double) m_llFrequency.QuadPart;

	m_llPrevCount = m_llCurCount; // 다음 계산을 위해
	if (m_dDeltaTime > 0.04)
		m_dDeltaTime = 0.04f;

	++m_iCallCount;
	m_dAcc += m_dDeltaTime;
	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		{
			/*if (!IsWindow(g_hWnd))
			{
				MessageBox(nullptr, L"g_hWnd가 유효하지 않습니다!", L"Error", MB_OK);
			}*/
			// 창 이름에 fps 출력
			TCHAR		m_szFPS[64] = {};
			swprintf_s(m_szFPS, L"FPS : %d, DT : %f", m_iFPS, m_dDeltaTime);

			SetWindowText(g_hWnd, m_szFPS);
		}

		m_dAcc = 0.f;
		m_iCallCount = 0;


	}
	return 0;
}
