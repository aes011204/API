#include "pch.h"
#include "CMyBmp.h"

CMyBmp::CMyBmp()
{
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::LoadBmp(const TCHAR* pFilePath)
{
	HDC hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC); // 호환 백버퍼

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,		// 프로그램 인스턴스 핸들
					pFilePath,  // 파일의 경로
					IMAGE_BITMAP,  // 어떤 타입을 읽어들일 것인가
					0, 0, // 이미지의 가로, 세로 사이즈
					LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					// LR_LOADFROMFILE : 파일에서 이미지 불러들이기 
					// LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형태로 변환

	// SelectObject : 준비한 dc에 gdi 오브젝트로 불러온 비트맵을 선택
	//기GDI 오브젝트를 선택하기 전에 가지고 있던 오브젝트를 반환
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteDC(m_hMemDC);

	DeleteObject(m_hBitmap);
}
