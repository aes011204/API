#include "pch.h"
#include "CTileMgr.h"
#include "CAbstractFactory.h"
#include "CCamera.h"
//#include "ScrollMgr.h"



CTileMgr::CTileMgr()
{
	m_vecTile.reserve(TILEX * TILEY);
	m_vTileSize = { TILECX*2, TILECY*2  };
}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = (float)(m_vTileSize.x /2) + (m_vTileSize.x * j);
			float fY = (float)(m_vTileSize.y / 2) + (m_vTileSize.y * i);
			
			CObj* pTile = CAbstractFactory<CTile>::Create({ fX, fY }, { m_vTileSize });
			m_vecTile.push_back(pTile);
		}
	}

}

void CTileMgr::Update()
{
	for (auto& pTile : m_vecTile)
		pTile->Update();

}

void CTileMgr::Late_Update()
{
	for (auto& pTile : m_vecTile)
		pTile->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{

	// for (auto& pTile : m_vecTile)
	// 	pTile->Render(hDC);

	//int iScrollCulX = abs((int)ScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	//int iScrollCulY = abs((int)ScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	//int iMaxX = /*iScrollCulX + */ (WINCX / TILECX) + 2;
	//int iMaxY = /*iScrollCulY + */ (WINCY / TILECY) + 2;
	//
	//for (int i = /*iScrollCulY*/0; i < iMaxY; ++i)
	//{
	//	for (int j = /*iScrollCulX*/0; j < iMaxX; ++j)
	//	{
	//		int iIndex = i * TILEX + j;
	//
	//		if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
	//			continue;
	//
	//		m_vecTile[iIndex]->Render(hDC);
	//	}
	//}

	Vector2 look = CCamera::Get_Instance()->GetLookAt();

	Vector2 center = { WINCX * 0.5f, WINCY * 0.5f };
	Vector2 RenderSize = CCamera::Get_Instance()->GetRenderSize(m_vTileSize);

	//화면에 보이는 화면의 좌 상단을 타일 좌표로 지점 의 시작점 센다
	Vector2  LeftTop = {(int)floor( (look.x - center.x)/ RenderSize.x),(int)floor((look.y - center.y )/ RenderSize.y)};
	Vector2 m_vScreenTileNum = { (int)ceil(WINCX / RenderSize.x)+2 ,(int)ceil(WINCY / RenderSize.y)+2 };

	Vector2  RightBottom = m_vScreenTileNum + LeftTop;

	//CCamera::Get_Instance()->GetRealPos();
	// 맵 경계로 클램프(TILEX / TILEY = 전체 타일 수)
	LeftTop.x = max(0, LeftTop.x);
	LeftTop.y = max(0, LeftTop.y);
	RightBottom.x = min(TILEX, RightBottom.x);
	RightBottom.y = min(TILEY, RightBottom.y);


	for (int i = LeftTop.y; i < RightBottom.y; ++i)
	{
		for (int j = LeftTop.x; j < RightBottom.x; ++j)
		{
			int iIndex = i * TILEX + j;

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			m_vecTile[iIndex]->Render(hDC);
		}
	}
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), [](auto& p) {if (p) { delete p; p = nullptr; }});
	m_vecTile.clear();
}

void CTileMgr::Picking(POINT pt, Vector2 iDrawID, int iOption)
{
	Vector2 mos = CCamera::Get_Instance()->GetRealPos({(float)pt.x,(float)pt.y});

	int x = mos.x / m_vTileSize.x;
	int y = mos.y / m_vTileSize.y;

	int iIndex = y * TILEX + x;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);

}

void CTileMgr::Save_Data()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat", // 파일 경로(이름까지 명시)
		GENERIC_WRITE,		// 파일 접근 모드(GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,				// 공유 모드 설정 : 공유하지 않음
		NULL,				// 보안 속성 설정 : 기본 값 설정
		CREATE_ALWAYS,		// 생성 방식 : 쓰기 전용인 경우 파일이 없으면 생성하여 저장, OPEN_EXISTING : 읽기 전용 모드일 때 파일이 있을 경우에만 불러오기 실행)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성 : 일반 파일
		NULL); // 생성될 파일의 속성을 제공할 템플릿 파일 주소(사용하지 않기 때문에 null)
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"Save Failed", _T("Error"), MB_OK);
		return;
	}
	
	DWORD	dwByte(0);
	Vector2 iDrawID{};
	Vector2 pos{};
	Vector2 size{};
	int	 iOption(0);
	
	for (auto& pTile : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();
	
		pos = dynamic_cast<CTile*>(pTile)->GetPosition();
		size = dynamic_cast<CTile*>(pTile)->GetSize();

		WriteFile(hFile, &pos, sizeof(Vector2), &dwByte, nullptr);
		WriteFile(hFile, &size, sizeof(Vector2), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(Vector2), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
	}
	
	CloseHandle(hFile);
	
	MessageBox(g_hWnd, L"Save Success", _T("축하"), MB_OK);
}

void CTileMgr::Load_Data()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat", // 파일 경로(이름까지 명시)
		GENERIC_READ,		// 파일 접근 모드(GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,				// 공유 모드 설정 : 공유하지 않음
		NULL,				// 보안 속성 설정 : 기본 값 설정
		OPEN_EXISTING,		// 생성 방식 : 쓰기 전용인 경우 파일이 없으면 생성하여 저장, OPEN_EXISTING : 읽기 전용 모드일 때 파일이 있을 경우에만 불러오기 실행)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성 : 일반 파일
		NULL); // 생성될 파일의 속성을 제공할 템플릿 파일 주소(사용하지 않기 때문에 null)
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"Load Failed", _T("Error"), MB_OK);
		return;
	}
	
	DWORD	dwByte(0);
	Vector2 iDrawID{};
	Vector2 pos{};
	Vector2 size{};
	int		 iOption(0);
	
	Release();
	
	while (true)
	{
		ReadFile(hFile, &pos, sizeof(Vector2), &dwByte, nullptr);
		ReadFile(hFile, &size, sizeof(Vector2), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(Vector2), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
	
		if (0 == dwByte)
			break;
	
		CObj* pTile = CAbstractFactory<CTile>::Create(pos,size);
	
		dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->Set_Option(iOption);
		m_vecTile.push_back(pTile);		
	}
	
	CloseHandle(hFile);
	
	MessageBox(g_hWnd, L"Load Success", _T("축하"), MB_OK);
}
